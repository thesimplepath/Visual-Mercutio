/****************************************************************************
 * ==> PSS_LogicalRulesDocument --------------------------------------------*
 ****************************************************************************
 * Description : Provides a logical rules document                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_LogicalRulesDocument.h"

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
IMPLEMENT_DYNCREATE(PSS_LogicalRulesDocument, PSS_BaseDocument)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_LogicalRulesDocument, PSS_BaseDocument)
    //{{AFX_MSG_MAP(PSS_LogicalRulesDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_LogicalRulesDocument
//---------------------------------------------------------------------------
PSS_LogicalRulesDocument::PSS_LogicalRulesDocument() :
    PSS_BaseDocument(),
    m_IsLoaded(false)
{
    m_GUID = PSS_GUID::CreateNewGUID();
}
//---------------------------------------------------------------------------
PSS_LogicalRulesDocument::~PSS_LogicalRulesDocument()
{}
//---------------------------------------------------------------------------
void PSS_LogicalRulesDocument::Serialize(CArchive& ar)
{
    // serialize stamp and base information
    PSS_BaseDocument::Serialize(ar);

    // serialize the environement
    m_RulesEnvironment.Serialize(ar);

    // if some other information to serialize, do it below
    if (ar.IsStoring())
        ar << m_GUID;
    else
        ar >> m_GUID;
}
//---------------------------------------------------------------------------
bool PSS_LogicalRulesDocument::ReadFromFile(const CString& fileName)
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
bool PSS_LogicalRulesDocument::SaveToFile(const CString& fileName)
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
    void PSS_LogicalRulesDocument::AssertValid() const
    {
        PSS_BaseDocument::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_LogicalRulesDocument::Dump(CDumpContext& dc) const
    {
        PSS_BaseDocument::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
BOOL PSS_LogicalRulesDocument::OnNewDocument()
{
    ASSERT(FALSE);
    return FALSE;
}
//---------------------------------------------------------------------------
