/****************************************************************************
 * ==> PSS_TemplateTreeCtrl ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a template tree control, which is automatically   *
 *               filled with a template manager object                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TemplateTreeCtrlH
#define PSS_TemplateTreeCtrlH

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
#include "PSS_TemplateTree.h"

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
* Template tree control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TemplateTreeCtrl : public PSS_TreeCtrl
{
    DECLARE_DYNCREATE(PSS_TemplateTreeCtrl)

    public:
        /**
        * Constructor
        *@param pTemplateManager - template manager
        *@param includeFiles - if TRUE, files will be included
        */
        PSS_TemplateTreeCtrl(PSS_TemplateManager* pTemplateManager = NULL, BOOL includeFiles = FALSE);

        virtual ~PSS_TemplateTreeCtrl();

        /**
        * Initializes the tree
        *@param pTemplateManager - template manager
        *@param includeFiles - if TRUE, files will be included
        */
        virtual void Initialize(PSS_TemplateManager* pTemplateManager, BOOL includeFiles = FALSE);

        /**
        * Re-initializes the tree
        *@param pTemplateManager - template manager
        *@param includeFiles - if TRUE, files will be included
        *@note This function will not work if the tree has never been initialized
        */
        virtual void ReInitialize(PSS_TemplateManager* pTemplateManager, BOOL includeFiles = FALSE);

        /**
        * Refreshes the current tree
        */
        virtual void Refresh();

        /**
        * Gets the selected item name
        *@return the selected item name, empty string if no selection or on error
        */
        virtual CString GetNameSelectedItem();

        /**
        * Gets the selected template directory
        *@return Gets the selected template directory, NULL if no selection or on error
        */
        virtual PSS_TemplateDir* GetSelectedFolderItem();

        /**
        * Gets the selected template file
        *@return the selected template file, NULL if no selection or on error
        */
        virtual PSS_TemplateFile* GetSelectedFileItem();

        /**
        * Selects an item
        *@param name - item name to select
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SelectItemName(const CString& name);

        /**
        * Called when tree selection has changed
        */
        virtual void OnSelChangedEvent();

        /**
        * Called when tree was clicked
        */
        virtual void OnClickEvent();

        /**
        * Called when tree was double-clicked
        */
        virtual void OnDblClickEvent();

        /**
        * Called when tree was right clicked
        */
        virtual void OnRightClickEvent();

        /**
        * Called when tree was right double-clicked
        */
        virtual void OnRightDblClickEvent();

    protected:
        PSS_TemplateManager* m_pTemplateManager;
        PSS_TemplateTree     m_TemplateTree;
        BOOL                 m_IncludeFiles;

        /// Additional Protected Declarations
        //{{AFX_MSG(PSS_TemplateTreeCtrl)
        afx_msg LRESULT OnInitializeTemplateManager(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnReloadTemplateManager( WPARAM wParam, LPARAM lParam );
        afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnDblClick(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnRightClick(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnRightDblClick(NMHDR* pNMHDR, LRESULT* pResult);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Gets the no drop image index
        *@return the no drop image index
        */
        virtual inline int GetIndexOfNoDropImage() const;

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_TemplateTreeCtrl(const PSS_TemplateTreeCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_TemplateTreeCtrl& operator = (const PSS_TemplateTreeCtrl& other);
};

//---------------------------------------------------------------------------
// PSS_TemplateTreeCtrl
//---------------------------------------------------------------------------
int PSS_TemplateTreeCtrl::GetIndexOfNoDropImage() const
{
    return 2;
}
//---------------------------------------------------------------------------

#endif
