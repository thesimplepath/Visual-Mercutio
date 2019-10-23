/****************************************************************************
 * ==> PSS_ActivityListAttributionCtrl -------------------------------------*
 ****************************************************************************
 * Description : Provides an activity list attribution control              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/
 
#ifndef PSS_ActivityListAttributionCtrlH
#define PSS_ActivityListAttributionCtrlH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zEvent\ZProcess.h"
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
* Activity list attribution control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
#ifdef _WIN32
    // 32 bit version
    class AFX_EXT_CLASS PSS_ActivityListAttributionCtrl : public PSS_ListCtrl
#else
    // 16 bit version
    class AFX_EXT_CLASS PSS_ActivityListAttributionCtrl : public CListBox
#endif
{
    public:
        /**
        * Constructor
        *@param pProcess - process, can be NULL
        *@param activityType - activity type
        *@param excludedActivity - excluded activity
        *@param stopOnFound - if TRUE, search will stop on first found item
        *@param attributedActivityOnly - if TRUE, only attributed activity will be processed
        */
        PSS_ActivityListAttributionCtrl(ZProcess*      pProcess               = NULL,
                                        int            activityType           = 0,
                                        const CString& excludedActivity       = "",
                                        BOOL           stopOnFound            = TRUE,
                                        BOOL           attributedActivityOnly = FALSE);

        virtual ~PSS_ActivityListAttributionCtrl();

        /**
        * Initializes the control
        *@param pProcess - process
        *@param activityType - activity type
        *@param excludedActivity - excluded activity
        *@param stopOnFound - if TRUE, search will stop on first found item
        *@param attributedActivityOnly - if TRUE, only attributed activity will be processed
        */
        virtual int Initialize(ZProcess*      pProcess,
                               int            activityType           = 0,
                               const CString& excludedActivity       = "",
                               BOOL           stopOnFound            = TRUE,
                               BOOL           attributedActivityOnly = FALSE);

        /**
        * Gets the selected activity
        *@return the selected activity, empty string if no selection or on error
        */
        virtual CString GetSelectedActivity();

        /**
        * Gets the selected activities
        *@param[out] activitiesArray - array containing the selected activities
        *@return selected activity count
        */
        virtual int GetSelectedActivities(CStringArray& activitiesArray);

        /**
        * Refreshes the control
        *@return activity count
        */
        virtual int Refresh();

    protected:
        //{{AFX_MSG(PSS_ActivityListAttributionCtrl)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        ZProcess* m_pProcess;
        int       m_ActivityType;
        CString   m_ExcludedActivity;
        BOOL      m_StopOnFound;
        BOOL      m_AttributedActivityOnly;
    
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ActivityListAttributionCtrl(const PSS_ActivityListAttributionCtrl &right);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityListAttributionCtrl & operator = (const PSS_ActivityListAttributionCtrl &right);
};

#endif
