/****************************************************************************
 * ==> PSS_BaseTitleMDIPage ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a base title multiple document interface page     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_BaseTitleMDIPage.h"

// std
#include <Limits.h>

// processsoft
#include "ZDDoc.h"
#include "DocData.h"
#include "ZAGlobal.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_BaseTitleMDIPage, SECMDIChildWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_BaseTitleMDIPage, SECMDIChildWnd)
    //{{AFX_MSG_MAP(PSS_BaseTitleMDIPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
PSS_BaseTitleMDIPage::PSS_BaseTitleMDIPage()
{
    m_TemplateDef.LoadString(IDS_TEMPLATEDEF_TITLE);
    m_TypeFile.LoadString(IDS_TEMPLATE_FILETYPE);
}
//---------------------------------------------------------------------------
PSS_BaseTitleMDIPage::~PSS_BaseTitleMDIPage()
{}
//---------------------------------------------------------------------------
void PSS_BaseTitleMDIPage::ActivateFrame(int cmdShow)
{
    // if another window is open, use default
    if (GetMDIFrame()->MDIGetActive())
        SECMDIChildWnd::ActivateFrame(cmdShow);
    else
    // the application require to create maximized window?
    if (ZAGlobal::MaximizeFormOnOpen() && ZAGlobal::IsDuringInitialization())
        // open maximized
        SECMDIChildWnd::ActivateFrame(SW_SHOWMAXIMIZED);
    else
        SECMDIChildWnd::ActivateFrame(cmdShow);
}
//---------------------------------------------------------------------------
void PSS_BaseTitleMDIPage::OnUpdate(ZISubject* pSubject, ZIObserverMsg* pMsg)
{}
//---------------------------------------------------------------------------
void PSS_BaseTitleMDIPage::OnUpdateFrameTitle(BOOL addToTitle)
{
    SECMDIChildWnd::OnUpdateFrameTitle(FALSE);

    if (!addToTitle)
        return;

    ZDDocument* pDocument = dynamic_cast<ZDDocument*>(GetActiveDocument());

    if (!pDocument)
        return;

    ZDDocumentData* pDocData = pDocument->GetActiveDocumentData();

    if (!pDocData)
        return;

    char text[10];

    // clear the text buffer
    text[0] = 0x00;

    if (m_nWindow > 0)
        wsprintf(text, _T(" :%d"), m_nWindow);

    CString title;
    CString newTitle;

    if (pDocument->GetPathName().IsEmpty())
        title = g_FormExtension;
    else
        title = pDocument->GetTitle();

    ZDFolderStamp& docStamp = pDocument->GetDocumentStamp();

    if (pDocument->DocumentIsTemplate())
        newTitle = m_TypeFile                      +
                   title                           +
                   _T(" [")                        +
                   docStamp.GetTitle()             +
                   _T(" : ")                       +
                   pDocData->GetStamp().GetTitle() +
                   _T("]")                         +
                   text;
    else
    if (docStamp.GetFolderName().IsEmpty())
        newTitle = title                           +
                   _T(" [")                        +
                   m_TemplateDef                   +
                   docStamp.GetTitle()             +
                   _T(" : ")                       +
                   pDocData->GetStamp().GetTitle() +
                   _T("]")                         +
                   text;
    else
        newTitle = docStamp.GetFolderName()        +
                   _T(" [")                        +
                   m_TemplateDef                   +
                   docStamp.GetTitle()             +
                   _T(" : ")                       +
                   pDocData->GetStamp().GetTitle() +
                   _T("]")                         +
                   text;

    if (title != newTitle)
        SetWindowText(newTitle);
}
//---------------------------------------------------------------------------
