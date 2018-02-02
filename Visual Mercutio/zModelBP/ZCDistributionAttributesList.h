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
// <nl>Created:		 05/2002
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


#include "zBaseLib\ZISubject.h"
#include "zBaseLib\ZIObserver.h"
#include "zBaseLib\ZVTreeListCtrl.h"


/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBDistributionAttribute;
class ZBDistributionAttributeManager;
class ZBDistributionRule;
class ZBDistributionRulesForRole;
class ZBDynamicPropertiesManager;
class ZDProcessGraphModelDoc;
class ZBUserGroupEntity;


#ifdef _ZMODELBPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif



class AFX_EXT_CLASS ZCDistributionAttributesList : public ZVTreeListCtrl, public ZISubject, public ZIObserver  
{

	DECLARE_DYNAMIC(ZCDistributionAttributesList)

public:
	ZCDistributionAttributesList ();
	virtual ~ZCDistributionAttributesList();

	ZBDistributionAttribute* GetSelectedDistributionAttribute();
	ZBDistributionRulesForRole*	GetSelectedDistributionRuleForRole();
	ZBDistributionRule*	GetSelectedDistributionRule();


	int	Initialize (ZBDistributionAttributeManager* pDistributionManager, 
					ZBDynamicPropertiesManager* pPropManager, 
					ZBUserGroupEntity* pMainUserGroup,
					ZBDistributionAttribute* pDistributionAttribute = NULL,
					bool ShowAll = false, int SymbolRef = -1);
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
	int	Refresh ();
	void	Empty();


	// Observer call back
	virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZCDistributionAttributesList)
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(ZCDistributionAttributesList)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    ZCDistributionAttributesList(const ZCDistributionAttributesList &right);
    const	ZCDistributionAttributesList & operator=(const ZCDistributionAttributesList &right);

	void	BuildColumns();
	void	DocumentActivated( ZDProcessGraphModelDoc* pDoc );
	int		InsertDistributionAttribute( ZBDistributionAttribute* pDistributionAttribute, int Level );

private: //## implementation
	ZBDistributionAttribute* m_pDistributionAttribute;
	ZBDistributionAttributeManager*	m_pDistributionManager;
	ZBDynamicPropertiesManager* m_pPropManager;
	ZBUserGroupEntity* m_pMainUserGroup;
	bool					m_ShowAll;
	int						m_SymbolRef;
	CODComponent*			m_pComp;
	BOOL					m_ColumnsBuilt;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif	  // ZCDistributionAttributesList_h
