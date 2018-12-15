// rsetuser.cpp : implementation file
//
#include <StdAfx.h>

#include "RSetUser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDUserRecordSet

IMPLEMENT_DYNAMIC(ZDUserRecordSet, CRecordset)

ZDUserRecordSet::ZDUserRecordSet(CDatabase* pdb)
    : CRecordset(pdb)
{
    //{{AFX_FIELD_INIT(ZDUserRecordSet)
    m_UserName = "";
    m_Email = "";
    m_Responsible = "";
    m_Description = "";
    m_nFields = 4;
    //}}AFX_FIELD_INIT
}


CString ZDUserRecordSet::GetDefaultConnect()
{
    return "ODBC;DSN=ADSoft Server Database;";
}

CString ZDUserRecordSet::GetDefaultSQL()
{
    return "Employee";
}

CString ZDUserRecordSet::GetUserDBTableName()
{
    return "Employee";
}

void ZDUserRecordSet::DoFieldExchange(CFieldExchange* pFX)
{
    //{{AFX_FIELD_MAP(ZDUserRecordSet)
    pFX->SetFieldType(CFieldExchange::outputColumn);
    RFX_Text(pFX, "UserName", m_UserName);
    RFX_Text(pFX, "Email", m_Email);
    RFX_Text(pFX, "Responsible", m_Responsible);
    RFX_Text(pFX, "Description", m_Description);
    //}}AFX_FIELD_MAP
}
