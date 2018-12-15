/////////////////////////////////////////////////////////////////////////////
//@doc ZUGridMercutioRepProcedureNavigation
//@module ZUGridMercutioRepProcedureNavigation.h | Interface of the <c ZUGridMercutioRepProcedureNavigation> class.
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
// <nl>Created:         07/2001
// <nl>Description:  ZUGridMercutioRepProcedureNavigation navigates through the process and
//                     write process information to the grid
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUGridMercutioRepProcedureNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUGridMercutioRepProcedureNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zModelBP\ZUProcessNavigation.h"

/////////////////////////////////////////////////////////////////////////////
// Forward declaration
class ZBOStreamGrid;

// JMR-MODIF - Le 7 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class ZUGridMercutioRepProcedureNavigation : public ZUProcessNavigation
{
public:

    ZUGridMercutioRepProcedureNavigation( ZDProcessGraphModelMdl* pModel = NULL, void* pClass = NULL );
    virtual ~ZUGridMercutioRepProcedureNavigation();

    // Call-back methods
    virtual bool OnStart();
    virtual bool OnFinish();
    virtual bool OnProcedureSymbol( ZBBPProcedureSymbol* pSymbol );

private:

    ZBOStreamGrid*    m_postream;

    // Styles
    CGXStyle        m_NormalStyle;
    CGXStyle        m_BoldStyle;
    CGXStyle        m_BlueStyle;
    CGXStyle        m_BoldBlueStyle;
    CGXStyle        m_GrayStyle;
    CGXStyle        m_LightGrayStyle;

    CGXStyle        m_BlackBorderStyle;
    CGXStyle        m_LeftOnlyBlackBorderStyle;
    
    CGXStyle        m_PercentFormatStyle;
    CGXStyle        m_NumericCellStyle;

    // String resources
    CString            m_DescriptionLabel;
    CString            m_UnitLabel;
    CString            m_CombinationLabel;
    CString            m_RuleListLabel;
    CString            m_TaskListLabel;
    CString            m_DecisionListLabel;
    CString            m_FormsLabel;
    CString            m_AppsLabel;
    CString            m_OutputDeliverableLabel;
    CString            m_LateralDeliverableLabel;
};

#endif // !defined(AFX_ZUGridMercutioRepProcedureNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)