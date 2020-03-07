/****************************************************************************
 * ==> PSS_PublishToMessengerWizard ----------------------------------------*
 ****************************************************************************
 * Description : Provides a publish to Messenger wizard                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishToMessengerWizardH
#define PSS_PublishToMessengerWizardH

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
#include "zBaseLib\PSS_IntelliEdit.h"
#include "zBaseLib\PSS_WizardDialog.h"
#include "zModelBP\zModelBPRes.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// forward class declaration
class PSS_ProcessGraphModelDoc;
class PSS_PublishMessengerModelInformation;
class PSS_Log;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Wizard to publish the document model to messenger
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PublishToMessengerWizard
{
    public:
        /**
        * Constructor
        *@param pModelDoc - the model document
        *@param pLog - the logger
        *@param iniFile - the ini file name
        */
        PSS_PublishToMessengerWizard(PSS_ProcessGraphModelDoc* pModelDoc,
                                     PSS_Log*                  pLog    = NULL,
                                     const CString&            iniFile = _T(""));

        virtual ~PSS_PublishToMessengerWizard();

        /**
        * Shows the wizard in a modal form
        *@return the modal result
        */
        virtual int DoModal();

    private:
        PSS_ProcessGraphModelDoc* m_pModelDoc;
        PSS_Log*                  m_pLog;
        CString                   m_IniFile;
};

/**
* Wizard to start the publication to Messenger
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_PublishToMessengerStartWizardDlg : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param iniFile - the ini file name
        *@param pParent - the parent window, can be NULL
        */
        PSS_PublishToMessengerStartWizardDlg(const CString& iniFile = _T(""), CWnd* pParent = NULL);

        /**
        * Gets the include model
        *@return the include model
        */
        virtual inline BOOL GetIncludeModel() const;

        /**
        * Gets the include groups
        *@return the include groups
        */
        virtual inline BOOL GetIncludeGroups() const;

        /**
        * Gets the include systems
        *@return the include system
        */
        virtual inline BOOL GetIncludeSystems() const;

        /**
        * Gets the include prestations
        *@return the include prestations
        */
        virtual inline BOOL GetIncludePrestations() const;

        /**
        * Gets the Messenger address
        *@return the Messenger address
        */
        virtual inline CString GetMessengerAddress() const;

        /**
        * Gets the Messenger alias
        *@return the Messenger alias
        */
        virtual inline CString GetMessengerAlias() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PublishToMessengerStartWizardDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_PublishToMessengerStartWizardDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnNext();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZ_PUBLISHTOMESSENGER_START
        };

        PSS_IntelliEdit m_MessengerAddressEdit;
        PSS_IntelliEdit m_MessengerAliasEdit;
        CStringArray    m_ArrayOfAddress;
        CString         m_MessengerAlias;
        CString         m_MessengerAddress;
        CString         m_IniFile;
        BOOL            m_IncludeModel;
        BOOL            m_IncludeGroups;
        BOOL            m_IncludeSystems;
        BOOL            m_IncludePrestations;

        /**
        * Loads the states from the ini file name
        *@return true on success, otherwise false
        */
        bool LoadStateFromIniFile();

        /**
        * Saves the states to the ini file name
        *@return true on success, otherwise false
        */
        bool SaveStateToIniFile();
};

//---------------------------------------------------------------------------
// PSS_PublishToMessengerStartWizardDlg
//---------------------------------------------------------------------------
BOOL PSS_PublishToMessengerStartWizardDlg::GetIncludeModel() const
{
    return m_IncludeModel;
}
//---------------------------------------------------------------------------
BOOL PSS_PublishToMessengerStartWizardDlg::GetIncludeGroups() const
{
    return m_IncludeGroups;
}
//---------------------------------------------------------------------------
BOOL PSS_PublishToMessengerStartWizardDlg::GetIncludeSystems() const
{
    return m_IncludeSystems;
}
//---------------------------------------------------------------------------
BOOL PSS_PublishToMessengerStartWizardDlg::GetIncludePrestations() const
{
    return m_IncludePrestations;
}
//---------------------------------------------------------------------------
CString PSS_PublishToMessengerStartWizardDlg::GetMessengerAddress() const
{
    return m_MessengerAddress;
}
//---------------------------------------------------------------------------
CString PSS_PublishToMessengerStartWizardDlg::GetMessengerAlias() const
{
    return m_MessengerAlias;
}
//---------------------------------------------------------------------------

/**
* Wizard to enter the Messenger logon
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_PublishToMessengerLogonWizardDlg : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param pInfo - the Messenger model info
        *@param pParent - the parent window, can be NULL
        */
        PSS_PublishToMessengerLogonWizardDlg(PSS_PublishMessengerModelInformation* pInfo, CWnd* pParent = NULL);

        virtual ~PSS_PublishToMessengerLogonWizardDlg();

        /**
        * Gets the begin date
        *@return the begin date
        */
        virtual inline CString GetBeginDate() const;

        /**
        * Gets the end date
        *@return the end date
        */
        virtual inline CString GetEndDate() const;

    protected:
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PublishToMessengerLogonWizardDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

    // Implementation
    protected:

        // Generated message map functions
        //{{AFX_MSG(PSS_PublishToMessengerLogonWizardDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZ_PUBLISHTOMESSENGER_AUTH
        };

        PSS_PublishMessengerModelInformation* m_pInfo;
        CString                               m_UserName;
        CString                               m_Password;
        CString                               m_BeginDate;
        CString                               m_EndDate;
};

//---------------------------------------------------------------------------
// PSS_PublishToMessengerLogonWizardDlg
//---------------------------------------------------------------------------
CString PSS_PublishToMessengerLogonWizardDlg::GetBeginDate() const
{
    return m_BeginDate;
}
//---------------------------------------------------------------------------
CString PSS_PublishToMessengerLogonWizardDlg::GetEndDate() const
{
    return m_EndDate;
}
//---------------------------------------------------------------------------

#endif
