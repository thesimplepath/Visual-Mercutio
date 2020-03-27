/****************************************************************************
 * ==> PSS_WorkspaceGroupEntity --------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace group entity                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkspaceGroupEntityH
#define PSS_WorkspaceGroupEntityH

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
#ifndef PSS_WorkspaceGroupEntity
    #define PSS_WorkspaceGroupEntity ZBWorkspaceGroupEntity
#endif

// class name mapping
#ifndef PSS_WorkspaceFileEntity
    #define PSS_WorkspaceFileEntity ZBWorkspaceFileEntity
#endif

// processsoft
#include "PSS_WorkspaceEntity.h"

// forward class declaration
class PSS_WorkspaceFileEntity;

#ifdef _ZBASELIBEXPORT
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
* Workspace group entity
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WorkspaceGroupEntity : public PSS_WorkspaceEntity
{
    DECLARE_SERIAL(PSS_WorkspaceGroupEntity)

    public:
        typedef CCArray_T<PSS_WorkspaceEntity*, PSS_WorkspaceEntity*> IEntitySet;
        typedef Iterator_T<PSS_WorkspaceEntity*>                      IEntityIterator;

        /**
        * Constructor
        *@param name - name
        *@param pParent - parent entity, NULL if root
        */
        PSS_WorkspaceGroupEntity(const CString& name = "", PSS_WorkspaceEntity* pParent = NULL);

        /**
        * Constructor
        *@param name - name
        *@param pExtensionList - extension list
        *@param pParent - parent entity, NULL if root
        */
        PSS_WorkspaceGroupEntity(const CString& name, CStringArray* pExtensionList, PSS_WorkspaceEntity* pParent = NULL);

        virtual ~PSS_WorkspaceGroupEntity();

        /**
        * Removes all the entities
        */
        virtual void RemoveAllEntities();

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
        * Gets the entity set
        *@return the entity set
        */
        virtual IEntitySet* GetEntitySet();

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
        virtual void AddElementToExtensionList(const CStringArray& ExtensionArray);

        /**
        * Checks if an extension is contained in the list
        *@param extension - extension
        *@return true if the extension is contained in the list, otherwise false
        */
        virtual bool ContainThisExtension(const CString& extension);

        /**
        * Checks if properties are visible
        *@return true if properties are visible, otherwise false
        */
        virtual bool PropertiesVisible();

        /**
        * Adds a group
        *@param name - name
        *@param pExtensionList - extension list
        *@return the newly added workspace group entity, NULL on error
        */
        virtual PSS_WorkspaceGroupEntity* AddGroup(const CString& name, CStringArray* pExtensionList = NULL);

        /**
        * Adds a group
        *@param name - name
        *@param pExtensionList - extension list
        *@param inGroupName - parent group name in which the group will be added
        *@return the newly added workspace group entity, NULL on error
        */
        virtual PSS_WorkspaceGroupEntity* AddGroup(const CString& name, CStringArray* pExtensionList, const CString& inGroupName);

        /**
        * Adds a group
        *@param name - name
        *@param pExtensionList - extension list
        *@param pInGroup - parent group in which the group will be added
        *@return the newly added workspace group entity, NULL on error
        */
        virtual PSS_WorkspaceGroupEntity* AddGroup(const CString&            name,
                                                   CStringArray*             pExtensionList,
                                                   PSS_WorkspaceGroupEntity* pInGroup);

        /**
        * Adds a group
        *@param name - name
        *@param pExtensionList - extension list
        *@return the newly added workspace group entity, NULL on error
        */
        virtual PSS_WorkspaceGroupEntity* AddGroup(const CString& name, const CString& extensions);

        /**
        * Adds a group
        *@param name - name
        *@param extensions - extensions
        *@param inGroupName - parent group name in which the group will be added
        *@return the newly added workspace group entity, NULL on error
        */
        virtual PSS_WorkspaceGroupEntity* AddGroup(const CString& name, const CString& extensions, const CString& inGroupName);

        /**
        * Adds a group
        *@param name - name
        *@param extensions - extensions
        *@param pInGroup - parent group in which the group will be added
        *@return the newly added workspace group entity, NULL on error
        */
        virtual PSS_WorkspaceGroupEntity* AddGroup(const CString&            name,
                                                   const CString&            extensions,
                                                   PSS_WorkspaceGroupEntity* pInGroup);

        /**
        * Removes a group
        *@param name - name
        *@param deeper - if true, the remove will be applied recursively
        *@return true on success, otherwise false
        */
        virtual bool RemoveGroup(const CString& name, bool deeper = false);

        /**
        * Removes a group
        *@param name - name
        *@param inGroupName - parent group name in which the group will be added
        *@return true on success, otherwise false
        */
        virtual bool RemoveGroup(const CString& name, const CString& inGroupName);

        /**
        * Removes a group
        *@param name - name
        *@param pInGroup - parent group in which the group will be added
        *@return true on success, otherwise false
        */
        virtual bool RemoveGroup(const CString& name, PSS_WorkspaceGroupEntity* pInGroup);

        /**
        * Removes a group
        *@param pGroup - group to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveGroup(PSS_WorkspaceGroupEntity* pGroup);

        /**
        * Finds a group
        *@param name - name
        *@param deeper - if true, the remove will be applied recursively
        *@return the group, NULL if not found or on error
        */
        virtual IEntitySet* FindGroup(const CString& name, bool deeper = false);

        /**
        * Finds a group
        *@param name - name
        *@param inGroupName - parent group name in which the group will be added
        *@return the group, NULL if not found or on error
        */
        virtual IEntitySet* FindGroup(const CString& name, const CString& inGroupName);

        /**
        * Finds a group
        *@param name - name
        *@param pInGroup - parent group in which the group will be added
        *@return the group, NULL if not found or on error
        */
        virtual IEntitySet* FindGroup(const CString& name, PSS_WorkspaceGroupEntity* pInGroup);

        /**
        * Checks if a group exists
        *@param name - name
        *@param deeper - if true, the remove will be applied recursively
        *@return true if the group exists, otherwise false
        */
        virtual bool GroupExist(const CString& name, bool deeper = false);

        /**
        * Checks if a group exists
        *@param name - name
        *@param inGroupName - parent group name in which the group will be added
        *@return true if the group exists, otherwise false
        */
        virtual bool GroupExist(const CString& name, const CString& inGroupName);

        /**
        * Checks if a group exists
        *@param name - name
        *@param pInGroup - parent group in which the group will be added
        *@return true if the group exists, otherwise false
        */
        virtual bool GroupExist(const CString& name, PSS_WorkspaceGroupEntity* pInGroup);

        /**
        * Adds a file
        *@param fileName - the file name
        *@return the added workspace file entity, NULL if not found or on error
        */
        virtual PSS_WorkspaceFileEntity* AddFile(const CString& fileName);

        /**
        * Adds a file
        *@param fileName - the file name
        *@param inGroupName - parent group name in which the group will be added
        *@return the added workspace file entity, NULL if not found or on error
        */
        virtual PSS_WorkspaceFileEntity* AddFile(const CString& fileName, const CString& inGroupName);

        /**
        * Adds a file
        *@param fileName - the file name
        *@param pInGroup - parent group in which the group will be added
        *@return the added workspace file entity, NULL if not found or on error
        */
        virtual PSS_WorkspaceFileEntity* AddFile(const CString& fileName, PSS_WorkspaceGroupEntity* pInGroup);

        /**
        * Removes a file
        *@param pFile - the file to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveFile(PSS_WorkspaceFileEntity* pFile);

        /**
        * Removes a file
        *@param fileName - the file name
        *@return true on success, otherwise false
        */
        virtual bool RemoveFile(const CString& fileName);

        /**
        * Removes a file
        *@param fileName - the file name
        *@param inGroupName - parent group name in which the group will be added
        *@return true on success, otherwise false
        */
        virtual bool RemoveFile(const CString& fileName, const CString& inGroupName);

        /**
        * Removes a file
        *@param fileName - the file name
        *@param pInGroup - parent group in which the group will be added
        *@return true on success, otherwise false
        */
        virtual bool RemoveFile(const CString& fileName, PSS_WorkspaceGroupEntity* pInGroup);

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
        IEntitySet        m_EntitySet;
        CStringArray      m_ExtensionList;

        /**
        * Finds a group (protected version)
        *@param name - name
        *@param deeper - if true, the remove will be applied recursively
        */
        virtual void FindGroupPvt(const CString& name, bool deeper = false);

        /**
        * Finds a group
        *@param name - name
        *@param pInGroup - parent group in which the group will be added
        */
        virtual void FindGroupPvt(const CString& name, PSS_WorkspaceGroupEntity* pInGroup);

        /**
        * Finds the first group
        *@param name - name
        *@param deeper - if true, the remove will be applied recursively
        *@return the group, NULL if not found or on error
        */
        virtual PSS_WorkspaceGroupEntity* FindFirstGroup(const CString& name, bool deeper = false);

        /**
        * Finds the first group
        *@param name - name
        *@param pInGroup - parent group in which the group will be added
        *@return the group, NULL if not found or on error
        */
        virtual PSS_WorkspaceGroupEntity* FindFirstGroup(const CString& name, PSS_WorkspaceGroupEntity* pInGroup);

        /**
        * Removes all the groups
        *@param groupArray - group array/
        *@return true on success, otherwise false
        */
        virtual bool RemoveGroups(IEntitySet& groupArray);

        /**
        * Recalculates the parent
        */
        virtual void RecalculateParent();

        /**
        * Parses the extension
        *@param extensions - extensions
        *@param[out] extensionArray - extension array
        *@return true on success, otherwise false
        */
        virtual bool ParseExtension(const CString& extensions, CStringArray& extensionArray);
};

#endif
