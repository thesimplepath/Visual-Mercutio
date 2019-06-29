/****************************************************************************
 * ==> PSS_Application -----------------------------------------------------*
 ****************************************************************************
 * Description : Basic application interface (may be shared between all     *
 *               DLLs). This is where the common functions, like those who  *
 *               refresh the interface, should be declared                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_Application.h"

 //---------------------------------------------------------------------------
 // Static variables
 //---------------------------------------------------------------------------
PSS_Application* PSS_Application::m_pInstance = NULL;
//---------------------------------------------------------------------------
// PSS_Application
//---------------------------------------------------------------------------
PSS_Application* PSS_Application::Instance()
{
    if (!m_pInstance)
    {
        // create new instance
        m_pInstance              = new PSS_Application();
        m_pInstance->m_pMainForm = NULL;
    }

    return m_pInstance;
}
//---------------------------------------------------------------------------
void PSS_Application::Release()
{
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}
//---------------------------------------------------------------------------
void PSS_Application::RegisterMainForm(PSS_MainForm* pForm)
{
    m_pMainForm = pForm;
}
//---------------------------------------------------------------------------
void PSS_Application::UnregisterMainForm()
{
    m_pMainForm = NULL;
}
//---------------------------------------------------------------------------
PSS_MainForm* PSS_Application::GetMainForm()
{
    return m_pMainForm;
}
//---------------------------------------------------------------------------
void PSS_Application::RefreshPropertiesWorkspace()
{
    if (m_pMainForm)
        m_pMainForm->DoRefreshProperties();
}
//---------------------------------------------------------------------------
void PSS_Application::RefreshSelectedSymbolAndProperties()
{
    if (m_pMainForm)
        m_pMainForm->DoRefreshSymbolsAndProperties();
}
//---------------------------------------------------------------------------
