// ZBSesterceReportGenerator.h: interface for the ZBSesterceReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSesterceReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_)
#define AFX_ZBSesterceReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_

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

// JMR-MODIF - Le 7 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBSesterceReportGenerator : public ZBModelBPReportGenerator
{
    DECLARE_SERIAL(ZBSesterceReportGenerator)

public:

    ZBSesterceReportGenerator(PSS_GridDocument*                pDoc = NULL,
                              PSS_ProcessGraphModelMdlBP*    pModel = NULL,
                              PSS_ProcessGraphModelDoc*        pSourceDoc = NULL);

    virtual ~ZBSesterceReportGenerator();

    /////////////////////////////////////////////////////////////////////////////
    // PSS_GridReportGenerator methods

    // Called by the framework to request a grid to be filled
    // The implementation uses the delegation
    virtual bool FillGrid(CGXGridCore& GridCore, size_t Index);

    virtual const CString GetReportTitle() const;

protected:

    virtual void FillTabArray();

private:

    bool FillGridUnit(CGXGridCore& GridCore);
    void FillGridUnitGroup(PSS_UserGroupEntity* pGroup, PSS_OStreamGrid &ostream);
    void FillGridUnitRole(PSS_UserRoleEntity* pRole, PSS_OStreamGrid &ostream);
    bool FillGridProcess(CGXGridCore& GridCore, std::size_t Index);

private:

    CGXStyle m_HeaderStyle;
    CGXStyle m_NormalStyle;
};

#endif