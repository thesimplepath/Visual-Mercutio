/****************************************************************************
 * ==> PSS_ActivityAttributionInputWizard ----------------------------------*
 ****************************************************************************
 * Description : Provides an activity attribution input wizard              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityAttributionInputWizardH
#define PSS_ActivityAttributionInputWizardH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_Mail.h"
#include "zBaseLib\PSS_UserManager.h"
#include "zEvent\Activity.h"

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
* Activity attribution input Wizard
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityAttributionInputWizard
{
    public:
        /**
        * Constructor
        *@param userManager - user manager
        *@param mail - mail
        *@param pActivity - activity
        *@param lastActivity - if TRUE, activity is the last activity
        *@param userAttribution - if TRUE, is an user attribution
        *@param backupUserAttribution - if TRUE, is a backup user attribution
        *@param timeAttribution - if TRUE, is a time attribution
        *@param visibilityAttribution - if TRUE, is a visibility attribution
        *@param pParent - parent window, can be NULL
        */
        PSS_ActivityAttributionInputWizard(PSS_UserManager& userManager,
                                           PSS_Mail&        mail,
                                           ZActivity*       pActivity,
                                           BOOL             lastActivity,
                                           BOOL             userAttribution       = TRUE,
                                           BOOL             backupUserAttribution = TRUE,
                                           BOOL             timeAttribution       = TRUE,
                                           BOOL             visibilityAttribution = TRUE,
                                           CWnd*            pParent               = NULL);

        /**
        * Gets the activity
        *@return the activity
        */
        virtual inline ZActivity* GetActivity() const;

        /**
        * Executes the wizard
        *@return modal result
        */
        virtual int Execute();

    private:
        PSS_UserManager& m_UserManager;
        PSS_Mail&        m_Mail;
        ZActivity*       m_pActivity;
        BOOL             m_LastActivity;
        BOOL             m_UserAttribution;
        BOOL             m_BackupUserAttribution;
        BOOL             m_TimeAttribution;
        BOOL             m_VisibilityAttribution;

        /**
        * Processes the user backup
        *@return TRUE on success, otherwise FALSE
        */
        BOOL ProcessBackupUser();

        /**
        * Processes the base value
        *@return TRUE on success, otherwise FALSE
        */
        BOOL ProcessBaseValue();
};

//---------------------------------------------------------------------------
// PSS_ActivityAttributionInputWizard
//---------------------------------------------------------------------------
ZActivity* PSS_ActivityAttributionInputWizard::GetActivity() const
{
    return m_pActivity;
}
//---------------------------------------------------------------------------

#endif
