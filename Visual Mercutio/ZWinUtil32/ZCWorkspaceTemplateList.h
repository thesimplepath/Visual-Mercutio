// Source file: ZCWorkspaceTemplateList.h

#ifndef ZCWorkspaceTemplateList_h
#define ZCWorkspaceTemplateList_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\ZIListCtrl.h"

#include "zBaseLib\ZBWorkspaceWizardTemplateItem.h"

// Forward class declaration
class ZBWorkspaceWizardTemplateMg;


#ifdef _ZWINUTIL32EXPORT
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

class AFX_EXT_CLASS ZCWorkspaceTemplateList : public ZIListCtrl
{
  public:
      ZCWorkspaceTemplateList (ZBWorkspaceWizardTemplateMg* pWorkspaceTemplateManager = NULL);
      virtual ~ZCWorkspaceTemplateList();
      void Initialize (ZBWorkspaceWizardTemplateMg* pWorkspaceTemplateManager);
      void Refresh ();
	  ZBWorkspaceWizardTemplateItem*	GetSelectedItem() const;

#ifdef _WIN32
	AFX_EXT_API	friend	ZBWorkspaceWizardTemplateItem&	operator>>( ZBWorkspaceWizardTemplateItem& left, ZCWorkspaceTemplateList& listCtrl );
#endif

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZCWorkspaceTemplateList)
	//}}AFX_VIRTUAL
  protected:
	//{{AFX_MSG(ZCWorkspaceTemplateList)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
  private:
      ZCWorkspaceTemplateList(const ZCWorkspaceTemplateList &right);
      const ZCWorkspaceTemplateList & operator=(const ZCWorkspaceTemplateList &right);

  private:
	BOOL	ColumnsHasBeenBuilt() const { return m_ColumnsHasBeenBuilt; };
	BOOL	BuildColumns();

  private: //## implementation
	ZBWorkspaceWizardTemplateMg*	m_pWorkspaceTemplateManager;
	BOOL							m_ColumnsHasBeenBuilt;

};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
