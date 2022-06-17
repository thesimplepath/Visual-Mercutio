/****************************************************************************
 * ==> PSS_File ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic file                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FileH
#define PSS_FileH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_File
    #define PSS_File ZFile
#endif

// std
#include <memory>

// mfc
#include "mfc.h"

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
* Generic file
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_File : public CObject
{
    DECLARE_SERIAL(PSS_File)

    public:
        /**
        * File attachment type
        */
        enum class IEAttachmentType
        {
            IE_AT_InsertedFile,
            IE_AT_HyperLinkFile,
            IE_AT_IncludeFileDynamic,
            IE_AT_Undefined
        };

        typedef CObject inherited;

        PSS_File();

        /**
        * Constructor
        *@param fileName - file name
        *@param attachment - attachment type
        */
        PSS_File(const CString& fileName, IEAttachmentType attachement = IEAttachmentType::IE_AT_InsertedFile);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_File(const PSS_File& other);

        virtual ~PSS_File();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_File& operator = (const PSS_File& other);

        /**
        * Equality operator
        *@param other - other object to compare with
        *@return 1 if the file names are the same, otherwise 0
        */
        int operator == (const PSS_File& other) const;

        /**
        * Not equality operator
        *@param other - other object to compare with
        *@return 1 if the file names are the same, otherwise 0
        */
        int operator != (const PSS_File& other) const;

        /**
        * Stores from the archive to the file
        *@param ar - archive
        *@param file - file
        *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
        */
        AFX_EXT_API friend CArchive& operator >> (CArchive& ar, PSS_File& file);

        /**
        * Stores the file to the archive
        *@param ar - archive
        *@param file - file
        *@return archive, to allow operator to be chained with other items, e.g a << b << c
        */
        AFX_EXT_API friend CArchive& operator << (CArchive& ar, const PSS_File& file);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual inline PSS_File* Clone() const;

        /**
        * Rebuilds the file name
        */
        virtual void Rebuild();

        /**
        * Gets the complete file name
        *@return the complete file name
        */
        virtual CString GetCompleteFileName() const;

        /**
        * Sets the complete file name
        *@param fileName - file name
        *@param attachment - attachment type
        */
        virtual void SetCompleteFileName(const CString& fileName, IEAttachmentType attachement = IEAttachmentType::IE_AT_InsertedFile);

        /**
        * Gets the file name
        *@return the file name
        */
        virtual CString GetFileName() const;

        /**
        * Sets the file name and rebuild the complete file name
        *@param fileName - file name
        *@param attachment - attachment type
        */
        virtual void SetFileName(const CString& fileName, IEAttachmentType attachement = IEAttachmentType::IE_AT_InsertedFile);

        /**
        * Gets the file name path
        *@return the file name path
        */
        virtual CString GetFilePath() const;

        /**
        * Sets the file name path and rebuild the complete file name
        *@param path - path
        */
        virtual void SetFilePath(const CString& path);

        /**
        * Gets the file name drive
        *@return the file name drive
        */
        virtual const char GetFileDrive() const;

        /**
        * Sets the file name drive and rebuild the complete file name
        *@param drive - file name drive
        */
        virtual void SetFileDrive(const char fileName);

        /**
        * Gets the display name
        *@return the display name
        */
        virtual CString GetDisplayName() const;

        /**
        * Gets the icon index
        *@return the icon index
        */
        virtual int GetIconIndex() const;

        /**
        * Gets the file title
        *@return the file title
        */
        virtual CString GetFileTitle() const;

        /**
        * Gets the file extension
        *@return the file extension
        */
        virtual CString GetFileExt() const;

        /**
        * Gets the file description
        *@return the file description
        */
        virtual CString GetDescription() const;

        /**
        * Checks if file exists
        *@param fileName - file name to check
        *@return TRUE if file exists, otherwise FALSE
        */
        static BOOL Exist(const CString& fileName);

        /**
        * Checks if file exists
        *@return TRUE if file exists, otherwise FALSE
        */
        virtual BOOL Exist() const;

        /**
        * Checks if file is opened in read-only mode
        *@return TRUE if file is opened in read-only mode, otherwise FALSE
        */
        virtual BOOL IsReadOnly() const;

        /**
        * Sets the read-only flag, dependent of the parameter
        *@param readOnly - if TRUE, file is read-only
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetReadOnly(BOOL ReadOnly = TRUE);

        /**
        * Checks if the file is an archive
        *@return TRUE if the file is an archive, otherwise FALSE
        */
        virtual BOOL IsArchive() const;

        /**
        * Sets the file as archive
        *@param archive - if TRUE the file is an archive
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetArchive(BOOL Archive = TRUE);

        /**
        * Gets the last write time
        *@param fileName - file name for which the write time should be get
        *@param[out] tm - last write time on function ends, on success
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL GetLastWriteTime(const CString& fileName, SYSTEMTIME& tm);

        /**
        * Gets the last write time
        *@param[out] tm - last write time on function ends, on success
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL GetLastWriteTime(SYSTEMTIME& tm) const;

        /**
        * Gets the attachment type
        *@return the attachment type
        */
        virtual inline const IEAttachmentType GetAttachmentType() const;

        /**
        * Sets the attachment type
        *@param value - the attachment type
        */
        virtual inline void SetAttachmentType(IEAttachmentType value);

    protected:
        CString m_FileName;

    private:
        IEAttachmentType m_AttachmentType;
        char             m_Drive         [_MAX_DRIVE];
        char             m_Dir           [_MAX_DIR];
        char             m_FileNameBuffer[_MAX_FNAME];
        char             m_FileExt       [_MAX_EXT];

        /**
        * Gets the file handle
        *@param fileName - file name
        *@return the file handle, NULL on error
        */
        static HANDLE GetFileHandle(const CString& fileName);
};

//---------------------------------------------------------------------------
// PSS_File
//---------------------------------------------------------------------------
PSS_File* PSS_File::Clone() const
{
    return new PSS_File(*this);
}
//---------------------------------------------------------------------------
const PSS_File::IEAttachmentType PSS_File::GetAttachmentType() const
{
    return m_AttachmentType;
}
//---------------------------------------------------------------------------
void PSS_File::SetAttachmentType(IEAttachmentType value)
{
    m_AttachmentType = value;
}
//---------------------------------------------------------------------------

#endif
