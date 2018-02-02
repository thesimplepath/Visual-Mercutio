//## begin module%33EC6F24029E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%33EC6F24029E.cm

//## begin module%33EC6F24029E.cp preserve=no
//## end module%33EC6F24029E.cp

//## Module: ZABorder%33EC6F24029E; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZABorder.h

#ifndef ZABorder_h
#define ZABorder_h 1

//## begin module%33EC6F24029E.additionalIncludes preserve=no
//## end module%33EC6F24029E.additionalIncludes

//## begin module%33EC6F24029E.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%33EC6F24029E.includes

// Mfc
#include "Mfc.h"
//## begin module%33EC6F24029E.declarations preserve=no
//## end module%33EC6F24029E.declarations

//## begin module%33EC6F24029E.additionalDeclarations preserve=yes
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
//## end module%33EC6F24029E.additionalDeclarations


//## begin ZABorder%33EC676303DE.preface preserve=yes
//## end ZABorder%33EC676303DE.preface

//## Class: ZABorder%33EC676303DE
//## Category: ZUtil library::Font & Style classes%36F91D94013C
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZABorder : public CObject  //## Inherits: <unnamed>%33EC678C0136
{
  //## begin ZABorder%33EC676303DE.initialDeclarations preserve=yes
	public:
	// Inherited feature
		typedef CObject inherited;
  //## end ZABorder%33EC676303DE.initialDeclarations

  public:
    //## Constructors (generated)
      ZABorder();

      ZABorder(const ZABorder &right);

    //## Destructor (generated)
      virtual ~ZABorder();

    //## Assignment Operation (generated)
      const ZABorder & operator=(const ZABorder &right);


    //## Other Operations (specified)
      //## Operation: Serialize%871131125
      //	Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: Clone%871131126
      //	Make a clone of the object.
      virtual ZABorder* Clone ();

      //## Operation: DrawBorderRect%908878453
      //	Draw the border rectangle.
      void DrawBorderRect (CDC* pDC, const CRect& rect);

      //## Operation: DrawBorderTopLine%908878454
      //	Draw the top border rectangle.
      void DrawBorderTopLine (CDC* pDC, const CPoint& StartPoint, const CPoint& EndPoint);

      //## Operation: DrawBorderBottomLine%908878455
      //	Draw the bottom border rectangle.
      void DrawBorderBottomLine (CDC* pDC, const CPoint& StartPoint, const CPoint& EndPoint);

      //## Operation: DrawBorderLeftLine%908878456
      //	Draw the left border rectangle.
      void DrawBorderLeftLine (CDC* pDC, const CPoint& StartPoint, const CPoint& EndPoint);

      //## Operation: DrawBorderRightLine%908878457
      //	Draw the right border rectangle.
      void DrawBorderRightLine (CDC* pDC, const CPoint& StartPoint, const CPoint& EndPoint);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: wLeftWidth%33EC695C00D2
      //	Define the width of the left border.
      const WORD GetwLeftWidth () const;
      void SetwLeftWidth (WORD value);

      //## Attribute: wTopWidth%33EC6A1E0140
      //	Define the width of the top border.
      const WORD GetwTopWidth () const;
      void SetwTopWidth (WORD value);

      //## Attribute: wRightWidth%33EC6A2F026C
      //	Define the width of the right border.
      const WORD GetwRightWidth () const;
      void SetwRightWidth (WORD value);

      //## Attribute: wBottomWidth%33EC6A3F0032
      //	Define the width of the bottom border.
      const WORD GetwBottomWidth () const;
      void SetwBottomWidth (WORD value);

      //## Attribute: LeftType%33EC6A5E0352
      //	Define the line type for the left border.
      const LineType GetLeftType () const;
      void SetLeftType (LineType value);

      //## Attribute: RightType%33EC6AAF0064
      //	Define the line type for the right border.
      const LineType GetRightType () const;
      void SetRightType (LineType value);

      //## Attribute: TopType%33EC6AC90352
      //	Define the line type for the top border.
      const LineType GetTopType () const;
      void SetTopType (LineType value);

      //## Attribute: BottomType%33EC6AD7001E
      //	Define the line type for the bottom border.
      const LineType GetBottomType () const;
      void SetBottomType (LineType value);

      //## Attribute: bShadow%33EC6AE801B8
      //	Define the shadow state.
      const BOOL GetbShadow () const;
      void SetbShadow (BOOL value);

      //## Attribute: TopColor%33EDEDF1035C
      //	Defines the color of the top border.
      const COLORREF GetTopColor () const;
      void SetTopColor (COLORREF value);

      //## Attribute: BottomColor%33EDEE15030C
      //	Defines the color of the bottom border.
      const COLORREF GetBottomColor () const;
      void SetBottomColor (COLORREF value);

      //## Attribute: LeftColor%33EDEE2901F4
      //	Defines the color of the left border.
      const COLORREF GetLeftColor () const;
      void SetLeftColor (COLORREF value);

      //## Attribute: RightColor%33EDEE380226
      //	Defines the color of the right border.
      const COLORREF GetRightColor () const;
      void SetRightColor (COLORREF value);

    // Additional Public Declarations
      //## begin ZABorder%33EC676303DE.public preserve=yes
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
      //## end ZABorder%33EC676303DE.public
  protected:
    // Additional Protected Declarations
      //## begin ZABorder%33EC676303DE.protected preserve=yes
	DECLARE_SERIAL(ZABorder)
      //## end ZABorder%33EC676303DE.protected
  private:

    //## Other Operations (specified)
      //## Operation: DrawBorderHorizontalLine%908904114
      //	Draw a horizontal line of a border rectangle.
      void DrawBorderHorizontalLine (CDC* pDC, const CPoint& StartPoint, const CPoint& EndPoint, LineType Type);

      //## Operation: DrawBorderVerticalLine%908904115
      //	Draw a vertical line of a border rectangle.
      void DrawBorderVerticalLine (CDC* pDC, const CPoint& StartPoint, const CPoint& EndPoint, LineType Type);

    // Additional Private Declarations
      //## begin ZABorder%33EC676303DE.private preserve=yes
      //## end ZABorder%33EC676303DE.private

  private: //## implementation
    // Data Members for Class Attributes

      //## begin ZABorder::wLeftWidth%33EC695C00D2.attr preserve=no  public: WORD {U} 1
      WORD m_wLeftWidth;
      //## end ZABorder::wLeftWidth%33EC695C00D2.attr

      //## begin ZABorder::wTopWidth%33EC6A1E0140.attr preserve=no  public: WORD {U} 1
      WORD m_wTopWidth;
      //## end ZABorder::wTopWidth%33EC6A1E0140.attr

      //## begin ZABorder::wRightWidth%33EC6A2F026C.attr preserve=no  public: WORD {U} 1
      WORD m_wRightWidth;
      //## end ZABorder::wRightWidth%33EC6A2F026C.attr

      //## begin ZABorder::wBottomWidth%33EC6A3F0032.attr preserve=no  public: WORD {U} 1
      WORD m_wBottomWidth;
      //## end ZABorder::wBottomWidth%33EC6A3F0032.attr

      //## begin ZABorder::LeftType%33EC6A5E0352.attr preserve=no  public: LineType {U} NoLine
      LineType m_LeftType;
      //## end ZABorder::LeftType%33EC6A5E0352.attr

      //## begin ZABorder::RightType%33EC6AAF0064.attr preserve=no  public: LineType {U} NoLine
      LineType m_RightType;
      //## end ZABorder::RightType%33EC6AAF0064.attr

      //## begin ZABorder::TopType%33EC6AC90352.attr preserve=no  public: LineType {U} NoLine
      LineType m_TopType;
      //## end ZABorder::TopType%33EC6AC90352.attr

      //## begin ZABorder::BottomType%33EC6AD7001E.attr preserve=no  public: LineType {U} NoLine
      LineType m_BottomType;
      //## end ZABorder::BottomType%33EC6AD7001E.attr

      //## begin ZABorder::bShadow%33EC6AE801B8.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_bShadow;
      //## end ZABorder::bShadow%33EC6AE801B8.attr

      //## begin ZABorder::TopColor%33EDEDF1035C.attr preserve=no  public: COLORREF {U} 
      COLORREF m_TopColor;
      //## end ZABorder::TopColor%33EDEDF1035C.attr

      //## begin ZABorder::BottomColor%33EDEE15030C.attr preserve=no  public: COLORREF {U} 
      COLORREF m_BottomColor;
      //## end ZABorder::BottomColor%33EDEE15030C.attr

      //## begin ZABorder::LeftColor%33EDEE2901F4.attr preserve=no  public: COLORREF {U} 
      COLORREF m_LeftColor;
      //## end ZABorder::LeftColor%33EDEE2901F4.attr

      //## begin ZABorder::RightColor%33EDEE380226.attr preserve=no  public: COLORREF {U} 
      COLORREF m_RightColor;
      //## end ZABorder::RightColor%33EDEE380226.attr

    // Additional Implementation Declarations
      //## begin ZABorder%33EC676303DE.implementation preserve=yes
      //## end ZABorder%33EC676303DE.implementation

};

