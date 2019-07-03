// posize.cpp : implementation file
//

#include "stdafx.h"
#include "posize.h"
// PaintOp
#include "zBaseLib\PaintOp.h"

#include "zBaseLib\ZAObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIPositionSizePropertyPage dialog


ZIPositionSizePropertyPage::ZIPositionSizePropertyPage(PlanFinObject* pObj)
    : ZIGenericPropPage(ZIPositionSizePropertyPage::IDD, pObj)
{
    //{{AFX_DATA_INIT(ZIPositionSizePropertyPage)
    m_PositionX = 0;
    m_PositionY = 0;
    m_Width = 0;
    m_Height = 0;
    //}}AFX_DATA_INIT
    ASSERT(pObj);
    CSize    Position;
    Position = ZBPaintOperations::ConvertLogicalUnitsMillimeters( CSize(pObj->GetClientRect().left, pObj->GetClientRect().bottom) ); 
    m_PositionX = (double)Position.cx / (double)100;
    m_PositionY = (double)Position.cy / (double)100;
    CSize    Size;
    Size = ZBPaintOperations::ConvertLogicalUnitsMillimeters( CSize(pObj->GetClientRect().Width(), pObj->GetClientRect().Height()) );
    m_Width = (double)Size.cx / (double)100;
    m_Height = (double)Size.cy / (double)100;
}

void ZIPositionSizePropertyPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIPositionSizePropertyPage)
    DDX_Text(pDX, IDC_POSITION_Y, m_PositionY);
    DDX_Text(pDX, IDC_SIZE_X, m_Width);
    DDX_Text(pDX, IDC_SIZE_Y, m_Height);
    DDX_Text(pDX, IDC_POSITION_X, m_PositionX);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZIPositionSizePropertyPage, CPropertyPage)
    //{{AFX_MSG_MAP(ZIPositionSizePropertyPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Virtual function used when the system resquests 
// to save value in the object
void    ZIPositionSizePropertyPage::SaveValuesToObject()
{
    UpdateData( TRUE );
    CSize    Position;
    Position = ZBPaintOperations::ConvertMillimetersLogicalUnits( CSize((int)(m_PositionX*(double)100, m_PositionY*(double)100)) );
    ((PlanFinObject&)GetObject()).GetClientRect().left = Position.cx;
    ((PlanFinObject&)GetObject()).GetClientRect().bottom = Position.cy;
    CSize    Size;
    Size = ZBPaintOperations::ConvertMillimetersLogicalUnits( CSize((int)(m_Width*(double)100, m_Height*(double)100)) );
    ((PlanFinObject&)GetObject()).GetClientRect().right = Position.cx + Size.cx;
    ((PlanFinObject&)GetObject()).GetClientRect().top = Position.cy - Size.cy;
    ((PlanFinObject&)GetObject()).SizePositionHasChanged();
}

/////////////////////////////////////////////////////////////////////////////
// ZIPositionSizePropertyPage message handlers

BOOL ZIPositionSizePropertyPage::OnInitDialog()
{
    // Set initialisation flag
      SetInitialized();
      
    CDialog::OnInitDialog();
    return TRUE;  // return TRUE  unless you set the focus to a control
}
