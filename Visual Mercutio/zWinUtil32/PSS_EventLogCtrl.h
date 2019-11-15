/****************************************************************************
 * ==> PSS_EventLogCtrl ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an event log control                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EventLogCtrlH
#define PSS_EventLogCtrlH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zEvent\PSS_EventManager.h"
#include "zEvent\ZBEventServer.h"
#include "zBaseLib\PSS_ListCtrl.h"

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
* Event log control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_EventLogCtrl : public PSS_ListCtrl
{
    public:
        /**
        * Constructor
        *@param pEventManager - event manager
        */
        PSS_EventLogCtrl(PSS_EventManager* pEventManager = NULL);

        ~PSS_EventLogCtrl();

        /**
        * Stream out operator
        *@param left - left event activity
        *@param listCtrl - event activity log controller
        *@return event activity
        */
        #ifdef _WIN32
            AFX_EXT_API friend ZBEventServer& operator >> (ZBEventServer& left, PSS_EventLogCtrl& listCtrl);
        #endif

        /**
        * Initializes the event log control
        *@param pEventManager - event manager
        */
        void Initialize(PSS_EventManager* pEventManager);

        /**
        * Refreshes the event log control
        */
        void Refresh();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_MSG(PSS_EventLogCtrl)
        afx_msg LRESULT OnNewEvent(WPARAM wParam, LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_EventManager* m_pEventManager;
        BOOL              m_ColumnsHasBeenBuilt;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_EventLogCtrl(const PSS_EventLogCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_EventLogCtrl& operator = (const PSS_EventLogCtrl& other);

        /**
        * Checkes if the columns were built
        *@return TRUE if the columns were built, otherwise FALSE
        */
        inline BOOL ColumnsHasBeenBuilt() const;

        /**
        * Builds the columns
        *@return TRUE on success, otherwise FALSE
        */
        BOOL BuildColumns();
};

//---------------------------------------------------------------------------
// PSS_EventLogCtrl
//---------------------------------------------------------------------------
BOOL PSS_EventLogCtrl::ColumnsHasBeenBuilt() const
{
    return m_ColumnsHasBeenBuilt;
}
//---------------------------------------------------------------------------

#endif
