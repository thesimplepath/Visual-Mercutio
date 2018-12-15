//## begin module%336510A302B2.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%336510A302B2.cm

//## begin module%336510A302B2.cp preserve=no
//## end module%336510A302B2.cp

//## Module: ZIViewCd%336510A302B2; Package specification
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\PLANFIN\ZIViewCd.h

#ifndef ZIViewCd_h
#define ZIViewCd_h 1

//## begin module%336510A302B2.additionalIncludes preserve=no
//## end module%336510A302B2.additionalIncludes

//## begin module%336510A302B2.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%336510A302B2.includes

// ZIView
#include "ZIView.h"
//## begin module%336510A302B2.declarations preserve=no
//## end module%336510A302B2.declarations

//## begin module%336510A302B2.additionalDeclarations preserve=yes
#ifdef _ZBASELIBEXPORT
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
//## end module%336510A302B2.additionalDeclarations


//## Class: ZIViewCode%3365104501F4
//## Category: PlanFin::Doc/View%334FC46002A2
//## Subsystem: PlanFin%334FC46302B2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZIViewCode : public ZIView  //## Inherits: <unnamed>%3365104501F5
{
  //## begin ZIViewCode%3365104501F4.initialDeclarations preserve=yes
    DECLARE_DYNCREATE(ZIViewCode)
    public:
    // Inherited feature
        typedef ZIView inherited;
  //## end ZIViewCode%3365104501F4.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: GetDisplayCode%862658274
      ClassType GetDisplayCode ();

      //## Operation: SetDisplayCode%862658275
      void SetDisplayCode (ClassType Type);

    // Additional Public Declarations
      //## begin ZIViewCode%3365104501F4.public preserve=yes
      //## end ZIViewCode%3365104501F4.public

  protected:
    //## Constructors (generated)
      ZIViewCode();

    //## Destructor (generated)
      virtual ~ZIViewCode();


    //## Other Operations (specified)
      //## Operation: OnDraw%862261465
      virtual void OnDraw (CDC* pDC);

      //## Operation: OnInitialUpdate%862261466
      virtual void OnInitialUpdate ();

      //## Operation: OnPrint%901710585
      virtual void OnPrint (CDC* pDC, CPrintInfo* pInfo);

      //## Operation: OnPreparePrinting%901710586
      virtual BOOL OnPreparePrinting (CPrintInfo* pInfo);

      //## Operation: OnBeginPrinting%901710587
      virtual void OnBeginPrinting (CDC* pDC, CPrintInfo* pInfo);

      //## Operation: OnEndPrinting%901710588
      virtual void OnEndPrinting (CDC* pDC, CPrintInfo* pInfo);

    // Additional Protected Declarations
      //## begin ZIViewCode%3365104501F4.protected preserve=yes
        // Generated message map functions
        //{{AFX_MSG(ZIViewCode)
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnOnlyNumericFields();
    afx_msg void OnUpdateOnlyNumericFields(CCmdUI* pCmdUI);
    afx_msg LONG OnDisplayFieldType(UINT message, LONG lParam);
    afx_msg LONG OnSynchronizeVScroll(UINT message, LONG lParam);
    afx_msg LONG OnSynchronizeHScroll(UINT message, LONG lParam);
    afx_msg void OnDisplayCalculatedCode();
    afx_msg void OnUpdateDisplayCalculatedCode(CCmdUI* pCmdUI);
    afx_msg void OnDisplayallCode();
    afx_msg void OnUpdateDisplayallCode(CCmdUI* pCmdUI);
    afx_msg void OnDisplayStaticCode();
    afx_msg void OnUpdateDisplayStaticCode(CCmdUI* pCmdUI);
    afx_msg void OnDisplayTextCode();
    afx_msg void OnUpdateDisplayTextCode(CCmdUI* pCmdUI);
    afx_msg void OnDisplayGraphicCode();
    afx_msg void OnUpdateDisplayGraphicCode(CCmdUI* pCmdUI);
    //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
      //## end ZIViewCode%3365104501F4.protected
  private:
    //## Constructors (generated)
      ZIViewCode(const ZIViewCode &right);

    //## Assignment Operation (generated)
      const ZIViewCode & operator=(const ZIViewCode &right);

    // Data Members for Class Attributes

      //## Attribute: iCodeType%336B1F0D0140
      //## begin ZIViewCode::iCodeType%336B1F0D0140.attr preserve=no  private: ClassType {U} 
      ClassType m_iCodeType;
      //## end ZIViewCode::iCodeType%336B1F0D0140.attr

      //## Attribute: iSavePageForPrinting%35BF04420022
      //## begin ZIViewCode::iSavePageForPrinting%35BF04420022.attr preserve=no  private: int {U} 
      int m_iSavePageForPrinting;
      //## end ZIViewCode::iSavePageForPrinting%35BF04420022.attr

    // Additional Private Declarations
      //## begin ZIViewCode%3365104501F4.private preserve=yes
      //## end ZIViewCode%3365104501F4.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZIViewCode%3365104501F4.implementation preserve=yes
      //## end ZIViewCode%3365104501F4.implementation
};

//## begin ZIViewCode%3365104501F4.postscript preserve=yes
//## end ZIViewCode%3365104501F4.postscript

// Class ZIViewCode 


//## Other Operations (inline)
inline ClassType ZIViewCode::GetDisplayCode ()
{
  //## begin ZIViewCode::GetDisplayCode%862658274.body preserve=yes
  return m_iCodeType;
  //## end ZIViewCode::GetDisplayCode%862658274.body
}

inline void ZIViewCode::SetDisplayCode (ClassType Type)
{
  //## begin ZIViewCode::SetDisplayCode%862658275.body preserve=yes
  m_iCodeType = Type;
  //## end ZIViewCode::SetDisplayCode%862658275.body
}

//## begin module%336510A302B2.epilog preserve=yes
//## end module%336510A302B2.epilog


#endif
