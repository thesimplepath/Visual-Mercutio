/****************************************************************************
 * ==> PSS_ModelTree -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic model tree interface                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ModelTreeH
#define PSS_ModelTreeH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_ObjectCollections.h"

// class name mapping
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif

// forward class declaration
class ZDProcessGraphPage;
class PSS_TreeCtrl;
class ZBModelSet;
class ZBSymbol;
class PSS_LinkSymbol;
class ZDProcessGraphModelMdl;

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
* Basic model tree interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ModelTree
{
    public:
        /**
        * Constructor
        *@param pTreeCtrl - the tree controller
        *@param rootName - the root name
        *@param pModelSet - the model set
        *@param imageResID - the image resource identifier
        *@param pSet - the runtime class set
        */
        PSS_ModelTree(PSS_TreeCtrl*        pTreeCtrl  =  NULL,
                      const CString&       rootName   =  _T(""),
                      ZBModelSet*          pModelSet  =  NULL,
                      UINT                 imageResID = -1,
                      PSS_RuntimeClassSet* pSet       =  NULL);

        virtual ~PSS_ModelTree();

        /**
        * Initializes the class
        *@param pTreeCtrl - the tree controller
        *@param rootName - the root name
        *@param pModelSet - the model set
        *@param imageResID - the image resource identifier
        *@param pSet - the runtime class set
        */
        virtual void Initialize(PSS_TreeCtrl*        pTreeCtrl,
                                const CString&       rootName   =  _T(""),
                                ZBModelSet*          pModelSet  =  NULL,
                                UINT                 imageResID = -1,
                                PSS_RuntimeClassSet* pSet       =  NULL);

        /**
        * Sets the root name
        *@param rootName - the root name
        */
        virtual void SetRootName(const CString& rootName);

        /**
        * Empties the model tree
        */
        virtual void Empty();

        /**
        * Refreshes the model tree
        */
        virtual void Refresh();

        /**
        * Gets the symbol
        *@param hItem - item handle
        *@return the symbol
        */
        virtual CODSymbolComponent* GetSymbol(HTREEITEM hItem);

        /**
        * Gets the model
        *@param hItem - item handle
        *@return the model
        */
        virtual ZDProcessGraphModelMdl* GetModel(HTREEITEM hItem);

        /**
        * Gets the page
        *@param hItem - item handle
        *@return the page
        */
        virtual ZDProcessGraphPage* GetPage(HTREEITEM hItem);

        /**
        * Gets the owner model
        *@param hItem - item handle
        *@return the owner model
        */
        virtual ZDProcessGraphModelMdl* GetOwnerModel(HTREEITEM hItem);

        /**
        * Gets the selected model
        *@return the selected model
        */
        virtual ZDProcessGraphModelMdl* GetSelectedModel();

        /**
        * Gets the selected symbol
        *@return the selected symbol
        */
        virtual CODSymbolComponent* GetSelectedSymbol();

        /**
        * Gets the selected page
        *@return the selected page
        */
        virtual ZDProcessGraphPage* GetSelectedPage();

        /**
        * Gets the selected owner model
        *@return the selected owner model
        */
        virtual ZDProcessGraphModelMdl* GetSelectedOwnerModel();

        /**
        * Checks if the item root is selected
        *@return true if the item root is selected, otherwise false
        */
        virtual bool IsRootSelected() const;

        /**
        * Checks if the document is selected
        *@return true if the document is selected, otherwise false
        */
        virtual bool IsDocumentSelected() const;

        /**
        * Adds a model
        *@param pModel - the model to add
        */
        virtual void AddModel(ZDProcessGraphModelMdl* pModel);

        /**
        * Removes a model
        *@param pModel - the model to remove
        */
        virtual void RemoveModel(ZDProcessGraphModelMdl* pModel);

        /**
        * Adds a model set
        *@param pModelSet - the model set to add
        */
        virtual void AddModelSet(ZBModelSet* pModelSet);

        /**
        * Removes a model
        *@param pModelSet - the model set to remove
        */
        virtual void RemoveModelSet(ZBModelSet* pModelSet);

        /**
        * Adds a symbol
        *@param pSymbol - the symbol to add
        *@param pModel - the model
        *@param checkUnique - if true, the symbol will be added only if still not exists in the model
        */
        virtual void AddSymbol(CODSymbolComponent*     pSymbol,
                               ZDProcessGraphModelMdl* pModel      = NULL,
                               bool                    checkUnique = true);

        /**
        * Removes a symbol
        *@param pSymbol - the symbol to remove
        *@param pModel - the model
        */
        virtual void RemoveSymbol(CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel = NULL);

        /**
        * Modifies a symbol
        *@param pSymbol - the symbol to modify
        *@param pModel - the model
        */
        virtual void ModifySymbol(CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel = NULL);

        /**
        * Called when the symbol is selected
        */
        virtual void DoSelectSymbol();

        /**
        * Called when the model changes
        */
        virtual void OnModelChange();

        /**
        * Called when the model tree is double clicked
        */
        virtual void OnDoubleClick();

    protected:
        HTREEITEM     m_hRootDocument;
        ZBModelSet*   m_pModelSet;
        PSS_TreeCtrl* m_pTreeCtrl;
        CString       m_RootName;
        UINT          m_ImageResID;
        BOOL          m_HasBeenInitialized;

        /**
        * Processes the model set
        *@param pModelSet - the model set to process
        *@param hParentTreeItem - the parent tree item handle
        */
        virtual void ProcessModelSet(ZBModelSet* pModelSet, HTREEITEM hParentTreeItem);

        /**
        * Processes the root model
        *@param pModel - the root model to process
        *@param hParentTreeItem - the parent tree item handle
        */
        virtual void ProcessRootModel(ZDProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem);

        /**
        * Processes the model by page set
        *@param pModel - the model to process
        *@param hParentTreeItem - the parent tree item handle
        */
        virtual void ProcessModelByPageSet(ZDProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem);

        /**
        * Processes the model
        *@param pModel - the model to process
        *@param hParentTreeItem - the parent tree item handle
        */
        virtual void ProcessModel(ZDProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem);

        /**
        * Processes the symbol
        *@param pSymbol - the symbol to process
        *@param hParentTreeItem - the parent tree item handle
        */
        virtual void ProcessSymbol(ZBSymbol* pSymbol, HTREEITEM hParentTreeItem);

        /**
        * Processes the link symbol
        *@param pModelSet - the link symbol to process
        *@param hParentTreeItem - the parent tree item handle
        */
        virtual void ProcessLinkSymbol(PSS_LinkSymbol* pSymbol, HTREEITEM hParentTreeItem);

        /**
        * Adds a type item
        *@param name - the item name
        *@param iconIndex - the icon index
        *@param hParentTreeItem - the parent tree item handle
        *@return the newly added item handle, NULL on error
        */
        virtual HTREEITEM AddTypeItem(const CString& name, int iconIndex, HTREEITEM hParentTreeItem = NULL);

        /**
        * Adds a model item
        *@param pModel - the model
        *@param hParentTreeItem - the parent tree item handle
        *@return the newly added item handle, NULL on error
        */
        virtual HTREEITEM AddModelItem(ZDProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem);

        /**
        * Adds a symbol item
        *@param pSymbol - the symbol
        *@param hParentTreeItem - the parent tree item handle
        *@return the newly added item handle, NULL on error
        */
        virtual HTREEITEM AddSymbolItem(ZBSymbol* pSymbol, HTREEITEM hParentTreeItem);

        /**
        * Adds a link symbol item
        *@param pSymbol - the link symbol
        *@param hParentTreeItem - the parent tree item handle
        *@return the newly added item handle, NULL on error
        */
        virtual HTREEITEM AddLinkSymbolItem(PSS_LinkSymbol* pSymbol, HTREEITEM hParentTreeItem);

        /**
        * Adds a page item
        *@param pPage - the page
        *@param hParentTreeItem - the parent tree item handle
        *@return the newly added item handle, NULL on error
        */
        virtual HTREEITEM AddPageItem(ZDProcessGraphPage* pPage, HTREEITEM hParentTreeItem);

        /**
        * Modifies a model item
        *@param pModel - the model
        *@param hItem - the item handle
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ModifyModelItem(ZDProcessGraphModelMdl* pModel, HTREEITEM hItem);

        /**
        * Modifies a symbol item
        *@param pSymbol - the symbol
        *@param hItem - the item handle
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ModifySymbolItem(ZBSymbol* pSymbol, HTREEITEM hItem);

        /**
        * Modifies a link symbol item
        *@param pSymbol - the link symbol
        *@param hItem - the item handle
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ModifyLinkSymbolItem(PSS_LinkSymbol* pSymbol, HTREEITEM hItem);

        /**
        * Modifies a page item
        *@param pModel - the page
        *@param hItem - the item handle
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ModifyPageItem(ZDProcessGraphPage* pPage, HTREEITEM hItem);

    private:
        /**
        * Model tree data
        */
        class IData : public CObject
        {
            public:
                /**
                * Model tree data type
                */
                enum IEType
                {
                    IE_DT_Symbol,
                    IE_DT_LinkSymbol,
                    IE_DT_GraphPage,
                    IE_DT_Model,
                    IE_DT_String,
                    IE_DT_Unknown
                };

                IEType                  m_Type;
                ZBSymbol*               m_pSymbol;
                PSS_LinkSymbol*         m_pLinkSymbol;
                ZDProcessGraphPage*     m_pGraphPage;
                ZDProcessGraphModelMdl* m_pModel;
                CString                 m_Str;
                bool                    m_Collapsed;

                IData();

                /**
                * Constructor
                *@param pSymbol - symbol
                */
                IData(ZBSymbol* pSymbol);

                /**
                * Constructor
                *@param pLinkSymbol - link symbol
                */
                IData(PSS_LinkSymbol* pLinkSymbol);

                /**
                * Constructor
                *@param pGraphPage - graphic page
                */
                IData(ZDProcessGraphPage* pGraphPage);

                /**
                * Constructor
                *@param pModel - model
                */
                IData(ZDProcessGraphModelMdl* pModel);

                /**
                * Constructor
                *@param str - string
                */
                IData(const CString& str);

                virtual ~IData();

                /**
                * Checks if the item is collapsed
                *@return true if the item is collapsed, otherwise false
                */
                virtual inline bool IsCollapsed() const;

                /**
                * Sets the item as collapsed
                *@param value - if true, the item is collapsed
                */
                virtual inline void SetCollapsed(bool value = true);
        };

        typedef sfl::CCArray_T<IData*, IData*> IDataSet;
        typedef sfl::Iterator_T<IData*>        IDataIterator;

        IDataSet             m_DataSet;
        PSS_RuntimeClassSet* m_pSet;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ModelTree(const PSS_ModelTree& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ModelTree& operator = (const PSS_ModelTree& other);

        /**
        * Creates the tree
        */
        void CreateTree();

        /**
        * Initializes the tree
        */
        void InitializeTree();

        /**
        * Creates the empty model set
        *@return true on success, otherwise false
        */
        bool CreateEmptyModelSet();

        /**
        * Frees the model set
        */
        void FreeModelSet();

        /**
        * Checks if a model set exists
        *@return true if a model set exists, otherwise false
        */
        inline bool ModelSetExist() const;

        /**
        * Checks if the symbol is part of the set
        *@param pSymbol - the symbol to check
        *@return true if the symbol is part of the set, otherwise false
        */
        bool SymbolIsPartOfSet(CODComponent* pSymbol) const;

        /**
        * Empties the dataset
        */
        void EmptyDataSet();

        /**
        * Adds an element to the dataset
        *@param pElement - element to add
        *@return the matching dataset, NULL if not found or on error
        */
        IData* AddDataToSet(ZBSymbol*               pElement);
        IData* AddDataToSet(PSS_LinkSymbol*         pElement);
        IData* AddDataToSet(ZDProcessGraphPage*     pElement);
        IData* AddDataToSet(ZDProcessGraphModelMdl* pElement);
        IData* AddDataToSet(const CString&          element);

        /**
        * Deletes an element from the dataset
        *@param pElement - element to delete
        *@return true on success, otherwise false
        */
        bool DeleteElementFromDataSet(CODSymbolComponent*     pElement);
        bool DeleteElementFromDataSet(ZBSymbol*               pElement);
        bool DeleteElementFromDataSet(PSS_LinkSymbol*         pElement);
        bool DeleteElementFromDataSet(ZDProcessGraphPage*     pElement);
        bool DeleteElementFromDataSet(ZDProcessGraphModelMdl* pElement);
        bool DeleteElementFromDataSet(const CString&          element);

        /**
        * Finds an element from the dataset
        *@param pElement - element to find
        *@return the matching dataset, NULL if not found or on error
        */
        IData* FindElementFromDataSet(CODSymbolComponent*     pElement);
        IData* FindElementFromDataSet(ZBSymbol*               pElement);
        IData* FindElementFromDataSet(PSS_LinkSymbol*         pElement);
        IData* FindElementFromDataSet(ZDProcessGraphPage*     pElement);
        IData* FindElementFromDataSet(ZDProcessGraphModelMdl* pElement);
        IData* FindElementFromDataSet(const CString&          element);
};

//---------------------------------------------------------------------------
// PSS_ModelTree::IData
//---------------------------------------------------------------------------
bool PSS_ModelTree::IData::IsCollapsed() const
{
    return m_Collapsed;
}
//---------------------------------------------------------------------------
void PSS_ModelTree::IData::SetCollapsed(bool value)
{
    m_Collapsed = value;
}
//---------------------------------------------------------------------------
// PSS_ModelTree
//---------------------------------------------------------------------------
bool PSS_ModelTree::ModelSetExist() const
{
    return m_pModelSet;
}
//---------------------------------------------------------------------------

#endif
