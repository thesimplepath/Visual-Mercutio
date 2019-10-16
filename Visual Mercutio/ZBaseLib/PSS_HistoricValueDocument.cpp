/****************************************************************************
 * ==> PSS_HistoricValueDocument -------------------------------------------*
 ****************************************************************************
 * Description : Provides an historic value document                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_HistoricValueDocument.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_HistoricValueDocument, CDocument)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_HistoricValueDocument, CDocument)
    //{{AFX_MSG_MAP(PSS_HistoricValueDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_HistoricValueDocument
//---------------------------------------------------------------------------
PSS_HistoricValueDocument::PSS_HistoricValueDocument() :
    CDocument(),
    m_IsLoaded(false)
{}
//---------------------------------------------------------------------------
PSS_HistoricValueDocument::~PSS_HistoricValueDocument()
{}
//---------------------------------------------------------------------------
bool PSS_HistoricValueDocument::ReadFromFile(const CString& fileName)
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
    CATCH(CArchiveException, e)
    {
        result = false;
    }
    END_CATCH

    loadArchive.Close();
    file.Close();

    // if everything is ok, set the path name
    if (result)
        SetPathName(fileName, FALSE);

    // set is loaded member
    m_IsLoaded = result;

    return result;
}
//---------------------------------------------------------------------------
bool PSS_HistoricValueDocument::SaveToFile(const CString& fileName)
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
    CATCH(CArchiveException, e)
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
void PSS_HistoricValueDocument::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
        ar << m_HistoricValueManager;
    else
        ar >> m_HistoricValueManager;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoricValueDocument::AssertValid() const
    {
        CDocument::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoricValueDocument::Dump(CDumpContext& dc) const
    {
        CDocument::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
BOOL PSS_HistoricValueDocument::OnNewDocument()
{
    ASSERT(FALSE);
    return FALSE;
}
//---------------------------------------------------------------------------
