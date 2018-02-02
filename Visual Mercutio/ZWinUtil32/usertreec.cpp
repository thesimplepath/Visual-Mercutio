// Source file: UserTreeC.cpp

#include <StdAfx.h>

// UserTreeC
#include "UserTreeC.h"
#include "zRes32\ZRes.h"

#ifndef _WIN32
	#include "ZWinUtil.h"
#endif
#ifdef _WIN32
	#include "ZWinUtil32.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZCUserTree, ZITreeCtrl)
	//{{AFX_MSG_MAP(ZCUserTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCUserTree 


ZCUserTree::ZCUserTree (ZUUserManager* pUserManager)
      : m_pUserManager(pUserManager)
{
	if (m_pUserManager)
		m_UserTree.Initialize( this, m_pUserManager );
}


ZCUserTree::~ZCUserTree()
{
}



void ZCUserTree::Initialize (ZUUserManager* pUserManager)
{
    m_pUserManager = pUserManager;
	m_UserTree.Initialize( this, pUserManager );
}

void ZCUserTree::ReInitialize (ZUUserManager* pUserManager)
{
    m_pUserManager = pUserManager;
	m_UserTree.ReInitialize( pUserManager );
}

void ZCUserTree::Refresh ()
{
	m_UserTree.Refresh();
}

ZUser* ZCUserTree::GetSelectedUser ()
{
	return m_UserTree.GetSelectedUser();
}

CString	ZCUserTree::GetSelectedDepartement()
{
	return m_UserTree.GetSelectedDepartement();
}
