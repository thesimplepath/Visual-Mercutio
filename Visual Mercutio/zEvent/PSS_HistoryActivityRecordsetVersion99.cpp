/****************************************************************************
 * ==> PSS_HistoryActivityRecordsetVersion99 -------------------------------*
 ****************************************************************************
 * Description : Provides an historic activity recordset (version 99)       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_HistoryActivityRecordsetVersion99.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_HistoryActivityRecordsetVersion99, CDaoRecordset)
//---------------------------------------------------------------------------
// PSS_HistoryActivityRecordsetVersion99
//---------------------------------------------------------------------------
PSS_HistoryActivityRecordsetVersion99::PSS_HistoryActivityRecordsetVersion99(CDaoDatabase* pDatabase, const CString& fileName) :
    CDaoRecordset(pDatabase),
    m_StartDate(DATE(0)),
    m_EndDate(DATE(0)),
    m_DatabaseFileName(fileName),
    m_ActivityID(0),
    m_ProcessID(0),
    m_InBackup(FALSE)
{
    m_nFields      = 10;
    m_nDefaultType = dbOpenDynaset;
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetDefaultDBName()
{
    return _T(m_DatabaseFileName);
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityRecordsetVersion99::GetDefaultSQL()
{
    return _T(g_HistoryActivityTableName);
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityRecordsetVersion99::DoFieldExchange(CDaoFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(PSS_HistoryActivityRecordsetVersion99)
    pFX->SetFieldType(CDaoFieldExchange::outputColumn);
    DFX_Long    (pFX, _T("[ActivityID]"), m_ActivityID);
    DFX_Long    (pFX, _T("[ProcessID]"),  m_ProcessID);
    DFX_Text    (pFX, _T("[Name]"),       m_Name);
    DFX_DateTime(pFX, _T("[StartDate]"),  m_StartDate);
    DFX_DateTime(pFX, _T("[EndDate]"),    m_EndDate);
    DFX_Text    (pFX, _T("[Initiator]"),  m_Initiator);
    DFX_Text    (pFX, _T("[Receiver]"),   m_Receiver);
    DFX_Text    (pFX, _T("[Status]"),     m_Status);
    DFX_Text    (pFX, _T("[Comment]"),    m_Comment);
    DFX_Bool    (pFX, _T("[InBackup]"),   m_InBackup);
    //}}AFX_FIELD_MAP
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryActivityRecordsetVersion99::AssertValid() const
    {
        CDaoRecordset::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryActivityRecordsetVersion99::Dump(CDumpContext& dc) const
    {
        CDaoRecordset::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
