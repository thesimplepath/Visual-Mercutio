/****************************************************************************
 * ==> PSS_SoapPublishUserGroup --------------------------------------------*
 ****************************************************************************
 * Description : Publish the user groups to Messenger through a SOAP        *
 *               protocol, and check the publication validity               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapPublishUserGroupH
#define PSS_SoapPublishUserGroupH

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

// processsoft
#include "zSOAP\PSS_SoapPublisher_Workgroup.h"

// old class name mapping
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif
#ifndef PSS_UserRoleEntity
    #define PSS_UserRoleEntity ZBUserRoleEntity
#endif

// forward class declaration
class PSS_UserGroupEntity;
class PSS_UserRoleEntity;
class PSS_PublishMessengerModelInformation;
class PSS_Log;

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
* Publish the user groups to Messenger through a SOAP protocol
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapPublishUserGroup
{
    public:
        /**
        * Constructor
        *@param pInfo - info to publish
        *@param pLog - logger, can be NULL
        */
        PSS_SoapPublishUserGroup(PSS_PublishMessengerModelInformation* pInfo, PSS_Log* pLog = NULL);

        virtual ~PSS_SoapPublishUserGroup();

        /**
        * Publishes the user groups and check their validity
        *@return true on success, otherwise false
        */
        bool Publish();

    private:
        PSS_PublishMessengerModelInformation* m_pInfo;
        PSS_SoapPublisher_Workgroup           m_PubWorkgroup;
        PSS_Log*                              m_pLog;

        /**
        * Publishes the user groups and check their validity
        *@param pGroup - user groups to publish
        *@return true on success, otherwise false
        */
        void PublishUserGroup(PSS_UserGroupEntity* pGroup);
};

#endif
