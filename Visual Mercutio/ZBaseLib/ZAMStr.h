//## begin module%38722BBA0254.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%38722BBA0254.cm

//## begin module%38722BBA0254.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%38722BBA0254.cp

//## Module: ZAMStr%38722BBA0254; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZAMStr.h

#ifndef ZAMStr_h
#define ZAMStr_h 1

//## begin module%38722BBA0254.additionalIncludes preserve=no
//## end module%38722BBA0254.additionalIncludes

//## begin module%38722BBA0254.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%38722BBA0254.includes

// ZAString
#include "ZAString.h"
//## begin module%38722BBA0254.declarations preserve=no
//## end module%38722BBA0254.declarations

//## begin module%38722BBA0254.additionalDeclarations preserve=yes
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
//## end module%38722BBA0254.additionalDeclarations


//## Class: PLFNMaskString%38722B7803AE
//    Visual objects functionnalities.
//## Category: ZBaseLib::Base objects%37E9429A0111
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS PLFNMaskString : public PLFNString  //## Inherits: <unnamed>%38722B7803AF
{
  //## begin PLFNMaskString%38722B7803AE.initialDeclarations preserve=yes
    public:
    // Inherited feature
        typedef PLFNString inherited;
          virtual UINT GetRightSubMenu() const { return g_MaskEditRightSubMenu; };
  //## end PLFNMaskString%38722B7803AE.initialDeclarations

  public:
    //## Constructors (generated)
      PLFNMaskString();

      PLFNMaskString(const PLFNMaskString &right);

    //## Destructor (generated)
      virtual ~PLFNMaskString();

    //## Assignment Operation (generated)
      const PLFNMaskString & operator=(const PLFNMaskString &right);


    //## Other Operations (specified)
      //## Operation: operator =%947006438
      //    A copy constructor with a pointer.
      const PLFNMaskString& operator = (const PLFNMaskString* right);

      //## Operation: DrawObject%947006442
      //    Draw the object with the current DC.
      virtual void DrawObject (CDC* pDC, ZIView* pView);

      //## Operation: Serialize%947006443
      //    Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: Clone%947006444
      //    Make a clone of the object.
      virtual PlanFinObject* Clone ();

      //## Operation: CopyObject%947006445
      virtual void CopyObject (PlanFinObject* pSrc);

      //## Operation: GetPropertyTabs%947102471
      //    Return the list of tabs that should be displayed when
      //    the user asks for object properties.
      virtual UINT GetPropertyTabs () const;

      //## Operation: GetFormatedObject%947341238
      //    Format the object with the current object's attributes.
      //## Semantics:
      //    This function return the string
      //    represented the object formated
      //    with the current format type
      //    this function is virtual
      //    The base function returns an empty string
      virtual CString GetFormatedObject ();

      //## Operation: IsEmpty%947341239
      //    Is it an empty field.
      BOOL IsEmpty () const;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Mask%38722D8401C6
      //    Contains the mask.
      const CString GetMask () const;
      void SetMask (CString value);

    // Additional Public Declarations
      //## begin PLFNMaskString%38722B7803AE.public preserve=yes
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
      //## end PLFNMaskString%38722B7803AE.public
  protected:
    // Additional Protected Declarations
      //## begin PLFNMaskString%38722B7803AE.protected preserve=yes
        DECLARE_SERIAL(PLFNMaskString)
      //## end PLFNMaskString%38722B7803AE.protected
  private:
    // Data Members for Class Attributes

      //## begin PLFNMaskString::Mask%38722D8401C6.attr preserve=no  public: CString {U} 
      CString m_Mask;
      //## end PLFNMaskString::Mask%38722D8401C6.attr

    // Additional Private Declarations
      //## begin PLFNMaskString%38722B7803AE.private preserve=yes
      //## end PLFNMaskString%38722B7803AE.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin PLFNMaskString%38722B7803AE.implementation preserve=yes
      //## end PLFNMaskString%38722B7803AE.implementation

};

//## begin PLFNMaskString%38722B7803AE.postscript preserve=yes
//## end PLFNMaskString%38722B7803AE.postscript

// Class PLFNMaskString 


//## Other Operations (inline)
inline UINT PLFNMaskString::GetPropertyTabs () const
{
  //## begin PLFNMaskString::GetPropertyTabs%947102471.body preserve=yes
      return PropertyGeneralTextPage | PropertySizePage | PropertyMaskTextPage;
  //## end PLFNMaskString::GetPropertyTabs%947102471.body
}

inline BOOL PLFNMaskString::IsEmpty () const
{
  //## begin PLFNMaskString::IsEmpty%947341239.body preserve=yes
    return m_Mask.IsEmpty();
  //## end PLFNMaskString::IsEmpty%947341239.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const CString PLFNMaskString::GetMask () const
{
  //## begin PLFNMaskString::GetMask%38722D8401C6.get preserve=no
  return m_Mask;
  //## end PLFNMaskString::GetMask%38722D8401C6.get
}

inline void PLFNMaskString::SetMask (CString value)
{
  //## begin PLFNMaskString::SetMask%38722D8401C6.set preserve=no
  m_Mask = value;
  //## end PLFNMaskString::SetMask%38722D8401C6.set
}

//## begin module%38722BBA0254.epilog preserve=yes
//## end module%38722BBA0254.epilog


#endif
