/////////////////////////////////////////////////////////////////////////////
//@doc ZUGridSesterceProcessNavigation
//@module ZUGridSesterceProcessNavigation.h | Interface of the <c ZUGridSesterceProcessNavigation> class.
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
// <nl>Description:  ZUGridSesterceProcessNavigation navigates through the process and
//                     write process information to the grid
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUGridSesterceProcessNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUGridSesterceProcessNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zModelBP\ZUProcessNavigation.h"

/////////////////////////////////////////////////////////////////////////////
// Forward declaration
class ZBOStreamGrid;

// JMR-MODIF - Le 7 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class ZUGridSesterceProcessNavigation : public ZUProcessNavigation
{
public:
    //*@param pClass - the custom data class, can be NULL
    ZUGridSesterceProcessNavigation(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);
    virtual ~ZUGridSesterceProcessNavigation();

    // Call-back methods
    virtual bool OnStart();
    virtual bool OnFinish();
    virtual bool OnProcedureSymbol(PSS_ProcedureSymbolBP*        pSymbol);
    virtual bool OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP*    pSymbol);

private:

    ZBOStreamGrid*    m_postream;

    // Styles
    CGXStyle        m_NormalStyle;
    CGXStyle        m_BoldStyle;
    CGXStyle        m_RoseStyle;
    CGXStyle        m_BoldRoseStyle;
    CGXStyle        m_BlueStyle;
    CGXStyle        m_GreenStyle;
    CGXStyle        m_RedStyle;
    CGXStyle        m_GrayStyle;
    CGXStyle        m_LightGrayStyle;

    CGXStyle        m_BlackBorderStyle;
    CGXStyle        m_LeftOnlyBlackBorderStyle;

    CGXStyle        m_PercentFormatStyle;
    CGXStyle        m_AmountFormatStyle;
    CGXStyle        m_NumberTwoDecFormatStyle;
    CGXStyle        m_NumericCellStyle;
};

#endif
