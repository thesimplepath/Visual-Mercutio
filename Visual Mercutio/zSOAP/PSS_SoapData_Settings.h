/****************************************************************************
 * ==> PSS_SoapData_Settings -----------------------------------------------*
 ****************************************************************************
 * Description : SOAP data containing the settings                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef __PPUBLISHSETTINGS_HDR_
#define __PPUBLISHSETTINGS_HDR_

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
* SOAP data containing the settings
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapData_Settings
{
    public:
        static std::string m_Url;
        static std::string m_ModelService;
        static std::string m_ServerService;
        static std::string m_FileService;

    private:
        PSS_SoapData_Settings()
        {};
};

#endif
