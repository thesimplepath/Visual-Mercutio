// **********************************************************************************************************
// *                      ZBLinkSymbol.cpp: implementation of the ZBLinkSymbol class.                        *
// **********************************************************************************************************

#include "stdafx.h"
#include "ZBLinkSymbol.h"

// JMR-MODIF - Le 26 septembre 2005 - Nettoyage des memory leaks, ajout de l'en-tête ZBSymbol.h
#include "ZBSymbol.h"

#include "ZUODSymbolManipulator.h"

#include "ZBBasicProp.h"

#include "zProperty\ZBDynamicProperties.h"

#include "ProcGraphModelMdl.h"
#include "zBaseLib\PSS_BaseDocument.h"

#include "ZBSymbolObserverMsg.h"
#include "ZBDocObserverMsg.h"

#include "zBaseLib\PSS_DrawFunctions.h"

// Resource include
#include "zModelRes.h"
#include "PSS_ResIDs.h"

#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 septembre 2005 - Ajout de la décoration unicode _T( ), nettoyage du code inutilisé.

PSS_Bitmap ZBLinkSymbol::m_ShortCutBitmap;

// **********************************************************************************************************
// * Dom November 2002                                                                                        *
// * Due to a bug the can select flag had been set to false                                                    *
// * when migrating the ObjectiveViews version 8.1                                                            *
// **********************************************************************************************************
#define _CANSELECTCONVERTER 1

IMPLEMENT_SERIAL(ZBLinkSymbol, CODLinkComponent, g_DefVersion)

// **********************************************************************************************************
// *              Construction, destruction, opérateurs et fonctions de manipulation de l'objet                *
// **********************************************************************************************************

// Constructeur par défaut de la classe ZBLinklSymbol.
ZBLinkSymbol::ZBLinkSymbol() : m_IsLocal(true),
m_pReference(NULL),
m_DynamicPropManager(NULL),
m_InitialLineWidth(1),
m_InitialLineColor(defCOLOR_BLACK),
m_CurrentLineColor(defCOLOR_BLACK),
m_InitialLineStyle(PS_SOLID),
m_CurrentLineStyle(PS_SOLID),
m_CurrentLineWidth(1),
m_InitialLabelLineWidth(1),
m_InitialLabelLineColor(defCOLOR_BLACK),
m_CurrentLabelLineColor(defCOLOR_BLACK),
m_IsInCreationProcess(false),
// JMR-MODIF - Le 7 février 2006 - Initialisation du flag m_IsCopy.
m_IsCopy(FALSE)
{
    SetSymbol(this);

    CreateSymbolProperties();
}

// Constructeur par copie de la classe ZBLinkSymbol.
ZBLinkSymbol::ZBLinkSymbol(const ZBLinkSymbol& src)
{
    *this = src;
}

// Destructeur de la classe ZBLinkSymbol.
ZBLinkSymbol::~ZBLinkSymbol()
{
    if (m_DynamicPropManager)
    {
        delete m_DynamicPropManager;
        m_DynamicPropManager = NULL;
    }
}

// Fonction de surcharge de l'opérateur =
ZBLinkSymbol& ZBLinkSymbol::operator=(const ZBLinkSymbol& src)
{
    // Call the base class assignement operator
    CODLinkComponent::operator=        ((const CODLinkComponent&)src);
    ZBExtAppPropertyMgr::operator=    ((const ZBExtAppPropertyMgr&)src);
    ZBExtFilePropertyMgr::operator=    ((const ZBExtFilePropertyMgr&)src);
    ZVSymbolAttributes::operator=    ((const ZVSymbolAttributes&)src);

    m_IsLocal = src.m_IsLocal;
    m_NameOfReference = src.m_NameOfReference;
    m_ObjectPath = src.m_ObjectPath;
    m_DynamicPropManager = src.m_DynamicPropManager->Dup();

    return *this;
}

// Cette fonction permet d'obtenir une copie de l'objet.
CODComponent* ZBLinkSymbol::Dup() const
{
    return (new ZBLinkSymbol(*this));
}

