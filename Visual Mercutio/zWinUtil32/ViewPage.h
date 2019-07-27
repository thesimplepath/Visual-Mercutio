
#ifndef ViewPage_h
#define ViewPage_h 1

// processsoft
#include "zBaseLib\AppOpt.h"
#include "PSS_GenericPropPage.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

class ZIViewPage : public PSS_GenericPropPage
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_VIEWPAGE
        };

        BOOL m_bCalculatedField;
        BOOL m_bShowHiddenField;
        BOOL m_bAnimationShow;
        BOOL m_bShowBoundsRect;
        BOOL m_AutomaticCreateFieldName;

        /**
        * Constructor
        *@param pApplicationOptions - application options
        */
        ZIViewPage (ZAApplicationOption* pApplicationOptions);

        virtual ~ZIViewPage();

        /**
        * Saves the values to object
        */
        virtual void SaveValuesToObject();

    protected:
        /**
        * Do data exchange mecanism of MFC dialog
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange (CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(ZIViewPage)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        ZIViewPage(const ZIViewPage& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const ZIViewPage& operator = (const ZIViewPage& other);
};

#endif
