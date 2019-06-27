/****************************************************************************
 * ==> PSS_SplashContainer -------------------------------------------------*
 ****************************************************************************
 * Description : Splash screen container                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SplashContainer.h"

// std
#include <memory>

// processsoft
#include "PSS_SplashDialog.h"
#include "ZSplashRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_SplashContainer
//---------------------------------------------------------------------------
PSS_SplashContainer::PSS_SplashContainer(LPCTSTR pFileName, const CString& info, CWnd* pParent) :
    m_pParentWnd(pParent),
    m_BitmapFileName(pFileName),
    m_Info(info),
    m_BitmapResID(0)
{}
//---------------------------------------------------------------------------
PSS_SplashContainer::PSS_SplashContainer(UINT resID, const CString& info, CWnd* pParent) :
    m_pParentWnd(pParent),
    m_Info(info),
    m_BitmapResID(resID)
{}
//---------------------------------------------------------------------------
PSS_SplashContainer::~PSS_SplashContainer()
{}
//---------------------------------------------------------------------------
bool PSS_SplashContainer::Show(LPCTSTR pFileName, const CString& info, CWnd* pParent)
{
    m_pParentWnd     = pParent;
    m_BitmapFileName = pFileName;
    m_Info           = info;

    return ShowModal();
}
//---------------------------------------------------------------------------
bool PSS_SplashContainer::Show(UINT resID, const CString& info, CWnd* pParent)
{
    m_pParentWnd  = pParent;
    m_Info        = info;
    m_BitmapResID = resID;

    return ShowModal();
}
//---------------------------------------------------------------------------
bool PSS_SplashContainer::Show(const CString& info)
{
    // check if the constructor has been called correctly
    if (m_BitmapFileName.IsEmpty() && !m_BitmapResID)
        return false;

    if (!info.IsEmpty())
        m_Info = info;

    return ShowModal();
}
//---------------------------------------------------------------------------
bool PSS_SplashContainer::ShowModal() const
{
    std::unique_ptr<PSS_SplashDialog> pSplash;

    if (m_BitmapFileName.IsEmpty())
        pSplash.reset(new PSS_SplashDialog(m_BitmapResID, m_Info, m_pParentWnd));
    else
        pSplash.reset(new PSS_SplashDialog(m_BitmapFileName, m_Info, m_pParentWnd));

    if (!pSplash.get())
        return false;

    pSplash->DoModal();

    return true;
}
//---------------------------------------------------------------------------
