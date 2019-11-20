/****************************************************************************
 * ==> PSS_ActivityEventLogCtrl --------------------------------------------*
 ****************************************************************************
 * Description : Provides an event activity logger control                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityEventLogCtrlH
#define PSS_ActivityEventLogCtrlH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_ListCtrl.h"
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
* Event activity logger control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityEventLogCtrl : public PSS_ListCtrl
{
    public:
        /**
        * Constructor
        *@param pEventManager - event manager, can be NULL
        */
        PSS_ActivityEventLogCtrl(PSS_EventManager* pEventManager = NULL);

        virtual ~PSS_ActivityEventLogCtrl();

        /**
        * Put the event in the event controller
        *@param activityEvent - the activity event
        *@param eventCtrl - the event controller
        *@return the activity event, to allow operator to be chained with other controllers, e.g a >> b >> c
        */
        #ifdef _WIN32
            AFX_EXT_API friend PSS_ActivityEvent& operator >> (PSS_ActivityEvent& activityEvent, PSS_ActivityEventLogCtrl& eventCtrl);
        #endif

        /**
        * Initializes the logger
        *@param pEventManager - event manager
        */
        virtual void Initialize(PSS_EventManager* pEventManager);

        /**
        * Gets selected item
        *@return selected item, NULL if not found or on error
        */
        virtual PSS_ActivityEvent* GetSelectedItem() const;

        /**
        * Refreshes the logger
        */
        virtual void Refresh();

    protected:
        //{{AFX_MSG(PSS_ActivityEventLogCtrl)
        afx_msg LRESULT OnNewActivityEvent(WPARAM wParam, LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_EventManager* m_pEventManager;
        BOOL              m_ColumnsHasBeenBuilt;

        /**
        * Copy constructor
        *@param other - other combo box to copy from
        */
        PSS_ActivityEventLogCtrl(const PSS_ActivityEventLogCtrl &other);

        /**
        * Copy operator
        *@param other - other combo box to copy from
        *@return copy of itself
        */
        const PSS_ActivityEventLogCtrl& operator = (const PSS_ActivityEventLogCtrl &other);

        /**
        * Checks if columns were built
        *@return TRUE if coulmns were build, otherwise FALSE
        */
        inline BOOL ColumnsHasBeenBuilt() const;

        /**
        * Builds the columns
        *@return TRUE on success, otherwise FALSE
        */
        BOOL BuildColumns();
};

//---------------------------------------------------------------------------
// PSS_ActivityEventLogCtrl
//---------------------------------------------------------------------------
BOOL PSS_ActivityEventLogCtrl::ColumnsHasBeenBuilt() const
{
    return m_ColumnsHasBeenBuilt;
}
//---------------------------------------------------------------------------

#endif
