//## begin module%33798B9A02E4.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%33798B9A02E4.cm

//## begin module%33798B9A02E4.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%33798B9A02E4.cp

//## Module: ZANumbrd%33798B9A02E4; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZANumbrd.h

#ifndef ZANumbrd_h
#define ZANumbrd_h 1

//## begin module%33798B9A02E4.additionalIncludes preserve=no
//## end module%33798B9A02E4.additionalIncludes

//## begin module%33798B9A02E4.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_PlanFinObj.h"
#include "ZAObject.h"

//## begin module%33798B9A02E4.additionalDeclarations preserve=yes
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
//## end module%33798B9A02E4.additionalDeclarations


//## Class: PLFNAutoNumbered%33798B3703D4
//    This class is used to represents header with automatic
//    numeration.
//## Category: ZBaseLib::Base objects%37E9429A0111
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS PLFNAutoNumbered : public PlanFinObject
{
    //## begin PLFNAutoNumbered%33798B3703D4.initialDeclarations preserve=yes
public:
    // Inherited feature
    typedef PlanFinObject inherited;

    //    Represents the fill color for the object.
    virtual const COLORREF GetFillColor() const;
    virtual void SetFillColor(COLORREF value);
    //    The handle of the font used to display the font.
    virtual const PSS_Font::FontHandle GethFont() const;
    virtual void SethFont(PSS_Font::FontHandle value);

    virtual const HandleStyle GethStyle() const;
    //## end PLFNAutoNumbered%33798B3703D4.initialDeclarations

public:
    //## Constructors (generated)
    PLFNAutoNumbered();

    PLFNAutoNumbered(const PLFNAutoNumbered &right);

    //## Destructor (generated)
    virtual ~PLFNAutoNumbered();

    //## Assignment Operation (generated)
    const PLFNAutoNumbered & operator=(const PLFNAutoNumbered &right);


    //## Other Operations (specified)
      //## Operation: operator =%863604533
      //    A copy constructor with a pointer.
    const PLFNAutoNumbered& operator = (const PLFNAutoNumbered* right);

    //## Operation: IsEmpty%863604534
    //    Is it an empty field.
    virtual BOOL IsEmpty() const;

    //## Operation: GetFormatedObject%863604535
    //    Format the object with the current object's attributes.
    //## Semantics:
    //    This function return the string
    //    represented the object formated
    //    with the current format type
    //    this function is virtual
    //    The base function returns an empty string
    virtual CString GetFormatedObject();

    //## Operation: ConvertFormatedObject%863604536
    //    Convert a formatted object to numeric, date, string, etc.
    //    Returns true if the value has changed.
    //## Semantics:
    //    This function convert the string
    //    and set the object with the right value
    //    For the base class nothing to do
    virtual BOOL ConvertFormatedObject(const CString& sValue, BOOL bLocateFormat = TRUE, BOOL EmptyWhenZero = FALSE);

    //## Operation: IsSelected%863604537
    //    Is this object selected.
    virtual BOOL IsSelected(const CPoint& point) const;

    //## Operation: Serialize%863604538
    //    Serialization function required for MFC mecanism.
    virtual void Serialize(CArchive& ar);

    //## Operation: Clone%863604539
    //    Make a clone of the object.
    virtual PlanFinObject* Clone();

    //## Operation: CopyObject%863615080
    virtual void CopyObject(PlanFinObject* pSrc);

    //## Operation: DrawObject%863615085
    //    Draw the object with the current DC.
    virtual void DrawObject(CDC* pDC, ZIView* pView);

    //## Operation: SetStringTextLevel%863711322
    //    Set the text level by taking a string.
    void SetStringTextLevel(const CString sText);

    //## Operation: GetStringTextLevel%863711323
    //    Return the TextLevel as a string.
    const CString& GetStringTextLevel() const;

    //## Operation: SizePositionHasChanged%863883949
    //    Notify when the object size and/or position has changed.
    virtual void SizePositionHasChanged();

    //## Operation: GetRightSubMenu%864330569
    //    Return the number of the submenu when the user click the
    //    right mouse button.
    virtual UINT GetRightSubMenu() const;

    //## Operation: GetPropertyTabs%885128490
    //    Return the list of tabs that should be displayed when
    //    the user asks for object properties.
    virtual UINT GetPropertyTabs() const;

    //## Operation: GetUnformatedObject%901298462
    //    Return an unformated string of the object image.
    virtual CString GetUnformatedObject();

    //## Operation: GetJustify%907408179
    virtual UINT GetJustify(ZDDocument* pDoc) const;

    //## Operation: SetJustify%907408180
    virtual void SetJustify(UINT nValue);

    //## Operation: SethStyle%907428568
    //    Assign a new style handle
    //## Postconditions:
    //    After having assigned the handle, remove the font
    //    handle, the object color and the object alignement.
    virtual void SethStyle(HandleStyle value);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: TextLevel%33798C8B03CA
      //    Used to contains the section and paragraph number.
    PSS_PLFNStatic& GetTextLevel();

    //## Attribute: pObject%33798CAF030C
    const PlanFinObject* GetpObject() const;
    void SetpObject(PlanFinObject* value);

    //## Attribute: iTextOffset%33798CEC01D6
    //    Used to specify the text offset from the Section and
    //    Paragraph number.
    const int GetiTextOffset() const;
    void SetiTextOffset(int value);

    //## Attribute: bAutoCalculate%33798E750168
    //    Define if the section and paragraph must be
    //    automatically calculated.
    const BOOL GetbAutoCalculate() const;
    void SetbAutoCalculate(BOOL value);

    //## Attribute: iSectionNumber%33798D34028A
    //    Describe the section number.
    const int GetiSectionNumber() const;
    void SetiSectionNumber(int value);

    //## Attribute: iLevel%33798EB4019A
    //    Define the level.
    const int GetiLevel() const;
    void SetiLevel(int value);

    // Additional Public Declarations
      //## begin PLFNAutoNumbered%33798B3703D4.public preserve=yes
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
    //## end PLFNAutoNumbered%33798B3703D4.public
protected:
    // Additional Protected Declarations
      //## begin PLFNAutoNumbered%33798B3703D4.protected preserve=yes
    DECLARE_SERIAL(PLFNAutoNumbered)
    //## end PLFNAutoNumbered%33798B3703D4.protected
private:
    // Data Members for Class Attributes

      //## begin PLFNAutoNumbered::TextLevel%33798C8B03CA.attr preserve=no  public: PLFNStatic {U} 
    PSS_PLFNStatic m_TextLevel;
    //## end PLFNAutoNumbered::TextLevel%33798C8B03CA.attr

    //## begin PLFNAutoNumbered::pObject%33798CAF030C.attr preserve=no  public: PlanFinObject* {U} NULL
    PlanFinObject* m_pObject;
    //## end PLFNAutoNumbered::pObject%33798CAF030C.attr

    //## begin PLFNAutoNumbered::iTextOffset%33798CEC01D6.attr preserve=no  public: int {U} 20
    int m_iTextOffset;
    //## end PLFNAutoNumbered::iTextOffset%33798CEC01D6.attr

    //## begin PLFNAutoNumbered::bAutoCalculate%33798E750168.attr preserve=no  public: BOOL {U} TRUE
    BOOL m_bAutoCalculate;
    //## end PLFNAutoNumbered::bAutoCalculate%33798E750168.attr

    //## begin PLFNAutoNumbered::iSectionNumber%33798D34028A.attr preserve=no  public: int {U} 
    int m_iSectionNumber;
    //## end PLFNAutoNumbered::iSectionNumber%33798D34028A.attr

    //## begin PLFNAutoNumbered::iLevel%33798EB4019A.attr preserve=no  public: int {U} 0
    int m_iLevel;
    //## end PLFNAutoNumbered::iLevel%33798EB4019A.attr
};

