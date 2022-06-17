/****************************************************************************
 * ==> PSS_PublishRuleBook -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will publish the rule book to   *
 *               html files                                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_PublishRuleBook.h"

// processsoft
#include "zModelBP\PSS_ProcedureSymbolBP.h"
#include "zModelBP\PSS_ProcessSymbolBP.h"
#include "zModelBP\PSS_StartSymbolBP.h"
#include "zModelBP\PSS_StopSymbolBP.h"
#include "zModelBP\PSS_DeliverableLinkSymbolBP.h"

// resources
#include "zReportWebRes.h"
#include "PSS_ModelResIDs.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_PublishRuleBook
//---------------------------------------------------------------------------
PSS_PublishRuleBook::PSS_PublishRuleBook(PSS_ProcessGraphModelMdlBP* pModel) :
    m_pRootModel(pModel),
    m_Level(0),
    m_Lvl1Counter(0),
    m_Lvl2Counter(0),
    m_Lvl3Counter(0),
    m_Lvl4Counter(0),
    m_Lvl5Counter(0),
    m_Lvl6Counter(0)
{}
//---------------------------------------------------------------------------
PSS_PublishRuleBook::~PSS_PublishRuleBook()
{}
//---------------------------------------------------------------------------
bool PSS_PublishRuleBook::Publish(const CString& dir)
{
    // if no doc or model defined, nothing to do
    if (!m_pRootModel)
        return false;

    // create the window to receive the file generation feedback
    m_FileGenerateWindow.Create();

    if (!CreateFileSystem(m_pRootModel->GetMainLogicalRules(), dir))
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
bool PSS_PublishRuleBook::CreateFileSystem(PSS_LogicalRulesEntity* pRules, const CString& dir)
{
    if (!pRules)
        return false;

    if (!m_HtmlFile.Create(GenerateFileName(dir)))
        return false;

    m_FileGenerateWindow.SetDestination(GenerateFileName(dir));
    m_FileGenerateWindow.UpdateWindow();

    CString title;
    title.LoadString(IDS_RULEBOOK_TITLE);

    GenerateHTMLPageHeader(title);
    CreateReport(pRules);
    GenerateHTMLPageFooter();

    m_HtmlFile.CloseFile();

    return true;
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBook::CreateReport(PSS_LogicalRulesEntity* pRules)
{
    if (!pRules)
        return;

    // get the rule name and description
          CString ruleName = pRules->GetEntityName();
    const CString ruleDesc = pRules->GetEntityDescription();

    if (!IsRuleInUse(ruleName))
        ruleName += _T("*");

    switch (m_Level)
    {
        case 0:
            GenerateHTMLDocumentHeader(ruleName, ruleDesc);
            break;

        case 1:
            ++m_Lvl1Counter;
            GenerateHTMLTable1(ruleName, ruleDesc);
            m_Lvl2Counter = 0;
            m_Lvl3Counter = 0;
            m_Lvl4Counter = 0;
            m_Lvl5Counter = 0;
            m_Lvl6Counter = 0;
            break;

        case 2:
            ++m_Lvl2Counter;
            GenerateHTMLTable2(ruleName, ruleDesc);
            m_Lvl3Counter = 0;
            m_Lvl4Counter = 0;
            m_Lvl5Counter = 0;
            m_Lvl6Counter = 0;
            break;

        case 3:
            ++m_Lvl3Counter;
            GenerateHTMLTable3(ruleName, ruleDesc);
            m_Lvl4Counter = 0;
            m_Lvl5Counter = 0;
            m_Lvl6Counter = 0;
            break;

        case 4:
            ++m_Lvl4Counter;
            GenerateHTMLTable4(ruleName, ruleDesc);
            m_Lvl5Counter = 0;
            m_Lvl6Counter = 0;
            break;

        case 5:
            ++m_Lvl5Counter;
            GenerateHTMLTable5(ruleName, ruleDesc);
            m_Lvl6Counter = 0;
            break;

        case 6:
        default:
            m_Lvl6Counter++;
            GenerateHTMLTable6(ruleName, ruleDesc);
            break;
    }

    // check if the rule contains children
    if (pRules->ContainEntity())
    {
        const int count = pRules->GetEntityCount();

        for (int i = 0; i < count; ++i)
        {
            PSS_LogicalRulesEntity* pEntity = dynamic_cast<PSS_LogicalRulesEntity*>(pRules->GetEntityAt(i));

            if (!pEntity)
                continue;

            ++m_Level;
            CreateReport(pEntity);
            --m_Level;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBook::GenerateHTMLPageHeader(const CString& title)
{
    CString output;
    output.Format(IDS_RULEBOOK_HTML_1, title);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBook::GenerateHTMLPageFooter()
{
    WriteLine(IDS_RULEBOOK_HTML_2);
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBook::GenerateHTMLDocumentHeader(const CString& ruleName, const CString& ruleDesc)
{
    CString output;
    output.Format(IDS_RULEBOOK_HTML_6, ruleName, ruleDesc);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBook::GenerateHTMLTable1(const CString& ruleName, const CString& ruleDesc)
{
    CString index;
    index.Format(_T("%d"), m_Lvl1Counter);

    CString output;
    output.Format(IDS_RULEBOOK_HTML_3, index, ruleName, ruleDesc);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBook::GenerateHTMLTable2(const CString& ruleName, const CString& ruleDesc)
{
    CString index;
    index.Format(_T("%d.%d"), m_Lvl1Counter, m_Lvl2Counter);

    CString output;
    output.Format(IDS_RULEBOOK_HTML_4, index, ruleName, ruleDesc);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBook::GenerateHTMLTable3(const CString& ruleName, const CString& ruleDesc)
{
    CString index;
    index.Format(_T("%d.%d.%d"), m_Lvl1Counter, m_Lvl2Counter, m_Lvl3Counter);

    CString output;
    output.Format(IDS_RULEBOOK_HTML_5, index, ruleName, ruleDesc);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBook::GenerateHTMLTable4(const CString& ruleName, const CString& ruleDesc)
{
    CString index;
    index.Format(_T("%d.%d.%d.%d"), m_Lvl1Counter, m_Lvl2Counter, m_Lvl3Counter, m_Lvl4Counter);

    CString output;
    output.Format(IDS_RULEBOOK_HTML_7, index, ruleName, ruleDesc);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBook::GenerateHTMLTable5(const CString& ruleName, const CString& ruleDesc)
{
    CString index;
    index.Format(_T("%d.%d.%d.%d.%d"), m_Lvl1Counter, m_Lvl2Counter, m_Lvl3Counter, m_Lvl4Counter, m_Lvl5Counter);

    CString output = _T("");
    output.Format(IDS_RULEBOOK_HTML_8, index, ruleName, ruleDesc);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBook::GenerateHTMLTable6(const CString& ruleName, const CString& ruleDesc)
{
    CString index;
    index.Format(_T("%d.%d.%d.%d.%d.%d"), m_Lvl1Counter, m_Lvl2Counter, m_Lvl3Counter, m_Lvl4Counter, m_Lvl5Counter, m_Lvl6Counter);

    CString output;
    output.Format(IDS_RULEBOOK_HTML_9, index, ruleName, ruleDesc);

    WriteLine(output);
}
//---------------------------------------------------------------------------
CString PSS_PublishRuleBook::GenerateFileName(const CString& dir)
{
    CString fileName  = dir;
    fileName         += _T("RuleBook");
    fileName         += _T(".htm");

    return fileName;
}
//---------------------------------------------------------------------------
BOOL PSS_PublishRuleBook::IsRuleInUse(const CString& ruleName, ZDProcessGraphModelMdlBP* pStartRootModel)
{
    // do search on the whole document?
    if (!pStartRootModel)
        // get the document model controller
        pStartRootModel = dynamic_cast<ZDProcessGraphModelMdlBP*>(m_pRootModel);

    if (!pStartRootModel)
        return FALSE;

    // get the model controller page set
    PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pPageSet = pStartRootModel->GetPageSet();

    if (!pPageSet)
        return FALSE;

    // get page set iterator
    PSS_ProcessGraphModelMdl::IProcessGraphPageIterator i(pPageSet);

    // iterate through children pages contained in the model controller
    for (PSS_ProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
    {
        // get current page model controller
        PSS_ProcessGraphModelMdlBP* pCurModel = dynamic_cast<ZDProcessGraphModelMdlBP*>(pPage->GetModel());

        if (!pCurModel)
            continue;

        // get symbols contained in model controller
        CODComponentSet* pCompSet = pCurModel->GetComponents();

        if (!pCompSet)
            continue;

        // iterate through symbols contained in model controller
        for (SEC_INT j = 0; j < pCompSet->GetSize(); ++j)
        {
            CODComponent* pComponent = pCompSet->GetAt(j);

            if (!pComponent)
                continue;

            // search for component type
            if (ISA(pComponent, PSS_ProcessSymbolBP))
            {
                PSS_ProcessSymbolBP* pProcess = static_cast<PSS_ProcessSymbolBP*>(pComponent);

                // get the process model controller
                PSS_ProcessGraphModelMdlBP* pChildModel =
                        dynamic_cast<ZDProcessGraphModelMdlBP*>(pProcess->GetModel());

                // if the model controller exists, continue recursively to search in it,
                // in order to iterate through all the document pages
                if (pChildModel)
                {
                    BOOL result = IsRuleInUse(ruleName, pChildModel);

                    // found the rule in the child model?
                    if (result)
                        return TRUE;
                }

                // found the rule in the process itself?
                if (pProcess->ContainsRule(ruleName))
                    return TRUE;
            }
            else
            if (ISA(pComponent, PSS_ProcedureSymbolBP))
            {
                PSS_ProcedureSymbolBP* pProcedure = static_cast<PSS_ProcedureSymbolBP*>(pComponent);

                // found the rule in the procedure?
                if (pProcedure)
                    if (pProcedure->ContainsRule(ruleName))
                        return TRUE;
            }
            else
            if (ISA(pComponent, PSS_StartSymbolBP))
            {
                PSS_StartSymbolBP* pStart = static_cast<PSS_StartSymbolBP*>(pComponent);

                // found the rule in the start point?
                if (pStart)
                    if (pStart->ContainsRule(ruleName))
                        return TRUE;
            }
            else
            if (ISA(pComponent, PSS_StopSymbolBP))
            {
                PSS_StopSymbolBP* pStop = static_cast<PSS_StopSymbolBP*>(pComponent);

                // found the rule in the stop point?
                if (pStop)
                    if (pStop->ContainsRule(ruleName))
                        return TRUE;
            }
            else
            if (ISA(pComponent, PSS_DeliverableLinkSymbolBP))
            {
                PSS_DeliverableLinkSymbolBP* pDeliverable = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pComponent);

                // found the rule in the deliverable?
                if (pDeliverable)
                    if (pDeliverable->ContainsRule(ruleName))
                        return TRUE;
            }
        }
    }

    // rule was not found
    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBook::WriteLine(const CString& text)
{
    if (!text.IsEmpty())
        m_HtmlFile << text;
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBook::WriteLine(int id)
{
    CString output;
    output.LoadString(id);

    if (!output.IsEmpty())
        m_HtmlFile << output;
}
//---------------------------------------------------------------------------
