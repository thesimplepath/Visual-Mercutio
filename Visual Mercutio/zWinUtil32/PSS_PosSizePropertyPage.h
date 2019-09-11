/****************************************************************************
 * ==> PSS_PosSizePropertyPage ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a position and size property page                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PosSizePropertyPageH
#define PSS_PosSizePropertyPageH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_GenericPropPage.h"

// resources
#include "zRes32\ZRes.h"

// class name mapping
#ifndef PSS_PlanFinObject
    #define PSS_PlanFinObject PlanFinObject
#endif

// forward declaration
class PSS_PlanFinObject;

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
* Position and size property page
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PosSizePropertyPage : public PSS_GenericPropPage
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_SIZE_POSITION_PROPERTY
        };

        double m_PositionX;
        double m_PositionY;
        double m_Width;
        double m_Height;

        /**
        * Constructor
        *@param pObj - planfin object
        */
        PSS_PosSizePropertyPage(PSS_PlanFinObject* pObj = NULL);

        /**
        * Saves the values to object
        */
        virtual void SaveValuesToObject();

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_PosSizePropertyPage)
        virtual BOOL OnInitDialog();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
