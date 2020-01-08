// ******************************************************************************************************
// *                                  Classe ZVPublishConceptorReport                                    *
// ******************************************************************************************************
// * JMR-MODIF - Le 29 juin 2005 - Création de la nouvelle classe ZVPublishConceptorReport.                *
// * Cette classe effectue la publication des rapports en tant que pages Internet.                        *
// ******************************************************************************************************

#include "stdafx.h"
#include "ZVPublishConceptorReport.h"

#include "zConversion\PSS_StringTools.h"

#include "zReportWebRes.h"
#include "PSS_ModelResIDs.h"

// JMR-MODIF - Le 28 février 2006 - Ressources de génération HTML déplacées dans zReportWeb.rc et zRMdlBPxx.rc.

// ******************************************************************************************************
// *                                   Construction et destruction                                        *
// ******************************************************************************************************

// Constructeur de la classe ZVPublishConceptorReport.
ZVPublishConceptorReport::ZVPublishConceptorReport(ZDProcessGraphModelMdlBP* pModel    /*= NULL*/,
                                                   BOOL bShowDetails                    /*= TRUE*/,
                                                   BOOL bShowDeliverables                /*= TRUE*/)
{
    m_pModel = pModel;

    m_pRootModel = NULL;
    m_pPreviousProcess = NULL;

    m_ShowDetails = bShowDetails;
    m_IncludeDeliverables = bShowDeliverables;

    m_First = false;

    m_DomainName = _T("");
    m_UnitName = _T("");
    m_CurrentProcessName = _T("");
}

// Destructeur de la classe ZVPublishConceptorReport.
ZVPublishConceptorReport::~ZVPublishConceptorReport()
{}

// ******************************************************************************************************
// *                       Fonctions publiques de la classe ZVPublishConceptorReport                    *
// ******************************************************************************************************

// Cette fonction permet de publier le rapport dans le répertoire fourni en entrée.
bool ZVPublishConceptorReport::Publish(CString Directory)
{
    // if no doc nor model defined. nothing to do.
    if (!m_pModel)
    {
        return false;
    }

    // Create the window for file generation feedback
    m_FileGenerateWindow.Create();

    if (!CreateFileSystem(m_pModel->GetMainUserGroup(), Directory))
    {
        // Hide the feedback dialog
        m_FileGenerateWindow.ShowWindow(SW_HIDE);

        return false;
    }

    // Hide the feedback dialog
    m_FileGenerateWindow.ShowWindow(SW_HIDE);

    return true;
}

// ******************************************************************************************************
// *                        Fonctions privées de la classe ZVPublishConceptorReport                        *
// ******************************************************************************************************

// Cette fonction permet de créer le système de fichiers.
bool ZVPublishConceptorReport::CreateFileSystem(PSS_UserGroupEntity* pGroup, CString Directory)
{
    CString sEntityName = pGroup->GetEntityName();
    CString sEntityDescription = pGroup->GetEntityDescription().IsEmpty() ? _T(" ") : pGroup->GetEntityDescription();

    if (!HtmlFile.Create(GenerateFileName(Directory, sEntityName)))
    {
        return false;
    }

    m_FileGenerateWindow.SetDestination(GenerateFileName(Directory, sEntityName));
    m_FileGenerateWindow.UpdateWindow();

    GeneratePageFile(sEntityName, sEntityDescription);

    HtmlFile.CloseFile();

    if (pGroup->ContainEntity())
    {
        int Count = pGroup->GetEntityCount();

        for (int i = 0; i < Count; ++i)
        {
            PSS_UserEntity* pEntity = pGroup->GetEntityAt(i);

            if (!pEntity)
            {
                continue;
            }

            if (ISA(pEntity, PSS_UserGroupEntity))
            {
                if (!CreateFileSystem(dynamic_cast<PSS_UserGroupEntity*>(pEntity), Directory))
                {
                    return false;
                }
            }
        }
    }

    return true;
}

// Cette fonction permet de créer le nom de fichier correct pour chaque page du rapport.
CString ZVPublishConceptorReport::GenerateFileName(CString Directory, CString EntityName)
{
    CString sFileName = Directory;
    sFileName += _T("Conceptor_");
    sFileName += PSS_StringTools::ConvertSpecialChar(EntityName);
    sFileName += _T(".htm");

    return sFileName;
}

