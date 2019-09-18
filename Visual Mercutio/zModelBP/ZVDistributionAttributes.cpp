// ZVDistributionAttributes.cpp : implementation file
//

#include "stdafx.h"
#include "ZVDistributionAttributes.h"

#include "zBaseLib\ZBToolbarObserverMsg.h"
#include "zBaseLib\PSS_DocumentObserverMsg.h"

#include "zModel\ProcGraphModelDoc.h"
#include "ProcGraphModelMdlBP.h"

#include "ZVDistributionAttributesDefinitionDlg.h"

#include "ZBDistributionAttributes.h"

#include "zModel\ZBSymbolObserverMsg.h"
#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"

#include "ZBBPProcedureSymbol.h"
#include "ZBBPStartSymbol.h"
#include "ZBBPStopSymbol.h"

#include "zModel\ZUDynamicAttributesManipulator.h"

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

const int IDC_ADDDISTRIBUTIONATTRIBUTE = 9000;
const int IDC_DELETEDISTRIBUTIONATTRIBUTE = 9001;
const int IDC_REFRESHVIEWS = 9002;
const int IDC_MODIFYDISTRIBUTIONATTRIBUTE = 9003;

const int UM_REFRESH = 22000;
const int UM_ADDDISTRIBUTIONATTRIBUTE = 22001;
const int UM_DELETEDISTRIBUTIONATTRIBUTE = 22002;
const int UM_MODIFYDISTRIBUTIONATTRIBUTE = 22003;

const int IDC_DISTRIBUTIONATTRIBUTE_FLATTOOLBAR = 12000;
const int IDC_DISTRIBUTIONATTRIBUTE_LISTCTRL = 12001;

/////////////////////////////////////////////////////////////////////////////
// _ZVFlatToolBarDistributionAttribs

_ZVFlatToolBarDistributionAttribs::_ZVFlatToolBarDistributionAttribs()
{
    m_ImageList.Create(IDB_DISTRIBATTRIBUTE_FLATTOOLBAR, 20, 1, RGB(255, 0, 255));
}

_ZVFlatToolBarDistributionAttribs::~_ZVFlatToolBarDistributionAttribs()
{}


BEGIN_MESSAGE_MAP(_ZVFlatToolBarDistributionAttribs, CStatic)
    //{{AFX_MSG_MAP(_ZVFlatToolBarDistributionAttribs)
    ON_BN_CLICKED(IDC_ADDDISTRIBUTIONATTRIBUTE, OnAddDistributionAttribButton)
    ON_BN_CLICKED(IDC_DELETEDISTRIBUTIONATTRIBUTE, OnDeleteDistributionAttribButton)
    ON_BN_CLICKED(IDC_MODIFYDISTRIBUTIONATTRIBUTE, OnModifyDistributionAttribButton)
    ON_BN_CLICKED(IDC_REFRESHVIEWS, OnRefreshButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// _ZVFlatToolBarDistributionAttribs message handlers

int _ZVFlatToolBarDistributionAttribs::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

    if (!m_AddDistributionAttribButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                              rc, this, IDC_ADDDISTRIBUTIONATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }
    m_AddDistributionAttribButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_DeleteDistributionAttribButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                                 rc, this, IDC_DELETEDISTRIBUTIONATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }
    m_DeleteDistributionAttribButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);

    if (!m_ModifyDistributionAttribButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                                 rc, this, IDC_MODIFYDISTRIBUTIONATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }
    m_ModifyDistributionAttribButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(20, 20));
    rc.OffsetRect(24, 0);


    // Create the ToolTip control.
    m_tooltip.Create(this);
    m_tooltip.Activate(TRUE);

    m_tooltip.AddTool(GetDlgItem(IDC_REFRESHVIEWS), IDS_REFRESH);
    m_tooltip.AddTool(GetDlgItem(IDC_ADDDISTRIBUTIONATTRIBUTE), IDS_ADDDISTRIBUTIONATTRIBUTE_TTIPS);
    m_tooltip.AddTool(GetDlgItem(IDC_DELETEDISTRIBUTIONATTRIBUTE), IDS_DELETEDISTRIBUTIONATTRIBUTE_TTIPS);
    m_tooltip.AddTool(GetDlgItem(IDC_MODIFYDISTRIBUTIONATTRIBUTE), IDS_MODIFYDISTRIBUTIONATTRIBUTE_TTIPS);

    return 0;
}

