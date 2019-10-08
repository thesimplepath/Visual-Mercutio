/****************************************************************************
 * ==> PSS_DirTreeCtrl -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a directory tree control                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DirTreeCtrlH
#define PSS_DirTreeCtrlH

#if _MSC_VER >= 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_NetResourceWrapper.h"
#include "zBaseLib\ZITreeCtl.h"

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
* Directory tree control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DirTreeCtrl : public ZITreeCtrl
{
    public:
        /**
        * Constructor
        *@param includeFile - it true, files will be included in tree
        */
        PSS_DirTreeCtrl(bool includeFile = false);

        virtual ~PSS_DirTreeCtrl();

        /**
        * Initializes the control
        *@param initialPath - initial path
        *@param clear - if true, the tree content will be cleared (not used here)
        *@param includeFile - it true, files will be included in tree
        */
        virtual void Initialize(const CString& initialPath = _T(""), bool clear = true, bool includeFile = false);

        /**
        * Gets the selected directory
        *@return the selected directory, empty string if no selection
        */
        virtual CString GetSelectedDirectory();

        /**
        * Sets the path
        *@param path - path
        */
        virtual void SetPath(const CString& path);

        /**
        * Checks if path is valid
        *@return true if path is valid, otherwise false
        */
        virtual inline bool IsValid() const;

        /**
        * Gets the no drop index image
        *@return the no drop index image
        */
        virtual inline int GetIndexOfNoDropImage() const;

        /**
        * Refreshes the control
        */
        virtual void Refresh();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_DirTreeCtrl)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnDestroy();
        afx_msg BOOL OnItemexpandingTree(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg BOOL OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CImageList m_ImageListTree;
        HTREEITEM  m_hNetworkRoot;
        CString    m_Path;
        bool       m_IsValid;
        bool       m_IncludeFile;
        bool       m_HasBeenInitialized;

        /**
        * Gets the item path
        *@param hItem - item for which the path should be get
        *@return the item path, empty string if not found or on error
        */
        CString GetItemPath(HTREEITEM hItem);

        /**
        * Populates the tree
        *@param path - path from which tree should be populated
        *@param hParent - parent item from which path content should be added in tree
        *@return true on success, otherwise false
        */
        bool PopulateTree(const CString& path, HTREEITEM hParent);

        /**
        * Enumerates the available network paths
        *@param hParent - parent item from which network paths should be added in tree
        *@return true on success, otherwise false
        */
        bool EnumNetwork(HTREEITEM hParent);

        /**
        * Inserts a path item in tree
        *@param hParent - parent item in which path item should be added
        *@param pNetResource - network resource
        *@param text - item text
        *@param fullName - item full name
        *@param imageIndex - image index
        *@param imageSelectedIndex - image selected index
        *@return newly added tree item handle, NULL on error
        */
        HTREEITEM InsertPathItem(HTREEITEM      hParent,
                                 NETRESOURCE*   pNetResource,
                                 const CString& text,
                                 const CString& fullName,
                                 int            imageIndex,
                                 int            imageSelectedIndex = -1);

        /**
        * Inserts a file item in tree
        *@param hParent - parent item in which file item should be added
        *@param pNetResource - network resource
        *@param text - item text
        *@param fullName - item full name
        *@param imageIndex - image index
        *@param imageSelectedIndex - image selected index
        *@return newly added tree item handle, NULL on error
        */
        HTREEITEM InsertFileItem(HTREEITEM      hParent,
                                 NETRESOURCE*   pNetResource,
                                 const CString& text,
                                 const CString& fullName,
                                 int            imageIndex,
                                 int            imageSelectedIndex = -1);

        /**
        * Clears the network resources
        */
        void ClearNetRessources();

        /**
        * Makes an object dynamic
        *@param pData - object data
        *@return dynamic object data, NULL on error
        */
        static TCHAR* MakeObjectDynamic(LPTSTR pData);

        /**
        * Format a name in a such manner the first char is in upper case and all the following are in lower case
        *@param name - name to format
        *@return formatted name
        *@note If the name contains any lower case char, it will be considered as already formatted, and returned as is
        */
        static CString FormatName(const CString& name);

        /**
        * Parses a path
        *@param path - path to parse
        *@param level - level
        *@param[out] dirName - directory name
        *@return true on success, otherwise false
        */
        static bool ParsePath(const CString& path, int level, CString& dirName);
};

//---------------------------------------------------------------------------
// PSS_DirTreeCtrl
//---------------------------------------------------------------------------
bool PSS_DirTreeCtrl::IsValid() const
{
    return m_IsValid;
}
//---------------------------------------------------------------------------
int PSS_DirTreeCtrl::GetIndexOfNoDropImage() const
{
    return DRIVE_RAMDISK + 3;
}
//---------------------------------------------------------------------------

#endif
