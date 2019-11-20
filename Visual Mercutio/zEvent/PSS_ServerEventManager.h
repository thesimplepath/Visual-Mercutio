/****************************************************************************
 * ==> PSS_ServerEventManager ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a server event manager                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ServerEventManagerH
#define PSS_ServerEventManagerH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_ServerEvent.h"
#include "PSS_EventManager.h"

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
* Server event manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ServerEventManager : public PSS_EventManager
{
    public:
        PSS_ServerEventManager();
        virtual ~PSS_ServerEventManager();

        /**
        * Adds an event
        *@param dateTime - date and time
        *@param fileName - file name
        *@param eventResult - the event result value
        *@return the newly added event, NULL on error
        */
        PSS_ServerEvent* AddEvent(const COleDateTime& dateTime, const CString& fileName, PSS_ServerEvent::IEResult eventResult);

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ServerEventManager(const PSS_ServerEventManager& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ServerEventManager& operator = (const PSS_ServerEventManager& other);
};

#endif
