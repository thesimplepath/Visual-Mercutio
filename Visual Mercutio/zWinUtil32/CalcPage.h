//## begin module%334FC463032C.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC463032C.cm

//## begin module%334FC463032C.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%334FC463032C.cp

//## Module: CalcPage%334FC463032C; Package specification
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\CalcPage.h

#ifndef CalcPage_h
#define CalcPage_h 1

//## begin module%334FC463032C.additionalIncludes preserve=no
//## end module%334FC463032C.additionalIncludes

//## begin module%334FC463032C.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#ifndef _WIN32
    #include "ZWinUtil.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32.h"
#endif
//## end module%334FC463032C.includes

// PropPage
#include "PropPage.h"
// AppOpt
#include "zBaseLib\AppOpt.h"
//## begin module%334FC463032C.declarations preserve=no
//## end module%334FC463032C.declarations

//## begin module%334FC463032C.additionalDeclarations preserve=yes
//## end module%334FC463032C.additionalDeclarations


//## begin ZICalculationPage%334FC4610046.preface preserve=yes
#ifdef _ZWINUTIL32EXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

#undef  AFX_DATA
#define AFX_DATA AFX_EXT_CLASS

//## end ZICalculationPage%334FC4610046.preface

//## Class: ZICalculationPage%334FC4610046
//    This page contains calculation options for the system.
//## Category: ZWinUtil library::Options classes::Property page for options%3705BE0901B4
//## Subsystem: ZWinUtil%36DEE1730346
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3705E98800E3;ZAApplicationOption { -> }

class ZICalculationPage : public ZIGenericPropPage  //## Inherits: <unnamed>%334FC461006E
{
  //## begin ZICalculationPage%334FC4610046.initialDeclarations preserve=yes
    public:
    // Dialog Data
        //{{AFX_DATA(ZICalculationPage)
    enum { IDD = IDD_CALCOPTION };
    BOOL    m_bAutoCalculate;
    //}}AFX_DATA
  //## end ZICalculationPage%334FC4610046.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZICalculationPage%923121237
      ZICalculationPage (ZAApplicationOption* pApplicationOptions);

    //## Destructor (generated)
      ~ZICalculationPage();


    //## Other Operations (specified)
      //## Operation: SaveValuesToObject%923121238
      virtual void SaveValuesToObject ();

    // Additional Public Declarations
      //## begin ZICalculationPage%334FC4610046.public preserve=yes
    BOOL    GetAutoCalculate() const { return m_bAutoCalculate; };
      //## end ZICalculationPage%334FC4610046.public
  protected:

    //## Other Operations (specified)
      //## Operation: DoDataExchange%827992043
      //    Do data exchange mecanism of MFC dialog
      virtual void DoDataExchange (CDataExchange* pDX);

    // Additional Protected Declarations
      //## begin ZICalculationPage%334FC4610046.protected preserve=yes
      
    // Generated message map functions
    //{{AFX_MSG(ZICalculationPage)
    virtual BOOL OnInitDialog();
    afx_msg void OnAutocalculation();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
    virtual void OnOK();    
    
      //## end ZICalculationPage%334FC4610046.protected
  private:
    //## Constructors (generated)
      ZICalculationPage(const ZICalculationPage &right);

    //## Assignment Operation (generated)
      const ZICalculationPage & operator=(const ZICalculationPage &right);

    // Additional Private Declarations
      //## begin ZICalculationPage%334FC4610046.private preserve=yes
      //## end ZICalculationPage%334FC4610046.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZICalculationPage%334FC4610046.implementation preserve=yes
      //## end ZICalculationPage%334FC4610046.implementation

};

//## begin ZICalculationPage%334FC4610046.postscript preserve=yes
#undef  AFX_DATA
#define AFX_DATA
//## end ZICalculationPage%334FC4610046.postscript

// Class ZICalculationPage 

//## begin module%334FC463032C.epilog preserve=yes
//## end module%334FC463032C.epilog


#endif
