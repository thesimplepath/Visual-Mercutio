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


#include "ZBEvent.h"


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
      ZBEventManager ();
      ~ZBEventManager();
      BOOL                Initialize( const CString Directory );

      CString            GetRootDirectory() const { return m_RootDirectory; };

      BOOL                AddEvent( ZBEvent* pEvent );
      BOOL                RemoveEvent( ZBEvent* pEvent );
      BOOL                RemoveEventAt( int Index );
      BOOL                RemoveAllEvents();
      ZBEvent*            GetEventAt( int Index );
      int                GetEventCount();
      BOOL                LoadFromDirectory( BOOL ClearAllFirst, BOOL IncludeSubDirectory );
      BOOL                LoadFromDirectory( const CString Directory, BOOL ClearAllFirst, BOOL IncludeSubDirectory );

      virtual ZBEvent*    LoadEventFromFile( const CString Filename );

  protected:

  private:
      ZBEventManager(const ZBEventManager &right);
      const ZBEventManager & operator=(const ZBEventManager &right);

      void                LoadFromSubDirectory( const CString Directory );

  private: //## implementation
    CObArray        m_Events;
    BOOL            m_IncludeSubDirectory;
    CString            m_RootDirectory;
};



//#undef  AFX_DATA
//#define AFX_DATA



inline ZBEvent*    ZBEventManager::GetEventAt( int Index )
{
    if (Index < m_Events.GetSize())
        return (ZBEvent*)m_Events[Index];
    return NULL;
}
inline int    ZBEventManager::GetEventCount()
{
    return m_Events.GetSize();
}


inline ZBEvent*    ZBEventManager::LoadEventFromFile( const CString Filename )
{
    return NULL;
}

#endif
