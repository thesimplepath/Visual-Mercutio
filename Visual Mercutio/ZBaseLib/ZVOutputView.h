// ZVOutputView.h : header file

#if !defined(AFX_ZVOUTPUTVIEW_H__34183E9D_2920_4176_B402_7CD142E62933__INCLUDED_)
#define AFX_ZVOUTPUTVIEW_H__34183E9D_2920_4176_B402_7CD142E62933__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _AFXEXT
// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
#endif

#include "ZILog.h"
#include "PSS_Subject.h"
#include "PSS_Observer.h"

#ifdef _ZBASELIBEXPORT
// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 28 septembre 2005 - Ajout des décorations unicode _T(), nettoyage du code inutile.(En commentaires)

/////////////////////////////////////////////////////////////////////////////
// _ZVOutputViewListBox window

class _ZVOutputViewListBox : public CListBox, public PSS_Subject
{
    // Construction
public:

    _ZVOutputViewListBox();
    virtual ~_ZVOutputViewListBox();

    // Operations
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(_ZVOutputViewListBox)
    //}}AFX_VIRTUAL

// Implementation
public:

    virtual BOOL _ZVOutputViewListBox::OnCmdMsg(UINT                    nID,
                                                int                    nCode,
                                                void*                    pExtra,
                                                AFX_CMDHANDLERINFO*    pHandlerInfo)
    {
        return CListBox::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
    }

    virtual BOOL _ZVOutputViewListBox::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
    {
        return CListBox::OnWndMsg(message, wParam, lParam, pResult);
    }

    // Generated message map functions
protected:

    //{{AFX_MSG(_ZVOutputViewListBox)
    afx_msg void OnSelchange();
    afx_msg void OnDblclk();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// ZVOutputView view

class AFX_EXT_CLASS ZVOutputView : public CWnd,
                                   public ZILog,
                                   public PSS_Subject,
                                   public PSS_Observer
{
public:

    DECLARE_DYNAMIC(ZVOutputView)

    // Protected constructor used by dynamic creation
    ZVOutputView();
    virtual ~ZVOutputView();

    // JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release.
    void Release();

    ///////////////////////////////////////////////////////////////////
    // ZILog methods
    virtual bool InitializeLog()
    {
        ClearLog();
        return true;
    }

    virtual void ClearLog()
    {
        // JMR-MODIF - Le 29 septembre 2005 - Contrôle que m_List existe avant de tenter de l'utiliser.
        if (m_List == NULL)
        {
            return;
        }

        m_List->ResetContent();

        // Immediate update
        UpdateWindow();
    }

    virtual void AddLine(const CString Line)
    {
        // JMR-MODIF - Le 29 septembre 2005 - Contrôle que m_List existe avant de tenter de l'utiliser.
        if (m_List == NULL)
        {
            return;
        }

        m_List->AddString(Line);

        if (m_SelectLast)
        {
            m_List->SelectString(-1, Line);
        }

        // Immediate update
        UpdateWindow();
    }

    virtual size_t GetCount() const
    {
        // JMR-MODIF - Le 29 septembre 2005 - Contrôle que m_List existe avant de tenter de l'utiliser.
        if (m_List == NULL)
        {
            return 0;
        }

        return m_List->GetCount();
    }

    virtual CString GetLineAt(size_t Index) const
    {
        // JMR-MODIF - Le 29 septembre 2005 - Contrôle que m_List existe avant de tenter de l'utiliser.
        if (m_List == NULL)
        {
            return _T("");
        }

        CString s;
        m_List->GetText(Index, s);

        return s;
    }

    virtual int GetCurrentSelection() const
    {
        // JMR-MODIF - Le 29 septembre 2005 - Contrôle que m_List existe avant de tenter de l'utiliser.
        if (m_List == NULL)
        {
            return -1;
        }

        return (m_List->GetCurSel() != LB_ERR) ? m_List->GetCurSel() : -1;
    }

    virtual void SetCurrentSelection(size_t Index)
    {
        // JMR-MODIF - Le 29 septembre 2005 - Contrôle que m_List existe avant de tenter de l'utiliser.
        if (m_List == NULL)
        {
            return;
        }

        m_List->SetCurSel(Index);
    }

    virtual void ClearCurrentSelection()
    {
        // JMR-MODIF - Le 29 septembre 2005 - Contrôle que m_List existe avant de tenter de l'utiliser.
        if (m_List == NULL)
        {
            return;
        }

        m_List->SetCurSel(-1);
    }

    virtual int GetCurrentItem(CString& s) const
    {
        // JMR-MODIF - Le 29 septembre 2005 - Contrôle que m_List existe avant de tenter de l'utiliser.
        if (m_List == NULL)
        {
            return 0;
        }

        int i = m_List->GetCurSel();

        if (i != LB_ERR)
        {
            m_List->GetText(i, s);
        }

        return i;
    }

    virtual bool IsInDebugMode() const
    {
        return m_IsInDebugMode;
    }

    virtual void SetDebugMode(bool value = true)
    {
        m_IsInDebugMode = value;
    }

    virtual bool SelectLast() const
    {
        return m_SelectLast;
    }

    virtual void SetSelectLast(bool value = true)
    {
        m_SelectLast = value;
    }

    ///////////////////////////////////////////////////////////////////
    // ZIObserver method
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

protected:

    // Generated message map functions
    //{{AFX_MSG(ZVOutputView)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    // Call back function base on list events
    virtual void OnSelChanged()
    {
        // Do nothing in the base class
    }

    virtual void OnDoubleClick()
    {
        // Do nothing in the base class
    }

private:

    _ZVOutputViewListBox*    m_List;

    CFont                    m_Font;

    COLORREF                m_clrBtnFace;

    bool                    m_IsInDebugMode;
    bool                    m_SelectLast;
};

#endif
