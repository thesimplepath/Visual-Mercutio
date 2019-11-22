// ZBSymbol.cpp: implementation of the ZBSymbol class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBSymbol.h"

#include "ZBSymbolEdit.h"
#include "zProperty\ZBDynamicProperties.h"

#include "ZUODSymbolManipulator.h"

#include "ProcGraphModelMdl.h"
#include "zBaseLib\PSS_BaseDocument.h"

#include "ZBDocObserverMsg.h"
#include "ZBSymbolObserverMsg.h"

// Resource include
#include "zModelRes.h"
#include "PSS_ResIDs.h"

#include "zBaseLib\PSS_MsgBox.h"

#include "ZBBasicProp.h"

#include "Views\OdGuids.h"
#include "zBaseLib\PSS_DrawFunctions.h"

//////////////////////////////////////////////////////////////////////
// Static members definition
PSS_Bitmap ZBSymbol::m_ShortCutBitmap;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 septembre 2005 - Ajout de la décoration unicode _T( ), nettoyage du code inutilisé.

//////////////////////////////////////////////////////////////////////
// Dom November 2002
// Due to a bug the can select flag had been set to false
// when migrating the ObjectiveViews version 8.1
#define _CANSELECTCONVERTER 1

IMPLEMENT_SERIAL(ZBSymbol, CODSymbolComponent, g_DefVersion)

// **********************************************************************************************************************
// *                                            Construction/Destruction                                                *
// **********************************************************************************************************************

// Constructeur par défaut.
ZBSymbol::ZBSymbol() : ZBExtAppPropertyMgr(this),
m_DynamicPropManager(NULL),
m_IsLocal(true),
m_pReference(NULL),
m_pModel(NULL),
m_InitialLineWidth(1),
m_InitialLineColor(defCOLOR_BLACK),
m_CurrentLineColor(defCOLOR_BLACK),
m_InitialLabelLineWidth(1),
m_InitialLabelLineColor(defCOLOR_BLACK),
m_CurrentLabelLineColor(defCOLOR_BLACK),
m_IsInCreationProcess(false),
// JMR-MODIF - Le 7 février 2006 - Initialisation du flag m_IsCopy.
m_IsCopy(FALSE)
{
    SetSymbol(this);

    // Work in absolute relative for the attributes
    m_RelativeCoordinates = true;

    // A reinitialization is necessary at creation
    m_ReinitializeAreaAtCreation = true;

    CreateSymbolProperties();
}

// Constructeur de copie.
ZBSymbol::ZBSymbol(const ZBSymbol& src)
{
    *this = src;
}

// Destructeur.
ZBSymbol::~ZBSymbol()
{
    if (m_DynamicPropManager != NULL)
    {
        delete m_DynamicPropManager;
        m_DynamicPropManager = NULL;
    }
}

// **********************************************************************************************************************
// *                                                    Operators                                                        *
// **********************************************************************************************************************

ZBSymbol& ZBSymbol::operator=(const ZBSymbol& src)
{
    // Call the base class assignement operator
    CODSymbolComponent::operator=    ((const CODSymbolComponent&)src);
    ZBExtAppPropertyMgr::operator=    ((const ZBExtAppPropertyMgr&)src);
    ZBExtFilePropertyMgr::operator=    ((const ZBExtFilePropertyMgr&)src);
    ZVSymbolAttributes::operator=    ((const ZVSymbolAttributes&)src);

    m_IsLocal = src.m_IsLocal;
    m_Name = src.m_Name;
    m_NameOfReference = src.m_NameOfReference;
    m_Comment = src.m_Comment;
    m_ObjectPath = src.m_ObjectPath;
    m_pModel = src.m_pModel;
    m_DynamicPropManager = src.m_DynamicPropManager->Dup();

    return *this;
}

CODComponent* ZBSymbol::Dup() const
{
    return (new ZBSymbol(*this));
}

BOOL ZBSymbol::CreateEmptyChildModel(CODModel* pParent)
{
    return FALSE;
}

bool ZBSymbol::Match(const CString            What,
                     ZBPropertyAttributes*    pPropAttributes    /*= NULL*/,
                     bool                    CaseSensitive    /*= false*/,
                     bool                    PartialSearch    /*= false*/)
{
    if (!pPropAttributes)
    {
        return false;
    }

    ZBPropertySet PropSet;

    // Retrieve the property set from object
    FillProperties(PropSet);

    // Match the property set with the property attributes
    bool RetValue = pPropAttributes->Match(PropSet, What, CaseSensitive, PartialSearch);

    // Remove all properties
    ZBPropertyIterator i(&PropSet);
    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        delete pProp;
    }

    PropSet.RemoveAll();

    return RetValue;
}

bool ZBSymbol::GetDisplayTitleText() const
{
    return (AcceptDynamicAttributes()) ? m_Attributes.GetDisplayTitleText() : false;
}

void ZBSymbol::SetDisplayTitleText(bool value)
{
    if (AcceptDynamicAttributes())
    {
        m_Attributes.SetDisplayTitleText(value);

        if (GetAttributeTextEdit())
        {
            GetAttributeTextEdit()->SetText(GetAttributeString(&m_Attributes));
            RedrawSymbol();
        }
    }
}

void ZBSymbol::RefreshAttributeTextArea(bool Redraw)
{
    if (AcceptDynamicAttributes() && GetAttributeTextEdit())
    {
        GetAttributeTextEdit()->SetText(GetAttributeString(&m_Attributes));

        if (Redraw)
        {
            RedrawSymbol();
        }
    }
}

bool ZBSymbol::OnFillDefaultAttributes(ZBPropertyAttributes* pAttributes)
{
    if (AcceptDynamicAttributes() && GetAttributeTextEdit())
    {
        GetAttributeTextEdit()->SetText(GetAttributeString(pAttributes));
        RedrawSymbol();
    }

    return true;
}

bool ZBSymbol::OnChangeAttributes(ZBPropertyAttributes* pAttributes)
{
    if (AcceptDynamicAttributes() && GetAttributeTextEdit())
    {
        // Copy the new attributes first
        m_Attributes = *pAttributes;

        // Redraw the attribute text
        GetAttributeTextEdit()->SetText(GetAttributeString(pAttributes));
        RedrawSymbol();
    }

    return true;
}

CString ZBSymbol::GetAttributeString(ZBPropertyAttributes* pAttributes) const
{
    if (AcceptDynamicAttributes())
    {
        ZBPropertySet PropSet;

        // Retrieve the property set from object
        const_cast<ZBSymbol*>(this)->FillProperties(PropSet);

        // Now format the string
        CString str = pAttributes->GetString(&PropSet);

        // Remove all properties
        ZBPropertyIterator i(&PropSet);
        ZBProperty* pProp;

        for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
        {
            delete pProp;
        }

        PropSet.RemoveAll();

        // Return the string
        return str;
    }

    return _T("");
}

