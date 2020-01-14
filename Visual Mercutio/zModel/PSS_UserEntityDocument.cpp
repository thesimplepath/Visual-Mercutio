/****************************************************************************
 * ==> PSS_UserEntityDocument ----------------------------------------------*
 ****************************************************************************
 * Description : Provides an user entity document                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UserEntityDocument.h"

#include "zBaseLib\PSS_GUID.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_UserEntityDocument, PSS_BaseDocument)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UserEntityDocument, PSS_BaseDocument)
    //{{AFX_MSG_MAP(PSS_UserEntityDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UserEntityDocument
//---------------------------------------------------------------------------
PSS_UserEntityDocument::PSS_UserEntityDocument() :
    PSS_BaseDocument(),
    m_IsLoaded(false),
    m_Beta1Format(false)
{
    m_GUID = PSS_GUID::CreateNewGUID();
}
//---------------------------------------------------------------------------
PSS_UserEntityDocument::~PSS_UserEntityDocument()
{}
//---------------------------------------------------------------------------
void PSS_UserEntityDocument::Serialize(CArchive& ar)
{
    // if not beta 1 format and the file is reading
    if ((ar.IsLoading() && !IsBeta1Format()) || ar.IsStoring())
        // serialize stamp and base information
        PSS_BaseDocument::Serialize(ar);

    // serialize the environment
    m_UserGroupEnvironment.Serialize(ar);

    // if some other information to serialize, do it below
    if (ar.IsStoring())
        ar << m_GUID;
    else
    if (!IsBeta1Format())
        ar >> m_GUID;
}
//---------------------------------------------------------------------------
bool PSS_UserEntityDocument::ReadFromFile(const CString& fileName)
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
        // if failed to load the file, then try to load the beta 1 format
        m_Beta1Format = true;
    }
    END_CATCH

    loadArchive.Close();
    file.Close();

    if (m_Beta1Format)
    {
        if (!file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe))
            return FALSE;

        CArchive loadArchiveBeta1(&file, CArchive::load | CArchive::bNoFlushOnDelete);
        loadArchiveBeta1.m_pDocument  = this;
        loadArchiveBeta1.m_bForceFlat = FALSE;

        TRY
        {
            Serialize(loadArchiveBeta1);
            result = TRUE;
        }
        CATCH (CArchiveException, e)
        {
            result = FALSE;
        }
        END_CATCH

        // close all files
        loadArchiveBeta1.Close();
        file.Close();
    }

    if (result)
        SetPathName(fileName, FALSE);

    m_IsLoaded = result;

    return result;
}
//---------------------------------------------------------------------------
bool PSS_UserEntityDocument::SaveToFile(const CString& fileName)
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
    void PSS_UserEntityDocument::AssertValid() const
    {
        PSS_BaseDocument::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_UserEntityDocument::Dump(CDumpContext& dc) const
    {
        PSS_BaseDocument::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
BOOL PSS_UserEntityDocument::OnNewDocument()
{
    ASSERT(FALSE);
    return FALSE;
}
//---------------------------------------------------------------------------
