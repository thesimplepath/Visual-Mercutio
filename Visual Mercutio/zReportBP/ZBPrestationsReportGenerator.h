// **************************************************************************************************************
// *                                    Classe ZBPrestationsReportGenerator                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 8 mars 2006 - Ajout de la classe ZBPrestationsReportGenerator.                                *
// **************************************************************************************************************
// * Cette classe permet la génération d'un rapport de type Prestations dans un nouveau document.                *
// **************************************************************************************************************

#if !defined(AFX_ZBPrestationsReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_)
#define AFX_ZBPrestationsReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_

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

// Architecture document/vue
#include "zReport\ZDGridDoc.h"
#include "zReport\ZVGridView.h"
#include "zReport\ZDGridDoc.h"
#include "zReport\zReportRes.h"

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

#include "ColorRefDefinition.h"
#include "zReportBPRes.h"
#include "PSS_ModelResIDs.h"

#include "ZBModelBPReportGenerator.h"

// old class name mapping
#ifndef PSS_LogicalPrestationsEntity
    #define PSS_LogicalPrestationsEntity ZBLogicalPrestationsEntity
#endif

// forward class declaration
class PSS_LogicalPrestationsEntity;

#ifdef _ZREPORTBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// ******************************************************************************************************
// *                                           Classes internes                                            *
// ******************************************************************************************************

// Classe conteneur de données relatives aux processus contenant une prestation.
class AFX_EXT_CLASS _ZBProcessDatas : public CObject
{
public:

    _ZBProcessDatas(CString                    ProcessName = _T(""),
                    PSS_AnnualNumberPropertiesBP    Workload = 0,
                    PSS_AnnualNumberPropertiesBP    Cost = 0,
                    PSS_AnnualNumberPropertiesBP    CostHMO = 0,
                    float                        Percentage = 0.0f);

    ~_ZBProcessDatas();

    void SetName(CString Name);
    CString GetName();

    void SetWorkload(PSS_AnnualNumberPropertiesBP Workload);
    PSS_AnnualNumberPropertiesBP GetWorkload();

    void SetCost(PSS_AnnualNumberPropertiesBP Cost);
    PSS_AnnualNumberPropertiesBP GetCost();

    void SetCostHMO(PSS_AnnualNumberPropertiesBP CostHMO);
    PSS_AnnualNumberPropertiesBP GetCostHMO();

    void SetPercentage(double Percentage);
    double GetPercentage();

private:

    CString                        m_ProcessName;
    PSS_AnnualNumberPropertiesBP    m_Workload;
    PSS_AnnualNumberPropertiesBP    m_Cost;
    PSS_AnnualNumberPropertiesBP    m_CostHMO;
    double                        m_ProprietaryPrestPercentage;
};

// Classe conteneur de données relatives aux prestations.
class AFX_EXT_CLASS _ZBPrestationsDatas : public CObject
{
public:

    _ZBPrestationsDatas(CString PrestationName = _T(""));
    ~_ZBPrestationsDatas();

    void SetName(CString Name);
    CString GetName();

    void GenerateHierarchy(PSS_LogicalPrestationsEntity* pPrestations, int Level = 0);
    void Associate(PSS_ProcessSymbolBP* Process);
    void UpdateTotals();

    void DisplayDatas(ZBOStreamGrid    &ostream,
                      CStringArray&    ProcessNameArray,
                      CGXStyle            DisplayStyle,
                      CGXStyle            AmountStyle,
                      CGXStyle            NumericStyle,
                      int                Index,
                      bool                IncludeMonthDetails);

    PSS_AnnualNumberPropertiesBP GetTotalWorkload();
    PSS_AnnualNumberPropertiesBP GetTotalCost();
    PSS_AnnualNumberPropertiesBP GetTotalCostHMO();

    CObList* GetProcessList();

private:

    void InternalUpdateTotals();

private:

    CString                        m_PrestationName;
    CString                        m_Space;

    PSS_AnnualNumberPropertiesBP    m_TotalWorkload;
    PSS_AnnualNumberPropertiesBP    m_TotalCost;
    PSS_AnnualNumberPropertiesBP    m_TotalCostHMO;

    CObList                        m_ProcessList;
    CObList                        m_ChildPrestationsList;
};

// ******************************************************************************************************
// *                                Classe ZBPrestationsReportGenerator                                    *
// ******************************************************************************************************

class AFX_EXT_CLASS ZBPrestationsReportGenerator : public ZBModelBPReportGenerator
{
    DECLARE_SERIAL(ZBPrestationsReportGenerator)

public:

    ZBPrestationsReportGenerator(ZDGridDocument*            pDoc = NULL,
                                 PSS_ProcessGraphModelMdlBP*    pModel = NULL,
                                 PSS_ProcessGraphModelDoc*    pSourceDoc = NULL,
                                 bool                        IncludeMonthDetails = true);

    virtual ~ZBPrestationsReportGenerator();

    /////////////////////////////////////////////////////////////////////////////
    // ZIGridReportGenerator methods

    // Called by the framework to request a grid to be filled
    // The implementation uses the delegation
    virtual bool FillGrid(CGXGridCore& GridCore, size_t Index);

    virtual const CString GetReportTitle() const;

protected:

    virtual void FillTabArray();

private:

    bool FillGridPrestationsReport(CGXGridCore& GridCore, int Index);
    void FillGridPrestationsHeaders(ZBOStreamGrid &ostream, ZVGridView* pView, int Index);
    void FillPrestationsDatas();
    void Associate(PSS_ProcessGraphModelMdlBP* m_RootModel);
    void UpdateTotals();
    void RemoveObsoleteDatas();

    CPoint CheckColumn(ZBOStreamGrid &ostream, int Quantity);

private:

    CStringArray    m_ProcessNameArray;

    CObList            m_PrestationsArray;

    CGXStyle        m_HeaderStyle;
    CGXStyle        m_NormalStyle;
    CGXStyle        m_BlackBorderStyle;
    CGXStyle        m_AmountFormatStyle;
    CGXStyle        m_NumericCellStyle;

    CSize            m_HeaderPrestationsTitle;
    CSize            m_HeaderStandardTitle;
    CSize            m_HeadersDetailsTitle;

    bool            m_IncludeMonthDetail;
};

#endif
