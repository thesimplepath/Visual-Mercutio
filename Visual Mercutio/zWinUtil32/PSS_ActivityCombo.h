/****************************************************************************
 * ==> PSS_ActivityCombo ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity combo box                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityComboH
#define PSS_ActivityComboH

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
    class AFX_EXT_CLASS PSS_ActivityCombo : public CCJFlatComboBox
#else
    // 16 bit version
    class AFX_EXT_CLASS PSS_ActivityCombo : public CComboBox
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
        PSS_ActivityCombo(ZProcess*      pProcess               = NULL,
                          int            activityType           = 0,
                          const CString& excludedActivity       = "",
                          BOOL           stopOnFound            = TRUE,
                          BOOL           attributedActivityOnly = FALSE);

        virtual ~PSS_ActivityCombo();

        /**
        * Initializes the combo box
        *@param pProcess - process, may be NULL
        *@param activityType - activity type
        *@param excludedActivity - excluded activity
        *@param stopOnFound - if TRUE, stop the search on found
        *@param attributedActivityOnly - if TRUE, attributed activity only will be processed
        */
        int Initialize(ZProcess*      pProcess,
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
        void SelectActivity(const CString& activityName);

        /**
        * Refreshes the combo box
        */
        int Refresh();

    private:
        ZProcess* m_pProcess;
        CString   m_ExcludedActivity;
        int       m_ActivityType;
        BOOL      m_StopOnFound;
        BOOL      m_AttributedActivityOnly;

        /**
        * Copy constructor
        *@param other - other combo box to copy from
        */
        PSS_ActivityCombo(const PSS_ActivityCombo& other);

        /**
        * Copy operator
        *@param other - other combo box to copy from
        */
        const PSS_ActivityCombo& operator = (const PSS_ActivityCombo& other);
};

#endif
