//## begin module%334FC463032D.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC463032D.cm

//## begin module%334FC463032D.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%334FC463032D.cp

//## Module: ViewPage%334FC463032D; Package body
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\ViewPage.cpp

//## begin module%334FC463032D.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%334FC463032D.additionalIncludes

//## begin module%334FC463032D.includes preserve=yes
//## end module%334FC463032D.includes

// ViewPage
#include "ViewPage.h"
//## begin module%334FC463032D.declarations preserve=no
//## end module%334FC463032D.declarations

//## begin module%334FC463032D.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZIViewPage, PSS_GenericPropPage)
    //{{AFX_MSG_MAP(ZIViewPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZIViewPage::ZIViewPage(ZAApplicationOption* pApplicationOptions) :
    PSS_GenericPropPage(ZIViewPage::IDD, pApplicationOptions)
{}

ZIViewPage::~ZIViewPage()
{}

void ZIViewPage::DoDataExchange (CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(ZIViewPage)
    DDX_Check(pDX, IDC_CALCULATEDFIELD,     m_bCalculatedField);
    DDX_Check(pDX, IDC_SHOWHIDDENFIELDS,    m_bShowHiddenField);
    DDX_Check(pDX, IDC_ANIMATION,           m_bAnimationShow);
    DDX_Check(pDX, IDC_SHOWBOUNDSRECT,      m_bShowBoundsRect);
    DDX_Check(pDX, IDC_AUTOCREATEFIELDNAME, m_AutomaticCreateFieldName);
    //}}AFX_DATA_MAP
}

void ZIViewPage::SaveValuesToObject ()
{
  //## begin ZIViewPage::SaveValuesToObject%923121236.body preserve=yes
    if (::IsWindow(GetSafeHwnd()))
        UpdateData( TRUE );

    ((ZAApplicationOption&)GetObject()).SetbAnimationShow( m_bAnimationShow );
    ((ZAApplicationOption&)GetObject()).SetbCalculateFieldShow( m_bCalculatedField );
    ((ZAApplicationOption&)GetObject()).SetbShowHiddenField( m_bShowHiddenField );
    ((ZAApplicationOption&)GetObject()).SetbShowBoundsRect( m_bShowBoundsRect );
    ((ZAApplicationOption&)GetObject()).SetAutomaticFieldNameCreation( m_AutomaticCreateFieldName );
  //## end ZIViewPage::SaveValuesToObject%923121236.body
}

// Additional Declarations
  //## begin ZIViewPage%334FC4610072.declarations preserve=yes
BOOL ZIViewPage::OnInitDialog()
{
    // Set initialisation flag
      SetInitialized();

    m_bCalculatedField = ((ZAApplicationOption&)GetObject()).GetbCalculateFieldShow();
    m_bShowHiddenField = ((ZAApplicationOption&)GetObject()).GetbShowHiddenField();
    m_bAnimationShow = ((ZAApplicationOption&)GetObject()).GetbAnimationShow();
    m_bShowBoundsRect = ((ZAApplicationOption&)GetObject()).GetbShowBoundsRect();
    m_AutomaticCreateFieldName = ((ZAApplicationOption&)GetObject()).GetAutomaticFieldNameCreation();
      
    CDialog::OnInitDialog();

    // return TRUE unless the focus is set to a control
    return TRUE;
}

void ZIViewPage::OnOK()
{
    if (Initialized())
        SaveValuesToObject();
}
