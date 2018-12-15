//## begin module%3373B1970190.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%3373B1970190.cm

//## begin module%3373B1970190.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%3373B1970190.cp

//## Module: ZACheck%3373B1970190; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZACheck.h

#ifndef ZACheck_h
#define ZACheck_h 1

//## begin module%3373B1970190.additionalIncludes preserve=no
//## end module%3373B1970190.additionalIncludes

//## begin module%3373B1970190.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%3373B1970190.includes

// ZATwoSts
#include "ZATwoSts.h"
//## begin module%3373B1970190.declarations preserve=no
//## end module%3373B1970190.declarations

//## begin module%3373B1970190.additionalDeclarations preserve=yes
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
//## end module%3373B1970190.additionalDeclarations


//## Class: PLFNCheck%3373B1310082
//    Manage the check button.
//## Category: ZBaseLib::Base objects%37E9429A0111
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS PLFNCheck : public PLFNTwoStates  //## Inherits: <unnamed>%3373B1310083
{
  //## begin PLFNCheck%3373B1310082.initialDeclarations preserve=yes
    public:
    // Inherited feature
        typedef PLFNTwoStates inherited;
  //## end PLFNCheck%3373B1310082.initialDeclarations

  public:
    //## Constructors (generated)
      PLFNCheck();

      PLFNCheck(const PLFNCheck &right);

    //## Destructor (generated)
      virtual ~PLFNCheck();

    //## Assignment Operation (generated)
      const PLFNCheck & operator=(const PLFNCheck &right);


    //## Other Operations (specified)
      //## Operation: operator =%863220179
      //    A copy constructor with a pointer.
      const PLFNCheck& operator = (const PLFNCheck* right);

      //## Operation: Clone%863220180
      //    Make a clone of the object.
      virtual PlanFinObject* Clone ();

      //## Operation: Serialize%863220181
      //    Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: DrawObject%863220182
      //    Draw the object with the current DC.
      virtual void DrawObject (CDC* pDC, ZIView* pView);

      //## Operation: EditObject%863220183
      //    Edit the object.
      void EditObject (CWnd* pParentWnd, CDC* pDC, ZDDocument* pDoc);

      //## Operation: IsSelected%863265786
      //    Is this object selected.
      virtual BOOL IsSelected (const CPoint& point) const;

      //## Operation: CopyObject%863615079
      virtual void CopyObject (PlanFinObject* pSrc);

      //## Operation: GetPropertyTabs%885128488
      //    Return the list of tabs that should be displayed when
      //    the user asks for object properties.
      virtual UINT GetPropertyTabs () const;

    // Additional Public Declarations
      //## begin PLFNCheck%3373B1310082.public preserve=yes
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
      //## end PLFNCheck%3373B1310082.public
  protected:
    // Additional Protected Declarations
      //## begin PLFNCheck%3373B1310082.protected preserve=yes
    DECLARE_SERIAL(PLFNCheck)
      //## end PLFNCheck%3373B1310082.protected
  private:
    // Additional Private Declarations
      //## begin PLFNCheck%3373B1310082.private preserve=yes
      //## end PLFNCheck%3373B1310082.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin PLFNCheck%3373B1310082.implementation preserve=yes
      //## end PLFNCheck%3373B1310082.implementation

};

//## begin PLFNCheck%3373B1310082.postscript preserve=yes
//## end PLFNCheck%3373B1310082.postscript

// Class PLFNCheck 


//## Other Operations (inline)
inline BOOL PLFNCheck::IsSelected (const CPoint& point) const
{
  //## begin PLFNCheck::IsSelected%863265786.body preserve=yes
    return( m_rctObject.PtInRect( point ) );
  //## end PLFNCheck::IsSelected%863265786.body
}

inline UINT PLFNCheck::GetPropertyTabs () const
{
  //## begin PLFNCheck::GetPropertyTabs%885128488.body preserve=yes
      return PropertyGeneralBasicPage | PropertySizePage | PropertyCheckBoxPage;
  //## end PLFNCheck::GetPropertyTabs%885128488.body
}

//## begin module%3373B1970190.epilog preserve=yes
//## end module%3373B1970190.epilog


#endif
