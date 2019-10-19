/****************************************************************************
 * ==> PSS_WelcomeDialog ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a welcome dialog box                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WelcomeDialogH
#define PSS_WelcomeDialogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_Dialog.h"
#include "zBaseLib\PSS_ApplicationOption.h"
#include "PSS_HoverButton.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"
#include "zRes32\ZRes.h"

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
* Welcome dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WelcomeDialog : public PSS_Dialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WELCOME
        };

        CHyperLink      m_HyperLink;
        PSS_HoverButton m_LastFile;
        PSS_HoverButton m_Cancel;
        BOOL            m_DoNotStart;

        /**
        * Constructor
        *@param id - identifier
        *@param bitmapID - bitmap identifier
        *@param pAppOptions - application options
        *@param enableMoveToGeneral - if TRUE, the move to general mode will be enabled
        *@param pPArent - parent window, can be NULL
        */
        PSS_WelcomeDialog(UINT                   id,
                          UINT                   bitmapID,
                          PSS_ApplicationOption* pAppOptions,
                          BOOL                   enableMoveToGeneral = FALSE,
                          CWnd*                  pParent             = NULL);

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        // Generated message map functions
        //{{AFX_MSG(PSS_WelcomeDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnWelcomeLastFile();
        afx_msg void OnPaint();
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
        virtual void OnCancel();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Saves the state
        */
        void SaveState();

    private:
        BOOL                   m_EnableMoveToGeneral;
        PSS_ApplicationOption* m_pAppOptions;
        UINT                   m_BitmapID;
};

#endif
