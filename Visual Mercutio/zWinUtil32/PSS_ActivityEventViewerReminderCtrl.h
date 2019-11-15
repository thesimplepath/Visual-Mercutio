/****************************************************************************
 * ==> PSS_ActivityEventViewerReminderCtrl ---------------------------------*
 ****************************************************************************
 * Description : Provides an event activity viewer reminder control         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityEventViewerReminderCtrlH
#define PSS_ActivityEventViewerReminderCtrlH

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_ListCtrl.h"
#include "zEvent\PSS_EventManager.h"
#include "zEvent\PSS_ActivityReminderEventManager.h"

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
* Event activity viewer reminder control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityEventViewerReminderCtrl : public PSS_ListCtrl
{
    public:
        /**
        * Constructor
        *@param pReminderManager - reminder manager, can be NULL
        */
        PSS_ActivityEventViewerReminderCtrl(PSS_ActivityReminderEventManager* pReminderManager = NULL);

        virtual ~PSS_ActivityEventViewerReminderCtrl();

        /**
        * Stream out operator
        *@param left - left event activity reminder
        *@param listCtrl - event activity view reminder controller
        *@return event activity reminder
        */
        #ifdef _WIN32
            AFX_EXT_API friend PSS_ActivityReminderEvent& operator >> (PSS_ActivityReminderEvent&           left,
                                                                       PSS_ActivityEventViewerReminderCtrl& listCtrl);
        #endif

        /**
        * Initializes the control
        *@param pReminderManager - reminder manager, can be NULL
        */
        virtual void Initialize(PSS_ActivityReminderEventManager* pReminderManager);

        /**
        * Gets the selected item
        *@return the selected item, NULL if no item selected or on error
        */
        PSS_ActivityReminderEvent* GetSelectedItem() const;

        /**
        * Refreshes the control
        */
        virtual void Refresh();

    protected:
        //{{AFX_MSG(PSS_ActivityEventViewerReminderCtrl)
        afx_msg LRESULT OnNewActivityEvent(WPARAM wParam, LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_ActivityReminderEventManager* m_pReminderManager;
        BOOL                              m_ColumnsHasBeenBuilt;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ActivityEventViewerReminderCtrl(const PSS_ActivityEventViewerReminderCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityEventViewerReminderCtrl& operator = (const PSS_ActivityEventViewerReminderCtrl& other);

        /**
        * Checks if columns were built
        *@return TRUE if columns were built, otherwise FALSE
        */
        inline BOOL ColumnsHasBeenBuilt() const;

        /**
        * Builds columns
        *@return TRUE on success, otherwise FALSE
        */
        BOOL BuildColumns();
};

//---------------------------------------------------------------------------
// PSS_ActivityEventViewerReminderCtrl
//---------------------------------------------------------------------------
BOOL PSS_ActivityEventViewerReminderCtrl::ColumnsHasBeenBuilt() const
{
    return m_ColumnsHasBeenBuilt;
}
//---------------------------------------------------------------------------

#endif
