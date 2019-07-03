//## begin module%35B620AF0085.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%35B620AF0085.cm

//## begin module%35B620AF0085.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%35B620AF0085.cp

//## Module: NavPage%35B620AF0085; Package specification
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\NavPage.h

#ifndef NavPage_h
#define NavPage_h 1

//## begin module%35B620AF0085.additionalIncludes preserve=no
//## end module%35B620AF0085.additionalIncludes

//## begin module%35B620AF0085.includes preserve=yes
#ifndef _WIN32
    #include "ZWinUtil.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32.h"
#endif
//## end module%35B620AF0085.includes

// PropPage
#include "PropPage.h"
// AppOpt
#include "zBaseLib\AppOpt.h"
//## begin module%35B620AF0085.declarations preserve=no
//## end module%35B620AF0085.declarations

//## begin module%35B620AF0085.additionalDeclarations preserve=yes
//## end module%35B620AF0085.additionalDeclarations


//## begin ZINavigationPage%35B61F1D02AD.preface preserve=yes
//## end ZINavigationPage%35B61F1D02AD.preface

//## Class: ZINavigationPage%35B61F1D02AD
//    This page contains calculation options for the system.
//## Category: ZWinUtil library::Options classes::Property page for options%3705BE0901B4
//## Subsystem: ZWinUtil%36DEE1730346
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3705E98202ED;ZAApplicationOption { -> }

class ZINavigationPage : public ZIGenericPropPage  //## Inherits: <unnamed>%370530B903BF
{
  //## begin ZINavigationPage%35B61F1D02AD.initialDeclarations preserve=yes
    public:
    // Dialog Data
        //{{AFX_DATA(ZINavigationPage)
    enum { IDD = IDD_NAVIGATIONPAGE };
    BOOL    m_GoNextEdit;
    //}}AFX_DATA
  //## end ZINavigationPage%35B61F1D02AD.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZINavigationPage%923121243
      ZINavigationPage (ZAApplicationOption* pApplicationOptions);

    //## Destructor (generated)
      ~ZINavigationPage();


    //## Other Operations (specified)
      //## Operation: SaveValuesToObject%923121244
      virtual void SaveValuesToObject ();

    // Additional Public Declarations
      //## begin ZINavigationPage%35B61F1D02AD.public preserve=yes
      //## end ZINavigationPage%35B61F1D02AD.public

  protected:

    //## Other Operations (specified)
      //## Operation: DoDataExchange%901127513
      //    Do data exchange mecanism of MFC dialog
      virtual void DoDataExchange (CDataExchange* pDX);

    // Additional Protected Declarations
      //## begin ZINavigationPage%35B61F1D02AD.protected preserve=yes
      
    // Generated message map functions
    //{{AFX_MSG(ZINavigationPage)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
    virtual void OnOK();    
    
      //## end ZINavigationPage%35B61F1D02AD.protected
  private:
    //## Constructors (generated)
      ZINavigationPage(const ZINavigationPage &right);

    //## Assignment Operation (generated)
      const ZINavigationPage & operator=(const ZINavigationPage &right);

    // Additional Private Declarations
      //## begin ZINavigationPage%35B61F1D02AD.private preserve=yes
      //## end ZINavigationPage%35B61F1D02AD.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZINavigationPage%35B61F1D02AD.implementation preserve=yes
      //## end ZINavigationPage%35B61F1D02AD.implementation

};

//## begin ZINavigationPage%35B61F1D02AD.postscript preserve=yes
//## end ZINavigationPage%35B61F1D02AD.postscript

// Class ZINavigationPage 

//## begin module%35B620AF0085.epilog preserve=yes
//## end module%35B620AF0085.epilog


#endif
