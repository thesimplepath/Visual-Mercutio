/****************************************************************************
 * ==> PSS_HistoryActivityStatusRecordset ----------------------------------*
 ****************************************************************************
 * Description : Provides an historic activity status recordset             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_HistoryActivityStatusRecordset.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_HistoryActivityStatusRecordset, CDaoRecordset)
//---------------------------------------------------------------------------
// PSS_HistoryActivityStatusRecordset
//---------------------------------------------------------------------------
PSS_HistoryActivityStatusRecordset::PSS_HistoryActivityStatusRecordset(CDaoDatabase* pDatabase, const CString& fileName) :
    CDaoRecordset(pDatabase),
    m_Date(DATE(0)),
    m_StartDate(DATE(0)),
    m_EndDate(DATE(0)),
    m_DatabaseFileName(fileName),
    m_ActivityStatusID(0),
    m_ActivityID(0),
    m_ProcessID(0)
{
    m_nFields      = 9;
    m_nDefaultType = dbOpenDynaset;
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityStatusRecordset::GetDefaultDBName()
{
    return _T(m_DatabaseFileName);
}
//---------------------------------------------------------------------------
CString PSS_HistoryActivityStatusRecordset::GetDefaultSQL()
{
    return _T(g_HistoryActivityStatusTableName);
}
//---------------------------------------------------------------------------
void PSS_HistoryActivityStatusRecordset::DoFieldExchange(CDaoFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(PSS_HistoryActivityStatusRecordset)
    pFX->SetFieldType(CDaoFieldExchange::outputColumn);
    DFX_Long    (pFX, _T("[ActivityStatusID]"), m_ActivityStatusID);
    DFX_Long    (pFX, _T("[ActivityID]"),       m_ActivityID);
    DFX_Long    (pFX, _T("[ProcessID]"),        m_ProcessID);
    DFX_Text    (pFX, _T("[FolderName]"),       m_FolderName);
    DFX_Text    (pFX, _T("[Name]"),             m_Name);
    DFX_DateTime(pFX, _T("[Date]"),             m_Date);
    DFX_DateTime(pFX, _T("[StartDate]"),        m_StartDate);
    DFX_DateTime(pFX, _T("[EndDate]"),          m_EndDate);
    DFX_Text    (pFX, _T("[Status]"),           m_Status);
    //}}AFX_FIELD_MAP
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryActivityStatusRecordset::AssertValid() const
    {
        CDaoRecordset::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryActivityStatusRecordset::Dump(CDumpContext& dc) const
    {
        CDaoRecordset::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
