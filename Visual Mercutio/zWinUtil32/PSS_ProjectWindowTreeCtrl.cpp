/****************************************************************************
 * ==> PSS_ProjectWindowTreeCtrl -------------------------------------------*
 ****************************************************************************
 * Description : Provides a project window tree control                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ProjectWindowTreeCtrl.h"

// processsoft
#include "zBaseLib\PSS_Document.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProjectWindowTreeCtrl, ZITreeCtrl)
    //{{AFX_MSG_MAP(PSS_ProjectWindowTreeCtrl)
    ON_MESSAGE(UM_FILELISTHASCHANGED, OnFileListChanged)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProjectWindowTreeCtrl
//---------------------------------------------------------------------------
PSS_ProjectWindowTreeCtrl::PSS_ProjectWindowTreeCtrl(PSS_Document* pDoc, BOOL visibleOnly) :
    ZITreeCtrl(),
    m_pDoc(pDoc),
    m_VisibleOnly(visibleOnly)
{}
//---------------------------------------------------------------------------
PSS_ProjectWindowTreeCtrl::PSS_ProjectWindowTreeCtrl(const PSS_ProjectWindowTreeCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ProjectWindowTreeCtrl::~PSS_ProjectWindowTreeCtrl()
{}
//---------------------------------------------------------------------------
const PSS_ProjectWindowTreeCtrl& PSS_ProjectWindowTreeCtrl::operator = (const PSS_ProjectWindowTreeCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ProjectWindowTreeCtrl::Initialize()
{
    m_ProjectTree.Initialize(this, m_pDoc, m_VisibleOnly);
}
//---------------------------------------------------------------------------
void PSS_ProjectWindowTreeCtrl::Initialize(PSS_Document* pDoc, BOOL visibleOnly)
{
    m_pDoc        = pDoc;
    m_VisibleOnly = visibleOnly;
    m_ProjectTree.Initialize(this, m_pDoc, m_VisibleOnly);
}
//---------------------------------------------------------------------------
void PSS_ProjectWindowTreeCtrl::Empty()
{
    m_ProjectTree.Empty();
}
//---------------------------------------------------------------------------
void PSS_ProjectWindowTreeCtrl::Refresh()
{
    m_ProjectTree.Refresh();
}
//---------------------------------------------------------------------------
PSS_DocumentData* PSS_ProjectWindowTreeCtrl::GetSelectedDocument()
{
    return m_ProjectTree.GetSelectedDocument();
}
//---------------------------------------------------------------------------
CString PSS_ProjectWindowTreeCtrl::GetSelectedDocumentTitle()
{
    return m_ProjectTree.GetSelectedDocumentTitle();
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_ProjectWindowTreeCtrl::OnFileListChanged(WPARAM wParam, LPARAM lParam)
{
    m_ProjectTree.OnFileListChanged();
    return 0;
}
//---------------------------------------------------------------------------
