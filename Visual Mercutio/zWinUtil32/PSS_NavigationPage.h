/****************************************************************************
 * ==> PSS_NavigationPage --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigation page                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef NavigationPageH
#define NavigationPageH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\AppOpt.h"
#include "PropPage.h"

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
* Navigation page
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_NavigationPage : public ZIGenericPropPage
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_NAVIGATIONPAGE
        };

        BOOL m_GoNextEdit;

        PSS_NavigationPage(ZAApplicationOption* pApplicationOptions);

        virtual ~PSS_NavigationPage();

        /**
        * Saves values to object
        */
        virtual void SaveValuesToObject();

    protected:
          /**
          * Do data exchange mecanism of MFC dialog
          *@param pDX - DDX/DDV data
          */
          virtual void DoDataExchange (CDataExchange* pDX);
      
        /// Generated message map functions
        //{{AFX_MSG(PSS_NavigationPage)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_NavigationPage(const PSS_NavigationPage& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_NavigationPage & operator = (const PSS_NavigationPage& other);
};

#endif
