//## begin module%3705B62C032C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3705B62C032C.cm

//## begin module%3705B62C032C.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%3705B62C032C.cp

//## Module: BPropSht%3705B62C032C; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\BPropSht.h

#ifndef BPropSht_h
#define BPropSht_h 1

//## begin module%3705B62C032C.additionalIncludes preserve=no
//## end module%3705B62C032C.additionalIncludes

//## begin module%3705B62C032C.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%3705B62C032C.includes

// PropPage
#include "PropPage.h"
// Mfc
#include "Mfc.h"
//## begin module%3705B62C032C.declarations preserve=no
//## end module%3705B62C032C.declarations

//## begin module%3705B62C032C.additionalDeclarations preserve=yes
#ifdef _ZWINUTIL32EXPORT
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
//## end module%3705B62C032C.additionalDeclarations


//## begin ZIBasePropSheet%3705B57B035A.preface preserve=yes
//## end ZIBasePropSheet%3705B57B035A.preface

//## Class: ZIBasePropSheet%3705B57B035A
//## Category: ZUtil library::Options & Configuration\rclasses%35D41E2C02C0
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3705B88D0332;ZIGenericPropPage { -> }

class AFX_EXT_CLASS ZIBasePropSheet : public CPropertySheet  //## Inherits: <unnamed>%3705B58701E4
{
  //## begin ZIBasePropSheet%3705B57B035A.initialDeclarations preserve=yes
	DECLARE_DYNAMIC(ZIBasePropSheet)
  //## end ZIBasePropSheet%3705B57B035A.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZIBasePropSheet%923121219
      ZIBasePropSheet (int DefaultTab = 0);

      //## Operation: ZIBasePropSheet%923598941
      ZIBasePropSheet (UINT nIDCaption, int DefaultTab = 0);

      //## Operation: ZIBasePropSheet%923598942
      ZIBasePropSheet (LPCTSTR pszCaption, int DefaultTab = 0);

    //## Destructor (generated)
      ~ZIBasePropSheet();


    //## Other Operations (specified)
      //## Operation: GetCurPage%923121220
      int GetCurPage () const;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: PageArray%3705B5D8024F
      CObArray& GetPageArray ();

    // Additional Public Declarations
      //## begin ZIBasePropSheet%3705B57B035A.public preserve=yes
		int  FindPropertyPage( CPropertyPage* pPage );
		bool DeletePropertyPage( CPropertyPage* pPage );
		bool DeletePropertyPageAt( size_t Index );
		void DeleteAllPropertyPages();
      //## end ZIBasePropSheet%3705B57B035A.public

  protected:
    // Data Members for Class Attributes

      //## begin ZIBasePropSheet::PageArray%3705B5D8024F.attr preserve=no  public: CObArray {U} 
      CObArray m_PageArray;
      //## end ZIBasePropSheet::PageArray%3705B5D8024F.attr

    // Additional Protected Declarations
      //## begin ZIBasePropSheet%3705B57B035A.protected preserve=yes
	// Generated message map functions
	//{{AFX_MSG(ZIBasePropSheet)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
      //## end ZIBasePropSheet%3705B57B035A.protected
  private:
    //## Constructors (generated)
      ZIBasePropSheet(const ZIBasePropSheet &right);

    //## Assignment Operation (generated)
      const ZIBasePropSheet & operator=(const ZIBasePropSheet &right);

    // Additional Private Declarations
      //## begin ZIBasePropSheet%3705B57B035A.private preserve=yes
      //## end ZIBasePropSheet%3705B57B035A.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZIBasePropSheet%3705B57B035A.implementation preserve=yes
      //## end ZIBasePropSheet%3705B57B035A.implementation

};

//## begin ZIBasePropSheet%3705B57B035A.postscript preserve=yes
//## end ZIBasePropSheet%3705B57B035A.postscript

// Class ZIBasePropSheet 

//## Get and Set Operations for Class Attributes (inline)

inline CObArray& ZIBasePropSheet::GetPageArray ()
{
  //## begin ZIBasePropSheet::GetPageArray%3705B5D8024F.get preserve=no
  return m_PageArray;
  //## end ZIBasePropSheet::GetPageArray%3705B5D8024F.get
}

//## begin module%3705B62C032C.epilog preserve=yes
//## end module%3705B62C032C.epilog


#endif
