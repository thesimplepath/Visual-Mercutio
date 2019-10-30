/****************************************************************************
 * ==> PSS_BasicScrollView -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic scroll view                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_BasicScrollView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_BasicScrollView, PSS_SpanView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_BasicScrollView, PSS_SpanView)
    //{{AFX_MSG_MAP(PSS_BasicScrollView)
    ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomIn)
    ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomOut)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_BasicScrollView
//---------------------------------------------------------------------------
PSS_BasicScrollView::PSS_BasicScrollView() :
    PSS_SpanView()
{}
//---------------------------------------------------------------------------
PSS_BasicScrollView::~PSS_BasicScrollView()
{}
//---------------------------------------------------------------------------
PSS_DocumentPageSetup* PSS_BasicScrollView::GetPrinterPageSize()
{
    // set format if still not defined
    m_PageSetup.OnUserDefinePageFormat();
    return &m_PageSetup;
}
//---------------------------------------------------------------------------
void PSS_BasicScrollView::SetPrinterPageSize(const CSize& paperSize, short standardSize, short orientation)
{
    m_PageSetup.SetPaperSize(paperSize);
    m_PageSetup.SetStandardSize(standardSize);
    m_PageSetup.SetOrientation(orientation);
    m_PageSetup.OnUpdatePrinterSettings();
    m_PageSetup.IsSupported(standardSize);
}
//---------------------------------------------------------------------------
void PSS_BasicScrollView::ViewZoomIn()
{}
//---------------------------------------------------------------------------
void PSS_BasicScrollView::ViewZoomOut()
{}
//---------------------------------------------------------------------------
void PSS_BasicScrollView::OnInitialUpdate()
{
    PSS_DocumentPageSetup* m_pPageSetup = GetPrinterPageSize();

    if (m_pPageSetup->IsFormatDefined())
        SetScrollSizes(MM_TEXT, m_pPageSetup->GetPaperSize());

    PSS_SpanView::OnInitialUpdate();
}
//---------------------------------------------------------------------------
void PSS_BasicScrollView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
}
//---------------------------------------------------------------------------
void PSS_BasicScrollView::OnViewZoomIn()
{}
//---------------------------------------------------------------------------
void PSS_BasicScrollView::OnViewZoomOut()
{}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_BasicScrollView::AssertValid() const
    {
        ZVSpanView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_BasicScrollView::Dump(CDumpContext& dc) const
    {
        ZVSpanView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