void ZBSymbol::CopySymbolDefinitionFrom(const CODSymbolComponent& src)
{
    if (ISA((&src), ZBSymbol))
    {
        // Don't use direct assignement, if
        // symbols are referenced, not notification will be done
        SetSymbolName(reinterpret_cast<const ZBSymbol&>(src).GetSymbolName());
        SetSymbolComment(reinterpret_cast<const ZBSymbol&>(src).GetSymbolComment());
        SetAbsolutePath(reinterpret_cast<const ZBSymbol&>(src).GetAbsolutePath());
        SetModel(const_cast<ZBSymbol&>(reinterpret_cast<const ZBSymbol&>(src)).GetModel());

        // Symbol is local
        m_IsLocal = true;

        // No reference
        m_pReference = NULL;
        m_NameOfReference.Empty();

        m_AllSymbolPosition = dynamic_cast<const ZBSymbol&>(src).m_AllSymbolPosition;
        m_ChildModelPathName = dynamic_cast<const ZBSymbol&>(src).m_ChildModelPathName;

        m_CurrentLineColor = dynamic_cast<const ZBSymbol&>(src).m_CurrentLineColor;
        m_CurrentLabelLineColor = dynamic_cast<const ZBSymbol&>(src).m_CurrentLabelLineColor;
        m_InitialLineColor = dynamic_cast<const ZBSymbol&>(src).m_InitialLineColor;
        m_InitialLineWidth = dynamic_cast<const ZBSymbol&>(src).m_InitialLineWidth;
        m_InitialLabelLineColor = dynamic_cast<const ZBSymbol&>(src).m_InitialLabelLineColor;
        m_InitialLabelLineWidth = dynamic_cast<const ZBSymbol&>(src).m_InitialLabelLineWidth;
        m_ShortCutBitmapPosition = dynamic_cast<const ZBSymbol&>(src).m_ShortCutBitmapPosition;

        m_ExternalApplications = dynamic_cast<const ZBSymbol&>(src).m_ExternalApplications;
        m_ExternalApplications.SetParent(this);

        m_ExternalFiles = dynamic_cast<const ZBSymbol&>(src).m_ExternalFiles;
        m_ExternalFiles.SetParent(this);

        m_DisplayNameArea = dynamic_cast<const ZBSymbol&>(src).m_DisplayNameArea;
        m_DisplayDescriptionArea = dynamic_cast<const ZBSymbol&>(src).m_DisplayDescriptionArea;
        m_DisplayAttributeArea = dynamic_cast<const ZBSymbol&>(src).m_DisplayAttributeArea;

        m_RelativeCoordinates = dynamic_cast<const ZBSymbol&>(src).m_RelativeCoordinates;
        m_Attributes = dynamic_cast<const ZBSymbol&>(src).m_Attributes;

        // JMR-MODIF - Le 6 février 2006 - Nettoyage des memory leaks, destruction de la variable
        // m_DynamicPropManager avant de tenter d'en assigner une nouvelle.
        if (m_DynamicPropManager)
        {
            delete m_DynamicPropManager;
            m_DynamicPropManager = NULL;
        }

        m_DynamicPropManager = dynamic_cast<const ZBSymbol&>(src).m_DynamicPropManager->Dup();

        // Now sets the right area name
        ZUODSymbolManipulator::MatchSymbolAreaName(this, const_cast<CODSymbolComponent*>(&src));
    }
}

void ZBSymbol::SetIsLocal(bool value /*= true*/)
{
    if (value == true)
    {
        SetCurrentLineColor(m_InitialLineColor);
        SetCurrentLabelColor(m_InitialLabelLineColor);
    }
    else
        // Sets the new line color to magenta and the line width to 2
    {
        SetCurrentLineColor(defCOLOR_BLUE);
        SetCurrentLabelColor(defCOLOR_BLUE);
    }

    m_IsLocal = value;

    // Now redraw the symbol
    RedrawSymbol();
}

// JMR-MODIF - Le 22 juillet 2007 - Mets à jour les données graphiques d'un symbole en fonction des risques.
void ZBSymbol::UpdateGraphicFromRisk(COLORREF Color, BOOL Italic)
{
    ZUODSymbolManipulator::ChangeTextColor(this, Color);
    ZUODSymbolManipulator::SetTextItalic(this, Italic);

    RedrawSymbol();
}

void ZBSymbol::ShowInError(bool value /*= true*/)
{
    if (value == true)
    {
        SetCurrentLineColor(defCOLOR_RED);
        SetCurrentLabelColor(defCOLOR_RED);
    }
    else
    {
        // Sets the new line color to magenta
        if (IsLocal())
        {
            SetCurrentLineColor(m_InitialLineColor);
            SetCurrentLabelColor(m_InitialLabelLineColor);
        }
        else
        {
            SetCurrentLineColor(defCOLOR_BLUE);
            SetCurrentLabelColor(defCOLOR_BLUE);
        }
    }

    // Now redraw the symbol
    RedrawSymbol();
}

void ZBSymbol::ApplyFormatFromObject(CODSymbolComponent&    Object,
                                     bool                    Font    /*= true*/,
                                     bool                    Fill    /*= true*/,
                                     bool                    Line    /*= true*/)
{
    ZUODSymbolManipulator::ApplyFormatFromObject(this, Object, Font, Fill, Line);
}

CODComponent* ZBSymbol::GetLocalSymbol()
{
    if (IsLocal())
    {
        return NULL;
    }

    ZDProcessGraphModelMdl* pRootModel = dynamic_cast<ZDProcessGraphModelMdl*>(GetRootModel());

    if (pRootModel)
    {
        CODComponentSet* pSet = pRootModel->FindSymbol(GetSymbolName(), _T(""), true, true, true);

        // If found, return it
        if (pSet && pSet->GetSize() > 0 && pSet->GetAt(0))
        {
            return pSet->GetAt(0);
        }
    }

    return NULL;
}

CODComponentSet* ZBSymbol::GetReferenceSymbols()
{
    if (!IsLocal())
    {
        return NULL;
    }

    ZDProcessGraphModelMdl* pRootModel = dynamic_cast<ZDProcessGraphModelMdl*>(GetRootModel());

    if (pRootModel)
    {
        CODComponentSet*  pSet = pRootModel->FindSymbol(GetSymbolName(), _T(""), true, true, false);

        if (pSet)
        {
            // Remove us from the set
            for (int i = 0; i < pSet->GetSize(); ++i)
            {
                if (pSet->GetAt(i) == this)
                {
                    pSet->RemoveAt(i);
                    --i;
                }
            }
        }

        return pSet;
    }

    return NULL;
}

// Create the symbol name label
CODLabelComponent* ZBSymbol::CreateSymbolLabel()
{
    return CreateLabel(_T("Test"));
}

// Start the edition of the symbol name
void ZBSymbol::EditSymbolName()
{
    int                    NumLabels = GetNumLabels();
    CODLabelComponent*    pSymbolLabel = NULL;

    if (NumLabels == 0)
    {
        pSymbolLabel = CreateSymbolLabel();
    }
    else
    {
        CODLabelComponent* pTempLabel;

        for (int i = 0; i < NumLabels; ++i)
        {
            pTempLabel = GetLabel(i);
        }
    }
}

CODModel* ZBSymbol::GetOwnerModel()
{
    // If the parent is a model
    CODComponent* pComp = GetParent();

    while (pComp)
    {
        // If a model, return it
        if (pComp && ISA(pComp, ZDProcessGraphModelMdl))
        {
            return dynamic_cast<CODModel*>(pComp);
        }

        // Otherwise retreive its parent
        pComp = pComp->GetParent();
    }

    return NULL;
}

CODModel* ZBSymbol::GetRootModel()
{
    CODModel* pModel = GetOwnerModel();

    // If the model is a GraphModel, return the root model
    if (pModel && ISA(pModel, ZDProcessGraphModelMdl))
    {
        return dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetRoot();
    }

    // Otherwise, return NULL;
    return NULL;
}

void ZBSymbol::SetModifiedFlag(BOOL Value /*= TRUE*/)
{
    CODModel* pModel = GetRootModel();

    if (pModel)
    {
        pModel->SetModifiedFlag(Value);
    }
}

