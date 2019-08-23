/****************************************************************************
 * ==> PSS_MailFileDescription ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a mail file description                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MailFileDescriptionH
#define PSS_MailFileDescriptionH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// Windows
#ifndef Mapi_h
    #define Mapi_h
    #include <mapi.h>
#endif

// processsoft
#include "PSS_FileManager.h"

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
* Mail file description
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MailFileDescription
{
    public:
        PSS_MailFileDescription();

        /**
        * Constructor
        *@param fileList - file list
        *@param attachType - attachment type
        */
        PSS_MailFileDescription(CStringArray& fileList, PSS_File::IEAttachementType attachType = PSS_File::IE_AT_InsertedFile);

        /**
        * Constructor
        *@param fileList - file list
        *@param attachType - attachment type
        */
        PSS_MailFileDescription(PSS_FileManager& fileList, PSS_File::IEAttachementType attachType = PSS_File::IE_AT_InsertedFile);

        virtual ~PSS_MailFileDescription();

        /**
        * Fills from a file list
        *@param fileList - file list
        *@param attachType - attachment type
        */
        virtual void Fill(CStringArray& fileList, PSS_File::IEAttachementType attachType = PSS_File::IE_AT_InsertedFile);

        /**
        * Fills from a file list
        *@param fileList - file list
        *@param attachType - attachment type
        */
        virtual void Fill(PSS_FileManager& fileList, PSS_File::IEAttachementType attachType = PSS_File::IE_AT_InsertedFile);

        /**
        * Adds an attachment file
        *@param file - file
        *@param attachType - attachment type
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL AddFile(const CString& file, PSS_File::IEAttachementType attachType = PSS_File::IE_AT_InsertedFile);

        /**
        * Adds an attachment file
        *@param file - file
        *@param attachType - attachment type
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddFile(PSS_File& file, PSS_File::IEAttachementType attachType = PSS_File::IE_AT_InsertedFile);

        /**
        * Gets the attachment count
        *@return the attachment count
        */
        virtual inline int GetCount() const;

        /**
        * Gets the mapi file description
        *@return the mapi file description
        */
        virtual MapiFileDesc* GetMapiFileDesc();

        /**
        * Removes all the files
        */
        virtual inline void RemoveAllFiles();

        /**
        * Gets the file text hyperlink
        *@return the hyperlink text
        */
        virtual const CString& GetHyperLinkText();

        /**
        * Gets the attachment type
        *@return the attachment type
        */
        virtual inline const PSS_File::IEAttachementType GetAttachementType() const;

        /**
        * Sets the attachment type
        *@param value - the attachment type
        */
        virtual inline void SetAttachementType(PSS_File::IEAttachementType value);

    private:
        MapiFileDesc*               m_MapiFileDesc;
        CStringArray                m_FileArray;
        CString                     m_HyperLinkText;
        PSS_File::IEAttachementType m_AttachementType;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_MailFileDescription(const PSS_MailFileDescription& right);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_MailFileDescription& operator = (const PSS_MailFileDescription& right);
};

//---------------------------------------------------------------------------
// PSS_MailFileDescription
//---------------------------------------------------------------------------
BOOL PSS_MailFileDescription::AddFile(const CString& file, PSS_File::IEAttachementType attachType)
{
    m_AttachementType = attachType;
    return (m_FileArray.Add(file) >= 0);
}
//---------------------------------------------------------------------------
int PSS_MailFileDescription::GetCount() const
{
    return m_FileArray.GetSize();
}
//---------------------------------------------------------------------------
void PSS_MailFileDescription::RemoveAllFiles()
{
    m_FileArray.RemoveAll();
}
//---------------------------------------------------------------------------
const PSS_File::IEAttachementType PSS_MailFileDescription::GetAttachementType() const
{
    return m_AttachementType;
}
//---------------------------------------------------------------------------
void PSS_MailFileDescription::SetAttachementType(PSS_File::IEAttachementType value)
{
    m_AttachementType = value;
}
//---------------------------------------------------------------------------

#endif
