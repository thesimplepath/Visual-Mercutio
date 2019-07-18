/****************************************************************************
 * ==> PSS_EventActivityLog ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an event activity logger                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EventActivityLogH
#define PSS_EventActivityLogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zEvent\EventManager.h"
#include "zEvent\ActEvent.h"
#include "zBaseLib\ZIListCtrl.h"

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
* Event activity logger
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_EventActivityLog : public ZIListCtrl
{
    public:
        /**
        * Constructor
        *@param pEventManager - event manager, can be NULL
        */
        PSS_EventActivityLog(ZBEventManager* pEventManager = NULL);

        virtual ~PSS_EventActivityLog();

        /**
        * Stream out operator
        *@param left - left event activity
        *@param listCtrl - list controller
        *@return event activity
        */
        #ifdef _WIN32
            AFX_EXT_API friend ZBEventActivity& operator >> (ZBEventActivity& left, PSS_EventActivityLog& listCtrl);
        #endif

        /**
        * Initializes the logger
        *@param pEventManager - event manager
        */
        void Initialize (ZBEventManager* pEventManager);

        /**
        * Gets selected item
        *@return selected item, NULL if not found or on error
        */
        ZBEventActivity* GetSelectedItem() const;

        /**
        * Refreshes the logger
        */
        void Refresh();

    protected:
        //{{AFX_MSG(PSS_EventActivityLog)
        afx_msg LRESULT OnNewActivityEvent(WPARAM wParam, LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        ZBEventManager* m_pEventManager;
        BOOL            m_ColumnsHasBeenBuilt;

        /**
        * Copy constructor
        *@param other - other combo box to copy from
        */
        PSS_EventActivityLog(const PSS_EventActivityLog &other);

        /**
        * Copy operator
        *@param other - other combo box to copy from
        */
        const PSS_EventActivityLog& operator = (const PSS_EventActivityLog &other);

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
// PSS_EventActivityLog
//---------------------------------------------------------------------------
BOOL PSS_EventActivityLog::ColumnsHasBeenBuilt() const
{
    return m_ColumnsHasBeenBuilt;
}
//---------------------------------------------------------------------------

#endif