ZBSymbolEdit* ZBSymbol::CreateEditText(const CString& AreaName,
                                       const CString& EditName,
                                       CODComponent*  pParent /*= NULL*/)
{
    return ZUODSymbolManipulator::CreateEditText(this, AreaName, EditName, pParent);
}

ZBSymbolEdit* ZBSymbol::CreateAndReplaceEditText(const CString& EditName, CODComponent* pParent /*= NULL*/)
{
    return ZUODSymbolManipulator::CreateAndReplaceEditText(this, EditName, pParent);
}

BOOL ZBSymbol::RemoveSymbol(const CString SymbolName)
{
    return ZUODSymbolManipulator::RemoveSymbol(this, SymbolName);
}

BOOL ZBSymbol::RemoveSymbol(CODComponent* pMainComponent, CODComponent* pComponent)
{
    return ZUODSymbolManipulator::RemoveSymbol(pMainComponent, pComponent);
}

CODComponent* ZBSymbol::FindSymbol(CODComponent* pMainComponent, const CString SymbolName)
{
    return ZUODSymbolManipulator::FindSymbol(pMainComponent, SymbolName);
}

// Create the symbol name label
CODComponent* ZBSymbol::FindSymbolInChild(CODComponent* pMainComponent, const CString SymbolName)
{
    return ZUODSymbolManipulator::FindSymbolInChild(pMainComponent, SymbolName);
}

bool ZBSymbol::IsNewNameValid(const CString value) const
{
    if (value.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_SYMBOLNAME_EMPTY, MB_OK);
        return false;
    }

    CODComponent* pComp = GetParent();

    if (pComp && ISA(pComp, ZDProcessGraphModelMdl))
    {
        // If not the same and
        // If already exists,
        // display an error message
        // and put back the initial value
        if (value != const_cast<ZBSymbol*>(this)->GetSymbolName() &&
            dynamic_cast<ZDProcessGraphModelMdl*>(pComp)->GetRoot()->SymbolNameAlreadyAllocated(value))
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_SYMBOLNAME_ALREADYEXIST, MB_OK);
            return false;
        }
        else if (value.FindOneOf(_T(";:\\/")) != -1)
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_SYMBOLNAME_INVALIDCHAR, MB_OK);
            return false;
        }
    }

    return true;
}

// **********************************************************************************************************************
// *                                            Symbol mouse methods                                                    *
// **********************************************************************************************************************

BOOL ZBSymbol::Create(UINT nID, HINSTANCE hInst, const CString Name /*= ""*/)
{
    if (!Name.IsEmpty())
    {
        ZBSymbol::SetSymbolName(Name);
    }

    BOOL RetValue = CODSymbolComponent::Create(nID, hInst);

    SetPortsVisible(FALSE);

    if (!GetSymbolName().IsEmpty())
    {
        SetSymbolName(GetSymbolName());
    }

    return TRUE;
}

CString ZBSymbol::GetSymbolName() const
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
    {
        return _T("");
    }

    return pBasicProps->GetSymbolName();
}

BOOL ZBSymbol::SetSymbolName(const CString& value)
{
    CString OldName = GetSymbolName();

    if (OldName != value)
    {
        if (GetSymbolNameTextEdit())
        {
            GetSymbolNameTextEdit()->SetText(value);
        }

        ZBBasicProperties BasicProps;
        ZBBasicProperties* pCurBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

        if (pCurBasicProps != NULL)
        {
            BasicProps = *pCurBasicProps;
            BasicProps.SetSymbolName(value);
            SetProperty(&BasicProps);

            // Advise the owner model of symbol changes
            ZDProcessGraphModelMdl* pRootModel = dynamic_cast<ZDProcessGraphModelMdl*>(GetRootModel());

            if (pRootModel)
            {
                pRootModel->OnSymbolNameChanged(*this, OldName);
            }

            // The symbol has changed
            // Notify all refences
            ZBSymbolObserverMsg Msg(ZBSymbolObserverMsg::NameHasChanged, this);
            NotifyAllObservers(&Msg);

            // Build the message
            ZBDocObserverMsg DocMsg(ZBDocObserverMsg::ChangedElement,
                                    NULL,
                                    dynamic_cast<ZDProcessGraphModelMdl*>(GetOwnerModel()),
                                    this);

            AfxGetMainWnd()->SendMessageToDescendants(UM_ELEMENTMODIFIEDDOCUMENTMODEL, 0, (LPARAM)&DocMsg);

            // Redraw the symbol
            RedrawSymbol();
            return TRUE;
        }

        return FALSE;
    }

    return TRUE;
}

CString ZBSymbol::GetSymbolComment() const
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
    {
        return _T("");
    }

    return pBasicProps->GetSymbolDescription();
}

BOOL ZBSymbol::SetSymbolComment(const CString& value)
{
    if (GetSymbolComment() != value)
    {
        if (GetCommentTextEdit())
        {
            GetCommentTextEdit()->SetText(value);
        }

        ZBBasicProperties BasicProps;
        ZBBasicProperties* pCurBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

        if (pCurBasicProps != NULL)
        {
            BasicProps = *pCurBasicProps;
            BasicProps.SetSymbolDescription(value);
            SetProperty(&BasicProps);

            // The symbol has changed
            // Notify all refences
            ZBSymbolObserverMsg Msg(ZBSymbolObserverMsg::DescriptionHasChanged, this);
            NotifyAllObservers(&Msg);

            // Redraw the symbol
            RedrawSymbol();
            return TRUE;
        }

        return FALSE;
    }

    return TRUE;
}

int ZBSymbol::GetSymbolReferenceNumber() const
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
    {
        return -1;
    }

    return pBasicProps->GetSymbolNumber();
}

CString ZBSymbol::GetSymbolReferenceNumberStr() const
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
    {
        return _T("");
    }

    return pBasicProps->GetSymbolNumberStr();
}

BOOL ZBSymbol::SetSymbolReferenceNumber(int value)
{
    if (GetSymbolReferenceNumber() != value)
    {
        ZBBasicProperties BasicProps;
        ZBBasicProperties* pCurBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

        if (pCurBasicProps != NULL)
        {
            BasicProps = *pCurBasicProps;
            BasicProps.SetSymbolNumber(value);
            SetProperty(&BasicProps);

            // The symbol has changed
            // Notify all refences
            ZBSymbolObserverMsg Msg(ZBSymbolObserverMsg::ElementHasChanged, this);
            NotifyAllObservers(&Msg);

            // Redraw the symbol
            RedrawSymbol();
            return TRUE;
        }

        return FALSE;
    }

    return TRUE;
}

BOOL ZBSymbol::SetSymbolReferenceNumberStr(const CString& value)
{
    if (GetSymbolReferenceNumberStr() != value)
    {
        ZBBasicProperties BasicProps;
        ZBBasicProperties* pCurBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

        if (pCurBasicProps != NULL)
        {
            BasicProps = *pCurBasicProps;
            BasicProps.SetSymbolNumber(value);
            SetProperty(&BasicProps);

            // The symbol has changed
            // Notify all refences
            ZBSymbolObserverMsg Msg(ZBSymbolObserverMsg::ElementHasChanged, this);
            NotifyAllObservers(&Msg);

            // Redraw the symbol
            RedrawSymbol();
            return TRUE;
        }

        return FALSE;
    }

    return TRUE;
}

CString ZBSymbol::RetreiveUnitGUID(const CString Name, bool& Error) const
{
    ZDProcessGraphModelMdl* pModel =
        dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<ZBSymbol*>(this)->GetOwnerModel());

    if (pModel)
    {
        return pModel->RetreiveUnitGUID(Name, Error);
    }

    Error = true;

    return _T("");
}

