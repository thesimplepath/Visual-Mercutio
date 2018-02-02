//## begin module%371399280091.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%371399280091.cm

//## begin module%371399280091.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%371399280091.cp

//## Module: ZBRect%371399280091; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZBRect.h

#ifndef ZBRect_h
#define ZBRect_h 1

//## begin module%371399280091.additionalIncludes preserve=no
//## end module%371399280091.additionalIncludes

//## begin module%371399280091.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%371399280091.includes

// Mfc
#include "Mfc.h"
//## begin module%371399280091.declarations preserve=no
//## end module%371399280091.declarations

//## begin module%371399280091.additionalDeclarations preserve=yes
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
//## end module%371399280091.additionalDeclarations


//## Class: ZBRect%3713985D0356
//	This class is used to provide a compatibility between
//	16bit and 32bit generated serialized files.
//## Category: ZBaseLib::Point and Rect classes%37E9424800C3
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZBRect : public CRect  //## Inherits: <unnamed>%3713988A026A
{
  //## begin ZBRect%3713985D0356.initialDeclarations preserve=yes
	public:
	// Inherited feature
		typedef CRect inherited;
  //## end ZBRect%3713985D0356.initialDeclarations

  public:
    //## Constructors (generated)
      ZBRect();

    //## Constructors (specified)
      //## Operation: ZBRect%924031310
      ZBRect (int l, int t, int r, int b);

      //## Operation: ZBRect%924419481
      ZBRect (CRect& Rect);

      //## Operation: ZBRect%941742745
      ZBRect (ZBRect& Rect);

    //## Destructor (generated)
      ~ZBRect();


    //## Other Operations (specified)
      //## Operation: Serialize%924031309
      //	Serialization function required for MFC mecanism. This
      //	is due to 16-32bit compatibility.
      virtual void Serialize (CArchive& ar);

      //## Operation: operator >>%924031311
      //	Store from the archive to the object Stamp.
      AFX_EXT_API friend CArchive& operator >> (CArchive& ar, ZBRect& Rect);

      //## Operation: operator <<%924031312
      //	Store the object Stamp to the archive.
      AFX_EXT_API friend CArchive& operator << (CArchive& ar, ZBRect& Rect);

      //## Operation: operator=%924419484
      const ZBRect & operator = (const CRect &right);

      //## Operation: operator=%941742746
      const ZBRect & operator = (const ZBRect &right);

    // Additional Public Declarations
      //## begin ZBRect%3713985D0356.public preserve=yes
      //## end ZBRect%3713985D0356.public

  protected:
    // Additional Protected Declarations
      //## begin ZBRect%3713985D0356.protected preserve=yes
      //## end ZBRect%3713985D0356.protected

  private:
    // Additional Private Declarations
      //## begin ZBRect%3713985D0356.private preserve=yes
      //## end ZBRect%3713985D0356.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZBRect%3713985D0356.implementation preserve=yes
      //## end ZBRect%3713985D0356.implementation

};

//## begin ZBRect%3713985D0356.postscript preserve=yes
//## end ZBRect%3713985D0356.postscript

// Class ZBRect 

inline ZBRect::ZBRect (int l, int t, int r, int b)
  //## begin ZBRect::ZBRect%924031310.hasinit preserve=no
  //## end ZBRect::ZBRect%924031310.hasinit
  //## begin ZBRect::ZBRect%924031310.initialization preserve=yes
  : CRect( l, t, r, b )
  //## end ZBRect::ZBRect%924031310.initialization
{
  //## begin ZBRect::ZBRect%924031310.body preserve=yes
  //## end ZBRect::ZBRect%924031310.body
}

inline ZBRect::ZBRect (CRect& Rect)
  //## begin ZBRect::ZBRect%924419481.hasinit preserve=no
  //## end ZBRect::ZBRect%924419481.hasinit
  //## begin ZBRect::ZBRect%924419481.initialization preserve=yes
  : CRect( Rect.left, Rect.top, Rect.right, Rect.bottom )
  //## end ZBRect::ZBRect%924419481.initialization
{
  //## begin ZBRect::ZBRect%924419481.body preserve=yes
  //## end ZBRect::ZBRect%924419481.body
}

inline ZBRect::ZBRect (ZBRect& Rect)
  //## begin ZBRect::ZBRect%941742745.hasinit preserve=no
  //## end ZBRect::ZBRect%941742745.hasinit
  //## begin ZBRect::ZBRect%941742745.initialization preserve=yes
  : CRect( Rect.left, Rect.top, Rect.right, Rect.bottom )
  //## end ZBRect::ZBRect%941742745.initialization
{
  //## begin ZBRect::ZBRect%941742745.body preserve=yes
  //## end ZBRect::ZBRect%941742745.body
}



//## Other Operations (inline)
inline const ZBRect & ZBRect::operator = (const CRect &right)
{
  //## begin ZBRect::operator=%924419484.body preserve=yes
	this->CRect::operator=( (CRect&)right );
	return (const ZBRect&)*this;
  //## end ZBRect::operator=%924419484.body
}

inline const ZBRect & ZBRect::operator = (const ZBRect &right)
{
  //## begin ZBRect::operator=%941742746.body preserve=yes
	this->CRect::operator=( (CRect&)right );
	return (const ZBRect&)*this;
  //## end ZBRect::operator=%941742746.body
}

//## begin module%371399280091.epilog preserve=yes
//## end module%371399280091.epilog


#endif


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin ZBRect%3713985D0356.preface preserve=no
//## end ZBRect%3713985D0356.preface

#endif
