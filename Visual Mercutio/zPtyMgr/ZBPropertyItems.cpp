// ZBPropertyItems.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBPropertyItems.h"

#include "ZCInPlaceEditPropItemString.h"
#include "ZCInPlaceListBox.h"
#include "ZCInPlaceExtendedEdit.h"
#include "ZCInPlaceIntelliEdit.h"
#include "ZCInPlaceMultiLineEdit.h"
#include "ZCInPlaceSearchEdit.h"
#include "ZCInPlaceDurationEdit.h"
#include "ZCInPlaceDateEdit.h"
//RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
#include "ZCInPlaceTimeEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 14 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemString

IMPLEMENT_DYNAMIC(ZBPropertyItemString, PSS_PropertyItem)

void ZBPropertyItemString::CreateInPlaceControl(CWnd*           pWndParent,
                                                const CRect&    rect,
                                                PSS_InPlaceEdit*& pWndInPlaceControl,
                                                const CSize&    extendedSize)
{
    CWnd* pWnd = dynamic_cast<CWnd*>(pWndInPlaceControl);

    DestroyInPlaceControl(pWndInPlaceControl);

    pWndInPlaceControl = new ZCInPlaceEditPropItemString();
    pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_StrValue, pWndParent, rect);
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemList

IMPLEMENT_DYNAMIC(ZBPropertyItemList, PSS_PropertyItem)

void ZBPropertyItemList::CreateInPlaceControl(CWnd*           pWndParent,
                                              const CRect&    rect,
                                              PSS_InPlaceEdit*& pWndInPlaceControl,
                                              const CSize&    extendedSize)
{
    CWnd* pWnd = dynamic_cast<CWnd*>(pWndInPlaceControl);
    DestroyInPlaceControl(pWndInPlaceControl);

    pWndInPlaceControl = new ZCInPlaceListBox(IsReadOnly());
    pWndInPlaceControl->InitializeInPlaceEditCtrl(this, GetData(), pWndParent, rect);

    SetItemListData((ZCInPlaceListBox*)pWndInPlaceControl);
    ((ZCInPlaceListBox*)pWndInPlaceControl)->SetCurSel(GetData(), false);
    ((ZCInPlaceListBox*)pWndInPlaceControl)->ResetListBoxHeight();
}

void ZBPropertyItemList::SetData(const CString sText)
{
    m_StrValue = sText;
}

void ZBPropertyItemList::SetItemListData(ZCInPlaceListBox* pWndInPlaceControl)
{
    LPCTSTR pStrText;

    for (int i = 0; (pStrText = GetItemData(i)) != NULL; i++)
    {
        pWndInPlaceControl->AddString(pStrText);
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemExtended

IMPLEMENT_DYNAMIC(ZBPropertyItemExtended, PSS_PropertyItem)

void ZBPropertyItemExtended::CreateInPlaceControl(CWnd*           pWndParent,
                                                  const CRect&    rect,
                                                  PSS_InPlaceEdit*& pWndInPlaceControl,
                                                  const CSize&    extendedSize)
{
    CWnd* pWnd = dynamic_cast<CWnd*>(pWndInPlaceControl);
    DestroyInPlaceControl(pWndInPlaceControl);

    pWndInPlaceControl = new ZCInPlaceExtendedEdit(IsReadOnly());

    // For processing extended command
    ((ZCInPlaceExtendedEdit*)pWndInPlaceControl)->SetSearchType(PSS_SearchEditButton::IE_T_Extended);

    switch (m_Type)
    {
        case IE_NT_String:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_StrValue, pWndParent, rect);
            break;
        }

        case IE_NT_Double:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_DoubleValue, pWndParent, rect);
            break;
        }

        case IE_NT_Float:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_FloatValue, pWndParent, rect);
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemIntelliEdit

IMPLEMENT_DYNAMIC(ZBPropertyItemIntelliEdit, PSS_PropertyItem)

