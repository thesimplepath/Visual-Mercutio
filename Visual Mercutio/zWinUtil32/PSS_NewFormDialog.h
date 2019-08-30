/****************************************************************************
 * ==> PSS_NewFormDialog ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a new form wizard dialog box                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_NewFormDialogH
#define PSS_NewFormDialogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_WizardDialog.h"
#include "zBaseLib\PSS_TemplateManager.h"
#include "PSS_BasePropSheet.h"
#include "PSS_GenericFormPage.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

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
* New form wizard dialog box property sheet
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_NewFormPropertySheet : public PSS_BasePropSheet
{
    DECLARE_DYNAMIC(PSS_NewFormPropertySheet)

    public:
        /**
        * Constructor
        *@param pTemplateManager - template manager
        */
        PSS_NewFormPropertySheet(PSS_TemplateManager* pTemplateManager);

        virtual ~PSS_NewFormPropertySheet();

        /**
        * Gets the root caption
        *@return the root caption
        */
        virtual inline const CString GetRootCaption() const;

        /**
        * Initializes the property sheet
        */
        virtual void Initialize();

        /**
        * Clears the property sheet content
        */
        virtual void ClearContents();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_NewFormPropertySheet)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_TemplateManager* m_pTemplateManager;
        CString              m_RootCaption;
        BOOL                 m_FirstInitialization;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_NewFormPropertySheet(const PSS_NewFormPropertySheet& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_NewFormPropertySheet & operator = (const PSS_NewFormPropertySheet& other);
};

//---------------------------------------------------------------------------
// PSS_NewFormPropertySheet
//---------------------------------------------------------------------------
const CString PSS_NewFormPropertySheet::GetRootCaption() const
{
    return m_RootCaption;
}
//---------------------------------------------------------------------------

/**
* New form wizard dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_NewFormDialog : public PSS_WizardDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_NEWFORM
        };

        /**
        * Dialog form type enumeration
        */
        enum IEDialogFormType
        {
            IE_T_StartForm,
            IE_T_AttachForm,
            IE_T_OpenForm,
            IE_T_SelectForm
        };

        /**
        * Dialog form extension type enumeration
        */
        enum IEDialogFormExtensionType
        {
            IE_ET_Form,
            IE_ET_ProcessForm,
            IE_ET_ModelForm
        };

        CStatic       m_Text;
        CButton       m_CopyFormatWnd;
        CButton       m_Button;
        CBitmapButton m_MoveToGeneralTabBtn;
        CString       m_Comment;
        BOOL          m_CopyFormat;

        /**
        * Constructor
        *@param pTemplateManager - template manager
        *@param type - form type
        *@param extensionType - form extension type
        */
        PSS_NewFormDialog(PSS_TemplateManager*      pTemplateManager,
                          IEDialogFormType          type,
                          IEDialogFormExtensionType extensionType);

        virtual ~PSS_NewFormDialog();

        /**
        * Gets the form name
        *@return the form name
        */
        virtual inline CString GetFormName() const;

        /**
        * Gets the file name
        *@return the file name
        */
        virtual inline CString GetFileName() const;

        /**
        * Gets the template file
        *@return the template file
        */
        virtual inline PSS_TemplateFile* GetTemplateFile() const;

        /**
        * Gets if format should be copied
        *@return TRUE if format should be copied, otherwise FALSE
        */
        virtual inline BOOL MustCopyFormat() const;

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_NewFormDialog)
        virtual BOOL OnInitDialog();
        afx_msg LONG OnCommentChange(UINT message, LONG lParam);
        afx_msg LONG OnFormActivate(UINT message, LONG lParam);
        afx_msg LONG OnFormsSelected(UINT message, LONG lParam);
        afx_msg void OnMoveToGeneralTab();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_TemplateManager*       m_pTemplateManager;
        PSS_NewFormPropertySheet*  m_pSystemPropertySheet;
        PSS_TemplateDir*           m_pCurrentTemplateDir;
        PSS_TemplateFile*          m_pCurrentTemplateFile;
        IEDialogFormType           m_Type;
        IEDialogFormExtensionType  m_ExtensionType;
        CString                    m_SelectedFormName;
        CString                    m_SelectedFileName;
};

//---------------------------------------------------------------------------
// PSS_NewFormDialog
//---------------------------------------------------------------------------
CString PSS_NewFormDialog::GetFormName() const
{
    return m_SelectedFormName;
}
//---------------------------------------------------------------------------
CString PSS_NewFormDialog::GetFileName() const
{
    return m_SelectedFileName;
}
//---------------------------------------------------------------------------
PSS_TemplateFile* PSS_NewFormDialog::GetTemplateFile() const
{
    return m_pCurrentTemplateFile;
}
//---------------------------------------------------------------------------
BOOL PSS_NewFormDialog::MustCopyFormat() const
{
    return m_CopyFormat;
}
//---------------------------------------------------------------------------

#endif