//## begin ZABorder%33EC676303DE.postscript preserve=yes
//## end ZABorder%33EC676303DE.postscript

// Class ZABorder 

//## Get and Set Operations for Class Attributes (inline)

inline const WORD ZABorder::GetwLeftWidth () const
{
  //## begin ZABorder::GetwLeftWidth%33EC695C00D2.get preserve=no
  return m_wLeftWidth;
  //## end ZABorder::GetwLeftWidth%33EC695C00D2.get
}

inline void ZABorder::SetwLeftWidth (WORD value)
{
  //## begin ZABorder::SetwLeftWidth%33EC695C00D2.set preserve=no
  m_wLeftWidth = value;
  //## end ZABorder::SetwLeftWidth%33EC695C00D2.set
}

inline const WORD ZABorder::GetwTopWidth () const
{
  //## begin ZABorder::GetwTopWidth%33EC6A1E0140.get preserve=no
  return m_wTopWidth;
  //## end ZABorder::GetwTopWidth%33EC6A1E0140.get
}

inline void ZABorder::SetwTopWidth (WORD value)
{
  //## begin ZABorder::SetwTopWidth%33EC6A1E0140.set preserve=no
  m_wTopWidth = value;
  //## end ZABorder::SetwTopWidth%33EC6A1E0140.set
}

