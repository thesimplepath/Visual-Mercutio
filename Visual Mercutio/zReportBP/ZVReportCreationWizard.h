// ZVReportCreationWizard.h: interface for the ZVReportCreationWizard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZVReportCreationWizard_H__5DA4C599_18FB_4411_B32C_FA6E5C4462DB__INCLUDED_)
#define AFX_ZVReportCreationWizard_H__5DA4C599_18FB_4411_B32C_FA6E5C4462DB__INCLUDED_

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
#include "zReportBP\zReportBPRes.h"

#ifdef _ZREPORTBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 6 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZVReportCreationWizard
{
public:

    ZVReportCreationWizard( bool EnableIncludeMonthDetail    = true,
                            bool EnableExcelFormat            = false );

    virtual ~ZVReportCreationWizard();

    bool ExcelFormat() const
    {
        return m_ExcelFormat;
    };

    bool IncludeMonthDetail() const
    {
        return m_IncludeMonthDetail;
    };

    int DoModal();

private:

    bool m_EnableIncludeMonthDetail;
    bool m_EnableExcelFormat;
    bool m_ExcelFormat;
    bool m_IncludeMonthDetail;
};

/////////////////////////////////////////////////////////////////////////////
// ZVReportCreationStart dialog

class ZVReportCreationStart : public ZIWizardDialog
{
// Construction
public:

    // Standard constructor
    ZVReportCreationStart( bool EnableIncludeMonthDetail    = true,
                           bool EnableExcelFormat            = false,
                           CWnd* pParent                    = NULL );

    BOOL GetExcelFormat() const
    {
        return m_ExcelFormat;
    };

    BOOL GetIncludeMonthDetail() const
    {
        return m_IncludeMonthDetail;
    };

private:

    // Dialog Data
    //{{AFX_DATA(ZVReportCreationStart)
    enum { IDD = IDD_WZ_REPORTGENERATION_START };
    BOOL    m_ExcelFormat;
    BOOL    m_IncludeMonthDetail;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVReportCreationStart)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:

    // Implementation
    // Generated message map functions
    //{{AFX_MSG(ZVReportCreationStart)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnNext();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    bool m_EnableIncludeMonthDetail;
    bool m_EnableExcelFormat;
};

#endif // !defined(AFX_ZVReportCreationWizard_H__5DA4C599_18FB_4411_B32C_FA6E5C4462DB__INCLUDED_)