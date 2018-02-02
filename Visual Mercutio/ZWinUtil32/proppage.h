//## begin module%3705B86B0148.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3705B86B0148.cm

//## begin module%3705B86B0148.cp preserve=no
//## end module%3705B86B0148.cp

//## Module: PropPage%3705B86B0148; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\PropPage.h

#ifndef PropPage_h
#define PropPage_h 1

//## begin module%3705B86B0148.additionalIncludes preserve=no
//## end module%3705B86B0148.additionalIncludes

//## begin module%3705B86B0148.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%3705B86B0148.includes

// Mfc
#include "Mfc.h"
//## begin module%3705B86B0148.declarations preserve=no
//## end module%3705B86B0148.declarations

//## begin module%3705B86B0148.additionalDeclarations preserve=yes
//## end module%3705B86B0148.additionalDeclarations


//## begin ZIGenericPropPage%37053093022A.preface preserve=yes
#ifdef _ZWINUTIL32EXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//## end ZIGenericPropPage%37053093022A.preface

//## Class: ZIGenericPropPage%37053093022A
//## Category: ZUtil library::Tools classes%35D41E2C02C0
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZIGenericPropPage : public CPropertyPage  //## Inherits: <unnamed>%370530A802A2
{
  //## begin ZIGenericPropPage%37053093022A.initialDeclarations preserve=yes
  //## end ZIGenericPropPage%37053093022A.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZIGenericPropPage%923121221
      ZIGenericPropPage (UINT nIDTemplate, CObject* pObj);

    //## Destructor (generated)
      ~ZIGenericPropPage();


    //## Other Operations (specified)
      //## Operation: GetObject%923121222
      CObject& GetObject ();

      //## Operation: HasBeenInitialized%923121223
      BOOL HasBeenInitialized () const;

      //## Operation: SetInitialized%923121224
      void SetInitialized ();

      //## Operation: SaveValuesToObject%923121225
      virtual void SaveValuesToObject () = 0;

    // Additional Public Declarations
      //## begin ZIGenericPropPage%37053093022A.public preserve=yes
      virtual BOOL IsOK() { return TRUE; };	// By default return true
      //## end ZIGenericPropPage%37053093022A.public

  protected:
    // Additional Protected Declarations
      //## begin ZIGenericPropPage%37053093022A.protected preserve=yes
	// Generated message map functions
	//{{AFX_MSG(ZIGenericPropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
      //## end ZIGenericPropPage%37053093022A.protected
  private:
    //## Constructors (generated)
      ZIGenericPropPage(const ZIGenericPropPage &right);

    //## Assignment Operation (generated)
      const ZIGenericPropPage & operator=(const ZIGenericPropPage &right);

    // Data Members for Class Attributes

      //## Attribute: pObj%3705B7B30176
      //## begin ZIGenericPropPage::pObj%3705B7B30176.attr preserve=no  private: CObject* {U} 
      CObject* m_pObj;
      //## end ZIGenericPropPage::pObj%3705B7B30176.attr

      //## Attribute: bHasBeenInitialized%3705B7D10241
      //## begin ZIGenericPropPage::bHasBeenInitialized%3705B7D10241.attr preserve=no  private: BOOL {U} 
      BOOL m_bHasBeenInitialized;
      //## end ZIGenericPropPage::bHasBeenInitialized%3705B7D10241.attr

    // Additional Private Declarations
      //## begin ZIGenericPropPage%37053093022A.private preserve=yes
      //## end ZIGenericPropPage%37053093022A.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZIGenericPropPage%37053093022A.implementation preserve=yes
      //## end ZIGenericPropPage%37053093022A.implementation

};

//## begin ZIGenericPropPage%37053093022A.postscript preserve=yes
//## end ZIGenericPropPage%37053093022A.postscript

// Class ZIGenericPropPage 


//## Other Operations (inline)
inline CObject& ZIGenericPropPage::GetObject ()
{
  //## begin ZIGenericPropPage::GetObject%923121222.body preserve=yes
  	return *m_pObj;
  //## end ZIGenericPropPage::GetObject%923121222.body
}

inline BOOL ZIGenericPropPage::HasBeenInitialized () const
{
  //## begin ZIGenericPropPage::HasBeenInitialized%923121223.body preserve=yes
  	return m_bHasBeenInitialized;
  //## end ZIGenericPropPage::HasBeenInitialized%923121223.body
}

inline void ZIGenericPropPage::SetInitialized ()
{
  //## begin ZIGenericPropPage::SetInitialized%923121224.body preserve=yes
  	m_bHasBeenInitialized = TRUE;
  //## end ZIGenericPropPage::SetInitialized%923121224.body
}

//## begin module%3705B86B0148.epilog preserve=yes
//## end module%3705B86B0148.epilog


#endif
