// ZBBPPageSymbol.cpp: implementation of the ZBBPPageSymbol class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "zBaseSym\zBaseSymRes.h"
#include "ZBBPPageSymbol.h"

#include "ProcGraphModelMdlBP.h"
#include "ProcGraphModelCtlrBP.h"
#include "zModel\ProcGraphModelVp.h"
#include "zModel\ZDProcessGraphPage.h"

#include "zModel\ZVInsertLinkModelPageDlg.h"
#include "ZBBPProcessSymbol.h"

#include "zModel\ZBDocObserverMsg.h"

// JMR-MODIF - Le 30 août 2006 - Ajout de l'en-tête ZUODSymbolManipulator.
#include "zModel\ZUODSymbolManipulator.h"

#include "zBaseLib\PSS_MsgBox.h"
#include "zModelBPRes.h"
#include "zBaseLib\PSS_DrawFunctions.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 3 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(ZBBPPageSymbol, ZBSymbol, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBBPPageSymbol::ZBBPPageSymbol(const CString Name /*= ""*/)
    : m_DisplayPreview(false),
    m_pPage(NULL),
    m_pTwinPageSymbol(NULL),
    m_TwinPageRefNumber(-1)
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

ZBBPPageSymbol::~ZBBPPageSymbol()
{}

ZBBPPageSymbol::ZBBPPageSymbol(const ZBBPPageSymbol& src)
{
    *this = src;
}

ZBBPPageSymbol& ZBBPPageSymbol::operator=(const ZBBPPageSymbol& src)
{
    // Call the base class assignement operator
    ZBSymbol::operator=((const ZBSymbol&)src);

    m_DisplayPreview = src.m_DisplayPreview;
    m_TwinPageRefNumber = src.m_TwinPageRefNumber;
    m_pTwinPageSymbol = src.m_pTwinPageSymbol;

    return *this;
}

CODComponent* ZBBPPageSymbol::Dup() const
{
    return (new ZBBPPageSymbol(*this));
}

ZDProcessGraphModelMdl* ZBBPPageSymbol::GetModelPage()
{
    return (GetPage()) ? GetPage()->GetModel() : NULL;
}

bool ZBBPPageSymbol::SetPageModel(ZDProcessGraphModelMdl* pModel)
{
    // Find the page corresponding to the model with extending to sub-model
    if (pModel)
    {
        m_pPage = pModel->GetRoot()->FindModelPage(pModel, true);
    }
    else
    {
        m_pPage = NULL;
    }

    m_pModel = pModel;

    // And assign the right page name
    SetSymbolName(BuildSymbolName());

    // ***********************************************************************************************
    // JMR-MODIF - Le 1er mai 2006 - Redimensionne la zone de texte par rapport à la largeur du texte.
    CODTextComponent* pText = GetSymbolNameTextEdit();

    if (pText)
    {
        pText->SizeToText();
    }
    // ***********************************************************************************************

    return (m_pPage) ? true : false;
}

void ZBBPPageSymbol::RecalculateTwinPageReference(ZDProcessGraphModelMdl* pRootModel)
{
    // First, find the right model pointer
    if (!m_PageName.IsEmpty() && pRootModel && ISA(pRootModel, ZDProcessGraphModelMdlBP))
    {
        // Find the page by its name
        m_pPage = reinterpret_cast<ZDProcessGraphModelMdlBP*>(pRootModel)->FindPage(m_PageName);

        // And assign the right child model if no submodel pathname defined
        if (m_SubModelPathName.IsEmpty())
        {
            if (m_pPage)
            {
                m_pModel = m_pPage->GetModel();
            }
        }
        else
        {
            m_pModel =
                reinterpret_cast<ZDProcessGraphModelMdlBP*>(pRootModel)->FindModelFromPath(m_SubModelPathName,
                                                                                           true);
        }
    }

    // Nothing to do
    if (GetTwinPageReferenceNumber() == -1 || !pRootModel)
    {
        return;
    }

    // Locate the other twin
    CODComponentSet* pSet = pRootModel->GetRoot()->FindSymbolByRefNumber(GetTwinPageReferenceNumber());

    if (pSet && pSet->GetSize() > 0)
    {
        // If it is a door symbol
        if (pSet->GetAt(0) && ISA(pSet->GetAt(0), ZBBPPageSymbol))
        {
            m_pTwinPageSymbol = dynamic_cast<ZBBPPageSymbol*>(pSet->GetAt(0));

            // Check if the door name is correct,
            // then empty the twin door name
            if (m_pTwinPageSymbol->GetTwinPageReferenceNumber() == GetSymbolReferenceNumber())
            {
            }
        }
    }
}