// Cette fonction permet de remplir les données du fichier contenant la page du rapport.
void ZVPublishConceptorReport::GeneratePageFile(CString Name, CString Description)
{
    if (!m_pModel)
    {
        return;
    }

    m_UnitName = Name;

    // Génération de l'en-tête de page.
    WriteLine(IDS_CONCEPTOR_HTML_1);
    WriteLine(Name);
    WriteLine(IDS_CONCEPTOR_HTML_2);
    WriteLine(IDS_CONCEPTOR_HTML_3);

    // Génération du corps de la page.
    WriteLine(IDS_CONCEPTOR_HTML_4);
    WriteLine(IDS_CONCEPTOR_HTML_5);
    WriteLine(Name);
    WriteLine(IDS_CONCEPTOR_HTML_6);
    WriteLine(IDS_CONCEPTOR_HTML_7);
    WriteLine(IDS_CONCEPTOR_HTML_8);
    WriteLine(IDS_CONCEPTOR_MTL_HTML_1);
    WriteLine(IDS_CONCEPTOR_HTML_9);
    WriteLine(IDS_CONCEPTOR_HTML_10);

    if (Description != _T(" "))
    {
        WriteLine(Description);
    }
    else
    {
        WriteLine(IDS_CONCEPTOR_MTL_HTML_2);
    }

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

    PublishProc = PUBLISH_CONCEPTOR_HEADERS;
    m_pRootModel = m_pModel;
    m_pModel->AcceptVisitor(*this);

    if (m_ShowDetails)
    {
        WriteLine(IDS_CONCEPTOR_HTML_19);
        WriteLine(IDS_CONCEPTOR_HTML_20);
        WriteLine(IDS_CONCEPTOR_MTL_HTML_7);
        WriteLine(IDS_CONCEPTOR_HTML_21);

        PublishProc = PUBLISH_CONCEPTOR_DETAILS;
        m_pRootModel = m_pModel;
        m_pModel->AcceptVisitor(*this);
    }

    // Génération de la fin de la page.
    WriteLine(IDS_CONCEPTOR_HTML_22);
}

// Cette fonction permet d'ajouter la section de processus.
bool ZVPublishConceptorReport::CreateProcess()
{
    if (m_pPreviousProcess == NULL)
    {
        return true;
    }

    m_First = true;

    // Deux lignes vides avant l'en-tête.
    WriteLine(IDS_CONCEPTOR_HTML_23);
    WriteLine(IDS_CONCEPTOR_HTML_24);

    // Create the header
    WriteLine(IDS_CONCEPTOR_HTML_25);
    WriteLine(m_DomainName);
    WriteLine(IDS_CONCEPTOR_HTML_26);
    WriteLine(IDS_CONCEPTOR_MTL_HTML_8);
    WriteLine(IDS_CONCEPTOR_HTML_27);
    WriteLine(m_CurrentProcessName);
    WriteLine(IDS_CONCEPTOR_HTML_28);

    // Une ligne vide à la fin de la section.
    WriteLine(IDS_CONCEPTOR_HTML_29);

    CODNodeArray Nodes;

    if (reinterpret_cast<ZDProcessGraphModelMdlBP*>(((PSS_Symbol*)m_pPreviousProcess)->GetChildModel())->GetBPStartSymbols(Nodes, false) > 0)
    {
        StartSection(Nodes);
    }

    return true;
}

