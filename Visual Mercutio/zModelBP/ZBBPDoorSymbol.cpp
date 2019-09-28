// ZBBPDoorSymbol.cpp: implementation of the ZBBPDoorSymbol class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBBPDoorSymbol.h"

#include "zBaseLib\PSS_DrawFunctions.h"
#include "zBaseLib\PSS_MsgBox.h"

#include "zBaseSym\zBaseSymRes.h"

#include "zModel\ZDProcessGraphPage.h"
#include "zModel\ProcGraphModelVp.h"
#include "zModel\ZVSelectModelSymbolDlg.h"
#include "zModel\ZBDocObserverMsg.h"

#include "ProcGraphModelMdlBP.h"
#include "ProcGraphModelCtlrBP.h"
#include "ZBBPProcessSymbol.h"
#include "ZBBPPageSymbol.h"

// JMR-MODIF - Le 30 août 2006 - Ajout de l'en-tête ZUODSymbolManipulator.
#include "zModel\ZUODSymbolManipulator.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 3 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(ZBBPDoorSymbol, ZBSymbol, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBBPDoorSymbol::ZBBPDoorSymbol(const CString Name /*= ""*/)
    : m_DisplayPreview(false),
    m_pTwinDoorSymbol(NULL),
    m_TwinDoorRefNumber(-1)
{
    ZBSymbol::SetSymbolName(Name);

    // ***********************************************************************************************
    // JMR-MODIF - Le 1er mai 2006 - Redimensionne la zone de texte par rapport à la largeur du texte.
    CODTextComponent* pText = GetSymbolNameTextEdit();

    if (pText)
    {
        pText->SizeToText();
    }
    // ***********************************************************************************************
}

ZBBPDoorSymbol::~ZBBPDoorSymbol()
{
    // todo -cCheck -oJean: on 26.09.2019, check if this modification is valid, revert it otherwise
    if (m_pTwinDoorSymbol)
    {
        m_pTwinDoorSymbol->DetachObserver(this);
        DetachObserver(m_pTwinDoorSymbol);
    }
}

ZBBPDoorSymbol::ZBBPDoorSymbol(const ZBBPDoorSymbol& src)
{
    *this = src;
}

ZBBPDoorSymbol& ZBBPDoorSymbol::operator=(const ZBBPDoorSymbol& src)
{
    // todo -cCheck -oJean: on 26.09.2019, check if this modification is valid, revert it otherwise
    if (m_pTwinDoorSymbol)
    {
        m_pTwinDoorSymbol->DetachObserver(this);
        DetachObserver(m_pTwinDoorSymbol);
    }

    // Call the base class assignement operator
    ZBSymbol::operator=((const ZBSymbol&)src);

    m_DisplayPreview = src.m_DisplayPreview;
    m_TwinDoorRefNumber = src.m_TwinDoorRefNumber;
    m_pTwinDoorSymbol = src.m_pTwinDoorSymbol;

    // todo -cCheck -oJean: on 26.09.2019, check if this modification is valid, revert it otherwise
    if (m_pTwinDoorSymbol)
    {
        AttachObserver(m_pTwinDoorSymbol);
        m_pTwinDoorSymbol->AttachObserver(this);
    }

    return *this;
}

CODComponent* ZBBPDoorSymbol::Dup() const
{
    return (new ZBBPDoorSymbol(*this));
}

ZDProcessGraphModelMdl* ZBBPDoorSymbol::GetModelDoor()
{
    ASSERT(ISA(m_pModel, ZDProcessGraphModelMdl));

    return dynamic_cast<ZDProcessGraphModelMdl*>(m_pModel);
}

bool ZBBPDoorSymbol::SetDoorModel(ZDProcessGraphModelMdl* pModel)
{
    m_pModel = pModel;

    // And assign the right door name
    SetSymbolName(BuildSymbolName());

    // ***********************************************************************************************
    // JMR-MODIF - Le 1er mai 2006 - Redimensionne la zone de texte par rapport à la largeur du texte.
    CODTextComponent* pText = GetSymbolNameTextEdit();

    if (pText)
    {
        pText->SizeToText();
    }
    // ***********************************************************************************************

    return (m_pModel) ? true : false;
}

