/****************************************************************************
 * ==> PSS_MailMessage -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a mail message                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MailMessageH
#define PSS_MailMessageH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_MailMessage
    #define PSS_MailMessage ZBMailMessage
#endif

// mfc
#include "mfc.h"

// processsoft
#include "PSS_FileManager.h"
#include "PSS_MailFileDescription.h"
#include "PSS_MailUserList.h"

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
* Mail mesage
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MailMessage : public CObject
{
    DECLARE_SERIAL(PSS_MailMessage)

    public:
        /**
        * Constructor
        *@param pUserList - user list
        *@param subject - subject
        *@param text - text
        */
        PSS_MailMessage(PSS_MailUserList* pUserList = NULL, const CString& subject = "", const CString& text = "");

        virtual ~PSS_MailMessage();

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
        *@param pMapiDEsc - MAPI description
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL AddPerson(MapiRecipDesc* pMapiDesc);

        /**
        * Fills from a person list
        *@param personList - person list to fill from
        *@param recipClass - recipient class
        *@return TRUE on success, otherwise FALSE
        */
        virtual void FillPerson(CStringArray& personList, ULONG recipClass = MAPI_TO);

        /**
        * Fills from a person list
        *@param personList - person list to fill from
        *@param recipClass - recipient class
        *@return TRUE on success, otherwise FALSE
        */
        virtual void FillPerson(PSS_UserManager& personList, ULONG recipClass = MAPI_TO);

        /**
        * Fills from a person list
        *@param pMapiDesc - MAPI description
        *@return TRUE on success, otherwise FALSE
        */
        virtual void FillPerson(lpMapiRecipDesc* pMapiDesc, ULONG Count);

        /**
        * Gets the mail user count
        *@return the mail user count
        */
        virtual inline int GetMailUserCount() const;

        /**
        * Gets the mapi recipicient description
        *@return the mapi recipicient description
        */
        virtual MapiRecipDesc* GetMapiRecipDesc();

        /**
        * Gets the person at the index
        *@param index - index
        *@return the person at index, NULL if not found or on error
        */
        virtual inline PSS_MailUser* GetMailUserAt(int index);

        /**
        * Removes all the mail users
        */
        virtual inline void RemoveAllMailUser();

        /**
        * Adds an attachment file
        *@param fileName - file name to add
        *@param attachType - attachment type
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL AddFile(const CString& fileName, PSS_File::IEAttachementType attachType = PSS_File::IE_AT_InsertedFile);

        /**
        * Adds an attachment file
        *@param file - file to add
        *@param attachType - attachment type
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL AddFile(PSS_File& file, PSS_File::IEAttachementType attachType = PSS_File::IE_AT_InsertedFile);

        /**
        * Fills attachment files from a list
        *@param fileList - file list
        *@param attachType - attachment type
        */
        virtual inline void FillFile(CStringArray& fileList, PSS_File::IEAttachementType attachType = PSS_File::IE_AT_InsertedFile);

        /**
        * Fills attachment files from a list
        *@param fileList - file list
        *@param attachType - attachment type
        */
        virtual inline void FillFile(PSS_FileManager& fileList, PSS_File::IEAttachementType attachType = PSS_File::IE_AT_InsertedFile);

        /**
        * Gets the attached file count
        *@return the attached file count
        */
        virtual inline int GetFileCount() const;

        /**
        * Gets the mapi file description
        *@return the mapi file description
        */
        virtual inline MapiFileDesc* GetMapiFileDesc();

        /**
        * Removes all the attached files
        */
        virtual inline void RemoveAllFiles();

        /**
        * Gets the file text hyperlink
        *@return the file text hyperlink
        */
        virtual inline const CString GetHyperLinkText();

        /**
        * Gets the attachment type
        *@return the attachment type
        */
        virtual inline PSS_File::IEAttachementType GetAttachementType() const;

        /**
        * Gets the subject
        *@return the subject
        */
        virtual inline const CString GetSubject() const;

        /**
        * Sets the subject
        *@param value - the subject
        */
        virtual inline void SetSubject(const CString& value);

        /**
        * Gets the message text
        *@return the message text
        */
        virtual inline const CString GetText() const;

        /**
        * Sets the message text
        *@param value - the message text
        */
        virtual inline void SetText(const CString& value);

        /**
        * Gets the mapi file list
        *@return the mapi file list
        */
        virtual inline const PSS_MailFileDescription* GetMailFileList() const;

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        PSS_MailUserList*        m_pMailUserList;
        PSS_MailFileDescription* m_pMailFileList;
        CString                  m_Subject;
        CString                  m_Text;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_MailMessage(const PSS_MailMessage& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_MailMessage& operator = (const PSS_MailMessage& other);
};

