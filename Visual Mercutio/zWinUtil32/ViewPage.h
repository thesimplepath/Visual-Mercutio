//## begin module%334FC463032F.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC463032F.cm

//## begin module%334FC463032F.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%334FC463032F.cp

//## Module: ViewPage%334FC463032F; Package specification
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\ViewPage.h

#ifndef ViewPage_h
#define ViewPage_h 1

//## begin module%334FC463032F.additionalIncludes preserve=no
//## end module%334FC463032F.additionalIncludes

//## begin module%334FC463032F.includes preserve=yes
#ifndef _WIN32
    #include "ZWinUtil.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32.h"
#endif
//## end module%334FC463032F.includes

// PropPage
#include "PropPage.h"
// AppOpt
#include "zBaseLib\AppOpt.h"
//## begin module%334FC463032F.declarations preserve=no
//## end module%334FC463032F.declarations

//## begin module%334FC463032F.additionalDeclarations preserve=yes
//## end module%334FC463032F.additionalDeclarations


//## begin ZIViewPage%334FC4610072.preface preserve=yes
//## end ZIViewPage%334FC4610072.preface

//## Class: ZIViewPage%334FC4610072
//    This page contains view options for the system.
//## Category: ZWinUtil library::Options classes::Property page for options%3705BE0901B4
//## Subsystem: ZWinUtil%36DEE1730346
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3705E97B0239;ZAApplicationOption { -> }

class ZIViewPage : public ZIGenericPropPage  //## Inherits: <unnamed>%370530CC0222
{
  //## begin ZIViewPage%334FC4610072.initialDeclarations preserve=yes
    public:
    // Dialog Data
        //{{AFX_DATA(ZIViewPage)
    enum { IDD = IDD_VIEWPAGE };
    BOOL    m_bCalculatedField;
    BOOL    m_bShowHiddenField;
    BOOL    m_bAnimationShow;
    BOOL    m_bShowBoundsRect;
    BOOL    m_AutomaticCreateFieldName;
    //}}AFX_DATA
  //## end ZIViewPage%334FC4610072.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZIViewPage%923121235
      ZIViewPage (ZAApplicationOption* pApplicationOptions);

    //## Destructor (generated)
      ~ZIViewPage();


    //## Other Operations (specified)
      //## Operation: SaveValuesToObject%923121236
      virtual void SaveValuesToObject ();

    // Additional Public Declarations
      //## begin ZIViewPage%334FC4610072.public preserve=yes
      //## end ZIViewPage%334FC4610072.public

  protected:

    //## Other Operations (specified)
      //## Operation: DoDataExchange%827992043
      //    Do data exchange mecanism of MFC dialog
      virtual void DoDataExchange (CDataExchange* pDX);

    // Additional Protected Declarations
      //## begin ZIViewPage%334FC4610072.protected preserve=yes
      
    // Generated message map functions
    //{{AFX_MSG(ZIViewPage)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
    virtual void OnOK();    
    
      //## end ZIViewPage%334FC4610072.protected
  private:
    //## Constructors (generated)
      ZIViewPage(const ZIViewPage &right);

    //## Assignment Operation (generated)
      const ZIViewPage & operator=(const ZIViewPage &right);

    // Additional Private Declarations
      //## begin ZIViewPage%334FC4610072.private preserve=yes
      //## end ZIViewPage%334FC4610072.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZIViewPage%334FC4610072.implementation preserve=yes
      //## end ZIViewPage%334FC4610072.implementation

};

//## begin ZIViewPage%334FC4610072.postscript preserve=yes
//## end ZIViewPage%334FC4610072.postscript

// Class ZIViewPage 

//## begin module%334FC463032F.epilog preserve=yes
//## end module%334FC463032F.epilog


#endif
