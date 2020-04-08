/****************************************************************************
 * ==> PSS_MailUserList ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a mail user list                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_MailUserList.h"

// mfc
#include <afxdisp.h>

// processsoft
#include "PSS_Defines.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_MailUserList, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_MailUserList
//---------------------------------------------------------------------------
PSS_MailUserList::PSS_MailUserList() :
    CObject(),
    m_MapiRecipDesc(NULL)
{}
//---------------------------------------------------------------------------
PSS_MailUserList::PSS_MailUserList(CStringArray& personListName, ULONG recipClass) :
    CObject(),
    m_MapiRecipDesc(NULL)
{
    Fill(personListName, recipClass);
}
//---------------------------------------------------------------------------
PSS_MailUserList::PSS_MailUserList(PSS_UserManager& personListName, ULONG recipClass) :
    CObject(),
    m_MapiRecipDesc(NULL)
{
    Fill(personListName, recipClass);
}
//---------------------------------------------------------------------------
PSS_MailUserList::PSS_MailUserList(lpMapiRecipDesc* pMapiDesc, ULONG count) :
    CObject(),
    m_MapiRecipDesc(NULL)
{
    Fill(pMapiDesc, count);
}
//---------------------------------------------------------------------------
PSS_MailUserList::PSS_MailUserList(const PSS_MailUserList& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_MailUserList::~PSS_MailUserList()
{
    if (m_MapiRecipDesc)
        delete[] m_MapiRecipDesc;

    RemoveAllPersons();
}
//---------------------------------------------------------------------------
const PSS_MailUserList& PSS_MailUserList::operator = (const PSS_MailUserList& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
MapiRecipDesc* PSS_MailUserList::GetMapiRecipDesc()
{
    if (m_MapiRecipDesc)
        delete[] m_MapiRecipDesc;

    m_MapiRecipDesc          = new FAR MapiRecipDesc[GetCount()];
    const register int count = GetCount();

    for (register int i = 0; i < count; ++i)
    {
        PSS_MailUser* pMailUser = GetAt(i);
        ASSERT(pMailUser);

        std::memset(lpMapiFileDesc(&m_MapiRecipDesc[i]), 0, sizeof(MapiRecipDesc));
        m_MapiRecipDesc[i].ulRecipClass = pMailUser->GetRecipClass();
        m_MapiRecipDesc[i].lpszName     = (char*)((const char*)(pMailUser->GetPersonName()));
    }

    return m_MapiRecipDesc;
}
//---------------------------------------------------------------------------
void PSS_MailUserList::RemoveAllPersons()
{
    const int count = GetCount();

    for (int i = 0; i < count; ++i)
        delete GetAt(i);

    m_PersonList.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_MailUserList::Fill(CStringArray& personList, ULONG recipClass)
{
    RemoveAllPersons();

    const register int count = personList.GetSize();

    for (register int i = 0; i < count; ++i)
        AddPerson(personList[i], recipClass);
}
//---------------------------------------------------------------------------
void PSS_MailUserList::Fill(PSS_UserManager& personList, ULONG recipClass)
{
    RemoveAllPersons();

    const register std::size_t count = personList.GetCount();

    for (register std::size_t i = 0; i < count; ++i)
        AddPerson(*personList.GetAt(i), recipClass);
}
//---------------------------------------------------------------------------
void PSS_MailUserList::Fill(lpMapiRecipDesc* pMapiDesc, ULONG count)
{
    RemoveAllPersons();

    for (register std::size_t i = 0; i < count; ++i)
        if (pMapiDesc[i])
            AddPerson(pMapiDesc[i]);
}
//---------------------------------------------------------------------------
void PSS_MailUserList::Serialize(CArchive& ar)
{
    m_PersonList.Serialize(ar);
}
//---------------------------------------------------------------------------
