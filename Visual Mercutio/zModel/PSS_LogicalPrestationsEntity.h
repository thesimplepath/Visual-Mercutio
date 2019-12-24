/****************************************************************************
 * ==> PSS_LogicalPrestationsEntity ----------------------------------------*
 ****************************************************************************
 * Description : Provides a logical prestations entity                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_LogicalPrestationsEntityH
#define PSS_LogicalPrestationsEntityH

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
#ifndef PSS_LogicalPrestationsEntity
    #define PSS_LogicalPrestationsEntity ZBLogicalPrestationsEntity
#endif

// processsoft
#include "ZBPrestationsEntity.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

using namespace sfl;

/**
* Logical prestations entity
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_LogicalPrestationsEntity : public ZBPrestationsEntity
{
    DECLARE_SERIAL(PSS_LogicalPrestationsEntity)

    public:
        typedef CCArray_T <ZBPrestationsEntity*, ZBPrestationsEntity*> IEntitySet;
        typedef Iterator_T<ZBPrestationsEntity*>                       IEntityIterator;

        /**
        * Constructor
        *@param name - the entity name
        *@param description - the entity description
        *@param pParent - the parent
        */
        PSS_LogicalPrestationsEntity(const CString&       name        = _T(""),
                                     const CString&       description = _T(""),
                                     ZBPrestationsEntity* pParent     = NULL);

        virtual ~PSS_LogicalPrestationsEntity();

        /**
        * Checks if this object contains an entity
        *@return true if this object contains an entity, otherwise false
        */
        virtual inline bool ContainEntity() const;

        /**
        * Gets the entity count
        *@return the entity count
        */
        virtual inline std::size_t GetEntityCount() const;

        /**
        * Gets the entity at index
        *@return the entity at index, NULL if not found or on error
        */
        virtual inline ZBPrestationsEntity* GetEntityAt(std::size_t index);

        /**
        * Gets the entity set
        *@return the entity set
        */
        virtual inline IEntitySet* GetEntitySet();

        /**
        * Checks if the entities were modified
        *@return TRUE if the entities were modified, otherwise FALSE
        */
        virtual inline BOOL IsModified();

        /**
        * Sets the entities as modified
        *@param value - if TRUE, the entities were modified
        */
        virtual inline void SetModifiedFlag(BOOL modified = TRUE);

        /**
        * Adds a prestation entity
        *@param name - the prestation name
        *@param description - the prestation description
        *@return the newly added prestation entity, NULL on error
        */
        virtual PSS_LogicalPrestationsEntity* AddPrestation(const CString& name, const CString& description);

        /**
        * Adds a prestation entity
        *@param name - the prestation name
        *@param description - the prestation description
        *@param inPrestationName - the prestation entity name in which this entity should be added
        *@return the newly added prestation entity, NULL on error
        */
        virtual PSS_LogicalPrestationsEntity* AddPrestation(const CString& name,
                                                            const CString& description,
                                                            const CString& inPrestationName);

        /**
        * Adds a prestation entity
        *@param name - the prestation name
        *@param description - the prestation description
        *@param pInPrestation - the prestation entity in which this entity should be added
        *@return the newly added prestation entity, NULL on error
        */
        virtual PSS_LogicalPrestationsEntity* AddPrestation(const CString&                name,
                                                            const CString&                description,
                                                            PSS_LogicalPrestationsEntity* pInPrestation);

        /**
        * Removes a prestation entity
        *@param name - the prestation name
        *@param deeper - if true, the prestation entity will be removed recursively in children
        *@return true on success, otherwise false
        */
        virtual bool RemovePrestation(const CString& name, bool deeper = false);

        /**
        * Removes a prestation entity
        *@param name - the prestation name
        *@param inPrestationName - the prestation entity name in which this entity should be removed
        *@return true on success, otherwise false
        */
        virtual bool RemovePrestation(const CString& name, const CString& inPrestationName);

        /**
        * Removes a prestation entity
        *@param name - the prestation name
        *@param pInPrestation - the prestation entity in which this entity should be removed
        *@return true on success, otherwise false
        */
        virtual bool RemovePrestation(const CString& name, PSS_LogicalPrestationsEntity* pInPrestation);

        /**
        * Removes a prestation entity
        *@param pPrestation - the prestation to remove
        *@return true on success, otherwise false
        */
        virtual bool RemovePrestation(PSS_LogicalPrestationsEntity* pPrestation);

        /**
        * Removes all the prestations entities
        */
        virtual void RemoveAllPrestationsEntities();

        /**
        * Finds a prestation from its guid
        *@param guid - the prestation guid to find
        *@param deeper - if true, the search will continue recursively in prestation children
        *@return the prestation, NULL if not found or on error
        */
        virtual ZBPrestationsEntity* FindPrestationByGUID(const CString& guid, bool deeper = false);

        /**
        * Finds a prestation
        *@param name - the prestation name to find
        *@param deeper - if true, the search will continue recursively in prestation children
        *@return the matching prestations, NULL if not found or on error
        */
        virtual IEntitySet* FindPrestation(const CString& name, bool deeper = false);

        /**
        * Finds a prestation
        *@param name - the prestation name to find
        *@param inPrestationName - the prestation entity name in which the search should begin
        *@return the matching prestations, NULL if not found or on error
        */
        virtual IEntitySet* FindPrestation(const CString& name, const CString& inPrestationName);

        /**
        * Finds a prestation
        *@param name - the prestation name to find
        *@param pInPrestation - the prestation entity in which the search should begin
        *@return the matching prestations, NULL if not found or on error
        */
        virtual IEntitySet* FindPrestation(const CString& name, PSS_LogicalPrestationsEntity* pInPrestation);

        /**
        * Checks if a prestation exists
        *@param name - the prestation name to find
        *@param deeper - if true, the search will continue recursively in prestation children
        *@return true if the prestation exists, otherwise false
        */
        virtual bool PrestationExist(const CString& name, bool deeper = false);

        /**
        * Checks if a prestation exists
        *@param name - the prestation name to find
        *@param inPrestationName - the prestation entity name in which the search should begin
        *@return true if the prestation exists, otherwise false
        */
        virtual bool PrestationExist(const CString& name, const CString& inPrestationName);

        /**
        * Checks if a prestation exists
        *@param name - the prestation name to find
        *@param pInPrestation - the prestation entity in which the search should begin
        *@return true if the prestation exists, otherwise false
        */
        virtual bool PrestationExist(const CString& name, PSS_LogicalPrestationsEntity* pInPrestation);

        /**
        * Moves a prestation
        *@param pPrestation - the prestation to move
        *@return true on success, otherwise false
        */
        virtual bool MovePrestation(ZBPrestationsEntity* pPrestation);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        static IEntitySet m_FindSet;
        static BOOL       m_Modified;
        IEntitySet        m_EntitySet;

        /**
        * Adds a prestation
        *@param pPrestation - the prestation to add
        *@return true on success, otherwise false
        */
        virtual inline bool AddPrestation(ZBPrestationsEntity* pPrestation);

        /**
        * Removes a prestation from the prestation set
        *@param pPrestation - the prestation to remove
        *@return true on success, otherwise false
        */
        virtual bool RemovePrestationFromSet(ZBPrestationsEntity* pPrestation);

        /**
        * Finds a prestation from its guid
        *@param guid - the prestation guid to find
        *@param deeper - if true, the search will continue recursively in prestation children
        *@return the prestation, NULL if not found or on error
        */
        virtual ZBPrestationsEntity* FindPrestationByGUIDPvt(const CString& guid, bool deeper = false);

        /**
        * Finds a prestation
        *@param name - the prestation name to find
        *@param deeper - if true, the search will continue recursively in prestation children
        *@return the matching prestations, NULL if not found or on error
        */
        virtual void FindPrestationPvt(const CString& name, bool deeper = false);

        /**
        * Finds a prestation
        *@param name - the prestation name to find
        *@param inPrestationName - the prestation entity name in which the search should begin
        *@return true if the prestation exists, otherwise false
        */
        virtual void FindPrestationPvt(const CString& name, PSS_LogicalPrestationsEntity* pInPrestation);

        /**
        * Finds the first prestation matching with the name
        *@param name - the prestation name to find
        *@param deeper - if true, the search will continue recursively in prestation children
        *@return the matching prestations, NULL if not found or on error
        */
        virtual PSS_LogicalPrestationsEntity* FindFirstPrestation(const CString& name, bool deeper = false);

        /**
        * Finds the first prestation matching with the name
        *@param name - the prestation name to find
        *@param inPrestationName - the prestation entity name in which the search should begin
        *@return true if the prestation exists, otherwise false
        */
        virtual PSS_LogicalPrestationsEntity* FindFirstPrestation(const CString&                name,
                                                                  PSS_LogicalPrestationsEntity* pInPrestation);

        /**
        * Removes all prestations in a set
        *@param set - the prestation set containing the prestations to remove
        *@return true on success, otherwise false
        */
        virtual bool RemovePrestations(IEntitySet& Set);

        /**
        * Recalculates the parent
        */
        virtual void RecalculateParent();
};

