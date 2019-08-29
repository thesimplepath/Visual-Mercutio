/****************************************************************************
 * ==> PSS_TemplateDir -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a template directory                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TemplateDirH
#define PSS_TemplateDirH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#include "Mfc.h"

// processsoft
#include "PSS_TemplateFile.h"

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
* Template directory, manage the template files contained in the template directory
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TemplateDir : public CObject
{
    DECLARE_DYNCREATE(PSS_TemplateDir)

    public:
        PSS_TemplateDir();

        /**
        * Constructor
        *@param directory - directory
        *@param title - title
        *@param fileExtension - file extension
        */
        PSS_TemplateDir(const CString& directory, const CString& title, const CString& fileExtension);

        virtual ~PSS_TemplateDir();

        /**
        * Finds a file in a template directory
        *@param fileName - file name
        *@return the file, NULL if not found or on error
        */
        virtual PSS_TemplateFile* FindFile(const CString& fileName);

        /**
        * Finds a file by title in a template directory
        *@param title - title
        *@return the file, NULL if not found or on error
        */
        virtual PSS_TemplateFile* FindTitle(const CString& title);

        /**
        * Create the template directory object
        *@param directory - directory
        *@param title - title
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(const CString& directory, const CString& title);

        /**
        * Gets the template file object at the specified index
        *@param index - index
        *@return the file, NULL if not found or on error
        */
        virtual inline PSS_TemplateFile* GetTemplateFileAt(std::size_t index);

        /**
        * Gets the template file count
        *@return the template file count
        */
        virtual inline std::size_t GetSize() const;

        /**
        * Gets the template directory
        *@return the template directory
        */
        virtual inline const CString GetDirectory() const;

        /**
        * Gets the directory title
        *@return thr directory title
        */
        virtual inline CString GetTitle();

        /**
        * Gets the file extension
        *@return the file extension
        */
        virtual inline const CString GetFileExtension() const;

        /**
        * Sets the file extension
        *@param value - the file extension
        */
        virtual inline void SetFileExtension(const CString& value);

        /**
        * Gets the template file list
        *@return the template file list
        */
        virtual inline const CStringArray& GetTemplateFileList() const;

    private:
        CStringArray m_TemplateFileList;
        CObArray     m_DirectoryList;
        CString      m_Directory;
        CString      m_Title;
        CString      m_FileExtension;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_TemplateDir(const PSS_TemplateDir& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_TemplateDir& operator = (const PSS_TemplateDir& other);

        /**
        * Frees the object list
        */
        void FreeList();
};

//---------------------------------------------------------------------------
// PSS_TemplateDir
//---------------------------------------------------------------------------
PSS_TemplateFile* PSS_TemplateDir::GetTemplateFileAt(std::size_t index)
{
    return (index <= std::size_t(m_DirectoryList.GetSize()) ? (PSS_TemplateFile*)m_DirectoryList[index] : NULL);
}
//---------------------------------------------------------------------------
std::size_t PSS_TemplateDir::GetSize() const
{
    return std::size_t(m_DirectoryList.GetSize());
}
//---------------------------------------------------------------------------
const CString PSS_TemplateDir::GetDirectory() const
{
    return m_Directory;
}
//---------------------------------------------------------------------------
CString PSS_TemplateDir::GetTitle()
{
    return m_Title;
}
//---------------------------------------------------------------------------
const CString PSS_TemplateDir::GetFileExtension() const
{
    return m_FileExtension;
}
//---------------------------------------------------------------------------
void PSS_TemplateDir::SetFileExtension(const CString& value)
{
    m_FileExtension = value;
}
//---------------------------------------------------------------------------
const CStringArray& PSS_TemplateDir::GetTemplateFileList() const
{
    return m_TemplateFileList;
}
//---------------------------------------------------------------------------

#endif
