/////////////////////////////////////////////////////////////////////////////
//@doc ZCDistributionAttributesList
//@module ZCDistributionAttributesList.h | Interface of the <c ZCDistributionAttributesList> class.
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
// <nl>Description:  ZCDistributionAttributesList list control for input attributes
//
/////////////////////////////////////////////////////////////////////////////

#ifndef ZCDistributionAttributesList_h
#define ZCDistributionAttributesList_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_TreeListCtrl.h"

// class name mapping
#ifndef PSS_DistributionAttribute
    #define PSS_DistributionAttribute ZBDistributionAttribute
#endif
#ifndef PSS_DistributionAttributeManager
    #define PSS_DistributionAttributeManager ZBDistributionAttributeManager
#endif
#ifndef PSS_DistributionRule
    #define PSS_DistributionRule ZBDistributionRule
#endif
#ifndef PSS_DistributionRulesForRole
    #define PSS_DistributionRulesForRole ZBDistributionRulesForRole
#endif
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif

// forward class declaration
class PSS_DistributionAttribute;
class PSS_DistributionAttributeManager;
class PSS_DistributionRule;
class PSS_DistributionRulesForRole;
class ZBDynamicPropertiesManager;
class PSS_ProcessGraphModelDoc;
class PSS_UserGroupEntity;


#ifdef _ZMODELBPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif



class AFX_EXT_CLASS ZCDistributionAttributesList : public PSS_TreeListCtrl,
                                                   public PSS_Subject,
                                                   public PSS_Observer
{

    DECLARE_DYNAMIC(ZCDistributionAttributesList)

public:
    ZCDistributionAttributesList();
    virtual ~ZCDistributionAttributesList();

    PSS_DistributionAttribute* GetSelectedDistributionAttribute();
    PSS_DistributionRulesForRole* GetSelectedDistributionRuleForRole();
    PSS_DistributionRule* GetSelectedDistributionRule();


    int    Initialize(PSS_DistributionAttributeManager* pDistributionManager,
                      ZBDynamicPropertiesManager* pPropManager,
                      PSS_UserGroupEntity* pMainUserGroup,
                      PSS_DistributionAttribute* pDistributionAttribute = NULL,
                      bool ShowAll = false, int SymbolRef = -1);
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
    //{{AFX_VIRTUAL(ZCDistributionAttributesList)
    //}}AFX_VIRTUAL
protected:
    //{{AFX_MSG(ZCDistributionAttributesList)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    ZCDistributionAttributesList(const ZCDistributionAttributesList &right);
    const    ZCDistributionAttributesList & operator=(const ZCDistributionAttributesList &right);

    void    BuildColumns();
    void    DocumentActivated(PSS_ProcessGraphModelDoc* pDoc);
    int        InsertDistributionAttribute(PSS_DistributionAttribute* pDistributionAttribute, int Level);

private: //## implementation
    PSS_DistributionAttribute* m_pDistributionAttribute;
    PSS_DistributionAttributeManager*    m_pDistributionManager;
    ZBDynamicPropertiesManager* m_pPropManager;
    PSS_UserGroupEntity* m_pMainUserGroup;
    bool                    m_ShowAll;
    int                        m_SymbolRef;
    CODComponent*            m_pComp;
    BOOL                    m_ColumnsBuilt;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif      // ZCDistributionAttributesList_h