bool ZBLinkSymbol::Match(const CString            What,
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

// **********************************************************************************************************
// *                                   Fonctions de création et de nettoyage                                *
// **********************************************************************************************************

BOOL ZBLinkSymbol::Create(int nStyle, int nPointSize, COLORREF crColor, int bTransparent)
{
    BOOL RetValue = CODLinkComponent::Create();

    if (RetValue)
    {
        AssignDefaultProperties();
        SetLineProperty(nStyle, nPointSize, crColor, bTransparent);
    }

    return RetValue;
}

BOOL ZBLinkSymbol::CreateOrthogonal(int nStyle, int nPointSize, COLORREF crColor, int bTransparent)
{
    BOOL RetValue = CODLinkComponent::CreateOrthogonal();

    if (RetValue)
    {
        AssignDefaultProperties();
        SetLineProperty(nStyle, nPointSize, crColor, bTransparent);
    }

    return RetValue;
}

ZBSymbolEdit* ZBLinkSymbol::CreateEditText(const CString& AreaName, const CString& EditName, CODComponent* pParent)
{
    return ZUODSymbolManipulator::CreateEditText(this, AreaName, EditName, pParent);
}

ZBSymbolEdit* ZBLinkSymbol::CreateAndReplaceEditText(const CString& EditName, CODComponent* pParent)
{
    return ZUODSymbolManipulator::CreateAndReplaceEditText(this, EditName, pParent);
}

// Create the symbol name label
CODLabelComponent* ZBLinkSymbol::CreateSymbolLabel()
{
    return CreateLabel(_T("Test"));
}

bool ZBLinkSymbol::CreateSymbolProperties()
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

    // JMR-MODIF - Le 21 septembre 2005 - Nettoyage des memory leaks, destruction de la variable m_DynamicPropManager
    // avant de tenter d'en assigner une nouvelle.
    if (m_DynamicPropManager)
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

void ZBLinkSymbol::CopySymbolDefinitionFrom(const CODSymbolComponent& src)
{
    if (ISA((&src), ZBLinkSymbol))
    {
        // Don't use direct assignement, if symbols are referenced, not notification will be done.
        SetSymbolName(reinterpret_cast<const ZBLinkSymbol&>(src).GetSymbolName());
        SetSymbolComment(reinterpret_cast<const ZBLinkSymbol&>(src).GetSymbolComment());
        SetAbsolutePath(reinterpret_cast<const ZBLinkSymbol&>(src).GetAbsolutePath());

        // Symbol is local
        m_IsLocal = true;

        // No reference
        m_pReference = NULL;
        m_NameOfReference.Empty();

        m_AllSymbolPosition = dynamic_cast<const ZBLinkSymbol&>(src).m_AllSymbolPosition;
        m_CurrentLineColor = dynamic_cast<const ZBLinkSymbol&>(src).m_CurrentLineColor;
        m_CurrentLabelLineColor = dynamic_cast<const ZBLinkSymbol&>(src).m_CurrentLabelLineColor;
        m_InitialLineColor = dynamic_cast<const ZBLinkSymbol&>(src).m_InitialLineColor;
        m_InitialLineWidth = dynamic_cast<const ZBLinkSymbol&>(src).m_InitialLineWidth;
        m_InitialLabelLineColor = dynamic_cast<const ZBLinkSymbol&>(src).m_InitialLabelLineColor;
        m_InitialLabelLineWidth = dynamic_cast<const ZBLinkSymbol&>(src).m_InitialLabelLineWidth;
        m_ShortCutBitmapPosition = dynamic_cast<const ZBLinkSymbol&>(src).m_ShortCutBitmapPosition;


        m_ExternalApplications = dynamic_cast<const ZBLinkSymbol&>(src).m_ExternalApplications;
        m_ExternalApplications.SetParent(this);

        m_ExternalFiles = dynamic_cast<const ZBLinkSymbol&>(src).m_ExternalFiles;
        m_ExternalFiles.SetParent(this);


        m_DisplayNameArea = dynamic_cast<const ZBLinkSymbol&>(src).m_DisplayNameArea;
        m_DisplayDescriptionArea = dynamic_cast<const ZBLinkSymbol&>(src).m_DisplayDescriptionArea;
        m_DisplayAttributeArea = dynamic_cast<const ZBLinkSymbol&>(src).m_DisplayAttributeArea;

        m_RelativeCoordinates = dynamic_cast<const ZBLinkSymbol&>(src).m_RelativeCoordinates;
        m_Attributes = dynamic_cast<const ZBLinkSymbol&>(src).m_Attributes;

        // JMR-MODIF - Le 6 février 2006 - Nettoyage des memory leaks, destruction de la variable
        // m_DynamicPropManager avant de tenter d'en assigner une nouvelle.
        if (m_DynamicPropManager)
        {
            delete m_DynamicPropManager;
            m_DynamicPropManager = NULL;
        }

        m_DynamicPropManager = dynamic_cast<const ZBLinkSymbol&>(src).m_DynamicPropManager->Dup();

        // Now sets the right area name
        ZUODSymbolManipulator::MatchSymbolAreaName(this, const_cast<CODSymbolComponent*>(&src));
    }
}

// When we attach a reference to a symbol,
// we need to attach the object to the subject
void ZBLinkSymbol::AssignReferenceSymbol(CODSymbolComponent* pReference)
{
    // todo -cCheck -oJean: on 26.09.2019, check if this modification is valid, revert it otherwise
    // remove previous reference before assigning the new one
    RemoveReferenceSymbol();

    m_pReference = pReference;

    if (m_pReference && ISA(m_pReference, ZBLinkSymbol))
    {
        // Sets the same name
        SetSymbolName(dynamic_cast<ZBLinkSymbol*>(m_pReference)->GetSymbolName());

        // Sets as reference
        SetIsLocal(false);

        // And attach this to the source reference
        dynamic_cast<ZBLinkSymbol*>(m_pReference)->AttachObserver(this);
    }
    // todo -cCheck -oJean: on 26.09.2019, check if this modification is valid, revert it otherwise
    //REM else RemoveReferenceSymbol();
}

void ZBLinkSymbol::ApplyFormatFromObject(CODSymbolComponent&    Object,
                                         bool                    Font    /*= true*/,
                                         bool                    Fill    /*= true*/,
                                         bool                    Line    /*= true*/)
{
    ZUODSymbolManipulator::ApplyFormatFromObject(this, Object, Font, Fill, Line);
}

// When we deattach a reference to a symbol, we need to deattach the object to the subject
void ZBLinkSymbol::RemoveReferenceSymbol()
{
    if (m_pReference)
    {
        reinterpret_cast<ZBLinkSymbol*>(m_pReference)->DetachObserver(this);
    }

    m_pReference = NULL;
}

// **********************************************************************************************************
// *                           Fonctions permettant la récupération de valeurs                                *
// **********************************************************************************************************

bool ZBLinkSymbol::OnFillDefaultAttributes(ZBPropertyAttributes* pAttributes)
{
    if (AcceptDynamicAttributes() && GetAttributeTextEdit())
    {
        GetAttributeTextEdit()->SetText(GetAttributeString(pAttributes));
        RedrawSymbol();
    }

    return true;
}

bool ZBLinkSymbol::OnChangeAttributes(ZBPropertyAttributes* pAttributes)
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

bool ZBLinkSymbol::OnPrePropertyChanged(CString NewValue, ZBProperty& Property, ZBPropertySet& Properties)
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

bool ZBLinkSymbol::OnPostPropertyChanged(ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh)
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

bool ZBLinkSymbol::OnDropInternalPropertyItem(ZBProperty&        SrcProperty,
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

// Cette fonction est appelée lorsque les symboles auxquelles ce symbole est ancré sont déplaçés.
BOOL ZBLinkSymbol::OnConnectionMove(CODConnection* pConnection)
{
    BOOL RetValue = CODLinkComponent::OnConnectionMove(pConnection);

    // JMR-MODIF - Le 18 janvier 2006 - Ajout de l'appel à la fonction AdjustLinePath.
    AdjustLinePath();

    // Call the function to adjust the position of embedded elements
    AdjustElementPosition();

    AdjustAreaPosition();

    // JMR-MODIF - Le 3 février 2006 - Ajout de l'appel pour éviter l'effet escargot.
    AdjustLinePath();

    return RetValue;
}

// Cette fonction est appelée lorsque l'utilisateur tente de déplaçer le symbole. (Cette fonction n'est pas
// appelée si l'utilisateur déplaçe les symboles auxquelles ce symbole est lié, ce qui provoque aussi un
// réajustement de sa position)
void ZBLinkSymbol::OnMove()
{
    CODLinkComponent::OnMove();

    // Call the function to adjust the position of embedded elements
    AdjustElementPosition();

    AdjustAreaPosition();

    // JMR-MODIF - Le 3 février 2006 - Ajout de l'appel pour éviter l'effet escargot.
    AdjustLinePath();
}

void ZBLinkSymbol::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    if (pSubject && pSubject != this && pMsg && ISA(pMsg, ZBSymbolObserverMsg))
    {
        switch (dynamic_cast<ZBSymbolObserverMsg*>(pMsg)->GetActionType())
        {
            case ZBSymbolObserverMsg::ElementHasChanged:
            case ZBSymbolObserverMsg::NoAction:
            {
                CopySymbolDefinitionFrom((ZBLinkSymbol&)*pSubject);
                break;
            }

            case ZBSymbolObserverMsg::NameHasChanged:
            {
                SetSymbolName(dynamic_cast<ZBLinkSymbol*>(pSubject)->GetSymbolName());
                break;
            }

            case ZBSymbolObserverMsg::DescriptionHasChanged:
            {
                SetSymbolComment(dynamic_cast<ZBLinkSymbol*>(pSubject)->GetSymbolComment());
                break;
            }
        }

        // Adjust element position for symbols
        AdjustElementPosition();
    }
}

// **********************************************************************************************************
// *                                 Fonctions de la classe ZBLinkSymbol                                    *
// **********************************************************************************************************

// **************************************** Fonctions graphiques ********************************************

// Cette fonction est appelée lorsque le symbole doit être (re)dessiné.
void ZBLinkSymbol::RedrawSymbol()
{
    // If the parent is a model
    CODComponent* pComp = GetParent();

    if (pComp && ISA(pComp, ZDProcessGraphModelMdl))
    {
        dynamic_cast<ZDProcessGraphModelMdl*>(pComp)->ReDrawComponent(*this);
    }

    // JMR-MODIF - Le 19 janvier 2006 - Ajout de l'appel vers AdjustLinePath.
    AdjustLinePath();
}

void ZBLinkSymbol::RefreshAttributeTextArea(bool Redraw /*= false*/)
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

// JMR-MODIF - Le 22 juillet 2007 - Mets à jour les données graphiques d'un symbole en fonction des risques.
void ZBLinkSymbol::UpdateGraphicFromRisk(COLORREF Color, BOOL Italic)
{
    ZUODSymbolManipulator::ChangeLabelTextColor(this, Color);
    ZUODSymbolManipulator::SetLabelItalic(this, Italic);

    // N'utilise pas la fonction RedrawSymbol, car celle-ci fait appel à un algorythme de
    // recalcuation du chemin des lvrables. Ici, on veut juste redessiner le symbole.
    CODComponent* pComp = GetParent();

    if (pComp && ISA(pComp, ZDProcessGraphModelMdl))
    {
        dynamic_cast<ZDProcessGraphModelMdl*>(pComp)->ReDrawComponent(*this);
    }
}

// Cette fonction permet de marquer le trait en rouge, en cas d'erreur.
void ZBLinkSymbol::ShowInError(bool value /*= true*/)
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

// JMR-MODIF - Le 18 janvier 2006 - Cette fonction contrôle et au besoin ajuste le chemin d'affichage d'un livrable.
void ZBLinkSymbol::AdjustLinePath()
{
    // Obtient le nombre de sommets que contient le chemin actuel.
    int myPointsCount = GetPointCount();

    // L'effet escargot n'a lieu que sur les chemins à 5 sommets.
    if (myPointsCount == 5)
    {
        Maths    myMathsAlgorythms;
        CPoint    myVertex[5];
        int        i = 0;

        CODComponent* SrcComp = GetSourceComponent();
        CODComponent* DestComp = GetTargetComponent();

        if (SrcComp != NULL && DestComp != NULL)
        {
            // Obtient les valeurs nécessaire aux calculs depuis les objets source et destination.
            CODComponentPosition* mySrcPosContainer = NULL;
            CODComponentPosition* myDestPosContainer = NULL;
            CRect                  mySrcBounds;
            CRect                  myDestBounds;

            // Obtient la valeur du rectangle de position de l'objet source.
            mySrcPosContainer = SrcComp->GetPosition();

            if (mySrcPosContainer != NULL)
            {
                mySrcBounds = mySrcPosContainer->GetBounds();
                delete mySrcPosContainer;
            }
            else return;

            // Obtient la valeur du rectangle de position de l'objet destination.
            myDestPosContainer = DestComp->GetPosition();

            if (myDestPosContainer != NULL)
            {
                myDestBounds = myDestPosContainer->GetBounds();
                delete myDestPosContainer;
            }
            else return;

            // Obtient la liste des sommets composant actuellement le chemin.
            for (i = 0; i < myPointsCount; i++)
            {
                myVertex[i] = GetVertex(i);
            }

            // Teste sur quel côté du rectangle source se trouve le point d'ancrage.
            int            mySrcEdge = 0;
            Vector2D*    mySrcTestPos = new Vector2D((float)myVertex[0].x, (float)myVertex[0].y);

            Vector2D mySrcVertice1;
            Vector2D mySrcVertice2;
            Vector2D mySrcVertice3;
            Vector2D mySrcVertice4;
            Vector2D mySrcCenter;

            mySrcVertice1.setX((float)mySrcBounds.left);
            mySrcVertice1.setY((float)mySrcBounds.top);
            mySrcVertice2.setX((float)mySrcBounds.left);
            mySrcVertice2.setY((float)mySrcBounds.bottom);
            mySrcVertice3.setX((float)mySrcBounds.right);
            mySrcVertice3.setY((float)mySrcBounds.bottom);
            mySrcVertice4.setX((float)mySrcBounds.right);
            mySrcVertice4.setY((float)mySrcBounds.top);
            mySrcCenter.setX((float)mySrcBounds.left + (((float)mySrcBounds.right - (float)mySrcBounds.left) / 2));
            mySrcCenter.setY((float)mySrcBounds.top + (((float)mySrcBounds.bottom - (float)mySrcBounds.top) / 2));

            Triangle* mySrcTri1 = new Triangle(mySrcVertice1, mySrcVertice2, mySrcCenter);
            Triangle* mySrcTri2 = new Triangle(mySrcVertice2, mySrcVertice3, mySrcCenter);
            Triangle* mySrcTri3 = new Triangle(mySrcVertice3, mySrcVertice4, mySrcCenter);
            Triangle* mySrcTri4 = new Triangle(mySrcVertice4, mySrcVertice1, mySrcCenter);

            if (myMathsAlgorythms.IsTriPointCollision(mySrcTri1, mySrcTestPos) == TRUE) mySrcEdge = 1;
            else if (myMathsAlgorythms.IsTriPointCollision(mySrcTri2, mySrcTestPos) == TRUE) mySrcEdge = 2;
            else if (myMathsAlgorythms.IsTriPointCollision(mySrcTri3, mySrcTestPos) == TRUE) mySrcEdge = 3;
            else if (myMathsAlgorythms.IsTriPointCollision(mySrcTri4, mySrcTestPos) == TRUE) mySrcEdge = 4;

            delete mySrcTestPos;
            delete mySrcTri1;
            delete mySrcTri2;
            delete mySrcTri3;
            delete mySrcTri4;

            // Teste sur quel côté du rectangle destination se trouve le point d'ancrage.
            int            myDestEdge = 0;
            Vector2D*    myDestTestPos = new Vector2D((float)myVertex[4].x, (float)myVertex[4].y);

            Vector2D myDestVertice1;
            Vector2D myDestVertice2;
            Vector2D myDestVertice3;
            Vector2D myDestVertice4;
            Vector2D myDestCenter;

            myDestVertice1.setX((float)myDestBounds.left);
            myDestVertice1.setY((float)myDestBounds.top);
            myDestVertice2.setX((float)myDestBounds.left);
            myDestVertice2.setY((float)myDestBounds.bottom);
            myDestVertice3.setX((float)myDestBounds.right);
            myDestVertice3.setY((float)myDestBounds.bottom);
            myDestVertice4.setX((float)myDestBounds.right);
            myDestVertice4.setY((float)myDestBounds.top);
            myDestCenter.setX((float)myDestBounds.left + (((float)myDestBounds.right - (float)myDestBounds.left) / 2));
            myDestCenter.setY((float)myDestBounds.top + (((float)myDestBounds.bottom - (float)myDestBounds.top) / 2));

            Triangle* myDestTri1 = new Triangle(myDestVertice1, myDestVertice2, myDestCenter);
            Triangle* myDestTri2 = new Triangle(myDestVertice2, myDestVertice3, myDestCenter);
            Triangle* myDestTri3 = new Triangle(myDestVertice3, myDestVertice4, myDestCenter);
            Triangle* myDestTri4 = new Triangle(myDestVertice4, myDestVertice1, myDestCenter);

            if (myMathsAlgorythms.IsTriPointCollision(myDestTri1, myDestTestPos) == TRUE) myDestEdge = 1;
            else if (myMathsAlgorythms.IsTriPointCollision(myDestTri2, myDestTestPos) == TRUE) myDestEdge = 2;
            else if (myMathsAlgorythms.IsTriPointCollision(myDestTri3, myDestTestPos) == TRUE) myDestEdge = 3;
            else if (myMathsAlgorythms.IsTriPointCollision(myDestTri4, myDestTestPos) == TRUE) myDestEdge = 4;

            delete myDestTestPos;
            delete myDestTri1;
            delete myDestTri2;
            delete myDestTri3;
            delete myDestTri4;

            // Construit le point le plus proche de la source.
            switch (mySrcEdge)
            {
                case 1:
                {
                    myVertex[1].x = myVertex[0].x - 20;
                    myVertex[1].y = myVertex[0].y;
                    break;
                }

                case 2:
                {
                    myVertex[1].x = myVertex[0].x;
                    myVertex[1].y = myVertex[0].y + 20;
                    break;
                }

                case 3:
                {
                    myVertex[1].x = myVertex[0].x + 20;
                    myVertex[1].y = myVertex[0].y;
                    break;
                }

                case 4:
                {
                    myVertex[1].x = myVertex[0].x;
                    myVertex[1].y = myVertex[0].y - 20;
                    break;
                }

                // Cas inapproprié, stoppe tout en cas d'erreur.
                default:
                {
                    return;
                }
            }

            // Construit le point le plus proche de la destination.
            switch (myDestEdge)
            {
                case 1:
                {
                    myVertex[3].x = myVertex[4].x - 20;
                    myVertex[3].y = myVertex[4].y;
                    break;
                }

                case 2:
                {
                    myVertex[3].x = myVertex[4].x;
                    myVertex[3].y = myVertex[4].y + 20;
                    break;
                }

                case 3:
                {
                    myVertex[3].x = myVertex[4].x + 20;
                    myVertex[3].y = myVertex[4].y;
                    break;
                }

                case 4:
                {
                    myVertex[3].x = myVertex[4].x;
                    myVertex[3].y = myVertex[4].y - 20;
                    break;
                }

                // Cas inapproprié, stoppe tout en cas d'erreur.
                default:
                {
                    return;
                }
            }

            if (mySrcEdge == 2 || mySrcEdge == 4)
            {
                myVertex[2].x = myVertex[3].x;
                myVertex[2].y = myVertex[1].y;
            }
            else
            {
                myVertex[2].x = myVertex[1].x;
                myVertex[2].y = myVertex[3].y;
            }

            // Inscrit la nouvelle liste des sommets du chemin.
            for (i = 0; i < myPointsCount; i++)
            {
                SetVertex(i, myVertex[i]);
            }

            // Mets à jour la position du label.
            UpdateRgn(TRUE);
        }
    }
}

// **************************************** Fonctions de contrôle *******************************************

bool ZBLinkSymbol::CheckPropertyValue(ZBProperty& Property, CString& value, ZBPropertySet& Properties)
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
        {
            return false;
        }
    }

    return true;
}

