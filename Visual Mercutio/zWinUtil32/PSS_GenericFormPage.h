/****************************************************************************
 * ==> PSS_GenericFormPage -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic form page                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GenericFormPageH
#define PSS_GenericFormPageH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_TemplateManager.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

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
* Generic form page
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GenericFormPage : public CPropertyPage
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_GENERICFORM
        };

        CListBox m_CtlListOfPlan;

        PSS_GenericFormPage();

        /**
        * Constructor
        *@param pMain - main window
        *@param title - title
        *@param pTemplateManager - template manager
        */
        PSS_GenericFormPage(CWnd* pMain, const CString& title, PSS_TemplateManager* pTemplateManager);

        virtual ~PSS_GenericFormPage();

        /**
        * Gets the caption
        *@return the caption
        */
        virtual inline CString GetCaption() const;

        /**
        * Called when the page become active
        *@return TRUE if activation is allowed, otherwise FALSE
        */
        virtual BOOL OnSetActive();

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_GenericFormPage)
        afx_msg void OnSelChangeList();
        afx_msg void OnDblclkListOfForms();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_TemplateManager* m_pTemplateManager;
};

//---------------------------------------------------------------------------
// PSS_GenericFormPage
//---------------------------------------------------------------------------
CString PSS_GenericFormPage::GetCaption() const
{
    return m_strCaption;
}
//---------------------------------------------------------------------------

#endif
