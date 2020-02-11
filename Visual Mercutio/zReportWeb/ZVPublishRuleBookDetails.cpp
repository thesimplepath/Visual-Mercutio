// ******************************************************************************************************
// *                                  Classe ZVPublishRuleBookDetails                                    *
// ******************************************************************************************************
// * JMR-MODIF - Le 24 avril 2007 - Création de la nouvelle classe ZVPublishRuleBookDetails.            *
// ******************************************************************************************************
// * Cette classe effectue la publication des détails du livre des règles en tant que pages Internet.    *
// ******************************************************************************************************

#include "StdAfx.h"
#include "ZVPublishRuleBookDetails.h"

#include "zReportWebRes.h"
#include "PSS_ModelResIDs.h"

// ******************************************************************************************************
// *                                   Construction et destruction                                        *
// ******************************************************************************************************

// Constructeur de la classe ZVPublishRuleBookDetails.
ZVPublishRuleBookDetails::ZVPublishRuleBookDetails(PSS_ProcessGraphModelMdlBP* pModel /*= NULL*/)
{
    m_pRootModel = pModel;

    Level = 0;
    Lvl1Counter = 0;
    Lvl2Counter = 0;
    Lvl3Counter = 0;
}

// Destructeur de la classe ZVPublishRuleBookDetails.
ZVPublishRuleBookDetails::~ZVPublishRuleBookDetails()
{}

// ******************************************************************************************************
// *                      Fonctions publiques de la classe ZVPublishRuleBookDetails                        *
// ******************************************************************************************************