bool ZBLinkSymbol::IsNewNameValid(const CString value) const
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
        if (value != const_cast<ZBLinkSymbol*>(this)->GetSymbolName() &&
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

// ********************************* Fonctions concernant les propriétés ************************************

// Start the edition of the symbol name
void ZBLinkSymbol::EditSymbolName()
{
    int                    NumLabels = GetNumLabels();
    CODLabelComponent*    pSymbolLabel = NULL;

    if (NumLabels == 0)
    {
        pSymbolLabel = CreateSymbolLabel();
    }
    else
    {
        CODLabelComponent*    pTempLabel;

        for (int i = 0; i < NumLabels; ++i)
        {
            pTempLabel = GetLabel(i);
        }
    }
}

// JMR-MODIF - Le 22 juillet 2007 - Cette fonction permet d'obtenir le niveau du risque du symbole.
CString ZBLinkSymbol::GetRiskLevel()
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    return pBasicProps->GetSymbolRiskLevel();
}

// JMR-MODIF - Le 22 juillet 2007 - Cette fonction permet de définir le niveau du risque du symbole.
void ZBLinkSymbol::SetRiskLevel(CString Level)
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    pBasicProps->SetSymbolRiskLevel(Level);
}

bool ZBLinkSymbol::FillProperties(ZBPropertySet&    PropSet,
                                  bool                NumericValue    /*= false*/,
                                  bool                GroupValue        /*= false*/)
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

    // JMR-MODIF - Le 29 juillet 2007 - Propriété "Niveau du risque" du groupe "General"
    ZBProperty* pRiskProp = new ZBProperty(IDS_ZS_BP_PROP_BASIC_TITLE,
                                           ZS_BP_PROP_BASIC,
                                           IDS_Z_SYMBOL_RISK_LEVEL_NAME,
                                           Z_SYMBOL_RISK_LEVEL,
                                           IDS_Z_SYMBOL_RISK_LEVEL_DESC,
                                           pBasicProps->GetSymbolRiskLevel(),
                                           ZBProperty::PT_EDIT_STRING_READONLY);
    PropSet.Add(pRiskProp);

    // Les propriétés du groupe "Lien externe" sont ajoutées par la classe ZBExtAppPropertyMgr.
    if (IsLocal() && AcceptExtApp())
    {
        if (!ZBExtAppPropertyMgr::FillProperties(PropSet, NumericValue, GroupValue))
        {
            return false;
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

        // If messenger activated
        if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
            dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetUseWorkflow())
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

bool ZBLinkSymbol::SaveProperties(ZBPropertySet& PropSet)
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

bool ZBLinkSymbol::FillProperty(ZBProperty& Property)
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

bool ZBLinkSymbol::SaveProperty(ZBProperty& Property)
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

bool ZBLinkSymbol::ProcessExtendedInput(ZBProperty&    Property,
                                        CString&        value,
                                        ZBPropertySet&    Properties,
                                        bool&            Refresh)
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

bool ZBLinkSymbol::ProcessMenuCommand(int                MenuCommand,
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

// ************************************** Fonctions de recherche ********************************************

CString ZBLinkSymbol::RetreiveUnitGUID(const CString Name, bool& Error) const
{
    ZDProcessGraphModelMdl* pModel =
        dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<ZBLinkSymbol*>(this)->GetOwnerModel());

    if (pModel)
    {
        return pModel->RetreiveUnitGUID(Name, Error);
    }

    Error = true;

    return _T("");
}

CString ZBLinkSymbol::RetreiveUnitName(const CString GUID, bool& Error) const
{
    ZDProcessGraphModelMdl* pModel =
        dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<ZBLinkSymbol*>(this)->GetOwnerModel());

    if (pModel)
    {
        return pModel->RetreiveUnitName(GUID, Error);
    }

    Error = true;

    return _T("");
}

