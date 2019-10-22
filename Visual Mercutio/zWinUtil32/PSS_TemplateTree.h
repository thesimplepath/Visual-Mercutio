/****************************************************************************
 * ==> PSS_TemplateTree ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a template tree                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TemplateTreeH
#define PSS_TemplateTreeH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#include "Mfc.h"

// processsoft
#include "zBaseLib\PSS_TreeCtrl.h"
#include "zBaseLib\PSS_TemplateManager.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Template tree
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TemplateTree
{
    public:
        /**
        * Constructor
        *@param pTreeCtrl - tree control, can be NULL
        *@param pTemplateManager - template manager, can be NULL
        *@param includeFiles - if TRUE, files will be included
        */
        PSS_TemplateTree(PSS_TreeCtrl* pTreeCtrl = NULL, PSS_TemplateManager* pTemplateManager = NULL, BOOL includeFiles = FALSE);

        virtual ~PSS_TemplateTree();

        /**
        * Initializes the template tree
        *@param pTreeCtrl - tree control, can be NULL
        *@param pTemplateManager - template manager, can be NULL
        *@param includeFiles - if TRUE, files will be included
        */
        void Initialize(PSS_TreeCtrl* pTreeCtrl, PSS_TemplateManager* pTemplateManager, BOOL IncludeFiles = FALSE);

        /**
        * Re-initializes the template tree
        *@param pTreeCtrl - tree control, can be NULL
        *@param pTemplateManager - template manager, can be NULL
        *@param includeFiles - if TRUE, files will be included
        *@note This function will not work if the tree has never been initialized
        */
        void ReInitialize(PSS_TemplateManager* pTemplateManager, BOOL IncludeFiles = FALSE);

        /**
        * Refreshes the tree
        */
        void Refresh();

        /**
        * Adds the root item
        *@param pData - template dir data
        *@param iconIndex - icon index
        *@return newly added item handle, NULL on error
        */
        HTREEITEM AddRootItem(PSS_TemplateDir* pData, int iconIndex = 0);

        /**
        * Adds a sub item
        *@param pData - template dir data
        *@param hParentTreeItem - parent item handle to add to
        *@param iconIndex - icon index
        *@return newly added item handle, NULL on error
        */
        HTREEITEM AddSubItem(PSS_TemplateDir* pData, HTREEITEM hParentTreeItem, int iconIndex = 0);

        /**
        * Adds a sub item
        *@param pData - template file data
        *@param hParentTreeItem - parent item handle to add to
        *@param iconIndex - icon index
        *@return newly added item handle, NULL on error
        */
        HTREEITEM AddSubItem(PSS_TemplateFile* pData, HTREEITEM hParentTreeItem, int iconIndex = 0);

        /**
        * Adds file items
        *@param pData - template dir data
        *@param hParentTreeItem - parent item handle to add to
        *@param iconIndex - icon index
        */
        void AddFileItems(PSS_TemplateDir* pTemplateDir, HTREEITEM hParentTreeItem, int iconIndex = 0);

        /**
        * Gets the selected item name
        *@return the selected item name, NULL if no selection or on error
        */
        CString GetSelectedItemName();

        /**
        * Gets the selected template directory
        *@return the selected template directory, NULL if no selection or on error
        */
        PSS_TemplateDir* GetSelectedItemFolder();

        /**
        * Gets the selected item file
        *@return the selected item file, NULL if no selection or on error
        */
        PSS_TemplateFile* GetSelectedItemFile();

        /**
        * Select an item
        *@param name - item name to select
        *@return TRUE on success, otherwise false
        */
        BOOL SelectItemName(const CString& name);

    private:
        PSS_TemplateManager* m_pTemplateManager;
        PSS_TreeCtrl*        m_pTreeCtrl;
        BOOL                 m_IncludeFiles;
        bool                 m_Invalid;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_TemplateTree(const PSS_TemplateTree& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_TemplateTree& operator = (const PSS_TemplateTree& other);

        /**
        * Initializes the tree
        */
        void InitializeTree();
};

#endif
