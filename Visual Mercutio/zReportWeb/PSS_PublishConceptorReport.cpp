/****************************************************************************
 * ==> PSS_PublishConceptorReport ------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will publish the Conceptor      *
 *               report to html files                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PublishConceptorReport.h"

// processsoft
#include "zConversion\PSS_StringTools.h"

// resources
#include "zReportWebRes.h"
#include "PSS_ModelResIDs.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_PublishConceptorReport
//---------------------------------------------------------------------------
PSS_PublishConceptorReport::PSS_PublishConceptorReport(PSS_ProcessGraphModelMdlBP* pModel,
                                                       BOOL                        showDetails,
                                                       BOOL                        showDeliverables) :
    PSS_BasicSymbolVisitor(),
    m_pRootModel(NULL),
    m_pModel(pModel),
    m_pSourceDoc(NULL),
    m_pPreviousProcess(NULL),
    m_PublishProc(IE_EP_PublishConceptorHeaders),
    m_ShowDetails(showDetails),
    m_IncludeDeliverables(showDeliverables),
    m_First(false)
{}
//---------------------------------------------------------------------------
PSS_PublishConceptorReport::~PSS_PublishConceptorReport()
{}
//---------------------------------------------------------------------------
bool PSS_PublishConceptorReport::Publish(const CString& dir)
{
    if (!m_pModel)
        return false;

    // create the window to receive the file generation feedback
    m_FileGenerateWindow.Create();

    if (!CreateFileSystem(m_pModel->GetMainUserGroup(), dir))
    {
        // hide the feedback dialog
        m_FileGenerateWindow.ShowWindow(SW_HIDE);

        return false;
    }

    // hide the feedback dialog
    m_FileGenerateWindow.ShowWindow(SW_HIDE);

    return true;
}
//---------------------------------------------------------------------------
void PSS_PublishConceptorReport::GeneratePageFile(const CString& name, const CString& description)
{
    if (!m_pModel)
        return;

    m_UnitName = name;

    // generate the page header
    WriteLine(IDS_CONCEPTOR_HTML_1);
    WriteLine(name);
    WriteLine(IDS_CONCEPTOR_HTML_2);
    WriteLine(IDS_CONCEPTOR_HTML_3);

    // generate the page body
    WriteLine(IDS_CONCEPTOR_HTML_4);
    WriteLine(IDS_CONCEPTOR_HTML_5);
    WriteLine(name);
    WriteLine(IDS_CONCEPTOR_HTML_6);
    WriteLine(IDS_CONCEPTOR_HTML_7);
    WriteLine(IDS_CONCEPTOR_HTML_8);
    WriteLine(IDS_CONCEPTOR_MTL_HTML_1);
    WriteLine(IDS_CONCEPTOR_HTML_9);
    WriteLine(IDS_CONCEPTOR_HTML_10);

    if (description != _T(" "))
        WriteLine(description);
    else
        WriteLine(IDS_CONCEPTOR_MTL_HTML_2);

    WriteLine(IDS_CONCEPTOR_HTML_11);
    WriteLine(IDS_CONCEPTOR_HTML_12);
    WriteLine(IDS_CONCEPTOR_HTML_13);
    WriteLine(IDS_CONCEPTOR_MTL_HTML_3);
    WriteLine(IDS_CONCEPTOR_HTML_14);
    WriteLine(IDS_CONCEPTOR_HTML_15);
    WriteLine(IDS_CONCEPTOR_MTL_HTML_4);
    WriteLine(IDS_CONCEPTOR_HTML_16);
    WriteLine(IDS_CONCEPTOR_MTL_HTML_5);
    WriteLine(IDS_CONCEPTOR_HTML_17);
    WriteLine(IDS_CONCEPTOR_MTL_HTML_6);
    WriteLine(IDS_CONCEPTOR_HTML_18);

    m_PublishProc = IE_EP_PublishConceptorHeaders;
    m_pRootModel  = m_pModel;
    m_pModel->AcceptVisitor(*this);

    if (m_ShowDetails)
    {
        WriteLine(IDS_CONCEPTOR_HTML_19);
        WriteLine(IDS_CONCEPTOR_HTML_20);
        WriteLine(IDS_CONCEPTOR_MTL_HTML_7);
        WriteLine(IDS_CONCEPTOR_HTML_21);

        m_PublishProc = IE_EP_PublishConceptorDetails;
        m_pRootModel  = m_pModel;
        m_pModel->AcceptVisitor(*this);
    }

    // generate the page footer
    WriteLine(IDS_CONCEPTOR_HTML_22);
}
//---------------------------------------------------------------------------
bool PSS_PublishConceptorReport::CreateFileSystem(PSS_UserGroupEntity* pGroup, const CString& dir)
{
    if (!pGroup)
        return false;

    const CString entityName        = pGroup->GetEntityName();
    const CString entityDescription = pGroup->GetEntityDescription().IsEmpty() ? _T(" ") : pGroup->GetEntityDescription();

    if (!m_HtmlFile.Create(GenerateFileName(dir, entityName)))
        return false;

    m_FileGenerateWindow.SetDestination(GenerateFileName(dir, entityName));
    m_FileGenerateWindow.UpdateWindow();

    GeneratePageFile(entityName, entityDescription);

    m_HtmlFile.CloseFile();

    if (pGroup->ContainEntity())
    {
        const int count = pGroup->GetEntityCount();

        for (int i = 0; i < count; ++i)
        {
            PSS_UserEntity* pEntity = pGroup->GetEntityAt(i);

            if (!pEntity)
                continue;

            PSS_UserGroupEntity* pUserGroup = dynamic_cast<PSS_UserGroupEntity*>(pEntity);

            if (pUserGroup)
                if (!CreateFileSystem(pUserGroup, dir))
                    return false;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishConceptorReport::CreateProcess()
{
    if (!m_pPreviousProcess)
        return true;

    m_First = true;

    // add 2 empty lines before the header
    WriteLine(IDS_CONCEPTOR_HTML_23);
    WriteLine(IDS_CONCEPTOR_HTML_24);

    // create the header
    WriteLine(IDS_CONCEPTOR_HTML_25);
    WriteLine(m_DomainName);
    WriteLine(IDS_CONCEPTOR_HTML_26);
    WriteLine(IDS_CONCEPTOR_MTL_HTML_8);
    WriteLine(IDS_CONCEPTOR_HTML_27);
    WriteLine(m_CurrentProcessName);
    WriteLine(IDS_CONCEPTOR_HTML_28);

    // add 1 empty line on the section end
    WriteLine(IDS_CONCEPTOR_HTML_29);

    PSS_ProcessGraphModelMdlBP* pProcGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pPreviousProcess->GetChildModel());
    CODNodeArray                nodes;

    if (pProcGraphModel && pProcGraphModel->GetBPStartSymbols(nodes, false) > 0)
        StartSection(nodes);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishConceptorReport::StartSection(CODNodeArray& nodes)
{
    const std::size_t nodeCount = nodes.GetSize();

    for (std::size_t i = 0; i < nodeCount; ++i)
    {
        IODNode*           pINode = nodes.GetAt(i);
        PSS_StartSymbolBP* pStart = static_cast<PSS_StartSymbolBP*>(pINode);

        if (!pStart)
            continue;

        // check if for the same unit
        if (pStart->GetUnitName() != m_UnitName)
            continue;

        // create the section
        WriteLine(IDS_CONCEPTOR_HTML_30);
        WriteLine(pStart->GetSymbolReferenceNumberStr());
        WriteLine(IDS_CONCEPTOR_HTML_31);
        WriteLine(IDS_CONCEPTOR_MTL_HTML_9);
        WriteLine(IDS_CONCEPTOR_HTML_32);
        WriteLine(pStart->GetSymbolName());
        WriteLine(IDS_CONCEPTOR_HTML_33);

        WriteLine(IDS_CONCEPTOR_HTML_34);
        WriteLine(IDS_CONCEPTOR_MTL_HTML_10);
        WriteLine(IDS_CONCEPTOR_HTML_35);
        WriteLine(pStart->GetSymbolComment());
        WriteLine(IDS_CONCEPTOR_HTML_36);
        WriteLine(_T(" "));
        WriteLine(IDS_CONCEPTOR_HTML_37);

        if (m_IncludeDeliverables)
        {
            // get  all leaving down deliverables
            CODEdgeArray edges;

            if (pStart->GetEdgesLeaving(edges) > 0)
            {
                PSS_DeliverableLinkSymbolBP* pDeliverable = NULL;
                const int                    edgeCount    = edges.GetSize();

                for (int j = 0; j < edgeCount; ++j)
                {
                    IODEdge* pIEdge = edges.GetAt(j);
                    pDeliverable    = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pDeliverable)
                        continue;

                    WriteLine(IDS_CONCEPTOR_HTML_38);
                    WriteLine(pDeliverable->GetSymbolReferenceNumberStr());
                    WriteLine(IDS_CONCEPTOR_HTML_39);
                    WriteLine(pDeliverable->GetSymbolName());
                    WriteLine(IDS_CONCEPTOR_HTML_40);
                    WriteLine(_T(" "));
                    WriteLine(IDS_CONCEPTOR_HTML_41);
                }
            }
        }
    }

    // add an empty line on the section end
    WriteLine(IDS_CONCEPTOR_HTML_42);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishConceptorReport::OnDoorSymbol(PSS_DoorSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishConceptorReport::OnPageSymbol(PSS_PageSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishConceptorReport::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    bool error;

    // only for the specific unit
    const CString unitName = pSymbol->RetrieveUnitName(pSymbol->GetUnitGUID(), error);

    // check if for the same unit
    if (m_UnitName == unitName)
        switch (m_PublishProc)
        {
            case IE_EP_PublishConceptorHeaders:
                WriteLine(IDS_CONCEPTOR_HTML_43);
                WriteLine(m_DomainName);
                WriteLine(IDS_CONCEPTOR_HTML_44);
                WriteLine(m_CurrentProcessName);
                WriteLine(IDS_CONCEPTOR_HTML_45);
                WriteLine(pSymbol->GetSymbolName());
                WriteLine(IDS_CONCEPTOR_HTML_46);
                break;

            case IE_EP_PublishConceptorDetails:
                // show the process section
                if (!m_First)
                    CreateProcess();

                // show the section
                WriteLine(IDS_CONCEPTOR_HTML_47);
                WriteLine(pSymbol->GetSymbolReferenceNumberStr());
                WriteLine(IDS_CONCEPTOR_HTML_48);
                WriteLine(IDS_CONCEPTOR_MTL_HTML_11);
                WriteLine(IDS_CONCEPTOR_HTML_49);
                WriteLine(pSymbol->GetSymbolName());
                WriteLine(IDS_CONCEPTOR_HTML_50);

                WriteLine(IDS_CONCEPTOR_HTML_51);
                WriteLine(IDS_CONCEPTOR_MTL_HTML_12);
                WriteLine(IDS_CONCEPTOR_HTML_52);
                WriteLine(pSymbol->GetSymbolComment());
                WriteLine(IDS_CONCEPTOR_HTML_53);
                WriteLine(_T(" "));
                WriteLine(IDS_CONCEPTOR_HTML_54);

                if (m_IncludeDeliverables)
                {
                    WriteLine(IDS_CONCEPTOR_HTML_55);
                    WriteLine(IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_1);
                    WriteLine(IDS_CONCEPTOR_HTML_56);

                    // get all entering up deliverables
                    CODEdgeArray edges;

                    if (pSymbol->GetEnteringUpDeliverable(edges) > 0)
                    {
                        const int edgeCount = edges.GetSize();

                        for (int i = 0; i < edgeCount; ++i)
                        {
                            IODEdge*                     pIEdge = edges.GetAt(i);
                            PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                            if (!pComp)
                                continue;

                            // show the reference number and the deliverable name
                            WriteLine(IDS_CONCEPTOR_HTML_57);
                            WriteLine(pComp->GetSymbolReferenceNumberStr());
                            WriteLine(IDS_CONCEPTOR_HTML_58);
                            WriteLine(pComp->GetSymbolName());
                            WriteLine(IDS_CONCEPTOR_HTML_59);
                            WriteLine(_T(" "));
                            WriteLine(IDS_CONCEPTOR_HTML_60);
                        }
                    }

                    WriteLine(IDS_CONCEPTOR_HTML_61);
                    WriteLine(IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_2);
                    WriteLine(IDS_CONCEPTOR_HTML_62);

                    // get all leaving right deliverables
                    if (pSymbol->GetEdgesLeaving_Right(edges) > 0)
                    {
                        const int edgeCount = edges.GetSize();

                        for (int i = 0; i < edgeCount; ++i)
                        {
                            IODEdge*                     pIEdge = edges.GetAt(i);
                            PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                            if (!pComp)
                                continue;

                            // Display the reference number and the deliverable name
                            WriteLine(IDS_CONCEPTOR_HTML_63);
                            WriteLine(pComp->GetSymbolReferenceNumberStr());
                            WriteLine(IDS_CONCEPTOR_HTML_64);
                            WriteLine(pComp->GetSymbolName());
                            WriteLine(IDS_CONCEPTOR_HTML_65);
                            WriteLine(_T(" "));
                            WriteLine(IDS_CONCEPTOR_HTML_66);
                        }
                    }

                    // get all leaving left deliverables
                    if (pSymbol->GetEdgesLeaving_Left(edges) > 0)
                    {
                        const int edgeCount = edges.GetSize();

                        for (int i = 0; i < edgeCount; ++i)
                        {
                            IODEdge*                     pIEdge = edges.GetAt(i);
                            PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                            if (!pComp)
                                continue;

                            // show the reference number and the deliverable name
                            WriteLine(IDS_CONCEPTOR_HTML_67);
                            WriteLine(pComp->GetSymbolReferenceNumberStr());
                            WriteLine(IDS_CONCEPTOR_HTML_68);
                            WriteLine(pComp->GetSymbolName());
                            WriteLine(IDS_CONCEPTOR_HTML_69);
                            WriteLine(_T(" "));
                            WriteLine(IDS_CONCEPTOR_HTML_70);
                        }
                    }

                    WriteLine(IDS_CONCEPTOR_HTML_71);
                    WriteLine(IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_3);
                    WriteLine(IDS_CONCEPTOR_HTML_72);

                    // get all entering right deliverables
                    if (pSymbol->GetEdgesEntering_Right(edges) > 0)
                    {
                        const int edgeCount = edges.GetSize();

                        for (int i = 0; i < edges.GetSize(); ++i)
                        {
                            IODEdge*                     pIEdge = edges.GetAt(i);
                            PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                            if (!pComp)
                                continue;

                            // show the reference number and the deliverable name
                            WriteLine(IDS_CONCEPTOR_HTML_73);
                            WriteLine(pComp->GetSymbolReferenceNumberStr());
                            WriteLine(IDS_CONCEPTOR_HTML_74);
                            WriteLine(pComp->GetSymbolName());
                            WriteLine(IDS_CONCEPTOR_HTML_75);
                            WriteLine(_T(" "));
                            WriteLine(IDS_CONCEPTOR_HTML_76);
                        }
                    }

                    // Retrieve all entering left deliverables
                    if (pSymbol->GetEdgesEntering_Left(edges) > 0)
                    {
                        const int edgeCount = edges.GetSize();

                        for (int i = 0; i < edgeCount; ++i)
                        {
                            IODEdge*                     pIEdge = edges.GetAt(i);
                            PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                            if (!pComp)
                                continue;

                            // show the reference number and the deliverable name
                            WriteLine(IDS_CONCEPTOR_HTML_77);
                            WriteLine(pComp->GetSymbolReferenceNumberStr());
                            WriteLine(IDS_CONCEPTOR_HTML_78);
                            WriteLine(pComp->GetSymbolName());
                            WriteLine(IDS_CONCEPTOR_HTML_79);
                            WriteLine(_T(" "));
                            WriteLine(IDS_CONCEPTOR_HTML_80);
                        }
                    }
                }

                // rules, decisions, tasks, etc.
                WriteLine(IDS_CONCEPTOR_HTML_81);
                WriteLine(IDS_CONCEPTOR_MTL_HTML_16);
                WriteLine(IDS_CONCEPTOR_HTML_82);

                CString str;

                // build the next lines with the  rules themselves, at least one empty line
                int count = max(pSymbol->GetRuleCount(), 1);

                for (int i = 0; i < count; ++i)
                {
                    str.Format(IDS_CONCEPTOR_MTL_HTML_17, i + 1);

                    WriteLine(IDS_CONCEPTOR_HTML_83);
                    WriteLine(str);
                    WriteLine(IDS_CONCEPTOR_HTML_84);
                    WriteLine(pSymbol->GetRuleAt(i));
                    WriteLine(IDS_CONCEPTOR_HTML_85);
                    WriteLine(_T(" "));
                    WriteLine(IDS_CONCEPTOR_HTML_86);
                }

                WriteLine(IDS_CONCEPTOR_HTML_87);
                WriteLine(IDS_CONCEPTOR_MTL_HTML_18);
                WriteLine(IDS_CONCEPTOR_HTML_88);

                // build the next lines with the  tasks themselves, at least one empty line
                count = max(pSymbol->GetTaskCount(), 1);

                for (int i = 0; i < count; ++i)
                {
                    str.Format(IDS_CONCEPTOR_MTL_HTML_19, i + 1);

                    WriteLine(IDS_CONCEPTOR_HTML_89);
                    WriteLine(str);
                    WriteLine(IDS_CONCEPTOR_HTML_90);
                    WriteLine(pSymbol->GetTaskAt(i));
                    WriteLine(IDS_CONCEPTOR_HTML_91);
                    WriteLine(_T(" "));
                    WriteLine(IDS_CONCEPTOR_HTML_92);
                }

                WriteLine(IDS_CONCEPTOR_HTML_93);
                WriteLine(IDS_CONCEPTOR_MTL_HTML_20);
                WriteLine(IDS_CONCEPTOR_HTML_94);

                // build the next lines with the decisions themselves, at least one empty line
                count = max(pSymbol->GetDecisionCount(), 1);

                for (int i = 0; i < count; ++i)
                {
                    str.Format(IDS_CONCEPTOR_MTL_HTML_21, i + 1);

                    WriteLine(IDS_CONCEPTOR_HTML_95);
                    WriteLine(str);
                    WriteLine(IDS_CONCEPTOR_HTML_96);
                    WriteLine(pSymbol->GetDecisionAt(i));
                    WriteLine(IDS_CONCEPTOR_HTML_97);
                    WriteLine(_T(" "));
                    WriteLine(IDS_CONCEPTOR_HTML_98);
                }

                if (m_IncludeDeliverables)
                {
                    WriteLine(IDS_CONCEPTOR_HTML_99);
                    WriteLine(IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_4);
                    WriteLine(IDS_CONCEPTOR_HTML_100);

                    CODEdgeArray edges;

                    // get all leaving down deliverables
                    if (pSymbol->GetEdgesLeaving_Down(edges) > 0)
                    {
                        const int edgeCount = edges.GetSize();

                        for (int i = 0; i < edgeCount; ++i)
                        {
                            IODEdge*                     pIEdge = edges.GetAt(i);
                            PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                            if (!pComp)
                                continue;

                            // show the reference number and the deliverable name
                            WriteLine(IDS_CONCEPTOR_HTML_101);
                            WriteLine(pComp->GetSymbolReferenceNumberStr());
                            WriteLine(IDS_CONCEPTOR_HTML_102);
                            WriteLine(pComp->GetSymbolName());
                            WriteLine(IDS_CONCEPTOR_HTML_103);
                            WriteLine(_T(" "));
                            WriteLine(IDS_CONCEPTOR_HTML_104);
                        }
                    }
                }

                break;
        }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishConceptorReport::OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol)
{
    switch (m_PublishProc)
    {
        case IE_EP_PublishConceptorHeaders:
        {
            m_CurrentProcessName = pSymbol->GetSymbolName();

            PSS_ProcessGraphModelMdl* pOwnerModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetOwnerModel());

            if (pOwnerModel)
            {
                PSS_ProcessGraphPage* pPage = m_pRootModel->FindModelPage(pOwnerModel, true);

                if (pPage)
                    m_DomainName = pPage->GetPageName();
                else
                    m_DomainName.LoadString(IDS_REPORTWEB_NOTFOUND);
            }

            break;
        }

        case IE_EP_PublishConceptorDetails:
        {
            m_pPreviousProcess   = pSymbol;
            m_CurrentProcessName = pSymbol->GetSymbolName();

            PSS_ProcessGraphModelMdl* pOwnerModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetOwnerModel());

            if (pOwnerModel)
            {
                PSS_ProcessGraphPage* pPage = m_pRootModel->FindModelPage(pOwnerModel, true);

                if (pPage)
                    m_DomainName = pPage->GetPageName();
                else
                    m_DomainName.LoadString(IDS_REPORTWEB_NOTFOUND);
            }

            m_First = false;
            break;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishConceptorReport::OnStartSymbol(PSS_StartSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishConceptorReport::OnStopSymbol(PSS_StopSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishConceptorReport::OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishConceptorReport::OnSymbol(PSS_Symbol* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishConceptorReport::OnLink(PSS_LinkSymbol* pLink)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishConceptorReport::Visit(CODComponent& component)
{
    CODComponent*          pComponent = &component;
    PSS_ProcedureSymbolBP* pProcedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pComponent);

    if (pProcedure)
        return OnProcedureSymbol(pProcedure);

    PSS_DeliverableLinkSymbolBP* pDeliverable = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pComponent);

    if (pDeliverable)
        return OnDeliverableLinkSymbol(pDeliverable);

    PSS_DoorSymbolBP* pDoor = dynamic_cast<PSS_DoorSymbolBP*>(pComponent);

    if (pDoor)
        return OnDoorSymbol(pDoor);

    PSS_PageSymbolBP* pPage = dynamic_cast<PSS_PageSymbolBP*>(pComponent);

    if (pPage)
        return OnPageSymbol(pPage);

    PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pComponent);

    if (pProcess)
        return OnProcessSymbol(pProcess);

    PSS_StartSymbolBP* pStart = dynamic_cast<PSS_StartSymbolBP*>(pComponent);

    if (pStart)
        return OnStartSymbol(pStart);

    PSS_StopSymbolBP* pStop = dynamic_cast<PSS_StopSymbolBP*>(pComponent);

    if (pStop)
        return OnStopSymbol(pStop);

    PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pComponent);

    if (pSymbol)
        return OnSymbol(pSymbol);

    PSS_LinkSymbol* pLink = dynamic_cast<PSS_LinkSymbol*>(pComponent);

    if (pLink)
        return OnLink(pLink);

    // not a known symbol or not required to be visited
    return false;
}
//---------------------------------------------------------------------------
CString PSS_PublishConceptorReport::GenerateFileName(const CString& dir, const CString& entityName)
{
    CString fileName  = dir;
    fileName         += _T("Conceptor_");
    fileName         += PSS_StringTools::ConvertSpecialChar(entityName);
    fileName         += _T(".htm");

    return fileName;
}
//---------------------------------------------------------------------------
void PSS_PublishConceptorReport::WriteLine(const CString& text)
{
    if (!text.IsEmpty())
        m_HtmlFile << text;
}
//---------------------------------------------------------------------------
void PSS_PublishConceptorReport::WriteLine(int id)
{
    CString output;
    output.LoadString(id);

    if (!output.IsEmpty())
        m_HtmlFile << output;
}
//---------------------------------------------------------------------------
