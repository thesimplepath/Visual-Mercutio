// ZBCheckReportGenerator.h: interface for the ZBCheckReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBCheckReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_)
#define AFX_ZBCheckReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_

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

#include "ZBModelBPReportGenerator.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBUserGroupEntity;
class ZBUserRoleEntity;

#ifdef _ZREPORTBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 7 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBCheckReportGenerator : public ZBModelBPReportGenerator
{
	DECLARE_SERIAL( ZBCheckReportGenerator )

public:

	ZBCheckReportGenerator( ZDGridDocument*				pDoc		= NULL,
							ZDProcessGraphModelMdlBP*	pModel		= NULL,
							ZDProcessGraphModelDoc*		pSourceDoc	= NULL );

	virtual ~ZBCheckReportGenerator();

	/////////////////////////////////////////////////////////////////////////////
	// ZIGridReportGenerator methods

	// Called by the framework to request a grid to be filled
	// The implementation uses the delegation
	virtual bool FillGrid( CGXGridCore& GridCore, size_t Index );

	virtual const CString GetReportTitle() const;

protected:

	virtual void FillTabArray();

private:

	bool FillGridUnit		( CGXGridCore& GridCore );
	void FillGridUnitGroup	( ZBUserGroupEntity* pGroup, ZBOStreamGrid &ostream );
	void FillGridUnitRole	( ZBUserRoleEntity* pRole, ZBOStreamGrid &ostream );
	bool FillGridProcess	( CGXGridCore& GridCore, size_t Index );
};

#endif // !defined(AFX_ZBCheckReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_)