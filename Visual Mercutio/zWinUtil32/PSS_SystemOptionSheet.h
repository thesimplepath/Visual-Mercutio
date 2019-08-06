/****************************************************************************
 * ==> PSS_SystemOptionSheet -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a system option sheet                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SystemOptionSheetH
#define PSS_SystemOptionSheetH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_BasePropSheet.h"

// forward class declaration
class PSS_ApplicationOption;

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
* System option sheet
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SystemOptionSheet : public PSS_BasePropSheet
{
    public:
        /**
        * Available pages
        *@note These values may be combined
        */
        enum IEOptionPage
        {
            IE_OP_General     = 0x0001,
            IE_OP_Calculation = 0x0002,
            IE_OP_View        = 0x0004,
            IE_OP_Navigation  = 0x0008,
            IE_OP_Export      = 0x0010,
            IE_OP_ViewReduced = 0x0020
        };

        /**
        * Constructor
        *@param pAppOptions - application options
        *@param optionPages - option pages to show
        */
        PSS_SystemOptionSheet(PSS_ApplicationOption* pAppOptions, IEOptionPage optionPages = IE_OP_General);

        virtual ~PSS_SystemOptionSheet();

        /**
        * Shows the system option sheet in modal mode
        *@return modal resolt
        */
        virtual int DoModal();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_SystemOptionSheet)
        virtual BOOL OnInitDialog();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_ApplicationOption* m_pAppOptions;
        IEOptionPage           m_OptionPages;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_SystemOptionSheet(const PSS_SystemOptionSheet& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_SystemOptionSheet& operator = (const PSS_SystemOptionSheet& other);
};

#endif
