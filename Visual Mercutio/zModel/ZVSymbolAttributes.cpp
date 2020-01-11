// ZVSymbolAttributes.cpp: implementation of the ZVSymbolAttributes class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZVSymbolAttributes.h"

#include "ZUODSymbolManipulator.h"

// Resource include
#include "zModelRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 septembre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile (en commentaires).

//////////////////////////////////////////////////////////////////////
// Constant definition
const int        gEditBoxSpaceFromBorder = 1;
const int        gSplitterLineSpaceFromBorder = 1;

//////////////////////////////////////////////////////////////////////
// Constant definition
static int        gSplitterPositionY = -1;
static int        gMaxUp = 0;
static int        gMaxDown = 0;

static bool        gInMoveSplitterMode = false;
static bool        gMoveSplitter1 = false;
static bool        gMoveSplitter2 = false;

static CRect     gInitialSymbolRect(0, 0, 0, 0);
static CPoint     gInitialPoint(0, 0);
static CPoint     gLastPoint(0, 0);

BOOL ZVSymbolAttributes::InitializeAttributeAreas()
{
    // Set all internal components to NULL
    // After the creation from resource or file, some internal
    // can be assigned to a pointer
    m_pNameEditText = NULL;
    m_pCommentEditText = NULL;
    m_pAttributeEditText = NULL;
    m_pSplitterComponent1 = NULL;
    m_pSplitterComponent2 = NULL;

    // Check the area text box fill properties
    if (!UseDynamicArea() || !GetEditBoxArea())
    {
        return TRUE;
    }

    // Test if we need to include the name area
    if (m_pSymbol->IncludeNameArea())
    {
        // First, create the name Text zone if it does not exist
        if (!ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                               M_SymbolNameComponentControlLabel))
        {
            m_pSymbol->CreateAndReplaceEditText(M_SymbolNameComponentControlLabel);

            // Sets the right content
            CODTextComponent* pText = GetSymbolNameTextEdit();

            if (pText)
            {
                pText->SetText(m_pSymbol->GetSymbolName());

                // Sets the right default
                pText->SetValue(OD_PROP_AUTOSIZE, FALSE);
                pText->SetValue(OD_PROP_WORDBREAK, TRUE);
                pText->SetValue(OD_PROP_MULTILINE, TRUE);
                pText->SetValue(OD_PROP_TRANSPARENT, TRUE);

                // Set transparent
                // JMR-MODIF - Le 31 mai 2005 - Conversion explicite remplace le cast. La conversion explicite
                // donne un résultat identique sur l'objet casté en classe de base, tandis que l'ancienne
                // implémentation (dynamic_cast) provoque une exception dans le compilateur VC.NET
                CODFillProperties* pFillProps = (CODFillProperties*)pText->GetProperty(OD_PROP_FILL);
                //                CODFillProperties* pFillProps = dynamic_cast<CODFillProperties*>( pText->GetProperty( OD_PROP_FILL ) );
                CODFillProperties FillProps(*pFillProps);
                FillProps.SetTransparent(TRUE);
                pText->SetProperty(&FillProps);

                // Can't be selected
                CODEditProperties* pEdit = (CODEditProperties*)pText->GetProperty(OD_PROP_EDIT);
                CODEditProperties editChange(*pEdit);
                editChange.SetCanSelect(FALSE);
                pText->SetProperty(&editChange);

                // No line
                CODLineProperties* pLine = (CODLineProperties*)pText->GetProperty(OD_PROP_LINE);
                CODLineProperties lineProp(*pLine);
                lineProp.SetTransparent(TRUE);
                pText->SetProperty(&lineProp);

                // Change font
                CODFontProperties* pFontProp = (CODFontProperties*)pText->GetProperty(OD_PROP_FONT);
                CODFontProperties FontProp(*pFontProp);
                FontProp.SetFaceName(_T("Arial"));
                FontProp.SetWeight(FW_BOLD);
                FontProp.SetPointSize(8);
                pText->SetProperty(&FontProp);
            }
        }

        // Now check if necessary to hide the attribute area and the splitter
        if (!IsNameAreaVisible())
        {
            if (GetSymbolNameTextEdit())
            {
                GetSymbolNameTextEdit()->SetVisible(FALSE);
            }
        }
    }
    else
    {
        // If we don't need a name area, check if exist and remove it
        CODComponent* pComp = ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                                                M_SymbolNameComponentControlLabel);

        if (pComp && ISA(pComp, CODTextComponent))
        {
            // Now remove the edit.
            ZUODSymbolManipulator::RemoveSymbol(dynamic_cast<CODComponent*>(m_pSymbol), pComp);
        }
    }

    // Test if we need to include the attribute area
    if (m_pSymbol->IncludeAttributeArea())
    {
        // Create the attribute Text area if it does not exist
        if (!ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                               M_AttributeAreaComponentLabel))
        {
            m_pSymbol->CreateAndReplaceEditText(M_AttributeAreaComponentLabel);

            CODTextComponent* pText = GetAttributeTextEdit();

            if (pText)
            {
                pText->SetValue(OD_PROP_AUTOSIZE, FALSE);
                pText->SetValue(OD_PROP_WORDBREAK, TRUE);
                pText->SetValue(OD_PROP_MULTILINE, TRUE);
                pText->SetValue(OD_PROP_HORZ_ALIGNMENT, DT_LEFT);
                pText->SetValue(OD_PROP_VERT_ALIGNMENT, DT_TOP);
                pText->SetValue(OD_PROP_TRANSPARENT, TRUE);

                // Set transparent
                // JMR-MODIF - Le 31 mai 2005 - Conversion explicite remplace le cast. La conversion explicite
                // donne un résultat identique sur l'objet casté en classe de base, tandis que l'ancienne
                // implémentation (dynamic_cast) provoque une exception dans le compilateur VC.NET
                CODFillProperties* pFillProps = (CODFillProperties*)pText->GetProperty(OD_PROP_FILL);
                //                CODFillProperties* pFillProps = dynamic_cast<CODFillProperties*>(pText->GetProperty(OD_PROP_FILL));
                CODFillProperties FillProps(*pFillProps);
                FillProps.SetTransparent(TRUE);
                pText->SetProperty(&FillProps);

                // Can't be selected
                CODEditProperties* pEdit = (CODEditProperties*)pText->GetProperty(OD_PROP_EDIT);
                CODEditProperties editChange(*pEdit);
                editChange.SetCanSelect(FALSE);
                pText->SetProperty(&editChange);

                // No line
                CODLineProperties* pLine = (CODLineProperties*)pText->GetProperty(OD_PROP_LINE);
                CODLineProperties lineProp(*pLine);
                lineProp.SetTransparent(TRUE);
                pText->SetProperty(&lineProp);

                // Change font
                CODFontProperties* pFontProp = (CODFontProperties*)pText->GetProperty(OD_PROP_FONT);
                CODFontProperties FontProp(*pFontProp);
                FontProp.SetFaceName(_T("Arial"));
                FontProp.SetWeight(FW_NORMAL);
                FontProp.SetPointSize(8);
                pText->SetProperty(&FontProp);
            }
        }

        // If we do have an attribute area, then check for the splitter1
        CODComponent* pComp = ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                                                M_SplitterComponentLine1);

        // If not found, then we need to create one
        if (!pComp || !ISA(pComp, CODLineComponent))
        {
            CODLineComponent* pSplitter1 = new CODLineComponent;
            ASSERT(pSplitter1);

            // Retrieve the edit box area rectangle
            CODComponent* pEditBoxArea = m_pSymbol->GetEditBoxArea();

            CODComponentPosition* pCompPosition =
                (pEditBoxArea != NULL) ? pEditBoxArea->GetPosition() : dynamic_cast<CODComponent*>(m_pSymbol)->GetPosition();

            CRect rect = pCompPosition->GetBounds();

            // JMR-MODIF - Le 21 septembre 2005 - Nettoyage des memory leaks, suppression de pCompPosition
            // après utilisation.
            if (pCompPosition != NULL)
            {
                delete pCompPosition;
                pCompPosition = NULL;
            }

            // Create the splitter
            POINT ptsLog[2];
            ptsLog[0] = CPoint(rect.left, rect.bottom);
            ptsLog[1] = CPoint(rect.right, rect.bottom);
            pSplitter1->Create(ptsLog, 2);

            // Append the splitter to the symbol
            dynamic_cast<CODComponent*>(m_pSymbol)->AppendChild(pSplitter1);

            // Now, set the new symbol name.
            pSplitter1->SetName(M_SplitterComponentLine1);
        }

        // Now check if necessary to hide the attribute area and the splitter
        if (!IsAttributeAreaVisible())
        {
            if (GetAttributeTextEdit())
            {
                GetAttributeTextEdit()->SetVisible(FALSE);
            }

            if (GetSplitter1())
            {
                GetSplitter1()->SetVisible(FALSE);
            }
        }
    }
    else
    {
        // Otherwise, if there is one, then remove it from the component
        CODComponent* pComp = ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                                                M_AttributeAreaComponentLabel);

        if (pComp && ISA(pComp, CODTextComponent))
        {
            // Now remove the edit.
            ZUODSymbolManipulator::RemoveSymbol(dynamic_cast<CODComponent*>(m_pSymbol), pComp);
        }

        // Remove also the splitter1
        pComp = ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                                  M_SplitterComponentLine1);

        if (pComp && ISA(pComp, CODLineComponent))
        {
            // Now remove the splitter1.
            ZUODSymbolManipulator::RemoveSymbol(dynamic_cast<CODComponent*>(m_pSymbol), pComp);
        }
    }

    // Test if we need to include the description area
    if (m_pSymbol->IncludeDescriptionArea())
    {
        // Create the Comment Text zone if it does not exists
        if (!ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                               M_CommentComponentControlLabel))
        {
            m_pSymbol->CreateAndReplaceEditText(M_CommentComponentControlLabel);

            // Sets the right content
            CODTextComponent* pText = GetCommentTextEdit();

            if (pText)
            {
                pText->SetText(m_pSymbol->GetSymbolComment());

                // Sets the default
                pText->SetValue(OD_PROP_AUTOSIZE, FALSE);
                pText->SetValue(OD_PROP_WORDBREAK, TRUE);
                pText->SetValue(OD_PROP_MULTILINE, TRUE);
                pText->SetValue(OD_PROP_TRANSPARENT, TRUE);

                // Set transparent
                // JMR-MODIF - Le 31 mai 2005 - Conversion explicite remplace le cast. La conversion explicite
                // donne un résultat identique sur l'objet casté en classe de base, tandis que l'ancienne
                // implémentation (dynamic_cast) provoque une exception dans le compilateur VC.NET
                CODFillProperties* pFillProps = (CODFillProperties*)pText->GetProperty(OD_PROP_FILL);
                //                CODFillProperties* pFillProps = dynamic_cast<CODFillProperties*>(pText->GetProperty(OD_PROP_FILL));
                CODFillProperties FillProps(*pFillProps);
                FillProps.SetTransparent(TRUE);
                pText->SetProperty(&FillProps);

                // Can't be selected
                CODEditProperties* pEdit = (CODEditProperties*)pText->GetProperty(OD_PROP_EDIT);
                CODEditProperties editChange(*pEdit);
                editChange.SetCanSelect(FALSE);
                pText->SetProperty(&editChange);

                // No line
                CODLineProperties* pLine = (CODLineProperties*)pText->GetProperty(OD_PROP_LINE);
                CODLineProperties lineProp(*pLine);
                lineProp.SetTransparent(TRUE);
                pText->SetProperty(&lineProp);

                // Change font
                CODFontProperties* pFontProp = (CODFontProperties*)pText->GetProperty(OD_PROP_FONT);
                CODFontProperties FontProp(*pFontProp);
                FontProp.SetFaceName(_T("Arial"));
                FontProp.SetWeight(FW_NORMAL);
                FontProp.SetPointSize(8);
                pText->SetProperty(&FontProp);
            }
        }

        // If we do have a description, then check for the splitter2
        CODComponent* pComp = ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                                                M_SplitterComponentLine2);

        // If not found, then we need to create one
        if (!pComp || !ISA(pComp, CODLineComponent))
        {
            CODLineComponent* pSplitter2 = new CODLineComponent;
            ASSERT(pSplitter2);

            // Retrieve the edit box area rectangle
            CODComponent* pEditBoxArea = m_pSymbol->GetEditBoxArea();

            CODComponentPosition* pCompPosition =
                (pEditBoxArea != NULL) ? pEditBoxArea->GetPosition() : dynamic_cast<CODComponent*>(m_pSymbol)->GetPosition();

            CRect rect = pCompPosition->GetBounds();

            // JMR-MODIF - Le 21 septembre 2005 - Nettoyage des memory leaks, suppression de pCompPosition
            // après utilisation.
            if (pCompPosition != NULL)
            {
                delete pCompPosition;
                pCompPosition = NULL;
            }

            // Create the splitter
            POINT ptsLog[2];
            ptsLog[0] = CPoint(rect.left, rect.bottom);
            ptsLog[1] = CPoint(rect.right, rect.bottom);
            pSplitter2->Create(ptsLog, 2);

            // Append the splitter to the symbol
            dynamic_cast<CODComponent*>(m_pSymbol)->AppendChild(pSplitter2);

            // Now, set the new symbol name.
            pSplitter2->SetName(M_SplitterComponentLine2);
        }

        // Now check if necessary to hide the comment area and the splitter
        if (!IsDescriptionsAreaVisible())
        {
            if (GetCommentTextEdit())
            {
                GetCommentTextEdit()->SetVisible(FALSE);
            }

            if (GetSplitter2())
            {
                GetSplitter2()->SetVisible(FALSE);
            }
        }
    }
    else
    {
        // Otherwise, if there is one, then remove it from the component
        CODComponent* pComp = ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                                                M_CommentComponentControlLabel);

        if (pComp && ISA(pComp, CODTextComponent))
        {
            // Now remove the edit.
            ZUODSymbolManipulator::RemoveSymbol(dynamic_cast<CODComponent*>(m_pSymbol), pComp);
        }

        // Remove also the splitter2
        pComp = ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                                  M_SplitterComponentLine2);

        if (pComp && ISA(pComp, CODLineComponent))
        {
            // Now remove the splitter2.
            ZUODSymbolManipulator::RemoveSymbol(dynamic_cast<CODComponent*>(m_pSymbol), pComp);
        }
    }

    // If it is not necessary to reinitialize area, then return true
    if (!m_ReinitializeAreaAtCreation)
    {
        return TRUE;
    }

    bool NameAreaMustBeShown = false;
    bool AttributeAreaMustBeShown = false;
    bool DescriptionAreaMustBeShown = false;

    bool bIsNameAreaVisible = false;
    bool bIsAttributeAreaVisible = false;
    bool bIsDescriptionsAreaVisible = false;

    if (m_pSymbol->IncludeNameArea())
    {
        // The area must be visible
        NameAreaMustBeShown = true;
        bIsNameAreaVisible = IsNameAreaVisible();
        DisplayNameArea();
    }

    if (m_pSymbol->IncludeAttributeArea())
    {
        // The area must be visible
        AttributeAreaMustBeShown = true;
        bIsAttributeAreaVisible = IsAttributeAreaVisible();
        DisplayAttributeArea();
    }

    if (m_pSymbol->IncludeDescriptionArea())
    {
        // The area must be visible
        DescriptionAreaMustBeShown = true;
        bIsDescriptionsAreaVisible = IsDescriptionsAreaVisible();
        DisplayDescriptionArea();
    }

    // Now adjust the different areas and 
    // show all areas.
    AdjustAreaPosition();

    // Put back initial states
    if (NameAreaMustBeShown)
    {
        DisplayNameArea(bIsNameAreaVisible);
    }

    if (AttributeAreaMustBeShown)
    {
        DisplayAttributeArea(bIsAttributeAreaVisible);
    }

    if (DescriptionAreaMustBeShown)
    {
        DisplayDescriptionArea(bIsDescriptionsAreaVisible);
    }

    // Let select the symbol
    CODEditProperties* pPropEdit =
        (CODEditProperties*) dynamic_cast<CODComponent*>(m_pSymbol)->GetProperty(OD_PROP_EDIT);

    if (pPropEdit)
    {
        CODEditProperties PropEdit(*pPropEdit);
        PropEdit.SetCanSelect(TRUE);
        dynamic_cast<CODComponent*>(m_pSymbol)->SetProperty(&PropEdit);
    }

    return TRUE;
}

