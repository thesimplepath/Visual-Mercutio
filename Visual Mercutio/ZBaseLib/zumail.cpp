//## begin module%366D7F590006.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%366D7F590006.cm

//## begin module%366D7F590006.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%366D7F590006.cp

//## Module: ZUMail%366D7F590006; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZUMail.cpp

//## begin module%366D7F590006.additionalIncludes preserve=no
//## end module%366D7F590006.additionalIncludes

//## begin module%366D7F590006.includes preserve=yes
#include <StdAfx.h>
//## end module%366D7F590006.includes

// ZUMail
#include "ZUMail.h"
//## begin module%366D7F590006.declarations preserve=no
//## end module%366D7F590006.declarations

//## begin module%366D7F590006.additionalDeclarations preserve=yes
#ifndef _WIN32
    // Special mode helpers
    HWND PASCAL _AfxGetSafeOwner(CWnd* pParent);
#endif // only if in 16bit

#ifdef _WIN32 
    #define szMAPIDLL       "MAPI32.DLL" 
#endif 
#ifndef _WIN32 
    #define szMAPIDLL       "MAPI.DLL" 
#endif 

LPMAPILOGON lpfnMAPILogon = NULL; 
LPMAPILOGOFF lpfnMAPILogoff = NULL; 
LPMAPISENDMAIL lpfnMAPISendMail = NULL; 
LPMAPISENDDOCUMENTS lpfnMAPISendDocuments = NULL; 
LPMAPIFINDNEXT lpfnMAPIFindNext = NULL; 
LPMAPIREADMAIL lpfnMAPIReadMail = NULL; 
LPMAPISAVEMAIL lpfnMAPISaveMail = NULL; 
LPMAPIDELETEMAIL lpfnMAPIDeleteMail = NULL; 
LPMAPIFREEBUFFER lpfnMAPIFreeBuffer = NULL; 
LPMAPIADDRESS lpfnMAPIAddress = NULL; 
LPMAPIDETAILS lpfnMAPIDetails = NULL; 
LPMAPIRESOLVENAME lpfnMAPIResolveName = NULL; 

//## end module%366D7F590006.additionalDeclarations


// Class ZUMail 

//## begin ZUMail::InstMail%366EAE9F0013.attr preserve=no  public: static HINSTANCE {V} NULL
HINSTANCE ZUMail::m_InstMail = NULL;
//## end ZUMail::InstMail%366EAE9F0013.attr

ZUMail::ZUMail()
  //## begin ZUMail::ZUMail%.hasinit preserve=no
  //## end ZUMail::ZUMail%.hasinit
  //## begin ZUMail::ZUMail%.initialization preserve=yes
  //## end ZUMail::ZUMail%.initialization
{
  //## begin ZUMail::ZUMail%.body preserve=yes
    m_InstMail = ::LoadLibrary(szMAPIDLL);

    lpfnMAPILogon = (LPMAPILOGON) GetProcAddress (m_InstMail, "MAPILogon");
    lpfnMAPILogoff = (LPMAPILOGOFF) GetProcAddress (m_InstMail, "MAPILogoff");
    lpfnMAPISendMail = (LPMAPISENDMAIL) GetProcAddress (m_InstMail, "MAPISendMail");
    lpfnMAPISendDocuments = (LPMAPISENDDOCUMENTS) GetProcAddress (m_InstMail, "MAPISendDocuments");
    lpfnMAPIFindNext = (LPMAPIFINDNEXT) GetProcAddress (m_InstMail, "MAPIFindNext");
    lpfnMAPIReadMail = (LPMAPIREADMAIL) GetProcAddress (m_InstMail, "MAPIReadMail");
    lpfnMAPISaveMail = (LPMAPISAVEMAIL) GetProcAddress (m_InstMail, "MAPISaveMail");
    lpfnMAPIDeleteMail = (LPMAPIDELETEMAIL) GetProcAddress (m_InstMail, "MAPIDeleteMail");
    lpfnMAPIFreeBuffer = (LPMAPIFREEBUFFER) GetProcAddress (m_InstMail, "MAPIFreeBuffer");
    lpfnMAPIAddress = (LPMAPIADDRESS) GetProcAddress (m_InstMail, "MAPIAddress");
    lpfnMAPIDetails = (LPMAPIDETAILS) GetProcAddress (m_InstMail, "MAPIDetails");
    lpfnMAPIResolveName = (LPMAPIRESOLVENAME) GetProcAddress (m_InstMail, "MAPIResolveName");
  //## end ZUMail::ZUMail%.body
}


