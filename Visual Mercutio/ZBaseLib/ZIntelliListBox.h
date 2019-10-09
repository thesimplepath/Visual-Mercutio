#if !defined(AFX_ZINTELLILISTBOX_H__85036D1D_E0AF_4249_9C4A_469775DEE39B__INCLUDED_)
#define AFX_ZINTELLILISTBOX_H__85036D1D_E0AF_4249_9C4A_469775DEE39B__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// forward class declaration
class PSS_IntelliEdit;

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class ZIntelliListBox : public CListBox
{
public:
    ZIntelliListBox(PSS_IntelliEdit* pEditCtrl = NULL);

    virtual ~ZIntelliListBox();

    virtual void SetEditControl(PSS_IntelliEdit* pEditCtrl);

protected:
    /// ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIntelliListBox)
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

    /// Generated message map functions
    //{{AFX_MSG(ZIntelliListBox)
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    PSS_IntelliEdit* m_pEditCtrl;
    int              m_CurrentSelectionOnDown;

    void TranslateSelectionToEditControl();
};

#endif
