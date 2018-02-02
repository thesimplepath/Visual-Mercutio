// Source file: fieldtreec.h

#ifndef FieldTreeC_h
#define FieldTreeC_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\ZITreeCtl.h"
#include "zBaseLib\FieldRep.h"


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


class AFX_EXT_CLASS ZCCommonFieldTree : public ZITreeCtrl
{
  public:
      ZCCommonFieldTree (ZBFieldRepository* pFieldRepository = NULL);
      virtual ~ZCCommonFieldTree();
      void Initialize(ZBFieldRepository* pFieldRepository);
	  void ReInitialize (ZBFieldRepository* pFieldRepository);
      void Refresh();
	  ZAObjectDefinition*		GetSelectedField();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZCCommonFieldTree)
	//}}AFX_VIRTUAL
  public:
	//{{AFX_MSG(ZCCommonFieldTree)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
  private:
      ZCCommonFieldTree(const ZCCommonFieldTree &right);
      const ZCCommonFieldTree & operator=(const ZCCommonFieldTree &right);
	  void	CreateTree();

  private:
	void		AddFieldItem(ZAObjectDefinition* pField);
	void		AddFieldHistoryItem(ZAHistoryField* pHistory, HTREEITEM hParentTreeItem);
	void		InitializeTree();

  private: //## implementation
    ZBFieldRepository*	m_pFieldRepository;
	CImageList			m_ImageListTree;					//Item in the Tree image list				

	CString				m_FieldDescriptionKey;
	CString				m_UserHelpKey;
	CString				m_IsReadOnlyKey;
	CString				m_SortedKey;
	CString				m_ClassNameKey;
	CString				m_HistoryKey;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
