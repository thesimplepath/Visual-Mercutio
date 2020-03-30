/****************************************************************************
 * ==> PSS_PrestationsReportGenerator --------------------------------------*
 ****************************************************************************
 * Description : Provides a prestations report generator                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PrestationsReportGenerator.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const std::size_t g_MaxDeliveryListSize = 20;
//---------------------------------------------------------------------------
// PSS_PrestationsReportGenerator::IProcessData
//---------------------------------------------------------------------------
PSS_PrestationsReportGenerator::IProcessData::IProcessData(const CString&                      processName,
                                                           const PSS_AnnualNumberPropertiesBP& workload,
                                                           const PSS_AnnualNumberPropertiesBP& cost,
                                                           const PSS_AnnualNumberPropertiesBP& costHMO,
                                                           float                               percentage) :
    CObject(),
    m_Workload(workload),
    m_Cost(cost),
    m_CostHMO(costHMO),
    m_ProcessName(processName),
    m_ProprietaryPrestPercentage(percentage)
{}
//---------------------------------------------------------------------------
PSS_PrestationsReportGenerator::IProcessData::~IProcessData()
{
    m_ProcessName.Empty();
}
//---------------------------------------------------------------------------
CString PSS_PrestationsReportGenerator::IProcessData::GetName()
{
    return m_ProcessName;
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::IProcessData::SetName(const CString& name)
{
    m_ProcessName = name;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_PrestationsReportGenerator::IProcessData::GetWorkload()
{
    return m_Workload;
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::IProcessData::SetWorkload(const PSS_AnnualNumberPropertiesBP& workload)
{
    m_Workload = workload;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_PrestationsReportGenerator::IProcessData::GetCost()
{
    return m_Cost;
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::IProcessData::SetCost(const PSS_AnnualNumberPropertiesBP& cost)
{
    m_Cost = cost;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_PrestationsReportGenerator::IProcessData::GetCostHMO()
{
    return m_CostHMO;
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::IProcessData::SetCostHMO(const PSS_AnnualNumberPropertiesBP& costHMO)
{
    m_CostHMO = costHMO;
}
//---------------------------------------------------------------------------
double PSS_PrestationsReportGenerator::IProcessData::GetPercentage()
{
    return m_ProprietaryPrestPercentage;
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::IProcessData::SetPercentage(double Percentage)
{
    m_ProprietaryPrestPercentage = Percentage;
}
//---------------------------------------------------------------------------
// PSS_PrestationsReportGenerator::IPrestationsData
//---------------------------------------------------------------------------
PSS_PrestationsReportGenerator::IPrestationsData::IPrestationsData(const CString& prestationName) :
    CObject(),
    m_PrestationName(prestationName),
    m_TotalWorkload(0),
    m_TotalCost(0),
    m_TotalCostHMO(0)
{}
//---------------------------------------------------------------------------
PSS_PrestationsReportGenerator::IPrestationsData::~IPrestationsData()
{
    m_PrestationName.Empty();
    m_Space.Empty();

    POSITION pPos = m_ProcessList.GetHeadPosition();

    while (pPos)
    {
        IProcessData* pData = dynamic_cast<IProcessData*>(m_ProcessList.GetNext(pPos));

        if (pData)
            delete pData;
    }

    m_ProcessList.RemoveAll();

    pPos = m_ChildPrestationsList.GetHeadPosition();

    while (pPos)
    {
        IPrestationsData* pData = dynamic_cast<IPrestationsData*>(m_ChildPrestationsList.GetNext(pPos));

        if (pData)
            delete pData;
    }

    m_ChildPrestationsList.RemoveAll();
}
//---------------------------------------------------------------------------
CString PSS_PrestationsReportGenerator::IPrestationsData::GetName()
{
    return m_PrestationName;
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::IPrestationsData::SetName(const CString& name)
{
    m_PrestationName = name;
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::IPrestationsData::GenerateHierarchy(PSS_LogicalPrestationsEntity* pPrestations, int level)
{
    if (!pPrestations)
        return;

    m_Space = _T("");

    // to respect the hierarchy, the most the level is low, the most the text is shifted on the right, so:
    // Level1
    // ¦-Level2
    // |   '-Level3
    // '-Level2
    //     '-Level3
    //         '-Etc...
    for (int i = level; i > 0; --i)
        // add the space matching with the hierarchy level
        m_Space += _T("    ");

    // set the prestation name
    m_PrestationName = pPrestations->GetEntityName();

    // check if the prestation contains children
    if (pPrestations->ContainEntity())
    {
        const int count = pPrestations->GetEntityCount();

        for (int i = 0; i < count; ++i)
        {
            PSS_LogicalPrestationsEntity* pEntity = dynamic_cast<PSS_LogicalPrestationsEntity*>(pPrestations->GetEntityAt(i));

            if (!pEntity)
                continue;

            // create a new prestations container
            std::unique_ptr<IPrestationsData> pChildPrestation(new IPrestationsData());

            // call the function recursively from the new container, to process the next level
            pChildPrestation->GenerateHierarchy(pEntity, level + 1);

            // add the child prestation in the prestations list
            m_ChildPrestationsList.AddTail(pChildPrestation.get());
            pChildPrestation.release();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::IPrestationsData::Associate(PSS_ProcessSymbolBP* pProcess)
{
    POSITION pPos = m_ChildPrestationsList.GetHeadPosition();

    // process the recursion for each prestation level
    while (pPos)
    {
        IPrestationsData* pData = dynamic_cast<IPrestationsData*>(m_ChildPrestationsList.GetNext(pPos));

        if (pData)
            pData->Associate(pProcess);
    }

    // get the prestation list from the process to associate
    PSS_Tokenizer prestationsList = pProcess->GetPrestationsList();

    // check if the current prestation belongs to this process
    for (std::size_t i = 0; i < prestationsList.GetTokenCount(); ++i)
    {
        CString prestationInProcessName;
        prestationsList.GetTokenAt(i, prestationInProcessName);

        // if the current prestation already belongs to this process, associate the data required for the calculation
        if (m_PrestationName == prestationInProcessName)
        {
            std::unique_ptr<IProcessData> pData(new IProcessData());

            PSS_Properties::IPropertySet propSet;
            pProcess->FillProperties(propSet);

            PSS_Properties::IPropertyIterator it(&propSet);
            PSS_Property* pProp;

            BOOL isGoodPrestationName = FALSE;

            // get the activity percentage value from the process to associate
            for (pProp = it.GetFirst(); pProp; pProp = it.GetNext())
            {
                // search for the matching prestation
                if (pProp->GetCategoryID() == ZS_BP_PROP_PRESTATIONS && pProp->GetItemID() == M_Prestation_Name)
                    if (pProp->GetValueString() == m_PrestationName)
                        isGoodPrestationName = TRUE;

                // get the prestation percentage value
                if (pProp->GetCategoryID() == ZS_BP_PROP_PRESTATIONS  &&
                    pProp->GetItemID()     == M_Prestation_Percentage &&
                    isGoodPrestationName)
                {
                    switch (pProp->GetValueType())
                    {
                        case PSS_Property::IE_VT_Double: pData->SetPercentage(       pProp->GetValueDouble()); break;
                        case PSS_Property::IE_VT_Float:  pData->SetPercentage(double(pProp->GetValueFloat())); break;
                    }

                    isGoodPrestationName = FALSE;
                }
            }

            // get the data to associate. The workload and cost are multiplicated by the prestation process activity rate
            pData->SetName    (pProcess->GetSymbolName());
            pData->SetWorkload(pProcess->GetProcessWorkloadForecast() * pData->GetPercentage());
            pData->SetCost    (pProcess->GetProcessCostForecast()     * pData->GetPercentage());
            pData->SetCostHMO (pProcess->GetProcessCostHMO()          * pData->GetPercentage());

            m_ProcessList.AddTail(pData.get());
            pData.release();

            // cleanup the memory used for the search
            for (pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                if (pProp)
                    delete pProp;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::IPrestationsData::UpdateTotals()
{
    m_TotalWorkload = 0;
    m_TotalCost     = 0;

    POSITION pPos = m_ChildPrestationsList.GetHeadPosition();

    // add the children total to the current one
    while (pPos)
    {
        IPrestationsData* pData = dynamic_cast<IPrestationsData*>(m_ChildPrestationsList.GetNext(pPos));

        if (pData)
        {
            pData->UpdateTotals();

            m_TotalWorkload += pData->GetTotalWorkload();
            m_TotalCost     += pData->GetTotalCost();
            m_TotalCostHMO  += pData->GetTotalCostHMO();
        }
    }

    InternalUpdateTotals();
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::IPrestationsData::ShowData(PSS_OStreamGrid& ostream,
                                                                CStringArray&    processNameArray,
                                                                const CGXStyle&  style,
                                                                const CGXStyle&  amountStyle,
                                                                const CGXStyle&  numericStyle,
                                                                int              index,
                                                                bool             includeMonthDetails)
{
    int left = 0;
    int top  = 0;

    // get the current position
    ostream.GetCurSel(left, top);

    // get the document row count
    const ROWCOL rowCount = ostream.GetGridCore()->GetRowCount();

    // if not enough, add the missing lines
    if ((top + 1) > int(rowCount))
        ostream.GetGridCore()->SetRowCount(rowCount + 1);

    ostream << _T("\n");

    // set the prestation name, with its matching hierarchical level
    ostream << m_Space + m_PrestationName;
    ostream << style;

    // search for the current report index
    switch (index)
    {
        // workload page
        case 0:
        {
            // column 1 - document
            ostream << _T("\t");
            ostream << m_TotalWorkload.GetNumberYear();
            ostream << style;
            ostream << numericStyle;
            ostream << amountStyle;

            // write the month details for the 1st column
            if (includeMonthDetails)
                for (int i = 0; i < 12; ++i)
                {
                    ostream << _T("\t");
                    ostream << m_TotalWorkload.GetNumberAt(i);
                    ostream << style;
                    ostream << numericStyle;
                    ostream << amountStyle;
                }

            // columns 2 to x - per process details
            for (int i = 0; i < processNameArray.GetSize(); ++i)
            {
                IProcessData* pCurData = NULL;
                POSITION      pPos     = m_ProcessList.GetHeadPosition();

                while (pPos)
                {
                    IProcessData* pData = dynamic_cast<IProcessData*>(m_ProcessList.GetNext(pPos));

                    if (pData)
                        if (pData->GetName() == processNameArray.GetAt(i))
                            pCurData = pData;
                }

                if (pCurData && pCurData->GetName() == processNameArray.GetAt(i))
                {
                    ostream << _T("\t");
                    ostream << pCurData->GetWorkload().GetNumberYear();
                    ostream << style;
                    ostream << numericStyle;
                    ostream << amountStyle;

                    // write the month details for the columns 2 to x
                    if (includeMonthDetails)
                        for (int i = 0; i < 12; ++i)
                        {
                            ostream << _T("\t");
                            ostream << pCurData->GetWorkload().GetNumberAt(i);
                            ostream << style;
                            ostream << numericStyle;
                            ostream << amountStyle;
                        }
                }
                else
                {
                    ostream << _T("\t");
                    ostream << 0.0;
                    ostream << style;
                    ostream << numericStyle;
                    ostream << amountStyle;

                    if (includeMonthDetails)
                        for (int i = 0; i < 12; ++i)
                        {
                            ostream << _T("\t");
                            ostream << 0.0;
                            ostream << style;
                            ostream << numericStyle;
                            ostream << amountStyle;
                        }
                }
            }

            break;
        }

        // cost page
        case 1:
        {
            // column 1 - document
            ostream << _T("\t");
            ostream << m_TotalCost.GetNumberYear();
            ostream << style;
            ostream << numericStyle;
            ostream << amountStyle;

            // write the month details for the 1st column
            if (includeMonthDetails)
                for (int i = 0; i < 12; ++i)
                {
                    ostream << _T("\t");
                    ostream << m_TotalCost.GetNumberAt(i);
                    ostream << style;
                    ostream << numericStyle;
                    ostream << amountStyle;
                }

            // columns 2 to x - per process details
            for (int i = 0; i < processNameArray.GetSize(); ++i)
            {
                IProcessData* pCurData = NULL;
                POSITION      pPos     = m_ProcessList.GetHeadPosition();

                while (pPos)
                {
                    IProcessData* pData = dynamic_cast<IProcessData*>(m_ProcessList.GetNext(pPos));

                    if (pData)
                        if (pData->GetName() == processNameArray.GetAt(i))
                            pCurData = pData;
                }

                if (pCurData && pCurData->GetName() == processNameArray.GetAt(i))
                {
                    ostream << _T("\t");
                    ostream << pCurData->GetCost().GetNumberYear();
                    ostream << style;
                    ostream << numericStyle;
                    ostream << amountStyle;

                    // write the month details for the columns 2 to x
                    if (includeMonthDetails)
                        for (int i = 0; i < 12; ++i)
                        {
                            ostream << _T("\t");
                            ostream << pCurData->GetCost().GetNumberAt(i);
                            ostream << style;
                            ostream << numericStyle;
                            ostream << amountStyle;
                        }
                }
                else
                {
                    ostream << _T("\t");
                    ostream << 0.0;
                    ostream << style;
                    ostream << numericStyle;
                    ostream << amountStyle;

                    if (includeMonthDetails)
                        for (int i = 0; i < 12; ++i)
                        {
                            ostream << _T("\t");
                            ostream << 0.0;
                            ostream << style;
                            ostream << numericStyle;
                            ostream << amountStyle;
                        }
                }
            }

            break;
        }

        // HMO cost page
        case 2:
        {
            // column 1 - document
            ostream << _T("\t");
            ostream << m_TotalCostHMO.GetNumberYear();
            ostream << style;
            ostream << numericStyle;
            ostream << amountStyle;

            // write the month details for the 1st column
            if (includeMonthDetails)
                for (int i = 0; i < 12; ++i)
                {
                    ostream << _T("\t");
                    ostream << m_TotalCostHMO.GetNumberAt(i);
                    ostream << style;
                    ostream << numericStyle;
                    ostream << amountStyle;
                }

            // columns 2 to x - per process details
            for (int i = 0; i < processNameArray.GetSize(); ++i)
            {
                IProcessData* pCurData = NULL;
                POSITION      pPos     = m_ProcessList.GetHeadPosition();

                while (pPos)
                {
                    IProcessData* pData = dynamic_cast<IProcessData*>(m_ProcessList.GetNext(pPos));

                    if (pData)
                        if (pData->GetName() == processNameArray.GetAt(i))
                            pCurData = pData;
                }

                if (pCurData && pCurData->GetName() == processNameArray.GetAt(i))
                {
                    ostream << _T("\t");
                    ostream << pCurData->GetCostHMO().GetNumberYear();
                    ostream << style;
                    ostream << numericStyle;
                    ostream << amountStyle;

                    // write the month details for the columns 2 to x
                    if (includeMonthDetails)
                        for (int i = 0; i < 12; ++i)
                        {
                            ostream << _T("\t");
                            ostream << pCurData->GetCostHMO().GetNumberAt(i);
                            ostream << style;
                            ostream << numericStyle;
                            ostream << amountStyle;
                        }
                }
                else
                {
                    ostream << _T("\t");
                    ostream << 0.0;
                    ostream << style;
                    ostream << numericStyle;
                    ostream << amountStyle;

                    if (includeMonthDetails)
                        for (int i = 0; i < 12; ++i)
                        {
                            ostream << _T("\t");
                            ostream << 0.0;
                            ostream << style;
                            ostream << numericStyle;
                            ostream << amountStyle;
                        }
                }
            }

            break;
        }

        default:
            break;
    }

    POSITION pPos = m_ChildPrestationsList.GetHeadPosition();

    // iterate recursively through children
    while (pPos)
    {
        IPrestationsData* pData = dynamic_cast<IPrestationsData*>(m_ChildPrestationsList.GetNext(pPos));

        if (pData)
            pData->ShowData(ostream,
                            processNameArray,
                            style,
                            amountStyle,
                            numericStyle,
                            index,
                            includeMonthDetails);
    }
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_PrestationsReportGenerator::IPrestationsData::GetTotalWorkload()
{
    return m_TotalWorkload;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_PrestationsReportGenerator::IPrestationsData::GetTotalCost()
{
    return m_TotalCost;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_PrestationsReportGenerator::IPrestationsData::GetTotalCostHMO()
{
    return m_TotalCostHMO;
}
//---------------------------------------------------------------------------
CObList* PSS_PrestationsReportGenerator::IPrestationsData::GetProcessList()
{
    return &m_ProcessList;
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::IPrestationsData::InternalUpdateTotals()
{
    // add the current prestation value to total
    POSITION pPos = m_ProcessList.GetHeadPosition();

    while (pPos)
    {
        IProcessData* pData = dynamic_cast<IProcessData*>(m_ProcessList.GetNext(pPos));

        if (pData)
        {
            m_TotalWorkload += pData->GetWorkload();
            m_TotalCost     += pData->GetCost();
            m_TotalCostHMO  += pData->GetCostHMO();
        }
    }

    POSITION pChildPos = m_ChildPrestationsList.GetHeadPosition();

    // update the process level by adding the children values
    while (pChildPos)
    {
        IPrestationsData* pChild = dynamic_cast<IPrestationsData*>(m_ChildPrestationsList.GetNext(pChildPos));

        if (pChild)
        {
            POSITION pChildList = pChild->GetProcessList()->GetHeadPosition();

            while (pChildList)
            {
                IProcessData* pChildData = dynamic_cast<IProcessData*>(pChild->GetProcessList()->GetNext(pChildList));

                if (pChildData)
                {
                    BOOL     isInCurList = FALSE;
                    POSITION pCurList    = m_ProcessList.GetHeadPosition();

                    while (pCurList)
                    {
                        IProcessData* pCurListData = dynamic_cast<IProcessData*>(m_ProcessList.GetNext(pCurList));

                        if (pCurListData)
                            if (pCurListData->GetName() == pChildData->GetName())
                            {
                                pCurListData->SetWorkload(pCurListData->GetWorkload() + pChildData->GetWorkload());
                                pCurListData->SetCost    (pCurListData->GetCost()     + pChildData->GetCost());
                                pCurListData->SetCostHMO (pCurListData->GetCostHMO()  + pChildData->GetCostHMO());
                                isInCurList = TRUE;
                            }
                    }

                    // create a new total if not found
                    if (!isInCurList)
                    {
                        std::unique_ptr<IProcessData> pData(new IProcessData());

                        // get the process data
                        pData->SetName      (pChildData->GetName());
                        pData->SetWorkload  (pChildData->GetWorkload());
                        pData->SetCost      (pChildData->GetCost());
                        pData->SetCostHMO   (pChildData->GetCostHMO());
                        pData->SetPercentage(pChildData->GetPercentage());

                        m_ProcessList.AddTail(pData.get());
                        pData.release();
                    }
                    else
                        isInCurList = FALSE;
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PrestationsReportGenerator, PSS_ModelBPReportGenerator, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PrestationsReportGenerator
//---------------------------------------------------------------------------
PSS_PrestationsReportGenerator::PSS_PrestationsReportGenerator(PSS_GridDocument*           pDoc,
                                                               PSS_ProcessGraphModelMdlBP* pModel,
                                                               PSS_ProcessGraphModelDoc*   pSourceDoc,
                                                               bool                        includeMonthDetails) :
    PSS_ModelBPReportGenerator(pDoc, pModel, pSourceDoc),
    m_IncludeMonthDetails(includeMonthDetails)
{
    // initialize the header style
    m_HeaderStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(10)
            .SetBold(FALSE))
            .SetInterior(M_Color_GreyProcess);

    // initialize the normal style
    m_NormalStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(10)
            .SetBold(FALSE))
            .SetInterior(defCOLOR_WHITE);

    m_BlackBorderStyle.SetBorders(gxBorderAll, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_AmountFormatStyle.SetFormat(GX_FMT_COMMA).SetPlaces(0);
    m_NumericCellStyle.SetValueType(GX_VT_NUMERIC).SetPlaces(0);

    // initialize the header cells size
    m_HeaderPrestationsTitle.cx = 300;
    m_HeaderPrestationsTitle.cy = 40;
    m_HeaderStandardTitle.cx    = 150;
    m_HeaderStandardTitle.cy    = 0;
    m_HeadersDetailsTitle.cx    = 80;
    m_HeadersDetailsTitle.cy    = 0;

    // create and associate the report data
    FillPrestationsData();
}
//---------------------------------------------------------------------------
PSS_PrestationsReportGenerator::~PSS_PrestationsReportGenerator()
{
    RemoveObsoleteDatas();

    POSITION pPos = m_PrestationsArray.GetHeadPosition();

    while (pPos)
    {
        IPrestationsData* pData = dynamic_cast<IPrestationsData*>(m_PrestationsArray.GetNext(pPos));

        if (pData)
            delete pData;
    }

    m_PrestationsArray.RemoveAll();
}
//---------------------------------------------------------------------------
const CString PSS_PrestationsReportGenerator::GetReportTitle() const
{
    CString str;

    if (m_pDoc)
        str = m_pDoc->GetTitle();

    CString reportType;
    reportType.LoadString(IDS_PRESTATIONS_RPT_T);

    str += _T(" [");
    str += reportType;
    str += _T(" : ");

    if (m_pModel)
        str += m_pModel->GetModelName();
    else
        str += _T("???");

    str += _T(" ]");

    return str;
}
//---------------------------------------------------------------------------
bool PSS_PrestationsReportGenerator::FillGrid(CGXGridCore& GridCore, size_t Index)
{
    return FillGridPrestationsReport(GridCore, Index);
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::FillTabArray()
{
    // do nothing if no document defined
    if (!m_pDoc || !m_pModel)
        return;

    // remove the previous items
    RemoveObsoleteDatas();

    // get the process name list
    PSS_ExtractProcessName extractProcessName(m_pModel);
    extractProcessName.FillProcessNameArray(&m_ProcessNameArray);

    // build the forms hierarchy
    CString str;

    // workload form
    str.LoadString(IDS_WORKLOAD_TAB);
    m_TabNameArray.Add(str);

    // cost form
    str.LoadString(IDS_COST_TAB);
    m_TabNameArray.Add(str);

    // HMO cost form
    str.LoadString(IDS_COSTHMO_TAB);
    m_TabNameArray.Add(str);
}
//---------------------------------------------------------------------------
bool PSS_PrestationsReportGenerator::FillGridPrestationsReport(CGXGridCore& gridCore, int index)
{
    PSS_OStreamGrid ostream(&gridCore);

    // default size, 60 rows x 15 columns
    gridCore.SetRowCount(60);
    gridCore.SetColCount(15);

    // get the grid view
    PSS_GridView* pGridView = dynamic_cast<PSS_GridView*>(gridCore.GridWnd());

    // publish the report headers
    if (pGridView)
        FillGridPrestationsHeaders(ostream, pGridView, index);

    POSITION pPos = m_PrestationsArray.GetHeadPosition();

    // publish the report data
    while (pPos)
    {
        IPrestationsData* pData = dynamic_cast<IPrestationsData*>(m_PrestationsArray.GetNext(pPos));

        if (pData)
            pData->ShowData(ostream,
                            m_ProcessNameArray,
                            m_NormalStyle,
                            m_AmountFormatStyle,
                            m_NumericCellStyle,
                            index,
                            m_IncludeMonthDetails);
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::FillGridPrestationsHeaders(PSS_OStreamGrid& ostream, PSS_GridView* pView, int index)
{
    CString   str;
    const int count = m_ProcessNameArray.GetSize() + 1;

    ostream << _T("\n\n");

    // create the control which will show the process monthly details
    if (m_IncludeMonthDetails)
        if (pView)
        {
            ostream << _T("\t");

            for (int i = 0; i < count; ++i)
            {
                CPoint curPos = CheckColumn(ostream, 20);

                CString label;
                label.LoadString(IDS_CHKBOX_LABEL);

                CString tooltipText;
                tooltipText.LoadString(IDS_CHKBOX_TTP);

                pView->InsertGroupCtrl(curPos.x,
                                       curPos.y,
                                       (i + 1 < count) ? 12 : 13,
                                       true,
                                       true,
                                       label,
                                       tooltipText);

                // shift the next control to the right
                ostream.Right(13);
            }
        }

    ostream << _T("\t");

    if (m_IncludeMonthDetails)
        CheckColumn(ostream, (count * 13));
    else
        CheckColumn(ostream, count);

    ostream << _T("\n");

    // get the prestations column title label
    switch (index)
    {
        case 0: str.LoadString(IDS_WORKLOAD_PRESTATIONREPORT_LBLRPT2);    break;
        case 1: str.LoadString(IDS_COSTUNIT_PRESTATIONREPORT_LBLRPT2);    break;
        case 2: str.LoadString(IDS_COSTHMOUNIT_PRESTATIONREPORT_LBLRPT2); break;
    }

    // set the prestations column cell title format
    ostream << str;
    ostream << m_HeaderPrestationsTitle;
    ostream << m_HeaderStyle;
    ostream << _T("\t");

    // set the model name
    ostream << m_pModel->GetModelName();
    ostream << m_HeaderStandardTitle;
    ostream << m_HeaderStyle;

    // set the label for each month
    if (m_IncludeMonthDetails)
    {
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT1);
        ostream << str;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT2);
        ostream << str;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT3);
        ostream << str;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT4);
        ostream << str;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT5);
        ostream << str;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT6);
        ostream << str;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT7);
        ostream << str;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT8);
        ostream << str;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT9);
        ostream << str;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT10);
        ostream << str;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT11);
        ostream << str;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT12);
        ostream << str;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
    }

    const int procCount = m_ProcessNameArray.GetSize();

    // get the header for each sub-process
    for (int i = 0; i < procCount; ++i)
    {
        ostream << _T("\t");
        ostream << m_ProcessNameArray.GetAt(i);
        ostream << m_HeaderStandardTitle;
        ostream << m_HeaderStyle;

        // set the label for each month
        if (m_IncludeMonthDetails)
        {
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT1);
            ostream << str;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT2);
            ostream << str;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT3);
            ostream << str;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT4);
            ostream << str;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT5);
            ostream << str;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT6);
            ostream << str;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT7);
            ostream << str;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT8);
            ostream << str;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT9);
            ostream << str;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT10);
            ostream << str;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT11);
            ostream << str;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT12);
            ostream << str;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
        }
    }

    // freeze the static columns
    PSS_GridDocument* pDoc = pView->GetDocument();

    if (pDoc)
    {
        pDoc->SetFrozenRow(4);
        pDoc->SetFrozenCol(1);
        pDoc->SetFrozenHeaderRow(4);
        pDoc->SetFrozenHeaderCol(1);

        pView->FreezeSplitter();
    }
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::FillPrestationsData()
{
    std::unique_ptr<IPrestationsData> pPrestationData(new IPrestationsData());

    pPrestationData->GenerateHierarchy(m_pModel->GetMainLogicalPrestations(), 0);

    m_PrestationsArray.AddTail(pPrestationData.get());
    pPrestationData.release();

    Associate(m_pModel);
    UpdateTotals();
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::Associate(PSS_ProcessGraphModelMdlBP* pRootModel)
{
    if (!pRootModel)
        return;

    // get the page set contained in the model controller
    PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = pRootModel->GetPageSet();

    if (!pSet)
        return;

    PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(pSet);

    // iterate through the children pages contained in the model controller
    for (PSS_ProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
    {
        // get the current page
        PSS_ProcessGraphModelMdlBP* pCurModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

        if (!pCurModel)
            continue;

        // get the symbol set contained in the page
        CODComponentSet* pCompSet = pCurModel->GetComponents();

        if (!pCompSet)
            continue;

        // iterate through the symbols
        for (int i = 0; i < pCompSet->GetSize(); ++i)
        {
            PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pCompSet->GetAt(i));

            if (!pProcess)
                continue;

            // get the process model controller
            PSS_ProcessGraphModelMdlBP* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pProcess->GetModel());

            // call the Associate() function recursively until all the model processes were visited
            Associate(pChildModel);

            POSITION pPos = m_PrestationsArray.GetHeadPosition();

            // associate the process values
            while (pPos)
            {
                IPrestationsData* pData = dynamic_cast<IPrestationsData*>(m_PrestationsArray.GetNext(pPos));

                if (pData)
                    pData->Associate(pProcess);
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::UpdateTotals()
{
    POSITION pPos = m_PrestationsArray.GetHeadPosition();

    while (pPos)
    {
        IPrestationsData* pData = dynamic_cast<IPrestationsData*>(m_PrestationsArray.GetNext(pPos));

        if (pData)
            pData->UpdateTotals();
    }
}
//---------------------------------------------------------------------------
void PSS_PrestationsReportGenerator::RemoveObsoleteDatas()
{
    m_ProcessNameArray.RemoveAll();
    m_TabNameArray.RemoveAll();
}
//---------------------------------------------------------------------------
CPoint PSS_PrestationsReportGenerator::CheckColumn(PSS_OStreamGrid& ostream, int quantity)
{
    int left = 0;
    int top  = 0;

    // get the current position
    ostream.GetCurSel(left, top);

    // get the document columns count
    ROWCOL colCount = ostream.GetGridCore()->GetColCount();

    // if not enough, add the missing columns
    if ((left + quantity) > int(colCount))
        ostream.GetGridCore()->SetColCount(colCount + quantity);

    return CPoint(top, left);
}
//---------------------------------------------------------------------------
