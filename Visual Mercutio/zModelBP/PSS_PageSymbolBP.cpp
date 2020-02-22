/****************************************************************************
 * ==> PSS_PageSymbolBP ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a page symbol for banking process                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PageSymbolBP.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_DrawFunctions.h"
#include "zModel\PSS_ProcessGraphModelViewport.h"
#include "zModel\PSS_ProcessGraphPage.h"
#include "zModel\PSS_InsertLinkModelPageDlg.h"
#include "zModel\PSS_DocObserverMsg.h"
#include "zModel\PSS_ODSymbolManipulator.h"
#include "PSS_ProcessGraphModelMdlBP.h"
#include "PSS_ProcessGraphModelControllerBP.h"
#include "PSS_ProcessSymbolBP.h"

// resources
#include "zBaseSym\zBaseSymRes.h"
#include "zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PageSymbolBP, PSS_Symbol, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PageSymbolBP
//---------------------------------------------------------------------------
PSS_PageSymbolBP::PSS_PageSymbolBP(const CString& name) :
    PSS_Symbol(),
    m_pPage(NULL),
    m_pTwinPageSymbol(NULL),
    m_TwinPageRefNumber(-1),
    m_ShowPreview(false)
{
    PSS_Symbol::SetSymbolName(name);

    CODTextComponent* pText = GetSymbolNameTextEdit();

    // resize the text name edit according to the text width
    if (pText)
        pText->SizeToText();
}
//---------------------------------------------------------------------------
PSS_PageSymbolBP::PSS_PageSymbolBP(const PSS_PageSymbolBP& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PageSymbolBP::~PSS_PageSymbolBP()
{}
//---------------------------------------------------------------------------
PSS_PageSymbolBP& PSS_PageSymbolBP::operator = (const PSS_PageSymbolBP& other)
{
    PSS_Symbol::operator = ((const PSS_Symbol&)other);

    m_pTwinPageSymbol   = other.m_pTwinPageSymbol;
    m_TwinPageRefNumber = other.m_TwinPageRefNumber;
    m_ShowPreview       = other.m_ShowPreview;

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_PageSymbolBP::Create(const CString& name)
{
    BOOL result = FALSE;

    try
    {
        m_IsInCreationProcess = true;
        result                = PSS_Symbol::Create(IDR_BP_PAGE,
                                                   ::AfxFindResourceHandle(MAKEINTRESOURCE(IDR_PACKAGE_SYM),
                                                                           _T("Symbol")),
                                                   name);

        if (!CreateSymbolProperties())
            result = FALSE;

        // change some name's properties
        CODTextComponent* pText = GetSymbolNameTextEdit();

        if (pText)
        {
            pText->SetValue(OD_PROP_VERT_ALIGNMENT, TRUE);

            CODFontProperties* pFontProp = static_cast<CODFontProperties*>(pText->GetProperty(OD_PROP_FONT));

            if (pFontProp)
            {
                std::unique_ptr<CODFontProperties> pNewFontProp(new CODFontProperties(*pFontProp));
                pNewFontProp->SetFaceName(_T("Arial"));
                pNewFontProp->SetWeight(FW_NORMAL);
                pNewFontProp->SetPointSize(8);
                pText->SetProperty(pNewFontProp.get());
                pNewFontProp.release();
            }
        }
    }
    catch (...)
    {
        m_IsInCreationProcess = false;
        throw;
    }

    m_IsInCreationProcess = false;
    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_PageSymbolBP::CreateEmptyChildModel(CODModel* pParent)
{
    // can't create an empty child model, must be done by page creation
    return FALSE;
}
//---------------------------------------------------------------------------
CODComponent* PSS_PageSymbolBP::Dup() const
{
    return new PSS_PageSymbolBP(*this);
}
//---------------------------------------------------------------------------
void PSS_PageSymbolBP::CopySymbolDefinitionFrom(const CODSymbolComponent& src)
{
    PSS_Symbol::CopySymbolDefinitionFrom(src);

    const PSS_PageSymbolBP* pPage = dynamic_cast<const PSS_PageSymbolBP*>(&src);

    if (pPage)
    {
        m_pPage             = pPage->m_pPage;
        m_pTwinPageSymbol   = pPage->m_pTwinPageSymbol;
        m_CommentRect       = pPage->m_CommentRect;
        m_PageName          = pPage->m_PageName;
        m_SubModelPathName  = pPage->m_SubModelPathName;
        m_TwinPageRefNumber = pPage->m_TwinPageRefNumber;
        m_ShowPreview       = pPage->m_ShowPreview;
    }
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_PageSymbolBP::GetPageModel()
{
    return (GetPage() ? GetPage()->GetModel() : NULL);
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::SetPageModel(PSS_ProcessGraphModelMdl* pModel)
{
    m_pModel = pModel;
    m_pPage  = NULL;

    // find the page matching with the model and extend to sub-model
    if (pModel)
    {
        PSS_ProcessGraphModelMdl* pRoot = pModel->GetRoot();

        if (pRoot)
            m_pPage = pRoot->FindModelPage(pModel, true);
    }

    // assign the page name
    SetSymbolName(BuildSymbolName());

    CODTextComponent* pText = GetSymbolNameTextEdit();

    // resize the text name edit according to the text width
    if (pText)
        pText->SizeToText();

    return m_pPage;
}
//---------------------------------------------------------------------------
void PSS_PageSymbolBP::RecalculateTwinPageReference(PSS_ProcessGraphModelMdl* pRootModel)
{
    PSS_ProcessGraphModelMdlBP* pGraphRootModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pRootModel);

    // get the model
    if (pGraphRootModel && !m_PageName.IsEmpty())
    {
        // find the page by its name
        m_pPage = pGraphRootModel->FindPage(m_PageName);

        // assign the child model if no sub-model path name defined
        if (m_SubModelPathName.IsEmpty())
        {
            if (m_pPage)
                m_pModel = m_pPage->GetModel();
        }
        else
            m_pModel = pGraphRootModel->FindModelFromPath(m_SubModelPathName, true);
    }

    // nothing else to do?
    if (!pRootModel || GetTwinPageReferenceNumber() == -1)
        return;

    PSS_ProcessGraphModelMdl* pRoot = pRootModel->GetRoot();

    if (!pRoot)
        return;

    CODComponentSet* pSet = pRoot->FindSymbolByRefNumber(GetTwinPageReferenceNumber());

    // get the twin page
    if (pSet && pSet->GetSize() > 0)
        m_pTwinPageSymbol = dynamic_cast<PSS_PageSymbolBP*>(pSet->GetAt(0));
}
//---------------------------------------------------------------------------
void PSS_PageSymbolBP::SetTwinPageReferenceNumber(int refNumber)
{
    m_TwinPageRefNumber = refNumber;
}
//---------------------------------------------------------------------------
void PSS_PageSymbolBP::AssignTwinPageSymbol(PSS_PageSymbolBP* pPage)
{
    if (!pPage)
        return;

    // assign the page
    m_pTwinPageSymbol = pPage;

    // link this symbol with its twin
    SetTwinPageReferenceNumber(pPage->GetSymbolReferenceNumber());
    pPage->SetTwinPageReferenceNumber(GetSymbolReferenceNumber());
    pPage->SetTwinPageSymbol(this);

    // attach this to the source reference
    AttachObserver(pPage);
    pPage->AttachObserver(this);
}
//---------------------------------------------------------------------------
void PSS_PageSymbolBP::RemoveTwinPageSymbol(bool removeTwin)
{
    PSS_ProcessGraphModelMdl* pParent = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetParent());

    // is the parent a model?
    if (!pParent)
        return;

    PSS_ProcessGraphModelMdl* pRoot = pParent->GetRoot();

    if (!pRoot)
        return;

    CODComponentSet* pSet = pRoot->FindSymbolByRefNumber(GetTwinPageReferenceNumber());

    if (pSet && pSet->GetSize() > 0)
    {
        PSS_PageSymbolBP* pPage = dynamic_cast<PSS_PageSymbolBP*>(pSet->GetAt(0));

        // is a page symbol?
        if (pPage)
        {
            // check if the page reference number is correct, empty the twin page ref number if not
            if (!removeTwin || pPage->GetTwinPageReferenceNumber() == GetSymbolReferenceNumber())
            {
                if (removeTwin)
                {
                    pPage->SetTwinPageReferenceNumber(-1);
                    pPage->SetTwinPageSymbol(NULL);
                }

                // unlink the twin symbol
                SetTwinPageReferenceNumber(-1);
                SetTwinPageSymbol(NULL);

                // remove the observer
                DetachObserver(pPage);
                pPage->DetachObserver(this);

                // remove the assignement
                if (!removeTwin)
                    SetPageModel(NULL);
            }
        }
    }
}
//---------------------------------------------------------------------------
BOOL PSS_PageSymbolBP::DuplicateStyleOnTwinSymbol()
{
    PSS_PageSymbolBP* pTwinSymbol = GetTwinPageSymbol();

    if (pTwinSymbol)
        return PSS_ODSymbolManipulator::CopySymbolStyle(this, pTwinSymbol);

    return FALSE;
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::CreateSymbolProperties()
{
    return PSS_Symbol::CreateSymbolProperties();
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::FillProperties(ZBPropertySet& propSet, bool numericValues, bool groupValues)
{
    return PSS_Symbol::FillProperties(propSet, numericValues, groupValues);
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::SaveProperties(ZBPropertySet& propSet)
{
    if (!PSS_Symbol::SaveProperties(propSet))
        return false;

    RefreshAttributeTextArea(true);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::AcceptDropItem(CObject* pObj, const CPoint& point)
{
    // don't allow the drop if the symbol isn't local
    if (!IsLocal())
        return false;

    return PSS_Symbol::AcceptDropItem(pObj, point);
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::DropItem(CObject* pObj, const CPoint& point)
{
    return PSS_Symbol::DropItem(pObj, point);
}
//---------------------------------------------------------------------------
void PSS_PageSymbolBP::Serialize(CArchive& ar)
{
    PSS_Symbol::Serialize(ar);

    // only if the object is serialized from or to a document
    if (ar.m_pDocument)
        if (ar.IsStoring())
        {
            TRACE(_T("PSS_PageSymbolBP::Serialize - Start save\n"));

            ar << WORD(m_ShowPreview);
            ar << m_pPage->GetPageName();

            PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(m_pModel);

            // if the model differs from the page model, serialize the model name but save an empty model
            if (pModel && pModel != m_pPage->GetModel())
                ar << pModel->GetAbsolutePath();
            else
            {
                CString emptyString;
                ar << emptyString;
            }

            ar << m_TwinPageRefNumber;

            TRACE(_T("PSS_PageSymbolBP::Serialize : End save\n"));
        }
        else
        {
            TRACE(_T("PSS_PageSymbolBP::Serialize : Start read\n"));

            m_pPage = NULL;

            WORD wValue;
            ar >> wValue;
            m_ShowPreview = bool(wValue);

            ar >> m_PageName;
            ar >> m_SubModelPathName;
            ar >> m_TwinPageRefNumber;

            TRACE(_T("PSS_PageSymbolBP::Serialize : End read\n"));
        }
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::OnPostCreation(CODModel* pModel, CODController* pCtrl)
{
    if (!PSS_Symbol::OnPostCreation(pModel, pCtrl))
        return false;

    PSS_ProcessGraphModelMdlBP* pProcessGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pModel);

    if (!pProcessGraphModel)
        return false;

    PSS_ProcessGraphModelMdlBP* pRootModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pProcessGraphModel->GetRoot());

    if (!pRootModel)
        return false;

    const CString newPage = pRootModel->GetValidNextPageName();

    // get this model page
    PSS_ProcessGraphPage* pModelPage = pRootModel->FindModelPage(pProcessGraphModel, true);

    if (!pModelPage)
        return false;

    // get the owner model
    PSS_ProcessGraphModelMdl* pOwnerModel = pRootModel->GetOwnerPageModel(pModelPage);

    PSS_RuntimeClassSet rtClasses;
    rtClasses.Add(RUNTIME_CLASS(PSS_PageSymbolBP));
    rtClasses.Add(RUNTIME_CLASS(PSS_ProcessSymbolBP));

    PSS_InsertLinkModelPageDlg dlg(pOwnerModel ? pOwnerModel : pRootModel,
                                   newPage,
                                   pRootModel->GetExistingPageNameArray(),
                                   &rtClasses);

    if (dlg.DoModal() != IDOK)
        return false;

    PSS_ProcessGraphModelViewport* pNewVp = NULL;

    // a new page should be inserted?
    if (dlg.SelectInsertNewPage())
    {
        PSS_ProcessGraphModelMdl* pNewModel = pRootModel->CreateEmptyModel(dlg.GetPageName(), pProcessGraphModel);

        // create the new page
        m_pPage = pRootModel->CreateNewPage(pNewModel, dlg.GetPageName(), dlg.GetParentModel());

        // assign the child model
        if (m_pPage)
            m_pModel = m_pPage->GetModel();

        // assign the page name
        SetSymbolName(BuildSymbolName());

        CODTextComponent* pText = GetSymbolNameTextEdit();

        // resize the text name edit according to the text width
        if (pText)
            pText->SizeToText();

        PSS_ProcessGraphModelControllerBP* pModelCtrl = dynamic_cast<PSS_ProcessGraphModelControllerBP*>(pCtrl);

        // open the model
        if (pModelCtrl)
            pNewVp = pModelCtrl->BrowseModel(pNewModel, pProcessGraphModel);
    }
    // do insert a link to an existing page
    else
    {
        // find the page by its name
        m_pPage = pRootModel->FindPage(dlg.GetPageName());

        // assign the child model
        if (m_pPage)
        {
            m_pModel = m_pPage->GetModel();

            // assign the page name
            SetSymbolName(BuildSymbolName());

            CODTextComponent* pText = GetSymbolNameTextEdit();

            // resize the text name edit according to the text width
            if (pText)
                pText->SizeToText();

            PSS_ProcessGraphModelControllerBP* pModelCtrl = dynamic_cast<PSS_ProcessGraphModelControllerBP*>(pCtrl);

            // open the model
            if (pModelCtrl)
            {
                PSS_ProcessGraphModelMdl* pThisProcGraphMdl = dynamic_cast<PSS_ProcessGraphModelMdl*>(m_pModel);

                if (pThisProcGraphMdl)
                    pNewVp = pModelCtrl->BrowseModel(pThisProcGraphMdl, pProcessGraphModel);
            }
        }
    }

    if (m_pPage && m_pModel && pCtrl)
    {
        PSS_ProcessGraphModelMdlBP* pThisGraphMdl = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pModel);

        if (pThisGraphMdl)
        {
            CODNodeArray      nodes;
            const std::size_t elementCount = pThisGraphMdl->GetBPPageSymbols(nodes);
            PSS_PageSymbolBP* pTwinPage    = NULL;
            bool              found        = false;

            for (std::size_t i = 0; i < elementCount; ++i)
            {
                IODNode* pINode = nodes.GetAt(i);
                pTwinPage       = static_cast<PSS_PageSymbolBP*>(pINode);

                if (!pTwinPage || !pTwinPage->GetPage())
                    continue;

                // is the page symbol matching with the twin page name?
                if (pTwinPage->GetTwinPageReferenceNumber() == GetSymbolReferenceNumber())
                {
                    found = true;
                    break;
                }
            }

            // if the symbol was not found, add a page symbol on the newly created model linked with the initial one
            if (found == false)
            {
                PSS_ProcessGraphModelControllerBP* pModelCtrl = dynamic_cast<PSS_ProcessGraphModelControllerBP*>(pNewVp->GetModelController());

                if (pModelCtrl)
                {
                    pModelCtrl->InsertPageSymbol();

                    PSS_PageSymbolBP* pNewSymbolInserted =
                            dynamic_cast<PSS_PageSymbolBP*>(pModelCtrl->InsertSymbol(0, CPoint(30, 30), false));

                    if (pNewSymbolInserted)
                    {
                        pNewSymbolInserted->SetPageModel(pProcessGraphModel);

                        // assign the twin page symbol
                        AssignTwinPageSymbol(pNewSymbolInserted);
                    }
                }
            }
            else
                // assign the twin page symbol
                AssignTwinPageSymbol(pTwinPage);
        }
    }

    CWnd* pWnd = AfxGetMainWnd();

    // build the message
    if (pWnd)
    {
        PSS_DocObserverMsg docMsg;
        pWnd->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, LPARAM(&docMsg));
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::OnPreDelete(CODModel* pModel, CODController* pCtrl)
{
    PSS_PageSymbolBP* pTwinPage = GetTwinPageSymbol();

    if (!pTwinPage)
        return true;

    PSS_MsgBox mBox;

    if (mBox.Show(IDS_DELETEPAGESYM_CONF, MB_YESNO) == IDYES)
    {
        PSS_ProcessGraphModelMdl* pProcessGraphModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel);

        // delete the symbol
        if (pProcessGraphModel)
            pProcessGraphModel->DeleteComponent(GetTwinPageSymbol());

        return true;
    }

    // don't delete the page symbol
    return false;
}
//---------------------------------------------------------------------------
void PSS_PageSymbolBP::OnPageNameChanged(PSS_ProcessGraphPage* pPage, const CString& oldName)
{
    if (pPage == GetPage())
    {
        PSS_ProcessGraphModelMdl* pModel = pPage->GetModel();

        // bug about renaming the page name, in fact the model name isn't changed. Therefore, in the navigation
        // and the web generation, the old name is shown
        if (pModel)
        {
            pModel->SetModelName(pPage->GetPageName());

            // assign the page name
            SetSymbolName(BuildSymbolName());

            CODTextComponent* pText = GetSymbolNameTextEdit();

            // resize the text name edit according to the text width
            if (pText)
                pText->SizeToText();
        }
    }
}
//---------------------------------------------------------------------------
BOOL PSS_PageSymbolBP::OnDoubleClick()
{
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PageSymbolBP::OnPostDoubleClick(CODModel* pModel, CODController* pCtrl)
{
    PSS_PageSymbolBP* pTwinPage = GetTwinPageSymbol();

    if (!pTwinPage)
        return;

    PSS_ProcessGraphModelController* pModelCtrl = dynamic_cast<PSS_ProcessGraphModelController*>(pCtrl);

    // force the symbol to be visible
    if (pModelCtrl)
        pModelCtrl->EnsureSymbolVisible(GetTwinPageSymbol());
}
//---------------------------------------------------------------------------
void PSS_PageSymbolBP::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_PageSymbolBP* pSymbol = dynamic_cast<PSS_PageSymbolBP*>(static_cast<PSS_Symbol*>(pSubject));

    // is a page symbol?
    if (pSymbol)
        // check if the twin page name has changed compared to the page symbol received from the message
        if (GetTwinPageReferenceNumber() != pSymbol->GetSymbolReferenceNumber())
            // reassign the new name
            SetTwinPageReferenceNumber(pSymbol->GetSymbolReferenceNumber());
}
//---------------------------------------------------------------------------
void PSS_PageSymbolBP::OnDraw(CDC* pDC)
{
    PSS_Symbol::OnDraw(pDC);
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    PSS_ProcessGraphPage* pPage = GetPage();

    if (pPage && pPage->GetPageName())
        toolTipText.Format(IDS_FS_BPPAGE_TOOLTIP, (const char*)pPage->GetPageName());
    else
        toolTipText.LoadString(IDS_FS_BPPAGE_ERR_TOOLTIP);

    if (mode == PSS_Symbol::IE_TT_Design)
    {
        // todo -cFeature -oJean: do nothing for now, need to implement the check result
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_PageSymbolBP::AdjustElementPosition()
{
    PSS_Symbol::AdjustElementPosition();

    // recalculate the comment rect
    CODTextComponent* pText = GetCommentTextEdit();

    if (pText)
    {
        m_CommentRect = pText->GetBounds();
        m_CommentRect.DeflateRect(1, 1);
    }
}
//---------------------------------------------------------------------------
CString PSS_PageSymbolBP::BuildSymbolName()
{
    // is a page defined?
    if (m_pPage)
        return m_pPage->GetPageName();

    return _T("");
}
//---------------------------------------------------------------------------
