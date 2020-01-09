/****************************************************************************
 * ==> PSS_PublishModelAttributesDialog ------------------------------------*
 ****************************************************************************
 * Description : Dialog box allowing to select the model attributes to      *
 *               publish                                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishModelAttributesDialogH
#define PSS_PublishModelAttributesDialogH

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
#include "zBaseLib\PSS_WizardDialog.h"
#include "zModel\PSS_SymbolAttributesTreeCtrl.h"

// resources
#include "zModelWebRes.h"

// forward declaration
class ZBPropertyAttributes;

#ifdef _ZMODELWEBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Dialog box to select the model attributes to publish
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_PublishModelAttributesDialog : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param pPropAttributes - attributes to publish, can be NULL
        *@param propSet - property set owning the attributes to publish, can be NULL
        *@param pParent - parent window, can be NULL
        */
        PSS_PublishModelAttributesDialog(ZBPropertyAttributes* pPropAttributes = NULL,
                                         ZBPropertySet*        pPropSet        = NULL,
                                         CWnd*                 pParent         = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PublishModelAttributesDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// generated message map functions
        //{{AFX_MSG(PSS_PublishModelAttributesDialog)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZPUBMODEL_ATTRIBUTE
        };

        PSS_SymbolAttributesTreeCtrl m_Attributes;
        ZBPropertyAttributes*        m_pPropAttributes;
        ZBPropertySet*               m_pPropSet;
};

#endif