void ZBPropertyItemIntelliEdit::CreateInPlaceControl(CWnd*           pWndParent,
                                                     const CRect&    rect,
                                                     PSS_InPlaceEdit*& pWndInPlaceControl,
                                                     const CSize&    extendedSize)
{
    CWnd* pWnd = dynamic_cast<CWnd*>(pWndInPlaceControl);
    DestroyInPlaceControl(pWndInPlaceControl);

    pWndInPlaceControl = new ZCInPlaceIntelliEdit(IsReadOnly());

    switch (m_Type)
    {
        case IE_NT_String:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_StrValue, pWndParent, rect);
            break;
        }

        case IE_NT_Double:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_DoubleValue, pWndParent, rect);
            break;
        }

        case IE_NT_Float:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_FloatValue, pWndParent, rect);
            break;
        }
    }

    // Initialize the control array of values
    ((ZCInPlaceIntelliEdit*)pWndInPlaceControl)->Initialize(m_data, (extendedSize.cx && extendedSize.cy) ?
                                                                            const_cast<CSize*>(&extendedSize) : NULL);
}

void ZBPropertyItemIntelliEdit::SetData(const CString sText)
{
    m_StrValue = sText;
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemMultiLineEdit

IMPLEMENT_DYNAMIC(ZBPropertyItemMultiLineEdit, PSS_PropertyItem)

void ZBPropertyItemMultiLineEdit::CreateInPlaceControl(CWnd*           pWndParent,
                                                       const CRect&    rect,
                                                       PSS_InPlaceEdit*& pWndInPlaceControl,
                                                       const CSize&    extendedSize)
{
    CWnd* pWnd = dynamic_cast<CWnd*>(pWndInPlaceControl);

    DestroyInPlaceControl(pWndInPlaceControl);

    pWndInPlaceControl = new ZCInPlaceMultiLineEdit(IsReadOnly());

    switch (m_Type)
    {
        case IE_NT_String:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_StrValue, pWndParent, rect);
            break;
        }

        case IE_NT_Double:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_DoubleValue, pWndParent, rect);
            break;
        }

        case IE_NT_Float:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_FloatValue, pWndParent, rect);
            break;
        }
    }

    // Initialize the control
    if (extendedSize.cx != 0 && extendedSize.cy != 0)
    {
        ((ZCInPlaceMultiLineEdit*)pWndInPlaceControl)->Initialize(extendedSize);
    }
    else
    {
        ((ZCInPlaceMultiLineEdit*)pWndInPlaceControl)->Initialize();
    }
}

void ZBPropertyItemMultiLineEdit::SetData(const CString sText)
{
    m_StrValue = sText;
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemDuration

IMPLEMENT_DYNAMIC(ZBPropertyItemDuration, PSS_PropertyItem)

void ZBPropertyItemDuration::CreateInPlaceControl(CWnd*           pWndParent,
                                                  const CRect&    rect,
                                                  PSS_InPlaceEdit*& pWndInPlaceControl,
                                                  const CSize&    extendedSize)
{
    CWnd* pWnd = dynamic_cast<CWnd*>(pWndInPlaceControl);
    DestroyInPlaceControl(pWndInPlaceControl);

    pWndInPlaceControl = new ZCInPlaceDurationEdit(IsReadOnly());

    // For processing extended command
    ((ZCInPlaceExtendedEdit*)pWndInPlaceControl)->SetSearchType(PSS_SearchEditButton::IE_T_Extended);

    switch (m_Type)
    {
        case IE_NT_String:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_StrValue, pWndParent, rect);
            break;
        }

        case IE_NT_Duration:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_DurationValue, pWndParent, rect);
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemDate

IMPLEMENT_DYNAMIC(ZBPropertyItemDate, PSS_PropertyItem)

void ZBPropertyItemDate::CreateInPlaceControl(CWnd*           pWndParent,
                                              const CRect&    rect,
                                              PSS_InPlaceEdit*& pWndInPlaceControl,
                                              const CSize&    extendedSize)
{
    CWnd* pWnd = dynamic_cast<CWnd*>(pWndInPlaceControl);
    DestroyInPlaceControl(pWndInPlaceControl);

    pWndInPlaceControl = new ZCInPlaceDateEdit(IsReadOnly());

    // For processing extended command
    ((ZCInPlaceExtendedEdit*)pWndInPlaceControl)->SetSearchType(PSS_SearchEditButton::IE_T_Extended);

    switch (m_Type)
    {
        case IE_NT_String:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_StrValue, pWndParent, rect);
            break;
        }

        case IE_NT_Date:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_DateValue, pWndParent, rect);
            break;
        }
    }
}

