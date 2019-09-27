#if !defined(_ZCPROPERTYDESCRIPTION_H__)
#define _ZCPROPERTYDESCRIPTION_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZCPropertyDescription.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_Observer.h"

/////////////////////////////////////////////////////////////////////////////
// Forward declaration
class ZBProperty;
class PSS_ObserverMsg;



#ifdef _ZPTYMGREXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


/////////////////////////////////////////////////////////////////////////////
// ZCPropertyDescription window

class AFX_EXT_CLASS ZCPropertyDescription : public CStatic, public PSS_Observer
{
    // Construction
public:
    ZCPropertyDescription();

    // Operations
public:
    // Observer call back
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    // Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ZCPropertyDescription)
        //}}AFX_VIRTUAL

    // Implementation
public:
    virtual ~ZCPropertyDescription();

    // Generated message map functions
protected:
    //{{AFX_MSG(ZCPropertyDescription)
    afx_msg void OnPaint();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()


private:
    void EmptyControlData();
    void UpdateControlData(ZBProperty* pProp);


private:
    CString m_Title;
    CString m_Description;

    COLORREF m_crBackground;
    COLORREF m_crText;
    CFont m_Font;
    CFont m_FontBold;

};

#endif
