// actattr.h : header file
//

#ifndef ActAttr_h
#define ActAttr_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


// ZUMail
#include "zBaseLib\ZUMail.h"

#include "zBaseLib\UserMng.h"

#include "zEvent\Activity.h"



#ifdef _ZWINUTIL32EXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

/////////////////////////////////////////////////////////////////////////////
// ZIActivityAttributionInput dialog

class AFX_EXT_CLASS ZIActivityAttributionInput
{
// Construction
public:
	ZIActivityAttributionInput(	ZUUserManager& UserManager, ZUMail& Mail, ZActivity* pActivity, 
								BOOL LastActivity, 
								BOOL UserAttribution = TRUE, 
								BOOL BackupUserAttribution = TRUE, 
								BOOL TimeAttribution = TRUE, 
								BOOL VisibilityAttribution = TRUE, CWnd* pParent = NULL);	// standard constructor
	ZActivity* 		GetActivity() { return m_pActivity; };
	int				DoModal();

private:
	ZUUserManager&	m_UserManager;
	ZUMail& 		m_Mail;
	ZActivity* 		m_pActivity;
	BOOL 			m_LastActivity;
	BOOL 			m_UserAttribution;
	BOOL			m_BackupUserAttribution;
	BOOL 			m_TimeAttribution; 	
	BOOL 			m_VisibilityAttribution;
private:
	BOOL	ProcessBackupUser();
	BOOL	ProcessBaseValue();
};



#endif
