/****************************************************************************
 * ==> PSS_Symbol ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol                                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_Symbol.h"

// stingray studio
#include "Views\OdGuids.h"

// processsoft
#include "zBaseLib\PSS_BaseDocument.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_DrawFunctions.h"
#include "zProperty\PSS_DynamicProperties.h"
#include "PSS_SymbolEdit.h"
#include "PSS_ODSymbolManipulator.h"
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_DocObserverMsg.h"
#include "PSS_SymbolObserverMsg.h"
#include "PSS_BasicProperties.h"

// resources
#include "zModelRes.h"
#include "PSS_ResIDs.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_CanSelectConverter 1
//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
PSS_Bitmap PSS_Symbol::m_ShortcutBitmap;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_Symbol, CODSymbolComponent, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_Symbol
//---------------------------------------------------------------------------
PSS_Symbol::PSS_Symbol() :
    CODSymbolComponent(),
    PSS_BasicSymbol(),
    PSS_ObjectPath(),
    PSS_NavigableSymbol(),
    PSS_Properties(),
    PSS_ExtAppPropertyMgr(this),
    PSS_ExtFilePropertyMgr(),
    PSS_SymbolAttributes(),
    PSS_BasicSymbolAcceptVisitor(),
    PSS_Subject(),
    PSS_Observer(),
    PSS_ToolTip(),
    m_pModel(NULL),
    m_pReference(NULL),
    m_pDynamicPropManager(NULL),
    m_IsInCreationProcess(false),
    m_IsLocal(true),
    m_CurrentLineColor(defCOLOR_BLACK),
    m_CurrentLabelLineColor(defCOLOR_BLACK),
    m_InitialLineColor(defCOLOR_BLACK),
    m_InitialLabelLineColor(defCOLOR_BLACK),
    m_InitialLineWidth(1),
    m_InitialLabelLineWidth(1),
    m_IsCopy(FALSE)
{
    SetSymbol(this);

    // set attributes in relative coordinates
    m_RelativeCoordinates = true;

    // a reinitialization is necessary at creation
    m_ReinitializeAreaAtCreation = true;

    CreateSymbolProperties();
}
//---------------------------------------------------------------------------
PSS_Symbol::PSS_Symbol(const PSS_Symbol& other) :
    CODSymbolComponent(),
    PSS_BasicSymbol(),
    PSS_ObjectPath(),
    PSS_NavigableSymbol(),
    PSS_Properties(),
    PSS_ExtAppPropertyMgr(this),
    PSS_ExtFilePropertyMgr(),
    PSS_SymbolAttributes(),
    PSS_BasicSymbolAcceptVisitor(),
    PSS_Subject(),
    PSS_Observer(),
    PSS_ToolTip(),
    m_pModel(NULL),
    m_pReference(NULL),
    m_pDynamicPropManager(NULL),
    m_IsInCreationProcess(false),
    m_IsLocal(true),
    m_CurrentLineColor(defCOLOR_BLACK),
    m_CurrentLabelLineColor(defCOLOR_BLACK),
    m_InitialLineColor(defCOLOR_BLACK),
    m_InitialLabelLineColor(defCOLOR_BLACK),
    m_InitialLineWidth(1),
    m_InitialLabelLineWidth(1),
    m_IsCopy(FALSE)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_Symbol::~PSS_Symbol()
{
    if (m_pDynamicPropManager)
        delete m_pDynamicPropManager;
}
//---------------------------------------------------------------------------
PSS_Symbol& PSS_Symbol::operator = (const PSS_Symbol& other)
{
    // Call the base class assignement operator
    CODSymbolComponent::    operator = ((const CODSymbolComponent&)    other);
    PSS_ExtAppPropertyMgr:: operator = ((const PSS_ExtAppPropertyMgr&) other);
    PSS_ExtFilePropertyMgr::operator = ((const PSS_ExtFilePropertyMgr&)other);
    PSS_SymbolAttributes::  operator = ((const PSS_SymbolAttributes&)  other);

    m_ObjectPath          = other.m_ObjectPath;
    m_pModel              = other.m_pModel;
    m_pDynamicPropManager = other.m_pDynamicPropManager->Dup();
    m_ReferenceName       = other.m_ReferenceName;
    m_IsLocal             = other.m_IsLocal;
    m_Name                = other.m_Name;
    m_Comment             = other.m_Comment;

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::Create(UINT id, HINSTANCE hInst, const CString& name)
{
    if (!name.IsEmpty())
        SetSymbolName(name);

    CODSymbolComponent::Create(id, hInst);

    SetPortsVisible(FALSE);

    if (!GetSymbolName().IsEmpty())
        SetSymbolName(GetSymbolName());

    return TRUE;
}
//---------------------------------------------------------------------------
CODComponent* PSS_Symbol::Dup() const
{
    return new PSS_Symbol(*this);
}
//---------------------------------------------------------------------------
CString PSS_Symbol::GetAttributeString(PSS_PropertyAttributes* pAttributes) const
{
    if (AcceptDynamicAttributes())
    {
        PSS_Properties::IPropertySet propSet;

        // Retrieve the property set from object
        const_cast<PSS_Symbol*>(this)->FillProperties(propSet);

        // format the string
        CString str = pAttributes->GetString(&propSet);

        PSS_Properties::IPropertyIterator it(&propSet);

        // remove all properties
        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
            delete pProp;

        propSet.RemoveAll();

        // return the string
        return str;
    }

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_Symbol::RefreshAttributeTextArea(bool redraw)
{
    if (AcceptDynamicAttributes() && GetAttributeTextEdit())
    {
        GetAttributeTextEdit()->SetText(GetAttributeString(&m_Attributes));

        if (redraw)
            RedrawSymbol();
    }
}
//---------------------------------------------------------------------------
bool PSS_Symbol::GetShowTitleText() const
{
    return (AcceptDynamicAttributes() ? m_Attributes.GetShowTitleText() : false);
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetShowTitleText(bool value)
{
    if (AcceptDynamicAttributes())
    {
        m_Attributes.SetShowTitleText(value);

        if (GetAttributeTextEdit())
        {
            GetAttributeTextEdit()->SetText(GetAttributeString(&m_Attributes));
            RedrawSymbol();
        }
    }
}
//---------------------------------------------------------------------------
PSS_SymbolEdit* PSS_Symbol::CreateEditText(const CString& areaName, const CString& editName, CODComponent* pParent)
{
    return PSS_ODSymbolManipulator::CreateEditText(this, areaName, editName, pParent);
}
//---------------------------------------------------------------------------
PSS_SymbolEdit* PSS_Symbol::CreateAndReplaceEditText(const CString& editName, CODComponent* pParent)
{
    return PSS_ODSymbolManipulator::CreateAndReplaceEditText(this, editName, pParent);
}
//---------------------------------------------------------------------------
CString PSS_Symbol::GetSymbolName() const
{
    PSS_BasicProperties* pBasicProps = static_cast<PSS_BasicProperties*>(GetProperty(ZS_BP_PROP_BASIC));

    if (!pBasicProps)
        return _T("");

    return pBasicProps->GetSymbolName();
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::SetSymbolName(const CString& value)
{
    CString oldName = GetSymbolName();

    if (oldName != value)
    {
        if (GetSymbolNameTextEdit())
            GetSymbolNameTextEdit()->SetText(value);

        PSS_BasicProperties  basicProps;
        PSS_BasicProperties* pCurBasicProps = static_cast<PSS_BasicProperties*>(GetProperty(ZS_BP_PROP_BASIC));

        if (pCurBasicProps)
        {
            basicProps = *pCurBasicProps;
            basicProps.SetSymbolName(value);
            SetProperty(&basicProps);

            // notify the owner model about symbol changes
            PSS_ProcessGraphModelMdl* pRootModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());

            if (pRootModel)
                pRootModel->OnSymbolNameChanged(*this, oldName);

            // the symbol has changed, notify all references
            PSS_SymbolObserverMsg msg(PSS_SymbolObserverMsg::IEActionType::IE_AT_NameHasChanged, this);
            NotifyAllObservers(&msg);

            // build the message
            PSS_DocObserverMsg docMsg(PSS_DocObserverMsg::IEActionType::IE_AT_ChangedElement,
                                      NULL,
                                      dynamic_cast<PSS_ProcessGraphModelMdl*>(GetOwnerModel()),
                                      this);

            CWnd* pMainWnd = ::AfxGetMainWnd();

            if (pMainWnd)
                pMainWnd->SendMessageToDescendants(UM_ELEMENTMODIFIEDDOCUMENTMODEL, 0, LPARAM(&docMsg));

            // redraw the symbol
            RedrawSymbol();
            return TRUE;
        }

        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_Symbol::GetSymbolComment() const
{
    PSS_BasicProperties* pBasicProps = static_cast<PSS_BasicProperties*>(GetProperty(ZS_BP_PROP_BASIC));

    if (!pBasicProps)
        return _T("");

    return pBasicProps->GetSymbolDescription();
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::SetSymbolComment(const CString& value)
{
    if (GetSymbolComment() != value)
    {
        if (GetCommentTextEdit())
            GetCommentTextEdit()->SetText(value);

        PSS_BasicProperties  basicProps;
        PSS_BasicProperties* pCurBasicProps = static_cast<PSS_BasicProperties*>(GetProperty(ZS_BP_PROP_BASIC));

        if (pCurBasicProps)
        {
            basicProps = *pCurBasicProps;
            basicProps.SetSymbolDescription(value);
            SetProperty(&basicProps);

            // the symbol has changed, notify all references
            PSS_SymbolObserverMsg msg(PSS_SymbolObserverMsg::IEActionType::IE_AT_DescriptionHasChanged, this);
            NotifyAllObservers(&msg);

            // redraw the symbol
            RedrawSymbol();
            return TRUE;
        }

        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_Symbol::GetSymbolReferenceNumber() const
{
    PSS_BasicProperties* pBasicProps = static_cast<PSS_BasicProperties*>(GetProperty(ZS_BP_PROP_BASIC));

    if (!pBasicProps)
        return -1;

    return pBasicProps->GetSymbolNumber();
}
//---------------------------------------------------------------------------
CString PSS_Symbol::GetSymbolReferenceNumberStr() const
{
    PSS_BasicProperties* pBasicProps = static_cast<PSS_BasicProperties*>(GetProperty(ZS_BP_PROP_BASIC));

    if (!pBasicProps)
        return _T("");

    return pBasicProps->GetSymbolNumberStr();
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::SetSymbolReferenceNumber(int value)
{
    if (GetSymbolReferenceNumber() != value)
    {
        PSS_BasicProperties  basicProps;
        PSS_BasicProperties* pCurBasicProps = static_cast<PSS_BasicProperties*>(GetProperty(ZS_BP_PROP_BASIC));

        if (pCurBasicProps)
        {
            basicProps = *pCurBasicProps;
            basicProps.SetSymbolNumber(value);
            SetProperty(&basicProps);

            // the symbol has changed, notify all references
            PSS_SymbolObserverMsg msg(PSS_SymbolObserverMsg::IEActionType::IE_AT_ElementHasChanged, this);
            NotifyAllObservers(&msg);

            // Redraw the symbol
            RedrawSymbol();
            return TRUE;
        }

        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::SetSymbolReferenceNumberStr(const CString& value)
{
    if (GetSymbolReferenceNumberStr() != value)
    {
        PSS_BasicProperties  basicProps;
        PSS_BasicProperties* pCurBasicProps = static_cast<PSS_BasicProperties*>(GetProperty(ZS_BP_PROP_BASIC));

        if (pCurBasicProps)
        {
            basicProps = *pCurBasicProps;
            basicProps.SetSymbolNumber(value);
            SetProperty(&basicProps);

            // the symbol has changed, notify all references
            PSS_SymbolObserverMsg msg(PSS_SymbolObserverMsg::IEActionType::IE_AT_ElementHasChanged, this);
            NotifyAllObservers(&msg);

            // redraw the symbol
            RedrawSymbol();
            return TRUE;
        }

        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::Match(const CString&          argument,
                       PSS_PropertyAttributes* pPropAttributes,
                       bool                    caseSensitive,
                       bool                    partialSearch)
{
    if (!pPropAttributes)
        return false;

    PSS_Properties::IPropertySet propSet;

    // get the property set from object
    FillProperties(propSet);

    // match the property set with the property attributes
    bool RetValue = pPropAttributes->Match(propSet, argument, caseSensitive, partialSearch);

    // remove all properties
    PSS_Properties::IPropertyIterator it(&propSet);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return RetValue;
}
//---------------------------------------------------------------------------
CString PSS_Symbol::RetrieveUnitGUID(const CString& name, bool& error) const
{
    PSS_ProcessGraphModelMdl* pModel =
            dynamic_cast<PSS_ProcessGraphModelMdl*>(const_cast<PSS_Symbol*>(this)->GetOwnerModel());

    if (pModel)
        return pModel->RetrieveUnitGUID(name, error);

    error = true;

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_Symbol::RetrieveUnitName(const CString& guid, bool& error) const
{
    PSS_ProcessGraphModelMdl* pModel =
            dynamic_cast<PSS_ProcessGraphModelMdl*>(const_cast<PSS_Symbol*>(this)->GetOwnerModel());

    if (pModel)
        return pModel->RetrieveUnitName(guid, error);

    error = true;

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_Symbol::RetrieveUnitDescription(const CString& guid, bool& error) const
{
    PSS_ProcessGraphModelMdl* pModel =
            dynamic_cast<PSS_ProcessGraphModelMdl*>(const_cast<PSS_Symbol*>(this)->GetOwnerModel());

    if (pModel)
        return pModel->RetrieveUnitDescription(guid, error);

    error = true;

    return _T("");
}
//---------------------------------------------------------------------------
float PSS_Symbol::RetrieveUnitCost(const CString& guid, bool& error) const
{
    PSS_ProcessGraphModelMdl* pModel =
            dynamic_cast<PSS_ProcessGraphModelMdl*>(const_cast<PSS_Symbol*>(this)->GetOwnerModel());

    if (pModel)
        return pModel->RetrieveUnitCost(guid, error);

    error = true;

    return 0;
}
//---------------------------------------------------------------------------
CString PSS_Symbol::RetrieveLogicalSystemGUID(const CString& name, bool& error) const
{
    PSS_ProcessGraphModelMdl* pModel =
            dynamic_cast<PSS_ProcessGraphModelMdl*>(const_cast<PSS_Symbol*>(this)->GetOwnerModel());

    if (pModel)
        return pModel->RetrieveLogicalSystemGUID(name, error);

    error = true;

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_Symbol::RetrieveLogicalSystemName(const CString& guid, bool& error) const
{
    PSS_ProcessGraphModelMdl* pModel =
            dynamic_cast<PSS_ProcessGraphModelMdl*>(const_cast<PSS_Symbol*>(this)->GetOwnerModel());

    if (pModel)
        return pModel->RetrieveLogicalSystemName(guid, error);

    error = true;

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_Symbol::RetrieveLogicalSystemDescription(const CString& guid, bool& error) const
{
    PSS_ProcessGraphModelMdl* pModel =
            dynamic_cast<PSS_ProcessGraphModelMdl*>(const_cast<PSS_Symbol*>(this)->GetOwnerModel());

    if (pModel)
        return pModel->RetrieveLogicalSystemDescription(guid, error);

    error = true;

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_Symbol::RetrievePrestationName(const CString& guid, bool& error) const
{
    PSS_ProcessGraphModelMdl* pModel =
            dynamic_cast<PSS_ProcessGraphModelMdl*>(const_cast<PSS_Symbol*>(this)->GetOwnerModel());

    if (pModel)
        return pModel->RetrievePrestationName(guid, error);

    error = true;

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_Symbol::EditSymbolName()
{
    const int          numLabels    = GetNumLabels();
    CODLabelComponent* pSymbolLabel = NULL;

    if (!numLabels)
        pSymbolLabel = CreateSymbolLabel();
    else
    {
        CODLabelComponent* pLabel;

        for (int i = 0; i < numLabels; ++i)
            pLabel = GetLabel(i);
    }
}
//---------------------------------------------------------------------------
bool PSS_Symbol::IsNewNameValid(const CString& value) const
{
    // is new name empty?
    if (value.IsEmpty())
        return false;

    bool result = false;

    ZDProcessGraphModelMdl* pLocalModel = dynamic_cast<ZDProcessGraphModelMdl*>(GetParent());

    // is name already attributed to another symbol?
    if (pLocalModel)
    {
        ZDProcessGraphModelMdl* pRootModel = pLocalModel->GetRoot();

        if (pRootModel)
            result = pRootModel->SymbolNameAlreadyAllocated(value);
    }

    // name is already attributed?
    if (result)
    {
        // get the symbol name
        const CString symbolName = const_cast<PSS_Symbol*>(this)->GetSymbolName();

        // if the name was already be attributed to another symbol, check if the old name
        // is identical to the new one. If it's the case, the user just entered the same name,
        // and there is nothing else to do
        if (value != symbolName)
            return false;
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_Symbol::CopySymbolDefinitionFrom(const CODSymbolComponent& src)
{
    const PSS_Symbol* pSymbol = dynamic_cast<const PSS_Symbol*>(&src);

    if (pSymbol)
    {
        // don't use direct assignment for these values, because if symbols are referenced,
        // no notification will be sent
        SetSymbolName   (pSymbol->GetSymbolName());
        SetSymbolComment(pSymbol->GetSymbolComment());
        SetAbsolutePath (pSymbol->GetAbsolutePath());
        SetModel        (const_cast<PSS_Symbol*>(pSymbol)->GetModel());

        // symbol is local
        m_IsLocal = true;

        // no reference
        m_pReference = NULL;
        m_ReferenceName.Empty();

        m_ShowNameArea           = pSymbol->m_ShowNameArea;
        m_ShowDescriptionArea    = pSymbol->m_ShowDescriptionArea;
        m_ShowAttributeArea      = pSymbol->m_ShowAttributeArea;
        m_RelativeCoordinates    = pSymbol->m_RelativeCoordinates;
        m_Attributes             = pSymbol->m_Attributes;
        m_AllSymbolPosition      = pSymbol->m_AllSymbolPosition;
        m_ChildModelPathName     = pSymbol->m_ChildModelPathName;
        m_ShortcutBitmapPosition = pSymbol->m_ShortcutBitmapPosition;
        m_CurrentLineColor       = pSymbol->m_CurrentLineColor;
        m_CurrentLabelLineColor  = pSymbol->m_CurrentLabelLineColor;
        m_InitialLineColor       = pSymbol->m_InitialLineColor;
        m_InitialLabelLineColor  = pSymbol->m_InitialLabelLineColor;
        m_InitialLineWidth       = pSymbol->m_InitialLineWidth;
        m_InitialLabelLineWidth  = pSymbol->m_InitialLabelLineWidth;

        m_ExternalApplications = pSymbol->m_ExternalApplications;
        m_ExternalApplications.SetParent(this);

        m_ExternalFiles = pSymbol->m_ExternalFiles;
        m_ExternalFiles.SetParent(this);

        // delete the current manager before assigning a new one
        if (m_pDynamicPropManager)
        {
            delete m_pDynamicPropManager;
            m_pDynamicPropManager = NULL;
        }

        m_pDynamicPropManager = pSymbol->m_pDynamicPropManager->Dup();

        // set the area name
        PSS_ODSymbolManipulator::MatchSymbolAreaName(this, const_cast<CODSymbolComponent*>(&src));
    }
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetIsLocal(bool value)
{
    if (value)
    {
        SetCurrentLineColor (m_InitialLineColor);
        SetCurrentLabelColor(m_InitialLabelLineColor);
    }
    else
    {
        SetCurrentLineColor (defCOLOR_BLUE);
        SetCurrentLabelColor(defCOLOR_BLUE);
    }

    m_IsLocal = value;

    RedrawSymbol();
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::DuplicateStyleOnTwinSymbol()
{
    return FALSE;
}
//---------------------------------------------------------------------------
CString PSS_Symbol::GetRiskLevel() const
{
    if (IsProcess() || IsProcedure() || IsStart() || IsStop())
    {
        PSS_BasicProperties* pBasicProps = static_cast<PSS_BasicProperties*>(GetProperty(ZS_BP_PROP_BASIC));

        if (pBasicProps)
            return pBasicProps->GetSymbolRiskLevel();
    }

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetRiskLevel(const CString& level)
{
    if (IsProcess() || IsProcedure() || IsStart() || IsStop())
    {
        PSS_BasicProperties* pBasicProps = static_cast<PSS_BasicProperties*>(GetProperty(ZS_BP_PROP_BASIC));

        if (pBasicProps)
            pBasicProps->SetSymbolRiskLevel(level);
    }
}
//---------------------------------------------------------------------------
void PSS_Symbol::ShowInError(bool value)
{
    if (value)
    {
        SetCurrentLineColor (defCOLOR_RED);
        SetCurrentLabelColor(defCOLOR_RED);
    }
    else
    if (IsLocal())
    {
        SetCurrentLineColor (m_InitialLineColor);
        SetCurrentLabelColor(m_InitialLabelLineColor);
    }
    else
    {
        SetCurrentLineColor (defCOLOR_BLUE);
        SetCurrentLabelColor(defCOLOR_BLUE);
    }

    RedrawSymbol();
}
//---------------------------------------------------------------------------
void PSS_Symbol::ApplyFormatFromObject(CODSymbolComponent& srcObj, bool font, bool fill, bool line)
{
    PSS_ODSymbolManipulator::ApplyFormatFromObject(this, srcObj, font, fill, line);
}
//---------------------------------------------------------------------------
CODComponent* PSS_Symbol::GetLocalSymbol()
{
    if (IsLocal())
        return NULL;

    PSS_ProcessGraphModelMdl* pRootModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());

    if (pRootModel)
    {
        CODComponentSet* pSet = pRootModel->FindSymbol(GetSymbolName(), _T(""), true, true, true);

        // if found, return it
        if (pSet && pSet->GetSize() > 0)
            return pSet->GetAt(0);
    }

    return NULL;
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_Symbol::GetReferenceSymbols()
{
    if (!IsLocal())
        return NULL;

    PSS_ProcessGraphModelMdl* pRootModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());

    if (pRootModel)
    {
        CODComponentSet* pSet = pRootModel->FindSymbol(GetSymbolName(), _T(""), true, true, false);

        if (pSet)
        {
            const int compCount = pSet->GetSize();

            // remove own symbol from set
            for (int i = compCount - 1; i >= 0; --i)
                if (pSet->GetAt(i) == this)
                    pSet->RemoveAt(i);
        }

        return pSet;
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_Symbol::AssignReferenceSymbol(CODSymbolComponent* pReference)
{
    RemoveReferenceSymbol();

    m_pReference = pReference;

    PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(m_pReference);

    if (pSymbol)
    {
        // set the same name
        SetSymbolName(pSymbol->GetSymbolName());

        // set as reference
        SetIsLocal(false);

        // attach this symbol to the source reference
        pSymbol->AttachObserver(this);
    }
}
//---------------------------------------------------------------------------
void PSS_Symbol::RemoveReferenceSymbol()
{
    if (m_pReference)
    {
        PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(m_pReference);

        if (pSymbol)
            pSymbol->DetachObserver(this);
    }

    m_pReference = NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::CreateEmptyChildModel(CODModel* pParent)
{
    return FALSE;
}
//---------------------------------------------------------------------------
CODModel* PSS_Symbol::GetOwnerModel()
{
    // if the parent is a model
    CODComponent* pComp = GetParent();

    while (pComp)
    {
        PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pComp);

        // if a model was found, return it
        if (pModel)
            return pModel;

        // get its parent
        pComp = pComp->GetParent();
    }

    return NULL;
}
//---------------------------------------------------------------------------
CODModel* PSS_Symbol::GetRootModel()
{
    PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetOwnerModel());

    // get the root model
    if (pModel)
        return pModel->GetRoot();

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetModifiedFlag(BOOL value)
{
    CODModel* pModel = GetRootModel();

    if (pModel)
        pModel->SetModifiedFlag(value);
}
//---------------------------------------------------------------------------
void PSS_Symbol::RedrawSymbol()
{
    PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetParent());

    // if the parent is a model
    if (pModel)
        pModel->RedrawComponent(*this);
}
//---------------------------------------------------------------------------
bool PSS_Symbol::FillProperties(PSS_Properties::IPropertySet& propSet, bool numericValue, bool groupValue)
{
    PSS_BasicProperties* pBasicProps = static_cast<PSS_BasicProperties*>(GetProperty(ZS_BP_PROP_BASIC));

    if (!pBasicProps)
        return false;

    CString name;

    if (numericValue)
    {
        name = pBasicProps->GetSymbolName();
        name.Remove('\n');
        name.Replace('\r', ' ');
    }

    std::unique_ptr<PSS_Property> pProp;

    // get the name property from the general group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_BASIC_TITLE,
                                 ZS_BP_PROP_BASIC,
                                 IDS_Z_SYMBOL_NAME_NAME,
                                 M_Symbol_Name_ID,
                                 IDS_Z_SYMBOL_NAME_DESC,
                                 numericValue ? name : pBasicProps->GetSymbolName(),
                                 !IsLocal() || SymbolNameTextEditReadOnly() ? PSS_Property::IEType::IE_T_EditMultilineReadOnly :
                                                                              PSS_Property::IEType::IE_T_EditMultiline));

    // allow the characters to be filtered on this property
    pProp->EnableCharFilter(true);

    propSet.Add(pProp.get());
    pProp.release();

    // get the description property from the general group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_BASIC_TITLE,
                                 ZS_BP_PROP_BASIC,
                                 IDS_Z_SYMBOL_DESCRIPTION_NAME,
                                 M_Symbol_Description_ID,
                                 IDS_Z_SYMBOL_DESCRIPTION_DESC,
                                 pBasicProps->GetSymbolDescription(),
                                 !IsLocal() || CommentTextEditReadOnly() ? PSS_Property::IEType::IE_T_EditMultilineReadOnly :
                                                                           PSS_Property::IEType::IE_T_EditMultiline));
    propSet.Add(pProp.get());
    pProp.release();

    // get the reference property from the general group
    if (numericValue)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_BASIC_TITLE,
                                     ZS_BP_PROP_BASIC,
                                     IDS_Z_SYMBOL_NUMBER_NAME,
                                     M_Symbol_Number_ID,
                                     IDS_Z_SYMBOL_NUMBER_DESC,
                                     double(pBasicProps->GetSymbolNumber()),
                                     IsLocal() ? PSS_Property::IEType::IE_T_EditNumber : PSS_Property::IEType::IE_T_EditNumberReadOnly));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_BASIC_TITLE,
                                     ZS_BP_PROP_BASIC,
                                     IDS_Z_SYMBOL_NUMBER_NAME,
                                     M_Symbol_Number_ID,
                                     IDS_Z_SYMBOL_NUMBER_DESC,
                                     pBasicProps->GetSymbolNumberStr(),
                                     IsLocal() ? PSS_Property::IEType::IE_T_EditString : PSS_Property::IEType::IE_T_EditStringReadOnly));

    propSet.Add(pProp.get());
    pProp.release();

    // get the risk level property from the general group
    if (IsProcess() || IsProcedure() || IsStart() || IsStop())
    {
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_BASIC_TITLE,
                                     ZS_BP_PROP_BASIC,
                                     IDS_Z_SYMBOL_RISK_LEVEL_NAME,
                                     M_Symbol_Risk_Level_ID,
                                     IDS_Z_SYMBOL_RISK_LEVEL_DESC,
                                     pBasicProps->GetSymbolRiskLevel(),
                                     PSS_Property::IEType::IE_T_EditStringReadOnly));

        propSet.Add(pProp.get());
        pProp.release();
    }

    // the external link properties are added by the external app properties manager itself
    if (IsLocal() && AcceptExtApp())
    {
        if (!PSS_ExtAppPropertyMgr::FillProperties(propSet, numericValue, groupValue))
            return false;

        // segregation conceptor
        PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());

        // if messenger activated
        if (pModel && pModel->GetUseWorkflow())
            if (!PSS_ExtAppPropertyMgr::FillPropertiesMessenger(propSet, numericValue, groupValue))
                return false;
    }

    // the external file properties are added by the external file properties manager itself
    if (IsLocal() && AcceptExtFile())
    {
        if (!PSS_ExtFilePropertyMgr::FillProperties(propSet, numericValue, groupValue))
            return false;

        // segregation conceptor
        PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());

        // if messenger activated
        if (pModel && pModel->GetUseWorkflow())
            if (!PSS_ExtFilePropertyMgr::FillPropertiesMessenger(propSet, numericValue, groupValue))
                return false;
    }

    // dynamic properties
    if (m_pDynamicPropManager)
        if (!m_pDynamicPropManager->FillProperties(propSet, numericValue, groupValue))
            return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::SaveProperties(PSS_Properties::IPropertySet& propSet)
{
    if (!IsLocal())
        return true;

    PSS_Properties::IPropertyIterator it(&propSet);

    // iterate through the data list and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        // if hasn't changed, continue
        if (!pProp->GetHasChanged())
            continue;

        if (pProp->GetCategoryID() == ZS_BP_PROP_BASIC)
            switch (pProp->GetItemID())
            {
                case M_Symbol_Name_ID:        SetSymbolName              (pProp->GetValueString()); break;
                case M_Symbol_Description_ID: SetSymbolComment           (pProp->GetValueString()); break;
                case M_Symbol_Number_ID:      SetSymbolReferenceNumberStr(pProp->GetValueString()); break;
                case M_Symbol_Risk_Level_ID:  SetRiskLevel               (pProp->GetValueString()); break;
            }
    }

    if (!PSS_ExtAppPropertyMgr::SaveProperties(propSet) || !PSS_ExtFilePropertyMgr::SaveProperties(propSet))
        return false;

    if (m_pDynamicPropManager)
        if (!m_pDynamicPropManager->SaveProperties(propSet))
            return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::FillProperty(PSS_Property& prop)
{
    PSS_BasicProperties* pBasicProps = static_cast<PSS_BasicProperties*>(GetProperty(ZS_BP_PROP_BASIC));

    if (!pBasicProps)
        return false;

    if (prop.GetCategoryID() == ZS_BP_PROP_BASIC)
        switch (prop.GetItemID())
        {
            case M_Symbol_Name_ID:        prop.SetValueString(pBasicProps->GetSymbolName());        break;
            case M_Symbol_Description_ID: prop.SetValueString(pBasicProps->GetSymbolDescription()); break;
            case M_Symbol_Number_ID:      prop.SetValueString(pBasicProps->GetSymbolNumberStr());   break;
            case M_Symbol_Risk_Level_ID:  prop.SetValueString(pBasicProps->GetSymbolRiskLevel());   break;
        }

    if (!PSS_ExtAppPropertyMgr::FillProperty(prop) || !PSS_ExtFilePropertyMgr::FillProperty(prop))
        return false;

    if (m_pDynamicPropManager)
        if (!m_pDynamicPropManager->FillProperty(prop))
            return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::SaveProperty(PSS_Property& prop)
{
    if (!IsLocal())
        return true;

    if (prop.GetCategoryID() == ZS_BP_PROP_BASIC)
    {
        switch (prop.GetItemID())
        {
            case M_Symbol_Name_ID:        SetSymbolName              (prop.GetValueString()); break;
            case M_Symbol_Description_ID: SetSymbolComment           (prop.GetValueString()); break;
            case M_Symbol_Number_ID:      SetSymbolReferenceNumberStr(prop.GetValueString()); break;
            case M_Symbol_Risk_Level_ID:  SetRiskLevel               (prop.GetValueString()); break;
        }

        // set the modified flag
        SetModifiedFlag();
    }

    if (!PSS_ExtAppPropertyMgr::SaveProperty(prop) || !PSS_ExtFilePropertyMgr::SaveProperty(prop))
        return false;

    if (m_pDynamicPropManager)
        if (!m_pDynamicPropManager->SaveProperty(prop))
            return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::CheckPropertyValue(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props)
{
    // if needed to check the reference number, check if allowed
    if (prop.GetCategoryID() == ZS_BP_PROP_BASIC)
        if (prop.GetItemID() == M_Symbol_Number_ID)
        {
            PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetParent());

            if (pModel)
            {
                PSS_ProcessGraphModelMdl* pRoot = pModel->GetRoot();

                // if not the same name and already exists, show an error message and put back the initial value
                if (value != GetSymbolReferenceNumberStr() && pRoot && pRoot->ReferenceNumberAlreadyAllocated(value))
                {
                    PSS_MsgBox mBox;
                    mBox.Show(IDS_REFERENCENUMBER_ALREADYEXIST, MB_OK);
                    value = GetSymbolReferenceNumberStr();
                    return false;
                }
            }
        }
        else
        if (prop.GetItemID() == M_Symbol_Name_ID)
            if (!IsNewNameValid(value))
            {
                value = GetSymbolName();
                return false;
            }

    if (!PSS_ExtAppPropertyMgr::CheckPropertyValue(prop, value, props) ||
        !PSS_ExtFilePropertyMgr::CheckPropertyValue(prop, value, props))
        return false;

    if (m_pDynamicPropManager)
        if (!m_pDynamicPropManager->CheckPropertyValue(prop, value, props))
            return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::ProcessExtendedInput(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props, bool& refresh)
{
    bool result = false;

    if (PSS_ExtAppPropertyMgr::ProcessExtendedInput(prop, value, props, refresh))
        result = true;

    if (PSS_ExtFilePropertyMgr::ProcessExtendedInput(prop, value, props, refresh))
        result = true;

    if (m_pDynamicPropManager)
        if (m_pDynamicPropManager->ProcessExtendedInput(prop, value, props, refresh))
            result = true;

    return result;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::ProcessMenuCommand(int                           menuCmdID,
                                    PSS_Property&                 prop,
                                    CString&                      value,
                                    PSS_Properties::IPropertySet& props,
                                    bool&                         refresh)
{
    bool result = false;

    // call the base template class method
    if (PSS_ExtAppPropertyMgr::ProcessMenuCommand(menuCmdID, prop, value, props, refresh))
        result = true;

    if (PSS_ExtFilePropertyMgr::ProcessMenuCommand(menuCmdID, prop, value, props, refresh))
        result = true;

    if (m_pDynamicPropManager)
        if (m_pDynamicPropManager->ProcessMenuCommand(menuCmdID, prop, value, props, refresh))
            result = true;

    return result;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::CreateSymbolProperties()
{
    PSS_BasicProperties propBasic;
    AddProperty(propBasic);

    PSS_ExtAppPropertyMgr::CreateSymbolProperties();
    PSS_ExtFilePropertyMgr::CreateSymbolProperties();

    // create the empty attributes if needed
    if (AcceptDynamicAttributes())
        OnFillDefaultAttributes(&m_Attributes);

    // delete the previous manager before reassigning a new one
    if (m_pDynamicPropManager)
    {
        delete m_pDynamicPropManager;
        m_pDynamicPropManager = NULL;
    }

    m_pDynamicPropManager = new PSS_DynamicProperties();

    if (m_pDynamicPropManager)
        m_pDynamicPropManager->CreateSymbolProperties();

    return true;
}
//---------------------------------------------------------------------------
void PSS_Symbol::UpdateGraphicFromRisk(COLORREF color, BOOL italic)
{
    PSS_ODSymbolManipulator::ChangeTextColor(this, color);
    PSS_ODSymbolManipulator::SetTextItalic  (this, italic);

    RedrawSymbol();
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetCurrentLineColor(COLORREF value)
{
    m_CurrentLineColor = value;
    PSS_ODSymbolManipulator::ChangeLineColor(this, value);
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetCurrentLabelColor(COLORREF value)
{
    m_CurrentLabelLineColor = value;
    PSS_ODSymbolManipulator::ChangeLabelLineColor(this, value);
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetInitialLineColor(COLORREF value)
{
    m_InitialLineColor = value;
    SetCurrentLineColor(value);
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetInitialLineWidth(int value)
{
    m_InitialLineWidth = value;
    PSS_ODSymbolManipulator::ChangeLineWidth(this, value);
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetInitialLabelLineColor(COLORREF value)
{
    m_InitialLabelLineColor = value;
    SetCurrentLabelColor(value);
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetInitialLabelLineWidth(int value)
{
    m_InitialLabelLineWidth = value;
    PSS_ODSymbolManipulator::ChangeLabelLineWidth(this, value);
}
//---------------------------------------------------------------------------
CODComponent* PSS_Symbol::FindSymbol(CODComponent* pMainComponent, const CString& symbolName)
{
    return PSS_ODSymbolManipulator::FindSymbol(pMainComponent, symbolName);
}
//---------------------------------------------------------------------------
CODComponent* PSS_Symbol::FindSymbolInChild(CODComponent* pMainComponent, const CString& symbolName)
{
    return PSS_ODSymbolManipulator::FindSymbolInChild(pMainComponent, symbolName);
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::RemoveSymbol(const CString& symbolName)
{
    return PSS_ODSymbolManipulator::RemoveSymbol(this, symbolName);
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::RemoveSymbol(CODComponent* pMainComponent, CODComponent* pComponent)
{
    return PSS_ODSymbolManipulator::RemoveSymbol(pMainComponent, pComponent);
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEnteringSymbols(CODNodeArray& nodes)
{
    nodes.RemoveAll();

    IODNode* pINode;
    pINode = guid_cast<IODNode*>(this);
    pINode->AddRef();

    if (pINode)
    {
        pINode->GetNodesAdjacentTo(&nodes);
        pINode->Release();
    }

    return nodes.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEnteringSymbols_Left(CODNodeArray& nodes)
{
    // remove all element
    nodes.RemoveAll();

    CODEdgeArray edges;

    // get the entering left edges
    if (!GetEdgesEntering_Left(edges))
        return 0;

    const int edgeSize = edges.GetSize();

    // the edge array contains only the left edges, for each edge, get the symbol attached on the destination
    for (int edgeIndex = 0; edgeIndex < edgeSize; ++edgeIndex)
    {
        // get the link
        IODEdge*          pIEdge       = edges.GetAt(edgeIndex);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
            continue;

        // get the source component attached to the link
        CODComponent* pComp = pLinkIndexed->GetSourceComponent();

        // if a target component is attached to, add it to the array
        if (pComp)
            nodes.Add(guid_cast<IODNode*>(pComp));
    }

    return nodes.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEnteringSymbols_Right(CODNodeArray& nodes)
{
    // remove all element
    nodes.RemoveAll();

    CODEdgeArray edges;

    // get the entering right edges
    if (!GetEdgesEntering_Right(edges))
        return 0;

    const int edgeSize = edges.GetSize();

    // the edge array contains only the right edges, for each edge, get the symbol attached on the destination
    for (int edgeIndex = 0; edgeIndex < edgeSize; ++edgeIndex)
    {
        // get the link
        IODEdge*          pIEdge       = edges.GetAt(edgeIndex);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
            continue;

        // get the source component attached to the link
        CODComponent* pComp = pLinkIndexed->GetSourceComponent();

        // if a target component is attached to, add it to the array
        if (pComp)
            nodes.Add(guid_cast<IODNode*>(pComp));
    }

    return nodes.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEnteringSymbols_Up(CODNodeArray& nodes)
{
    // remove all element
    nodes.RemoveAll();

    // get the entering up edges
    CODEdgeArray edges;

    if (!GetEdgesEntering_Up(edges))
        return 0;

    const int edgeSize = edges.GetSize();

    // the edge array contains only the up edges, for each edge, get the symbol attached on the destination
    for (int edgeIndex = 0; edgeIndex < edgeSize; ++edgeIndex)
    {
        // Get the link
        IODEdge*          pIEdge       = edges.GetAt(edgeIndex);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
            continue;

        // get the source component attached to the link
        CODComponent* pComp = pLinkIndexed->GetSourceComponent();

        // if a target component is attached to, add it to the array
        if (pComp)
            nodes.Add(guid_cast<IODNode*>(pComp));
    }

    return nodes.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEnteringSymbols_Down(CODNodeArray& nodes)
{
    // remove all element
    nodes.RemoveAll();

    CODEdgeArray edges;

    // get the entering down edges
    if (!GetEdgesEntering_Down(edges))
        return 0;

    const int edgeSize = edges.GetSize();

    // the edge array contains only the up edges, for each edge, get the symbol attached on the destination
    for (int edgeIndex = 0; edgeIndex < edgeSize; ++edgeIndex)
    {
        // get the link
        IODEdge*          pIEdge       = edges.GetAt(edgeIndex);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
            continue;

        // get the source component attached to the link
        CODComponent* pComp = pLinkIndexed->GetSourceComponent();

        // if a target component is attached to, add it to the array
        if (pComp)
            nodes.Add(guid_cast<IODNode*>(pComp));
    }

    return nodes.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetFollowingSymbols(CODNodeArray& nodes)
{
    nodes.RemoveAll();

    IODNode* pINode;
    pINode = guid_cast<IODNode*>(this);
    pINode->AddRef();

    if (pINode)
    {
        pINode->GetNodesAdjacentFrom(&nodes);
        pINode->Release();
    }

    return nodes.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetFollowingSymbols_Left(CODNodeArray& nodes)
{
    // remove all element
    nodes.RemoveAll();

    CODEdgeArray edges;

    // get the left edges
    if (!GetEdgesLeaving_Left(edges))
        return 0;

    const int edgeSize = edges.GetSize();

    // the edge array contains only the left edges, for each edge, get the symbol attached on the destination
    for (int edgeIndex = 0; edgeIndex < edgeSize; ++edgeIndex)
    {
        // get the link
        IODEdge*          pIEdge       = edges.GetAt(edgeIndex);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
            continue;

        // now retrieve the target component
        CODComponent* pComp = pLinkIndexed->GetTargetComponent();

        // if a target component is attached to, add it to the array
        if (pComp)
            nodes.Add(guid_cast<IODNode*>(pComp));
    }

    return nodes.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetFollowingSymbols_Right(CODNodeArray& nodes)
{
    // remove all element
    nodes.RemoveAll();

    CODEdgeArray edges;

    // get the right edges
    if (!GetEdgesLeaving_Right(edges))
        return 0;

    const int edgeSize = edges.GetSize();

    // the edge array contains only the right edges, for each edge, get the symbol attached on the destination
    for (int edgeIndex = 0; edgeIndex < edgeSize; ++edgeIndex)
    {
        // get the link
        IODEdge*          pIEdge       = edges.GetAt(edgeIndex);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
            continue;

        // get the target component
        CODComponent* pComp = pLinkIndexed->GetTargetComponent();

        // if a target component is attached to, add it to the array
        if (pComp)
            nodes.Add(guid_cast<IODNode*>(pComp));
    }

    return nodes.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetFollowingSymbols_Up(CODNodeArray& nodes)
{
    // remove all element
    nodes.RemoveAll();

    CODEdgeArray edges;

    // get the up edges
    if (!GetEdgesLeaving_Up(edges))
        return 0;

    const int edgeSize = edges.GetSize();

    // the edge array contains only the up edges, for each edge, get the symbol attached on the destination
    for (int edgeIndex = 0; edgeIndex < edges.GetSize(); ++edgeIndex)
    {
        // get the link
        IODEdge*          pIEdge       = edges.GetAt(edgeIndex);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
            continue;

        // get the target component
        CODComponent* pComp = pLinkIndexed->GetTargetComponent();

        // if a target component is attached to, add it to the array
        if (pComp)
            nodes.Add(guid_cast<IODNode*>(pComp));
    }

    return nodes.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetFollowingSymbols_Down(CODNodeArray& nodes)
{
    // remove all element
    nodes.RemoveAll();

    CODEdgeArray edges;

    // get the down edges
    if (!GetEdgesLeaving_Down(edges))
        return 0;

    const int edgeSize = edges.GetSize();

    // the edge array contains only the down edges, for each edge, get the symbol attached on the destination
    for (int edgeIndex = 0; edgeIndex < edges.GetSize(); ++edgeIndex)
    {
        // get the link
        IODEdge*          pIEdge       = edges.GetAt(edgeIndex);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
            continue;

        // get the target component
        CODComponent* pComp = pLinkIndexed->GetTargetComponent();

        // if a target component is attached to, add it to the array
        if (pComp)
            nodes.Add(guid_cast<IODNode*>(pComp));
    }

    return nodes.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEdgesEntering(CODEdgeArray& edges)
{
    edges.RemoveAll();

    IODNode* pINode;
    pINode = guid_cast<IODNode*>(this);
    pINode->AddRef();

    if (pINode)
    {
        pINode->GetEdgesEntering(&edges);
        pINode->Release();
    }

    return edges.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEdgesEntering_Left(CODEdgeArray& edges)
{
    return GetEdgesEntering_Name(M_PortLEFTComponentLabel, edges);
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEdgesEntering_Right(CODEdgeArray& edges)
{
    return GetEdgesEntering_Name(M_PortRIGHTComponentLabel, edges);
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEdgesEntering_Up(CODEdgeArray& edges)
{
    return GetEdgesEntering_Name(M_PortUPComponentLabel, edges);
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEdgesEntering_Down(CODEdgeArray& edges)
{
    return GetEdgesEntering_Name(M_PortDOWNComponentLabel, edges);
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEdgesLeaving(CODEdgeArray& edges)
{
    edges.RemoveAll();

    IODNode* pINode;
    pINode = guid_cast<IODNode*>(this);
    pINode->AddRef();

    if (pINode)
    {
        pINode->GetEdgesLeaving(&edges);
        pINode->Release();
    }

    return edges.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEdgesLeaving_Left(CODEdgeArray& edges)
{
    return GetEdgesLeaving_Name(M_PortLEFTComponentLabel, edges);
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEdgesLeaving_Right(CODEdgeArray& edges)
{
    return GetEdgesLeaving_Name(M_PortRIGHTComponentLabel, edges);
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEdgesLeaving_Up(CODEdgeArray& edges)
{
    return GetEdgesLeaving_Name(M_PortUPComponentLabel, edges);
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEdgesLeaving_Down(CODEdgeArray& edges)
{
    return GetEdgesLeaving_Name(M_PortDOWNComponentLabel, edges);
}
//---------------------------------------------------------------------------
void PSS_Symbol::Serialize(CArchive& ar)
{
    // serialize the canvas model
    CODSymbolComponent::Serialize(ar);

    // only if the object is serialize from and to a document
    if (ar.m_pDocument)
        if (ar.IsStoring())
        {
            CODModel* pNULLModel = NULL;
            CString   emptyString(_T(""));

            PSS_Symbol* pRefSymbol = dynamic_cast<PSS_Symbol*>(m_pReference);

            if (pRefSymbol)
                m_ReferenceName = pRefSymbol->GetSymbolReferenceNumberStr();
            else
                m_ReferenceName.Empty();

            ar << m_Name;
            ar << m_Comment;
            ar << WORD(m_IsLocal);
            ar << m_ObjectPath;
            ar << m_ReferenceName;

            ar << WORD(m_ShowNameArea);
            ar << WORD(m_ShowDescriptionArea);
            ar << WORD(m_ShowAttributeArea);

            ar << m_CurrentLineColor;
            ar << m_CurrentLabelLineColor;
            ar << m_InitialLineColor;
            ar << m_InitialLineWidth;
            ar << m_InitialLabelLineColor;
            ar << m_InitialLabelLineWidth;

            // serialize the attributes
            ar << m_Attributes;

            PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(m_pModel);

            // keep the child model path name if there is one
            if (pModel)
                ar << pModel->GetAbsolutePath();
            else
                ar << emptyString;

            if (!IsChildModelRef())
                ar << m_pModel;
            else
                ar << pNULLModel;

            // serialize the dynamic properties
            ar << m_pDynamicPropManager;
        }
        else
        {
            ar >> m_Name;
            ar >> m_Comment;

            WORD wValue;
            ar >> wValue;
            m_IsLocal = bool(wValue);

            ar >> m_ObjectPath;

            // used to rebuild the reference
            ar >> m_ReferenceName;

            ar >> wValue;
            m_ShowNameArea = bool(wValue);

            ar >> wValue;
            m_ShowDescriptionArea = bool(wValue);

            ar >> wValue;
            m_ShowAttributeArea = bool(wValue);

            PSS_BaseDocument* pBaseDoc = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

            // if is the right version, deserialize the current line and label color
            if (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 19)
            {
                ar >> m_CurrentLineColor;
                ar >> m_CurrentLabelLineColor;
            }
            else
            {
                // otherwise initialize them to their respective initial colors
                m_CurrentLineColor = m_InitialLineColor;
                m_CurrentLabelLineColor = m_InitialLabelLineColor;
            }

            ar >> m_InitialLineColor;
            ar >> m_InitialLineWidth;
            ar >> m_InitialLabelLineColor;
            ar >> m_InitialLabelLineWidth;

            // serialize the attributes
            m_Attributes.RemoveAllAttributes();
            ar >> m_Attributes;

            // the child model path name
            ar >> m_ChildModelPathName;

            // the target model
            ar >> m_pModel;

            // delete the existing manager before creating a new one
            if (m_pDynamicPropManager)
            {
                delete m_pDynamicPropManager;
                m_pDynamicPropManager = NULL;
            }

            // serialize the dynamic properties
            if (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 21)
                ar >> (CObject*&)m_pDynamicPropManager;

            if (!m_pDynamicPropManager)
                m_pDynamicPropManager = new PSS_DynamicProperties();

            CODEditProperties* pPropEdit = static_cast<CODEditProperties*>(GetProperty(OD_PROP_EDIT));

            if (pPropEdit)
                pPropEdit->SetCanSelect(TRUE);
        }

    // serialize external applications and files
    if (!m_IsInCreationProcess)
    {
        PSS_ExtAppPropertyMgr::Serialize(ar);
        PSS_ExtFilePropertyMgr::Serialize(ar);
    }

    // once loaded, call the base function to finalize the embedded element positions
    AdjustElementPosition();
}
//---------------------------------------------------------------------------
bool PSS_Symbol::OnPostCreation(CODModel* pModel, CODController* pCtrl)
{
    if (!InitializeAttributeAreas())
        return false;

    // check the components size
    AdjustAreaPosition();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::OnPreDelete(CODModel* pModel, CODController* pCtrl)
{
    return true;
}
//---------------------------------------------------------------------------
void PSS_Symbol::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_SymbolObserverMsg* pObserverMsg = dynamic_cast<PSS_SymbolObserverMsg*>(pMsg);

    if (pSubject && pSubject != this && pObserverMsg)
    {
        PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pSubject);

        if (pSymbol)
            switch (pObserverMsg->GetActionType())
            {
                case PSS_SymbolObserverMsg::IEActionType::IE_AT_ElementHasChanged:
                case PSS_SymbolObserverMsg::IEActionType::IE_AT_None:                  CopySymbolDefinitionFrom((PSS_Symbol&)*pSymbol); break;
                case PSS_SymbolObserverMsg::IEActionType::IE_AT_NameHasChanged:        SetSymbolName(pSymbol->GetSymbolName());         break;
                case PSS_SymbolObserverMsg::IEActionType::IE_AT_DescriptionHasChanged: SetSymbolComment(pSymbol->GetSymbolComment());   break;
            }

        // finalize the symbol element positions
        AdjustElementPosition();
    }
}
//---------------------------------------------------------------------------
void PSS_Symbol::OnMove()
{
    CODSymbolComponent::OnMove();

    // call the function to finalize the embedded element positions
    AdjustElementPosition();
}
//---------------------------------------------------------------------------
bool PSS_Symbol::OnMouseMove(UINT flags, const CPoint& point, CODController& ctrl)
{
    return PSS_SymbolAttributes::OnMouseMove(flags, point, ctrl);
}
//---------------------------------------------------------------------------
bool PSS_Symbol::OnLButtonDown(UINT flags, const CPoint& point, CODController& ctrl)
{
    return PSS_SymbolAttributes::OnLButtonDown(flags, point, ctrl);
}
//---------------------------------------------------------------------------
bool PSS_Symbol::OnLButtonUp(UINT flags, const CPoint& point, CODController& ctrl)
{
    return PSS_SymbolAttributes::OnLButtonUp(flags, point, ctrl);
}
//---------------------------------------------------------------------------
bool PSS_Symbol::OnLButtonDblClk(UINT flags, const CPoint& point, CODController& ctrl)
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::OnRButtonDown(UINT flags, const CPoint& point, CODController& ctrl)
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::OnRButtonUp(UINT flags, const CPoint& point, CODController& ctrl)
{
    return false;
}
//---------------------------------------------------------------------------
void PSS_Symbol::OnPostDoubleClick(CODModel* pModel, CODController* pCtrl)
{}
//---------------------------------------------------------------------------
void PSS_Symbol::OnLinkConnect(CODLinkComponent* pLink)
{}
//---------------------------------------------------------------------------
void PSS_Symbol::OnLinkDisconnect(CODLinkComponent* pLink)
{}
//---------------------------------------------------------------------------
bool PSS_Symbol::OnFillDefaultAttributes(PSS_PropertyAttributes* pAttributes)
{
    if (AcceptDynamicAttributes() && GetAttributeTextEdit())
    {
        GetAttributeTextEdit()->SetText(GetAttributeString(pAttributes));
        RedrawSymbol();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::OnChangeAttributes(PSS_PropertyAttributes* pAttributes)
{
    if (AcceptDynamicAttributes() && GetAttributeTextEdit())
    {
        // copy the new attributes first
        m_Attributes = *pAttributes;

        // redraw the attribute text
        GetAttributeTextEdit()->SetText(GetAttributeString(pAttributes));
        RedrawSymbol();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::OnPrePropertyChanged(const CString& newValue, PSS_Property& prop, PSS_Properties::IPropertySet& props)
{
    bool result = true;

    // call the base template class method
    if (!PSS_ExtAppPropertyMgr::OnPrePropertyChanged(newValue, prop, props))
        result = false;

    if (!PSS_ExtFilePropertyMgr::OnPrePropertyChanged(newValue, prop, props))
        result = false;

    if (m_pDynamicPropManager)
        if (!m_pDynamicPropManager->OnPrePropertyChanged(newValue, prop, props))
            result = false;

    return result;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::OnPostPropertyChanged(PSS_Property& prop, PSS_Properties::IPropertySet& props, bool& refresh)
{
    bool result = false;

    // call the base template class method
    if (PSS_ExtAppPropertyMgr::OnPostPropertyChanged(prop, props, refresh))
        result = true;

    if (PSS_ExtFilePropertyMgr::OnPostPropertyChanged(prop, props, refresh))
        result = true;

    if (m_pDynamicPropManager)
        if (m_pDynamicPropManager->OnPostPropertyChanged(prop, props, refresh))
            result = true;

    return result;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::OnDropInternalPropertyItem(PSS_Property&                 srcProperty,
                                            PSS_Property&                 dstProperty,
                                            bool                          top2Down,
                                            PSS_Properties::IPropertySet& props)
{
    if (m_pDynamicPropManager)
        if (!m_pDynamicPropManager->OnDropInternalPropertyItem(srcProperty, dstProperty, top2Down, props))
            return false;

    return true;
}
//---------------------------------------------------------------------------
void PSS_Symbol::OnSymbolNameChanged(CODComponent& comp, const CString& oldName)
{}
//---------------------------------------------------------------------------
void PSS_Symbol::OnPageNameChanged(PSS_ProcessGraphPage* pPage, const CString& oldName)
{}
//---------------------------------------------------------------------------
void PSS_Symbol::OnUserEntityChanged(PSS_UserEntity* pUserEntity, const CString& oldName)
{}
//---------------------------------------------------------------------------
void PSS_Symbol::OnDeleteSymbol()
{
    RemoveReferenceSymbol();
}
//---------------------------------------------------------------------------
bool PSS_Symbol::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    return false;
}
//---------------------------------------------------------------------------
CODLabelComponent* PSS_Symbol::CreateSymbolLabel()
{
    return CreateLabel(_T("Test"));
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEdgesEntering_Name(const CString& name, CODEdgeArray& edges)
{
    // get all entering edges
    if (!GetEdgesEntering(edges))
        return 0;

    // iterate through all edges and determine what is the destination port name
    for (int edgeIndex = 0; edgeIndex < edges.GetSize(); ++edgeIndex)
    {
        // get the link
        IODEdge*          pIEdge       = edges.GetAt(edgeIndex);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
            continue;

        // get the target port to check its name
        CODPortComponent* pPort = pLinkIndexed->GetTargetPort();

        // if no source port or the name doesn't match, remove it from the array
        if (!pPort || pPort->GetName() != name)
        {
            edges.RemoveAt(edgeIndex);
            --edgeIndex;
        }
    }

    // return the array size
    return edges.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_Symbol::GetEdgesLeaving_Name(const CString& name, CODEdgeArray& edges)
{
    // get all leaving edges
    if (!GetEdgesLeaving(edges))
        return 0;

    // iterate through all edges and determine what is the source port name
    for (int edgeIndex = 0; edgeIndex < edges.GetSize(); ++edgeIndex)
    {
        // get the link
        IODEdge*          pIEdge       = edges.GetAt(edgeIndex);
        CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

        if (!pLinkIndexed)
            continue;

        // get the source port to check its name
        CODPortComponent* pPort = pLinkIndexed->GetSourcePort();

        // if no source port or the name doesn't match, remove it from the array
        if (!pPort || pPort->GetName() != name)
        {
            edges.RemoveAt(edgeIndex);
            --edgeIndex;
        }
    }

    // return the array size
    return edges.GetSize();
}
//---------------------------------------------------------------------------
