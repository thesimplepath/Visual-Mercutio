//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//  Source file: z:\adsoft~1\ZWinUtil\ProcTree.h

#ifndef ProcTree_h
#define ProcTree_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\ZITreeCtl.h"
#include "zEvent\ZProcess.h"

//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZCProcessTreeCtrl : public ZITreeCtrl  
{
  public:
      ZCProcessTreeCtrl (ZProcess* pProcess = NULL);
      ~ZCProcessTreeCtrl();


      void Initialize (ZProcess* pProcess);

      ZProcess*        GetProcess() { return m_pProcess; };
      ZProcess*        GetSelectedProcessItem ();
      ZProcess*        GetRootProcessItem();
      ZActivity*    GetSelectedActivityItem ();
      void            Refresh();
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCProcessTreeCtrl)
    //}}AFX_VIRTUAL
  protected:
    //{{AFX_MSG(ZCProcessTreeCtrl)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  private:
      ZCProcessTreeCtrl(const ZCProcessTreeCtrl &right);
      const ZCProcessTreeCtrl & operator=(const ZCProcessTreeCtrl &right);

      ZProcess*        m_pProcess;

  protected:
      void            FillControl ();

      void            AddProcess (ZBaseActivity* pBaseActivity, HTREEITEM hParentTreeItem, int IconIndex);
      void            AddActivityItems (ZBaseActivity* pBaseActivity, HTREEITEM hParentTreeItem, int IconIndex = 0);
      HTREEITEM        AddProcessItem (ZBaseActivity* pData, HTREEITEM hParentTreeItem, int IconIndex = 0);
      HTREEITEM        AddSubItem (ZActivity* pData, HTREEITEM hParentTreeItem, int IconIndex = 0);

};

//#undef  AFX_DATA
//#define AFX_DATA


#endif
