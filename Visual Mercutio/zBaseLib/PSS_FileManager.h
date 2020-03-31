/****************************************************************************
 * ==> PSS_FileManager -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file manager, i.e a list of files. Implements   *
 *               methods to copy, move, or delete files                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FileManagerH
#define PSS_FileManagerH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_FileManager
    #define PSS_FileManager ZFileManager
#endif

// mfc
#include "mfc.h"

// processsoft
#include "PSS_File.h"

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
* File manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FileManager : public CObject
{
    DECLARE_SERIAL(PSS_FileManager)

    public:
        typedef CObject inherited;

        PSS_FileManager();
        virtual ~PSS_FileManager();

        /**
        * Adds a new file
        *@param fileName - file name to add
        *@param attachment - attachment
        */
        virtual void AddFile(const CString& fileName, PSS_File::IEAttachmentType attachement = PSS_File::IE_AT_InsertedFile);

        /**
        * Adds a new file
        *@param pFile - file to add
        */
        virtual inline void AddFile(PSS_File* pFile);

        /**
        * Gets the number of elements contained in the history manager
        *@return the number of elements contained in the history manager
        */
        virtual inline std::size_t GetCount();

        /**
        * Gets the file at index
        *@param index - index
        *@return the file at index, NULL if not found or on error
        */
        virtual inline PSS_File* GetAt(int index);

        /**
        * Removes the file located at the index
        *@param index - index
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveFile(int index);

        /**
        * Removes a specific file
        *@param pFile - file to remove
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveFile(PSS_File* pFile);

        /**
        * Removes a specific file
        *@param fileName - file name to remove
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveFile(const CString& fileName);

        /**
        * Removes all the files
        */
        virtual void RemoveAllFiles();

        /**
        * Searches if a specific file exists
        *@param fileName - file name to search
        *@return file on success, NULL if not found or on error
        */
        virtual PSS_File* FindFile(const CString& fileName);

        /**
        * Searches if a specific file exists
        *@param pFile - file to search
        *@return file on success, NULL if not found or on error
        */
        virtual PSS_File* FindFile(PSS_File* pFile);

        /**
        * Creates a temporary file name
        *@param drive - drive
        *@param prefix - prefix
        *@return the temporary file name
        *@note It is possible to specify:
        *      - the drive
        *      - the directory
        *      - the start file name
        *      - the extension
        */
        virtual CString GetTemporaryFileName(char drive = 0, const CString& prefix = _T(""));

        /**
        * Creates a temporary file name
        *@param drive - drive
        *@param prefix - prefix
        *@return the temporary file name
        *@note It is possible to specify:
        *      - the drive
        *      - the directory
        *      - the start file name
        *      - the extension
        */
        virtual CString GetTemporaryFileName(const CString& path   = _T(""),
                                             const CString& prefix = _T(""),
                                             const CString& ext    = _T(""));

        /**
        * Gets the temporary path
        *@return the temporary path, empty string on error
        */
        virtual CString GetTemporaryPath();

        /**
        * Serializes the file manager
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CObArray m_FileArray;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FileManager(const PSS_FileManager& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_FileManager& operator = (const PSS_FileManager& other);
};

//---------------------------------------------------------------------------
// PSS_FileManager
//---------------------------------------------------------------------------
void PSS_FileManager::AddFile(PSS_File* pFile)
{
    m_FileArray.Add(pFile);
}
//---------------------------------------------------------------------------
std::size_t PSS_FileManager::GetCount()
{
    return m_FileArray.GetSize();
}
//---------------------------------------------------------------------------
PSS_File* PSS_FileManager::GetAt(int index)
{
    return dynamic_cast<PSS_File*>(m_FileArray.GetAt(index));
}
//---------------------------------------------------------------------------

#endif
