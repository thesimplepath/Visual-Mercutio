/****************************************************************************
 * ==> PSS_FolderStamp -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a folder stamp                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef FldStamp_h
#define FldStamp_h 1

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_Stamp.h"

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
* Folder stamp
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FolderStamp : public PSS_Stamp
{
    public:
        typedef PSS_Stamp inherited;

        PSS_FolderStamp();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FolderStamp(const PSS_FolderStamp& other);

        virtual ~PSS_FolderStamp();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        virtual const PSS_FolderStamp& operator = (const PSS_FolderStamp& other);

        /**
        * Stores from the archive to the object stamp
        *@param ar - archive
        *@param stamp - folder stamp
        *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
        */
        AFX_EXT_API friend CArchive& operator >> (CArchive& ar, PSS_FolderStamp& stamp);

        /**
        * Stores the object stamp to the archive
        *@param ar - archive
        *@param stamp - folder stamp
        *@return archive, to allow operator to be chained with other items, e.g a << b << c
        */
        AFX_EXT_API friend CArchive& operator << (CArchive& ar, const PSS_FolderStamp& stamp);

        /**
        * Clones the stamp
        *@return cloned stamp, NULL on error
        */
        virtual PSS_FolderStamp* Clone();

        /**
        * Reads the stamp from a file name
        *@param fileName - file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ReadFromFile(const CString& fileName);

        /**
        * Clears the existing password
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ClearPassword();

        /**
        * Sets a new password
        *@param password - password
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetPassword(const CString& password);

        /**
        * Checks if document is password protected
        *@return true if the document is password protected, otherwise FALSE
        */
        virtual inline BOOL HasPassword() const;

        /**
        * Gets the folder name
        *@return the folder name
        */
        virtual inline const CString GetFolderName() const;

        /**
        * Sets the folder name
        *@param name - the folder name
        */
        virtual inline void SetFolderName(const CString& name);

        /**
        * Gets the folder description
        *@return the folder description
        */
        virtual inline const CString GetFolderDescription() const;

        /**
        * Sets the folder description
        *@param description - the folder description
        */
        virtual inline void SetFolderDescription(const CString& description);

        /**
        * Gets the user name for the creation
        *@return the user name for the creation
        */
        virtual inline const CString GetCreationUserName() const;

        /**
        * Sets the user name for the creation
        *@param name - the user name
        */
        virtual inline void SetCreationUserName(const CString& name);

        /**
        * Gets the creation date
        *@return the creation date
        */
        virtual inline const ZBDate GetCreationDate() const;

        /**
        * Sets the creation date
        *@param date - the creation date
        */
        virtual inline void SetCreationDate(const ZBDate& date);

        /**
        * Gets the user name for the last modification
        *@return the user name for the last modification
        */
        virtual inline const CString GetModificationUserName() const;

        /**
        * Sets the user name for the modification
        *@param name - the user name
        */
        virtual inline void SetModificationUserName(const CString& value);

        /**
        * Gets the last modification date
        *@return the last modification date
        */
        virtual inline const ZBDate GetModificationDate() const;

        /**
        * Sets the last modification date
        *@param date - the last modification date
        */
        virtual inline void SetModificationDate(const ZBDate& date);

        /**
        * Gets the private key
        *@return the private key
        */
        virtual inline const CString GetKey1() const;

        /**
        * Sets the private key
        *@param key - the private key
        */
        virtual inline void SetKey1(const CString& key);

    private:
        CString m_FolderName;
        CString m_FolderDescription;
        CString m_CreationUserName;
        CString m_ModificationUserName;
        CString m_Password;
        CString m_Key1;
        ZBDate  m_CreationDate;
        ZBDate  m_ModificationDate;
};

//---------------------------------------------------------------------------
// PSS_FolderStamp
//---------------------------------------------------------------------------
BOOL PSS_FolderStamp::HasPassword() const
{
    return m_Password.IsEmpty() == FALSE;
}
//---------------------------------------------------------------------------
const CString PSS_FolderStamp::GetFolderName() const
{
    return m_FolderName;
}
//---------------------------------------------------------------------------
void PSS_FolderStamp::SetFolderName(const CString& name)
{
    m_FolderName = name;
}
//---------------------------------------------------------------------------
const CString PSS_FolderStamp::GetFolderDescription() const
{
    return m_FolderDescription;
}
//---------------------------------------------------------------------------
void PSS_FolderStamp::SetFolderDescription(const CString& description)
{
    m_FolderDescription = description;
}
//---------------------------------------------------------------------------
const CString PSS_FolderStamp::GetCreationUserName() const
{
    return m_CreationUserName;
}
//---------------------------------------------------------------------------
void PSS_FolderStamp::SetCreationUserName(const CString& name)
{
    m_CreationUserName = name;
}
//---------------------------------------------------------------------------
const ZBDate PSS_FolderStamp::GetCreationDate() const
{
    return m_CreationDate;
}
//---------------------------------------------------------------------------
void PSS_FolderStamp::SetCreationDate(const ZBDate& date)
{
    m_CreationDate = date;
}
//---------------------------------------------------------------------------
const CString PSS_FolderStamp::GetModificationUserName() const
{
    return m_ModificationUserName;
}
//---------------------------------------------------------------------------
void PSS_FolderStamp::SetModificationUserName(const CString& name)
{
    m_ModificationUserName = name;
}
//---------------------------------------------------------------------------
const ZBDate PSS_FolderStamp::GetModificationDate() const
{
    return m_ModificationDate;
}
//---------------------------------------------------------------------------
void PSS_FolderStamp::SetModificationDate(const ZBDate& date)
{
    m_ModificationDate = date;
}
//---------------------------------------------------------------------------
const CString PSS_FolderStamp::GetKey1() const
{
    return m_Key1;
}
//---------------------------------------------------------------------------
void PSS_FolderStamp::SetKey1(const CString& key)
{
    m_Key1 = key;
}
//---------------------------------------------------------------------------

#endif
