// ZBIOStreamGrid.h: interface for the ZBIOStreamGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBIOSTREAMGRID_H__800F9AB8_B3A2_4EF9_A34C_477321362153__INCLUDED_)
#define AFX_ZBIOSTREAMGRID_H__800F9AB8_B3A2_4EF9_A34C_477321362153__INCLUDED_

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

#include "ZBOStreamGrid.h"
#include "ZBIStreamGrid.h"

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

class AFX_EXT_CLASS ZBIOStreamGrid : public ZBIStreamGrid,
									 public ZBOStreamGrid
{
public:

	ZBIOStreamGrid( CGXGridCore* pGridCore = NULL );
	virtual ~ZBIOStreamGrid();
};

#endif // !defined(AFX_ZBIOSTREAMGRID_H__800F9AB8_B3A2_4EF9_A34C_477321362153__INCLUDED_)