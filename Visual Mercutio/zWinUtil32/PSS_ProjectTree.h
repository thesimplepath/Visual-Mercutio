/****************************************************************************
 * ==> PSS_ProjectTree -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a project tree                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProjectTreeH
#define PSS_ProjectTreeH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// forward class declaration
class ZDDocument;
class PSS_DocumentData;
class ZITreeCtrl;

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
* Project tree
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProjectTree
{
    public:
        /**
        * Constructor
        *@param pTreeCtrl - tree controller, can be NULL
        *@param pDoc - document, can be NULL
        *@param visibleOnly - visible only
        */
        PSS_ProjectTree(ZITreeCtrl* pTreeCtrl = NULL, ZDDocument* pDoc = NULL, BOOL visibleOnly = TRUE);

        virtual ~PSS_ProjectTree();

        /**
        * Initializes the project tree
        *@param pTreeCtrl - tree controller, can be NULL
        *@param pDoc - document, can be NULL
        *@param visibleOnly - visible only
        */
        void Initialize(ZITreeCtrl* pTreeCtrl, ZDDocument* pDoc, BOOL OnlyVisible = TRUE);

        /**
        * Empties the tree
        */
        void Empty();

        /**
        * Refreshes the tree
        */
        void Refresh();

        /**
        * Gets the selected document
        *@return the selected document, NULL if no selection or on error
        */
        PSS_DocumentData* GetSelectedDocument();

        /**
        * Gets the selected document title
        *@return the selected document title, empty string if no selection or on error
        */
        CString GetSelectedDocumentTitle();

        /**
        * Called when file list has changed
        */
        void OnFileListChanged();

    protected:
        ZDDocument* m_pDoc;
        ZITreeCtrl* m_pTreeCtrl;
        CString     m_InternalDocumentType;
        CString     m_ExternalDocumentType;
        BOOL        m_VisibleOnly;
        BOOL        m_HasBeenInitialized;

        /**
        * Adds a document type item
        *@param documentType - document type
        *@param iconIndex - icon index
        *@param hParent - parent item at which the document type item should be added, if NULL item will be added to the root item
        *@return newly added item handle, NULL on error
        */
        HTREEITEM AddDocumentTypeItem(const CString& documentType, int iconIndex, HTREEITEM hParent = NULL);

        /**
        * Adds a document item
        *@param pData - document data
        *@param hParentTreeItem - parent item at which the document item should be added, if NULL item will be added to the root item
        *@param iconIndex - icon index
        *@return newly added item handle, NULL on error
        */
        HTREEITEM AddDocumentItem(PSS_DocumentData* pData, HTREEITEM hParentTreeItem, int iconIndex);

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ProjectTree(const PSS_ProjectTree& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ProjectTree & operator = (const PSS_ProjectTree& other);

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
