/****************************************************************************
 * ==> PSS_EventActivityUserOverviewCtrl -----------------------------------*
 ****************************************************************************
 * Description : Provides an event activity user overview control           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EventActivityUserOverviewCtrlH
#define PSS_EventActivityUserOverviewCtrlH

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
* Event activity user overview control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_EventActivityUserOverviewCtrl : public ZITreeCtrl
{
    public:
        /**
        * Constructor
        *@param pEventManager - event manager
        */
        PSS_EventActivityUserOverviewCtrl(ZBEventManager* pEventManager = NULL);

        virtual ~PSS_EventActivityUserOverviewCtrl();

        /**
        * Initializes the control
        *@param pEventManager - event manager
        */
        void Initialize();
        void Initialize(ZBEventManager* pEventManager);

        /**
        * Gets the selected activity item
        *@return the selected activity item, NULL if no selection or on error
        */
        ZBEventActivity* GetSelectedActivityItem();

        /**
        * Gets the selected process
        *@return the selected process, empty string if no selection or on error
        */
        CString GetSelectedProcess();

        /**
        * Refreshes the control
        */
        void Refresh();

        //{{AFX_MSG(PSS_EventActivityUserOverviewCtrl)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        ZBEventManager* m_pEventManager;
        CStringArray    m_ProcessArray;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_EventActivityUserOverviewCtrl(const PSS_EventActivityUserOverviewCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_EventActivityUserOverviewCtrl& operator = (const PSS_EventActivityUserOverviewCtrl& other);

        /**
        * Adds a process item
        *@param processName - process name to add
        *@param iconIndex - icon index
        *@return newly added process item handle, NULL on error
        */
        HTREEITEM AddProcessItem(const CString& processName, int iconIndex);

        /**
        * Adds a sub-item
        *@param pData - event activity data
        *@param hParentTreeItem - parent tree item to attach to, root if NULL
        *@param iconIndex - icon index
        *@return newly added sub-item handle, NULL on error
        */
        HTREEITEM AddSubItem(ZBEventActivity* pData, HTREEITEM hParentTreeItem, int iconIndex);

        /**
        * Checks if a process exists
        *@param process - process to check
        *@return TRUE if process exists, otherwise FALSE
        */
        BOOL ProcessExist(const CString& process);

        /**
        * Builds the process array
        */
        void BuildProcessArray();
};

#endif
