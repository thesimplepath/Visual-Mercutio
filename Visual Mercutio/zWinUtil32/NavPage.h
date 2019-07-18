#ifndef NavPage_h
#define NavPage_h 1

// processsoft
#include "zBaseLib\AppOpt.h"
#include "PropPage.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

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