// Cette fonction permet de publier le rapport dans le répertoire fourni en entrée.
bool ZVPublishRuleBookDetails::Publish(CString Directory)
{
    // if no doc nor model defined. nothing to do.
    if (!m_pRootModel)
    {
        return false;
    }

    // Create the window for file generation feedback
    m_FileGenerateWindow.Create();

    if (!CreateFileSystem(m_pRootModel->GetMainLogicalRules(), Directory))
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
// *                       Fonctions privées de la classe ZVPublishRuleBookDetails                        *
// ******************************************************************************************************

// Cette fonction permet de créer le système de fichiers.
bool ZVPublishRuleBookDetails::CreateFileSystem(PSS_LogicalRulesEntity* pRules, CString Directory)
{
    if (pRules == NULL)
    {
        return false;
    }

    if (!HtmlFile.Create(GenerateFileName(Directory)))
    {
        return false;
    }

    m_FileGenerateWindow.SetDestination(GenerateFileName(Directory));
    m_FileGenerateWindow.UpdateWindow();

    CString Title = _T("");
    Title.LoadString(IDS_RULEBOOKDETAILS_TITLE);
    GenerateHTMLPageHead(Title);

    CreateReport(pRules);

    GenerateHTMLPageFoot();

    HtmlFile.CloseFile();

    return true;
}

// Explore le document, recherche les objets contenus, et teste s'ils contiennent la règle demandée.
void ZVPublishRuleBookDetails::ExploreProcessHierarchy(CString                        RuleNumber,
                                                       CString                        RuleName,
                                                       PSS_ProcessGraphModelMdlBP*    m_StartRootModel    /*= NULL*/)
{
    // Si le modèle d'entrée est vide, cela veut dire que l'on veut une recherche sur tout le document.
    if (m_StartRootModel == NULL)
    {
        // Obtient le contrôleur de modèles du document.
        m_StartRootModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pRootModel);
    }

    if (m_StartRootModel != NULL)
    {
        // Obtient l'ensemble des pages contenues dans le contrôleur de modèles.
        PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = m_StartRootModel->GetPageSet();

        if (pSet != NULL)
        {
            PSS_ProcessGraphModelMdl::IProcessGraphPageIterator i(pSet);

            // On passe en revue toutes les pages enfants contenues dans le contrôleur de modèles.
            for (PSS_ProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
            {
                // Obtient le contrôleur de modèle de la page courante.
                PSS_ProcessGraphModelMdlBP* m_CurModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

                if (m_CurModel != NULL)
                {
                    // Obtient l'ensemble des symboles contenus dans le contrôleur de modèles.
                    CODComponentSet* pCompSet = m_CurModel->GetComponents();

                    if (pCompSet != NULL)
                    {
                        // On passe en revue toutes les symboles contenus dans le contrôleur de modèles.
                        for (int j = 0; j < pCompSet->GetSize(); ++j)
                        {
                            CODComponent* pComponent = pCompSet->GetAt(j);

                            // Contrôle que le composant soit valide, et identifie s'il s'agit d'un processus.
                            if (pComponent && ISA(pComponent, PSS_ProcessSymbolBP))
                            {
                                PSS_ProcessSymbolBP* m_Process = dynamic_cast<PSS_ProcessSymbolBP*>(pComponent);

                                if (m_Process != NULL)
                                {
                                    // Obtient le contrôleur de modèles enfant du processus.
                                    PSS_ProcessGraphModelMdlBP* m_ChildModel =
                                        dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_Process->GetModel());

                                    // Si le contrôleur de modèles existe, fait un appel récursif sur celui-ci,
                                    // afin de passer en revue toutes les pages du document.
                                    if (m_ChildModel != NULL)
                                    {
                                        ExploreProcessHierarchy(RuleNumber,
                                                                RuleName,
                                                                m_ChildModel);
                                    }

                                    if (m_Process->ContainsRule(RuleName) == TRUE)
                                    {
                                        CString ObjectName = _T("");
                                        ObjectName.LoadString(IDS_ZS_BP_PROP_PROCESS_TITLE);

                                        GenerateSection(RuleNumber,
                                                        RuleName,
                                                        ObjectName,
                                                        m_Process->GetSymbolName(),
                                                        m_Process->GetUnitName());
                                    }
                                }
                            }

                            // Contrôle que le composant soit valide, et identifie s'il s'agit d'une procédure.
                            if (pComponent && ISA(pComponent, PSS_ProcedureSymbolBP))
                            {
                                PSS_ProcedureSymbolBP* m_Procedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pComponent);

                                if (m_Procedure != NULL)
                                {
                                    if (m_Procedure->ContainsRule(RuleName) == TRUE)
                                    {
                                        CString ObjectName = _T("");
                                        ObjectName.LoadString(IDS_ZS_BP_PROP_PROCEDURE_TITLE);

                                        GenerateSection(RuleNumber,
                                                        RuleName,
                                                        ObjectName,
                                                        m_Procedure->GetSymbolName(),
                                                        m_Procedure->GetUnitName());
                                    }
                                }
                            }

                            // Contrôle que le composant soit valide, et identifie s'il s'agit d'un point start.
                            if (pComponent && ISA(pComponent, ZBBPStartSymbol))
                            {
                                ZBBPStartSymbol* m_Start = dynamic_cast<ZBBPStartSymbol*>(pComponent);

                                if (m_Start != NULL)
                                {
                                    if (m_Start->ContainsRule(RuleName) == TRUE)
                                    {
                                        CString ObjectName = _T("");
                                        ObjectName.LoadString(IDS_ZS_BP_PROP_START_TITLE);

                                        GenerateSection(RuleNumber,
                                                        RuleName,
                                                        ObjectName,
                                                        m_Start->GetSymbolName(),
                                                        m_Start->GetUnitName());
                                    }
                                }
                            }

                            // Contrôle que le composant soit valide, et identifie s'il s'agit d'un point stop.
                            if (pComponent && ISA(pComponent, ZBBPStopSymbol))
                            {
                                ZBBPStopSymbol* m_Stop = dynamic_cast<ZBBPStopSymbol*>(pComponent);

                                if (m_Stop != NULL)
                                {
                                    if (m_Stop->ContainsRule(RuleName) == TRUE)
                                    {
                                        CString ObjectName = _T("");
                                        ObjectName.LoadString(IDS_ZS_BP_PROP_STOP_TITLE);

                                        GenerateSection(RuleNumber,
                                                        RuleName,
                                                        ObjectName,
                                                        m_Stop->GetSymbolName(),
                                                        m_Stop->GetUnitName());
                                    }
                                }
                            }

                            // Contrôle que le composant soit valide, et identifie s'il s'agit d'un livrable.
                            if (pComponent && ISA(pComponent, ZBDeliverableLinkSymbol))
                            {
                                ZBDeliverableLinkSymbol* m_Deliverable =
                                    dynamic_cast<ZBDeliverableLinkSymbol*>(pComponent);

                                if (m_Deliverable != NULL)
                                {
                                    if (m_Deliverable->ContainsRule(RuleName) == TRUE)
                                    {
                                        CString ObjectName = _T("");
                                        ObjectName.LoadString(IDS_ZS_BP_PROP_DELIVERABLE_TITLE);

                                        CODSymbolComponent*    m_EnteringSymbol = m_Deliverable->GetEnteringSymbol();
                                        CString                s_UnitName = _T("");

                                        // Recherche l'unité de traitement du symbole entrant.
                                        if (m_EnteringSymbol != NULL)
                                        {
                                            if (ISA(m_EnteringSymbol, PSS_ProcessSymbolBP))
                                            {
                                                s_UnitName =
                                                    dynamic_cast<PSS_ProcessSymbolBP*>(m_EnteringSymbol)->GetUnitName();
                                            }

                                            if (ISA(m_EnteringSymbol, PSS_ProcedureSymbolBP))
                                            {
                                                s_UnitName =
                                                    dynamic_cast<PSS_ProcedureSymbolBP*>(m_EnteringSymbol)->GetUnitName();
                                            }

                                            if (ISA(m_EnteringSymbol, ZBBPStartSymbol))
                                            {
                                                s_UnitName =
                                                    dynamic_cast<ZBBPStartSymbol*>(m_EnteringSymbol)->GetUnitName();
                                            }

                                            if (ISA(m_EnteringSymbol, ZBBPStopSymbol))
                                            {
                                                s_UnitName =
                                                    dynamic_cast<ZBBPStopSymbol*>(m_EnteringSymbol)->GetUnitName();
                                            }
                                        }

                                        GenerateSection(RuleNumber,
                                                        RuleName,
                                                        ObjectName,
                                                        m_Deliverable->GetSymbolName(),
                                                        s_UnitName);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Cette fonction permet de publier les données du livre de détails des règles.
void ZVPublishRuleBookDetails::CreateReport(PSS_LogicalRulesEntity* pRules)
{
    if (pRules != NULL)
    {
        // Obtient le nom et la description de la règle.
        CString RuleName = pRules->GetEntityName();
        CString RuleNumber = _T("");

        switch (Level)
        {
            case 0:
            {
                GenerateHTMLDocumentHeader();
                ExploreProcessHierarchy(_T("0"), RuleName);

                break;
            }

            case 1:
            {
                Lvl1Counter++;

                RuleNumber.Format(_T("%d"), Lvl1Counter);
                ExploreProcessHierarchy(RuleNumber, RuleName);

                Lvl2Counter = 0;
                Lvl3Counter = 0;

                break;
            }

            case 2:
            {
                Lvl2Counter++;

                RuleNumber.Format(_T("%d.%d"), Lvl1Counter, Lvl2Counter);
                ExploreProcessHierarchy(RuleNumber, RuleName);

                Lvl3Counter = 0;
                break;
            }

            case 3:
            default:
            {
                Lvl3Counter++;

                RuleNumber.Format(_T("%d.%d.%d"), Lvl1Counter, Lvl2Counter, Lvl3Counter);
                ExploreProcessHierarchy(RuleNumber, RuleName);

                break;
            }
        }

        // Teste si la prestation contient des prestations enfants.
        if (pRules->ContainEntity())
        {
            int Count = pRules->GetEntityCount();

            for (int i = 0; i < Count; ++i)
            {
                PSS_RulesEntity* pEntity = pRules->GetEntityAt(i);

                if (!pEntity)
                {
                    continue;
                }

                // Teste si l'objet enfant est bien un objet de type PSS_LogicalRulesEntity.
                if (ISA(pEntity, PSS_LogicalRulesEntity))
                {
                    Level++;
                    CreateReport(dynamic_cast<PSS_LogicalRulesEntity*>(pEntity));
                    Level--;
                }
            }
        }
    }
}

// Cette fonction permet de créer le nom de fichier correct pour le livre du détail des règles.
CString ZVPublishRuleBookDetails::GenerateFileName(CString Directory)
{
    CString sFileName = Directory;
    sFileName += _T("RuleBookDetails");
    sFileName += _T(".htm");

    return sFileName;
}

// Cette fonction permet la génération d'un en-tête standard HTML.
void ZVPublishRuleBookDetails::GenerateHTMLPageHead(CString Title)
{
    CString Output = _T("");

    Output.Format(IDS_RULEBOOKDETAILS_HTML_1, Title);

    WriteLine(Output);
}

// Cette fonction permet la génération d'un pied de page standard HTML.
void ZVPublishRuleBookDetails::GenerateHTMLPageFoot()
{
    WriteLine(IDS_RULEBOOKDETAILS_HTML_2);
}

// Cette fonction permet de générer l'en-tête du document de détails des règles.
void ZVPublishRuleBookDetails::GenerateHTMLDocumentHeader()
{
    CString Output = _T("");
    CString Header1 = _T("");
    CString Header2 = _T("");
    CString Header3 = _T("");
    CString Header4 = _T("");
    CString Header5 = _T("");

    Header1.LoadString(IDS_RULEBOOKDETAILS_MTL_HTML_1);
    Header2.LoadString(IDS_RULEBOOKDETAILS_MTL_HTML_2);
    Header3.LoadString(IDS_RULEBOOKDETAILS_MTL_HTML_3);
    Header4.LoadString(IDS_RULEBOOKDETAILS_MTL_HTML_4);
    Header5.LoadString(IDS_RULEBOOKDETAILS_MTL_HTML_5);

    Output.Format(IDS_RULEBOOKDETAILS_HTML_3,
                  Header1,
                  Header2,
                  Header3,
                  Header4,
                  Header5);

    WriteLine(Output);
}

// Cette fonction permet de générer une section dans le document de détails des règles.
void ZVPublishRuleBookDetails::GenerateSection(CString RuleNumber,
                                               CString RuleName,
                                               CString ObjType,
                                               CString ObjName,
                                               CString UnitName)
{
    CString Output = _T("");

    Output.Format(IDS_RULEBOOKDETAILS_HTML_4,
                  RuleNumber,
                  RuleName,
                  ObjType,
                  ObjName,
                  UnitName);

    WriteLine(Output);
}

// Cette fonction permet d'écrire une chaîne de caractères sur le disque, en provenance d'un ID.
void ZVPublishRuleBookDetails::WriteLine(int nID)
{
    CString Output = _T("");

    Output.LoadString(nID);

    if (Output != _T(""))
    {
        HtmlFile << Output;
    }
}

// Cette fonction permet d'écrire une chaîne de caractères sur le disque.
void ZVPublishRuleBookDetails::WriteLine(CString Text)
{
    if (Text != _T(""))
    {
        HtmlFile << Text;
    }
}
