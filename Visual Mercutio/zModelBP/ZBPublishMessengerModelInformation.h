// ZBPublishMessengerModelInformation.h: interface for the ZBPublishMessengerModelInformation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ZBPublishMessengerModelInformation_H__)
#define _ZBPublishMessengerModelInformation_H__

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

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZDProcessGraphModelDoc;

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 29 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZBPublishMessengerModelInformation

class AFX_EXT_CLASS ZBPublishMessengerModelInformation
{
public:

    // JMR-MODIF - Le 21 juin 2006 - Ajout de l'alias et des dates dans les paramètres de construction de la classe.
    ZBPublishMessengerModelInformation( ZDProcessGraphModelDoc*    pDoc,
                                        CString                    MessengerAddress,
                                        CString                    MessengerAlias )
    {
        m_pDoc                = pDoc;
        m_MessengerAddress    = MessengerAddress;
        m_MessengerAlias    = MessengerAlias;
        m_BeginDate            = _T( "" );
        m_EndDate            = _T( "" );
    };

    virtual ~ZBPublishMessengerModelInformation()
    {
    };

    CString                    m_MessengerAddress;

    // JMR-MODIF - Le 21 juin 2006 - Ajout des variables m_MessengerAlias, m_BeginDate et m_EndDate.
    CString                    m_MessengerAlias;
    CString                    m_BeginDate;
    CString                    m_EndDate;

    ZDProcessGraphModelDoc*    m_pDoc;
};

#endif // !defined(_ZBPublishMessengerModelInformation_H__)