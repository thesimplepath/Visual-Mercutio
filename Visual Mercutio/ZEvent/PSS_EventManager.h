/****************************************************************************
 * ==> PSS_EventManager ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an event manager                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EventManagerH
#define PSS_EventManagerH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_Event.h"

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
* Event manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_EventManager
{
    public:
        PSS_EventManager();
        virtual ~PSS_EventManager();

        /**
        * Initializes the class
        *@param directory - directory
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Initialize(const CString& directory);

        /**
        * Gets the root directory
        *@return the root directory
        */
        virtual inline CString GetRootDirectory() const;

        /**
        * Adds an event
        *@param pEvent - event to add
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddEvent(PSS_Event* pEvent);

        /**
        * Removes an event
        *@param pEvent - event to remove
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveEvent(PSS_Event* pEvent);

        /**
        * Removes an event at index
        *@param index - index
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveEventAt(int index);

        /**
        * Removes all the events
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveAllEvents();

        /**
        * Gets an event at index
        *@param index - index
        *@return the event, NULL if not found or on error
        */
        virtual inline PSS_Event* GetEventAt(int index);

        /**
        * Gets the event count
        *@return the event count
        */
        virtual inline int GetEventCount() const;

        /**
        * Loads from a directory
        *@param clearAllFirst - if TRUE, the manager content will be cleared before the load
        *@param includeSubDirectory - if TRUE, the bub-directories will be included in the load
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL LoadFromDirectory(BOOL clearAllFirst, BOOL includeSubDirectory);

        /**
        * Loads from a directory
        *@param directory - directory
        *@param clearAllFirst - if TRUE, the manager content will be cleared before the load
        *@param includeSubDirectory - if TRUE, the bub-directories will be included in the load
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL LoadFromDirectory(const CString& directory, BOOL clearAllFirst, BOOL includeSubDirectory);

        /**
        * Loads an event from a file
        *@param fileName - file name
        *@return the event, NULL on error
        */
        virtual inline PSS_Event* LoadEventFromFile(const CString& filename);

    private:
        CObArray m_Events;
        CString  m_RootDirectory;
        BOOL     m_IncludeSubDirectory;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_EventManager(const PSS_EventManager &right);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_EventManager & operator=(const PSS_EventManager &right);

        /**
        * Loads from a sub-directory
        *@param directory - sub-directory to load from
        */
        virtual void LoadFromSubDirectory(const CString& directory);
};

//---------------------------------------------------------------------------
// PSS_EventManager
//---------------------------------------------------------------------------
CString PSS_EventManager::GetRootDirectory() const
{
    return m_RootDirectory;
}
//---------------------------------------------------------------------------
PSS_Event* PSS_EventManager::GetEventAt(int index)
{
    if (index < m_Events.GetSize())
        return static_cast<PSS_Event*>(m_Events[index]);

    return NULL;
}
//---------------------------------------------------------------------------
int PSS_EventManager::GetEventCount() const
{
    return m_Events.GetSize();
}
//---------------------------------------------------------------------------
PSS_Event* PSS_EventManager::LoadEventFromFile(const CString& fileName)
{
    return NULL;
}
//---------------------------------------------------------------------------

#endif
