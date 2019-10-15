//## begin module%334FC4630320.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC4630320.cm

//## begin module%334FC4630320.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%334FC4630320.cp

//## Module: ZIView%334FC4630320; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZIView.h

#ifndef ZIView_h
#define ZIView_h 1

//## begin module%334FC4630320.additionalIncludes preserve=no
//## end module%334FC4630320.additionalIncludes

//## begin module%334FC4630320.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%334FC4630320.includes

// Mfc
#include "Mfc.h"
//## begin module%334FC4630320.declarations preserve=no
//## end module%334FC4630320.declarations

//## begin module%334FC4630320.additionalDeclarations preserve=yes
#include "PSS_PlanFinObject.h"
#include "PSS_DropScrollView.h"

// class name mapping
#ifndef PSS_Document
    #define PSS_Document ZDDocument
#endif

class PSS_Document;

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


enum    ViewType { UnknownView,
                   FormReadView, 
                   FormModifyView, 
                   FormFieldCodeView, 
                   FormDesignView, 
                   ProcessReadView, 
                   ProcessModifyView, 
                   ProcessDesignView };

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS
//## end module%334FC4630320.additionalDeclarations


//## Class: ZIView%334FC46002A6
//## Category: ZBaseLib::view classes%37EC7715011E
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZIView : public PSS_DropScrollView
{
  //## begin ZIView%334FC46002A6.initialDeclarations preserve=yes
    DECLARE_DYNCREATE(ZIView)
    public:
    // Inherited feature
        typedef PSS_DropScrollView inherited;
    //## end ZIView%334FC46002A6.initialDeclarations

  public:

    //## Other Operations (specified)
      // Initialize the view
      void Initialize();
      //## Operation: CalculateTheDocumentSize%832201962
      //    Calculate the document size.
      void CalculateTheDocumentSize ();

      //## Operation: SetLogicalCoordinates%832201963
      void SetLogicalCoordinates (CDC* pDC);

      //## Operation: GetDocument%832201964
      //    Return a cast document pointer.
      PSS_Document* GetDocument ();

      //## Operation: OnPrepareDC%832201965
      virtual void OnPrepareDC (CDC* pDC, CPrintInfo* pInfo = NULL);

      //## Operation: ActiveSelectedObject%832201974
      //    bAutoReset permits to turn on or off
      //    the selection
      //    If the object was already selected, then
      //    he is turn non selected
      //
      //    This return the object selected by the righ-click. Null
      //    if no object selected.
      PSS_PlanFinObject* ActiveSelectedObject (CPoint& point, BOOL bAutoReset = FALSE);

      //## Operation: SelectObjectInRect%832201975
      void SelectObjectInRect (const CRect& rect, CWnd* pWnd, CDC* pDC);

      //## Operation: GetRectOfSelectedObject%832201973
      BOOL GetRectOfSelectedObject (CRect& rect);

      //## Operation: DeselectAllObject%832201976
      void DeselectAllObject (CWnd* pWnd, CDC* pDC, PSS_Document* pDoc);

      //## Operation: ClientToDoc%832637469
      //    Converts the client screen coordinates to document
      //    coordinates.
      void ClientToDoc (CPoint& point);

      //## Operation: ClientToDoc%832637470
      //    Converts the client screen coordinates to document
      //    coordinates.
      void ClientToDoc (CRect& rect);

      //## Operation: DocToClient%832637471
      //    Converts the document coordinates to client screen
      //    coordinates.
      void DocToClient (CPoint& point);

      //## Operation: DocToClient%832637472
      //    Converts the document coordinates to client screen
      //    coordinates.
      void DocToClient (CRect& rect);

      //## Operation: FindHitObject%837834739
      //    Return the selected object pointed by the point
      //    argument. If nothing return FALSE.
      PSS_PlanFinObject* FindHitObject (CPoint& point);

      //## Operation: ChooseObject%850768721
      PSS_PlanFinObject* ChooseObject ();

      //## Operation: GetArrayOfSelectedObject%863883947
      //    Return a reference of the array of selected object
      CObArray& GetArrayOfSelectedObject ();

      //## Operation: KeepObjectInPage%901975365
      //    This function tests if the object stills in the page
      //    report. If not, the object is moved.
      void KeepObjectInPage (PSS_PlanFinObject* pObj, CSize& ReportSize);

      //## Operation: GetZoomPercentage%938112085
      //    Returns the current zoom percentage.
      int GetZoomPercentage ();

      //## Operation: SetZoomPercentage%938112086
      //    Sets a new zoom percentage.
      void SetZoomPercentage (int iZoom);

      //## Operation: EditObject%938177648
      //    Process the edition of the object.
      virtual void EditObject (PSS_PlanFinObject* pObj = NULL);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ToolTip%37EDDD520385
      //    The tooltip class member. Used to display tooltip for
      //    fields.
      CToolTipCtrl& GetToolTip ();

      //## Attribute: ViewType%381BFE8502FD
      //    Defines which views we have constructed.
      const ViewType GetViewType () const;

    // Additional Public Declarations
      //## begin ZIView%334FC46002A6.public preserve=yes
        void SetScrollSizes();
      //## end ZIView%334FC46002A6.public

  protected:
    //## Constructors (generated)
      ZIView();
    //## Destructor (generated)
      virtual ~ZIView();


    //## Other Operations (specified)
      //## Operation: OnInitialUpdate%832201961
      virtual void OnInitialUpdate ();

      //## Operation: GetReportPageSize%908446783
      //    Returns the report page size.
      CSize GetReportPageSize ();

      //## Operation: GetReportPageSizeInPixels%908446784
      //    Returns the report page size in pixels.
      CSize GetReportPageSizeInPixels ();

      //## Operation: DrawPageRect%908446785
      //    Draw the page rect.
      void DrawPageRect (CDC* pDC);

      //## Operation: OnDraw%908620922
      virtual void OnDraw (CDC* pDC);

    // Data Members for Class Attributes

      //## Attribute: TotalSize%334FC4600354
      //    The total size of the document.
      //## begin ZIView::TotalSize%334FC4600354.attr preserve=no  public: CSize {V} 
      CSize m_TotalSize;
      //## end ZIView::TotalSize%334FC4600354.attr

      //## Attribute: PageSize%334FC4600355
      //    The size of the page.
      //## begin ZIView::PageSize%334FC4600355.attr preserve=no  public: CSize {V} 
      CSize m_PageSize;
      //## end ZIView::PageSize%334FC4600355.attr

      //## Attribute: pOldPointerSelectedObj%334FC460037D
      //    To keep the old selected object when using pointer.
      //## begin ZIView::pOldPointerSelectedObj%334FC460037D.attr preserve=no  protected: static PlanFinObject* {V} NULL
      static PSS_PlanFinObject* m_pOldPointerSelectedObj;
      //## end ZIView::pOldPointerSelectedObj%334FC460037D.attr

      //## Attribute: LineSize%334FC460037E
      //    The size of a line.
      //## begin ZIView::LineSize%334FC460037E.attr preserve=no  public: CSize {V} 
      CSize m_LineSize;
      //## end ZIView::LineSize%334FC460037E.attr

      //## Attribute: hSelectorCursor%334FC4600381
      //    The cursor for object selection.
      //## begin ZIView::hSelectorCursor%334FC4600381.attr preserve=no  public: HCURSOR {V} 
      HCURSOR m_hSelectorCursor;
      //## end ZIView::hSelectorCursor%334FC4600381.attr

      //## Attribute: ArrayOfSelectedObject%337DD272032A
      //## begin ZIView::ArrayOfSelectedObject%337DD272032A.attr preserve=no  public: CObArray {U} 
      CObArray m_ArrayOfSelectedObject;
      //## end ZIView::ArrayOfSelectedObject%337DD272032A.attr

      //## Attribute: PageRect%3625CCE601FE
      //    Keep the page rect.
      //## begin ZIView::PageRect%3625CCE601FE.attr preserve=no  public: CRect {U} 
      CRect m_PageRect;
      //## end ZIView::PageRect%3625CCE601FE.attr

      //## Attribute: bChooseObjectMode%3627761B02A7
      //    To known if the user must choose an object for the mouse
      //    left click down.
      //## begin ZIView::bChooseObjectMode%3627761B02A7.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_bChooseObjectMode;
      //## end ZIView::bChooseObjectMode%3627761B02A7.attr

      //## begin ZIView::ToolTip%37EDDD520385.attr preserve=no  public: CToolTipCtrl {U} 
      CToolTipCtrl m_ToolTip;
      //## end ZIView::ToolTip%37EDDD520385.attr

      //## begin ZIView::ViewType%381BFE8502FD.attr preserve=no  public: ViewType {U} 
      ViewType m_ViewType;
      //## end ZIView::ViewType%381BFE8502FD.attr

    // Additional Protected Declarations
      //## begin ZIView%334FC46002A6.protected preserve=yes
        // Generated message map functions
        //{{AFX_MSG(ZIView)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        CString        m_StrToolTip;
      //## end ZIView%334FC46002A6.protected
  private:
    //## Constructors (generated)
      ZIView(const ZIView &right);

    //## Assignment Operation (generated)
      const ZIView & operator=(const ZIView &right);

    // Data Members for Class Attributes

      //## Attribute: iLogUnitX%334FC4600352
      //    The logical unit for the X axis
      //## begin ZIView::iLogUnitX%334FC4600352.attr preserve=no  public: int {V} 
      int m_iLogUnitX;
      //## end ZIView::iLogUnitX%334FC4600352.attr

      //## Attribute: iLogUnitY%334FC4600353
      //    The logical coordonates for Y axis.
      //## begin ZIView::iLogUnitY%334FC4600353.attr preserve=no  public: int {V} 
      int m_iLogUnitY;
      //## end ZIView::iLogUnitY%334FC4600353.attr

      //## Attribute: ChoosedObject%334FC4600380
      //    The return object choosed.
      //## begin ZIView::ChoosedObject%334FC4600380.attr preserve=no  public: PlanFinObject* {V} NULL
      PSS_PlanFinObject* m_ChoosedObject;
      //## end ZIView::ChoosedObject%334FC4600380.attr

      //## Attribute: iZoom%37EA8EB600C4
      //    Defines the zoom percentage.
      //## begin ZIView::iZoom%37EA8EB600C4.attr preserve=no  public: int {U} 
      int m_iZoom;
      //## end ZIView::iZoom%37EA8EB600C4.attr

    // Additional Private Declarations
      //## begin ZIView%334FC46002A6.private preserve=yes
      //## end ZIView%334FC46002A6.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZIView%334FC46002A6.implementation preserve=yes
      //## end ZIView%334FC46002A6.implementation

};

//## begin ZIView%334FC46002A6.postscript preserve=yes
//## end ZIView%334FC46002A6.postscript

// Class ZIView 


//## Other Operations (inline)
inline PSS_Document* ZIView::GetDocument ()
{
  //## begin ZIView::GetDocument%832201964.body preserve=yes
      return (PSS_Document*)CView::GetDocument();
  //## end ZIView::GetDocument%832201964.body
}

inline int ZIView::GetZoomPercentage ()
{
  //## begin ZIView::GetZoomPercentage%938112085.body preserve=yes
      return m_iZoom;
  //## end ZIView::GetZoomPercentage%938112085.body
}

//## Get and Set Operations for Class Attributes (inline)

inline CToolTipCtrl& ZIView::GetToolTip ()
{
  //## begin ZIView::GetToolTip%37EDDD520385.get preserve=no
  return m_ToolTip;
  //## end ZIView::GetToolTip%37EDDD520385.get
}

inline const ViewType ZIView::GetViewType () const
{
  //## begin ZIView::GetViewType%381BFE8502FD.get preserve=no
  return m_ViewType;
  //## end ZIView::GetViewType%381BFE8502FD.get
}

//## begin module%334FC4630320.epilog preserve=yes
//## end module%334FC4630320.epilog


#endif
