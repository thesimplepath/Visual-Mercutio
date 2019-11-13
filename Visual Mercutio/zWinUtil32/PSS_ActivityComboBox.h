/****************************************************************************
 * ==> PSS_ActivityComboBox ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity combo box                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityComboBoxH
#define PSS_ActivityComboBoxH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
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
* Activity combo box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
#ifdef _WIN32
    // 32 bit version
    class AFX_EXT_CLASS PSS_ActivityComboBox : public CCJFlatComboBox
#else
    // 16 bit version
    class AFX_EXT_CLASS PSS_ActivityComboBox : public CComboBox
#endif
{
    public:
        /**
        * Constructor
        *@param pProcess - process, may be NULL
        *@param activityType - activity type
        *@param excludedActivity - excluded activity
        *@param stopOnFound - if TRUE, stop the search on found
        *@param attributedActivityOnly - if TRUE, attributed activity only will be processed
        */
        PSS_ActivityComboBox(PSS_Process*   pProcess               = NULL,
                             int            activityType           = 0,
                             const CString& excludedActivity       = "",
                             BOOL           stopOnFound            = TRUE,
                             BOOL           attributedActivityOnly = FALSE);

        virtual ~PSS_ActivityComboBox();

        /**
        * Initializes the combo box
        *@param pProcess - process, may be NULL
        *@param activityType - activity type
        *@param excludedActivity - excluded activity
        *@param stopOnFound - if TRUE, stop the search on found
        *@param attributedActivityOnly - if TRUE, attributed activity only will be processed
        */
        virtual int Initialize(PSS_Process*   pProcess,
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
        * Selects an activity
        *@param activityName - activity name to select
        */
        virtual void SelectActivity(const CString& activityName);

        /**
        * Refreshes the combo box
        */
        virtual int Refresh();

    private:
        PSS_Process* m_pProcess;
        CString      m_ExcludedActivity;
        int          m_ActivityType;
        BOOL         m_StopOnFound;
        BOOL         m_AttributedActivityOnly;

        /**
        * Copy constructor
        *@param other - other combo box to copy from
        */
        PSS_ActivityComboBox(const PSS_ActivityComboBox& other);

        /**
        * Copy operator
        *@param other - other combo box to copy from
        *@return copy of itself
        */
        const PSS_ActivityComboBox& operator = (const PSS_ActivityComboBox& other);
};

#endif
