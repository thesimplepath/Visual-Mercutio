// **********************************************************************************************************
// *                                       Classe ZBDeliverableLinkSymbol                                    *
// **********************************************************************************************************
// * Cette classe représente un livrable. Elle hélrite de la classe PSS_LinkSymbol, qui contient tous les        *
// * outils nécessaires à la jonction entre deux symboles, et ajoute à cette classe l'interface complète    *
// * pour la gestion des livrables.                                                                            *
// **********************************************************************************************************

#include "stdafx.h"
#include "ZBDeliverableLinkSymbol.h"

#include "PSS_ProcessGraphModelMdlBP.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"

#include "ZBBPRuleListProp.h"
#include "ZBBPTextItemListProp.h"
#include "PSS_CostPropertiesDeliverableBP.h"
#include "ZBBPAnnualNumberProp.h"
#include "ZBBPSimPropDeliverable.h"

#include "ZBBPDoorSymbol.h"
#include "ZBBPPageSymbol.h"
#include "ZBBPProcedureSymbol.h"
#include "ZBBPProcessSymbol.h"
#include "ZBBPStartSymbol.h"
#include "ZBBPStopSymbol.h"

#include "zModel\PSS_SymbolLabel.h"
#include <Views\OdLineOrientation.h>

#include "zModel\PSS_ODSymbolManipulator.h"
#include "zModel\PSS_UserGroupEntity.h"
#include "zModel\PSS_SelectUserGroupDlg.h"

#include "PSS_ProcessGraphModelControllerBP.h"

#include "ZVEqualizeQuantityDlg.h"

#include "zBaseLib\PSS_Tokenizer.h"

// JMR-MODIF - Le 13 juin 2007 - Ajout de l'en-tête ZVRiskOptionsDlg.h
#include "ZVRiskOptionsDlg.h"

// Resources
#include "PSS_ModelResIDs.h"
#include "zModelBPRes.h"

// Global resources
#include "zBaseLib\PSS_Global.h"

#include "zModel\PSS_SelectModelSymbolDlg.h"

#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 3 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(ZBDeliverableLinkSymbol, PSS_LinkSymbol, g_DefVersion)

// **********************************************************************************************************
// *                                           Static variables                                                *
// **********************************************************************************************************

// JMR-MODIF - Le 28 novembre 2006 - Ajout de la nouvelle variable statique gRulesMenu.
static CMenu gRulesMenu;
// JMR-MODIF - Le 10 juin 2007 - Ajout de la nouvelle variable statique gRiskMenu
static CMenu gRiskMenu;

const size_t _MaxRuleListSize = 20;
const size_t _MaxTextItemListSize = 20;
// JMR-MODIF - Le 22 novembre 2006 - Ajout de la constante _MaxRulesSize.
const size_t _MaxRulesSize = 20;
// JMR-MODIF - Le 3 juin 2007 - Ajout de la constante _MaxRisksSize.
const size_t _MaxRisksSize = 20;

// **********************************************************************************************************
// *              Construction, destruction, opérateurs et fonctions de manipulation de l'objet                *
// **********************************************************************************************************

// Constructeur par défaut de l'objet.
ZBDeliverableLinkSymbol::ZBDeliverableLinkSymbol()
{
    // don't use dynamic area
    SetUseDynamicArea(false);
    CreateSymbolProperties();
}

// Destructeur par défaut de l'objet.
ZBDeliverableLinkSymbol::~ZBDeliverableLinkSymbol()
{}

// Constructeur par copie de l'objet.
ZBDeliverableLinkSymbol::ZBDeliverableLinkSymbol(const ZBDeliverableLinkSymbol& src)
{
    *this = src;
}

// Fonction de surcharge de l'opérateur =
ZBDeliverableLinkSymbol& ZBDeliverableLinkSymbol::operator=(const ZBDeliverableLinkSymbol& src)
{
    // Call the base class assignement operator
    PSS_LinkSymbol::operator=((const PSS_LinkSymbol&)src);

    m_Quantity = src.m_Quantity;
    m_SimProperties = src.m_SimProperties;
    m_CostDeliverableProperties = src.m_CostDeliverableProperties;
    m_UnitProp = src.m_UnitProp;

    // JMR-MODIF - Le 26 novembre 2006 - Ajout de la copie des règles.
    m_Rules = src.m_Rules;

    // JMR-MODIF - Le 29 juillet 2007 - Ajout du code de copie pour les risques
    m_Risks = src.m_Risks;

    for (int i = 0; i < src.m_UnitDoubleValidationTypeArray.GetSize(); ++i)
    {
        m_UnitDoubleValidationTypeArray.Add(src.m_UnitDoubleValidationTypeArray.GetAt(i));
    }

    return *this;
}

// Cette fonction permet d'obtenir une copie de l'objet.
CODComponent* ZBDeliverableLinkSymbol::Dup() const
{
    return (new ZBDeliverableLinkSymbol(*this));
}

// **********************************************************************************************************
// *                                   Fonctions de création du symbole                                        *
// **********************************************************************************************************

BOOL ZBDeliverableLinkSymbol::Create(int nStyle, int nPointSize, COLORREF crColor, int bTransparent)
{
    m_IsInCreationProcess = true;

    BOOL bResult = PSS_LinkSymbol::Create(nStyle, nPointSize, crColor, bTransparent);

    if (bResult)
    {
        SetTargetEndpoint(new CODArrowEndpoint());
    }

    if (!CreateSymbolProperties())
    {
        bResult = FALSE;
    }

    if (!CreateSymbolName())
    {
        bResult = FALSE;
    }

    // Sets the default line color for the label
    SetInitialLabelLineColor(defCOLOR_LTLTGRAY);

    // Adjust the element position for symbols
    AdjustElementPosition();

    m_IsInCreationProcess = false;

    return bResult;
}

// Cette fonction crée le squelette du symbole. Elle crée les propriétés graphiques du symbole.
BOOL ZBDeliverableLinkSymbol::CreateOrthogonal(int nStyle, int nPointSize, COLORREF crColor, int bTransparent)
{
    m_IsInCreationProcess = true;

    BOOL bResult = PSS_LinkSymbol::CreateOrthogonal(nStyle, nPointSize, crColor, bTransparent);

    if (bResult)
    {
        SetTargetEndpoint(new CODArrowEndpoint());
    }

    if (!CreateSymbolProperties())
    {
        bResult = FALSE;
    }

    if (!CreateSymbolName())
    {
        bResult = FALSE;
    }

    // JMR-MODIF - Le 14 juin 2005 - Mets à jour les informations visuelles en fonction du pourcentage.
    SetVisualInfo(100);

    // Sets the default line color for the label
    SetInitialLabelLineColor(defCOLOR_LTLTGRAY);

    // Adjust the element position for symbols
    AdjustElementPosition();

    m_IsInCreationProcess = false;

    return bResult;
}

CODLabelComponent* ZBDeliverableLinkSymbol::CreateLabel(const LPCTSTR            lpszText,
                                                        const OD_CONTROL_POINT    ctlPoint,
                                                        CDC*                    pDC)
{
    if (UseDynamicArea())
    {
        CODLabelComponent* pLabelComp = new PSS_SymbolLabel(ctlPoint, true);
        pLabelComp->SetText(lpszText);

        if (pLabelComp->Create(pDC))
        {
            AddLabel(pLabelComp);

            pLabelComp->SetOrientationFlag(TRUE);
            pLabelComp->SetOrientation(ctlPoint);
        }
        else
        {
            delete pLabelComp;
            pLabelComp = NULL;
        }

        if (pLabelComp != NULL)
        {
            CODLineOrientation propLineOrientation;
            pLabelComp->AddProperty(propLineOrientation);
        }

        return pLabelComp;
    }

    return PSS_LinkSymbol::CreateLabel(lpszText, ctlPoint, pDC);
}

bool ZBDeliverableLinkSymbol::CreateSymbolName()
{
    // Create the area box as a label.
    CODLabelComponent* pLabelComp = CODLinkComponent::CreateLabel(_T(""));

    if (!pLabelComp)
    {
        return false;
    }

    // If we would like to use dynamic area
    if (UseDynamicArea())
    {
        pLabelComp->SetName(M_EditAreaComponentControlLabel);

        pLabelComp->SetValue(OD_PROP_AUTOSIZE, TRUE);
        pLabelComp->SetValue(OD_PROP_WORDBREAK, TRUE);
        pLabelComp->SetValue(OD_PROP_MULTILINE, TRUE);
        pLabelComp->SetValue(OD_PROP_TRANSPARENT, TRUE);

        pLabelComp->SetTextBox(CRect(0, 0, 100, 40));

        CODFontProperties* pFontProp = (CODFontProperties*)pLabelComp->GetProperty(OD_PROP_FONT);
        CODFontProperties FontProp(*pFontProp);
        FontProp.SetFaceName(_T("Arial"));
        FontProp.SetWeight(FW_BOLD);
        FontProp.SetPointSize(8);
        pLabelComp->SetProperty(&FontProp);

        CODFillProperties* pFillProps = dynamic_cast<CODFillProperties*>(pLabelComp->GetProperty(OD_PROP_FILL));
        CODFillProperties FillProps(*pFillProps);
        FillProps.SetTransparent(TRUE);
        pLabelComp->SetProperty(&FillProps);

        // Create the symbol name text component
        CODTextComponent* pTextComp = new CODTextComponent;

        // Set its size
        pTextComp->Create(pLabelComp->GetBounds(), NULL);

        pTextComp->SetName(M_SymbolNameComponentControlLabel);
        CODLineProperties lineProp;
        lineProp.SetTransparent(TRUE);
        pTextComp->SetProperty(&lineProp);

        // Can't be selected
        CODEditProperties* pEdit = (CODEditProperties*)pTextComp->GetProperty(OD_PROP_EDIT);
        CODEditProperties editChange(*pEdit);
        editChange.SetCanSelect(FALSE);
        pTextComp->SetProperty(&editChange);

        // Change the fill color
        pFillProps = dynamic_cast<CODFillProperties*>(pTextComp->GetProperty(OD_PROP_FILL));
        CODFillProperties FillProps1(*pFillProps);
        FillProps1.SetColor(RGB(192, 220, 192));
        pTextComp->SetProperty(&FillProps1);

        AppendChild(pTextComp);

        pTextComp->SetValue(OD_PROP_AUTOSIZE, TRUE);
        pTextComp->SetValue(OD_PROP_WORDBREAK, TRUE);
        pTextComp->SetValue(OD_PROP_MULTILINE, TRUE);
        pTextComp->SetValue(OD_PROP_TRANSPARENT, TRUE);
        pTextComp->SetTextBox(CRect(0, 0, 100, 40));

        pFontProp = (CODFontProperties*)pTextComp->GetProperty(OD_PROP_FONT);

        if (pFontProp != NULL)
        {
            pFontProp->SetFaceName(_T("Arial"));
            pFontProp->SetWeight(FW_BOLD);
            pFontProp->SetPointSize(8);
            pTextComp->SetProperty(pFontProp);
        }

        // Create the symbol comment text component
        pTextComp = new CODTextComponent;

        // Set its size
        pTextComp->Create(pLabelComp->GetBounds(), NULL);

        pTextComp->SetName(M_CommentComponentControlLabel);
        CODLineProperties lineProp2;
        lineProp2.SetTransparent(TRUE);
        pTextComp->SetProperty(&lineProp2);

        // Can't be selected
        pEdit = (CODEditProperties*)pTextComp->GetProperty(OD_PROP_EDIT);
        CODEditProperties editChange2(*pEdit);
        editChange2.SetCanSelect(FALSE);
        pTextComp->SetProperty(&editChange2);

        // Change the fill color
        pFillProps = dynamic_cast<CODFillProperties*>(pTextComp->GetProperty(OD_PROP_FILL));
        CODFillProperties FillProps2(*pFillProps);
        FillProps2.SetColor(RGB(192, 220, 192));
        pTextComp->SetProperty(&FillProps2);

        AppendChild(pTextComp);

        pTextComp->SetValue(OD_PROP_AUTOSIZE, TRUE);
        pTextComp->SetValue(OD_PROP_WORDBREAK, TRUE);
        pTextComp->SetValue(OD_PROP_MULTILINE, TRUE);
        pTextComp->SetValue(OD_PROP_TRANSPARENT, TRUE);
        pTextComp->SetTextBox(CRect(0, 0, 100, 40));

        pFontProp = (CODFontProperties*)pTextComp->GetProperty(OD_PROP_FONT);

        if (pFontProp != NULL)
        {
            pFontProp->SetFaceName(_T("Arial"));
            pFontProp->SetWeight(FW_BOLD);
            pFontProp->SetPointSize(8);
            pTextComp->SetProperty(pFontProp);
        }

        // Create the symbol attribute text component
        pTextComp = new CODTextComponent;

        // Set its size
        pTextComp->Create(pLabelComp->GetBounds(), NULL);

        pTextComp->SetName(M_AttributeAreaComponentLabel);
        CODLineProperties lineProp3;
        lineProp3.SetTransparent(TRUE);
        pTextComp->SetProperty(&lineProp3);

        // Can't be selected
        pEdit = (CODEditProperties*)pTextComp->GetProperty(OD_PROP_EDIT);
        CODEditProperties editChange3(*pEdit);
        editChange3.SetCanSelect(FALSE);
        pTextComp->SetProperty(&editChange3);

        // Change the fill color
        pFillProps = dynamic_cast<CODFillProperties*>(pTextComp->GetProperty(OD_PROP_FILL));
        CODFillProperties FillProps3(*pFillProps);
        FillProps3.SetColor(RGB(192, 220, 192));
        pTextComp->SetProperty(&FillProps3);

        AppendChild(pTextComp);

        pTextComp->SetValue(OD_PROP_AUTOSIZE, TRUE);
        pTextComp->SetValue(OD_PROP_WORDBREAK, TRUE);
        pTextComp->SetValue(OD_PROP_MULTILINE, TRUE);
        pTextComp->SetValue(OD_PROP_TRANSPARENT, TRUE);
        pTextComp->SetValue(OD_PROP_HORZ_ALIGNMENT, DT_LEFT);
        pTextComp->SetValue(OD_PROP_VERT_ALIGNMENT, DT_TOP);
        pTextComp->SetTextBox(CRect(0, 0, 100, 40));

        pFontProp = (CODFontProperties*)pTextComp->GetProperty(OD_PROP_FONT);

        if (pFontProp != NULL)
        {
            pFontProp->SetFaceName(_T("Arial"));
            pFontProp->SetWeight(FW_BOLD);
            pFontProp->SetPointSize(8);
            pTextComp->SetProperty(pFontProp);
        }
    }
    else
    {
        // No dynamic attributes
        pLabelComp->SetName(M_SymbolNameComponentControlLabel);
        pLabelComp->SetTextBox(CRect(0, 0, 100, 40));

        CODFontProperties* pFontProp = (CODFontProperties*)pLabelComp->GetProperty(OD_PROP_FONT);
        CODFontProperties FontProp(*pFontProp);
        FontProp.SetFaceName(_T("Arial"));
        FontProp.SetWeight(FW_BOLD);
        FontProp.SetPointSize(8);
        pLabelComp->SetProperty(&FontProp);

        pLabelComp->SetValue(OD_PROP_AUTOSIZE, TRUE);
        pLabelComp->SetValue(OD_PROP_WORDBREAK, TRUE);
        pLabelComp->SetValue(OD_PROP_MULTILINE, TRUE);
        pLabelComp->SetValue(OD_PROP_HORZ_ALIGNMENT, DT_CENTER);
        pLabelComp->SetValue(OD_PROP_VERT_ALIGNMENT, DT_TOP);

        // Change the fill color
        // JMR-MODIF - Le 31 mai 2005 - Conversion explicite remplace le cast. La conversion explicite
        // donne un résultat identique sur l'objet casté en classe de base, tandis que l'ancienne
        // implémentation (dynamic_cast) provoque une exception dans le compilateur VC.NET
        CODFillProperties* pFillProps = (CODFillProperties*)pLabelComp->GetProperty(OD_PROP_FILL);
        //        CODFillProperties* pFillProps = dynamic_cast<CODFillProperties*>(pLabelComp->GetProperty(OD_PROP_FILL));
        CODFillProperties FillProps1(*pFillProps);
        FillProps1.SetColor(RGB(192, 220, 192));
        pLabelComp->SetProperty(&FillProps1);
    }

    return true;
}

void ZBDeliverableLinkSymbol::CopySymbolDefinitionFrom(CODSymbolComponent& src)
{
    // Class the base class method
    PSS_LinkSymbol::CopySymbolDefinitionFrom(src);

    if (ISA((&src), ZBDeliverableLinkSymbol))
    {
        m_Quantity = ((ZBDeliverableLinkSymbol&)src).m_Quantity;
        m_SimProperties = ((ZBDeliverableLinkSymbol&)src).m_SimProperties;
        m_CostDeliverableProperties = ((ZBDeliverableLinkSymbol&)src).m_CostDeliverableProperties;
        m_UnitProp = ((ZBDeliverableLinkSymbol&)src).m_UnitProp;

        // JMR-MODIF - Le 26 novembre 2006 - Ajout de la copie de la variable m_Rules.
        m_Rules = ((ZBDeliverableLinkSymbol&)src).m_Rules;

        // JMR-MODIF - Le 29 juillet 2007 - Ajout du code de copie pour les risques
        m_Risks = ((ZBDeliverableLinkSymbol&)src).m_Risks;

        for (int i = 0; i < ((ZBDeliverableLinkSymbol&)src).m_UnitDoubleValidationTypeArray.GetSize(); ++i)
        {
            m_UnitDoubleValidationTypeArray.Add(((ZBDeliverableLinkSymbol&)src).m_UnitDoubleValidationTypeArray.GetAt(i));
        }
    }
}

// **********************************************************************************************************
// *                              Fonctions de réponse aux événements de l'objet                            *
// **********************************************************************************************************

// JMR-MODIF - Le 19 novembre 2006 - Détermine la validité d'un objet obtenu par glisser-coller.
bool ZBDeliverableLinkSymbol::AcceptDropItem(CObject* pObj, const CPoint& pt)
{
    // JMR-MODIF - Le 19 décembre 2006 - Si le symbole n'est pas local, interdit l'opération de glisser-coller.
    if (!IsLocal())
    {
        return false;
    }

    if (pObj && ISA(pObj, PSS_LogicalRulesEntity))
    {
        return true;
    }

    return PSS_LinkSymbol::AcceptDropItem(pObj, pt);
}

// JMR-MODIF - Le 19 novembre 2006 - Fonction de réponse à l'ordre de glisser-coller.
bool ZBDeliverableLinkSymbol::DropItem(CObject* pObj, const CPoint& pt)
{
    // *********************************************************************************************
    // JMR-MODIF - Le 20 novembre 2006 - Ajout du code pour le traitement des objets de type règles.
    if (pObj && ISA(pObj, PSS_LogicalRulesEntity))
    {
        // First, check if the rule is valid
        CODModel* pModel = GetRootModel();

        if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
            !dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->MainLogicalRulesIsValid())
        {
            // Cannot delete all rules
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTDROP_RULENOTINLINE, MB_OK);
            return false;
        }

        PSS_LogicalRulesEntity* pRule = dynamic_cast<PSS_LogicalRulesEntity*>(pObj);

        ZBBPRulesProperties* m_NewRule = new ZBBPRulesProperties();

        m_NewRule->SetRuleName(pRule->GetEntityName());
        m_NewRule->SetRuleDescription(pRule->GetEntityDescription());
        m_NewRule->SetRuleGUID(pRule->GetGUID());

        m_Rules.AddRule(m_NewRule);

        // Set flag for modification
        SetModifiedFlag(TRUE);

        // Redraw the symbol
        RedrawSymbol();
        return true;
    }
    // *********************************************************************************************

    return PSS_LinkSymbol::DropItem(pObj, pt);
}

// JMR-MODIF - Le 27 mars 2006 - Ajout de la fonction virtuelle OnSymbolNameChange.
void ZBDeliverableLinkSymbol::OnSymbolNameChange(CString OldName, CString NewName)
{
    NotifyNameChange(OldName, NewName);
}

