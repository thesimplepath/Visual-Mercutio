/****************************************************************************
 * ==> PSS_EventActivityViewerReminderCtrl ---------------------------------*
 ****************************************************************************
 * Description : Provides an event activity viewer reminder control         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EventActivityViewerReminderCtrlH
#define PSS_EventActivityViewerReminderCtrlH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZIListCtrl.h"
#include "zEvent\EventManager.h"
#include "zEvent\ActEvtReminderManager.h"

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
class AFX_EXT_CLASS PSS_EventActivityViewerReminderCtrl : public ZIListCtrl
{
    public:
        /**
        * Constructor
        *@param pReminderManager - reminder manager, can be NULL
        */
        PSS_EventActivityViewerReminderCtrl(ZBActivityEventReminderManager* pReminderManager = NULL);

        virtual ~PSS_EventActivityViewerReminderCtrl();

        /**
        * Stream out operator
        *@param left - left event activity reminder
        *@param listCtrl - event activity view reminder controller
        *@return event activity reminder
        */
        #ifdef _WIN32
            AFX_EXT_API friend ZBEventActivityReminder& operator >> (ZBEventActivityReminder&             left,
                                                                     PSS_EventActivityViewerReminderCtrl& listCtrl);
        #endif

        /**
        * Initializes the control
        *@param pReminderManager - reminder manager, can be NULL
        */
        virtual void Initialize(ZBActivityEventReminderManager* pReminderManager);

        /**
        * Gets the selected item
        *@return the selected item, NULL if no item selected or on error
        */
        ZBEventActivityReminder* GetSelectedItem() const;

        /**
        * Refreshes the control
        */
        virtual void Refresh();

    protected:
        //{{AFX_MSG(PSS_EventActivityViewerReminderCtrl)
        afx_msg LRESULT OnNewActivityEvent( WPARAM wParam, LPARAM lParam );
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        ZBActivityEventReminderManager* m_pReminderManager;
        BOOL                            m_ColumnsHasBeenBuilt;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_EventActivityViewerReminderCtrl(const PSS_EventActivityViewerReminderCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_EventActivityViewerReminderCtrl& operator = (const PSS_EventActivityViewerReminderCtrl& other);

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
// PSS_EventActivityViewerReminderCtrl
//---------------------------------------------------------------------------
BOOL PSS_EventActivityViewerReminderCtrl::ColumnsHasBeenBuilt() const
{
    return m_ColumnsHasBeenBuilt;
}
//---------------------------------------------------------------------------

#endif
