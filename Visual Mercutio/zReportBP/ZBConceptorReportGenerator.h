// ZBConceptorReportGenerator.h: interface for the ZBConceptorReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBConceptorReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_)
#define AFX_ZBConceptorReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_

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
#include "ZBModelBPReportGenerator.h"

// class name mapping
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif
#ifndef PSS_UserRoleEntity
    #define PSS_UserRoleEntity ZBUserRoleEntity
#endif

// forward class declaration
class PSS_UserGroupEntity;
class PSS_UserRoleEntity;

#ifdef _ZREPORTBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 29 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBConceptorReportGenerator : public ZBModelBPReportGenerator
{
    DECLARE_SERIAL(ZBConceptorReportGenerator)

public:

    ZBConceptorReportGenerator(ZDGridDocument*                pDoc = NULL,
                               ZDProcessGraphModelMdlBP*    pModel = NULL,
                               PSS_ProcessGraphModelDoc*        pSourceDoc = NULL,
                               BOOL                        bIncludeSynthesis = TRUE,
                               BOOL                        bIncludeDetail = TRUE,
                               BOOL                        bIncludeDeliverables = TRUE);

    virtual ~ZBConceptorReportGenerator();

    /////////////////////////////////////////////////////////////////////////////
    // ZIGridReportGenerator methods

    virtual void Initialize(ZDGridDocument*            pDoc,
                            ZDProcessGraphModelMdlBP*    pModel,
                            PSS_ProcessGraphModelDoc*    pSourceDoc,
                            BOOL                        bIncludeSynthesis = TRUE,
                            BOOL                        bIncludeDetail = TRUE,
                            BOOL                        bIncludeDeliverables = TRUE);

    // Called by the framework to request a grid to be filled
    // The implementation uses the delegation
    virtual bool FillGrid(CGXGridCore& GridCore, size_t Index);

    virtual const CString GetReportTitle() const;

    // Serialization call-back
    virtual void OnPostRead(CArchive& ar);

    // Implementation
public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    void FillTabArray();

private:

    void RemoveAllData();
    void FillTabUnitGroup(PSS_UserGroupEntity* pGroup);
    bool FillSynthesis(ZBOStreamGrid& ostream, size_t Index);
    bool FillGridAllProcess(ZBOStreamGrid& ostream, size_t Index);

private:

    CStringArray    m_ProcessNameArray;
    CStringArray    m_UnitCommentArray;
    CObArray        m_ModelArray;

    BOOL            m_IncludeSynthesis;
    BOOL            m_IncludeDetail;
    BOOL            m_IncludeDeliverables;

    CGXStyle        m_BlueStyle;
    CGXStyle        m_OrangeStyle;
    CGXStyle        m_GrayStyle;

    CGXStyle        m_BlackBorderStyle;
    CGXStyle        m_LeftOnlyBlackBorderStyle;
    CGXStyle        m_RightOnlyBlackBorderStyle;
    CGXStyle        m_TopOnlyBlackBorderStyle;
    CGXStyle        m_BottomOnlyBlackBorderStyle;
};

#endif
