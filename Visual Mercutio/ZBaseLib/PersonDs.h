/****************************************************************************
 * ==> PSS_MailUser --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a mail user                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MailUserH
#define PSS_MailUserH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_MailUser
    //#define PSS_MailUser ZBMailUser
#endif

// mfc
#include "mfc.h"
#ifndef _WIN32
    #ifndef Mapi_h
        #define Mapi_h
        #include <mapi.h>
    #endif
#else
    #include <mapi.h>
#endif

// processsoft
#include "ZUser.h"

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
* Mail user
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MailUser : public CObject
{
    DECLARE_SERIAL(PSS_MailUser)

    public:
        /**
        * Constructor
        *@param personName - person name
        *@param recipClass - recipient class
        */
        PSS_MailUser(const CString& personName = "", ULONG recipClass = MAPI_TO);

        /**
        * Constructor
        *@param personName - person name
        *@param recipClass - recipient class
        */
        PSS_MailUser(ZUser& personName, ULONG recipClass = MAPI_TO);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_MailUser(const PSS_MailUser& other);

        virtual ~PSS_MailUser();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_MailUser& operator = (const PSS_MailUser& other);

        /**
        * Stores from the archive to the object stamp
        *@param ar - archive
        *@param user - mail user
        *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
        */
        friend CArchive& operator >> (CArchive& ar, PSS_MailUser& user);

        /**
        * Stores the object stamp to the archive
        *@param ar - archive
        *@param user - mail user
        *@return archive, to allow operator to be chained with other items, e.g a << b << c
        */
        friend CArchive& operator << (CArchive& ar, PSS_MailUser& user);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_MailUser* Clone() const;

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Gets the person name
        *@return the person name
        */
        virtual inline const CString& GetPersonName() const;

        /**
        * Sets the person name
        *@param value - the person name
        */
        virtual inline void SetPersonName(const CString& value);

        /**
        * Gets the recipicient class
        *@return the recipicient class
        */
        virtual inline const ULONG GetRecipClass() const;

        /**
        * Sets the recipicient class
        *@param value - the recipicient class
        */
        virtual inline void SetRecipClass(ULONG value);

    private:
        CString m_PersonName;
        ULONG   m_RecipClass;
};

//---------------------------------------------------------------------------
// PSS_MailUser
//---------------------------------------------------------------------------
const CString& PSS_MailUser::GetPersonName() const
{
    return m_PersonName;
}
//---------------------------------------------------------------------------
void PSS_MailUser::SetPersonName(const CString& value)
{
    m_PersonName = value;
}
//---------------------------------------------------------------------------
const ULONG PSS_MailUser::GetRecipClass() const
{
    return m_RecipClass;
}
//---------------------------------------------------------------------------
void PSS_MailUser::SetRecipClass(ULONG value)
{
    m_RecipClass = value;
}
//---------------------------------------------------------------------------

#endif