//////////////////////////////////////////////////////////////////////
// Assignement operator
//////////////////////////////////////////////////////////////////////

ZVSymbolAttributes& ZVSymbolAttributes::operator=(const ZVSymbolAttributes& src)
{
    m_UseDynamicArea = src.m_UseDynamicArea;
    m_DisplayNameArea = src.m_DisplayNameArea;
    m_DisplayDescriptionArea = src.m_DisplayDescriptionArea;
    m_DisplayAttributeArea = src.m_DisplayAttributeArea;
    m_Attributes = src.m_Attributes;
    m_RelativeCoordinates = src.m_RelativeCoordinates;
    m_ReinitializeAreaAtCreation = src.m_ReinitializeAreaAtCreation;

    return *this;
}

CODComponent* ZVSymbolAttributes::GetEditBoxArea()
{
    ASSERT(m_pSymbol != NULL);

    if (!m_pEditBoxArea)
    {
        m_pEditBoxArea = ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                                           M_EditAreaComponentControlLabel);

        // If not found, try to locate label
        if (!m_pEditBoxArea)
        {
            m_pEditBoxArea = ZUODSymbolManipulator::FindLabel(dynamic_cast<CODSymbolComponent*>(m_pSymbol),
                                                              M_EditAreaComponentControlLabel);
        }
    }

    return m_pEditBoxArea;
}

CODTextComponent* ZVSymbolAttributes::GetSymbolNameTextEdit()
{
    ASSERT(m_pSymbol != NULL);

    if (!m_pNameEditText)
    {
        CODComponent* pFound = ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                                                 M_SymbolNameComponentControlLabel);

        if (pFound && ISA(pFound, CODTextComponent))
        {
            m_pNameEditText = (CODTextComponent*)pFound;
        }
    }

    return m_pNameEditText;
}

CODTextComponent* ZVSymbolAttributes::GetCommentTextEdit()
{
    ASSERT(m_pSymbol != NULL);

    if (!m_pCommentEditText)
    {
        CODComponent* pFound = ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                                                 M_CommentComponentControlLabel);

        if (pFound && ISA(pFound, CODTextComponent))
        {
            m_pCommentEditText = (CODTextComponent*)pFound;
        }
    }

    return m_pCommentEditText;
}

CODTextComponent* ZVSymbolAttributes::GetAttributeTextEdit()
{
    ASSERT(m_pSymbol != NULL);

    if (!m_pAttributeEditText)
    {
        CODComponent* pFound = ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                                                 M_AttributeAreaComponentLabel);

        if (pFound && ISA(pFound, CODTextComponent))
        {
            m_pAttributeEditText = (CODTextComponent*)pFound;
        }
    }

    return m_pAttributeEditText;
}

CODLineComponent* ZVSymbolAttributes::GetSplitter1()
{
    ASSERT(m_pSymbol != NULL);

    if (!m_pSplitterComponent1)
    {
        CODComponent* pFound = ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                                                 M_SplitterComponentLine1);

        if (pFound && ISA(pFound, CODLineComponent))
        {
            m_pSplitterComponent1 = (CODLineComponent*)pFound;
        }
    }

    return m_pSplitterComponent1;
}

CODLineComponent* ZVSymbolAttributes::GetSplitter2()
{
    ASSERT(m_pSymbol != NULL);

    if (!m_pSplitterComponent2)
    {
        CODComponent* pFound = ZUODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol),
                                                                 M_SplitterComponentLine2);

        if (pFound && ISA(pFound, CODLineComponent))
        {
            m_pSplitterComponent2 = (CODLineComponent*)pFound;
        }
    }

    return m_pSplitterComponent2;
}

