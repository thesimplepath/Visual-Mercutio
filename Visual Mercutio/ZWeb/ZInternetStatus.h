// ZInternetStatus.h: interface for the ZInternetStatus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZINTERNETSTATUS_H__53C888A5_D428_4008_BFD6_8482C0747E69__INCLUDED_)
#define AFX_ZINTERNETSTATUS_H__53C888A5_D428_4008_BFD6_8482C0747E69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZWEBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 26 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commenatires)

class AFX_EXT_CLASS ZInternetStatus
{
public:

    ZInternetStatus();
    virtual ~ZInternetStatus();

    // JMR-MODIF - Le 26 janvier 2006 - TEMPORAIRE : Erreur inexpliquée avec afxsock, lié à une fonction apparamment
    // inutilisée, temporairement désactivée le temps de trouver une réponse.
    //bool IsConnected();
};

#endif // !defined(AFX_ZINTERNETSTATUS_H__53C888A5_D428_4008_BFD6_8482C0747E69__INCLUDED_)