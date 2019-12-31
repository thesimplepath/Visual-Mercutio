/****************************************************************************
 * ==> PSS_SymbolStamp -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol stamp                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SymbolStampH
#define PSS_SymbolStampH

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

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_SymbolStamp
    #define PSS_SymbolStamp ZBSymbolStamp
#endif

// processsoft
#include "zBaseLib\PSS_Date.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Symbol stamp
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SymbolStamp : public CObject
{
    DECLARE_SERIAL(PSS_SymbolStamp)

    public:
        PSS_SymbolStamp();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_SymbolStamp(const PSS_SymbolStamp& other);

        virtual ~PSS_SymbolStamp();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_SymbolStamp& operator = (const PSS_SymbolStamp& other);

        /**
        * Stores from the archive to the stamp
        *@param ar - the archive
        *@param stamp - the stamp
        *@return the archive, to allow operator to be chained with other items, e.g a >> b >> c
        */
        AFX_EXT_API friend CArchive& operator >> (CArchive& ar, PSS_SymbolStamp& Stamp);

        /**
        * Stores the stamp to the archive
        *@param ar - the archive
        *@param stamp - the stamp
        *@return the archive, to allow operator to be chained with other items, e.g a << b << c
        */
        AFX_EXT_API friend CArchive& operator << (CArchive& ar, const PSS_SymbolStamp& Stamp);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_SymbolStamp* Clone() const;

        /**
        * Gets the name
        *@return the name
        */
        virtual inline CString GetName() const;

        /**
        * Sets the name
        *@param value - the name
        */
        virtual inline void SetName(const CString& value);

        /**
        * Gets the description
        *@return the description
        */
        virtual inline CString GetDescription() const;

        /**
        * Sets the description
        *@param value - the description
        */
        virtual inline void SetDescription(const CString& value);

        /**
        * Gets the class name
        *@return the class name
        */
        virtual inline CString GetClassName() const;

        /**
        * Sets the class name
        *@param value - the class name
        */
        virtual inline void SetClassName(const CString& value);

        /**
        * Gets the category
        *@return the category
        */
        virtual inline CString GetCategory() const;

        /**
        * Sets the category
        *@param value - the category
        */
        virtual inline void SetCategory(const CString& value);

        /**
        * Gets the author
        *@return the author
        */
        virtual inline CString GetAuthor() const;

        /**
        * Sets the author
        *@param value - the author
        */
        virtual inline void SetAuthor(const CString& value);

        /**
        * Gets the creation date
        *@return the creation date
        */
        virtual inline PSS_Date GetCreationDate() const;

        /**
        * Sets the creation date
        *@param value - the creation date
        */
        virtual inline void SetCreationDate(const PSS_Date& value);

        /**
        * Gets the modification date
        *@return the modification date
        */
        virtual inline PSS_Date GetModificationDate() const;

        /**
        * Sets the modification date
        *@param value - the modification date
        */
        virtual inline void SetModificationDate(const PSS_Date& value);

        /**
        * Gets the symbol version
        *@return the symbol version
        */
        virtual inline DWORD GetSymbolVersion() const;

        /**
        * Sets the symbol version
        *@param value - the symbol version
        */
        virtual inline void SetSymbolVersion(DWORD value);

        /**
        * Gets the internal file version
        *@return the internal file version
        */
        virtual inline DWORD GetInternalFileVersion() const;

        /**
        * Sets the internal file version
        *@param value - the internal file version
        */
        virtual inline void SetInternalFileVersion(DWORD value);

        /**
        * Increments the published file version
        *@param fileName - the file name
        *@return the new published file version, -1 on error
        */
        virtual DWORD IncrementPublishVersionOfFile(const CString& fileName);

        /**
        * Decrements the published file version
        *@param fileName - the file name
        *@return the new published file version, -1 on error
        */
        virtual DWORD DecrementPublishVersionOfFile(const CString& fileName);

        /**
        * Gets the published file version
        *@param fileName - the file name
        *@return the published file version, -1 on error
        */
        virtual DWORD GetPublishVersionOfFile(const CString& fileName);

        /**
        * Sets the published file version
        *@param fileName - the file name
        *@param version - the file version
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetPublishVersionOfFile(const CString& fileName, DWORD version);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Reads the stamp from a file
        *@param fileName - the file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ReadFromFile(const CString& fileName);

        /**
        * Writes the stamp to a file
        *@param fileName - the file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL WriteToFile(const CString& fileName);

    private:
        CString  m_Name;
        CString  m_Description;
        CString  m_ClassName;
        CString  m_Category;
        CString  m_Author;
        PSS_Date m_CreationDate;
        PSS_Date m_ModificationDate;
        DWORD    m_SymbolVersion;
        DWORD    m_InternalFileVersion;
};

//---------------------------------------------------------------------------
// PSS_SymbolStamp
//---------------------------------------------------------------------------
CString PSS_SymbolStamp::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void PSS_SymbolStamp::SetName(const CString& value)
{
    m_Name = value;
}
//---------------------------------------------------------------------------
CString PSS_SymbolStamp::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------
void PSS_SymbolStamp::SetDescription(const CString& value)
{
    m_Description = value;
}
//---------------------------------------------------------------------------
CString PSS_SymbolStamp::GetClassName() const
{
    return m_ClassName;
}
//---------------------------------------------------------------------------
void PSS_SymbolStamp::SetClassName(const CString& value)
{
    m_ClassName = value;
}
//---------------------------------------------------------------------------
CString PSS_SymbolStamp::GetCategory() const
{
    return m_Category;
}
//---------------------------------------------------------------------------
void PSS_SymbolStamp::SetCategory(const CString& value)
{
    m_Category = value;
}
//---------------------------------------------------------------------------
CString PSS_SymbolStamp::GetAuthor() const
{
    return m_Author;
}
//---------------------------------------------------------------------------
void PSS_SymbolStamp::SetAuthor(const CString& value)
{
    m_Author = value;
}
//---------------------------------------------------------------------------
PSS_Date PSS_SymbolStamp::GetCreationDate() const
{
    return m_CreationDate;
}
//---------------------------------------------------------------------------
void PSS_SymbolStamp::SetCreationDate(const PSS_Date& value)
{
    m_CreationDate = value;
}
//---------------------------------------------------------------------------
PSS_Date PSS_SymbolStamp::GetModificationDate() const
{
    return m_ModificationDate;
}
//---------------------------------------------------------------------------
void PSS_SymbolStamp::SetModificationDate(const PSS_Date& value)
{
    m_ModificationDate = value;
}
//---------------------------------------------------------------------------
DWORD PSS_SymbolStamp::GetSymbolVersion() const
{
    return m_SymbolVersion;
}
//---------------------------------------------------------------------------
void PSS_SymbolStamp::SetSymbolVersion(DWORD value)
{
    m_SymbolVersion = value;
}
//---------------------------------------------------------------------------
DWORD PSS_SymbolStamp::GetInternalFileVersion() const
{
    return m_InternalFileVersion;
}
//---------------------------------------------------------------------------
void PSS_SymbolStamp::SetInternalFileVersion(DWORD value)
{
    m_InternalFileVersion = value;
}
//---------------------------------------------------------------------------

#endif