void ZBBPDoorSymbol::RecalculateTwinDoorReference(ZDProcessGraphModelMdl* pRootModel)
{
    // Nothing to do
    if (GetTwinDoorReferenceNumber() == -1 || !pRootModel)
    {
        return;
    }

    // Locate the other twin
    CODComponentSet* pSet = pRootModel->GetRoot()->FindSymbolByRefNumber(GetTwinDoorReferenceNumber());

    if (pSet && pSet->GetSize() > 0)
    {
        // If it is a door symbol
        if (pSet->GetAt(0) && ISA(pSet->GetAt(0), ZBBPDoorSymbol))
        {
            // todo -cCheck -oJean: on 26.09.2019, check if this modification is valid, revert it otherwise
            if (m_pTwinDoorSymbol)
            {
                m_pTwinDoorSymbol->DetachObserver(this);
                DetachObserver(m_pTwinDoorSymbol);
            }

            m_pTwinDoorSymbol = dynamic_cast<ZBBPDoorSymbol*>(pSet->GetAt(0));

            if (!m_pTwinDoorSymbol)
                return;

            // Check if the door name is correct,
            // then empty the twin door name
            if (m_pTwinDoorSymbol->GetTwinDoorReferenceNumber() == GetSymbolReferenceNumber())
            {
            }

            // todo -cCheck -oJean: on 26.09.2019, check if this modification is valid, revert it otherwise
            AttachObserver(m_pTwinDoorSymbol);
            m_pTwinDoorSymbol->AttachObserver(this);
        }
    }
}

void ZBBPDoorSymbol::SetTwinDoorReferenceNumber(int RefNumber)
{
    m_TwinDoorRefNumber = RefNumber;
}

void ZBBPDoorSymbol::RemoveTwinDoorSymbol(bool RemoveTwin /*= true*/)
{
    // If the parent is a model
    CODComponent* pMdl = GetParent();

    if (pMdl && ISA(pMdl, ZDProcessGraphModelMdl) && dynamic_cast<ZDProcessGraphModelMdl*>(pMdl)->GetRoot())
    {
        CODComponentSet* pSet =
            dynamic_cast<ZDProcessGraphModelMdl*>(pMdl)->GetRoot()->FindSymbolByRefNumber(GetTwinDoorReferenceNumber());

        if (pSet && pSet->GetSize() > 0)
        {
            // If it is a door symbol
            if (pSet->GetAt(0) && ISA(pSet->GetAt(0), ZBBPDoorSymbol))
            {
                ZBBPDoorSymbol* pDoor = dynamic_cast<ZBBPDoorSymbol*>(pSet->GetAt(0));

                // Check if the door name is correct, then empty the twin door name
                if (!RemoveTwin || pDoor->GetTwinDoorReferenceNumber() == GetSymbolReferenceNumber())
                {
                    if (RemoveTwin)
                    {
                        pDoor->SetTwinDoorReferenceNumber(-1);
                        pDoor->SetTwinDoorSymbol(NULL);
                    }

                    // and also empty our twin door name
                    SetTwinDoorReferenceNumber(-1);
                    SetTwinDoorSymbol(NULL);

                    // and remove the observer we set
                    DetachObserver(pDoor);
                    pDoor->DetachObserver(this);

                    if (!RemoveTwin)
                    {
                        SetDoorModel(NULL);
                    }
                }
            }
        }
    }
}

void ZBBPDoorSymbol::AssignTwinDoorSymbol(ZBBPDoorSymbol* pDoor)
{
    // todo -cCheck -oJean: on 26.09.2019, check if this modification is valid, revert it otherwise
    if (m_pTwinDoorSymbol)
    {
        m_pTwinDoorSymbol->DetachObserver(this);
        DetachObserver(m_pTwinDoorSymbol);
    }

    // Assign the twin door symbol
    m_pTwinDoorSymbol = pDoor;

    if (!pDoor)
        return;

    // Sets our twin door name to him
    SetTwinDoorReferenceNumber(pDoor->GetSymbolReferenceNumber());

    // Sets the twin door name to us
    pDoor->SetTwinDoorReferenceNumber(GetSymbolReferenceNumber());
    pDoor->SetTwinDoorSymbol(this);

    // attach this to the source reference
    AttachObserver(pDoor);
    pDoor->AttachObserver(this);
}

// JMR-MODIF - Le 3 septembre 2006 - Cette fonction permet de répercuter un style sur le jumeau d'un symbole.
BOOL ZBBPDoorSymbol::DuplicateStyleOnTwinSymbol()
{
    ZBBPDoorSymbol* m_TwinSymbol = GetTwinDoorSymbol();

    if (m_TwinSymbol != NULL)
    {
        return ZUODSymbolManipulator::CopySymbolStyle(this, m_TwinSymbol);
    }

    return FALSE;
}

