/****************************************************************************
 * ==> PSS_UserRecordSet ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user record set                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_UserRecordSet.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_UserRecordSet, CRecordset)
//---------------------------------------------------------------------------
// PSS_UserRecordSet
//---------------------------------------------------------------------------
PSS_UserRecordSet::PSS_UserRecordSet(CDatabase* pDB) :
    CRecordset(pDB)
{
    // configure field number in base
    m_nFields = 4;
}
//---------------------------------------------------------------------------
CString PSS_UserRecordSet::GetUserDBTableName() const
{
    return "Employee";
}
//---------------------------------------------------------------------------
CString PSS_UserRecordSet::GetDefaultConnect() const
{
    return "ODBC;DSN=ADSoft Server Database;";
}
//---------------------------------------------------------------------------
CString PSS_UserRecordSet::GetDefaultSQL() const
{
    return "Employee";
}
//---------------------------------------------------------------------------
void PSS_UserRecordSet::DoFieldExchange(CFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(PSS_UserRecordSet)
    pFX->SetFieldType(CFieldExchange::outputColumn);
    RFX_Text(pFX, "UserName",    m_UserName);
    RFX_Text(pFX, "Email",       m_Email);
    RFX_Text(pFX, "Responsible", m_Responsible);
    RFX_Text(pFX, "Description", m_Description);
    //}}AFX_FIELD_MAP
}
//---------------------------------------------------------------------------
