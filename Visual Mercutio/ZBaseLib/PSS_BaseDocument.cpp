/****************************************************************************
 * ==> PSS_BaseDocument ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic document                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_BaseDocument.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_BaseDocument, CDocument, g_DefVersion)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_BaseDocument, CDocument)
    //{{AFX_MSG_MAP(PSS_BaseDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_BaseDocument
//---------------------------------------------------------------------------
PSS_BaseDocument::PSS_BaseDocument() :
    CDocument()
{}
//---------------------------------------------------------------------------
PSS_BaseDocument::PSS_BaseDocument(const PSS_BaseDocument& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_BaseDocument::~PSS_BaseDocument()
{}
//---------------------------------------------------------------------------
const PSS_BaseDocument& PSS_BaseDocument::operator = (const PSS_BaseDocument& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_BaseDocument::ReadDocument(const CString& fileName)
{
    BOOL           result = FALSE;
    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe))
        return FALSE;

    CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);

    loadArchive.m_pDocument  = this;
    loadArchive.m_bForceFlat = FALSE;

    TRY
    {
        Serialize(loadArchive);
        result = TRUE;
    }
    CATCH(CArchiveException, e)
    {
        result = FALSE;
    }
    END_CATCH

    loadArchive.Close();
    file.Close();

    // if everything is ok, set the path name
    if (result)
        SetPathName(fileName, FALSE);

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseDocument::SaveDocument()
{
    return (GetPathName().IsEmpty()) ? FALSE : DoSave(GetPathName());
}
//---------------------------------------------------------------------------
void PSS_BaseDocument::FillDocumentStampInformationForCreation(const CString& userName)
{
    // update dynamic information of the file stamp
    GetDocumentStamp().SetStampCreationDate(CTime::GetCurrentTime());
}
//---------------------------------------------------------------------------
void PSS_BaseDocument::FillDocumentStampInformationForModification(const CString& UserName)
{
    // update dynamic information of the file stamp
    GetDocumentStamp().SetStampModificationDate(CTime::GetCurrentTime());
}
//---------------------------------------------------------------------------
void PSS_BaseDocument::FillDocumentStampInformationForPublication(const CString& userName, LONG version)
{
    // and therefore, update the folder information for publishing
    GetDocumentStamp().SetPublishVersion(version);
    GetDocumentStamp().SetPublishUser(userName);
    GetDocumentStamp().SetPublishDate(CTime::GetCurrentTime());
}
//---------------------------------------------------------------------------
void PSS_BaseDocument::FillFolderStampInformationForCreation(const CString& userName)
{
    // and therefore, updates the folder information
    GetDocumentStamp().SetCreationUserName(userName);
    GetDocumentStamp().SetCreationDate(CTime::GetCurrentTime());
}
//---------------------------------------------------------------------------
void PSS_BaseDocument::FillFolderStampInformationForModification(const CString& userName)
{
    // and therefore, updates the folder information
    GetDocumentStamp().SetModificationUserName(userName);
    GetDocumentStamp().SetModificationDate(CTime::GetCurrentTime());
}
//---------------------------------------------------------------------------
void PSS_BaseDocument::Serialize(CArchive& ar)
{
    // do write?
    if (ar.IsStoring())
        // write data
        WriteFileStamp(ar, GetDocumentStamp());
    else
    {
        // read data
        const WORD stamp = ReadFileStamp(ar, GetDocumentStamp());

        if (stamp != 0xFFFF)
            AfxThrowArchiveException(CArchiveException::generic);

        if (GetDocumentStamp().GetInternalVersion() > g_VersionFile)
            AfxThrowArchiveException(CArchiveException::badSchema);
    }
}
//---------------------------------------------------------------------------
int PSS_BaseDocument::ReadFileStamp(CArchive& archive, PSS_FolderStamp& stamp)
{
    WORD fileStamp = 0;

    TRY
    {
        archive >> fileStamp;
    }
    CATCH (CArchiveException, e)
    {
        return 0;
    }
    END_CATCH

    // check if the stamp has been set for next generation of files
    if (fileStamp == 0xFFFF)
        archive >> stamp;

    return fileStamp;
}
//---------------------------------------------------------------------------
void PSS_BaseDocument::WriteFileStamp(CArchive& archive, PSS_FolderStamp& stamp)
{
    // set the new version before writing the file
    stamp.SetInternalVersion(g_VersionFile);

    WORD temp = 0xFFFF;

    // put the stamp for differentiate the new generation of files
    archive << temp;
    archive << stamp;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_BaseDocument::AssertValid() const
    {
        CTreeView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_BaseDocument::Dump(CDumpContext& dc) const
    {
        CTreeView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
