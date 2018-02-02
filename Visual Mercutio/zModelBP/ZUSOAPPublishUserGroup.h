// ZUSOAPPublishUserGroup.h: interface for the ZUSOAPPublishUserGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUSOAPPUBLISHUSERGROUP_H__007D541D_39C0_4FA9_A177_CB51E06B7DE7__INCLUDED_)
#define AFX_ZUSOAPPUBLISHUSERGROUP_H__007D541D_39C0_4FA9_A177_CB51E06B7DE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zSOAP\pPublishWorkgroup.h"

//////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBUserGroupEntity;
class ZBUserRoleEntity;
class ZBPublishMessengerModelInformation;
class ZILog;

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 24 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Cette classe s'occupe de la publication des groupes utilisateurs.
class AFX_EXT_CLASS ZUSOAPPublishUserGroup
{
public:

	ZUSOAPPublishUserGroup( ZBPublishMessengerModelInformation* pInfo, ZILog* pLog = NULL );
	virtual ~ZUSOAPPublishUserGroup();

	bool Publish();

private:

	void _PublishUserGroup( ZBUserGroupEntity* pGroup );

	// JMR-MODIF - Le 24 janvier 2006 - Suppression de la routine de publication des rôles.
//	void _PublishUserRole( ZBUserRoleEntity* pRole );

private:

	ZBPublishMessengerModelInformation* m_pInfo;
	pPublishWorkgroup					m_pw;
	ZILog*								m_pLog;
};

#endif // !defined(AFX_ZUSOAPPUBLISHUSERGROUP_H__007D541D_39C0_4FA9_A177_CB51E06B7DE7__INCLUDED_)