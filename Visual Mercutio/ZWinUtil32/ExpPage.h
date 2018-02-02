//## begin module%35B620CA026E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%35B620CA026E.cm

//## begin module%35B620CA026E.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%35B620CA026E.cp

//## Module: ExpPage%35B620CA026E; Package specification
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\ExpPage.h

#ifndef ExpPage_h
#define ExpPage_h 1

//## begin module%35B620CA026E.additionalIncludes preserve=no
//## end module%35B620CA026E.additionalIncludes

//## begin module%35B620CA026E.includes preserve=yes
#ifndef _WIN32
	#include "ZWinUtil.h"
#endif
#ifdef _WIN32
	#include "ZWinUtil32.h"
#endif
//## end module%35B620CA026E.includes

// PropPage
#include "PropPage.h"
// AppOpt
#include "zBaseLib\AppOpt.h"
//## begin module%35B620CA026E.declarations preserve=no
//## end module%35B620CA026E.declarations

//## begin module%35B620CA026E.additionalDeclarations preserve=yes
//## end module%35B620CA026E.additionalDeclarations


//## begin ZIExportPage%35B620390175.preface preserve=yes
//## end ZIExportPage%35B620390175.preface

//## Class: ZIExportPage%35B620390175
//	This page contains calculation options for the system.
//## Category: ZWinUtil library::Options classes::Property page for options%3705BE0901B4
//## Subsystem: ZWinUtil%36DEE1730346
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3705E97F020D;ZAApplicationOption { -> }

class ZIExportPage : public ZIGenericPropPage  //## Inherits: <unnamed>%370530B602FD
{
  //## begin ZIExportPage%35B620390175.initialDeclarations preserve=yes
	public:
	// Dialog Data
		//{{AFX_DATA(ZIExportPage)
	enum { IDD = IDD_EXPORTPAGE };
//	CString	m_SVMFile;
	int		m_Propagation;
	CString	m_SchemaName;
	BOOL	m_EmptyWhenZero;
	//}}AFX_DATA
  //## end ZIExportPage%35B620390175.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZIExportPage%923121241
      ZIExportPage (ZAApplicationOption* pApplicationOptions);

    //## Destructor (generated)
      ~ZIExportPage();


    //## Other Operations (specified)
      //## Operation: SaveValuesToObject%923121242
      virtual void SaveValuesToObject ();

    // Additional Public Declarations
      //## begin ZIExportPage%35B620390175.public preserve=yes
      //## end ZIExportPage%35B620390175.public

  protected:

    //## Other Operations (specified)
      //## Operation: DoDataExchange%901127512
      //	Do data exchange mecanism of MFC dialog
      virtual void DoDataExchange (CDataExchange* pDX);

    // Additional Protected Declarations
      //## begin ZIExportPage%35B620390175.protected preserve=yes
      
	// Generated message map functions
	//{{AFX_MSG(ZIExportPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();	
	
      //## end ZIExportPage%35B620390175.protected
  private:
    //## Constructors (generated)
      ZIExportPage(const ZIExportPage &right);

    //## Assignment Operation (generated)
      const ZIExportPage & operator=(const ZIExportPage &right);

    // Additional Private Declarations
      //## begin ZIExportPage%35B620390175.private preserve=yes
      //## end ZIExportPage%35B620390175.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZIExportPage%35B620390175.implementation preserve=yes
      //## end ZIExportPage%35B620390175.implementation

};

//## begin ZIExportPage%35B620390175.postscript preserve=yes
//## end ZIExportPage%35B620390175.postscript

// Class ZIExportPage 

//## begin module%35B620CA026E.epilog preserve=yes
//## end module%35B620CA026E.epilog


#endif