//## Other Operations (inline)
inline BOOL PLFNAutoNumbered::IsEmpty() const
{
    //## begin PLFNAutoNumbered::IsEmpty%863604534.body preserve=yes
    if (m_pObject)
        return m_pObject->IsEmpty();
    return TRUE;
    //## end PLFNAutoNumbered::IsEmpty%863604534.body
}

inline BOOL PLFNAutoNumbered::IsSelected(const CPoint& point) const
{
    //## begin PLFNAutoNumbered::IsSelected%863604537.body preserve=yes
    return(m_rctObject.PtInRect(point));
    //## end PLFNAutoNumbered::IsSelected%863604537.body
}

inline void PLFNAutoNumbered::SetStringTextLevel(const CString sText)
{
    //## begin PLFNAutoNumbered::SetStringTextLevel%863711322.body preserve=yes
    m_TextLevel.SetStr(sText);
    //## end PLFNAutoNumbered::SetStringTextLevel%863711322.body
}

inline const CString& PLFNAutoNumbered::GetStringTextLevel() const
{
    //## begin PLFNAutoNumbered::GetStringTextLevel%863711323.body preserve=yes
    return m_TextLevel.GetStr();
    //## end PLFNAutoNumbered::GetStringTextLevel%863711323.body
}

inline UINT PLFNAutoNumbered::GetRightSubMenu() const
{
    //## begin PLFNAutoNumbered::GetRightSubMenu%864330569.body preserve=yes
    return g_AutoNumberedRightSubMenu;
    //## end PLFNAutoNumbered::GetRightSubMenu%864330569.body
}