void ZVSymbolAttributes::MoveTo(CODComponent& Comp, CRect& rcPosition)
{
    if (rcPosition.IsRectEmpty())
    {
        return;
    }

    CRect rcBounds = Comp.GetPosition()->GetBounds();
    CSize szTranslate = rcPosition.TopLeft() - rcBounds.TopLeft();

    float fOriginX;
    float fOriginY;
    CODGlobal::GetControlPoint(rcBounds, OD_TOP_LEFT, fOriginX, fOriginY);

    float fScaleX = (float)rcPosition.Width() / (float)rcBounds.Width();
    float fScaleY = (float)rcPosition.Height() / (float)rcBounds.Height();

    CODTransform* pXform = Comp.GetTransform();

    if (pXform == NULL)
    {
        pXform = new CODTransform();
    }

    pXform->Scale(fScaleX, fScaleY, fOriginX, fOriginY);
    pXform->Translate(szTranslate.cx, szTranslate.cy);
    Comp.SetTransform(pXform);
    Comp.OnMove();
}

void ZVSymbolAttributes::MoveTo(CODComponent& Comp, CPoint point)
{
    CRect rc = Comp.GetPosition()->GetBounds();
    CPoint ptOrigin(rc.left, rc.top);
    CPoint ptTranslate(point - ptOrigin);
    Comp.Translate(ptTranslate.x, ptTranslate.y);
}

void ZVSymbolAttributes::Scale(CODComponent& Comp, const CSize& szBounds, const OD_CONTROL_POINT nControlPoint)
{
    if (szBounds.cx == 0 || szBounds.cy == 0)
    {
        return;
    }

    float fOriginX;
    float fOriginY;
    CRect rcBounds = Comp.GetPosition()->GetBounds();
    CODGlobal::GetControlPoint(rcBounds, nControlPoint, fOriginX, fOriginY);

    float fScaleX = (float)szBounds.cx / (float)rcBounds.Width();
    float fScaleY = (float)szBounds.cy / (float)rcBounds.Height();

    Comp.Scale(fScaleX, fScaleY, fOriginX, fOriginY);
}

void ZVSymbolAttributes::AdjustElementPosition()
{}

