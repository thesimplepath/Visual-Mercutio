/****************************************************************************
 * ==> PSS_TemplateFile ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a template file                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TemplateFileH
#define PSS_TemplateFileH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_TemplateFile
    #define PSS_TemplateFile ZDTemplateFile
#endif

// processsoft
#include "PSS_FolderStamp.h"

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
* Template file, encapsulate information of a template file
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TemplateFile : public CObject
{
    DECLARE_SERIAL(PSS_TemplateFile)

    public:
        /**
        * Constructor
        *@param fileName - file name
        */
        PSS_TemplateFile(const CString& fileName = "");

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_TemplateFile(const PSS_TemplateFile& other);

        virtual ~PSS_TemplateFile();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_TemplateFile& operator = (const PSS_TemplateFile& other);

        /**
        * Stores from the archive to the file
        *@param ar - archive
        *@param file - file
        *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
        */
        AFX_EXT_API friend CArchive& operator >> (CArchive& ar, PSS_TemplateFile& templateFile);

        /**
        * Stores the file to the archive
        *@param ar - archive
        *@param file - file
        *@return archive, to allow operator to be chained with other items, e.g a << b << c
        */
        AFX_EXT_API friend CArchive& operator << (CArchive& ar, const PSS_TemplateFile& templateFile);

        /**
        * Creates the object
        *@param fileName - file name
        */
        virtual BOOL Create(const CString& fileName);

        /**
        * Clones this object
        *@return the cloned object, NULL on error
        */
        virtual PSS_TemplateFile* Clone();

        /**
        * Checks if object is persistent
        *@return TRUE if object is persistent, otherwise FALSE
        */
        virtual inline BOOL IsPersistent() const;

        /**
        * Gets the title contained in the stamp member
        *@return the title contained in the stamp member
        */
        virtual inline CString GetTitle() const;

        /**
        * Gets the description contained in the stamp member
        *@return the description contained in the stamp member
        */
        virtual inline CString GetDescription() const;

        /**
        * Gets the template file name
        *@return the template file name
        */
        virtual inline const CString GetFileName() const;

        /**
        * Gets the template stamp contained in the template file name
        *@return the template stamp
        */
        virtual inline const PSS_FolderStamp GetStamp() const;

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        PSS_FolderStamp m_Stamp;
        CString         m_FileName;
        BOOL            m_Persistent;
};

//---------------------------------------------------------------------------
// PSS_TemplateFile
//---------------------------------------------------------------------------
BOOL PSS_TemplateFile::IsPersistent() const
{
    return m_Persistent;
}
//---------------------------------------------------------------------------
CString PSS_TemplateFile::GetTitle() const
{
    return m_Stamp.GetTitle();
}
//---------------------------------------------------------------------------
CString PSS_TemplateFile::GetDescription() const
{
    return m_Stamp.GetDescription();
}
//---------------------------------------------------------------------------
const CString PSS_TemplateFile::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
const PSS_FolderStamp PSS_TemplateFile::GetStamp() const
{
    return m_Stamp;
}
//---------------------------------------------------------------------------

#endif
