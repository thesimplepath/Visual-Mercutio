/****************************************************************************
 * ==> PSS_PropertyEditControl ---------------------------------------------*
 ****************************************************************************
 * Description : Override the CEdit class, in order to create a custom edit *
 *               control which allows to show properties                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PropertyEditControl.h"

// processsoft
#include "zBaseLibRes.h"

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PropertyEditControl, CEdit)
//{{AFX_MSG_MAP(PSS_PropertyEditControl)
    ON_COMMAND(ID_PROPERTIES_CANCEL, OnCancel)
    ON_COMMAND(ID_PROPERTIES_CUT, OnCut)
    ON_COMMAND(ID_PROPERTIES_COPY, OnCopy)
    ON_COMMAND(ID_PROPERTIES_PASTE, OnPaste)
    ON_COMMAND(ID_PROPERTIES_DELETE, OnDelete)
    ON_WM_RBUTTONUP()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PropertyEditControl
//---------------------------------------------------------------------------
PSS_PropertyEditControl::PSS_PropertyEditControl() :
    CEdit()
{}
//---------------------------------------------------------------------------
PSS_PropertyEditControl::~PSS_PropertyEditControl()
{}
//---------------------------------------------------------------------------
afx_msg void PSS_PropertyEditControl::OnCancel()
{
    Undo();
    OnPropertieValueChanged();
}
//---------------------------------------------------------------------------
afx_msg void PSS_PropertyEditControl::OnCut()
{
    Cut();
    OnPropertieValueChanged();
}
//---------------------------------------------------------------------------
afx_msg void PSS_PropertyEditControl::OnCopy()
{
    // copy to clipboard, so the component value will not change. For that reason
    // the OnPropertieValueChanged() function isn't called
    Copy();
}
//---------------------------------------------------------------------------
afx_msg void PSS_PropertyEditControl::OnPaste()
{
    Paste();
    OnPropertieValueChanged();
}
//---------------------------------------------------------------------------
afx_msg void PSS_PropertyEditControl::OnDelete()
{
    Clear();
    OnPropertieValueChanged();
}
//---------------------------------------------------------------------------
afx_msg void PSS_PropertyEditControl::OnRButtonUp(UINT nFlags, CPoint point)
{
    // if the menu is still not loaded in memory, load it
    if (!m_pPropertiesMenu.GetSafeHmenu())
        m_pPropertiesMenu.LoadMenu(IDR_PROPERTIES_POPUP);

    // Convert local coordinates to screen coordinates
    CPoint pt(point);
    ClientToScreen(&pt);

    // get menu pointer. This works as follow:
    // Properties =========> m_pPropertiesMenu
    //     |            |
    //     |- Cancel    |
    //     |- --------- |
    //     |- Cut       |
    //     |- Copy      | => m_pPropertiesMenu.GetSubMenu(0)
    //     |- Paste     |
    //     |- --------- |
    //     |- Delete    |
    //     |            |
    // Thus, if m_pPropertiesMenu is only used to get the popup menu via TrackPopupMenu,
    // the result will be to show the Properties item, or at worst a simple blank square
    CMenu* pPopupMenu = m_pPropertiesMenu.GetSubMenu(0);

    // show the menu
    if (pPopupMenu)
        pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, this);
}
//---------------------------------------------------------------------------
void PSS_PropertyEditControl::OnPropertieValueChanged()
{}
//---------------------------------------------------------------------------
