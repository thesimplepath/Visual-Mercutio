// Source file: ProjectWndC.h

#ifndef ProjectWndC_h
#define ProjectWndC_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ProjectI.h"
#include "zBaseLib\ZITreeCtl.h"

/////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZDDocument;
class ZDDocumentData;


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



class AFX_EXT_CLASS ZCProjectWindowTree : public ZITreeCtrl
{
  public:
      ZCProjectWindowTree (ZDDocument* pDoc = NULL, BOOL OnlyVisible = TRUE);
      virtual ~ZCProjectWindowTree();
      void Initialize(ZDDocument* pDoc, BOOL OnlyVisible = TRUE);
      void Initialize();
      void Empty();
      void Refresh();
	  ZDDocumentData*	GetSelectedDocument();
	  CString			GetSelectedDocumentTitle();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZCProjectWindowTree)
	//}}AFX_VIRTUAL
  public:
	//{{AFX_MSG(ZCProjectWindowTree)
	afx_msg LONG OnFileListChanged(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
  private:
      ZCProjectWindowTree(const ZCProjectWindowTree &right);
      const ZCProjectWindowTree & operator=(const ZCProjectWindowTree &right);

  private:

  private: //## implementation
    ZDDocument*		m_pDoc;
	BOOL			m_OnlyVisible;
	ZIProjectTree	m_ProjectTree;

};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
