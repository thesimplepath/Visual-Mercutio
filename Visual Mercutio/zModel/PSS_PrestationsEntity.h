/****************************************************************************
 * ==> PSS_PrestationsEntity -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a prestations entity                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PrestationsEntityH
#define PSS_PrestationsEntityH

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
#ifndef PSS_PrestationsEntity
    #define PSS_PrestationsEntity ZBPrestationsEntity
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
* Prestations entity. An entity is a kind of group containing properties of a specific type
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PrestationsEntity : public CObject
{
    DECLARE_SERIAL(PSS_PrestationsEntity)

    public:
        /**
        * Constructor
        *@param name - the entity name
        *@param description - the entity description
        *@param pParent - the parent entity, root entity if NULL
        */
        PSS_PrestationsEntity(const CString&         name        = _T(""),
                              const CString&         description = _T(""),
                              PSS_PrestationsEntity* pParent     = NULL);

        virtual ~PSS_PrestationsEntity();

        /**
        * Gets the parent entity
        *@return the parent entity
        */
        virtual inline PSS_PrestationsEntity* GetParent();

        /**
        * Sets the parent entity
        *@param pParent - the parent entity
        */
        virtual inline void SetParent(PSS_PrestationsEntity* pParent);

        /**
        * Gets the root entity
        *@return the root entity
        */
        virtual inline PSS_PrestationsEntity* GetRoot();

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
        virtual inline PSS_PrestationsEntity* GetEntityAt(std::size_t index);

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
        virtual inline bool ShowProperties() const;

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
        virtual void CreateGUID();

    private:
        PSS_PrestationsEntity* m_pParent;
        CString                m_GUID;
        CString                m_EntityName;
        CString                m_EntityDescription;
};

//---------------------------------------------------------------------------
// PSS_PrestationsEntity
//---------------------------------------------------------------------------
PSS_PrestationsEntity* PSS_PrestationsEntity::GetParent()
{
    return m_pParent;
}
//---------------------------------------------------------------------------
void PSS_PrestationsEntity::SetParent(PSS_PrestationsEntity* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
PSS_PrestationsEntity* PSS_PrestationsEntity::GetRoot()
{
    if (m_pParent)
        return m_pParent->GetRoot();

    return this;
}
//---------------------------------------------------------------------------
bool PSS_PrestationsEntity::ContainEntity() const
{
    return false;
}
//---------------------------------------------------------------------------
std::size_t PSS_PrestationsEntity::GetEntityCount() const
{
    return 0;
}
//---------------------------------------------------------------------------
PSS_PrestationsEntity* PSS_PrestationsEntity::GetEntityAt(std::size_t index)
{
    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_PrestationsEntity::GetGUID() const
{
    return m_GUID;
}
//---------------------------------------------------------------------------
void PSS_PrestationsEntity::SetGUID(const CString& value)
{
    m_GUID = value;
}
//---------------------------------------------------------------------------
CString PSS_PrestationsEntity::GetEntityName() const
{
    return m_EntityName;
}
//---------------------------------------------------------------------------
void PSS_PrestationsEntity::SetEntityName(const CString& value)
{
    m_EntityName = value;
}
//---------------------------------------------------------------------------
CString PSS_PrestationsEntity::GetEntityDescription() const
{
    return m_EntityDescription;
}
//---------------------------------------------------------------------------
void PSS_PrestationsEntity::SetEntityDescription(const CString& value)
{
    m_EntityDescription = value;
}
//---------------------------------------------------------------------------
bool PSS_PrestationsEntity::ShowProperties() const
{
    return false;
}
//---------------------------------------------------------------------------

#endif