//---------------------------------------------------------------------------
// PSS_LogicalPrestationsEntity
//---------------------------------------------------------------------------
bool PSS_LogicalPrestationsEntity::ContainEntity() const
{
    return true;
}
//---------------------------------------------------------------------------
std::size_t PSS_LogicalPrestationsEntity::GetEntityCount() const
{
    return m_EntitySet.GetSize();
}
//---------------------------------------------------------------------------
ZBPrestationsEntity* PSS_LogicalPrestationsEntity::GetEntityAt(std::size_t index)
{
    return (index < GetEntityCount() ? m_EntitySet.GetAt(index) : NULL);
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity::IEntitySet* PSS_LogicalPrestationsEntity::GetEntitySet()
{
    return &m_EntitySet;
}
//---------------------------------------------------------------------------
BOOL PSS_LogicalPrestationsEntity::IsModified()
{
    return m_Modified;
}
//---------------------------------------------------------------------------
void PSS_LogicalPrestationsEntity::SetModifiedFlag(BOOL modified)
{
    m_Modified = modified;
}
//---------------------------------------------------------------------------
bool PSS_LogicalPrestationsEntity::AddPrestation(ZBPrestationsEntity* pPrestation)
{
    m_EntitySet.Add(pPrestation);
    return true;
}
//---------------------------------------------------------------------------

#endif