bool ZBDeliverableLinkSymbol::OnPostCreation(CODModel* pModel /*= NULL*/, CODController* pCtrl /*= NULL*/)
{
    if (!PSS_LinkSymbol::OnPostCreation(pModel, pCtrl))
    {
        return false;
    }

    // Check the symbols attached to the deliverable
    CODSymbolComponent*    pDst = GetFollowingSymbol();
    CODSymbolComponent*    pSrc = GetEnteringSymbol();

    if (pSrc && pDst)
    {
        // Check for door procedure and procedure door
        if (ISA(pSrc, ZBBPDoorSymbol) && ISA(pDst, ZBBPProcedureSymbol))
        {
            DoDoorProcedureConnection(dynamic_cast<ZBBPDoorSymbol*>(pSrc),
                                      dynamic_cast<ZBBPProcedureSymbol*>(pDst),
                                      pModel);
        }
        else if (ISA(pSrc, ZBBPProcedureSymbol) && ISA(pDst, ZBBPDoorSymbol))
        {
            DoProcedureDoorConnection(dynamic_cast<ZBBPProcedureSymbol*>(pSrc),
                                      dynamic_cast<ZBBPDoorSymbol*>(pDst),
                                      pModel);
        }
        // Check for page procedure and procedure page
        else if (ISA(pSrc, ZBBPPageSymbol) && ISA(pDst, ZBBPProcedureSymbol))
        {
            DoPageProcedureConnection(dynamic_cast<ZBBPPageSymbol*>(pSrc),
                                      dynamic_cast<ZBBPProcedureSymbol*>(pDst),
                                      pModel);
        }
        else if (ISA(pSrc, ZBBPProcedureSymbol) && ISA(pDst, ZBBPPageSymbol))
        {
            DoProcedurePageConnection(dynamic_cast<ZBBPProcedureSymbol*>(pSrc),
                                      dynamic_cast<ZBBPPageSymbol*>(pDst),
                                      pModel);
        }
        // And finally, for process to process
        else if (ISA(pSrc, ZBBPProcessSymbol) && ISA(pDst, ZBBPProcessSymbol))
        {
            DoProcessProcessConnection(dynamic_cast<ZBBPProcessSymbol*>(pSrc),
                                       dynamic_cast<ZBBPProcessSymbol*>(pDst),
                                       pModel);
        }
    }

    // Check the status in order to set the right color
    CheckDeliverableStatus();

    return true;
}

bool ZBDeliverableLinkSymbol::OnPreDelete(CODModel* pModel /*= NULL*/, CODController* pCtrl /*= NULL*/)
{
    // Before disconnecting the link from the symbol
    CODSymbolComponent* pDst = GetFollowingSymbol();

    if (pDst && ISA(pDst, PSS_Symbol))
    {
        dynamic_cast<PSS_Symbol*>(pDst)->OnLinkDisconnect(this);
    }

    CODSymbolComponent* pSrc = GetEnteringSymbol();

    if (pSrc && ISA(pSrc, PSS_Symbol))
    {
        dynamic_cast<PSS_Symbol*>(pSrc)->OnLinkDisconnect(this);
    }

    return true;
}

// JMR-MODIF - Le 7 juin 2006 - Cette fonction corrige un bug d'affichage propre aux symboles procédures.
void ZBDeliverableLinkSymbol::AdjustPoints()
{
    if (m_pILinkShape != NULL)
    {
        CODPortComponent* pSourcePort = GetSourcePort();
        CODPortComponent* pTargetPort = GetTargetPort();

        CODOrthogonalLinkShape* m_LinkShape = static_cast<CODOrthogonalLinkShape*>(m_pILinkShape);

        if (m_LinkShape == NULL)
        {
            m_pILinkShape->Dock(pSourcePort, pTargetPort);
            return;
        }

        int nPointCount = m_LinkShape->GetPointCount();

        if (nPointCount < 2)
        {
            return;
        }

        CODIntProperty propSpacing;

        int nSpacing = (m_LinkShape->GetParent()->GetProperty(OD_PROP_LINK_SPACING, propSpacing) ?
                        propSpacing.GetValue() : odg_nDefaultLinkSpacing);

        CPoint ptTail = m_LinkShape->GetVertex(0);
        CPoint ptHead = m_LinkShape->GetVertex(nPointCount - 1);

        CODComponent* pTailComp = NULL;
        CODComponent* pHeadComp = NULL;

        if (pSourcePort != NULL)
        {
            ptTail = pSourcePort->GetLocation();
            pTailComp = pSourcePort->GetOwner();
        }

        if (pTargetPort != NULL)
        {
            ptHead = pTargetPort->GetLocation();
            pHeadComp = pTargetPort->GetOwner();
        }

        m_LinkShape->SetVertex(0, ptTail);
        m_LinkShape->SetVertex(nPointCount - 1, ptHead);

        CRect rcLinePadding(odg_rcOrthogonalLinePadding);

        // Calculate points to be orthogonal (all 90 degree angles).
        // We must determine the direction for each endpoint.
        CSize szDirPt1(0, 0);
        CSize szDirPt2(0, 0);

        // The default calculation assumes that the line stops at the perimeter
        // of each symbol. In this case, we have more control over the direction
        // of the line because it won't cross the symbol. This calculation makes
        // both endpoints face towards each other to minimize the number of
        // bends in the line.
        m_LinkShape->CalcEndpointDirections(szDirPt1, szDirPt2);

        if (pTailComp != NULL && pHeadComp != NULL)
        {
            CRect rcTail = pTailComp->GetBounds();
            CRect rcHead = pHeadComp->GetBounds();

            int nLeftInflate = rcLinePadding.left / 2;
            int nTopInflate = rcLinePadding.top / 2;
            int nRightInflate = rcLinePadding.right / 2;
            int nBottomInflate = rcLinePadding.bottom / 2;

            rcTail.InflateRect(nLeftInflate, nTopInflate, nRightInflate, nBottomInflate);
            rcHead.InflateRect(nLeftInflate, nTopInflate, nRightInflate, nBottomInflate);

            CRect rcIntersect;
            BOOL bIntersect = rcIntersect.IntersectRect(&rcTail, &rcHead);

            if (rcTail == rcHead)
            {
                CSize szTmp = szDirPt1;
                int nTurnDirection = 1;

                szDirPt1.cx = (szTmp.cy * nTurnDirection);
                szDirPt1.cy = (szTmp.cx * nTurnDirection);
            }
            else if (bIntersect)
            {
                CSize szTmp = szDirPt1;
                int nTurnDirection = 1;

                szDirPt1.cx = (szTmp.cy * nTurnDirection);
                szDirPt1.cy = (szTmp.cx * nTurnDirection);

                szTmp = szDirPt2;
                nTurnDirection = -1;

                szDirPt2.cx = (szTmp.cy * nTurnDirection);
                szDirPt2.cy = (szTmp.cx * nTurnDirection);
            }
        }

        // If a port doesn't allow attaching the line at the perimeter of the symbol,
        // then it is possible (even likely) that the line will cross the symbol.
        // Calculate the direction for the endpoint to minimize the intersection of
        // the line and symbol.
        if (pSourcePort != NULL && pSourcePort->MustAttachAtPerimeter())
        {
            ASSERT_VALID(pTailComp);

            CRect rcTail = pTailComp->GetBounds();
            CPoint ptNext = ptTail;

            if (szDirPt1.cx < 0)
            {
                ptNext.x = rcTail.left - 1;
            }

            if (szDirPt1.cx > 0)
            {
                ptNext.x = rcTail.right + 1;
            }

            if (szDirPt1.cy < 0)
            {
                ptNext.y = rcTail.top - 1;
            }

            if (szDirPt1.cy > 0)
            {
                ptNext.y = rcTail.bottom + 1;
            }

            CPoint ptAdjustedTail = pTailComp->GetBaseRgn().GetBoundaryPoint(&ptTail, &ptNext, nSpacing);
            m_LinkShape->SetVertex(0, ptAdjustedTail);
        }
        else if (pTailComp != NULL)
        {
            szDirPt1 = CODGlobal::CalcOrthogonalDirection(ptTail, pTailComp->GetBounds());

            CString SrcPortName = pSourcePort->GetName();

            if (SrcPortName == M_PortUPComponentLabel)
            {
                szDirPt1.cx = 0;
                szDirPt1.cy = -1;
            }
            else if (SrcPortName == M_PortDOWNComponentLabel)
            {
                szDirPt1.cx = 0;
                szDirPt1.cy = 1;
            }
            else if (SrcPortName == M_PortLEFTComponentLabel)
            {
                szDirPt1.cx = -1;
                szDirPt1.cy = 0;
            }
            else if (SrcPortName == M_PortRIGHTComponentLabel)
            {
                szDirPt1.cx = 1;
                szDirPt1.cy = 0;
            }
            else
            {
                szDirPt1 = CODGlobal::CalcOrthogonalDirection(ptTail, pTailComp->GetBounds());
            }
        }

        if (pTargetPort != NULL && pTargetPort->MustAttachAtPerimeter())
        {
            ASSERT_VALID(pHeadComp);

            CRect rcHead = pHeadComp->GetBounds();
            CPoint ptPrev = ptHead;

            if (szDirPt2.cx < 0)
            {
                ptPrev.x = rcHead.left - 1;
            }

            if (szDirPt2.cx > 0)
            {
                ptPrev.x = rcHead.right + 1;
            }

            if (szDirPt2.cy < 0)
            {
                ptPrev.y = rcHead.top - 1;
            }

            if (szDirPt2.cy > 0)
            {
                ptPrev.y = rcHead.bottom + 1;
            }

            CPoint ptAdjustedHead = pHeadComp->GetBaseRgn().GetBoundaryPoint(&ptHead, &ptPrev, nSpacing);
            m_LinkShape->SetVertex(nPointCount - 1, ptAdjustedHead);
        }
        else if (pHeadComp != NULL)
        {
            szDirPt2 = CODGlobal::CalcOrthogonalDirection(ptHead, pHeadComp->GetBounds());

            CString TrgPortName = pTargetPort->GetName();

            if (TrgPortName == M_PortUPComponentLabel)
            {
                szDirPt2.cx = 0;
                szDirPt2.cy = -1;
            }
            else if (TrgPortName == M_PortDOWNComponentLabel)
            {
                szDirPt2.cx = 0;
                szDirPt2.cy = 1;
            }
            else if (TrgPortName == M_PortLEFTComponentLabel)
            {
                szDirPt2.cx = -1;
                szDirPt2.cy = 0;
            }
            else if (TrgPortName == M_PortRIGHTComponentLabel)
            {
                szDirPt2.cx = 1;
                szDirPt2.cy = 0;
            }
            else
            {
                szDirPt2 = CODGlobal::CalcOrthogonalDirection(ptHead, pHeadComp->GetBounds());
            }
        }

        BOOL bPaddingOk = TRUE;

        if (nPointCount > 2)
        {
            CSize szTailSeg = m_LinkShape->GetVertex(1) - m_LinkShape->GetVertex(0);
            CSize szHeadSeg = m_LinkShape->GetVertex(nPointCount - 2) - m_LinkShape->GetVertex(nPointCount - 1);

            szTailSeg.cx = szTailSeg.cx * szDirPt1.cx;
            szTailSeg.cy = szTailSeg.cy * szDirPt1.cy;

            szHeadSeg.cx = szHeadSeg.cx * szDirPt2.cx;
            szHeadSeg.cy = szHeadSeg.cy * szDirPt2.cy;

            CSize szTailPad(0, 0);

            if (szDirPt1.cx > 0)
            {
                szTailPad.cx = rcLinePadding.right;
            }
            else if (szDirPt1.cy < 0)
            {
                szTailPad.cx = rcLinePadding.left;
            }

            if (szDirPt1.cy > 0)
            {
                szTailPad.cy = rcLinePadding.bottom;
            }
            else if (szDirPt1.cy < 0)
            {
                szTailPad.cy = rcLinePadding.top;
            }

            CSize szHeadPad(0, 0);

            if (szDirPt2.cx > 0)
            {
                szHeadPad.cx = rcLinePadding.right;
            }
            else if (szDirPt2.cy < 0)
            {
                szHeadPad.cx = rcLinePadding.left;
            }

            if (szDirPt2.cy > 0)
            {
                szHeadPad.cy = rcLinePadding.bottom;
            }
            else if (szDirPt2.cy < 0)
            {
                szHeadPad.cy = rcLinePadding.top;
            }

            if (szTailSeg.cx < szTailPad.cx)
            {
                bPaddingOk = FALSE;
            }
            else if (szTailSeg.cy < szTailPad.cy)
            {
                bPaddingOk = FALSE;
            }

            if (szHeadSeg.cx < szHeadPad.cx)
            {
                bPaddingOk = FALSE;
            }
            else if (szHeadSeg.cy < szHeadPad.cy)
            {
                bPaddingOk = FALSE;
            }
        }

        // Calculate the points needed to connect the two endpoints with
        // a set of orthogonal line segments.
        m_LinkShape->MakeOrthogonal(szDirPt1, szDirPt2);
    }
    else
    {
        CODLinkComponent::AdjustPoints();
    }
}

// Cette fonction est appelée lorsque la connection du livrable sur ses symboles d'ancrage doit être crée.
void ZBDeliverableLinkSymbol::OnConnect(CODConnection* pConnection)
{
    PSS_LinkSymbol::OnConnect(pConnection);

    // After connecting the link to the symbol
    CODSymbolComponent* pDst = GetFollowingSymbol();

    if (pDst && ISA(pDst, PSS_Symbol) && pDst->GetDependentPortOnConnection(pConnection))
    {
        dynamic_cast<PSS_Symbol*>(pDst)->OnLinkConnect(this);
    }
    else
    {
        CODSymbolComponent* pSrc = GetEnteringSymbol();

        if (pSrc && ISA(pSrc, PSS_Symbol) && pSrc->GetDependentPortOnConnection(pConnection))
        {
            dynamic_cast<PSS_Symbol*>(pSrc)->OnLinkConnect(this);
        }
    }

    // Check the status in order to set the right color
    CheckDeliverableStatus();
}

// Cette fonction est appelée lorsque la connection du livrable sur ses symboles d'ancrage doit être supprimée.
void ZBDeliverableLinkSymbol::OnDisconnect(CODConnection* pConnection)
{
    // Before disconnecting the link from the symbol
    CODSymbolComponent* pDst = GetFollowingSymbol();

    if (pDst && ISA(pDst, PSS_Symbol) && pDst->GetDependentPortOnConnection(pConnection))
    {
        dynamic_cast<PSS_Symbol*>(pDst)->OnLinkDisconnect(this);
    }
    else
    {
        CODSymbolComponent* pSrc = GetEnteringSymbol();

        if (pSrc && ISA(pSrc, PSS_Symbol) && pSrc->GetDependentPortOnConnection(pConnection))
        {
            dynamic_cast<PSS_Symbol*>(pSrc)->OnLinkDisconnect(this);
        }
    }

    PSS_LinkSymbol::OnDisconnect(pConnection);

    // Check the status in order to set the right color
    CheckDeliverableStatus();
}

// Cette fonction est appelée lorsque les points d'ancrage du symbole bougent.
BOOL ZBDeliverableLinkSymbol::OnConnectionMove(CODConnection* pConnection)
{
    BOOL RetValue = PSS_LinkSymbol::OnConnectionMove(pConnection);

    // Check the status in order to set the right color
    CheckDeliverableStatus();

    return RetValue;
}

BOOL ZBDeliverableLinkSymbol::OnRemoveDependent(CODConnection* pConnection)
{
    BOOL RetValue = PSS_LinkSymbol::OnRemoveDependent(pConnection);

    // Check the status in order to set the right color
    CheckDeliverableStatus();

    return RetValue;
}

bool ZBDeliverableLinkSymbol::OnPrePropertyChanged(const CString& newValue, ZBProperty& prop, ZBPropertySet& props)
{
    // only local symbols have access to properties
    if (!IsLocal())
        return true;

    return PSS_LinkSymbol::OnPrePropertyChanged(newValue, prop, props);
}

bool ZBDeliverableLinkSymbol::OnPostPropertyChanged(ZBProperty&    Property,
                                                    ZBPropertySet&    Properties,
                                                    bool&            Refresh)
{
    // Only local symbol have access to properties
    if (!IsLocal())
    {
        return true;
    }

    bool RetValue = false;

    if (Property.GetCategoryID() == ZS_BP_PROP_TEXTITEMLIST)
    {
        // Change the return value to reload the properties
        // We need to reload since the tasklist has an empty task.
        // If the user fill it, we need to enable a new empty one.
        // And if the user remove one task, we need also to disable one from
        // the property list

        // Run trough the set of properties and changed the enable flag
        // To change the enable flag, we need to check if it is a new
        // property that need to be enabled or not
        // Then we need to insure that only one empty property is enable
        ZBPropertyIterator i(&Properties);
        ZBProperty* pProp;
        size_t        CounterEnableEmpty = 0;

        for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
        {
            if (pProp->GetCategoryID() == ZS_BP_PROP_TEXTITEMLIST)
            {
                // If the string is not empty, first, sets the enable flag to true
                if (!pProp->GetValueString().IsEmpty())
                {
                    pProp->SetEnable(true);
                }

                // If the string is empty
                // Check if he has the enable flag and add it to the counter
                // If the counter is not equal to 1, then enable or disable it
                if (pProp->GetValueString().IsEmpty())
                {
                    if (pProp->GetEnable() == true)
                    {
                        ++CounterEnableEmpty;
                    }
                    else
                    {
                        // If not at least one empty element
                        if (CounterEnableEmpty < 1)
                        {
                            pProp->SetEnable(true);
                            ++CounterEnableEmpty;
                        }
                    }

                    // Now if the counter is greather than 1, then you need to disable the empty element
                    if (CounterEnableEmpty > 1)
                    {
                        --CounterEnableEmpty;
                        pProp->SetEnable(false);
                    }
                }
            }
        }

        RetValue = true;
    }
    else if (Property.GetCategoryID() == ZS_BP_PROP_RULELIST)
    {
        // Change the return value to reload the properties
        // We need to reload since the rulelist has an empty task.
        // If the user fill it, we need to enable a new empty one.
        // And if the user remove one task, we need also to disable one from
        // the property list

        // Run trough the set of properties and changed the enable flag
        // To change the enable flag, we need to check if it is a new
        // property that need to be enabled or not
        // Then we need to insure that only one empty property is enable
        ZBPropertyIterator i(&Properties);
        ZBProperty* pProp;
        size_t        CounterEnableEmpty = 0;

        for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
        {
            if (pProp->GetCategoryID() == ZS_BP_PROP_RULELIST)
            {
                // If the string is not empty, first, sets the enable flag to true
                if (!pProp->GetValueString().IsEmpty())
                {
                    pProp->SetEnable(true);
                }

                // If the string is empty
                // Check if he has the enable flag and add it to the counter
                // If the counter is not equal to 1, then enable or disable it
                if (pProp->GetValueString().IsEmpty())
                {
                    if (pProp->GetEnable() == true)
                    {
                        ++CounterEnableEmpty;
                    }
                    else
                    {
                        // If not at least one empty element
                        if (CounterEnableEmpty < 1)
                        {
                            pProp->SetEnable(true);
                            ++CounterEnableEmpty;
                        }
                    }

                    // Now if the counter is greather than 1, then you need to disable the empty element
                    if (CounterEnableEmpty > 1)
                    {
                        --CounterEnableEmpty;
                        pProp->SetEnable(false);
                    }
                }
            }
        }

        RetValue = true;
    }
    else if (Property.GetCategoryID() == ZS_BP_PROP_QUANTITY && Property.GetItemID() == Z_NUMBER_YEAR)
    {
        // Sets the new value and equalize the information
        m_Quantity.SetAndCalculateQuantitiesBasedOnYear(Property.GetValueDouble());

        // Now saves the equalizer value to the properties to avoid
        // working with wrong figures in the equalizer
        SaveEqualizerToProperties(Properties);
        RetValue = true;
    }
    else if (Property.GetCategoryID() == ZS_BP_PROP_UNIT && Property.GetItemID() == Z_UNIT_NAME)
    {
        // Run trough the set of properties and changed the unit cost
        // to the value of the property
        ZBPropertyIterator i(&Properties);
        ZBProperty* pProp;
        CString GUID;

        for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
        {
            if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT && pProp->GetItemID() == Z_UNIT_GUID)
            {
                GUID = pProp->GetValueString();
                break;
            }
        }

        if (!GUID.IsEmpty())
        {
            for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
            {
                if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT && pProp->GetItemID() == Z_UNIT_COST)
                {
                    bool Error;
                    float UnitCost = RetrieveUnitCost(GUID, Error);

                    if (Error == false)
                    {
                        // If the previous value is different
                        pProp->SetValueFloat(UnitCost);

                        // Change the return value
                        RetValue = true;
                    }

                    break;
                }
            }
        }
    }
    // JMR-MODIF - Le 14 juin 2005 - Mets à jour les informations visuelles en fonction du pourcentage.
    else if (Property.GetCategoryID() == ZS_BP_PROP_DELIVERABLE_COST &&
             Property.GetItemID() == Z_COST_OUT_WORKLOAD_PERCENT)
    {
        SetVisualInfo((int)(Property.GetValueFloat() * 100));
        RedrawSymbol();
    }

    if (RetValue == false)
    {
        return PSS_LinkSymbol::OnPostPropertyChanged(Property, Properties, Refresh);
    }

    return RetValue;
}

