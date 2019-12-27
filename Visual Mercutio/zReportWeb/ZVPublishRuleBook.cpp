// ******************************************************************************************************
// *                                         Classe ZVPublishRuleBook                                    *
// ******************************************************************************************************
// * JMR-MODIF - Le 14 janvier 2007 - Création de la nouvelle classe ZVPublishRuleBook.                    *
// ******************************************************************************************************
// * Cette classe effectue la publication du livre des règles en tant que pages Internet.                *
// ******************************************************************************************************

#include "StdAfx.h"
#include "ZVPublishRuleBook.h"

#include "zReportWebRes.h"
#include "PSS_ModelResIDs.h"

// ******************************************************************************************************
// *                                   Construction et destruction                                        *
// ******************************************************************************************************

// Constructeur de la classe ZVPublishRuleBook.
ZVPublishRuleBook::ZVPublishRuleBook(ZDProcessGraphModelMdlBP* pModel /*= NULL*/)
{
    m_pRootModel = pModel;
    Level = 0;
    Lvl1Counter = 0;
    Lvl2Counter = 0;
    Lvl3Counter = 0;
}

// Destructeur de la classe ZVPublishRuleBook.
ZVPublishRuleBook::~ZVPublishRuleBook()
{}

// ******************************************************************************************************
// *                          Fonctions publiques de la classe ZVPublishRuleBook                        *
// ******************************************************************************************************

// Cette fonction permet de publier le rapport dans le répertoire fourni en entrée.
bool ZVPublishRuleBook::Publish(CString Directory)
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
// *                           Fonctions privées de la classe ZVPublishRuleBook                            *
// ******************************************************************************************************

// Cette fonction permet de créer le système de fichiers.
bool ZVPublishRuleBook::CreateFileSystem(PSS_LogicalRulesEntity* pRules, CString Directory)
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
    Title.LoadString(IDS_RULEBOOK_TITLE);
    GenerateHTMLPageHead(Title);

    CreateReport(pRules);

    GenerateHTMLPageFoot();

    HtmlFile.CloseFile();

    return true;
}

// Cette fonction permet de publier les données du livre des règles.
void ZVPublishRuleBook::CreateReport(PSS_LogicalRulesEntity* pRules)
{
    if (pRules != NULL)
    {
        // Obtient le nom et la description de la règle.
        CString RuleName = pRules->GetEntityName();
        CString RuleDesc = pRules->GetEntityDescription();

        switch (Level)
        {
            case 0:
            {
                GenerateHTMLDocumentHeader(RuleName, RuleDesc);
                break;
            }

            case 1:
            {
                Lvl1Counter++;
                GenerateHTMLTable1(RuleName, RuleDesc);
                Lvl2Counter = 0;
                Lvl3Counter = 0;
                break;
            }

            case 2:
            {
                Lvl2Counter++;
                GenerateHTMLTable2(RuleName, RuleDesc);
                Lvl3Counter = 0;
                break;
            }

            case 3:
            default:
            {
                Lvl3Counter++;
                GenerateHTMLTable3(RuleName, RuleDesc);
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

// Cette fonction permet de créer le nom de fichier correct pour le livre des règles.
CString ZVPublishRuleBook::GenerateFileName(CString Directory)
{
    CString sFileName = Directory;
    sFileName += _T("RuleBook");
    sFileName += _T(".htm");

    return sFileName;
}

// Cette fonction permet la génération d'un en-tête standard HTML.
void ZVPublishRuleBook::GenerateHTMLPageHead(CString Title)
{
    CString Output = _T("");

    Output.Format(IDS_RULEBOOK_HTML_1, Title);

    WriteLine(Output);
}

// Cette fonction permet la génération d'un pied de page standard HTML.
void ZVPublishRuleBook::GenerateHTMLPageFoot()
{
    WriteLine(IDS_RULEBOOK_HTML_2);
}

// Cette fonction permet de générer l'en-tête du document dans le livre des règles.
void ZVPublishRuleBook::GenerateHTMLDocumentHeader(CString RuleName, CString RuleDesc)
{
    CString Output = _T("");

    Output.Format(IDS_RULEBOOK_HTML_6,
                  RuleName,
                  RuleDesc);

    WriteLine(Output);
}

// Cette fonction permet de générer une entrée de niveau 1 dans le livre des règles.
void ZVPublishRuleBook::GenerateHTMLTable1(CString RuleName, CString RuleDesc)
{
    CString Output = _T("");
    CString Index = _T("");

    Index.Format(_T("%d"), Lvl1Counter);

    Output.Format(IDS_RULEBOOK_HTML_3,
                  Index,
                  RuleName,
                  RuleDesc);

    WriteLine(Output);
}

// Cette fonction permet de générer une entrée de niveau 2 dans le livre des règles.
void ZVPublishRuleBook::GenerateHTMLTable2(CString RuleName, CString RuleDesc)
{
    CString Output = _T("");
    CString Index = _T("");

    Index.Format(_T("%d.%d"), Lvl1Counter, Lvl2Counter);

    Output.Format(IDS_RULEBOOK_HTML_4,
                  Index,
                  RuleName,
                  RuleDesc);

    WriteLine(Output);
}

// Cette fonction permet de générer une entrée de niveau 3 dans le livre des règles.
void ZVPublishRuleBook::GenerateHTMLTable3(CString RuleName, CString RuleDesc)
{
    CString Output = _T("");
    CString Index = _T("");

    Index.Format(_T("%d.%d.%d"), Lvl1Counter, Lvl2Counter, Lvl3Counter);

    Output.Format(IDS_RULEBOOK_HTML_5,
                  Index,
                  RuleName,
                  RuleDesc);

    WriteLine(Output);
}

// Cette fonction permet d'écrire une chaîne de caractères sur le disque, en provenance d'un ID.
void ZVPublishRuleBook::WriteLine(int nID)
{
    CString Output = _T("");

    Output.LoadString(nID);

    if (Output != _T(""))
    {
        HtmlFile << Output;
    }
}

// Cette fonction permet d'écrire une chaîne de caractères sur le disque.
void ZVPublishRuleBook::WriteLine(CString Text)
{
    if (Text != _T(""))
    {
        HtmlFile << Text;
    }
}
