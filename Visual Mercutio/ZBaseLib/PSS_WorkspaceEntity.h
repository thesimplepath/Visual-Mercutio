/****************************************************************************
 * ==> PSS_WorkspaceEntity -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace entity                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkspaceEntityH
#define PSS_WorkspaceEntityH

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
#ifndef PSS_WorkspaceEntity
    #define PSS_WorkspaceEntity ZBWorkspaceEntity
#endif

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
* Workspace entity
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WorkspaceEntity : public CObject
{
    DECLARE_SERIAL(PSS_WorkspaceEntity)

    public:
        /**
        * Constructor
        *@param name - name
        *@param pParent - parent entity, NULL if root
        */
        PSS_WorkspaceEntity(const CString& name = "", PSS_WorkspaceEntity* pParent = NULL);

        virtual ~PSS_WorkspaceEntity();

        /**
        * Gets the parent entity
        *@return the parent entity, NULL if root entity
        */
        virtual inline PSS_WorkspaceEntity* GetParent();

        /**
        * Sets the parent entity
        *@param pPArent - the parent entity
        */
        virtual inline void SetParent(PSS_WorkspaceEntity* pParent);

        /**
        * Gets the root entity
        *@return the root entity
        */
        virtual inline PSS_WorkspaceEntity* GetRoot();

        /**
        * Checks if contains entity
        *@return true if contains entity, otherwise false
        */
        virtual bool ContainEntity() const;

        /**
        * Gets the entity count
        *@reuturn the entity count
        */
        virtual std::size_t GetEntityCount() const;

        /**
        * Gets the entity at index
        *@param index - index
        *@reuturn the entity, NULL if not found or on error
        */
        virtual PSS_WorkspaceEntity* GetEntityAt(std::size_t index);

        /**
        * Gets the entity name
        *@reuturn the entity name
        */
        virtual CString GetEntityName() const;

        /**
        * Sets the entity name
        *@param value - the entity name
        */
        virtual void SetEntityName(const CString& value);

        /**
        * Gets the entity description
        *@reuturn the entity description
        */
        virtual CString GetEntityDescription() const;

        /**
        * Sets the entity description
        *@param value - the entity description
        */
        virtual void SetEntityDescription(const CString& value);

        /**
        * Clears the extension list
        */
        virtual void ClearExtensionList();

        /**
        * Gets the extension list
        *@return the extension list, NULL if not found or on error
        */
        virtual CStringArray* GetExtensionList();

        /**
        * Gets the extension list
        *@param[out] extensions - the string containing the extension list on function ends
        */
        virtual void GetExtensionList(CString& extensions);

        /**
        * Sets the extension list
        *@param extensionArray - the extension array to set
        */
        virtual void SetExtensionList(const CStringArray& extensionArray);

        /**
        * Sets the extension list
        *@param extensions - the extensions to set
        */
        virtual void SetExtensionList(const CString& extensions);

        /**
        * Adds elements to the extension list
        *@param extensionArray - the extension array containing the elements to set
        */
        virtual void AddElementToExtensionList(const CStringArray& extensionArray);

        /**
        * Checks if an extension is contained in the list
        *@param extension - extension
        *@return true if the extension is contained in the list, otherwise false
        */
        virtual bool ContainThisExtension(const CString& extension);

        /**
        * Checks if a file name is defined
        *@return true if a file name is defined, otherwise false
        */
        virtual bool HasFileName() const;

        /**
        * Gets the file name
        *@return the file name
        */
        virtual CString GetFileName() const;

        /**
        * Sets the file name
        *@param value - the file name
        */
        virtual void SetFileName(const CString& value);

        /**
        * Gets the file title
        *@return the file title
        */
        virtual CString GetFileTitle() const;

        /**
        * Gets the file path
        *@return the file path
        */
        virtual CString GetFilePath() const;

        /**
        * Gets the file extension
        *@return the file extension
        */
        virtual CString GetFileExt() const;

        /**
        * Gets the file name icon
        *@return the file name icon
        */
        virtual HICON GetFileNameIcon() const;

        /**
        * Checks if properties are visible
        *@return true if properties are visible, otherwise false
        */
        virtual bool PropertiesVisible();

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

    private:
        PSS_WorkspaceEntity* m_pParent;
        CString              m_EntityName;
        CString              m_EntityDescription;
};

//---------------------------------------------------------------------------
// PSS_WorkspaceEntity
//---------------------------------------------------------------------------
PSS_WorkspaceEntity* PSS_WorkspaceEntity::GetParent()
{
    return m_pParent;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceEntity::SetParent(PSS_WorkspaceEntity* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
PSS_WorkspaceEntity* PSS_WorkspaceEntity::GetRoot()
{
    if (m_pParent)
        return m_pParent->GetRoot();

    return this;
}
//---------------------------------------------------------------------------

#endif
