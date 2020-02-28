/****************************************************************************
 * ==> PSS_DistributionAttributesList --------------------------------------*
 ****************************************************************************
 * Description : Provides a distribution attributes list                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DistributionAttributesListH
#define PSS_DistributionAttributesListH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_TreeListCtrl.h"

// class name mapping
#ifndef PSS_DistributionAttribute
    #define PSS_DistributionAttribute ZBDistributionAttribute
#endif
#ifndef PSS_DistributionAttributeManager
    #define PSS_DistributionAttributeManager ZBDistributionAttributeManager
#endif
#ifndef PSS_DistributionRule
    #define PSS_DistributionRule ZBDistributionRule
#endif
#ifndef PSS_DistributionRulesForRole
    #define PSS_DistributionRulesForRole ZBDistributionRulesForRole
#endif
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif

// forward class declaration
class PSS_DistributionAttribute;
class PSS_DistributionAttributeManager;
class PSS_DistributionRule;
class PSS_DistributionRulesForRole;
class ZBDynamicPropertiesManager;
class PSS_ProcessGraphModelDoc;
class PSS_UserGroupEntity;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Distribution attributes list
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DistributionAttributesList : public PSS_TreeListCtrl,
                                                     public PSS_Subject,
                                                     public PSS_Observer
{
    DECLARE_DYNAMIC(PSS_DistributionAttributesList)

    public:
        PSS_DistributionAttributesList();
        virtual ~PSS_DistributionAttributesList();

        /**
        * Initializes the list
        *@param pDistributionManager - the distribution manager
        *@param pPropManager - the properties manager
        *@param pMainUserGroup - the main user group
        *@param pDistributionAttribute - the distribution attribute
        *@param showAll - if true, all the attributes should be shown
        *@param symbolRef - the symbol reference
        *@return the attribute count
        */
        virtual int Initialize(PSS_DistributionAttributeManager* pDistributionManager,
                               ZBDynamicPropertiesManager*       pPropManager,
                               PSS_UserGroupEntity*              pMainUserGroup,
                               PSS_DistributionAttribute*        pDistributionAttribute =  NULL,
                               bool                              showAll                =  false,
                               int                               symbolRef              = -1);

        /**
        * Gets the selected distribution attribute
        *@return the selected distribution attribute, NULL if no selection or on error
        */
        virtual PSS_DistributionAttribute* GetSelectedDistributionAttribute();

        /**
        * Gets the selected distribution attribute for a role
        *@return the selected distribution attribute for a role, NULL if no selection or on error
        */
        virtual PSS_DistributionRulesForRole* GetSelectedDistributionRuleForRole();

        /**
        * Gets the selected distribution rule
        *@return the selected distribution rule, NULL if no selection or on error
        */
        virtual PSS_DistributionRule* GetSelectedDistributionRule();

        /**
        * Shows all the attributes
        *@param value - if true, all the attributes will be shown
        *@param refresh - if true, the attributes will be refreshed immediately
        */
        virtual inline void ShowAll(bool value = true, bool refresh = true);

        /**
        * Sets the symbol reference
        *@param value - the symbol reference
        *@param refresh - if true, the attributes will be refreshed immediately
        */
        virtual inline void SetSymbolRef(int value, bool refresh = true);

        /**
        * Refreshes the attributes
        *@return the attribute count
        */
        virtual int Refresh();

        /**
        * Deletes all the attributes
        */
        virtual void Empty();

        /**
        * Called when the frame is updated
        *@param pSubject - subject
        *@param pMSg - message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_DistributionAttributesList)
        //}}AFX_VIRTUAL

        /// Generated message map
        //{{AFX_MSG(PSS_DistributionAttributesList)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_DistributionAttribute*        m_pDistributionAttribute;
        PSS_DistributionAttributeManager* m_pDistributionManager;
        ZBDynamicPropertiesManager*       m_pPropManager;
        PSS_UserGroupEntity*              m_pMainUserGroup;
        CODComponent*                     m_pComp;
        int                               m_SymbolRef;
        BOOL                              m_ColumnsBuilt;
        bool                              m_ShowAll;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DistributionAttributesList(const PSS_DistributionAttributesList& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_DistributionAttributesList& operator = (const PSS_DistributionAttributesList& other);

        /**
        * Builds the columns
        */
        void BuildColumns();

        /**
        * Called when the document was activated
        *@param pDoc - the activated document
        */
        void DocumentActivated(PSS_ProcessGraphModelDoc* pDoc);

        /**
        * Inserts a distribution attribute
        *@param pDistributionAttribute - the distribution attribute to insert
        *@param level - the insertion level
        */
        int InsertDistributionAttribute(PSS_DistributionAttribute* pDistributionAttribute, int level);
};

//---------------------------------------------------------------------------
// PSS_DistributionAttributesList
//---------------------------------------------------------------------------
void PSS_DistributionAttributesList::ShowAll(bool value, bool refresh)
{
    m_ShowAll = value;

    if (refresh)
        Refresh();
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesList::SetSymbolRef(int value, bool refresh)
{
    m_SymbolRef = value;

    if (refresh)
        Refresh();
}
//---------------------------------------------------------------------------

#endif