ZUMail::~ZUMail()
{
  //## begin ZUMail::~ZUMail%.body preserve=yes
    lpfnMAPILogon = NULL; 
    lpfnMAPILogoff = NULL; 
    lpfnMAPISendMail = NULL; 
    lpfnMAPISendDocuments = NULL; 
    lpfnMAPIFindNext = NULL; 
    lpfnMAPIReadMail = NULL; 
    lpfnMAPISaveMail = NULL; 
    lpfnMAPIDeleteMail = NULL; 
    lpfnMAPIFreeBuffer = NULL; 
    lpfnMAPIAddress = NULL; 
    lpfnMAPIDetails = NULL; 
    lpfnMAPIResolveName = NULL; 
    
    ::FreeLibrary( m_InstMail );
    m_InstMail = NULL;
  //## end ZUMail::~ZUMail%.body
}



//## Other Operations (implementation)
BOOL ZUMail::SendMail (CString Subject, CString MessageHeader, CString MessageFooter, ZUMailUserList* PersonList)
{
  //## begin ZUMail::SendMail%913142858.body preserve=yes
    if (m_InstMail == NULL)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_LOAD);
        return FALSE;
    }

    if (lpfnMAPISendMail == NULL)
    {
        AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
        return FALSE;
    }
    ASSERT(lpfnMAPISendMail != NULL);

    // prepare the message (empty with 1 attachment)
    MapiMessage message;
    memset(&message, 0, sizeof(message));
    // Assigns the subject
    message.lpszSubject = (char*)((const char*)Subject);
    CString    Message = MessageHeader;
    Message += MessageFooter;
    message.lpszNoteText = (char*)((const char*)Message);

    if (PersonList && PersonList->GetCount() > 0)
    {
        message.nRecipCount = PersonList->GetCount();
        message.lpRecips = PersonList->GetMapiRecipDescPtr();
    }

#ifndef _WIN32
    // allow MAPI to send the mail message
    HWND hWndParent = _AfxGetSafeOwner(NULL);
#else
    // allow MAPI to send the mail message
    HWND hWndTop;       
    CWnd* pWnd = CWnd::GetSafeOwner(NULL, &hWndTop);
    if (pWnd == NULL)         
       pWnd = CWnd::GetDesktopWindow();
    ASSERT_VALID(pWnd);    
    HWND hWndParent = pWnd->GetSafeHwnd();
#endif

    // some extra precautions are required to use MAPISendMail as it
    // tends to enable the parent window in between dialogs (after
    // the login dialog, but before the send note dialog).
    ::SetCapture(hWndParent);
    ::SetFocus(NULL);
    ::SetProp(hWndParent, "StayDisabled", (HANDLE)1);

    ULONG nError = lpfnMAPISendMail(NULL, MAKELONG(hWndParent, 0), &message,
        (PersonList && PersonList->GetCount() > 0) ? MAPI_LOGON_UI : MAPI_LOGON_UI|MAPI_DIALOG, 0);

    // If problem with recipient, send the message again by displaying the email dialog
    if (nError == MAPI_E_UNKNOWN_RECIPIENT ||
        nError == MAPI_E_AMBIGUOUS_RECIPIENT)
    {
        nError = lpfnMAPISendMail(NULL, MAKELONG(hWndParent, 0), &message, MAPI_LOGON_UI|MAPI_DIALOG, 0);
    }

    // after returning from the MAPISendMail call, the window must
    // be re-enabled and focus returned to the frame to undo the workaround
    // done before the MAPI call.
    ::ReleaseCapture();
    ::RemoveProp(hWndParent, "StayDisabled");
    ::EnableWindow(hWndParent, TRUE);
    ::SetFocus(NULL);
    ::SetFocus(hWndParent);

    BOOL    bRetValue = TRUE;
    
    if (nError != SUCCESS_SUCCESS && 
        nError != MAPI_USER_ABORT && nError != MAPI_E_LOGIN_FAILURE)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
        bRetValue = FALSE;
    }

    return bRetValue;
  //## end ZUMail::SendMail%913142858.body
}

