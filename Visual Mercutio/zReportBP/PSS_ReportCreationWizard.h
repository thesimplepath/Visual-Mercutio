/****************************************************************************
 * ==> PSS_ReportCreationWizard --------------------------------------------*
 ****************************************************************************
 * Description : Provides a report creation wizard                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ReportCreationWizardH
#define PSS_ReportCreationWizardH

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

// processsoft
#include "zBaseLib\PSS_WizardDialog.h"
#include "zReportBP\zReportBPRes.h"

#ifdef _ZREPORTBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Report creation wizard
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ReportCreationWizard
{
    public:
        /**
        * Constructor
        *@param enableIncludeMonthDetail - if true, the include month details checkbox will be enabled
        *@param enableExcelFormat - if true, the Excel format checkbox will be enabled
        */
        PSS_ReportCreationWizard(bool enableIncludeMonthDetail = true, bool enableExcelFormat = false);

        virtual ~PSS_ReportCreationWizard();

        /**
        * Gets if the month details should be included
        *@return true if the month details should be included, otherwise false
        */
        virtual inline bool IncludeMonthDetail() const;

        /**
        * Gets if the Excel format should be included
        *@return true if the Excel format should be included, otherwise false
        */
        virtual inline bool ExcelFormat() const;

        /**
        * Shows the wizard in a modal way
        *@return the modal result
        */
        virtual int DoModal();

    private:
        bool m_EnableIncludeMonthDetail;
        bool m_EnableExcelFormat;
        bool m_IncludeMonthDetail;
        bool m_ExcelFormat;
};

//---------------------------------------------------------------------------
// PSS_ReportCreationWizard
//---------------------------------------------------------------------------
bool PSS_ReportCreationWizard::IncludeMonthDetail() const
{
    return m_IncludeMonthDetail;
}
//---------------------------------------------------------------------------
bool PSS_ReportCreationWizard::ExcelFormat() const
{
    return m_ExcelFormat;
}
//---------------------------------------------------------------------------

/**
* Report creation start dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ReportCreationStartDlg : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param enableIncludeMonthDetail - if true, the include month details checkbox will be enabled
        *@param enableExcelFormat - if true, the Excel format checkbox will be enabled
        *@param pParent - the parent window, can be NULL
        */
        PSS_ReportCreationStartDlg(bool  enableIncludeMonthDetail = true,
                                   bool  enableExcelFormat        = false,
                                   CWnd* pParent                  = NULL);

        virtual ~PSS_ReportCreationStartDlg();

        /**
        * Gets if the month details should be included
        *@return true if the month details option was enabled, otherwise false
        */
        virtual inline BOOL GetIncludeMonthDetail() const;

        /**
        * Gets if the Excel format should be included
        *@return true if the Excel format should be included, otherwise false
        */
        virtual inline BOOL GetExcelFormat() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ReportCreationStartDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ReportCreationStartDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnNext();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZ_REPORTGENERATION_START
        };

        BOOL m_IncludeMonthDetail;
        BOOL m_ExcelFormat;
        bool m_EnableIncludeMonthDetail;
        bool m_EnableExcelFormat;
};

//---------------------------------------------------------------------------
// PSS_ReportCreationStartDlg
//---------------------------------------------------------------------------
BOOL PSS_ReportCreationStartDlg::GetIncludeMonthDetail() const
{
    return m_IncludeMonthDetail;
}
//---------------------------------------------------------------------------
BOOL PSS_ReportCreationStartDlg::GetExcelFormat() const
{
    return m_ExcelFormat;
}
//---------------------------------------------------------------------------

#endif