bool ZBDeliverableLinkSymbol::OnDropInternalPropertyItem(ZBProperty&        SrcProperty,
                                                         ZBProperty&        DstProperty,
                                                         bool                Top2Down,
                                                         ZBPropertySet&    Properties)
{
    // Call the utility function for swaping two property items
    bool RetValue = ::SwapInternalPropertyItem(SrcProperty,
                                               DstProperty,
                                               Top2Down,
                                               Properties,
                                               ZS_BP_PROP_RULELIST);

    // If done, return
    if (RetValue)
    {
        return true;
    }

    // ********************************************************************************************
    // JMR-MODIF - Le 10 décembre 2006 - Ajout du code pour permettre le glisser-coller des règles.

    RetValue = ::SwapInternalPropertyItem(SrcProperty,
                                          DstProperty,
                                          Top2Down,
                                          Properties,
                                          ZS_BP_PROP_RULES);

    // If done, return
    if (RetValue)
    {
        int SrcIndex = (SrcProperty.GetItemID() - Z_RULE_NAME) / _MaxRulesSize;
        int DstIndex = (DstProperty.GetItemID() - Z_RULE_NAME) / _MaxRulesSize;

        CString SrcRuleName = m_Rules.GetRuleName(SrcIndex);
        CString SrcRuleDesc = m_Rules.GetRuleDescription(SrcIndex);
        CString SrcRuleGUID = m_Rules.GetRuleGUID(SrcIndex);

        CString DstRuleName = m_Rules.GetRuleName(DstIndex);
        CString DstRuleDesc = m_Rules.GetRuleDescription(DstIndex);
        CString DstRuleGUID = m_Rules.GetRuleGUID(DstIndex);

        m_Rules.SetRuleName(SrcIndex, DstRuleName);
        m_Rules.SetRuleDescription(SrcIndex, DstRuleDesc);
        m_Rules.SetRuleGUID(SrcIndex, DstRuleGUID);

        m_Rules.SetRuleName(DstIndex, SrcRuleName);
        m_Rules.SetRuleDescription(DstIndex, SrcRuleDesc);
        m_Rules.SetRuleGUID(DstIndex, SrcRuleGUID);

        return true;
    }
    // ********************************************************************************************

    // Call the utility function for swaping two property items
    return ::SwapInternalPropertyItem(SrcProperty, DstProperty, Top2Down, Properties, ZS_BP_PROP_TEXTITEMLIST);
}

bool ZBDeliverableLinkSymbol::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    toolTipText.Format(IDS_FS_BPDELIVERABLE_TOOLTIP,
        (const char*)GetSymbolName(),
                       (const char*)GetSymbolComment(),
                       (const char*)GetSymbolReferenceNumberStr());

    if (mode == PSS_ToolTip::IE_TT_Design)
    {
        bool bNotConnectedFollowing = (GetFollowingSymbol() == NULL);
        bool bNotConnectedEntering = (GetEnteringSymbol() == NULL);

        if (bNotConnectedFollowing || bNotConnectedEntering)
        {
            toolTipText += _T("\n");

            if (bNotConnectedEntering)
            {
                CString s;
                s.LoadString(IDS_FS_BPDELIVERABLE_MISSING_INCONX_TOOLTIP);
                toolTipText += (s + _T("\n"));
            }

            if (bNotConnectedFollowing)
            {
                CString s;
                s.LoadString(IDS_FS_BPDELIVERABLE_MISSING_OUTCONX_TOOLTIP);
                toolTipText += s;
            }
        }
    }

    return true;
}

// **********************************************************************************************************
// *                              Fonctions de la classe ZBDeliverableLinkSymbol                            *
// **********************************************************************************************************

// *********************************************** Notifications ********************************************

// JMR-MODIF - Le 27 mars 2006 - Fonction de notification pour les processus.
void ZBDeliverableLinkSymbol::NotifyNameChange(const CString                OldName,
                                               const CString                NewName,
                                               PSS_ProcessGraphModelMdlBP* m_RootModel    /* = NULL */)
{
    // Si les noms sont vides, ne fait rien.
    if (OldName.IsEmpty() || NewName.IsEmpty())
    {
        return;
    }

    // Si le modèle d'entrée est vide, cela veut dire que l'on veut une recherche sur tout le document.
    if (m_RootModel == NULL)
    {
        // Obtient le contrôleur de modèles du document.
        m_RootModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(GetRootModel());
    }

    if (m_RootModel != NULL)
    {
        // Obtient l'ensemble des pages contenues dans le contrôleur de modèles.
        PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = m_RootModel->GetPageSet();

        if (pSet != NULL)
        {
            PSS_ProcessGraphModelMdl::IProcessGraphPageIterator i(pSet);

            // On passe en revue toutes les pages enfants contenues dans le contrôleur de modèles.
            for (PSS_ProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
            {
                // Obtient le contrôleur de modèle de la page courante.
                PSS_ProcessGraphModelMdlBP* m_CurModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

                if (m_CurModel != NULL)
                {
                    // Obtient l'ensemble des symboles contenus dans le contrôleur de modèles.
                    CODComponentSet* pCompSet = m_CurModel->GetComponents();

                    if (pCompSet != NULL)
                    {
                        // On passe en revue toutes les symboles contenus dans le contrôleur de modèles.
                        for (int j = 0; j < pCompSet->GetSize(); ++j)
                        {
                            CODComponent* pComponent = pCompSet->GetAt(j);

                            // Contrôle que le composant soit valide, et identifie s'il s'agit d'un processus.
                            if (pComponent && ISA(pComponent, ZBBPProcessSymbol))
                            {
                                // Convertit le symbole.
                                ZBBPProcessSymbol* m_Process = dynamic_cast<ZBBPProcessSymbol*>(pComponent);

                                // Obtient le contrôleur de modèle du processus.
                                PSS_ProcessGraphModelMdlBP* m_ChildModel =
                                    dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_Process->GetModel());

                                // Appel récursif à NotifyNameChange, jusqu'à ce que toutes les pages des
                                // processus enfants aient été visitées.
                                NotifyNameChange(OldName, NewName, m_ChildModel);

                                // Indique au processus que le nom du livrable a changé.
                                m_Process->OnDeliverableNameChange(OldName, NewName);
                            }
                        }
                    }
                }
            }
        }
    }
}

// ******************************************* Fonctions de contrôle ****************************************

// Contrôle si le livrable est correctement initialisé et lié. Si ce n'est pas le cas, fixe la couleur à rouge.
void ZBDeliverableLinkSymbol::CheckDeliverableStatus()
{
    // Advise the owner model of symbol changes
    PSS_ProcessGraphModelMdl* pRootModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());

    if (pRootModel && pRootModel->IsInCutOperation())
    {
        return;
    }

    // Check the symbols attached to the deliverable
    CODSymbolComponent* pDst = GetFollowingSymbol();
    CODSymbolComponent* pSrc = GetEnteringSymbol();

    // Set the right symbol color only if the symbol is correctly connected
    ShowInError((pSrc && pDst) ? false : true);
}

bool ZBDeliverableLinkSymbol::CheckPropertyValue(ZBProperty&        Property,
                                                 CString&            value,
                                                 ZBPropertySet&    Properties)
{
    if (Property.GetCategoryID() == ZS_BP_PROP_QUANTITY && Property.GetItemID() == Z_NUMBER_YEAR)
    {
        // Check if the value entered is less than the sum of locked item
        double NewTotal = atol(value);

        if (NewTotal < m_Quantity.GetSumOfLockedNumbers())
        {
            // Warm the user and put back the old value
            PSS_MsgBox mBox;
            mBox.Show(IDS_LOCKEDTOTAL_GREATERINPUT, MB_OK);

            // Assign the oldvalue
            value.Format(_T("%f"), Property.GetValueDouble());
            return false;
        }

        return true;
    }

    return PSS_LinkSymbol::CheckPropertyValue(Property, value, Properties);
}

// **************************** Fonctions concernant la connexion à un symbole ******************************

// Cette fonction est appelée lorsque l'un des points d'attache du livrable est déplacé.
BOOL ZBDeliverableLinkSymbol::MovePort(CODPortComponent* pPort, const int nOffsetX, const int nOffsetY)
{
    BOOL RetValue = PSS_LinkSymbol::MovePort(pPort, nOffsetX, nOffsetY);

    // Check the status in order to set the right color
    CheckDeliverableStatus();

    return RetValue;
}

bool ZBDeliverableLinkSymbol::DoDoorProcedureConnection(ZBBPDoorSymbol*        pSrc,
                                                        ZBBPProcedureSymbol*    pDst,
                                                        CODModel*                pModel)
{
    // If the door is pointing to a model
    if (pModel && pSrc->GetChildModel() &&
        ISA(pSrc->GetChildModel(), PSS_ProcessGraphModelMdlBP) &&
        ISA(pModel, PSS_ProcessGraphModelMdlBP))
    {
        CODNodeArray Nodes;
        size_t ElementCount =
            dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pSrc->GetChildModel())->GetBPDoorSymbols(Nodes);

        for (size_t nNodeIdx = 0; nNodeIdx < ElementCount; ++nNodeIdx)
        {
            IODNode* pINode = Nodes.GetAt(nNodeIdx);
            ZBBPDoorSymbol* pComp = static_cast<ZBBPDoorSymbol*>(pINode);

            if (!pComp || !pComp->GetChildModel())
            {
                continue;
            }

            // If the door symbol contains a door with a model pointing to our model, we found it
            if (pComp->GetTwinDoorReferenceNumber() == pSrc->GetSymbolReferenceNumber())
            {
                CODEdgeArray EnteringEdges;
                size_t EnteringLinkCount = pComp->GetEdgesEntering_Up(EnteringEdges);

                if (EnteringLinkCount > 0)
                {
                    // Get the link
                    IODEdge* pIEdge = EnteringEdges.GetAt(0);
                    CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

                    if (!pLinkIndexed || !ISA(pLinkIndexed, ZBDeliverableLinkSymbol))
                    {
                        return false;
                    }

                    // Define as a reference
                    AssignReferenceSymbol(pLinkIndexed);
                }

                // Even if we found a link or not, return without error
                return true;
            }
        }
    }

    return true;
}

bool ZBDeliverableLinkSymbol::DoProcedureDoorConnection(ZBBPProcedureSymbol*    pSrc,
                                                        ZBBPDoorSymbol*        pDst,
                                                        CODModel*                pModel)
{
    // If the door is pointing to a model
    if (pModel && pDst->GetChildModel() &&
        ISA(pDst->GetChildModel(), PSS_ProcessGraphModelMdlBP) &&
        ISA(pModel, PSS_ProcessGraphModelMdlBP))
    {
        CODNodeArray Nodes;

        size_t ElementCount =
            dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDst->GetChildModel())->GetBPDoorSymbols(Nodes);

        for (size_t nNodeIdx = 0; nNodeIdx < ElementCount; ++nNodeIdx)
        {
            IODNode* pINode = Nodes.GetAt(nNodeIdx);
            ZBBPDoorSymbol* pComp = static_cast<ZBBPDoorSymbol*>(pINode);

            if (!pComp || !pComp->GetChildModel())
            {
                continue;
            }

            // If the door symbol contains a door with a model
            // pointing to our model, we found it
            if (pComp->GetTwinDoorReferenceNumber() == pDst->GetSymbolReferenceNumber())
            {
                CODEdgeArray LeavingEdges;
                size_t LeavingLinkCount = pComp->GetEdgesLeaving_Down(LeavingEdges);

                if (LeavingLinkCount > 0)
                {
                    // Get the link 
                    IODEdge* pIEdge = LeavingEdges.GetAt(0);
                    CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

                    if (!pLinkIndexed || !ISA(pLinkIndexed, ZBDeliverableLinkSymbol))
                    {
                        return false;
                    }

                    // Define as a reference
                    AssignReferenceSymbol(pLinkIndexed);
                }

                // Even if we found a link or not, return without error
                return true;
            }
        }
    }

    return true;
}

bool ZBDeliverableLinkSymbol::DoPageProcedureConnection(ZBBPPageSymbol*        pSrc,
                                                        ZBBPProcedureSymbol*    pDst,
                                                        CODModel*                pModel)
{
    // If the page is pointing to a model
    if (pModel && pSrc->GetModelPage() &&
        ISA(pSrc->GetModelPage(), PSS_ProcessGraphModelMdlBP) &&
        ISA(pModel, PSS_ProcessGraphModelMdlBP))
    {
        CODNodeArray Nodes;

        size_t ElementCount =
            dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pSrc->GetModelPage())->GetBPPageSymbols(Nodes);

        for (size_t nNodeIdx = 0; nNodeIdx < ElementCount; ++nNodeIdx)
        {
            IODNode* pINode = Nodes.GetAt(nNodeIdx);
            ZBBPPageSymbol* pComp = static_cast<ZBBPPageSymbol*>(pINode);

            if (!pComp || !pComp->GetModelPage())
            {
                continue;
            }

            // If the page symbol contains a page with a reference number
            // pointing to our, we found it
            if (pComp->GetTwinPageReferenceNumber() == pSrc->GetSymbolReferenceNumber())
            {
                CODEdgeArray EnteringEdges;
                size_t EnteringLinkCount = pComp->GetEdgesEntering_Up(EnteringEdges);

                if (EnteringLinkCount > 0)
                {
                    // Get the link
                    IODEdge* pIEdge = EnteringEdges.GetAt(0);
                    CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

                    if (!pLinkIndexed || !ISA(pLinkIndexed, ZBDeliverableLinkSymbol))
                    {
                        return false;
                    }

                    // Define as a reference
                    AssignReferenceSymbol(pLinkIndexed);
                }

                // Even if we found a link or not, return without error
                return true;
            }
        }
    }

    return true;
}

bool ZBDeliverableLinkSymbol::DoProcedurePageConnection(ZBBPProcedureSymbol*    pSrc,
                                                        ZBBPPageSymbol*        pDst,
                                                        CODModel*                pModel)
{
    // If the page is pointing to a model
    if (pModel && pDst->GetModelPage() &&
        ISA(pDst->GetModelPage(), PSS_ProcessGraphModelMdlBP) &&
        ISA(pModel, PSS_ProcessGraphModelMdlBP))
    {
        CODNodeArray Nodes;

        size_t ElementCount =
            dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDst->GetModelPage())->GetBPPageSymbols(Nodes);

        for (size_t nNodeIdx = 0; nNodeIdx < ElementCount; ++nNodeIdx)
        {
            IODNode* pINode = Nodes.GetAt(nNodeIdx);
            ZBBPPageSymbol* pComp = static_cast<ZBBPPageSymbol*>(pINode);

            if (!pComp || !pComp->GetModelPage())
            {
                continue;
            }

            // If the page symbol contains a page with a reference number
            // pointing to our, we found it
            if (pComp->GetTwinPageReferenceNumber() == pDst->GetSymbolReferenceNumber())
            {
                CODEdgeArray LeavingEdges;
                size_t LeavingLinkCount = pComp->GetEdgesLeaving_Down(LeavingEdges);

                if (LeavingLinkCount > 0)
                {
                    // Get the link 
                    IODEdge* pIEdge = LeavingEdges.GetAt(0);
                    CODLinkComponent* pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);

                    if (!pLinkIndexed || !ISA(pLinkIndexed, ZBDeliverableLinkSymbol))
                    {
                        return false;
                    }

                    // Define as a reference
                    AssignReferenceSymbol(pLinkIndexed);
                }

                // Even if we found a link or not, return without error
                return true;
            }
        }
    }

    return true;
}

bool ZBDeliverableLinkSymbol::DoProcessProcessConnection(ZBBPProcessSymbol*    pSrc,
                                                         ZBBPProcessSymbol*    pDst,
                                                         CODModel*                pModel)
{
    // Check if source and destination have child model
    // If the page is pointing to a model
    if (pModel && pSrc->GetChildModel() && pDst->GetChildModel() &&
        ISA(pSrc->GetChildModel(), PSS_ProcessGraphModelMdlBP) &&
        ISA(pDst->GetChildModel(), PSS_ProcessGraphModelMdlBP) &&
        ISA(pModel, PSS_ProcessGraphModelMdlBP))
    {
        // In the destination process, retreive all door symbols.
        // Go deeper.
        CODNodeArray Nodes;

        size_t ElementCount =
            dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDst->GetChildModel())->GetBPDoorSymbols(Nodes, true);

        for (size_t nNodeIdx = 0; nNodeIdx < ElementCount; ++nNodeIdx)
        {
            // For each door symbol, keep only entering up deliverable
            IODNode* pINode = Nodes.GetAt(nNodeIdx);
            ZBBPDoorSymbol* pComp = static_cast<ZBBPDoorSymbol*>(pINode);

            if (!pComp || !pComp->GetChildModel())
            {
                continue;
            }

            CODLinkComponent* pLinkIndexed = NULL;
            CODEdgeArray LeavingEdges;
            size_t LeavingLinkCount = pComp->GetEdgesLeaving_Down(LeavingEdges);

            // If entering link, check if it is a deliverable
            if (LeavingLinkCount > 0)
            {
                // Get the link 
                IODEdge* pIEdge = LeavingEdges.GetAt(0);
                pLinkIndexed = static_cast<CODLinkComponent*>(pIEdge);
            }

            // If no link or if not a deliverable, remove it from the array
            if (!pLinkIndexed || !ISA(pLinkIndexed, ZBDeliverableLinkSymbol))
            {
                // Remove it and decrement the index and the element count
                Nodes.RemoveAt(nNodeIdx--);
                --ElementCount;
            }
        }

        // If still door symbols available
        if (Nodes.GetSize() > 0)
        {
            ZBBPDoorSymbol* pDoorSelected = NULL;
            CODLinkComponent* pLinkSelected = NULL;

            // If we have more than one symbol,
            // asks the user to choose which one he would like to assign
            if (Nodes.GetSize() > 1)
            {
                // filter object classes
                PSS_RuntimeClassSet rtClasses;
                rtClasses.Add(RUNTIME_CLASS(ZBBPPageSymbol));
                rtClasses.Add(RUNTIME_CLASS(ZBBPProcessSymbol));
                rtClasses.Add(RUNTIME_CLASS(ZBDeliverableLinkSymbol));

                PSS_SelectModelSymbolDlg Dlg(dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDst->GetChildModel()),
                                             IDS_SYMBOL_SELECTDELIVERABLE,
                                             RUNTIME_CLASS(ZBDeliverableLinkSymbol),
                                             &rtClasses);

                if (Dlg.DoModal() == IDOK)
                    if (Dlg.GetSelectedSymbol() && ISA(Dlg.GetSelectedSymbol(), ZBDeliverableLinkSymbol))
                        pLinkSelected = dynamic_cast<ZBDeliverableLinkSymbol*>(Dlg.GetSelectedSymbol());
            }
            else
            {
                // Otherwise, select the first door symbol
                IODNode* pINode = Nodes.GetAt(0);
                pDoorSelected = static_cast<ZBBPDoorSymbol*>(pINode);
            }

            // If no door selected and no link selected, display warning message
            // and select the first door
            if (!pDoorSelected && !pLinkSelected)
            {
                PSS_MsgBox mBox;
                mBox.Show(IDS_P2P_FIRSTDELIVERABLE_SELECTED, MB_OK);
                IODNode* pINode = Nodes.GetAt(0);
                pDoorSelected = static_cast<ZBBPDoorSymbol*>(pINode);
            }

            // If no link selected
            if (!pLinkSelected)
            {
                if (!pDoorSelected || !pDoorSelected->GetChildModel())
                {
                    return false;
                }

                CODEdgeArray LeavingEdges;
                size_t LinkCount = pDoorSelected->GetEdgesLeaving_Down(LeavingEdges);

                if (LinkCount > 0)
                {
                    // Get the link
                    IODEdge* pIEdge = LeavingEdges.GetAt(0);
                    pLinkSelected = static_cast<CODLinkComponent*>(pIEdge);
                }
            }

            if (!pLinkSelected || !ISA(pLinkSelected, ZBDeliverableLinkSymbol))
            {
                return true;
            }

            // Define as a reference
            AssignReferenceSymbol(pLinkSelected);
        }
    }

    return true;
}

