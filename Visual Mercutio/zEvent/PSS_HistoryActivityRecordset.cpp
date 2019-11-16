/****************************************************************************
 * ==> PSS_HistoryActivityRecordset ----------------------------------------*
 ****************************************************************************
 * Description : Provides an historic activity recordset                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_HistoryActivityRecordset.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_HistoryActivityRecordset, CDaoRecordset)
//---------------------------------------------------------------------------
// PSS_HistoryActivityRecordset
//---------------------------------------------------------------------------
PSS_HistoryActivityRecordset::PSS_HistoryActivityRecordset(CDaoDatabase* pDatabase, const CString& fileName) :
    CDaoRecordset(pDatabase),
    m_Date(DATE(0)),
    m_StartDate(DATE(0)),
    m_EndDate(DATE(0)),
    m_ForecastedEndDate(DATE(0)),
    m_DatabaseFileName(fileName),
    m_ActivityID(0),
    m_ProcessID(0),
    m_InitialDays(0),
    m_InBackup(FALSE)
{
    m_nFields      = 13;
    m_nDefaultType = dbOpenDynaset;
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetDefaultDBName()
{
    return _T(m_DatabaseFileName);
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordset::GetDefaultSQL()
{
    return _T(g_HistoryActivityTableName);
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordset::DoFieldExchange(CDaoFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(PSS_HistoryActivityRecordset)
    pFX->SetFieldType(CDaoFieldExchange::outputColumn);
    DFX_Long    (pFX, _T("[ActivityID]"),        m_ActivityID);
    DFX_Long    (pFX, _T("[ProcessID]"),         m_ProcessID);
    DFX_Text    (pFX, _T("[Name]"),              m_Name);
    DFX_DateTime(pFX, _T("[Date]"),              m_Date);
    DFX_DateTime(pFX, _T("[StartDate]"),         m_StartDate);
    DFX_DateTime(pFX, _T("[EndDate]"),           m_EndDate);
    DFX_Long    (pFX, _T("[InitialDays]"),       m_InitialDays);
    DFX_DateTime(pFX, _T("[ForecastedEndDate]"), m_ForecastedEndDate);
    DFX_Text    (pFX, _T("[Initiator]"),         m_Initiator);
    DFX_Text    (pFX, _T("[Receiver]"),          m_Receiver);
    DFX_Text    (pFX, _T("[Status]"),            m_Status);
    DFX_Text    (pFX, _T("[Comment]"),           m_Comment);
    DFX_Bool    (pFX, _T("[InBackup]"),          m_InBackup);
    //}}AFX_FIELD_MAP
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryActivityRecordset::AssertValid() const
    {
        CDaoRecordset::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryActivityRecordset::Dump(CDumpContext& dc) const
    {
        CDaoRecordset::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
