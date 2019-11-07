// Source file: EventManager.h

#ifndef EventManager_h
#define EventManager_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_Event.h"

#ifdef _ZEVENTEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZBEventManager
{
public:
    ZBEventManager();
    ~ZBEventManager();
    BOOL                Initialize(const CString Directory);

    CString            GetRootDirectory() const
    {
        return m_RootDirectory;
    };

    BOOL                AddEvent(PSS_Event* pEvent);
    BOOL                RemoveEvent(PSS_Event* pEvent);
    BOOL                RemoveEventAt(int Index);
    BOOL                RemoveAllEvents();
    PSS_Event*            GetEventAt(int Index);
    int                GetEventCount();
    BOOL                LoadFromDirectory(BOOL ClearAllFirst, BOOL IncludeSubDirectory);
    BOOL                LoadFromDirectory(const CString Directory, BOOL ClearAllFirst, BOOL IncludeSubDirectory);

    virtual PSS_Event*    LoadEventFromFile(const CString Filename);

protected:

private:
    ZBEventManager(const ZBEventManager &right);
    const ZBEventManager & operator=(const ZBEventManager &right);

    void                LoadFromSubDirectory(const CString Directory);

private: //## implementation
    CObArray        m_Events;
    BOOL            m_IncludeSubDirectory;
    CString            m_RootDirectory;
};



//#undef  AFX_DATA
//#define AFX_DATA



inline PSS_Event*    ZBEventManager::GetEventAt(int Index)
{
    if (Index < m_Events.GetSize())
        return (PSS_Event*)m_Events[Index];
    return NULL;
}
inline int    ZBEventManager::GetEventCount()
{
    return m_Events.GetSize();
}


inline PSS_Event*    ZBEventManager::LoadEventFromFile(const CString Filename)
{
    return NULL;
}

#endif