void _ZVFlatToolBarDistributionAttribs::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();


}

void _ZVFlatToolBarDistributionAttribs::OnRefreshButton()
{
    ZBToolbarObserverMsg    Msg(UM_REFRESH);
    NotifyAllObservers(&Msg);
}

void _ZVFlatToolBarDistributionAttribs::OnAddDistributionAttribButton()
{
    ZBToolbarObserverMsg    Msg(UM_ADDDISTRIBUTIONATTRIBUTE);
    NotifyAllObservers(&Msg);
}

void _ZVFlatToolBarDistributionAttribs::OnDeleteDistributionAttribButton()
{
    ZBToolbarObserverMsg    Msg(UM_DELETEDISTRIBUTIONATTRIBUTE);
    NotifyAllObservers(&Msg);
}


void _ZVFlatToolBarDistributionAttribs::OnModifyDistributionAttribButton()
{
    ZBToolbarObserverMsg    Msg(UM_MODIFYDISTRIBUTIONATTRIBUTE);
    NotifyAllObservers(&Msg);
}


BOOL _ZVFlatToolBarDistributionAttribs::PreTranslateMessage(MSG* pMsg)
{
    // Let the ToolTip process this message.
    m_tooltip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// ZVDistributionAttributes

IMPLEMENT_DYNCREATE(ZVDistributionAttributes, CWnd)

BEGIN_MESSAGE_MAP(ZVDistributionAttributes, CWnd)
    //{{AFX_MSG_MAP(ZVDistributionAttributes)
    ON_WM_CREATE()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()




ZVDistributionAttributes::ZVDistributionAttributes()
    : m_pCurrentDoc(NULL),
    m_pSymbol(NULL)
{}

ZVDistributionAttributes::~ZVDistributionAttributes()
{}


void ZVDistributionAttributes::OnUpdate(ZISubject* pSubject, ZIObserverMsg* pMsg)
{
    // Forward the message to the property control
    m_listctrl.OnUpdate(pSubject, pMsg);

    if (pMsg && ISA(pMsg, ZBSymbolObserverMsg))
    {
        if (dynamic_cast<ZBSymbolObserverMsg*>(pMsg)->GetActionType() == ZBSymbolObserverMsg::ElementSelected)
        {
            m_pSymbol = dynamic_cast<ZBSymbolObserverMsg*>(pMsg)->GetpElement();
        }
    }
    else
        if (pMsg && ISA(pMsg, ZBToolbarObserverMsg))
        {
            switch (dynamic_cast<ZBToolbarObserverMsg*>(pMsg)->GetMessageID())
            {
                case UM_REFRESH:
                {
                    OnRefresh();
                    break;
                }
                case UM_ADDDISTRIBUTIONATTRIBUTE:
                {
                    OnAddDistributionAttrib();
                    break;
                }
                case UM_DELETEDISTRIBUTIONATTRIBUTE:
                {
                    OnDeleteDistributionAttrib();
                    break;
                }
                case UM_MODIFYDISTRIBUTIONATTRIBUTE:
                {
                    OnModifyDistributionAttrib();
                    break;
                }
            }
        }
        else
            // Check about document close
            if (pMsg && ISA(pMsg, PSS_DocumentObserverMsg) &&
                ISA(dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetDocument(), ZDProcessGraphModelDoc))
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
                        m_pCurrentDoc = dynamic_cast<ZDProcessGraphModelDoc*>(dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetDocument());
                    }

                }
            }


}


void ZVDistributionAttributes::Refresh()
{
    CWaitCursor    Cursor;
    // Refresh controls
    if (::IsWindow(m_listctrl.GetSafeHwnd()))
        m_listctrl.Refresh();
}

void ZVDistributionAttributes::Empty()
{
    CWaitCursor    Cursor;
    m_listctrl.Empty();
}


