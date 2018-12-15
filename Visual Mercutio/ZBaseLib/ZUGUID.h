// ZUGUID.h: interface for the ZUGUID class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUGUID_H__04FCF69B_C60A_4906_B330_4ECC3EAE4EB7__INCLUDED_)
#define AFX_ZUGUID_H__04FCF69B_C60A_4906_B330_4ECC3EAE4EB7__INCLUDED_

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

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 11 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZUGUID
{
public:
    ZUGUID();
    virtual ~ZUGUID();

    // Returns a new GUID 
    static CString CreateNewGUID();

    // Returns true if the string contains a valid GUID
    static bool GUIDIsValid( const CString s );
};

#endif // !defined(AFX_ZUGUID_H__04FCF69B_C60A_4906_B330_4ECC3EAE4EB7__INCLUDED_)