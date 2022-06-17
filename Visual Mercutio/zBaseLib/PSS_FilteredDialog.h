/****************************************************************************
 * ==> PSS_FilteredDialog --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a dialog which provides input filters             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FilteredDialogH
#define PSS_FilteredDialogH

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
#include "PSS_Dialog.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Dialog which provides input filters
*@author Jean-Milost Reymond
*/
 class AFX_EXT_CLASS PSS_FilteredDialog : public PSS_Dialog
{
    public:
        /**
        * Constructor
        *@param templateID - dialog template identifier
        *@param autoCenter - if TRUE, the dialog will be auto-centered
        *@param pParentWnd - parent window, can be NULL
        */
        PSS_FilteredDialog(UINT templateID = -1, BOOL autoCenter = TRUE, CWnd* pParentWnd = NULL);

        /**
        * Constructor
        *@param pTemplateName - dialog template name
        *@param autoCenter - if TRUE, the dialog will be auto-centered
        *@param pParentWnd - parent window, can be NULL
        */
        PSS_FilteredDialog(LPCSTR pTemplateName, BOOL autoCenter = TRUE, CWnd* pParentWnd = NULL);

        /**
        * Constructor
        *@param templateID - dialog template identifier
        *@param autoCenter - if TRUE, the dialog will be auto-centered
        *@param bgCol - background color
        *@param staticCol - static label color
        *@param editCol - edit color
        *@param pParentWnd - parent window, can be NULL
        */
        PSS_FilteredDialog(UINT     templateID,
                           BOOL     autoCenter,
                           COLORREF bgCol,
                           COLORREF staticCol,
                           COLORREF editCol,
                           CWnd*    pParentWnd = NULL);

        /**
        * Constructor
        *@param pTemplateName - dialog template name
        *@param autoCenter - if TRUE, the dialog will be auto-centered
        *@param bgCol - background color
        *@param staticCol - static label color
        *@param editCol - edit color
        *@param pParentWnd - parent window, can be NULL
        */
        PSS_FilteredDialog(LPCSTR   pTemplateName,
                           BOOL     autoCenter,
                           COLORREF bgCol,
                           COLORREF staticCol,
                           COLORREF editCol,
                           CWnd*    pParentWnd = NULL);

        virtual ~PSS_FilteredDialog();

        /**
        * Pre-translates the Windows messages
        *@param pMsg - message
        */
        BOOL PreTranslateMessage(MSG* pMsg);

    protected:
        // Generated message map functions
        //{{AFX_MSG(PSS_FilteredDialog)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