bool ZBDeliverableLinkSymbol::CanEditNonDynamicName() const
{
    return true;

}
bool ZBDeliverableLinkSymbol::AcceptExtApp() const
{
    CODModel * pModel = const_cast<ZBDeliverableLinkSymbol*>(this)->GetRootModel();

    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
        dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetUseWorkflow())
    {
        return true;
    }

    // RS-MODIF 11.12.04 Ext App should appear in conceptor
    return true;
}

bool ZBDeliverableLinkSymbol::AcceptExtFile() const
{
    CODModel * pModel = const_cast<ZBDeliverableLinkSymbol*>(this)->GetRootModel();

    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
        dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetUseWorkflow())
    {
        return true;
    }

    // RS-MODIF 11.12.04 Ext File should appear in conceptor
    return true;
}

bool ZBDeliverableLinkSymbol::ProcessExtendedInput(ZBProperty&        Property,
                                                   CString&        value,
                                                   ZBPropertySet&    Properties,
                                                   bool&            Refresh)
{
    // ****************************************************************************************************
    // JMR-MODIF - Le 13 juin 2007 - Ajout de la prise en charge des risques.

    if (Property.GetCategoryID() >= ZS_BP_PROP_RISK &&
        Property.GetCategoryID() <= ZS_BP_PROP_RISK + GetRiskCount())
    {
        int            i = Property.GetCategoryID() - ZS_BP_PROP_RISK;
        CODModel*    pModel = GetRootModel();
        CString        CurrencySymbol = PSS_Global::GetLocaleCurrency();

        if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl))
        {
            CDocument* pDoc = dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetDocument();

            if (pDoc && ISA(pDoc, PSS_ProcessGraphModelDoc))
            {
                // Retrieve the model's currency symbol
                CurrencySymbol = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetCurrencySymbol();
            }
        }

        CString s_NoRiskType = _T("");
        s_NoRiskType.LoadString(IDS_NO_RISK_TYPE);

        ZVRiskOptionsDlg m_RiskOptions(GetRiskName(i),
                                       GetRiskDesc(i),
                                       (GetRiskType(i).IsEmpty()) ? s_NoRiskType : GetRiskType(i),
                                       GetRiskImpact(i),
                                       GetRiskProbability(i),
                                       GetRiskUE(i),
                                       GetRiskPOA(i),
                                       GetRiskAction(i),
                                       CurrencySymbol);

        if (m_RiskOptions.DoModal() == IDOK)
        {
            SetRiskName(i, m_RiskOptions.GetRiskTitle());
            SetRiskDesc(i, m_RiskOptions.GetRiskDescription());
            SetRiskType(i, m_RiskOptions.GetRiskType());
            SetRiskImpact(i, m_RiskOptions.GetRiskImpact());
            SetRiskProbability(i, m_RiskOptions.GetRiskProbability());
            SetRiskSeverity(i, m_RiskOptions.GetRiskSeverity());
            SetRiskUE(i, m_RiskOptions.GetRiskUE());
            SetRiskPOA(i, m_RiskOptions.GetRiskPOA());
            SetRiskAction(i, m_RiskOptions.GetRiskAction());

            SetModifiedFlag(TRUE);

            Refresh = true;

            return true;
        }
    }
    // ****************************************************************************************************

    CODModel * pModel = GetOwnerModel();

    if (Property.GetCategoryID() == ZS_BP_PROP_UNIT && Property.GetItemID() == Z_UNIT_NAME)
    {
        if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl))
        {
            PSS_SelectUserGroupDlg dlg(IDS_SELECTAGROUP_T,
                                       dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetMainUserGroup(),
                                       true,        // Allow group selection
                                       false);    // Doesn't allow role selection

            if (dlg.DoModal() == IDOK)
            {
                PSS_UserEntity* pUserEntity = dlg.GetSelectedUserEntity();

                if (pUserEntity)
                {
                    value = pUserEntity->GetEntityName();

                    // And change the unit GUID of the disable property
                    ZBPropertyIterator i(&Properties);
                    ZBProperty* pProp;

                    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
                    {
                        if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT && pProp->GetItemID() == Z_UNIT_GUID)
                        {
                            pProp->SetValueString(pUserEntity->GetGUID());
                            break;
                        }
                    }

                    return true;
                }
            }
        }
    }
    else if (Property.GetCategoryID() == ZS_BP_PROP_QUANTITY &&
             Property.GetItemID() == Z_NUMBER_YEAR)
    {
        // Sets the new value and equalize the information
        m_Quantity.SetAndCalculateQuantitiesBasedOnYear(Property.GetValueDouble());

        // Now saves the equalizer value to the properties to avoid
        // working with wrong figures in the equalizer
        SaveEqualizerToProperties(Properties);
        ZVEqualizeQuantityDlg Equalize(&Properties);

        if (Equalize.DoModal() == IDOK)
        {
            value.Format(_T("%.0f"), Equalize.GetfQuantityYear());

            SavePropertiesToQuantity(Properties);
            return true;
        }
    }

    return PSS_LinkSymbol::ProcessExtendedInput(Property, value, Properties, Refresh);
}

// JMR-MODIF - Le 28 novembre 2006 - Ajout de la fonction ProcessMenuCommand.
bool ZBDeliverableLinkSymbol::ProcessMenuCommand(int                MenuCommand,
                                                 ZBProperty&        Property,
                                                 CString&            value,
                                                 ZBPropertySet&    Properties,
                                                 bool&                Refresh)
{
    // ************************************************************************************************************
    // JMR-MODIF - Le 10 juin - Ajout du code pour traitement du menu des risques.

    if (Property.GetCategoryID() >= ZS_BP_PROP_RISK &&
        Property.GetCategoryID() <= ZS_BP_PROP_RISK + GetRiskCount())
    {
        switch (MenuCommand)
        {
            case ID_ADD_NEWRISK:
            {
                OnAddNewRisk(Property, value, Properties, Refresh);
                break;
            }

            case ID_DEL_CURRENTRISK:
            {
                OnDelCurrentRisk(Property, value, Properties, Refresh);
                break;
            }

            default:
            {
                break;
            }
        }

        return true;
    }
    // ************************************************************************************************************

    if (Property.GetCategoryID() == ZS_BP_PROP_RULES)
    {
        switch (MenuCommand)
        {
            case ID_DEL_CURRENTRULE:
            {
                int Index = (Property.GetItemID() - Z_RULE_NAME) / _MaxRulesSize;

                m_Rules.DeleteRule(Index);

                // JMR-MODIF - Le 8 mai 2007 - Demande le rafraîchissement après exécution de l'opération.
                Refresh = true;

                break;
            }

            default:
            {
                break;
            }
        }
    }

    return PSS_LinkSymbol::ProcessMenuCommand(MenuCommand, Property, value, Properties, Refresh);
}

// JMR-MODIF - Le 10 juin 2007 - Ajout de la fonction OnAddNewRisk.
void ZBDeliverableLinkSymbol::OnAddNewRisk(ZBProperty&        Property,
                                           CString&        value,
                                           ZBPropertySet&    Properties,
                                           bool&            Refresh)
{
    // Add a new risk
    if (AddNewRisk() >= 0)
    {
        // Sets the refresh flag to true
        Refresh = true;
        SetModifiedFlag(TRUE);
    }
}

// JMR-MODIF - Le 10 juin 2007 - Ajout de la fonction OnDelCurrentRisk.
void ZBDeliverableLinkSymbol::OnDelCurrentRisk(ZBProperty&        Property,
                                               CString&        value,
                                               ZBPropertySet&    Properties,
                                               bool&            Refresh)
{
    int Count = GetRiskCount();

    if (Count <= 1)
    {
        // Cannot delete all risks
        PSS_MsgBox mBox;
        mBox.Show(IDS_CANNOTDELETE_ALLRISKS, MB_OK);
        return;
    }

    // Otherwise, delete the current selected risk
    int Index = Property.GetCategoryID() - ZS_BP_PROP_RISK;

    if (DeleteRisk(Index))
    {
        // Sets the refresh flag to true
        Refresh = true;
        SetModifiedFlag(TRUE);
    }
}

// ************************************ Fonctions concernant les Règles *************************************

bool ZBDeliverableLinkSymbol::RuleExist(const CString Value)
{
    PSS_Tokenizer token(GetRuleList());    // Initialize the token with the task list
                                        // and with the default ; as separator

    return (token.TokenExist(Value) == TRUE) ? true : false;
}

void ZBDeliverableLinkSymbol::AddRule(const CString Value)
{
    PSS_Tokenizer token(GetRuleList());    // Initialize the token with the task list
                                        // and with the default ; as separator

    // If the new task has been added correctly,
    // then set the new task list
    if (token.AddUniqueToken(Value))
    {
        // Add the value to the history
        CString Key;
        Key.LoadString(IDS_ZS_BP_PROP_RULELST_TITLE);
        PSS_Global::GetHistoricValueManager().AddHistoryValue(Key, Value);

        // Set the new task string
        SetRuleList(token.GetString());
    }
}

void ZBDeliverableLinkSymbol::RemoveRule(const CString Value)
{
    PSS_Tokenizer token(GetRuleList());    // Initialize the token with the task list
                                        // and with the default ; as separator

    // If the new task has been removed correctly,
    // then set the new task list
    if (token.RemoveToken(Value))
    {
        SetRuleList(token.GetString());
    }
}

// ************************************ Fonctions concernant les Items **************************************

bool ZBDeliverableLinkSymbol::TextItemExist(const CString Value)
{
    PSS_Tokenizer token(GetTextItemList());    // Initialize the token with the list
                                            // and with the default ; as separator

    return (token.TokenExist(Value) == TRUE) ? true : false;
}

void ZBDeliverableLinkSymbol::AddTextItem(const CString Value)
{
    PSS_Tokenizer token(GetTextItemList());    // Initialize the token with the list
                                            // and with the default ; as separator

    // If the new task has been added correctly,
    // then set the new list
    if (token.AddUniqueToken(Value))
    {
        // Add the value to the history
        CString Key;
        Key.LoadString(IDS_ZS_BP_PROP_PROCEDURE_ITMTXTLST_TITLE);
        PSS_Global::GetHistoricValueManager().AddHistoryValue(Key, Value);

        // Set the new list string
        SetTextItemList(token.GetString());
    }
}

void ZBDeliverableLinkSymbol::RemoveTextItem(const CString Value)
{
    PSS_Tokenizer token(GetTextItemList());    // Initialize the token with the list
                                            // and with the default ; as separator

    // If the new task has been removed correctly,
    // then set the new list
    if (token.RemoveToken(Value))
    {
        SetTextItemList(token.GetString());
    }
}

// **************************** Fonctions concernant les propriétés du symbole ******************************

bool ZBDeliverableLinkSymbol::CreateSymbolProperties()
{
    if (!PSS_LinkSymbol::CreateSymbolProperties())
    {
        return false;
    }

    ZBBPRuleListProperties propRules;
    AddProperty(propRules);

    ZBBPTextItemListProperties textItemList;
    AddProperty(textItemList);

    PSS_CostPropertiesDeliverableBP propCost;
    AddProperty(propCost);

    // Fill the array of unit double validation type
    m_UnitDoubleValidationTypeArray.RemoveAll();
    GetUnitDoubleValidationTypeStringArray(m_UnitDoubleValidationTypeArray);

    // JMR-MODIF - Le 3 juin 2007 - Ajoute au moins un catalogue de propriétés dans les risques.
    m_Risks.CreateInitialProperties();

    return true;
}

// JMR-MODIF - Le 26 avril 2007 - Cette fonction permet de déterminer si une règle donnée a été attribuée à cet objet.
BOOL ZBDeliverableLinkSymbol::ContainsRule(CString RuleName)
{
    for (int i = 0; i < m_Rules.GetRulesCount(); i++)
    {
        if (m_Rules.GetRuleName(i) == RuleName)
        {
            return TRUE;
        }
    }

    return FALSE;
}

