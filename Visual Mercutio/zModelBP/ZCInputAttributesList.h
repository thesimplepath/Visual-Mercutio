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


#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_ListCtrl.h"

// class name mapping
#ifndef PSS_InputAttribute
    #define PSS_InputAttribute ZBInputAttribute
#endif
#ifndef PSS_InputAttributeManager
    #define PSS_InputAttributeManager ZBInputAttributeManager
#endif
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// forward class declaration
class PSS_InputAttribute;
class PSS_InputAttributeManager;
class ZBDynamicPropertiesManager;
class PSS_ProcessGraphModelDoc;

#ifdef _ZMODELBPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif



class AFX_EXT_CLASS ZCInputAttributesList : public PSS_ListCtrl,
                                            public PSS_Subject,
                                            public PSS_Observer
{
    DECLARE_DYNAMIC(ZCInputAttributesList)

public:
    ZCInputAttributesList();
    virtual ~ZCInputAttributesList();

    PSS_InputAttribute* GetSelectedInputAttribute();


    int    Initialize(PSS_InputAttributeManager* pInputManager, ZBDynamicPropertiesManager* pPropManager, bool ShowAll = false, int SymbolRef = -1);
    void  ShowAll(bool value = true, bool bRefresh = true)
    {
        m_ShowAll = value;
        if (bRefresh)
            Refresh();
    };
    void  SetSymbolRef(int value, bool bRefresh = true)
    {
        m_SymbolRef = value;
        if (bRefresh)
            Refresh();
    };
    int    Refresh();
    void    Empty();


    // Observer call back
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

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
    void    DocumentActivated(PSS_ProcessGraphModelDoc* pDoc);

private: //## implementation
    PSS_InputAttributeManager*    m_pInputManager;
    ZBDynamicPropertiesManager* m_pPropManager;
    bool                    m_ShowAll;
    int                        m_SymbolRef;
    CODComponent*            m_pComp;
    BOOL                    m_ColumnsBuilt;
    PSS_ProcessGraphModelDoc*    m_pDoc;
};

#endif