BOOL ZUMail::SendMail (PSS_MailMessage& MailMessage)
{
  //## begin ZUMail::SendMail%927831783.body preserve=yes
    if (m_InstMail == NULL)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_LOAD);
        return FALSE;
    }

    if (lpfnMAPISendMail == NULL)
    {
        AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
        return FALSE;
    }
    ASSERT(lpfnMAPISendMail != NULL);

    // prepare the message (empty with 1 attachment)
    MapiMessage message;
    memset(&message, 0, sizeof(message));
    // Assigns the subject
    message.lpszSubject = (char*)((const char*)MailMessage.GetSubject());
    message.lpszNoteText = (char*)((const char*)MailMessage.GetText());

    CString    Message;
    // If file has been defined
    if (MailMessage.GetFileCount() > 0 && MailMessage.GetAttachementType() != PSS_File::IE_AT_Undefined)
    {
        // If the files must be inserted
        if (MailMessage.GetAttachementType() == PSS_File::IE_AT_InsertedFile)
        {
            message.nFileCount = MailMessage.GetFileCount();
            message.lpFiles = MailMessage.GetMapiFileDesc();
        }
        else
        {
            Message = MailMessage.GetText();
            Message += MailMessage.GetHyperLinkText();
            message.lpszNoteText = (char*)((const char*)Message);
        }
    }
    if (MailMessage.GetMailUserCount() > 0)
    {
        message.nRecipCount = MailMessage.GetMailUserCount();
        message.lpRecips = MailMessage.GetMapiRecipDesc();
    }

#ifndef _WIN32
    // allow MAPI to send the mail message
    HWND hWndParent = _AfxGetSafeOwner(NULL);
#else
    // allow MAPI to send the mail message
    HWND hWndTop;       
    CWnd* pWnd = CWnd::GetSafeOwner(NULL, &hWndTop);
    if (pWnd == NULL)         
       pWnd = CWnd::GetDesktopWindow();
    ASSERT_VALID(pWnd);    
    HWND hWndParent = pWnd->GetSafeHwnd();
#endif

    // some extra precautions are required to use MAPISendMail as it
    // tends to enable the parent window in between dialogs (after
    // the login dialog, but before the send note dialog).
    ::SetCapture(hWndParent);
    ::SetFocus(NULL);
    ::SetProp(hWndParent, "StayDisabled", (HANDLE)1);

    ULONG nError = lpfnMAPISendMail(NULL, MAKELONG(hWndParent, 0), &message,
        (MailMessage.GetMailUserCount() > 0) ? MAPI_LOGON_UI : MAPI_LOGON_UI|MAPI_DIALOG, 0);

    // If problem with recipient, send the message again by displaying the email dialog
    if (nError == MAPI_E_UNKNOWN_RECIPIENT ||
        nError == MAPI_E_AMBIGUOUS_RECIPIENT)
    {
        nError = lpfnMAPISendMail(NULL, MAKELONG(hWndParent, 0), &message, MAPI_LOGON_UI|MAPI_DIALOG, 0);
    }

    // after returning from the MAPISendMail call, the window must
    // be re-enabled and focus returned to the frame to undo the workaround
    // done before the MAPI call.
    ::ReleaseCapture();
    ::RemoveProp(hWndParent, "StayDisabled");
    ::EnableWindow(hWndParent, TRUE);
    ::SetFocus(NULL);
    ::SetFocus(hWndParent);

    BOOL    bRetValue = TRUE;
    
    if (nError != SUCCESS_SUCCESS && 
        nError != MAPI_USER_ABORT && nError != MAPI_E_LOGIN_FAILURE)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
        bRetValue = FALSE;
    }

    return bRetValue;
  //## end ZUMail::SendMail%927831783.body
}

