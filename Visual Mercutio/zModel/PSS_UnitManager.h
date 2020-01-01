/****************************************************************************
 * ==> PSS_UnitManager -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an unit manager                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UnitManagerH
#define PSS_UnitManagerH

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
#ifndef PSS_UnitManager
    #define PSS_UnitManager ZBUnitManager
#endif

// processsoft
#include "zBaseLib\PSS_ProcessModelDocTmpl.h"
#include "PSS_Unit.h"

// class name mapping
#ifndef PSS_ModelSet
    #define PSS_ModelSet ZBModelSet
#endif

class PSS_ModelSet;

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
* Unit manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UnitManager : public CObject
{
    DECLARE_SERIAL(PSS_UnitManager)

    public:
        /**
        * Constructor
        *@param pDocTmpl - the document template
        */
        PSS_UnitManager(PSS_ProcessModelDocTmpl* pDocTmpl = NULL);

        virtual ~PSS_UnitManager();

        /**
        * Initializes the manager
        *@param pDocTmpl - the document template
        */
        virtual void Initialize(PSS_ProcessModelDocTmpl* pDocTmpl);

        /**
        * Fills the model set
        *@param[out] set - the model set
        *@return the model set item count
        */
        virtual std::size_t FillModelSet(PSS_ModelSet& set);

        /**
        * Creates a new unit
        *@param name - the unit name
        *@param fileName - the unit file name
        *@return true on success, otherwise false
        */
        virtual PSS_Unit* CreateNewUnit(const CString& name, const CString& fileName = "");

        /**
        * Adds an unit
        *@param pUnit - the unit to add
        *@return true on success, otherwise false
        */
        virtual bool AddUnit(PSS_Unit* pUnit);

        /**
        * Loads all the units
        *@return true on success, otherwise false
        */
        virtual bool LoadAllUnits();

        /**
        * Loads an unit
        *@param pUnit - the unit to load
        *@return true on success, otherwise false
        */
        virtual bool LoadUnit(PSS_Unit* pUnit);

        /**
        * Loads an unit
        *@param name - the unit name to load
        *@return true on success, otherwise false
        */
        virtual bool LoadUnit(const CString& name);

        /**
        * Loads an unit matching with a key
        *@param key - the unit key to load
        *@return true on success, otherwise false
        */
        virtual bool LoadUnitByKey(const CString& key);

        /**
        * Unloads all the units
        *@return true on success, otherwise false
        */
        virtual bool UnloadAllUnits();

        /**
        * Unloads an unit
        *@param pUnit - the unit to load
        *@return true on success, otherwise false
        */
        virtual bool UnloadUnit(PSS_Unit* pUnit);

        /**
        * Unloads an unit
        *@param name - the unit name to load
        *@return true on success, otherwise false
        */
        virtual bool UnloadUnit(const CString& name);

        /**
        * Unloads an unit matching with a key
        *@param key - the unit key to unload
        *@return true on success, otherwise false
        */
        virtual bool UnloadUnitByKey(const CString& key);

        /**
        * Removes all the units
        */
        virtual void RemoveAllUnits();

        /**
        * Removes an unit at index
        *@param index - the index
        *@return true on success, otherwise false
        */
        virtual bool RemoveUnitAt(std::size_t index);

        /**
        * Removes an unit
        *@param pUnit - the unit to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveUnit(PSS_Unit* pUnit);

        /**
        * Removes an unit
        *@param name - the unit name to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveUnit(const CString& name);

        /**
        * Removes an unit matching with a key
        *@param key - the unit key to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveUnitByKey(const CString& key);

        /**
        * Finds an unit
        *@param name - the unit name to find
        *@return the unit, NULL if not found or on error
        */
        virtual PSS_Unit* FindUnit(const CString& name);

        /**
        * Finds an unit matching with a key
        *@param key - the unit key to find
        *@return the unit, NULL if not found or on error
        */
        virtual PSS_Unit* FindUnitByKey(const CString& key);

        /**
        * Finds an unit index
        *@param name - the unit name for which the index should be found
        *@return the unit index, -1 if not found or on error
        */
        virtual int FindUnitIndex(const CString& name);

        /**
        * Finds an unit index matching with a key
        *@param key - the unit key for which the index should be found
        *@return the unit index, -1 if not found or on error
        */
        virtual int FindUnitIndexByKey(const CString& key);

        /**
        * Gets the unit at index
        *@param index - the index
        *@return the unit, NULL if not found or on error
        */
        virtual PSS_Unit* GetUnitAt(std::size_t index);

        /**
        * Gets the unit count
        *@return the unit count
        */
        virtual inline std::size_t GetUnitCount() const;

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        PSS_ProcessModelDocTmpl* m_pDocTmpl;
        CObArray                 m_UnitSet;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UnitManager(const PSS_UnitManager& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_UnitManager& operator = (const PSS_UnitManager& other);
};

//---------------------------------------------------------------------------
// PSS_UnitManager
//---------------------------------------------------------------------------
std::size_t PSS_UnitManager::GetUnitCount() const
{
    return std::size_t(m_UnitSet.GetSize());
}
//---------------------------------------------------------------------------

#endif
