/****************************************************************************
 * ==> PSS_SymbolEntity ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol entity                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SymbolEntityH
#define PSS_SymbolEntityH

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
#ifndef PSS_SymbolEntity
    #define PSS_SymbolEntity ZBSymbolEntity
#endif

// stingray studio
#include "Foundation/Image/MFC/SECJPEG.H"

// processsoft
#include "ZBSymbolStamp.h"

// class name mapping
#ifndef PSS_Symbol
    #define PSS_Symbol ZBSymbol
#endif

// forward class declaration
class PSS_Symbol;

#ifdef _ZMODELEXPORT
    //put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

using namespace sfl;

/**
* Symbol entity. An entity is a kind of group containing properties of a specific type
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SymbolEntity : public CObject
{
    DECLARE_SERIAL(PSS_SymbolEntity)

    public:
        typedef CCArray_T <PSS_SymbolEntity*, PSS_SymbolEntity*> IEntitySet;
        typedef Iterator_T<PSS_SymbolEntity*>                    IEntityIterator;

        PSS_SymbolEntity();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_SymbolEntity(const PSS_SymbolEntity& other);

        virtual ~PSS_SymbolEntity();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_SymbolEntity& operator = (const PSS_SymbolEntity& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_SymbolEntity* Clone();

        /**
        * Gets the internal file version
        *@return the internal file version
        */
        virtual inline DWORD GetInternalFileVersion() const;

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
        * Gets the symbol stamp
        *@return the symbol stamp
        */
        virtual inline ZBSymbolStamp&       GetSymbolStamp();
        virtual inline const ZBSymbolStamp& GetSymbolStamp() const;

        /**
        * Gets the symbol
        *@return the symbol
        */
        virtual inline PSS_Symbol*       GetSymbol();
        virtual inline const PSS_Symbol* GetSymbol() const;

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

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Increments the published version of the file
        *@param fileName - the file name
        *@return the version number
        */
        virtual inline DWORD IncrementPublishVersionOfFile(const CString& fileName);

        /**
        * Decrements the published version of the file
        *@param fileName - the file name
        *@return the version number
        */
        virtual inline DWORD DecrementPublishVersionOfFile(const CString& fileName);

        /**
        * Gets the published version of the file
        *@param fileName - the file name
        *@return the version number
        */
        virtual inline DWORD GetPublishVersionOfFile(const CString& fileName);

        /**
        * Sets the published version of the file
        *@param fileName - the file name
        *@param version - the version number
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL SetPublishVersionOfFile(const CString& fileName, DWORD version);

    protected:
        ZBSymbolStamp m_SymbolStamp;
        PSS_Symbol*   m_pSymbol;

    private:
        SECJpeg m_Image;
};

//---------------------------------------------------------------------------
// PSS_SymbolEntity
//---------------------------------------------------------------------------
DWORD PSS_SymbolEntity::GetInternalFileVersion() const
{
    return m_SymbolStamp.GetInternalFileVersion();
}
//---------------------------------------------------------------------------
CString PSS_SymbolEntity::GetName() const
{
    return m_SymbolStamp.GetName();
}
//---------------------------------------------------------------------------
void PSS_SymbolEntity::SetName(const CString& value)
{
    m_SymbolStamp.SetName(value);
}
//---------------------------------------------------------------------------
CString PSS_SymbolEntity::GetDescription() const
{
    return m_SymbolStamp.GetDescription();
}
//---------------------------------------------------------------------------
void PSS_SymbolEntity::SetDescription(const CString& value)
{
    m_SymbolStamp.SetDescription(value);
}
//---------------------------------------------------------------------------
CString PSS_SymbolEntity::GetCategory() const
{
    return m_SymbolStamp.GetCategory();
}
//---------------------------------------------------------------------------
void PSS_SymbolEntity::SetCategory(const CString& value)
{
    m_SymbolStamp.SetCategory(value);
}
//---------------------------------------------------------------------------
CString PSS_SymbolEntity::GetAuthor() const
{
    return m_SymbolStamp.GetAuthor();
}
//---------------------------------------------------------------------------
void PSS_SymbolEntity::SetAuthor(const CString& value)
{
    m_SymbolStamp.SetAuthor(value);
}
//---------------------------------------------------------------------------
PSS_Date PSS_SymbolEntity::GetCreationDate() const
{
    return m_SymbolStamp.GetCreationDate();
}
//---------------------------------------------------------------------------
void PSS_SymbolEntity::SetCreationDate(const PSS_Date& value)
{
    m_SymbolStamp.SetCreationDate(value);
}
//---------------------------------------------------------------------------
PSS_Date PSS_SymbolEntity::GetModificationDate() const
{
    return m_SymbolStamp.GetModificationDate();
}
//---------------------------------------------------------------------------
void PSS_SymbolEntity::SetModificationDate(const PSS_Date& value)
{
    m_SymbolStamp.SetModificationDate(value);
}
//---------------------------------------------------------------------------
DWORD PSS_SymbolEntity::GetSymbolVersion() const
{
    return m_SymbolStamp.GetSymbolVersion();
}
//---------------------------------------------------------------------------
void PSS_SymbolEntity::SetSymbolVersion(DWORD value)
{
    m_SymbolStamp.SetSymbolVersion(value);
}
//---------------------------------------------------------------------------
ZBSymbolStamp& PSS_SymbolEntity::GetSymbolStamp()
{
    return m_SymbolStamp;
}
//---------------------------------------------------------------------------
const ZBSymbolStamp& PSS_SymbolEntity::GetSymbolStamp() const
{
    return m_SymbolStamp;
}
//---------------------------------------------------------------------------
PSS_Symbol* PSS_SymbolEntity::GetSymbol()
{
    return m_pSymbol;
}
//---------------------------------------------------------------------------
const PSS_Symbol* PSS_SymbolEntity::GetSymbol() const
{
    return m_pSymbol;
}
//---------------------------------------------------------------------------
DWORD PSS_SymbolEntity::IncrementPublishVersionOfFile(const CString& fileName)
{
    return m_SymbolStamp.IncrementPublishVersionOfFile(fileName);
}
//---------------------------------------------------------------------------
DWORD PSS_SymbolEntity::DecrementPublishVersionOfFile(const CString& fileName)
{
    return m_SymbolStamp.DecrementPublishVersionOfFile(fileName);
}
//---------------------------------------------------------------------------
DWORD PSS_SymbolEntity::GetPublishVersionOfFile(const CString& fileName)
{
    return m_SymbolStamp.GetPublishVersionOfFile(fileName);
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolEntity::SetPublishVersionOfFile(const CString& fileName, DWORD version)
{
    return m_SymbolStamp.SetPublishVersionOfFile(fileName, version);
}
//---------------------------------------------------------------------------

#endif
