//## begin module%3513889300DC.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3513889300DC.cm

//## begin module%3513889300DC.cp preserve=no
//## end module%3513889300DC.cp

//## Module: ZATwoSts%3513889300DC; Package specification
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\PLANFIN\ZATwoSts.h

#ifndef ZATwoSts_h
#define ZATwoSts_h 1

//## begin module%3513889300DC.additionalIncludes preserve=no
//## end module%3513889300DC.additionalIncludes

//## begin module%3513889300DC.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%3513889300DC.includes

// ZAGraphc
#include "ZAGraphc.h"
//## begin module%3513889300DC.declarations preserve=no
//## end module%3513889300DC.declarations

//## begin module%3513889300DC.additionalDeclarations preserve=yes
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
//## end module%334FC46302EF.additionalDeclarations
//## end module%3513889300DC.additionalDeclarations


//## Class: PLFNTwoStates%35138727014A
//	Implements the two states for radio and check button
//## Category: PlanFin::Objects%334FC461017C
//## Subsystem: PlanFin%334FC46302B2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS PLFNTwoStates : public PLFNGraphic  //## Inherits: <unnamed>%35138751023A
{
  //## begin PLFNTwoStates%35138727014A.initialDeclarations preserve=yes
	public:
	// Inherited feature
		typedef PLFNGraphic inherited;
      	virtual UINT GetRightSubMenu() const { return TwoStateRightSubMenu; };
		virtual const BOOL GetIsStatic () const { return FALSE; };
  //## end PLFNTwoStates%35138727014A.initialDeclarations

  public:
    //## Constructors (generated)
      PLFNTwoStates();

      PLFNTwoStates(const PLFNTwoStates &right);

    //## Destructor (generated)
      virtual ~PLFNTwoStates();

    //## Assignment Operation (generated)
      const PLFNTwoStates & operator=(const PLFNTwoStates &right);


    //## Other Operations (specified)
      //## Operation: operator =%890472640
      //	A copy constructor with a pointer.
      const PLFNTwoStates& operator = (const PLFNTwoStates* right);

      //## Operation: Serialize%890472641
      //	Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: Clone%890472642
      //	Make a clone of the object.
      virtual PlanFinObject* Clone ();

      //## Operation: CopyObject%890472643
      virtual void CopyObject (PlanFinObject* pSrc);

      //## Operation: GetUnformatedObject%917858762
      //	Return an unformated string of the object image.
      virtual CString GetUnformatedObject ();

      //## Operation: ConvertFormatedObject%917889603
      //	Convert a formatted object to numeric, date, string, etc.
      //	Returns true if the value has changed.
      //## Semantics:
      //	This function convert the string
      //	and set the object with the right value
      //	For the base class nothing to d
      virtual BOOL ConvertFormatedObject (const CString& sValue, BOOL bLocateFormat = TRUE, BOOL EmptyWhenZero = FALSE);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: CheckType%35138814033E
      const CheckButtonType GetCheckType () const;
      void SetCheckType (CheckButtonType value);

      //## Attribute: bCheckState%3513881E0226
      const BOOL GetbCheckState () const;
      void SetbCheckState (BOOL value);

      //## Attribute: uSize%35138827026C
      const unsigned short GetuSize () const;
      void SetuSize (unsigned short value);

      //## Attribute: sText%35138B540348
      //	Contains the text of the two states control.
      const CString GetsText () const;
      void SetsText (CString value);

      //## Attribute: bShowText%35138BD003CA
      //	Flag for showing text.
      const BOOL GetbShowText () const;
      void SetbShowText (BOOL value);

      //## Attribute: bTextIsCtrl%35138C6E0154
      //	Flag to specify if the text acts as the control. In this
      //	case, the control is not displayed.
      const BOOL GetbTextIsCtrl () const;
      void SetbTextIsCtrl (BOOL value);

      //## Attribute: OffsetText%351396A70366
      //	Specifies the text offset.
      const WORD GetOffsetText () const;
      void SetOffsetText (WORD value);

      //## Attribute: bLeftText%351F6EAB023A
      //	Flag to display text on the left of the control.
      const BOOL GetbLeftText () const;
      void SetbLeftText (BOOL value);

    // Additional Public Declarations
      //## begin PLFNTwoStates%35138727014A.public preserve=yes
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
      //## end PLFNTwoStates%35138727014A.public
  protected:
    // Additional Protected Declarations
      //## begin PLFNTwoStates%35138727014A.protected preserve=yes
	DECLARE_SERIAL(PLFNTwoStates)
      //## end PLFNTwoStates%35138727014A.protected
  private:
    // Data Members for Class Attributes

      //## begin PLFNTwoStates::CheckType%35138814033E.attr preserve=no  public: CheckButtonType {U} Rounded
      CheckButtonType m_CheckType;
      //## end PLFNTwoStates::CheckType%35138814033E.attr

      //## begin PLFNTwoStates::bCheckState%3513881E0226.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_bCheckState;
      //## end PLFNTwoStates::bCheckState%3513881E0226.attr

      //## begin PLFNTwoStates::uSize%35138827026C.attr preserve=no  public: unsigned short {U} 
      unsigned short m_uSize;
      //## end PLFNTwoStates::uSize%35138827026C.attr

      //## begin PLFNTwoStates::bShowText%35138BD003CA.attr preserve=no  public: BOOL {U} TRUE
      BOOL m_bShowText;
      //## end PLFNTwoStates::bShowText%35138BD003CA.attr

      //## begin PLFNTwoStates::bTextIsCtrl%35138C6E0154.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_bTextIsCtrl;
      //## end PLFNTwoStates::bTextIsCtrl%35138C6E0154.attr

      //## begin PLFNTwoStates::OffsetText%351396A70366.attr preserve=no  public: WORD {U} 10
      WORD m_OffsetText;
      //## end PLFNTwoStates::OffsetText%351396A70366.attr

      //## begin PLFNTwoStates::bLeftText%351F6EAB023A.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_bLeftText;
      //## end PLFNTwoStates::bLeftText%351F6EAB023A.attr

    // Additional Private Declarations
      //## begin PLFNTwoStates%35138727014A.private preserve=yes
      //## end PLFNTwoStates%35138727014A.private

  private:  //## implementation
    // Data Members for Class Attributes

      //## begin PLFNTwoStates::sText%35138B540348.attr preserve=no  public: CString {U} 
      CString m_sText;
      //## end PLFNTwoStates::sText%35138B540348.attr

    // Additional Implementation Declarations
      //## begin PLFNTwoStates%35138727014A.implementation preserve=yes
      //## end PLFNTwoStates%35138727014A.implementation

};