CString ZBLinkSymbol::RetreiveUnitDescription(const CString GUID, bool& Error) const
{
    ZDProcessGraphModelMdl* pModel =
        dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<ZBLinkSymbol*>(this)->GetOwnerModel());

    if (pModel)
    {
        return pModel->RetreiveUnitDescription(GUID, Error);
    }

    Error = true;

    return _T("");
}

float ZBLinkSymbol::RetreiveUnitCost(const CString GUID, bool& Error) const
{
    ZDProcessGraphModelMdl* pModel =
        dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<ZBLinkSymbol*>(this)->GetOwnerModel());

    if (pModel)
    {
        return pModel->RetreiveUnitCost(GUID, Error);
    }

    Error = true;

    return 0;
}

CString ZBLinkSymbol::RetreiveLogicalSystemGUID(const CString Name, bool& Error) const
{
    ZDProcessGraphModelMdl* pModel =
        dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<ZBLinkSymbol*>(this)->GetOwnerModel());

    if (pModel)
    {
        return pModel->RetreiveLogicalSystemGUID(Name, Error);
    }

    Error = true;

    return _T("");
}

CString ZBLinkSymbol::RetreiveLogicalSystemName(const CString GUID, bool& Error) const
{
    ZDProcessGraphModelMdl* pModel =
        dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<ZBLinkSymbol*>(this)->GetOwnerModel());

    if (pModel)
    {
        return pModel->RetreiveLogicalSystemName(GUID, Error);
    }

    Error = true;

    return _T("");
}

