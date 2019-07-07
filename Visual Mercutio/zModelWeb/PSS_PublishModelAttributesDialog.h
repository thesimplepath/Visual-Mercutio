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

#include "zBaseLib\ZWizard.h"
#include "zModel\ZCSymbolAttributesTreeCtrl.h"

// resources
#include "zModelWebRes.h"

// forward declaration
class ZBPropertyAttributes;

/**
* Dialog box to select the model attributes to publish
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_PublishModelAttributesDialog : public ZIWizardDialog
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

        ZCSymbolAttributesTreeCtrl m_Attributes;
        ZBPropertyAttributes*      m_pPropAttributes;
        ZBPropertySet*             m_pPropSet;
};

#endif
