/****************************************************************************
 * ==> PSS_PublishMessengerModelInformation --------------------------------*
 ****************************************************************************
 * Description : Provides the publish to Messenger model information        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishMessengerModelInformationH
#define PSS_PublishMessengerModelInformationH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// forward class declaration
class PSS_ProcessGraphModelDoc;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Publish to Messenger model information
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PublishMessengerModelInformation
{
    public:
        PSS_ProcessGraphModelDoc* m_pDoc;
        CString                   m_MessengerAddress;
        CString                   m_MessengerAlias;
        CString                   m_BeginDate;
        CString                   m_EndDate;

        /**
        * Constructor
        *@param pDoc - the Messenger model document
        *@param messengerAddress - the Messenger server address
        *@param messengerAlias - the Messenger server alias
        */
        PSS_PublishMessengerModelInformation(PSS_ProcessGraphModelDoc* pDoc,
                                             const CString&            messengerAddress,
                                             const CString&            messengerAlias);

        virtual ~PSS_PublishMessengerModelInformation();
};

#endif
