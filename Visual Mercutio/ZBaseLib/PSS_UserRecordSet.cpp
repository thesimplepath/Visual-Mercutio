/****************************************************************************
 * ==> PSS_UserRecordset ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user recordset                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_UserRecordset.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_UserRecordset, CRecordset)
//---------------------------------------------------------------------------
// PSS_UserRecordset
//---------------------------------------------------------------------------
PSS_UserRecordset::PSS_UserRecordset(CDatabase* pDB) :
    CRecordset(pDB)
{
    // configure field number in base
    m_nFields = 4;
}
//---------------------------------------------------------------------------
CString PSS_UserRecordset::GetUserDBTableName() const
{
    return "Employee";
}
//---------------------------------------------------------------------------
CString PSS_UserRecordset::GetDefaultConnect() const
{
    return "ODBC;DSN=ADSoft Server Database;";
}
//---------------------------------------------------------------------------
CString PSS_UserRecordset::GetDefaultSQL() const
{
    return "Employee";
}
//---------------------------------------------------------------------------
void PSS_UserRecordset::DoFieldExchange(CFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(PSS_UserRecordset)
    pFX->SetFieldType(CFieldExchange::outputColumn);
    RFX_Text(pFX, "UserName",    m_UserName);
    RFX_Text(pFX, "Email",       m_Email);
    RFX_Text(pFX, "Responsible", m_Responsible);
    RFX_Text(pFX, "Description", m_Description);
    //}}AFX_FIELD_MAP
}
//---------------------------------------------------------------------------
