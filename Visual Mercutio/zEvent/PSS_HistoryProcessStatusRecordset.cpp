/****************************************************************************
 * ==> PSS_HistoryProcessStatusRecordset -----------------------------------*
 ****************************************************************************
 * Description : Provides an historic process status recordset              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_HistoryProcessStatusRecordset.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_HistoryProcessStatusRecordset, CDaoRecordset)
//---------------------------------------------------------------------------
// PSS_HistoryProcessStatusRecordset
//---------------------------------------------------------------------------
PSS_HistoryProcessStatusRecordset::PSS_HistoryProcessStatusRecordset(CDaoDatabase* pDatabase, const CString& fileName) :
    CDaoRecordset(pDatabase),
    m_Date(DATE(0)),
    m_StartDate(DATE(0)),
    m_EndDate(DATE(0)),
    m_DatabaseFileName(fileName),
    m_ProcessStatusID(0),
    m_ProcessID(0),
    m_CurrentActivity(0)
{
    m_nFields      = 7;
    m_nDefaultType = dbOpenDynaset;
}
//---------------------------------------------------------------------------
CString PSS_HistoryProcessStatusRecordset::GetDefaultDBName()
{
    return _T(m_DatabaseFileName);
}
//---------------------------------------------------------------------------
CString PSS_HistoryProcessStatusRecordset::GetDefaultSQL()
{
    return _T(g_HistoryProcessStatusTableName);
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessStatusRecordset::DoFieldExchange(CDaoFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(PSS_HistoryProcessStatusRecordset)
    pFX->SetFieldType(CDaoFieldExchange::outputColumn);
    DFX_Long    (pFX, _T("[ProcessStatusID]"), m_ProcessStatusID);
    DFX_DateTime(pFX, _T("[Date]"),            m_Date);
    DFX_DateTime(pFX, _T("[StartDate]"),       m_StartDate);
    DFX_DateTime(pFX, _T("[EndDate]"),         m_EndDate);
    DFX_Long    (pFX, _T("[ProcessID]"),       m_ProcessID);
    DFX_Text    (pFX, _T("[Status]"),          m_Status);
    DFX_Long    (pFX, _T("[CurrentActivity]"), m_CurrentActivity);
    //}}AFX_FIELD_MAP
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryProcessStatusRecordset::AssertValid() const
    {
        CDaoRecordset::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryProcessStatusRecordset::Dump(CDumpContext& dc) const
    {
        CDaoRecordset::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
