/****************************************************************************
 * ==> PSS_SoapPublisher_MessengerInfo -------------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish the Messenger info                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapPublisher_MessengerInfoH
#define PSS_SoapPublisher_MessengerInfoH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZSOAPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* SOAP protocol to publish the Messenger info
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapPublisher_MessengerInfo
{
    public:
        PSS_SoapPublisher_MessengerInfo();
        virtual ~PSS_SoapPublisher_MessengerInfo();

        /**
        * Gets the server version
        *@return server version
        */
        virtual int GetVersion();

        /**
        * Gets the language
        *@return the language
        */
        virtual std::string GetLanguage();

        /**
        * Authenticate on server (administrator only)
        *@param login - login name
        *@param password - password
        *@return
        */
        virtual int Authenticate(const std::string& login, const std::string& password);
};

#endif
