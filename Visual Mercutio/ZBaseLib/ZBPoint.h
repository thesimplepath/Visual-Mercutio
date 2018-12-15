//## begin module%3719856A01B4.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%3719856A01B4.cm

//## begin module%3719856A01B4.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%3719856A01B4.cp

//## Module: ZBPoint%3719856A01B4; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZBPoint.h

#ifndef ZBPoint_h
#define ZBPoint_h 1

//## begin module%3719856A01B4.additionalIncludes preserve=no
//## end module%3719856A01B4.additionalIncludes

//## begin module%3719856A01B4.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%3719856A01B4.includes

// Mfc
#include "Mfc.h"
//## begin module%3719856A01B4.declarations preserve=no
//## end module%3719856A01B4.declarations

//## begin module%3719856A01B4.additionalDeclarations preserve=yes
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
//## end module%3719856A01B4.additionalDeclarations


//## Class: ZBPoint%371984F6035C
//    This class is used to provide a compatibility between
//    16bit and 32bit generated serialized files.
//## Category: ZBaseLib::Point and Rect classes%37E9424800C3
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZBPoint : public CPoint  //## Inherits: <unnamed>%3719851B0192
{
  //## begin ZBPoint%371984F6035C.initialDeclarations preserve=yes
    public:
    // Inherited feature
        typedef CPoint inherited;
  //## end ZBPoint%371984F6035C.initialDeclarations

  public:
    //## Constructors (generated)
      ZBPoint();

    //## Constructors (specified)
      //## Operation: ZBPoint%924419477
      ZBPoint (int x, int y);

      //## Operation: ZBPoint%924419482
      ZBPoint (CPoint& Point);

      //## Operation: ZBPoint%941742747
      ZBPoint (ZBPoint& Point);

    //## Destructor (generated)
      ~ZBPoint();


    //## Other Operations (specified)
      //## Operation: Serialize%924419478
      //    Serialization function required for MFC mecanism. This
      //    is due to 16-32bit compatibility.
      virtual void Serialize (CArchive& ar);

      //## Operation: operator >>%924419479
      //    Store from the archive to the object Stamp.
      AFX_EXT_API friend CArchive& operator >> (CArchive& ar, ZBPoint& Point);

      //## Operation: operator <<%924419480
      //    Store the object Stamp to the archive.
      AFX_EXT_API friend CArchive& operator << (CArchive& ar, ZBPoint& Point);

      //## Operation: operator=%924419483
      const ZBPoint & operator = (const CPoint &right);

      //## Operation: operator=%941742748
      const ZBPoint & operator = (const ZBPoint &right);

    // Additional Public Declarations
      //## begin ZBPoint%371984F6035C.public preserve=yes
      //## end ZBPoint%371984F6035C.public

  protected:
    // Additional Protected Declarations
      //## begin ZBPoint%371984F6035C.protected preserve=yes
      //## end ZBPoint%371984F6035C.protected

  private:
    // Additional Private Declarations
      //## begin ZBPoint%371984F6035C.private preserve=yes
      //## end ZBPoint%371984F6035C.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZBPoint%371984F6035C.implementation preserve=yes
      //## end ZBPoint%371984F6035C.implementation

};

//## begin ZBPoint%371984F6035C.postscript preserve=yes
//## end ZBPoint%371984F6035C.postscript

// Class ZBPoint 

inline ZBPoint::ZBPoint (int x, int y)
  //## begin ZBPoint::ZBPoint%924419477.hasinit preserve=no
  //## end ZBPoint::ZBPoint%924419477.hasinit
  //## begin ZBPoint::ZBPoint%924419477.initialization preserve=yes
  : CPoint( x, y )
  //## end ZBPoint::ZBPoint%924419477.initialization
{
  //## begin ZBPoint::ZBPoint%924419477.body preserve=yes
  //## end ZBPoint::ZBPoint%924419477.body
}

inline ZBPoint::ZBPoint (CPoint& Point)
  //## begin ZBPoint::ZBPoint%924419482.hasinit preserve=no
  //## end ZBPoint::ZBPoint%924419482.hasinit
  //## begin ZBPoint::ZBPoint%924419482.initialization preserve=yes
  : CPoint( Point.x, Point.y )
  //## end ZBPoint::ZBPoint%924419482.initialization
{
  //## begin ZBPoint::ZBPoint%924419482.body preserve=yes
  //## end ZBPoint::ZBPoint%924419482.body
}

inline ZBPoint::ZBPoint (ZBPoint& Point)
  //## begin ZBPoint::ZBPoint%941742747.hasinit preserve=no
  //## end ZBPoint::ZBPoint%941742747.hasinit
  //## begin ZBPoint::ZBPoint%941742747.initialization preserve=yes
  : CPoint( Point.x, Point.y )
  //## end ZBPoint::ZBPoint%941742747.initialization
{
  //## begin ZBPoint::ZBPoint%941742747.body preserve=yes
  //## end ZBPoint::ZBPoint%941742747.body
}



//## Other Operations (inline)
inline const ZBPoint & ZBPoint::operator = (const CPoint &right)
{
  //## begin ZBPoint::operator=%924419483.body preserve=yes
    this->CPoint::operator=( (CPoint&)right );
    return (const ZBPoint&)*this;
  //## end ZBPoint::operator=%924419483.body
}

inline const ZBPoint & ZBPoint::operator = (const ZBPoint &right)
{
  //## begin ZBPoint::operator=%941742748.body preserve=yes
    this->CPoint::operator=( (CPoint&)right );
    return (const ZBPoint&)*this;
  //## end ZBPoint::operator=%941742748.body
}

//## begin module%3719856A01B4.epilog preserve=yes
//## end module%3719856A01B4.epilog


#endif