/////////////////////////////////////////////////////////////////////////////
// ZVDistributionAttributes message handlers


int ZVDistributionAttributes::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // Create the flat toolbar
    reinterpret_cast<CStatic&>(m_FlatToolBar).Create(_T(""), WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT, CRect(0, 0, 100, _FlatToolbarHeight), this, IDC_DISTRIBUTIONATTRIBUTE_FLATTOOLBAR);
    // Create the list control
    m_listctrl.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | LBS_NOINTEGRALHEIGHT | LVS_REPORT | LVS_SHOWSELALWAYS, CRect(0, 0, 0, 0), this, IDC_DISTRIBUTIONATTRIBUTE_LISTCTRL);

    // Attach us as an observer for messages
    m_FlatToolBar.AttachObserver(this);
    m_listctrl.AttachObserver(this);

    return 0;
}

void ZVDistributionAttributes::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_FlatToolBar.GetSafeHwnd()) &&
        ::IsWindow(m_listctrl.GetSafeHwnd()))
    {
        m_FlatToolBar.MoveWindow(0, 0, cx, _FlatToolbarHeight);
        m_listctrl.MoveWindow(0, _FlatToolbarHeight, cx, cy - _FlatToolbarHeight);
    }
}

CString ZVDistributionAttributes::GetAndCheckUnitGUID() const
{
    CString UnitGUID;
    // Check if the symbol selected can accept distribution attributes
    // and has a group defined
    if (m_pSymbol)
    {
        if (ISA(m_pSymbol, ZBBPProcedureSymbol))
            UnitGUID = dynamic_cast<ZBBPProcedureSymbol*>(m_pSymbol)->GetUnitGUID();
        else
            if (ISA(m_pSymbol, ZBBPStartSymbol))
                UnitGUID = (wchar_t)(dynamic_cast<ZBBPStartSymbol*>(m_pSymbol)->GetUnitGUID().IsEmpty());
            else
                if (ISA(m_pSymbol, ZBBPStopSymbol))
                    UnitGUID = (wchar_t)(dynamic_cast<ZBBPStopSymbol*>(m_pSymbol)->GetUnitGUID().IsEmpty());
                else
                {
                    PSS_MsgBox mBox;
                    mBox.Show(IDS_DISTRIBUTIONATTR_WRONGSYMBOLSEL, MB_OK);
                    return _T("");
                }

        if (UnitGUID.IsEmpty())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_DISTRIBUTIONATTR_NOUSERGROUPDEF, MB_OK);
            return _T("");
        }

    }

    return UnitGUID;
}

/////////////////////////////////////////////////////////////////////////////
// ZVDistributionAttributes message handlers from toolbar

void ZVDistributionAttributes::OnRefresh()
{
    Refresh();
}

