// ZVInputAttributes.cpp : implementation file
//

#include "stdafx.h"
#include "ZVInputAttributes.h"

#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zBaseLib\PSS_DocumentObserverMsg.h"

#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "PSS_ProcessGraphModelMdlBP.h"

#include "ZVInputAttributesDefinitionDlg.h"
#include "ZBInputAttributes.h"

#include "zModel\PSS_SymbolObserverMsg.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"

#include "zModel\PSS_DynamicAttributesManipulator.h"

#include "zBaseLib\PSS_MsgBox.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Constant definition
const int _FlatToolbarHeight = 22;

const int IDC_ADDINPUTATTRIBUTE = 8000;
const int IDC_DELETEINPUTATTRIBUTE = 8001;
const int IDC_REFRESHVIEWS = 8002;
const int IDC_MODIFYINPUTATTRIBUTE = 8003;
const int IDC_SHOWSYMBOLATTRIBUTE = 8004;
const int IDC_SHOWALLATTRIBUTE = 8005;

const int UM_REFRESH = 21000;
const int UM_ADDINPUTATTRIBUTE = 21001;
const int UM_DELETEINPUTATTRIBUTE = 21002;
const int UM_MODIFYINPUTATTRIBUTE = 21003;
const int UM_SHOWSYMBOLATTRIBUTE = 21004;
const int UM_SHOWALLATTRIBUTE = 21005;

const int IDC_INPUTATTRIBUTE_FLATTOOLBAR = 11000;
const int IDC_INPUTATTRIBUTE_LISTCTRL = 11001;

/////////////////////////////////////////////////////////////////////////////
// _ZVFlatToolBarInputAttributes

_ZVFlatToolBarInputAttributes::_ZVFlatToolBarInputAttributes()
{
    m_ImageList.Create(IDB_INPUTATTRIBUTE_FLATTOOLBAR, 20, 1, RGB(255, 0, 255));
}

_ZVFlatToolBarInputAttributes::~_ZVFlatToolBarInputAttributes()
{}


BEGIN_MESSAGE_MAP(_ZVFlatToolBarInputAttributes, CStatic)
    //{{AFX_MSG_MAP(_ZVFlatToolBarInputAttributes)
    ON_BN_CLICKED(IDC_ADDINPUTATTRIBUTE, OnAddInputAttributeButton)
    ON_BN_CLICKED(IDC_DELETEINPUTATTRIBUTE, OnDeleteInputAttributeButton)
    ON_BN_CLICKED(IDC_MODIFYINPUTATTRIBUTE, OnModifyInputAttributeButton)
    ON_BN_CLICKED(IDC_SHOWSYMBOLATTRIBUTE, OnShowSymbolAttributeButton)
    ON_BN_CLICKED(IDC_SHOWALLATTRIBUTE, OnShowAllAttributeButton)
    ON_BN_CLICKED(IDC_REFRESHVIEWS, OnRefreshButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// _ZVFlatToolBarInputAttributes message handlers

int _ZVFlatToolBarInputAttributes::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
        return -1;

    int    IconIndex = 0;

    CRect rc;
    GetWindowRect(&rc);
    ScreenToClient(&rc);
    rc.top += 1; rc.bottom -= 1;
    rc.left += 1;
    rc.right = rc.left + 24;


    if (!m_RefreshButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                rc, this, IDC_REFRESHVIEWS))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }
    m_RefreshButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_AddInputAttributeButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                          rc, this, IDC_ADDINPUTATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }
    m_AddInputAttributeButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_DeleteInputAttributeButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                             rc, this, IDC_DELETEINPUTATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }
    m_DeleteInputAttributeButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_ModifyInputAttributeButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                             rc, this, IDC_MODIFYINPUTATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }
    m_ModifyInputAttributeButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_ShowSymbolAttributeButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                            rc, this, IDC_SHOWSYMBOLATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }
    m_ShowSymbolAttributeButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_ShowAllAttributeButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                         rc, this, IDC_SHOWALLATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }
    m_ShowAllAttributeButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);


    // Create the ToolTip control.
    m_tooltip.Create(this);
    m_tooltip.Activate(TRUE);

    m_tooltip.AddTool(GetDlgItem(IDC_REFRESHVIEWS), IDS_REFRESH);
    m_tooltip.AddTool(GetDlgItem(IDC_ADDINPUTATTRIBUTE), IDS_ADDINPUTATTRIBUTE_TTIPS);
    m_tooltip.AddTool(GetDlgItem(IDC_DELETEINPUTATTRIBUTE), IDS_DELETEINPUTATTRIBUTE_TTIPS);
    m_tooltip.AddTool(GetDlgItem(IDC_MODIFYINPUTATTRIBUTE), IDS_MODIFYINPUTATTRIBUTE_TTIPS);
    m_tooltip.AddTool(GetDlgItem(IDC_SHOWSYMBOLATTRIBUTE), IDS_SHOWSYMBOLATTRIBUTE_TTIPS);
    m_tooltip.AddTool(GetDlgItem(IDC_SHOWALLATTRIBUTE), IDS_SHOWALLATTRIBUTE_TTIPS);

    return 0;
}

