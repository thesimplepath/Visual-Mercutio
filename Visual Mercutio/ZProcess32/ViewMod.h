//## begin module%3624CA5100B6.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3624CA5100B6.cm

//## begin module%3624CA5100B6.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%3624CA5100B6.cp

//## Module: ViewMod%3624CA5100B6; Package specification
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\ZDesigner\ViewMod.h

#ifndef ViewMod_h
#define ViewMod_h 1

//## begin module%3624CA5100B6.additionalIncludes preserve=no
//## end module%3624CA5100B6.additionalIncludes

//## begin module%3624CA5100B6.includes preserve=yes
//## end module%3624CA5100B6.includes

// ViewRead
#include "zBaseLib\ViewRead.h"

#include "Resource.h"
//## end module%3624CA5100B6.additionalDeclarations



// Forward class declaration
class ZDDocumentReadWrite;



//## Class: ZIViewModify%3624C8EC015D
//## Category: PlanFin::View classes%367B9529010E
//## Subsystem: PlanFin%334FC46302B2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class ZIViewModify : public ZIViewRead  //## Inherits: <unnamed>%3624C90D00CE
{
  //## begin ZIViewModify%3624C8EC015D.initialDeclarations preserve=yes
	DECLARE_DYNCREATE(ZIViewModify)
	public:
	// Inherited feature
		typedef ZIViewRead inherited;
  //## end ZIViewModify%3624C8EC015D.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: GetDocument%908380078
      //	Return a cast document pointer.
      ZDDocumentReadWrite* GetDocument ();

      //## Operation: EditObject%938177640
      //	Process the edition of the object.
      virtual void EditObject (PlanFinObject* pObj = NULL);

    // Additional Public Declarations
      //## begin ZIViewModify%3624C8EC015D.public preserve=yes
      //## end ZIViewModify%3624C8EC015D.public

  protected:
    //## Constructors (generated)
      ZIViewModify();

    //## Destructor (generated)
      virtual ~ZIViewModify();


    //## Other Operations (specified)
      //## Operation: OnDraw%908380093
      virtual void OnDraw (CDC* pDC);

      //## Operation: OnCalculateAllFormula%938112087
      afx_msg LONG OnCalculateAllFormula (UINT message, LONG wParam);

      //## Operation: OnFieldChange%938112088
      //	When a field change this function is called.
      //	This function check if another field have the same
      //	name and copy the contain of the current to the other.
      //	Parameters:
      //	message is the message.
      //	wParam  points to the adress of the object contain.
      afx_msg LONG OnFieldChange (UINT message, LONG wParam);

      //## Operation: CreateEditControl%938177641
      //	returns the right edit control. Based on the object.
      virtual Edit* CreateEditControl (PlanFinObject* pObj, CDC* pDC = NULL);

      //## Operation: AddObjectNotes%941353880
      //	Add an object notes.
      void AddObjectNotes (PlanFinObject* pObj);

	  virtual UINT GetRightPopupMenuID();

    // Data Members for Class Attributes

      //## Attribute: ToolTipTypeObject%381BEA780035
      //	Contains the type object text. Used in tooltip.
      //## begin ZIViewModify::ToolTipTypeObject%381BEA780035.attr preserve=no  protected: CString {U} 
      CString m_ToolTipTypeObject;
      //## end ZIViewModify::ToolTipTypeObject%381BEA780035.attr

      //## Attribute: ToolTipNoteText%381BEA9A01E3
      //	Contains the note object text. Used in tooltip
      //## begin ZIViewModify::ToolTipNoteText%381BEA9A01E3.attr preserve=no  protected: CString {U} 
      CString m_ToolTipNoteText;
      //## end ZIViewModify::ToolTipNoteText%381BEA9A01E3.attr

    // Additional Protected Declarations
      //## begin ZIViewModify%3624C8EC015D.protected preserve=yes
		// Generated message map functions
		//{{AFX_MSG(ZIViewModify)
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);

