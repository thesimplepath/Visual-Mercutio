/****************************************************************************
 * ==> PSS_UserRecordSet ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user record set                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserRecordSetH
#define PSS_UserRecordSetH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

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
* User record set
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserRecordSet : public CRecordset
{
    DECLARE_DYNAMIC(PSS_UserRecordSet)

    public:
        CString m_UserName;
        CString m_Email;
        CString m_Responsible;
        CString m_Description;

        /**
        * Constructor
        *@param pDatabase - database, can be NULL
        */
        PSS_UserRecordSet(CDatabase* pDatabase = NULL);

        /**
        * Gets the user database table name
        *@return the user database table name
        */
        CString GetUserDBTableName() const;

    protected:
        /**
        * Gets the default connection string
        *@return the default connection string
        */
        virtual CString GetDefaultConnect() const;

        /**
        * Gets the default SQL for recordset
        *@return the default SQL for recordset
        */
        virtual CString GetDefaultSQL() const;

        /**
        * RFX support
        *@param pFX - RFX data
        */
        virtual void DoFieldExchange(CFieldExchange* pFX);
};

#endif
