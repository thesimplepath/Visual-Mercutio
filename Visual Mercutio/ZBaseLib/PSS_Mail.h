/****************************************************************************
 * ==> PSS_Mail ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an email manager                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MailH
#define PSS_MailH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// windows
#ifndef _WIN32
    #ifndef MapiH
        #define MapiH
        #include <mapi.h>
    #endif
#else
    #include <mapi.h>
#endif

// processsoft
#include "PSS_MailUserList.h"
#include "PSS_MailFileDescription.h"
#include "PSS_MailMessage.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Email manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Mail
{
    public:
        PSS_Mail();
        virtual ~PSS_Mail();

        /**
        * Sends an email
        *@param subject - subject
        *@param messageHeader - message header
        *@param messageFooter - message footer
        *@param pPersonList - person list
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SendMail(const CString&    subject       = "",
                              const CString&    messageHeader = "",
                              const CString&    messageFooter = "",
                              PSS_MailUserList* pPersonList   = NULL);

        /**
        * Sends an email
        *@param mailMessage - mail message to send
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SendMail(PSS_MailMessage& mailMessage);

        /**
        * Sends a document
        *@param doc - document
        *@param subject - subject
        *@param messageHeader - message header
        *@param messageFooter - message footer
        *@param pPersonList - person list
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SendDocument(CDocument&        doc,
                                  const CString&    subject       = "",
                                  const CString&    messageHeader = "",
                                  const CString&    messageFooter = "",
                                  PSS_MailUserList* pPersonList   = NULL);

        /**
        * Sends documents
        *@param fileList - document file list
        *@param subject - subject
        *@param messageHeader - message header
        *@param messageFooter - message footer
        *@param pPersonList - person list
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SendDocuments(PSS_MailFileDescription& fileList,
                                   const CString&           subject       = "",
                                   const CString&           messageHeader = "",
                                   const CString&           messageFooter = "",
                                   PSS_MailUserList*        pPersonList   = NULL);

        /**
        * Sends documents
        *@param fileList - document file list
        *@param subject - subject
        *@param messageHeader - message header
        *@param messageFooter - message footer
        *@param pPersonList - person list
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SendDocuments(CStringArray&     fileList,
                                   const CString&    subject       = "",
                                   const CString&    messageHeader = "",
                                   const CString&    messageFooter = "",
                                   PSS_MailUserList* pPersonList   = NULL);

        /**
        * Resolves the email name
        *@param name - name to resolve
        *@param[out] personList - person list to populate with result
        *@param showDialog - if TRUE, the send dialog will be shown
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ResolveName(const CString& name, PSS_MailUserList& personList, BOOL showDialog = FALSE);

        /**
        * Addresses a person list to the MAPI server
        *@param personList - person list
        *@return TRUE on success, otherwise FALSE
        */
        BOOL Address(PSS_MailUserList& personList);

    private:
        static HINSTANCE m_hInstMail;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Mail(const PSS_Mail& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Mail& operator = (const PSS_Mail& other);
};

#endif
