/****************************************************************************
 * ==> PSS_PublishRuleBook -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will publish the rule book to   *
 *               html files                                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_PublishRuleBook.h"

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
    m_Lvl3Counter(0)
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
    const CString ruleName = pRules->GetEntityName();
    const CString ruleDesc = pRules->GetEntityDescription();

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
            break;

        case 2:
            ++m_Lvl2Counter;
            GenerateHTMLTable2(ruleName, ruleDesc);
            m_Lvl3Counter = 0;
            break;

        case 3:
        default:
            ++m_Lvl3Counter;
            GenerateHTMLTable3(ruleName, ruleDesc);
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
CString PSS_PublishRuleBook::GenerateFileName(const CString& dir)
{
    CString fileName  = dir;
    fileName         += _T("RuleBook");
    fileName         += _T(".htm");

    return fileName;
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
