// ZBIStreamGrid.h: interface for the ZBIStreamGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBISTREAMGRID_H__BF3A0819_013A_4A0A_A7BF_902B83C96AFB__INCLUDED_)
#define AFX_ZBISTREAMGRID_H__BF3A0819_013A_4A0A_A7BF_902B83C96AFB__INCLUDED_

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

#include "ZBIOSGrid.h"

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

class AFX_EXT_CLASS ZBIStreamGrid : virtual public ZBIOSGrid
{
public:

	ZBIStreamGrid( CGXGridCore* pGridCore = NULL );
	virtual ~ZBIStreamGrid();
};

#endif // !defined(AFX_ZBISTREAMGRID_H__BF3A0819_013A_4A0A_A7BF_902B83C96AFB__INCLUDED_)