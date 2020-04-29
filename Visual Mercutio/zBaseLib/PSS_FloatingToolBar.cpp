/****************************************************************************
 * ==> PSS_FloatingToolBar -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic floating toolbar                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FloatingToolBar.h"

// processsoft
#include "PSS_BaseMainFrame.h"
#include "PSS_WindowConfiguration.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
PSS_FloatingToolBar::IToolBarSet PSS_FloatingToolBar::m_ToolBarSet;
PSS_FloatingToolBar::IMenuBarSet PSS_FloatingToolBar::m_MenuBarSet;
PSS_WindowConfiguration*         PSS_FloatingToolBar::m_pWndConf        = NULL;
SECToolBarManager*               PSS_FloatingToolBar::m_pToolBarManager = NULL;
SECMenuBar*                      PSS_FloatingToolBar::m_pMenuBarManager = NULL;
EModelNotation                   PSS_FloatingToolBar::m_CurrentNotation = E_MN_Unknown;
//---------------------------------------------------------------------------
// PSS_FloatingToolBar::IToolBarData
//---------------------------------------------------------------------------
PSS_FloatingToolBar::IToolBarData::IToolBarData(const CString& name, CControlBar* pBar, CFrameWnd* pFrame, EModelNotation notation) :
    m_Name(name),
    m_ToolBarID(-1),
    m_pBar(pBar),
    m_pFrame(pFrame),
    m_Notation(notation),
    m_Reloaded(false)
{}
//---------------------------------------------------------------------------
PSS_FloatingToolBar::IToolBarData::IToolBarData(const CString& name, UINT toolBarID, CFrameWnd* pFrame, EModelNotation notation) :
    m_Name(name),
    m_ToolBarID(toolBarID),
    m_pBar(NULL),
    m_pFrame(pFrame),
    m_Notation(notation),
    m_Reloaded(false)
{}
//---------------------------------------------------------------------------
PSS_FloatingToolBar::IToolBarData::~IToolBarData()
{}
//---------------------------------------------------------------------------
// PSS_FloatingToolBar::IMenuBarData
//---------------------------------------------------------------------------
PSS_FloatingToolBar::IMenuBarData::IMenuBarData(const CString& name, CMenu* pMenu, CFrameWnd* pFrame, EModelNotation notation) :
    m_Name(name),
    m_MenuID(-1),
    m_pMenu(pMenu),
    m_pFrame(pFrame),
    m_Notation(notation),
    m_Reloaded(false)
{}
//---------------------------------------------------------------------------
PSS_FloatingToolBar::IMenuBarData::IMenuBarData(const CString& name, UINT menuBarID, CFrameWnd* pFrame, EModelNotation notation) :
    m_Name(name),
    m_MenuID(menuBarID),
    m_pMenu(NULL),
    m_pFrame(pFrame),
    m_Notation(notation),
    m_Reloaded(false)
{}
//---------------------------------------------------------------------------
PSS_FloatingToolBar::IMenuBarData::~IMenuBarData()
{}
//---------------------------------------------------------------------------
// PSS_FloatingToolBar
//---------------------------------------------------------------------------
PSS_FloatingToolBar::PSS_FloatingToolBar()
{}
//---------------------------------------------------------------------------
PSS_FloatingToolBar::~PSS_FloatingToolBar()
{}
//---------------------------------------------------------------------------
void PSS_FloatingToolBar::Initialize(PSS_WindowConfiguration* pWndConf,
                                     SECToolBarManager*       pToolBarManager,
                                     SECMenuBar*              pMenuBarManager)
{
    m_pToolBarManager = pToolBarManager;
    m_pMenuBarManager = pMenuBarManager;
    m_pWndConf        = pWndConf;
}
//---------------------------------------------------------------------------
void PSS_FloatingToolBar::Release()
{
    IToolBarIterator itToolBar(&m_ToolBarSet);

    for (IToolBarData* pData = itToolBar.GetFirst(); pData; pData = itToolBar.GetNext())
        delete pData;

    m_ToolBarSet.RemoveAll();

    IMenuBarIterator itMenuBar(&m_MenuBarSet);

    for (IMenuBarData* pData = itMenuBar.GetFirst(); pData; pData = itMenuBar.GetNext())
        delete pData;

    m_MenuBarSet.RemoveAll();
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::RegisterToolBar(const CString& name, CControlBar* pBar, CFrameWnd* pFrame, EModelNotation notation)
{
    // check if toolbar exists
    if (ToolBarExist(name))
        return true;

    const int actSize = m_ToolBarSet.GetSize();

    std::unique_ptr<IToolBarData> pData(new IToolBarData(name, pBar, pFrame, notation));
    m_ToolBarSet.Add(pData.get());

    const bool added = (m_ToolBarSet.GetSize() > actSize);

    if (added)
        pData.release();

    return added;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::RegisterToolBar(const CString& name, UINT toolBarID, CFrameWnd* pFrame, EModelNotation notation)
{
    // check if toolbar exists
    if (ToolBarExist(toolBarID))
        return true;

    const int actSize = m_ToolBarSet.GetSize();

    std::unique_ptr<IToolBarData> pData(new IToolBarData(name, toolBarID, pFrame, notation));
    m_ToolBarSet.Add(pData.get());

    const bool added = (m_ToolBarSet.GetSize() > actSize);

    if (added)
        pData.release();

    return added;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::UnregisterToolBar(CControlBar* pBar)
{
    IToolBarIterator it(&m_ToolBarSet);

    for (IToolBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_pBar == pBar)
        {
            // hide the control bar
            pData->m_pFrame->ShowControlBar(pData->m_pBar, FALSE, FALSE);

            // remove the control bar from the set
            it.Remove();

            // delete the control bar
            delete pData;
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::UnregisterToolBar(UINT toolBarID)
{
    IToolBarIterator it(&m_ToolBarSet);

    for (IToolBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_ToolBarID == toolBarID)
        {
            SECCustomToolBar* pToolBar = NULL;

            if (m_pToolBarManager)
                pToolBar = m_pToolBarManager->ToolBarFromID(toolBarID);

            // if the toolbar was found, hide the control bar
            if (pToolBar)
                pData->m_pFrame->ShowControlBar(pToolBar, FALSE, FALSE);

            // remove the control bar from the set
            it.Remove();

            // delete the data pointer
            delete pData;
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::RegisterMenuBar(const CString& name, CMenu* pMenu, CFrameWnd* pFrame, EModelNotation notation)
{
    // check if menu bar exists
    if (MenuBarExist(name))
        return true;

    const int actSize = m_MenuBarSet.GetSize();

    std::unique_ptr<IMenuBarData> pData(new IMenuBarData(name, pMenu, pFrame, notation));
    m_MenuBarSet.Add(pData.get());

    const bool added = (m_MenuBarSet.GetSize() > actSize);

    if (added)
        pData.release();

    return added;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::RegisterMenuBar(const CString& name, UINT menuBarID, CFrameWnd* pFrame, EModelNotation notation)
{
    // check if menu bar exists
    if (MenuBarExist(name))
        return true;

    const int actSize = m_MenuBarSet.GetSize();

    PSS_BaseMainFrame* pMainFrame = dynamic_cast<PSS_BaseMainFrame*>(pFrame);

    // load additional menus
    if (pMainFrame)
        pMainFrame->LoadAdditionalMenus(1, menuBarID);

    std::unique_ptr<IMenuBarData> pData(new IMenuBarData(name, menuBarID, pFrame, notation));
    m_MenuBarSet.Add(pData.get());

    const bool added = (m_MenuBarSet.GetSize() > actSize);

    if (added)
        pData.release();

    return added;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::RegisterAndLoadMenuBar(const CString& name, UINT menuBarID, CFrameWnd* pFrame, EModelNotation notation)
{
    PSS_BaseMainFrame* pMainFrame = dynamic_cast<PSS_BaseMainFrame*>(pFrame);

    if (pMainFrame)
    {
        pMainFrame->LoadMenuBar(menuBarID);
        return RegisterMenuBar(name, menuBarID, pFrame, notation);
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::UnregisterMenuBar(CMenu* pMenu)
{
    IMenuBarIterator it(&m_MenuBarSet);

    for (IMenuBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_pMenu == pMenu)
        {
            // hide the menu bar and remove it from the set
            it.Remove();

            // delete the menu bar
            delete pData;
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::UnregisterMenuBar(UINT menuBarID)
{
    IMenuBarIterator it(&m_MenuBarSet);

    for (IMenuBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_MenuID == menuBarID)
        {
            // hide the menu bar and remove it from the set
            it.Remove();

            // delete the menu bar
            delete pData;
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::SwitchContext(EModelNotation notation)
{
    // do nothing if already in the current notation
    if (m_CurrentNotation != notation)
    {
        // hide all toolbars from the current notation
        if (!HideToolBars(m_CurrentNotation))
            return false;

        // hide all menu bars from the current notation
        if (!HideMenuBars(m_CurrentNotation))
            return false;

        // show all toolbars matching with the new notation
        if (!ShowToolBars(notation))
            return false;
    }

    // show all menu bars matching with the new notation
    if (!ShowMenuBars(notation))
        return false;

    // keep the current notation
    m_CurrentNotation = notation;
    return true;
}
//---------------------------------------------------------------------------
void PSS_FloatingToolBar::ReloadBarState()
{
    if (!m_pWndConf)
        return;

    IToolBarIterator it(&m_ToolBarSet);

    for (IToolBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_pBar)
            m_pWndConf->RestoreWindowPosition(pData->m_pBar, pData->m_Name, TRUE);
}
//---------------------------------------------------------------------------
void PSS_FloatingToolBar::ReloadBarState(const CString& name)
{
    if (!m_pWndConf)
        return;

    IToolBarIterator it(&m_ToolBarSet);

    for (IToolBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_pBar && pData->m_Name == name)
            m_pWndConf->RestoreWindowPosition(pData->m_pBar, pData->m_Name, TRUE);
}
//---------------------------------------------------------------------------
void PSS_FloatingToolBar::SaveBarState()
{
    if (!m_pWndConf)
        return;

    IToolBarIterator it(&m_ToolBarSet);

    for (IToolBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_pBar)
            m_pWndConf->SaveWindowPosition(pData->m_pBar, pData->m_Name, TRUE);
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::ShowToolBars(EModelNotation notation)
{
    IToolBarIterator it(&m_ToolBarSet);

    for (IToolBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Notation == notation)
            if (pData->m_pBar)
                // show the control bar
                pData->m_pFrame->ShowControlBar(pData->m_pBar, TRUE, TRUE);
            else
            {
                SECCustomToolBar* pToolBar = NULL;

                if (m_pToolBarManager)
                    pToolBar = m_pToolBarManager->ToolBarFromID(pData->m_ToolBarID);

                // if the toolbar was found, hide the control bar
                if (pToolBar)
                    pData->m_pFrame->ShowControlBar(pToolBar, TRUE, TRUE);
            }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::HideToolBars(EModelNotation notation)
{
    IToolBarIterator it(&m_ToolBarSet);

    for (IToolBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Notation == notation)
            if (pData->m_pBar)
                // hide the control bar
                pData->m_pFrame->ShowControlBar(pData->m_pBar, FALSE, TRUE);
            else
            {
                SECCustomToolBar* pToolBar = NULL;

                if (m_pToolBarManager)
                    pToolBar = m_pToolBarManager->ToolBarFromID(pData->m_ToolBarID);

                // if the toolbar was found, hide the control bar
                if (pToolBar)
                    pData->m_pFrame->ShowControlBar(pToolBar, FALSE, FALSE);
            }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::ToolBarExist(const CString& name)
{
    IToolBarIterator it(&m_ToolBarSet);

    for (IToolBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Name == name)
            return true;

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::ToolBarExist(UINT toolBarID)
{
    IToolBarIterator it(&m_ToolBarSet);

    for (IToolBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_ToolBarID == toolBarID)
            return true;

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::ToolBarExist(CControlBar* pBar)
{
    IToolBarIterator it(&m_ToolBarSet);

    for (IToolBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_pBar == pBar)
            return true;

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::ShowMenuBars(EModelNotation notation)
{
    IMenuBarIterator it(&m_MenuBarSet);

    for (IMenuBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Notation == notation)
            if (pData->m_MenuID == -1)
            {
                pData->m_pFrame->Invalidate();
                pData->m_pFrame->SetMenu(pData->m_pMenu);
                pData->m_pFrame->DrawMenuBar();
                pData->m_pFrame->RecalcLayout();
                pData->m_pFrame->UpdateWindow();
            }
            else
            {
                PSS_Assert(pData->m_pFrame);
                ASSERT_KINDOF(SECMDIFrameWnd, pData->m_pFrame);
                SECMDIFrameWnd* pMainWnd = (SECMDIFrameWnd*)pData->m_pFrame;

                // update the menu bar, if any
                pMainWnd->ActivateMenu(pData->m_MenuID);
            }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::HideMenuBars(EModelNotation notation)
{
    IMenuBarIterator it(&m_MenuBarSet);

    for (IMenuBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Notation == notation)
            if (pData->m_MenuID == -1)
            {
                // hide the control bar
                pData->m_pFrame->Invalidate();
                pData->m_pFrame->SetMenu(NULL);
                pData->m_pFrame->RecalcLayout();
                pData->m_pFrame->UpdateWindow();
            }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::MenuBarExist(const CString& name)
{
    IMenuBarIterator it(&m_MenuBarSet);

    for (IMenuBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Name == name)
            return true;

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::MenuBarExist(UINT menuBarID)
{
    IMenuBarIterator it(&m_MenuBarSet);

    for (IMenuBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_MenuID == menuBarID)
            return true;

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FloatingToolBar::MenuBarExist(CMenu* pMenu)
{
    IMenuBarIterator it(&m_MenuBarSet);

    for (IMenuBarData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_pMenu == pMenu)
            return true;

    return false;
}
//---------------------------------------------------------------------------
