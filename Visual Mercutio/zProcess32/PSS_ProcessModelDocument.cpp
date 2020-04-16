/****************************************************************************
 * ==> PSS_ProcessModelDocument --------------------------------------------*
 ****************************************************************************
 * Description : Provides a process model document                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessModelDocument.h"

// resources
#include "Resources.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_ProcessModelDocument, PSS_ProcessModelTree)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessModelDocument, PSS_ProcessModelTree)
    //{{AFX_MSG_MAP(PSS_ProcessModelDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProcessModelDocument
//---------------------------------------------------------------------------
PSS_ProcessModelDocument::PSS_ProcessModelDocument() :
    PSS_ProcessModelTree(),
    PSS_Observer()
{
    if (m_SymbolPopupMainMenu.GetSafeHmenu())
        m_SymbolPopupMainMenu.DestroyMenu();

    if (m_SymbolRefPopupMainMenu.GetSafeHmenu())
        m_SymbolRefPopupMainMenu.DestroyMenu();

    // load the component main menus
    m_SymbolPopupMainMenu.LoadMenu(IDR_NAVSYMBOL_POPUP);
    m_SymbolRefPopupMainMenu.LoadMenu(IDR_NAVSYMBOL_REF_POPUP);
}
//---------------------------------------------------------------------------
PSS_ProcessModelDocument::~PSS_ProcessModelDocument()
{}
//---------------------------------------------------------------------------
void PSS_ProcessModelDocument::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}
//---------------------------------------------------------------------------