BOOL ZUMail::SendDocument (CDocument& Doc, CString Subject, CString MessageHeader, CString MessageFooter, ZUMailUserList* PersonList)
{
  //## begin ZUMail::SendDocument%913223369.body preserve=yes
    if (m_InstMail == NULL)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_LOAD);
        return FALSE;
    }

    if (lpfnMAPISendMail == NULL)
    {
        AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
        return FALSE;
    }
    ASSERT(lpfnMAPISendMail != NULL);

    Doc.BeginWaitCursor();

    TCHAR szTempName[_MAX_PATH];
    BOOL bRemoveTemp = FALSE;
    if (Doc.GetPathName().IsEmpty() || Doc.IsModified())
    {
#ifndef _WIN32
        // save to temporary path
        VERIFY(GetTempFileName( GetTempDrive(0), _T("afx"), 0, szTempName ) != 0);
#else
        char    szPath[100];
        VERIFY(GetTempPath( sizeof(szPath), szPath ) != 0);
        VERIFY(GetTempFileName( szPath, _T("afx"), 0, szTempName ) != 0);
#endif
        BOOL bModified = Doc.IsModified();
        BOOL bResult = Doc.DoSave(szTempName, FALSE);
        Doc.SetModifiedFlag(bModified);
        if (!bResult)
        {
            Doc.EndWaitCursor();
            TRACE0("Warning: file save failed during File.Send Mail.\n");
            return FALSE;
        }
        bRemoveTemp = TRUE;
    }
    else
    {
        // use actual file since it isn't modified
        lstrcpyn(szTempName, Doc.GetPathName(), sizeof(szTempName));
    }

    // build an appropriate title for the attachment
    char szTitle[_MAX_PATH];
    lstrcpyn(szTitle, Doc.GetTitle(), sizeof(szTitle));
    if (Doc.GetTitle().Find('.') == -1)
    {
        // append the default suffix if there is one
        CString strExt;
        CDocTemplate* pTemplate = Doc.GetDocTemplate();
        if (pTemplate != NULL && 
            pTemplate->GetDocString(strExt, CDocTemplate::filterExt) &&
              !strExt.IsEmpty())
        {
            ASSERT(strExt[0] == '.');
            int nLen = lstrlen(szTitle);
            lstrcpyn(szTitle+nLen, strExt, sizeof(szTitle)-nLen);
        }
    }

    // prepare the file description (for the attachment)
    MapiFileDesc fileDesc;
    memset(&fileDesc, 0, sizeof(fileDesc));
    fileDesc.nPosition = (ULONG)-1;
    fileDesc.lpszPathName = szTempName;
    fileDesc.lpszFileName = szTitle;

    // prepare the message (empty with 1 attachment)
    MapiMessage message;
    memset(&message, 0, sizeof(message));
    message.nFileCount = 1;
    message.lpFiles = &fileDesc;
    if (PersonList && PersonList->GetCount() > 0)
    {
        message.nRecipCount = PersonList->GetCount();
        message.lpRecips = PersonList->GetMapiRecipDescPtr();
    }
    // Build the message
    CString    Message = MessageHeader;
    Message += MessageFooter;
    message.lpszNoteText = (char*)((const char*)Message);
    
#ifndef _WIN32
    // allow MAPI to send the mail message
    HWND hWndParent = _AfxGetSafeOwner(NULL);
