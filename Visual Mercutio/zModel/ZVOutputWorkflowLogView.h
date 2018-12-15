#if !defined(AFX_ZVOutputWorkflowLogView_H__8D6DF672_6E58_4F75_A154_14FFDB5EE0F1__INCLUDED_)
#define AFX_ZVOutputWorkflowLogView_H__8D6DF672_6E58_4F75_A154_14FFDB5EE0F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVOutputWorkflowLogView.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\ZVOutputView.h"

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
// ZVOutputWorkflowLogView view

class AFX_EXT_CLASS ZVOutputWorkflowLogView : public ZVOutputView
{
public:

    DECLARE_DYNAMIC( ZVOutputWorkflowLogView )

    ZVOutputWorkflowLogView();           // protected constructor used by dynamic creation
    virtual ~ZVOutputWorkflowLogView();

// Operations
public:

// Generated message map functions
protected:

    //{{AFX_MSG(ZVOutputWorkflowLogView)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    // Call back function base on list events
    virtual void OnSelChanged();
    virtual void OnDoubleClick();
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVOutputWorkflowLogView_H__8D6DF672_6E58_4F75_A154_14FFDB5EE0F1__INCLUDED_)