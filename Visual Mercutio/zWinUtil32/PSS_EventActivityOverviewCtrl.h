/****************************************************************************
 * ==> PSS_EventActivityOverviewCtrl ---------------------------------------*
 ****************************************************************************
 * Description : Provides an event activity overview control                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EventActivityOverviewCtrlH
#define PSS_EventActivityOverviewCtrlH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZITreeCtl.h"
#include "zEvent\EventManager.h"
#include "zEvent\ActEvent.h"

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
class AFX_EXT_CLASS PSS_EventActivityOverviewCtrl : public ZITreeCtrl
{
    public:
        /**
        * Constructor
        *@param pEventManager - event manager
        */
        PSS_EventActivityOverviewCtrl(ZBEventManager* pEventManager = NULL);

        virtual ~PSS_EventActivityOverviewCtrl();

        /**
        * Initializes the control
        *@param pEventManager - event manager
        */
        virtual void Initialize();
        virtual void Initialize(ZBEventManager* pEventManager);

        /**
        * Gets the selected activity item
        *@return the selected activity item, NULL if no selection or on error
        */
        virtual ZBEventActivity* GetSelectedActivityItem();

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

        //{{AFX_MSG(PSS_EventActivityOverviewCtrl)
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
            enum IEActivityType
            {
                IE_AT_User,
                IE_AT_Process,
                IE_AT_Activity
            };

            ZBEventActivity* m_pData;
            CString          m_Name;
            IEActivityType   m_Type;

            /**
            * Constructor
            *@param pData - element data, can be NULL
            *@param type - activity type
            */
            IElementType(ZBEventActivity* pData = NULL, IEActivityType type = IE_AT_Activity);

            /**
            * Constructor
            *@param name - activity name
            *@param type - activity type
            */
            IElementType(const CString& name, IEActivityType type);

            ~IElementType();
        };

        ZBEventManager* m_pEventManager;
        CStringArray    m_UserArray;
        CStringArray    m_ProcessArray;
        CObArray        m_ActPtrArray;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_EventActivityOverviewCtrl(const PSS_EventActivityOverviewCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_EventActivityOverviewCtrl& operator = (const PSS_EventActivityOverviewCtrl& other);

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
        CString FormatActivityText(ZBEventActivity* pData);

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
        BOOL EventExist(ZBEventActivity* pActEvent);

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
