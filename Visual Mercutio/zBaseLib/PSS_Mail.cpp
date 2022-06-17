/****************************************************************************
 * ==> PSS_Mail ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an email manager                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Mail.h"

#ifndef _WIN32
    // special mode helpers
    HWND PASCAL _AfxGetSafeOwner(CWnd* pParent);
#endif

#ifdef _WIN32
    #define szMAPIDLL "MAPI32.DLL"
#else
    #define szMAPIDLL "MAPI.DLL"
#endif

//---------------------------------------------------------------------------
// Callback functions
//---------------------------------------------------------------------------
typedef ULONG(FAR PASCAL *LPMAPILOGON)(ULONG     ulUIParam,
                                       LPSTR     lpszName,
                                       LPSTR     lpszPassword,
                                       FLAGS     flFlags,
                                       ULONG     ulReserved,
                                       LPLHANDLE lplhSession);
//---------------------------------------------------------------------------
typedef ULONG(FAR PASCAL *LPMAPILOGOFF)(LHANDLE lhSession,
                                        ULONG   ulUIParam,
                                        FLAGS   flFlags,
                                        ULONG   ulReserved);
//---------------------------------------------------------------------------
typedef ULONG(FAR PASCAL *LPMAPISENDMAIL)(LHANDLE       lhSession,
                                          ULONG         ulUIParam,
                                          lpMapiMessage lpMessage,
                                          FLAGS         flFlags,
                                          ULONG         ulReserved);
//---------------------------------------------------------------------------
typedef ULONG(FAR PASCAL *LPMAPISENDDOCUMENTS)(ULONG ulUIParam,
                                               LPSTR lpszDelimChar,
                                               LPSTR lpszFilePaths,
                                               LPSTR lpszFileNames,
                                               ULONG ulReserved);
//---------------------------------------------------------------------------
typedef ULONG(FAR PASCAL *LPMAPIFINDNEXT)(LHANDLE lhSession,
                                          ULONG   ulUIParam,
                                          LPSTR   lpszMessageType,
                                          LPSTR   lpszSeedMessageID,
                                          FLAGS   flFlags,
                                          ULONG   ulReserved,
                                          LPSTR   lpszMessageID);
//---------------------------------------------------------------------------
typedef ULONG(FAR PASCAL *LPMAPIREADMAIL)(LHANDLE            lhSession,
                                          ULONG              ulUIParam,
                                          LPSTR              lpszMessageID,
                                          FLAGS              flFlags,
                                          ULONG              ulReserved,
                                          lpMapiMessage FAR* lppMessageOut);
//---------------------------------------------------------------------------
typedef ULONG(FAR PASCAL *LPMAPISAVEMAIL)(LHANDLE       lhSession,
                                          ULONG         ulUIParam,
                                          lpMapiMessage pMessage,
                                          FLAGS         flFlags,
                                          ULONG         ulReserved,
                                          LPSTR         lpszMessageID);
//---------------------------------------------------------------------------
typedef ULONG(FAR PASCAL *LPMAPIDELETEMAIL)(LHANDLE lhSession,
                                            ULONG   ulUIParam,
                                            LPSTR   lpszMessageID,
                                            FLAGS   flFlags,
                                            ULONG   ulReserved);
//---------------------------------------------------------------------------
typedef ULONG(FAR PASCAL *LPMAPIFREEBUFFER)(LPVOID pv);
//---------------------------------------------------------------------------
typedef ULONG(FAR PASCAL *LPMAPIADDRESS)(LHANDLE              lhSession,
                                         ULONG                ulUIParam,
                                         LPSTR                plszCaption,
                                         ULONG                nEditFields,
                                         LPSTR                lpszLabels,
                                         ULONG                nRecips,
                                         lpMapiRecipDesc      lpRecips,
                                         FLAGS                flFlags,
                                         ULONG                ulReserved,
                                         LPULONG              lpnNewRecips,
                                         lpMapiRecipDesc FAR* lppNewRecips);
//---------------------------------------------------------------------------
typedef ULONG(FAR PASCAL *LPMAPIDETAILS)(LHANDLE         lhSession,
                                         ULONG           ulUIParam,
                                         lpMapiRecipDesc lpRecip,
                                         FLAGS           flFlags,
                                         ULONG           ulReserved);
//---------------------------------------------------------------------------
typedef ULONG(FAR PASCAL *LPMAPIRESOLVENAME)(LHANDLE              lhSession,
                                             ULONG                ulUIParam,
                                             LPSTR                lpszName,
                                             FLAGS                flFlags,
                                             ULONG                ulReserved,
                                             lpMapiRecipDesc FAR* lppRecip);
//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
LPMAPILOGON         g_hMAPILogon         = NULL;
LPMAPILOGOFF        g_hMAPILogoff        = NULL;
LPMAPISENDMAIL      g_hMAPISendMail      = NULL;
LPMAPISENDDOCUMENTS g_hMAPISendDocuments = NULL;
LPMAPIFINDNEXT      g_hMAPIFindNext      = NULL;
LPMAPIREADMAIL      g_hMAPIReadMail      = NULL;
LPMAPISAVEMAIL      g_hMAPISaveMail      = NULL;
LPMAPIDELETEMAIL    g_hMAPIDeleteMail    = NULL;
LPMAPIFREEBUFFER    g_hMAPIFreeBuffer    = NULL;
LPMAPIADDRESS       g_hMAPIAddress       = NULL;
LPMAPIDETAILS       g_hMAPIDetails       = NULL;
LPMAPIRESOLVENAME   g_hMAPIResolveName   = NULL;
//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
HINSTANCE PSS_Mail::m_hInstMail = NULL;
//---------------------------------------------------------------------------
// PSS_Mail
//---------------------------------------------------------------------------
PSS_Mail::PSS_Mail()
{
    // open the mapi32.dll library
    m_hInstMail = ::LoadLibrary(szMAPIDLL);
    PSS_Assert(m_hInstMail);

    // hook mapi32.dll library functions
    g_hMAPILogon         = LPMAPILOGON        (::GetProcAddress(m_hInstMail, "MAPILogon"));
    g_hMAPILogoff        = LPMAPILOGOFF       (::GetProcAddress(m_hInstMail, "MAPILogoff"));
    g_hMAPISendMail      = LPMAPISENDMAIL     (::GetProcAddress(m_hInstMail, "MAPISendMail"));
    g_hMAPISendDocuments = LPMAPISENDDOCUMENTS(::GetProcAddress(m_hInstMail, "MAPISendDocuments"));
    g_hMAPIFindNext      = LPMAPIFINDNEXT     (::GetProcAddress(m_hInstMail, "MAPIFindNext"));
    g_hMAPIReadMail      = LPMAPIREADMAIL     (::GetProcAddress(m_hInstMail, "MAPIReadMail"));
    g_hMAPISaveMail      = LPMAPISAVEMAIL     (::GetProcAddress(m_hInstMail, "MAPISaveMail"));
    g_hMAPIDeleteMail    = LPMAPIDELETEMAIL   (::GetProcAddress(m_hInstMail, "MAPIDeleteMail"));
    g_hMAPIFreeBuffer    = LPMAPIFREEBUFFER   (::GetProcAddress(m_hInstMail, "MAPIFreeBuffer"));
    g_hMAPIAddress       = LPMAPIADDRESS      (::GetProcAddress(m_hInstMail, "MAPIAddress"));
    g_hMAPIDetails       = LPMAPIDETAILS      (::GetProcAddress(m_hInstMail, "MAPIDetails"));
    g_hMAPIResolveName   = LPMAPIRESOLVENAME  (::GetProcAddress(m_hInstMail, "MAPIResolveName"));
}
//---------------------------------------------------------------------------
PSS_Mail::PSS_Mail(const PSS_Mail& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_Mail::~PSS_Mail()
{
    // unhook mapi32.dll library functions
    g_hMAPILogon         = NULL;
    g_hMAPILogoff        = NULL;
    g_hMAPISendMail      = NULL;
    g_hMAPISendDocuments = NULL;
    g_hMAPIFindNext      = NULL;
    g_hMAPIReadMail      = NULL;
    g_hMAPISaveMail      = NULL;
    g_hMAPIDeleteMail    = NULL;
    g_hMAPIFreeBuffer    = NULL;
    g_hMAPIAddress       = NULL;
    g_hMAPIDetails       = NULL;
    g_hMAPIResolveName   = NULL;

    // close the mapi32.dll library
    ::FreeLibrary(m_hInstMail);
    m_hInstMail = NULL;
}
//---------------------------------------------------------------------------
const PSS_Mail& PSS_Mail::operator = (const PSS_Mail& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_Mail::SendMail(const CString&    subject,
                        const CString&    messageHeader,
                        const CString&    messageFooter,
                        PSS_MailUserList* pPersonList)
{
    if (!m_hInstMail)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_LOAD);
        return FALSE;
    }

    if (!g_hMAPISendMail)
    {
        AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
        return FALSE;
    }

    PSS_Assert(g_hMAPISendMail);

    // prepare the message (empty with 1 attachment)
    ::MapiMessage message;
    std::memset(&message, 0, sizeof(message));

    // assign the subject
    message.lpszSubject = (char*)((const char*)subject);

    const CString msgText = messageHeader + messageFooter;
    message.lpszNoteText  = (char*)((const char*)msgText);

    if (pPersonList && pPersonList->GetCount() > 0)
    {
        message.nRecipCount = pPersonList->GetCount();
        message.lpRecips    = pPersonList->GetMapiRecipDesc();
    }

    #ifndef _WIN32
        // allow MAPI to send the mail message
        HWND hWndParent = _AfxGetSafeOwner(NULL);
    #else
        HWND  hWndTop;

        // allow MAPI to send the mail message
        CWnd* pWnd = CWnd::GetSafeOwner(NULL, &hWndTop);

        if (!pWnd)
            pWnd = CWnd::GetDesktopWindow();

        ASSERT_VALID(pWnd);

        HWND hWndParent = pWnd->GetSafeHwnd();
    #endif

    // some extra precautions are required to use MAPISendMail as it tends to enable the parent window
    // in between dialogs (after the login dialog, but before the send note dialog)
    ::SetCapture(hWndParent);
    ::SetFocus(NULL);
    ::SetProp(hWndParent, "StayDisabled", HANDLE(1));

    ULONG error =
            g_hMAPISendMail(NULL,
                            MAKELONG(hWndParent, 0),
                            &message,
                            (pPersonList && pPersonList->GetCount() > 0) ? MAPI_LOGON_UI : MAPI_LOGON_UI | MAPI_DIALOG,
                            0);

    // if a problem occurred with recipient, send the message again by showing the email dialog
    if (error == MAPI_E_UNKNOWN_RECIPIENT || error == MAPI_E_AMBIGUOUS_RECIPIENT)
        error = g_hMAPISendMail(NULL, MAKELONG(hWndParent, 0), &message, MAPI_LOGON_UI | MAPI_DIALOG, 0);

    // after returning from the MAPISendMail call, the window must be re-enabled and focus returned to the frame
    // to undo the workaround done before the MAPI call
    ::ReleaseCapture();
    ::RemoveProp(hWndParent, "StayDisabled");
    ::EnableWindow(hWndParent, TRUE);
    ::SetFocus(NULL);
    ::SetFocus(hWndParent);

    BOOL result = TRUE;

    if (error != SUCCESS_SUCCESS && error != MAPI_USER_ABORT && error != MAPI_E_LOGIN_FAILURE)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
        result = FALSE;
    }

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_Mail::SendMail(PSS_MailMessage& mailMessage)
{
    if (!m_hInstMail)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_LOAD);
        return FALSE;
    }

    if (!g_hMAPISendMail)
    {
        AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
        return FALSE;
    }

    PSS_Assert(g_hMAPISendMail);

    // prepare the message (empty with 1 attachment)
    ::MapiMessage message;
    std::memset(&message, 0, sizeof(message));

    // assign the subject
    message.lpszSubject  = (char*)((const char*)mailMessage.GetSubject());
    message.lpszNoteText = (char*)((const char*)mailMessage.GetText());

    // if file has been defined
    if (mailMessage.GetFileCount() > 0 && mailMessage.GetAttachmentType() != PSS_File::IEAttachmentType::IE_AT_Undefined)
        // if the files must be inserted
        if (mailMessage.GetAttachmentType() == PSS_File::IEAttachmentType::IE_AT_InsertedFile)
        {
            message.nFileCount = mailMessage.GetFileCount();
            message.lpFiles    = mailMessage.GetMapiFileDesc();
        }
        else
        {
            const CString msgText = mailMessage.GetText() + mailMessage.GetHyperLinkText();
            message.lpszNoteText = (char*)((const char*)msgText);
        }

    if (mailMessage.GetMailUserCount() > 0)
    {
        message.nRecipCount = mailMessage.GetMailUserCount();
        message.lpRecips    = mailMessage.GetMapiRecipDesc();
    }

    #ifndef _WIN32
        // allow MAPI to send the mail message
        HWND hWndParent = _AfxGetSafeOwner(NULL);
    #else
        HWND hWndTop;

        // allow MAPI to send the mail message
        CWnd* pWnd = CWnd::GetSafeOwner(NULL, &hWndTop);

        if (!pWnd)
            pWnd = CWnd::GetDesktopWindow();

        ASSERT_VALID(pWnd);

        HWND hWndParent = pWnd->GetSafeHwnd();
    #endif

    // some extra precautions are required to use MAPISendMail as it tends to enable the parent window
    // in between dialogs (after the login dialog, but before the send note dialog)
    ::SetCapture(hWndParent);
    ::SetFocus(NULL);
    ::SetProp(hWndParent, "StayDisabled", HANDLE(1));

    ULONG error =
            g_hMAPISendMail(NULL,
                            MAKELONG(hWndParent, 0),
                            &message,
                            (mailMessage.GetMailUserCount() > 0) ? MAPI_LOGON_UI : MAPI_LOGON_UI | MAPI_DIALOG,
                            0);

    // if a problem occurred with recipient, send the message again by displaying the email dialog
    if (error == MAPI_E_UNKNOWN_RECIPIENT || error == MAPI_E_AMBIGUOUS_RECIPIENT)
        error = g_hMAPISendMail(NULL, MAKELONG(hWndParent, 0), &message, MAPI_LOGON_UI | MAPI_DIALOG, 0);

    // after returning from the MAPISendMail call, the window must be re-enabled and focus returned to the frame
    // to undo the workaround done before the MAPI call
    ::ReleaseCapture();
    ::RemoveProp(hWndParent, "StayDisabled");
    ::EnableWindow(hWndParent, TRUE);
    ::SetFocus(NULL);
    ::SetFocus(hWndParent);

    BOOL result = TRUE;

    if (error != SUCCESS_SUCCESS && error != MAPI_USER_ABORT && error != MAPI_E_LOGIN_FAILURE)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
        result = FALSE;
    }

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_Mail::SendDocument(CDocument&        doc,
                            const CString&    subject,
                            const CString&    messageHeader,
                            const CString&    messageFooter,
                            PSS_MailUserList* pPersonList)
{
    if (!m_hInstMail)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_LOAD);
        return FALSE;
    }

    if (!g_hMAPISendMail)
    {
        AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
        return FALSE;
    }

    PSS_Assert(g_hMAPISendMail);

    doc.BeginWaitCursor();

    TCHAR tempName[_MAX_PATH];
    BOOL  removeTemp = FALSE;

    if (doc.GetPathName().IsEmpty() || doc.IsModified())
    {
        #ifndef _WIN32
            // save to temporary path
            VERIFY(GetTempFileName(GetTempDrive(0), _T("afx"), 0, tempName) != 0);
        #else
            char path[100];
            VERIFY(::GetTempPath(sizeof(path), path) != 0);
            VERIFY(::GetTempFileName(path, _T("afx"), 0, tempName) != 0);
        #endif

        BOOL modified = doc.IsModified();
        BOOL result   = doc.DoSave(tempName, FALSE);
        doc.SetModifiedFlag(modified);

        if (!result)
        {
            doc.EndWaitCursor();
            TRACE0("Warning: file save failed during File.Send Mail.\n");
            return FALSE;
        }

        removeTemp = TRUE;
    }
    else
        // use actual file since it isn't modified
        lstrcpyn(tempName, doc.GetPathName(), sizeof(tempName));

    // build an appropriate title for the attachment
    char title[_MAX_PATH];
    lstrcpyn(title, doc.GetTitle(), sizeof(title));

    if (doc.GetTitle().Find('.') == -1)
    {
        // append the default suffix if there is one
        CString       ext;
        CDocTemplate* pTemplate = doc.GetDocTemplate();

        if (pTemplate && pTemplate->GetDocString(ext, CDocTemplate::filterExt) && !ext.IsEmpty())
        {
            PSS_Assert(ext[0] == '.');

            const int len = lstrlen(title);
            lstrcpyn(title + len, ext, sizeof(title) - len);
        }
    }

    // prepare the file description (for the attachment)
    ::MapiFileDesc fileDesc;
    std::memset(&fileDesc, 0, sizeof(fileDesc));
    fileDesc.nPosition    = ULONG(-1);
    fileDesc.lpszPathName = tempName;
    fileDesc.lpszFileName = title;

    // prepare the message (empty with 1 attachment)
    ::MapiMessage message;
    std::memset(&message, 0, sizeof(message));
    message.nFileCount = 1;
    message.lpFiles    = &fileDesc;

    if (pPersonList && pPersonList->GetCount() > 0)
    {
        message.nRecipCount = pPersonList->GetCount();
        message.lpRecips    = pPersonList->GetMapiRecipDesc();
    }

    // build the message
    const CString textStr = messageHeader + messageFooter;
    message.lpszNoteText = (char*)((const char*)textStr);

    #ifndef _WIN32
        // allow MAPI to send the mail message
        HWND hWndParent = _AfxGetSafeOwner(NULL);
    #else
        HWND hWndTop;

        // allow MAPI to send the mail message
        CWnd* pWnd = CWnd::GetSafeOwner(NULL, &hWndTop);

        if (!pWnd)
            pWnd = CWnd::GetDesktopWindow();

        ASSERT_VALID(pWnd);

        HWND hWndParent = pWnd->GetSafeHwnd();
    #endif

    // some extra precautions are required to use MAPISendMail as it tends to enable the parent window
    // in between dialogs (after the login dialog, but before the send note dialog)
    ::SetCapture(hWndParent);
    ::SetFocus(NULL);
    ::SetProp(hWndParent, "StayDisabled", HANDLE(1));

    ULONG error =
            g_hMAPISendMail(NULL,
                            MAKELONG(hWndParent, 0),
                            &message,
                            (pPersonList && pPersonList->GetCount() > 0) ? MAPI_LOGON_UI : MAPI_LOGON_UI | MAPI_DIALOG,
                            0);

    // if problem with recipient, send the message again by showing the email dialog
    if (error == MAPI_E_UNKNOWN_RECIPIENT || error == MAPI_E_AMBIGUOUS_RECIPIENT)
        error = g_hMAPISendMail(NULL, MAKELONG(hWndParent, 0), &message, MAPI_LOGON_UI | MAPI_DIALOG, 0);

    // after returning from the MAPISendMail call, the window must be re-enabled and focus returned to the frame
    // to undo the workaround done before the MAPI call
    ::ReleaseCapture();
    ::RemoveProp(hWndParent, "StayDisabled");
    ::EnableWindow(hWndParent, TRUE);
    ::SetFocus(NULL);
    ::SetFocus(hWndParent);

    BOOL result = TRUE;

    if (error != SUCCESS_SUCCESS && error != MAPI_USER_ABORT && error != MAPI_E_LOGIN_FAILURE)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
        result = FALSE;
    }

    // remove temporary file, if temporary file was used
    if (removeTemp)
        CFile::Remove(tempName);

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_Mail::SendDocuments(PSS_MailFileDescription& fileList,
                             const CString&           subject,
                             const CString&           messageHeader,
                             const CString&           messageFooter,
                             PSS_MailUserList*        pPersonList)
{
    if (!m_hInstMail)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_LOAD);
        return FALSE;
    }

    if (!g_hMAPISendMail)
    {
        AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
        return FALSE;
    }

    PSS_Assert(g_hMAPISendMail);

    // prepare the message (empty with 1 attachment)
    ::MapiMessage message;
    std::memset(&message, 0, sizeof(message));

    // assign the subject
    message.lpszSubject = (char*)((const char*)subject);

    CString textStr = messageHeader;

    // if the files must be inserted
    if (fileList.GetAttachmentType() == PSS_File::IEAttachmentType::IE_AT_InsertedFile)
    {
        message.nFileCount = fileList.GetCount();
        message.lpFiles    = fileList.GetMapiFileDesc();
    }
    else
    {
        textStr              += fileList.GetHyperLinkText();
        textStr              += messageFooter;
        message.lpszNoteText  = (char*)((const char*)textStr);
    }

    if (pPersonList && pPersonList->GetCount() > 0)
    {
        message.nRecipCount = pPersonList->GetCount();
        message.lpRecips    = pPersonList->GetMapiRecipDesc();
    }

    #ifndef _WIN32
        // allow MAPI to send the mail message
        HWND hWndParent = _AfxGetSafeOwner(NULL);
    #else
        HWND hWndTop;

        // allow MAPI to send the mail message
        CWnd* pWnd = CWnd::GetSafeOwner(NULL, &hWndTop);

        if (pWnd == NULL)
            pWnd = CWnd::GetDesktopWindow();

        ASSERT_VALID(pWnd);

        HWND hWndParent = pWnd->GetSafeHwnd();
    #endif

    // some extra precautions are required to use MAPISendMail as it tends to enable the parent window
    // in between dialogs (after the login dialog, but before the send note dialog)
    ::SetCapture(hWndParent);
    ::SetFocus(NULL);
    ::SetProp(hWndParent, "StayDisabled", HANDLE(1));

    ULONG error =
            g_hMAPISendMail(NULL,
                            MAKELONG(hWndParent, 0),
                            &message,
                            (pPersonList && pPersonList->GetCount() > 0) ? MAPI_LOGON_UI : MAPI_LOGON_UI | MAPI_DIALOG,
                            0);

    // if problem with recipient, send the message again by showing the email dialog
    if (error == MAPI_E_UNKNOWN_RECIPIENT || error == MAPI_E_AMBIGUOUS_RECIPIENT)
        error = g_hMAPISendMail(NULL, MAKELONG(hWndParent, 0), &message, MAPI_LOGON_UI | MAPI_DIALOG, 0);

    // after returning from the MAPISendMail call, the window must be re-enabled and focus returned to the frame
    // to undo the workaround done before the MAPI call
    ::ReleaseCapture();
    ::RemoveProp(hWndParent, "StayDisabled");
    ::EnableWindow(hWndParent, TRUE);
    ::SetFocus(NULL);
    ::SetFocus(hWndParent);

    BOOL result = TRUE;

    if (error != SUCCESS_SUCCESS && error != MAPI_USER_ABORT && error != MAPI_E_LOGIN_FAILURE)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
        result = FALSE;
    }

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_Mail::SendDocuments(CStringArray&     fileList,
                             const CString&    subject,
                             const CString&    messageHeader,
                             const CString&    messageFooter,
                             PSS_MailUserList* pPersonList)
{
    return SendDocuments(PSS_MailFileDescription(fileList), messageHeader, messageFooter, subject, pPersonList);
}
//---------------------------------------------------------------------------
BOOL PSS_Mail::ResolveName(const CString& name, PSS_MailUserList& personList, BOOL showDialog)
{
    if (!g_hMAPIFreeBuffer || !g_hMAPIResolveName)
    {
        ::AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
        return NULL;
    }

    PSS_Assert(g_hMAPIFreeBuffer && g_hMAPIResolveName);

    #ifndef _WIN32
        // allow MAPI to send the mail message
        HWND hWndParent = _AfxGetSafeOwner(NULL);
    #else
        HWND hWndTop;
    
        // allow MAPI to send the mail message
        CWnd* pWnd = CWnd::GetSafeOwner(NULL, &hWndTop);

        if (!pWnd)
            pWnd = CWnd::GetDesktopWindow();

        ASSERT_VALID(pWnd);

        HWND hWndParent = pWnd->GetSafeHwnd();
    #endif

    // some extra precautions are required to use MAPISendMail as it tends to enable the parent window
    // in between dialogs (after the login dialog, but before the send note dialog)
    ::SetCapture(hWndParent);
    ::SetFocus(NULL);
    ::SetProp(hWndParent, "StayDisabled", HANDLE(1));

    ::MapiRecipDesc* recip[2];

    ULONG error =
            g_hMAPIResolveName(NULL,
                               MAKELONG(hWndParent, 0),
                               LPTSTR((const char*)name),
                               showDialog ? MAPI_LOGON_UI | MAPI_DIALOG : MAPI_LOGON_UI,
                               0,
                               &recip[0]);

    // after returning from the MAPISendMail call, the window must be re-enabled and focus returned to the frame
    // to undo the workaround done before the MAPI call
    ::ReleaseCapture();
    ::RemoveProp(hWndParent, "StayDisabled");
    ::EnableWindow(hWndParent, TRUE);
    ::SetFocus(NULL);
    ::SetFocus(hWndParent);

    BOOL result = TRUE;

    if (error != SUCCESS_SUCCESS && error != MAPI_USER_ABORT && error != MAPI_E_LOGIN_FAILURE)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
        result = FALSE;
    }

    if (recip)
    {
        personList.AddPerson(recip[0]);
        g_hMAPIFreeBuffer(recip);
    }

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_Mail::Address(PSS_MailUserList& personList)
{
    if (!g_hMAPIFreeBuffer || !g_hMAPIAddress)
    {
        ::AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
        return NULL;
    }

    PSS_Assert(g_hMAPIFreeBuffer && g_hMAPIAddress);

    #ifndef _WIN32
        // allow MAPI to send the mail message
        HWND hWndParent = _AfxGetSafeOwner(NULL);
    #else
        HWND hWndTop;

        // allow MAPI to send the mail message
        CWnd* pWnd = CWnd::GetSafeOwner(NULL, &hWndTop);

        if (pWnd == NULL)
            pWnd = CWnd::GetDesktopWindow();

        ASSERT_VALID(pWnd);

        HWND hWndParent = pWnd->GetSafeHwnd();
    #endif

    // some extra precautions are required to use MAPISendMail as it tends to enable the parent window
    // in between dialogs (after the login dialog, but before the send note dialog)
    ::SetCapture(hWndParent);
    ::SetFocus(NULL);
    ::SetProp(hWndParent, "StayDisabled", HANDLE(1));

    ULONG            addressCount = 2;
    ::MapiRecipDesc* pNewRecips[2];

    const ULONG error =
            g_hMAPIAddress(NULL,
                           MAKELONG(hWndParent, 0),
                           NULL,
                           1,
                           "",
                           personList.GetCount(),
                           (personList.GetCount() > 0) ? personList.GetMapiRecipDesc() : NULL,
                           MAPI_LOGON_UI | MAPI_DIALOG,
                           0,
                           &addressCount,
                           &pNewRecips[0]);

    // because supports only one address
    addressCount = __max(1, addressCount);

    // after returning from the MAPIAddress call, the window must be re-enabled and focus returned to the frame
    // to undo the workaround done before the MAPI call
    ::ReleaseCapture();
    ::RemoveProp(hWndParent, "StayDisabled");
    ::EnableWindow(hWndParent, TRUE);
    ::SetFocus(NULL);
    ::SetFocus(hWndParent);

    BOOL result = TRUE;

    if (error != SUCCESS_SUCCESS && error != MAPI_USER_ABORT && error != MAPI_E_LOGIN_FAILURE)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
        result = FALSE;
    }

    if (pNewRecips && error != MAPI_USER_ABORT)
    {
        personList.RemoveAllPersons();
        personList.Fill(pNewRecips, addressCount);
        g_hMAPIFreeBuffer(pNewRecips);
    }

    return result;
}
//---------------------------------------------------------------------------
