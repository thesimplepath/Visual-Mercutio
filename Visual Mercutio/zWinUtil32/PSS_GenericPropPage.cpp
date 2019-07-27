/****************************************************************************
 * ==> PSS_GenericPropPage -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic property page                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_GenericPropPage.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_GenericPropPage, CPropertyPage)
    //{{AFX_MSG_MAP(PSS_GenericPropPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_GenericPropPage
//---------------------------------------------------------------------------
PSS_GenericPropPage::PSS_GenericPropPage(UINT templateID, CObject* pObj) :
    CPropertyPage(templateID),
    m_pObj(pObj),
    m_Initialized(FALSE)
{}
//---------------------------------------------------------------------------
PSS_GenericPropPage::PSS_GenericPropPage(const PSS_GenericPropPage& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_GenericPropPage::~PSS_GenericPropPage()
{}
//---------------------------------------------------------------------------
const PSS_GenericPropPage& PSS_GenericPropPage::operator = (const PSS_GenericPropPage& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
