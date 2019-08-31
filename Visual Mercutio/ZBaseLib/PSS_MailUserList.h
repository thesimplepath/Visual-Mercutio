/****************************************************************************
 * ==> PSS_MailUserList ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a mail user list                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MailUserListH
#define PSS_MailUserListH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_MailUserList
    #define PSS_MailUserList ZUMailUserList
#endif

// std
#include <memory>

// mfc
#include "mfc.h"

// processsoft
#include "PSS_MailUser.h"
#include "PSS_UserManager.h"

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
* Mail user list
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MailUserList : public CObject
{
    DECLARE_SERIAL(PSS_MailUserList)

    public:
        PSS_MailUserList();

        /**
        * Constructor
        *@param personNameList - person name list
        *@param recipClass - recipient class
        */
        PSS_MailUserList(CStringArray& personNameList, ULONG recipClass = MAPI_TO);

        /**
        * Constructor
        *@param personNameList - person name list
        *@param recipClass - recipient class
        */
        PSS_MailUserList(PSS_UserManager& personNameList, ULONG recipClass = MAPI_TO);

        /**
        * Constructor
        *@param pMapiDesc - mapi descriptor
        *@param count - count
        */
        PSS_MailUserList(lpMapiRecipDesc* pMapiDesc, ULONG count = 1);

        virtual ~PSS_MailUserList();

        /**
        * Gets the mapi recipicient description
        *@return the mapi recipicient description
        */
        virtual MapiRecipDesc* GetMapiRecipDesc();

        /**
        * Adds a new person
        *@param personName - person name to add
        *@param recipClass - recipient class
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL AddPerson(const CString& personName, ULONG recipClass = MAPI_TO);

        /**
        * Adds a new person
        *@param person - person to add
        *@param recipClass - recipient class
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL AddPerson(PSS_MailUser& person, ULONG recipClass = MAPI_TO);

        /**
        * Adds a new person
        *@param person - person to add
        *@param recipClass - recipient class
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL AddPerson(ZUser& person, ULONG recipClass = MAPI_TO);

        /**
        * Adds a new person
        *@param pMapiDesc - mapi descriptor
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL AddPerson(MapiRecipDesc* pMapiDesc);

        /**
        * Gets the person count
        *@return the person count
        */
        virtual inline int GetCount() const;

        /**
        * Gets the person at index
        *@param index - index
        *@return the parson at index, NULL if not found or on error
        */
        virtual inline PSS_MailUser* GetAt(int index);

        /**
        * Removes all the persons
        */
        virtual void RemoveAllPersons();

        /**
        * Fills a person array
        *@param personArray - person array to fill with content
        *@param recipClass - recipient class matching with person to fill
        */
        virtual void Fill(CStringArray& personList, ULONG recipClass = MAPI_TO);

        /**
        * Fills a person array
        *@param personArray - person array to fill with content
        *@param recipClass - recipient class matching with person to fill
        */
        virtual void Fill(PSS_UserManager& personList, ULONG recipClass = MAPI_TO);

        /**
        * Fills a person array
        *@param pMapiDesc - mapi descriptor
        *@param count - count
        */
        virtual void Fill(lpMapiRecipDesc* pMapiDesc, ULONG count);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        MapiRecipDesc* m_MapiRecipDesc;
        CObArray       m_PersonList;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_MailUserList(const PSS_MailUserList& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_MailUserList& operator = (const PSS_MailUserList& other);
};

//---------------------------------------------------------------------------
// PSS_MailUserList
//---------------------------------------------------------------------------
BOOL PSS_MailUserList::AddPerson(const CString& personName, ULONG recipClass)
{
    std::unique_ptr<PSS_MailUser> pNewPerson(new PSS_MailUser(personName, recipClass));
    const bool result = m_PersonList.Add(pNewPerson.get()) >= 0;
    pNewPerson.release();
    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_MailUserList::AddPerson(PSS_MailUser& person, ULONG recipClass)
{
    return m_PersonList.Add(&person) >= 0;
}
//---------------------------------------------------------------------------
BOOL PSS_MailUserList::AddPerson(ZUser& person, ULONG recipClass)
{
    std::unique_ptr<PSS_MailUser> pNewPerson(new PSS_MailUser(person.GetMailAddress(), recipClass));
    const bool result = m_PersonList.Add(pNewPerson.get()) >= 0;
    pNewPerson.release();
    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_MailUserList::AddPerson(MapiRecipDesc* pMapiDesc)
{
    if (!pMapiDesc)
        return FALSE;

    std::unique_ptr<PSS_MailUser> pNewPerson(new PSS_MailUser(pMapiDesc->lpszName, pMapiDesc->ulRecipClass));
    const bool result = m_PersonList.Add(pNewPerson.get()) >= 0;
    pNewPerson.release();
    return result;
}
//---------------------------------------------------------------------------
int PSS_MailUserList::GetCount() const
{
    return m_PersonList.GetSize();
}
//---------------------------------------------------------------------------
PSS_MailUser* PSS_MailUserList::GetAt(int index)
{
    if (index < GetCount())
        return (PSS_MailUser*)m_PersonList.GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------

#endif