//---------------------------------------------------------------------------
// PSS_MailMessage
//---------------------------------------------------------------------------
BOOL PSS_MailMessage::AddPerson(const CString& personName, ULONG recipClass)
{
    if (!m_pMailUserList)
        m_pMailUserList = new PSS_MailUserList;

    return m_pMailUserList->AddPerson(personName, recipClass);
}
//---------------------------------------------------------------------------
BOOL PSS_MailMessage::AddPerson(PSS_MailUser& person, ULONG recipClass)
{
    if (!m_pMailUserList)
        m_pMailUserList = new PSS_MailUserList;

    return m_pMailUserList->AddPerson(person, recipClass);
}
//---------------------------------------------------------------------------
BOOL PSS_MailMessage::AddPerson(ZUser& person, ULONG recipClass)
{
    if (!m_pMailUserList)
        m_pMailUserList = new PSS_MailUserList;

    return m_pMailUserList->AddPerson(person, recipClass);
}
//---------------------------------------------------------------------------
BOOL PSS_MailMessage::AddPerson(MapiRecipDesc* pMapiDesc)
{
    if (!m_pMailUserList)
        m_pMailUserList = new PSS_MailUserList;

    return m_pMailUserList->AddPerson(pMapiDesc);
}
//---------------------------------------------------------------------------
int PSS_MailMessage::GetMailUserCount() const
{
    if (m_pMailUserList)
        return m_pMailUserList->GetCount();

    return 0;
}
//---------------------------------------------------------------------------
PSS_MailUser* PSS_MailMessage::GetMailUserAt(int index)
{
    if (m_pMailUserList)
        return m_pMailUserList->GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_MailMessage::RemoveAllMailUser()
{
    if (m_pMailUserList)
        m_pMailUserList->RemoveAllPersons();
}
//---------------------------------------------------------------------------
BOOL PSS_MailMessage::AddFile(const CString& fileName, PSS_File::IEAttachementType attachType)
{
    if (!m_pMailFileList)
        m_pMailFileList = new PSS_MailFileDescription;

    if (m_pMailFileList)
        return m_pMailFileList->AddFile(fileName, attachType);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_MailMessage::AddFile(PSS_File& file, PSS_File::IEAttachementType attachType)
{
    if (!m_pMailFileList)
        m_pMailFileList = new PSS_MailFileDescription;

    if (m_pMailFileList)
        return m_pMailFileList->AddFile(file, attachType);

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_MailMessage::FillFile(CStringArray& fileList, PSS_File::IEAttachementType attachType)
{
    if (!m_pMailFileList)
        m_pMailFileList = new PSS_MailFileDescription;

    if (m_pMailFileList)
        m_pMailFileList->Fill(fileList, attachType);
}
//---------------------------------------------------------------------------
void PSS_MailMessage::FillFile(PSS_FileManager& fileList, PSS_File::IEAttachementType attachType)
{
    if (!m_pMailFileList)
        m_pMailFileList = new PSS_MailFileDescription;

    if (m_pMailFileList)
        m_pMailFileList->Fill(fileList, attachType);
}
//---------------------------------------------------------------------------
int PSS_MailMessage::GetFileCount() const
{
    if (m_pMailFileList)
        return m_pMailFileList->GetCount();

    return 0;
}
//---------------------------------------------------------------------------
MapiFileDesc* PSS_MailMessage::GetMapiFileDesc()
{
    if (m_pMailFileList)
        return m_pMailFileList->GetMapiFileDesc();

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_MailMessage::RemoveAllFiles()
{
    if (m_pMailFileList)
        m_pMailFileList->RemoveAllFiles();
}
//---------------------------------------------------------------------------
const CString PSS_MailMessage::GetHyperLinkText()
{
    if (m_pMailFileList)
        return m_pMailFileList->GetHyperLinkText();

    return "";
}
//---------------------------------------------------------------------------
PSS_File::IEAttachementType PSS_MailMessage::GetAttachementType() const
{
    if (m_pMailFileList)
        return m_pMailFileList->GetAttachementType();

    return PSS_File::IE_AT_Undefined;
}
//---------------------------------------------------------------------------
const CString PSS_MailMessage::GetSubject() const
{
    return m_Subject;
}
//---------------------------------------------------------------------------
void PSS_MailMessage::SetSubject(const CString& value)
{
    m_Subject = value;
}
//---------------------------------------------------------------------------
const CString PSS_MailMessage::GetText() const
{
    return m_Text;
}
//---------------------------------------------------------------------------
void PSS_MailMessage::SetText(const CString& value)
{
    m_Text = value;
}
//---------------------------------------------------------------------------
const PSS_MailFileDescription* PSS_MailMessage::GetMailFileList() const
{
    return m_pMailFileList;
}
//---------------------------------------------------------------------------

#endif
