/****************************************************************************
 * ==> PSS_ActivityListCtrl ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity list control                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityListCtrlH
#define PSS_ActivityListCtrlH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_ListCtrl.h"
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
* Activity list control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
#ifdef _WIN32
    // 32 bit version
    class AFX_EXT_CLASS PSS_ActivityListCtrl : public PSS_ListCtrl
#else
    // 16 bit version
    class AFX_EXT_CLASS PSS_ActivityListCtrl : public CListBox
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
        PSS_ActivityListCtrl(ZProcess*      pProcess               = NULL,
                             int            activityType           = 0,
                             const CString& excludedActivity       = "",
                             BOOL           stopOnFound            = TRUE,
                             BOOL           attributedActivityOnly = FALSE);

        virtual ~PSS_ActivityListCtrl();

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
        //{{AFX_MSG(PSS_ActivityListCtrl)
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
        PSS_ActivityListCtrl(const PSS_ActivityListCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityListCtrl & operator = (const PSS_ActivityListCtrl& other);
};

#endif