void ZBBPPageSymbol::SetTwinPageReferenceNumber(int RefNumber)
{
    m_TwinPageRefNumber = RefNumber;
}

void ZBBPPageSymbol::RemoveTwinPageSymbol(bool RemoveTwin /*= true*/)
{
    // If the parent is a model
    CODComponent* pMdl = GetParent();

    if (pMdl && ISA(pMdl, ZDProcessGraphModelMdl) && dynamic_cast<ZDProcessGraphModelMdl*>(pMdl)->GetRoot())
    {
        CODComponentSet* pSet =
            dynamic_cast<ZDProcessGraphModelMdl*>(pMdl)->GetRoot()->FindSymbolByRefNumber(GetTwinPageReferenceNumber());

        if (pSet && pSet->GetSize() > 0)
        {
            // If it is a door symbol
            if (pSet->GetAt(0) && ISA(pSet->GetAt(0), ZBBPPageSymbol))
            {
                ZBBPPageSymbol* pPage = dynamic_cast<ZBBPPageSymbol*>(pSet->GetAt(0));

                // Check if the page name is correct,
                // then empty the twin page name
                if (!RemoveTwin || pPage->GetTwinPageReferenceNumber() == GetSymbolReferenceNumber())
                {
                    if (RemoveTwin)
                    {
                        pPage->SetTwinPageReferenceNumber(-1);
                        pPage->SetTwinPageSymbol(NULL);
                    }

                    // and also empty our twin page name
                    SetTwinPageReferenceNumber(-1);
                    SetTwinPageSymbol(NULL);

                    // and remove the observer we set
                    DetachObserver(pPage);
                    pPage->DetachObserver(this);

                    // Remove the assignement
                    if (!RemoveTwin)
                    {
                        SetPageModel(NULL);
                    }
                }
            }
        }
    }
}

void ZBBPPageSymbol::AssignTwinPageSymbol(ZBBPPageSymbol* pPage)
{
    // Page assignement
    m_pTwinPageSymbol = pPage;

    // Sets our twin door name to him
    SetTwinPageReferenceNumber(pPage->GetSymbolReferenceNumber());

    // Sets the twin door name to us
    pPage->SetTwinPageReferenceNumber(GetSymbolReferenceNumber());
    pPage->SetTwinPageSymbol(this);

    // And attach this to the source reference
    AttachObserver(pPage);
    pPage->AttachObserver(this);
}

// JMR-MODIF - Le 3 septembre 2006 - Cette fonction permet de répercuter un style sur le jumeau d'un symbole.
BOOL ZBBPPageSymbol::DuplicateStyleOnTwinSymbol()
{
    ZBBPPageSymbol* m_TwinSymbol = GetTwinPageSymbol();

    if (m_TwinSymbol != NULL)
    {
        return ZUODSymbolManipulator::CopySymbolStyle(this, m_TwinSymbol);
    }

    return FALSE;
}

