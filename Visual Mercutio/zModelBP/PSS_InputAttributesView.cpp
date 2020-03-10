/****************************************************************************
 * ==> PSS_InputAttributesView ---------------------------------------------*
 ****************************************************************************
 * Description : Provides an input attributes view                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InputAttributesView.h"

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
#include "PSS_InputAttributesDefinitionDlg.h"
#include "PSS_InputAttributes.h"

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
// Messages
//---------------------------------------------------------------------------
const int IDC_ADDINPUTATTRIBUTE          = 8000;
const int IDC_DELETEINPUTATTRIBUTE       = 8001;
const int IDC_REFRESHVIEWS               = 8002;
const int IDC_MODIFYINPUTATTRIBUTE       = 8003;
const int IDC_SHOWSYMBOLATTRIBUTE        = 8004;
const int IDC_SHOWALLATTRIBUTE           = 8005;
const int UM_REFRESH                     = 21000;
const int UM_ADDINPUTATTRIBUTE           = 21001;
const int UM_DELETEINPUTATTRIBUTE        = 21002;
const int UM_MODIFYINPUTATTRIBUTE        = 21003;
const int UM_SHOWSYMBOLATTRIBUTE         = 21004;
const int UM_SHOWALLATTRIBUTE            = 21005;
const int IDC_INPUTATTRIBUTE_FLATTOOLBAR = 11000;
const int IDC_INPUTATTRIBUTE_LISTCTRL    = 11001;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InputAttributesView::IFlatToolbar, CStatic)
    //{{AFX_MSG_MAP(PSS_InputAttributesView::IFlatToolbar)
    ON_BN_CLICKED(IDC_ADDINPUTATTRIBUTE, OnAddInputAttributeButton)
    ON_BN_CLICKED(IDC_DELETEINPUTATTRIBUTE, OnDeleteInputAttributeButton)
    ON_BN_CLICKED(IDC_MODIFYINPUTATTRIBUTE, OnModifyInputAttributeButton)
    ON_BN_CLICKED(IDC_SHOWSYMBOLATTRIBUTE, OnShowSymbolAttributeButton)
    ON_BN_CLICKED(IDC_SHOWALLATTRIBUTE, OnShowAllAttributeButton)
    ON_BN_CLICKED(IDC_REFRESHVIEWS, OnRefreshButton)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InputAttributesView::IFlatToolbar
//---------------------------------------------------------------------------
PSS_InputAttributesView::IFlatToolbar::IFlatToolbar()
{
    m_ImageList.Create(IDB_INPUTATTRIBUTE_FLATTOOLBAR, 20, 1, RGB(255, 0, 255));
}
//---------------------------------------------------------------------------
PSS_InputAttributesView::IFlatToolbar::~IFlatToolbar()
{}
//---------------------------------------------------------------------------
BOOL PSS_InputAttributesView::IFlatToolbar::PreTranslateMessage(MSG* pMsg)
{
    // let the tooltip process this message
    m_Tooltip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::IFlatToolbar::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
}
//---------------------------------------------------------------------------
int PSS_InputAttributesView::IFlatToolbar::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

    if (!m_AddInputAttributeButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                          rc,
                                          this,
                                          IDC_ADDINPUTATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_AddInputAttributeButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    ++iconIndex;
    rc.OffsetRect(24, 0);

    if (!m_DeleteInputAttributeButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                             rc,
                                             this,
                                             IDC_DELETEINPUTATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_DeleteInputAttributeButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    ++iconIndex;
    rc.OffsetRect(24, 0);

    if (!m_ModifyInputAttributeButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                             rc,
                                             this,
                                             IDC_MODIFYINPUTATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_ModifyInputAttributeButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    ++iconIndex;
    rc.OffsetRect(24, 0);

    if (!m_ShowSymbolAttributeButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                            rc,
                                            this,
                                            IDC_SHOWSYMBOLATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_ShowSymbolAttributeButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    ++iconIndex;
    rc.OffsetRect(24, 0);

    if (!m_ShowAllAttributeButton.Create(NULL, WS_VISIBLE | BS_ICON | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
                                         rc,
                                         this,
                                         IDC_SHOWALLATTRIBUTE))
    {
        TRACE0("Unable to create button.\n");
        return -1;
    }

    m_ShowAllAttributeButton.SetIcon(m_ImageList.ExtractIcon(iconIndex), CSize(20, 20));
    rc.OffsetRect(24, 0);

    // create the tooltip control
    m_Tooltip.Create(this);
    m_Tooltip.Activate(TRUE);

    m_Tooltip.AddTool(GetDlgItem(IDC_REFRESHVIEWS),         IDS_REFRESH);
    m_Tooltip.AddTool(GetDlgItem(IDC_ADDINPUTATTRIBUTE),    IDS_ADDINPUTATTRIBUTE_TTIPS);
    m_Tooltip.AddTool(GetDlgItem(IDC_DELETEINPUTATTRIBUTE), IDS_DELETEINPUTATTRIBUTE_TTIPS);
    m_Tooltip.AddTool(GetDlgItem(IDC_MODIFYINPUTATTRIBUTE), IDS_MODIFYINPUTATTRIBUTE_TTIPS);
    m_Tooltip.AddTool(GetDlgItem(IDC_SHOWSYMBOLATTRIBUTE),  IDS_SHOWSYMBOLATTRIBUTE_TTIPS);
    m_Tooltip.AddTool(GetDlgItem(IDC_SHOWALLATTRIBUTE),     IDS_SHOWALLATTRIBUTE_TTIPS);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::IFlatToolbar::OnRefreshButton()
{
    PSS_ToolbarObserverMsg msg(UM_REFRESH);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::IFlatToolbar::OnAddInputAttributeButton()
{
    PSS_ToolbarObserverMsg msg(UM_ADDINPUTATTRIBUTE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::IFlatToolbar::OnDeleteInputAttributeButton()
{
    PSS_ToolbarObserverMsg msg(UM_DELETEINPUTATTRIBUTE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::IFlatToolbar::OnModifyInputAttributeButton()
{
    PSS_ToolbarObserverMsg msg(UM_MODIFYINPUTATTRIBUTE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::IFlatToolbar::OnShowSymbolAttributeButton()
{
    PSS_ToolbarObserverMsg msg(UM_SHOWSYMBOLATTRIBUTE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::IFlatToolbar::OnShowAllAttributeButton()
{
    PSS_ToolbarObserverMsg msg(UM_SHOWALLATTRIBUTE);
    NotifyAllObservers(&msg);
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_InputAttributesView, CWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InputAttributesView, CWnd)
    //{{AFX_MSG_MAP(PSS_InputAttributesView)
    ON_WM_CREATE()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InputAttributesView
//---------------------------------------------------------------------------
PSS_InputAttributesView::PSS_InputAttributesView() :
    CWnd(),
    m_pCurrentDoc(NULL),
    m_SymbolRef(-1)
{}
//---------------------------------------------------------------------------
PSS_InputAttributesView::~PSS_InputAttributesView()
{
    m_FlatToolBar.DetachObserver(this);
    m_ListCtrl.DetachObserver(this);
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::Refresh()
{
    CWaitCursor cursor;

    // refresh controls
    if (::IsWindow(m_ListCtrl.GetSafeHwnd()))
        m_ListCtrl.Refresh();
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::Empty()
{
    CWaitCursor cursor;

    if (::IsWindow(m_ListCtrl.GetSafeHwnd()))
        m_ListCtrl.Empty();
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // forward the message to the toolbar control
    m_ListCtrl.OnUpdate(pSubject, pMsg);

    PSS_SymbolObserverMsg* pSymbolObserver = dynamic_cast<PSS_SymbolObserverMsg*>(pMsg);

    if (pSymbolObserver)
    {
        if (pSymbolObserver->GetActionType() == PSS_SymbolObserverMsg::IE_AT_ElementSelected)
        {
            PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pSymbolObserver->GetElement());
            PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pSymbolObserver->GetElement());

            if (pSymbol)
                m_SymbolRef = pSymbol->GetSymbolReferenceNumber();
            else
            if (pLinkSymbol)
                m_SymbolRef = pLinkSymbol->GetSymbolReferenceNumber();
        }

        return;
    }

    PSS_ToolbarObserverMsg* pToolbarObserver = dynamic_cast<PSS_ToolbarObserverMsg*>(pMsg);

    if (pToolbarObserver)
    {
        switch (pToolbarObserver->GetMessageID())
        {
            case UM_REFRESH:              OnRefresh();              break;
            case UM_ADDINPUTATTRIBUTE:    OnAddInputAttribute();    break;
            case UM_DELETEINPUTATTRIBUTE: OnDeleteInputAttribute(); break;
            case UM_MODIFYINPUTATTRIBUTE: OnModifyInputAttribute(); break;
            case UM_SHOWSYMBOLATTRIBUTE:  ShowAll(false);           break;
            case UM_SHOWALLATTRIBUTE:     ShowAll();                break;
        }

        return;
    }

    PSS_DocumentObserverMsg* pDocObserver = dynamic_cast<PSS_DocumentObserverMsg*>(pMsg);

    if (pDocObserver)
    {
        PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDocObserver->GetDocument());

        // check the document status
        if (pDoc)
            switch (pDocObserver->GetMessageID())
            {
                case UM_REFRESHDOCUMENT:
                case UM_OPENDOCUMENT:                                break;
                case UM_CLOSEDOCUMENT:         Empty();              break;
                case UM_FRAMEHASBEENACTIVATED: m_pCurrentDoc = pDoc; break;
            }
    }
}
//---------------------------------------------------------------------------
int PSS_InputAttributesView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // create the flat toolbar
    dynamic_cast<CStatic&>(m_FlatToolBar).Create(_T(""),
                                                 WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
                                                 CRect(0, 0, 100, g_FlatToolbarHeight),
                                                 this,
                                                 IDC_INPUTATTRIBUTE_FLATTOOLBAR);

    // create the list control
    m_ListCtrl.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | LBS_NOINTEGRALHEIGHT | LVS_REPORT,
                      CRect(0, 0, 0, 0),
                      this,
                      IDC_INPUTATTRIBUTE_LISTCTRL);

    // attach the message observers
    m_FlatToolBar.AttachObserver(this);
    m_ListCtrl.AttachObserver(this);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if (::IsWindow(m_FlatToolBar.GetSafeHwnd()) && ::IsWindow(m_ListCtrl.GetSafeHwnd()))
    {
        m_FlatToolBar.MoveWindow(0, 0, cx, g_FlatToolbarHeight);
        m_ListCtrl.MoveWindow(0, g_FlatToolbarHeight, cx, cy - g_FlatToolbarHeight);
    }
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::OnAddInputAttribute()
{
    if (!m_pCurrentDoc)
        return;

    PSS_ProcessGraphModelMdlBP* pProcessGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pCurrentDoc->GetModel());

    if (!pProcessGraphModel)
        return;

    if (!pProcessGraphModel->HasInputAttributes())
        pProcessGraphModel->AllocateInputAttributes();

    PSS_InputAttributeManager* pInputAttrManager = pProcessGraphModel->GetInputAttributes();

    if (!pInputAttrManager)
        return;

    if (!m_pCurrentDoc->HasDynamicPropertiesManager())
        m_pCurrentDoc->AllocatePropertiesManager();

    PSS_DynamicPropertiesManager* pDynPropMgr = m_pCurrentDoc->GetDynamicPropertiesManager();

    if (!pDynPropMgr)
        return;

    ZBPropertySet propSet;
    PSS_DynamicAttributesManipulator::ExtractUniqueAttributes(m_pCurrentDoc->GetModel(), propSet);


    PSS_InputAttributesDefinitionDlg dlg(m_pCurrentDoc->GetDynamicPropertiesManager(), &propSet);

    if (dlg.DoModal() == IDOK)
    {
        // allocate a new attribute
        std::unique_ptr<PSS_InputAttribute> pInputAttribute(new PSS_InputAttribute());
        ASSERT(pInputAttribute.get());

        // assign value members
        pInputAttribute->SetCategoryID(dlg.GetCategoryID());
        pInputAttribute->SetItemID(dlg.GetItemID());

        // if for the selected symbol?
        if (!dlg.GetVisibility())
            pInputAttribute->SetSymbolRef(m_SymbolRef);
        else
            // for the whole model
            pInputAttribute->SetSymbolRef(-1);

        pInputAttribute->SetDefaultValue(dlg.GetDefaultValue());
        pInputAttribute->SetFlag(dlg.GetFlag());

        // add the new attribute
        pInputAttrManager->AddInputAttribute(pInputAttribute.get());
        pInputAttribute.release();

        // document is modified
        m_pCurrentDoc->SetModifiedFlag();

        // refresh the list to reflect the change
        Refresh();
    }

    ZBPropertyIterator it(&propSet);

    // remove all properties
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::OnDeleteInputAttribute()
{
    if (!m_pCurrentDoc)
        return;

    PSS_ProcessGraphModelMdlBP* pProcessGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pCurrentDoc->GetModel());

    if (!pProcessGraphModel)
        return;

    PSS_InputAttributeManager* pInputAttrManager = pProcessGraphModel->GetInputAttributes();

    if (!pInputAttrManager)
        return;

    PSS_InputAttribute* pInputAttribute = GetSelectedInputAttribute();

    if (!pInputAttribute)
        return;

    PSS_MsgBox mBox;

    if (mBox.Show(IDS_DELETEINPUTATTR_CONF, MB_YESNO) == IDYES)
    {
        pInputAttrManager->DeleteInputAttribute(pInputAttribute);

        // document is modified
        m_pCurrentDoc->SetModifiedFlag();

        // refresh the list to reflect the change
        Refresh();
    }
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::OnModifyInputAttribute()
{
    if (!m_pCurrentDoc)
        return;

    PSS_InputAttribute* pInputAttribute = GetSelectedInputAttribute();

    if (!pInputAttribute)
        return;

    PSS_InputAttributesDefinitionDlg dlg(m_pCurrentDoc->GetDynamicPropertiesManager(), NULL, pInputAttribute);

    if (dlg.DoModal() == IDOK)
    {
        pInputAttribute->SetDefaultValue(dlg.GetDefaultValue());

        // if for the selected symbol?
        if (dlg.GetVisibility() == 0)
            pInputAttribute->SetSymbolRef(m_SymbolRef);
        else
            // for the whole model
            pInputAttribute->SetSymbolRef(-1);

        pInputAttribute->SetFlag(dlg.GetFlag());

        // document is modified
        m_pCurrentDoc->SetModifiedFlag();

        // refresh the list to reflect the change
        Refresh();
    }
}
//---------------------------------------------------------------------------
void PSS_InputAttributesView::OnRefresh()
{
    Refresh();
}
//---------------------------------------------------------------------------