void ZVSymbolAttributes::AdjustAreaPosition(CODLineComponent* pComp /*= NULL*/, int y /*= -1*/)
{
    if (!UseDynamicArea())
    {
        return;
    }

    ASSERT(m_pSymbol != NULL);

    size_t    CounterSplitter = 0;
    bool    Redraw = false;
    bool    NameAreaMustBeShown = false;
    bool    AttributeAreaMustBeShown = false;
    bool    DescriptionAreaMustBeShown = false;

    int        YPositionSplitter1;
    int        YPositionSplitter2;

    // Check the area text box fill properties
    if (!GetEditBoxArea())
    {
        return;
    }

    // We need to check all the area and if they are
    // visible and well placed

    // First, sets the right flag
    if (m_pSymbol->IncludeNameArea() && IsNameAreaVisible())
    {
        // The area must be visible
        NameAreaMustBeShown = true;
        ++CounterSplitter;
    }

    if (m_pSymbol->IncludeAttributeArea() && IsAttributeAreaVisible())
    {
        // The area must be visible
        AttributeAreaMustBeShown = true;
        ++CounterSplitter;
    }

    if (m_pSymbol->IncludeDescriptionArea() && IsDescriptionsAreaVisible())
    {
        // The area must be visible
        DescriptionAreaMustBeShown = true;
        ++CounterSplitter;
    }

    // Retrieve the component position
    CODComponentPosition* pCompPosition = dynamic_cast<CODComponent*>(m_pSymbol)->GetPosition();
    CRect rectSymbol = pCompPosition->GetBounds();

    // JMR-MODIF - Le 21 septembre 2005 - Nettoyage des memory leaks, suppression de pCompPosition après utilisation.
    if (pCompPosition != NULL)
    {
        delete pCompPosition;
        pCompPosition = NULL;
    }

    CODComponent* pEditBoxArea = GetEditBoxArea();

    CODComponentPosition* pAreaPosition =
        (pEditBoxArea != NULL) ? pEditBoxArea->GetPosition() : dynamic_cast<CODComponent*>(m_pSymbol)->GetPosition();

    CRect rect = pAreaPosition->GetBounds();

    // JMR-MODIF - Le 21 septembre 2005 - Nettoyage des memory leaks, suppression de pAreaPosition après utilisation.
    if (pAreaPosition != NULL)
    {
        delete pAreaPosition;
        pAreaPosition = NULL;
    }

    CRect rectEdgeRgn = pEditBoxArea->GetEdgeRgn().GetBounds();
    int OffsetLeft = rect.left - rectSymbol.left;
    int OffsetTop = rect.top - rectSymbol.top;

    // Tests the number of splitter necessary to show or hide
    if (CounterSplitter > 2)
    {
        // Then move the splitters
        // Resize edit control, only if the rect is not empty
        if (!rect.IsRectEmpty())
        {
            int SegmentHeight;

            if (m_RelativeCoordinates)
            {
                SegmentHeight = (rectEdgeRgn.Height() - (2 * gEditBoxSpaceFromBorder)) / 3;
            }
            else
            {
                SegmentHeight = (rect.Height() - (2 * gEditBoxSpaceFromBorder)) / 3;
            }

            // If the splitter is not visible, then we need to show
            // it to calculate its new position. We need also to show
            // the corresponding edit and to calculate it new position also
            if (GetSplitter1() && GetCommentTextEdit() && GetSymbolNameTextEdit())
            {
                CODLineComponent* pSplitter1 = GetSplitter1();
                CODTextComponent* pTextComment = GetCommentTextEdit();
                CODTextComponent* pTextName = GetSymbolNameTextEdit();

                // Show the splitter and the text box
                pSplitter1->SetVisible(TRUE);
                pTextComment->SetVisible(TRUE);
                pTextName->SetVisible(TRUE);

                // Sets the redraw flag
                Redraw = true;

                if (m_RelativeCoordinates)
                {
                    // Move splitter in relative
                    CRect rcSplitter1 = pSplitter1->GetEdgeRgn().GetBounds();
                    rcSplitter1.left = rectEdgeRgn.left + gSplitterLineSpaceFromBorder;

                    // Test if this is for this splitter
                    if (pComp == pSplitter1)
                    {
                        rcSplitter1.top = (y - rect.top + OffsetTop) * rectEdgeRgn.Height() / rect.Height();
                        rcSplitter1.bottom = rcSplitter1.top;

                        // Save the y position of the splitter
                        YPositionSplitter1 = (y - rect.top + OffsetTop);// - rectEdgeRgn.top;
                    }
                    else
                    {
                        // Define the default
                        if (pComp == NULL)
                        {
                            rcSplitter1.top = rectEdgeRgn.top + SegmentHeight + gEditBoxSpaceFromBorder;
                            rcSplitter1.bottom = rcSplitter1.top;
                        }

                        // Save the y position of the splitter
                        YPositionSplitter1 = rcSplitter1.top;
                    }

                    rcSplitter1.right = rcSplitter1.left + rectEdgeRgn.Width() - gSplitterLineSpaceFromBorder;

                    // Scale the splitter
                    float fOriginX;
                    float fOriginY;
                    pSplitter1->GetControlPoint(OD_TOP_LEFT, fOriginX, fOriginY);
                    CRect rcBounds = pSplitter1->GetEdgeRgn().GetBounds();
                    float fScaleX = (float)rcSplitter1.Width() / (float)rcBounds.Width();
                    pSplitter1->Scale(fScaleX, 1, fOriginX, fOriginY);
                    pSplitter1->MoveTo(CPoint(rcSplitter1.left, rcSplitter1.top));
                }
                else
                {
                    // Move the splitter
                    CODComponentPosition* pPosition = pSplitter1->GetPosition();

                    ASSERT(pPosition);

                    CRect rcSplitter1 = pPosition->GetBounds();
                    rcSplitter1.left = rect.left + gSplitterLineSpaceFromBorder;

                    // Test if this is for this splitter
                    if (pComp == pSplitter1)
                    {
                        rcSplitter1.top = rcSplitter1.bottom = y;
                    }
                    else
                    {
                        // Define the default
                        if (pComp == NULL)
                        {
                            rcSplitter1.top = rect.top + SegmentHeight + gEditBoxSpaceFromBorder;
                            rcSplitter1.bottom = rcSplitter1.top;
                        }
                    }

                    rcSplitter1.right = rect.right - gSplitterLineSpaceFromBorder;

                    // Save the y position of the splitter
                    YPositionSplitter1 = rcSplitter1.top;

                    // Scale the splitter
                    float fOriginX;
                    float fOriginY;
                    pSplitter1->GetControlPoint(OD_TOP_LEFT, fOriginX, fOriginY);

                    CRect rcBounds = pPosition->GetBounds();
                    float fScaleX = (float)rcSplitter1.Width() / (float)rcBounds.Width();
                    pSplitter1->Scale(fScaleX, 1, fOriginX, fOriginY);
                    pSplitter1->MoveTo(CPoint(rcSplitter1.left, rcSplitter1.top));
                }

                // Move the two text box
                // First, the name
                if (m_RelativeCoordinates)
                {
                    // Move the text box in relative
                    CRect rcTextBox = pTextName->GetEdgeRgn().GetBounds();
                    rcTextBox.left = rectEdgeRgn.left + gEditBoxSpaceFromBorder;

                    // Test if this is for this splitter
                    if (pComp == pSplitter1 && y != 1)
                    {
                        rcTextBox.top = rectEdgeRgn.top + gEditBoxSpaceFromBorder;
                        rcTextBox.bottom = (y - rect.top + OffsetTop) * rectEdgeRgn.Height() / rect.Height();
                    }
                    else
                    {
                        rcTextBox.top = rectEdgeRgn.top + gEditBoxSpaceFromBorder;
                        rcTextBox.bottom = YPositionSplitter1;
                    }

                    rcTextBox.right = rcTextBox.left + rectEdgeRgn.Width() - gEditBoxSpaceFromBorder;

                    pTextName->MoveTo(rcTextBox);
                }
                else
                {
                    // Move in absolute
                    CODComponentPosition* pPosition = pTextName->GetPosition();
                    ASSERT(pPosition);

                    CRect rcTextBox = pPosition->GetBounds();
                    rcTextBox.left = rect.left + gEditBoxSpaceFromBorder - rectSymbol.left;

                    // Test if this is for this splitter
                    if (pComp == pSplitter1 && y != 1)
                    {
                        rcTextBox.top -= rectSymbol.top;
                        rcTextBox.bottom = y - rectSymbol.top;
                    }
                    else
                    {
                        rcTextBox.top = rect.top + gEditBoxSpaceFromBorder - rectSymbol.top;
                        rcTextBox.bottom = YPositionSplitter1 - rectSymbol.top;
                    }

                    rcTextBox.right = rect.right - gEditBoxSpaceFromBorder - rectSymbol.left;

                    pTextName->MoveTo(rcTextBox);
                }

                // Second, the comment
                if (m_RelativeCoordinates)
                {
                    // Move in relative
                    CRect rcTextBox = pTextComment->GetEdgeRgn().GetBounds();
                    rcTextBox.left = rectEdgeRgn.left + gEditBoxSpaceFromBorder;

                    // Test if this is for this splitter
                    if (pComp == pSplitter1 && y != 1)
                    {
                        rcTextBox.top = (y - rect.top + OffsetTop) * rectEdgeRgn.Height() / rect.Height();
                    }
                    else
                    {
                        rcTextBox.top = YPositionSplitter1;

                        // If null, then define the default
                        if (pComp == NULL)
                        {
                            rcTextBox.bottom = YPositionSplitter1 + SegmentHeight;
                        }
                        else
                        {
                            // Otherwise, it is the second splitter,
                            // then calculate its position
                            rcTextBox.bottom = (y - rect.top + OffsetTop) * rectEdgeRgn.Height() / rect.Height();
                        }
                    }

                    rcTextBox.right = rcTextBox.left + rectEdgeRgn.Width() - gEditBoxSpaceFromBorder;

                    pTextComment->MoveTo(rcTextBox);
                }
                else
                {
                    // Move in absolute
                    CODComponentPosition* pPosition = pTextComment->GetPosition();
                    ASSERT(pPosition);

                    CRect rcTextBox = pPosition->GetBounds();
                    rcTextBox.left = rect.left + gEditBoxSpaceFromBorder - rectSymbol.left;

                    // Test if this is for this splitter
                    if (pComp == pSplitter1 && y != 1)
                    {
                        rcTextBox.top = y - rectSymbol.top;

                        // Don't adjust the bottom
                        rcTextBox.bottom -= rectSymbol.top;
                    }
                    else
                    {
                        rcTextBox.top = YPositionSplitter1 - rectSymbol.top;

                        // Define the default
                        if (pComp == NULL)
                        {
                            rcTextBox.bottom =
                                rect.top + (SegmentHeight * 2) + gEditBoxSpaceFromBorder - 2 - rectSymbol.top;
                        }
                        else rcTextBox.bottom = y;
                    }

                    rcTextBox.right = rect.right - gEditBoxSpaceFromBorder - rectSymbol.left;

                    pTextComment->MoveTo(rcTextBox);
                }
            }

            if (GetSplitter2() && GetAttributeTextEdit())
            {
                // Then move the splitter
                CODLineComponent* pSplitter2 = GetSplitter2();
                CODTextComponent* pTextAttribute = GetAttributeTextEdit();

                // Show the splitter and the text box
                pSplitter2->SetVisible(TRUE);
                pTextAttribute->SetVisible(TRUE);

                // Sets the redraw flag
                Redraw = true;

                if (m_RelativeCoordinates)
                {
                    // Move in Relative
                    CRect rcSplitter2 = pSplitter2->GetEdgeRgn().GetBounds();
                    rcSplitter2.left = rectEdgeRgn.left + gSplitterLineSpaceFromBorder;

                    // Test if this is for this splitter
                    if (pComp == pSplitter2 && y != 1)
                    {
                        rcSplitter2.top = (y - rect.top + OffsetTop) * rectEdgeRgn.Height() / rect.Height();
                        rcSplitter2.bottom = rcSplitter2.top;

                        // Save the y position of the splitter
                        YPositionSplitter2 = (y - rect.top + OffsetTop);
                    }
                    else
                    {
                        // Define the default
                        if (pComp == NULL)
                        {
                            rcSplitter2.top = rectEdgeRgn.top + (SegmentHeight * 2) + gEditBoxSpaceFromBorder;
                            rcSplitter2.bottom = rcSplitter2.top;
                        }

                        // Save the y position of the splitter
                        YPositionSplitter2 = rcSplitter2.top;
                    }

                    rcSplitter2.right = rcSplitter2.left + rectEdgeRgn.Width() - gSplitterLineSpaceFromBorder;

                    // Scale the splitter
                    float fOriginX;
                    float fOriginY;
                    pSplitter2->GetControlPoint(OD_TOP_LEFT, fOriginX, fOriginY);
                    CRect rcBounds = pSplitter2->GetEdgeRgn().GetBounds();
                    float fScaleX = (float)rcSplitter2.Width() / (float)rcBounds.Width();
                    pSplitter2->Scale(fScaleX, 1, fOriginX, fOriginY);
                    pSplitter2->MoveTo(CPoint(rcSplitter2.left, rcSplitter2.top));
                }
                else
                {
                    // Move in absolute
                    CODComponentPosition* pPosition = pSplitter2->GetPosition();

                    ASSERT(pPosition);

                    CRect rcSplitter2 = pPosition->GetBounds();
                    rcSplitter2.left = rect.left + gSplitterLineSpaceFromBorder;

                    // Test if this is for this splitter
                    if (pComp == pSplitter2 && y != 1)
                    {
                        rcSplitter2.top = rcSplitter2.bottom = y;
                    }
                    else
                    {
                        // Define the default
                        if (pComp == NULL)
                        {
                            rcSplitter2.top = rect.top + (SegmentHeight * 2) + gEditBoxSpaceFromBorder;
                            rcSplitter2.bottom = rcSplitter2.top;
                        }
                    }

                    rcSplitter2.right = rect.right - gSplitterLineSpaceFromBorder;

                    // Save the y position of the splitter
                    YPositionSplitter2 = rcSplitter2.top;

                    // Scale the splitter
                    float fOriginX;
                    float fOriginY;
                    pSplitter2->GetControlPoint(OD_TOP_LEFT, fOriginX, fOriginY);
                    CRect rcBounds = pPosition->GetBounds();
                    float fScaleX = (float)rcSplitter2.Width() / (float)rcBounds.Width();
                    pSplitter2->Scale(fScaleX, 1, fOriginX, fOriginY);
                    pSplitter2->MoveTo(CPoint(rcSplitter2.left, rcSplitter2.top));
                }

                // Move the text box attribute
                if (m_RelativeCoordinates)
                {
                    // Move in relative
                    CRect rcTextBox = pTextAttribute->GetEdgeRgn().GetBounds();
                    rcTextBox.left = rectEdgeRgn.left + gEditBoxSpaceFromBorder;

                    // Test if this is for this splitter
                    if (pComp == pSplitter2 && y != 1)
                    {
                        rcTextBox.top = (y - rect.top + OffsetTop) * rectEdgeRgn.Height() / rect.Height();

                        // Don't adjust the bottom
                        rcTextBox.bottom = rectEdgeRgn.Height() + OffsetTop - gEditBoxSpaceFromBorder;
                    }
                    else
                    {
                        rcTextBox.top = YPositionSplitter2;
                        rcTextBox.bottom = rectEdgeRgn.Height() + OffsetTop - gEditBoxSpaceFromBorder;
                    }

                    rcTextBox.right = rcTextBox.left + rectEdgeRgn.Width() - gEditBoxSpaceFromBorder;

                    pTextAttribute->MoveTo(rcTextBox);
                }
                else
                {
                    // Move in absolute
                    CODComponentPosition* pPosition = pTextAttribute->GetPosition();
                    ASSERT(pPosition);

                    CRect rcTextBox = pPosition->GetBounds();
                    rcTextBox.left = rect.left + gEditBoxSpaceFromBorder - rectSymbol.left;

                    // Test if this is for this splitter
                    if (pComp == pSplitter2 && y != 1)
                    {
                        rcTextBox.top = y - rectSymbol.top;

                        // Don't adjust the bottom
                        rcTextBox.bottom -= rectSymbol.top;
                    }
                    else
                    {
                        rcTextBox.top = YPositionSplitter2 - rectSymbol.top;
                        rcTextBox.bottom = rect.bottom - gEditBoxSpaceFromBorder - rectSymbol.top;
                    }

                    rcTextBox.right = rect.right - gEditBoxSpaceFromBorder - rectSymbol.left;

                    pTextAttribute->MoveTo(rcTextBox);
                }
            }
        }
    }
    else if (CounterSplitter > 1)
    {
        // Then move the splitter
        // Resize edit control, only if the rect is not empty
        if (!rect.IsRectEmpty())
        {
            int SegmentHeight;

            if (m_RelativeCoordinates)
            {
                SegmentHeight = (rectEdgeRgn.Height() - (2 * gEditBoxSpaceFromBorder)) / 2;
            }
            else
            {
                SegmentHeight = (rect.Height() - (2 * gEditBoxSpaceFromBorder)) / 2;
            }

            // We need only one splitter
            if (GetSplitter1())
            {
                CODLineComponent* pSplitter1 = GetSplitter1();
                pSplitter1->SetVisible(TRUE);

                // Sets the redraw flag
                Redraw = true;

                if (m_RelativeCoordinates)
                {
                    // Move splitter in relative
                    CRect rcSplitter1 = pSplitter1->GetEdgeRgn().GetBounds();
                    rcSplitter1.left = rectEdgeRgn.left + gSplitterLineSpaceFromBorder;

                    // Test if this is for this splitter
                    if (pComp == pSplitter1 && y != 1)
                    {
                        rcSplitter1.top = (y - rect.top + OffsetTop) * rectEdgeRgn.Height() / rect.Height();
                        rcSplitter1.bottom = rcSplitter1.top;

                        // Save the y position of the splitter
                        YPositionSplitter1 = (y - rect.top + OffsetTop);
                    }
                    else
                    {
                        rcSplitter1.top = rectEdgeRgn.top + SegmentHeight + gEditBoxSpaceFromBorder;
                        rcSplitter1.bottom = rcSplitter1.top;

                        // Save the y position of the splitter
                        YPositionSplitter1 = rcSplitter1.top;
                    }

                    rcSplitter1.right = rcSplitter1.left + rectEdgeRgn.Width() - gSplitterLineSpaceFromBorder;

                    // Scale the splitter
                    float fOriginX;
                    float fOriginY;
                    pSplitter1->GetControlPoint(OD_TOP_LEFT, fOriginX, fOriginY);
                    CRect rcBounds = pSplitter1->GetEdgeRgn().GetBounds();
                    float fScaleX = (float)rcSplitter1.Width() / (float)rcBounds.Width();
                    pSplitter1->Scale(fScaleX, 1, fOriginX, fOriginY);
                    pSplitter1->MoveTo(CPoint(rcSplitter1.left, rcSplitter1.top));
                }
                else
                {
                    // In absolute
                    CODComponentPosition* pPosition = pSplitter1->GetPosition();

                    ASSERT(pPosition);

                    CRect rcSplitter1 = pPosition->GetBounds();
                    rcSplitter1.left = rect.left + gSplitterLineSpaceFromBorder;

                    // Test if this is for this splitter
                    if (pComp == pSplitter1 && y != 1)
                    {
                        rcSplitter1.top = y;
                        rcSplitter1.bottom = y;
                    }
                    else
                    {
                        rcSplitter1.top = rect.top + SegmentHeight + gEditBoxSpaceFromBorder;
                        rcSplitter1.bottom = rect.top + SegmentHeight + gEditBoxSpaceFromBorder;
                    }

                    rcSplitter1.right = rect.right - gSplitterLineSpaceFromBorder;

                    // Save the y position of the splitter
                    YPositionSplitter1 = rcSplitter1.top;

                    // Scale the splitter
                    float fOriginX;
                    float fOriginY;
                    pSplitter1->GetControlPoint(OD_TOP_LEFT, fOriginX, fOriginY);
                    CRect rcBounds = pSplitter1->GetBaseRgn().GetBounds();
                    float fScaleX = (float)rcSplitter1.Width() / (float)rcBounds.Width();
                    pSplitter1->Scale(fScaleX, 1, fOriginX, fOriginY);
                    pSplitter1->MoveTo(CPoint(rcSplitter1.left, rcSplitter1.top));
                }

                bool bDoneFirst = false;

                // And finally, 
                // test what text box to reposition between the splitter
                // The name is always the first or the comment
                if (IsNameAreaVisible())
                {
                    CODTextComponent* pTextName = GetSymbolNameTextEdit();

                    if (pTextName)
                    {
                        // Show the symbol name edit box
                        pTextName->SetVisible(TRUE);

                        if (m_RelativeCoordinates)
                        {
                            // Move the text box in relative
                            CRect rcTextBox = pTextName->GetEdgeRgn().GetBounds();
                            rcTextBox.left = rectEdgeRgn.left + gEditBoxSpaceFromBorder;

                            // Test if this is for this splitter
                            if (pComp == pSplitter1 && y != 1)
                            {
                                rcTextBox.top = rectEdgeRgn.top + gEditBoxSpaceFromBorder;
                                rcTextBox.bottom =
                                    (y - rect.top + OffsetTop) * rectEdgeRgn.Height() / rect.Height();
                            }
                            else
                            {
                                rcTextBox.top = rectEdgeRgn.top + gEditBoxSpaceFromBorder;
                                rcTextBox.bottom = YPositionSplitter1;
                            }

                            rcTextBox.right = rcTextBox.left + rectEdgeRgn.Width() - gEditBoxSpaceFromBorder;

                            pTextName->MoveTo(rcTextBox);
                        }
                        else
                        {
                            // Move the text box in absolute
                            CODComponentPosition* pPosition = pTextName->GetPosition();
                            ASSERT(pPosition);

                            CRect rcTextBox = pPosition->GetBounds();
                            rcTextBox.left = rect.left + gEditBoxSpaceFromBorder - rectSymbol.left;

                            // Test if this is for this splitter
                            if (pComp == pSplitter1 && y != 1)
                            {
                                rcTextBox.top = rect.top + gEditBoxSpaceFromBorder - rectSymbol.top;
                                rcTextBox.bottom = y - rectSymbol.top;
                            }
                            else
                            {
                                rcTextBox.top = rect.top + gEditBoxSpaceFromBorder - rectSymbol.top;
                                rcTextBox.bottom = YPositionSplitter1 - rectSymbol.top;
                            }

                            rcTextBox.right = rect.right - gEditBoxSpaceFromBorder - rectSymbol.left;

                            pTextName->MoveTo(rcTextBox);
                        }

                        // Sets the flag
                        bDoneFirst = true;
                    }
                }
                else
                {
                    // We don't need to include this edit are,
                    // Resize it at the bottom of the symbol
                    CODTextComponent* pTextName = GetSymbolNameTextEdit();

                    if (pTextName)
                    {
                        if (m_RelativeCoordinates)
                        {
                            // Move the text box in relative
                            CRect rcTextBox = pTextName->GetEdgeRgn().GetBounds();
                            rcTextBox.left = rectEdgeRgn.left + gEditBoxSpaceFromBorder;
                            rcTextBox.top = rectEdgeRgn.Height() - gEditBoxSpaceFromBorder - 2;
                            rcTextBox.bottom = rectEdgeRgn.Height() - gEditBoxSpaceFromBorder;
                            rcTextBox.right = rectEdgeRgn.Width() - gEditBoxSpaceFromBorder;

                            pTextName->MoveTo(rcTextBox);
                        }
                        else
                        {
                            // Move the text box in absolute
                            CODComponentPosition* pPosition = pTextName->GetPosition();
                            ASSERT(pPosition);

                            CRect rcTextBox = pPosition->GetBounds();
                            rcTextBox.left = rect.left + gEditBoxSpaceFromBorder - rectSymbol.left;
                            rcTextBox.top = rect.bottom - gEditBoxSpaceFromBorder - rectSymbol.top;
                            rcTextBox.bottom = rect.bottom - 1 - rectSymbol.top;
                            rcTextBox.right = rect.right - gEditBoxSpaceFromBorder - rectSymbol.left;

                            pTextName->MoveTo(rcTextBox);
                        }
                    }
                }

                // The description is either the first or the last
                if (IsDescriptionsAreaVisible())
                {
                    CODTextComponent* pTextComment = GetCommentTextEdit();

                    if (pTextComment)
                    {
                        // Show the symbol comment edit box
                        pTextComment->SetVisible(TRUE);

                        if (m_RelativeCoordinates)
                        {
                            // Move the text box in relative
                            CRect rcTextBox = pTextComment->GetEdgeRgn().GetBounds();
                            rcTextBox.left = rectEdgeRgn.left + gEditBoxSpaceFromBorder;

                            // Test if this is for this splitter
                            if (pComp == pSplitter1 && y != 1)
                            {
                                if (bDoneFirst)
                                {
                                    rcTextBox.top =
                                        (y - rect.top + OffsetTop) * rectEdgeRgn.Height() / rect.Height();

                                    rcTextBox.bottom =
                                        rectEdgeRgn.Height() + OffsetTop - gEditBoxSpaceFromBorder;
                                }
                                else
                                {
                                    rcTextBox.top = rectEdgeRgn.top + gEditBoxSpaceFromBorder;
                                    rcTextBox.bottom =
                                        (y - rect.top + OffsetTop) * rectEdgeRgn.Height() / rect.Height();
                                }
                            }
                            else
                            {
                                if (bDoneFirst)
                                {
                                    rcTextBox.top = YPositionSplitter1;
                                    rcTextBox.bottom =
                                        rectEdgeRgn.Height() + OffsetTop - gEditBoxSpaceFromBorder;
                                }
                                else
                                {
                                    rcTextBox.top = rectEdgeRgn.top + gEditBoxSpaceFromBorder;
                                    rcTextBox.bottom = YPositionSplitter1;
                                }
                            }

                            rcTextBox.right = rcTextBox.left + rectEdgeRgn.Width() - gEditBoxSpaceFromBorder;

                            pTextComment->MoveTo(rcTextBox);
                        }
                        else
                        {
                            // Move the text box in absolute
                            CODComponentPosition* pPosition = pTextComment->GetPosition();
                            ASSERT(pPosition);

                            CRect rcTextBox = pPosition->GetBounds();
                            rcTextBox.left = rect.left + gEditBoxSpaceFromBorder - rectSymbol.left;

                            // Test if this is for this splitter
                            if (pComp == pSplitter1 && y != 1)
                            {
                                if (bDoneFirst)
                                {
                                    rcTextBox.top = y - rectSymbol.top;
                                    rcTextBox.bottom -= rectSymbol.top;
                                }
                                else
                                {
                                    rcTextBox.top -= rectSymbol.top;
                                    rcTextBox.bottom = y - rectSymbol.top;
                                }
                            }
                            else
                            {
                                if (bDoneFirst)
                                {
                                    rcTextBox.top = YPositionSplitter1 - rectSymbol.top;
                                    rcTextBox.bottom = rect.bottom - gEditBoxSpaceFromBorder - rectSymbol.top;
                                }
                                else
                                {
                                    rcTextBox.top = rect.top + gEditBoxSpaceFromBorder - rectSymbol.top;
                                    rcTextBox.bottom = YPositionSplitter1 - rectSymbol.top;
                                }
                            }

                            rcTextBox.right = rect.right - gEditBoxSpaceFromBorder - rectSymbol.left;

                            pTextComment->MoveTo(rcTextBox);
                        }

                        // Sets the flag
                        bDoneFirst = true;
                    }
                }
                else
                {
                    // We don't need to include this edit are,
                    // Resize it at the bottom of the symbol
                    CODTextComponent* pTextComment = GetCommentTextEdit();

                    if (pTextComment)
                    {
                        if (m_RelativeCoordinates)
                        {
                            // Move the text box in relative
                            CRect rcTextBox = pTextComment->GetEdgeRgn().GetBounds();
                            rcTextBox.left = rectEdgeRgn.left + gEditBoxSpaceFromBorder;
                            rcTextBox.top = rectEdgeRgn.Height() - gEditBoxSpaceFromBorder - 2;
                            rcTextBox.bottom = rectEdgeRgn.Height() - gEditBoxSpaceFromBorder;
                            rcTextBox.right = rectEdgeRgn.Width() - gEditBoxSpaceFromBorder;

                            pTextComment->MoveTo(rcTextBox);
                        }
                        else
                        {
                            // Move the text box in absolute
                            CODComponentPosition* pPosition = pTextComment->GetPosition();
                            ASSERT(pPosition);

                            CRect rcTextBox = pPosition->GetBounds();
                            rcTextBox.left = rect.left + gEditBoxSpaceFromBorder - rectSymbol.left;
                            rcTextBox.top = rect.bottom - gEditBoxSpaceFromBorder - rectSymbol.top;
                            rcTextBox.bottom = rect.bottom - 1 - rectSymbol.top;
                            rcTextBox.right = rect.right - gEditBoxSpaceFromBorder - rectSymbol.left;

                            pTextComment->MoveTo(rcTextBox);
                        }
                    }
                }

                // The attribute is always the last
                if (IsAttributeAreaVisible())
                {
                    CODTextComponent* pTextAttribute = GetAttributeTextEdit();

                    if (pTextAttribute)
                    {
                        // Show the symbol attribute edit box
                        pTextAttribute->SetVisible(TRUE);

                        if (m_RelativeCoordinates)
                        {
                            // Move the text box in relative
                            CRect rcTextBox = pTextAttribute->GetEdgeRgn().GetBounds();
                            rcTextBox.left = rectEdgeRgn.left + gEditBoxSpaceFromBorder;

                            // Test if this is for this splitter
                            if (pComp == pSplitter1 && y != 1)
                            {
                                rcTextBox.top =
                                    (y - rect.top + OffsetTop) * rectEdgeRgn.Height() / rect.Height();

                                rcTextBox.bottom = rectEdgeRgn.Height() + OffsetTop - gEditBoxSpaceFromBorder;
                            }
                            else
                            {
                                rcTextBox.top = YPositionSplitter1;
                                rcTextBox.bottom = rectEdgeRgn.Height() + OffsetTop - gEditBoxSpaceFromBorder;
                            }

                            rcTextBox.right = rcTextBox.left + rectEdgeRgn.Width() - gEditBoxSpaceFromBorder;

                            pTextAttribute->MoveTo(rcTextBox);
                        }
                        else
                        {
                            // Move the text box in absolute
                            CODComponentPosition* pPosition = pTextAttribute->GetPosition();
                            ASSERT(pPosition);

                            CRect rcTextBox = pPosition->GetBounds();
                            rcTextBox.left = rect.left + gEditBoxSpaceFromBorder - rectSymbol.left;

                            // Test if this is for this splitter
                            if (pComp == pSplitter1 && y != 1)
                            {
                                rcTextBox.top = y - rectSymbol.top;
                                rcTextBox.bottom = rect.bottom - gEditBoxSpaceFromBorder - rectSymbol.top;
                            }
                            else
                            {
                                rcTextBox.top = YPositionSplitter1 - rectSymbol.top;
                                rcTextBox.bottom = rect.bottom - gEditBoxSpaceFromBorder - rectSymbol.top;
                            }

                            rcTextBox.right = rect.right - gEditBoxSpaceFromBorder - rectSymbol.left;

                            pTextAttribute->MoveTo(rcTextBox);
                        }
                    }
                }
                else
                {
                    // We don't need to include this edit are,
                    // Resize it at the bottom of the symbol
                    CODTextComponent* pTextAttribute = GetAttributeTextEdit();

                    if (pTextAttribute)
                    {
                        if (m_RelativeCoordinates)
                        {
                            // Move the text box in relative
                            CRect rcTextBox = pTextAttribute->GetEdgeRgn().GetBounds();
                            rcTextBox.left = rectEdgeRgn.left + gEditBoxSpaceFromBorder;
                            rcTextBox.top = rectEdgeRgn.Height() - gEditBoxSpaceFromBorder - 2;
                            rcTextBox.bottom = rectEdgeRgn.Height() - gEditBoxSpaceFromBorder;
                            rcTextBox.right = rectEdgeRgn.Width() - gEditBoxSpaceFromBorder;

                            pTextAttribute->MoveTo(rcTextBox);
                        }
                        else
                        {
                            // Move the text box in absolute
                            CODComponentPosition* pPosition = pTextAttribute->GetPosition();
                            ASSERT(pPosition);

                            CRect rcTextBox = pPosition->GetBounds();
                            rcTextBox.left = rect.left + gEditBoxSpaceFromBorder - rectSymbol.left;
                            rcTextBox.top = rect.bottom - gEditBoxSpaceFromBorder - rectSymbol.top;
                            rcTextBox.bottom = rect.bottom - 1 - rectSymbol.top;
                            rcTextBox.right = rect.right - gEditBoxSpaceFromBorder - rectSymbol.left;

                            pTextAttribute->MoveTo(rcTextBox);
                        }
                    }
                }
            }

            // With need only one splitter
            if (GetSplitter2() && GetSplitter2()->IsVisible() == TRUE)
            {
                GetSplitter2()->SetVisible(FALSE);

                // Sets the redraw flag
                Redraw = true;
            }
        }
    }
    else
    {
        // We need don't need splitter
        if (GetSplitter1() && GetSplitter1()->IsVisible() == TRUE)
        {
            GetSplitter1()->SetVisible(FALSE);

            // Sets the redraw flag
            Redraw = true;
        }

        if (GetSplitter2() && GetSplitter2()->IsVisible() == TRUE)
        {
            GetSplitter2()->SetVisible(FALSE);

            // Sets the redraw flag
            Redraw = true;
        }

        // Then move the splitters
        CODComponent* pEditBoxArea = GetEditBoxArea();
        ASSERT(pEditBoxArea);

        CODComponentPosition* pCompPosition =
            (pEditBoxArea != NULL) ? pEditBoxArea->GetPosition() : dynamic_cast<CODComponent*>(m_pSymbol)->GetPosition();

        CRect rect = pCompPosition->GetBounds();
        CRect rectEdgeRgn = pEditBoxArea->GetEdgeRgn().GetBounds();

        // JMR-MODIF - Le 28 septembre 2005 - Nettoyage des memory leaks, suppression de la variable pCompPosition
        // après son utilisation.
        if (pCompPosition != NULL)
        {
            delete pCompPosition;
            pCompPosition = NULL;
        }

        // Resize edit control, only if the rect is not empty
        if (!rect.IsRectEmpty())
        {
            // Now check what component must be displayed full
            if (IsNameAreaVisible() && GetSymbolNameTextEdit())
            {
                CODTextComponent* pTextName = GetSymbolNameTextEdit();

                // Show the symbol name edit box
                pTextName->SetVisible(TRUE);

                if (m_RelativeCoordinates)
                {
                    // Move the text box in relative
                    CRect rcTextBox = pTextName->GetEdgeRgn().GetBounds();
                    rcTextBox.left = rectEdgeRgn.left + gEditBoxSpaceFromBorder;
                    rcTextBox.top = rectEdgeRgn.top + gEditBoxSpaceFromBorder;
                    rcTextBox.right = rcTextBox.left + rectEdgeRgn.Width() - gEditBoxSpaceFromBorder;
                    rcTextBox.bottom = rectEdgeRgn.Height() + OffsetTop - gEditBoxSpaceFromBorder;

                    pTextName->MoveTo(rcTextBox);
                }
                else
                {
                    // Move the text box in absolute
                    CODComponentPosition* pPosition = pTextName->GetPosition();
                    ASSERT(pPosition);

                    CRect rcTextBox = pPosition->GetBounds();
                    rcTextBox.left = rect.left + gEditBoxSpaceFromBorder - rectSymbol.left;
                    rcTextBox.top = rect.top + gEditBoxSpaceFromBorder - rectSymbol.top;
                    rcTextBox.bottom = rect.bottom - gEditBoxSpaceFromBorder - rectSymbol.top;
                    rcTextBox.right = rect.right - gEditBoxSpaceFromBorder - rectSymbol.left;

                    pTextName->MoveTo(rcTextBox);
                }
            }
            else if (IsDescriptionsAreaVisible() && GetCommentTextEdit())
            {
                CODTextComponent* pTextComment = GetCommentTextEdit();

                // Show the symbol comment edit box
                pTextComment->SetVisible(TRUE);

                if (m_RelativeCoordinates)
                {
                    // Move the text box in relative
                    CRect rcTextBox = pTextComment->GetEdgeRgn().GetBounds();
                    rcTextBox.left = rectEdgeRgn.left + gEditBoxSpaceFromBorder;
                    rcTextBox.top = rectEdgeRgn.top + gEditBoxSpaceFromBorder;
                    rcTextBox.right = rcTextBox.left + rectEdgeRgn.Width() - gEditBoxSpaceFromBorder;
                    rcTextBox.bottom = rectEdgeRgn.Height() + OffsetTop - gEditBoxSpaceFromBorder;

                    pTextComment->MoveTo(rcTextBox);
                }
                else
                {
                    // Move the text box in absolute
                    CODComponentPosition* pPosition = pTextComment->GetPosition();
                    ASSERT(pPosition);

                    CRect rcTextBox = pPosition->GetBounds();
                    rcTextBox.left = rect.left + gEditBoxSpaceFromBorder - rectSymbol.left;
                    rcTextBox.top = rect.top + gEditBoxSpaceFromBorder - rectSymbol.top;
                    rcTextBox.bottom = rect.bottom - gEditBoxSpaceFromBorder - rectSymbol.top;
                    rcTextBox.right = rect.right - gEditBoxSpaceFromBorder - rectSymbol.left;

                    pTextComment->MoveTo(rcTextBox);
                }
            }
            else if (IsAttributeAreaVisible() && GetAttributeTextEdit())
            {
                CODTextComponent* pTextAttribute = GetAttributeTextEdit();

                // Show the symbol attribute edit box
                pTextAttribute->SetVisible(TRUE);

                if (m_RelativeCoordinates)
                {
                    // Move the text box in relative
                    CRect rcTextBox = pTextAttribute->GetEdgeRgn().GetBounds();
                    rcTextBox.left = rectEdgeRgn.left + gEditBoxSpaceFromBorder;
                    rcTextBox.top = rectEdgeRgn.top + gEditBoxSpaceFromBorder;
                    rcTextBox.right = rcTextBox.left + rectEdgeRgn.Width() - gEditBoxSpaceFromBorder;
                    rcTextBox.bottom = rectEdgeRgn.Height() + OffsetTop - gEditBoxSpaceFromBorder;

                    pTextAttribute->MoveTo(rcTextBox);
                }
                else
                {
                    // Move the text box in absolute
                    CODComponentPosition* pPosition = pTextAttribute->GetPosition();
                    ASSERT(pPosition);

                    CRect rcTextBox = pPosition->GetBounds();
                    rcTextBox.left = rect.left + gEditBoxSpaceFromBorder - rectSymbol.left;
                    rcTextBox.top = rect.top + gEditBoxSpaceFromBorder - rectSymbol.top;
                    rcTextBox.bottom = rect.bottom - gEditBoxSpaceFromBorder - rectSymbol.top;
                    rcTextBox.right = rect.right - gEditBoxSpaceFromBorder - rectSymbol.left;

                    pTextAttribute->MoveTo(rcTextBox);
                }
            }
        }
    }

    // And finally, test what text box to hide
    if (!IsNameAreaVisible() && GetSymbolNameTextEdit() && GetSymbolNameTextEdit()->IsVisible() == TRUE)
    {
        // Hide the symbol name edit box
        GetSymbolNameTextEdit()->SetVisible(FALSE);

        // Sets the redraw flag
        Redraw = true;
    }

    if (!IsAttributeAreaVisible() && GetAttributeTextEdit() && GetAttributeTextEdit()->IsVisible() == TRUE)
    {
        // Hide the symbol attribute edit box
        GetAttributeTextEdit()->SetVisible(FALSE);

        // Sets the redraw flag
        Redraw = true;
    }

    if (!IsDescriptionsAreaVisible() && GetCommentTextEdit() && GetCommentTextEdit()->IsVisible() == TRUE)
    {
        // Hide the symbol comment edit box
        GetCommentTextEdit()->SetVisible(FALSE);

        // Sets the redraw flag
        Redraw = true;
    }

    // If we do need to redraw the symbol
    if (Redraw)
        m_pSymbol->RedrawSymbol();

#ifdef _DEBUG
    // Just to check the position of text boxes
    pCompPosition = dynamic_cast<CODComponent*>(m_pSymbol)->GetPosition();
    CRect rectFinalText = pCompPosition->GetBounds();
    CString s;

    // JMR-MODIF - Le 20 septembre 2005 - Nettoyage des memory leaks, suppression de pCompPosition après utilisation.
    if (pCompPosition != NULL)
    {
        delete pCompPosition;
        pCompPosition = NULL;
    }

    s.Format(_T("\nSymbol: top=%d left=%d bottom=%d right=%d\n"),
             rectFinalText.top,
             rectFinalText.left,
             rectFinalText.bottom,
             rectFinalText.right);

    TRACE(s);

    if (GetEditBoxArea())
    {
        CODComponentPosition* pTextPosition = GetEditBoxArea()->GetPosition();
        rectFinalText = pTextPosition->GetBounds();

        // JMR-MODIF - Le 20 septembre 2005 - Nettoyage des memory leaks, suppression de pTextPosition après utilisation.
        if (pTextPosition != NULL)
        {
            delete pTextPosition;
            pTextPosition = NULL;
        }

        s.Format(_T("AreaBox: top=%d left=%d bottom=%d right=%d\n"),
                 rectFinalText.top,
                 rectFinalText.left,
                 rectFinalText.bottom,
                 rectFinalText.right);

        TRACE(s);
    }

    if (GetSymbolNameTextEdit())
    {
        CODComponentPosition* pTextPosition = GetSymbolNameTextEdit()->GetPosition();
        rectFinalText = pTextPosition->GetBounds();

        // JMR-MODIF - Le 20 septembre 2005 - Nettoyage des memory leaks, suppression de pTextPosition après utilisation.
        if (pTextPosition != NULL)
        {
            delete pTextPosition;
            pTextPosition = NULL;
        }

        s.Format(_T("NameBox: top=%d left=%d bottom=%d right=%d\n"),
                 rectFinalText.top,
                 rectFinalText.left,
                 rectFinalText.bottom,
                 rectFinalText.right);

        TRACE(s);
    }

    if (GetCommentTextEdit())
    {
        CODComponentPosition* pTextPosition = GetCommentTextEdit()->GetPosition();
        rectFinalText = pTextPosition->GetBounds();

        // JMR-MODIF - Le 20 septembre 2005 - Nettoyage des memory leaks, suppression de pTextPosition après utilisation.
        if (pTextPosition != NULL)
        {
            delete pTextPosition;
            pTextPosition = NULL;
        }

        s.Format(_T("CommentBox: top=%d left=%d bottom=%d right=%d\n"),
                 rectFinalText.top,
                 rectFinalText.left,
                 rectFinalText.bottom,
                 rectFinalText.right);

        TRACE(s);
    }

    if (GetAttributeTextEdit())
    {
        CODComponentPosition* pTextPosition = GetAttributeTextEdit()->GetPosition();
        rectFinalText = pTextPosition->GetBounds();

        // JMR-MODIF - Le 20 septembre 2005 - Nettoyage des memory leaks, suppression de pTextPosition après utilisation.
        if (pTextPosition != NULL)
        {
            delete pTextPosition;
            pTextPosition = NULL;
        }

        s.Format(_T("AttributeBox: top=%d left=%d bottom=%d right=%d\n"),
                 rectFinalText.top,
                 rectFinalText.left,
                 rectFinalText.bottom,
                 rectFinalText.right);

        TRACE(s);
    }

    if (GetSplitter1())
    {
        CODComponentPosition* pSplitterPosition = GetSplitter1()->GetPosition();
        rectFinalText = pSplitterPosition->GetBounds();

        // JMR-MODIF - Le 20 septembre 2005 - Nettoyage des memory leaks, suppression de pSplitterPosition
        // après utilisation.
        if (pSplitterPosition != NULL)
        {
            delete pSplitterPosition;
            pSplitterPosition = NULL;
        }

        s.Format(_T("Splitter1: top=%d left=%d bottom=%d right=%d\n"),
                 rectFinalText.top,
                 rectFinalText.left,
                 rectFinalText.bottom,
                 rectFinalText.right);

        TRACE(s);
    }

    if (GetSplitter2())
    {
        CODComponentPosition* pSplitterPosition = GetSplitter2()->GetPosition();
        rectFinalText = pSplitterPosition->GetBounds();

        // JMR-MODIF - Le 20 septembre 2005 - Nettoyage des memory leaks, suppression de pSplitterPosition
        // après utilisation.
        if (pSplitterPosition != NULL)
        {
            delete pSplitterPosition;
            pSplitterPosition = NULL;
        }

        s.Format(_T("Splitter2: top=%d left=%d bottom=%d right=%d\n"),
                 rectFinalText.top,
                 rectFinalText.left,
                 rectFinalText.bottom,
                 rectFinalText.right);

        TRACE(s);
    }
#endif
}