CString ZBSymbol::RetreiveUnitName(const CString GUID, bool& Error) const
{
    ZDProcessGraphModelMdl* pModel =
        dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<ZBSymbol*>(this)->GetOwnerModel());

    if (pModel)
    {
        return pModel->RetreiveUnitName(GUID, Error);
    }

    Error = true;

    return _T("");
}

CString ZBSymbol::RetreiveUnitDescription(const CString GUID, bool& Error) const
{
    ZDProcessGraphModelMdl* pModel =
        dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<ZBSymbol*>(this)->GetOwnerModel());

    if (pModel)
    {
        return pModel->RetreiveUnitDescription(GUID, Error);
    }

    Error = true;

    return _T("");
}

float ZBSymbol::RetreiveUnitCost(const CString GUID, bool& Error) const
{
    ZDProcessGraphModelMdl* pModel =
        dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<ZBSymbol*>(this)->GetOwnerModel());

    if (pModel)
    {
        return pModel->RetreiveUnitCost(GUID, Error);
    }

    Error = true;

    return 0;
}

CString ZBSymbol::RetreiveLogicalSystemGUID(const CString Name, bool& Error) const
{
    ZDProcessGraphModelMdl* pModel =
        dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<ZBSymbol*>(this)->GetOwnerModel());

    if (pModel)
    {
        return pModel->RetreiveLogicalSystemGUID(Name, Error);
    }

    Error = true;

    return _T("");
}

CString ZBSymbol::RetreiveLogicalSystemName(const CString GUID, bool& Error) const
{
    ZDProcessGraphModelMdl* pModel =
        dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<ZBSymbol*>(this)->GetOwnerModel());

    if (pModel)
    {
        return pModel->RetreiveLogicalSystemName(GUID, Error);
    }

    Error = true;

    return _T("");
}

CString ZBSymbol::RetreiveLogicalSystemDescription(const CString GUID, bool& Error) const
{
    ZDProcessGraphModelMdl* pModel =
        dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<ZBSymbol*>(this)->GetOwnerModel());

    if (pModel)
    {
        return pModel->RetreiveLogicalSystemDescription(GUID, Error);
    }

    Error = true;

    return _T("");
}

// JMR-MODIF - Le 27 février 2006 - Ajout de la fonction RetreivePrestationName pour mettre à jour les prestations.
CString ZBSymbol::RetreivePrestationName(const CString GUID, bool& Error) const
{
    ZDProcessGraphModelMdl* pModel =
        dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<ZBSymbol*>(this)->GetOwnerModel());

    if (pModel)
    {
        return pModel->RetreivePrestationName(GUID, Error);
    }

    Error = true;

    return _T("");
}

// JMR-MODIF - Le 22 juillet 2007 - Cette fonction permet d'obtenir le niveau du risque du symbole.
CString ZBSymbol::GetRiskLevel()
{
    if (IsProcess() || IsProcedure() || IsStart() || IsStop())
    {
        ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

        return pBasicProps->GetSymbolRiskLevel();
    }

    return _T("");
}

// JMR-MODIF - Le 22 juillet 2007 - Cette fonction permet de définir le niveau du risque du symbole.
void ZBSymbol::SetRiskLevel(CString Level)
{
    if (IsProcess() || IsProcedure() || IsStart() || IsStop())
    {
        ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

        pBasicProps->SetSymbolRiskLevel(Level);
    }
}

bool ZBSymbol::CreateSymbolProperties()
{
    ZBBasicProperties propBasic;
    AddProperty(propBasic);

    ZBExtAppPropertyMgr::CreateSymbolProperties();
    ZBExtFilePropertyMgr::CreateSymbolProperties();

    // Create the empty attributes if requested
    if (AcceptDynamicAttributes())
    {
        OnFillDefaultAttributes(&m_Attributes);
    }

    // JMR-MODIF - Le 21 septembre 2005 - Nettoyage des memory leaks, destruction de m_DynamicPropManager avant une
    // nouvelle attribution.
    if (m_DynamicPropManager != NULL)
    {
        delete m_DynamicPropManager;
        m_DynamicPropManager = NULL;
    }

    m_DynamicPropManager = new ZBDynamicProperties;

    if (m_DynamicPropManager)
    {
        m_DynamicPropManager->CreateSymbolProperties();
    }

    return true;
}

bool ZBSymbol::FillProperties(ZBPropertySet& PropSet, bool NumericValue /*= false*/, bool GroupValue /*= false*/)
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
    {
        return false;
    }

    CString Name;

    if (NumericValue)
    {
        Name = pBasicProps->GetSymbolName();
        Name.Remove('\n');
        Name.Replace('\r', ' ');
    }

    // Propriété "Nom" du groupe "General"
    ZBProperty* pNameProp = new ZBProperty(IDS_ZS_BP_PROP_BASIC_TITLE,
                                           ZS_BP_PROP_BASIC,
                                           IDS_Z_SYMBOL_NAME_NAME,
                                           Z_SYMBOL_NAME,
                                           IDS_Z_SYMBOL_NAME_DESC,
                                           (NumericValue == true) ? Name : pBasicProps->GetSymbolName(),
                                           (!IsLocal() || SymbolNameTextEditReadOnly()) ? ZBProperty::PT_EDIT_MULTILINE_READONLY : ZBProperty::PT_EDIT_MULTILINE);
    PropSet.Add(pNameProp);

    // Propriété "Description" du groupe "General"
    ZBProperty* pDescProp = new ZBProperty(IDS_ZS_BP_PROP_BASIC_TITLE,
                                           ZS_BP_PROP_BASIC,
                                           IDS_Z_SYMBOL_DESCRIPTION_NAME,
                                           Z_SYMBOL_DESCRIPTION,
                                           IDS_Z_SYMBOL_DESCRIPTION_DESC,
                                           pBasicProps->GetSymbolDescription(),
                                           (!IsLocal() || CommentTextEditReadOnly()) ? ZBProperty::PT_EDIT_MULTILINE_READONLY : ZBProperty::PT_EDIT_MULTILINE);
    PropSet.Add(pDescProp);

    ZBProperty* pNumberProp;

    if (NumericValue)
    {
        // Propriété "Référence" du groupe "General"
        pNumberProp = new ZBProperty(IDS_ZS_BP_PROP_BASIC_TITLE,
                                     ZS_BP_PROP_BASIC,
                                     IDS_Z_SYMBOL_NUMBER_NAME,
                                     Z_SYMBOL_NUMBER,
                                     IDS_Z_SYMBOL_NUMBER_DESC,
                                     (double)pBasicProps->GetSymbolNumber(),
                                     IsLocal() ? ZBProperty::PT_EDIT_NUMBER : ZBProperty::PT_EDIT_NUMBER_READONLY);
    }
    else
    {
        // Propriété "Référence" du groupe "General"
        pNumberProp = new ZBProperty(IDS_ZS_BP_PROP_BASIC_TITLE,
                                     ZS_BP_PROP_BASIC,
                                     IDS_Z_SYMBOL_NUMBER_NAME,
                                     Z_SYMBOL_NUMBER,
                                     IDS_Z_SYMBOL_NUMBER_DESC,
                                     pBasicProps->GetSymbolNumberStr(),
                                     IsLocal() ? ZBProperty::PT_EDIT_STRING : ZBProperty::PT_EDIT_STRING_READONLY);
    }

    PropSet.Add(pNumberProp);

    // JMR-MODIF - le 22 juillet 2007 - Ajout de la nouvelle propriété "Niveau du risque"
    if (IsProcess() || IsProcedure() || IsStart() || IsStop())
    {
        // Propriété "Niveau du risque" du groupe "General"
        ZBProperty* pRiskProp = new ZBProperty(IDS_ZS_BP_PROP_BASIC_TITLE,
                                               ZS_BP_PROP_BASIC,
                                               IDS_Z_SYMBOL_RISK_LEVEL_NAME,
                                               Z_SYMBOL_RISK_LEVEL,
                                               IDS_Z_SYMBOL_RISK_LEVEL_DESC,
                                               pBasicProps->GetSymbolRiskLevel(),
                                               ZBProperty::PT_EDIT_STRING_READONLY);
        PropSet.Add(pRiskProp);
    }

    // Les propriétés du groupe "Lien externe" sont ajoutées par la classe ZBExtAppPropertyMgr.
    if (IsLocal() && AcceptExtApp())
    {
        if (!ZBExtAppPropertyMgr::FillProperties(PropSet, NumericValue, GroupValue))
        {
            return false;
        }

        // RS-MODIF 11.12.04 segregation conceptor
        CODModel * pModel = GetRootModel();

        // If messenger activated
        if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
            dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetUseWorkflow())
        {
            if (!ZBExtAppPropertyMgr::FillPropertiesMessenger(PropSet, NumericValue, GroupValue))
            {
                return false;
            }
        }
    }

    // Les propriétés du groupe "Fichier externe" sont ajoutées par la classe ZBExtFilePropertyMgr.
    if (IsLocal() && AcceptExtFile())
    {
        if (!ZBExtFilePropertyMgr::FillProperties(PropSet, NumericValue, GroupValue))
        {
            return false;
        }

        // RS-MODIF 11.12.04 segregation conceptor
        CODModel * pModel = GetRootModel();

        if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
            dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetUseWorkflow()) // if messenger activated
        {
            if (!ZBExtFilePropertyMgr::FillPropertiesMessenger(PropSet, NumericValue, GroupValue))
            {
                return false;
            }
        }
    }

    // Propriétés dynamiques.
    if (m_DynamicPropManager)
    {
        if (!m_DynamicPropManager->FillProperties(PropSet, NumericValue, GroupValue))
        {
            return false;
        }
    }

    return true;
}

