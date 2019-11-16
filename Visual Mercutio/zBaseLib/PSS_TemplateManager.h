/****************************************************************************
 * ==> PSS_TemplateManager -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a template manager                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TemplateManagerH
#define PSS_TemplateManagerH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_TemplateDir.h"

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
* Template manager, manages all templates contained in sub-directories
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TemplateManager
{
    public:
        PSS_TemplateManager();

        /**
        * Constructor
        *@param rootDirectory - root directory
        *@param fileExtension - file extension
        */
        PSS_TemplateManager(const CString& rootDirectory, const CString& fileExtension);

        virtual ~PSS_TemplateManager();

        /**
        * Creates the manager
        *@param rootDirectory - root directory
        *@param fileExtension - file extension
        */
        virtual BOOL Create(const CString& rootDirectory, const CString& fileExtension);

        /**
        * Scans all directories and reinitialize all template dir objects
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Scan();

        /**
        * Gets the template directory file count
        *@return the template directory file count
        */
        virtual inline std::size_t GetSize() const;

        /**
        * Gets the template directory object at the specified index
        *@return the template directory object, NULL if not found or on error
        */
        virtual inline PSS_TemplateDir* GetTemplateDirAt(std::size_t index);

        /**
        * Finds the template directory object matching with the template directory name
        *@param templateDir - template directory name to search
        *@return the template directory object, NULL if not found or on error
        */
        virtual PSS_TemplateDir* FindTemplateDir(const CString& templateDir);

        /**
        * Finds the template file matching with the template name
        *@return the template file, NULL if not found or on error
        */
        virtual PSS_TemplateFile* FindTemplate(const CString& templateName);

        /**
        * Gets the root caption matching with the root directory
        *@return the root caption, empty string if not found or on error
        */
        virtual CString GetRootCaption();

        /**
        * Moves the template file from a template to another
        *@param fileName - file name to move
        *@param sourceTemplateDir - source template directory name
        *@param destinationTemplateDir - destination template directory name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL MoveTemplateFile(const CString& fileName,
                                      const CString& sourceTemplateDir,
                                      const CString& destinationTemplateDir);

        /**
        * Moves the template file from a template to another
        *@param file - file to move
        *@param sourceTemplateDir - source template directory
        *@param destinationTemplateDir - destination template directory
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL MoveTemplateFile(PSS_TemplateFile& file,
                                      PSS_TemplateDir&  sourceTemplateDir,
                                      PSS_TemplateDir&  destinationTemplateDir);

        /**
        * Gets the root directory
        *@return the root directory
        */
        virtual inline const CString& GetRootDirectory() const;

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
        * Gets the template directory list
        *@return the template directory list
        */
        virtual inline const CStringArray& GetTemplateDirList() const;

    private:
        CStringArray m_TemplateDirList;
        CObArray     m_TemplateList;
        CString      m_RootDirectory;
        CString      m_FileExtension;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_TemplateManager(const PSS_TemplateManager& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_TemplateManager& operator = (const PSS_TemplateManager& other);

        /**
        * Frees the object list
        */
        void FreeList();
};

//---------------------------------------------------------------------------
// PSS_TemplateManager
//---------------------------------------------------------------------------
std::size_t PSS_TemplateManager::GetSize() const
{
    return std::size_t(m_TemplateList.GetSize());
}
//---------------------------------------------------------------------------
PSS_TemplateDir* PSS_TemplateManager::GetTemplateDirAt(std::size_t index)
{
    return (index <= std::size_t(m_TemplateList.GetSize()) ? (PSS_TemplateDir*)m_TemplateList[index] : NULL);
}
//---------------------------------------------------------------------------
const CString& PSS_TemplateManager::GetRootDirectory() const
{
    return m_RootDirectory;
}
//---------------------------------------------------------------------------
const CString PSS_TemplateManager::GetFileExtension() const
{
    return m_FileExtension;
}
//---------------------------------------------------------------------------
void PSS_TemplateManager::SetFileExtension(const CString& value)
{
    m_FileExtension = value;
}
//---------------------------------------------------------------------------
const CStringArray& PSS_TemplateManager::GetTemplateDirList() const
{
    return m_TemplateDirList;
}
//---------------------------------------------------------------------------

#endif
