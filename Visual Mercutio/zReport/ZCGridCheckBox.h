// ZCGridCheckBox.h: interface for the ZCGridCheckBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZCGRIDCHECKBOX_H__24661DBC_8BAD_403E_99C5_F14D20C6231C__INCLUDED_)
#define AFX_ZCGRIDCHECKBOX_H__24661DBC_8BAD_403E_99C5_F14D20C6231C__INCLUDED_

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

#ifdef _ZREPORTEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZCGridCheckBox : public CGXCheckBox
{
public:

    ZCGridCheckBox( CGXGridCore* pGrid );
    virtual ~ZCGridCheckBox();

    virtual COLORREF GetColorValue( COLORREF rgb, BOOL bPrint );
};

#endif
