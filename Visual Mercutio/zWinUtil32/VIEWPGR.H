#ifndef ViewPgR_h
#define ViewPgR_h 1

// processsoft
#include "zBaseLib\AppOpt.h"
#include "PropPage.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

//## Class: ZIViewPageReduced%334FC4610072
//    This page contains view options for the system.
//## Category: ZWinUtil library::Options classes::Property page for options%3705BE0901B4
//## Subsystem: ZWinUtil%36DEE1730346
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3705E97B0239;ZAApplicationOption { -> }

class ZIViewPageReduced : public ZIGenericPropPage  //## Inherits: <unnamed>%370530CC0222
{
  //## begin ZIViewPageReduced%334FC4610072.initialDeclarations preserve=yes
    public:
    // Dialog Data
        //{{AFX_DATA(ZIViewPageReduced)
    enum { IDD = IDD_VIEWPAGE_REDUCED };
    BOOL    m_bCalculatedField;
    BOOL    m_bShowHiddenField;
    BOOL    m_bAnimationShow;
    //}}AFX_DATA
  //## end ZIViewPageReduced%334FC4610072.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZIViewPageReduced%923121235
      ZIViewPageReduced (ZAApplicationOption* pApplicationOptions);

    //## Destructor (generated)
      ~ZIViewPageReduced();


    //## Other Operations (specified)
      //## Operation: SaveValuesToObject%923121236
      virtual void SaveValuesToObject ();

    // Additional Public Declarations
      //## begin ZIViewPageReduced%334FC4610072.public preserve=yes
      //## end ZIViewPageReduced%334FC4610072.public

  protected:

    //## Other Operations (specified)
      //## Operation: DoDataExchange%827992043
      //    Do data exchange mecanism of MFC dialog
      virtual void DoDataExchange (CDataExchange* pDX);

    // Additional Protected Declarations
      //## begin ZIViewPageReduced%334FC4610072.protected preserve=yes
      
    // Generated message map functions
    //{{AFX_MSG(ZIViewPageReduced)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
    virtual void OnOK();    
    
      //## end ZIViewPageReduced%334FC4610072.protected
  private:
    //## Constructors (generated)
      ZIViewPageReduced(const ZIViewPageReduced &right);

    //## Assignment Operation (generated)
      const ZIViewPageReduced & operator=(const ZIViewPageReduced &right);

    // Additional Private Declarations
      //## begin ZIViewPageReduced%334FC4610072.private preserve=yes
      //## end ZIViewPageReduced%334FC4610072.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZIViewPageReduced%334FC4610072.implementation preserve=yes
      //## end ZIViewPageReduced%334FC4610072.implementation

};

//## begin ZIViewPageReduced%334FC4610072.postscript preserve=yes
//## end ZIViewPageReduced%334FC4610072.postscript

// Class ZIViewPageReduced 

//## begin module%334FC463032F.epilog preserve=yes
//## end module%334FC463032F.epilog


#endif