//## begin PLFNTwoStates%35138727014A.postscript preserve=yes
//## end PLFNTwoStates%35138727014A.postscript

// Class PLFNTwoStates 

//## Get and Set Operations for Class Attributes (inline)

inline const CheckButtonType PLFNTwoStates::GetCheckType () const
{
  //## begin PLFNTwoStates::GetCheckType%35138814033E.get preserve=no
  return m_CheckType;
  //## end PLFNTwoStates::GetCheckType%35138814033E.get
}

inline void PLFNTwoStates::SetCheckType (CheckButtonType value)
{
  //## begin PLFNTwoStates::SetCheckType%35138814033E.set preserve=no
  m_CheckType = value;
  //## end PLFNTwoStates::SetCheckType%35138814033E.set
}

inline const BOOL PLFNTwoStates::GetbCheckState () const
{
  //## begin PLFNTwoStates::GetbCheckState%3513881E0226.get preserve=no
  return m_bCheckState;
  //## end PLFNTwoStates::GetbCheckState%3513881E0226.get
}

inline void PLFNTwoStates::SetbCheckState (BOOL value)
{
  //## begin PLFNTwoStates::SetbCheckState%3513881E0226.set preserve=no
  m_bCheckState = value;
  //## end PLFNTwoStates::SetbCheckState%3513881E0226.set
}

inline const unsigned short PLFNTwoStates::GetuSize () const
{
  //## begin PLFNTwoStates::GetuSize%35138827026C.get preserve=no
  return m_uSize;
  //## end PLFNTwoStates::GetuSize%35138827026C.get
}

inline void PLFNTwoStates::SetuSize (unsigned short value)
{
  //## begin PLFNTwoStates::SetuSize%35138827026C.set preserve=no
  m_uSize = value;
  //## end PLFNTwoStates::SetuSize%35138827026C.set
}

inline const CString PLFNTwoStates::GetsText () const
{
  //## begin PLFNTwoStates::GetsText%35138B540348.get preserve=no
  return m_sText;
  //## end PLFNTwoStates::GetsText%35138B540348.get
}

inline void PLFNTwoStates::SetsText (CString value)
{
  //## begin PLFNTwoStates::SetsText%35138B540348.set preserve=no
  m_sText = value;
  //## end PLFNTwoStates::SetsText%35138B540348.set
}

inline const BOOL PLFNTwoStates::GetbShowText () const
{
  //## begin PLFNTwoStates::GetbShowText%35138BD003CA.get preserve=no
  return m_bShowText;
  //## end PLFNTwoStates::GetbShowText%35138BD003CA.get
}

inline void PLFNTwoStates::SetbShowText (BOOL value)
{
  //## begin PLFNTwoStates::SetbShowText%35138BD003CA.set preserve=no
  m_bShowText = value;
  //## end PLFNTwoStates::SetbShowText%35138BD003CA.set
}

inline const BOOL PLFNTwoStates::GetbTextIsCtrl () const
{
  //## begin PLFNTwoStates::GetbTextIsCtrl%35138C6E0154.get preserve=no
  return m_bTextIsCtrl;
  //## end PLFNTwoStates::GetbTextIsCtrl%35138C6E0154.get
}

inline void PLFNTwoStates::SetbTextIsCtrl (BOOL value)
{
  //## begin PLFNTwoStates::SetbTextIsCtrl%35138C6E0154.set preserve=no
  m_bTextIsCtrl = value;
  //## end PLFNTwoStates::SetbTextIsCtrl%35138C6E0154.set
}

inline const WORD PLFNTwoStates::GetOffsetText () const
{
  //## begin PLFNTwoStates::GetOffsetText%351396A70366.get preserve=no
  return m_OffsetText;
  //## end PLFNTwoStates::GetOffsetText%351396A70366.get
}

inline void PLFNTwoStates::SetOffsetText (WORD value)
{
  //## begin PLFNTwoStates::SetOffsetText%351396A70366.set preserve=no
  m_OffsetText = value;
  //## end PLFNTwoStates::SetOffsetText%351396A70366.set
}

inline const BOOL PLFNTwoStates::GetbLeftText () const
{
  //## begin PLFNTwoStates::GetbLeftText%351F6EAB023A.get preserve=no
  return m_bLeftText;
  //## end PLFNTwoStates::GetbLeftText%351F6EAB023A.get
}

inline void PLFNTwoStates::SetbLeftText (BOOL value)
{
  //## begin PLFNTwoStates::SetbLeftText%351F6EAB023A.set preserve=no
  m_bLeftText = value;
  //## end PLFNTwoStates::SetbLeftText%351F6EAB023A.set
}

//## begin module%3513889300DC.epilog preserve=yes
//## end module%3513889300DC.epilog


#endif
