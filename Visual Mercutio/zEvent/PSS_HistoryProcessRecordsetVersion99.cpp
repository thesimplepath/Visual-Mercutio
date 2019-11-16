/****************************************************************************
 * ==> PSS_HistoryProcessRecordsetVersion99 --------------------------------*
 ****************************************************************************
 * Description : Provides an historic process recordset (version 99)        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_HistoryProcessRecordsetVersion99.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_HistoryProcessRecordsetVersion99, CDaoRecordset)
//---------------------------------------------------------------------------
// PSS_HistoryProcessRecordsetVersion99
//---------------------------------------------------------------------------
PSS_HistoryProcessRecordsetVersion99::PSS_HistoryProcessRecordsetVersion99(CDaoDatabase* pDatabase, const CString& fileName) :
    CDaoRecordset(pDatabase),
    m_StartDate(DATE(0)),
    m_EndDate(DATE(0)),
    m_DatabaseFileName(fileName),
    m_ProcessID(0)
{
    m_nFields      = 9;
    m_nDefaultType = dbOpenDynaset;
}
//---------------------------------------------------------------------------
CString PSS_HistoryProcessRecordsetVersion99::GetDefaultDBName()
{
    return _T(m_DatabaseFileName);
}
//---------------------------------------------------------------------------
CString PSS_HistoryProcessRecordsetVersion99::GetDefaultSQL()
{
    return _T(g_HistoryProcessTableName);
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessRecordsetVersion99::DoFieldExchange(CDaoFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(PSS_HistoryProcessRecordsetVersion99)
    pFX->SetFieldType(CDaoFieldExchange::outputColumn);
    DFX_Long    (pFX, _T("[ProcessID]"),    m_ProcessID);
    DFX_Text    (pFX, _T("[Name]"),         m_Name);
    DFX_Text    (pFX, _T("[Filename]"),     m_FileName);
    DFX_Text    (pFX, _T("[FolderName]"),   m_FolderName);
    DFX_Text    (pFX, _T("[DataFeedForm]"), m_DataFeedForm);
    DFX_Text    (pFX, _T("[DataFeedProc]"), m_DataFeedProc);
    DFX_DateTime(pFX, _T("[StartDate]"),    m_StartDate);
    DFX_DateTime(pFX, _T("[EndDate]"),      m_EndDate);
    DFX_Text    (pFX, _T("[Initiator]"),    m_Initiator);
    //}}AFX_FIELD_MAP
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryProcessRecordsetVersion99::AssertValid() const
    {
        CDaoRecordset::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryProcessRecordsetVersion99::Dump(CDumpContext& dc) const
    {
        CDaoRecordset::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
