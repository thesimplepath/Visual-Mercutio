/****************************************************************************
 * ==> PSS_Directory -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a directory helper                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DirectoryH
#define PSS_DirectoryH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

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
* Generic directory
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Directory
{
    public:
        PSS_Directory();
        virtual ~PSS_Directory();

        /**
        * Creates a directory
        *@param directory - directory name to create
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL CreateDirectory(const CString& directory);

        /**
        * Deletes a directory
        *@param directory - directory name to delete
        *@param includeContents - if TRUE, the content will also be deleted, otherwise the function will fail if dir isn't empty
        *@param includeSubDirectory - if TRUE, sub-directories will also be deleted, otherwise the function will fail if dir isn't empty
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL DeleteDirectory(const CString& directory, BOOL includeContents = FALSE, BOOL includeSubDirectory = FALSE);

        /**
        * Deletes a file inside the directory
        *@param fileName - file name to delete
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL DeleteFile(const CString& file);

        /**
        * Deletes all files from a directory
        *@param directory - directory in which files should be deleted
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL DeleteFilesFromDirectory(const CString& directory);

        /**
        * Copies a file
        *@param srcFile - source file name to copy from
        *@param dstFile - destination file name to copy to
        *@param overwrite - if TRUE, the file will be overwritten if already exists in destination dir
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL CopyFile(const CString& srcFile, const CString& dstFile, BOOL overwrite = TRUE);

        /**
        * Moves a file
        *@param srcFile - source file name to move from
        *@param dstFile - destination file name to move to
        *@param overwrite - if TRUE, the file will be overwritten if already exists in destination dir
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL MoveFile(const CString& srcFile, const CString& dstFile, BOOL overwrite = TRUE);

        /**
        * Copies a file from a directory to another
        *@param srcDir - source directory to copy from
        *@param dstDir - destination directory to copy to
        *@param fileName - file name
        *@param overwrite - if TRUE, the file will be overwritten if already exists in destination dir
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL CopyFileFromToDirectory(const CString& srcDir,
                                            const CString& dstDir,
                                            const CString& fileName,
                                            BOOL           overwrite = TRUE);

        /**
        * Moves a file from a directory to another
        *@param srcDir - source directory to copy from
        *@param dstDir - destination directory to copy to
        *@param fileName - file name to copy
        *@param overwrite - if TRUE, the file will be overwritten if already exists in destination dir
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL MoveFileFromToDirectory(const CString& srcDir,
                                            const CString& dstDir,
                                            const CString& fileName,
                                            BOOL           overwrite = TRUE);

        /**
        * Copies all the files from a directory to another
        *@param srcDir - source directory to copy from
        *@param dstDir - destination directory to copy to
        *@param overwrite - if TRUE, the file will be overwritten if already exists in destination dir
        *@param includeSubDirectory - if TRUE, sub-directories will also be copied
        *@param createDir - if TRUE, the destination directory will be created if still not exists
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL CopyAllFilesFromToDirectory(const CString& srcDir,
                                                const CString& dstDir,
                                                BOOL           overwrite           = TRUE,
                                                BOOL           includeSubDirectory = FALSE,
                                                BOOL           createDir           = FALSE);

        /**
        * Moves a file from a directory to another
        *@param srcDir - source directory to copy from
        *@param dstDir - destination directory to copy to
        *@param overwrite - if TRUE, the file will be overwritten if already exists in destination dir
        *@param includeSubDirectory - if TRUE, the files in sub-directories will also be copied
        *@param createDir - if TRUE, the destination directory will be created if still not exists
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL MoveAllFilesFromToDirectory(const CString& srcDir,
                                                const CString& dstDir,
                                                BOOL           overwrite           = TRUE,
                                                BOOL           includeSubDirectory = FALSE,
                                                BOOL           createDir           = FALSE);

        /**
        * Finds the files matching with the filters inside the directory
        *@param filters - filters
        *@param directory - directory to search in
        *@param[out] fileArray - file array to populate with found files
        *@param includeSubDir - if true, sub-directories will be included in the search
        *@return found files count
        */
        static int FindFile(const CString& filters, CStringArray& fileArray);
        static int FindFile(const CString& filters, const CString& directory, CStringArray& fileArray, bool includeSubDir = false);

        /**
        * Normalizes the directory
        *@param directory - directory to normalize
        *@param checkFullPath - if true, the full path will be checked
        *@return the normalized directory
        */
        static CString NormalizeDirectory(const CString& directory, bool checkFullPath = false);

        /**
        * Gets the upper directory
        *@param directory - directory to search from
        *@return the upper directory
        */
        static CString GetUpperDirectory(const CString& directory);

        /**
        * Gets the short directory name
        *@param directory - source directory name
        *@return the short directory name
        */
        static CString GetShortDirectoryName(const CString& directory);

        /**
        * Checks if a directory exists
        *@param directory - directory name to check
        *@return TRUE if the directory exists, otherwise FALSE
        */
        static BOOL Exist(const CString& directory);

        /**
        * Gets the current directory
        *@return the current directory
        */
        static CString GetCurrentDirectory();

        /**
        * Changes the current directory
        *@param directory - directory name to change to
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL ChangeCurrentDirectory(const CString& directory);
};

#endif
