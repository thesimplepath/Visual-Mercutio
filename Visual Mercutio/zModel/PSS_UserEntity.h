/****************************************************************************
 * ==> PSS_UserEntity ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user entity                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserEntityH
#define PSS_UserEntityH

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
#ifndef PSS_UserEntity
    #define PSS_UserEntity ZBUserEntity
#endif

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
* User entity. An entity is a kind of group containing properties of a specific type
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserEntity : public CObject
{
    DECLARE_SERIAL(PSS_UserEntity)

    public:
        /**
        * Constructor
        *@param name - the entity name
        *@param description - the entity description
        *@param cost - the entity cost
        *@param pParent - the parent entity, root entity if NULL
        */
        PSS_UserEntity(const CString&  name        = _T(""),
                       const CString&  description = _T(""),
                       const float     cost        = 0,
                       PSS_UserEntity* pParent     = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UserEntity(const PSS_UserEntity& src);

        virtual ~PSS_UserEntity();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_UserEntity& operator = (const PSS_UserEntity& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_UserEntity* Clone() const;

        /**
        * Gets the parent entity
        *@return the parent entity
        */
        virtual inline PSS_UserEntity* GetParent();

        /**
        * Sets the parent entity
        *@param pParent - the parent entity
        */
        virtual inline void SetParent(PSS_UserEntity* pParent);

        /**
        * Gets the root entity
        *@return the root entity
        */
        virtual inline PSS_UserEntity* GetRoot();

        /**
        * Checks if contains children entities
        *@return true if contains children entities, otherwise false
        */
        virtual inline bool ContainEntity() const;

        /**
        * Gets the entity count
        *@return the entity count
        */
        virtual inline std::size_t GetEntityCount() const;

        /**
        * Gets the entity at index
        *@return the entity at index
        */
        virtual inline PSS_UserEntity* GetEntityAt(std::size_t index);

        /**
        * Gets the guid
        *@return the guid
        */
        virtual inline CString GetGUID() const;

        /**
        * Sets the guid
        *@param value - the guid
        */
        virtual inline void SetGUID(const CString& value);

        /**
        * Gets the entity name
        *@return the entity name
        */
        virtual inline CString GetEntityName() const;

        /**
        * Sets the entity name
        *@param value - the entity name
        */
        virtual inline void SetEntityName(const CString& value);

        /**
        * Gets the entity description
        *@return the entity description
        */
        virtual inline CString GetEntityDescription() const;

        /**
        * Sets the entity description
        *@param value - the entity description
        */
        virtual inline void SetEntityDescription(const CString& value);

        /**
        * Gets the entity cost
        *@return the entity cost
        */
        virtual inline float GetEntityCost() const;

        /**
        * Sets the entity cost
        *@param value - the entity cost
        */
        virtual inline void SetEntityCost(const float value);

        /**
        * Checks if a role is contained in this entity
        *@param role - the role to check
        *@return true if the role is contained in this entity, otherwise false
        */
        virtual inline bool ContainThisRole(const CString& role);

        /**
        * Checks if the properties are shown
        *@return true if the properties are shown, otherwise false
        */
        virtual inline bool ShowProperties();

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
        /**
        * Creates a new GUID
        */
        void CreateGUID();

    private:
        PSS_UserEntity* m_pParent;
        CString         m_GUID;
        CString         m_EntityName;
        CString         m_EntityDescription;
        float           m_EntityCost;
};

//---------------------------------------------------------------------------
// PSS_UserEntity
//---------------------------------------------------------------------------
PSS_UserEntity* PSS_UserEntity::GetParent()
{
    return m_pParent;
}
//---------------------------------------------------------------------------
void PSS_UserEntity::SetParent(PSS_UserEntity* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
PSS_UserEntity* PSS_UserEntity::GetRoot()
{
    if (m_pParent)
        return m_pParent->GetRoot();

    return this;
}
//---------------------------------------------------------------------------
bool PSS_UserEntity::ContainEntity() const
{
    return false;
}
//---------------------------------------------------------------------------
std::size_t PSS_UserEntity::GetEntityCount() const
{
    return 0;
}
//---------------------------------------------------------------------------
PSS_UserEntity* PSS_UserEntity::GetEntityAt(std::size_t index)
{
    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_UserEntity::GetGUID() const
{
    return m_GUID;
}
//---------------------------------------------------------------------------
void PSS_UserEntity::SetGUID(const CString& value)
{
    m_GUID = value;
}
//---------------------------------------------------------------------------
CString PSS_UserEntity::GetEntityName() const
{
    return m_EntityName;
}
//---------------------------------------------------------------------------
void PSS_UserEntity::SetEntityName(const CString& value)
{
    m_EntityName = value;
}
//---------------------------------------------------------------------------
CString PSS_UserEntity::GetEntityDescription() const
{
    return m_EntityDescription;
}
//---------------------------------------------------------------------------
void PSS_UserEntity::SetEntityDescription(const CString& value)
{
    m_EntityDescription = value;
}
//---------------------------------------------------------------------------
float PSS_UserEntity::GetEntityCost() const
{
    return m_EntityCost;
}
//---------------------------------------------------------------------------
void PSS_UserEntity::SetEntityCost(const float value)
{
    m_EntityCost = value;
}
//---------------------------------------------------------------------------
bool PSS_UserEntity::ContainThisRole(const CString& role)
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_UserEntity::ShowProperties()
{
    return false;
}
//---------------------------------------------------------------------------

#endif
