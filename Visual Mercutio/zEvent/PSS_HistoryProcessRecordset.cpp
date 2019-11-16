/****************************************************************************
 * ==> PSS_HistoryProcessRecordset -----------------------------------------*
 ****************************************************************************
 * Description : Provides an historic process recordset                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_HistoryProcessRecordset.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_HistoryProcessRecordset, CDaoRecordset)
//---------------------------------------------------------------------------
// PSS_HistoryProcessRecordset
//---------------------------------------------------------------------------
PSS_HistoryProcessRecordset::PSS_HistoryProcessRecordset(CDaoDatabase* pDatabase, const CString& fileName) :
    CDaoRecordset(pDatabase),
    m_Date(DATE(0)),
    m_StartDate(DATE(0)),
    m_EndDate(DATE(0)),
    m_ForecastedEndDate(DATE(0)),
    m_DatabaseFileName(fileName),
    m_ProcessID(0),
    m_InitialDays(0)
{
    m_nFields      = 12;
    m_nDefaultType = dbOpenDynaset;
}
//---------------------------------------------------------------------------
CString PSS_HistoryProcessRecordset::GetDefaultDBName()
{
    return _T(m_DatabaseFileName);
}
//---------------------------------------------------------------------------
CString PSS_HistoryProcessRecordset::GetDefaultSQL()
{
    return _T(g_HistoryProcessTableName);
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessRecordset::DoFieldExchange(CDaoFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(PSS_HistoryProcessRecordset)
    pFX->SetFieldType(CDaoFieldExchange::outputColumn);
    DFX_Long    (pFX, _T("[ProcessID]"),         m_ProcessID);
    DFX_Text    (pFX, _T("[Name]"),              m_Name);
    DFX_Text    (pFX, _T("[Filename]"),          m_FileName);
    DFX_Text    (pFX, _T("[FolderName]"),        m_FolderName);
    DFX_Text    (pFX, _T("[DataFeedForm]"),      m_DataFeedForm);
    DFX_Text    (pFX, _T("[DataFeedProc]"),      m_DataFeedProc);
    DFX_DateTime(pFX, _T("[Date]"),              m_Date);
    DFX_DateTime(pFX, _T("[StartDate]"),         m_StartDate);
    DFX_DateTime(pFX, _T("[EndDate]"),           m_EndDate);
    DFX_Long    (pFX, _T("[InitialDays]"),       m_InitialDays);
    DFX_DateTime(pFX, _T("[ForecastedEndDate]"), m_ForecastedEndDate);
    DFX_Text    (pFX, _T("[Initiator]"),         m_Initiator);
    //}}AFX_FIELD_MAP
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryProcessRecordset::AssertValid() const
    {
        CDaoRecordset::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryProcessRecordset::Dump(CDumpContext& dc) const
    {
        CDaoRecordset::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
