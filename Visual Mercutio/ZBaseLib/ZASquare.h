/****************************************************************************
 * ==> PSS_PLFNSquare ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan form square object               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PLFNSquareH
#define PSS_PLFNSquareH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNSquare
    //#define PSS_PLFNSquare PLFNSquare
#endif

// processsoft
#include "PSS_PlanFinObject.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Financial plan form square object. A square may only contain one char
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PLFNSquare : public PSS_PlanFinObject
{
public:
    // Inherited feature
    typedef PSS_PlanFinObject inherited;
    //## end PLFNSquare%336D04BA0208.initialDeclarations

public:
    //## Constructors (generated)
    PLFNSquare();

    PLFNSquare(const PLFNSquare &right);

    //## Constructors (specified)
      //## Operation: PLFNSquare%863099799
    PLFNSquare(CSize SquareSize, int iMaxLength);

    //## Destructor (generated)
    virtual ~PLFNSquare();

    //## Assignment Operation (generated)
    const PLFNSquare & operator=(const PLFNSquare &right);


    //## Other Operations (specified)
      //## Operation: operator =%862783356
      //    A copy constructor with a pointer.
    const PLFNSquare& operator = (const PLFNSquare* right);

    //## Operation: Clone%862783358
    //    Make a clone of the object.
    virtual PSS_PlanFinObject* Clone();

    //## Operation: Serialize%862783359
    //    Serialization function required for MFC mecanism.
    virtual void Serialize(CArchive& ar);

    //## Operation: DrawObject%862783360
    //    Draw the object with the current DC.
    virtual void DrawObject(CDC* pDC, ZIView* pView);

    //## Operation: CopyObject%863615081
    virtual void CopyObject(PSS_PlanFinObject* pSrc);

    //## Operation: GetPropertyTabs%885128492
    //    Return the list of tabs that should be displayed when
    //    the user asks for object properties.
    virtual UINT GetPropertyTabs() const;

    //## Operation: IsEmpty%909073220
    //    Is it an empty field.
    virtual BOOL IsEmpty() const;

    //## Operation: GetFormattedObject%909073221
    //    Format the object with the current object's attributes.
    //## Semantics:
    //    This function return the string
    //    represented the object formatted
    //    with the current format type
    //    this function is virtual
    //    The base function returns an empty string
    virtual CString GetFormattedObject();

    //## Operation: ConvertFormattedObject%909073222
    //    Convert a formatted object to numeric, date, string, etc.
    //    Returns true if the value has changed.
    //## Semantics:
    //    This function convert the string
    //    and set the object with the right value
    //    For the base class nothing to do
    virtual BOOL ConvertFormattedObject(const CString& sValue, BOOL bLocateFormat = TRUE, BOOL EmptyWhenZero = FALSE);

    //## Operation: IsSelected%909073223
    //    Is this object selected.
    virtual BOOL IsSelected(const CPoint& point) const;

    //## Operation: GetRightSubMenu%909073224
    //    Return the number of the submenu when the user click the
    //    right mouse button.
    virtual UINT GetRightSubMenu() const;

    //## Operation: GetUnformattedObject%909073225
    //    Return an unformatted string of the object image.
    virtual CString GetUnformattedObject();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: SizeSquare%3371DB18029E
      //    Define the size of each square
    const CSize GetSizeSquare() const;
    void SetSizeSquare(CSize value);

    //## Attribute: SquareMaxLength%3371DB3F03B6
    //    Define the maximum length of the text included within
    //    the squares. Put -1 if you do not want to limit the
    //    input.
    const int GetSquareMaxLength() const;
    void SetSquareMaxLength(int value);

    //## Attribute: bAutoAdjustSize%3372025D0168
    const BOOL GetbAutoAdjustSize() const;
    void SetbAutoAdjustSize(BOOL value);

    //## Attribute: nCharPerSquare%3378676D00FA
    const unsigned int GetnCharPerSquare() const;
    void SetnCharPerSquare(unsigned int value);

    //## Attribute: pObject%362DF9940391
    const PSS_PlanFinObject* GetpObject() const;
    void SetpObject(PSS_PlanFinObject* value);

    //## Attribute: TypeOfSquare%36305ABB03C1
    //    Defines the way the square should be represented.
    const ESquareType GetTypeOfSquare() const;
    void SetTypeOfSquare(ESquareType value);

    //## Attribute: ParsingMode%36305B92030C
    //    Defines the way the parsing should be done.
    const EParsingModeType GetParsingMode() const;
    void SetParsingMode(EParsingModeType value);

    // Additional Public Declarations
      //## begin PLFNSquare%336D04BA0208.public preserve=yes
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
    //## end PLFNSquare%336D04BA0208.public
protected:
    // Additional Protected Declarations
      //## begin PLFNSquare%336D04BA0208.protected preserve=yes
    DECLARE_SERIAL(PLFNSquare)
    //## end PLFNSquare%336D04BA0208.protected
private:

    //## Other Operations (specified)
      //## Operation: DrawSquares%863099801
      //    Draw all squares.
    void DrawSquares(CDC* pDC);

    // Data Members for Class Attributes

      //## begin PLFNSquare::SquareMaxLength%3371DB3F03B6.attr preserve=no  public: int {V} 
    int m_SquareMaxLength;
    //## end PLFNSquare::SquareMaxLength%3371DB3F03B6.attr

    //## begin PLFNSquare::bAutoAdjustSize%3372025D0168.attr preserve=no  public: BOOL {U} 
    BOOL m_bAutoAdjustSize;
    //## end PLFNSquare::bAutoAdjustSize%3372025D0168.attr

    //## begin PLFNSquare::nCharPerSquare%3378676D00FA.attr preserve=no  public: unsigned int {U} 1
    unsigned int m_nCharPerSquare;
    //## end PLFNSquare::nCharPerSquare%3378676D00FA.attr

    //## begin PLFNSquare::pObject%362DF9940391.attr preserve=no  public: PlanFinObject* {U} NULL
    PSS_PlanFinObject* m_pObject;
    //## end PLFNSquare::pObject%362DF9940391.attr

    //## begin PLFNSquare::TypeOfSquare%36305ABB03C1.attr preserve=no  public: SquareType {U} NormalSquare
    ESquareType m_TypeOfSquare;
    //## end PLFNSquare::TypeOfSquare%36305ABB03C1.attr

    //## begin PLFNSquare::ParsingMode%36305B92030C.attr preserve=no  public: ParsingModeType {U} NormalParsing
    EParsingModeType m_ParsingMode;
    //## end PLFNSquare::ParsingMode%36305B92030C.attr

  // Additional Private Declarations
    //## begin PLFNSquare%336D04BA0208.private preserve=yes
    //## end PLFNSquare%336D04BA0208.private

private:  //## implementation
  // Data Members for Class Attributes

    //## begin PLFNSquare::SizeSquare%3371DB18029E.attr preserve=no  public: CSize {V} 
    CSize m_SizeSquare;
    //## end PLFNSquare::SizeSquare%3371DB18029E.attr

  // Additional Implementation Declarations
    //## begin PLFNSquare%336D04BA0208.implementation preserve=yes
    //## end PLFNSquare%336D04BA0208.implementation

};

//## begin PLFNSquare%336D04BA0208.postscript preserve=yes
//## end PLFNSquare%336D04BA0208.postscript

// Class PLFNSquare 


//## Other Operations (inline)
inline UINT PLFNSquare::GetPropertyTabs() const
{
    //## begin PLFNSquare::GetPropertyTabs%885128492.body preserve=yes
    return (g_PropertyGeneralPage | g_PropertySizePage | g_PropertySquarePage);
    //## end PLFNSquare::GetPropertyTabs%885128492.body
}

inline BOOL PLFNSquare::IsEmpty() const
{
    //## begin PLFNSquare::IsEmpty%909073220.body preserve=yes
    if (m_pObject)
        return m_pObject->IsEmpty();
    return TRUE;
    //## end PLFNSquare::IsEmpty%909073220.body
}

inline BOOL PLFNSquare::IsSelected(const CPoint& point) const
{
    //## begin PLFNSquare::IsSelected%909073223.body preserve=yes
    if (m_pObject)
        return m_pObject->IsSelected(point);
    return FALSE;
    //## end PLFNSquare::IsSelected%909073223.body
}

inline UINT PLFNSquare::GetRightSubMenu() const
{
    //## begin PLFNSquare::GetRightSubMenu%909073224.body preserve=yes
    if (m_pObject)
        return m_pObject->GetRightSubMenu();
    return g_ObjectRightSubMenu;
    //## end PLFNSquare::GetRightSubMenu%909073224.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const CSize PLFNSquare::GetSizeSquare() const
{
    //## begin PLFNSquare::GetSizeSquare%3371DB18029E.get preserve=no
    return m_SizeSquare;
    //## end PLFNSquare::GetSizeSquare%3371DB18029E.get
}

inline void PLFNSquare::SetSizeSquare(CSize value)
{
    //## begin PLFNSquare::SetSizeSquare%3371DB18029E.set preserve=no
    m_SizeSquare = value;
    //## end PLFNSquare::SetSizeSquare%3371DB18029E.set
}

inline const int PLFNSquare::GetSquareMaxLength() const
{
    //## begin PLFNSquare::GetSquareMaxLength%3371DB3F03B6.get preserve=no
    return m_SquareMaxLength;
    //## end PLFNSquare::GetSquareMaxLength%3371DB3F03B6.get
}

inline void PLFNSquare::SetSquareMaxLength(int value)
{
    //## begin PLFNSquare::SetSquareMaxLength%3371DB3F03B6.set preserve=no
    m_SquareMaxLength = value;
    //## end PLFNSquare::SetSquareMaxLength%3371DB3F03B6.set
}

inline const BOOL PLFNSquare::GetbAutoAdjustSize() const
{
    //## begin PLFNSquare::GetbAutoAdjustSize%3372025D0168.get preserve=no
    return m_bAutoAdjustSize;
    //## end PLFNSquare::GetbAutoAdjustSize%3372025D0168.get
}

inline void PLFNSquare::SetbAutoAdjustSize(BOOL value)
{
    //## begin PLFNSquare::SetbAutoAdjustSize%3372025D0168.set preserve=no
    m_bAutoAdjustSize = value;
    //## end PLFNSquare::SetbAutoAdjustSize%3372025D0168.set
}

inline const unsigned int PLFNSquare::GetnCharPerSquare() const
{
    //## begin PLFNSquare::GetnCharPerSquare%3378676D00FA.get preserve=no
    return m_nCharPerSquare;
    //## end PLFNSquare::GetnCharPerSquare%3378676D00FA.get
}

inline void PLFNSquare::SetnCharPerSquare(unsigned int value)
{
    //## begin PLFNSquare::SetnCharPerSquare%3378676D00FA.set preserve=no
    m_nCharPerSquare = value;
    //## end PLFNSquare::SetnCharPerSquare%3378676D00FA.set
}

inline const PSS_PlanFinObject* PLFNSquare::GetpObject() const
{
    //## begin PLFNSquare::GetpObject%362DF9940391.get preserve=no
    return m_pObject;
    //## end PLFNSquare::GetpObject%362DF9940391.get
}

inline void PLFNSquare::SetpObject(PSS_PlanFinObject* value)
{
    //## begin PLFNSquare::SetpObject%362DF9940391.set preserve=no
    m_pObject = value;
    //## end PLFNSquare::SetpObject%362DF9940391.set
}

inline const ESquareType PLFNSquare::GetTypeOfSquare() const
{
    //## begin PLFNSquare::GetTypeOfSquare%36305ABB03C1.get preserve=no
    return m_TypeOfSquare;
    //## end PLFNSquare::GetTypeOfSquare%36305ABB03C1.get
}

inline void PLFNSquare::SetTypeOfSquare(ESquareType value)
{
    //## begin PLFNSquare::SetTypeOfSquare%36305ABB03C1.set preserve=no
    m_TypeOfSquare = value;
    //## end PLFNSquare::SetTypeOfSquare%36305ABB03C1.set
}

inline const EParsingModeType PLFNSquare::GetParsingMode() const
{
    //## begin PLFNSquare::GetParsingMode%36305B92030C.get preserve=no
    return m_ParsingMode;
    //## end PLFNSquare::GetParsingMode%36305B92030C.get
}

inline void PLFNSquare::SetParsingMode(EParsingModeType value)
{
    //## begin PLFNSquare::SetParsingMode%36305B92030C.set preserve=no
    m_ParsingMode = value;
    //## end PLFNSquare::SetParsingMode%36305B92030C.set
}

#endif