// RS-MODIF 08.08.2005: ajout de la propriété d'attribut "time"
/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemTime

IMPLEMENT_DYNAMIC(ZBPropertyItemTime, PSS_PropertyItem)

void ZBPropertyItemTime::CreateInPlaceControl(CWnd*           pWndParent,
                                              const CRect&    rect,
                                              PSS_InPlaceEdit*& pWndInPlaceControl,
                                              const CSize&    extendedSize)
{
    CWnd* pWnd = dynamic_cast<CWnd*>(pWndInPlaceControl);
    DestroyInPlaceControl(pWndInPlaceControl);

    pWndInPlaceControl = new ZCInPlaceTimeEdit(IsReadOnly());

    // For processing extended command
    ((ZCInPlaceExtendedEdit*)pWndInPlaceControl)->SetSearchType(PSS_SearchEditButton::IE_T_Extended);

    switch (m_Type)
    {
        case IE_NT_String:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_StrValue, pWndParent, rect);
            break;
        }

        case IE_NT_Time:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_TimeValue, pWndParent, rect);
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemMenuFileDir

IMPLEMENT_DYNAMIC(ZBPropertyItemMenuFileDir, PSS_PropertyItem)

void ZBPropertyItemMenuFileDir::CreateInPlaceControl(CWnd*           pWndParent,
                                                     const CRect&    rect,
                                                     PSS_InPlaceEdit*& pWndInPlaceControl,
                                                     const CSize&    extendedSize)
{
    CWnd* pWnd = dynamic_cast<CWnd*>(pWndInPlaceControl);
    DestroyInPlaceControl(pWndInPlaceControl);

    pWndInPlaceControl = new ZCInPlaceSearchEdit(IsReadOnly());

    switch (m_ControlType)
    {
        case MFD_MENU:
        {
            // Enable all menu items and no notification
            ((ZCInPlaceSearchEdit*)pWndInPlaceControl)->SetSearchType(PSS_SearchEditButton::IE_T_Popup,
                                                                      m_pMenu,
                                                                      true,
                                                                      true);

            break;
        }

        case MFD_FILE:
        {
            ((ZCInPlaceSearchEdit*)pWndInPlaceControl)->SetSearchType(PSS_SearchEditButton::IE_T_File);
            break;
        }

        case MFD_DIRECTORY:
        {
            ((ZCInPlaceSearchEdit*)pWndInPlaceControl)->SetSearchType(PSS_SearchEditButton::IE_T_Directory);
            break;
        }
    }

    switch (m_Type)
    {
        case IE_NT_String:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_StrValue, pWndParent, rect);
            break;
        }

        case IE_NT_Double:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_DoubleValue, pWndParent, rect);
            break;
        }

        case IE_NT_Float:
        {
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_FloatValue, pWndParent, rect);
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBPropertyItemNumber

IMPLEMENT_DYNAMIC(ZBPropertyItemNumber, PSS_PropertyItem)

void ZBPropertyItemNumber::CreateInPlaceControl(CWnd*           pWndParent,
                                                const CRect&    rect,
                                                PSS_InPlaceEdit*& pWndInPlaceControl,
                                                const CSize&    extendedSize)
{
    CWnd* pWnd = dynamic_cast<CWnd*>(pWndInPlaceControl);
    DestroyInPlaceControl(pWndInPlaceControl);

    switch (m_Type)
    {
        case IE_NT_Double:
        {
            pWndInPlaceControl = new ZCInPlaceEditPropItemNumber(m_DoubleValue, IsReadOnly());
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_DoubleValue, pWndParent, rect);
            break;
        }

        case IE_NT_Float:
        {
            pWndInPlaceControl = new ZCInPlaceEditPropItemNumber(m_FloatValue, IsReadOnly());
            pWndInPlaceControl->InitializeInPlaceEditCtrl(this, m_FloatValue, pWndParent, rect);
            break;
        }
    }
}
