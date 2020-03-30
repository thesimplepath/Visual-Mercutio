/****************************************************************************
 * ==> PSS_SesterceConsolidatedReportGenerator -----------------------------*
 ****************************************************************************
 * Description : Provides a Sesterce consolidated report generator          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SesterceConsolidatedReportGeneratorH
#define PSS_SesterceConsolidatedReportGeneratorH

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
#ifndef PSS_SesterceConsolidatedReportGenerator
    #define PSS_SesterceConsolidatedReportGenerator ZBSesterceConsolidatedReportGenerator
#endif

// processsoft
#include "zModelBP\PSS_UserGroupCalculateTotals.h"
#include "PSS_ModelBPReportGenerator.h"

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
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Sesterce consolidated report generator
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SesterceConsolidatedReportGenerator : public PSS_ModelBPReportGenerator
{
    DECLARE_SERIAL(PSS_SesterceConsolidatedReportGenerator)

    public:
        /**
        * Constructor
        *@param pDoc - the document
        *@param pModel - the model
        *@param pSourceDoc - the source document
        *@param includeMonthDetails - if true, the month details will be included
        */
        PSS_SesterceConsolidatedReportGenerator(PSS_GridDocument*           pDoc                = NULL,
                                                PSS_ProcessGraphModelMdlBP* pModel              = NULL,
                                                PSS_ProcessGraphModelDoc*   pSourceDoc          = NULL,
                                                bool                        includeMonthDetails = true);

        virtual ~PSS_SesterceConsolidatedReportGenerator();

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
        virtual bool FillGrid(CGXGridCore& gridCore, std::size_t index);

    protected:
        /**
        * Fills the tab array
        */
        virtual void FillTabArray();

    private:
        static int   m_UnitLevel;
        CGXStyle     m_NormalStyle;
        CGXStyle     m_BoldStyle;
        CGXStyle     m_RoseStyle;
        CGXStyle     m_BoldRoseStyle;
        CGXStyle     m_BlueStyle;
        CGXStyle     m_GreenStyle;
        CGXStyle     m_RedStyle;
        CGXStyle     m_GrayStyle;
        CGXStyle     m_LightGrayStyle;
        CGXStyle     m_BlackBorderStyle;
        CGXStyle     m_LeftOnlyBlackBorderStyle;
        CGXStyle     m_PercentFormatStyle;
        CGXStyle     m_AmountFormatStyle;
        CGXStyle     m_NumberTwoDecFormatStyle;
        CGXStyle     m_NumericCellStyle;
        CStringArray m_ProcessNameArray;
        CObArray     m_ModelArray;
        CObArray     m_NavigationTotalArray;
        bool         m_IncludeMonthDetails;

        /**
        * Removes all the data
        */
        void RemoveAllData();

        /**
        * Fills the grid unit group
        *@param pGroup - the unit group to fill
        *@param ostream - the output stream
        */
        void FillGridUnitGroup(PSS_UserGroupEntity* pGroup, std::size_t Index, PSS_OStreamGrid& ostream);

        /**
        * Fills the grid unit role
        *@param pRole - the unit role to fill
        *@param ostream - the output stream
        */
        void FillGridUnitRole(PSS_UserRoleEntity* pRole, std::size_t Index, PSS_OStreamGrid& ostream);

        /**
        * Fills the process figures
        *@param pModel - the model
        *@param pTotal - the total
        *@param pGroup - the group
        *@param index - the index
        *@param ostream - the output stream
        */
        void FillProcessFigures(PSS_ProcessGraphModelMdl*     pModel,
                                PSS_UserGroupCalculateTotals* pTotal,
                                PSS_UserGroupEntity*          pGroup,
                                std::size_t                   index,
                                PSS_OStreamGrid&              ostream);
};

#endif
