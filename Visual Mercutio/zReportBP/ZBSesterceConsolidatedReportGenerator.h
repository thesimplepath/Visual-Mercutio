// ZBSesterceConsolidatedReportGenerator.h: interface for the ZBSesterceConsolidatedReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSesterceConsolidatedReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_)
#define AFX_ZBSesterceConsolidatedReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_

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

// processsoft
#include "zModelBP\PSS_UserGroupCalculateTotals.h"
#include "ZBModelBPReportGenerator.h"

// class name mapping
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif
#ifndef PSS_UserRoleEntity
    #define PSS_UserRoleEntity ZBUserRoleEntity
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_UserGroupEntity;
class PSS_UserRoleEntity;
class PSS_ProcessGraphModelMdl;
class PSS_UserGroupCalculateTotals;

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

class AFX_EXT_CLASS ZBSesterceConsolidatedReportGenerator : public ZBModelBPReportGenerator
{
    DECLARE_SERIAL(ZBSesterceConsolidatedReportGenerator)

public:

    ZBSesterceConsolidatedReportGenerator(ZDGridDocument*                pDoc = NULL,
                                          PSS_ProcessGraphModelMdlBP*    pModel = NULL,
                                          PSS_ProcessGraphModelDoc*        pSourceDoc = NULL,
                                          bool                            IncludeMonthDetail = true);

    virtual ~ZBSesterceConsolidatedReportGenerator();

    /////////////////////////////////////////////////////////////////////////////
    // ZIGridReportGenerator methods

    // Called by the framework to request a grid to be filled
    // The implementation uses the delegation
    virtual bool FillGrid(CGXGridCore& GridCore, size_t Index);

    virtual const CString GetReportTitle() const;

protected:

    virtual void FillTabArray();

private:

    void RemoveAllData();
    void FillGridUnitGroup(PSS_UserGroupEntity* pGroup, size_t Index, ZBOStreamGrid &ostream);
    void FillGridUnitRole(PSS_UserRoleEntity* pRole, size_t Index, ZBOStreamGrid &ostream);

    void FillProcessFigures(PSS_ProcessGraphModelMdl*     pModel,
                            PSS_UserGroupCalculateTotals* pTotal,
                            PSS_UserGroupEntity*          pGroup,
                            size_t                        Index,
                            ZBOStreamGrid                 &ostream);

    // Implementation
private:

    CStringArray    m_ProcessNameArray;

    // Report's styles
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

    CObArray        m_ModelArray;
    CObArray        m_NavigationTotalArray;

    bool            m_IncludeMonthDetail;

    static int        m_UnitLevel;
};

#endif