#if defined( _ZDESIGNER ) || defined( _ZSCRIPTOR )
		afx_msg void OnToday();
		afx_msg void OnEditionProtectObject();
		afx_msg void OnUpdateEditionProtectObject(CCmdUI* pCmdUI);
		afx_msg LONG ProcessCalculate(WPARAM wParam, LPARAM lParam);
		afx_msg LONG OnProcessFieldEditNext(WPARAM wParam, LPARAM lParam);
		afx_msg LONG ProcessFieldChange(WPARAM wParam, LPARAM lParam);
		afx_msg BOOL OnToolTipNeedText(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
		afx_msg void OnAddObjectNotes();
		afx_msg void OnDeleteObjectNotes();
		afx_msg void OnUpdateDeleteObjectNotes(CCmdUI* pCmdUI);
		afx_msg LONG OnEmptyObject(WPARAM wParam, LPARAM lParam);
		afx_msg LONG OnWizardMenu(WPARAM wParam, LPARAM lParam);
		afx_msg LONG OnCalendarObject(WPARAM wParam, LPARAM lParam);
		afx_msg LONG OnObjectNote(WPARAM wParam, LPARAM lParam);
		afx_msg LONG OnAssociationMenu(WPARAM wParam, LPARAM lParam);
		afx_msg LONG OnMenuSelected(WPARAM wParam, LPARAM lParam);
		afx_msg void OnSubmenu1Selectobject();
		afx_msg void OnSubmenu1Unselectobject();
		afx_msg LONG OnClearSelectionAll(WPARAM wParam, LPARAM lParam);
		afx_msg LONG OnPointerSelection(WPARAM wParam, LPARAM lParam);
		afx_msg LONG OnPointerHasSelected(WPARAM wParam, LPARAM lParam);
		afx_msg LONG OnFieldEditNext (WPARAM wParam, LPARAM lParam);
		afx_msg LONG OnDeselectAllObjects(WPARAM wParam, LPARAM lParam);
		afx_msg void OnInsertFile();
		afx_msg void OnUpdateInsertFile(CCmdUI* pCmdUI);
		afx_msg LONG OnObjectProperty(WPARAM wParam, LPARAM lParam);
		afx_msg void OnFieldPositionSize();
		afx_msg void OnFieldProperty();
		afx_msg void OnWizardCreateFormula();
		afx_msg void OnSubmenu1Fontchange();
		afx_msg void OnUpdateSubmenu1Fontchange(CCmdUI* pCmdUI);
		afx_msg void OnSubmenuFormat();
		afx_msg void OnSubmenuModifyFormula();
		afx_msg void OnUpdateSubMenuFormat(CCmdUI* pCmdUI);
		afx_msg void OnUpdateSubmenuAlign(CCmdUI* pCmdUI);
		afx_msg void OnUpdateSubmenuModifyFormula(CCmdUI* pCmdUI);
		afx_msg void OnSubmenuAlign();
		afx_msg void OnSubmenuHidePrtObject();
		afx_msg void OnUpdateSubmenuHidePrtObject(CCmdUI* pCmdUI);
		afx_msg void OnSubmenuObjectHide();
		afx_msg void OnUpdateSubmenuObjectHide(CCmdUI* pCmdUI);
		afx_msg void OnSubmenuChangeColor();
		afx_msg void OnWizardFormat();
		afx_msg void OnWizardCalculated();
		afx_msg void OnFieldAlignCenter();
		afx_msg void OnFieldAlignLeft();
		afx_msg void OnFieldAlignRight();
		afx_msg void OnUpdateFieldAlignCenter(CCmdUI* pCmdUI);
		afx_msg void OnUpdateFieldAlignLeft(CCmdUI* pCmdUI);
		afx_msg void OnUpdateFieldAlignRight(CCmdUI* pCmdUI);
		afx_msg void OnFieldApplyRounded();
		afx_msg void OnSubmenuChangeFillcolor();
		afx_msg void OnSectionAlign();
		afx_msg void OnSectionChangeStyle();
		afx_msg void OnSectionChangeColor();
		afx_msg void OnSectionChangeFillColor();
		afx_msg void OnSectionFontChange();
		afx_msg void OnChangeBorder();
		afx_msg void OnChangeLineColor();
#endif
	//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
      //## end ZIViewModify%3624C8EC015D.protected
  private:
    //## Constructors (generated)
      ZIViewModify(const ZIViewModify &right);

    //## Assignment Operation (generated)
      const ZIViewModify & operator=(const ZIViewModify &right);

    // Additional Private Declarations
      //## begin ZIViewModify%3624C8EC015D.private preserve=yes
      //## end ZIViewModify%3624C8EC015D.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZIViewModify%3624C8EC015D.implementation preserve=yes
      //## end ZIViewModify%3624C8EC015D.implementation

};

//## begin ZIViewModify%3624C8EC015D.postscript preserve=yes
//## end ZIViewModify%3624C8EC015D.postscript

// Class ZIViewModify 


//## Other Operations (inline)
inline ZDDocumentReadWrite* ZIViewModify::GetDocument ()
{
  //## begin ZIViewModify::GetDocument%908380078.body preserve=yes
  	return (ZDDocumentReadWrite*)CView::GetDocument();
  //## end ZIViewModify::GetDocument%908380078.body
}

inline UINT ZIViewModify::GetRightPopupMenuID()
{
#ifdef _ZSCRIPTOR
	return IDR_CONTEXT1_SCRIPTOR;
#endif

#ifdef _ZDESIGNER
	return IDR_CONTEXT1;
#endif

	return -1;
}

//## begin module%3624CA5100B6.epilog preserve=yes
//## end module%3624CA5100B6.epilog


#endif
