#if !defined(AFX_ZVOutputSymbolLogView_H__8D6DF672_6E58_4F75_A154_14FFDB5EE0F1__INCLUDED_)
#define AFX_ZVOutputSymbolLogView_H__8D6DF672_6E58_4F75_A154_14FFDB5EE0F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVOutputSymbolLogView.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\PSS_OutputView.h"

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

/////////////////////////////////////////////////////////////////////////////
// ZVOutputSymbolLogView view

class AFX_EXT_CLASS ZVOutputSymbolLogView : public PSS_OutputView
{
public:
    DECLARE_DYNAMIC( ZVOutputSymbolLogView )

    ZVOutputSymbolLogView();           // protected constructor used by dynamic creation
    virtual ~ZVOutputSymbolLogView();

// Operations
public:

// Generated message map functions
protected:

    //{{AFX_MSG(ZVOutputSymbolLogView)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    // Call back function base on list events
    virtual void OnSelChanged();
    virtual void OnDoubleClick();
};

#endif
