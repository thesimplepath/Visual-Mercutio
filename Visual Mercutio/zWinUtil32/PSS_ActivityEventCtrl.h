/****************************************************************************
 * ==> PSS_ActivityEventCtrl -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an event activity control                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityEventCtrlH
#define PSS_ActivityEventCtrlH

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
#include "zEvent\PSS_ActivityEvent.h"

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
* Event activity control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityEventCtrl : public PSS_ListCtrl
{
    public:
        /**
        * Constructor
        *@param pEventManager - event manager, can be NULL
        */
        PSS_ActivityEventCtrl(ZBEventManager* pEventManager = NULL);

        virtual ~PSS_ActivityEventCtrl();

        /**
        * Stream out operator
        *@param left - left event activity
        *@param listCtrl - event activity controller
        *@return event activity
        */
        #ifdef _WIN32
            AFX_EXT_API friend PSS_ActivityEvent& operator >> (PSS_ActivityEvent& left, PSS_ActivityEventCtrl& listCtrl);
        #endif

        /**
        * Initializes the control
        *@param pReminderManager - reminder manager, can be NULL
        */
        virtual void Initialize(ZBEventManager* pEventManager);

        /**
        * Gets the selected item
        *@return the selected item, NULL if no item selected or on error
        */
        virtual PSS_ActivityEvent* GetSelectedItem() const;

        /**
        * Refreshes the control
        */
        virtual void Refresh();

    protected:
        //{{AFX_MSG(PSS_ActivityEventCtrl)
        afx_msg LRESULT OnNewActivityEvent(WPARAM wParam, LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        ZBEventManager* m_pEventManager;
        BOOL            m_ColumnsHasBeenBuilt;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ActivityEventCtrl(const PSS_ActivityEventCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityEventCtrl& operator = (const PSS_ActivityEventCtrl& other);
      
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
// PSS_ActivityEventCtrl
//---------------------------------------------------------------------------
BOOL PSS_ActivityEventCtrl::ColumnsHasBeenBuilt() const
{
    return m_ColumnsHasBeenBuilt;
}
//---------------------------------------------------------------------------

#endif