// JMR-MODIF - Le 9 octobre 2007 - Cette fonction retourne les règles qui ne sont plus synchronisées avec le référentiel.
void ZBDeliverableLinkSymbol::CheckRulesSync(CStringArray& RulesList)
{
    CODModel * pModel = GetRootModel();

    if (pModel == NULL)
    {
        return;
    }

    if (m_Rules.GetRulesCount() > 0)
    {
        PSS_LogicalRulesEntity* p_MainRule = NULL;

        if (GetOwnerModel() != NULL && ISA(GetOwnerModel(), PSS_ProcessGraphModelMdlBP))
        {
            PSS_ProcessGraphModelMdlBP* p_Model = reinterpret_cast<PSS_ProcessGraphModelMdlBP*>(GetOwnerModel());

            p_MainRule = p_Model->GetMainLogicalRules();
        }
        else
        {
            return;
        }

        for (int i = 0; i < m_Rules.GetRulesCount(); i++)
        {
            CString m_SafeName = GetRuleNameByGUID(p_MainRule, m_Rules.GetRuleGUID(i));

            if (m_SafeName.IsEmpty())
            {
                RulesList.Add(m_Rules.GetRuleName(i));
            }
        }
    }
}
//---------------------------------------------------------------------------
bool ZBDeliverableLinkSymbol::FillProperties(ZBPropertySet& propSet, bool numericValue, bool groupValue)
{
    CODModel * pModel = GetRootModel();

    // if no file, add new one
    if (!GetExtFileCount())
        AddNewExtFile();

    // FIXME translate comments
    // Les propriétés "Nom", "Description" et "Référence" du groupe "General" sont affichées par la classe de base.
    // La classe de base affiche également les propriétés des groupes "Liens externes" et "Fichiers externes",
    // ainsi que les propriétés dynamiques.
    if (!PSS_LinkSymbol::FillProperties(propSet, numericValue, groupValue))
        return false;

    // FIXME translate comments
    // Seuls les symboles locaux ont accès aux propriétés.
    if (!IsLocal())
        return true;

    // initialize the Currency symbol with the user local currency symbol defined in the Control Panel
    CString currencySymbol = PSS_Global::GetLocaleCurrency();

    // FIXME translate comments
    // JMR-MODIF - Le 30 juillet 2007 - Mets à jour le symbole monétaire en fonction de la sélection utilisateur.
    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl))
    {
        CDocument* pDoc = dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetDocument();

        if (pDoc && ISA(pDoc, PSS_ProcessGraphModelDoc))
            // retreive the model's currency symbol
            currencySymbol = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetCurrencySymbol();
    }

    int     count;
    CString sValue;
    CString finalPropName;
    CString propTitle;
    CString propName;
    CString propDesc;
    bool    groupEnabled = true;

    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
        !dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->MainUserGroupIsValid())
        groupEnabled = false;

    // ************************************************************************************************************
    // JMR-MODIF - Le 22 novembre 2006 - Nouvelle architecture des règles.

    // if the menu is not loaded, load it
    if (!gRulesMenu.GetSafeHmenu())
        gRulesMenu.LoadMenu(IDR_RULES_MENU);

    if (m_Rules.GetRulesCount() > 0)
    {
        CString ruleSectionTitle = _T("");
        CString ruleName = _T("");
        CString ruleDesc = _T("");

        ruleSectionTitle.LoadString(IDS_Z_RULES_TITLE);
        ruleDesc.LoadString(IDS_Z_RULES_DESC);

        PSS_LogicalRulesEntity* pMainRule = NULL;

        if (GetOwnerModel() && ISA(GetOwnerModel(), PSS_ProcessGraphModelMdlBP))
        {
            PSS_ProcessGraphModelMdlBP* pOwnerModel = reinterpret_cast<PSS_ProcessGraphModelMdlBP*>(GetOwnerModel());

            if (pOwnerModel && pOwnerModel->GetController() && ISA(pOwnerModel->GetController(), PSS_ProcessGraphModelControllerBP))
            {
                PSS_ProcessGraphModelControllerBP* pController =
                    reinterpret_cast<PSS_ProcessGraphModelControllerBP*>(pOwnerModel->GetController());

                if (pController && ISA(pController->GetDocument(), PSS_ProcessGraphModelDoc))
                {
                    PSS_ProcessGraphModelDoc* pDocument =
                        reinterpret_cast<PSS_ProcessGraphModelDoc*>(pController->GetDocument());

                    if (pDocument && pDocument->GetMainLogicalRules())
                        pMainRule = pDocument->GetMainLogicalRules();
                }
            }
        }

        for (int i = 0; i < m_Rules.GetRulesCount(); ++i)
        {
            // FIXME translate comments
            // Le contrôle des règles ne peut être appliqué que si le modèle est en phase avec le système des règles.
            if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
                dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->MainLogicalRulesIsValid())
            {
                CString safeName = GetRuleNameByGUID(pMainRule, m_Rules.GetRuleGUID(i));

                // FIXME translate comments
                // ********************************************************************************************
                // JMR-MODIF - Le 8 octobre 2007 - Rééctriture de la routine suite à un bug de perte de règles.
                // Avant, le test supprimait une règle qui n'était plus synchronisée au référentiel, maintenant
                // seul le nom de la règle est contrôlé et renommé, à condition qu'il soit synchronisé avec le
                // référentiel.
                /*
                if ( m_SafeName.IsEmpty() )
                {
                    m_Rules.DeleteRule( i );
                }
                else if ( m_SafeName != m_Rules.GetRuleName( i ) )
                {
                    m_Rules.SetRuleName( i, m_SafeName );
                }
                */

                if (!safeName.IsEmpty() && safeName != m_Rules.GetRuleName(i))
                    m_Rules.SetRuleName(i, safeName);
                // ********************************************************************************************
            }

            ruleName.Format(IDS_Z_RULES_NAME, i + 1);

            // FIXME translate comments
            // Propriété "Règle x" du groupe "Règles"
            ZBProperty* pRule = new ZBProperty(ruleSectionTitle,
                                               ZS_BP_PROP_RULES,
                                               ruleName,
                                               Z_RULE_NAME + (i * _MaxRulesSize),
                                               ruleDesc,
                                               m_Rules.GetRuleName(i),
                                               ZBProperty::PT_EDIT_MENU,
                                               true,
                                               PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                               NULL,
                                               &gRulesMenu);

            pRule->EnableDragNDrop();
            propSet.Add(pRule);
        }
    }
    // ************************************************************************************************************

    // FIXME translate comments
    // ************************************************************************************************************
    // JMR-MODIF - Le 22 novembre 2006 - ATTENTION : L'ancienne architecture de règles ci-dessous a maintenant
    // changé, et est désignée sous le terme de contrôle, car celle-ci était devenue obsolète après la nouvelle
    // implémentation du système de règles datant de novembre 2006. Mais les deux architectures étant trop
    // différentes l'une de l'autre, il a fallu faire cohabiter les deux pour des raisons de compatibilité avec les
    // anciens fichiers. Cependant, les textes concernant l'ancienne architecture ont été corrigés, et les termes
    // "règles" ont été remplacés par les termes "Contrôles" dans les ressources de textes. Toutefois, les autres
    // corrections étaient trop importantes pour être appliquées au code, ce qui provoque une ambiguité dans le nom
    // des classes et des ressources. Si une nouvelle modification doit être approtée à l'architecture des contrôles
    // il faut donc le faire avec la plus grande prudence.

    // add rules
    ZBBPRuleListProperties* pRulesProps;

    // FIXME translate comments
    // Obtention des données pour l'affichage des règles.
    if ((pRulesProps = (ZBBPRuleListProperties*)GetProperty(ZS_BP_PROP_RULELIST)) == NULL)
    {
        // try to add it
        ZBBPRuleListProperties propRules;
        AddProperty(propRules);

        // retreive it
        pRulesProps = (ZBBPRuleListProperties*)GetProperty(ZS_BP_PROP_RULELIST);

        if (!pRulesProps)
            return false;
    }

    // run through all tasks properties, add one to the counter to have always one empty task
    count = GetRuleCount() + 1;
    propTitle.LoadString(IDS_ZS_BP_PROP_RULELST_TITLE);
    CStringArray* pArrayOfValues = PSS_Global::GetHistoricValueManager().GetFieldHistory(propTitle);

    propName.LoadString(IDS_Z_RULE_LIST_NAME);
    propDesc.LoadString(IDS_Z_RULE_LIST_DESC);

    int index = 0;

    for (int i = 0; i < count; ++i)
    {
        index = i;

        finalPropName.Format(_T("%s %d"), propName, i + 1);

        // FIXME translate comments
        // Propriété "Règle x" du groupe "Règles"
        ZBProperty* pRuleList = new ZBProperty(propTitle,
                                               ZS_BP_PROP_RULELIST,
                                               finalPropName,
                                               Z_RULE_LIST + (i * _MaxRuleListSize),
                                               propDesc,
                                               GetRuleAt(i),
                                               ZBProperty::PT_EDIT_INTELI,
                                               true, // Enable
                                               PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                               pArrayOfValues);

        pRuleList->EnableDragNDrop();
        propSet.Add(pRuleList);
    }

    // now continue to add empty tasks till the maximum size
    for (int i = index; i < _MaxRuleListSize; ++i)
    {
        finalPropName.Format(_T("%s %d"), propName, i + 1);

        // FIXME translate comments
        // Propriété "Règle x" du groupe "Règles"
        ZBProperty* pRuleList = new ZBProperty(propTitle,
                                               ZS_BP_PROP_RULELIST,
                                               finalPropName,
                                               Z_RULE_LIST + (i * _MaxRuleListSize),
                                               propDesc,
                                               _T(""),
                                               ZBProperty::PT_EDIT_INTELI,
                                               false, // Disable
                                               PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                               pArrayOfValues);

        pRuleList->EnableDragNDrop();
        propSet.Add(pRuleList);
    }
    // ************************************************************************************************************

    // FIXME translate comments
    // ***********************************************************************************************************
    // JMR-MODIF - Le 3 juin 2007 - Ajout des propriétés liées aux risques.

    // FIXME translate comments
    // Obtient le menu des risques si celui-ci n'est pas encore présent.
    if (!gRiskMenu.GetSafeHmenu())
        gRiskMenu.LoadMenu(IDR_RISK_MENU);

    CString finalRiskName = _T("");
    CString finalRiskTitle = _T("");
    CString riskTitle = _T("");
    CString riskName = _T("");
    CString riskDesc = _T("");

    riskTitle.LoadString(IDS_ZS_BP_PROP_RISK_TITLE);

    index = 0;

    for (int i = 0; i < GetRiskCount(); ++i)
    {
        index = i;

        finalRiskTitle.Format(_T("%s (%d)"), riskTitle, i + 1);

        riskName.LoadString(IDS_Z_RISK_NAME_NAME);
        riskDesc.LoadString(IDS_Z_RISK_NAME_DESC);

        // FIXME translate comments
        // Propriété "Titre Risque" du groupe "Risque (x)"
        ZBProperty* pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                                           riskName,
                                           (groupValue ? Z_RISK_NAME : (Z_RISK_NAME + (i * _MaxRisksSize))),
                                           riskDesc,
                                           GetRiskName(i),
                                           ZBProperty::PT_EDIT_MENU,
                                           true,
                                           PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                           NULL,
                                           &gRiskMenu);

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_DESC_NAME);
        riskDesc.LoadString(IDS_Z_RISK_DESC_DESC);

        // FIXME translate comments
        // Propriété "Description" du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? Z_RISK_DESC : (Z_RISK_DESC + (i * _MaxRisksSize))),
                               riskDesc,
                               GetRiskDesc(i),
                               ZBProperty::PT_EDIT_EXTENDED);

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_TYPE_NAME);
        riskDesc.LoadString(IDS_Z_RISK_TYPE_DESC);

        CString sNoRiskType = _T("");
        sNoRiskType.LoadString(IDS_NO_RISK_TYPE);

        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? Z_RISK_TYPE : (Z_RISK_TYPE + (i * _MaxRisksSize))),
                               riskDesc,
                               GetRiskType(i).IsEmpty() ? sNoRiskType : GetRiskType(i),
                               ZBProperty::PT_EDIT_EXTENDED_READONLY);

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_IMPACT_NAME);
        riskDesc.LoadString(IDS_Z_RISK_IMPACT_DESC);

        // FIXME translate comments
        // Propriété "Impact" du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? Z_RISK_IMPACT : (Z_RISK_IMPACT + (i * _MaxRisksSize))),
                               riskDesc,
                               PSS_Application::Instance()->GetMainForm()->GetRiskImpactContainer()->GetElementAt(GetRiskImpact(i)),
                               ZBProperty::PT_EDIT_EXTENDED_READONLY);

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_PROBABILITY_NAME);
        riskDesc.LoadString(IDS_Z_RISK_PROBABILITY_DESC);

        // FIXME translate comments
        // Propriété "Probabilité" du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? Z_RISK_PROBABILITY : (Z_RISK_PROBABILITY + (i * _MaxRisksSize))),
                               riskDesc,
                               PSS_Application::Instance()->GetMainForm()->GetRiskProbabilityContainer()->GetElementAt(GetRiskProbability(i)),
                               ZBProperty::PT_EDIT_EXTENDED_READONLY);

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_SEVERITY_NAME);
        riskDesc.LoadString(IDS_Z_RISK_SEVERITY_DESC);

        // FIXME translate comments
        // Propriété "Sévérité" du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? Z_RISK_SEVERITY : (Z_RISK_SEVERITY + (i * _MaxRisksSize))),
                               riskDesc,
                               double(GetRiskSeverity(i)),
                               ZBProperty::PT_EDIT_NUMBER_READONLY);

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_UE_NAME);
        riskDesc.LoadString(IDS_Z_RISK_UE_DESC);

        // FIXME translate comments
        // Propriété "Est. unit." du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? Z_RISK_UE : (Z_RISK_UE + (i * _MaxRisksSize))),
                               riskDesc,
                               GetRiskUE(i),
                               ZBProperty::PT_EDIT_NUMBER,
                               true,
                               PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol));

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_POA_NAME);
        riskDesc.LoadString(IDS_Z_RISK_POA_DESC);

        // FIXME translate comments
        // Propriété "POA" du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? Z_RISK_POA : (Z_RISK_POA + (i * _MaxRisksSize))),
                               riskDesc,
                               GetRiskPOA(i),
                               ZBProperty::PT_EDIT_NUMBER,
                               true,
                               PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol));

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_ACTION_NAME);
        riskDesc.LoadString(IDS_Z_RISK_ACTION_DESC);

        // FIXME translate comments
        // Propriété "Action" du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? Z_RISK_ACTION : (Z_RISK_ACTION + (i * _MaxRisksSize))),
                               riskDesc,
                               (GetRiskAction(i) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()),
                               ZBProperty::PT_COMBO_STRING_READONLY,
                               TRUE,
                               PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                               PSS_Global::GetArrayYesNo());

        propSet.Add(pRisk);
    }
    // ***********************************************************************************************************

    // text item list
    ZBBPTextItemListProperties* pTextItemProps = (ZBBPTextItemListProperties*)GetProperty(ZS_BP_PROP_TEXTITEMLIST);

    if (!pTextItemProps)
        return false;

    // run through all text items property, add one to the counter to have always one empty item
    count = GetTextItemCount() + 1;
    propTitle.LoadString(IDS_ZS_BP_PROP_PROCEDURE_ITMTXTLST_TITLE);
    pArrayOfValues = PSS_Global::GetHistoricValueManager().GetFieldHistory(propTitle);

    propName.LoadString(IDS_Z_TEXTITEM_LIST_NAME);
    propDesc.LoadString(IDS_Z_TEXTITEM_LIST_DESC);

    index = 0;

    for (int i = 0; i < count; ++i)
    {
        index = i;

        finalPropName.Format(_T("%s %d"), propName, i + 1);

        // FIXME translate comments
        // Propriété "Information x" du groupe "Liste des informations"
        ZBProperty* pTextList = new ZBProperty(propTitle,
                                               ZS_BP_PROP_TEXTITEMLIST,
                                               finalPropName,
                                               Z_TEXTITEM_LIST + (i * _MaxTextItemListSize),
                                               propDesc,
                                               GetTextItemAt(i),
                                               ZBProperty::PT_EDIT_INTELI,
                                               true, // Enable
                                               PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                               pArrayOfValues);

        pTextList->EnableDragNDrop();
        propSet.Add(pTextList);
    }

    // now continue to add empty tasks till the maximum size
    for (int i = index; i < _MaxTextItemListSize; ++i)
    {
        finalPropName.Format(_T("%s %d"), propName, i + 1);

        // FIXME translate comments
        // Propriété "Information x" du groupe "Liste des informations"
        ZBProperty* pTextList = new ZBProperty(propTitle,
                                               ZS_BP_PROP_TEXTITEMLIST,
                                               finalPropName,
                                               Z_TEXTITEM_LIST + (i * _MaxTextItemListSize),
                                               propDesc,
                                               _T(""),
                                               ZBProperty::PT_EDIT_INTELI,
                                               false, // Disable
                                               PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                               pArrayOfValues);

        pTextList->EnableDragNDrop();
        propSet.Add(pTextList);
    }

    int hourPerDay = -1;
    int dayPerWeek = -1;
    int dayPerMonth = -1;
    int dayPerYear = -1;

    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl))
    {
        CDocument* pDoc = dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetDocument();

        if (pDoc && ISA(pDoc, PSS_ProcessGraphModelDoc))
        {
            // FIXME translate comments
            // JMR-MODIF - Le 30 juillet 2007 - Cette opération est effectuée une fois pour toutes au début de la fonction.
            // Retrieve the model's currency symbol
            //CurrencySymbol = dynamic_cast<PSS_ProcessGraphModelDoc*>( pDoc )->GetCurrencySymbol();

            // todo FIXME -cFeature -oJean: please cast once and reuse the same pointer!!!
            // retreive the standard time definition
            hourPerDay = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetHourPerDay();
            dayPerWeek = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetDayPerWeek();
            dayPerMonth = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetDayPerMonth();
            dayPerYear = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetDayPerYear();
        }
    }

    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
        dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetIntegrateCostSimulation())
    {
        ZBProperty* pTime;

        if (numericValue)
            // FIXME translate comments
            // Propriété "Temps standard" du groupe "Livrable"
            pTime = new ZBProperty(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                   ZS_BP_PROP_DELIVERABLE_COST,
                                   IDS_Z_COST_PROCESSING_TIME_NAME,
                                   Z_COST_PROCESSING_TIME,
                                   IDS_Z_COST_PROCESSING_TIME_DESC,
                                   GetProcessingTime(),
                                   ZBProperty::PT_EDIT_NUMBER);
        else
            // FIXME translate comments
            // Propriété "Temps standard" du groupe "Livrable"
            pTime = new ZBProperty(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                   ZS_BP_PROP_DELIVERABLE_COST,
                                   IDS_Z_COST_PROCESSING_TIME_NAME,
                                   Z_COST_PROCESSING_TIME,
                                   IDS_Z_COST_PROCESSING_TIME_DESC,
                                   PSS_Duration(GetProcessingTime(),
                                                hourPerDay,
                                                dayPerWeek,
                                                dayPerMonth,
                                                dayPerYear),
                                   ZBProperty::PT_EDIT_DURATION,
                                   true,
                                   PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7));

        propSet.Add(pTime);
    }

    // FIXME translate comments
    // JMR-MODIF - Le 14 mars 2006 - La propriété "% en sortie" n'est plus dépendante de Sesterces.
    // Propriété "% en sortie" du groupe "Livrable"
    ZBProperty* pOutPercent = new ZBProperty(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                             ZS_BP_PROP_DELIVERABLE_COST,
                                             IDS_Z_COST_OUT_WORKLOAD_PERCENT_NAME,
                                             Z_COST_OUT_WORKLOAD_PERCENT,
                                             IDS_Z_COST_OUT_WORKLOAD_PERCENT_DESC,
                                             GetOutWorkloadPercent(),
                                             ZBProperty::PT_EDIT_NUMBER,
                                             true, // Enable
                                             PSS_StringFormat(PSS_StringFormat::IE_FT_Percentage));

    propSet.Add(pOutPercent);

    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
        dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetIntegrateCostSimulation())
    {
        // FIXME translate comments
        // Propriété "Coût unitaire" du groupe "Livrable"
        ZBProperty* pPrice = new ZBProperty(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                            ZS_BP_PROP_DELIVERABLE_COST,
                                            IDS_Z_COST_UNITARY_COST_NAME,
                                            Z_COST_UNITARY_COST,
                                            IDS_Z_COST_UNITARY_COST_DESC,
                                            GetUnitaryCost(),
                                            ZBProperty::PT_EDIT_NUMBER,
                                            true,
                                            PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol));

        propSet.Add(pPrice);

        ZBProperty* pCaseDuration;

        if (numericValue)
            // FIXME translate comments
            // Propriété "Age du cas (pondéré)" du groupe "Livrable"
            pCaseDuration = new ZBProperty(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                           ZS_BP_PROP_DELIVERABLE_COST,
                                           IDS_Z_COST_CASE_DURATION_NAME,
                                           Z_COST_CASE_DURATION,
                                           IDS_Z_COST_CASE_DURATION_DESC,
                                           GetCaseDuration(),
                                           ZBProperty::PT_EDIT_NUMBER);
        else
            // FIXME translate comments
            // Propriété "Age du cas (pondéré)" du groupe "Livrable"
            pCaseDuration = new ZBProperty(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                           ZS_BP_PROP_DELIVERABLE_COST,
                                           IDS_Z_COST_CASE_DURATION_NAME,
                                           Z_COST_CASE_DURATION,
                                           IDS_Z_COST_CASE_DURATION_DESC,
                                           PSS_Duration(GetCaseDuration(),
                                                        hourPerDay,
                                                        dayPerWeek,
                                                        dayPerMonth,
                                                        dayPerYear),
                                           ZBProperty::PT_EDIT_DURATION_READONLY,
                                           true,
                                           PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7));

        propSet.Add(pCaseDuration);

        ZBProperty* pCaseDurationMax;

        if (numericValue)
            // FIXME translate comments
            // Propriété "Age du cas (maximum)" du groupe "Livrable"
            pCaseDurationMax = new ZBProperty(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                              ZS_BP_PROP_DELIVERABLE_COST,
                                              IDS_Z_COST_CASE_DURATIONMAX_NAME,
                                              Z_COST_CASE_DURATIONMAX,
                                              IDS_Z_COST_CASE_DURATIONMAX_DESC,
                                              GetCaseDurationMax(),
                                              ZBProperty::PT_EDIT_NUMBER);
        else
            // FIXME translate comments
            // Propriété "Age du cas (maximum)" du groupe "Livrable"
            pCaseDurationMax = new ZBProperty(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                              ZS_BP_PROP_DELIVERABLE_COST,
                                              IDS_Z_COST_CASE_DURATIONMAX_NAME,
                                              Z_COST_CASE_DURATIONMAX,
                                              IDS_Z_COST_CASE_DURATIONMAX_DESC,
                                              PSS_Duration(GetCaseDurationMax(),
                                                           hourPerDay,
                                                           dayPerWeek,
                                                           dayPerMonth,
                                                           dayPerYear),
                                              ZBProperty::PT_EDIT_DURATION_READONLY,
                                              true,
                                              PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7));

        propSet.Add(pCaseDurationMax);

        ZBProperty* pTargetDuration;

        if (numericValue)
            // FIXME translate comments
            // Propriété "durée cible" du groupe "Livrable"
            pTargetDuration = new ZBProperty(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                             ZS_BP_PROP_DELIVERABLE_COST,
                                             IDS_Z_COST_TARGET_DURATION_NAME,
                                             Z_COST_TARGET_DURATION,
                                             IDS_Z_COST_TARGET_DURATION_DESC,
                                             GetTargetDuration(),
                                             ZBProperty::PT_EDIT_NUMBER);
        else
            // FIXME translate comments
            // Propriété "durée cible" du groupe "Livrable"
            pTargetDuration = new ZBProperty(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                             ZS_BP_PROP_DELIVERABLE_COST,
                                             IDS_Z_COST_TARGET_DURATION_NAME,
                                             Z_COST_TARGET_DURATION,
                                             IDS_Z_COST_TARGET_DURATION_DESC,
                                             PSS_Duration(GetTargetDuration(),
                                                          hourPerDay,
                                                          dayPerWeek,
                                                          dayPerMonth,
                                                          dayPerYear),
                                             ZBProperty::PT_EDIT_DURATION,
                                             true,
                                             PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7));

        propSet.Add(pTargetDuration);

        ZBProperty* pGreenLineDuration;

        if (numericValue)
            // FIXME translate comments
            // Propriété "ligne verte" du groupe "Livrable"
            pGreenLineDuration = new ZBProperty(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                                ZS_BP_PROP_DELIVERABLE_COST,
                                                IDS_Z_COST_GREENLINE_DURATION_NAME,
                                                Z_COST_GREENLINE_DURATION,
                                                IDS_Z_COST_GREENLINE_DURATION_DESC,
                                                GetGreenLineDuration(),
                                                ZBProperty::PT_EDIT_NUMBER);
        else
            // FIXME translate comments
            // Propriété "ligne verte" du groupe "Livrable"
            pGreenLineDuration = new ZBProperty(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                                ZS_BP_PROP_DELIVERABLE_COST,
                                                IDS_Z_COST_GREENLINE_DURATION_NAME,
                                                Z_COST_GREENLINE_DURATION,
                                                IDS_Z_COST_GREENLINE_DURATION_DESC,
                                                PSS_Duration(GetGreenLineDuration(),
                                                             hourPerDay,
                                                             dayPerWeek,
                                                             dayPerMonth,
                                                             dayPerYear),
                                                ZBProperty::PT_EDIT_DURATION,
                                                true,
                                                PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7));

        propSet.Add(pGreenLineDuration);
    }

    // FIXME translate comments
    // Propriété "Quantité" du groupe "Quantités"
    ZBProperty* pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                          ZS_BP_PROP_QUANTITY,
                                          IDS_Z_NUMBER_YEAR_NAME,
                                          Z_NUMBER_YEAR,
                                          IDS_Z_NUMBER_YEAR_DESC,
                                          GetQuantityYear(),
                                          ZBProperty::PT_EDIT_EXTENDED,
                                          true,
                                          PSS_StringFormat(PSS_StringFormat::IE_FT_Accounting, true, 0));    // depends on display detail

    propSet.Add(pPropQty);

    sValue = GetLockQuantityYear() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    if (numericValue)
        // FIXME translate comments
        // Propriété "Bloquer" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_YEAR_NAME,
                                  Z_LOCKED_YEAR,
                                  IDS_Z_LOCKED_YEAR_DESC,
                                  GetLockQuantityYear() ? 1.0 : 0.0);
    else
        // FIXME translate comments
        // Propriété "Bloquer" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_YEAR_NAME,
                                  Z_LOCKED_YEAR,
                                  IDS_Z_LOCKED_YEAR_DESC,
                                  sValue,
                                  ZBProperty::PT_COMBO_STRING_READONLY,
                                  true, // Enable
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                  PSS_Global::GetArrayYesNo());

    propSet.Add(pPropQty);

    sValue = GetForceEqualizer() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    if (numericValue)
        // FIXME translate comments
        // Propriété "Forcer" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_FORCE_EQUALIZER_NAME,
                                  Z_FORCE_EQUALIZER,
                                  IDS_Z_FORCE_EQUALIZER_DESC,
                                  GetForceEqualizer() ? 1.0 : 0.0);
    else
        // FIXME translate comments
        // Propriété "Forcer" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_FORCE_EQUALIZER_NAME,
                                  Z_FORCE_EQUALIZER,
                                  IDS_Z_FORCE_EQUALIZER_DESC,
                                  sValue,
                                  ZBProperty::PT_COMBO_STRING_READONLY,
                                  true, // Enable
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                  PSS_Global::GetArrayYesNo());

    propSet.Add(pPropQty);

    // FIXME translate comments
    // Propriété "Quantité janvier" du groupe "Quantités"
    pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                              ZS_BP_PROP_QUANTITY,
                              IDS_Z_NUMBER_JANUARY_NAME,
                              Z_NUMBER_JANUARY,
                              IDS_Z_NUMBER_JANUARY_DESC,
                              GetQuantityJanuary(),
                              ZBProperty::PT_EDIT_NUMBER,
                              false); // don't display detail

    propSet.Add(pPropQty);

    // todo FIXME -cImprovement -oJean: 12x the same code for each month of the year... Please create a function!
    sValue = GetLockQuantityJanuary() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    if (numericValue)
        // FIXME translate comments
        // Propriété "Bloquer janvier" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_JANUARY_NAME,
                                  Z_LOCKED_JANUARY,
                                  IDS_Z_LOCKED_JANUARY_DESC,
                                  GetLockQuantityJanuary() ? 1.0 : 0.0);
    else
        // FIXME translate comments
        // Propriété "Bloquer janvier" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_JANUARY_NAME,
                                  Z_LOCKED_JANUARY,
                                  IDS_Z_LOCKED_JANUARY_DESC,
                                  sValue,
                                  ZBProperty::PT_COMBO_STRING_READONLY,
                                  false, // don't display detail
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                  PSS_Global::GetArrayYesNo());

    propSet.Add(pPropQty);

    // FIXME translate comments
    // Propriété "Quantité février" du groupe "Quantités"
    pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                              ZS_BP_PROP_QUANTITY,
                              IDS_Z_NUMBER_FEBRUARY_NAME,
                              Z_NUMBER_FEBRUARY,
                              IDS_Z_NUMBER_FEBRUARY_DESC,
                              GetQuantityFebruary(),
                              ZBProperty::PT_EDIT_NUMBER,
                              false); // don't display detail

    propSet.Add(pPropQty);

    sValue = GetLockQuantityFebruary() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    if (numericValue)
        // FIXME translate comments
        // Propriété "Bloquer février" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_FEBRUARY_NAME,
                                  Z_LOCKED_FEBRUARY,
                                  IDS_Z_LOCKED_FEBRUARY_DESC,
                                  GetLockQuantityFebruary() ? 1.0 : 0.0);
    else
        // FIXME translate comments
        // Propriété "Bloquer février" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_FEBRUARY_NAME,
                                  Z_LOCKED_FEBRUARY,
                                  IDS_Z_LOCKED_FEBRUARY_DESC,
                                  sValue,
                                  ZBProperty::PT_COMBO_STRING_READONLY,
                                  false, // don't display detail
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                  PSS_Global::GetArrayYesNo());

    propSet.Add(pPropQty);

    // FIXME translate comments
    // Propriété "Quantité mars" du groupe "Quantités"
    pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                              ZS_BP_PROP_QUANTITY,
                              IDS_Z_NUMBER_MARCH_NAME,
                              Z_NUMBER_MARCH,
                              IDS_Z_NUMBER_MARCH_DESC,
                              GetQuantityMarch(),
                              ZBProperty::PT_EDIT_NUMBER,
                              false); // don't display detail

    propSet.Add(pPropQty);

    sValue = GetLockQuantityMarch() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    if (numericValue)
        // FIXME translate comments
        // Propriété "Bloquer mars" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_MARCH_NAME,
                                  Z_LOCKED_MARCH,
                                  IDS_Z_LOCKED_MARCH_DESC,
                                  GetLockQuantityMarch() ? 1.0 : 0.0);
    else
        // FIXME translate comments
        // Propriété "Bloquer mars" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_MARCH_NAME,
                                  Z_LOCKED_MARCH,
                                  IDS_Z_LOCKED_MARCH_DESC,
                                  sValue,
                                  ZBProperty::PT_COMBO_STRING_READONLY,
                                  false, // don't display detail
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                  PSS_Global::GetArrayYesNo());

    propSet.Add(pPropQty);

    // FIXME translate comments
    // Propriété "Quantité avril" du groupe "Quantités"
    pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                              ZS_BP_PROP_QUANTITY,
                              IDS_Z_NUMBER_APRIL_NAME,
                              Z_NUMBER_APRIL,
                              IDS_Z_NUMBER_APRIL_DESC,
                              GetQuantityApril(),
                              ZBProperty::PT_EDIT_NUMBER,
                              false); // don't display detail

    propSet.Add(pPropQty);

    sValue = GetLockQuantityApril() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    if (numericValue)
        // FIXME translate comments
        // Propriété "Bloquer avril" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_APRIL_NAME,
                                  Z_LOCKED_APRIL,
                                  IDS_Z_LOCKED_APRIL_DESC,
                                  GetLockQuantityApril() ? 1.0 : 0.0);
    else
        // FIXME translate comments
        // Propriété "Bloquer avril" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_APRIL_NAME,
                                  Z_LOCKED_APRIL,
                                  IDS_Z_LOCKED_APRIL_DESC,
                                  sValue,
                                  ZBProperty::PT_COMBO_STRING_READONLY,
                                  false, // don't display detail
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                  PSS_Global::GetArrayYesNo());

    propSet.Add(pPropQty);

    // FIXME translate comments
    // Propriété "Quantité mai" du groupe "Quantités"
    pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                              ZS_BP_PROP_QUANTITY,
                              IDS_Z_NUMBER_MAY_NAME,
                              Z_NUMBER_MAY,
                              IDS_Z_NUMBER_MAY_DESC,
                              GetQuantityMay(),
                              ZBProperty::PT_EDIT_NUMBER,
                              false); // don't display detail

    propSet.Add(pPropQty);

    sValue = GetLockQuantityMay() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    if (numericValue)
        // FIXME translate comments
        // Propriété "Bloquer mai" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_MAY_NAME,
                                  Z_LOCKED_MAY,
                                  IDS_Z_LOCKED_MAY_DESC,
                                  GetLockQuantityMay() ? 1.0 : 0.0);
    else
        // FIXME translate comments
        // Propriété "Bloquer mai" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_MAY_NAME,
                                  Z_LOCKED_MAY,
                                  IDS_Z_LOCKED_MAY_DESC,
                                  sValue,
                                  ZBProperty::PT_COMBO_STRING_READONLY,
                                  false, // don't display detail
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                  PSS_Global::GetArrayYesNo());

    propSet.Add(pPropQty);

    // FIXME translate comments
    // Propriété "Quantité juin" du groupe "Quantités"
    pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                              ZS_BP_PROP_QUANTITY,
                              IDS_Z_NUMBER_JUNE_NAME,
                              Z_NUMBER_JUNE,
                              IDS_Z_NUMBER_JUNE_DESC,
                              GetQuantityJune(),
                              ZBProperty::PT_EDIT_NUMBER,
                              false); // don't display detail

    propSet.Add(pPropQty);

    sValue = GetLockQuantityJune() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    if (numericValue)
        // FIXME translate comments
        // Propriété "Bloquer juin" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_JUNE_NAME,
                                  Z_LOCKED_JUNE,
                                  IDS_Z_LOCKED_JUNE_DESC,
                                  GetLockQuantityJune() ? 1.0 : 0.0);
    else
        // FIXME translate comments
        // Propriété "Bloquer juin" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_JUNE_NAME,
                                  Z_LOCKED_JUNE,
                                  IDS_Z_LOCKED_JUNE_DESC,
                                  sValue,
                                  ZBProperty::PT_COMBO_STRING_READONLY,
                                  false, // don't display detail
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                  PSS_Global::GetArrayYesNo());

    propSet.Add(pPropQty);

    // FIXME translate comments
    // Propriété "Quantité juillet" du groupe "Quantités"
    pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                              ZS_BP_PROP_QUANTITY,
                              IDS_Z_NUMBER_JULY_NAME,
                              Z_NUMBER_JULY,
                              IDS_Z_NUMBER_JULY_DESC,
                              GetQuantityJuly(),
                              ZBProperty::PT_EDIT_NUMBER,
                              false); // don't display detail

    propSet.Add(pPropQty);

    sValue = GetLockQuantityJuly() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    if (numericValue)
        // FIXME translate comments
        // Propriété "Bloquer juillet" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_JULY_NAME,
                                  Z_LOCKED_JULY,
                                  IDS_Z_LOCKED_JULY_DESC,
                                  GetLockQuantityJuly() ? 1.0 : 0.0);
    else
        // FIXME translate comments
        // Propriété "Bloquer juillet" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_JULY_NAME,
                                  Z_LOCKED_JULY,
                                  IDS_Z_LOCKED_JULY_DESC,
                                  sValue,
                                  ZBProperty::PT_COMBO_STRING_READONLY,
                                  false, // don't display detail
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                  PSS_Global::GetArrayYesNo());

    propSet.Add(pPropQty);

    // FIXME translate comments
    // Propriété "Quantité août" du groupe "Quantités"
    pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                              ZS_BP_PROP_QUANTITY,
                              IDS_Z_NUMBER_AUGUST_NAME,
                              Z_NUMBER_AUGUST,
                              IDS_Z_NUMBER_AUGUST_DESC,
                              GetQuantityAugust(),
                              ZBProperty::PT_EDIT_NUMBER,
                              false); // don't display detail

    propSet.Add(pPropQty);

    sValue = GetLockQuantityAugust() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    if (numericValue)
        // FIXME translate comments
        // Propriété "Bloquer août" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_AUGUST_NAME,
                                  Z_LOCKED_AUGUST,
                                  IDS_Z_LOCKED_AUGUST_DESC,
                                  GetLockQuantityAugust() ? 1.0 : 0.0);
    else
        // FIXME translate comments
        // Propriété "Bloquer août" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_AUGUST_NAME,
                                  Z_LOCKED_AUGUST,
                                  IDS_Z_LOCKED_AUGUST_DESC,
                                  sValue,
                                  ZBProperty::PT_COMBO_STRING_READONLY,
                                  false, // don't display detail
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                  PSS_Global::GetArrayYesNo());

    propSet.Add(pPropQty);

    // FIXME translate comments
    // Propriété "Quantité septembre" du groupe "Quantités"
    pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                              ZS_BP_PROP_QUANTITY,
                              IDS_Z_NUMBER_SEPTEMBER_NAME,
                              Z_NUMBER_SEPTEMBER,
                              IDS_Z_NUMBER_SEPTEMBER_DESC,
                              GetQuantitySeptember(),
                              ZBProperty::PT_EDIT_NUMBER,
                              false); // don't display detail

    propSet.Add(pPropQty);

    sValue = GetLockQuantitySeptember() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    if (numericValue)
        // FIXME translate comments
        // Propriété "Bloquer septembre" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_SEPTEMBER_NAME,
                                  Z_LOCKED_SEPTEMBER,
                                  IDS_Z_LOCKED_SEPTEMBER_DESC,
                                  GetLockQuantitySeptember() ? 1.0 : 0.0);
    else
        // FIXME translate comments
        // Propriété "Bloquer septembre" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_SEPTEMBER_NAME,
                                  Z_LOCKED_SEPTEMBER,
                                  IDS_Z_LOCKED_SEPTEMBER_DESC,
                                  sValue,
                                  ZBProperty::PT_COMBO_STRING_READONLY,
                                  false, // don't display detail
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                  PSS_Global::GetArrayYesNo());

    propSet.Add(pPropQty);

    // FIXME translate comments
    // Propriété "Quantité octobre" du groupe "Quantités"
    pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                              ZS_BP_PROP_QUANTITY,
                              IDS_Z_NUMBER_OCTOBER_NAME,
                              Z_NUMBER_OCTOBER,
                              IDS_Z_NUMBER_OCTOBER_DESC,
                              GetQuantityOctober(),
                              ZBProperty::PT_EDIT_NUMBER,
                              false); // don't display detail

    propSet.Add(pPropQty);

    sValue = GetLockQuantityOctober() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    if (numericValue)
        // FIXME translate comments
        // Propriété "Bloquer octobre" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_OCTOBER_NAME,
                                  Z_LOCKED_OCTOBER,
                                  IDS_Z_LOCKED_OCTOBER_DESC,
                                  GetLockQuantityOctober() ? 1.0 : 0.0);
    else
        // FIXME translate comments
        // Propriété "Bloquer octobre" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_OCTOBER_NAME,
                                  Z_LOCKED_OCTOBER,
                                  IDS_Z_LOCKED_OCTOBER_DESC,
                                  sValue,
                                  ZBProperty::PT_COMBO_STRING_READONLY,
                                  false, // don't display detail
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                  PSS_Global::GetArrayYesNo());

    propSet.Add(pPropQty);

    // FIXME translate comments
    // Propriété "Quantité novembre" du groupe "Quantités"
    pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                              ZS_BP_PROP_QUANTITY,
                              IDS_Z_NUMBER_NOVEMBER_NAME,
                              Z_NUMBER_NOVEMBER,
                              IDS_Z_NUMBER_NOVEMBER_DESC,
                              GetQuantityNovember(),
                              ZBProperty::PT_EDIT_NUMBER,
                              false); // don't display detail

    propSet.Add(pPropQty);

    sValue = GetLockQuantityNovember() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    if (numericValue)
        // FIXME translate comments
        // Propriété "Bloquer novembre" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_NOVEMBER_NAME,
                                  Z_LOCKED_NOVEMBER,
                                  IDS_Z_LOCKED_NOVEMBER_DESC,
                                  GetLockQuantityNovember() ? 1.0 : 0.0);
    else
        // FIXME translate comments
        // Propriété "Bloquer novembre" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_NOVEMBER_NAME,
                                  Z_LOCKED_NOVEMBER,
                                  IDS_Z_LOCKED_NOVEMBER_DESC,
                                  sValue,
                                  ZBProperty::PT_COMBO_STRING_READONLY,
                                  false, // don't display detail
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                  PSS_Global::GetArrayYesNo());

    propSet.Add(pPropQty);

    // FIXME translate comments
    // Propriété "Quantité décembre" du groupe "Quantités"
    pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                              ZS_BP_PROP_QUANTITY,
                              IDS_Z_NUMBER_DECEMBER_NAME,
                              Z_NUMBER_DECEMBER,
                              IDS_Z_NUMBER_DECEMBER_DESC,
                              GetQuantityDecember(),
                              ZBProperty::PT_EDIT_NUMBER,
                              false); // don't display detail

    propSet.Add(pPropQty);

    sValue = GetLockQuantityDecember() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    if (numericValue)
        // FIXME translate comments
        // Propriété "Bloquer décembre" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_DECEMBER_NAME,
                                  Z_LOCKED_DECEMBER,
                                  IDS_Z_LOCKED_DECEMBER_DESC,
                                  GetLockQuantityDecember() ? 1.0 : 0.0);
    else
        // FIXME translate comments
        // Propriété "Bloquer décembre" du groupe "Quantités"
        pPropQty = new ZBProperty(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                  ZS_BP_PROP_QUANTITY,
                                  IDS_Z_LOCKED_DECEMBER_NAME,
                                  Z_LOCKED_DECEMBER,
                                  IDS_Z_LOCKED_DECEMBER_DESC,
                                  sValue,
                                  ZBProperty::PT_COMBO_STRING_READONLY,
                                  false, // don't display detail
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                  PSS_Global::GetArrayYesNo());

    propSet.Add(pPropQty);

    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
        dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetIntegrateCostSimulation())
    {
        // add simulation properties
        ZBProperty* pSimProp = NULL;

        // FIXME translate comments
        // Propriété "Coût" du groupe "Calculs et prévisions"
        pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_DELIVERABLE,
                                  ZS_BP_PROP_SIM_DELIVERABLE,
                                  IDS_Z_SIM_DELIV_COST_NAME,
                                  Z_SIM_DELIV_COST,
                                  IDS_Z_SIM_DELIV_COST_DESC,
                                  double(GetCost()),
                                  ZBProperty::PT_EDIT_NUMBER_READONLY,
                                  true,
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol));

        propSet.Add(pSimProp);

        // FIXME translate comments
        // Propriété "Charge de travail" du groupe "Calculs et prévisions"
        pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_DELIVERABLE,
                                  ZS_BP_PROP_SIM_DELIVERABLE,
                                  IDS_Z_SIM_DELIV_WORKLOAD_FORECAST_NAME,
                                  Z_SIM_DELIV_WORKLOAD_FORECAST,
                                  IDS_Z_SIM_DELIV_WORKLOAD_FORECAST_DESC,
                                  PSS_Duration(double(GetWorkloadForecast()),
                                               hourPerDay,
                                               dayPerWeek,
                                               dayPerMonth,
                                               dayPerYear),
                                  ZBProperty::PT_EDIT_DURATION_READONLY,
                                  true,
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7));

        propSet.Add(pSimProp);

        // FIXME translate comments
        // Propriété "Guid" du groupe "Unité de traitement" (Non visible)
        ZBProperty* pUnitGUID = new ZBProperty(IDS_ZS_BP_PROP_UNIT_TITLE,
                                               ZS_BP_PROP_UNIT,
                                               IDS_Z_UNIT_GUID_NAME,
                                               Z_UNIT_GUID,
                                               IDS_Z_UNIT_GUID_DESC,
                                               GetUnitGUID(),
                                               ZBProperty::PT_EDIT_EXTENDED_READONLY,
                                               false); // not enable, used for saving the unit GUID

        propSet.Add(pUnitGUID);

        bool    error;
        CString unitName = RetrieveUnitName(GetUnitGUID(), error);

        // FIXME translate comments
        // Propriété "Unité" du groupe "Unité de traitement" (Non visible)
        ZBProperty* pUnitName = new ZBProperty(IDS_ZS_BP_PROP_UNIT_TITLE,
                                               ZS_BP_PROP_UNIT,
                                               IDS_Z_UNIT_NAME_NAME,
                                               Z_UNIT_NAME,
                                               IDS_Z_UNIT_NAME_DESC,
                                               unitName,
                                               groupEnabled ? ZBProperty::PT_EDIT_EXTENDED_READONLY : ZBProperty::PT_EDIT_STRING_READONLY,
                                               false);
        propSet.Add(pUnitName);

        const float unitCost = RetrieveUnitCost(GetUnitGUID(), error);

        // FIXME translate comments
        // Propriété "Coût" du groupe "Unité de traitement" (Non visible)
        ZBProperty* pUnitCost = new ZBProperty(IDS_ZS_BP_PROP_UNIT_TITLE,
                                               ZS_BP_PROP_UNIT,
                                               IDS_Z_UNIT_COST_NAME,
                                               Z_UNIT_COST,
                                               IDS_Z_UNIT_COST_DESC,
                                               unitCost,
                                               ZBProperty::PT_EDIT_NUMBER_READONLY,
                                               false,
                                               PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol),
                                               false);
        propSet.Add(pUnitCost);
    }

    // FIXME translate comments
    // RS-MODIF 17.11.04 Double validation should appear in Conceptor
    ZBProperty* pUnitDoubleValid;

    if (numericValue)
        // FIXME translate comments
        // Propriété "Double validation" du groupe "Unité de traitement"
        pUnitDoubleValid = new ZBProperty(IDS_ZS_BP_PROP_UNIT_TITLE,
                                          ZS_BP_PROP_UNIT,
                                          IDS_Z_UNIT_DOUBLE_VALIDATION_NAME,
                                          Z_UNIT_DOUBLE_VALIDATION,
                                          IDS_Z_UNIT_DOUBLE_VALIDATION_DESC,
                                          double(GetUnitDoubleValidationType()));
    else
        // FIXME translate comments
        // Propriété "Double validation" du groupe "Unité de traitement"
        pUnitDoubleValid = new ZBProperty(IDS_ZS_BP_PROP_UNIT_TITLE,
                                          ZS_BP_PROP_UNIT,
                                          IDS_Z_UNIT_DOUBLE_VALIDATION_NAME,
                                          Z_UNIT_DOUBLE_VALIDATION,
                                          IDS_Z_UNIT_DOUBLE_VALIDATION_DESC,
                                          GetUnitDoubleValidationTypeString(GetUnitDoubleValidationType()),
                                          ZBProperty::PT_COMBO_STRING_READONLY,
                                          true,
                                          PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                          &m_UnitDoubleValidationTypeArray);

    propSet.Add(pUnitDoubleValid);

    return true;
}
//---------------------------------------------------------------------------
bool ZBDeliverableLinkSymbol::SaveProperties(ZBPropertySet& PropSet)
{
    if (!PSS_LinkSymbol::SaveProperties(PropSet))
    {
        return false;
    }

    // Only local symbol have access to properties
    if (!IsLocal())
    {
        return true;
    }

    // Save the rules
    ZBBPRuleListProperties* pRulesProps = (ZBBPRuleListProperties*)GetProperty(ZS_BP_PROP_RULELIST);

    if (!pRulesProps)
    {
        return false;
    }

    // Now run through the list of data and fill the property set
    ZBProperty* pProp;
    ZBPropertyIterator f(&PropSet);

    // Empty the task list
    SetRuleList(_T(""));

    for (pProp = f.GetFirst(); pProp; pProp = f.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_RULELIST)
        {
            switch (pProp->GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    // If not empty, add this new task
                    if (!pProp->GetValueString().IsEmpty())
                    {
                        AddRule(pProp->GetValueString());
                    }

                    break;
                }
            }
        }
    }

    // Now run through the list of data and fill the property set
    ZBPropertyIterator i(&PropSet);

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_DELIVERABLE_COST)
        {
            switch (pProp->GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    m_CostDeliverableProperties.SetValue(pProp->GetItemID(), pProp->GetValueString());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    m_CostDeliverableProperties.SetValue(pProp->GetItemID(),
                                                         static_cast<float>(pProp->GetValueDouble()));
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    m_CostDeliverableProperties.SetValue(pProp->GetItemID(), pProp->GetValueFloat());
                    break;
                }

                case ZBProperty::PT_DATE:
                {
                    m_CostDeliverableProperties.SetValue(pProp->GetItemID(),
                                                         static_cast<float>((DATE)pProp->GetValueDate()));
                    break;
                }

                case ZBProperty::PT_TIMESPAN:
                {
                    m_CostDeliverableProperties.SetValue(pProp->GetItemID(), (double)pProp->GetValueTimeSpan());
                    break;
                }

                case ZBProperty::PT_DURATION:
                {
                    m_CostDeliverableProperties.SetValue(pProp->GetItemID(), (double)pProp->GetValueDuration());
                    break;
                }
            }
        }
    }

    SavePropertiesToQuantity(PropSet);

    // *************************************************************************************************************
    // JMR-MODIF - Le 11 juillet 2007 - Ajout du code pour la mise à jour des valeurs des risques.

    ZBPropertyIterator j(&PropSet);

    for (pProp = j.GetFirst(); pProp; pProp = j.GetNext())
    {
        if (pProp->GetCategoryID() >= ZS_BP_PROP_RISK &&
            pProp->GetCategoryID() <= ZS_BP_PROP_RISK + GetRiskCount())
        {
            int i = pProp->GetCategoryID() - ZS_BP_PROP_RISK;

            if (pProp->GetItemID() == Z_RISK_NAME + (i * _MaxRisksSize))
            {
                SetRiskName(i, pProp->GetValueString());
            }

            if (pProp->GetItemID() == Z_RISK_DESC + (i * _MaxRisksSize))
            {
                SetRiskDesc(i, pProp->GetValueString());
            }

            if (pProp->GetItemID() == Z_RISK_UE + (i * _MaxRisksSize))
            {
                SetRiskUE(i, pProp->GetValueFloat());
            }

            if (pProp->GetItemID() == Z_RISK_POA + (i * _MaxRisksSize))
            {
                SetRiskPOA(i, pProp->GetValueFloat());
            }

            if (pProp->GetItemID() == Z_RISK_ACTION + (i * _MaxRisksSize))
            {
                SetRiskAction(i, (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo() ? 1 : 0));
            }
        }
    }
    // *************************************************************************************************************

    // Now run through the list of data and fill the property set
    ZBPropertyIterator k(&PropSet);

    for (pProp = k.GetFirst(); pProp; pProp = k.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_SIM_DELIVERABLE)
        {
            switch (pProp->GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    m_SimProperties.SetValue(pProp->GetItemID(), pProp->GetValueString());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    m_SimProperties.SetValue(pProp->GetItemID(), pProp->GetValueDouble());
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    m_SimProperties.SetValue(pProp->GetItemID(), pProp->GetValueFloat());
                    break;
                }

                case ZBProperty::PT_DATE:
                {
                    m_SimProperties.SetValue(pProp->GetItemID(),
                                             static_cast<float>((DATE)pProp->GetValueDate()));
                    break;
                }

                case ZBProperty::PT_TIMESPAN:
                {
                    m_SimProperties.SetValue(pProp->GetItemID(),
                        (double)pProp->GetValueTimeSpan());
                    break;
                }

                case ZBProperty::PT_DURATION:
                {
                    m_SimProperties.SetValue(pProp->GetItemID(), (double)pProp->GetValueDuration());
                    break;
                }
            }
        }
    }

    ZBBPTextItemListProperties* pTextItemProps = (ZBBPTextItemListProperties*)GetProperty(ZS_BP_PROP_TEXTITEMLIST);

    if (!pTextItemProps)
    {
        return false;
    }

    // Now run through the list of data and fill the property set
    ZBPropertyIterator l(&PropSet);

    // Empty the text item list
    SetTextItemList(_T(""));

    for (pProp = l.GetFirst(); pProp; pProp = l.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_TEXTITEMLIST)
        {
            switch (pProp->GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    // If not empty, add this new text item
                    if (!pProp->GetValueString().IsEmpty())
                    {
                        AddTextItem(pProp->GetValueString());
                    }

                    break;
                }
            }
        }
    }
    // Because using the AddTask function, not necessary to SetProperty

    // Now run through the list of data and fill the property set
    ZBPropertyIterator m(&PropSet);

    for (pProp = m.GetFirst(); pProp; pProp = m.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT)
        {
            // Check if a flag
            if (pProp->GetItemID() == Z_UNIT_DOUBLE_VALIDATION)
            {
                m_UnitProp.SetValue(pProp->GetItemID(),
                                    ConvertUnitDoubleValidationString2Type(pProp->GetValueString()));
            }
            else
            {
                switch (pProp->GetPTValueType())
                {
                    case ZBProperty::PT_DOUBLE:
                    {
                        m_UnitProp.SetValue(pProp->GetItemID(), static_cast<float>(pProp->GetValueDouble()));
                        break;
                    }

                    case ZBProperty::PT_FLOAT:
                    {
                        m_UnitProp.SetValue(pProp->GetItemID(), pProp->GetValueFloat());
                        break;
                    }

                    case ZBProperty::PT_STRING:
                    {
                        m_UnitProp.SetValue(pProp->GetItemID(), pProp->GetValueString());
                        break;
                    }
                }
            }
        }
    }

    RefreshAttributeTextArea(true);

    return true;
}

