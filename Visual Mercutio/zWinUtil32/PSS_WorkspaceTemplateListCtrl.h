/****************************************************************************
 * ==> PSS_WorkspaceTemplateListCtrl ---------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace template list control                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkspaceTemplateListCtrlH
#define PSS_WorkspaceTemplateListCtrlH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZIListCtrl.h"
#include "zBaseLib\ZBWorkspaceWizardTemplateItem.h"

// forward class declaration
class ZBWorkspaceWizardTemplateMg;

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
* Workspace template list control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WorkspaceTemplateListCtrl : public ZIListCtrl
{
    public:
        /**
        * constructor
        *@param pWorkspaceTemplateManager - workspace template manager, can be NULL
        */
        PSS_WorkspaceTemplateListCtrl(ZBWorkspaceWizardTemplateMg* pWorkspaceTemplateManager = NULL);

        virtual ~PSS_WorkspaceTemplateListCtrl();

        /**
        * Stream out operator
        *@param left - left value to stream out
        *@param listCtrl - workspace template list control
        *@return workspace wizard template item instance
        */
        #ifdef _WIN32
            AFX_EXT_API friend ZBWorkspaceWizardTemplateItem& operator >> (ZBWorkspaceWizardTemplateItem& left,
                                                                           PSS_WorkspaceTemplateListCtrl& listCtrl);
        #endif

        /**
        * Initializes the workspace template list control
        *@param pWorkspaceTemplateManager - workspace template manager
        */
        virtual void Initialize(ZBWorkspaceWizardTemplateMg* pWorkspaceTemplateManager);

        /**
        * Refreshes the control
        */
        virtual void Refresh();

        /**
        * Gets the selected item
        *@return the selected item, NULL if no selection or on error
        */
        virtual ZBWorkspaceWizardTemplateItem* GetSelectedItem() const;

      protected:
        /// ClassWizard generated message map functions
        //{{AFX_MSG(PSS_WorkspaceTemplateListCtrl)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        ZBWorkspaceWizardTemplateMg* m_pWorkspaceTemplateManager;
        BOOL                         m_ColumnsHasBeenBuilt;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_WorkspaceTemplateListCtrl(const PSS_WorkspaceTemplateListCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_WorkspaceTemplateListCtrl& operator = (const PSS_WorkspaceTemplateListCtrl& other);

        /**
        * Builds the columns
        *@return TRUE on success, otherwise FALSE
        */
        BOOL BuildColumns();

        /**
        * Checks if columns were built
        *@return TRUE if columns were built, otherwise FALSE
        */
        inline BOOL ColumnsHasBeenBuilt() const;
};

//---------------------------------------------------------------------------
// PSS_WorkspaceTemplateListCtrl
//---------------------------------------------------------------------------
BOOL PSS_WorkspaceTemplateListCtrl::ColumnsHasBeenBuilt() const
{
    return m_ColumnsHasBeenBuilt;
}
//---------------------------------------------------------------------------

#endif
