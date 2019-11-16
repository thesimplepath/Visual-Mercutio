/****************************************************************************
 * ==> PSS_ActivityToDoEventManager ----------------------------------------*
 ****************************************************************************
 * Description : Provides an activity todo event manager                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityToDoEventManagerH
#define PSS_ActivityToDoEventManagerH

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
* Activity todo event manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityToDoEventManager : public PSS_ActivityEventManager
{
    public:
        PSS_ActivityToDoEventManager();
        virtual ~PSS_ActivityToDoEventManager();

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
        PSS_ActivityToDoEventManager(const PSS_ActivityToDoEventManager& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityToDoEventManager& operator = (const PSS_ActivityToDoEventManager& other);
};

#endif
