/****************************************************************************
 * ==> PSS_FindFile --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a helper to find files                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FindFileH
#define PSS_FindFileH

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// std
#include <io.h>

// windows
#include <winver.h>
#include <dos.h>
#include <direct.h>

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
 * Helper to find files
 *@author Dominique Aigroz, Jean-Milost Reymond
 */
class PSS_FindFile
{
    public:
        /**
        * Constructor
        *@param[in, out] fileArray - array in which the found files will be added
        */
        PSS_FindFile(CStringArray& fileArray);

        /**
        * Gets the found file array
        *@return the found file array
        */
        virtual inline CStringArray& GetFoundFiles() const;

        /**
        * Copies the found files array
        *@param[out] fileArray - array in which the found files will be copied
        *@return copied file count
        */
        virtual int CopyFoundFileArray(CStringArray& fileArray);

        /**
        * Finds a file and adds it to the found file array
        *@param fileName - file name to search for
        *@param defaultDir - default directory to start to search from
        *@return found file count
        */
        virtual int FindFile(const CString& fileName, const CString& defaultDir = "");

    private:
        static int    m_Level;
        CStringArray& m_FoundFiles;
        CString       m_FoundFileName;
        CString       m_FileNameToSearch;
        CString       m_FullPath;
        BOOL          m_TranslateMessage;

        /**
        * Processes the search in main subdir and its subdirs
        *@return always 0 for now
        */
        int ProcessMainSubDir();

        /**
        * Gets the main sub directory
        *@return the main sub directory index in the array, -1 if not found or on error
        */
        int GetMainSubDir(CStringArray& dirArray);

        /**
        * Finds a file in a drive
        *@param fileName - file name to search for
        *@param drive - drive number
        *@return found file index in the array, -1 if not found or on error
        */
        int FindFileInDrive(const CString& fileName, int drive);

        /**
        * Finds a file in the current dir
        */
        void FindFileInCurrentDir();

        /**
        * Searches for the first sub-directory
        *@param pFileInfo - file info
        *@return TRUE if a sub-directory was found, otherwise FALSE
        */
        BOOL FirstSubDir(struct ::_finddata_t* pFileInfo);

        /**
        * Searches for and gets the next sub-directory
        *@param hFile - file handle
        *@param pFileInfo - file info
        *@return TRUE if a sub-directory was found, otherwise FALSE
        */
        BOOL NextSubDir(std::intptr_t hFile, struct ::_finddata_t* pFileInfo);

        /**
        * Searches for a file in a sub-directory
        *@return always FALSE for now
        */
        BOOL FindFileInSubDir();
};

//---------------------------------------------------------------------------
// PSS_FindFile
//---------------------------------------------------------------------------
CStringArray& PSS_FindFile::GetFoundFiles() const
{
    return m_FoundFiles;
}
//---------------------------------------------------------------------------

#endif