inline const WORD ZABorder::GetwRightWidth () const
{
  //## begin ZABorder::GetwRightWidth%33EC6A2F026C.get preserve=no
  return m_wRightWidth;
  //## end ZABorder::GetwRightWidth%33EC6A2F026C.get
}

inline void ZABorder::SetwRightWidth (WORD value)
{
  //## begin ZABorder::SetwRightWidth%33EC6A2F026C.set preserve=no
  m_wRightWidth = value;
  //## end ZABorder::SetwRightWidth%33EC6A2F026C.set
}

inline const WORD ZABorder::GetwBottomWidth () const
{
  //## begin ZABorder::GetwBottomWidth%33EC6A3F0032.get preserve=no
  return m_wBottomWidth;
  //## end ZABorder::GetwBottomWidth%33EC6A3F0032.get
}

inline void ZABorder::SetwBottomWidth (WORD value)
{
  //## begin ZABorder::SetwBottomWidth%33EC6A3F0032.set preserve=no
  m_wBottomWidth = value;
  //## end ZABorder::SetwBottomWidth%33EC6A3F0032.set
}

inline const LineType ZABorder::GetLeftType () const
{
  //## begin ZABorder::GetLeftType%33EC6A5E0352.get preserve=no
  return m_LeftType;
  //## end ZABorder::GetLeftType%33EC6A5E0352.get
}

inline void ZABorder::SetLeftType (LineType value)
{
  //## begin ZABorder::SetLeftType%33EC6A5E0352.set preserve=no
  m_LeftType = value;
  //## end ZABorder::SetLeftType%33EC6A5E0352.set
}