void ZBBPDoorSymbol::OnSymbolNameChanged(CODComponent& Comp, const CString OldName)
{
    // Check if the old symbol name was used somewhere in this door symbol
    CODComponent* pComp = &Comp;

    // Check if a process and the same we pointed to
    if (ISA(pComp, ZBBPProcessSymbol) &&
        !dynamic_cast<ZBBPProcessSymbol*>(pComp)->IsChildModelRef() &&
        dynamic_cast<ZBBPProcessSymbol*>(pComp)->GetChildModel() == GetChildModel())
    {
        // And assign the right door name
        SetSymbolName(BuildSymbolName());

        // ***********************************************************************************************
        // JMR-MODIF - Le 1er mai 2006 - Redimensionne la zone de texte par rapport à la largeur du texte.
        CODTextComponent* pText = GetSymbolNameTextEdit();

        if (pText)
        {
            pText->SizeToText();
        }
        // ***********************************************************************************************
    }
}

void ZBBPDoorSymbol::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    ZBSymbol* pSymbol = static_cast<ZBSymbol*>(pSubject);

    // If it is a door symbol
    if (pSymbol && ISA(pSymbol, ZBBPDoorSymbol))
    {
        // Check if the twin door name we have has changed compared
        // to the door symbol we received the message
        if (GetTwinDoorReferenceNumber() != dynamic_cast<ZBBPDoorSymbol*>(pSymbol)->GetSymbolReferenceNumber())
        {
            // Then, reassign the new name
            SetTwinDoorReferenceNumber(dynamic_cast<ZBBPDoorSymbol*>(pSymbol)->GetSymbolReferenceNumber());
        }
    }
}

CString ZBBPDoorSymbol::BuildSymbolName()
{
    // If a model is defined
    if (m_pModel && ISA(m_pModel, ZDProcessGraphModelMdl))
    {
        // ***************************************************************************************************
        // JMR-MODIF - Le 1er mai 2006 - Suppression des guillemets dans le titre des portes.
/*
        CString DoorStr;
        DoorStr.Format( _T( "'%s'" ), reinterpret_cast<ZDProcessGraphModelMdl*>( m_pModel )->GetModelName() );
        return DoorStr;
*/

        return reinterpret_cast<ZDProcessGraphModelMdl*>(m_pModel)->GetModelName();
        // ***************************************************************************************************
    }

    return _T("");
}

// Drag and drop methods
bool ZBBPDoorSymbol::AcceptDropItem(CObject* pObj, CPoint pt)
{
    // JMR-MODIF - Le 19 décembre 2006 - Si le symbole n'est pas local, interdit l'opération de glisser-coller.
    if (!IsLocal())
    {
        return false;
    }

    return ZBSymbol::AcceptDropItem(pObj, pt);
}

bool ZBBPDoorSymbol::DropItem(CObject* pObj, CPoint pt)
{
    return ZBSymbol::DropItem(pObj, pt);
}

void ZBBPDoorSymbol::CopySymbolDefinitionFrom(CODSymbolComponent& src)
{
    // Class the base class method
    ZBSymbol::CopySymbolDefinitionFrom(src);

    if (ISA((&src), ZBBPDoorSymbol))
    {
        // todo -cCheck -oJean: on 26.09.2019, check if this modification is valid, revert it otherwise
        if (m_pTwinDoorSymbol)
        {
            m_pTwinDoorSymbol->DetachObserver(this);
            DetachObserver(m_pTwinDoorSymbol);
        }

        m_DisplayPreview = ((ZBBPDoorSymbol&)src).m_DisplayPreview;
        m_CommentRect = ((ZBBPDoorSymbol&)src).m_CommentRect;
        m_SubModelPathName = ((ZBBPDoorSymbol&)src).m_SubModelPathName;

        // The twin door name saves the name of the other door
        m_TwinDoorRefNumber = ((ZBBPDoorSymbol&)src).m_TwinDoorRefNumber;
        m_pTwinDoorSymbol = ((ZBBPDoorSymbol&)src).m_pTwinDoorSymbol;

        // todo -cCheck -oJean: on 26.09.2019, check if this modification is valid, revert it otherwise
        if (m_pTwinDoorSymbol)
        {
            AttachObserver(m_pTwinDoorSymbol);
            m_pTwinDoorSymbol->AttachObserver(this);
        }
    }
}

