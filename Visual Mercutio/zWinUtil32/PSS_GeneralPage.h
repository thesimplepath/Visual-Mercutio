/****************************************************************************
 * ==> PSS_GeneralPage -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a general page                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GeneralPageH
#define PSS_GeneralPageH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_ApplicationOption.h"
#include "PSS_GenericPropPage.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* General page
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GeneralPage : public PSS_GenericPropPage
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_SYSOPTIONPAGE
        };

        CButton m_BtnMaximizeForm;
        CButton m_BtnShowWelcome;
        CButton m_BtnReloadLastFile;
        CButton m_BtnStartupOpenFile;
        CButton m_BtnScreenPos;
        BOOL    m_DontShowTaskList;
        BOOL    m_DontShowTips;
        BOOL    m_ForceNetwork;

        /**
        * Constructor
        *@param pApplicationOptions - application options
        */
        PSS_GeneralPage(PSS_ApplicationOption* pApplicationOptions);

        virtual ~PSS_GeneralPage();

        /**
        * Saves the values to the object
        */
        virtual void SaveValuesToObject();

    protected:
        /**
        * Do data exchange mecanism of MFC dialog
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange (CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(ZIGeneralPage)
        virtual BOOL OnInitDialog();
        afx_msg void OnShowWelcomeScreen();
        afx_msg void OnReloadLastFile();
        afx_msg void OnStartupOpenFile();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_GeneralPage(const PSS_GeneralPage& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_GeneralPage& operator = (const PSS_GeneralPage& other);
};

#endif
