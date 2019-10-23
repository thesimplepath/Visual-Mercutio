/****************************************************************************
 * ==> PSS_EventActivityLogCtrl --------------------------------------------*
 ****************************************************************************
 * Description : Provides an event activity logger control                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EventActivityLogCtrlH
#define PSS_EventActivityLogCtrlH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_ListCtrl.h"
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
* Event activity logger control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_EventActivityLogCtrl : public PSS_ListCtrl
{
    public:
        /**
        * Constructor
        *@param pEventManager - event manager, can be NULL
        */
        PSS_EventActivityLogCtrl(ZBEventManager* pEventManager = NULL);

        virtual ~PSS_EventActivityLogCtrl();

        /**
        * Stream out operator
        *@param left - left event activity
        *@param listCtrl - event activity log controller
        *@return event activity
        */
        #ifdef _WIN32
            AFX_EXT_API friend ZBEventActivity& operator >> (ZBEventActivity& left, PSS_EventActivityLogCtrl& listCtrl);
        #endif

        /**
        * Initializes the logger
        *@param pEventManager - event manager
        */
        virtual void Initialize (ZBEventManager* pEventManager);

        /**
        * Gets selected item
        *@return selected item, NULL if not found or on error
        */
        virtual ZBEventActivity* GetSelectedItem() const;

        /**
        * Refreshes the logger
        */
        virtual void Refresh();

    protected:
        //{{AFX_MSG(PSS_EventActivityLogCtrl)
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
        PSS_EventActivityLogCtrl(const PSS_EventActivityLogCtrl &other);

        /**
        * Copy operator
        *@param other - other combo box to copy from
        *@return copy of itself
        */
        const PSS_EventActivityLogCtrl& operator = (const PSS_EventActivityLogCtrl &other);

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
// PSS_EventActivityLogCtrl
//---------------------------------------------------------------------------
BOOL PSS_EventActivityLogCtrl::ColumnsHasBeenBuilt() const
{
    return m_ColumnsHasBeenBuilt;
}
//---------------------------------------------------------------------------

#endif
