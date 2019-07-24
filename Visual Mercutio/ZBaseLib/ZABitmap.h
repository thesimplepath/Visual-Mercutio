//## begin module%3378993C0104.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%3378993C0104.cm

//## begin module%3378993C0104.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%3378993C0104.cp

//## Module: ZABitmap%3378993C0104; Package specification
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\ZDesigner\ZABitmap.h

#ifndef ZABitmap_h
#define ZABitmap_h 1

//## begin module%3378993C0104.additionalIncludes preserve=no
//## end module%3378993C0104.additionalIncludes

//## begin module%3378993C0104.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZBitmap.h"

// Define different type of strikes
enum    DisplayStyles{ InitialSize, FitToRect, FitToRectProp };
//## end module%3378993C0104.includes

// ZAObject
#include "ZAObject.h"
//## begin module%3378993C0104.declarations preserve=no
//## end module%3378993C0104.declarations

//## begin module%3378993C0104.additionalDeclarations preserve=yes
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
//## end module%3378993C0104.additionalDeclarations


//## begin PLFNBitmap%337898F5019A.preface preserve=yes
//## end PLFNBitmap%337898F5019A.preface

//## Class: PLFNBitmap%337898F5019A
//    Bitmap object functionnalities.
//## Category: PlanFin::Objects%334FC461017C
//## Subsystem: PlanFin%334FC46302B2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS PLFNBitmap : public PlanFinObject  //## Inherits: <unnamed>%337898F5019D
{
  //## begin PLFNBitmap%337898F5019A.initialDeclarations preserve=yes
    public:
    // Inherited feature
        typedef PlanFinObject inherited;
          virtual UINT GetRightSubMenu() const { return g_BitmapRightSubMenu; };
  //## end PLFNBitmap%337898F5019A.initialDeclarations

  public:
    //## Constructors (generated)
      PLFNBitmap();

      PLFNBitmap(const PLFNBitmap &right);

    //## Destructor (generated)
      virtual ~PLFNBitmap();

    //## Assignment Operation (generated)
      const PLFNBitmap & operator=(const PLFNBitmap &right);


    //## Other Operations (specified)
      //## Operation: operator =%863541707
      //    A copy constructor with a pointer.
      const PLFNBitmap& operator = (const PLFNBitmap* right);

      //## Operation: Serialize%863541708
      //    Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: Clone%863541709
      //    Make a clone of the object.
      virtual PlanFinObject* Clone ();

      //## Operation: DrawObject%863541710
      //    Draw the object with the current DC.
      virtual void DrawObject (CDC* pDC, ZIView* pView);

      //## Operation: CopyObject%863615076
      virtual void CopyObject (PlanFinObject* pSrc);

      //## Operation: SelectBitmapFile%866485623
      //    Select the bitmpa file from the disk.
      BOOL SelectBitmapFile (CDC* pDC);

      //## Operation: AssignBitmapFile%901981234
      //    Sets the bitmap file and load the image contained in the
      //    file.
      BOOL AssignBitmapFile (CString& File, CDC* pDC);

      //## Operation: SelectBitmapFileDialog%901981235
      //    Displays and process the bitmap file dialog.
      CString SelectBitmapFileDialog ();

      //## Operation: GetPropertyTabs%925634620
      //    Return the list of tabs that should be displayed when
      //    the user asks for object properties.
      virtual UINT GetPropertyTabs () const;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: DisplayStyle%34AFE4F2029E
      //    Defines the different display styles for the bitmap.
      const DisplayStyles GetDisplayStyle () const;
      void SetDisplayStyle (DisplayStyles value);

    // Additional Public Declarations
      //## begin PLFNBitmap%337898F5019A.public preserve=yes
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
      //## end PLFNBitmap%337898F5019A.public
  protected:
    // Additional Protected Declarations
      //## begin PLFNBitmap%337898F5019A.protected preserve=yes
    DECLARE_SERIAL(PLFNBitmap)
      //## end PLFNBitmap%337898F5019A.protected
  private:

    //## Other Operations (specified)
      //## Operation: OpenBitmapFileDialog%866485624
      //    Ask the user for a bitmap file.
      CString OpenBitmapFileDialog ();

      //## Operation: GetBitmapFile%866485625
      //    Read the bitmap file and transfer it to memory.
      BOOL GetBitmapFile (CString sFilename, CDC* pDC);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: hBitmap%33A5880D02E4
      const HBITMAP GethBitmap () const;
      void SethBitmap (HBITMAP value);

      //## Attribute: nBytes%33A589BD0190
      //    Save the length of the pBits buffer.
      const unsigned long GetnBytes () const;
      void SetnBytes (unsigned long value);

      //## Attribute: nHeaderSize%33A856CD0366
      //    Save the length of the pBits buffer.
      const size_t GetnHeaderSize () const;
      void SetnHeaderSize (size_t value);

    // Data Members for Class Attributes

      //## Attribute: pBitmapFileHeader%33A5892A008C
      //## begin PLFNBitmap::pBitmapFileHeader%33A5892A008C.attr preserve=no  private: BITMAPFILEHEADER* {U} 
      BITMAPFILEHEADER* m_pBitmapFileHeader;
      //## end PLFNBitmap::pBitmapFileHeader%33A5892A008C.attr

      //## Attribute: pBitmapInfoHeader%33A589400302
      //## begin PLFNBitmap::pBitmapInfoHeader%33A589400302.attr preserve=no  private: BITMAPINFOHEADER* {U} 
      BITMAPINFOHEADER* m_pBitmapInfoHeader;
      //## end PLFNBitmap::pBitmapInfoHeader%33A589400302.attr

      //## Attribute: pBits%33A589580118
      //## begin PLFNBitmap::pBits%33A589580118.attr preserve=no  private: BYTE* {U} 
      BYTE* m_pBits;
      //## end PLFNBitmap::pBits%33A589580118.attr

      //## begin PLFNBitmap::DisplayStyle%34AFE4F2029E.attr preserve=no  public: DisplayStyles {U} InitialSize
      DisplayStyles m_DisplayStyle;
      //## end PLFNBitmap::DisplayStyle%34AFE4F2029E.attr

    // Additional Private Declarations
      //## begin PLFNBitmap%337898F5019A.private preserve=yes
      //## end PLFNBitmap%337898F5019A.private

  private: //## implementation
    // Data Members for Class Attributes

      //## begin PLFNBitmap::hBitmap%33A5880D02E4.attr preserve=no  private: HBITMAP {U} 
      HBITMAP m_hBitmap;
      //## end PLFNBitmap::hBitmap%33A5880D02E4.attr

      //## begin PLFNBitmap::nBytes%33A589BD0190.attr preserve=no  private: unsigned long {U} 
      unsigned long m_nBytes;
      //## end PLFNBitmap::nBytes%33A589BD0190.attr

      //## begin PLFNBitmap::nHeaderSize%33A856CD0366.attr preserve=no  private: size_t {U} 
      size_t m_nHeaderSize;
      //## end PLFNBitmap::nHeaderSize%33A856CD0366.attr

    // Additional Implementation Declarations
      //## begin PLFNBitmap%337898F5019A.implementation preserve=yes
      ZBitmap    m_Bitmap;
      //## end PLFNBitmap%337898F5019A.implementation

};