inline const LineType ZABorder::GetRightType () const
{
  //## begin ZABorder::GetRightType%33EC6AAF0064.get preserve=no
  return m_RightType;
  //## end ZABorder::GetRightType%33EC6AAF0064.get
}

inline void ZABorder::SetRightType (LineType value)
{
  //## begin ZABorder::SetRightType%33EC6AAF0064.set preserve=no
  m_RightType = value;
  //## end ZABorder::SetRightType%33EC6AAF0064.set
}

inline const LineType ZABorder::GetTopType () const
{
  //## begin ZABorder::GetTopType%33EC6AC90352.get preserve=no
  return m_TopType;
  //## end ZABorder::GetTopType%33EC6AC90352.get
}

inline void ZABorder::SetTopType (LineType value)
{
  //## begin ZABorder::SetTopType%33EC6AC90352.set preserve=no
  m_TopType = value;
  //## end ZABorder::SetTopType%33EC6AC90352.set
}

inline const LineType ZABorder::GetBottomType () const
{
  //## begin ZABorder::GetBottomType%33EC6AD7001E.get preserve=no
  return m_BottomType;
  //## end ZABorder::GetBottomType%33EC6AD7001E.get
}

inline void ZABorder::SetBottomType (LineType value)
{
  //## begin ZABorder::SetBottomType%33EC6AD7001E.set preserve=no
  m_BottomType = value;
  //## end ZABorder::SetBottomType%33EC6AD7001E.set
}

inline const BOOL ZABorder::GetbShadow () const
{
  //## begin ZABorder::GetbShadow%33EC6AE801B8.get preserve=no
  return m_bShadow;
  //## end ZABorder::GetbShadow%33EC6AE801B8.get
}

inline void ZABorder::SetbShadow (BOOL value)
{
  //## begin ZABorder::SetbShadow%33EC6AE801B8.set preserve=no
  m_bShadow = value;
  //## end ZABorder::SetbShadow%33EC6AE801B8.set
}

inline const COLORREF ZABorder::GetTopColor () const
{
  //## begin ZABorder::GetTopColor%33EDEDF1035C.get preserve=no
  return m_TopColor;
  //## end ZABorder::GetTopColor%33EDEDF1035C.get
}

inline void ZABorder::SetTopColor (COLORREF value)
{
  //## begin ZABorder::SetTopColor%33EDEDF1035C.set preserve=no
  m_TopColor = value;
  //## end ZABorder::SetTopColor%33EDEDF1035C.set
}

inline const COLORREF ZABorder::GetBottomColor () const
{
  //## begin ZABorder::GetBottomColor%33EDEE15030C.get preserve=no
  return m_BottomColor;
  //## end ZABorder::GetBottomColor%33EDEE15030C.get
}

inline void ZABorder::SetBottomColor (COLORREF value)
{
  //## begin ZABorder::SetBottomColor%33EDEE15030C.set preserve=no
  m_BottomColor = value;
  //## end ZABorder::SetBottomColor%33EDEE15030C.set
}

inline const COLORREF ZABorder::GetLeftColor () const
{
  //## begin ZABorder::GetLeftColor%33EDEE2901F4.get preserve=no
  return m_LeftColor;
  //## end ZABorder::GetLeftColor%33EDEE2901F4.get
}

inline void ZABorder::SetLeftColor (COLORREF value)
{
  //## begin ZABorder::SetLeftColor%33EDEE2901F4.set preserve=no
  m_LeftColor = value;
  //## end ZABorder::SetLeftColor%33EDEE2901F4.set
}

inline const COLORREF ZABorder::GetRightColor () const
{
  //## begin ZABorder::GetRightColor%33EDEE380226.get preserve=no
  return m_RightColor;
  //## end ZABorder::GetRightColor%33EDEE380226.get
}

inline void ZABorder::SetRightColor (COLORREF value)
{
  //## begin ZABorder::SetRightColor%33EDEE380226.set preserve=no
  m_RightColor = value;
  //## end ZABorder::SetRightColor%33EDEE380226.set
}

//## begin module%33EC6F24029E.epilog preserve=yes
//## end module%33EC6F24029E.epilog


#endif
