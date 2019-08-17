/****************************************************************************
 * ==> PSS_PosSizePropertyPage ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a position and size property page                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PosSizePropertyPage.h"

// processsoft
#include "zBaseLib\PaintOp.h"
#include "zBaseLib\ZAObject.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PosSizePropertyPage, PSS_GenericPropPage)
    //{{AFX_MSG_MAP(PSS_PosSizePropertyPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PosSizePropertyPage
//---------------------------------------------------------------------------
PSS_PosSizePropertyPage::PSS_PosSizePropertyPage(PlanFinObject* pObj) :
    PSS_GenericPropPage(PSS_PosSizePropertyPage::IDD, pObj),
    m_PositionX(0.0),
    m_PositionY(0.0),
    m_Width(0.0),
    m_Height(0.0)
{
    ASSERT(pObj);

    const CSize pos = ZBPaintOperations::ConvertLogicalUnitsMillimeters(CSize(pObj->GetClientRect().left, 
                                                                              pObj->GetClientRect().bottom));
    m_PositionX = double(pos.cx) / 100.0;
    m_PositionY = double(pos.cy) / 100.0;

    const CSize size = ZBPaintOperations::ConvertLogicalUnitsMillimeters(CSize(pObj->GetClientRect().Width(),
                                                                               pObj->GetClientRect().Height()));
    m_Width  = double(size.cx) / 100.0;
    m_Height = double(size.cy) / 100.0;
}
//---------------------------------------------------------------------------
void PSS_PosSizePropertyPage::SaveValuesToObject()
{
    UpdateData(TRUE);

    const CSize pos = ZBPaintOperations::ConvertMillimetersLogicalUnits(CSize(int(m_PositionX * 100.0), int(m_PositionY * 100.0)));
    ((PlanFinObject&)GetObject()).GetClientRect().left   = pos.cx;
    ((PlanFinObject&)GetObject()).GetClientRect().bottom = pos.cy;

    const CSize size = ZBPaintOperations::ConvertMillimetersLogicalUnits(CSize(int(m_Width * 100.0), int(m_Height * 100.0)));
    ((PlanFinObject&)GetObject()).GetClientRect().right = pos.cx + size.cx;
    ((PlanFinObject&)GetObject()).GetClientRect().top   = pos.cy - size.cy;
    ((PlanFinObject&)GetObject()).SizePositionHasChanged();
}
//---------------------------------------------------------------------------
void PSS_PosSizePropertyPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_PosSizePropertyPage)
    DDX_Text(pDX, IDC_POSITION_Y, m_PositionY);
    DDX_Text(pDX, IDC_SIZE_X,     m_Width);
    DDX_Text(pDX, IDC_SIZE_Y,     m_Height);
    DDX_Text(pDX, IDC_POSITION_X, m_PositionX);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_PosSizePropertyPage::OnInitDialog()
{
    // set initialisation flag
    SetInitialized();
      
    CDialog::OnInitDialog();

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------