/****************************************************************************
 * ==> PSS_LogicalSystemDocument -------------------------------------------*
 ****************************************************************************
 * Description : Provides a logical system document                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_LogicalSystemDocument.h"

// processsoft
#include "zBaseLib\PSS_GUID.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_LogicalSystemDocument, PSS_BaseDocument)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_LogicalSystemDocument, PSS_BaseDocument)
    //{{AFX_MSG_MAP(PSS_LogicalSystemDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_LogicalSystemDocument
//---------------------------------------------------------------------------
PSS_LogicalSystemDocument::PSS_LogicalSystemDocument() :
    PSS_BaseDocument(),
    m_IsLoaded(false)
{
    m_GUID = PSS_GUID::CreateNewGUID();
}
//---------------------------------------------------------------------------
PSS_LogicalSystemDocument::~PSS_LogicalSystemDocument()
{}
//---------------------------------------------------------------------------
void PSS_LogicalSystemDocument::Serialize(CArchive& ar)
{
    // serialize stamp and base information
    PSS_BaseDocument::Serialize(ar);

    // serialize the environement
    m_LogicalSystemEnvironment.Serialize(ar);

    // if some other information to serialize, do it below
    if (ar.IsStoring())
        ar << m_GUID;
    else
        ar >> m_GUID;
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemDocument::ReadFromFile(const CString& fileName)
{
    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe))
        return FALSE;

    CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);
    loadArchive.m_pDocument  = this;
    loadArchive.m_bForceFlat = FALSE;

    bool result = false;

    TRY
    {
        Serialize(loadArchive);
        result = true;
    }
    CATCH (CArchiveException, e)
    {
        result = false;
    }
    END_CATCH

    loadArchive.Close();
    file.Close();

    if (result)
        SetPathName(fileName, FALSE);

    m_IsLoaded = result;

    return result;
}
//---------------------------------------------------------------------------
bool PSS_LogicalSystemDocument::SaveToFile(const CString& fileName)
{
    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite, &fe))
        return FALSE;

    CArchive saveArchive(&file, CArchive::store | CArchive::bNoFlushOnDelete);
    saveArchive.m_pDocument  = this;
    saveArchive.m_bForceFlat = FALSE;

    bool result = false;

    TRY
    {
        Serialize(saveArchive);
        result = true;
    }
    CATCH (CArchiveException, e)
    {
        result = false;
    }
    END_CATCH

    saveArchive.Close();
    file.Close();

    // after a save, clear the modified flag
    SetModifiedFlag(FALSE);

    return result;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_LogicalSystemDocument::AssertValid() const
    {
        PSS_BaseDocument::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_LogicalSystemDocument::Dump(CDumpContext& dc) const
    {
        PSS_BaseDocument::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
BOOL PSS_LogicalSystemDocument::OnNewDocument()
{
    ASSERT(FALSE);
    return FALSE;
}
//---------------------------------------------------------------------------
