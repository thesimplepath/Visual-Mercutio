#ifndef SysOpt32_h
#define SysOpt32_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_BasePropSheet.h"

// forward class declaration
class ZAApplicationOption;

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


unsigned int GeneralOptionPage = 0x0001;
unsigned int CalculationOptionPage = 0x0002;
unsigned int ViewOptionPage = 0x0004;
unsigned int NavigationOptionPage = 0x0008;
unsigned int ExportOptionPage = 0x0010;
unsigned int ViewReducedOptionPage = 0x0020;
//unsigned int GlobalOptionPage = 0x0020;

class AFX_EXT_CLASS ZISystemOption : public PSS_BasePropSheet
{
//    DECLARE_DYNAMIC(ZISystemOption)

  public:
      ZISystemOption(ZAApplicationOption* ApplicationOptions, unsigned int PageOptions = GeneralOptionPage);
      ~ZISystemOption();
      // Simulate the DoModal for capturing the OnOk.
      int    DoModal();

// Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(ZIOption)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

  private:
      ZISystemOption(const ZISystemOption &right);
      const ZISystemOption & operator=(const ZISystemOption &right);

  private:  
      ZAApplicationOption* m_pApplicationOptions;
      unsigned int m_PageOptions;
};





#endif
