//## begin module%37E4CD2D023D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%37E4CD2D023D.cm

//## begin module%37E4CD2D023D.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%37E4CD2D023D.cp

//## Module: ZBNotes%37E4CD2D023D; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZBNotes.h

#ifndef ZBNotes_h
#define ZBNotes_h 1

//## begin module%37E4CD2D023D.additionalIncludes preserve=no
//## end module%37E4CD2D023D.additionalIncludes

//## begin module%37E4CD2D023D.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%37E4CD2D023D.includes

// ZUser
#include "ZUser.h"
// Mfc
#include "Mfc.h"
//## begin module%37E4CD2D023D.declarations preserve=no
//## end module%37E4CD2D023D.declarations

//## begin module%37E4CD2D023D.additionalDeclarations preserve=yes
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
//## end module%37E4CD2D023D.additionalDeclarations


//## Class: ZBNotes%37E4CC9F024D
//	Defines a notes
//## Category: ZBaseLib::Note classes%37E4CC89007E
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%37E4CC9F024F;ZUser { -> }

class AFX_EXT_CLASS ZBNotes : public CObject  //## Inherits: <unnamed>%37E4CC9F024E
{
  //## begin ZBNotes%37E4CC9F024D.initialDeclarations preserve=yes
  //## end ZBNotes%37E4CC9F024D.initialDeclarations

  public:
    //## Constructors (generated)
      ZBNotes(const ZBNotes &right);

    //## Constructors (specified)
      //## Operation: ZBNotes%937741717
      ZBNotes (CString Comment = "", CString Username = "");

    //## Destructor (generated)
      virtual ~ZBNotes();

    //## Assignment Operation (generated)
      const ZBNotes & operator=(const ZBNotes &right);


    //## Other Operations (specified)
      //## Operation: Clone%937741718
      ZBNotes* Clone ();

      //## Operation: ClearNotes%937741722
      //	Clear the notes
      void ClearNotes ();

      //## Operation: ClearComment%937741723
      //	Clear the note's comment
      void ClearComment ();

      //## Operation: ClearUsername%937741724
      //	Clear the note's username.
      void ClearUsername ();

      //## Operation: GetFormatedNotes%937741725
      //	Return the notes with \r\n char.
      CString GetFormatedNotes (CRect* pRect = NULL);

      //## Operation: operator >>%937741719
      //	Store from the archive to the object Notes.
      AFX_EXT_API friend CArchive& operator >> (CArchive& ar, ZBNotes& Notes);

      //## Operation: operator <<%937741720
      //	Store the object Notes to the archive.
      AFX_EXT_API friend CArchive& operator << (CArchive& ar, ZBNotes& Notes);

      //## Operation: Serialize%937741721
      //	Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Comment%37E4CC9F025F
      //	Contains the comment
      const CString& GetComment () const;
      void SetComment (const CString& value);

      //## Attribute: Username%37E4CC9F0260
      //	Contains the username of the note.
      const CString GetUsername () const;
      void SetUsername (CString value);

    // Additional Public Declarations
      //## begin ZBNotes%37E4CC9F024D.public preserve=yes
      //## end ZBNotes%37E4CC9F024D.public

  protected:
    // Additional Protected Declarations
      //## begin ZBNotes%37E4CC9F024D.protected preserve=yes
	DECLARE_SERIAL(ZBNotes)
      //## end ZBNotes%37E4CC9F024D.protected

  private:
    // Data Members for Class Attributes

      //## begin ZBNotes::Comment%37E4CC9F025F.attr preserve=no  public: CString {U} 
      CString m_Comment;
      //## end ZBNotes::Comment%37E4CC9F025F.attr

      //## begin ZBNotes::Username%37E4CC9F0260.attr preserve=no  public: CString {U} 
      CString m_Username;
      //## end ZBNotes::Username%37E4CC9F0260.attr

    // Additional Private Declarations
      //## begin ZBNotes%37E4CC9F024D.private preserve=yes
      //## end ZBNotes%37E4CC9F024D.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZBNotes%37E4CC9F024D.implementation preserve=yes
      //## end ZBNotes%37E4CC9F024D.implementation

};

//## begin ZBNotes%37E4CC9F024D.postscript preserve=yes
//## end ZBNotes%37E4CC9F024D.postscript

// Class ZBNotes 

//## Get and Set Operations for Class Attributes (inline)

inline const CString& ZBNotes::GetComment () const
{
  //## begin ZBNotes::GetComment%37E4CC9F025F.get preserve=no
  return m_Comment;
  //## end ZBNotes::GetComment%37E4CC9F025F.get
}

inline void ZBNotes::SetComment (const CString& value)
{
  //## begin ZBNotes::SetComment%37E4CC9F025F.set preserve=no
  m_Comment = value;
  //## end ZBNotes::SetComment%37E4CC9F025F.set
}

inline const CString ZBNotes::GetUsername () const
{
  //## begin ZBNotes::GetUsername%37E4CC9F0260.get preserve=no
  return m_Username;
  //## end ZBNotes::GetUsername%37E4CC9F0260.get
}

inline void ZBNotes::SetUsername (CString value)
{
  //## begin ZBNotes::SetUsername%37E4CC9F0260.set preserve=no
  m_Username = value;
  //## end ZBNotes::SetUsername%37E4CC9F0260.set
}

//## begin module%37E4CD2D023D.epilog preserve=yes
//## end module%37E4CD2D023D.epilog


#endif