#else
    // allow MAPI to send the mail message
    HWND hWndTop;       
    CWnd* pWnd = CWnd::GetSafeOwner(NULL, &hWndTop);
    if (pWnd == NULL)         
       pWnd = CWnd::GetDesktopWindow();
    ASSERT_VALID(pWnd);    
    HWND hWndParent = pWnd->GetSafeHwnd();
#endif

    // some extra precautions are required to use MAPISendMail as it
    // tends to enable the parent window in between dialogs (after
    // the login dialog, but before the send note dialog).
    ::SetCapture(hWndParent);
    ::SetFocus(NULL);
    ::SetProp(hWndParent, "StayDisabled", (HANDLE)1);

    ULONG nError = lpfnMAPISendMail(NULL, MAKELONG(hWndParent, 0), &message,
        (PersonList && PersonList->GetCount() > 0) ? MAPI_LOGON_UI : MAPI_LOGON_UI|MAPI_DIALOG, 0);

    // If problem with recipient, send the message again by displaying the email dialog
    if (nError == MAPI_E_UNKNOWN_RECIPIENT ||
        nError == MAPI_E_AMBIGUOUS_RECIPIENT)
    {
        nError = lpfnMAPISendMail(NULL, MAKELONG(hWndParent, 0), &message, MAPI_LOGON_UI|MAPI_DIALOG, 0);
    }

    // after returning from the MAPISendMail call, the window must
    // be re-enabled and focus returned to the frame to undo the workaround
    // done before the MAPI call.
    ::ReleaseCapture();
    ::RemoveProp(hWndParent, "StayDisabled");
    ::EnableWindow(hWndParent, TRUE);
    ::SetFocus(NULL);
    ::SetFocus(hWndParent);

    BOOL    bRetValue = TRUE;
    
    if (nError != SUCCESS_SUCCESS && 
        nError != MAPI_USER_ABORT && nError != MAPI_E_LOGIN_FAILURE)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
        bRetValue = FALSE;
    }

    // remove temporary file, if temporary file was used
    if (bRemoveTemp)
        CFile::Remove(szTempName);
    
    return bRetValue;
  //## end ZUMail::SendDocument%913223369.body
}

BOOL ZUMail::SendDocuments (ZUMailFileDescription& FileList, CString Subject, CString MessageHeader, CString MessageFooter, ZUMailUserList* PersonList)
{
  //## begin ZUMail::SendDocuments%913223376.body preserve=yes
    if (m_InstMail == NULL)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_LOAD);
        return FALSE;
    }

    if (lpfnMAPISendMail == NULL)
    {
        AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
        return FALSE;
    }
    ASSERT(lpfnMAPISendMail != NULL);

    // prepare the message (empty with 1 attachment)
    MapiMessage message;
    memset(&message, 0, sizeof(message));
    // Assigns the subject
    message.lpszSubject = (char*)((const char*)Subject);
    CString    Message = MessageHeader;
    // If the files must be inserted
    if (FileList.GetAttachementType() == PSS_File::IE_AT_InsertedFile)
    {
        message.nFileCount = FileList.GetCount();
        message.lpFiles = FileList.GetMapiFileDescPtr();
    }
    else
    {
        Message += FileList.GetHyperLinkText();
        Message += MessageFooter;
        message.lpszNoteText = (char*)((const char*)Message);
    }
    if (PersonList && PersonList->GetCount() > 0)
    {
        message.nRecipCount = PersonList->GetCount();
        message.lpRecips = PersonList->GetMapiRecipDescPtr();
    }

#ifndef _WIN32
    // allow MAPI to send the mail message
    HWND hWndParent = _AfxGetSafeOwner(NULL);
#else
    // allow MAPI to send the mail message
    HWND hWndTop;       
    CWnd* pWnd = CWnd::GetSafeOwner(NULL, &hWndTop);
    if (pWnd == NULL)         
       pWnd = CWnd::GetDesktopWindow();
    ASSERT_VALID(pWnd);    
    HWND hWndParent = pWnd->GetSafeHwnd();