// Cette fonction génère la sous-section du processus.
bool ZVPublishConceptorReport::StartSection(CODNodeArray& Nodes)
{
    for (size_t nNodeIdx = 0; nNodeIdx < (size_t)Nodes.GetSize(); ++nNodeIdx)
    {
        IODNode* pINode = Nodes.GetAt(nNodeIdx);
        ZBBPStartSymbol* pStart = static_cast<ZBBPStartSymbol*>(pINode);

        if (!pStart)
        {
            continue;
        }

        // Check if for the same unit
        if (pStart->GetUnitName() != m_UnitName)
        {
            continue;
        }

        // Create the section
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
            // Retrieve all leaving down deliverables
            CODEdgeArray Edges;

            if (pStart->GetEdgesLeaving(Edges) > 0)
            {
                ZBDeliverableLinkSymbol* pDeliverable = NULL;

                for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
                {
                    IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
                    pDeliverable = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

                    // Check if null and continue if the case
                    if (!pDeliverable)
                    {
                        continue;
                    }
                }

                if (pDeliverable)
                {
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

    // Une ligne vide à la fin de la section.
    WriteLine(IDS_CONCEPTOR_HTML_42);

    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPDoorSymbol.
bool ZVPublishConceptorReport::OnDoorSymbol(ZBBPDoorSymbol* pSymbol)
{
    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPPageSymbol.
bool ZVPublishConceptorReport::OnPageSymbol(ZBBPPageSymbol* pSymbol)
{
    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPProcedureSymbol.
bool ZVPublishConceptorReport::OnProcedureSymbol(ZBBPProcedureSymbol* pSymbol)
{
    // Only for the specific unit
    // Check if for the same unit
    bool Error;

    CString UnitName = pSymbol->RetrieveUnitName(pSymbol->GetUnitGUID(), Error);

    if (m_UnitName == UnitName)
    {
        switch (PublishProc)
        {
            case PUBLISH_CONCEPTOR_HEADERS:
            {
                WriteLine(IDS_CONCEPTOR_HTML_43);
                WriteLine(m_DomainName);
                WriteLine(IDS_CONCEPTOR_HTML_44);
                WriteLine(m_CurrentProcessName);
                WriteLine(IDS_CONCEPTOR_HTML_45);
                WriteLine(pSymbol->GetSymbolName());
                WriteLine(IDS_CONCEPTOR_HTML_46);

                break;
            }

            case PUBLISH_CONCEPTOR_DETAILS:
            {
                // If not yet displayed, display the process section
                if (m_First == false)
                {
                    CreateProcess();
                }

                // Display the section
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

                    // Retrieve all entering up deliverables
                    CODEdgeArray Edges;

                    if (pSymbol->GetEnteringUpDeliverable(Edges) > 0)
                    {
                        for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
                        {
                            IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
                            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

                            // Check if null and continue if the case
                            if (!pComp)
                            {
                                continue;
                            }

                            // Display the reference number and the deliverable name
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

                    // Retrieve all leaving right deliverables
                    if (pSymbol->GetEdgesLeaving_Right(Edges) > 0)
                    {
                        for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
                        {
                            IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
                            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

                            // Check if null and continue if the case
                            if (!pComp)
                            {
                                continue;
                            }

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

                    // Retrieve all leaving left deliverables
                    if (pSymbol->GetEdgesLeaving_Left(Edges) > 0)
                    {
                        for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
                        {
                            IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
                            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

                            // Check if null and continue if the case
                            if (!pComp)
                            {
                                continue;
                            }

                            // Display the reference number and the deliverable name
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

                    // Retrieve all entering right deliverables
                    if (pSymbol->GetEdgesEntering_Right(Edges) > 0)
                    {
                        for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
                        {
                            IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
                            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

                            // Check if null and continue if the case
                            if (!pComp)
                            {
                                continue;
                            }

                            // Display the reference number and the deliverable name
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
                    if (pSymbol->GetEdgesEntering_Left(Edges) > 0)
                    {
                        for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
                        {
                            IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
                            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

                            // Check if null and continue if the case
                            if (!pComp)
                            {
                                continue;
                            }

                            // Display the reference number and the deliverable name
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

                // Rules, decisions, tasks, etc.
                CString s;

                WriteLine(IDS_CONCEPTOR_HTML_81);
                WriteLine(IDS_CONCEPTOR_MTL_HTML_16);
                WriteLine(IDS_CONCEPTOR_HTML_82);

                // Build the next lines with the 
                // rules themselves, at least one empty line
                int Count = max(pSymbol->GetRuleCount(), 1);

                for (int i = 0; i < Count; ++i)
                {
                    s.Format(IDS_CONCEPTOR_MTL_HTML_17, i + 1);

                    WriteLine(IDS_CONCEPTOR_HTML_83);
                    WriteLine(s);
                    WriteLine(IDS_CONCEPTOR_HTML_84);
                    WriteLine(pSymbol->GetRuleAt(i));
                    WriteLine(IDS_CONCEPTOR_HTML_85);
                    WriteLine(_T(" "));
                    WriteLine(IDS_CONCEPTOR_HTML_86);
                }

                WriteLine(IDS_CONCEPTOR_HTML_87);
                WriteLine(IDS_CONCEPTOR_MTL_HTML_18);
                WriteLine(IDS_CONCEPTOR_HTML_88);

                // Build the next lines with the 
                // tasks themselves, at least one empty line
                Count = max(pSymbol->GetTaskCount(), 1);

                for (int i = 0; i < Count; ++i)
                {
                    s.Format(IDS_CONCEPTOR_MTL_HTML_19, i + 1);

                    WriteLine(IDS_CONCEPTOR_HTML_89);
                    WriteLine(s);
                    WriteLine(IDS_CONCEPTOR_HTML_90);
                    WriteLine(pSymbol->GetTaskAt(i));
                    WriteLine(IDS_CONCEPTOR_HTML_91);
                    WriteLine(_T(" "));
                    WriteLine(IDS_CONCEPTOR_HTML_92);
                }

                WriteLine(IDS_CONCEPTOR_HTML_93);
                WriteLine(IDS_CONCEPTOR_MTL_HTML_20);
                WriteLine(IDS_CONCEPTOR_HTML_94);

                // Build the next lines with the 
                // decisions themselves, at least one empty line
                Count = max(pSymbol->GetDecisionCount(), 1);

                for (int i = 0; i < Count; ++i)
                {
                    s.Format(IDS_CONCEPTOR_MTL_HTML_21, i + 1);

                    WriteLine(IDS_CONCEPTOR_HTML_95);
                    WriteLine(s);
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

                    // Retrieve all leaving down deliverables
                    CODEdgeArray Edges;

                    if (pSymbol->GetEdgesLeaving_Down(Edges) > 0)
                    {
                        for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
                        {
                            IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
                            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

                            // Check if null and continue if the case
                            if (!pComp)
                            {
                                continue;
                            }

                            // Display the reference number and the deliverable name
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
        }
    }

    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPProcessSymbol.
bool ZVPublishConceptorReport::OnProcessSymbol(ZBBPProcessSymbol* pSymbol)
{
    switch (PublishProc)
    {
        case PUBLISH_CONCEPTOR_HEADERS:
        {
            m_CurrentProcessName = pSymbol->GetSymbolName();

            PSS_ProcessGraphModelMdl* pOwnerModel = (PSS_ProcessGraphModelMdl*)pSymbol->GetOwnerModel();

            if (pOwnerModel)
            {
                ZDProcessGraphPage* pPage = m_pRootModel->FindModelPage(pOwnerModel, true);

                if (pPage)
                {
                    m_DomainName = pPage->GetPageName();
                }
                else
                {
                    m_DomainName.LoadString(IDS_REPORTWEB_NOTFOUND);
                }
            }

            break;
        }

        case PUBLISH_CONCEPTOR_DETAILS:
        {
            m_pPreviousProcess = pSymbol;
            m_CurrentProcessName = pSymbol->GetSymbolName();

            PSS_ProcessGraphModelMdl* pOwnerModel = (PSS_ProcessGraphModelMdl*)pSymbol->GetOwnerModel();

            if (pOwnerModel)
            {
                ZDProcessGraphPage* pPage = m_pRootModel->FindModelPage(pOwnerModel, true);

                if (pPage)
                {
                    m_DomainName = pPage->GetPageName();
                }
                else
                {
                    m_DomainName.LoadString(IDS_REPORTWEB_NOTFOUND);
                }
            }

            m_First = false;

            break;
        }
    }

    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPStartSymbol.
bool ZVPublishConceptorReport::OnStartSymbol(ZBBPStartSymbol* pSymbol)
{
    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPStopSymbol.
bool ZVPublishConceptorReport::OnStopSymbol(ZBBPStopSymbol* pSymbol)
{
    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBDeliverableLinkSymbol.
bool ZVPublishConceptorReport::OnDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol)
{
    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type PSS_Symbol.
bool ZVPublishConceptorReport::OnSymbol(PSS_Symbol* pSymbol)
{
    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type PSS_LinkSymbol.
bool ZVPublishConceptorReport::OnLink(PSS_LinkSymbol* pLink)
{
    return true;
}

// Fonction principale de navigation. Appelle les sous-fonctions par rapport à l'objet visité.
bool ZVPublishConceptorReport::Visit(CODComponent& Symbol)
{
    CODComponent* pSymbol = &Symbol;

    if (ISA(pSymbol, ZBBPProcedureSymbol))
    {
        return OnProcedureSymbol(dynamic_cast<ZBBPProcedureSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBDeliverableLinkSymbol))
    {
        return OnDeliverableLinkSymbol(dynamic_cast<ZBDeliverableLinkSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBBPDoorSymbol))
    {
        return OnDoorSymbol(dynamic_cast<ZBBPDoorSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBBPPageSymbol))
    {
        return OnPageSymbol(dynamic_cast<ZBBPPageSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBBPProcessSymbol))
    {
        return OnProcessSymbol(dynamic_cast<ZBBPProcessSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBBPStartSymbol))
    {
        return OnStartSymbol(dynamic_cast<ZBBPStartSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBBPStopSymbol))
    {
        return OnStopSymbol(dynamic_cast<ZBBPStopSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, PSS_Symbol))
    {
        return OnSymbol(dynamic_cast<PSS_Symbol*>(&Symbol));
    }
    else if (ISA(pSymbol, PSS_LinkSymbol))
    {
        return OnLink(dynamic_cast<PSS_LinkSymbol*>(&Symbol));
    }

    // Not a right symbol or not necessary to visit
    return false;
}

// Cette fonction permet d'écrire une chaîne de caractères sur le disque, en provenance d'un ID.
void ZVPublishConceptorReport::WriteLine(int nID)
{
    CString Output = _T("");

    Output.LoadString(nID);

    if (Output != _T(""))
    {
        HtmlFile << Output;
    }
}

// Cette fonction permet d'écrire une chaîne de caractères sur le disque.
void ZVPublishConceptorReport::WriteLine(CString Text)
{
    if (Text != _T(""))
    {
        HtmlFile << Text;
    }
}
