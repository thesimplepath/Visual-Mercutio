/****************************************************************************
 * ==> PSS_LogicalSystemInfoDlg --------------------------------------------*
 ****************************************************************************
 * Description : Provides a logical system info dialog box                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_LogicalSystemInfoDlgH
#define PSS_LogicalSystemInfoDlgH

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

#include "zModelRes.h"

// old class name mapping
#ifndef PSS_LogicalSystemEntity
    #define PSS_LogicalSystemEntity ZBLogicalSystemEntity
#endif

// forward class declaration
class PSS_LogicalSystemEntity;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Logical system info dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_LogicalSystemInfoDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param titleID - the title identifier
        *@param pLogicalSystem - the logical system
        *@param name - the name
        *@param description - the description
        *@param modifyMode - the modify mode
        *@param pParent - the parent window, can be NULL
        */
        PSS_LogicalSystemInfoDlg(UINT                     titleID        = -1,
                                 PSS_LogicalSystemEntity* pLogicalSystem = NULL,
                                 const CString&           name           = _T(""),
                                 const CString&           description    = _T(""),
                                 bool                     modifyMode     = false,
                                 CWnd*                    pParent        = NULL);

        virtual ~PSS_LogicalSystemInfoDlg();

        /**
        * Gets the name
        *@return the name
        */
        virtual inline CString GetName() const;

        /**
        * Gets the description
        *@return the description
        */
        virtual inline CString GetDescription() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_LogicalSystemInfoDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_LogicalSystemInfoDlg)
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
            IDD = IDD_LOGICALSYSTEM_INFO
        };

        PSS_LogicalSystemEntity* m_pLogicalSystem;
        CString                  m_Title;
        CString                  m_Name;
        CString                  m_Description;
        bool                     m_ModifyMode;
};

//---------------------------------------------------------------------------
// PSS_LogicalSystemInfoDlg
//---------------------------------------------------------------------------
CString PSS_LogicalSystemInfoDlg::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
CString PSS_LogicalSystemInfoDlg::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------

#endif
