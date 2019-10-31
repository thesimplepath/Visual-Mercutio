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

#include "zModel\ProcGraphModelDoc.h"
#include "zModel\ZBLogicalPrestationsEntity.h"
#include "zModel\ZDProcessGraphPage.h"

#include "zModelBP\ProcGraphModelMdlBP.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"
#include "zModelBP\ZUExtractProcessName.h"
#include "zModelBP\ZBBPDeliveriesProp.h"
#include "zModelBP\ZBBPAnnualNumberProp.h"

#include "zProperty\ZBProperty.h"

#include "ColorRefDefinition.h"
#include "zReportBPRes.h"
#include "PSS_ModelResIDs.h"

#include "ZBModelBPReportGenerator.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBLogicalPrestationsEntity;

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

    _ZBProcessDatas( CString                    ProcessName        = _T( "" ),
                     ZBBPAnnualNumberProperties    Workload        = 0,
                     ZBBPAnnualNumberProperties    Cost            = 0,
                     ZBBPAnnualNumberProperties    CostHMO            = 0,
                     float                        Percentage        = 0.0f );

    ~_ZBProcessDatas();

    void SetName( CString Name );
    CString GetName();

    void SetWorkload( ZBBPAnnualNumberProperties Workload );
    ZBBPAnnualNumberProperties GetWorkload();

    void SetCost( ZBBPAnnualNumberProperties Cost );
    ZBBPAnnualNumberProperties GetCost();

    void SetCostHMO( ZBBPAnnualNumberProperties CostHMO );
    ZBBPAnnualNumberProperties GetCostHMO();

    void SetPercentage( double Percentage );
    double GetPercentage();

private:

    CString                        m_ProcessName;
    ZBBPAnnualNumberProperties    m_Workload;
    ZBBPAnnualNumberProperties    m_Cost;
    ZBBPAnnualNumberProperties    m_CostHMO;
    double                        m_ProprietaryPrestPercentage;
};

// Classe conteneur de données relatives aux prestations.
class AFX_EXT_CLASS _ZBPrestationsDatas : public CObject
{
public:

    _ZBPrestationsDatas( CString PrestationName = _T( "" ) );
    ~_ZBPrestationsDatas();

    void SetName( CString Name );
    CString GetName();

    void GenerateHierarchy( ZBLogicalPrestationsEntity* pPrestations, int Level = 0 );
    void Associate( ZBBPProcessSymbol* Process );
    void UpdateTotals();

    void DisplayDatas( ZBOStreamGrid    &ostream,
                       CStringArray&    ProcessNameArray,
                       CGXStyle            DisplayStyle,
                       CGXStyle            AmountStyle,
                       CGXStyle            NumericStyle,
                       int                Index,
                       bool                IncludeMonthDetails );

    ZBBPAnnualNumberProperties GetTotalWorkload();
    ZBBPAnnualNumberProperties GetTotalCost();
    ZBBPAnnualNumberProperties GetTotalCostHMO();

    CObList* GetProcessList();

private:

    void InternalUpdateTotals();

private:

    CString                        m_PrestationName;
    CString                        m_Space;

    ZBBPAnnualNumberProperties    m_TotalWorkload;
    ZBBPAnnualNumberProperties    m_TotalCost;
    ZBBPAnnualNumberProperties    m_TotalCostHMO;

    CObList                        m_ProcessList;
    CObList                        m_ChildPrestationsList;
};

// ******************************************************************************************************
// *                                Classe ZBPrestationsReportGenerator                                    *
// ******************************************************************************************************

class AFX_EXT_CLASS ZBPrestationsReportGenerator : public ZBModelBPReportGenerator
{
    DECLARE_SERIAL( ZBPrestationsReportGenerator )

public:

    ZBPrestationsReportGenerator( ZDGridDocument*            pDoc                = NULL,
                                  ZDProcessGraphModelMdlBP*    pModel                = NULL,
                                  ZDProcessGraphModelDoc*    pSourceDoc            = NULL,
                                  bool                        IncludeMonthDetails    = true );

    virtual ~ZBPrestationsReportGenerator();

    /////////////////////////////////////////////////////////////////////////////
    // ZIGridReportGenerator methods
    
    // Called by the framework to request a grid to be filled
    // The implementation uses the delegation
    virtual bool FillGrid( CGXGridCore& GridCore, size_t Index );

    virtual const CString GetReportTitle() const;

protected:

    virtual void FillTabArray();

private:

    bool FillGridPrestationsReport( CGXGridCore& GridCore, int Index );
    void FillGridPrestationsHeaders( ZBOStreamGrid &ostream, ZVGridView* pView, int Index );
    void FillPrestationsDatas();
    void Associate( ZDProcessGraphModelMdlBP* m_RootModel );
    void UpdateTotals();
    void RemoveObsoleteDatas();

    CPoint CheckColumn( ZBOStreamGrid &ostream, int Quantity );

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

#endif // !defined(AFX_ZBPrestationsReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_)