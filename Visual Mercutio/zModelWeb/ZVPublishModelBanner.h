// ZVPublishModelBanner.h : header file

#if !defined(AFX_ZVPublishModelBanner_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
#define AFX_ZVPublishModelBanner_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\ZWizard.h"
#include "zModelWebRes.h"

#include "zWinUtil32\ZSearchEdit.h"

// JMR-MODIF - Le 8 août 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelBanner dialog

class ZVPublishModelBanner : public ZIWizardDialog
{
// Construction
public:

    // Standard constructor
    ZVPublishModelBanner( CString    HyperLink        = _T( "" ),
                          CString    ImageFilename    = _T( "" ),
                          CWnd*        pParent            = NULL );

    CString GetHyperLink() const
    {
        return m_HyperLink;
    }

    CString GetImageFilename() const
    {
        return m_ImageFilename;
    }

private:

    // Dialog Data
    //{{AFX_DATA(ZVPublishModelBanner)
    enum { IDD = IDD_WZPUBMODEL_BANNER };
    ZCSearchEdit    m_Image;
    CString            m_HyperLink;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVPublishModelBanner)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVPublishModelBanner)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    CString m_ImageFilename;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVPublishModelBanner_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
