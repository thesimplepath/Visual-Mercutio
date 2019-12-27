/****************************************************************************
 * ==> PSS_RulesEntity -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a rules entity                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RulesEntityH
#define PSS_RulesEntityH

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
#ifndef PSS_RulesEntity
    #define PSS_RulesEntity ZBRulesEntity
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
* Rules entity. An entity is a kind of group containing properties of a specific type
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_RulesEntity : public CObject
{
    DECLARE_SERIAL(PSS_RulesEntity)

    public:
        /**
        * Constructor
        *@param name - the entity name
        *@param description - the entity description
        *@param pParent - the parent entity, root entity if NULL
        */
        PSS_RulesEntity(const CString&   name        = _T(""),
                        const CString&   description = _T(""),
                        PSS_RulesEntity* pParent     = NULL);

        virtual ~PSS_RulesEntity();

        /**
        * Gets the parent entity
        *@return the parent entity
        */
        virtual inline PSS_RulesEntity* GetParent();

        /**
        * Sets the parent entity
        *@param pParent - the parent entity
        */
        virtual inline void SetParent(PSS_RulesEntity* pParent);

        /**
        * Gets the root entity
        *@return the root entity
        */
        virtual inline PSS_RulesEntity* GetRoot();

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
        virtual inline PSS_RulesEntity* GetEntityAt(std::size_t index);

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
        PSS_RulesEntity* m_pParent;
        CString          m_GUID;
        CString          m_EntityName;
        CString          m_EntityDescription;
};

//---------------------------------------------------------------------------
// PSS_RulesEntity
//---------------------------------------------------------------------------
PSS_RulesEntity* PSS_RulesEntity::GetParent()
{
    return m_pParent;
}
//---------------------------------------------------------------------------
void PSS_RulesEntity::SetParent(PSS_RulesEntity* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
PSS_RulesEntity* PSS_RulesEntity::GetRoot()
{
    if (m_pParent)
        return m_pParent->GetRoot();

    return this;
}
//---------------------------------------------------------------------------
bool PSS_RulesEntity::ContainEntity() const
{
    return false;
}
//---------------------------------------------------------------------------
std::size_t PSS_RulesEntity::GetEntityCount() const
{
    return 0;
}
//---------------------------------------------------------------------------
PSS_RulesEntity* PSS_RulesEntity::GetEntityAt(std::size_t index)
{
    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_RulesEntity::GetGUID() const
{
    return m_GUID;
}
//---------------------------------------------------------------------------
void PSS_RulesEntity::SetGUID(const CString& value)
{
    m_GUID = value;
}
//---------------------------------------------------------------------------
CString PSS_RulesEntity::GetEntityName() const
{
    return m_EntityName;
}
//---------------------------------------------------------------------------
void PSS_RulesEntity::SetEntityName(const CString& value)
{
    m_EntityName = value;
}
//---------------------------------------------------------------------------
CString PSS_RulesEntity::GetEntityDescription() const
{
    return m_EntityDescription;
}
//---------------------------------------------------------------------------
void PSS_RulesEntity::SetEntityDescription(const CString& value)
{
    m_EntityDescription = value;
}
//---------------------------------------------------------------------------
bool PSS_RulesEntity::ShowProperties()
{
    return false;
}
//---------------------------------------------------------------------------

#endif