bool ZBDeliverableLinkSymbol::SaveProperty(ZBProperty& Property)
{
    if (!PSS_LinkSymbol::SaveProperty(Property))
    {
        return false;
    }

    // Only local symbol have access to properties
    if (!IsLocal())
    {
        return true;
    }

    // ************************************************************************************************
    // JMR-MODIF - Le 17 juillet 2007 - Mise à jour des valeurs des propriétés des risques.

    if (Property.GetCategoryID() >= ZS_BP_PROP_RISK &&
        Property.GetCategoryID() <= ZS_BP_PROP_RISK + GetRiskCount())
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_RISK;

        if (Property.GetItemID() == Z_RISK_NAME + (i * _MaxRisksSize))
        {
            SetRiskName(i, Property.GetValueString());
        }

        if (Property.GetItemID() == Z_RISK_DESC + (i * _MaxRisksSize))
        {
            SetRiskDesc(i, Property.GetValueString());
        }

        if (Property.GetItemID() == Z_RISK_UE + (i * _MaxRisksSize))
        {
            SetRiskUE(i, Property.GetValueFloat());
        }

        if (Property.GetItemID() == Z_RISK_POA + (i * _MaxRisksSize))
        {
            SetRiskPOA(i, Property.GetValueFloat());
        }

        if (Property.GetItemID() == Z_RISK_ACTION + (i * _MaxRisksSize))
        {
            SetRiskAction(i, (Property.GetValueString() == PSS_Global::GetYesFromArrayYesNo() ? 1 : 0));
        }
    }
    // ************************************************************************************************

    // JMR-MODIF - Le 9 mai 2007 - Contrôle si l'utilisateur a tenté de renommer une règle.
    // Si c'est le cas, réetablit le nom d'origine.
    if (Property.GetCategoryID() == ZS_BP_PROP_RULES)
    {
        int Index = (Property.GetItemID() - Z_RULE_NAME) / _MaxRulesSize;

        if (m_Rules.GetRuleName(Index) != Property.GetValueString())
        {
            Property.SetValueString(m_Rules.GetRuleName(Index));
        }
    }

    if (Property.GetCategoryID() == ZS_BP_PROP_RULELIST)
    {
        // If not empty, add this new rule
        if (!Property.GetValueString().IsEmpty())
        {
            AddRule(Property.GetValueString());
        }
    }

    if (Property.GetCategoryID() == ZS_BP_PROP_TEXTITEMLIST)
    {
        // If not empty, add this new text item
        if (!Property.GetValueString().IsEmpty())
        {
            AddTextItem(Property.GetValueString());
        }
    }

    // Set the modified flag to true,
    // Do nothing more, the values will be saved by the save properties method
    SetModifiedFlag();
    return true;
}

