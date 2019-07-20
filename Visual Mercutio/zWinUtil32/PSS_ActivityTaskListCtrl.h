/****************************************************************************
 * ==> PSS_ActivityTaskListCtrl --------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity task list control                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityTaskListCtrlH
#define PSS_ActivityTaskListCtrlH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZIListCtrl.h"
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
* Activity task list control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
#ifdef _WIN32
    // 32 bit version
    class AFX_EXT_CLASS PSS_ActivityTaskListCtrl : public ZIListCtrl
#else
    // 16 bit version
    class AFX_EXT_CLASS PSS_ActivityTaskListCtrl : public CListBox
#endif
{
    public:
        /**
        * Constructor
        *@param pProcess - process, can be NULL
        */
        PSS_ActivityTaskListCtrl(ZProcess* pProcess = NULL);

        virtual ~PSS_ActivityTaskListCtrl();

        /**
        * Initializes the control
        *@param pProcess - process
        */
        int Initialize(ZProcess* pProcess);

        /**
        * Gets the selected activity
        *@return the selected activity, empty string if no selection or on error
        */
        CString GetSelectedActivity();

        /**
        * Gets the selected activities
        *@param[out] activitiesArray - array containing the selected activities
        *@return selected activity count
        */
        int GetSelectedActivities(CStringArray& activitiesArray);

        /**
        * Selects an activity
        *@param activityIndex - activity index to select
        *@param activityName - activity name to select
        *@param shouldClearAllSelection - if TRUE, all previous selection will be cleared
        */
        void SelectActivity(std::size_t    activityIndex, BOOL shouldClearAllSelection = FALSE);
        void SelectActivity(const CString& activityName,  BOOL shouldClearAllSelection = FALSE);

        /**
        * Clears the selection
        */
        void ClearAllSelection();

        /**
        * Refreshes the control
        *@return activity count
        */
        int Refresh();

        /**
        * Checks if columns were built
        *@return TRUE if columns were built, otherwise FALSE
        */
        virtual inline BOOL HasBuiltColumns() const;

    protected:
        //{{AFX_MSG(PSS_ActivityTaskListCtrl)
        afx_msg LRESULT OnActivityListChange(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnSelectActivityInTaskList(WPARAM wParam, LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        ZProcess* m_pProcess;
        BOOL      m_HasBuiltColumns;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ActivityTaskListCtrl(const PSS_ActivityTaskListCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityTaskListCtrl& operator = (const PSS_ActivityTaskListCtrl& other);

        /**
        * Inserts an activity
        *@param activity - activity
        *@param isCurrentActivity - if true, inserted activity will be the current one
        */
        void InsertActivity(ZBaseActivity& activity, bool isCurrentActivity);

        /**
        * Builds the columns
        */
        #ifdef _WIN32
            void BuildColumns();
        #endif
};

//---------------------------------------------------------------------------
// PSS_ActivityTaskListCtrl
//---------------------------------------------------------------------------
BOOL PSS_ActivityTaskListCtrl::HasBuiltColumns() const
{
    return m_HasBuiltColumns;
}
//---------------------------------------------------------------------------

#endif