#endif

    // some extra precautions are required to use MAPISendMail as it
    // tends to enable the parent window in between dialogs (after
    // the login dialog, but before the send note dialog).
    ::SetCapture(hWndParent);
    ::SetFocus(NULL);
    ::SetProp(hWndParent, "StayDisabled", (HANDLE)1);

    ULONG nError = lpfnMAPISendMail(NULL, MAKELONG(hWndParent, 0), &message,
        (PersonList && PersonList->GetCount() > 0) ? MAPI_LOGON_UI : MAPI_LOGON_UI|MAPI_DIALOG, 0);

    // If problem with recipient, send the message again by displaying the email dialog
    if (nError == MAPI_E_UNKNOWN_RECIPIENT ||
        nError == MAPI_E_AMBIGUOUS_RECIPIENT)
    {
        nError = lpfnMAPISendMail(NULL, MAKELONG(hWndParent, 0), &message, MAPI_LOGON_UI|MAPI_DIALOG, 0);
    }

    // after returning from the MAPISendMail call, the window must
    // be re-enabled and focus returned to the frame to undo the workaround
    // done before the MAPI call.
    ::ReleaseCapture();
    ::RemoveProp(hWndParent, "StayDisabled");
    ::EnableWindow(hWndParent, TRUE);
    ::SetFocus(NULL);
    ::SetFocus(hWndParent);

    BOOL    bRetValue = TRUE;
    
    if (nError != SUCCESS_SUCCESS && 
        nError != MAPI_USER_ABORT && nError != MAPI_E_LOGIN_FAILURE)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
        bRetValue = FALSE;
    }

    return bRetValue;
  //## end ZUMail::SendDocuments%913223376.body
}

BOOL ZUMail::SendDocuments (CStringArray& FileList, CString Subject, CString MessageHeader, CString MessageFooter, ZUMailUserList* PersonList)
{
  //## begin ZUMail::SendDocuments%913223377.body preserve=yes
      return SendDocuments( ZUMailFileDescription( FileList ), MessageHeader, MessageFooter, Subject, PersonList );
  //## end ZUMail::SendDocuments%913223377.body
}

BOOL ZUMail::ResolveName (const CString Name, ZUMailUserList& PersonList, BOOL ShowDialog)
{
  //## begin ZUMail::ResolveName%921575858.body preserve=yes
    if (lpfnMAPIFreeBuffer == NULL || lpfnMAPIResolveName == NULL)
    {
        AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
        return NULL;
    }
    ASSERT(lpfnMAPIFreeBuffer != NULL && lpfnMAPIResolveName != NULL);

#ifndef _WIN32
    // allow MAPI to send the mail message
    HWND hWndParent = _AfxGetSafeOwner(NULL);
#else
    // allow MAPI to send the mail message
    HWND hWndTop;       
    CWnd* pWnd = CWnd::GetSafeOwner(NULL, &hWndTop);
    if (pWnd == NULL)         
       pWnd = CWnd::GetDesktopWindow();
    ASSERT_VALID(pWnd);    
    HWND hWndParent = pWnd->GetSafeHwnd();
#endif

    // some extra precautions are required to use MAPISendMail as it
    // tends to enable the parent window in between dialogs (after
    // the login dialog, but before the send note dialog).
    ::SetCapture(hWndParent);
    ::SetFocus(NULL);
    ::SetProp(hWndParent, "StayDisabled", (HANDLE)1);

    MapiRecipDesc*     lppRecip[2];
    
    ULONG nError = lpfnMAPIResolveName(    NULL, MAKELONG(hWndParent, 0), (LPTSTR)((const char*)Name),
                                        (ShowDialog == TRUE) ? MAPI_LOGON_UI|MAPI_DIALOG : MAPI_LOGON_UI, 0, &lppRecip[0]);

    // after returning from the MAPISendMail call, the window must
    // be re-enabled and focus returned to the frame to undo the workaround
    // done before the MAPI call.
    ::ReleaseCapture();
    ::RemoveProp(hWndParent, "StayDisabled");
    ::EnableWindow(hWndParent, TRUE);
    ::SetFocus(NULL);
    ::SetFocus(hWndParent);

    BOOL    bRetValue = TRUE;
    
    if (nError != SUCCESS_SUCCESS && 
        nError != MAPI_USER_ABORT && nError != MAPI_E_LOGIN_FAILURE)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
        bRetValue = FALSE;
    }

      if (lppRecip)
      {
          PersonList.AddPerson( lppRecip[0] );
          lpfnMAPIFreeBuffer( lppRecip );
      }

    return bRetValue;
  //## end ZUMail::ResolveName%921575858.body
}

