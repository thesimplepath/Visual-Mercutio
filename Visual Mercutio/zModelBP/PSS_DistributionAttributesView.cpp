/****************************************************************************
 * ==> PSS_DistributionAttributesView --------------------------------------*
 ****************************************************************************
 * Description : Provides the distribution attributes view                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DistributionAttributesView.h"

// processsoft
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zBaseLib\PSS_DocumentObserverMsg.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_SymbolObserverMsg.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_DynamicAttributesManipulator.h"
#include "PSS_ProcessGraphModelMdlBP.h"
#include "PSS_DistributionAttributesDefinitionDlg.h"
#include "PSS_DistributionAttributes.h"
#include "PSS_ProcedureSymbolBP.h"
#include "PSS_StartSymbolBP.h"
#include "PSS_StopSymbolBP.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const int g_FlatToolbarHeight = 22;
//---------------------------------------------------------------------------
// Custom messages
//---------------------------------------------------------------------------
const int IDC_ADDDISTRIBUTIONATTRIBUTE          = 9000;
const int IDC_DELETEDISTRIBUTIONATTRIBUTE       = 9001;
const int IDC_REFRESHVIEWS                      = 9002;
const int IDC_MODIFYDISTRIBUTIONATTRIBUTE       = 9003;
const int IDC_DISTRIBUTIONATTRIBUTE_FLATTOOLBAR = 12000;
const int IDC_DISTRIBUTIONATTRIBUTE_LISTCTRL    = 12001;
const int UM_REFRESH                            = 22000;
const int UM_ADDDISTRIBUTIONATTRIBUTE           = 22001;
const int UM_DELETEDISTRIBUTIONATTRIBUTE        = 22002;
const int UM_MODIFYDISTRIBUTIONATTRIBUTE        = 22003;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DistributionAttributesView::IFlatToolbar, CStatic)
    //{{AFX_MSG_MAP(PSS_DistributionAttributesView::IFlatToolbar)
    ON_BN_CLICKED(IDC_ADDDISTRIBUTIONATTRIBUTE, OnAddDistributionAttribButton)
    ON_BN_CLICKED(IDC_DELETEDISTRIBUTIONATTRIBUTE, OnDeleteDistributionAttribButton)
    ON_BN_CLICKED(IDC_MODIFYDISTRIBUTIONATTRIBUTE, OnModifyDistributionAttribButton)
    ON_BN_CLICKED(IDC_REFRESHVIEWS, OnRefreshButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DistributionAttributesView::IFlatToolbar
//---------------------------------------------------------------------------
PSS_DistributionAttributesView::IFlatToolbar::IFlatToolbar() :
    CStatic(),
    PSS_Subject()
{
    m_ImageList.Create(IDB_DISTRIBATTRIBUTE_FLATTOOLBAR, 20, 1, RGB(255, 0, 255));
}
//---------------------------------------------------------------------------
PSS_DistributionAttributesView::IFlatToolbar::~IFlatToolbar()
{}
//---------------------------------------------------------------------------
BOOL PSS_DistributionAttributesView::IFlatToolbar::PreTranslateMessage(MSG* pMsg)
{
    // let the tooltip process this message
    m_Tooltip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::IFlatToolbar::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
}
//---------------------------------------------------------------------------
int PSS_DistributionAttributesView::IFlatToolbar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
        return -1;

    int iconIndex = 0;

    CRect rc;
    GetWindowRect(&rc);
    ScreenToClient(&rc);
    rc.top    += 1;
    rc.bottom -= 1;
    rc.left   += 1;
    rc.right   = rc.left + 24;

    if (!m_RefreshButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                rc,
                                this,
                                IDC_REFRESHVIEWS))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_RefreshButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    ++iconIndex;
    rc.OffsetRect(24, 0);

    if (!m_AddDistributionAttribButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                              rc,
                                              this,
                                              IDC_ADDDISTRIBUTIONATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_AddDistributionAttribButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    ++iconIndex;
    rc.OffsetRect(24, 0);

    if (!m_DeleteDistributionAttribButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                                 rc,
                                                 this,
                                                 IDC_DELETEDISTRIBUTIONATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_DeleteDistributionAttribButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    ++iconIndex;
    rc.OffsetRect(24, 0);

    if (!m_ModifyDistributionAttribButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                                 rc,
                                                 this,
                                                 IDC_MODIFYDISTRIBUTIONATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_ModifyDistributionAttribButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);

    // create the tooltip control
    m_Tooltip.Create(this);
    m_Tooltip.Activate(TRUE);

    m_Tooltip.AddTool(GetDlgItem(IDC_REFRESHVIEWS),                IDS_REFRESH);
    m_Tooltip.AddTool(GetDlgItem(IDC_ADDDISTRIBUTIONATTRIBUTE),    IDS_ADDDISTRIBUTIONATTRIBUTE_TTIPS);
    m_Tooltip.AddTool(GetDlgItem(IDC_DELETEDISTRIBUTIONATTRIBUTE), IDS_DELETEDISTRIBUTIONATTRIBUTE_TTIPS);
    m_Tooltip.AddTool(GetDlgItem(IDC_MODIFYDISTRIBUTIONATTRIBUTE), IDS_MODIFYDISTRIBUTIONATTRIBUTE_TTIPS);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::IFlatToolbar::OnRefreshButton()
{
    PSS_ToolbarObserverMsg msg(UM_REFRESH);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::IFlatToolbar::OnAddDistributionAttribButton()
{
    PSS_ToolbarObserverMsg msg(UM_ADDDISTRIBUTIONATTRIBUTE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::IFlatToolbar::OnDeleteDistributionAttribButton()
{
    PSS_ToolbarObserverMsg msg(UM_DELETEDISTRIBUTIONATTRIBUTE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::IFlatToolbar::OnModifyDistributionAttribButton()
{
    PSS_ToolbarObserverMsg msg(UM_MODIFYDISTRIBUTIONATTRIBUTE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
// Dynamic implementation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_DistributionAttributesView, CWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DistributionAttributesView, CWnd)
    //{{AFX_MSG_MAP(PSS_DistributionAttributesView)
    ON_WM_CREATE()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DistributionAttributesView
//---------------------------------------------------------------------------
PSS_DistributionAttributesView::PSS_DistributionAttributesView() :
    CWnd(),
    PSS_Subject(),
    PSS_Observer(),
    m_pCurrentDoc(NULL),
    m_pSymbol(NULL)
{}
//---------------------------------------------------------------------------
PSS_DistributionAttributesView::~PSS_DistributionAttributesView()
{
    m_FlatToolbar.DetachObserver(this);
    m_ListCtrl.DetachObserver(this);
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::Refresh()
{
    CWaitCursor cursor;

    // refresh the controls
    if (::IsWindow(m_ListCtrl.GetSafeHwnd()))
        m_ListCtrl.Refresh();
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::Empty()
{
    CWaitCursor cursor;
    m_ListCtrl.Empty();
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // forward the message to the property control
    m_ListCtrl.OnUpdate(pSubject, pMsg);

    PSS_SymbolObserverMsg* pSymbolObserverMsg = dynamic_cast<PSS_SymbolObserverMsg*>(pMsg);

    if (pSymbolObserverMsg)
    {
        if (pSymbolObserverMsg->GetActionType() == PSS_SymbolObserverMsg::IE_AT_ElementSelected)
            m_pSymbol = pSymbolObserverMsg->GetElement();

        return;
    }

    PSS_ToolbarObserverMsg* pToolbarObserverMsg = dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg);

    if (pToolbarObserverMsg)
    {
        switch (pToolbarObserverMsg->GetMessageID())
        {
            case UM_REFRESH:                     OnRefresh();                  break;
            case UM_ADDDISTRIBUTIONATTRIBUTE:    OnAddDistributionAttrib();    break;
            case UM_DELETEDISTRIBUTIONATTRIBUTE: OnDeleteDistributionAttrib(); break;
            case UM_MODIFYDISTRIBUTIONATTRIBUTE: OnModifyDistributionAttrib(); break;
        }

        return;
    }

    PSS_DocumentObserverMsg* pDocObserverMsg = dynamic_cast<PSS_DocumentObserverMsg*>(pMsg);

    if (pDocObserverMsg)
    {
        PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDocObserverMsg->GetDocument());

        // check the document status
        if (pDoc)
            switch (pDocObserverMsg->GetMessageID())
            {
                case UM_REFRESHDOCUMENT:
                case UM_OPENDOCUMENT:                                break;
                case UM_CLOSEDOCUMENT:         Empty();              break;
                case UM_FRAMEHASBEENACTIVATED: m_pCurrentDoc = pDoc; break;
            }
    }
}
//---------------------------------------------------------------------------
int PSS_DistributionAttributesView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // create the flat toolbar
    dynamic_cast<CStatic&>(m_FlatToolbar).Create(_T(""),
                                                 WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                                                 CRect(0, 0, 100, g_FlatToolbarHeight),
                                                 this,
                                                 IDC_DISTRIBUTIONATTRIBUTE_FLATTOOLBAR);

    // create the list control
    m_ListCtrl.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | LBS_NOINTEGRALHEIGHT | LVS_REPORT | LVS_SHOWSELALWAYS,
                      CRect(0, 0, 0, 0),
                      this,
                      IDC_DISTRIBUTIONATTRIBUTE_LISTCTRL);

    // attach the message observers
    m_FlatToolbar.AttachObserver(this);
    m_ListCtrl.AttachObserver(this);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_FlatToolbar.GetSafeHwnd()) && ::IsWindow(m_ListCtrl.GetSafeHwnd()))
    {
        m_FlatToolbar.MoveWindow(0, 0, cx, g_FlatToolbarHeight);
        m_ListCtrl.MoveWindow(0, g_FlatToolbarHeight, cx, cy - g_FlatToolbarHeight);
    }
}
//---------------------------------------------------------------------------
CString PSS_DistributionAttributesView::GetAndCheckUnitGUID() const
{
    CString unitGUID;

    // check if the symbol selected can accept distribution attributes and has a group defined
    if (m_pSymbol)
    {
        PSS_ProcedureSymbolBP* pProcedure =                     dynamic_cast<PSS_ProcedureSymbolBP*>(m_pSymbol);
        PSS_StartSymbolBP*     pStart     = pProcedure ? NULL : dynamic_cast<PSS_StartSymbolBP*>(m_pSymbol);
        PSS_StopSymbolBP*      pStop      = pStart     ? NULL : dynamic_cast<PSS_StopSymbolBP*>(m_pSymbol);

        if (pProcedure)
            unitGUID = pProcedure->GetUnitGUID();
        else
        if (pStart)
            unitGUID = pStart->GetUnitGUID();
        else
        if (pStop)
            unitGUID = pStop->GetUnitGUID();
        else
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_DISTRIBUTIONATTR_WRONGSYMBOLSEL, MB_OK);
            return _T("");
        }

        if (unitGUID.IsEmpty())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_DISTRIBUTIONATTR_NOUSERGROUPDEF, MB_OK);
            return _T("");
        }
    }

    return unitGUID;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::OnAddDistributionAttrib()
{
    if (!m_pCurrentDoc)
        return;

    PSS_ProcessGraphModelMdlBP* pProcessGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pCurrentDoc->GetModel());

    if (!pProcessGraphModel)
        return;

    if (!pProcessGraphModel->HasDistributionAttributes())
        pProcessGraphModel->AllocateDistributionAttributes();

    PSS_DistributionAttributeManager* pDistribManager = pProcessGraphModel->GetDistributionAttributes();

    if (!pDistribManager)
        return;

    if (!m_pCurrentDoc->HasDynamicPropertiesManager())
        m_pCurrentDoc->AllocatePropertiesManager();

    PSS_DynamicPropertiesManager* pDynPropMgr = m_pCurrentDoc->GetDynamicPropertiesManager();

    if (!pDynPropMgr)
        return;

    const CString unitGUID = GetAndCheckUnitGUID();

    ZBPropertySet propSet;
    PSS_DynamicAttributesManipulator::ExtractUniqueAttributes(m_pCurrentDoc->GetModel(), propSet);

    PSS_DistributionAttributesDefinitionDlg dlg(pDistribManager,
                                                pDynPropMgr,
                                                &propSet,
                                                m_pCurrentDoc->GetMainUserGroup(),
                                                unitGUID);
 
    if (dlg.DoModal() == IDOK)
    {
        // allocate a new attribute
        PSS_DistributionAttribute* pDistributionAttrib = dlg.GetDistributionAttribute();

        if (pDistributionAttrib)
        {
            PSS_DistributionAttribute* pDistr = pDistributionAttrib->Dup();
            ASSERT(pDistr);

            PSS_BasicSymbol* pBasicSym = dynamic_cast<PSS_BasicSymbol*>(m_pSymbol);

            // assign the value members
            pDistr->SetCategoryID(dlg.GetCategoryID());
            pDistr->SetItemID(dlg.GetItemID());
            pDistr->SetSymbolRef(pBasicSym ? pBasicSym->GetSymbolReferenceNumber() : -1);
            pDistr->SetUserGroupGUID(dlg.GetGroupGUID());

            // add the new attribute
            pDistribManager->AddDistributionAttribute(pDistr);

            // document is modified
            m_pCurrentDoc->SetModifiedFlag();

            // refresh the list to reflect the change
            Refresh();
        }
    }

    ZBPropertyIterator it(&propSet);

    // remove all properties
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::OnDeleteDistributionAttrib()
{
    if (!m_pCurrentDoc)
        return;

    PSS_ProcessGraphModelMdlBP* pProcessGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pCurrentDoc->GetModel());

    if (!pProcessGraphModel)
        return;

    PSS_DistributionAttributeManager* pDistribManager = pProcessGraphModel->GetDistributionAttributes();

    if (!pDistribManager)
        return;

    PSS_DistributionAttribute* pDistributionAttrib = GetSelectedDistributionAttribute();

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

        // document is modified
        m_pCurrentDoc->SetModifiedFlag();

        // refresh the list to reflect the change
        Refresh();
    }
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::OnModifyDistributionAttrib()
{
    if (!m_pCurrentDoc)
        return;

    PSS_ProcessGraphModelMdlBP* pProcessGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pCurrentDoc->GetModel());

    if (!pProcessGraphModel)
        return;

    PSS_DistributionAttributeManager* pDistribManager = pProcessGraphModel->GetDistributionAttributes();

    if (!pDistribManager)
        return;

    PSS_DistributionAttribute* pDistributionAttrib = GetSelectedDistributionAttribute();

    if (!pDistributionAttrib)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_SELECTDISTRIBATTR_MSG, MB_OK);
        return;
    }

    const CString unitGUID = GetAndCheckUnitGUID();

    ZBPropertySet propSet;
    PSS_DynamicAttributesManipulator::ExtractUniqueAttributes(m_pCurrentDoc->GetModel(), propSet);

    PSS_DistributionAttributesDefinitionDlg dlg(pDistribManager,
                                                m_pCurrentDoc->GetDynamicPropertiesManager(),
                                                &propSet,
                                                m_pCurrentDoc->GetMainUserGroup(),
                                                unitGUID,
                                                pDistributionAttrib);

    if (dlg.DoModal() == IDOK)
    {
        // document is modified
        m_pCurrentDoc->SetModifiedFlag();

        // refresh the list to reflect the change
        Refresh();
    }
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesView::OnRefresh()
{
    Refresh();
}
//---------------------------------------------------------------------------
