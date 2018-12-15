//## begin module%3705B8640383.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%3705B8640383.cm

//## begin module%3705B8640383.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%3705B8640383.cp

//## Module: PropPage%3705B8640383; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\PropPage.cpp

//## begin module%3705B8640383.additionalIncludes preserve=no
//## end module%3705B8640383.additionalIncludes

//## begin module%3705B8640383.includes preserve=yes
#include <StdAfx.h>
//## end module%3705B8640383.includes

// PropPage
#include "PropPage.h"
//## begin module%3705B8640383.declarations preserve=no
//## end module%3705B8640383.declarations

//## begin module%3705B8640383.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZIGenericPropPage, CPropertyPage)
    //{{AFX_MSG_MAP(ZIGenericPropPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//## end module%3705B8640383.additionalDeclarations


// Class ZIGenericPropPage 



ZIGenericPropPage::ZIGenericPropPage (UINT nIDTemplate, CObject* pObj)
  //## begin ZIGenericPropPage::ZIGenericPropPage%923121221.hasinit preserve=no
  //## end ZIGenericPropPage::ZIGenericPropPage%923121221.hasinit
  //## begin ZIGenericPropPage::ZIGenericPropPage%923121221.initialization preserve=yes
  : CPropertyPage(nIDTemplate), m_pObj(pObj), m_bHasBeenInitialized(FALSE)
  //## end ZIGenericPropPage::ZIGenericPropPage%923121221.initialization
{
  //## begin ZIGenericPropPage::ZIGenericPropPage%923121221.body preserve=yes
  //## end ZIGenericPropPage::ZIGenericPropPage%923121221.body
}


ZIGenericPropPage::~ZIGenericPropPage()
{
  //## begin ZIGenericPropPage::~ZIGenericPropPage%.body preserve=yes
  //## end ZIGenericPropPage::~ZIGenericPropPage%.body
}


// Additional Declarations
  //## begin ZIGenericPropPage%37053093022A.declarations preserve=yes
  //## end ZIGenericPropPage%37053093022A.declarations

//## begin module%3705B8640383.epilog preserve=yes
//## end module%3705B8640383.epilog