void ZBDeliverableLinkSymbol::SavePropertiesToQuantity(ZBPropertySet& Properties)
{
    // Now run through the list of data and fill the property set
    ZBPropertyIterator j(&Properties);

    for (ZBProperty* pProp = j.GetFirst(); pProp; pProp = j.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_QUANTITY)
        {
            // Check if a flag
            if (pProp->GetItemID() == Z_LOCKED_YEAR ||
                pProp->GetItemID() == Z_LOCKED_JANUARY ||
                pProp->GetItemID() == Z_LOCKED_FEBRUARY ||
                pProp->GetItemID() == Z_LOCKED_MARCH ||
                pProp->GetItemID() == Z_LOCKED_APRIL ||
                pProp->GetItemID() == Z_LOCKED_MAY ||
                pProp->GetItemID() == Z_LOCKED_JUNE ||
                pProp->GetItemID() == Z_LOCKED_JULY ||
                pProp->GetItemID() == Z_LOCKED_AUGUST ||
                pProp->GetItemID() == Z_LOCKED_SEPTEMBER ||
                pProp->GetItemID() == Z_LOCKED_OCTOBER ||
                pProp->GetItemID() == Z_LOCKED_NOVEMBER ||
                pProp->GetItemID() == Z_LOCKED_DECEMBER ||
                pProp->GetItemID() == Z_FORCE_EQUALIZER)
            {
                m_Quantity.SetValue(pProp->GetItemID(),
                    (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? 1 : 0);
            }
            else
            {
                switch (pProp->GetPTValueType())
                {
                    case ZBProperty::PT_STRING:
                    {
                        m_Quantity.SetValue(pProp->GetItemID(), pProp->GetValueString());
                        break;
                    }

                    case ZBProperty::PT_DOUBLE:
                    {
                        m_Quantity.SetValue(pProp->GetItemID(), static_cast<float>(pProp->GetValueDouble()));
                        break;
                    }

                    case ZBProperty::PT_FLOAT:
                    {
                        m_Quantity.SetValue(pProp->GetItemID(), pProp->GetValueFloat());
                        break;
                    }

                    case ZBProperty::PT_DATE:
                    {
                        m_Quantity.SetValue(pProp->GetItemID(), static_cast<float>((DATE)pProp->GetValueDate()));
                        break;
                    }

                    case ZBProperty::PT_TIMESPAN:
                    {
                        ASSERT(FALSE);
                        break;
                    }

                    case ZBProperty::PT_DURATION:
                    {
                        ASSERT(FALSE);
                        break;
                    }
                }
            }
        }
    }

    // Now calculates all percents, its is necessary to equalize
    m_Quantity.CalculatePercents();
}

