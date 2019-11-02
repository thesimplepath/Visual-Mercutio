/****************************************************************************
 * ==> PSS_DatabaseListCtrl ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a database list controller                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DatabaseListCtrlH
#define PSS_DatabaseListCtrlH

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
#include "zBaseLib\PSS_ListCtrl.h"

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
* Database list controller
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DatabaseListCtrl : public PSS_ListCtrl
{
    public:
        /**
        * Constructor
        *@param fileName - database file name
        *@param tableName - table name
        */
        PSS_DatabaseListCtrl(const CString& fileName = "", const CString& tableName = "");

        virtual ~PSS_DatabaseListCtrl();

        /**
        * Initializes the controller
        *@param fileName - database file name
        *@param tableName - table name
        */
        virtual BOOL Initialize(const CString& fileName, const CString& tableName);

        /**
        * Gets the record set
        *@return the record set
        */
        virtual CDaoRecordset* GetRecordSet();

        /**
        * Gets the record count
        *@return the record count
        */
        virtual long GetRecordCount() const;

        /**
        * Refreshes the listbox content
        */
        virtual BOOL Refresh();

    protected:
        CImageList* m_pImageList;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_DatabaseListCtrl)
        virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_DatabaseListCtrl)
        afx_msg void OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CDaoRecordset* m_pRecordSet;
        CDaoDatabase*  m_pDataBase;
        CString        m_FileName;
        CString        m_TableName;
        BOOL           m_ColumnsBuilt;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DatabaseListCtrl(const PSS_DatabaseListCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_DatabaseListCtrl& operator = (const PSS_DatabaseListCtrl& other);

        /**
        * Builds the columns
        */
        void BuildColumns();

        /**
        * Opens the database
        *@return TRUE on success, otherwise FALSE
        */
        BOOL OpenDatabase();

        /**
        * Closes the database
        *@return TRUE on success, otherwise FALSE
        */
        BOOL CloseDatabase();
};

#endif
