/****************************************************************************
 * ==> PSS_ActivityEventOverviewCtrl ---------------------------------------*
 ****************************************************************************
 * Description : Provides an event activity overview control                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityEventOverviewCtrlH
#define PSS_ActivityEventOverviewCtrlH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_TreeCtrl.h"
#include "zEvent\PSS_ActivityEvent.h"
#include "zEvent\PSS_EventManager.h"

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
* Event activity overview control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityEventOverviewCtrl : public PSS_TreeCtrl
{
    public:
        /**
        * Constructor
        *@param pEventManager - event manager
        */
        PSS_ActivityEventOverviewCtrl(PSS_EventManager* pEventManager = NULL);

        virtual ~PSS_ActivityEventOverviewCtrl();

        /**
        * Initializes the control
        *@param pEventManager - event manager
        */
        virtual void Initialize();
        virtual void Initialize(PSS_EventManager* pEventManager);

        /**
        * Gets the selected activity item
        *@return the selected activity item, NULL if no selection or on error
        */
        virtual PSS_ActivityEvent* GetSelectedActivityItem();

        /**
        * Gets the selected user
        *@return the selected user, empty string if no selection or on error
        */
        virtual CString GetSelectedUser();

        /**
        * Gets the selected process
        *@return the selected process, empty string if no selection or on error
        */
        virtual CString GetSelectedProcess();

        /**
        * Gets the user activities
        *@param user - user for which activities should be get
        *@return the user activities
        */
        virtual CObArray& GetUserActivities(const CString& user);

        /**
        * Gets the process activities
        *@param process - process for which activities should be get
        *@param user - user owning the process for which activities should be get
        *@return the user activities
        */
        virtual CObArray& GetProcessActivities(const CString& process, const CString& user);

        /**
        * Refreshes the control
        */
        virtual void Refresh();

        //{{AFX_MSG(PSS_ActivityEventOverviewCtrl)
        afx_msg void OnDestroy();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Element type
        */
        struct IElementType
        {
            /**
            * Activity type
            */
            enum class IEActivityType
            {
                IE_AT_User,
                IE_AT_Process,
                IE_AT_Activity
            };

            PSS_ActivityEvent* m_pData;
            CString            m_Name;
            IEActivityType     m_Type;

            /**
            * Constructor
            *@param pData - element data, can be NULL
            *@param type - activity type
            */
            IElementType(PSS_ActivityEvent* pData = NULL, IEActivityType type = IEActivityType::IE_AT_Activity);

            /**
            * Constructor
            *@param name - activity name
            *@param type - activity type
            */
            IElementType(const CString& name, IEActivityType type);

            ~IElementType();
        };

        PSS_EventManager* m_pEventManager;
        CStringArray      m_UserArray;
        CStringArray      m_ProcessArray;
        CObArray          m_ActPtrArray;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ActivityEventOverviewCtrl(const PSS_ActivityEventOverviewCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityEventOverviewCtrl& operator = (const PSS_ActivityEventOverviewCtrl& other);

        /**
        * Adds an user item
        *@param pElement - element type
        *@param iconIndex - icon index
        *@return newly added user item handle, NULL on error
        */
        HTREEITEM AddUserItem(IElementType* pElement, int iconIndex);

        /**
        * Adds a process item
        *@param pElement - element type
        *@param hParentTreeItem - parent tree item to attach to, root if NULL
        *@param iconIndex - icon index
        *@return newly added process item handle, NULL on error
        */
        HTREEITEM AddProcessItem(IElementType* pElement, HTREEITEM hParentTreeItem, int iconIndex);

        /**
        * Adds a sub-item
        *@param pElement - element type
        *@param hParentTreeItem - parent tree item to attach to, root if NULL
        *@param iconIndex - icon index
        *@return newly added sub-item handle, NULL on error
        */
        HTREEITEM AddSubItem(IElementType* pElement, HTREEITEM hParentTreeItem, int iconIndex);

        /**
        * Formats the activity text
        *@param pData - activity data
        *@return the formatted activity text
        */
        CString FormatActivityText(PSS_ActivityEvent* pData);

        /**
        * Checks if an user exists
        *@param user - user to check
        *@return TRUE if user exists, otherwise FALSE
        */
        BOOL UserExist(const CString& user);

        /**
        * Checks if a process exists
        *@param process - process to check
        *@return TRUE if process exists, otherwise FALSE
        */
        BOOL ProcessExist(const CString& process);

        /**
        * Checks if an activity event exists
        *@param pActEvent - activity event to check
        *@return TRUE if activity event exists, otherwise FALSE
        */
        BOOL EventExist(PSS_ActivityEvent* pActEvent);

        /**
        * Builds the user array
        */
        void BuildUserArray();

        /**
        * Builds the process array
        */
        void BuildProcessArray();

        /**
        * Deletes all items
        */
        void DeleteAllItems();

        /**
        * Deletes all items contained in a tree item
        *@param hTreeItem - item for which all sub-items should be deleted
        */
        void DeleteAllItems(HTREEITEM hTreeItem);
};

#endif
