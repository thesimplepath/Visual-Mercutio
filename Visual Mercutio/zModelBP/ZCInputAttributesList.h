/////////////////////////////////////////////////////////////////////////////
//@doc ZCInputAttributesList
//@module ZCInputAttributesList.h | Interface of the <c ZCInputAttributesList> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:         05/2002
// <nl>Description:  ZCInputAttributesList list control for input attributes
//
/////////////////////////////////////////////////////////////////////////////

#ifndef ZCInputAttributesList_h
#define ZCInputAttributesList_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\ZISubject.h"
#include "zBaseLib\ZIObserver.h"
#include "zBaseLib\ZIListCtrl.h"


/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBInputAttribute;
class ZBInputAttributeManager;
class ZBDynamicPropertiesManager;
class ZDProcessGraphModelDoc;


#ifdef _ZMODELBPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif



class AFX_EXT_CLASS ZCInputAttributesList : public ZIListCtrl, public ZISubject, public ZIObserver  
{

    DECLARE_DYNAMIC(ZCInputAttributesList)

public:
    ZCInputAttributesList ();
    virtual ~ZCInputAttributesList();

    ZBInputAttribute* GetSelectedInputAttribute();


    int    Initialize (ZBInputAttributeManager* pInputManager, ZBDynamicPropertiesManager* pPropManager, bool ShowAll = false, int SymbolRef = -1);
    void  ShowAll( bool value = true, bool bRefresh = true )
    {
      m_ShowAll = value;
      if (bRefresh)
          Refresh();
    };
    void  SetSymbolRef( int value, bool bRefresh = true )
    {
      m_SymbolRef = value;
      if (bRefresh)
          Refresh();
    };
    int    Refresh ();
    void    Empty();


    // Observer call back
    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCInputAttributesList)
    //}}AFX_VIRTUAL
protected:
    //{{AFX_MSG(ZCInputAttributesList)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    ZCInputAttributesList(const ZCInputAttributesList &right);
    const    ZCInputAttributesList & operator=(const ZCInputAttributesList &right);

    void    BuildColumns();
    void    DocumentActivated( ZDProcessGraphModelDoc* pDoc );

private: //## implementation
    ZBInputAttributeManager*    m_pInputManager;
    ZBDynamicPropertiesManager* m_pPropManager;
    bool                    m_ShowAll;
    int                        m_SymbolRef;
    CODComponent*            m_pComp;
    BOOL                    m_ColumnsBuilt;
    ZDProcessGraphModelDoc*    m_pDoc;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif      // ZCInputAttributesList_h
