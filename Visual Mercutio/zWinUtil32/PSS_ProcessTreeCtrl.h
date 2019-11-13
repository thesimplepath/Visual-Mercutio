/****************************************************************************
 * ==> PSS_ProcessTreeCtrl -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a process tree control                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef ProcTree_h
#define ProcTree_h 1

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_TreeCtrl.h"
#include "zEvent\ZProcess.h"

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
* New form wizard dialog box property sheet
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessTreeCtrl : public PSS_TreeCtrl
{
    public:
        /**
        * Constructor
        *@param pPropcess - process
        */
        PSS_ProcessTreeCtrl(PSS_Process* pProcess = NULL);

        virtual ~PSS_ProcessTreeCtrl();

        /**
        * Initializes the control
        *@param pProcess - process
        */
        virtual void Initialize(PSS_Process* pProcess);

        /**
        * Gets the process
        *@return the process, NULL if no process or on error
        */
        virtual inline PSS_Process* GetProcess() const;

        /**
        * Gets the selected process item
        *@return the selected process item, NULL if no item selected or on error
        */
        virtual PSS_Process* GetSelectedProcessItem();

        /**
        * Gets the root process item
        *@return the root process item, NULL if no root item or on error
        */
        virtual PSS_Process* GetRootProcessItem();

        /**
        * Gets the selected activity item
        *@return the selected activity item, NULL if no item selected or on error
        */
        virtual PSS_Activity* GetSelectedActivityItem();

        /**
        * Refreshes the control
        */
        virtual void Refresh();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_MSG(PSS_ProcessTreeCtrl)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Fills the control
        */
        virtual void FillControl();

        /**
        * Adds a process
        *@param pBaseActivity - base activity
        *@param hParentTreeItem - parent tree item to add to, will be added to root if NULL
        *@param iconIndex - icon index
        */
        virtual void AddProcess(PSS_BaseActivity* pBaseActivity, HTREEITEM hParentTreeItem, int iconIndex);

        /**
        * Adds activity items
        *@param pBaseActivity - base activity
        *@param hParentTreeItem - parent tree item to add to, will be added to root if NULL
        *@param iconIndex - icon index
        */
        virtual void AddActivityItems(PSS_BaseActivity* pBaseActivity, HTREEITEM hParentTreeItem, int iconIndex = 0);

        /**
        * Adds a process item
        *@param pBaseActivity - base activity
        *@param hParentTreeItem - parent tree item to add to, will be added to root if NULL
        *@param iconIndex - icon index
        *@return newly added item handle, NULL on error
        */
        virtual HTREEITEM AddProcessItem(PSS_BaseActivity* pBaseActivity, HTREEITEM hParentTreeItem, int iconIndex = 0);

        /**
        * Adds a sub-item
        *@param pBaseActivity - base activity
        *@param hParentTreeItem - parent tree item to add to, will be added to root if NULL
        *@param iconIndex - icon index
        *@return newly added sub-item handle, NULL on error
        */
        virtual HTREEITEM AddSubItem(PSS_Activity* pBaseActivity, HTREEITEM hParentTreeItem, int iconIndex = 0);

    private:
        PSS_Process* m_pProcess;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ProcessTreeCtrl(const PSS_ProcessTreeCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ProcessTreeCtrl & operator = (const PSS_ProcessTreeCtrl& other);
};

//---------------------------------------------------------------------------
// PSS_ProcessTreeCtrl
//---------------------------------------------------------------------------
PSS_Process* PSS_ProcessTreeCtrl::GetProcess() const
{
    return m_pProcess;
}
//---------------------------------------------------------------------------

#endif