void _ZVFlatToolBarInputAttributes::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();


}

void _ZVFlatToolBarInputAttributes::OnRefreshButton()
{
    PSS_ToolbarObserverMsg    msg(UM_REFRESH);
    NotifyAllObservers(&msg);
}

void _ZVFlatToolBarInputAttributes::OnAddInputAttributeButton()
{
    PSS_ToolbarObserverMsg    msg(UM_ADDINPUTATTRIBUTE);
    NotifyAllObservers(&msg);
}

void _ZVFlatToolBarInputAttributes::OnDeleteInputAttributeButton()
{
    PSS_ToolbarObserverMsg    msg(UM_DELETEINPUTATTRIBUTE);
    NotifyAllObservers(&msg);
}


void _ZVFlatToolBarInputAttributes::OnModifyInputAttributeButton()
{
    PSS_ToolbarObserverMsg    msg(UM_MODIFYINPUTATTRIBUTE);
    NotifyAllObservers(&msg);
}

void _ZVFlatToolBarInputAttributes::OnShowSymbolAttributeButton()
{
    PSS_ToolbarObserverMsg    msg(UM_SHOWSYMBOLATTRIBUTE);
    NotifyAllObservers(&msg);
}

void _ZVFlatToolBarInputAttributes::OnShowAllAttributeButton()
{
    PSS_ToolbarObserverMsg    msg(UM_SHOWALLATTRIBUTE);
    NotifyAllObservers(&msg);
}




