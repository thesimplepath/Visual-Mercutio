//## begin module%379033D80156.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%379033D80156.cm

//## begin module%379033D80156.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%379033D80156.cp

//## Module: ProcIter%379033D80156; Package specification
//## Subsystem: ZEvent%378A5F7E02DB
//## Source file: z:\adsoft~1\ZEvent\ProcIter.h

#ifndef ProcIter_h
#define ProcIter_h 1

//## begin module%379033D80156.additionalIncludes preserve=no
//## end module%379033D80156.additionalIncludes

//## begin module%379033D80156.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

class    ZBaseActivity;
class    ZActivity;
class    ZProcess;
//## end module%379033D80156.includes

//## begin module%379033D80156.declarations preserve=no
//## end module%379033D80156.declarations

//## begin module%379033D80156.additionalDeclarations preserve=yes
#ifdef _ZEVENTEXPORT
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
//## end module%379033D80156.additionalDeclarations


//## Class: ZProcessIterator%379031B90231
//## Category: ZEvent::Process Classes - Event%378A5FD903A4
//## Subsystem: ZEvent%378A5F7E02DB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZProcessIterator 
{
  //## begin ZProcessIterator%379031B90231.initialDeclarations preserve=yes
  //## end ZProcessIterator%379031B90231.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZProcessIterator%932194635
      //    Initialize the process iterator.
      ZProcessIterator (ZProcess* pProcess = NULL);

    //## Destructor (generated)
      ~ZProcessIterator();


    //## Other Operations (specified)
      //## Operation: GetFirstBaseActivity%932194644
      //    Get the first base activity pointer.
      ZBaseActivity* GetFirstBaseActivity ();

      //## Operation: GetLastBaseActivity%932278212
      //    Get the last base activity pointer.
      ZBaseActivity* GetLastBaseActivity ();

      //## Operation: GetFirstValidActivity%932314503
      //    Get the first base activity pointer.
      ZBaseActivity* GetFirstValidActivity ();

      //## Operation: GetFirstValidBaseActivity%937152025
      //    Return the first activity pointer.
      ZBaseActivity* GetFirstValidBaseActivity ();

      //## Operation: GetLastValidActivity%932314504
      //    Get the last activity pointer.
      ZBaseActivity* GetLastValidActivity ();

      //## Operation: GetLastActivityWithinProcess%932314505
      //    Get the last base activity pointer within the same
      //    process.
      ZActivity* GetLastActivityWithinProcess ();

      //## Operation: GetParent%932278211
      //    Return the parent process of an activity.
      ZBaseActivity* GetParent (ZBaseActivity* pActivity);

      ZProcess*         GetParentProcess (ZBaseActivity* pActivity);

      //## Operation: GetNextValidActivity%932194636
      //    Get the next valid activity pointer.
      ZBaseActivity* GetNextValidActivity ();

      //## Operation: GetPreviousValidActivity%932194637
      //    Get the previous valid activity pointer.
      ZBaseActivity* GetPreviousValidActivity ();

      //## Operation: GetNextBaseActivity%933094114
      //    Get the next activity pointer.
      ZBaseActivity* GetNextBaseActivity ();

      //## Operation: GetNextValidBaseActivity%937152026
      //    Return the next activity pointer. If no, return NULL.
      ZBaseActivity* GetNextValidBaseActivity ();

      //## Operation: GetPreviousBaseActivity%933094115
      //    Get the previous activity pointer.
      ZBaseActivity* GetPreviousBaseActivity ();

      //## Operation: GetPreviousValidBaseActivity%937152027
      //    Return the previous activity pointer. If no, return NULL.
      ZBaseActivity* GetPreviousValidBaseActivity ();

      //## Operation: GetNextProcess%932194638
      //    Get the next valid activity pointer.
      ZProcess* GetNextProcess ();

      //## Operation: GetPreviousProcess%932194639
      //    Get the previous valid activity pointer.
      ZProcess* GetPreviousProcess ();

      //## Operation: StartIterator%932194640
      //    Start the iterator using an activity index.
      ZBaseActivity* StartIterator (ZBaseActivity* pActivity = NULL, ZProcess* pProcess = NULL);

      //## Operation: StartIterator%932194641
      //    Start the iterator using an activity name.
      ZBaseActivity* StartIterator (const CString& ActivityName, ZProcess* pProcess = NULL);

      //## Operation: FindActivity%932194643
      //    Finds an activity. Returns the pointer to the activity.
      virtual ZBaseActivity* FindActivity (const CString& ActivityName);

    // Additional Public Declarations
      //## begin ZProcessIterator%379031B90231.public preserve=yes
      //## end ZProcessIterator%379031B90231.public

  protected:
    // Additional Protected Declarations
      //## begin ZProcessIterator%379031B90231.protected preserve=yes
      //## end ZProcessIterator%379031B90231.protected

  private:
    //## Constructors (generated)
      ZProcessIterator(const ZProcessIterator &right);

    //## Assignment Operation (generated)
      const ZProcessIterator & operator=(const ZProcessIterator &right);

    // Data Members for Class Attributes

      //## Attribute: IteratorActivityPointer%379031CE01A5
      //    Used for iterating through activity list
      //## begin ZProcessIterator::IteratorActivityPointer%379031CE01A5.attr preserve=no  private: ZBaseActivity* {U} NULL
      ZBaseActivity* m_IteratorActivityPointer;
      //## end ZProcessIterator::IteratorActivityPointer%379031CE01A5.attr

      //## Attribute: pProcess%379034DE00DA
      //    Contains the process pointer.
      //## begin ZProcessIterator::pProcess%379034DE00DA.attr preserve=no  private: ZProcess* {U} 
      ZProcess* m_pProcess;
      //## end ZProcessIterator::pProcess%379034DE00DA.attr

    // Additional Private Declarations
      //## begin ZProcessIterator%379031B90231.private preserve=yes
      //## end ZProcessIterator%379031B90231.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZProcessIterator%379031B90231.implementation preserve=yes
      //## end ZProcessIterator%379031B90231.implementation

};

//## begin ZProcessIterator%379031B90231.postscript preserve=yes
//## end ZProcessIterator%379031B90231.postscript

// Class ZProcessIterator 

//## begin module%379033D80156.epilog preserve=yes
//## end module%379033D80156.epilog


#endif
