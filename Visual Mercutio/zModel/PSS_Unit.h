/****************************************************************************
 * ==> PSS_Unit ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a document unit                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UnitH
#define PSS_UnitH

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
#ifndef PSS_Unit
    #define PSS_Unit ZBUnit
#endif

// processsoft
#include "zBaseLib\PSS_ProcessModelDocTmpl.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// forward class declaration
class PSS_ProcessGraphModelDoc;

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
* Document unit
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Unit : public CObject
{
    DECLARE_SERIAL(PSS_Unit)

    public:
        /**
        * Constructor
        *@param name - the unit name
        *@param fileName - the unit file name
        */
        PSS_Unit(const CString& name = "", const CString& fileName = "");

        virtual ~PSS_Unit();

        /**
        * Creates the unit
        *@param name - the unit name
        *@return true on success, otherwise false
        */
        virtual bool Create(const CString& name);

        /**
        * Creates the unit
        *@param name - the unit name
        *@param fileName - the unit file name
        *@return true on success, otherwise false
        */
        virtual bool Create(const CString& name, const CString& fileName);

        /**
        * Creates an unique key
        *@return the newly created unique key
        */
        virtual CString CreateUniqueKey();

        /**
        * Loads the unit
        *@param pDocTmpl - the document template
        *@return true on success, otherwise false
        */
        virtual bool LoadUnit(PSS_ProcessModelDocTmpl* pDocTmpl);

        /**
        * Unloads the unit
        *@return true on success, otherwise false
        */
        virtual bool UnloadUnit();

        /**
        * Checks if the unit was loaded
        *@return true if the unit was loaded, otherwise false
        */
        virtual inline bool IsLoaded() const;

        /**
        * Gets the unit document
        *@return the unit document
        */
        virtual inline PSS_ProcessGraphModelDoc* GetUnitDocument();

        /**
        * Gets the unit name
        *@return the unit name
        */
        virtual inline CString GetName() const;

        /**
        * Sets the unit name
        *@param value - the unit name
        */
        virtual inline void SetName(const CString& value);

        /**
        * Gets the unit key
        *@return the unit key
        */
        virtual inline CString GetKey() const;

        /**
        * Sets the unit key
        *@param value - the unit key
        */
        virtual inline void SetKey(const CString& value);

        /**
        * Gets the unit file name
        *@return the unit file name
        */
        virtual inline CString GetFileName() const;

        /**
        * Sets the unit file name
        *@param value - the unit file name
        */
        virtual inline void SetFileName(const CString& value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    protected:
        PSS_ProcessGraphModelDoc* m_pUnitDoc;
        CString                   m_Name;
        CString                   m_Key;
        CString                   m_FileName;

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Unit(const PSS_Unit& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Unit& operator = (const PSS_Unit& other);
};

//---------------------------------------------------------------------------
// PSS_Unit
//---------------------------------------------------------------------------
bool PSS_Unit::IsLoaded() const
{
    return m_pUnitDoc;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelDoc* PSS_Unit::GetUnitDocument()
{
    return m_pUnitDoc;
}
//---------------------------------------------------------------------------
CString PSS_Unit::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void PSS_Unit::SetName(const CString& value)
{
    m_Name = value;
}
//---------------------------------------------------------------------------
CString PSS_Unit::GetKey() const
{
    return m_Key;
}
//---------------------------------------------------------------------------
void PSS_Unit::SetKey(const CString& value)
{
    m_Key = value;
}
//---------------------------------------------------------------------------
CString PSS_Unit::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
void PSS_Unit::SetFileName(const CString& value)
{
    m_FileName = value;
}
//---------------------------------------------------------------------------

#endif
