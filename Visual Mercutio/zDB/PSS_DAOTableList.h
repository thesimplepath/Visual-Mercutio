/****************************************************************************
 * ==> PSS_DAOTableList ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a data access object (DAO) table listbox          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DAOTableListH
#define PSS_DAOTableListH

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

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
* Data access object (DAO) table listbox
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DAOTableList : public CListBox
{
    public:
        /**
        * Constructor
        *@param pDB - DAO database, can be NULL
        */
        PSS_DAOTableList(CDaoDatabase* pDB = NULL);

        virtual ~PSS_DAOTableList();

        /**
        * Initializes the listbox
        *@param pDB - DAO database, can be NULL
        */
        virtual int Initialize(CDaoDatabase* pDB);

        /**
        * Gets the selected table
        *@return the selected table
        */
        virtual CString GetSelectedTable() const;

        /**
        * Gets the selected tables
        *@param[out] tableArray - table array to populate with result
        *@return the selected table count
        */
        virtual int GetSelectedTables(CStringArray& tableArray) const;

        /**
        * Refreshes the listbox content
        */
        virtual int Refresh();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_DAOTableList)
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_DAOTableList)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CDaoDatabase* m_pDB;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DAOTableList(const PSS_DAOTableList& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_DAOTableList& operator = (const PSS_DAOTableList& other);
};

#endif
