/////////////////////////////////////////////////////////////////////////////
//@doc ZUGridMercutioRepDeliverableNavigation
//@module ZUGridMercutioRepDeliverableNavigation.h | Interface of the <c ZUGridMercutioRepDeliverableNavigation> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:		 07/2001
// <nl>Description:  ZUGridMercutioRepDeliverableNavigation navigates through the process and
//					 write process information to the grid
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUGridMercutioRepDeliverableNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUGridMercutioRepDeliverableNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zModelBP\ZUProcessNavigation.h"

/////////////////////////////////////////////////////////////////////////////
// Forward declaration
class ZBOStreamGrid;

// JMR-MODIF - Le 7 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class ZUGridMercutioRepDeliverableNavigation : public ZUProcessNavigation
{
public:

	ZUGridMercutioRepDeliverableNavigation( ZDProcessGraphModelMdl* pModel = NULL, void* pClass = NULL );
	virtual ~ZUGridMercutioRepDeliverableNavigation();

	// Call-back methods
	virtual bool OnStart();
	virtual bool OnFinish();
	virtual bool OnDeliverableLinkSymbol( ZBDeliverableLinkSymbol* pSymbol );

private:

	ZBOStreamGrid* m_postream;

	// Styles
	CGXStyle	m_NormalStyle;
	CGXStyle	m_BoldStyle;
	CGXStyle	m_BlueStyle;
	CGXStyle	m_BoldBlueStyle;
	CGXStyle	m_GrayStyle;
	CGXStyle	m_LightGrayStyle;
	CGXStyle	m_BlackBorderStyle;
	CGXStyle	m_LeftOnlyBlackBorderStyle;

	// String resources
	CString		m_DescriptionLabel;
	CString		m_RuleListLabel;
	CString		m_KeyInfoLabel;
	CString		m_FormListLabel;
	CString		m_InputProcedureLabel;
	CString		m_OutputProcedureLabel;
	CString		m_ComingFromProcedureLabel;
	CString		m_GoingToProcedureLabel;
	CString		m_InitialProcedureLabel;
	CString		m_FinalProcedureLabel;
};

#endif // !defined(AFX_ZUGridMercutioRepDeliverableNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)