//////////////////////////////////////////////////////////////////////
// Symbol mouse methods
bool ZVSymbolAttributes::OnMouseMove(UINT nFlags, CPoint point, CODController& Ctrl)
{
    if (!UseDynamicArea())
    {
        return false;
    }

    // Tests if we are in splitter moving mode
    if (gInMoveSplitterMode)
    {
        // Retrieve the device context to draw
        CWnd* pWnd = Ctrl.GetWnd();

        if (!pWnd)
        {
            return true;
        }

        CDC* pDC = pWnd->GetDC();

        if (!pDC)
        {
            return true;
        }

        // Converts the point
        CPoint pt(point);
        Ctrl.VpLPtoDP(&pt);

        CPen penMark(PS_DASH, 0, defCOLOR_BLACK);
        CPen* pPrevPen = (CPen*)pDC->SelectObject(&penMark);
        int nPrevRop2 = pDC->SetROP2(R2_NOTXORPEN);

        // If not empty, then erase the previous line
        if (gLastPoint.x != 0 && gLastPoint.y != 0)
        {
            pDC->MoveTo(gInitialSymbolRect.left, gLastPoint.y);
            pDC->LineTo(gInitialSymbolRect.right, gLastPoint.y);
        }

        // Check the maximum and the minimum
        if (gMaxUp != 0 && gMaxDown != 0)
        {
            if (pt.y > gMaxDown)
            {
                pt.y = gMaxDown;
            }
            else if (pt.y < gMaxUp)
            {
                pt.y = gMaxUp;
            }
        }

        pDC->MoveTo(gInitialSymbolRect.left, pt.y);
        pDC->LineTo(gInitialSymbolRect.right, pt.y);

        pDC->SetROP2(nPrevRop2);
        pDC->SelectObject(pPrevPen);

        // Save the current line position
        gLastPoint = pt;

        // Release the dc used
        pWnd->ReleaseDC(pDC);

        return true;
    }
    else
    {
        // Test if the first splitter is visible and over
        if (GetSplitter1() && GetSplitter1()->IsVisible())
        {
            CODComponentPosition* pPosition = GetSplitter1()->GetPosition();

            CRect rcSplitter1 = pPosition->GetBounds();
            rcSplitter1.InflateRect(0, 3);

            // JMR-MODIF - Le 20 septembre 2005 - Nettoyage des memory leaks, suppression de pPosition après utilisation.
            if (pPosition != NULL)
            {
                delete pPosition;
                pPosition = NULL;
            }

            if (rcSplitter1.PtInRect(point))
            {
                Ctrl.SetCustomCursor(IDC_SYM_SPLITTER_V);
                return true;
            }
        }

        // Test if the second splitter is visible and over
        if (GetSplitter2() && GetSplitter2()->IsVisible())
        {
            CODComponentPosition* pPosition = GetSplitter2()->GetPosition();

            CRect rcSplitter2 = pPosition->GetBounds();
            rcSplitter2.InflateRect(0, 3);

            // JMR-MODIF - Le 20 septembre 2005 - Nettoyage des memory leaks, suppression de pPosition après utilisation.
            if (pPosition != NULL)
            {
                delete pPosition;
                pPosition = NULL;
            }

            if (rcSplitter2.PtInRect(point))
            {
                Ctrl.SetCustomCursor(IDC_SYM_SPLITTER_V);
                return true;
            }
        }
    }

    return false;
}

