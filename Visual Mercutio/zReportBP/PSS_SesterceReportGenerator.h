/****************************************************************************
 * ==> PSS_SesterceReportGenerator -----------------------------------------*
 ****************************************************************************
 * Description : Provides a Sesterce report generator                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SesterceReportGeneratorH
#define PSS_SesterceReportGeneratorH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_SesterceReportGenerator
    #define PSS_SesterceReportGenerator ZBSesterceReportGenerator
#endif

// processsoft
#include "PSS_ModelBPReportGenerator.h"

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
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Sesterce report generator
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SesterceReportGenerator : public PSS_ModelBPReportGenerator
{
    DECLARE_SERIAL(PSS_SesterceReportGenerator)

    public:
        /**
        * Constructor
        *@param pDoc - the document
        *@param pModel - the model
        *@param pSourceDoc - the source document
        */
        PSS_SesterceReportGenerator(PSS_GridDocument*           pDoc       = NULL,
                                    PSS_ProcessGraphModelMdlBP* pModel     = NULL,
                                    PSS_ProcessGraphModelDoc*   pSourceDoc = NULL);

        virtual ~PSS_SesterceReportGenerator();

        /**
        * Gets the report title
        *@return the report title
        */
        virtual const CString GetReportTitle() const;

        /**
        * Fills the grid
        *@param gridCore - the grid to fill
        *@param index - the generator tab index
        */
        virtual bool FillGrid(CGXGridCore& GridCore, size_t Index);

    protected:
        /**
        * Fills the tab array
        */
        virtual void FillTabArray();

    private:
        CGXStyle m_HeaderStyle;
        CGXStyle m_NormalStyle;

        /**
        * Fills the grid unit
        *@param ostream - the output stream
        */
        bool FillGridUnit(CGXGridCore& gridCore);

        /**
        * Fills the grid unit group
        *@param pGroup - the unit group to fill
        *@param ostream - the output stream
        */
        void FillGridUnitGroup(PSS_UserGroupEntity* pGroup, PSS_OStreamGrid& ostream);

        /**
        * Fills the grid unit role
        *@param pRole - the unit role to fill
        *@param ostream - the output stream
        */
        void FillGridUnitRole(PSS_UserRoleEntity* pRole, PSS_OStreamGrid& ostream);

        /**
        * Fills the grid process at index
        *@param ostream - the output stream
        *@param index - the index
        */
        bool FillGridProcess(CGXGridCore& gridCore, std::size_t index);
};

#endif
