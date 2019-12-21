/****************************************************************************
 * ==> PSS_CalculationPage -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a page containing calculation options for the     *
 *               system                                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CalculationPageH
#define PSS_CalculationPageH

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
#endif
#ifdef _WIN32
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
* Text button with alignement style
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_CalculationPage : public PSS_GenericPropPage
{
    public:
        /**
        * Data resources
        */
        enum
        {
            IDD = IDD_CALCOPTION
        };

        BOOL m_AutoCalculate;

    public:
        /**
        * Constructor
        *@param pAppOptions - application options
        */
        PSS_CalculationPage(PSS_ApplicationOption* pAppOptions);

        virtual ~PSS_CalculationPage();

        /**
        * Saves the values to object
        */
        virtual void SaveValuesToObject();

        /**
        * Gets the auto-calculate option state
        *@return the auto-calculate option state
        */
        virtual inline BOOL GetAutoCalculate() const;

    protected:
        /**
        * DDX/DDV data support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange (CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_CalculationPage)
        virtual BOOL OnInitDialog();
        afx_msg void OnAutocalculation();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
    
    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_CalculationPage(const PSS_CalculationPage& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_CalculationPage& operator = (const PSS_CalculationPage& other);
};

//---------------------------------------------------------------------------
// PSS_CalculationPage
//---------------------------------------------------------------------------
BOOL PSS_CalculationPage::GetAutoCalculate() const
{
    return m_AutoCalculate;
}
//---------------------------------------------------------------------------

#endif