BOOL ZBBPDoorSymbol::Create(const CString Name /*= ""*/)
{
    m_IsInCreationProcess = true;

    BOOL RetValue = ZBSymbol::Create(IDR_BP_DOOR,
                                     AfxFindResourceHandle(MAKEINTRESOURCE(IDR_PACKAGE_SYM),
                                                           _T("Symbol")),
                                     Name);

    if (!CreateSymbolProperties())
    {
        RetValue = FALSE;
    }

    // Change some name's properties
    CODTextComponent* pText = GetSymbolNameTextEdit();

    if (pText)
    {
        pText->SetValue(OD_PROP_VERT_ALIGNMENT, TRUE);

        CODFontProperties* pFontProp = (CODFontProperties*)pText->GetProperty(OD_PROP_FONT);

        if (pFontProp != NULL)
        {
            pFontProp->SetFaceName(_T("Arial"));
            pFontProp->SetWeight(FW_NORMAL);
            pFontProp->SetPointSize(8);
            pText->SetProperty(pFontProp);
        }
    }

    m_IsInCreationProcess = false;

    return RetValue;
}

bool ZBBPDoorSymbol::OnPostCreation(CODModel* pModel /*= NULL*/, CODController* pCtrl /*= NULL*/)
{
    if (!ZBSymbol::OnPostCreation(pModel, pCtrl))
    {
        return false;
    }

    if (pModel && ISA(pModel, ZDProcessGraphModelMdlBP))
    {
        ZDProcessGraphModelMdlBP* pRootModel =
            reinterpret_cast<ZDProcessGraphModelMdlBP*>(reinterpret_cast<ZDProcessGraphModelMdlBP*>(pModel)->GetRoot());

        if (!pRootModel)
        {
            return false;
        }

        // filter object classes
        ZBRuntimeClassSet rtClasses;
        rtClasses.Add(RUNTIME_CLASS(ZBBPPageSymbol));
        rtClasses.Add(RUNTIME_CLASS(ZBBPProcessSymbol));

        ZVSelectModelSymbolDlg Dlg(pRootModel,
                                   ISD_DOOR_SELECTMODEL,
                                   Selectable_Model | Selectable_GraphPage,
                                   &rtClasses);

        if (Dlg.DoModal() == IDOK)
        {
            ZIProcessGraphModelViewport*    pNewVp = NULL;
            ZDProcessGraphModelMdl*            pSelectedModel = NULL;

            // If a page has been selected
            if (Dlg.GetSelectedPage() && Dlg.GetSelectedPage()->GetpModel())
            {
                pSelectedModel = Dlg.GetSelectedPage()->GetpModel();
            }

            // If a a model has been selected
            if (Dlg.GetSelectedModel() && ISA(Dlg.GetSelectedModel(), ZDProcessGraphModelMdl))
            {
                pSelectedModel = dynamic_cast<ZDProcessGraphModelMdl*>(Dlg.GetSelectedModel());
            }

            if (pSelectedModel)
            {
                // Assign the model
                SetDoorModel(pSelectedModel);

                // And finally, open the model
                if (pCtrl)
                {
                    pNewVp =
                        dynamic_cast<ZDProcessGraphModelControllerBP*>(pCtrl)->BrowseModel(pSelectedModel,
                                                                                           pSelectedModel->GetParent());
                }
            }

            // Now if the page and the model exist
            // Check if another Page symbol is already in
            // If not, create one with a link to this page
            if (m_pModel && pNewVp && pCtrl)
            {
                CODNodeArray Nodes;
                size_t ElementCount = dynamic_cast<ZDProcessGraphModelMdlBP*>(m_pModel)->GetBPDoorSymbols(Nodes);
                bool Found = false;
                ZBBPDoorSymbol* pDoorFound = NULL;

                for (size_t nNodeIdx = 0; nNodeIdx < ElementCount; ++nNodeIdx)
                {
                    IODNode* pINode = Nodes.GetAt(nNodeIdx);
                    pDoorFound = static_cast<ZBBPDoorSymbol*>(pINode);

                    if (!pDoorFound || !pDoorFound->GetChildModel())
                    {
                        continue;
                    }

                    // If the door symbol contains a twin door name equivalent
                    // to us, we found it
                    if (pDoorFound->GetTwinDoorReferenceNumber() == GetSymbolReferenceNumber())
                    {
                        Found = true;
                        break;
                    }
                }

                // If we don't found the right symbol, add a page symbol on
                // this new model pointing to the initial model
                if (Found == false)
                {
                    dynamic_cast<ZDProcessGraphModelControllerBP*>(pNewVp->GetModelController())->InsertDoorSymbol();
                    CODComponent* pNewSymbolInserted = pNewVp->GetModelController()->InsertSymbol(0, CPoint(30, 30), false);

                    if (pNewSymbolInserted && ISA(pNewSymbolInserted, ZBBPDoorSymbol))
                    {
                        dynamic_cast<ZBBPDoorSymbol*>(pNewSymbolInserted)->SetDoorModel(reinterpret_cast<ZDProcessGraphModelMdlBP*>(pModel));

                        // Assigns the twin door symbol
                        AssignTwinDoorSymbol(dynamic_cast<ZBBPDoorSymbol*>(pNewSymbolInserted));
                    }
                }
                else
                {
                    // Assigns the twin door symbol
                    AssignTwinDoorSymbol(dynamic_cast<ZBBPDoorSymbol*>(pDoorFound));
                }
            }

            // Build the message
            ZBDocObserverMsg DocMsg;
            AfxGetMainWnd()->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, (LPARAM)&DocMsg);
            return true;
        }
    }

    return false;
}

