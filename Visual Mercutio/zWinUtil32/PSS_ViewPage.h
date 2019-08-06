/****************************************************************************
 * ==> PSS_ViewPage --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a view page                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ViewPageH
#define PSS_ViewPageH

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
* View page
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ViewPage : public PSS_GenericPropPage
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_VIEWPAGE
        };

        BOOL m_CalculatedField;
        BOOL m_ShowHiddenField;
        BOOL m_AnimationShow;
        BOOL m_ShowBoundsRect;
        BOOL m_AutomaticCreateFieldName;

        /**
        * Constructor
        *@param pApplicationOptions - application options
        */
        PSS_ViewPage(PSS_ApplicationOption* pApplicationOptions);

        virtual ~PSS_ViewPage();

        /**
        * Saves the values to object
        */
        virtual void SaveValuesToObject();

    protected:
        /**
        * Do data exchange mecanism of MFC dialog
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_ViewPage)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ViewPage(const PSS_ViewPage& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ViewPage& operator = (const PSS_ViewPage& other);
};

#endif
