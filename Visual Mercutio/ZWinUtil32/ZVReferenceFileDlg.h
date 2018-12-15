// ZVReferenceFileDlg.h : header file

#if !defined(AFX_ZVREFERENCEFILEDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_)
#define AFX_ZVREFERENCEFILEDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_

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

#include "ZSearchEdit.h"

#include "zWinUtil32\zWinUtil32.h"

#ifdef _ZWINUTIL32EXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 12 juin 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVReferenceFileDlg dialog

class AFX_EXT_CLASS ZVReferenceFileDlg : public CDialog
{
// Construction / Destruction
public:

    // Standard constructor
    ZVReferenceFileDlg( const CString    Reference        = _T( "" ),
                        int                InsertionType    = 0,
                        int                ActivationType    = 0,
                        CWnd*            pParent            = NULL );

public:

    CString GetReference() const
    {
        return m_Reference;
    }

    int GetInsertionType() const
    {
        return m_InsertionType;
    }

    int GetActivationType() const
    {
        return m_ActivationType;
    }

private:

    // Dialog Data
    //{{AFX_DATA(ZVReferenceFileDlg)
    enum { IDD = IDD_REFERENCE_FILE };
    CComboBox    m_ActivationTypeCtrl;
    CComboBox    m_InsertionTypeCtrl;
    CString        m_Reference;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVReferenceFileDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVReferenceFileDlg)
    afx_msg void OnAddfile();
    afx_msg void OnAddurl();
    afx_msg void OnScriptor();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    void SaveValuesToObject();
    void CheckControlState();

private:

    int m_InsertionType;
    int m_ActivationType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVREFERENCEFILEDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_)
