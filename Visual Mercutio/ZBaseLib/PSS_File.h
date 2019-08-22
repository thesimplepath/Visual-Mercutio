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
        enum IEAttachementType
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
        PSS_File(const CString& fileName, IEAttachementType attachement = IE_AT_InsertedFile);

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
        AFX_EXT_API friend CArchive& operator >> (CArchive& ar, PSS_File& File);

        /**
        * Stores the file to the archive
        *@param ar - archive
        *@param file - file
        *@return archive, to allow operator to be chained with other items, e.g a << b << c
        */
        AFX_EXT_API friend CArchive& operator << (CArchive& ar, PSS_File& File);

        /**
        * Rebuilds the file name
        */
        void Rebuild();

        /**
        * Gets the complete file name
        *@return the complete file name
        */
        CString GetCompleteFileName() const;

        /**
        * Sets the complete file name
        *@param fileName - file name
        *@param attachment - attachment type
        */
        void SetCompleteFileName(const CString& fileName, IEAttachementType attachement = IE_AT_InsertedFile);

        /**
        * Gets the file name
        *@return the file name
        */
        CString GetFileName() const;

        /**
        * Sets the file name and rebuild the complete file name
        *@param fileName - file name
        *@param attachment - attachment type
        */
        void SetFileName(const CString& fileName, IEAttachementType attachement = IE_AT_InsertedFile);

        /**
        * Gets the file name path
        *@return the file name path
        */
        CString GetFilePath() const;

        /**
        * Sets the file name path and rebuild the complete file name
        *@param path - path
        */
        void SetFilePath(const CString& path);

        /**
        * Gets the file name drive
        *@return the file name drive
        */
        const char GetFileDrive() const;

        /**
        * Sets the file name drive and rebuild the complete file name
        *@param drive - file name drive
        */
        void SetFileDrive(const char fileName);

        /**
        * Clones the file object
        *@return the cloned object, NULL on error
        */
        virtual inline PSS_File* Clone() const;

        /**
        * Gets the display name
        *@return the display name
        */
        CString GetDisplayName() const;

        /**
        * Gets the icon index
        *@return the icon index
        */
        int GetIconIndex() const;

        /**
        * Gets the file title
        *@return the file title
        */
        CString GetFileTitle() const;

        /**
        * Gets the file extension
        *@return the file extension
        */
        CString GetFileExt() const;

        /**
        * Gets the file description
        *@return the file description
        */
        CString GetDescription() const;

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
        BOOL Exist() const;

        /**
        * Checks if file is opened in read-only mode
        *@return TRUE if file is opened in read-only mode, otherwise FALSE
        */
        BOOL IsReadOnly() const;

        /**
        * Sets the read-only flag, dependent of the parameter
        *@param readOnly - if TRUE, file is read-only
        *@return TRUE on success, otherwise FALSE
        */
        BOOL SetReadOnly(BOOL ReadOnly = TRUE);

        /**
        * Checks if the file is an archive
        *@return TRUE if the file is an archive, otherwise FALSE
        */
        BOOL IsArchive() const;

        /**
        * Sets the file as archive
        *@param archive - if TRUE the file is an archive
        *@return TRUE on success, otherwise FALSE
        */
        BOOL SetArchive(BOOL Archive = TRUE);

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
        BOOL GetLastWriteTime(SYSTEMTIME& tm) const;

        /**
        * Gets the attachment type
        *@return the attachment type
        */
        virtual inline const IEAttachementType GetAttachementType() const;

        /**
        * Sets the attachment type
        *@param value - the attachment type
        */
        virtual inline void SetAttachementType(IEAttachementType value);

    protected:
        CString m_FileName;

    private:
        IEAttachementType m_AttachementType;
        char              m_Drive         [_MAX_DRIVE];
        char              m_Dir           [_MAX_DIR];
        char              m_FileNameBuffer[_MAX_FNAME];
        char              m_FileExt       [_MAX_EXT];

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
    std::unique_ptr<PSS_File> pFile(new PSS_File(*this));
    return pFile.release();
}
//---------------------------------------------------------------------------
const PSS_File::IEAttachementType PSS_File::GetAttachementType() const
{
    return m_AttachementType;
}
//---------------------------------------------------------------------------
void PSS_File::SetAttachementType(IEAttachementType value)
{
    m_AttachementType = value;
}
//---------------------------------------------------------------------------

#endif