bool ZVSymbolAttributes::OnLButtonDown(UINT nFlags, CPoint point, CODController& Ctrl)
{
    if (!UseDynamicArea())
    {
        return false;
    }

    // Test if we are positioned on a splitter
    if (GetSplitter1() && GetSplitter1()->IsVisible())
    {
        CODComponentPosition* pPosition = GetSplitter1()->GetPosition();

        CRect rcSplitter1 = pPosition->GetBounds();
        rcSplitter1.InflateRect(0, 3);

        // JMR-MODIF - Le 20 septembre 2005 - Nettoyage des memory leaks, suppression de pPosition après utilisation.
        if (pPosition != NULL)
        {
            delete pPosition;
            pPosition = NULL;
        }

        if (rcSplitter1.PtInRect(point))
        {
            gInMoveSplitterMode = true;
            gMoveSplitter1 = true;
            CODComponent* pEditBoxArea = GetEditBoxArea();
            CODComponentPosition* pCompPosition = (pEditBoxArea != NULL) ? pEditBoxArea->GetPosition() : dynamic_cast<CODComponent*>(m_pSymbol)->GetPosition();
            gInitialSymbolRect = pCompPosition->GetBounds();

            // JMR-MODIF - Le 20 septembre 2005 - Nettoyage des memory leaks, suppression de pCompPosition
            // après utilisation.
            if (pCompPosition != NULL)
            {
                delete pCompPosition;
                pCompPosition = NULL;
            }

            gInitialSymbolRect.DeflateRect(gEditBoxSpaceFromBorder, gEditBoxSpaceFromBorder);

            // Converts the point
            CPoint pt(point);
            Ctrl.VpLPtoDP(&pt);
            CPoint Start(gInitialSymbolRect.left, gInitialSymbolRect.top);
            Ctrl.VpLPtoDP(&Start);
            CPoint End(gInitialSymbolRect.right, gInitialSymbolRect.bottom);
            Ctrl.VpLPtoDP(&End);

            gInitialSymbolRect.left = Start.x;
            gInitialSymbolRect.top = Start.y;
            gInitialSymbolRect.right = End.x;
            gInitialSymbolRect.bottom = End.y;

            gInitialPoint = pt;
            gLastPoint.x = 0;
            gLastPoint.y = 0;

            // Check if there is a maximum to respect
            if (GetSplitter2() && GetSplitter2()->IsVisible())
            {
                CODComponentPosition* pPosition = GetSplitter2()->GetPosition();
                CRect rcSplitter2 = pPosition->GetBounds();

                rcSplitter2.InflateRect(0, 3);

                // JMR-MODIF - Le 20 septembre 2005 - Nettoyage des memory leaks, suppression de pPosition
                // après utilisation.
                if (pPosition != NULL)
                {
                    delete pPosition;
                    pPosition = NULL;
                }

                // Converts the point
                CPoint UpPoint(rcSplitter2.left, rcSplitter2.top);
                Ctrl.VpLPtoDP(&UpPoint);
                gMaxDown = UpPoint.y;
                gMaxUp = gInitialSymbolRect.top + gEditBoxSpaceFromBorder;
            }
        }
    }

    // If not already in move mode
    if (!gInMoveSplitterMode && GetSplitter2() && GetSplitter2()->IsVisible())
    {
        CODComponentPosition* pPosition = GetSplitter2()->GetPosition();
        CRect rcSplitter2 = pPosition->GetBounds();

        rcSplitter2.InflateRect(0, 3);

        // JMR-MODIF - Le 20 septembre 2005 - Nettoyage des memory leaks, suppression de pPosition après utilisation.
        if (pPosition != NULL)
        {
            delete pPosition;
            pPosition = NULL;
        }

        if (rcSplitter2.PtInRect(point))
        {
            gInMoveSplitterMode = true;
            gMoveSplitter2 = true;
            CODComponent* pEditBoxArea = GetEditBoxArea();
            CODComponentPosition* pCompPosition = (pEditBoxArea != NULL) ? pEditBoxArea->GetPosition() : dynamic_cast<CODComponent*>(m_pSymbol)->GetPosition();
            gInitialSymbolRect = pCompPosition->GetBounds();

            // JMR-MODIF - Le 20 septembre 2005 - Nettoyage des memory leaks, suppression de pCompPosition
            // après utilisation.
            if (pCompPosition != NULL)
            {
                delete pCompPosition;
                pCompPosition = NULL;
            }

            gInitialSymbolRect.DeflateRect(gEditBoxSpaceFromBorder, gEditBoxSpaceFromBorder);

            // Converts the point
            CPoint pt(point);
            Ctrl.VpLPtoDP(&pt);
            CPoint Start(gInitialSymbolRect.left, gInitialSymbolRect.top);
            Ctrl.VpLPtoDP(&Start);
            CPoint End(gInitialSymbolRect.right, gInitialSymbolRect.bottom);
            Ctrl.VpLPtoDP(&End);

            gInitialSymbolRect.left = Start.x;
            gInitialSymbolRect.top = Start.y;
            gInitialSymbolRect.right = End.x;
            gInitialSymbolRect.bottom = End.y;

            gInitialPoint = pt;
            gLastPoint.x = 0;
            gLastPoint.y = 0;

            // Check if there is a maximum to respect
            if (GetSplitter1() && GetSplitter1()->IsVisible())
            {
                CODComponentPosition* pPosition = GetSplitter1()->GetPosition();
                CRect rcSplitter1 = pPosition->GetBounds();

                rcSplitter1.InflateRect(0, 3);

                // JMR-MODIF - Le 20 septembre 2005 - Nettoyage des memory leaks, suppression de pPosition
                // après utilisation.
                if (pPosition != NULL)
                {
                    delete pPosition;
                    pPosition = NULL;
                }

                // Converts the point
                CPoint UpPoint(rcSplitter1.left, rcSplitter1.bottom);
                Ctrl.VpLPtoDP(&UpPoint);
                gMaxUp = UpPoint.y;
                gMaxDown = gInitialSymbolRect.bottom - gEditBoxSpaceFromBorder;
            }
        }
    }

    if (gInMoveSplitterMode)
    {
        Ctrl.SetCapture();
        CWnd* pWnd = Ctrl.GetWnd();

        if (pWnd)
        {
            CRect rect(gInitialSymbolRect);
            pWnd->ClientToScreen(&rect);
            ::ClipCursor(&rect);
        }
    }

    return gInMoveSplitterMode;
}

