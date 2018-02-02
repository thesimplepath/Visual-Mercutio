//## begin module%334FC46302F5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%334FC46302F5.cm

//## begin module%334FC46302F5.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%334FC46302F5.cp

//## Module: ZAString%334FC46302F5; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZAString.h

#ifndef ZAString_h
#define ZAString_h 1

//## begin module%334FC46302F5.additionalIncludes preserve=no
//## end module%334FC46302F5.additionalIncludes

//## begin module%334FC46302F5.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%334FC46302F5.includes

// ZAText
#include "ZAText.h"
//## begin module%334FC46302F5.declarations preserve=no
//## end module%334FC46302F5.declarations

//## begin module%334FC46302F5.additionalDeclarations preserve=yes
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
//## end module%334FC46302F5.additionalDeclarations


//## Class: PLFNString%334FC46102D5
//	Visual objects functionnalities.
//## Category: ZBaseLib::Base objects%37E9429A0111
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS PLFNString : public PLFNText  //## Inherits: <unnamed>%334FC46102D6
{
  //## begin PLFNString%334FC46102D5.initialDeclarations preserve=yes
	public:
	// Inherited feature
		typedef PLFNText inherited;
  //## end PLFNString%334FC46102D5.initialDeclarations

  public:
    //## Constructors (generated)
      PLFNString();

      PLFNString(const PLFNString &right);

    //## Destructor (generated)
      virtual ~PLFNString();

    //## Assignment Operation (generated)
      const PLFNString & operator=(const PLFNString &right);


    //## Other Operations (specified)
      //## Operation: operator =%829516133
      //	A copy constructor with a pointer.
      const PLFNString& operator = (const PLFNString* right);

      //## Operation: SetStringValue%831699786
      virtual void SetStringValue (const CString& str);

      //## Operation: GetStringValue%831699787
      virtual CString GetStringValue ();

      //## Operation: GetObjectAdress%831699788
      //	return the adress of the member.
      virtual void * GetObjectAdress () const;

      //## Operation: DrawObject%829516173
      //	Draw the object with the current DC.
      virtual void DrawObject (CDC* pDC, ZIView* pView);

      //## Operation: Serialize%829516183
      //	Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: Clone%849755977
      //	Make a clone of the object.
      virtual PlanFinObject* Clone ();

      //## Operation: CopyObject%863615083
      virtual void CopyObject (PlanFinObject* pSrc);

    // Additional Public Declarations
      //## begin PLFNString%334FC46102D5.public preserve=yes
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
      //## end PLFNString%334FC46102D5.public
  protected:
    // Additional Protected Declarations
      //## begin PLFNString%334FC46102D5.protected preserve=yes
		DECLARE_SERIAL(PLFNString)
      //## end PLFNString%334FC46102D5.protected
  private:
    // Additional Private Declarations
      //## begin PLFNString%334FC46102D5.private preserve=yes
      //## end PLFNString%334FC46102D5.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin PLFNString%334FC46102D5.implementation preserve=yes
      //## end PLFNString%334FC46102D5.implementation

};

//## begin PLFNString%334FC46102D5.postscript preserve=yes
//## end PLFNString%334FC46102D5.postscript

// Class PLFNString 


//## Other Operations (inline)
inline void PLFNString::SetStringValue (const CString& str)
{
  //## begin PLFNString::SetStringValue%831699786.body preserve=yes
  	m_Str = str;
	ClearEmptyObjectFlag();  	
  //## end PLFNString::SetStringValue%831699786.body
}

inline CString PLFNString::GetStringValue ()
{
  //## begin PLFNString::GetStringValue%831699787.body preserve=yes
  	return(m_Str);
  //## end PLFNString::GetStringValue%831699787.body
}

inline void * PLFNString::GetObjectAdress () const
{
  //## begin PLFNString::GetObjectAdress%831699788.body preserve=yes
  	return((void*)&m_Str);
  //## end PLFNString::GetObjectAdress%831699788.body
}

//## begin module%334FC46302F5.epilog preserve=yes
//## end module%334FC46302F5.epilog


#endif
