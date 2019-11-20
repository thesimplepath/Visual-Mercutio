/****************************************************************************
 * ==> PSS_ActivityLogRecordset --------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity log recordset                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ActivityLogRecordset.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_ActivityLogRecordset, CDaoRecordset)
//---------------------------------------------------------------------------
// PSS_ActivityLogRecordset
//---------------------------------------------------------------------------
PSS_ActivityLogRecordset::PSS_ActivityLogRecordset(CDaoDatabase* pDatabase, const CString& fileName) :
    CDaoRecordset(pDatabase),
    m_Date(DATE(0)),
    m_ProcessCreationDate(DATE(0)),
    m_ProcessDueDate(DATE(0)),
    m_ActivityCreationDate(DATE(0)),
    m_ActivityDueDate(DATE(0)),
    m_DatabaseFileName(fileName),
    m_InBackup(FALSE)
{
    m_nFields      = 18;
    m_nDefaultType = dbOpenDynaset;
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetDefaultDBName()
{
    return _T(m_DatabaseFileName);
}
//---------------------------------------------------------------------------
CString PSS_ActivityLogRecordset::GetDefaultSQL()
{
    return _T(g_ActivityLogTableName);
}
//---------------------------------------------------------------------------
void PSS_ActivityLogRecordset::DoFieldExchange(CDaoFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(PSS_ActivityLogRecordset)
    pFX->SetFieldType(CDaoFieldExchange::outputColumn);
    DFX_DateTime(pFX, _T("[Date]"),                 m_Date);
    DFX_Text    (pFX, _T("[EventType]"),            m_EventType);
    DFX_Text    (pFX, _T("[ProcessFilename]"),      m_ProcessFileName);
    DFX_Text    (pFX, _T("[FormDataFilename]"),     m_FormDataFileName);
    DFX_Text    (pFX, _T("[ProcessDataFilename]"),  m_ProcessDataFileName);
    DFX_Text    (pFX, _T("[FolderName]"),           m_FolderName);
    DFX_Text    (pFX, _T("[ProcessName]"),          m_ProcessName);
    DFX_DateTime(pFX, _T("[ProcessCreationDate]"),  m_ProcessCreationDate);
    DFX_DateTime(pFX, _T("[ProcessDueDate]"),       m_ProcessDueDate);
    DFX_Text    (pFX, _T("[ActivityType]"),         m_ActivityType);
    DFX_Text    (pFX, _T("[ActivityName]"),         m_ActivityName);
    DFX_DateTime(pFX, _T("[ActivityCreationDate]"), m_ActivityCreationDate);
    DFX_DateTime(pFX, _T("[ActivityDueDate]"),      m_ActivityDueDate);
    DFX_Text    (pFX, _T("[ActivityStatus]"),       m_ActivityStatus);
    DFX_Text    (pFX, _T("[Sender]"),               m_Sender);
    DFX_Text    (pFX, _T("[Receiver]"),             m_Receiver);
    DFX_Text    (pFX, _T("[Comments]"),             m_Comments);
    DFX_Bool    (pFX, _T("[InBackup]"),             m_InBackup);
    //}}AFX_FIELD_MAP
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ActivityLogRecordset::AssertValid() const
    {
        CDaoRecordset::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ActivityLogRecordset::Dump(CDumpContext& dc) const
    {
        CDaoRecordset::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
