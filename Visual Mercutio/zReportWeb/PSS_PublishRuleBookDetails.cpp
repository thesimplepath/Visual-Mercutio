/****************************************************************************
 * ==> PSS_PublishRuleBookDetails ------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will publish the rule book      *
 *               details to html files                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_PublishRuleBookDetails.h"

// resources
#include "zReportWebRes.h"
#include "PSS_ModelResIDs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_PublishRuleBookDetails
//---------------------------------------------------------------------------
PSS_PublishRuleBookDetails::PSS_PublishRuleBookDetails(PSS_ProcessGraphModelMdlBP* pModel) :
    m_pRootModel(pModel),
    m_Level(0),
    m_Lvl1Counter(0),
    m_Lvl2Counter(0),
    m_Lvl3Counter(0)
{}
//---------------------------------------------------------------------------
PSS_PublishRuleBookDetails::~PSS_PublishRuleBookDetails()
{}
//---------------------------------------------------------------------------
bool PSS_PublishRuleBookDetails::Publish(const CString& dir)
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
bool PSS_PublishRuleBookDetails::CreateFileSystem(PSS_LogicalRulesEntity* pRules, const CString& dir)
{
    if (!pRules)
        return false;

    if (!m_HtmlFile.Create(GenerateFileName(dir)))
        return false;

    m_FileGenerateWindow.SetDestination(GenerateFileName(dir));
    m_FileGenerateWindow.UpdateWindow();

    CString title;
    title.LoadString(IDS_RULEBOOKDETAILS_TITLE);

    GenerateHTMLPageHeader(title);
    CreateReport(pRules);
    GenerateHTMLPageFooter();

    m_HtmlFile.CloseFile();

    return true;
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBookDetails::CreateReport(PSS_LogicalRulesEntity* pRules)
{
    if (!pRules)
        return;

    // get the rule name and number
    const CString ruleName = pRules->GetEntityName();
    CString       ruleNumber;

    switch (m_Level)
    {
        case 0:
            GenerateHTMLDocumentHeader();
            ExploreProcessHierarchy(_T("0"), ruleName);
            break;

        case 1:
            ++m_Lvl1Counter;

            ruleNumber.Format(_T("%d"), ++m_Lvl1Counter);
            ExploreProcessHierarchy(ruleNumber, ruleName);

            m_Lvl2Counter = 0;
            m_Lvl3Counter = 0;

            break;

        case 2:
            ++m_Lvl2Counter;

            ruleNumber.Format(_T("%d.%d"), m_Lvl1Counter, m_Lvl2Counter);
            ExploreProcessHierarchy(ruleNumber, ruleName);

            m_Lvl3Counter = 0;
            break;

        case 3:
        default:
            ++m_Lvl3Counter;

            ruleNumber.Format(_T("%d.%d.%d"), m_Lvl1Counter, m_Lvl2Counter, m_Lvl3Counter);
            ExploreProcessHierarchy(ruleNumber, ruleName);

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
void PSS_PublishRuleBookDetails::GenerateHTMLPageHeader(const CString& title)
{
    CString output;
    output.Format(IDS_RULEBOOKDETAILS_HTML_1, title);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBookDetails::GenerateHTMLPageFooter()
{
    WriteLine(IDS_RULEBOOKDETAILS_HTML_2);
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBookDetails::GenerateHTMLDocumentHeader()
{
    CString header1;
    header1.LoadString(IDS_RULEBOOKDETAILS_MTL_HTML_1);

    CString header2;
    header2.LoadString(IDS_RULEBOOKDETAILS_MTL_HTML_2);

    CString header3;
    header3.LoadString(IDS_RULEBOOKDETAILS_MTL_HTML_3);

    CString header4;
    header4.LoadString(IDS_RULEBOOKDETAILS_MTL_HTML_4);

    CString header5;
    header5.LoadString(IDS_RULEBOOKDETAILS_MTL_HTML_5);

    CString output;
    output.Format(IDS_RULEBOOKDETAILS_HTML_3,
                  header1,
                  header2,
                  header3,
                  header4,
                  header5);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBookDetails::GenerateSection(const CString& ruleNumber,
                                                 const CString& ruleName,
                                                 const CString& objType,
                                                 const CString& objName,
                                                 const CString& unitName)
{
    CString output;
    output.Format(IDS_RULEBOOKDETAILS_HTML_4,
                  ruleNumber,
                  ruleName,
                  objType,
                  objName,
                  unitName);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBookDetails::ExploreProcessHierarchy(const CString&              ruleNumber,
                                                         const CString&              ruleName,
                                                         PSS_ProcessGraphModelMdlBP* pStartRootModel)
{
    // if no root model, the exploration should be performed on the whole document
    if (!pStartRootModel)
        // get the document root model controller
        pStartRootModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pRootModel);

    if (!pStartRootModel)
        return;

    // get the pages contained in the model controller
    PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = pStartRootModel->GetPageSet();

    if (!pSet)
        return;

    PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(pSet);

    // iterate through the children pages contained in the model controller
    for (PSS_ProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
    {
        // get the current page model controller
        PSS_ProcessGraphModelMdlBP* pCurModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

        if (!pCurModel)
            continue;

        // get the symbol set contained in the page model controller
        CODComponentSet* pCompSet = pCurModel->GetComponents();

        if (!pCompSet)
            continue;

        // iterate through the symbols contained in the page model controller
        for (int i = 0; i < pCompSet->GetSize(); ++i)
        {
            CODComponent*        pComponent = pCompSet->GetAt(i);
            PSS_ProcessSymbolBP* pProcess   = dynamic_cast<PSS_ProcessSymbolBP*>(pComponent);

            if (pProcess)
            {
                // get the process child model
                PSS_ProcessGraphModelMdlBP* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pProcess->GetModel());

                // iterate recursively through the child model rules
                if (pChildModel)
                    ExploreProcessHierarchy(ruleNumber, ruleName, pChildModel);

                if (pProcess->ContainsRule(ruleName))
                {
                    CString objectName;
                    objectName.LoadString(IDS_ZS_BP_PROP_PROCESS_TITLE);

                    GenerateSection(ruleNumber,
                                    ruleName,
                                    objectName,
                                    pProcess->GetSymbolName(),
                                    pProcess->GetUnitName());
                }
            }

            PSS_ProcedureSymbolBP* pProcedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pComponent);

            if (pProcedure)
                if (pProcedure->ContainsRule(ruleName))
                {
                    CString objectName;
                    objectName.LoadString(IDS_ZS_BP_PROP_PROCEDURE_TITLE);

                    GenerateSection(ruleNumber,
                                    ruleName,
                                    objectName,
                                    pProcedure->GetSymbolName(),
                                    pProcedure->GetUnitName());
                }

            PSS_StartSymbolBP* pStart = dynamic_cast<PSS_StartSymbolBP*>(pComponent);

            if (pStart)
                if (pStart->ContainsRule(ruleName))
                {
                    CString objectName;
                    objectName.LoadString(IDS_ZS_BP_PROP_START_TITLE);

                    GenerateSection(ruleNumber,
                                    ruleName,
                                    objectName,
                                    pStart->GetSymbolName(),
                                    pStart->GetUnitName());
                }

            PSS_StopSymbolBP* pStop = dynamic_cast<PSS_StopSymbolBP*>(pComponent);

            if (pStop)
                if (pStop->ContainsRule(ruleName))
                {
                    CString objectName;
                    objectName.LoadString(IDS_ZS_BP_PROP_STOP_TITLE);

                    GenerateSection(ruleNumber,
                                    ruleName,
                                    objectName,
                                    pStop->GetSymbolName(),
                                    pStop->GetUnitName());
                }

            PSS_DeliverableLinkSymbolBP* pDeliverable = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pComponent);

            if (pDeliverable)
                if (pDeliverable->ContainsRule(ruleName))
                {
                    CString objectName;
                    objectName.LoadString(IDS_ZS_BP_PROP_DELIVERABLE_TITLE);

                    CODSymbolComponent* pEnteringSymbol = pDeliverable->GetEnteringSymbol();
                    CString             unitName;

                    // Search for the entering symbol process
                    if (pEnteringSymbol)
                    {
                        PSS_ProcessSymbolBP* pEnteringProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pEnteringSymbol);

                        if (pEnteringProcess)
                            unitName = pEnteringProcess->GetUnitName();

                        PSS_ProcedureSymbolBP* pEnteringProcedure =
                                pEnteringProcess ? NULL : dynamic_cast<PSS_ProcedureSymbolBP*>(pEnteringSymbol);

                        if (pEnteringProcedure)
                            unitName = pEnteringProcedure->GetUnitName();

                        PSS_StartSymbolBP* pEnteringStart =
                                pEnteringProcedure ? NULL : dynamic_cast<PSS_StartSymbolBP*>(pEnteringSymbol);

                        if (pEnteringStart)
                            unitName = pEnteringStart->GetUnitName();

                        PSS_StopSymbolBP* pEnteringEnd =
                                pEnteringStart ? NULL : dynamic_cast<PSS_StopSymbolBP*>(pEnteringSymbol);

                        if (pEnteringEnd)
                            unitName = pEnteringEnd->GetUnitName();
                    }

                    GenerateSection(ruleNumber,
                                    ruleName,
                                    objectName,
                                    pDeliverable->GetSymbolName(),
                                    unitName);
                }
        }
    }
}
//---------------------------------------------------------------------------
CString PSS_PublishRuleBookDetails::GenerateFileName(const CString& dir)
{
    CString fileName  = dir;
    fileName         += _T("RuleBookDetails");
    fileName         += _T(".htm");

    return fileName;
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBookDetails::WriteLine(const CString& text)
{
    if (!text.IsEmpty())
        m_HtmlFile << text;
}
//---------------------------------------------------------------------------
void PSS_PublishRuleBookDetails::WriteLine(int id)
{
    CString output;
    output.LoadString(id);

    if (!output.IsEmpty())
        m_HtmlFile << output;
}
//---------------------------------------------------------------------------
