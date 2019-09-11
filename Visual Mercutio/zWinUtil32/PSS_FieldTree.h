/****************************************************************************
 * ==> PSS_FieldTree -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a field tree                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FieldTreeH
#define PSS_FieldTreeH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZITreeCtl.h"
#include "zBaseLib\ZDDoc.h"
#include "zBaseLib\PSS_FieldRepository.h"

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
* Field tree
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FieldTree
{
    public:
        /**
        * Constructor
        *@param pTreeCtrl - tree control, can be NULL
        *@param pDoc - document, can be NULL
        *@param pFieldRepository - field repository, can be NULL
        */
        PSS_FieldTree(ZITreeCtrl* pTreeCtrl = NULL, ZDDocument* pDoc = NULL, PSS_FieldRepository* pFieldRepository = NULL);

        virtual ~PSS_FieldTree();

        /**
        * Initializes the tree
        *@param pTreeCtrl - tree control
        *@param pDoc - document
        *@param pFieldRepository - field repository, can be NULL
        */
        virtual void Initialize(ZITreeCtrl* pTreeCtrl, ZDDocument* pDoc, PSS_FieldRepository* pFieldRepository = NULL);

        /**
        * Empties the tree
        */
        virtual void Empty();

        /**
        * Refreshes the tree
        */
        virtual void Refresh();

        /**
        * Gets the selected repository field
        *@return the selected repository field, NULL if not found or on error
        */
        virtual PSS_FieldObjectDefinition* GetSelectedRepositoryField();

        /**
        * Gets the selected document field
        *@return the selected document field, NULL if not found or on error
        */
        virtual PSS_PlanFinObject* GetSelectedDocumentField();

        /**
        * Called when field changed
        */
        virtual void OnFieldListChanged();

    protected:
        ZITreeCtrl*          m_pTreeCtrl;
        ZDDocument*          m_pDoc;
        PSS_FieldRepository* m_pFieldRepository;
        CString              m_DocumentType;
        CString              m_RepositoryType;
        CString              m_NoDocument;
        CString              m_NoRepository;
        BOOL                 m_HasBeenInitialized;

        /**
        * Adds a type item
        *@param fieldType - field type to add
        *@param iconIndex - icon index
        *@param hParentTreeItem - parent tree in which the item will be added, if NULL will be added to the root item
        *@return newly added item handle, NULL on error
        */
        virtual HTREEITEM AddTypeItem(const CString& fieldType, int iconIndex, HTREEITEM hParentTreeItem = NULL);

        /**
        * Adds a documentation item
        *@param pData - document data to add
        *@param hParentTreeItem - parent tree in which the item will be added
        *@param iconIndex - icon index
        *@return newly added item handle, NULL on error
        */
        virtual HTREEITEM AddDocumentItem(PSS_DocumentData* pData, HTREEITEM hParentTreeItem, int iconIndex);

        /**
        * Adds a repository field item
        *@param pField - repository field to add
        *@param hParentTreeItem - parent tree in which the item will be added
        */
        virtual void AddRepositoryFieldItem(PSS_FieldObjectDefinition* pField, HTREEITEM hParentTreeItem);

        /**
        * Adds a document field item
        *@param pObj - document field object to add
        *@param hParentTreeItem - parent tree in which the item will be added
        *@return newly added item handle, NULL on error
        */
        virtual HTREEITEM AddDocumentFieldItem(PSS_PlanFinObject* pObj, HTREEITEM hParentTreeItem);

        /**
        * Gets the item index
        *@param pObj - object for which the item index should be found
        *@return item index, -1 if not found or on error
        */
        virtual int GetItemIndex(PSS_PlanFinObject* pObj);

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FieldTree(const PSS_FieldTree& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_FieldTree& operator = (const PSS_FieldTree& other);

        /**
        * Creates the tree
        */
        void CreateTree();

        /**
        * Initializes the tree
        */
        void InitializeTree();
};

#endif