CString ZBLinkSymbol::RetreiveLogicalSystemDescription(const CString GUID, bool& Error) const
{
    ZDProcessGraphModelMdl* pModel =
        dynamic_cast<ZDProcessGraphModelMdl*>(const_cast<ZBLinkSymbol*>(this)->GetOwnerModel());

    if (pModel)
    {
        return pModel->RetreiveLogicalSystemDescription(GUID, Error);
    }

    Error = true;

    return _T("");
}

// ********************************************* Fonctions Get **********************************************

bool ZBLinkSymbol::GetDisplayTitleText() const
{
    return (AcceptDynamicAttributes()) ? m_Attributes.GetDisplayTitleText() : false;
}

CString ZBLinkSymbol::GetAttributeString(ZBPropertyAttributes* pAttributes) const
{
    if (AcceptDynamicAttributes())
    {
        ZBPropertySet PropSet;

        // Retrieve the property set from object
        const_cast<ZBLinkSymbol*>(this)->FillProperties(PropSet);

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

CODComponent* ZBLinkSymbol::GetLocalSymbol()
{
    if (IsLocal())
    {
        return NULL;
    }

    ZDProcessGraphModelMdl* pRootModel = dynamic_cast<ZDProcessGraphModelMdl*>(GetRootModel());

    if (pRootModel)
    {
        CODComponentSet*  pSet = pRootModel->FindSymbol(GetSymbolName(), _T(""), true, true, true);

        // If found, return it
        if (pSet && pSet->GetSize() > 0 && pSet->GetAt(0))
        {
            return pSet->GetAt(0);
        }
    }

    return NULL;
}

CODComponentSet* ZBLinkSymbol::GetReferenceSymbols()
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

CODModel* ZBLinkSymbol::GetOwnerModel()
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

CODModel* ZBLinkSymbol::GetRootModel()
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

CString ZBLinkSymbol::GetSymbolComment() const
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
    {
        return _T("");
    }

    return pBasicProps->GetSymbolDescription();
}

CString ZBLinkSymbol::GetSymbolName() const
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
    {
        return _T("");
    }

    return pBasicProps->GetSymbolName();
}

