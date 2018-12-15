//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//  Source file: ViewRead.h

#ifndef ViewRead_h
#define ViewRead_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


// ZIView
#include "ZIView.h"
#include "ZDDoc.h"


#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif



class AFX_EXT_CLASS ZIViewRead : public ZIView
{
    DECLARE_DYNCREATE(ZIViewRead)
    public:
    // Inherited feature
        typedef CScrollView inherited;

  public:
    //## Constructors (generated)
      ZIViewRead();

      //    Return a cast document pointer.
      ZDDocument* GetDocument ();

  protected:

    //## Destructor (generated)
      virtual ~ZIViewRead();


    //## Other Operations (specified)
      //## Operation: OnDraw%908122317
      virtual void OnDraw (CDC* pDC);

      //## Operation: OnPrint%908122321
      virtual void OnPrint (CDC* pDC, CPrintInfo* pInfo);

      //## Operation: OnPreparePrinting%908122322
      virtual BOOL OnPreparePrinting (CPrintInfo* pInfo);

      //## Operation: OnBeginPrinting%908122323
      virtual void OnBeginPrinting (CDC* pDC, CPrintInfo* pInfo);

      //## Operation: OnEndPrinting%908122324
      virtual void OnEndPrinting (CDC* pDC, CPrintInfo* pInfo);

      //## Operation: PreTranslateMessage%938177645
      //    Pre translates key message.
      virtual BOOL PreTranslateMessage (MSG* pMsg);

      virtual UINT GetRightPopupMenuID();

    // Additional Protected Declarations
      //## begin ZIViewRead%3620D7FF0234.protected preserve=yes
        // Generated message map functions
        //{{AFX_MSG(ZIViewRead)
        afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnViewZoomin();
        afx_msg void OnViewZoomout();
        afx_msg void OnUpdateViewZoomin(CCmdUI* pCmdUI);
        afx_msg void OnUpdateViewZoomout(CCmdUI* pCmdUI);
    //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
      //## end ZIViewRead%3620D7FF0234.protected
  private:
    //## Constructors (generated)
      ZIViewRead(const ZIViewRead &right);

    //## Assignment Operation (generated)
      const ZIViewRead & operator=(const ZIViewRead &right);

    // Data Members for Class Attributes

      //## Attribute: iSavePageForPrinting%3620D7FF027F
      //    Used for multiple page printing.
      //    To save the current page.
      //    Used when the user wants select more than one object
      //## begin ZIViewRead::iSavePageForPrinting%3620D7FF027F.attr preserve=no  public: int {U} 
      int m_iSavePageForPrinting;
      //## end ZIViewRead::iSavePageForPrinting%3620D7FF027F.attr

    // Additional Private Declarations
      //## begin ZIViewRead%3620D7FF0234.private preserve=yes
      //## end ZIViewRead%3620D7FF0234.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZIViewRead%3620D7FF0234.implementation preserve=yes
      //## end ZIViewRead%3620D7FF0234.implementation

};

//## begin ZIViewRead%3620D7FF0234.postscript preserve=yes
//## end ZIViewRead%3620D7FF0234.postscript

// Class ZIViewRead 


//## Other Operations (inline)
inline ZDDocument* ZIViewRead::GetDocument ()
{
  //## begin ZIViewRead::GetDocument%908122302.body preserve=yes
      return (ZDDocument*)CView::GetDocument();
  //## end ZIViewRead::GetDocument%908122302.body
}


inline UINT ZIViewRead::GetRightPopupMenuID()
{
    return IDR_POPUPMENU_READERVIEW;
}

//## begin module%3620D88A00CB.epilog preserve=yes
//## end module%3620D88A00CB.epilog


#endif