BOOL _ZVFlatToolBarInputAttributes::PreTranslateMessage(MSG* pMsg)
{
    // Let the ToolTip process this message.
    m_tooltip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// ZVInputAttributes

IMPLEMENT_DYNCREATE(ZVInputAttributes, CWnd)

BEGIN_MESSAGE_MAP(ZVInputAttributes, CWnd)
    //{{AFX_MSG_MAP(ZVInputAttributes)
    ON_WM_CREATE()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()




ZVInputAttributes::ZVInputAttributes()
    : m_pCurrentDoc(NULL),
    m_SymbolRef(-1)
{}

ZVInputAttributes::~ZVInputAttributes()
{
    // todo -cCheck -oJean: on 26.09.2019, check if this modification is valid, revert it otherwise
    m_FlatToolBar.DetachObserver(this);
    m_listctrl.DetachObserver(this);
}


void ZVInputAttributes::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // Forward the message to the property control
    m_listctrl.OnUpdate(pSubject, pMsg);

    if (pMsg && ISA(pMsg, PSS_SymbolObserverMsg))
    {
        if (dynamic_cast<PSS_SymbolObserverMsg*>(pMsg)->GetActionType() == PSS_SymbolObserverMsg::IE_AT_ElementSelected)
        {
            if (dynamic_cast<PSS_SymbolObserverMsg*>(pMsg)->GetElement() &&
                (ISA(dynamic_cast<PSS_SymbolObserverMsg*>(pMsg)->GetElement(), PSS_Symbol) ||
                 ISA(dynamic_cast<PSS_SymbolObserverMsg*>(pMsg)->GetElement(), PSS_LinkSymbol)))
                m_SymbolRef = dynamic_cast<PSS_BasicSymbol*>(dynamic_cast<PSS_SymbolObserverMsg*>(pMsg)->GetElement())->GetSymbolReferenceNumber();
        }
    }
    else
        if (pMsg && ISA(pMsg, PSS_ToolbarObserverMsg))
        {
            switch (dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg)->GetMessageID())
            {
                case UM_REFRESH:
                {
                    OnRefresh();
                    break;
                }
                case UM_ADDINPUTATTRIBUTE:
                {
                    OnAddInputAttribute();
                    break;
                }
                case UM_DELETEINPUTATTRIBUTE:
                {
                    OnDeleteInputAttribute();
                    break;
                }
                case UM_MODIFYINPUTATTRIBUTE:
                {
                    OnModifyInputAttribute();
                    break;
                }
                case UM_SHOWSYMBOLATTRIBUTE:
                {
                    ShowAll(false);
                    break;
                }
                case UM_SHOWALLATTRIBUTE:
                {
                    ShowAll();
                    break;
                }
            }
        }
        else
            // Check about document close
            if (pMsg && ISA(pMsg, PSS_DocumentObserverMsg) &&
                ISA(dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetDocument(), PSS_ProcessGraphModelDoc))
            {
                switch (dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetMessageID())
                {
                    case UM_REFRESHDOCUMENT:
                    case UM_OPENDOCUMENT: break;

                    case UM_CLOSEDOCUMENT:
                    {
                        Empty();
                        break;
                    }
                    case UM_FRAMEHASBEENACTIVATED:
                    {
                        m_pCurrentDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetDocument());
                    }

                }
            }


}


void ZVInputAttributes::Refresh()
{
    CWaitCursor    Cursor;
    // Refresh controls
    if (::IsWindow(m_listctrl.GetSafeHwnd()))
        m_listctrl.Refresh();
}

void ZVInputAttributes::Empty()
{
    CWaitCursor    Cursor;
    if (::IsWindow(m_listctrl.GetSafeHwnd()))
        m_listctrl.Empty();
}


/////////////////////////////////////////////////////////////////////////////
// ZVInputAttributes message handlers


int ZVInputAttributes::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // Create the flat toolbar
    reinterpret_cast<CStatic&>(m_FlatToolBar).Create(_T(""), WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT, CRect(0, 0, 100, _FlatToolbarHeight), this, IDC_INPUTATTRIBUTE_FLATTOOLBAR);
    // Create the list control
    m_listctrl.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | LBS_NOINTEGRALHEIGHT | LVS_REPORT, CRect(0, 0, 0, 0), this, IDC_INPUTATTRIBUTE_LISTCTRL);

    // Attach us as an observer for messages
    m_FlatToolBar.AttachObserver(this);
    m_listctrl.AttachObserver(this);

    return 0;
}

void ZVInputAttributes::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_FlatToolBar.GetSafeHwnd()) &&
        ::IsWindow(m_listctrl.GetSafeHwnd()))
    {
        m_FlatToolBar.MoveWindow(0, 0, cx, _FlatToolbarHeight);
        m_listctrl.MoveWindow(0, _FlatToolbarHeight, cx, cy - _FlatToolbarHeight);
    }
}


/////////////////////////////////////////////////////////////////////////////
// ZVInputAttributes message handlers from toolbar

void ZVInputAttributes::OnRefresh()
{
    Refresh();
}