int ZBLinkSymbol::GetSymbolReferenceNumber() const
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
    {
        return -1;
    }

    return pBasicProps->GetSymbolNumber();
}

CString ZBLinkSymbol::GetSymbolReferenceNumberStr() const
{
    ZBBasicProperties* pBasicProps = (ZBBasicProperties*)GetProperty(ZS_BP_PROP_BASIC);

    if (!pBasicProps)
    {
        return _T("");
    }

    return pBasicProps->GetSymbolNumberStr();
}

// ********************************************* Fonctions Set **********************************************

BOOL ZBLinkSymbol::SetSymbolReferenceNumber(int value)
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
            NotifyAllObservers(NULL);

            // Redraw the symbol
            RedrawSymbol();
            return TRUE;
        }

        return FALSE;
    }

    return TRUE;
}

void ZBLinkSymbol::SetIsLocal(bool value /*= true*/)
{
    if (value == true)
    {
        SetCurrentLineColor(m_InitialLineColor);
        SetCurrentLabelColor(m_InitialLabelLineColor);
    }
    // Sets the new line color to magenta
    else
    {
        SetCurrentLineColor(defCOLOR_BLUE);
        SetCurrentLabelColor(defCOLOR_BLUE);
    }

    m_IsLocal = value;

    // Now redraw the symbol
    RedrawSymbol();
}