bool ZBBPDoorSymbol::OnPreDelete(CODModel* pModel /*= NULL*/, CODController* pCtrl /*= NULL*/)
{
    if (GetTwinDoorSymbol())
    {
        PSS_MsgBox mBox;

        if (mBox.Show(IDS_DELETEDOORSYM_CONF, MB_YESNO) == IDYES)
        {
            // Retrieve the owner model
            CODModel* pOwnerModel = GetTwinDoorSymbol()->GetOwnerModel();

            // Request the symbol deletion
            if (pOwnerModel)
            {
                dynamic_cast<ZDProcessGraphModelMdl*>(pOwnerModel)->DeleteComponent(GetTwinDoorSymbol());
            }

            return true;
        }

        // Don't delete the door symbol
        return false;
    }

    return true;
}

void ZBBPDoorSymbol::OnPostDoubleClick(CODModel* pModel /*= NULL*/, CODController* pCtrl /*= NULL*/)
{
    if (GetTwinDoorSymbol())
    {
        // ensure the symbol visible
        if (pModel && ISA(pModel, ZDProcessGraphModelMdl)) // Check the model type to be able to cast the controller
        {
            dynamic_cast<ZDProcessGraphModelController*>(pCtrl)->EnsureSymbolVisible(GetTwinDoorSymbol());
        }
    }
}

void ZBBPDoorSymbol::AdjustElementPosition()
{
    ZBSymbol::AdjustElementPosition();
}

void ZBBPDoorSymbol::OnDraw(CDC* pDC)
{
    ZBSymbol::OnDraw(pDC);
}

BOOL ZBBPDoorSymbol::OnDoubleClick()
{
    return TRUE;
}

bool ZBBPDoorSymbol::OnToolTip(CString& ToolTipText, CPoint point, ToolTipMode ToolTip /*= NormalToolTip*/)
{
    // If a model is defined
    if (m_pModel && ISA(m_pModel, ZDProcessGraphModelMdl))
    {
        ToolTipText.Format(IDS_FS_BPDOOR_TOOLTIP,
            (const char*)(reinterpret_cast<ZDProcessGraphModelMdl*>(m_pModel)->GetModelName()));
    }
    else ToolTipText.LoadString(IDS_FS_BPDOOR_ERR_TOOLTIP);

    if (ToolTip == ZBSymbol::DesignToolTip)
    {
        // From now do nothing,
        // need to implement the result of the control checking
        // TODO
    }

    return true;
}

void ZBBPDoorSymbol::Serialize(CArchive& ar)
{
    // Serialize the canvas model.
    ZBSymbol::Serialize(ar);

    // Only if the object is serialize from and to a document
    if (ar.m_pDocument)
    {
        if (ar.IsStoring())
        {
            TRACE(_T("ZBBPDoorSymbol::Serialize : Start Save\n"));

            ar << (WORD)m_DisplayPreview;
            ar << m_TwinDoorRefNumber;

            TRACE(_T("ZBBPDoorSymbol::Serialize : End Save\n"));
        }
        else
        {
            TRACE(_T("ZBBPDoorSymbol::Serialize : Start Read\n"));

            WORD wValue;
            ar >> wValue;
            m_DisplayPreview = (wValue == 0) ? false : true;
            ar >> m_TwinDoorRefNumber;

            TRACE(_T("ZBBPDoorSymbol::Serialize : End Read\n"));
        }

        if (m_pModel)
            m_pModel->SetName(GetSymbolName());
    }
}
