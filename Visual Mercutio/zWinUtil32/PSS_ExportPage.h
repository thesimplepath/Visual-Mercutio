/****************************************************************************
 * ==> PSS_ExportPage ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an export options page                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ExportPageH
#define PSS_ExportPageH

// processsoft
#include "zBaseLib\PSS_ApplicationOption.h"
#include "PSS_GenericPropPage.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

/**
* Export options page
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ExportPage : public PSS_GenericPropPage
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_EXPORTPAGE
        };

        int     m_Propagation;
        CString m_SchemaName;
        BOOL    m_EmptyWhenZero;

        /**
        * Constructor
        *@param pAppOptions - application options
        */
        PSS_ExportPage(PSS_ApplicationOption* pApplicationOptions);

        virtual ~PSS_ExportPage();

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
        //{{AFX_MSG(ZIExportPage)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ExportPage(const PSS_ExportPage& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ExportPage & operator = (const PSS_ExportPage& other);
};

#endif
