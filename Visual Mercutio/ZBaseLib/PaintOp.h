//## begin module%37EA7A640312.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%37EA7A640312.cm

//## begin module%37EA7A640312.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%37EA7A640312.cp

//## Module: PaintOp%37EA7A640312; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\PaintOp.h

#ifndef PaintOp_h
#define PaintOp_h 1

//## begin module%37EA7A640312.additionalIncludes preserve=no
//## end module%37EA7A640312.additionalIncludes

//## begin module%37EA7A640312.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%37EA7A640312.includes

//## begin module%37EA7A640312.declarations preserve=no
//## end module%37EA7A640312.declarations

//## begin module%37EA7A640312.additionalDeclarations preserve=yes
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
//## end module%37EA7A640312.additionalDeclarations


//## Class: ZBPaintOperations%37EA7946011C
//    Encapsulates some painting operations.
//## Category: ZBaseLib::Painting classes%37EA70B902D7
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZBPaintOperations 
{
  //## begin ZBPaintOperations%37EA7946011C.initialDeclarations preserve=yes
  //## end ZBPaintOperations%37EA7946011C.initialDeclarations

  public:
    //## Constructors (generated)
      ZBPaintOperations();

    //## Destructor (generated)
      ~ZBPaintOperations();


    //## Other Operations (specified)
      //## Operation: SetLogicalBasicUnits%938112081
      //    Save the basic logical units.
      static void SetLogicalBasicUnits (const CSize LogicalBasicUnits);

      //## Operation: GetLogicalBasicUnits%938112082
      //    Retreive the logical basic units
      static const CSize& GetLogicalBasicUnits ();

      //## Operation: ConvertLogicalUnitsMillimeters%938112083
      //    Convert logical units in millimeters
      static CSize ConvertLogicalUnitsMillimeters (const CSize LogicalUnits);

      //## Operation: ConvertMillimetersLogicalUnits%938112084
      //    Convert millimeters in logical units
      static CSize ConvertMillimetersLogicalUnits (const CSize Millimetres);

    // Additional Public Declarations
      //## begin ZBPaintOperations%37EA7946011C.public preserve=yes
      //## end ZBPaintOperations%37EA7946011C.public

  protected:
    // Additional Protected Declarations
      //## begin ZBPaintOperations%37EA7946011C.protected preserve=yes
      //## end ZBPaintOperations%37EA7946011C.protected

  private:
    //## Constructors (generated)
      ZBPaintOperations(const ZBPaintOperations &right);

    //## Assignment Operation (generated)
      const ZBPaintOperations & operator=(const ZBPaintOperations &right);

    // Data Members for Class Attributes

      //## Attribute: LogicalBasicUnits%37EA79B60159
      //## begin ZBPaintOperations::LogicalBasicUnits%37EA79B60159.attr preserve=no  private: static CSize {V} 
      static CSize m_LogicalBasicUnits;
      //## end ZBPaintOperations::LogicalBasicUnits%37EA79B60159.attr

    // Additional Private Declarations
      //## begin ZBPaintOperations%37EA7946011C.private preserve=yes
      //## end ZBPaintOperations%37EA7946011C.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZBPaintOperations%37EA7946011C.implementation preserve=yes
      //## end ZBPaintOperations%37EA7946011C.implementation

};

//## begin ZBPaintOperations%37EA7946011C.postscript preserve=yes
//## end ZBPaintOperations%37EA7946011C.postscript

// Class ZBPaintOperations 


//## Other Operations (inline)
inline void ZBPaintOperations::SetLogicalBasicUnits (const CSize LogicalBasicUnits)
{
  //## begin ZBPaintOperations::SetLogicalBasicUnits%938112081.body preserve=yes
      m_LogicalBasicUnits = LogicalBasicUnits;
  //## end ZBPaintOperations::SetLogicalBasicUnits%938112081.body
}

inline const CSize& ZBPaintOperations::GetLogicalBasicUnits ()
{
  //## begin ZBPaintOperations::GetLogicalBasicUnits%938112082.body preserve=yes
      return m_LogicalBasicUnits;
  //## end ZBPaintOperations::GetLogicalBasicUnits%938112082.body
}

inline CSize ZBPaintOperations::ConvertLogicalUnitsMillimeters (const CSize LogicalUnits)
{
  //## begin ZBPaintOperations::ConvertLogicalUnitsMillimeters%938112083.body preserve=yes
      return CSize(
                  (int) ((double)LogicalUnits.cx / ((double)m_LogicalBasicUnits.cx / (double)2540)),
                  (int) ((double)LogicalUnits.cy / ((double)m_LogicalBasicUnits.cy / (double)2540)) );
  //## end ZBPaintOperations::ConvertLogicalUnitsMillimeters%938112083.body
}

inline CSize ZBPaintOperations::ConvertMillimetersLogicalUnits (const CSize Millimetres)
{
  //## begin ZBPaintOperations::ConvertMillimetersLogicalUnits%938112084.body preserve=yes
      return CSize(
                  (int) ((double)Millimetres.cx * ((double)m_LogicalBasicUnits.cx / (double)2540)),
                  (int) ((double)Millimetres.cy * ((double)m_LogicalBasicUnits.cy / (double)2540)) );
  //## end ZBPaintOperations::ConvertMillimetersLogicalUnits%938112084.body
}

//## begin module%37EA7A640312.epilog preserve=yes
//## end module%37EA7A640312.epilog


#endif
