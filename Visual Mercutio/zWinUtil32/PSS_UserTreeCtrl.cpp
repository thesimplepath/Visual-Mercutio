/****************************************************************************
 * ==> PSS_UserTreeCtrl ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user tree control                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_UserTreeCtrl.h"

// processsoft
#include "zRes32\ZRes.h"

#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UserTreeCtrl, ZITreeCtrl)
    //{{AFX_MSG_MAP(PSS_UserTreeCtrl)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UserTreeCtrl
//---------------------------------------------------------------------------
PSS_UserTreeCtrl::PSS_UserTreeCtrl(ZUUserManager* pUserManager) :
    m_pUserManager(pUserManager),
    m_Invalid(false)
{
    if (m_pUserManager)
        m_UserTree.Initialize(this, m_pUserManager);
}
//---------------------------------------------------------------------------
PSS_UserTreeCtrl::PSS_UserTreeCtrl(const PSS_UserTreeCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_UserTreeCtrl::~PSS_UserTreeCtrl()
{}
//---------------------------------------------------------------------------
const PSS_UserTreeCtrl& PSS_UserTreeCtrl::operator = (const PSS_UserTreeCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_UserTreeCtrl::Initialize(ZUUserManager* pUserManager)
{
    m_pUserManager = pUserManager;
    m_UserTree.Initialize(this, pUserManager);
}
//---------------------------------------------------------------------------
void PSS_UserTreeCtrl::ReInitialize(ZUUserManager* pUserManager)
{
    m_pUserManager = pUserManager;
    m_UserTree.ReInitialize(pUserManager);
}
//---------------------------------------------------------------------------
void PSS_UserTreeCtrl::Refresh()
{
    m_UserTree.Refresh();
}
//---------------------------------------------------------------------------
ZUser* PSS_UserTreeCtrl::GetSelectedUser()
{
    return m_UserTree.GetSelectedUser();
}
//---------------------------------------------------------------------------
CString PSS_UserTreeCtrl::GetSelectedDepartement()
{
    return m_UserTree.GetSelectedDepartement();
}
//---------------------------------------------------------------------------
