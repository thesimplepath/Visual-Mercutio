/****************************************************************************
 * ==> PSS_DAOTableDlg -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a data access object (DAO) table dialog box       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DAOTableDlgH
#define PSS_DAOTableDlgH

#if _MSC_VER >= 1000
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
#include "ZBaseLib\PSS_Dialog.h"
#include "PSS_DAOTableList.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

#ifdef _ZDBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Data access object (DAO) table dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DAOTableDlg : public PSS_Dialog
{
    public:
        /**
        * Constructor
        *@param pParent - parent window, can be NULL
        */
        PSS_DAOTableDlg(CWnd* pParent = NULL);

        /**
        * Constructor
        *@param pDB - DAO database
        *@param pParent - parent window, can be NULL
        */
        PSS_DAOTableDlg(CDaoDatabase* pDB, CWnd* pParent = NULL);

        /**
        * Gets the table name
        *@return the table name
        */
        virtual inline CString GetTableName() const;

    protected:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_DATABASE_TABLE
        };

        PSS_DAOTableList m_ListBox;
        CDaoDatabase*    m_pDB;
        CString          m_TableName;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_DAOTableDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_DAOTableDlg)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
// PSS_DAOTableDlg
//---------------------------------------------------------------------------
CString PSS_DAOTableDlg::GetTableName() const
{
    return m_TableName;
}
//---------------------------------------------------------------------------

#endif
