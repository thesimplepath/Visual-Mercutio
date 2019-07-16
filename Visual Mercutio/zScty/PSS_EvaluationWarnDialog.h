/****************************************************************************
 * ==> PSS_EvaluationWarnDialog --------------------------------------------*
 ****************************************************************************
 * Description : Provides an evaluation warning dialog box                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EvaluationWarnDialogH
#define PSS_EvaluationWarnDialogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZSCTYEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Evaluation warning dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_EvaluationWarnDialog : public CDialog
{
    public:
        /**
        * Constructor
        *@param pParent - parent window
        */
        PSS_EvaluationWarnDialog(CWnd* pParent = NULL);

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_EvaluationWarnDialog)
        virtual BOOL OnInitDialog();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
