/****************************************************************************
 * ==> PSS_DocumentPageSetupDlg --------------------------------------------*
 ****************************************************************************
 * Description : Provides a document page setup dialog box                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DocumentPageSetupDlgH
#define PSS_DocumentPageSetupDlgH

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
#include "Define.h"
#include "PSS_WizardDialog.h"

// resources
#include "zBaseLibRes.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS PSS_DocumentPageSetupDlg : public PSS_WizardDialog
{
    DECLARE_DYNAMIC(PSS_DocumentPageSetupDlg)

    public:
        /**
        * Dialog box resources
        */
        enum
        {
            IDD = IDD_WZ_DOCUMENT_PAGESETUP
        };

        /**
        * Constructor
        *@param pParent - parent window, can be NULL
        */
        PSS_DocumentPageSetupDlg(CWnd* pParent = NULL);

        virtual ~PSS_DocumentPageSetupDlg();

        /**
        * Gets the background file name
        *@return the background file name
        */
        virtual CString GetBackgroundFileName() const;

        /**
        * Gets the paper size
        *@return the paper size
        */
        virtual CSize GetPaperSize() const;

        /**
        * Sets the paper size
        *@param paperSize - the paper size
        */
        virtual void SetPaperSize(const CSize& paperSize);

        /**
        * Gets the standard size
        *@return the standard size
        */
        virtual short GetStandardSize() const;

        /**
        * Sets the standard size
        *@param standardSize - the standard size
        */
        virtual void SetStandardSize(short standardSize);

        /**
        * Gets the orientation
        *@return the orientation
        */
        virtual short GetOrientation() const;

        /**
        * Sets the orientation
        *@param orientation - the orientation
        */
        virtual void SetOrientation(short orientation);

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map
        //{{AFX_MSG(PSS_DocumentPageSetupDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnBnClickedPortrait();
        afx_msg void OnBnClickedLandscape();
        afx_msg void OnBnClickedBtOpenfile();
        afx_msg void OnEnChangeEditFilename();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CString m_BgName;
        CSize   m_PaperSize;
        short   m_StandardSize;
        short   m_Orientation;

        /**
        * Updates the data
        */
        void UpdateDatas();
};

#endif
