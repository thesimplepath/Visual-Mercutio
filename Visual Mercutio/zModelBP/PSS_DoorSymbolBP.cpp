/****************************************************************************
 * ==> PSS_DoorSymbolBP ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a door symbol for banking process                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DoorSymbolBP.h"

// processsoft
#include "zBaseLib\PSS_DrawFunctions.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseSym\zBaseSymRes.h"
#include "zModel\PSS_ProcessGraphPage.h"
#include "zModel\PSS_ProcessGraphModelViewport.h"
#include "zModel\PSS_SelectModelSymbolDlg.h"
#include "zModel\PSS_DocObserverMsg.h"
#include "PSS_ProcessGraphModelMdlBP.h"
#include "PSS_ProcessGraphModelControllerBP.h"
#include "PSS_ProcessSymbolBP.h"
#include "PSS_PageSymbolBP.h"
#include "zModel\PSS_ODSymbolManipulator.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_DoorSymbolBP, PSS_Symbol, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_DoorSymbolBP
//---------------------------------------------------------------------------
PSS_DoorSymbolBP::PSS_DoorSymbolBP(const CString& name) :
    PSS_Symbol(),
    m_pTwinDoorSymbol(NULL),
    m_TwinDoorRefNumber(-1),
    m_ShowPreview(false)
{
    PSS_Symbol::SetSymbolName(name);

    CODTextComponent* pText = GetSymbolNameTextEdit();

    // resize the text name edit according to the text width
    if (pText)
        pText->SizeToText();
}
//---------------------------------------------------------------------------
PSS_DoorSymbolBP::PSS_DoorSymbolBP(const PSS_DoorSymbolBP& other) :
    PSS_Symbol(),
    m_pTwinDoorSymbol(NULL),
    m_TwinDoorRefNumber(-1),
    m_ShowPreview(false)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_DoorSymbolBP::~PSS_DoorSymbolBP()
{
    if (m_pTwinDoorSymbol)
    {
        m_pTwinDoorSymbol->DetachObserver(this);
        DetachObserver(m_pTwinDoorSymbol);
    }
}
//---------------------------------------------------------------------------
PSS_DoorSymbolBP& PSS_DoorSymbolBP::operator = (const PSS_DoorSymbolBP& other)
{
    if (m_pTwinDoorSymbol)
    {
        m_pTwinDoorSymbol->DetachObserver(this);
        DetachObserver(m_pTwinDoorSymbol);
    }

    PSS_Symbol::operator = ((const PSS_Symbol&)other);

    m_pTwinDoorSymbol   = other.m_pTwinDoorSymbol;
    m_TwinDoorRefNumber = other.m_TwinDoorRefNumber;
    m_ShowPreview       = other.m_ShowPreview;

    if (m_pTwinDoorSymbol)
    {
        AttachObserver(m_pTwinDoorSymbol);
        m_pTwinDoorSymbol->AttachObserver(this);
    }

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_DoorSymbolBP::Create(const CString& name)
{
    BOOL result           = FALSE;
    m_IsInCreationProcess = true;

    try
    {
        result = PSS_Symbol::Create(IDR_BP_DOOR,
                                    ::AfxFindResourceHandle(MAKEINTRESOURCE(IDR_PACKAGE_SYM), _T("Symbol")),
                                    name);

        if (!CreateSymbolProperties())
            result = FALSE;

        // change some name properties
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
CODComponent* PSS_DoorSymbolBP::Dup() const
{
    return new PSS_DoorSymbolBP(*this);
}
//---------------------------------------------------------------------------
void PSS_DoorSymbolBP::CopySymbolDefinitionFrom(const CODSymbolComponent& src)
{
    PSS_Symbol::CopySymbolDefinitionFrom(src);

    const PSS_DoorSymbolBP* pDoor = dynamic_cast<const PSS_DoorSymbolBP*>(&src);

    if (pDoor)
    {
        if (m_pTwinDoorSymbol)
        {
            m_pTwinDoorSymbol->DetachObserver(this);
            DetachObserver(m_pTwinDoorSymbol);
        }

        m_pTwinDoorSymbol   = pDoor->m_pTwinDoorSymbol;
        m_CommentRect       = pDoor->m_CommentRect;
        m_SubModelPathName  = pDoor->m_SubModelPathName;
        m_TwinDoorRefNumber = pDoor->m_TwinDoorRefNumber;
        m_ShowPreview       = pDoor->m_ShowPreview;


        if (m_pTwinDoorSymbol)
        {
            AttachObserver(m_pTwinDoorSymbol);
            m_pTwinDoorSymbol->AttachObserver(this);
        }
    }
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_DoorSymbolBP::GetDoorModel()
{
    PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(m_pModel);
    PSS_Assert(pModel);

    return pModel;
}
//---------------------------------------------------------------------------
bool PSS_DoorSymbolBP::SetDoorModel(PSS_ProcessGraphModelMdl* pModel)
{
    m_pModel = pModel;

    // assign the door name
    SetSymbolName(BuildSymbolName());

    CODTextComponent* pText = GetSymbolNameTextEdit();

    // resize the text name edit according to the text width
    if (pText)
        pText->SizeToText();

    return m_pModel;
}
//---------------------------------------------------------------------------
void PSS_DoorSymbolBP::RecalculateTwinDoorReference(PSS_ProcessGraphModelMdl* pRootModel)
{
    if (GetTwinDoorReferenceNumber() == -1 || !pRootModel)
        return;

    PSS_ProcessGraphModelMdl* pRoot = pRootModel->GetRoot();

    if (!pRoot)
        return;

    // get the other twin
    CODComponentSet* pSet = pRoot->FindSymbolByRefNumber(GetTwinDoorReferenceNumber());

    if (pSet && pSet->GetSize() > 0)
    {
        PSS_DoorSymbolBP* pTwin = dynamic_cast<PSS_DoorSymbolBP*>(pSet->GetAt(0));

        if (pTwin)
        {
            if (m_pTwinDoorSymbol)
            {
                m_pTwinDoorSymbol->DetachObserver(this);
                DetachObserver(m_pTwinDoorSymbol);
            }

            m_pTwinDoorSymbol = pTwin;

            AttachObserver(m_pTwinDoorSymbol);
            m_pTwinDoorSymbol->AttachObserver(this);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_DoorSymbolBP::SetTwinDoorReferenceNumber(int refNumber)
{
    m_TwinDoorRefNumber = refNumber;
}
//---------------------------------------------------------------------------
void PSS_DoorSymbolBP::AssignTwinDoorSymbol(PSS_DoorSymbolBP* pDoor)
{
    if (m_pTwinDoorSymbol)
    {
        m_pTwinDoorSymbol->DetachObserver(this);
        DetachObserver(m_pTwinDoorSymbol);
    }

    // assign the twin door symbol
    m_pTwinDoorSymbol = pDoor;

    if (!pDoor)
        return;

    // link this symbol to its twin
    SetTwinDoorReferenceNumber(pDoor->GetSymbolReferenceNumber());
    pDoor->SetTwinDoorReferenceNumber(GetSymbolReferenceNumber());
    pDoor->SetTwinDoorSymbol(this);

    // attach the observers
    AttachObserver(pDoor);
    pDoor->AttachObserver(this);
}
//---------------------------------------------------------------------------
void PSS_DoorSymbolBP::RemoveTwinDoorSymbol(bool removeTwin)
{
    PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetParent());

    if (!pModel)
        return;

    PSS_ProcessGraphModelMdl* pRoot = pModel->GetRoot();

    if (!pRoot)
        return;

    CODComponentSet* pSet = pRoot->FindSymbolByRefNumber(GetTwinDoorReferenceNumber());

    if (pSet && pSet->GetSize() > 0)
    {
        PSS_DoorSymbolBP* pDoor = dynamic_cast<PSS_DoorSymbolBP*>(pSet->GetAt(0));

        if (!pDoor)
            return;

        // check if the door name is correct, then empty the twin door name
        if (!removeTwin || pDoor->GetTwinDoorReferenceNumber() == GetSymbolReferenceNumber())
        {
            if (removeTwin)
            {
                pDoor->SetTwinDoorReferenceNumber(-1);
                pDoor->SetTwinDoorSymbol(NULL);
            }

            // empty the twin door ref number
            SetTwinDoorReferenceNumber(-1);
            SetTwinDoorSymbol(NULL);

            // remove the observer
            DetachObserver(pDoor);
            pDoor->DetachObserver(this);

            if (!removeTwin)
                SetDoorModel(NULL);
        }
    }
}
//---------------------------------------------------------------------------
BOOL PSS_DoorSymbolBP::DuplicateStyleOnTwinSymbol()
{
    PSS_DoorSymbolBP* pTwinSymbol = GetTwinDoorSymbol();

    if (pTwinSymbol)
        return PSS_ODSymbolManipulator::CopySymbolStyle(this, pTwinSymbol);

    return FALSE;
}
//---------------------------------------------------------------------------
bool PSS_DoorSymbolBP::AcceptDropItem(CObject* pObj, const CPoint& point)
{
    // don't allow the drop if the symbol isn't local
    if (!IsLocal())
        return false;

    return PSS_Symbol::AcceptDropItem(pObj, point);
}
//---------------------------------------------------------------------------
bool PSS_DoorSymbolBP::DropItem(CObject* pObj, const CPoint& point)
{
    return PSS_Symbol::DropItem(pObj, point);
}
//---------------------------------------------------------------------------
void PSS_DoorSymbolBP::Serialize(CArchive& ar)
{
    PSS_Symbol::Serialize(ar);

    // only if the object is serialized from or to a document
    if (ar.m_pDocument)
    {
        if (ar.IsStoring())
        {
            TRACE("PSS_DoorSymbolBP::Serialize - Start save\n");

            ar << WORD(m_ShowPreview);
            ar << m_TwinDoorRefNumber;

            TRACE("PSS_DoorSymbolBP::Serialize - End save\n");
        }
        else
        {
            TRACE("PSS_DoorSymbolBP::Serialize - Start read\n");

            WORD wValue;
            ar >> wValue;
            m_ShowPreview = bool(wValue);

            ar >> m_TwinDoorRefNumber;

            TRACE("PSS_DoorSymbolBP::Serialize - End read\n");
        }

        if (m_pModel)
            m_pModel->SetName(GetSymbolName());
    }
}
//---------------------------------------------------------------------------
bool PSS_DoorSymbolBP::OnPostCreation(CODModel* pModel, CODController* pCtrl)
{
    if (!PSS_Symbol::OnPostCreation(pModel, pCtrl))
        return false;

    PSS_ProcessGraphModelMdlBP* pGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pModel);

    if (!pGraphModel)
        return false;

    PSS_ProcessGraphModelMdlBP* pRootModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pGraphModel->GetRoot());

    if (!pRootModel)
        return false;

    // filter object classes
    PSS_RuntimeClassSet rtClasses;
    rtClasses.Add(RUNTIME_CLASS(PSS_PageSymbolBP));
    rtClasses.Add(RUNTIME_CLASS(PSS_ProcessSymbolBP));

    PSS_SelectModelSymbolDlg dlg(pRootModel, ISD_DOOR_SELECTMODEL, g_Selectable_Model | g_Selectable_GraphPage, &rtClasses);

    if (dlg.DoModal() != IDOK)
        return false;

    PSS_ProcessGraphModelViewport* pNewVp         = NULL;
    PSS_ProcessGraphModelMdl*      pSelectedModel = NULL;

    // a model was selected?
    if (dlg.GetSelectedModel())
        pSelectedModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(dlg.GetSelectedModel());

    // a page was selected, and no model was previously selected?
    if (!pSelectedModel && dlg.GetSelectedPage() && dlg.GetSelectedPage()->GetModel())
        pSelectedModel = dlg.GetSelectedPage()->GetModel();

    if (pSelectedModel)
    {
        // assign the model
        SetDoorModel(pSelectedModel);

        PSS_ProcessGraphModelControllerBP* pModelCtrl = dynamic_cast<PSS_ProcessGraphModelControllerBP*>(pCtrl);

        // open it
        if (pModelCtrl)
            pNewVp = pModelCtrl->BrowseModel(pSelectedModel, pSelectedModel->GetParent());
    }

    if (m_pModel && pNewVp && pCtrl)
    {
        PSS_ProcessGraphModelMdlBP* pThisGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pModel);

        if (pThisGraphModel)
        {
            CODNodeArray      nodes;
            const std::size_t elementCount = pThisGraphModel->GetBPDoorSymbols(nodes);
            PSS_DoorSymbolBP* pTwinDoor    = NULL;
            bool              found        = false;

            // iterate through the model symbols and check if a door with the same ref number already exists
            for (std::size_t i = 0; i < elementCount; ++i)
            {
                IODNode* pNode = nodes.GetAt(i);
                pTwinDoor      = static_cast<PSS_DoorSymbolBP*>(pNode);

                if (!pTwinDoor || !pTwinDoor->GetChildModel())
                    continue;

                // found a door with the same ref number as this one?
                if (pTwinDoor->GetTwinDoorReferenceNumber() == GetSymbolReferenceNumber())
                {
                    found = true;
                    break;
                }
            }

            // found a twin door symbol?
            if (found)
                // assign it
                AssignTwinDoorSymbol(pTwinDoor);
            else
            {
                // if no existing door symbol was found in the model, create a new one
                PSS_ProcessGraphModelControllerBP* pModelCtrl =
                        dynamic_cast<PSS_ProcessGraphModelControllerBP*>(pNewVp->GetModelController());

                if (pModelCtrl)
                {
                    pModelCtrl->InsertDoorSymbol();

                    PSS_DoorSymbolBP* pNewSymbolInserted =
                            dynamic_cast<PSS_DoorSymbolBP*>(pModelCtrl->InsertSymbol(0, CPoint(30, 30), false));

                    if (pNewSymbolInserted)
                    {
                        pNewSymbolInserted->SetDoorModel(pGraphModel);

                        // assigns the twin door symbol
                        AssignTwinDoorSymbol(pNewSymbolInserted);
                    }
                }
            }
        }
    }

    CWnd* pWnd = ::AfxGetMainWnd();

    // build the message
    if (pWnd)
    {
        PSS_DocObserverMsg docMsg;
        pWnd->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, LPARAM(&docMsg));
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DoorSymbolBP::OnPreDelete(CODModel* pModel, CODController* pCtrl)
{
    // get the twin door symbol
    PSS_DoorSymbolBP* pTwinDoor = GetTwinDoorSymbol();

    if (!pTwinDoor)
        return true;

    PSS_MsgBox mBox;

    if (mBox.Show(IDS_DELETEDOORSYM_CONF, MB_YESNO) == IDYES)
    {
        // get the owner model
        PSS_ProcessGraphModelMdl* pOwnerModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pTwinDoor->GetOwnerModel());

        // delete the twin door symbol
        if (pOwnerModel)
            pOwnerModel->DeleteComponent(pTwinDoor);

        return true;
    }

    // don't delete the door symbol
    return false;
}
//---------------------------------------------------------------------------
void PSS_DoorSymbolBP::OnSymbolNameChanged(CODComponent& comp, const CString& oldName)
{
    // check if the old symbol name was used somewhere in this door symbol
    PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(&comp);

    // Check if a process and the same we pointed to
    if (pProcess && !pProcess->IsChildModelRef() && pProcess->GetChildModel() == GetChildModel())
    {
        // assign the door name
        SetSymbolName(BuildSymbolName());

        CODTextComponent* pText = GetSymbolNameTextEdit();

        // resize the text name edit according to the text width
        if (pText)
            pText->SizeToText();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_DoorSymbolBP::OnDoubleClick()
{
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DoorSymbolBP::OnPostDoubleClick(CODModel* pModel, CODController* pCtrl)
{
    // get the twin door symbol
    PSS_DoorSymbolBP* pTwinDoor = GetTwinDoorSymbol();

    if (!pTwinDoor)
        return;

    PSS_ProcessGraphModelController* pModelCtrl = dynamic_cast<PSS_ProcessGraphModelController*>(pCtrl);

    // force the symbol to be visible
    if (pModelCtrl)
        pModelCtrl->EnsureSymbolVisible(pTwinDoor);
}
//---------------------------------------------------------------------------
void PSS_DoorSymbolBP::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_DoorSymbolBP* pDoor = dynamic_cast<PSS_DoorSymbolBP*>(static_cast<PSS_Symbol*>(pSubject));

    // is a door symbol?
    if (pDoor)
        // check if the twin door ref number has changed compared to the received door symbol in the message
        if (GetTwinDoorReferenceNumber() != pDoor->GetSymbolReferenceNumber())
            // reassign the new name
            SetTwinDoorReferenceNumber(pDoor->GetSymbolReferenceNumber());
}
//---------------------------------------------------------------------------
void PSS_DoorSymbolBP::OnDraw(CDC* pDC)
{
    PSS_Symbol::OnDraw(pDC);
}
//---------------------------------------------------------------------------
bool PSS_DoorSymbolBP::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    PSS_ProcessGraphModelMdl* pGraphModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(m_pModel);

    // is a model defined?
    if (pGraphModel)
        toolTipText.Format(IDS_FS_BPDOOR_TOOLTIP, (const char*)pGraphModel->GetModelName());
    else
        toolTipText.LoadString(IDS_FS_BPDOOR_ERR_TOOLTIP);

    if (mode == PSS_Symbol::IE_TT_Design)
    {
        // todo -cFeature -oJean: do nothing for now, need to implement the design mode
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_DoorSymbolBP::AdjustElementPosition()
{
    PSS_Symbol::AdjustElementPosition();
}
//---------------------------------------------------------------------------
CString PSS_DoorSymbolBP::BuildSymbolName()
{
    PSS_ProcessGraphModelMdl* pGraphModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(m_pModel);

    // is a model defined?
    if (pGraphModel)
        return pGraphModel->GetModelName();

    return _T("");
}
//---------------------------------------------------------------------------