void ZVDistributionAttributes::OnAddDistributionAttrib()
{
    if (!m_pCurrentDoc)
        return;
    if (!m_pCurrentDoc->GetModel() ||
        !ISA(m_pCurrentDoc->GetModel(), ZDProcessGraphModelMdlBP))
        return;

    if (!dynamic_cast<ZDProcessGraphModelMdlBP*>(m_pCurrentDoc->GetModel())->HasDistributionAttributes())
        dynamic_cast<ZDProcessGraphModelMdlBP*>(m_pCurrentDoc->GetModel())->AllocateDistributionAttributes();

    ZBDistributionAttributeManager* pDistribManager = dynamic_cast<ZDProcessGraphModelMdlBP*>(m_pCurrentDoc->GetModel())->GetDistributionAttributes();
    if (!pDistribManager)
        return;

    if (!m_pCurrentDoc->HasDynamicPropertiesManager())
        m_pCurrentDoc->AllocatePropertiesManager();

    ZBDynamicPropertiesManager* pDynPropMgr = m_pCurrentDoc->GetDynamicPropertiesManager();
    if (!pDynPropMgr)
        return;

    CString UnitGUID = GetAndCheckUnitGUID();
    //    if (UnitGUID.IsEmpty())
    //        return;

    ZBPropertySet Set;
    ZUDynamicAttributesManipulator::ExtractUniqueAttributes(m_pCurrentDoc->GetModel(), Set);


    ZVDistributionAttributesDefinitionDlg dlg(pDistribManager, pDynPropMgr, &Set, m_pCurrentDoc->GetMainUserGroup(), UnitGUID);
    if (dlg.DoModal() == IDOK)
    {
        // Allocate a new attribute
        ZBDistributionAttribute* pDistributionAttrib = dlg.GetDistributionAttribute();
        if (pDistributionAttrib)
        {
            ZBDistributionAttribute* pDistr = pDistributionAttrib->Dup();
            ASSERT(pDistr);

            // Assigns value members
            pDistr->SetCategoryID(dlg.GetCategoryID());
            pDistr->SetItemID(dlg.GetItemID());
            pDistr->SetSymbolRef((m_pSymbol) ? dynamic_cast<ZIBasicSymbol*>(m_pSymbol)->GetSymbolReferenceNumber() : -1);

            pDistr->SetUserGroupGUID(dlg.GetGroupGUID());

            // Then add the new attribute
            pDistribManager->AddDistributionAttribute(pDistr);

            // Document is modified
            m_pCurrentDoc->SetModifiedFlag();
            // Refresh the list to reflect the change
            Refresh();
        }
    }

    // Remove all properties
    ZBPropertyIterator i(&Set);
    ZBProperty* pProp;
    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
        delete pProp;
    Set.RemoveAll();
}

void ZVDistributionAttributes::OnDeleteDistributionAttrib()
{
    if (!m_pCurrentDoc)
        return;

    if (!m_pCurrentDoc->GetModel() ||
        !ISA(m_pCurrentDoc->GetModel(), ZDProcessGraphModelMdlBP))
        return;

    ZBDistributionAttributeManager* pDistribManager = dynamic_cast<ZDProcessGraphModelMdlBP*>(m_pCurrentDoc->GetModel())->GetDistributionAttributes();
    if (!pDistribManager)
        return;


    ZBDistributionAttribute* pDistributionAttrib = GetSelectedDistributionAttribute();
    if (!pDistributionAttrib)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_SELECTDISTRIBATTR_MSG, MB_OK);
        return;
    }

    PSS_MsgBox mBox;
    if (mBox.Show(IDS_DELETEDISTRIBUTIONATTR_CONF, MB_YESNO) == IDYES)
    {
        pDistribManager->DeleteDistributionAttribute(pDistributionAttrib);

        // Document is modified
        m_pCurrentDoc->SetModifiedFlag();
        // Refresh the list to reflect the change
        Refresh();
    }
}


void ZVDistributionAttributes::OnModifyDistributionAttrib()
{
    if (!m_pCurrentDoc)
        return;

    if (!m_pCurrentDoc->GetModel() ||
        !ISA(m_pCurrentDoc->GetModel(), ZDProcessGraphModelMdlBP))
        return;

    ZBDistributionAttributeManager* pDistribManager = dynamic_cast<ZDProcessGraphModelMdlBP*>(m_pCurrentDoc->GetModel())->GetDistributionAttributes();
    if (!pDistribManager)
        return;

    ZBDistributionAttribute* pDistributionAttrib = GetSelectedDistributionAttribute();
    if (!pDistributionAttrib)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_SELECTDISTRIBATTR_MSG, MB_OK);
        return;
    }

    CString UnitGUID = GetAndCheckUnitGUID();
    //    if (UnitGUID.IsEmpty())
    //        return;

    ZBPropertySet Set;
    ZUDynamicAttributesManipulator::ExtractUniqueAttributes(m_pCurrentDoc->GetModel(), Set);

    ZVDistributionAttributesDefinitionDlg dlg(pDistribManager, m_pCurrentDoc->GetDynamicPropertiesManager(), &Set, m_pCurrentDoc->GetMainUserGroup(), UnitGUID, pDistributionAttrib);
    if (dlg.DoModal() == IDOK)
    {
        // Document is modified
        m_pCurrentDoc->SetModifiedFlag();
        // Refresh the list to reflect the change
        Refresh();
    }
}
