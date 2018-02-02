// ZBSesterceUnitReportGenerator.h: interface for the ZBSesterceUnitReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSesterceUnitReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_)
#define AFX_ZBSesterceUnitReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_

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
class ZDProcessGraphModelMdl;
class ZUUserGroupCalculateTotals;

#ifdef _ZREPORTBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 8 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBSesterceUnitReportGenerator : public ZBModelBPReportGenerator
{
	DECLARE_SERIAL( ZBSesterceUnitReportGenerator )

public:

	ZBSesterceUnitReportGenerator( ZDGridDocument*				pDoc				= NULL,
								   ZDProcessGraphModelMdlBP*	pModel				= NULL,
								   ZDProcessGraphModelDoc*		pSourceDoc			= NULL,
								   bool							IncludeMonthDetail	= true );

	virtual ~ZBSesterceUnitReportGenerator();

	/////////////////////////////////////////////////////////////////////////////
	// ZIGridReportGenerator methods
	
	// Called by the framework to request a grid to be filled
	// The implementation uses the delegation
	virtual bool FillGrid( CGXGridCore& GridCore, size_t Index );

	virtual const CString GetReportTitle() const;

protected:

	virtual void FillTabArray();

private:

	void RemoveAllData();
	void FillGridUnitGroup( ZBUserGroupEntity* pGroup, size_t Index, ZBOStreamGrid &ostream );
	void FillGridUnitRole( ZBUserRoleEntity* pRole, size_t Index, ZBOStreamGrid &ostream );

	void FillProcessFigures( ZDProcessGraphModelMdl*		pModel,
							 ZUUserGroupCalculateTotals*	pTotal,
							 ZBUserGroupEntity*				pGroup,
							 size_t							Index,
							 ZBOStreamGrid					&ostream );

// Implementation
private:

	CStringArray	m_ProcessNameArray;

	// Report's styles
	CGXStyle		m_NormalStyle;
	CGXStyle		m_BoldStyle;
	CGXStyle		m_RoseStyle;
	CGXStyle		m_BoldRoseStyle;
	CGXStyle		m_BlueStyle;
	CGXStyle		m_GreenStyle;
	CGXStyle		m_RedStyle;
	CGXStyle		m_GrayStyle;
	CGXStyle		m_LightGrayStyle;

	CGXStyle		m_BlackBorderStyle;
	CGXStyle		m_LeftOnlyBlackBorderStyle;

	CGXStyle		m_PercentFormatStyle;
	CGXStyle		m_AmountFormatStyle;
	CGXStyle		m_NumberTwoDecFormatStyle;
	CGXStyle		m_NumericCellStyle;


//	ZUUserGroupCalculateTotals m_UserGroupTotals;
	CObArray		m_ModelArray;
	CObArray		m_NavigationTotalArray;

	bool			m_IncludeMonthDetail;
};

#endif // !defined(AFX_ZBSesterceUnitReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_)