//## begin PLFNBitmap%337898F5019A.postscript preserve=yes
//## end PLFNBitmap%337898F5019A.postscript

// Class PLFNBitmap 


//## Other Operations (inline)
inline CString PLFNBitmap::SelectBitmapFileDialog ()
{
  //## begin PLFNBitmap::SelectBitmapFileDialog%901981235.body preserve=yes
      return OpenBitmapFileDialog();
  //## end PLFNBitmap::SelectBitmapFileDialog%901981235.body
}

inline UINT PLFNBitmap::GetPropertyTabs () const
{
  //## begin PLFNBitmap::GetPropertyTabs%925634620.body preserve=yes
      return PropertyGeneralBasicPage | PropertySizePage;
  //## end PLFNBitmap::GetPropertyTabs%925634620.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const HBITMAP PLFNBitmap::GethBitmap () const
{
  //## begin PLFNBitmap::GethBitmap%33A5880D02E4.get preserve=no
  return m_hBitmap;
  //## end PLFNBitmap::GethBitmap%33A5880D02E4.get
}

inline void PLFNBitmap::SethBitmap (HBITMAP value)
{
  //## begin PLFNBitmap::SethBitmap%33A5880D02E4.set preserve=no
  m_hBitmap = value;
  //## end PLFNBitmap::SethBitmap%33A5880D02E4.set
}

inline const unsigned long PLFNBitmap::GetnBytes () const
{
  //## begin PLFNBitmap::GetnBytes%33A589BD0190.get preserve=no
  return m_nBytes;
  //## end PLFNBitmap::GetnBytes%33A589BD0190.get
}

inline void PLFNBitmap::SetnBytes (unsigned long value)
{
  //## begin PLFNBitmap::SetnBytes%33A589BD0190.set preserve=no
  m_nBytes = value;
  //## end PLFNBitmap::SetnBytes%33A589BD0190.set
}

inline const size_t PLFNBitmap::GetnHeaderSize () const
{
  //## begin PLFNBitmap::GetnHeaderSize%33A856CD0366.get preserve=no
  return m_nHeaderSize;
  //## end PLFNBitmap::GetnHeaderSize%33A856CD0366.get
}

inline void PLFNBitmap::SetnHeaderSize (size_t value)
{
  //## begin PLFNBitmap::SetnHeaderSize%33A856CD0366.set preserve=no
  m_nHeaderSize = value;
  //## end PLFNBitmap::SetnHeaderSize%33A856CD0366.set
}

inline const DisplayStyles PLFNBitmap::GetDisplayStyle () const
{
  //## begin PLFNBitmap::GetDisplayStyle%34AFE4F2029E.get preserve=no
  return m_DisplayStyle;
  //## end PLFNBitmap::GetDisplayStyle%34AFE4F2029E.get
}

inline void PLFNBitmap::SetDisplayStyle (DisplayStyles value)
{
  //## begin PLFNBitmap::SetDisplayStyle%34AFE4F2029E.set preserve=no
  m_DisplayStyle = value;
  //## end PLFNBitmap::SetDisplayStyle%34AFE4F2029E.set
}

//## begin module%3378993C0104.epilog preserve=yes
//## end module%3378993C0104.epilog


#endif
