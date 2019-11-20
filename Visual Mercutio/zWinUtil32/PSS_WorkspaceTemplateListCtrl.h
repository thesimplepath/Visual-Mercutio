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

// class name mapping
#ifndef PSS_WorkspaceWizardTemplateManager
    #define PSS_WorkspaceWizardTemplateManager ZBWorkspaceWizardTemplateMg
#endif

// processsoft
#include "zBaseLib\PSS_WorkspaceWizardTemplateItem.h"
#include "zBaseLib\PSS_ListCtrl.h"

// forward class declaration
class PSS_WorkspaceWizardTemplateManager;

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
class AFX_EXT_CLASS PSS_WorkspaceTemplateListCtrl : public PSS_ListCtrl
{
    public:
        /**
        * constructor
        *@param pWorkspaceTemplateManager - workspace template manager, can be NULL
        */
        PSS_WorkspaceTemplateListCtrl(PSS_WorkspaceWizardTemplateManager* pWorkspaceTemplateManager = NULL);

        virtual ~PSS_WorkspaceTemplateListCtrl();

        /**
        * Put the workspace wizard template item in the workspace template list controller
        *@param templateItem - the template item
        *@param listCtrl - the template list controller
        *@return the template item, to allow operator to be chained with other controllers, e.g a >> b >> c
        */
        #ifdef _WIN32
            AFX_EXT_API friend PSS_WorkspaceWizardTemplateItem& operator >> (PSS_WorkspaceWizardTemplateItem& templateItem,
                                                                             PSS_WorkspaceTemplateListCtrl&   listCtrl);
        #endif

        /**
        * Initializes the workspace template list control
        *@param pWorkspaceTemplateManager - workspace template manager
        */
        virtual void Initialize(PSS_WorkspaceWizardTemplateManager* pWorkspaceTemplateManager);

        /**
        * Refreshes the control
        */
        virtual void Refresh();

        /**
        * Gets the selected item
        *@return the selected item, NULL if no selection or on error
        */
        virtual PSS_WorkspaceWizardTemplateItem* GetSelectedItem() const;

      protected:
        /// ClassWizard generated message map functions
        //{{AFX_MSG(PSS_WorkspaceTemplateListCtrl)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_WorkspaceWizardTemplateManager* m_pWorkspaceTemplateManager;
        BOOL                                m_ColumnsHasBeenBuilt;

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
