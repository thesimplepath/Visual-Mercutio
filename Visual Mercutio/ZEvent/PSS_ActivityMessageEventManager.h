/****************************************************************************
 * ==> PSS_ActivityMessageEventManager -------------------------------------*
 ****************************************************************************
 * Description : Provides an activity message event manager                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef ActivityEventMessageManager_h
#define ActivityEventMessageManager_h 1

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_ActivityEventManager.h"

#ifdef _ZEVENTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Activity message event manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityMessageEventManager : public PSS_ActivityEventManager
{
    public:
        PSS_ActivityMessageEventManager();
        virtual ~PSS_ActivityMessageEventManager();

        /**
        * Loads an event from a file
        *@param fileName - file name
        *@return the loaded event, NULL on error
        */
        virtual PSS_Event* LoadEventFromFile(const CString& fileName);

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ActivityMessageEventManager(const PSS_ActivityMessageEventManager& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityMessageEventManager& operator = (const PSS_ActivityMessageEventManager& other);
};

#endif
