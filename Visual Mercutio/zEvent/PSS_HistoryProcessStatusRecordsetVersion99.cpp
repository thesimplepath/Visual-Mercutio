/****************************************************************************
 * ==> PSS_HistoryProcessStatusRecordsetVersion99 --------------------------*
 ****************************************************************************
 * Description : Provides an historic process status recordset              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_HistoryProcessStatusRecordsetVersion99.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_HistoryProcessStatusRecordsetVersion99, CDaoRecordset)
//---------------------------------------------------------------------------
// PSS_HistoryProcessStatusRecordsetVersion99
//---------------------------------------------------------------------------
PSS_HistoryProcessStatusRecordsetVersion99::PSS_HistoryProcessStatusRecordsetVersion99(CDaoDatabase*  pDatabase,
                                                                                       const CString& fileName) :
    CDaoRecordset(pDatabase),
    m_Date(DATE(0)),
    m_DatabaseFileName(fileName),
    m_ProcessStatusID(0),
    m_ProcessID(0),
    m_CurrentActivity(0)
{
    m_nFields      = 5;
    m_nDefaultType = dbOpenDynaset;
}
//---------------------------------------------------------------------------
CString PSS_HistoryProcessStatusRecordsetVersion99::GetDefaultDBName()
{
    return _T(m_DatabaseFileName);
}
//---------------------------------------------------------------------------
CString PSS_HistoryProcessStatusRecordsetVersion99::GetDefaultSQL()
{
    return _T(g_HistoryProcessStatusTableName);
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessStatusRecordsetVersion99::DoFieldExchange(CDaoFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(PSS_HistoryProcessStatusRecordsetVersion99)
    pFX->SetFieldType(CDaoFieldExchange::outputColumn);
    DFX_Long    (pFX, _T("[ProcessStatusID]"), m_ProcessStatusID);
    DFX_DateTime(pFX, _T("[Date]"),            m_Date);
    DFX_Long    (pFX, _T("[ProcessID]"),       m_ProcessID);
    DFX_Text    (pFX, _T("[Status]"),          m_Status);
    DFX_Long    (pFX, _T("[CurrentActivity]"), m_CurrentActivity);
    //}}AFX_FIELD_MAP
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryProcessStatusRecordsetVersion99::AssertValid() const
    {
        CDaoRecordset::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryProcessStatusRecordsetVersion99::Dump(CDumpContext& dc) const
    {
        CDaoRecordset::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
