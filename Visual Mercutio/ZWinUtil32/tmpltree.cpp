//## begin module%3735C9FC0149.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%3735C9FC0149.cm

//## begin module%3735C9FC0149.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%3735C9FC0149.cp

//## Module: TmplTree%3735C9FC0149; Package body
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\TmplTree.cpp

//## begin module%3735C9FC0149.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%3735C9FC0149.additionalIncludes

//## begin module%3735C9FC0149.includes preserve=yes
//## end module%3735C9FC0149.includes

// TmplTree
#include "TmplTree.h"
//## begin module%3735C9FC0149.declarations preserve=no
//## end module%3735C9FC0149.declarations

//## begin module%3735C9FC0149.additionalDeclarations preserve=yes
#ifndef _WIN32
    #include "ZWinUtil.h"
#else
    #include "ZWinUtil32.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 10 juillet 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_DYNCREATE( ZCTemplateTreeCtrl, ZITreeCtrl )

BEGIN_MESSAGE_MAP( ZCTemplateTreeCtrl, ZITreeCtrl )
    //{{AFX_MSG_MAP(ZCTemplateTreeCtrl)
    ON_MESSAGE(UM_INITIALIZE_TEMPLATEMANAGER, OnInitializeTemplateManager)
    ON_MESSAGE(UM_INITIALIZE_PROCESSTEMPLATEMANAGER, OnInitializeTemplateManager)
    ON_MESSAGE(UM_RELOAD_TEMPLATEMANAGER, OnReloadTemplateManager)
    ON_MESSAGE(UM_RELOAD_PROCESSTEMPLATEMANAGER, OnReloadTemplateManager)
    ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
    ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblClick)
    ON_NOTIFY_REFLECT(NM_RCLICK, OnRightClick)
    ON_NOTIFY_REFLECT(NM_RDBLCLK, OnRightDblClick)
    ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//## end module%3735C9FC0149.additionalDeclarations

// Class ZCTemplateTreeCtrl

ZCTemplateTreeCtrl::ZCTemplateTreeCtrl( ZDTemplateManager* pTemplateManager, BOOL IncludeFiles )
    //## begin ZCTemplateTreeCtrl::ZCTemplateTreeCtrl%926272048.hasinit preserve=no
    //## end ZCTemplateTreeCtrl::ZCTemplateTreeCtrl%926272048.hasinit
    //## begin ZCTemplateTreeCtrl::ZCTemplateTreeCtrl%926272048.initialization preserve=yes
    : m_pTemplateManager( pTemplateManager ),
      m_IncludeFiles    ( IncludeFiles )
    //## end ZCTemplateTreeCtrl::ZCTemplateTreeCtrl%926272048.initialization
{
    //## begin ZCTemplateTreeCtrl::ZCTemplateTreeCtrl%926272048.body preserve=yes
    //## end ZCTemplateTreeCtrl::ZCTemplateTreeCtrl%926272048.body
}

ZCTemplateTreeCtrl::~ZCTemplateTreeCtrl()
{
    //## begin ZCTemplateTreeCtrl::~ZCTemplateTreeCtrl%.body preserve=yes
    //## end ZCTemplateTreeCtrl::~ZCTemplateTreeCtrl%.body
}

//## Other Operations (implementation)
void ZCTemplateTreeCtrl::Initialize( ZDTemplateManager* pTemplateManager, BOOL IncludeFiles )
{
    //## begin ZCTemplateTreeCtrl::Initialize%926272049.body preserve=yes
    m_pTemplateManager    = pTemplateManager;
    m_IncludeFiles        = IncludeFiles;

    m_TemplateTree.Initialize( this, m_pTemplateManager, m_IncludeFiles );
    //## end ZCTemplateTreeCtrl::Initialize%926272049.body
}

void ZCTemplateTreeCtrl::ReInitialize( ZDTemplateManager* pTemplateManager, BOOL IncludeFiles )
{
    //## begin ZCTemplateTreeCtrl::ReInitialize%941625570.body preserve=yes
    m_pTemplateManager    = pTemplateManager;
    m_IncludeFiles        = IncludeFiles;

    m_TemplateTree.ReInitialize( m_pTemplateManager, m_IncludeFiles );
    //## end ZCTemplateTreeCtrl::ReInitialize%941625570.body
}

