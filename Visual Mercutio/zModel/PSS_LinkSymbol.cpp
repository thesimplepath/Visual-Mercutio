/****************************************************************************
 * ==> PSS_LinkSymbol ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a link symbol                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_LinkSymbol.h"

// processsoft
#include "zBaseLib\PSS_DrawFunctions.h"
#include "zBaseLib\PSS_BaseDocument.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zProperty\ZBDynamicProperties.h"
#include "ZUODSymbolManipulator.h"
#include "ProcGraphModelMdl.h"
#include "ZBBasicProp.h"
#include "ZBSymbol.h"
#include "ZBSymbolObserverMsg.h"
#include "ZBDocObserverMsg.h"

// resources
#include "PSS_ResIDs.h"
#include "zModelRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define _CANSELECTCONVERTER 1
//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
PSS_Bitmap PSS_LinkSymbol::m_ShortcutBitmap;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_LinkSymbol, CODLinkComponent, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_LinkSymbol
//---------------------------------------------------------------------------
PSS_LinkSymbol::PSS_LinkSymbol() :
    CODLinkComponent(),
    m_pReference(NULL),
    m_DynamicPropManager(NULL),
    m_IsInCreationProcess(false),
    m_IsLocal(true),
    m_InitialLineColor(defCOLOR_BLACK),
    m_InitialLabelLineColor(defCOLOR_BLACK),
    m_CurrentLineColor(defCOLOR_BLACK),
    m_CurrentLabelLineColor(defCOLOR_BLACK),
    m_InitialLineWidth(1),
    m_InitialLabelLineWidth(1),
    m_InitialLineStyle(PS_SOLID),
    m_CurrentLineWidth(1),
    m_CurrentLineStyle(PS_SOLID),
    m_IsCopy(FALSE)
{
    SetSymbol(this);
    CreateSymbolProperties();
}
//---------------------------------------------------------------------------
PSS_LinkSymbol::PSS_LinkSymbol(const PSS_LinkSymbol& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_LinkSymbol::~PSS_LinkSymbol()
{
    if (m_DynamicPropManager)
        delete m_DynamicPropManager;
}
//---------------------------------------------------------------------------
PSS_LinkSymbol& PSS_LinkSymbol::operator = (const PSS_LinkSymbol& other)
{
    // call the base class assignment operators
    CODLinkComponent::operator = ((const CODLinkComponent&)other);
    ZBExtAppPropertyMgr::operator = ((const ZBExtAppPropertyMgr&)other);
    ZBExtFilePropertyMgr::operator = ((const ZBExtFilePropertyMgr&)other);
    ZVSymbolAttributes::operator = ((const ZVSymbolAttributes&)other);

    m_ObjectPath         = other.m_ObjectPath;
    m_DynamicPropManager = other.m_DynamicPropManager->Dup();
    m_ReferenceName      = other.m_ReferenceName;
    m_IsLocal            = other.m_IsLocal;

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_LinkSymbol::Create(int style, int pointSize, COLORREF color, int transparent)
{
    const BOOL result = CODLinkComponent::Create();

    if (result)
    {
        AssignDefaultProperties();
        SetLineProperty(style, pointSize, color, transparent);
    }

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_LinkSymbol::CreateOrthogonal(int style, int pointSize, COLORREF color, int transparent)
{
    const BOOL result = CODLinkComponent::CreateOrthogonal();

    if (result)
    {
        AssignDefaultProperties();
        SetLineProperty(style, pointSize, color, transparent);
    }

    return result;
}
//---------------------------------------------------------------------------
CODComponent* PSS_LinkSymbol::Dup() const
{
    return new PSS_LinkSymbol(*this);
}
//---------------------------------------------------------------------------
BOOL PSS_LinkSymbol::SetLineProperty(int style, int pointSize, COLORREF color, int transparent)
{
    CODPropPtr pProp = GetProperty(OD_PROP_LINE);

    if (pProp)
    {
        CODLineProperties lineProp(*((CODLineProperties*)((CODProperty*)pProp)));

        if (style != -1)
            lineProp.SetStyle(style);

        if (pointSize != -1)
            lineProp.SetPointSize(pointSize);

        if (color != -1)
            lineProp.SetColor(color);

        if (transparent != -1)
            lineProp.SetTransparent(BOOL(transparent));

        SetProperty(&lineProp);

        return TRUE;
    }

    CODLineProperties lineProp;

    if (style != -1)
        lineProp.SetStyle(style);

    if (pointSize != -1)
        lineProp.SetPointSize(pointSize);

    if (color != -1)
        lineProp.SetColor(color);

    if (transparent != -1)
        lineProp.SetTransparent(BOOL(transparent));

    SetProperty(&lineProp);

    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_LinkSymbol::GetAttributeString(ZBPropertyAttributes* pAttributes) const
{
    if (AcceptDynamicAttributes())
    {
        ZBPropertySet propSet;

        // get the property set from object
        const_cast<PSS_LinkSymbol*>(this)->FillProperties(propSet);

        // format the string
        const CString str = pAttributes->GetString(&propSet);

        ZBPropertyIterator it(&propSet);

        // remove all properties
        for (ZBProperty* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
            delete pProp;

        propSet.RemoveAll();

        return str;
    }

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::RefreshAttributeTextArea(bool redraw)
{
    if (AcceptDynamicAttributes() && GetAttributeTextEdit())
    {
        GetAttributeTextEdit()->SetText(GetAttributeString(&m_Attributes));

        if (redraw)
            RedrawSymbol();
    }
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::GetShowTitleText() const
{
    return (AcceptDynamicAttributes() ? m_Attributes.GetDisplayTitleText() : false);
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetShowTitleText(bool value)
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
//---------------------------------------------------------------------------
ZBSymbolEdit* PSS_LinkSymbol::CreateEditText(const CString& areaName, const CString& editName, CODComponent* pParent)
{
    return ZUODSymbolManipulator::CreateEditText(this, areaName, editName, pParent);
}
//---------------------------------------------------------------------------
ZBSymbolEdit* PSS_LinkSymbol::CreateAndReplaceEditText(const CString& editName, CODComponent* pParent)
{
    return ZUODSymbolManipulator::CreateAndReplaceEditText(this, editName, pParent);
}
//---------------------------------------------------------------------------
CString PSS_LinkSymbol::GetSymbolName() const
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
        return _T("");

    return pBasicProps->GetSymbolName();
}
//---------------------------------------------------------------------------
BOOL PSS_LinkSymbol::SetSymbolName(const CString& value)
{
    const CString oldName = GetSymbolName();

    if (oldName != value)
    {
        OnSymbolNameChange(oldName, value);

        if (GetSymbolNameTextEdit())
            GetSymbolNameTextEdit()->SetText(value);

        ZBBasicProperties* pCurBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

        if (pCurBasicProps)
        {
            ZBBasicProperties basicProps = *pCurBasicProps;
            basicProps.SetSymbolName(value);
            SetProperty(&basicProps);

            // notify the owner model about symbol changes
            ZDProcessGraphModelMdl* pRootModel = dynamic_cast<ZDProcessGraphModelMdl*>(GetRootModel());

            if (pRootModel)
                pRootModel->OnSymbolNameChanged(*this, oldName);

            // the symbol has changed, notify all refences
            ZBSymbolObserverMsg msg(ZBSymbolObserverMsg::NameHasChanged, this);
            NotifyAllObservers(&msg);

            // build the message
            ZBDocObserverMsg docMsg(ZBDocObserverMsg::ChangedElement, NULL, pRootModel, this);

            AfxGetMainWnd()->SendMessageToDescendants(UM_ELEMENTMODIFIEDDOCUMENTMODEL, 0, LPARAM(&docMsg));

            // redraw the symbol
            RedrawSymbol();

            return TRUE;
        }

        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_LinkSymbol::GetSymbolComment() const
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
        return _T("");

    return pBasicProps->GetSymbolDescription();
}
//---------------------------------------------------------------------------
BOOL PSS_LinkSymbol::SetSymbolComment(const CString& value)
{
    if (GetSymbolComment() != value)
    {
        if (GetCommentTextEdit())
            GetCommentTextEdit()->SetText(value);

        ZBBasicProperties* pCurBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

        if (pCurBasicProps)
        {
            ZBBasicProperties basicProps = *pCurBasicProps;
            basicProps.SetSymbolDescription(value);
            SetProperty(&basicProps);

            // the symbol has changed, notify all refences
            ZBSymbolObserverMsg msg(ZBSymbolObserverMsg::DescriptionHasChanged, this);
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
int PSS_LinkSymbol::GetSymbolReferenceNumber() const
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
        return -1;

    return pBasicProps->GetSymbolNumber();
}
//---------------------------------------------------------------------------
CString PSS_LinkSymbol::GetSymbolReferenceNumberStr() const
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
        return _T("");

    return pBasicProps->GetSymbolNumberStr();
}
//---------------------------------------------------------------------------
BOOL PSS_LinkSymbol::SetSymbolReferenceNumber(int value)
{
    if (GetSymbolReferenceNumber() != value)
    {
        ZBBasicProperties* pCurBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

        if (pCurBasicProps)
        {
            ZBBasicProperties basicProps = *pCurBasicProps;
            basicProps.SetSymbolNumber(value);
            SetProperty(&basicProps);

            // the symbol has changed, notify all refences
            NotifyAllObservers(NULL);

            // redraw the symbol
            RedrawSymbol();

            return TRUE;
        }

        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_LinkSymbol::SetSymbolReferenceNumberStr(const CString& value)
{
    if (GetSymbolReferenceNumberStr() != value)
    {
        ZBBasicProperties* pCurBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

        if (pCurBasicProps)
        {
            ZBBasicProperties basicProps = *pCurBasicProps;
            basicProps.SetSymbolNumber(value);
            SetProperty(&basicProps);

            // the symbol has changed, notify all refences
            NotifyAllObservers(NULL);

            // redraw the symbol
            RedrawSymbol();

            return TRUE;
        }

        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::Match(const CString&        argument,
                           ZBPropertyAttributes* pPropAttributes,
                           bool                  caseSensitive,
                           bool                  partialSearch)
{
    if (!pPropAttributes)
        return false;

    ZBPropertySet propSet;

    // get the property set from object
    FillProperties(propSet);

    // match the property set with the property attributes
    bool result = pPropAttributes->Match(propSet, argument, caseSensitive, partialSearch);

    ZBPropertyIterator it(&propSet);

    // remove all properties
    for (ZBProperty* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return result;
}
//---------------------------------------------------------------------------
CString PSS_LinkSymbol::RetreiveUnitGUID(const CString& name, bool& error) const
{
    ZDProcessGraphModelMdl* pModel =
            dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<PSS_LinkSymbol*>(this)->GetOwnerModel());

    if (pModel)
        return pModel->RetreiveUnitGUID(name, error);

    error = true;

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_LinkSymbol::RetreiveUnitName(const CString& guid, bool& error) const
{
    ZDProcessGraphModelMdl* pModel =
            dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<PSS_LinkSymbol*>(this)->GetOwnerModel());

    if (pModel)
        return pModel->RetreiveUnitName(guid, error);

    error = true;

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_LinkSymbol::RetreiveUnitDescription(const CString& guid, bool& error) const
{
    ZDProcessGraphModelMdl* pModel =
            dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<PSS_LinkSymbol*>(this)->GetOwnerModel());

    if (pModel)
        return pModel->RetreiveUnitDescription(guid, error);

    error = true;

    return _T("");
}
//---------------------------------------------------------------------------
float PSS_LinkSymbol::RetreiveUnitCost(const CString& guid, bool& error) const
{
    ZDProcessGraphModelMdl* pModel =
            dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<PSS_LinkSymbol*>(this)->GetOwnerModel());

    if (pModel)
        return pModel->RetreiveUnitCost(guid, error);

    error = true;

    return 0;
}
//---------------------------------------------------------------------------
CString PSS_LinkSymbol::RetreiveLogicalSystemGUID(const CString& name, bool& error) const
{
    ZDProcessGraphModelMdl* pModel =
            dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<PSS_LinkSymbol*>(this)->GetOwnerModel());

    if (pModel)
        return pModel->RetreiveLogicalSystemGUID(name, error);

    error = true;

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_LinkSymbol::RetreiveLogicalSystemName(const CString& guid, bool& error) const
{
    ZDProcessGraphModelMdl* pModel =
            dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<PSS_LinkSymbol*>(this)->GetOwnerModel());

    if (pModel)
        return pModel->RetreiveLogicalSystemName(guid, error);

    error = true;

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_LinkSymbol::RetreiveLogicalSystemDescription(const CString& guid, bool& error) const
{
    ZDProcessGraphModelMdl* pModel =
            dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<PSS_LinkSymbol*>(this)->GetOwnerModel());

    if (pModel)
        return pModel->RetreiveLogicalSystemDescription(guid, error);

    error = true;

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::EditSymbolName()
{
    const int          numLabels    = GetNumLabels();
    CODLabelComponent* pSymbolLabel = NULL;

    if (!numLabels)
        pSymbolLabel = CreateSymbolLabel();
    else
    {
        CODLabelComponent* pTempLabel;

        for (int i = 0; i < numLabels; ++i)
            pTempLabel = GetLabel(i);
    }
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::IsNewNameValid(const CString& value) const
{
    if (value.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_SYMBOLNAME_EMPTY, MB_OK);
        return false;
    }

    ZDProcessGraphModelMdl* pModel = dynamic_cast<ZDProcessGraphModelMdl*>(GetParent());

    if (pModel)
        // if already exists and not the same, show an error message and put back the initial value
        if (value != GetSymbolName() && pModel->GetRoot()->SymbolNameAlreadyAllocated(value))
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_SYMBOLNAME_ALREADYEXIST, MB_OK);
            return false;
        }
        else
        if (value.FindOneOf(_T(";:\\/")) != -1)
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_SYMBOLNAME_INVALIDCHAR, MB_OK);
            return false;
        }

    return true;
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::CopySymbolDefinitionFrom(const CODSymbolComponent& src)
{
    const PSS_LinkSymbol* pSymbol = dynamic_cast<const PSS_LinkSymbol*>(&src);

    if (pSymbol)
    {
        // don't use direct assignement, if symbols are referenced, not notification will be done
        SetSymbolName   (pSymbol->GetSymbolName());
        SetSymbolComment(pSymbol->GetSymbolComment());
        SetAbsolutePath (pSymbol->GetAbsolutePath());

        // symbol is local
        m_IsLocal = true;

        // no reference
        m_pReference = NULL;
        m_ReferenceName.Empty();

        m_AllSymbolPosition      = pSymbol->m_AllSymbolPosition;
        m_CurrentLineColor       = pSymbol->m_CurrentLineColor;
        m_CurrentLabelLineColor  = pSymbol->m_CurrentLabelLineColor;
        m_InitialLineColor       = pSymbol->m_InitialLineColor;
        m_InitialLineWidth       = pSymbol->m_InitialLineWidth;
        m_InitialLabelLineColor  = pSymbol->m_InitialLabelLineColor;
        m_InitialLabelLineWidth  = pSymbol->m_InitialLabelLineWidth;
        m_ShortcutBitmapPosition = pSymbol->m_ShortcutBitmapPosition;

        m_ExternalApplications = pSymbol->m_ExternalApplications;
        m_ExternalApplications.SetParent(this);

        m_ExternalFiles = pSymbol->m_ExternalFiles;
        m_ExternalFiles.SetParent(this);

        m_DisplayNameArea        = pSymbol->m_DisplayNameArea;
        m_DisplayDescriptionArea = pSymbol->m_DisplayDescriptionArea;
        m_DisplayAttributeArea   = pSymbol->m_DisplayAttributeArea;

        m_RelativeCoordinates = pSymbol->m_RelativeCoordinates;
        m_Attributes          = pSymbol->m_Attributes;

        if (m_DynamicPropManager)
        {
            delete m_DynamicPropManager;
            m_DynamicPropManager = NULL;
        }

        m_DynamicPropManager = pSymbol->m_DynamicPropManager->Dup();

        // set the right area name
        ZUODSymbolManipulator::MatchSymbolAreaName(this, const_cast<CODSymbolComponent*>(&src));
    }
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetIsLocal(bool value)
{
    if (value)
    {
        SetCurrentLineColor(m_InitialLineColor);
        SetCurrentLabelColor(m_InitialLabelLineColor);
    }
    else
    {
        SetCurrentLineColor(defCOLOR_BLUE);
        SetCurrentLabelColor(defCOLOR_BLUE);
    }

    m_IsLocal = value;

    // redraw the symbol
    RedrawSymbol();
}
//---------------------------------------------------------------------------
CString PSS_LinkSymbol::GetRiskLevel() const
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);
    return pBasicProps->GetSymbolRiskLevel();
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetRiskLevel(const CString& level)
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);
    pBasicProps->SetSymbolRiskLevel(level);
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::ShowInError(bool value)
{
    if (value)
    {
        SetCurrentLineColor(defCOLOR_RED);
        SetCurrentLabelColor(defCOLOR_RED);
    }
    else
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

    // redraw the symbol
    RedrawSymbol();
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::ApplyFormatFromObject(CODSymbolComponent& srcObj,
                                           bool                font,
                                           bool                fill,
                                           bool                line)
{
    ZUODSymbolManipulator::ApplyFormatFromObject(this, srcObj, font, fill, line);
}
//---------------------------------------------------------------------------
CODComponent* PSS_LinkSymbol::GetLocalSymbol()
{
    if (IsLocal())
        return NULL;

    ZDProcessGraphModelMdl* pRootModel = dynamic_cast<ZDProcessGraphModelMdl*>(GetRootModel());

    if (pRootModel)
    {
        CODComponentSet* pSet = pRootModel->FindSymbol(GetSymbolName(), _T(""), true, true, true);

        // if found, return it
        if (pSet && pSet->GetSize() > 0 && pSet->GetAt(0))
            return pSet->GetAt(0);
    }

    return NULL;
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_LinkSymbol::GetReferenceSymbols()
{
    if (!IsLocal())
        return NULL;

    ZDProcessGraphModelMdl* pRootModel = dynamic_cast<ZDProcessGraphModelMdl*>(GetRootModel());

    if (pRootModel)
    {
        CODComponentSet*  pSet = pRootModel->FindSymbol(GetSymbolName(), _T(""), true, true, false);

        // remove from the set
        if (pSet)
        {
            const int setCount = pSet->GetSize();

            for (int i = 0; i < setCount; ++i)
                if (pSet->GetAt(i) == this)
                {
                    pSet->RemoveAt(i);
                    --i;
                }
        }

        return pSet;
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::AssignReferenceSymbol(CODSymbolComponent* pReference)
{
    // remove previous reference before assigning the new one
    RemoveReferenceSymbol();

    m_pReference             = pReference;
    PSS_LinkSymbol* pRefLink = dynamic_cast<PSS_LinkSymbol*>(m_pReference);

    if (pRefLink)
    {
        // set the same name
        SetSymbolName(pRefLink->GetSymbolName());

        // set as reference
        SetIsLocal(false);

        // attach this to the source reference
        pRefLink->AttachObserver(this);
    }
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::RemoveReferenceSymbol()
{
    if (!m_pReference)
        return;

    PSS_LinkSymbol* pRefLink = dynamic_cast<PSS_LinkSymbol*>(m_pReference);

    if (pRefLink)
        pRefLink->DetachObserver(this);

    m_pReference = NULL;
}
//---------------------------------------------------------------------------
CODModel* PSS_LinkSymbol::GetOwnerModel()
{
    // is the parent a model?
    CODComponent* pComp = GetParent();

    while (pComp)
    {
        ZDProcessGraphModelMdl* pModel = dynamic_cast<ZDProcessGraphModelMdl*>(pComp);

        // if a model, return it
        if (pModel)
            return pModel;

        // otherwise retreive its parent
        pComp = pComp->GetParent();
    }

    return NULL;
}
//---------------------------------------------------------------------------
CODModel* PSS_LinkSymbol::GetRootModel()
{
    ZDProcessGraphModelMdl* pModel = dynamic_cast<ZDProcessGraphModelMdl*>(GetOwnerModel());

    // if the model is a graph model, it contains the root, so get and return it
    if (pModel)
        return pModel->GetRoot();

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetModifiedFlag(BOOL value)
{
    CODModel* pModel = GetRootModel();

    if (pModel)
        pModel->SetModifiedFlag(value);
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::RedrawSymbol()
{
    // if the parent is a model
    ZDProcessGraphModelMdl* pModel = dynamic_cast<ZDProcessGraphModelMdl*>(GetParent());

    if (pModel)
        pModel->ReDrawComponent(*this);

    AdjustLinePath();
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::AdjustLinePath()
{
    // get the actual path vertices count
    const int pointsCount = GetPointCount();

    // the snail effect happens only on paths which contain 5 vertices
    if (pointsCount != 5)
        return;

    CODComponent* pSrcComp  = GetSourceComponent();
    CODComponent* pDestComp = GetTargetComponent();

    // needs the both
    if (pSrcComp && pDestComp)
    {
        // get the source container
        std::unique_ptr<CODComponentPosition> pSrcPosContainer(pSrcComp->GetPosition());

        if (!pSrcPosContainer.get())
            return;

        // get the source container bounding rectangle
        const CRect srcBounds = pSrcPosContainer->GetBounds();

        // get the destination container
        std::unique_ptr<CODComponentPosition> pDestPosContainer(pDestComp->GetPosition());

        if (!pDestPosContainer->GetBounds())
            return;

        // get the destination container bounding rectangle
        const CRect destBounds = pDestPosContainer->GetBounds();

        CPoint vertices[5];

        // get the actual vertices composing the path
        for (int i = 0; i < pointsCount; ++i)
            vertices[i] = GetVertex(i);

        // calculate the source anchor center point
        const PSS_Vector2D srcCenter(float(srcBounds.left) + ((float(srcBounds.right)  - float(srcBounds.left)) / 2.0f),
                                     float(srcBounds.top)  + ((float(srcBounds.bottom) - float(srcBounds.top))  / 2.0f));

        // get the source component vertices
        const PSS_Vector2D srcVertices[] =
        {
            PSS_Vector2D(float(srcBounds.left),  float(srcBounds.top)),
            PSS_Vector2D(float(srcBounds.left),  float(srcBounds.bottom)),
            PSS_Vector2D(float(srcBounds.right), float(srcBounds.bottom)),
            PSS_Vector2D(float(srcBounds.right), float(srcBounds.top))
        };

        // calculate 4 polygons around the source component center
        const PSS_Triangle srcTriangles[] =
        {
            PSS_Triangle(srcVertices[0], srcVertices[1], srcCenter),
            PSS_Triangle(srcVertices[1], srcVertices[2], srcCenter),
            PSS_Triangle(srcVertices[2], srcVertices[3], srcCenter),
            PSS_Triangle(srcVertices[3], srcVertices[0], srcCenter)
        };

        // get the source test point
        const PSS_Vector2D srcTestPos(float(vertices[0].x), float(vertices[0].y));
        int                srcEdge = 0;

        // find on which component edge the source anchor is
        for (int i = 0; i < 4; ++i)
            if (PSS_MathHelper::Inside(srcTriangles[i], srcTestPos))
            {
                srcEdge = i + 1;
                break;
            }

        // search the source closest point
        switch (srcEdge)
        {
            case 1:
                vertices[1].x = vertices[0].x - 20;
                vertices[1].y = vertices[0].y;
                break;

            case 2:
                vertices[1].x = vertices[0].x;
                vertices[1].y = vertices[0].y + 20;
                break;

            case 3:
                vertices[1].x = vertices[0].x + 20;
                vertices[1].y = vertices[0].y;
                break;

            case 4:
                vertices[1].x = vertices[0].x;
                vertices[1].y = vertices[0].y - 20;
                break;

            default:
                return;
        }

        // calculate the destination anchor center point
        const PSS_Vector2D dstCenter(float(destBounds.left) + ((float(destBounds.right)  - float(destBounds.left)) / 2.0f),
                                     float(destBounds.top)  + ((float(destBounds.bottom) - float(destBounds.top))  / 2.0f));

        // get the destination component vertices
        const PSS_Vector2D dstVertices[] =
        {
            PSS_Vector2D(float(destBounds.left),  float(destBounds.top)),
            PSS_Vector2D(float(destBounds.left),  float(destBounds.bottom)),
            PSS_Vector2D(float(destBounds.right), float(destBounds.bottom)),
            PSS_Vector2D(float(destBounds.right), float(destBounds.top))
        };

        // calculate 4 polygons around the destination component center
        const PSS_Triangle dstTriangles[] =
        {
            PSS_Triangle(dstVertices[0], dstVertices[1], dstCenter),
            PSS_Triangle(dstVertices[1], dstVertices[2], dstCenter),
            PSS_Triangle(dstVertices[2], dstVertices[3], dstCenter),
            PSS_Triangle(dstVertices[3], dstVertices[0], dstCenter)
        };

        // get the destination test point
        const PSS_Vector2D dstTestPos(float(vertices[4].x), float(vertices[4].y));
        int                dstEdge = 0;

        // find on which component edge the destination anchor is
        for (int i = 0; i < 4; ++i)
            if (PSS_MathHelper::Inside(dstTriangles[i], dstTestPos))
            {
                dstEdge = i + 1;
                break;
            }

        // search the destination closest point
        switch (dstEdge)
        {
            case 1:
                vertices[3].x = vertices[4].x - 20;
                vertices[3].y = vertices[4].y;
                break;

            case 2:
                vertices[3].x = vertices[4].x;
                vertices[3].y = vertices[4].y + 20;
                break;

            case 3:
                vertices[3].x = vertices[4].x + 20;
                vertices[3].y = vertices[4].y;
                break;

            case 4:
                vertices[3].x = vertices[4].x;
                vertices[3].y = vertices[4].y - 20;
                break;

            default:
                return;
        }

        // handle special cases
        if (srcEdge == 2 || srcEdge == 4)
        {
            vertices[2].x = vertices[3].x;
            vertices[2].y = vertices[1].y;
        }
        else
        {
            vertices[2].x = vertices[1].x;
            vertices[2].y = vertices[3].y;
        }

        // write the new path vertices
        for (int i = 0; i < pointsCount; ++i)
            SetVertex(i, vertices[i]);

        // update the label position
        UpdateRgn(TRUE);
    }
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::FillProperties(ZBPropertySet& propSet, bool numericValue, bool groupValue)
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
        return false;

    CString name;

    if (numericValue)
    {
        name = pBasicProps->GetSymbolName();
        name.Remove('\n');
        name.Replace('\r', ' ');
    }

    std::unique_ptr<ZBProperty> pProp;

    // the name property in the general group
    pProp.reset(new ZBProperty(IDS_ZS_BP_PROP_BASIC_TITLE,
                               ZS_BP_PROP_BASIC,
                               IDS_Z_SYMBOL_NAME_NAME,
                               Z_SYMBOL_NAME,
                               IDS_Z_SYMBOL_NAME_DESC,
                               (numericValue ? name : pBasicProps->GetSymbolName()),
                               (!IsLocal() || SymbolNameTextEditReadOnly() ?
                                       ZBProperty::PT_EDIT_MULTILINE_READONLY : ZBProperty::PT_EDIT_MULTILINE)));
    propSet.Add(pProp.get());
    pProp.release();

    // the description property in the general group
    pProp.reset(new ZBProperty(IDS_ZS_BP_PROP_BASIC_TITLE,
                               ZS_BP_PROP_BASIC,
                               IDS_Z_SYMBOL_DESCRIPTION_NAME,
                               Z_SYMBOL_DESCRIPTION,
                               IDS_Z_SYMBOL_DESCRIPTION_DESC,
                               pBasicProps->GetSymbolDescription(),
                               (!IsLocal() || CommentTextEditReadOnly() ?
                                       ZBProperty::PT_EDIT_MULTILINE_READONLY : ZBProperty::PT_EDIT_MULTILINE)));
    propSet.Add(pProp.get());
    pProp.release();

    // the reference property in the general group
    if (numericValue)
        pProp.reset(new ZBProperty(IDS_ZS_BP_PROP_BASIC_TITLE,
                                   ZS_BP_PROP_BASIC,
                                   IDS_Z_SYMBOL_NUMBER_NAME,
                                   Z_SYMBOL_NUMBER,
                                   IDS_Z_SYMBOL_NUMBER_DESC,
                                   double(pBasicProps->GetSymbolNumber()),
                                   (IsLocal() ? ZBProperty::PT_EDIT_NUMBER : ZBProperty::PT_EDIT_NUMBER_READONLY)));
    else
        pProp.reset(new ZBProperty(IDS_ZS_BP_PROP_BASIC_TITLE,
                                   ZS_BP_PROP_BASIC,
                                   IDS_Z_SYMBOL_NUMBER_NAME,
                                   Z_SYMBOL_NUMBER,
                                   IDS_Z_SYMBOL_NUMBER_DESC,
                                   pBasicProps->GetSymbolNumberStr(),
                                   (IsLocal() ? ZBProperty::PT_EDIT_STRING : ZBProperty::PT_EDIT_STRING_READONLY)));

    propSet.Add(pProp.get());
    pProp.release();

    // the Risk level in the general group
    pProp.reset(new ZBProperty(IDS_ZS_BP_PROP_BASIC_TITLE,
                               ZS_BP_PROP_BASIC,
                               IDS_Z_SYMBOL_RISK_LEVEL_NAME,
                               Z_SYMBOL_RISK_LEVEL,
                               IDS_Z_SYMBOL_RISK_LEVEL_DESC,
                               pBasicProps->GetSymbolRiskLevel(),
                               ZBProperty::PT_EDIT_STRING_READONLY));
    propSet.Add(pProp.get());
    pProp.release();

    // the external link properties in the external links are added by the ZBExtAppPropertyMgr class
    if (IsLocal() && AcceptExtApp())
        if (!ZBExtAppPropertyMgr::FillProperties(propSet, numericValue, groupValue))
            return false;

    // the external file properties are added by the ZBExtFilePropertyMgr class
    if (IsLocal() && AcceptExtFile())
    {
        if (!ZBExtFilePropertyMgr::FillProperties(propSet, numericValue, groupValue))
            return false;

        // segregation conceptor
        ZDProcessGraphModelMdl* pModel = dynamic_cast<ZDProcessGraphModelMdl*>(GetRootModel());

        // is messenger activated?
        if (pModel && pModel->GetUseWorkflow())
            if (!ZBExtFilePropertyMgr::FillPropertiesMessenger(propSet, numericValue, groupValue))
                return false;
    }

    // dynamic properties
    if (m_DynamicPropManager)
        if (!m_DynamicPropManager->FillProperties(propSet, numericValue, groupValue))
            return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::SaveProperties(ZBPropertySet& propSet)
{
    if (!IsLocal())
        return true;

    // iterate through the data list and fill the property set
    ZBPropertyIterator it(&propSet);

    for (ZBProperty* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        // if no changes, continue
        if (!pProp->GetHasChanged())
            continue;

        if (pProp->GetCategoryID() == ZS_BP_PROP_BASIC)
            switch (pProp->GetItemID())
            {
                case Z_SYMBOL_NAME:        SetSymbolName(pProp->GetValueString());               break;
                case Z_SYMBOL_DESCRIPTION: SetSymbolComment(pProp->GetValueString());            break;
                case Z_SYMBOL_NUMBER:      SetSymbolReferenceNumberStr(pProp->GetValueString()); break;
            }
    }

    if (!ZBExtAppPropertyMgr::SaveProperties(propSet) || !ZBExtFilePropertyMgr::SaveProperties(propSet))
        return false;

    if (m_DynamicPropManager)
        if (!m_DynamicPropManager->SaveProperties(propSet))
            return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::FillProperty(ZBProperty& prop)
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
        return false;

    if (prop.GetCategoryID() == ZS_BP_PROP_BASIC)
        switch (prop.GetItemID())
        {
            case Z_SYMBOL_NAME:        prop.SetValueString(pBasicProps->GetSymbolName());        break;
            case Z_SYMBOL_DESCRIPTION: prop.SetValueString(pBasicProps->GetSymbolDescription()); break;
            case Z_SYMBOL_NUMBER:      prop.SetValueString(pBasicProps->GetSymbolNumberStr());   break;
        }

    if (!ZBExtAppPropertyMgr::FillProperty(prop) || !ZBExtFilePropertyMgr::FillProperty(prop))
        return false;

    if (m_DynamicPropManager)
        if (!m_DynamicPropManager->FillProperty(prop))
            return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::SaveProperty(ZBProperty& prop)
{
    if (!IsLocal())
        return true;

    if (prop.GetCategoryID() == ZS_BP_PROP_BASIC)
    {
        switch (prop.GetItemID())
        {
            case Z_SYMBOL_NAME:        SetSymbolName(prop.GetValueString());               break;
            case Z_SYMBOL_DESCRIPTION: SetSymbolComment(prop.GetValueString());            break;
            case Z_SYMBOL_NUMBER:      SetSymbolReferenceNumberStr(prop.GetValueString()); break;
        }

        // set the modified flag to true
        SetModifiedFlag();
    }

    if (!ZBExtAppPropertyMgr::SaveProperty(prop) || !ZBExtFilePropertyMgr::SaveProperty(prop))
        return false;

    if (m_DynamicPropManager)
        if (!m_DynamicPropManager->SaveProperty(prop))
            return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::CheckPropertyValue(ZBProperty& prop, CString& value, ZBPropertySet& props)
{
    // do check the reference number?
    if (prop.GetCategoryID() == ZS_BP_PROP_BASIC)
        if (prop.GetItemID() == Z_SYMBOL_NUMBER)
        {
            ZDProcessGraphModelMdl* pModel = dynamic_cast<ZDProcessGraphModelMdl*>(GetParent());

            // if not the same and already exists, show an error message and restore the initial value
            if (pModel)
                if (value != GetSymbolReferenceNumberStr() && pModel->GetRoot()->ReferenceNumberAlreadyAllocated(value))
                {
                    PSS_MsgBox mBox;
                    mBox.Show(IDS_REFERENCENUMBER_ALREADYEXIST, MB_OK);
                    value = GetSymbolReferenceNumberStr();
                    return false;
                }
        }
        else
        if (prop.GetItemID() == Z_SYMBOL_NAME)
            if (!IsNewNameValid(value))
            {
                value = GetSymbolName();
                return false;
            }

    if (!ZBExtAppPropertyMgr::CheckPropertyValue(prop, value, props) ||
        !ZBExtFilePropertyMgr::CheckPropertyValue(prop, value, props))
        return false;

    if (m_DynamicPropManager)
        if (!m_DynamicPropManager->CheckPropertyValue(prop, value, props))
            return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::ProcessExtendedInput(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh)
{
    bool result = false;

    if (ZBExtAppPropertyMgr::ProcessExtendedInput(prop, value, props, refresh))
        result = true;

    if (ZBExtFilePropertyMgr::ProcessExtendedInput(prop, value, props, refresh))
        result = true;

    if (m_DynamicPropManager)
        if (m_DynamicPropManager->ProcessExtendedInput(prop, value, props, refresh))
            result = true;

    return result;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::ProcessMenuCommand(int            menuCommand,
                                        ZBProperty&    prop,
                                        CString&       value,
                                        ZBPropertySet& props,
                                        bool&          refresh)
{
    bool result = false;

    // call the base template class method
    if (ZBExtAppPropertyMgr::ProcessMenuCommand(menuCommand, prop, value, props, refresh))
        result = true;

    if (ZBExtFilePropertyMgr::ProcessMenuCommand(menuCommand, prop, value, props, refresh))
        result = true;

    if (m_DynamicPropManager)
        if (m_DynamicPropManager->ProcessMenuCommand(menuCommand, prop, value, props, refresh))
            result = true;

    return result;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::CreateSymbolProperties()
{
    ZBBasicProperties basicProp;
    AddProperty(basicProp);

    ZBExtAppPropertyMgr::CreateSymbolProperties();
    ZBExtFilePropertyMgr::CreateSymbolProperties();

    // create the empty attributes if required
    if (AcceptDynamicAttributes())
        OnFillDefaultAttributes(&m_Attributes);

    if (m_DynamicPropManager)
    {
        delete m_DynamicPropManager;
        m_DynamicPropManager = NULL;
    }

    m_DynamicPropManager = new ZBDynamicProperties();

    if (m_DynamicPropManager)
        m_DynamicPropManager->CreateSymbolProperties();

    return true;
}
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_LinkSymbol::GetEnteringSymbol()
{
    IODNode* pINode = NULL;
    IODEdge* pIEdge = guid_cast<IODEdge*>(this);
    pIEdge->AddRef();

    if (pIEdge)
    {
        pINode = pIEdge->GetTailNode();

        CODComponent* m_pTailComp = GetTailComponent();

        if (m_pTailComp && pINode)
        {
            m_pTailComp->AddRef();

            if (m_pTailComp->Release() > 1)
                m_pTailComp->Release();
        }

        pIEdge->Release();
    }

    return static_cast<CODSymbolComponent*>(pINode);
}
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_LinkSymbol::GetFollowingSymbol()
{
    IODNode* pINode = NULL;
    IODEdge* pIEdge = guid_cast<IODEdge*>(this);
    pIEdge->AddRef();

    if (pIEdge)
    {
        pINode = pIEdge->GetHeadNode();

        CODComponent* m_pHeadComp = GetHeadComponent();

        if (m_pHeadComp && pINode)
        {
            m_pHeadComp->AddRef();

            if (m_pHeadComp->Release() > 1)
                m_pHeadComp->Release();
        }

        pIEdge->Release();
    }

    return static_cast<CODSymbolComponent*>(pINode);
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::UpdateGraphicFromRisk(COLORREF color, BOOL italic)
{
    ZUODSymbolManipulator::ChangeLabelTextColor(this, color);
    ZUODSymbolManipulator::SetLabelItalic(this, italic);

    // don't use the RedrawSymbol() function because it recalculates the entire link path,
    // and only a redraw is required here
    ZDProcessGraphModelMdl* pModel = dynamic_cast<ZDProcessGraphModelMdl*>(GetParent());

    if (pModel)
        pModel->ReDrawComponent(*this);
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetCurrentLineColor(COLORREF value)
{
    m_CurrentLineColor = value;
    ZUODSymbolManipulator::ChangeLineColor(this, value);
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetCurrentLineWidth(int value)
{
    m_CurrentLineWidth = value;
    ZUODSymbolManipulator::ChangeLineWidth(this, value);
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetCurrentLineStyle(int value)
{
    m_CurrentLineStyle = value;
    ZUODSymbolManipulator::ChangeLineStyle(this, value);
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetInitialLineStyle(int value)
{
    m_InitialLineStyle = value;
    SetCurrentLineStyle(value);
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetCurrentLabelColor(COLORREF value)
{
    m_CurrentLabelLineColor = value;
    ZUODSymbolManipulator::ChangeLabelLineColor(this, value);
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetInitialLineColor(COLORREF value)
{
    m_InitialLineColor = value;
    SetCurrentLineColor(value);
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetInitialLineWidth(int value)
{
    m_InitialLineWidth = value;
    SetCurrentLineWidth(value);
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetInitialLabelLineColor(COLORREF value)
{
    m_InitialLabelLineColor = value;
    SetCurrentLabelColor(value);
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetInitialLabelLineWidth(int value)
{
    m_InitialLabelLineWidth = value;
    ZUODSymbolManipulator::ChangeLabelLineWidth(this, value);
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::Serialize(CArchive& ar)
{
    // serialize the link symbol
    CODLinkComponent::Serialize(ar);

    // only if the object is serialized from and to a document
    if (ar.m_pDocument)
        if (ar.IsStoring())
        {
            if (m_pReference)
                m_ReferenceName = dynamic_cast<PSS_LinkSymbol*>(m_pReference)->GetSymbolReferenceNumberStr();
            else
                m_ReferenceName.Empty();

            ar << WORD(m_IsLocal);
            ar << m_ObjectPath;
            ar << m_ReferenceName;

            ar << WORD(m_DisplayNameArea);
            ar << WORD(m_DisplayDescriptionArea);
            ar << WORD(m_DisplayAttributeArea);

            ar << m_CurrentLineColor;
            ar << m_CurrentLabelLineColor;
            ar << m_InitialLineColor;
            ar << m_InitialLineWidth;
            ar << m_InitialLabelLineColor;
            ar << m_InitialLabelLineWidth;

            // serialize the attributes
            ar << m_Attributes;

            // serialize the dynamic properties
            ar << m_DynamicPropManager;
        }
        else
        {
            WORD wValue;
            ar >> wValue;
            m_IsLocal = bool(wValue);

            ar >> m_ObjectPath;

            // used to rebuild the reference
            ar >> m_ReferenceName;

            ar >> wValue;
            m_DisplayNameArea = bool(wValue);

            ar >> wValue;
            m_DisplayDescriptionArea = bool(wValue);

            ar >> wValue;
            m_DisplayAttributeArea = bool(wValue);

            PSS_BaseDocument* pBaseDoc = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

            if (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 19)
            {
                ar >> m_CurrentLineColor;
                ar >> m_CurrentLabelLineColor;
            }
            else
            {
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

            if (m_DynamicPropManager)
            {
                delete m_DynamicPropManager;
                m_DynamicPropManager = NULL;
            }

            // serialize the dynamic properties
            if (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 21)
                ar >> (CObject*&)m_DynamicPropManager;

            if (!m_DynamicPropManager)
                m_DynamicPropManager = new ZBDynamicProperties;

            CODEditProperties* pPropEdit = (CODEditProperties*)GetProperty(OD_PROP_EDIT);

            if (pPropEdit)
                pPropEdit->SetCanSelect(TRUE);
        }

    // serialize external applications and files
    ZBExtAppPropertyMgr::Serialize(ar);
    ZBExtFilePropertyMgr::Serialize(ar);

    // once loaded, call the base function to recalculate the embedded element positions
    AdjustElementPosition();
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::OnPostCreation(CODModel* pModel, CODController* pCtrl)
{
    if (!InitializeAttributeAreas())
        return false;

    // check the components size
    AdjustAreaPosition();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::OnPreDelete(CODModel* pModel, CODController* pCtrl)
{
    return true;
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    ZBSymbolObserverMsg* pObserverMsg = dynamic_cast<ZBSymbolObserverMsg*>(pMsg);

    if (pSubject && pSubject != this && pObserverMsg)
    {
        switch (pObserverMsg->GetActionType())
        {
            case ZBSymbolObserverMsg::ElementHasChanged:
            case ZBSymbolObserverMsg::NoAction:
                CopySymbolDefinitionFrom((PSS_LinkSymbol&)*pSubject);
                break;

            case ZBSymbolObserverMsg::NameHasChanged:
                SetSymbolName(dynamic_cast<PSS_LinkSymbol*>(pSubject)->GetSymbolName());
                break;

            case ZBSymbolObserverMsg::DescriptionHasChanged:
                SetSymbolComment(dynamic_cast<PSS_LinkSymbol*>(pSubject)->GetSymbolComment());
                break;
        }

        // adjust symbols element positions
        AdjustElementPosition();
    }
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::OnMove()
{
    CODLinkComponent::OnMove();

    // call the function to adjust the position of embedded elements
    AdjustElementPosition();
    AdjustAreaPosition();
    AdjustLinePath();
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::OnMouseMove(UINT flags, const CPoint& point, CODController& ctrl)
{
    return ZVSymbolAttributes::OnMouseMove(flags, point, ctrl);
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::OnLButtonDown(UINT flags, const CPoint& point, CODController& ctrl)
{
    return ZVSymbolAttributes::OnLButtonDown(flags, point, ctrl);
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::OnLButtonUp(UINT flags, const CPoint& point, CODController& ctrl)
{
    return ZVSymbolAttributes::OnLButtonUp(flags, point, ctrl);
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::OnLButtonDblClk(UINT flags, const CPoint& point, CODController& ctrl)
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::OnRButtonDown(UINT flags, const CPoint& point, CODController& ctrl)
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::OnRButtonUp(UINT flags, const CPoint& point, CODController& ctrl)
{
    return false;
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::OnPostDoubleClick(CODModel* pModel, CODController* pCtrl)
{}
//---------------------------------------------------------------------------
BOOL PSS_LinkSymbol::OnConnectionMove(CODConnection* pConnection)
{
    BOOL result = CODLinkComponent::OnConnectionMove(pConnection);

    AdjustLinePath();
    AdjustElementPosition();
    AdjustAreaPosition();
    AdjustLinePath();

    return result;
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::OnSymbolNameChange(const CString& oldName, const CString& newName)
{}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::OnFillDefaultAttributes(ZBPropertyAttributes* pAttributes)
{
    if (AcceptDynamicAttributes() && GetAttributeTextEdit())
    {
        GetAttributeTextEdit()->SetText(GetAttributeString(pAttributes));
        RedrawSymbol();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::OnChangeAttributes(ZBPropertyAttributes* pAttributes)
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
bool PSS_LinkSymbol::OnPrePropertyChanged(const CString& newValue, ZBProperty& prop, ZBPropertySet& props)
{
    bool result = true;

    // call the base template class method
    if (!ZBExtAppPropertyMgr::OnPrePropertyChanged(newValue, prop, props))
        result = false;

    if (!ZBExtFilePropertyMgr::OnPrePropertyChanged(newValue, prop, props))
        result = false;

    if (m_DynamicPropManager)
        if (!m_DynamicPropManager->OnPrePropertyChanged(newValue, prop, props))
            result = false;

    return result;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::OnPostPropertyChanged(ZBProperty& prop, ZBPropertySet& props, bool& refresh)
{
    bool result = false;

    // call the base template class method
    if (ZBExtAppPropertyMgr::OnPostPropertyChanged(prop, props, refresh))
        result = true;

    if (ZBExtFilePropertyMgr::OnPostPropertyChanged(prop, props, refresh))
        result = true;

    if (m_DynamicPropManager)
        if (m_DynamicPropManager->OnPostPropertyChanged(prop, props, refresh))
            result = true;

    return result;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::OnDropInternalPropertyItem(ZBProperty&    srcProperty,
                                                ZBProperty&    dstProperty,
                                                bool           top2Down,
                                                ZBPropertySet& props)
{
    if (m_DynamicPropManager)
        if (!m_DynamicPropManager->OnDropInternalPropertyItem(srcProperty, dstProperty, top2Down, props))
            return false;

    return true;
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::OnSymbolNameChanged(CODComponent& Comp, const CString& oldName)
{}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::OnPageNameChanged(ZDProcessGraphPage* pPage, const CString& oldName)
{}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::OnUserEntityChanged(ZBUserEntity* pUserEntity, const CString& oldName)
{}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    return false;
}
//---------------------------------------------------------------------------
CODLabelComponent* PSS_LinkSymbol::CreateSymbolLabel()
{
    return CreateLabel(_T("Test"));
}
//---------------------------------------------------------------------------