void ZBLinkSymbol::SetDisplayTitleText(bool value)
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

// Cette fonction crée le registre de propriétés de la ligne.
BOOL ZBLinkSymbol::SetLineProperty(int nStyle, int nPointSize, COLORREF crColor, int bTransparent)
{
    CODPropPtr pProp;

    pProp = GetProperty(OD_PROP_LINE);

    if (pProp != (CODPropPtr)NULL)
    {
        CODLineProperties LineProp(*((CODLineProperties*)((CODProperty*)pProp)));

        if (nStyle != -1)
        {
            LineProp.SetStyle(nStyle);
        }

        if (nPointSize != -1)
        {
            LineProp.SetPointSize(nPointSize);
        }

        if (crColor != -1)
        {
            LineProp.SetColor(crColor);
        }

        if (bTransparent != -1)
        {
            LineProp.SetTransparent((BOOL)bTransparent);
        }

        SetProperty(&LineProp);

        return TRUE;
    }

    CODLineProperties LineProp;

    if (nStyle != -1)
    {
        LineProp.SetStyle(nStyle);
    }

    if (nPointSize != -1)
    {
        LineProp.SetPointSize(nPointSize);
    }

    if (crColor != -1)
    {
        LineProp.SetColor(crColor);
    }

    if (bTransparent != -1)
    {
        LineProp.SetTransparent((BOOL)bTransparent);
    }

    SetProperty(&LineProp);

    return TRUE;
}

void ZBLinkSymbol::SetCurrentLineColor(COLORREF value)
{
    m_CurrentLineColor = value;
    ZUODSymbolManipulator::ChangeLineColor(this, value);
}

void ZBLinkSymbol::SetInitialLineColor(COLORREF value)
{
    m_InitialLineColor = value;
    SetCurrentLineColor(value);
}

// JMR-MODIF - Le 13 juin 2005 - Ajout de la fonction SetCurrentLineWidth.
// Cette fonction permet de changer la largeur de trait d'une ligne existante.
void ZBLinkSymbol::SetCurrentLineWidth(int value)
{
    m_CurrentLineWidth = value;
    ZUODSymbolManipulator::ChangeLineWidth(this, value);
}

void ZBLinkSymbol::SetInitialLineWidth(int value)
{
    m_InitialLineWidth = value;

    // JMR-MODIF - Le 23 juin 2005 - Remplacé ZUODSymbolManipulator::ChangeLineWidth( this, value ); par
    // SetCurrentLineWidth( value ); pour se conformer aux modèles d'initialisation déjà existants.
    SetCurrentLineWidth(value);
}

// JMR-MODIF - Le 24 juin 2005 - Ajout de la fonction SetCurrentLineStyle.
// Cette fonction permet de changer la largeur de trait d'une ligne existante.
void ZBLinkSymbol::SetCurrentLineStyle(int value)
{
    m_CurrentLineStyle = value;
    ZUODSymbolManipulator::ChangeLineStyle(this, value);
}

// JMR-MODIF - Le 24 juin 2005 - Ajout de la fonction SetInitialLineStyle.
// Cette fonction permet de changer la largeur de trait d'une ligne existante.
void ZBLinkSymbol::SetInitialLineStyle(int value)
{
    m_InitialLineStyle = value;
    SetCurrentLineStyle(value);
}