void ZBBPPageSymbol::OnPageNameChanged(ZDProcessGraphPage* pPage, const CString OldName)
{
    if (pPage == GetPage())
    {
        // Bug about renaming the page name.
        // In fact the model name isn't changed. Therefore, in the navigation and the
        // web generation, the old name is displayed.
        pPage->GetModel()->SetModelName(pPage->GetPageName());

        // And assign the right page name
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

void ZBBPPageSymbol::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    ZBSymbol* pSymbol = static_cast<ZBSymbol*>(pSubject);

    // If it is a page symbol
    if (pSymbol && ISA(pSymbol, ZBBPPageSymbol))
    {
        // Check if the twin door name we have has changed compared
        // to the door symbol we received the message
        if (GetTwinPageReferenceNumber() != dynamic_cast<ZBBPPageSymbol*>(pSymbol)->GetSymbolReferenceNumber())
        {
            // Then, reassign the new name
            SetTwinPageReferenceNumber(dynamic_cast<ZBBPPageSymbol*>(pSymbol)->GetSymbolReferenceNumber());
        }
    }
}

CString ZBBPPageSymbol::BuildSymbolName()
{
    // If a page is defined
    if (m_pPage)
    {
        // *********************************************************************************
        // JMR-MODIF - Le 1er mai 2006 - Suppression des guillemets dans le titre des pages.
/*
        CString PageStr;
        PageStr.Format( _T( "'%s'" ), m_pPage->GetPageName() );

        return PageStr;
*/

        return m_pPage->GetPageName();
        // *********************************************************************************
    }

    return _T("");
}

// Drag and drop methods
bool ZBBPPageSymbol::AcceptDropItem(CObject* pObj, CPoint pt)
{
    // JMR-MODIF - Le 19 décembre 2006 - Si le symbole n'est pas local, interdit l'opération de glisser-coller.
    if (!IsLocal())
    {
        return false;
    }

    return ZBSymbol::AcceptDropItem(pObj, pt);
}

bool ZBBPPageSymbol::DropItem(CObject* pObj, CPoint pt)
{
    return ZBSymbol::DropItem(pObj, pt);
}

void ZBBPPageSymbol::CopySymbolDefinitionFrom(CODSymbolComponent& src)
{
    // Class the base class method
    ZBSymbol::CopySymbolDefinitionFrom(src);

    if (ISA((&src), ZBBPPageSymbol))
    {
        m_DisplayPreview = ((ZBBPPageSymbol&)src).m_DisplayPreview;

        m_CommentRect = ((ZBBPPageSymbol&)src).m_CommentRect;
        m_PageName = ((ZBBPPageSymbol&)src).m_PageName;
        m_SubModelPathName = ((ZBBPPageSymbol&)src).m_SubModelPathName;

        // The twin page name saves the name of the other page
        m_TwinPageRefNumber = ((ZBBPPageSymbol&)src).m_TwinPageRefNumber;
        m_pTwinPageSymbol = ((ZBBPPageSymbol&)src).m_pTwinPageSymbol;
        m_pPage = ((ZBBPPageSymbol&)src).m_pPage;
    }
}

bool ZBBPPageSymbol::CreateSymbolProperties()
{
    if (!ZBSymbol::CreateSymbolProperties())
    {
        return false;
    }

    return true;
}

bool ZBBPPageSymbol::FillProperties(ZBPropertySet&    PropSet,
                                    bool            NumericValue    /*= false*/,
                                    bool            GroupValue        /*= false*/)
{
    if (!ZBSymbol::FillProperties(PropSet, NumericValue, GroupValue))
    {
        return false;
    }

    return true;
}

bool ZBBPPageSymbol::SaveProperties(ZBPropertySet& PropSet)
{
    if (!ZBSymbol::SaveProperties(PropSet))
    {
        return false;
    }

    RefreshAttributeTextArea(true);

    return true;
}

BOOL ZBBPPageSymbol::Create(const CString Name /*= ""*/)
{
    m_IsInCreationProcess = true;

    BOOL RetValue = ZBSymbol::Create(IDR_BP_PAGE,
                                     AfxFindResourceHandle(MAKEINTRESOURCE(IDR_PACKAGE_SYM), _T("Symbol")),
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

bool ZBBPPageSymbol::OnPostCreation(CODModel* pModel /*= NULL*/, CODController* pCtrl /*= NULL*/)
{
    if (!ZBSymbol::OnPostCreation(pModel, pCtrl))
    {
        return false;
    }

    if (pModel && ISA(pModel, ZDProcessGraphModelMdlBP))
    {
        ZDProcessGraphModelMdlBP* pRootModel =
            dynamic_cast<ZDProcessGraphModelMdlBP*>(reinterpret_cast<ZDProcessGraphModelMdlBP*>(pModel)->GetRoot());

        if (!pRootModel)
        {
            return false;
        }

        CString NewPage = pRootModel->GetValidNextPageName();

        // Get the page of this model
        ZDProcessGraphPage* pPageFromModel =
            pRootModel->FindModelPage(reinterpret_cast<ZDProcessGraphModelMdlBP*>(pModel), true);

        if (!pPageFromModel)
        {
            return false;
        }

        // and then get the owner model
        ZDProcessGraphModelMdl* pOwnerModel = pRootModel->GetOwnerPageModel(pPageFromModel);

        PSS_RuntimeClassSet rtClasses;

        rtClasses.Add(RUNTIME_CLASS(ZBBPPageSymbol));
        rtClasses.Add(RUNTIME_CLASS(ZBBPProcessSymbol));

        ZVInsertLinkModelPageDlg Dlg((pOwnerModel) ? pOwnerModel : pRootModel,
                                     NewPage,
                                     pRootModel->GetExistingPageNameArray(),
                                     &rtClasses);

        if (Dlg.DoModal() == IDOK)
        {
            ZIProcessGraphModelViewport* pNewVp = NULL;

            // If a new page must be inserted
            if (Dlg.ChooseInsertNewPage())
            {
                ZDProcessGraphModelMdl* pNewModel =
                    pRootModel->CreateEmptyModel(Dlg.GetPageName(), reinterpret_cast<ZDProcessGraphModelMdl*>(pModel));

                // Create the new page
                m_pPage = pRootModel->CreateNewPage(pNewModel, Dlg.GetPageName(), Dlg.GetParentModel());

                // And assign the right child model
                if (m_pPage)
                {
                    m_pModel = m_pPage->GetModel();
                }

                // And assign the right page name
                SetSymbolName(BuildSymbolName());

                // ***********************************************************************************************
                // JMR-MODIF - Le 1er mai 2006 - Redimensionne la zone de texte par rapport à la largeur du texte.
                CODTextComponent* pText = GetSymbolNameTextEdit();

                if (pText)
                {
                    pText->SizeToText();
                }
                // ***********************************************************************************************

                // And finally, open the model
                if (pCtrl)
                {
                    pNewVp =
                        dynamic_cast<ZDProcessGraphModelControllerBP*>(pCtrl)->BrowseModel(pNewModel,
                                                                                           reinterpret_cast<ZDProcessGraphModelMdl*>(pModel));
                }
            }
            // A link to an existing page is requested
            else
            {
                // Find the page by its name
                m_pPage = pRootModel->FindPage(Dlg.GetPageName());

                // And assign the right child model
                if (m_pPage)
                {
                    m_pModel = m_pPage->GetModel();

                    // And assign the right page name
                    SetSymbolName(BuildSymbolName());

                    // **************************************************************************************
                    // JMR-MODIF - Le 1er mai 2006 - Redimensionne la zone par rapport à la largeur du texte.
                    CODTextComponent* pText = GetSymbolNameTextEdit();

                    if (pText)
                    {
                        pText->SizeToText();
                    }
                    // **************************************************************************************

                    // And finally, open the model
                    if (pCtrl)
                    {
                        pNewVp =
                            dynamic_cast<ZDProcessGraphModelControllerBP*>(pCtrl)->BrowseModel(reinterpret_cast<ZDProcessGraphModelMdl*>(m_pModel),
                                                                                               reinterpret_cast<ZDProcessGraphModelMdl*>(pModel));
                    }
                }
            }

            // Now if the page and the model exist
            // Check if another Page symbol is already in
            // If not, create one with a link to this page
            if (m_pPage && m_pModel && pCtrl)
            {
                CODNodeArray    Nodes;
                size_t            ElementCount = dynamic_cast<ZDProcessGraphModelMdlBP*>(m_pModel)->GetBPPageSymbols(Nodes);
                bool            Found = false;
                ZBBPPageSymbol*    pPageFound = NULL;

                for (size_t nNodeIdx = 0; nNodeIdx < ElementCount; ++nNodeIdx)
                {
                    IODNode* pINode = Nodes.GetAt(nNodeIdx);
                    pPageFound = static_cast<ZBBPPageSymbol*>(pINode);

                    if (!pPageFound || !pPageFound->GetPage())
                    {
                        continue;
                    }

                    // If the page symbol contains a twin page name equivalent
                    // to us, we found it
                    if (pPageFound->GetTwinPageReferenceNumber() == GetSymbolReferenceNumber())
                    {
                        Found = true;
                        break;
                    }
                }

                // If we don't found the right symbol, add a page symbol on
                // this new model pointing to the initial model
                if (Found == false)
                {
                    dynamic_cast<ZDProcessGraphModelControllerBP*>(pNewVp->GetModelController())->InsertPageSymbol();

                    CODComponent* pNewSymbolInserted =
                        pNewVp->GetModelController()->InsertSymbol(0, CPoint(30, 30), false);

                    if (pNewSymbolInserted && ISA(pNewSymbolInserted, ZBBPPageSymbol))
                    {
                        dynamic_cast<ZBBPPageSymbol*>(pNewSymbolInserted)->SetPageModel(reinterpret_cast<ZDProcessGraphModelMdlBP*>(pModel));

                        // Assigns the twin door symbol
                        AssignTwinPageSymbol(dynamic_cast<ZBBPPageSymbol*>(pNewSymbolInserted));
                    }
                }
                else
                {
                    // Assigns the twin door symbol
                    AssignTwinPageSymbol(dynamic_cast<ZBBPPageSymbol*>(pPageFound));
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

bool ZBBPPageSymbol::OnPreDelete(CODModel* pModel /*= NULL*/, CODController* pCtrl /*= NULL*/)
{
    if (GetTwinPageSymbol())
    {
        PSS_MsgBox mBox;

        if (mBox.Show(IDS_DELETEPAGESYM_CONF, MB_YESNO) == IDYES)
        {
            // Request the symbol deletion
            if (pModel && ISA(pModel, ZDProcessGraphModelMdl))
            {
                dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->DeleteComponent(GetTwinPageSymbol());
            }

            return true;
        }

        // Don't delete the door symbol
        return false;
    }

    return true;
}

void ZBBPPageSymbol::OnPostDoubleClick(CODModel* pModel /*= NULL*/, CODController* pCtrl /*= NULL*/)
{
    if (GetTwinPageSymbol())
    {
        // Ensure the symbol visible, and check the model type to be able to cast the controller
        if (pModel && ISA(pModel, ZDProcessGraphModelMdl))
        {
            dynamic_cast<PSS_ProcessGraphModelController*>(pCtrl)->EnsureSymbolVisible(GetTwinPageSymbol());
        }
    }
}

void ZBBPPageSymbol::AdjustElementPosition()
{
    ZBSymbol::AdjustElementPosition();

    // Recalculate the comment rect
    CODTextComponent* pText = GetCommentTextEdit();

    if (pText)
    {
        m_CommentRect = pText->GetBounds();
        m_CommentRect.DeflateRect(1, 1);
    }

    // Calculate the position of symbols
    CRect SymbolPosition = GetBounds();
}

void ZBBPPageSymbol::OnDraw(CDC* pDC)
{
    ZBSymbol::OnDraw(pDC);
}

BOOL ZBBPPageSymbol::CreateEmptyChildModel(CODModel* pParent)
{
    // Can't create an empty child model.
    // Must be done by page creation.
    return FALSE;
}

BOOL ZBBPPageSymbol::OnDoubleClick()
{
    return TRUE;
}

bool ZBBPPageSymbol::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    if (GetPage() && GetPage()->GetPageName())
    {
        toolTipText.Format(IDS_FS_BPPAGE_TOOLTIP,
            (const char*)GetPage()->GetPageName());
    }
    else
    {
        toolTipText.LoadString(IDS_FS_BPPAGE_ERR_TOOLTIP);
    }

    if (mode == ZBSymbol::IE_TT_Design)
    {
        // From now do nothing,
        // need to implement the result of the control checking
        // TODO
    }

    return true;
}

void ZBBPPageSymbol::Serialize(CArchive& ar)
{
    // Serialize the canvas model.
    ZBSymbol::Serialize(ar);

    // Only if the object is serialize from and to a document
    if (ar.m_pDocument)
    {
        if (ar.IsStoring())
        {
            TRACE(_T("ZBBPPageSymbol::Serialize : Start Save\n"));

            CString EmptyString(_T(""));

            ar << (WORD)m_DisplayPreview;
            ar << m_pPage->GetPageName();

            // If the model is different from the model page,
            // serialize the model name and put null to model
            if (m_pModel && ISA(m_pModel, ZDProcessGraphModelMdl) && m_pModel != m_pPage->GetModel())
            {
                ar << reinterpret_cast<ZDProcessGraphModelMdl*>(m_pModel)->GetAbsolutePath();
            }
            else
            {
                ar << EmptyString;
            }

            ar << m_TwinPageRefNumber;

            TRACE(_T("ZBBPPageSymbol::Serialize : End Save\n"));
        }
        else
        {
            TRACE(_T("ZBBPPageSymbol::Serialize : Start Read\n"));

            WORD wValue;
            ar >> wValue;
            m_DisplayPreview = (wValue == 0) ? false : true;

            ar >> m_PageName;
            m_pPage = NULL;

            ar >> m_SubModelPathName;
            ar >> m_TwinPageRefNumber;

            TRACE(_T("ZBBPPageSymbol::Serialize : End Read\n"));
        }
    }
}
