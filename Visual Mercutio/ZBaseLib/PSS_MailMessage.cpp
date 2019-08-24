/****************************************************************************
 * ==> PSS_MailMessage -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a mail message                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_MailMessage.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_MailMessage, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_MailMessage
//---------------------------------------------------------------------------
PSS_MailMessage::PSS_MailMessage(PSS_MailUserList* pUserList, const CString& subject, const CString& text) :
    CObject(),
    m_pMailUserList(pUserList),
    m_pMailFileList(NULL),
    m_Subject(subject),
    m_Text(text)
{}
//---------------------------------------------------------------------------
PSS_MailMessage::PSS_MailMessage(const PSS_MailMessage& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_MailMessage::~PSS_MailMessage()
{
    if (m_pMailUserList)
        delete m_pMailUserList;

    m_pMailUserList = NULL;
}
//---------------------------------------------------------------------------
const PSS_MailMessage& PSS_MailMessage::operator = (const PSS_MailMessage& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_MailMessage::FillPerson(CStringArray& personList, ULONG recipClass)
{
    if (!m_pMailUserList)
        m_pMailUserList = new PSS_MailUserList;

    m_pMailUserList->Fill(personList, recipClass);
}
//---------------------------------------------------------------------------
void PSS_MailMessage::FillPerson(ZUUserManager& personList, ULONG recipClass)
{
    if (!m_pMailUserList)
        m_pMailUserList = new PSS_MailUserList;

    m_pMailUserList->Fill(personList, recipClass);
}
//---------------------------------------------------------------------------
void PSS_MailMessage::FillPerson(lpMapiRecipDesc* pMapiDesc, ULONG count)
{
    if (!m_pMailUserList)
        m_pMailUserList = new PSS_MailUserList;

    m_pMailUserList->Fill(pMapiDesc, count);
}
//---------------------------------------------------------------------------
MapiRecipDesc* PSS_MailMessage::GetMapiRecipDesc()
{
    if (m_pMailUserList)
        return m_pMailUserList->GetMapiRecipDesc();

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_MailMessage::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements
        ar << m_Subject;
        ar << m_Text;
        ar << m_pMailUserList;
    }
    else
    {
        // read the elements
        ar >> m_Subject;
        ar >> m_Text;
        ar >> m_pMailUserList;
    }
}
//---------------------------------------------------------------------------