bool ZBSymbol::SaveProperties(ZBPropertySet& PropSet)
{
    if (!IsLocal())
    {
        return true;
    }

    // Now run through the list of data and fill the property set
    ZBPropertyIterator i(&PropSet);
    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // If has not changed, continue
        if (pProp->GetHasChanged() == false)
        {
            continue;
        }

        if (pProp->GetCategoryID() == ZS_BP_PROP_BASIC)
        {
            switch (pProp->GetItemID())
            {
                case Z_SYMBOL_NAME:
                {
                    SetSymbolName(pProp->GetValueString());
                    break;
                }

                case Z_SYMBOL_DESCRIPTION:
                {
                    SetSymbolComment(pProp->GetValueString());
                    break;
                }

                case Z_SYMBOL_NUMBER:
                {
                    SetSymbolReferenceNumberStr(pProp->GetValueString());
                    break;
                }
            }
        }
    }

    if (!ZBExtAppPropertyMgr::SaveProperties(PropSet) || !ZBExtFilePropertyMgr::SaveProperties(PropSet))
    {
        return false;
    }

    if (m_DynamicPropManager)
    {
        if (!m_DynamicPropManager->SaveProperties(PropSet))
        {
            return false;
        }
    }

    return true;
}

bool ZBSymbol::FillProperty(ZBProperty& Property)
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
    {
        return false;
    }

    if (Property.GetCategoryID() == ZS_BP_PROP_BASIC)
    {
        switch (Property.GetItemID())
        {
            case Z_SYMBOL_NAME:
            {
                Property.SetValueString(pBasicProps->GetSymbolName());
                break;
            }

            case Z_SYMBOL_DESCRIPTION:
            {
                Property.SetValueString(pBasicProps->GetSymbolDescription());
                break;
            }

            case Z_SYMBOL_NUMBER:
            {
                Property.SetValueString(pBasicProps->GetSymbolNumberStr());
                break;
            }
        }
    }

    if (!ZBExtAppPropertyMgr::FillProperty(Property) || !ZBExtFilePropertyMgr::FillProperty(Property))
    {
        return false;
    }

    if (m_DynamicPropManager)
    {
        if (!m_DynamicPropManager->FillProperty(Property))
        {
            return false;
        }
    }

    return true;
}

bool ZBSymbol::SaveProperty(ZBProperty& Property)
{
    if (!IsLocal())
    {
        return true;
    }

    if (Property.GetCategoryID() == ZS_BP_PROP_BASIC)
    {
        switch (Property.GetItemID())
        {
            case Z_SYMBOL_NAME:
            {
                SetSymbolName(Property.GetValueString());
                break;
            }

            case Z_SYMBOL_DESCRIPTION:
            {
                SetSymbolComment(Property.GetValueString());
                break;
            }

            case Z_SYMBOL_NUMBER:
            {
                SetSymbolReferenceNumberStr(Property.GetValueString());
                break;
            }
        }

        // Set the modified flag to true
        SetModifiedFlag();
    }

    if (!ZBExtAppPropertyMgr::SaveProperty(Property) || !ZBExtFilePropertyMgr::SaveProperty(Property))
    {
        return false;
    }

    if (m_DynamicPropManager)
    {
        if (!m_DynamicPropManager->SaveProperty(Property))
        {
            return false;
        }
    }

    return true;
}

bool ZBSymbol::CheckPropertyValue(ZBProperty& Property, CString& value, ZBPropertySet& Properties)
{
    // If requested to check the Reference number,
    // Check if allowed
    if (Property.GetCategoryID() == ZS_BP_PROP_BASIC)
    {
        if (Property.GetItemID() == Z_SYMBOL_NUMBER)
        {
            CODComponent* pComp = GetParent();

            if (pComp && ISA(pComp, ZDProcessGraphModelMdl))
            {
                // If not the same and
                // If already exists,
                // display an error message
                // and put back the initial value
                if (value != GetSymbolReferenceNumberStr() &&
                    dynamic_cast<ZDProcessGraphModelMdl*>(pComp)->GetRoot()->ReferenceNumberAlreadyAllocated(value))
                {
                    PSS_MsgBox mBox;
                    mBox.Show(IDS_REFERENCENUMBER_ALREADYEXIST, MB_OK);
                    value = GetSymbolReferenceNumberStr();
                    return false;
                }
            }
        }
        else if (Property.GetItemID() == Z_SYMBOL_NAME)
        {
            if (!IsNewNameValid(value))
            {
                value = GetSymbolName();
                return false;
            }
        }
    }

    if (!ZBExtAppPropertyMgr::CheckPropertyValue(Property, value, Properties) ||
        !ZBExtFilePropertyMgr::CheckPropertyValue(Property, value, Properties))
    {
        return false;
    }

    if (m_DynamicPropManager)
    {
        if (!m_DynamicPropManager->CheckPropertyValue(Property, value, Properties))
            return false;
    }

    return true;
}