void ZBDeliverableLinkSymbol::SaveEqualizerToProperties(ZBPropertySet& Properties)
{
    ZBPropertyIterator i(&Properties);
    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        if (!pProp || pProp->GetCategoryID() != ZS_BP_PROP_QUANTITY)
        {
            continue;
        }

        switch (pProp->GetItemID())
        {
            case Z_NUMBER_YEAR:
            {
                pProp->SetValueDouble(m_Quantity.GetNumberYear());
                break;
            }

            case Z_NUMBER_JANUARY:
            {
                pProp->SetValueDouble(m_Quantity.GetNumberJanuary());
                break;
            }

            case Z_NUMBER_FEBRUARY:
            {
                pProp->SetValueDouble(m_Quantity.GetNumberFebruary());
                break;
            }

            case Z_NUMBER_MARCH:
            {
                pProp->SetValueDouble(m_Quantity.GetNumberMarch());
                break;
            }

            case Z_NUMBER_APRIL:
            {
                pProp->SetValueDouble(m_Quantity.GetNumberApril());
                break;
            }

            case Z_NUMBER_MAY:
            {
                pProp->SetValueDouble(m_Quantity.GetNumberMay());
                break;
            }

            case Z_NUMBER_JUNE:
            {
                pProp->SetValueDouble(m_Quantity.GetNumberJune());
                break;
            }

            case Z_NUMBER_JULY:
            {
                pProp->SetValueDouble(m_Quantity.GetNumberJuly());
                break;
            }

            case Z_NUMBER_AUGUST:
            {
                pProp->SetValueDouble(m_Quantity.GetNumberAugust());
                break;
            }

            case Z_NUMBER_SEPTEMBER:
            {
                pProp->SetValueDouble(m_Quantity.GetNumberSeptember());
                break;
            }

            case Z_NUMBER_OCTOBER:
            {
                pProp->SetValueDouble(m_Quantity.GetNumberOctober());
                break;

            }
            case Z_NUMBER_NOVEMBER:
            {
                pProp->SetValueDouble(m_Quantity.GetNumberNovember());
                break;
            }

            case Z_NUMBER_DECEMBER:
            {
                pProp->SetValueDouble(m_Quantity.GetNumberDecember());
                break;
            }

            case Z_LOCKED_YEAR:
            {
                break;
            }

            case Z_LOCKED_JANUARY:
            {
                pProp->SetValueString((m_Quantity.GetLockNumberJanuary() == true) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }

            case Z_LOCKED_FEBRUARY:
            {
                pProp->SetValueString((m_Quantity.GetLockNumberFebruary() == true) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }

            case Z_LOCKED_MARCH:
            {
                pProp->SetValueString((m_Quantity.GetLockNumberMarch() == true) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }

            case Z_LOCKED_APRIL:
            {
                pProp->SetValueString((m_Quantity.GetLockNumberApril() == true) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }

            case Z_LOCKED_MAY:
            {
                pProp->SetValueString((m_Quantity.GetLockNumberMay() == true) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }

            case Z_LOCKED_JUNE:
            {
                pProp->SetValueString((m_Quantity.GetLockNumberJune() == true) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }

            case Z_LOCKED_JULY:
            {
                pProp->SetValueString((m_Quantity.GetLockNumberJuly() == true) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }

            case Z_LOCKED_AUGUST:
            {
                pProp->SetValueString((m_Quantity.GetLockNumberAugust() == true) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }

            case Z_LOCKED_SEPTEMBER:
            {
                pProp->SetValueString((m_Quantity.GetLockNumberSeptember() == true) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }

            case Z_LOCKED_OCTOBER:
            {
                pProp->SetValueString((m_Quantity.GetLockNumberOctober() == true) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }

            case Z_LOCKED_NOVEMBER:
            {
                pProp->SetValueString((m_Quantity.GetLockNumberNovember() == true) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }

            case Z_LOCKED_DECEMBER:
            {
                pProp->SetValueString((m_Quantity.GetLockNumberDecember() == true) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }

            case Z_FORCE_EQUALIZER:
            {
                pProp->SetValueString((m_Quantity.GetForceEqualizer() == true) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }
        }
    }
}

// ********************************************* Fonctions Set **********************************************

void ZBDeliverableLinkSymbol::SetNewNumberAndEqualize(ZBProperty& Property, ZBPropertySet& Properties)
{
    ZBPropertyIterator i(&Properties);
    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // Continue till we've found the right property to change
        if (!pProp || pProp->GetCategoryID() != ZS_BP_PROP_QUANTITY || pProp->GetItemID() != Property.GetItemID())
        {
            continue;
        }

        switch (pProp->GetItemID())
        {
            case Z_NUMBER_YEAR:
            {
                m_Quantity.SetAndCalculateQuantitiesBasedOnYear(Property.GetValueDouble());
                return;
            }

            case Z_NUMBER_JANUARY:
            {
                m_Quantity.SetAndCalculateQuantitiesBasedOnJanuary(Property.GetValueDouble());
                return;
            }

            case Z_NUMBER_FEBRUARY:
            {
                m_Quantity.SetAndCalculateQuantitiesBasedOnFebruary(Property.GetValueDouble());
                return;
            }

            case Z_NUMBER_MARCH:
            {
                m_Quantity.SetAndCalculateQuantitiesBasedOnMarch(Property.GetValueDouble());
                return;
            }

            case Z_NUMBER_APRIL:
            {
                m_Quantity.SetAndCalculateQuantitiesBasedOnApril(Property.GetValueDouble());
                return;
            }

            case Z_NUMBER_MAY:
            {
                m_Quantity.SetAndCalculateQuantitiesBasedOnMay(Property.GetValueDouble());
                return;
            }

            case Z_NUMBER_JUNE:
            {
                m_Quantity.SetAndCalculateQuantitiesBasedOnJune(Property.GetValueDouble());
                return;
            }

            case Z_NUMBER_JULY:
            {
                m_Quantity.SetAndCalculateQuantitiesBasedOnJuly(Property.GetValueDouble());
                return;
            }

            case Z_NUMBER_AUGUST:
            {
                m_Quantity.SetAndCalculateQuantitiesBasedOnAugust(Property.GetValueDouble());
                return;
            }

            case Z_NUMBER_SEPTEMBER:
            {
                m_Quantity.SetAndCalculateQuantitiesBasedOnSeptember(Property.GetValueDouble());
                return;
            }

            case Z_NUMBER_OCTOBER:
            {
                m_Quantity.SetAndCalculateQuantitiesBasedOnOctober(Property.GetValueDouble());
                return;
            }

            case Z_NUMBER_NOVEMBER:
            {
                m_Quantity.SetAndCalculateQuantitiesBasedOnNovember(Property.GetValueDouble());
                return;
            }

            case Z_NUMBER_DECEMBER:
            {
                m_Quantity.SetAndCalculateQuantitiesBasedOnDecember(Property.GetValueDouble());
                return;
            }

            // Nothing to do
            default:
            {
                return;
            }
        }
    }
}

void ZBDeliverableLinkSymbol::SetTextItemList(const CString Value)
{
    ZBBPTextItemListProperties* pProps = (ZBBPTextItemListProperties*)GetProperty(ZS_BP_PROP_TEXTITEMLIST);

    if (pProps)
    {
        ZBBPTextItemListProperties Props(*pProps);
        Props.SetTextItemList(Value);
        SetProperty(&Props);
    }
}

void ZBDeliverableLinkSymbol::SetRuleList(const CString Value)
{
    ZBBPRuleListProperties* pProps = (ZBBPRuleListProperties*)GetProperty(ZS_BP_PROP_RULELIST);

    if (pProps)
    {
        ZBBPRuleListProperties Props(*pProps);
        Props.SetRuleList(Value);
        SetProperty(&Props);
    }
}

// JMR-MODIF - Le 14 juin 2005 - Ajout de la fonction SetVisualInfo
// Change les attributs du trait afin de permettre une information visuelle du pourcentage.
void ZBDeliverableLinkSymbol::SetVisualInfo(int iPercent)
{
    // Contrôle que la valeur du pourcentage ne dépasse pas les 100%, et convertit en valeur pour le choix du style.
    int Style = iPercent <= 100 ? ((2 * iPercent) / 100) : 2;

    // A 100%, le trait est plein. Sinon, il est soit pointillé (0 à 49%), soit traitillé (50-99%).
    if (Style == 2)
    {
        PSS_LinkSymbol::SetCurrentLineStyle(PS_SOLID);
    }
    else
    {
        switch (Style)
        {
            // 0%-49% -> Le trait est pointillé. (........)
            case 0:
            {
                PSS_LinkSymbol::SetCurrentLineStyle(PS_DOT);
                break;
            }

            // 50%-99% -> le trait est traitillé. (--------)
            case 1:
            {
                PSS_LinkSymbol::SetCurrentLineStyle(PS_DASH);
                break;
            }
        }
    }
}

// ********************************************* Fonctions Get **********************************************

// JMR-MODIF - Le 25 décembre 2006 - Permet de rechercher le nom original d'une règle en fonction de son GUID.
CString ZBDeliverableLinkSymbol::GetRuleNameByGUID(PSS_LogicalRulesEntity* p_Rule, CString RuleGUID)
{
    if (p_Rule == NULL)
    {
        return _T("");
    }

    if (p_Rule->GetGUID() == RuleGUID)
    {
        return p_Rule->GetEntityName();
    }

    if (p_Rule->ContainEntity())
    {
        int Count = p_Rule->GetEntityCount();

        for (int i = 0; i < Count; ++i)
        {
            PSS_RulesEntity* pEntity = p_Rule->GetEntityAt(i);

            if (!pEntity)
            {
                continue;
            }

            if (ISA(pEntity, PSS_LogicalRulesEntity))
            {
                CString m_Name = GetRuleNameByGUID(dynamic_cast<PSS_LogicalRulesEntity*>(pEntity), RuleGUID);

                if (!m_Name.IsEmpty())
                {
                    return m_Name;
                }
            }
        }
    }

    return _T("");
}

CString ZBDeliverableLinkSymbol::GetTextItemList() const
{
    ZBBPTextItemListProperties* pProps = (ZBBPTextItemListProperties*)GetProperty(ZS_BP_PROP_TEXTITEMLIST);

    if (!pProps)
    {
        return _T("");
    }

    return pProps->GetTextItemList();
}

CString ZBDeliverableLinkSymbol::GetTextItemAt(size_t Index)
{
    PSS_Tokenizer token(GetTextItemList());    // Initialize the token with the list
                                            // and with the default ; as separator

    CString Value;

    // Retrieve the specific indexed token
    if (token.GetTokenAt(Index, Value))
    {
        return Value;
    }

    return _T("");
}

size_t ZBDeliverableLinkSymbol::GetTextItemCount() const
{
    PSS_Tokenizer token(GetTextItemList());    // Initialize the token with the list
                                            // and with the default ; as separator

    return token.GetTokenCount();
}

CString ZBDeliverableLinkSymbol::GetCombinationName() const
{
    // Retrieve the destination procedure
    ZBBPProcedureSymbol* pProcedure = GetTargetProcedure();

    if (!pProcedure)
    {
        return _T("");
    }

    // From this procedure, check what combination owns us
    size_t Count = pProcedure->GetCombinationCount();

    for (size_t i = 0; i < Count; ++i)
    {
        if (pProcedure->IsDeliverableInString(pProcedure->GetCombinationDeliverables(i),
                                              const_cast<ZBDeliverableLinkSymbol*>(this)->GetSymbolName()))
        {
            return pProcedure->GetCombinationName(i);
        }
    }

    // Otherwise, not found
    return _T("");
}

CString ZBDeliverableLinkSymbol::GetRuleList() const
{
    ZBBPRuleListProperties* pProps = (ZBBPRuleListProperties*)GetProperty(ZS_BP_PROP_RULELIST);

    if (!pProps)
    {
        return _T("");
    }

    return pProps->GetRuleList();
}

CString ZBDeliverableLinkSymbol::GetRuleAt(size_t Index)
{
    PSS_Tokenizer token(GetRuleList());    // Initialize the token with the task list
                                        // and with the default ; as separator
    CString Value;

    // Retrieve the specific indexed token
    if (token.GetTokenAt(Index, Value))
    {
        return Value;
    }

    return _T("");
}

size_t ZBDeliverableLinkSymbol::GetRuleCount() const
{
    PSS_Tokenizer token(GetRuleList());    // Initialize the token with the task list
                                        // and with the default ; as separator
    return token.GetTokenCount();
}

float ZBDeliverableLinkSymbol::GetCombinationMaxPercentage() const
{
    // Retrieve the destination procedure
    ZBBPProcedureSymbol* pProcedure = GetTargetProcedure();

    // Test if it is a local symbol
    if (pProcedure && !pProcedure->IsLocal())
    {
        // Locate the local symbol
        CODComponent* pLocal = pProcedure->GetLocalSymbol();

        if (pLocal && ISA(pLocal, ZBBPProcedureSymbol))
        {
            pProcedure = dynamic_cast<ZBBPProcedureSymbol*>(pLocal);
        }
        else
        {
            pProcedure = NULL;
        }
    }

    if (!pProcedure)
    {
        return (float)INT_MAX;
    }

    // From this procedure, check what combination owns us
    size_t Count = pProcedure->GetCombinationCount();

    for (size_t i = 0; i < Count; ++i)
    {
        if (pProcedure->IsDeliverableInString(pProcedure->GetCombinationDeliverables(i),
                                              const_cast<ZBDeliverableLinkSymbol*>(this)->GetSymbolName()))
        {
            return pProcedure->GetCombinationActivationPerc(i);
        }
    }

    // Otherwise, not found
    return (float)INT_MAX;
}

ZBBPProcedureSymbol* ZBDeliverableLinkSymbol::GetSourceProcedure() const
{
    // Retrieve the input procedure name
    CODComponent* pComp = GetSourceComponent();

    if (pComp && ISA(pComp, ZBBPProcedureSymbol))
    {
        return dynamic_cast<ZBBPProcedureSymbol*>(pComp);
    }
    else if (pComp && ISA(pComp, ZBBPDoorSymbol))
    {
        // Locate the previous connection
        // of the twin symbol
        if (!(pComp = dynamic_cast<ZBBPDoorSymbol*>(pComp)->GetTwinDoorSymbol()))
        {
            return NULL;
        }

        CODEdgeArray EnteringEdges;
        size_t EnteringLinkCount = dynamic_cast<ZBBPDoorSymbol*>(pComp)->GetEdgesEntering_Up(EnteringEdges);

        if (EnteringLinkCount > 0)
        {
            // Get the link 
            IODEdge* pIEdge = EnteringEdges.GetAt(0);
            CODLinkComponent* pLink = static_cast<CODLinkComponent*>(pIEdge);

            if (!pLink || !ISA(pLink, ZBDeliverableLinkSymbol))
            {
                return NULL;
            }

            // Call the same function from the twin deliverable
            return dynamic_cast<ZBDeliverableLinkSymbol*>(pLink)->GetSourceProcedure();
        }

        // Otherwise, problem, then return NULL at the end of the function
    }
    else if (pComp && ISA(pComp, ZBBPPageSymbol))
    {
        // Locate the previous connection
        // of the twin symbol
        if (!(pComp = dynamic_cast<ZBBPPageSymbol*>(pComp)->GetTwinPageSymbol()))
        {
            return NULL;
        }

        CODEdgeArray EnteringEdges;
        size_t EnteringLinkCount = dynamic_cast<ZBBPPageSymbol*>(pComp)->GetEdgesEntering_Up(EnteringEdges);

        if (EnteringLinkCount > 0)
        {
            // Get the link 
            IODEdge* pIEdge = EnteringEdges.GetAt(0);
            CODLinkComponent* pLink = static_cast<CODLinkComponent*>(pIEdge);

            if (!pLink || !ISA(pLink, ZBDeliverableLinkSymbol))
            {
                return NULL;
            }

            // Call the same function from the twin deliverable
            return dynamic_cast<ZBDeliverableLinkSymbol*>(pLink)->GetSourceProcedure();
        }

        // Otherwise, problem, then return NULL at the end of the function
    }

    // Not a procedure connected to
    return NULL;
}

ZBBPProcedureSymbol* ZBDeliverableLinkSymbol::GetTargetProcedure() const
{
    // Retrieve the target connected symbol
    CODComponent* pComp = GetTargetComponent();

    if (pComp && ISA(pComp, ZBBPProcedureSymbol))
    {
        return dynamic_cast<ZBBPProcedureSymbol*>(pComp);
    }
    else if (pComp && ISA(pComp, ZBBPDoorSymbol))
    {
        // Locate the previous connection
        // of the twin symbol
        if (!(pComp = dynamic_cast<ZBBPDoorSymbol*>(pComp)->GetTwinDoorSymbol()))
        {
            return NULL;
        }

        CODEdgeArray LeavingEdges;
        size_t LeavingLinkCount = dynamic_cast<ZBBPDoorSymbol*>(pComp)->GetEdgesLeaving_Down(LeavingEdges);

        if (LeavingLinkCount > 0)
        {
            // Get the link 
            IODEdge*            pIEdge = LeavingEdges.GetAt(0);
            CODLinkComponent*    pLink = static_cast<CODLinkComponent*>(pIEdge);

            if (!pLink || !ISA(pLink, ZBDeliverableLinkSymbol))
            {
                return NULL;
            }

            // Call the same function from the twin deliverable
            return dynamic_cast<ZBDeliverableLinkSymbol*>(pLink)->GetTargetProcedure();
        }
        // Otherwise, problem, then return NULL at the end of the function
    }
    else if (pComp && ISA(pComp, ZBBPPageSymbol))
    {
        // Locate the previous connection
        // of the twin symbol
        if (!(pComp = dynamic_cast<ZBBPPageSymbol*>(pComp)->GetTwinPageSymbol()))
        {
            return NULL;
        }

        CODEdgeArray LeavingEdges;
        size_t LeavingLinkCount = dynamic_cast<ZBBPPageSymbol*>(pComp)->GetEdgesLeaving_Down(LeavingEdges);

        if (LeavingLinkCount > 0)
        {
            // Get the link 
            IODEdge*            pIEdge = LeavingEdges.GetAt(0);
            CODLinkComponent*    pLink = static_cast<CODLinkComponent*>(pIEdge);

            if (!pLink || !ISA(pLink, ZBDeliverableLinkSymbol))
            {
                return NULL;
            }

            // Call the same function from the twin deliverable
            return dynamic_cast<ZBDeliverableLinkSymbol*>(pLink)->GetTargetProcedure();
        }

        // Otherwise, problem, then return NULL at the end of the function
    }

    // Not a procedure connected to
    return NULL;
}

PSS_ProcessGraphModelMdl* ZBDeliverableLinkSymbol::GetComingFromModel() const
{
    // Retrieve the input procedure name
    CODComponent* pComp = GetSourceComponent();

    if (pComp && ISA(pComp, ZBBPDoorSymbol))
    {
        // Locate the previous connection
        // of the twin symbol
        ZBBPDoorSymbol* pSrcDoor = dynamic_cast<ZBBPDoorSymbol*>(pComp)->GetTwinDoorSymbol();

        if (pSrcDoor)
        {
            return pSrcDoor->GetModelDoor();
        }

        // Otherwise, return NULL at the end of the function
    }

    return NULL;
}

ZBBPProcessSymbol* ZBDeliverableLinkSymbol::GetComingFromProcess() const
{
    // Retrieve the coming from model
    PSS_ProcessGraphModelMdl* pModel = GetComingFromModel();

    if (pModel)
    {
        CODModel* pRootModel = const_cast<ZBDeliverableLinkSymbol*>(this)->GetRootModel();

        if (pRootModel && ISA(pRootModel, PSS_ProcessGraphModelMdl))
        {
            // Find the symbol pointed by the door model
            CODComponentSet* pSet = dynamic_cast<PSS_ProcessGraphModelMdl*>(pRootModel)->FindSymbol(pModel);

            if (pSet)
            {
                int Count = pSet->GetSize();

                for (int i = 0; i < Count; ++i)
                {
                    if (pSet->GetAt(i) && ISA(pSet->GetAt(i), ZBBPProcessSymbol))
                    {
                        return dynamic_cast<ZBBPProcessSymbol*>(pSet->GetAt(i));
                    }
                }
            }
        }

        // Otherwise, return NULL at the end of the function
    }

    return NULL;
}

PSS_ProcessGraphModelMdl* ZBDeliverableLinkSymbol::GetGoingToModel() const
{
    // Retrieve the target connected symbol
    CODComponent* pComp = GetTargetComponent();

    if (pComp && ISA(pComp, ZBBPDoorSymbol))
    {
        // Locate the previous connection
        // of the twin symbol
        ZBBPDoorSymbol* pSrcDoor = dynamic_cast<ZBBPDoorSymbol*>(pComp)->GetTwinDoorSymbol();

        if (pSrcDoor)
        {
            return pSrcDoor->GetModelDoor();
        }

        // Otherwise, return NULL at the end of the function
    }

    return NULL;
}

ZBBPProcessSymbol* ZBDeliverableLinkSymbol::GetGoingToProcess() const
{
    // Retrieve the going to model
    PSS_ProcessGraphModelMdl* pModel = GetGoingToModel();

    if (pModel)
    {
        CODModel* pRootModel = const_cast<ZBDeliverableLinkSymbol*>(this)->GetRootModel();

        if (pRootModel && ISA(pRootModel, PSS_ProcessGraphModelMdl))
        {
            // Find the symbol pointed by the door model
            CODComponentSet* pSet = dynamic_cast<PSS_ProcessGraphModelMdl*>(pRootModel)->FindSymbol(pModel);

            if (pSet)
            {
                int Count = pSet->GetSize();

                for (int i = 0; i < Count; ++i)
                {
                    if (pSet->GetAt(i) && ISA(pSet->GetAt(i), ZBBPProcessSymbol))
                    {
                        return dynamic_cast<ZBBPProcessSymbol*>(pSet->GetAt(i));
                    }
                }
            }
        }

        // Otherwise, return NULL at the end of the function
    }

    return NULL;
}

// ********************************************* Fonctions Is ***********************************************

bool ZBDeliverableLinkSymbol::IsMasterOfCombination() const
{
    // Retrieve the destination procedure
    ZBBPProcedureSymbol* pProcedure = GetTargetProcedure();

    // Test if it is a local symbol
    if (pProcedure && !pProcedure->IsLocal())
    {
        // Locate the local symbol
        CODComponent* pLocal = pProcedure->GetLocalSymbol();

        if (pLocal && ISA(pLocal, ZBBPProcedureSymbol))
        {
            pProcedure = dynamic_cast<ZBBPProcedureSymbol*>(pLocal);
        }
        else
        {
            pProcedure = NULL;
        }
    }

    if (!pProcedure)
    {
        return false;
    }

    // From this procedure, check what combination has a master defined as us
    size_t Count = pProcedure->GetCombinationCount();

    for (size_t i = 0; i < Count; ++i)
    {
        if (pProcedure->GetCombinationMaster(i) == const_cast<ZBDeliverableLinkSymbol*>(this)->GetSymbolName())
        {
            return true;
        }
    }

    // Otherwise, not a master
    return false;
}

bool ZBDeliverableLinkSymbol::IsInitial() const
{
    // Retrieve the source connected symbol
    CODComponent* pComp = GetSourceComponent();
    return (pComp && ISA(pComp, ZBBPStartSymbol)) ? true : false;
}

bool ZBDeliverableLinkSymbol::IsFinal() const
{
    // Retrieve the target connected symbol
    CODComponent* pComp = GetTargetComponent();
    return (pComp && ISA(pComp, ZBBPStopSymbol)) ? true : false;
}

bool ZBDeliverableLinkSymbol::IsInterProcess() const
{
    // Retrieve the source connected symbol
    CODComponent* pSourceComp = GetSourceComponent();

    // Retrieve the target connected symbol
    CODComponent* pTargetComp = GetTargetComponent();

    return ((pSourceComp && ISA(pSourceComp, ZBBPDoorSymbol)) ||
        (pTargetComp && ISA(pTargetComp, ZBBPDoorSymbol))) ? true : false;
}

// **********************************************************************************************************
// *                                               Sérialisation                                            *
// **********************************************************************************************************

void ZBDeliverableLinkSymbol::Serialize(CArchive& ar)
{
    // Serialize the link symbol
    PSS_LinkSymbol::Serialize(ar);

    // Only if the object is serialize from and to a document
    if (ar.m_pDocument)
    {
        m_Quantity.Serialize(ar);
        m_SimProperties.Serialize(ar);

        // JMR-MODIF - Le 10 juin 2007 - Ajout du code pour la sérialisation des risques.
        if (dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 27)
        {
            m_Risks.Serialize(ar);
        }

        if (ar.IsStoring() ||
            dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 19)
        {
            m_CostDeliverableProperties.Serialize(ar);

            // JMR-MODIF - Le 7 septembre 2005 - Suppression de l'ajout du 4 août : Problème de corruption sur les
            // anciens fichiers !...
            // JMR-MODIF - Le 4 août 2005 - Ajout du code pour la mise à jour des anciens modèles.
            //if ( dynamic_cast<ZDBaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 22 )
            //{
            //    SetVisualInfo((int)(m_CostDeliverableProperties.GetOutWorkloadPercent()*100));
            //    RedrawSymbol();
            //}
        }
        else
        {
            // Transfert the properties to new format
            PSS_CostPropertiesDeliverableBP* pCostProps =
                (PSS_CostPropertiesDeliverableBP*)GetProperty(ZS_BP_PROP_DELIVERABLE_COST);

            if (pCostProps)
            {
                SetProcessingTime(pCostProps->GetProcessingTime());
                SetInWorkloadPercent(pCostProps->GetInWorkloadPercent());
                SetOutWorkloadPercent(pCostProps->GetOutWorkloadPercent());
                SetUnitaryCost(pCostProps->GetUnitaryCost());
            }
        }

        if (ar.IsStoring())
        {
            m_UnitProp.Serialize(ar);

            // JMR-MODIF - Le 26 novembre 2006 - Ajout de la sérialisation des règles.
            m_Rules.Serialize(ar);
        }
        else
        {
            if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 20)
            {
                m_UnitProp.Serialize(ar);
            }

            // JMR-MODIF - Le 26 novembre 2006 - Ajout de la sérialisation des règles.
            if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 26)
            {
                m_Rules.Serialize(ar);
            }
        }
    }
}