bool ZVSymbolAttributes::OnLButtonUp(UINT nFlags, CPoint point, CODController& Ctrl)
{
    if (!UseDynamicArea())
    {
        return false;
    }

    // Tests if we were in splitter moving mode
    if (gInMoveSplitterMode)
    {
        // Release the cursor capture
        Ctrl.ReleaseCapture();
        ::ClipCursor(NULL);

        // Retrieve the device context to draw
        CWnd* pWnd = Ctrl.GetWnd();

        if (!pWnd)
        {
            return true;
        }

        CDC* pDC = pWnd->GetDC();

        if (!pDC)
        {
            return true;
        }

        // Converts the point
        CPoint pt(point);
        Ctrl.VpLPtoDP(&pt);

        CPen penMark(PS_DASH, 0, defCOLOR_BLACK);
        CPen* pPrevPen = (CPen*)pDC->SelectObject(&penMark);
        int nPrevRop2 = pDC->SetROP2(R2_NOTXORPEN);

        // If not empty, then erase the previous line
        if (gLastPoint.x != 0 && gLastPoint.y != 0)
        {
            pDC->MoveTo(gInitialSymbolRect.left, gLastPoint.y);
            pDC->LineTo(gInitialSymbolRect.right, gLastPoint.y);
        }

        pDC->SetROP2(nPrevRop2);
        pDC->SelectObject(pPrevPen);

        // Saves the Y position
        if (gMoveSplitter1)
        {
            AdjustAreaPosition(GetSplitter1(), point.y);
        }
        else if (gMoveSplitter2)
        {
            AdjustAreaPosition(GetSplitter2(), point.y);
        }

        // Reset flags and value
        gInMoveSplitterMode = false;
        gSplitterPositionY = -1;
        gMoveSplitter1 = false;
        gMoveSplitter2 = false;
        gMaxUp = 0;
        gMaxDown = 0;

        // Release the dc used
        pWnd->ReleaseDC(pDC);
    }

    return false;
}
