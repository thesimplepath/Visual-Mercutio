/****************************************************************************
 * ==> PSS_CodeView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a code view                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "ZIViewCd.h"

 // processsoft
#include "PSS_PlanFinObjects.h"
#include "PSS_PLFNAutoNumbered.h"
#include "PSS_PLFNBitmap.h"
#include "PSS_Document.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(ZIViewCode, PSS_View)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(ZIViewCode, PSS_View)
    //{{AFX_MSG_MAP(ZIViewCode)
    ON_WM_RBUTTONDOWN()
    ON_COMMAND(ID_ONLY_NUMERICFIELDS, OnOnlyNumericFields)
    ON_UPDATE_COMMAND_UI(ID_ONLY_NUMERICFIELDS, OnUpdateOnlyNumericFields)
    ON_MESSAGE(ID_DISPLAY_FIELD_TYPE, OnDisplayFieldType)
    ON_MESSAGE(ID_SYNCHRONIZE_VSCROLL, OnSynchronizeVScroll)
    ON_MESSAGE(ID_SYNCHRONIZE_HSCROLL, OnSynchronizeHScroll)
    ON_COMMAND(ID_DISPLAYCALCULATEDCODE, OnDisplayCalculatedCode)
    ON_UPDATE_COMMAND_UI(ID_DISPLAYCALCULATEDCODE, OnUpdateDisplayCalculatedCode)
    ON_COMMAND(ID_DISPLAYALLCODE, OnDisplayallCode)
    ON_UPDATE_COMMAND_UI(ID_DISPLAYALLCODE, OnUpdateDisplayallCode)
    ON_COMMAND(ID_DISPLAYSTATICCODE, OnDisplayStaticCode)
    ON_UPDATE_COMMAND_UI(ID_DISPLAYSTATICCODE, OnUpdateDisplayStaticCode)
    ON_COMMAND(ID_DISPLAYTEXTCODE, OnDisplayTextCode)
    ON_UPDATE_COMMAND_UI(ID_DISPLAYTEXTCODE, OnUpdateDisplayTextCode)
    ON_COMMAND(ID_DISPLAYGRAPHICCODE, OnDisplayGraphicCode)
    ON_UPDATE_COMMAND_UI(ID_DISPLAYGRAPHICCODE, OnUpdateDisplayGraphicCode)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_FILEPRINT_PAGE_FIELDNAME, CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILEPRINTPREVIEW_PAGE_FIELDNAME, CScrollView::OnFilePrintPreview)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_CodeView
//---------------------------------------------------------------------------
ZIViewCode::ZIViewCode() :
    PSS_View(),
    m_iCodeType(E_CT_AllObjects),
    m_iSavePageForPrinting(0)
{
    m_ViewType = PSS_View::IE_VT_FormFieldCode;
}
//---------------------------------------------------------------------------
ZIViewCode::ZIViewCode(const ZIViewCode& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
ZIViewCode::~ZIViewCode()
{}
//---------------------------------------------------------------------------
const ZIViewCode& ZIViewCode::operator = (const ZIViewCode& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------



//## Other Operations (implementation)
void ZIViewCode::OnDraw(CDC* pDC)
{
    //## begin ZIViewCode::OnDraw%862261465.body preserve=yes
    PSS_Document*    pDoc = GetDocument();
    ASSERT(pDoc);
    int                iPage;
    PSS_PlanFinObject  *obj;
    POSITION        Position;
    // Translate to absolute coordinates
    OnPrepareDC(pDC);
    // Retreive the current page
    iPage = pDoc->GetCurrentPage();

    DrawPageRect(pDC);
    // Optimisation first step
    // call directly the list functions
    Position = (pDoc->GetObjectList()).GetHeadPosition();
    while (Position)
    {
        obj = (PSS_PlanFinObject *)(pDoc->GetObjectList()).GetNext(Position);
        // If the page of the next object is greater than
        // the actual page, it is not necessary to continue.
        if (obj->GetObjectPage() > iPage)
            break;
        if (iPage != obj->GetObjectPage())
            continue;
        switch (GetDisplayCode())
        {
            case E_CT_AllObjects:
            {
                // Display object on the right page
                // and if he is visible into the viewport
                obj->ShowObjectName(pDC);
                break;
            }
            case E_CT_Long:
            {
                if (obj->IsKindOf(RUNTIME_CLASS(PSS_PLFNLong)))
                    obj->ShowObjectName(pDC);
                break;
            }
            case E_CT_Calculated:
            {
                if (obj->IsKindOf(RUNTIME_CLASS(PSS_PLFNLong)) && ((PSS_PLFNLong*)obj)->IsCalculatedField())
                    obj->ShowObjectName(pDC);
                break;
            }
            case E_CT_Static:
            {
                if (obj->IsKindOf(RUNTIME_CLASS(PSS_PLFNText)) && ((PSS_PLFNText*)obj)->GetIsStatic())
                    obj->ShowObjectName(pDC);
                break;
            }
            case E_CT_Text:
            {
                if ((obj->IsKindOf(RUNTIME_CLASS(PSS_PLFNText)) && !((PSS_PLFNText*)obj)->GetIsStatic()) || obj->IsKindOf(RUNTIME_CLASS(PSS_PLFNAutoNumbered)))
                    obj->ShowObjectName(pDC);
                break;
            }
            case E_CT_Graphic:
            {
                if (obj->IsKindOf(RUNTIME_CLASS(PSS_PLFNGraphic)) && obj->IsKindOf(RUNTIME_CLASS(PSS_PLFNBitmap)))
                    obj->ShowObjectName(pDC);
                break;
            }
        }
    }
    //## end ZIViewCode::OnDraw%862261465.body
}

void ZIViewCode::OnInitialUpdate()
{
    //## begin ZIViewCode::OnInitialUpdate%862261466.body preserve=yes
    PSS_View::OnInitialUpdate();
    //## end ZIViewCode::OnInitialUpdate%862261466.body
}

void ZIViewCode::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
    //## begin ZIViewCode::OnPrint%901710585.body preserve=yes
      // Assign the current page
    GetDocument()->SetCurrentPage(pInfo->m_nCurPage);
    // Now print the page
    OnDraw(pDC);
    //## end ZIViewCode::OnPrint%901710585.body
}

BOOL ZIViewCode::OnPreparePrinting(CPrintInfo* pInfo)
{
    //## begin ZIViewCode::OnPreparePrinting%901710586.body preserve=yes
        // Do not check for evaluation version
    pInfo->SetMaxPage(GetDocument()->GetPageCount());
    return(DoPreparePrinting(pInfo));
    //## end ZIViewCode::OnPreparePrinting%901710586.body
}

void ZIViewCode::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    //## begin ZIViewCode::OnBeginPrinting%901710587.body preserve=yes
      // Save the current page before printing
    m_iSavePageForPrinting = GetDocument()->GetCurrentPage();
    SetLogicalCoordinates(pDC);
    //## end ZIViewCode::OnBeginPrinting%901710587.body
}

void ZIViewCode::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    //## begin ZIViewCode::OnEndPrinting%901710588.body preserve=yes
        // Do not check for evaluation version
      // Put back the current page
    GetDocument()->SetCurrentPage(m_iSavePageForPrinting);
    //## end ZIViewCode::OnEndPrinting%901710588.body
}

// Additional Declarations
  //## begin ZIViewCode%3365104501F4.declarations preserve=yes
void ZIViewCode::OnRButtonDown(UINT nFlags, CPoint point)
{
    CPoint    pt(point);
    ReleaseCapture();

    // Display the context menu
    CMenu   *pMenu, DummyMenu;
    DummyMenu.LoadMenu(IDR_CONTEXT_VIEWCODE);

    pMenu = DummyMenu.GetSubMenu(0);
    ASSERT(pMenu);
    ClientToScreen(&pt);
    pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, AfxGetMainWnd());
    CScrollView::OnRButtonDown(nFlags, point);
}


void ZIViewCode::OnDisplayallCode()
{
    m_iCodeType = E_CT_AllObjects;
    RedrawWindow();
}

void ZIViewCode::OnUpdateDisplayallCode(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_iCodeType == E_CT_AllObjects);
}


void ZIViewCode::OnDisplayStaticCode()
{
    m_iCodeType = (m_iCodeType == E_CT_Static) ? E_CT_AllObjects : E_CT_Static;
    RedrawWindow();
}

void ZIViewCode::OnUpdateDisplayStaticCode(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_iCodeType == E_CT_Static);
}

void ZIViewCode::OnDisplayTextCode()
{
    m_iCodeType = (m_iCodeType == E_CT_Text) ? E_CT_AllObjects : E_CT_Text;
    RedrawWindow();
}

void ZIViewCode::OnUpdateDisplayTextCode(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_iCodeType == E_CT_Text);
}

void ZIViewCode::OnOnlyNumericFields()
{
    m_iCodeType = (m_iCodeType == E_CT_Long) ? E_CT_AllObjects : E_CT_Long;
    RedrawWindow();
}

void ZIViewCode::OnUpdateOnlyNumericFields(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_iCodeType == E_CT_Long);
}

void ZIViewCode::OnDisplayCalculatedCode()
{
    m_iCodeType = (m_iCodeType == E_CT_Calculated) ? E_CT_AllObjects : E_CT_Calculated;
    RedrawWindow();
}

void ZIViewCode::OnUpdateDisplayCalculatedCode(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_iCodeType == E_CT_Calculated);
}


void ZIViewCode::OnDisplayGraphicCode()
{
    m_iCodeType = (m_iCodeType == E_CT_Graphic) ? E_CT_AllObjects : E_CT_Graphic;
    RedrawWindow();
}

void ZIViewCode::OnUpdateDisplayGraphicCode(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_iCodeType == E_CT_Graphic);
}

afx_msg LONG ZIViewCode::OnDisplayFieldType(UINT message, LONG lParam)
{
    m_iCodeType = EClassType(lParam);
    RedrawWindow();
    return(1);
}

afx_msg LONG ZIViewCode::OnSynchronizeVScroll(UINT message, LONG lParam)
{
    ScrollToPosition(*(POINT*)lParam);
    return(1);
}
afx_msg LONG ZIViewCode::OnSynchronizeHScroll(UINT message, LONG lParam)
{
    ScrollToPosition(*(POINT*)lParam);
    return(1);
}
