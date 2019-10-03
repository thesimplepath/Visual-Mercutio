/****************************************************************************
 * ==> PSS_WorkspaceWizardTemplateManager ----------------------------------*
 ****************************************************************************
 * Description : Provides a workspace wizard template manager               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkspaceWizardTemplateManagerH
#define PSS_WorkspaceWizardTemplateManagerH

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
#ifndef PSS_WorkspaceWizardTemplateManager
    #define PSS_WorkspaceWizardTemplateManager ZBWorkspaceWizardTemplateMg
#endif

// class name mapping
#ifndef PSS_WorkspaceWizardTemplateItem
    #define PSS_WorkspaceWizardTemplateItem ZBWorkspaceWizardTemplateItem
#endif

// forward class declaration
class PSS_WorkspaceWizardTemplateItem;

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
* Workspace wizard template item array
*/
typedef CCArray_T<PSS_WorkspaceWizardTemplateItem*, PSS_WorkspaceWizardTemplateItem*> PSS_WorkspaceWizardTemplateItemSet;

/**
* Workspace wizard template item iterator
*/
typedef Iterator_T<PSS_WorkspaceWizardTemplateItem*> PSS_WorkspaceWizardTemplateItemIterator;

/**
* Workspace wizard template manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WorkspaceWizardTemplateManager : public CObject
{
    DECLARE_SERIAL(PSS_WorkspaceWizardTemplateManager)

    public:
        PSS_WorkspaceWizardTemplateManager();
        virtual ~PSS_WorkspaceWizardTemplateManager();

        /**
        * Adds a template item
        *@param pItem - template item to add
        *@return true on success, otherwise false
        */
        virtual inline bool AddTemplateItem(PSS_WorkspaceWizardTemplateItem* pItem);

        /**
        * Gets a template item at index
        *@param index - index
        *@return the template item, NULL if not found or on error
        */
        virtual inline PSS_WorkspaceWizardTemplateItem* GetTemplateItemAt(std::size_t index);

        /**
        * Gets the item count
        *@return the item count
        */
        virtual inline std::size_t GetItemCount() const;

        /**
        * Gets the template item array
        *@return the template item array
        */
        virtual inline PSS_WorkspaceWizardTemplateItemSet* GetTemplateItemSet();

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
        PSS_WorkspaceWizardTemplateItemSet m_Set;
};

//---------------------------------------------------------------------------
// PSS_WorkspaceWizardTemplateManager
//---------------------------------------------------------------------------
bool PSS_WorkspaceWizardTemplateManager::AddTemplateItem(PSS_WorkspaceWizardTemplateItem* pItem)
{
    m_Set.Add(pItem);
    return true;
}
//---------------------------------------------------------------------------
PSS_WorkspaceWizardTemplateItem* PSS_WorkspaceWizardTemplateManager::GetTemplateItemAt(std::size_t index)
{
    return (int(index) < m_Set.GetSize() ? m_Set.GetAt(index) : NULL);
}
//---------------------------------------------------------------------------
std::size_t PSS_WorkspaceWizardTemplateManager::GetItemCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------
PSS_WorkspaceWizardTemplateItemSet* PSS_WorkspaceWizardTemplateManager::GetTemplateItemSet()
{
    return &m_Set;
}
//---------------------------------------------------------------------------

#endif