inline UINT PLFNAutoNumbered::GetPropertyTabs() const
{
    //## begin PLFNAutoNumbered::GetPropertyTabs%885128490.body preserve=yes
    return PropertyGeneralPage | PropertySizePage | PropertyNumberedPage;
    //## end PLFNAutoNumbered::GetPropertyTabs%885128490.body
}

inline UINT PLFNAutoNumbered::GetJustify(ZDDocument* pDoc) const
{
    //## begin PLFNAutoNumbered::GetJustify%907408179.body preserve=yes
    if (m_pObject)
        return m_pObject->GetJustify(pDoc);
    return 0;
    //## end PLFNAutoNumbered::GetJustify%907408179.body
}

inline void PLFNAutoNumbered::SetJustify(UINT nValue)
{
    //## begin PLFNAutoNumbered::SetJustify%907408180.body preserve=yes
    if (m_pObject)
        m_pObject->SetJustify(nValue);
    //## end PLFNAutoNumbered::SetJustify%907408180.body
}

//## Get and Set Operations for Class Attributes (inline)

inline PSS_PLFNStatic& PLFNAutoNumbered::GetTextLevel()
{
    //## begin PLFNAutoNumbered::GetTextLevel%33798C8B03CA.get preserve=no
    return m_TextLevel;
    //## end PLFNAutoNumbered::GetTextLevel%33798C8B03CA.get
}

inline const PlanFinObject* PLFNAutoNumbered::GetpObject() const
{
    //## begin PLFNAutoNumbered::GetpObject%33798CAF030C.get preserve=no
    return m_pObject;
    //## end PLFNAutoNumbered::GetpObject%33798CAF030C.get
}

inline void PLFNAutoNumbered::SetpObject(PlanFinObject* value)
{
    //## begin PLFNAutoNumbered::SetpObject%33798CAF030C.set preserve=no
    m_pObject = value;
    //## end PLFNAutoNumbered::SetpObject%33798CAF030C.set
}

inline const int PLFNAutoNumbered::GetiTextOffset() const
{
    //## begin PLFNAutoNumbered::GetiTextOffset%33798CEC01D6.get preserve=no
    return m_iTextOffset;
    //## end PLFNAutoNumbered::GetiTextOffset%33798CEC01D6.get
}

inline void PLFNAutoNumbered::SetiTextOffset(int value)
{
    //## begin PLFNAutoNumbered::SetiTextOffset%33798CEC01D6.set preserve=no
    m_iTextOffset = value;
    //## end PLFNAutoNumbered::SetiTextOffset%33798CEC01D6.set
}

inline const BOOL PLFNAutoNumbered::GetbAutoCalculate() const
{
    //## begin PLFNAutoNumbered::GetbAutoCalculate%33798E750168.get preserve=no
    return m_bAutoCalculate;
    //## end PLFNAutoNumbered::GetbAutoCalculate%33798E750168.get
}

inline void PLFNAutoNumbered::SetbAutoCalculate(BOOL value)
{
    //## begin PLFNAutoNumbered::SetbAutoCalculate%33798E750168.set preserve=no
    m_bAutoCalculate = value;
    //## end PLFNAutoNumbered::SetbAutoCalculate%33798E750168.set
}

inline const int PLFNAutoNumbered::GetiSectionNumber() const
{
    //## begin PLFNAutoNumbered::GetiSectionNumber%33798D34028A.get preserve=no
    return m_iSectionNumber;
    //## end PLFNAutoNumbered::GetiSectionNumber%33798D34028A.get
}

inline void PLFNAutoNumbered::SetiSectionNumber(int value)
{
    //## begin PLFNAutoNumbered::SetiSectionNumber%33798D34028A.set preserve=no
    m_iSectionNumber = value;
    //## end PLFNAutoNumbered::SetiSectionNumber%33798D34028A.set
}

inline const int PLFNAutoNumbered::GetiLevel() const
{
    //## begin PLFNAutoNumbered::GetiLevel%33798EB4019A.get preserve=no
    return m_iLevel;
    //## end PLFNAutoNumbered::GetiLevel%33798EB4019A.get
}

inline void PLFNAutoNumbered::SetiLevel(int value)
{
    //## begin PLFNAutoNumbered::SetiLevel%33798EB4019A.set preserve=no
    m_iLevel = value;
    //## end PLFNAutoNumbered::SetiLevel%33798EB4019A.set
}

//## begin module%33798B9A02E4.epilog preserve=yes

inline const PSS_Font::FontHandle PLFNAutoNumbered::GethFont() const
{
    if (m_pObject)
        return m_pObject->GethFont();
    return GethFont();
}

inline void PLFNAutoNumbered::SethFont(PSS_Font::FontHandle value)
{
    if (m_pObject)
        m_pObject->SethFont(value);
}

inline const HandleStyle PLFNAutoNumbered::GethStyle() const
{
    if (m_pObject)
        return m_pObject->GethStyle();
    return GethStyle();
}

#endif