bool ZBSymbol::ProcessExtendedInput(ZBProperty& Property, CString& value, ZBPropertySet& Properties, bool& Refresh)
{
    bool RetValue = false;

    if (ZBExtAppPropertyMgr::ProcessExtendedInput(Property, value, Properties, Refresh))
    {
        RetValue = true;
    }

    if (ZBExtFilePropertyMgr::ProcessExtendedInput(Property, value, Properties, Refresh))
    {
        RetValue = true;
    }

    if (m_DynamicPropManager)
    {
        if (m_DynamicPropManager->ProcessExtendedInput(Property, value, Properties, Refresh))
        {
            RetValue = true;
        }
    }

    return RetValue;
}

bool ZBSymbol::ProcessMenuCommand(int                MenuCommand,
                                  ZBProperty&        Property,
                                  CString&            value,
                                  ZBPropertySet&    Properties,
                                  bool&            Refresh)
{
    bool RetValue = false;

    // Call the base template class method
    if (ZBExtAppPropertyMgr::ProcessMenuCommand(MenuCommand, Property, value, Properties, Refresh))
    {
        RetValue = true;
    }

    if (ZBExtFilePropertyMgr::ProcessMenuCommand(MenuCommand, Property, value, Properties, Refresh))
    {
        RetValue = true;
    }

    if (m_DynamicPropManager)
    {
        if (m_DynamicPropManager->ProcessMenuCommand(MenuCommand, Property, value, Properties, Refresh))
        {
            RetValue = true;
        }
    }

    return RetValue;
}

bool ZBSymbol::OnPrePropertyChanged(const CString& NewValue, ZBProperty& Property, ZBPropertySet& Properties)
{
    bool RetValue = true;

    // Call the base template class method
    if (!ZBExtAppPropertyMgr::OnPrePropertyChanged(NewValue, Property, Properties))
    {
        RetValue = false;
    }

    if (!ZBExtFilePropertyMgr::OnPrePropertyChanged(NewValue, Property, Properties))
    {
        RetValue = false;
    }

    if (m_DynamicPropManager)
    {
        if (!m_DynamicPropManager->OnPrePropertyChanged(NewValue, Property, Properties))
        {
            RetValue = false;
        }
    }

    return RetValue;
}

bool ZBSymbol::OnPostPropertyChanged(ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh)
{
    bool RetValue = false;

    // Call the base template class method
    if (ZBExtAppPropertyMgr::OnPostPropertyChanged(Property, Properties, Refresh))
    {
        RetValue = true;
    }

    if (ZBExtFilePropertyMgr::OnPostPropertyChanged(Property, Properties, Refresh))
    {
        RetValue = true;
    }

    if (m_DynamicPropManager)
    {
        if (m_DynamicPropManager->OnPostPropertyChanged(Property, Properties, Refresh))
        {
            RetValue = true;
        }
    }

    return RetValue;
}

bool ZBSymbol::OnDropInternalPropertyItem(ZBProperty&        SrcProperty,
                                          ZBProperty&        DstProperty,
                                          bool                Top2Down,
                                          ZBPropertySet&    Properties)
{
    if (m_DynamicPropManager)
    {
        if (!m_DynamicPropManager->OnDropInternalPropertyItem(SrcProperty, DstProperty, Top2Down, Properties))
        {
            return false;
        }
    }

    return true;
}

void ZBSymbol::RedrawSymbol()
{
    // If the parent is a model
    CODComponent* pComp = GetParent();

    if (pComp && ISA(pComp, ZDProcessGraphModelMdl))
    {
        dynamic_cast<ZDProcessGraphModelMdl*>(pComp)->ReDrawComponent(*this);
    }
}

void ZBSymbol::OnMove()
{
    CODSymbolComponent::OnMove();

    // call the function to adjust 
    // the position of embedded elements
    AdjustElementPosition();
}

void ZBSymbol::OnDeleteSymbol()
{
    RemoveReferenceSymbol();
}

// When we attach a reference to a symbol,
// we need to attach the object to the subject
void ZBSymbol::AssignReferenceSymbol(CODSymbolComponent* pReference)
{
    // todo -cCheck -oJean: on 26.09.2019, check if this modification is valid, revert it otherwise
    RemoveReferenceSymbol();

    m_pReference = pReference;

    if (m_pReference && ISA(m_pReference, ZBSymbol))
    {
        // Sets the same name
        SetSymbolName(dynamic_cast<ZBSymbol*>(m_pReference)->GetSymbolName());

        // Sets as reference
        SetIsLocal(false);

        // And attach this to the source reference
        dynamic_cast<ZBSymbol*>(m_pReference)->AttachObserver(this);
    }
    // todo -cCheck -oJean: on 26.09.2019, check if this modification is valid, revert it otherwise
    /*
    else
    {
        RemoveReferenceSymbol();
    }
    */
}

// When we deattach a reference to a symbol,
// we need to deattach the object to the subject
void ZBSymbol::RemoveReferenceSymbol()
{
    if (m_pReference)
    {
        dynamic_cast<ZBSymbol*>(m_pReference)->DetachObserver(this);
    }

    m_pReference = NULL;
}

void ZBSymbol::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    if (pSubject && pSubject != this && pMsg && ISA(pMsg, ZBSymbolObserverMsg))
    {
        switch (dynamic_cast<ZBSymbolObserverMsg*>(pMsg)->GetActionType())
        {
            case ZBSymbolObserverMsg::ElementHasChanged:
            case ZBSymbolObserverMsg::NoAction:
            {
                CopySymbolDefinitionFrom((ZBSymbol&)*pSubject);
                break;
            }

            case ZBSymbolObserverMsg::NameHasChanged:
            {
                SetSymbolName(dynamic_cast<ZBSymbol*>(pSubject)->GetSymbolName());
                break;
            }

            case ZBSymbolObserverMsg::DescriptionHasChanged:
            {
                SetSymbolComment(dynamic_cast<ZBSymbol*>(pSubject)->GetSymbolComment());
                break;
            }
        }

        // Adjust element position for symbols
        AdjustElementPosition();
    }
}

void ZBSymbol::SetCurrentLineColor(COLORREF value)
{
    m_CurrentLineColor = value;
    ZUODSymbolManipulator::ChangeLineColor(this, value);
}

void ZBSymbol::SetInitialLineColor(COLORREF value)
{
    m_InitialLineColor = value;
    SetCurrentLineColor(value);
}

void ZBSymbol::SetInitialLineWidth(int value)
{
    m_InitialLineWidth = value;
    ZUODSymbolManipulator::ChangeLineWidth(this, value);
}

void ZBSymbol::SetCurrentLabelColor(COLORREF value)
{
    m_CurrentLabelLineColor = value;
    ZUODSymbolManipulator::ChangeLabelLineColor(this, value);
}

void ZBSymbol::SetInitialLabelLineColor(COLORREF value)
{
    m_InitialLabelLineColor = value;
    SetCurrentLabelColor(value);
}

void ZBSymbol::SetInitialLabelLineWidth(int value)
{
    m_InitialLabelLineWidth = value;
    ZUODSymbolManipulator::ChangeLabelLineWidth(this, value);
}

/////////////////////////////////////////////////////////////////////////////
// Following and Entering symbol methods
size_t ZBSymbol::GetFollowingSymbols(CODNodeArray& Nodes)
{
    Nodes.RemoveAll();

    IODNode* pINode;
    pINode = guid_cast<IODNode*>(this);
    pINode->AddRef();

    if (pINode != NULL)
    {
        pINode->GetNodesAdjacentFrom(&Nodes);
        pINode->Release();
    }

    return Nodes.GetSize();
}

