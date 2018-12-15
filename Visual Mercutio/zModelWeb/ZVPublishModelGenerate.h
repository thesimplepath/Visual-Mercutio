// ZVPublishModelGenerate.h : header file

#if !defined(AFX_ZVPublishModelGenerate_H__94954CA4_85F3_11D3_9878_00C04FB4D0D7__INCLUDED_)
#define AFX_ZVPublishModelGenerate_H__94954CA4_85F3_11D3_9878_00C04FB4D0D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\ZWizard.h"
#include "zModelWebRes.h"

#ifdef _ZMODELWEBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 1er mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

////////////////////////////////////////////////////////////////////////////
// ZVPublishModelGenerate dialog

class AFX_EXT_CLASS ZVPublishModelGenerate : public ZIWizardDialog
{
// Construction
public:

    // Standard constructor
    ZVPublishModelGenerate();

    bool    Create( CWnd* pParent = NULL );

    void    SetDestination( const CString Destination );
    bool    RequestCancel() const
    {
        return m_RequestCancel;
    };

    // Dialog Data
    //{{AFX_DATA(ZVPublishModelGenerate)
    enum { IDD = IDD_WZPUBMODEL_GENERATE };
    CAnimateCtrl    m_FileMoveAnimation;
    CString    m_Destination;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVPublishModelGenerate)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

private:

    // Implementation
    // Generated message map functions
    //{{AFX_MSG(ZVPublishModelGenerate)
    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    bool    m_RequestCancel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVPublishModelGenerate_H__94954CA4_85F3_11D3_9878_00C04FB4D0D7__INCLUDED_)