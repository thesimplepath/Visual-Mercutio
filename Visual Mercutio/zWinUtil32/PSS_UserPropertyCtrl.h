/****************************************************************************
 * ==> PSS_UserPropertyCtrl ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user property control                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserPropertyH
#define PSS_UserPropertyH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_User.h"
#include "zBaseLib\PSS_ListCtrl.h"

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
* User property control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
#ifdef _WIN32
    // 32 bit version
    class AFX_EXT_CLASS PSS_UserPropertyCtrl : public PSS_ListCtrl
#else
    // 16 bit version
    class AFX_EXT_CLASS PSS_UserPropertyCtrl : public CListBox
#endif
{
    public:
        /**
        * Constructor
        *@param pUser - user
        *@param enableModify - if TRUE, property may be modified
        */
        PSS_UserPropertyCtrl(PSS_User* pUser = NULL, BOOL enableModify = FALSE);

        virtual ~PSS_UserPropertyCtrl();

        /**
        * Initializes the user property
        *@param pUser - user
        *@param enableModify - if TRUE, property may be modified
        */
        virtual int Initialize(PSS_User* pUser, BOOL enableModify = FALSE);

        /**
        * Checks if property is modified
        *@return TRUE if property is modified, otherwise FALSE
        */
        virtual inline BOOL IsModified() const;

        /**
        * Allows or denies the property to be modified
        *@param enableModify - if TRUE, property may be modified
        */
        virtual inline void EnableModify(BOOL enableModify = TRUE);

        /**
        * Refreshes the control
        */
        int Refresh();

    protected:
        /// ClassWizard generated message map functions
        //{{AFX_MSG(PSS_UserPropertyCtrl)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_User* m_pUser;
        BOOL      m_EnableModify;
        BOOL      m_ColumnsBuilt;
        BOOL      m_IsModified;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UserPropertyCtrl(const PSS_UserPropertyCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_UserPropertyCtrl& operator = (const PSS_UserPropertyCtrl& other);

        /**
        * Builds the columns
        */
        void BuildColumns();
};

//---------------------------------------------------------------------------
// PSS_UserPropertyCtrl
//---------------------------------------------------------------------------
BOOL PSS_UserPropertyCtrl::IsModified() const
{
    return m_IsModified;
}
//---------------------------------------------------------------------------
void PSS_UserPropertyCtrl::EnableModify(BOOL enableModify)
{
    m_EnableModify = enableModify;
}
//---------------------------------------------------------------------------

#endif
