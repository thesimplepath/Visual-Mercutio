/****************************************************************************
 * ==> PSS_SingleInstanceApplication ---------------------------------------*
 ****************************************************************************
 * Description : Provides a single instance application structure           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SingleInstanceApplication.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
PSS_SingleInstanceApplication* g_pOneApp = NULL;
//---------------------------------------------------------------------------
// Global functions
//---------------------------------------------------------------------------
HDDEDATA CALLBACK DdeCallback(WORD     type,
                              WORD     format,
                              HCONV    hConv,
                              HSZ      hszTopic,
                              HSZ      hszItem,
                              HDDEDATA hData,
                              DWORD    data1,
                              DWORD    data2)
{
    if (!g_pOneApp)
        return NULL;

    return g_pOneApp->AppDdeCallback(type,
                                     format,
                                     hConv,
                                     hszTopic,
                                     hszItem,
                                     hData,
                                     data1,
                                     data2);
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SingleInstanceApplication, PSS_MainForm)
    //{{AFX_MSG_MAP(PSS_SingleInstanceApplication)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SingleInstanceApplication
//---------------------------------------------------------------------------
PSS_SingleInstanceApplication::PSS_SingleInstanceApplication() :
    PSS_MainForm(),
    m_hSzCppServer(NULL),
    m_hSzCppTopic(NULL),
    m_hConvCppServer(NULL),
    m_IdInst(0),
    m_DDEResult(0),
    m_IsRun(false)
{
    // used for DDE
    g_pOneApp = this;
}
//---------------------------------------------------------------------------
PSS_SingleInstanceApplication::~PSS_SingleInstanceApplication()
{}
//---------------------------------------------------------------------------
HDDEDATA PSS_SingleInstanceApplication::AppDdeCallback(WORD     type,
                                                       WORD     format,
                                                       HCONV    hConv,
                                                       HSZ      hszTopic,
                                                       HSZ      hszItem,
                                                       HDDEDATA hData,
                                                       DWORD    data1,
                                                       DWORD    data2)
{
    int   count;
    char* buffer;

    HDDEDATA result = HDDEDATA(NULL);

    switch (type)
    {
        case XTYP_CONNECT:
            count  = ::DdeQueryString(m_IdInst, hszTopic, NULL, 0, CP_WINANSI);
            buffer = (char*)std::malloc(count + 1);
            DdeQueryString(m_IdInst, hszTopic, buffer, count + 1, CP_WINANSI);

            if (!std::strcmp(buffer, m_CppTopicName))
            {
                CWnd* pWnd = ::AfxGetMainWnd();

                if (!pWnd)
                    return NULL;

                pWnd->ShowWindow(SW_RESTORE);
                pWnd->BringWindowToTop();
                pWnd->SetForegroundWindow();

                // add any code for the first instance, have found the second one is launch
                result = HDDEDATA(DDE_FACK);
            }

            if (buffer)
                std::free(buffer);

            return result;

        default:
            return result;
    }
}
//---------------------------------------------------------------------------
BOOL PSS_SingleInstanceApplication::InitInstance()
{
    // must be defined, used for DDE single instance
    PSS_Assert(!m_CppServerName.IsEmpty());
    PSS_Assert(!m_CppTopicName.IsEmpty());

    // check DDE
    if (::DdeInitialize(&m_IdInst, (PFNCALLBACK)DdeCallback, 0, 0))
        return false;

    m_hSzCppServer = ::DdeCreateStringHandle(m_IdInst, m_CppServerName, CP_WINANSI);
    m_hSzCppTopic  = ::DdeCreateStringHandle(m_IdInst, m_CppTopicName,  CP_WINANSI);

    // find the first instance
    m_hConvCppServer = ::DdeConnect(m_IdInst, m_hSzCppServer, m_hSzCppTopic, NULL);

    if (m_hConvCppServer)
    {
        m_IsRun = true;
        return false;
    }

    ::DdeNameService(m_IdInst, m_hSzCppServer, 0, DNS_REGISTER);

    return true;
}
//---------------------------------------------------------------------------
int PSS_SingleInstanceApplication::ExitInstance()
{
    // DDE close
    ::DdeFreeStringHandle(m_IdInst, m_hSzCppServer);
    ::DdeFreeStringHandle(m_IdInst, m_hSzCppTopic);

    // unregister the DDE server only for first instance
    if (!m_IsRun)
        if (!::DdeNameService(m_IdInst, m_hSzCppServer, 0, DNS_UNREGISTER))
            ::MessageBox(0, "Error", "in ServiceUnRegister", MB_OK);

    ::DdeUninitialize(m_IdInst);

    return true;
}
//---------------------------------------------------------------------------
