#ifndef GenPage_h
#define GenPage_h 1

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PropPage.h"
#include "zBaseLib\AppOpt.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//## Class: ZIGeneralPage%334FC461003C
//    This page contains general options for the system.
//## Category: ZWinUtil library::Options classes::Property page for options%3705BE0901B4
//## Subsystem: ZWinUtil%36DEE1730346
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3705E979010A;ZAApplicationOption { -> }

class AFX_EXT_CLASS ZIGeneralPage : public ZIGenericPropPage  //## Inherits: <unnamed>%334FC461003D
{
  //## begin ZIGeneralPage%334FC461003C.initialDeclarations preserve=yes
    public:
    // Dialog Data
        //{{AFX_DATA(ZIGeneralPage)
    enum { IDD = IDD_SYSOPTIONPAGE };
        CButton    m_btnMaximizeForm;
        CButton    m_btnShowWelcome;
        CButton    m_btnReloadLastFile;
        CButton    m_btnStartupOpenFile;
        CButton    m_btnScreenPos;
    BOOL    m_DontShowTaskList;
    BOOL    m_DontShowTips;
    BOOL    m_ForceNetwork;
    //}}AFX_DATA
  //## end ZIGeneralPage%334FC461003C.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZIGeneralPage%923121234
      ZIGeneralPage (ZAApplicationOption* pApplicationOptions);

    //## Destructor (generated)
      ~ZIGeneralPage();


    //## Other Operations (specified)
      //## Operation: SaveValuesToObject%923121226
      virtual void SaveValuesToObject ();

    // Additional Public Declarations
      //## begin ZIGeneralPage%334FC461003C.public preserve=yes
      //## end ZIGeneralPage%334FC461003C.public

  protected:

    //## Other Operations (specified)
      //## Operation: DoDataExchange%827992043
      //    Do data exchange mecanism of MFC dialog
      virtual void DoDataExchange (CDataExchange* pDX);

    // Additional Protected Declarations
      //## begin ZIGeneralPage%334FC461003C.protected preserve=yes
      
    // Generated message map functions
    //{{AFX_MSG(ZIGeneralPage)
//    afx_msg void OnSavesettings();
    virtual BOOL OnInitDialog();
    afx_msg void OnReloadLastFile();
    afx_msg void OnStartupOpenFile();
    afx_msg void OnShowWelcomeScreen();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
    virtual void OnOK();    
      //## end ZIGeneralPage%334FC461003C.protected
  private:
    //## Constructors (generated)
      ZIGeneralPage(const ZIGeneralPage &right);

    //## Assignment Operation (generated)
      const ZIGeneralPage & operator=(const ZIGeneralPage &right);

    // Additional Private Declarations
      //## begin ZIGeneralPage%334FC461003C.private preserve=yes
      //## end ZIGeneralPage%334FC461003C.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZIGeneralPage%334FC461003C.implementation preserve=yes
      //## end ZIGeneralPage%334FC461003C.implementation

};

//## begin ZIGeneralPage%334FC461003C.postscript preserve=yes
//#undef  AFX_DATA
//#define AFX_DATA
//## end ZIGeneralPage%334FC461003C.postscript

// Class ZIGeneralPage 

//## begin module%334FC46302C2.epilog preserve=yes
//## end module%334FC46302C2.epilog


#endif