size_t ZBSymbol::GetFollowingSymbols_Right(CODNodeArray& Nodes)
{
    // First, remove all element
    Nodes.RemoveAll();

    // Now start by retrieving the right edges
    CODEdgeArray Edges;

    if (GetEdgesLeaving_Right(Edges) == 0)
    {
        return 0;
    }

    // Now in the Edges array we only have right edges
    // For each edge, retreive the symbol attached on the destination
    for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
    {
        // Get the link 
        IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
        {
            continue;
        }

        // Now retreive the target component
        CODComponent* pComp = pLinkIndexed->GetTargetComponent();

        // If a target component is attached to,
        // add it to the array
        if (pComp)
        {
            Nodes.Add(guid_cast<IODNode*>(pComp));
        }
    }

    return Nodes.GetSize();
}

size_t ZBSymbol::GetFollowingSymbols_Left(CODNodeArray& Nodes)
{
    // First, remove all element
    Nodes.RemoveAll();

    // Now start by retrieving the left edges
    CODEdgeArray Edges;

    if (GetEdgesLeaving_Left(Edges) == 0)
    {
        return 0;
    }

    // Now in the Edges array we only have left edges
    // For each edge, retreive the symbol attached on the destination
    for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
    {
        // Get the link 
        IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
        {
            continue;
        }

        // Now retreive the target component
        CODComponent* pComp = pLinkIndexed->GetTargetComponent();

        // If a target component is attached to,
        // add it to the array
        if (pComp)
        {
            Nodes.Add(guid_cast<IODNode*>(pComp));
        }
    }

    return Nodes.GetSize();
}

size_t ZBSymbol::GetFollowingSymbols_Up(CODNodeArray& Nodes)
{
    // First, remove all element
    Nodes.RemoveAll();

    // Now start by retrieving the up edges
    CODEdgeArray Edges;

    if (GetEdgesLeaving_Up(Edges) == 0)
    {
        return 0;
    }

    // Now in the Edges array we only have up edges
    // For each edge, retreive the symbol attached on the destination
    for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
    {
        // Get the link
        IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
        {
            continue;
        }

        // Now retreive the target component
        CODComponent* pComp = pLinkIndexed->GetTargetComponent();

        // If a target component is attached to,
        // add it to the array
        if (pComp)
        {
            Nodes.Add(guid_cast<IODNode*>(pComp));
        }
    }

    return Nodes.GetSize();
}

size_t ZBSymbol::GetFollowingSymbols_Down(CODNodeArray& Nodes)
{
    // First, remove all element
    Nodes.RemoveAll();

    // Now start by retrieving the down edges
    CODEdgeArray Edges;

    if (GetEdgesLeaving_Down(Edges) == 0)
    {
        return 0;
    }

    // Now in the Edges array we only have down edges
    // For each edge, retreive the symbol attached on the destination
    for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
    {
        // Get the link 
        IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
        {
            continue;
        }

        // Now retreive the target component
        CODComponent* pComp = pLinkIndexed->GetTargetComponent();

        // If a target component is attached to,
        // add it to the array
        if (pComp)
        {
            Nodes.Add(guid_cast<IODNode*>(pComp));
        }
    }

    return Nodes.GetSize();
}

size_t ZBSymbol::GetEnteringSymbols(CODNodeArray& Nodes)
{
    Nodes.RemoveAll();

    IODNode* pINode;
    pINode = guid_cast<IODNode*>(this);
    pINode->AddRef();

    if (pINode != NULL)
    {
        pINode->GetNodesAdjacentTo(&Nodes);
        pINode->Release();
    }

    return Nodes.GetSize();
}

size_t ZBSymbol::GetEnteringSymbols_Right(CODNodeArray& Nodes)
{
    // First, remove all element
    Nodes.RemoveAll();

    // Now start by retrieving the entering right edges
    CODEdgeArray Edges;

    if (GetEdgesEntering_Right(Edges) == 0)
    {
        return 0;
    }

    // Now in the Edges array we only have right edges
    // For each edge, retreive the symbol attached on the destination
    for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
    {
        // Get the link 
        IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
        {
            continue;
        }

        // Now retreive the source component attached to the link
        CODComponent* pComp = pLinkIndexed->GetSourceComponent();

        // If a target component is attached to,
        // add it to the array
        if (pComp)
        {
            Nodes.Add(guid_cast<IODNode*>(pComp));
        }
    }

    return Nodes.GetSize();
}

size_t ZBSymbol::GetEnteringSymbols_Left(CODNodeArray& Nodes)
{
    // First, remove all element
    Nodes.RemoveAll();

    // Now start by retrieving the entering left edges
    CODEdgeArray Edges;

    if (GetEdgesEntering_Left(Edges) == 0)
    {
        return 0;
    }

    // Now in the Edges array we only have left edges
    // For each edge, retreive the symbol attached on the destination
    for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
    {
        // Get the link 
        IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
        {
            continue;
        }

        // Now retreive the source component attached to the link
        CODComponent* pComp = pLinkIndexed->GetSourceComponent();

        // If a target component is attached to,
        // add it to the array
        if (pComp)
        {
            Nodes.Add(guid_cast<IODNode*>(pComp));
        }
    }

    return Nodes.GetSize();
}

size_t ZBSymbol::GetEnteringSymbols_Up(CODNodeArray& Nodes)
{
    // First, remove all element
    Nodes.RemoveAll();

    // Now start by retrieving the entering up edges
    CODEdgeArray Edges;

    if (GetEdgesEntering_Up(Edges) == 0)
    {
        return 0;
    }

    // Now in the Edges array we only have up edges
    // For each edge, retreive the symbol attached on the destination
    for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
    {
        // Get the link 
        IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
        {
            continue;
        }

        // Now retreive the source component attached to the link
        CODComponent* pComp = pLinkIndexed->GetSourceComponent();

        // If a target component is attached to,
        // add it to the array
        if (pComp)
        {
            Nodes.Add(guid_cast<IODNode*>(pComp));
        }
    }

    return Nodes.GetSize();
}

size_t ZBSymbol::GetEnteringSymbols_Down(CODNodeArray& Nodes)
{
    // First, remove all element
    Nodes.RemoveAll();

    // Now start by retrieving the entering down edges
    CODEdgeArray Edges;

    if (GetEdgesEntering_Down(Edges) == 0)
    {
        return 0;
    }

    // Now in the Edges array we only have down edges
    // For each edge, retreive the symbol attached on the destination
    for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
    {
        // Get the link 
        IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
        {
            continue;
        }

        // Now retreive the source component attached to the link
        CODComponent* pComp = pLinkIndexed->GetSourceComponent();

        // If a target component is attached to,
        // add it to the array
        if (pComp)
        {
            Nodes.Add(guid_cast<IODNode*>(pComp));
        }
    }

    return Nodes.GetSize();
}

/////////////////////////////////////////////////////////////////////////////
// Following and Entering edge methods
size_t ZBSymbol::GetEdgesLeaving(CODEdgeArray& Edges)
{
    Edges.RemoveAll();

    IODNode* pINode;
    pINode = guid_cast<IODNode*>(this);
    pINode->AddRef();

    if (pINode != NULL)
    {
        pINode->GetEdgesLeaving(&Edges);
        pINode->Release();
    }

    return Edges.GetSize();
}

size_t ZBSymbol::GetEdgesLeaving_Name(const CString Name, CODEdgeArray& Edges)
{
    // Retreive all leaving edges
    if (GetEdgesLeaving(Edges) == 0)
    {
        return 0;
    }

    // Run through all edges and determine what is the source port name
    for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
    {
        // Get the link 
        IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
        {
            continue;
        }

        // Now retreive the source port to check its name
        CODPortComponent* pPort = pLinkIndexed->GetSourcePort();

        // If no source port or the name is not down
        // Remove it from the array
        if (!pPort || pPort->GetName() != Name)
        {
            Edges.RemoveAt(nEdgeIdx);
            --nEdgeIdx;
        }
    }

    // Finally, return the array size
    return Edges.GetSize();
}

