// Source file: ProjectWndC.cpp

#include <StdAfx.h>

#include "ProjectWndC.h"

#include "zBaseLib\ZDDoc.h"

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



BEGIN_MESSAGE_MAP(ZCProjectWindowTree, ZITreeCtrl)
	//{{AFX_MSG_MAP(ZCProjectWindowTree)
	ON_MESSAGE(UM_FILELISTHASCHANGED, OnFileListChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Class ZCProjectWindowTree 

ZCProjectWindowTree::ZCProjectWindowTree (ZDDocument* pDoc, BOOL OnlyVisible)
      : m_pDoc(pDoc), m_OnlyVisible(OnlyVisible)
{
}


ZCProjectWindowTree::~ZCProjectWindowTree()
{
}



void ZCProjectWindowTree::Empty()
{
	m_ProjectTree.Empty();
}


void ZCProjectWindowTree::Initialize (ZDDocument* pDoc, BOOL OnlyVisible)
{
    m_pDoc = pDoc;
	m_OnlyVisible = OnlyVisible;
	m_ProjectTree.Initialize( this, m_pDoc, m_OnlyVisible );
}

void ZCProjectWindowTree::Initialize ()
{
	m_ProjectTree.Initialize( this, m_pDoc, m_OnlyVisible );
}


void ZCProjectWindowTree::Refresh ()
{
	m_ProjectTree.Refresh();
}



ZDDocumentData* ZCProjectWindowTree::GetSelectedDocument ()
{
	return m_ProjectTree.GetSelectedDocument();
}

CString	ZCProjectWindowTree::GetSelectedDocumentTitle()
{
	return m_ProjectTree.GetSelectedDocumentTitle();
}


afx_msg LONG ZCProjectWindowTree::OnFileListChanged(WPARAM wParam, LPARAM lParam)
{
	m_ProjectTree.OnFileListChanged();
	return 0;
}