void ZBLinkSymbol::SetCurrentLabelColor(COLORREF value)
{
    m_CurrentLabelLineColor = value;
    ZUODSymbolManipulator::ChangeLabelLineColor(this, value);
}

void ZBLinkSymbol::SetInitialLabelLineColor(COLORREF value)
{
    m_InitialLabelLineColor = value;
    SetCurrentLabelColor(value);
}

void ZBLinkSymbol::SetInitialLabelLineWidth(int value)
{
    m_InitialLabelLineWidth = value;
    ZUODSymbolManipulator::ChangeLabelLineWidth(this, value);
}

BOOL ZBLinkSymbol::SetSymbolComment(const CString& value)
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

BOOL ZBLinkSymbol::SetSymbolName(const CString& value)
{
    CString OldName = GetSymbolName();

    if (OldName != value)
    {
        // JMR-MODIF - Le 27 mars 2006 - Ajout de l'appel à la fonction OnSymbolNameChange.
        OnSymbolNameChange(OldName, value);

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

BOOL ZBLinkSymbol::SetSymbolReferenceNumberStr(const CString& value)
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
            NotifyAllObservers(NULL);

            // Redraw the symbol
            RedrawSymbol();

            return TRUE;
        }

        return FALSE;
    }

    return TRUE;
}

// Cette fonction permet d'attribuer le drapeau de modification.
void ZBLinkSymbol::SetModifiedFlag(BOOL Value /*= TRUE*/)
{
    CODModel* pModel = GetRootModel();

    if (pModel)
    {
        pModel->SetModifiedFlag(Value);
    }
}

// ********************************** Following and Entering link methods ***********************************

CODSymbolComponent* ZBLinkSymbol::GetFollowingSymbol()
{
    IODNode* pINode = NULL;
    IODEdge* pIEdge;
    pIEdge = guid_cast<IODEdge*>(this);
    pIEdge->AddRef();

    if (pIEdge != NULL)
    {
        pINode = pIEdge->GetHeadNode();

        // ******************************************************************************************************
        // JMR-MODIF - Le 28 septembre 2005 - Nettoyage des memory leaks, supprime la référence redondante.
        // Lors de l'appel à GetHeadNode, une référence supplémentaire est ajouté sur le composant recherché, qui
        // empêche la destruction de l'objet par la suite.
        CODComponent* m_pHeadComp = GetHeadComponent();

        if (m_pHeadComp != NULL && pINode != NULL)
        {
            m_pHeadComp->AddRef();

            if (m_pHeadComp->Release() > 1)
            {
                m_pHeadComp->Release();
            }
        }
        // ******************************************************************************************************

        pIEdge->Release();
    }

    return static_cast<CODSymbolComponent*>(pINode);
}

CODSymbolComponent* ZBLinkSymbol::GetEnteringSymbol()
{
    IODNode* pINode = NULL;
    IODEdge* pIEdge;
    pIEdge = guid_cast<IODEdge*>(this);
    pIEdge->AddRef();

    if (pIEdge != NULL)
    {
        pINode = pIEdge->GetTailNode();

        // ******************************************************************************************************
        // JMR-MODIF - Le 28 septembre 2005 - Nettoyage des memory leaks, supprime la référence redondante.
        // Lors de l'appel à GetTailNode, une référence supplémentaire est ajouté sur le composant recherché, qui
        // empêche la destruction de l'objet par la suite.
        CODComponent* m_pTailComp = GetTailComponent();

        if (m_pTailComp != NULL && pINode != NULL)
        {
            m_pTailComp->AddRef();

            if (m_pTailComp->Release() > 1)
            {
                m_pTailComp->Release();
            }
        }
        // ******************************************************************************************************

        pIEdge->Release();
    }

    return static_cast<CODSymbolComponent*>(pINode);
}

// **********************************************************************************************************
// *                                               Sérialisation                                            *
// **********************************************************************************************************

void ZBLinkSymbol::Serialize(CArchive& ar)
{
    // Serialize the link symbol
    CODLinkComponent::Serialize(ar);

    // Only if the object is serialize from and to a document
    if (ar.m_pDocument)
    {
        if (ar.IsStoring())
        {
            if (m_pReference)
            {
                m_NameOfReference = dynamic_cast<ZBLinkSymbol*>(m_pReference)->GetSymbolReferenceNumberStr();
            }
            else
            {
                m_NameOfReference.Empty();
            }

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

            // Serialize the dynamic properties
            ar << m_DynamicPropManager;
        }
        else
        {
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

            if (ar.m_pDocument &&
                dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 19)
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

            // Serialize the attributes
            m_Attributes.RemoveAllAttributes();
            ar >> m_Attributes;

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
                ar >> (CObject*&)m_DynamicPropManager;

            if (!m_DynamicPropManager)
                m_DynamicPropManager = new ZBDynamicProperties;

            CODEditProperties* pPropEdit = (CODEditProperties*)GetProperty(OD_PROP_EDIT);

            if (pPropEdit)
                pPropEdit->SetCanSelect(TRUE);
        }
    }

    // Serialize external applications and files
    ZBExtAppPropertyMgr::Serialize(ar);
    ZBExtFilePropertyMgr::Serialize(ar);

    // Once loaded, call the base function 
    // to adjust the position of embedded elements
    AdjustElementPosition();
}