void ZVInputAttributes::OnAddInputAttribute()
{
    if (!m_pCurrentDoc)
        return;
    if (!m_pCurrentDoc->GetModel() ||
        !ISA(m_pCurrentDoc->GetModel(), PSS_ProcessGraphModelMdlBP))
        return;

    if (!dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pCurrentDoc->GetModel())->HasInputAttributes())
        dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pCurrentDoc->GetModel())->AllocateInputAttributes();

    ZBInputAttributeManager* pInputAttrManager = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pCurrentDoc->GetModel())->GetInputAttributes();
    if (!pInputAttrManager)
        return;

    if (!m_pCurrentDoc->HasDynamicPropertiesManager())
        m_pCurrentDoc->AllocatePropertiesManager();

    ZBDynamicPropertiesManager* pDynPropMgr = m_pCurrentDoc->GetDynamicPropertiesManager();
    if (!pDynPropMgr)
        return;

    ZBPropertySet Set;
    PSS_DynamicAttributesManipulator::ExtractUniqueAttributes(m_pCurrentDoc->GetModel(), Set);


    ZVInputAttributesDefinitionDlg dlg(m_pCurrentDoc->GetDynamicPropertiesManager(), &Set);
    if (dlg.DoModal() == IDOK)
    {
        // Allocate a new attribute
        ZBInputAttribute* pInputAttribute = new ZBInputAttribute;
        ASSERT(pInputAttribute);

        // Assigns value members
        pInputAttribute->SetCategoryID(dlg.GetCategoryID());
        pInputAttribute->SetItemID(dlg.GetItemID());
        // If for the symbol selected
        if (dlg.GetVisibility() == 0)
            pInputAttribute->SetSymbolRef(m_SymbolRef);
        else
            // For the whole model
            pInputAttribute->SetSymbolRef(-1);

        pInputAttribute->SetDefaultValue(dlg.GetDefaultValue());
        pInputAttribute->SetFlag(dlg.GetFlag());

        // Then add the new attribute
        pInputAttrManager->AddInputAttribute(pInputAttribute);

        // Document is modified
        m_pCurrentDoc->SetModifiedFlag();
        // Refresh the list to reflect the change
        Refresh();
    }

    // Remove all properties
    ZBPropertyIterator i(&Set);
    ZBProperty* pProp;
    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
        delete pProp;
    Set.RemoveAll();

}

void ZVInputAttributes::OnDeleteInputAttribute()
{
    if (!m_pCurrentDoc)
        return;

    if (!m_pCurrentDoc->GetModel() ||
        !ISA(m_pCurrentDoc->GetModel(), PSS_ProcessGraphModelMdlBP))
        return;

    ZBInputAttributeManager* pInputAttrManager = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pCurrentDoc->GetModel())->GetInputAttributes();
    if (!pInputAttrManager)
        return;


    ZBInputAttribute* pInputAttribute = GetSelectedInputAttribute();
    if (!pInputAttribute)
        return;
    PSS_MsgBox mBox;
    if (mBox.Show(IDS_DELETEINPUTATTR_CONF, MB_YESNO) == IDYES)
    {
        pInputAttrManager->DeleteInputAttribute(pInputAttribute);

        // Document is modified
        m_pCurrentDoc->SetModifiedFlag();
        // Refresh the list to reflect the change
        Refresh();

    }
}

void ZVInputAttributes::OnModifyInputAttribute()
{
    if (!m_pCurrentDoc)
        return;

    ZBInputAttribute* pInputAttribute = GetSelectedInputAttribute();
    if (!pInputAttribute)
        return;

    ZVInputAttributesDefinitionDlg dlg(m_pCurrentDoc->GetDynamicPropertiesManager(), NULL, pInputAttribute);
    if (dlg.DoModal() == IDOK)
    {
        pInputAttribute->SetDefaultValue(dlg.GetDefaultValue());
        // If for the symbol selected
        if (dlg.GetVisibility() == 0)
            pInputAttribute->SetSymbolRef(m_SymbolRef);
        else
            // For the whole model
            pInputAttribute->SetSymbolRef(-1);
        pInputAttribute->SetFlag(dlg.GetFlag());

        // Document is modified
        m_pCurrentDoc->SetModifiedFlag();
        // Refresh the list to reflect the change
        Refresh();

    }
}