size_t ZBSymbol::GetEdgesLeaving_Right(CODEdgeArray& Edges)
{
    return ZBSymbol::GetEdgesLeaving_Name(M_PortRIGHTComponentLabel, Edges);
}

size_t ZBSymbol::GetEdgesLeaving_Left(CODEdgeArray& Edges)
{
    return ZBSymbol::GetEdgesLeaving_Name(M_PortLEFTComponentLabel, Edges);
}

size_t ZBSymbol::GetEdgesLeaving_Up(CODEdgeArray& Edges)
{
    return ZBSymbol::GetEdgesLeaving_Name(M_PortUPComponentLabel, Edges);
}

size_t ZBSymbol::GetEdgesLeaving_Down(CODEdgeArray& Edges)
{
    return ZBSymbol::GetEdgesLeaving_Name(M_PortDOWNComponentLabel, Edges);
}

size_t ZBSymbol::GetEdgesEntering(CODEdgeArray& Edges)
{
    Edges.RemoveAll();

    IODNode* pINode;
    pINode = guid_cast<IODNode*>(this);
    pINode->AddRef();

    if (pINode != NULL)
    {
        pINode->GetEdgesEntering(&Edges);
        pINode->Release();
    }

    return Edges.GetSize();
}

size_t ZBSymbol::GetEdgesEntering_Name(const CString Name, CODEdgeArray& Edges)
{
    // Retreive all entering edges
    if (GetEdgesEntering(Edges) == 0)
    {
        return 0;
    }

    // Run through all edges and determine what is the destination port name
    for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
    {
        // Get the link
        IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
        {
            continue;
        }

        // Now retreive the target port to check its name
        CODPortComponent* pPort = pLinkIndexed->GetTargetPort();

        // If no source port or the name is not right
        // Remove it from the array
        if (!pPort || pPort->GetName() != Name)
        {
            Edges.RemoveAt(nEdgeIdx);
            --nEdgeIdx;
        }
    }

    // Finally, return the array size
    return Edges.GetSize();
}

size_t ZBSymbol::GetEdgesEntering_Right(CODEdgeArray& Edges)
{
    return ZBSymbol::GetEdgesEntering_Name(M_PortRIGHTComponentLabel, Edges);
}

size_t ZBSymbol::GetEdgesEntering_Left(CODEdgeArray& Edges)
{
    return ZBSymbol::GetEdgesEntering_Name(M_PortLEFTComponentLabel, Edges);
}

size_t ZBSymbol::GetEdgesEntering_Up(CODEdgeArray& Edges)
{
    return ZBSymbol::GetEdgesEntering_Name(M_PortUPComponentLabel, Edges);
}

size_t ZBSymbol::GetEdgesEntering_Down(CODEdgeArray& Edges)
{
    return ZBSymbol::GetEdgesEntering_Name(M_PortDOWNComponentLabel, Edges);
}

void ZBSymbol::Serialize(CArchive& ar)
{
    // Serialize the canvas model.
    CODSymbolComponent::Serialize(ar);

    // Only if the object is serialize from and to a document
    if (ar.m_pDocument)
    {
        if (ar.IsStoring())
        {
            CODModel* pNULLModel = NULL;
            CString EmptyString(_T(""));

            if (m_pReference)
            {
                m_NameOfReference = dynamic_cast<ZBSymbol*>(m_pReference)->GetSymbolReferenceNumberStr();
            }
            else
            {
                m_NameOfReference.Empty();
            }

            ar << m_Name;
            ar << m_Comment;
            ar << (WORD)m_IsLocal;
            ar << m_ObjectPath;
            ar << m_NameOfReference;

            ar << (WORD)m_DisplayNameArea;
            ar << (WORD)m_DisplayDescriptionArea;
            ar << (WORD)m_DisplayAttributeArea;

            ar << m_CurrentLineColor;
            ar << m_CurrentLabelLineColor;
            ar << m_InitialLineColor;
            ar << m_InitialLineWidth;
            ar << m_InitialLabelLineColor;
            ar << m_InitialLabelLineWidth;

            // Serialize the attributes
            ar << m_Attributes;

            // Keep the child model pathname if there is one
            if (m_pModel && ISA(m_pModel, ZDProcessGraphModelMdl))
            {
                ar << dynamic_cast<ZDProcessGraphModelMdl*>(m_pModel)->GetAbsolutePath();
            }
            else
            {
                ar << EmptyString;
            }

            if (!IsChildModelRef())
            {
                ar << m_pModel;
            }
            else
            {
                ar << pNULLModel;
            }

            // Serialize the dynamic properties
            ar << m_DynamicPropManager;
        }
        else
        {
            ar >> m_Name;
            ar >> m_Comment;

            WORD wValue;
            ar >> wValue;
            m_IsLocal = ((wValue == 1) ? (true) : (false));

            ar >> m_ObjectPath;

            // Used to reconstruct the m_pReference
            ar >> m_NameOfReference;

            ar >> wValue;
            m_DisplayNameArea = ((wValue == 1) ? (true) : (false));

            ar >> wValue;
            m_DisplayDescriptionArea = ((wValue == 1) ? (true) : (false));

            ar >> wValue;
            m_DisplayAttributeArea = ((wValue == 1) ? (true) : (false));

            // If we have the right version, then deserialize the current line and label color
            if (ar.m_pDocument &&
                dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 19)
            {
                ar >> m_CurrentLineColor;
                ar >> m_CurrentLabelLineColor;
            }
            else
            {
                // Otherwise, initialize them to their respective initial colors
                m_CurrentLineColor = m_InitialLineColor;
                m_CurrentLabelLineColor = m_InitialLabelLineColor;
            }

            ar >> m_InitialLineColor;
            ar >> m_InitialLineWidth;
            ar >> m_InitialLabelLineColor;
            ar >> m_InitialLabelLineWidth;

            // Serialize the attributes
            m_Attributes.RemoveAllAttributes();
            ar >> m_Attributes;

            // The child model path name
            ar >> m_ChildModelPathName;

            // The model pointed to
            ar >> m_pModel;

            // JMR-MODIF - Le 21 septembre 2005 - Nettoyage des memory leaks, destruction de la variable
            // m_DynamicPropManager avant de tenter d'en assigner une nouvelle.
            if (m_DynamicPropManager != NULL)
            {
                delete m_DynamicPropManager;
                m_DynamicPropManager = NULL;
            }

            // Serialize the dynamic properties
            if (ar.m_pDocument &&
                dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 21)
            {
                ar >> (CObject*&)m_DynamicPropManager;
            }

            if (!m_DynamicPropManager)
            {
                m_DynamicPropManager = new ZBDynamicProperties;
            }

            CODEditProperties* pPropEdit = (CODEditProperties*)GetProperty(OD_PROP_EDIT);

            if (pPropEdit)
            {
                pPropEdit->SetCanSelect(TRUE);
            }
        }
    }

    // Serialize external applications and files
    if (!m_IsInCreationProcess)
    {
        ZBExtAppPropertyMgr::Serialize(ar);
        ZBExtFilePropertyMgr::Serialize(ar);
    }

    // Once loaded, call the base function 
    // to adjust the position of embedded elements
    AdjustElementPosition();
}
