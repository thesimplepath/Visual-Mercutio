/****************************************************************************
 * ==> PSS_PublishProcessReport --------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will publish the process report *
 *               to html files                                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PublishProcessReport.h"

// processsoft
#include "zBaseLib\PSS_StringFormatter.h"
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
// PSS_PublishProcessReport::ISymbolEntity
//---------------------------------------------------------------------------
PSS_PublishProcessReport::ISymbolEntity::ISymbolEntity() :
    CObject(),
    m_Ref(-1)
{}
//---------------------------------------------------------------------------
PSS_PublishProcessReport::ISymbolEntity::ISymbolEntity(int ref, const CString& name, const CString& description) :
    CObject(),
    m_Name(name),
    m_Description(description),
    m_Ref(ref)
{}
//---------------------------------------------------------------------------
PSS_PublishProcessReport::ISymbolEntity::~ISymbolEntity()
{}
//---------------------------------------------------------------------------
int PSS_PublishProcessReport::ISymbolEntity::GetRef() const
{
    return m_Ref;
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::ISymbolEntity::SetRef(int ref)
{
    m_Ref = ref;
}
//---------------------------------------------------------------------------
CString PSS_PublishProcessReport::ISymbolEntity::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::ISymbolEntity::SetName(const CString& name)
{
    m_Name = name;
}
//---------------------------------------------------------------------------
CString PSS_PublishProcessReport::ISymbolEntity::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::ISymbolEntity::SetDescription(const CString& description)
{
    m_Description = description;
}
//---------------------------------------------------------------------------
// PSS_PublishProcessReport::ISymbolContainer
//---------------------------------------------------------------------------
PSS_PublishProcessReport::ISymbolContainer::ISymbolContainer() :
    m_pPos(NULL)
{}
//---------------------------------------------------------------------------
PSS_PublishProcessReport::ISymbolContainer::~ISymbolContainer()
{}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::ISymbolContainer::AddSymbol(ISymbolEntity* pSymbolEntity)
{
    m_pPos = m_SymbolList.AddTail(pSymbolEntity);
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::ISymbolContainer::RemoveAll()
{
    POSITION pPos = GetHeadPosition();

    while (pPos)
    {
        ISymbolEntity* pSymbol = dynamic_cast<ISymbolEntity*>(m_SymbolList.GetAt(pPos));

        if (pSymbol)
            delete pSymbol;

        GetNextPosition();

        m_SymbolList.RemoveAt(pPos);

        pPos = m_pPos;
    }
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::ISymbolContainer::Sort()
{
    POSITION pCurPos  = GetHeadPosition();
    POSITION pNextPos = pCurPos;

    while (pCurPos)
    {
        m_SymbolList.GetNext(pNextPos);

        ISymbolEntity* pCurSymbol  = dynamic_cast<ISymbolEntity*>(m_SymbolList.GetAt(pCurPos));
        ISymbolEntity* pNextSymbol = NULL;

        if (pNextPos)
            pNextSymbol = dynamic_cast<ISymbolEntity*>(m_SymbolList.GetAt(pNextPos));

        if (pCurSymbol && pNextSymbol)
        {
            // swap the symbols if the current symbol reference number is greater than the next one
            if (Trim(pCurSymbol->GetName()).Collate(Trim(pNextSymbol->GetName())) > 0)
            {
                m_SymbolList.SetAt(pCurPos,  pNextSymbol);
                m_SymbolList.SetAt(pNextPos, pCurSymbol);

                // recursively sort the symbols until all the symbols are sorted as expected
                Sort();
                return;
            }
        }

        pCurPos = pNextPos;
    }
}
//---------------------------------------------------------------------------
PSS_PublishProcessReport::ISymbolEntity* PSS_PublishProcessReport::ISymbolContainer::GetAt(POSITION pPos)
{
    if (pPos)
        return dynamic_cast<ISymbolEntity*>(m_SymbolList.GetAt(pPos));

    return NULL;
}
//---------------------------------------------------------------------------
POSITION PSS_PublishProcessReport::ISymbolContainer::GetHeadPosition()
{
    m_pPos = m_SymbolList.GetHeadPosition();
    return m_pPos;
}
//---------------------------------------------------------------------------
POSITION PSS_PublishProcessReport::ISymbolContainer::GetTailPosition()
{
    m_pPos = m_SymbolList.GetTailPosition();
    return m_pPos;
}
//---------------------------------------------------------------------------
POSITION PSS_PublishProcessReport::ISymbolContainer::GetPrevPosition()
{
    if (m_pPos)
        m_SymbolList.GetPrev(m_pPos);

    return m_pPos;
}
//---------------------------------------------------------------------------
POSITION PSS_PublishProcessReport::ISymbolContainer::GetNextPosition()
{
    if (m_pPos)
        m_SymbolList.GetNext(m_pPos);

    return m_pPos;
}
//---------------------------------------------------------------------------
CString PSS_PublishProcessReport::ISymbolContainer::Trim(const CString& str) const
{
    CString output;
    int     i                   = 0;
    BOOL    firstCharIsNotEmpty = FALSE;
    BOOL    doTestNextChar      = FALSE;

    while (i < str.GetLength())
    {
        // remove all empty chars before the first char
        if (!firstCharIsNotEmpty)
        {
            if (str.GetAt(i) != _T(' '))
            {
                output              += str.GetAt(i);
                firstCharIsNotEmpty  = TRUE;
            }
        }
        else
        if (!doTestNextChar)
        {
            output += str.GetAt(i);

            // if an empty string is found, check if the following is also empty, if true, remove it
            if (str.GetAt(i) == _T(' '))
                doTestNextChar = TRUE;
        }
        else
        if (str.GetAt(i) != _T(' '))
        {
            output         += str.GetAt(i);
            doTestNextChar  = FALSE;
        }

        ++i;
    }

    return output;
}
//---------------------------------------------------------------------------
// PSS_PublishProcessReport
//---------------------------------------------------------------------------
PSS_PublishProcessReport::PSS_PublishProcessReport(PSS_ProcessGraphModelMdlBP* pModel, PSS_PropertyAttributes* pPropAttributes) :
    m_pPropAttributes(pPropAttributes),
    m_pRootModel(pModel)
{}
//---------------------------------------------------------------------------
PSS_PublishProcessReport::~PSS_PublishProcessReport()
{
    ResetData();
}
//---------------------------------------------------------------------------
bool PSS_PublishProcessReport::Publish(const CString& dir)
{
    if (!m_pRootModel)
        return false;

    // create the window to receive the file generation feedback
    m_FileGenerateWindow.Create();

    if (!CreateFileSystem(dir))
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
bool PSS_PublishProcessReport::CreateFileSystem(const CString& dir, PSS_ProcessGraphModelMdlBP* pStartRootModel)
{
    // if no root model, the exploration should be performed on the whole document
    if (!pStartRootModel)
        // get the document model controller
        pStartRootModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pRootModel);

    if (!pStartRootModel)
        return true;

    // get the pages contained in the model controller
    PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = pStartRootModel->GetPageSet();

    if (!pSet)
        return true;

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

        const int compCount = pCompSet->GetSize();

        // iterate through the symbols contained in the page model controller
        for (int i = 0; i < compCount; ++i)
        {
            PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pCompSet->GetAt(i));

            if (!pProcess)
                continue;

            PSS_ProcessGraphModelMdlBP* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pProcess->GetModel());

            if (pChildModel)
                CreateFileSystem(dir, pChildModel);

            ResetData();

            const CString processName = pProcess->GetSymbolName();

            if (!m_HtmlFile.Create(GenerateFileName(dir, processName)))
                return false;

            m_FileGenerateWindow.SetDestination(GenerateFileName(dir, processName));
            m_FileGenerateWindow.UpdateWindow();

            GenerateHTMLPageHeader(processName);

            PSS_ProcessGraphModelMdl* pOwnerModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pProcess->GetOwnerModel());
            PSS_ProcessGraphPage*     pPage       = m_pRootModel->FindModelPage(pOwnerModel, true);
            CString                   domainName;

            if (pPage)
                domainName = pPage->GetPageName();
            else
                domainName.LoadString(IDS_REPORTWEB_NOTFOUND);

            GenerateHTMLReportTitle(domainName, processName);
            GenerateHTMLTableHeader();
            CreateReport(pProcess);
            GenerateHTMLPageFooter();
            m_HtmlFile.CloseFile();
        }
    }

    return true;
}
//---------------------------------------------------------------------------
PSS_Symbol* PSS_PublishProcessReport::SearchSymbol(const CString& symbolName, PSS_ProcessGraphModelMdlBP* pStartRootModel)
{
    if (symbolName.IsEmpty())
        return NULL;

    // if no root model, the exploration should be performed on the whole document
    if (!pStartRootModel)
        // get the document model controller
        pStartRootModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pRootModel);

    if (!pStartRootModel)
        return NULL;

    // get the pages contained in the model controller
    PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = pStartRootModel->GetPageSet();

    if (!pSet)
        return NULL;

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

        const int compCount = pCompSet->GetSize();

        // iterate through the symbols contained in the page model controller
        for (int i = 0; i < compCount; ++i)
        {
            CODComponent* pComponent = pCompSet->GetAt(i);

            if (!pComponent)
                continue;

            PSS_ProcedureSymbolBP* pProcedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pComponent);

            if (pProcedure && pProcedure->GetSymbolName() == symbolName && pProcedure->IsLocal())
                return pProcedure;

            PSS_StartSymbolBP* pStart = dynamic_cast<PSS_StartSymbolBP*>(pComponent);

            if (pStart &&  pStart->GetSymbolName() == symbolName && pStart->IsLocal())
                return pStart;

            PSS_StopSymbolBP* pStop = dynamic_cast<PSS_StopSymbolBP*>(pComponent);

            if (pStop && pStop->IsLocal() && pStop->GetSymbolName() == symbolName)
                return pStop;

            PSS_DoorSymbolBP* pDoor = dynamic_cast<PSS_DoorSymbolBP*>(pComponent);

            if (pDoor && pDoor->IsLocal() && pDoor->GetSymbolName() == symbolName)
                return pDoor;

            PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pComponent);

            if (pProcess)
            {
                PSS_Symbol* pResult = NULL;

                // get the process model controller
                PSS_ProcessGraphModelMdlBP* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pProcess->GetModel());

                // search the symbol recursively, until each the children process pages were visited,
                // or the original symbol was found
                pResult = SearchSymbol(symbolName, pChildModel);

                // if no result, the original symbol may be in another page set, so continue to search
                if (pResult)
                    return pResult;
            }
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_LinkSymbol* PSS_PublishProcessReport::SearchLinkSymbol(const CString& symbolName, PSS_ProcessGraphModelMdlBP* pStartRootModel)
{
    if (symbolName.IsEmpty())
        return NULL;

    // if no root model, the exploration should be performed on the whole document
    if (!pStartRootModel)
        // get the document model controller
        pStartRootModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pRootModel);

    if (!pStartRootModel)
        return NULL;

    // get the pages contained in the model controller
    PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = pStartRootModel->GetPageSet();

    if (!pSet)
        return NULL;

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

        const int compCount = pCompSet->GetSize();

        // iterate through the symbols contained in the page model controller
        for (int i = 0; i < compCount; ++i)
        {
            CODComponent* pComponent = pCompSet->GetAt(i);

            if (!pComponent)
                continue;

            PSS_DeliverableLinkSymbolBP* pDeliverable = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pComponent);

            if (pDeliverable && pDeliverable->IsLocal() &&  pDeliverable->GetSymbolName() == symbolName)
                return pDeliverable;

            PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pComponent);

            if (pProcess)
            {
                PSS_LinkSymbol* pResult = NULL;

                // get the process child model
                PSS_ProcessGraphModelMdlBP* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pProcess->GetModel());

                // search the symbol recursively, until each the children process pages were visited,
                // or the original symbol was found
                pResult = SearchLinkSymbol(symbolName, pChildModel);

                // if no result, the original symbol may be in another page set, so continue to search
                if (pResult)
                    return pResult;
            }
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::CreateReport(PSS_ProcessSymbolBP* pProcessSymbol)
{
    CString output;

    PSS_ProcessGraphModelMdlBP* pChildModel = NULL;

    if (pProcessSymbol)
    {
        PSS_Properties::IPropertySet propSet;
        pProcessSymbol->FillProperties(propSet);

        GenerateSection(propSet);

        PSS_Properties::IPropertyIterator it(&propSet);

        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
            delete pProp;

        pChildModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pProcessSymbol->GetModel());
    }

    GenerateHTMLTableFooter();

    if (pChildModel)
    {
        // get the pages contained in the model controller
        PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = pChildModel->GetPageSet();

        if (pSet)
        {
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

                const int compCount = pCompSet->GetSize();

                // iterate through the symbols contained in the page model controller
                for (int i = 0; i < compCount; ++i)
                {
                    CODComponent* pComponent = pCompSet->GetAt(i);

                    if (!pComponent)
                        continue;

                    PSS_ProcedureSymbolBP* pProcedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pComponent);

                    if (pProcedure)
                    {
                        std::unique_ptr<ISymbolEntity> pSymEntity(new ISymbolEntity(pProcedure->GetSymbolReferenceNumber(),
                                                                                    pProcedure->GetSymbolName(),
                                                                                    pProcedure->GetSymbolComment()));

                        m_ProcedureContainer.AddSymbol(pSymEntity.get());
                        pSymEntity.release();
                    }

                    PSS_StartSymbolBP* pStart = dynamic_cast<PSS_StartSymbolBP*>(pComponent);

                    if (pStart)
                    {
                        std::unique_ptr<ISymbolEntity> pSymEntity (new ISymbolEntity(pStart->GetSymbolReferenceNumber(),
                                                                                     pStart->GetSymbolName(),
                                                                                     pStart->GetSymbolComment()));

                        m_StartContainer.AddSymbol(pSymEntity.get());
                        pSymEntity.release();
                    }

                    PSS_StopSymbolBP* pStop = dynamic_cast<PSS_StopSymbolBP*>(pComponent);

                    if (pStop)
                    {
                        std::unique_ptr<ISymbolEntity> pSymEntity(new ISymbolEntity(pStop->GetSymbolReferenceNumber(),
                                                                                    pStop->GetSymbolName(),
                                                                                    pStop->GetSymbolComment()));

                        m_StopContainer.AddSymbol(pSymEntity.get());
                        pSymEntity.release();
                    }

                    PSS_DoorSymbolBP* pDoor = dynamic_cast<PSS_DoorSymbolBP*>(pComponent);

                    if (pDoor)
                    {
                        std::unique_ptr<ISymbolEntity> pSymEntity(new ISymbolEntity(pDoor->GetSymbolReferenceNumber(),
                                                                                    pDoor->GetSymbolName(),
                                                                                    pDoor->GetSymbolComment()));

                        m_DoorContainer.AddSymbol(pSymEntity.get());
                        pSymEntity.release();
                    }
                }
            }
        }
    }

    m_StartContainer.Sort();
    m_StopContainer.Sort();
    m_ProcedureContainer.Sort();
    m_DoorContainer.Sort();

    POSITION pPos = m_StartContainer.GetHeadPosition();

    // create the separation between paragraphs
    if (pPos)
    {
        GenerateSeparation();
        GenerateBlackLine();
    }

    while (pPos)
    {
        ISymbolEntity* pCurNode = m_StartContainer.GetAt(pPos);

        if (!pCurNode)
        {
            pPos = m_StartContainer.GetNextPosition();
            continue;
        }

        CString objType;
        objType.LoadString(IDS_OBJECTTYPE_START);

        GenerateHTMLSymbolTitle(pCurNode->GetRef(),
                                pCurNode->GetName(),
                                objType,
                                RGB(0, 255, 0));

        PSS_StartSymbolBP* pStartSymbol = dynamic_cast<PSS_StartSymbolBP*>(SearchSymbol(pCurNode->GetName()));

        if (pStartSymbol)
        {
            PSS_Properties::IPropertySet propSet;
            pStartSymbol->FillProperties(propSet);

            GenerateSection(propSet);

            PSS_Properties::IPropertyIterator it(&propSet);

            for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                delete pProp;
        }

        GenerateHTMLTableFooter();

        if (pStartSymbol)
        {
            ISymbolContainer deliverableContainer;
            CODEdgeArray     edges;

            // get the output deliverables
            if (pStartSymbol->GetEdgesLeaving(edges) > 0)
            {
                // add the separator for the paragraph
                GenerateSeparation();
                GenerateHTMLTableHeader();

                output.LoadString(IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_4);
                GenerateHTMLSectionTitle(output);

                GenerateHTMLTableFooter();

                const int edgeCount = edges.GetSize();

                for (int i = 0; i < edgeCount; ++i)
                {
                    IODEdge*                     pIEdge = edges.GetAt(i);
                    PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pComp)
                        continue;

                    std::unique_ptr<ISymbolEntity> pDeliverableEntity(new ISymbolEntity(0, pComp->GetSymbolName(), _T("")));

                    deliverableContainer.AddSymbol(pDeliverableEntity.get());
                    pDeliverableEntity.release();
                }

                deliverableContainer.Sort();

                POSITION pDelivPos = deliverableContainer.GetHeadPosition();

                while (pDelivPos)
                {
                    ISymbolEntity* pDelivCurNode = deliverableContainer.GetAt(pDelivPos);

                    PSS_DeliverableLinkSymbolBP* pLinkSymbol =
                            dynamic_cast<PSS_DeliverableLinkSymbolBP*>(SearchLinkSymbol(pDelivCurNode->GetName()));

                    if (pLinkSymbol)
                    {
                        CString objType;
                        objType.LoadString(IDS_OBJECTTYPE_DELIVERABLE);

                        GenerateHTMLSymbolTitle(pLinkSymbol->GetSymbolReferenceNumber(),
                                                pLinkSymbol->GetSymbolName(),
                                                objType,
                                                RGB(162, 221, 198));

                        PSS_Properties::IPropertySet propSet;
                        pLinkSymbol->FillProperties(propSet);

                        GenerateSection(propSet);

                        PSS_Properties::IPropertyIterator it(&propSet);

                        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                            delete pProp;

                        GenerateHTMLTableFooter();
                    }

                    pDelivPos = deliverableContainer.GetNextPosition();
                }

                deliverableContainer.RemoveAll();
            }

            GenerateSeparation();
        }

        pPos = m_StartContainer.GetNextPosition();
    }

    pPos = m_DoorContainer.GetHeadPosition();

    // add the paragraph separator
    if (pPos)
        GenerateBlackLine();

    while (pPos)
    {
        ISymbolEntity* pCurNode = m_DoorContainer.GetAt(pPos);

        if (!pCurNode)
        {
            pPos = m_DoorContainer.GetNextPosition();
            continue;
        }

        PSS_DoorSymbolBP* pDoorSymbol = dynamic_cast<PSS_DoorSymbolBP*>(SearchSymbol(pCurNode->GetName()));

        if (pDoorSymbol)
        {
            // add the door symbol in the report only if it contains a deliverable
            CODEdgeArray edges;

            // get the output deliverable
            if (pDoorSymbol->GetEdgesLeaving(edges) > 0)
            {
                CString objType;
                objType.LoadString(IDS_OBJECTTYPE_DOOR);

                GenerateHTMLSymbolTitle(pCurNode->GetRef(),
                                        pCurNode->GetName(),
                                        objType,
                                        RGB(155, 255, 155));

                PSS_Properties::IPropertySet propSet;
                pDoorSymbol->FillProperties(propSet);

                GenerateSection(propSet);

                PSS_Properties::IPropertyIterator it(&propSet);

                for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                    delete pProp;

                GenerateHTMLTableFooter();

                // the section title should appear only if a deliverable exists
                if (edges.GetSize() > 0)
                {
                    // add the paragraph separator line
                    GenerateSeparation();
                    GenerateHTMLTableHeader();

                    output.LoadString(IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_4);
                    GenerateHTMLSectionTitle(output);

                    GenerateHTMLTableFooter();
                }

                const int edgeCount = edges.GetSize();

                for (int i = 0; i < edgeCount; ++i)
                {
                    IODEdge*                     pIEdge = edges.GetAt(i);
                    PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pComp)
                        continue;

                    PSS_DeliverableLinkSymbolBP* pLinkSymbol =
                            dynamic_cast<PSS_DeliverableLinkSymbolBP*>(SearchLinkSymbol(pComp->GetSymbolName()));

                    if (pLinkSymbol)
                    {
                        CString objType;
                        objType.LoadString(IDS_OBJECTTYPE_DELIVERABLE);

                        GenerateHTMLSymbolTitle(pLinkSymbol->GetSymbolReferenceNumber(),
                                                pLinkSymbol->GetSymbolName(),
                                                objType,
                                                RGB(162, 221, 198));

                        PSS_Properties::IPropertySet propSet;
                        pLinkSymbol->FillProperties(propSet);

                        GenerateSection(propSet);

                        PSS_Properties::IPropertyIterator it(&propSet);

                        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                            delete pProp;

                        GenerateHTMLTableFooter();
                    }
                }

                GenerateSeparation();
            }
        }

        pPos = m_DoorContainer.GetNextPosition();
    }

    pPos = m_ProcedureContainer.GetHeadPosition();

    while (pPos != NULL)
    {
        // add the paragraph separator
        GenerateBlackLine();

        ISymbolEntity* pCurNode = m_ProcedureContainer.GetAt(pPos);

        if (!pCurNode)
        {
            pPos = m_ProcedureContainer.GetNextPosition();
            continue;
        }

        CString objType;
        objType.LoadString(IDS_OBJECTTYPE_PROCEDURE);

        GenerateHTMLSymbolTitle(pCurNode->GetRef(),
                                pCurNode->GetName(),
                                objType,
                                RGB(192, 192, 192));

        PSS_ProcedureSymbolBP* pProcedureSymbol = dynamic_cast<PSS_ProcedureSymbolBP*>(SearchSymbol(pCurNode->GetName()));

        if (pProcedureSymbol)
        {
            PSS_Properties::IPropertySet propSet;
            pProcedureSymbol->FillProperties(propSet);

            GenerateSection(propSet);

            PSS_Properties::IPropertyIterator it(&propSet);

            for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                delete pProp;
        }

        GenerateHTMLTableFooter();

        if (pProcedureSymbol)
        {
            CODEdgeArray     edges;
            ISymbolContainer deliverableContainer;

            // get all the symbol entering up deliverables
            if (pProcedureSymbol->GetEnteringUpDeliverable(edges) > 0)
            {
                // add the paragraph separator
                GenerateSeparation();
                GenerateHTMLTableHeader();

                output.LoadString(IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_1);
                GenerateHTMLSectionTitle(output);

                GenerateHTMLTableFooter();

                const int edgeCount = edges.GetSize();

                for (int i = 0; i < edgeCount; ++i)
                {
                    IODEdge*                     pIEdge = edges.GetAt(i);
                    PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pComp)
                        continue;

                    std::unique_ptr<ISymbolEntity> pDeliverableEntity(new ISymbolEntity(0, pComp->GetSymbolName(), _T("")));

                    deliverableContainer.AddSymbol(pDeliverableEntity.get());
                    pDeliverableEntity.release();
                }

                deliverableContainer.Sort();

                POSITION pDelivPos = deliverableContainer.GetHeadPosition();

                while (pDelivPos)
                {
                    ISymbolEntity* pDelivCurNode = deliverableContainer.GetAt(pDelivPos);

                    if (!pDelivCurNode)
                    {
                        pDelivPos = deliverableContainer.GetNextPosition();
                        continue;
                    }

                    PSS_DeliverableLinkSymbolBP* pLinkSymbol =
                            dynamic_cast<PSS_DeliverableLinkSymbolBP*>(SearchLinkSymbol(pDelivCurNode->GetName()));

                    if (pLinkSymbol)
                    {
                        CString objType = _T("");
                        objType.LoadString(IDS_OBJECTTYPE_DELIVERABLE);

                        GenerateHTMLSymbolTitle(pLinkSymbol->GetSymbolReferenceNumber(),
                                                pLinkSymbol->GetSymbolName(),
                                                objType,
                                                RGB(162, 221, 198));

                        PSS_Properties::IPropertySet propSet;
                        pLinkSymbol->FillProperties(propSet);

                        GenerateSection(propSet);

                        PSS_Properties::IPropertyIterator it(&propSet);

                        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                            delete pProp;

                        GenerateHTMLTableFooter();
                    }

                    pDelivPos = deliverableContainer.GetNextPosition();
                }

                deliverableContainer.RemoveAll();
            }

            // get all the leaving right edges deliverables
            if (pProcedureSymbol->GetEdgesLeaving_Right(edges) > 0)
            {
                // add the paragraph separator
                GenerateSeparation();
                GenerateHTMLTableHeader();

                output.LoadString(IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_2);
                GenerateHTMLSectionTitle(output);

                GenerateHTMLTableFooter();

                const int edgeCount = edges.GetSize();

                for (int i = 0; i < edgeCount; ++i)
                {
                    IODEdge*                     pIEdge = edges.GetAt(i);
                    PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pComp)
                        continue;

                    std::unique_ptr<ISymbolEntity> pDeliverableEntity(new ISymbolEntity(0, pComp->GetSymbolName(), _T("")));

                    deliverableContainer.AddSymbol(pDeliverableEntity.get());
                    pDeliverableEntity.release();
                }

                deliverableContainer.Sort();

                POSITION pDelivPos = deliverableContainer.GetHeadPosition();

                while (pDelivPos)
                {
                    ISymbolEntity* pDelivCurNode = deliverableContainer.GetAt(pDelivPos);

                    if (!pDelivCurNode)
                    {
                        pDelivPos = deliverableContainer.GetNextPosition();
                        continue;
                    }

                    PSS_DeliverableLinkSymbolBP* pLinkSymbol =
                            dynamic_cast<PSS_DeliverableLinkSymbolBP*>(SearchLinkSymbol(pDelivCurNode->GetName()));

                    if (pLinkSymbol)
                    {
                        CString objType = _T("");
                        objType.LoadString(IDS_OBJECTTYPE_DELIVERABLE);

                        GenerateHTMLSymbolTitle(pLinkSymbol->GetSymbolReferenceNumber(),
                                                pLinkSymbol->GetSymbolName(),
                                                objType,
                                                RGB(162, 221, 198));

                        PSS_Properties::IPropertySet propSet;
                        pLinkSymbol->FillProperties(propSet);

                        GenerateSection(propSet);

                        PSS_Properties::IPropertyIterator it(&propSet);

                        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                            delete pProp;

                        GenerateHTMLTableFooter();
                    }

                    pDelivPos = deliverableContainer.GetNextPosition();
                }

                deliverableContainer.RemoveAll();
            }

            // get all the leaving left edges deliverables
            if (pProcedureSymbol->GetEdgesLeaving_Left(edges) > 0)
            {
                const int edgeCount = edges.GetSize();

                for (int i = 0; i < edgeCount; ++i)
                {
                    IODEdge*                     pIEdge = edges.GetAt(i);
                    PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pComp)
                        continue;

                    std::unique_ptr<ISymbolEntity> pDeliverableEntity(new ISymbolEntity(0, pComp->GetSymbolName(), _T("")));

                    deliverableContainer.AddSymbol(pDeliverableEntity.get());
                    pDeliverableEntity.release();
                }

                deliverableContainer.Sort();

                POSITION pDelivPos = deliverableContainer.GetHeadPosition();

                while (pDelivPos)
                {
                    ISymbolEntity* pDelivCurNode = deliverableContainer.GetAt(pDelivPos);

                    if (!pDelivCurNode)
                    {
                        pDelivPos = deliverableContainer.GetNextPosition();
                        continue;
                    }

                    PSS_DeliverableLinkSymbolBP* pLinkSymbol =
                            dynamic_cast<PSS_DeliverableLinkSymbolBP*>(SearchLinkSymbol(pDelivCurNode->GetName()));

                    if (pLinkSymbol)
                    {
                        CString objType;
                        objType.LoadString(IDS_OBJECTTYPE_DELIVERABLE);

                        GenerateHTMLSymbolTitle(pLinkSymbol->GetSymbolReferenceNumber(),
                                                pLinkSymbol->GetSymbolName(),
                                                objType,
                                                RGB(162, 221, 198));

                        PSS_Properties::IPropertySet propSet;
                        pLinkSymbol->FillProperties(propSet);

                        GenerateSection(propSet);

                        PSS_Properties::IPropertyIterator it(&propSet);

                        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                            delete pProp;

                        GenerateHTMLTableFooter();
                    }

                    pDelivPos = deliverableContainer.GetNextPosition();
                }

                deliverableContainer.RemoveAll();
            }

            // get all the entering right edges deliverables
            if (pProcedureSymbol->GetEdgesEntering_Right(edges) > 0)
            {
                // add the paragraph separator
                GenerateSeparation();
                GenerateHTMLTableHeader();

                output.LoadString(IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_3);
                GenerateHTMLSectionTitle(output);

                GenerateHTMLTableFooter();

                const int edgeCount = edges.GetSize();

                for (int i = 0; i < edgeCount; ++i)
                {
                    IODEdge*                     pIEdge = edges.GetAt(i);
                    PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pComp)
                        continue;

                    std::unique_ptr<ISymbolEntity> pDeliverableEntity(new ISymbolEntity(0, pComp->GetSymbolName(), _T("")));

                    deliverableContainer.AddSymbol(pDeliverableEntity.get());
                    pDeliverableEntity.release();
                }

                deliverableContainer.Sort();

                POSITION pDelivPos = deliverableContainer.GetHeadPosition();

                while (pDelivPos)
                {
                    ISymbolEntity* pDelivCurNode = deliverableContainer.GetAt(pDelivPos);

                    if (!pDelivCurNode)
                    {
                        pDelivPos = deliverableContainer.GetNextPosition();
                        continue;
                    }

                    PSS_DeliverableLinkSymbolBP* pLinkSymbol =
                            dynamic_cast<PSS_DeliverableLinkSymbolBP*>(SearchLinkSymbol(pDelivCurNode->GetName()));

                    if (pLinkSymbol)
                    {
                        CString objType;
                        objType.LoadString(IDS_OBJECTTYPE_DELIVERABLE);

                        GenerateHTMLSymbolTitle(pLinkSymbol->GetSymbolReferenceNumber(),
                                                pLinkSymbol->GetSymbolName(),
                                                objType,
                                                RGB(162, 221, 198));

                        PSS_Properties::IPropertySet propSet;
                        pLinkSymbol->FillProperties(propSet);

                        GenerateSection(propSet);

                        PSS_Properties::IPropertyIterator it(&propSet);

                        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                            delete pProp;

                        GenerateHTMLTableFooter();
                    }

                    pDelivPos = deliverableContainer.GetNextPosition();
                }

                deliverableContainer.RemoveAll();
            }

            // get all the entering left edges deliverables
            if (pProcedureSymbol->GetEdgesEntering_Left(edges) > 0)
            {
                const int edgeCount = edges.GetSize();

                for (int i = 0; i < edgeCount; ++i)
                {
                    IODEdge*                     pIEdge = edges.GetAt(i);
                    PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pComp)
                        continue;

                    std::unique_ptr<ISymbolEntity> pDeliverableEntity(new ISymbolEntity(0, pComp->GetSymbolName(), _T("")));

                    deliverableContainer.AddSymbol(pDeliverableEntity.get());
                    pDeliverableEntity.release();
                }

                deliverableContainer.Sort();

                POSITION pDelivPos = deliverableContainer.GetHeadPosition();

                while (pDelivPos)
                {
                    ISymbolEntity* pDelivCurNode = deliverableContainer.GetAt(pDelivPos);

                    if (!pDelivCurNode)
                    {
                        pDelivPos = deliverableContainer.GetNextPosition();
                        continue;
                    }

                    PSS_DeliverableLinkSymbolBP* pLinkSymbol =
                            dynamic_cast<PSS_DeliverableLinkSymbolBP*>(SearchLinkSymbol(pDelivCurNode->GetName()));

                    if (pLinkSymbol)
                    {
                        CString objType;
                        objType.LoadString(IDS_OBJECTTYPE_DELIVERABLE);

                        GenerateHTMLSymbolTitle(pLinkSymbol->GetSymbolReferenceNumber(),
                                                pLinkSymbol->GetSymbolName(),
                                                objType,
                                                RGB(162, 221, 198));

                        PSS_Properties::IPropertySet propSet;
                        pLinkSymbol->FillProperties(propSet);

                        GenerateSection(propSet);

                        PSS_Properties::IPropertyIterator it(&propSet);

                        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                            delete pProp;

                        GenerateHTMLTableFooter();
                    }

                    pDelivPos = deliverableContainer.GetNextPosition();
                }

                deliverableContainer.RemoveAll();
            }

            // get all the leaving down edges deliverables
            if (pProcedureSymbol->GetEdgesLeaving_Down(edges) > 0)
            {
                // add the paragraph separator
                GenerateSeparation();
                GenerateHTMLTableHeader();

                output.LoadString(IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_4);
                GenerateHTMLSectionTitle(output);

                GenerateHTMLTableFooter();

                const int edgeCount = edges.GetSize();

                for (int i = 0; i < edgeCount; ++i)
                {
                    IODEdge*                     pIEdge = edges.GetAt(i);
                    PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pComp)
                        continue;

                    std::unique_ptr<ISymbolEntity> pDeliverableEntity(new ISymbolEntity(0, pComp->GetSymbolName(), _T("")));

                    deliverableContainer.AddSymbol(pDeliverableEntity.get());
                    pDeliverableEntity.release();
                }

                deliverableContainer.Sort();

                POSITION pDelivPos = deliverableContainer.GetHeadPosition();

                while (pDelivPos)
                {
                    ISymbolEntity* pDelivCurNode = deliverableContainer.GetAt(pDelivPos);

                    if (!pDelivCurNode)
                    {
                        pDelivPos = deliverableContainer.GetNextPosition();
                        continue;
                    }

                    PSS_DeliverableLinkSymbolBP* pLinkSymbol =
                            dynamic_cast<PSS_DeliverableLinkSymbolBP*>(SearchLinkSymbol(pDelivCurNode->GetName()));

                    if (pLinkSymbol)
                    {
                        CString objType;
                        objType.LoadString(IDS_OBJECTTYPE_DELIVERABLE);

                        GenerateHTMLSymbolTitle(pLinkSymbol->GetSymbolReferenceNumber(),
                                                pLinkSymbol->GetSymbolName(),
                                                objType,
                                                RGB(162, 221, 198));

                        PSS_Properties::IPropertySet propSet;
                        pLinkSymbol->FillProperties(propSet);

                        GenerateSection(propSet);

                        PSS_Properties::IPropertyIterator it(&propSet);

                        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                            delete pProp;

                        GenerateHTMLTableFooter();
                    }

                    pDelivPos = deliverableContainer.GetNextPosition();
                }

                deliverableContainer.RemoveAll();
            }

            GenerateSeparation();
        }

        pPos = m_ProcedureContainer.GetNextPosition();
    }

    pPos = m_DoorContainer.GetHeadPosition();

    // add the paragraph separator
    if (pPos)
        GenerateBlackLine();

    while (pPos)
    {
        ISymbolEntity* pCurNode = m_DoorContainer.GetAt(pPos);

        if (!pCurNode)
        {
            pPos = m_DoorContainer.GetNextPosition();
            continue;
        }

        PSS_DoorSymbolBP* pDoorSymbol = dynamic_cast<PSS_DoorSymbolBP*>(SearchSymbol(pCurNode->GetName()));

        if (pDoorSymbol)
        {
            // add the door symbol to the report only if it contains a deliverale
            CODEdgeArray edges;

            // get the entering edge deliverables
            if (pDoorSymbol->GetEdgesEntering(edges) > 0)
            {
                CString objType;
                objType.LoadString(IDS_OBJECTTYPE_DOOR);

                GenerateHTMLSymbolTitle(pCurNode->GetRef(),
                                        pCurNode->GetName(),
                                        objType,
                                        RGB(255, 155, 155));

                PSS_Properties::IPropertySet propSet;
                pDoorSymbol->FillProperties(propSet);

                GenerateSection(propSet);

                PSS_Properties::IPropertyIterator it(&propSet);

                for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                    delete pProp;

                GenerateHTMLTableFooter();

                if (edges.GetSize() > 0)
                {
                    // add the paragraph separator
                    GenerateSeparation();
                    GenerateHTMLTableHeader();

                    output.LoadString(IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_4);
                    GenerateHTMLSectionTitle(output);

                    GenerateHTMLTableFooter();
                }

                const int edgeCount = edges.GetSize();

                for (int i = 0; i < edgeCount; ++i)
                {
                    IODEdge*                     pIEdge = edges.GetAt(i);
                    PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pComp)
                        continue;

                    PSS_DeliverableLinkSymbolBP* pLinkSymbol =
                            dynamic_cast<PSS_DeliverableLinkSymbolBP*>(SearchLinkSymbol(pComp->GetSymbolName()));

                    if (pLinkSymbol)
                    {
                        CString objType;
                        objType.LoadString(IDS_OBJECTTYPE_DELIVERABLE);

                        GenerateHTMLSymbolTitle(pLinkSymbol->GetSymbolReferenceNumber(),
                                                pLinkSymbol->GetSymbolName(),
                                                objType,
                                                RGB(162, 221, 198));

                        PSS_Properties::IPropertySet propSet;
                        pLinkSymbol->FillProperties(propSet);

                        GenerateSection(propSet);

                        PSS_Properties::IPropertyIterator it(&propSet);

                        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                            delete pProp;

                        GenerateHTMLTableFooter();
                    }
                }

                GenerateSeparation();
            }
        }

        pPos = m_DoorContainer.GetNextPosition();
    }

    pPos = m_StopContainer.GetHeadPosition();

    // add the paragraph separator
    if (pPos)
        GenerateBlackLine();

    while (pPos)
    {
        ISymbolEntity* pCurNode = m_StopContainer.GetAt(pPos);

        if (!pCurNode)
        {
            pPos = m_StopContainer.GetNextPosition();
            continue;
        }

        CString objType;
        objType.LoadString(IDS_OBJECTTYPE_STOP);

        GenerateHTMLSymbolTitle(pCurNode->GetRef(),
                                pCurNode->GetName(),
                                objType,
                                RGB(255, 0, 0));

        PSS_StopSymbolBP* pStopSymbol = dynamic_cast<PSS_StopSymbolBP*>(SearchSymbol(pCurNode->GetName()));

        if (pStopSymbol)
        {
            PSS_Properties::IPropertySet propSet;
            pStopSymbol->FillProperties(propSet);

            GenerateSection(propSet);

            PSS_Properties::IPropertyIterator it(&propSet);

            for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                delete pProp;
        }

        GenerateHTMLTableFooter();

        if (pStopSymbol)
        {
            CODEdgeArray     edges;
            ISymbolContainer deliverableContainer;

            // get all the entering edges deliverables
            if (pStopSymbol->GetEdgesEntering(edges) > 0)
            {
                // add the paragraph separator
                GenerateSeparation();
                GenerateHTMLTableHeader();

                output.LoadString(IDS_CONCEPTOR_PROCESSREPORT_MTL_HTML_1);
                GenerateHTMLSectionTitle(output);

                GenerateHTMLTableFooter();

                const int edgeCount = edges.GetSize();

                for (int i = 0; i < edgeCount; ++i)
                {
                    IODEdge*                     pIEdge = edges.GetAt(i);
                    PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pComp)
                        continue;

                    std::unique_ptr<ISymbolEntity> pDeliverableEntity(new ISymbolEntity(0, pComp->GetSymbolName(), _T("")));

                    deliverableContainer.AddSymbol(pDeliverableEntity.get());
                    pDeliverableEntity.release();
                }

                deliverableContainer.Sort();

                POSITION pDelivPos = deliverableContainer.GetHeadPosition();

                while (pDelivPos)
                {
                    ISymbolEntity* pDelivCurNode = deliverableContainer.GetAt(pDelivPos);

                    if (!pDelivCurNode)
                    {
                        pDelivPos = deliverableContainer.GetNextPosition();
                        continue;
                    }

                    PSS_DeliverableLinkSymbolBP* pLinkSymbol =
                            dynamic_cast<PSS_DeliverableLinkSymbolBP*>(SearchLinkSymbol(pDelivCurNode->GetName()));

                    if (pLinkSymbol)
                    {
                        CString objType;
                        objType.LoadString(IDS_OBJECTTYPE_DELIVERABLE);

                        GenerateHTMLSymbolTitle(pLinkSymbol->GetSymbolReferenceNumber(),
                                                pLinkSymbol->GetSymbolName(),
                                                objType,
                                                RGB(162, 221, 198));

                        PSS_Properties::IPropertySet propSet;
                        pLinkSymbol->FillProperties(propSet);

                        GenerateSection(propSet);

                        PSS_Properties::IPropertyIterator it(&propSet);

                        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                            delete pProp;

                        GenerateHTMLTableFooter();
                    }

                    pDelivPos = deliverableContainer.GetNextPosition();
                }

                deliverableContainer.RemoveAll();
            }

            GenerateSeparation();
        }

        pPos = m_StopContainer.GetNextPosition();
    }
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::GenerateSection(PSS_Properties::IPropertySet& propSet)
{
    int                               catID         = -1;
    int                               riskID        = -1;
    BOOL                              riskIsValid   =  FALSE;
    BOOL                              doPublishRisk =  FALSE;
    CStringArray                      riskContainer;
    PSS_Properties::IPropertyIterator it(&propSet);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        // Check if the filter property attributes should be shown
        if (m_pPropAttributes)
            // Check if exists
            if (!m_pPropAttributes->FindAttribute(pProp->GetCategoryID(), pProp->GetItemID()))
                continue;

        CString value;

        // get the formatted value
        switch (pProp->GetValueType())
        {
            case PSS_Property::IE_VT_Double:   value = PSS_StringFormatter::GetFormattedBuffer(               pProp->GetValueDouble(),   pProp->GetStringFormat()); break;
            case PSS_Property::IE_VT_Float:    value = PSS_StringFormatter::GetFormattedBuffer(               pProp->GetValueFloat(),    pProp->GetStringFormat()); break;
            case PSS_Property::IE_VT_Date:     value = PSS_StringFormatter::GetFormattedBuffer((PSS_Date&)    pProp->GetValueDate(),     pProp->GetStringFormat()); break;
            case PSS_Property::IE_VT_TimeSpan: value = PSS_StringFormatter::GetFormattedBuffer((PSS_TimeSpan&)pProp->GetValueTimeSpan(), pProp->GetStringFormat()); break;
            case PSS_Property::IE_VT_Duration: value = PSS_StringFormatter::GetFormattedBuffer((PSS_Duration&)pProp->GetValueDuration(), pProp->GetStringFormat()); break;
            case PSS_Property::IE_VT_String:   value = pProp->GetValueString();                                                                                     break;
            default:                                                                                                                                                break;
        }

        CString propCatName;
        propCatName.LoadString(IDS_ZS_BP_PROP_RISK_TITLE);

        if (pProp->GetCategory().Find(propCatName) > -1)
        {
            // generate a new risk section
            if (pProp->GetCategoryID() != riskID)
            {
                riskContainer.RemoveAll();

                riskID = pProp->GetCategoryID();
                riskContainer.Add(pProp->GetCategory());
            }

            if (!value.IsEmpty())
            {
                riskContainer.Add(pProp->GetLabel());
                riskContainer.Add(value);

                CString propLabelName;
                propLabelName.LoadString(IDS_Z_RISK_SEVERITY_NAME);

                // check if the severity is set to 0, otherwise the risk shouldn't be published
                if (pProp->GetLabel() == propLabelName && value != _T("0"))
                    riskIsValid = TRUE;

                propLabelName.LoadString(IDS_Z_RISK_ACTION_NAME);

                // if the last risk value was reached and if the risk is valid, publish it
                if (pProp->GetLabel() == propLabelName && riskIsValid)
                    doPublishRisk = TRUE;

                // reset the value to avoid to wrongly publish it again later
                value.Empty();
            }
        }

        // publish the risk, if allowed to process
        if (doPublishRisk)
            if (!riskContainer.IsEmpty())
            {
                GenerateHTMLSectionTitle(riskContainer.GetAt(0));

                for (int i = 1; i < riskContainer.GetCount(); i += 2)
                    GenerateHTMLSectionLine(_T(""), riskContainer.GetAt(i), riskContainer.GetAt(i + 1));
            }

        // reset all values for the next publication
        riskContainer.RemoveAll();
        riskIsValid   = FALSE;
        doPublishRisk = FALSE;

        if (!value.IsEmpty())
        {
            // add section on new category
            if (pProp->GetCategoryID() != catID)
            {
                GenerateHTMLSectionTitle(pProp->GetCategory());
                catID = pProp->GetCategoryID();
            }

            GenerateHTMLSectionLine(_T(""), pProp->GetLabel(), value);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::GenerateHTMLPageHeader(const CString& title)
{
    CString output;
    output.Format(IDS_PROCESSREPORT_HTML_1, title);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::GenerateHTMLPageFooter()
{
    WriteLine(IDS_PROCESSREPORT_HTML_2);
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::GenerateHTMLTableHeader()
{
    WriteLine(IDS_PROCESSREPORT_HTML_3);
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::GenerateHTMLTableFooter()
{
    WriteLine(IDS_PROCESSREPORT_HTML_4);
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::GenerateHTMLReportTitle(const CString& domainName, const CString& title)
{
    CString output;
    output.Format(IDS_PROCESSREPORT_HTML_5, domainName, title);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::GenerateHTMLSymbolTitle(int            ref,
                                                       const CString& title,
                                                       const CString& objectType,
                                                       COLORREF       colorTitle)
{
    // colors are written in BGR format, swap their components to become RGB
    const COLORREF r             = (colorTitle & 0xFF0000) >> 16;
    const COLORREF g             =  colorTitle & 0xFF00;
    const COLORREF b             = (colorTitle & 0xFF)     << 16;
    const COLORREF outColorTitle = r + g + b;

    CString output;
    output.Format(IDS_PROCESSREPORT_HTML_6,
                  UINT(outColorTitle),
                  ref,
                  title,
                  UINT(outColorTitle),
                  objectType);

    BOOL foundStartChar = FALSE;

    // convert spaces to 0 to avoid an incorrect color value in the html file
    for (int i = 0; i < output.GetLength(); ++i)
    {
        if (output.GetAt(i) == '#')
            foundStartChar = TRUE;

        if (foundStartChar)
        {
            if (output.GetAt(i) == ' ')
                output.SetAt(i, '0');

            if (output.GetAt(i) == '"')
                foundStartChar = FALSE;
        }
    }

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::GenerateHTMLSymbolTitle(int            ref,
                                                       const CString& title,
                                                       COLORREF       colorTitle)
{
    // colors are written in BGR format, swap their components to become RGB
    const COLORREF r             = (colorTitle & 0xFF0000) >> 16;
    const COLORREF g             =  colorTitle & 0xFF00;
    const COLORREF b             = (colorTitle & 0xFF)     << 16;
    const COLORREF outColorTitle = r + g + b;

    CString output;
    output.Format(IDS_PROCESSREPORT_HTML_7, UINT(outColorTitle), ref, title);

    BOOL foundStartChar = FALSE;

    // convert spaces to 0 to avoid an incorrect color value in the html file
    for (int i = 0; i < output.GetLength(); ++i)
    {
        if (output.GetAt(i) == '#')
            foundStartChar = TRUE;

        if (foundStartChar)
        {
            if (output.GetAt(i) == ' ')
                output.SetAt(i, '0');

            if (output.GetAt(i) == '"')
                foundStartChar = FALSE;
        }
    }

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::GenerateHTMLSectionTitle(const CString& title)
{
    CString output;
    output.Format(IDS_PROCESSREPORT_HTML_8, title);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::GenerateHTMLSectionLine(const CString& ref, const CString& title, const CString& description)
{
    CString output;
    output.Format(IDS_PROCESSREPORT_HTML_9, ref, title, description);

    WriteLine(output);
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::GenerateBlackLine()
{
    WriteLine(IDS_PROCESSREPORT_HTML_10);
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::GenerateSeparation()
{
    WriteLine(IDS_PROCESSREPORT_HTML_11);
}
//---------------------------------------------------------------------------
CString PSS_PublishProcessReport::GenerateFileName(const CString& dir, const CString& processName)
{
    CString fileName  = dir;
    fileName         += _T("ProcessReport_");
    fileName         += PSS_StringTools::ConvertSpecialChar(processName);
    fileName         += _T(".htm");

    return fileName;
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::WriteLine(const CString& text)
{
    if (!text.IsEmpty())
        m_HtmlFile << text;
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::WriteLine(int id)
{
    CString output;
    output.LoadString(id);

    if (!output.IsEmpty())
        m_HtmlFile << output;
}
//---------------------------------------------------------------------------
void PSS_PublishProcessReport::ResetData()
{
    m_StartContainer.RemoveAll();
    m_StopContainer.RemoveAll();
    m_ProcedureContainer.RemoveAll();
    m_DoorContainer.RemoveAll();
}
//---------------------------------------------------------------------------