void ZCTemplateTreeCtrl::Refresh()
{
    //## begin ZCTemplateTreeCtrl::Refresh%926579196.body preserve=yes
    m_TemplateTree.Refresh();
    //## end ZCTemplateTreeCtrl::Refresh%926579196.body
}

CString ZCTemplateTreeCtrl::GetNameSelectedItem()
{
    //## begin ZCTemplateTreeCtrl::GetNameSelectedItem%926358694.body preserve=yes
    return m_TemplateTree.GetNameSelectedItem();
    //## end ZCTemplateTreeCtrl::GetNameSelectedItem%926358694.body
}

ZDTemplateDir* ZCTemplateTreeCtrl::GetSelectedFolderItem()
{
    //## begin ZCTemplateTreeCtrl::GetSelectedFolderItem%926358695.body preserve=yes
    return m_TemplateTree.GetSelectedFolderItem();
    //## end ZCTemplateTreeCtrl::GetSelectedFolderItem%926358695.body
}

ZDTemplateFile* ZCTemplateTreeCtrl::GetSelectedFileItem()
{
    //## begin ZCTemplateTreeCtrl::GetSelectedFileItem%926358696.body preserve=yes
    return m_TemplateTree.GetSelectedFileItem();
    //## end ZCTemplateTreeCtrl::GetSelectedFileItem%926358696.body
}

BOOL ZCTemplateTreeCtrl::SelectItemName( const CString Name )
{
    //## begin ZCTemplateTreeCtrl::SelectItemName%927987845.body preserve=yes
    return m_TemplateTree.SelectItemName( Name );
    //## end ZCTemplateTreeCtrl::SelectItemName%927987845.body
}

/////////////////////////////////////////////////////////////////////////////
// ZCTemplateTreeCtrl message handlers

afx_msg LRESULT ZCTemplateTreeCtrl::OnInitializeTemplateManager( WPARAM wParam, LPARAM lParam )
{
    if ( !::IsWindow( GetSafeHwnd() ) )
    {
        return 1;
    }

    m_pTemplateManager = (ZDTemplateManager*)lParam;
    m_IncludeFiles = (BOOL)wParam;

    if ( m_pTemplateManager )
    {
        ZCTemplateTreeCtrl::Initialize( m_pTemplateManager, m_IncludeFiles );
    }

    return 1;
}

afx_msg LRESULT ZCTemplateTreeCtrl::OnReloadTemplateManager( WPARAM wParam, LPARAM lParam )
{
    if ( !::IsWindow( GetSafeHwnd() ) )
    {
        return 1;
    }

    m_pTemplateManager = (ZDTemplateManager*)lParam;

    if ( m_pTemplateManager )
    {
        ZCTemplateTreeCtrl::ReInitialize( m_pTemplateManager, m_IncludeFiles );
    }

    return 1;
}

void ZCTemplateTreeCtrl::OnSelchanged( NMHDR* pNMHDR, LRESULT* pResult )
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if ( !AfxGetMainWnd() )
    {
        return;
    }

    // Call the virtual method
    OnSelChangedEvent();

    *pResult = 0;
}

void ZCTemplateTreeCtrl::OnClick( NMHDR* pNMHDR, LRESULT* pResult )
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if ( !AfxGetMainWnd() )
    {
        return;
    }

    // Call the virtual method
    OnClickEvent();

    *pResult = 0;
}

void ZCTemplateTreeCtrl::OnDblClick( NMHDR* pNMHDR, LRESULT* pResult )
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if ( !AfxGetMainWnd() )
    {
        return;
    }

    // If something selected.
    if ( GetSelectedFileItem() )
    {
        AfxGetMainWnd()->SendMessage( UM_FORM_OPEN,
                                      1, // Change the file
                                      (LPARAM)(const char*)GetSelectedFileItem()->GetFilename() );
    }

    // Call the virtual method
    OnDblClickEvent();

    *pResult = 0;
}

void ZCTemplateTreeCtrl::OnRightClick( NMHDR* pNMHDR, LRESULT* pResult )
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if ( !AfxGetMainWnd() )
    {
        return;
    }

    // Call the virtual method
    OnRightClickEvent();

    *pResult = 0;
}

void ZCTemplateTreeCtrl::OnRightDblClick( NMHDR* pNMHDR, LRESULT* pResult )
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if ( !AfxGetMainWnd() )
    {
        return;
    }

    // Call the virtual method
    OnRightDblClickEvent();

    *pResult = 0;
}
