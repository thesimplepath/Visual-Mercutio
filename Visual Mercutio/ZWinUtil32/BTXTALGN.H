//## begin module.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module.cm

//## begin module.cp preserve=no
//## end module.cp

//## Module: BTxtAlgn; Package specification
//## Subsystem: Source
//## Source file: d:\adsoft~1\source\btxtalgn.h


#ifndef BTxtAlgn_h
#define BTxtAlgn_h 1

//## begin module.additionalIncludes preserve=no
//## end module.additionalIncludes

//## begin module.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

//## end module.includes

// Mfc
#include "Mfc.h"

//## begin module.declarations preserve=no
//## end module.declarations

//## begin module.additionalDeclarations preserve=yes

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

//## end module.additionalDeclarations


//## Class: ZITextAlignButton
//	Defines a text button with alignement style.
//## Category: Sources
//## Subsystem: Source
//## Persistence: Transient
//## Cardinality/Multiplicity: n


class AFX_EXT_CLASS ZITextAlignButton : public CBitmapButton  //## Inherits: <unnamed>

{
  //## begin ZITextAlignButton.initialDeclarations preserve=yes
	DECLARE_DYNCREATE(ZITextAlignButton)
	public:
	// Inherited feature
		typedef CBitmapButton inherited;
  //## end ZITextAlignButton.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZITextAlignButton%833240214
      //	The default constructor with default parameters.
      ZITextAlignButton(const CString sText = "", UINT nStyle = DT_SINGLELINE | DT_BOTTOM | DT_LEFT, BOOL bCheck = FALSE, CWnd* pParentWnd = NULL, UINT nID = 0);

    //## Destructor (generated)
      ~ZITextAlignButton();


    //## Other Operations (specified)
      //## Operation: Create%833240214
      //	The create function.
      void Create(const CString sText, UINT nStyle, BOOL bCheck, CWnd* pParentWnd, UINT nID);

      //## Operation: SetCheck%833261590
      void SetCheck(BOOL bValue = TRUE);

      //## Operation: GetCheck%833261591
      BOOL GetCheck() const;

    // Additional Public Declarations
      //## begin ZITextAlignButton.public preserve=yes
      //## end ZITextAlignButton.public


  protected:

    //## Other Operations (specified)
      //## Operation: DrawItem%833240215
      //	Used to draw the button.
      virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

    // Additional Protected Declarations
      //## begin ZITextAlignButton.protected preserve=yes
		// Generated message map functions
		//{{AFX_MSG(ZITextAlignButton)
	//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
      //## end ZITextAlignButton.protected


  private:
    //## Constructors (generated)
      ZITextAlignButton(const ZITextAlignButton &right);

    //## Assignment Operation (generated)
      const ZITextAlignButton & operator=(const ZITextAlignButton &right);

    // Data Members for Class Attributes

      //## Attribute: nStyle
      //	Define the button style.
      //## begin ZITextAlignButton::nStyle.attr preserve=no  public: UINT {V} 
      UINT m_nStyle;
      //## end ZITextAlignButton::nStyle.attr

      //## Attribute: pParentWnd
      //	The parent window of the button.
      //## begin ZITextAlignButton::pParentWnd.attr preserve=no  public: CWnd* {V} 
      CWnd* m_pParentWnd;
      //## end ZITextAlignButton::pParentWnd.attr

      //## Attribute: nID
      //	The resource ID of the button.
      //## begin ZITextAlignButton::nID.attr preserve=no  public: UINT {V} 
      UINT m_nID;
      //## end ZITextAlignButton::nID.attr

      //## Attribute: sText
      //	The button's text.
      //## begin ZITextAlignButton::sText.attr preserve=no  public: CString {V} 
      CString m_sText;
      //## end ZITextAlignButton::sText.attr

      //## Attribute: bCheck
      //	State the button for checked or not.
      //## begin ZITextAlignButton::bCheck.attr preserve=no  public: BOOL {V} 
      BOOL m_bCheck;
      //## end ZITextAlignButton::bCheck.attr

    // Additional Private Declarations
      //## begin ZITextAlignButton.private preserve=yes
      //## end ZITextAlignButton.private


  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZITextAlignButton.implementation preserve=yes
      //## end ZITextAlignButton.implementation

};



// Class ZITextAlignButton 


//## Other Operations (inline)
inline void ZITextAlignButton::SetCheck(BOOL bValue)
{
  //## begin ZITextAlignButton::SetCheck%833261590.body preserve=yes
  	m_bCheck = bValue;
  	Invalidate();
  //## end ZITextAlignButton::SetCheck%833261590.body
}

inline BOOL ZITextAlignButton::GetCheck() const
{
  //## begin ZITextAlignButton::GetCheck%833261591.body preserve=yes
  	return m_bCheck;
  //## end ZITextAlignButton::GetCheck%833261591.body
}





#endif