BOOL ZUMail::Address (ZUMailUserList& PersonList)
{
  //## begin ZUMail::Address%921594740.body preserve=yes
    if (lpfnMAPIFreeBuffer == NULL || lpfnMAPIAddress == NULL)
    {
        AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
        return NULL;
    }
    ASSERT(lpfnMAPIFreeBuffer != NULL && lpfnMAPIAddress != NULL);

#ifndef _WIN32
    // allow MAPI to send the mail message
    HWND hWndParent = _AfxGetSafeOwner(NULL);
#else
    // allow MAPI to send the mail message
    HWND hWndTop;       
    CWnd* pWnd = CWnd::GetSafeOwner(NULL, &hWndTop);
    if (pWnd == NULL)         
       pWnd = CWnd::GetDesktopWindow();
    ASSERT_VALID(pWnd);    
    HWND hWndParent = pWnd->GetSafeHwnd();
#endif

    // some extra precautions are required to use MAPISendMail as it
    // tends to enable the parent window in between dialogs (after
    // the login dialog, but before the send note dialog).
    ::SetCapture(hWndParent);
    ::SetFocus(NULL);
    ::SetProp(hWndParent, "StayDisabled", (HANDLE)1);

    ULONG                    NbAddress=2;
    MapiRecipDesc*            lppNewRecips[2];
    
    ULONG nError = lpfnMAPIAddress(    NULL, MAKELONG(hWndParent, 0), NULL, 1, "",
                                    PersonList.GetCount(), (PersonList.GetCount() > 0) ? PersonList.GetMapiRecipDescPtr() : NULL,
                                    MAPI_LOGON_UI|MAPI_DIALOG, 0,
                                    &NbAddress, &lppNewRecips[0]);

    // Because supports only one address
    NbAddress = __max( 1, NbAddress );
    // after returning from the MAPIAddress call, the window must
    // be re-enabled and focus returned to the frame to undo the workaround
    // done before the MAPI call.
    ::ReleaseCapture();
    ::RemoveProp(hWndParent, "StayDisabled");
    ::EnableWindow(hWndParent, TRUE);
    ::SetFocus(NULL);
    ::SetFocus(hWndParent);

    BOOL    bRetValue = TRUE;
    
    if (nError != SUCCESS_SUCCESS && 
        nError != MAPI_USER_ABORT && nError != MAPI_E_LOGIN_FAILURE)
    {
        AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
        bRetValue = FALSE;
    }
    
      if (lppNewRecips && nError != MAPI_USER_ABORT)
      {
          PersonList.RemoveAllPersons();
          PersonList.Fill( lppNewRecips, NbAddress );
          lpfnMAPIFreeBuffer( lppNewRecips );
      }

    return bRetValue;
  //## end ZUMail::Address%921594740.body
}

// Additional Declarations
  //## begin ZUMail%366D7F74031C.declarations preserve=yes
  //## end ZUMail%366D7F74031C.declarations

//## begin module%366D7F590006.epilog preserve=yes
//## end module%366D7F590006.epilog
