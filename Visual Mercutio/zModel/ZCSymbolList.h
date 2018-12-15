//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//    Source file: ZCSymbolList.h

#ifndef ZCSymbolList_h
#define ZCSymbolList_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\ZIListCtrl.h"


#ifdef _ZMODELEXPORT
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


class AFX_EXT_CLASS ZCSymbolList : public ZIListCtrl  
{

    DECLARE_DYNAMIC(ZCSymbolList)

  public:
      ZCSymbolList ();
      virtual ~ZCSymbolList();

      CODSymbolComponent*    GetSelectedSymbol();


      int    Initialize (CODComponentSet* pSet, UINT nIDRes);
      int    Refresh ();

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCSymbolList)
    //}}AFX_VIRTUAL
  protected:
    //{{AFX_MSG(ZCSymbolList)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  private:
    ZCSymbolList(const ZCSymbolList &right);
    const    ZCSymbolList & operator=(const ZCSymbolList &right);

    void    BuildColumns(UINT nIDRes);
    int        GetItemIndex( CODSymbolComponent* pSymbol );

  private: //## implementation
        CODComponentSet*    m_pSet;
        BOOL                m_ColumnsBuilt;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif      // ZCSymbolList_h
