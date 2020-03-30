/****************************************************************************
 * ==> PSS_PrestationsReportGenerator --------------------------------------*
 ****************************************************************************
 * Description : Provides a prestations report generator                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PrestationsReportGeneratorH
#define PSS_PrestationsReportGeneratorH

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
#ifndef PSS_PrestationsReportGenerator
    #define PSS_PrestationsReportGenerator ZBPrestationsReportGenerator
#endif

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zBaseLib\PSS_Tokenizer.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_LogicalPrestationsEntity.h"
#include "zModel\PSS_ProcessGraphPage.h"
#include "zModelBP\PSS_ProcessGraphModelMdlBP.h"
#include "zModelBP\PSS_ProcessSymbolBP.h"
#include "zModelBP\PSS_DeliverableLinkSymbolBP.h"
#include "zModelBP\PSS_ExtractProcessName.h"
#include "zModelBP\PSS_DeliveriesPropertiesBP.h"
#include "zModelBP\PSS_AnnualNumberPropertiesBP.h"
#include "zProperty\PSS_Property.h"
#include "zReport\PSS_GridDocument.h"
#include "zReport\PSS_GridView.h"
#include "PSS_ModelBPReportGenerator.h"
#include "PSS_ColorRefDefinition.h"
#include "PSS_ModelResIDs.h"

// resources
#include "zReport\zReportRes.h"
#include "zReportBPRes.h"

// old class name mapping
#ifndef PSS_LogicalPrestationsEntity
    #define PSS_LogicalPrestationsEntity ZBLogicalPrestationsEntity
#endif

// forward class declaration
class PSS_LogicalPrestationsEntity;

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
* Prestations report generator
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PrestationsReportGenerator : public PSS_ModelBPReportGenerator
{
    DECLARE_SERIAL(PSS_PrestationsReportGenerator)

    public:
        /**
        * Constructor
        *@param pDoc - the document
        *@param pModel - the model
        *@param pSourceDoc - the source document
        *@param includeMonthDetails - if true, the month details will be included
        */
        PSS_PrestationsReportGenerator(PSS_GridDocument*           pDoc                = NULL,
                                       PSS_ProcessGraphModelMdlBP* pModel              = NULL,
                                       PSS_ProcessGraphModelDoc*   pSourceDoc          = NULL,
                                       bool                        includeMonthDetails = true);

        virtual ~PSS_PrestationsReportGenerator();

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
        * Process owning prestation data
        */
        class AFX_EXT_CLASS IProcessData : public CObject
        {
            public:
                /**
                * Constructor
                *@param processName - the process name
                *@param workload - the workload
                *@param cost - the cost
                *@param costHMO - the HMO cost
                *@param percentage - the percentage
                */
                IProcessData(const CString&                      processName = _T(""),
                             const PSS_AnnualNumberPropertiesBP& workload    = 0,
                             const PSS_AnnualNumberPropertiesBP& cost        = 0,
                             const PSS_AnnualNumberPropertiesBP& costHMO     = 0,
                             float                               percentage  = 0.0f);

                virtual ~IProcessData();

                /**
                * Gets the name
                *@return the name
                */
                virtual CString GetName();

                /**
                * Sets the name
                *@param name - the name
                */
                virtual void SetName(const CString& name);

                /**
                * Gets the workload
                *@return the workload
                */
                virtual PSS_AnnualNumberPropertiesBP GetWorkload();

                /**
                * Sets the workload
                *@param workload - the workload
                */
                virtual void SetWorkload(const PSS_AnnualNumberPropertiesBP& workload);

                /**
                * Gets the cost
                *@return the cost
                */
                virtual PSS_AnnualNumberPropertiesBP GetCost();

                /**
                * Sets the cost
                *@param cost - the cost
                */
                virtual void SetCost(const PSS_AnnualNumberPropertiesBP& cost);

                /**
                * Gets the HMO cost
                *@return the HMO cost
                */
                virtual PSS_AnnualNumberPropertiesBP GetCostHMO();

                /**
                * Sets the HMO cost
                *@param name - the HMO cost
                */
                virtual void SetCostHMO(const PSS_AnnualNumberPropertiesBP& costHMO);

                /**
                * Gets the percentage
                *@return the percentage
                */
                virtual double GetPercentage();

                /**
                * Sets the percentage
                *@param name - the percentage
                */
                virtual void SetPercentage(double Percentage);

            private:
                PSS_AnnualNumberPropertiesBP m_Workload;
                PSS_AnnualNumberPropertiesBP m_Cost;
                PSS_AnnualNumberPropertiesBP m_CostHMO;
                CString                      m_ProcessName;
                double                       m_ProprietaryPrestPercentage;
        };

        /**
        * Prestations data
        */
        class AFX_EXT_CLASS IPrestationsData : public CObject
        {
            public:
                /**
                * Constructor
                *@param prestationName - the prestation name
                */
                IPrestationsData(const CString& prestationName = _T(""));

                virtual ~IPrestationsData();

                /**
                * Gets the name
                *@return the name
                */
                virtual CString GetName();

                /**
                * Sets the name
                *@param name - the name
                */
                virtual void SetName(const CString& name);

                /**
                * Generates the hierarchy
                *@param pPrestations - the prestations
                *@param level - the level
                */
                virtual void GenerateHierarchy(PSS_LogicalPrestationsEntity* pPrestations, int level = 0);

                /**
                * Associates the process with the prestation
                *@param pProcess - the process to associate
                */
                virtual void Associate(PSS_ProcessSymbolBP* pProcess);

                /**
                * Updates the totals
                */
                virtual void UpdateTotals();

                /**
                * Shows the data at index
                *@param ostream - the output stream
                *@param processNameArray - the process name array
                *@param style - the main style
                *@param amountStyle - the amount style
                *@param style - the numeric style
                *@param index - the index
                *@param includeMonthDetails - if true, the month details will be included
                */
                virtual void ShowData(PSS_OStreamGrid& ostream,
                                      CStringArray&    processNameArray,
                                      const CGXStyle&  style,
                                      const CGXStyle&  amountStyle,
                                      const CGXStyle&  numericStyle,
                                      int              index,
                                      bool             includeMonthDetails);

                /**
                * Gets the total workload
                *@return the total workload
                */
                virtual PSS_AnnualNumberPropertiesBP GetTotalWorkload();

                /**
                * Gets the total cost
                *@return the total cost
                */
                virtual PSS_AnnualNumberPropertiesBP GetTotalCost();

                /**
                * Gets the total HMO cost
                *@return the total HMO cost
                */
                virtual PSS_AnnualNumberPropertiesBP GetTotalCostHMO();

                /**
                * Gets the process list
                *@return the process list
                */
                virtual CObList* GetProcessList();

            private:
                PSS_AnnualNumberPropertiesBP m_TotalWorkload;
                PSS_AnnualNumberPropertiesBP m_TotalCost;
                PSS_AnnualNumberPropertiesBP m_TotalCostHMO;
                CObList                      m_ProcessList;
                CObList                      m_ChildPrestationsList;
                CString                      m_PrestationName;
                CString                      m_Space;

                /**
                * Update the totals (internal version)
                */
                void InternalUpdateTotals();
        };

        /**
        * Fills the tab array
        */
        virtual void FillTabArray();

    private:
        CStringArray m_ProcessNameArray;
        CObList      m_PrestationsArray;
        CGXStyle     m_HeaderStyle;
        CGXStyle     m_NormalStyle;
        CGXStyle     m_BlackBorderStyle;
        CGXStyle     m_AmountFormatStyle;
        CGXStyle     m_NumericCellStyle;
        CSize        m_HeaderPrestationsTitle;
        CSize        m_HeaderStandardTitle;
        CSize        m_HeadersDetailsTitle;
        bool         m_IncludeMonthDetails;

        /**
        * Fills the grid prestation report at index
        *@param gridCore - the grid core
        *@param index - the index
        */
        bool FillGridPrestationsReport(CGXGridCore& gridCore, int index);

        /**
        * Fills the grid prestation headers at index
        *@param ostream - the output stream
        *@param pView - the view
        *@param gridCore - the grid core
        *@param index - the index
        */
        void FillGridPrestationsHeaders(PSS_OStreamGrid& ostream, PSS_GridView* pView, int index);

        /**
        * Fills the prestations data
        */
        void FillPrestationsData();

        /**
        * Associates the model with the report
        *@param pRootModel - the root model to associate
        */
        void Associate(PSS_ProcessGraphModelMdlBP* pRootModel);

        /**
        * Updates the totals
        */
        void UpdateTotals();

        /**
        * Removes the obsolete data
        */
        void RemoveObsoleteDatas();

        /**
        * Checks the column
        *@param ostream - the output stream
        *@param quantity - the quantity
        *@return the column position
        */
        CPoint CheckColumn(PSS_OStreamGrid& ostream, int quantity);
};

#endif
