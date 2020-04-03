/****************************************************************************
 * ==> PSS_PublishPrestationsReport ----------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will publish the prestations    *
 *               report to html files                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PublishPrestationsReport.h"

// resources
#include "zReportWebRes.h"
#include "PSS_ModelResIDs.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_PublishPrestationsReport
//---------------------------------------------------------------------------
PSS_PublishPrestationsReport::PSS_PublishPrestationsReport(PSS_ProcessGraphModelMdlBP* pModel) :
    m_pRootModel(pModel)
{}
//---------------------------------------------------------------------------
PSS_PublishPrestationsReport::~PSS_PublishPrestationsReport()
{}
//---------------------------------------------------------------------------
bool PSS_PublishPrestationsReport::Publish(const CString& dir)
{
    if (!m_pRootModel)
        return false;

    // create the window to receive the file generation feedback
    m_FileGenerateWindow.Create();

    if (!CreateFileSystem(m_pRootModel->GetMainLogicalPrestations(), dir))
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
bool PSS_PublishPrestationsReport::CreateFileSystem(PSS_LogicalPrestationsEntity* pPrestations, const CString& dir)
{
    if (!pPrestations)
        return false;

    // get the prestation name and description
    const CString prestationName = pPrestations->GetEntityName();
    const CString prestationDesc = pPrestations->GetEntityDescription();

    if (!m_HtmlFile.Create(GenerateFileName(dir, prestationName)))
        return false;

    m_FileGenerateWindow.SetDestination(GenerateFileName(dir, prestationName));
    m_FileGenerateWindow.UpdateWindow();

    GenerateHTMLPageHeader(prestationName);

    GenerateHTMLTableHeader();
    GenerateHTMLReportTitle(prestationName, prestationDesc);
    GenerateHTMLTableFooter();

    GenerateHTMLTableHeader();
    CreateReport(prestationName);
    GenerateHTMLTableFooter();

    GenerateHTMLPageFooter();

    m_HtmlFile.CloseFile();

    // check if the prestation contains children
    if (pPrestations->ContainEntity())
    {
        const int count = pPrestations->GetEntityCount();

        for (int i = 0; i < count; ++i)
        {
            PSS_PrestationsEntity* pEntity = pPrestations->GetEntityAt(i);

            if (!pEntity)
                continue;

            PSS_LogicalPrestationsEntity* pPrestationEntity = dynamic_cast<PSS_LogicalPrestationsEntity*>(pEntity);

            // check if the child object is a logical prestation
            if (pPrestationEntity)
                CreateFileSystem(pPrestationEntity, dir);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_PublishPrestationsReport::CreateReport(const CString& prestationName)
{
    GenerateHTMLSectionTitle();
    ExploreProcessHierarchy(prestationName);
}
//---------------------------------------------------------------------------
void PSS_PublishPrestationsReport::GenerateHTMLPageHeader(const CString& title)
{
    CString output;
    output.Format(IDS_PRESTATIONSREPORT_HTML_1, title);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishPrestationsReport::GenerateHTMLPageFooter()
{
    WriteLine(IDS_PRESTATIONSREPORT_HTML_2);
}
//---------------------------------------------------------------------------
void PSS_PublishPrestationsReport::GenerateHTMLTableHeader()
{
    WriteLine(IDS_PRESTATIONSREPORT_HTML_3);
}
//---------------------------------------------------------------------------
void PSS_PublishPrestationsReport::GenerateHTMLTableFooter()
{
    WriteLine(IDS_PRESTATIONSREPORT_HTML_4);
}
//---------------------------------------------------------------------------
void PSS_PublishPrestationsReport::GenerateHTMLReportTitle(const CString& prestationName, const CString& description)
{
    CString descriptionTitle;
    descriptionTitle.LoadString(IDS_PRESTATIONSREPORT_MTL_HTML_1);

    CString output;
    output.Format(IDS_PRESTATIONSREPORT_HTML_5,
                  prestationName,
                  descriptionTitle,
                  description);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishPrestationsReport::GenerateHTMLSectionTitle()
{
    CString groupNameTitle;
    groupNameTitle.LoadString(IDS_PRESTATIONSREPORT_MTL_HTML_2);

    CString processTitle;
    processTitle.LoadString(IDS_PRESTATIONSREPORT_MTL_HTML_5);

    CString procedureTitle;
    procedureTitle.LoadString(IDS_PRESTATIONSREPORT_MTL_HTML_3);

    CString output;
    output.Format(IDS_PRESTATIONSREPORT_HTML_6, groupNameTitle, processTitle, procedureTitle);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishPrestationsReport::GenerateHTMLSectionLine(const CString& group, const CString& process, const CString& procedure)
{
    CString groupName;

    if (group.IsEmpty())
        groupName.LoadString(IDS_PRESTATIONSREPORT_MTL_HTML_4);
    else
        groupName = group;

    CString processName;

    if (process.IsEmpty())
        processName.LoadString(IDS_PRESTATIONSREPORT_MTL_HTML_4);
    else
        processName = process;

    CString procedureName;

    if (procedure.IsEmpty())
        procedureName.LoadString(IDS_PRESTATIONSREPORT_MTL_HTML_4);
    else
        procedureName = procedure;

    CString output;
    output.Format(IDS_PRESTATIONSREPORT_HTML_7, groupName, processName, procedureName);

    WriteLine(output);
}
//---------------------------------------------------------------------------
CString PSS_PublishPrestationsReport::GenerateFileName(const CString& dir, const CString& prestationName)
{
    CString fileName  = dir;
    fileName         += _T("PrestationsReport_");
    fileName         += PSS_StringTools::ConvertSpecialChar(prestationName);
    fileName         += _T(".htm");

    return fileName;
}
//---------------------------------------------------------------------------
void PSS_PublishPrestationsReport::WriteLine(const CString& text)
{
    if (!text.IsEmpty())
        m_HtmlFile << text;
}
//---------------------------------------------------------------------------
void PSS_PublishPrestationsReport::WriteLine(int id)
{
    CString output;
    output.LoadString(id);

    if (!output.IsEmpty())
        m_HtmlFile << output;
}
//---------------------------------------------------------------------------
void PSS_PublishPrestationsReport::SearchProcedures(const CString& processName, PSS_ProcessGraphModelMdlBP* pStartModel)
{
    if (!pStartModel)
        return;

    // get the pages contained in the model controller
    PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = pStartModel->GetPageSet();

    if (!pSet)
        return;

    PSS_ProcessGraphModelMdl::IProcessGraphPageIterator itPage(pSet);

    // iterate through the children pages contained in the model controller
    for (PSS_ProcessGraphPage* pPage = itPage.GetFirst(); pPage; pPage = itPage.GetNext())
    {
        // get the current page model controller
        PSS_ProcessGraphModelMdlBP* pCurModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

        if (!pCurModel)
            continue;

        // get the symbol set contained in the page
        CODComponentSet* pCompSet = pCurModel->GetComponents();

        if (!pCompSet)
            continue;

        // iterate through the symbols contained in the page
        for (int i = 0; i < pCompSet->GetSize(); ++i)
        {
            PSS_ProcedureSymbolBP* pProcedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pCompSet->GetAt(i));

            if (!pProcedure)
                continue;

            PSS_Properties::IPropertySet propSet;
            pProcedure->FillProperties(propSet);

            PSS_Properties::IPropertyIterator itProp(&propSet);

            // iterate through properties
            for (PSS_Property* pProp = itProp.GetFirst(); pProp; pProp = itProp.GetNext())
                // on new category, create a new section
                if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT && pProp->GetItemID() == M_Unit_Name_ID)
                    GenerateHTMLSectionLine(pProp->GetValueString(), processName, pProcedure->GetSymbolName());

            // iterate through properties and delete them
            for (PSS_Property* pProp = itProp.GetFirst(); pProp; pProp = itProp.GetNext())
                delete pProp;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_PublishPrestationsReport::SearchUnitGroupChildren(PSS_UserGroupEntity* pGroup,
                                                           const CString&       propertyName,
                                                           const CString&       processName,
                                                           const CString&       procedureName,
                                                           BOOL                 childMode,
                                                           int                  childLevel)
{
    if (!pGroup)
        return;

    const CString groupName = pGroup->GetEntityName();

    if (groupName == propertyName || childMode)
        if (childMode)
        {
            CString childGroupName;

            for (int i = 0; i < childLevel; ++i)
                childGroupName += _T("---");

            childGroupName += _T(">");
            childGroupName += groupName;

            GenerateHTMLSectionLine(childGroupName, processName, procedureName);
        }
        else
        {
            GenerateHTMLSectionLine(groupName, processName, procedureName);
            childMode = TRUE;
        }

    // check if the group contains children
    if (pGroup->ContainEntity())
    {
        const int count = pGroup->GetEntityCount();

        for (int i = 0; i < count; ++i)
        {
            PSS_UserGroupEntity* pUserGroupEntity = dynamic_cast<PSS_UserGroupEntity*>(pGroup->GetEntityAt(i));

            if (!pUserGroupEntity)
                continue;

            int childLevelCount = childLevel;

            if (childMode)
                ++childLevelCount;

            SearchUnitGroupChildren(pUserGroupEntity, propertyName, processName, procedureName, childMode, childLevelCount);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_PublishPrestationsReport::ExploreProcessHierarchy(const CString&              prestationName,
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
            PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pCompSet->GetAt(i));

            if (!pProcess)
                continue;

            // get the process child model
            PSS_ProcessGraphModelMdlBP* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pProcess->GetModel());

            // iterate recursively through the child model pages
            if (pChildModel)
                ExploreProcessHierarchy(prestationName, pChildModel);

            PSS_Tokenizer     prestationsList = pProcess->GetPrestationsList();
            const std::size_t tokenCount      = prestationsList.GetTokenCount();

            for (std::size_t j = 0; j < tokenCount; ++j)
            {
                CString processPrestationName;
                prestationsList.GetTokenAt(j, processPrestationName);

                if (processPrestationName == prestationName)
                    SearchProcedures(pProcess->GetSymbolName(), pChildModel);
            }
        }
    }
}
//---------------------------------------------------------------------------
