/****************************************************************************
 * ==> PSS_SymbolAttributes ------------------------------------------------*
 ****************************************************************************
 * Description : Provides the symbol attributes                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SymbolAttributes.h"

// processsoft
#include "PSS_ODSymbolManipulator.h"

// resources
#include "zModelRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const int g_EditBoxSpaceFromBorder      = 1;
const int g_SplitterLineSpaceFromBorder = 1;
//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static CRect  g_InitialSymbolRect(0, 0, 0, 0);
static CPoint g_InitialPoint(0, 0);
static CPoint g_LastPoint(0, 0);
static int    g_SplitterPositionY  = -1;
static int    g_MaxUp              = 0;
static int    g_MaxDown            = 0;
static bool   g_InMoveSplitterMode = false;
static bool   g_MoveSplitter1      = false;
static bool   g_MoveSplitter2      = false;
//---------------------------------------------------------------------------
// PSS_SymbolAttributes
//---------------------------------------------------------------------------
PSS_SymbolAttributes::PSS_SymbolAttributes(PSS_BasicSymbol* pSymbol) :
    m_pSymbol(pSymbol),
    m_pEditBoxArea(NULL),
    m_pNameEditText(NULL),
    m_pCommentEditText(NULL),
    m_pAttributeEditText(NULL),
    m_pSplitterComponent1(NULL),
    m_pSplitterComponent2(NULL),
    m_UseDynamicArea(true),
    m_ShowNameArea(true),
    m_ShowDescriptionArea(false),
    m_ShowAttributeArea(false),
    m_RelativeCoordinates(false),
    m_ReinitializeAreaAtCreation(false)
{}
//---------------------------------------------------------------------------
PSS_SymbolAttributes::PSS_SymbolAttributes(const PSS_SymbolAttributes& src)
{
    *this = src;
};
//---------------------------------------------------------------------------
PSS_SymbolAttributes::~PSS_SymbolAttributes()
{
    CODComponent* pComponent = dynamic_cast<CODComponent*>(m_pSymbol);

    if (pComponent)
        pComponent->RemoveAllChildren();
}
//---------------------------------------------------------------------------
PSS_SymbolAttributes& PSS_SymbolAttributes::operator = (const PSS_SymbolAttributes& other)
{
    m_Attributes                 = other.m_Attributes;
    m_UseDynamicArea             = other.m_UseDynamicArea;
    m_ShowNameArea               = other.m_ShowNameArea;
    m_ShowDescriptionArea        = other.m_ShowDescriptionArea;
    m_ShowAttributeArea          = other.m_ShowAttributeArea;
    m_RelativeCoordinates        = other.m_RelativeCoordinates;
    m_ReinitializeAreaAtCreation = other.m_ReinitializeAreaAtCreation;

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolAttributes::InitializeAttributeAreas()
{
    // set all internal components to NULL. After the creation from resource or file, some of them will be assigned
    m_pNameEditText       = NULL;
    m_pCommentEditText    = NULL;
    m_pAttributeEditText  = NULL;
    m_pSplitterComponent1 = NULL;
    m_pSplitterComponent2 = NULL;

    // check the area text box fill properties
    if (!UseDynamicArea() || !GetEditBoxArea())
        return TRUE;

    if (!m_pSymbol)
        THROW("Cannot initialize the attributes without an owning symbol");

    CODComponent* pSymComp = dynamic_cast<CODComponent*>(m_pSymbol);

    if (!pSymComp)
        THROW("The owning symbol isn't a CODComponent child - incorrect runtime class type");

    // check if needed to include the name area
    if (m_pSymbol->IncludeNameArea())
    {
        // create the name text zone if it doesn't exist
        if (!PSS_ODSymbolManipulator::FindSymbol(pSymComp, M_SymbolNameComponentControlLabel))
        {
            m_pSymbol->CreateAndReplaceEditText(M_SymbolNameComponentControlLabel);

            // set the text editor
            CODTextComponent* pText = GetSymbolNameTextEdit();

            if (pText)
            {
                pText->SetText(m_pSymbol->GetSymbolName());

                // set the default values
                pText->SetValue(OD_PROP_AUTOSIZE,    FALSE);
                pText->SetValue(OD_PROP_WORDBREAK,   TRUE);
                pText->SetValue(OD_PROP_MULTILINE,   TRUE);
                pText->SetValue(OD_PROP_TRANSPARENT, TRUE);

                // set transparent
                CODFillProperties* pFillProps = dynamic_cast<CODFillProperties*>(pText->GetProperty(OD_PROP_FILL));

                if (pFillProps)
                {
                    std::unique_ptr<CODFillProperties> pNewProps(new CODFillProperties(*pFillProps));
                    pNewProps->SetTransparent(TRUE);
                    pText->SetProperty(pNewProps.get());
                    pNewProps.release();
                }

                CODEditProperties* pEdit = dynamic_cast<CODEditProperties*>(pText->GetProperty(OD_PROP_EDIT));

                // can't be selected
                if (pEdit)
                {
                    std::unique_ptr<CODEditProperties> pNewEdit(new CODEditProperties(*pEdit));
                    pNewEdit->SetCanSelect(FALSE);
                    pText->SetProperty(pNewEdit.get());
                    pNewEdit.release();
                }

                CODLineProperties* pLine = dynamic_cast<CODLineProperties*>(pText->GetProperty(OD_PROP_LINE));

                // no line
                if (pLine)
                {
                    std::unique_ptr<CODLineProperties> pNewLine(new CODLineProperties(*pLine));
                    pNewLine->SetTransparent(TRUE);
                    pText->SetProperty(pNewLine.get());
                    pNewLine.release();
                }

                CODFontProperties* pFontProp = dynamic_cast<CODFontProperties*>(pText->GetProperty(OD_PROP_FONT));

                // change font
                if (pFontProp)
                {
                    std::unique_ptr<CODFontProperties> pNewfontProp(new CODFontProperties(*pFontProp));
                    pNewfontProp->SetFaceName(_T("Arial"));
                    pNewfontProp->SetWeight(FW_BOLD);
                    pNewfontProp->SetPointSize(8);
                    pText->SetProperty(pNewfontProp.get());
                    pNewfontProp.release();
                }
            }
        }

        // check if the attribute area and the splitter should be hidden
        if (!IsNameAreaVisible())
            if (GetSymbolNameTextEdit())
                GetSymbolNameTextEdit()->SetVisible(FALSE);
    }
    else
    {
        // if no name area is required, check if exists and remove it
        CODTextComponent* pTextComp =
                dynamic_cast<CODTextComponent*>(PSS_ODSymbolManipulator::FindSymbol(pSymComp, M_SymbolNameComponentControlLabel));

        // remove the edit
        if (pTextComp)
            PSS_ODSymbolManipulator::RemoveSymbol(pSymComp, pTextComp);
    }

    // check if the attribute area is required
    if (m_pSymbol->IncludeAttributeArea())
    {
        // create the attribute text area if it does not exist
        if (!PSS_ODSymbolManipulator::FindSymbol(pSymComp, M_AttributeAreaComponentLabel))
        {
            m_pSymbol->CreateAndReplaceEditText(M_AttributeAreaComponentLabel);

            CODTextComponent* pText = GetAttributeTextEdit();

            if (pText)
            {
                pText->SetValue(OD_PROP_AUTOSIZE,       FALSE);
                pText->SetValue(OD_PROP_WORDBREAK,      TRUE);
                pText->SetValue(OD_PROP_MULTILINE,      TRUE);
                pText->SetValue(OD_PROP_HORZ_ALIGNMENT, DT_LEFT);
                pText->SetValue(OD_PROP_VERT_ALIGNMENT, DT_TOP);
                pText->SetValue(OD_PROP_TRANSPARENT,    TRUE);

                CODFillProperties* pFillProps = dynamic_cast<CODFillProperties*>(pText->GetProperty(OD_PROP_FILL));

                // set transparent
                if (pFillProps)
                {
                    std::unique_ptr<CODFillProperties> pNewProps(new CODFillProperties(*pFillProps));
                    pNewProps->SetTransparent(TRUE);
                    pText->SetProperty(pNewProps.get());
                    pNewProps.release();
                }

                CODEditProperties* pEdit = dynamic_cast<CODEditProperties*>(pText->GetProperty(OD_PROP_EDIT));

                // can't be selected
                if (pEdit)
                {
                    std::unique_ptr<CODEditProperties> pNewEdit(new CODEditProperties(*pEdit));
                    pNewEdit->SetCanSelect(FALSE);
                    pText->SetProperty(pNewEdit.get());
                    pNewEdit.release();
                }

                CODLineProperties* pLine = dynamic_cast<CODLineProperties*>(pText->GetProperty(OD_PROP_LINE));

                // no line
                if (pLine)
                {
                    std::unique_ptr<CODLineProperties> pNewLine(new CODLineProperties(*pLine));
                    pNewLine->SetTransparent(TRUE);
                    pText->SetProperty(pNewLine.get());
                    pNewLine.release();
                }

                CODFontProperties* pFontProp = dynamic_cast<CODFontProperties*>(pText->GetProperty(OD_PROP_FONT));

                // change font
                if (pFontProp)
                {
                    std::unique_ptr<CODFontProperties> pNewFont(new CODFontProperties(*pFontProp));
                    pNewFont->SetFaceName(_T("Arial"));
                    pNewFont->SetWeight(FW_NORMAL);
                    pNewFont->SetPointSize(8);
                    pText->SetProperty(pNewFont.get());
                    pNewFont.release();
                }
            }
        }

        // if an attribute area exists, check for the splitter1
        CODComponent* pComp = PSS_ODSymbolManipulator::FindSymbol(pSymComp, M_SplitterComponentLine1);

        // if not found, need to create one
        if (!pComp || !ISA(pComp, CODLineComponent))
        {
            std::unique_ptr<CODLineComponent> pSplitter(new CODLineComponent());

            // get the edit box rectangle area
            CODComponent*                         pEditBoxArea  = m_pSymbol->GetEditBoxArea();
            std::unique_ptr<CODComponentPosition> pCompPosition(pEditBoxArea ? pEditBoxArea->GetPosition() : pSymComp->GetPosition());
            const CRect                           rect          = pCompPosition->GetBounds();

            // create the splitter
            POINT ptLog[2];
            ptLog[0] = CPoint(rect.left,  rect.bottom);
            ptLog[1] = CPoint(rect.right, rect.bottom);
            pSplitter->Create(ptLog, 2);

            // set the new splitter name
            pSplitter->SetName(M_SplitterComponentLine1);

            // append the splitter to the symbol
            pSymComp->AppendChild(pSplitter.get());
            pSplitter.release();
        }

        // check if the attribute area and the splitter should be hidden
        if (!IsAttributeAreaVisible())
        {
            if (GetAttributeTextEdit())
                GetAttributeTextEdit()->SetVisible(FALSE);

            if (GetSplitter1())
                GetSplitter1()->SetVisible(FALSE);
        }
    }
    else
    {
        // found an attribute area, remove it from the component
        CODComponent* pComp = PSS_ODSymbolManipulator::FindSymbol(pSymComp, M_AttributeAreaComponentLabel);

        // remove the edit
        if (pComp && ISA(pComp, CODTextComponent))
            PSS_ODSymbolManipulator::RemoveSymbol(pSymComp, pComp);

        pComp = PSS_ODSymbolManipulator::FindSymbol(pSymComp, M_SplitterComponentLine1);

        // also remove the first splitter
        if (pComp && ISA(pComp, CODLineComponent))
            PSS_ODSymbolManipulator::RemoveSymbol(pSymComp, pComp);
    }

    // check if a description area is needed
    if (m_pSymbol->IncludeDescriptionArea())
    {
        // create the comment text zone if it doesn't exists
        if (!PSS_ODSymbolManipulator::FindSymbol(pSymComp, M_CommentComponentControlLabel))
        {
            m_pSymbol->CreateAndReplaceEditText(M_CommentComponentControlLabel);

            // set the matching content
            CODTextComponent* pText = GetCommentTextEdit();

            if (pText)
            {
                pText->SetText(m_pSymbol->GetSymbolComment());

                // set the default values
                pText->SetValue(OD_PROP_AUTOSIZE,    FALSE);
                pText->SetValue(OD_PROP_WORDBREAK,   TRUE);
                pText->SetValue(OD_PROP_MULTILINE,   TRUE);
                pText->SetValue(OD_PROP_TRANSPARENT, TRUE);

                CODFillProperties* pFillProps = dynamic_cast<CODFillProperties*>(pText->GetProperty(OD_PROP_FILL));

                // set transparent
                if (pFillProps)
                {
                    std::unique_ptr<CODFillProperties> pNewProps(new CODFillProperties(*pFillProps));
                    pNewProps->SetTransparent(TRUE);
                    pText->SetProperty(pNewProps.get());
                    pNewProps.release();
                }

                CODEditProperties* pEdit = dynamic_cast<CODEditProperties*>(pText->GetProperty(OD_PROP_EDIT));

                // can't be selected
                if (pEdit)
                {
                    std::unique_ptr<CODEditProperties> pNewEdit(new CODEditProperties(*pEdit));
                    pNewEdit->SetCanSelect(FALSE);
                    pText->SetProperty(pNewEdit.get());
                    pNewEdit.release();
                }

                CODLineProperties* pLine = dynamic_cast<CODLineProperties*>(pText->GetProperty(OD_PROP_LINE));

                // no line
                if (pLine)
                {
                    std::unique_ptr<CODLineProperties> pNewLine(new CODLineProperties(*pLine));
                    pNewLine->SetTransparent(TRUE);
                    pText->SetProperty(pNewLine.get());
                    pNewLine.release();
                }

                CODFontProperties* pFontProp = dynamic_cast<CODFontProperties*>(pText->GetProperty(OD_PROP_FONT));

                // change font
                if (pFontProp)
                {
                    std::unique_ptr<CODFontProperties> pNewFont(new CODFontProperties(*pFontProp));
                    pNewFont->SetFaceName(_T("Arial"));
                    pNewFont->SetWeight(FW_NORMAL);
                    pNewFont->SetPointSize(8);
                    pText->SetProperty(pNewFont.get());
                    pNewFont.release();
                }
            }
        }

        // if a description exists, check for the second splitter
        CODComponent* pComp = PSS_ODSymbolManipulator::FindSymbol(dynamic_cast<CODComponent*>(m_pSymbol), 
                                                                  M_SplitterComponentLine2);

        // if not found, need to create one
        if (!pComp || !ISA(pComp, CODLineComponent))
        {
            std::unique_ptr<CODLineComponent> pSplitter(new CODLineComponent());

            // get the edit box area
            CODComponent*                         pEditBoxArea  = m_pSymbol->GetEditBoxArea();
            std::unique_ptr<CODComponentPosition> pCompPosition(pEditBoxArea ? pEditBoxArea->GetPosition() : pSymComp->GetPosition());
            const CRect                           rect          = pCompPosition->GetBounds();

            // create the splitter
            POINT ptLog[2];
            ptLog[0] = CPoint(rect.left,  rect.bottom);
            ptLog[1] = CPoint(rect.right, rect.bottom);
            pSplitter->Create(ptLog, 2);

            // set the new splitter name
            pSplitter->SetName(M_SplitterComponentLine2);

            // append the splitter to the symbol
            pSymComp->AppendChild(pSplitter.get());
            pSplitter.release();
        }

        // check if the comment area and the splitter should be hidden
        if (!IsDescriptionsAreaVisible())
        {
            if (GetCommentTextEdit())
                GetCommentTextEdit()->SetVisible(FALSE);

            if (GetSplitter2())
                GetSplitter2()->SetVisible(FALSE);
        }
    }
    else
    {
        // found a description area, remove it from the component
        CODComponent* pComp = PSS_ODSymbolManipulator::FindSymbol(pSymComp, M_CommentComponentControlLabel);

        // remove the edit
        if (pComp && ISA(pComp, CODTextComponent))
            PSS_ODSymbolManipulator::RemoveSymbol(pSymComp, pComp);

        pComp = PSS_ODSymbolManipulator::FindSymbol(pSymComp, M_SplitterComponentLine2);

        // also remove the second splitter
        if (pComp && ISA(pComp, CODLineComponent))
            PSS_ODSymbolManipulator::RemoveSymbol(pSymComp, pComp);
    }

    // do reinitialize the whole area?
    if (!m_ReinitializeAreaAtCreation)
        return TRUE;

    bool nameAreaMustBeShown        = false;
    bool attributeAreaMustBeShown   = false;
    bool descriptionAreaMustBeShown = false;
    bool isNameAreaVisible          = false;
    bool isAttributeAreaVisible     = false;
    bool isDescriptionsAreaVisible  = false;

    // is the name area visible?
    if (m_pSymbol->IncludeNameArea())
    {
        nameAreaMustBeShown = true;
        isNameAreaVisible   = IsNameAreaVisible();
        ShowNameArea();
    }

    // is the attribute area visible?
    if (m_pSymbol->IncludeAttributeArea())
    {
        attributeAreaMustBeShown = true;
        isAttributeAreaVisible   = IsAttributeAreaVisible();
        ShowAttributeArea();
    }

    // is the description area visible?
    if (m_pSymbol->IncludeDescriptionArea())
    {
        descriptionAreaMustBeShown = true;
        isDescriptionsAreaVisible  = IsDescriptionsAreaVisible();
        ShowDescriptionArea();
    }

    // adjust the different areas and show them
    AdjustAreaPosition();

    // put back initial states
    if (nameAreaMustBeShown)
        ShowNameArea(isNameAreaVisible);

    if (attributeAreaMustBeShown)
        ShowAttributeArea(isAttributeAreaVisible);

    if (descriptionAreaMustBeShown)
        ShowDescriptionArea(isDescriptionsAreaVisible);

    // select the symbol
    CODEditProperties* pPropEdit = dynamic_cast<CODEditProperties*>(pSymComp->GetProperty(OD_PROP_EDIT));

    if (pPropEdit)
    {
        std::unique_ptr<CODEditProperties> pNewEdit(new CODEditProperties(*pPropEdit));
        pNewEdit->SetCanSelect(TRUE);
        pSymComp->SetProperty(pNewEdit.get());
        pNewEdit.release();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributes::AdjustAreaPosition(CODLineComponent* pComp, int y)
{
    if (!UseDynamicArea())
        return;

    ASSERT(m_pSymbol);

    CODComponent* pSymComp = dynamic_cast<CODComponent*>(m_pSymbol);

    if (!pSymComp)
        THROW("The owning symbol isn't a CODComponent child - incorrect runtime class type");

    // check the area text box fill properties
    if (!GetEditBoxArea())
        return;

    std::size_t counterSplitter            = 0;
    bool        nameAreaMustBeShown        = false;
    bool        attributeAreaMustBeShown   = false;
    bool        descriptionAreaMustBeShown = false;

    // check if the name area is visible and well placed
    if (m_pSymbol->IncludeNameArea() && IsNameAreaVisible())
    {
        nameAreaMustBeShown = true;
        ++counterSplitter;
    }

    // check if the attribute area is visible and well placed
    if (m_pSymbol->IncludeAttributeArea() && IsAttributeAreaVisible())
    {
        attributeAreaMustBeShown = true;
        ++counterSplitter;
    }

    // check if the description area is visible and well placed
    if (m_pSymbol->IncludeDescriptionArea() && IsDescriptionsAreaVisible())
    {
        descriptionAreaMustBeShown = true;
        ++counterSplitter;
    }

    // get the component position
    std::unique_ptr<CODComponentPosition> pCompPosition(pSymComp->GetPosition());
    const CRect                           rectSymbol         = pCompPosition->GetBounds();
    CODComponent*                         pEditBoxArea       = GetEditBoxArea();
    std::unique_ptr<CODComponentPosition> pAreaPosition(pEditBoxArea ? pEditBoxArea->GetPosition() : pSymComp->GetPosition());
    const CRect                           rect               = pAreaPosition->GetBounds();
    const CRect                           rectEdgeRgn        = pEditBoxArea->GetEdgeRgn().GetBounds();
    const int                             offsetLeft         = rect.left - rectSymbol.left;
    const int                             offsetTop          = rect.top - rectSymbol.top;
    int                                   yPositionSplitter1 = 0;
    int                                   yPositionSplitter2 = 0;
    bool                                  redraw             = false;

    // check if the splitter should be show or hide
    if (counterSplitter > 2)
    {
        // move the splitters, only resize edit control if the rect is not empty
        if (!rect.IsRectEmpty())
        {
            int segmentHeight;

            if (m_RelativeCoordinates)
                segmentHeight = (rectEdgeRgn.Height() - (2 * g_EditBoxSpaceFromBorder)) / 3;
            else
                segmentHeight = (rect.Height()        - (2 * g_EditBoxSpaceFromBorder)) / 3;

            CODLineComponent* pSplitter1   = GetSplitter1();
            CODTextComponent* pTextComment = GetCommentTextEdit();
            CODTextComponent* pTextName    = GetSymbolNameTextEdit();

            // if the splitter isn't visible, need to show it to calculate its new position.
            // Need also to show the matching edit, and to calculate its new position
            if (pSplitter1 && pTextComment && pTextName)
            {
                // show the splitter and the text box
                pSplitter1->SetVisible(TRUE);
                pTextComment->SetVisible(TRUE);
                pTextName->SetVisible(TRUE);

                // do redraw the symbol
                redraw = true;

                if (m_RelativeCoordinates)
                {
                    // move splitter in relative coordinates
                    CRect rcSplitter1 = pSplitter1->GetEdgeRgn().GetBounds();
                    rcSplitter1.left  = rectEdgeRgn.left + g_SplitterLineSpaceFromBorder;

                    // check if applied to correct splitter
                    if (pComp == pSplitter1)
                    {
                        rcSplitter1.top    = (y - rect.top + offsetTop) * rectEdgeRgn.Height() / rect.Height();
                        rcSplitter1.bottom = rcSplitter1.top;

                        // save the splitter y position
                        yPositionSplitter1 = (y - rect.top + offsetTop);
                    }
                    else
                    {
                        // apply to the default one
                        if (!pComp)
                        {
                            rcSplitter1.top    = rectEdgeRgn.top + segmentHeight + g_EditBoxSpaceFromBorder;
                            rcSplitter1.bottom = rcSplitter1.top;
                        }

                        // save the splitter y position
                        yPositionSplitter1 = rcSplitter1.top;
                    }

                    rcSplitter1.right = rcSplitter1.left + rectEdgeRgn.Width() - g_SplitterLineSpaceFromBorder;

                    float originX;
                    float originY;

                    // scale the splitter
                    pSplitter1->GetControlPoint(OD_TOP_LEFT, originX, originY);
                    const CRect rcBounds = pSplitter1->GetEdgeRgn().GetBounds();
                    const float scaleX   = float(rcSplitter1.Width()) / float(rcBounds.Width());
                    pSplitter1->Scale(scaleX, 1, originX, originY);
                    pSplitter1->MoveTo(CPoint(rcSplitter1.left, rcSplitter1.top));
                }
                else
                {
                    // move the splitter
                    CODComponentPosition* pPosition = pSplitter1->GetPosition();
                    ASSERT(pPosition);

                    CRect rcSplitter1 = pPosition->GetBounds();
                    rcSplitter1.left  = rect.left + g_SplitterLineSpaceFromBorder;

                    // check if applied to correct splitter
                    if (pComp == pSplitter1)
                        rcSplitter1.top = rcSplitter1.bottom = y;
                    else
                    if (!pComp)
                    {
                        rcSplitter1.top    = rect.top + segmentHeight + g_EditBoxSpaceFromBorder;
                        rcSplitter1.bottom = rcSplitter1.top;
                    }

                    rcSplitter1.right = rect.right - g_SplitterLineSpaceFromBorder;

                    // save the splitter y position
                    yPositionSplitter1 = rcSplitter1.top;

                    float originX;
                    float originY;

                    // scale the splitter
                    pSplitter1->GetControlPoint(OD_TOP_LEFT, originX, originY);
                    const CRect rcBounds = pPosition->GetBounds();
                    const float scaleX   = float(rcSplitter1.Width()) / float(rcBounds.Width());
                    pSplitter1->Scale(scaleX, 1, originX, originY);
                    pSplitter1->MoveTo(CPoint(rcSplitter1.left, rcSplitter1.top));
                }

                // move the two text box. First, the name
                if (m_RelativeCoordinates)
                {
                    // move the text box in relative coordinates
                    CRect rcTextBox = pTextName->GetEdgeRgn().GetBounds();
                    rcTextBox.left  = rectEdgeRgn.left + g_EditBoxSpaceFromBorder;

                    // check if applied to correct splitter
                    if (pComp == pSplitter1 && y != 1)
                    {
                        rcTextBox.top    = rectEdgeRgn.top + g_EditBoxSpaceFromBorder;
                        rcTextBox.bottom = (y - rect.top + offsetTop) * rectEdgeRgn.Height() / rect.Height();
                    }
                    else
                    {
                        rcTextBox.top    = rectEdgeRgn.top + g_EditBoxSpaceFromBorder;
                        rcTextBox.bottom = yPositionSplitter1;
                    }

                    rcTextBox.right = rcTextBox.left + rectEdgeRgn.Width() - g_EditBoxSpaceFromBorder;
                    pTextName->MoveTo(rcTextBox);
                }
                else
                {
                    // move in absolute coordinates
                    CODComponentPosition* pPosition = pTextName->GetPosition();
                    ASSERT(pPosition);

                    CRect rcTextBox = pPosition->GetBounds();
                    rcTextBox.left  = rect.left + g_EditBoxSpaceFromBorder - rectSymbol.left;

                    // check if applied to correct splitter
                    if (pComp == pSplitter1 && y != 1)
                    {
                        rcTextBox.top   -=     rectSymbol.top;
                        rcTextBox.bottom = y - rectSymbol.top;
                    }
                    else
                    {
                        rcTextBox.top    = rect.top + g_EditBoxSpaceFromBorder - rectSymbol.top;
                        rcTextBox.bottom = yPositionSplitter1 - rectSymbol.top;
                    }

                    rcTextBox.right = rect.right - g_EditBoxSpaceFromBorder - rectSymbol.left;
                    pTextName->MoveTo(rcTextBox);
                }

                // then the comment
                if (m_RelativeCoordinates)
                {
                    // move in relative coordinates
                    CRect rcTextBox = pTextComment->GetEdgeRgn().GetBounds();
                    rcTextBox.left  = rectEdgeRgn.left + g_EditBoxSpaceFromBorder;

                    // check if applied to correct splitter
                    if (pComp == pSplitter1 && y != 1)
                        rcTextBox.top = (y - rect.top + offsetTop) * rectEdgeRgn.Height() / rect.Height();
                    else
                    {
                        rcTextBox.top = yPositionSplitter1;

                        // if no splitter defined, apply to the default one
                        if (!pComp)
                            rcTextBox.bottom = yPositionSplitter1 + segmentHeight;
                        else
                            // otherwise it's the second splitter, calculate its position
                            rcTextBox.bottom = (y - rect.top + offsetTop) * rectEdgeRgn.Height() / rect.Height();
                    }

                    rcTextBox.right = rcTextBox.left + rectEdgeRgn.Width() - g_EditBoxSpaceFromBorder;
                    pTextComment->MoveTo(rcTextBox);
                }
                else
                {
                    // move in absolute coordinates
                    CODComponentPosition* pPosition = pTextComment->GetPosition();
                    ASSERT(pPosition);

                    CRect rcTextBox = pPosition->GetBounds();
                    rcTextBox.left  = rect.left + g_EditBoxSpaceFromBorder - rectSymbol.left;

                    // check if applied to correct splitter
                    if (pComp == pSplitter1 && y != 1)
                    {
                        rcTextBox.top = y - rectSymbol.top;

                        // don't adjust the bottom
                        rcTextBox.bottom -= rectSymbol.top;
                    }
                    else
                    {
                        rcTextBox.top = yPositionSplitter1 - rectSymbol.top;

                        // apply to the default one
                        if (!pComp)
                            rcTextBox.bottom = rect.top + (segmentHeight * 2) + g_EditBoxSpaceFromBorder - 2 - rectSymbol.top;
                        else
                            rcTextBox.bottom = y;
                    }

                    rcTextBox.right = rect.right - g_EditBoxSpaceFromBorder - rectSymbol.left;
                    pTextComment->MoveTo(rcTextBox);
                }
            }

            if (GetSplitter2() && GetAttributeTextEdit())
            {
                // move the second splitter
                CODLineComponent* pSplitter2     = GetSplitter2();
                CODTextComponent* pTextAttribute = GetAttributeTextEdit();

                // show the splitter and the text box
                pSplitter2->SetVisible(TRUE);
                pTextAttribute->SetVisible(TRUE);

                // do redraw the symbol
                redraw = true;

                if (m_RelativeCoordinates)
                {
                    // move in Relative coordinates
                    CRect rcSplitter2 = pSplitter2->GetEdgeRgn().GetBounds();
                    rcSplitter2.left  = rectEdgeRgn.left + g_SplitterLineSpaceFromBorder;

                    // check if applied to correct splitter
                    if (pComp == pSplitter2 && y != 1)
                    {
                        rcSplitter2.top    = (y - rect.top + offsetTop) * rectEdgeRgn.Height() / rect.Height();
                        rcSplitter2.bottom = rcSplitter2.top;

                        // save the y position of the splitter
                        yPositionSplitter2 = (y - rect.top + offsetTop);
                    }
                    else
                    {
                        // apply to the default one
                        if (!pComp)
                        {
                            rcSplitter2.top    = rectEdgeRgn.top + (segmentHeight * 2) + g_EditBoxSpaceFromBorder;
                            rcSplitter2.bottom = rcSplitter2.top;
                        }

                        // save the splitter y position
                        yPositionSplitter2 = rcSplitter2.top;
                    }

                    rcSplitter2.right = rcSplitter2.left + rectEdgeRgn.Width() - g_SplitterLineSpaceFromBorder;

                    float originX;
                    float originY;

                    // scale the splitter
                    pSplitter2->GetControlPoint(OD_TOP_LEFT, originX, originY);
                    const CRect rcBounds = pSplitter2->GetEdgeRgn().GetBounds();
                    const float scaleX   = float(rcSplitter2.Width()) / float(rcBounds.Width());
                    pSplitter2->Scale(scaleX, 1, originX, originY);
                    pSplitter2->MoveTo(CPoint(rcSplitter2.left, rcSplitter2.top));
                }
                else
                {
                    // move in absolute coordinates
                    CODComponentPosition* pPosition = pSplitter2->GetPosition();
                    ASSERT(pPosition);

                    CRect rcSplitter2 = pPosition->GetBounds();
                    rcSplitter2.left  = rect.left + g_SplitterLineSpaceFromBorder;

                    // check if applied to correct splitter
                    if (pComp == pSplitter2 && y != 1)
                        rcSplitter2.top = rcSplitter2.bottom = y;
                    else
                    if (!pComp)
                    {
                        rcSplitter2.top    = rect.top + (segmentHeight * 2) + g_EditBoxSpaceFromBorder;
                        rcSplitter2.bottom = rcSplitter2.top;
                    }

                    rcSplitter2.right = rect.right - g_SplitterLineSpaceFromBorder;

                    // save the splitter y position
                    yPositionSplitter2 = rcSplitter2.top;

                    float originX;
                    float originY;

                    // Scale the splitter
                    pSplitter2->GetControlPoint(OD_TOP_LEFT, originX, originY);
                    const CRect rcBounds = pPosition->GetBounds();
                    const float scaleX   = float(rcSplitter2.Width()) / float(rcBounds.Width());
                    pSplitter2->Scale(scaleX, 1, originX, originY);
                    pSplitter2->MoveTo(CPoint(rcSplitter2.left, rcSplitter2.top));
                }

                // move the text box attribute
                if (m_RelativeCoordinates)
                {
                    // move in relative coordinates
                    CRect rcTextBox = pTextAttribute->GetEdgeRgn().GetBounds();
                    rcTextBox.left  = rectEdgeRgn.left + g_EditBoxSpaceFromBorder;

                    // check if applied to correct splitter
                    if (pComp == pSplitter2 && y != 1)
                    {
                        rcTextBox.top = (y - rect.top + offsetTop) * rectEdgeRgn.Height() / rect.Height();

                        // don't adjust the bottom
                        rcTextBox.bottom = rectEdgeRgn.Height() + offsetTop - g_EditBoxSpaceFromBorder;
                    }
                    else
                    {
                        rcTextBox.top    = yPositionSplitter2;
                        rcTextBox.bottom = rectEdgeRgn.Height() + offsetTop - g_EditBoxSpaceFromBorder;
                    }

                    rcTextBox.right = rcTextBox.left + rectEdgeRgn.Width() - g_EditBoxSpaceFromBorder;
                    pTextAttribute->MoveTo(rcTextBox);
                }
                else
                {
                    // move in absolute coordinates
                    CODComponentPosition* pPosition = pTextAttribute->GetPosition();
                    ASSERT(pPosition);

                    CRect rcTextBox = pPosition->GetBounds();
                    rcTextBox.left  = rect.left + g_EditBoxSpaceFromBorder - rectSymbol.left;

                    // check if applied to correct splitter
                    if (pComp == pSplitter2 && y != 1)
                    {
                        rcTextBox.top = y - rectSymbol.top;

                        // don't adjust the bottom
                        rcTextBox.bottom -= rectSymbol.top;
                    }
                    else
                    {
                        rcTextBox.top    = yPositionSplitter2 - rectSymbol.top;
                        rcTextBox.bottom = rect.bottom - g_EditBoxSpaceFromBorder - rectSymbol.top;
                    }

                    rcTextBox.right = rect.right - g_EditBoxSpaceFromBorder - rectSymbol.left;
                    pTextAttribute->MoveTo(rcTextBox);
                }
            }
        }
    }
    else
    if (counterSplitter > 1)
    {
        // move the splitter, only resize the edit control if the rect is not empty
        if (!rect.IsRectEmpty())
        {
            int segmentHeight;

            if (m_RelativeCoordinates)
                segmentHeight = (rectEdgeRgn.Height() - (2 * g_EditBoxSpaceFromBorder)) / 2;
            else
                segmentHeight = (rect.Height()        - (2 * g_EditBoxSpaceFromBorder)) / 2;

            CODLineComponent* pSplitter1 = GetSplitter1();

            // only one splitter is needed
            if (pSplitter1)
            {
                pSplitter1->SetVisible(TRUE);

                // the symbol should be redrawn
                redraw = true;

                if (m_RelativeCoordinates)
                {
                    // move splitter in relative coordinates
                    CRect rcSplitter1 = pSplitter1->GetEdgeRgn().GetBounds();
                    rcSplitter1.left  = rectEdgeRgn.left + g_SplitterLineSpaceFromBorder;

                    // check if applied to correct splitter
                    if (pComp == pSplitter1 && y != 1)
                    {
                        rcSplitter1.top    = (y - rect.top + offsetTop) * rectEdgeRgn.Height() / rect.Height();
                        rcSplitter1.bottom = rcSplitter1.top;

                        // save the y position of the splitter
                        yPositionSplitter1 = (y - rect.top + offsetTop);
                    }
                    else
                    {
                        rcSplitter1.top    = rectEdgeRgn.top + segmentHeight + g_EditBoxSpaceFromBorder;
                        rcSplitter1.bottom = rcSplitter1.top;

                        // save the y position of the splitter
                        yPositionSplitter1 = rcSplitter1.top;
                    }

                    rcSplitter1.right = rcSplitter1.left + rectEdgeRgn.Width() - g_SplitterLineSpaceFromBorder;

                    float originX;
                    float originY;

                    // Scale the splitter
                    pSplitter1->GetControlPoint(OD_TOP_LEFT, originX, originY);
                    const CRect rcBounds = pSplitter1->GetEdgeRgn().GetBounds();
                    const float scaleX   = float(rcSplitter1.Width()) / float(rcBounds.Width());
                    pSplitter1->Scale(scaleX, 1, originX, originY);
                    pSplitter1->MoveTo(CPoint(rcSplitter1.left, rcSplitter1.top));
                }
                else
                {
                    // move in absolute coordinates
                    CODComponentPosition* pPosition = pSplitter1->GetPosition();
                    ASSERT(pPosition);

                    CRect rcSplitter1 = pPosition->GetBounds();
                    rcSplitter1.left  = rect.left + g_SplitterLineSpaceFromBorder;

                    // check if applied to correct splitter
                    if (pComp == pSplitter1 && y != 1)
                    {
                        rcSplitter1.top    = y;
                        rcSplitter1.bottom = y;
                    }
                    else
                    {
                        rcSplitter1.top    = rect.top + segmentHeight + g_EditBoxSpaceFromBorder;
                        rcSplitter1.bottom = rect.top + segmentHeight + g_EditBoxSpaceFromBorder;
                    }

                    rcSplitter1.right = rect.right - g_SplitterLineSpaceFromBorder;

                    // save the splitter y position
                    yPositionSplitter1 = rcSplitter1.top;

                    float originX;
                    float originY;

                    // scale the splitter
                    pSplitter1->GetControlPoint(OD_TOP_LEFT, originX, originY);
                    const CRect rcBounds = pSplitter1->GetBaseRgn().GetBounds();
                    const float scaleX   = float(rcSplitter1.Width()) / float(rcBounds.Width());
                    pSplitter1->Scale(scaleX, 1, originX, originY);
                    pSplitter1->MoveTo(CPoint(rcSplitter1.left, rcSplitter1.top));
                }

                bool doneFirst = false;

                // check the text box to realign between the splitter, the name is always the first or the comment
                if (IsNameAreaVisible())
                {
                    CODTextComponent* pTextName = GetSymbolNameTextEdit();

                    if (pTextName)
                    {
                        // show the symbol name edit box
                        pTextName->SetVisible(TRUE);

                        if (m_RelativeCoordinates)
                        {
                            // move the text box in relative coordinates
                            CRect rcTextBox = pTextName->GetEdgeRgn().GetBounds();
                            rcTextBox.left  = rectEdgeRgn.left + g_EditBoxSpaceFromBorder;

                            // check if applied to correct splitter
                            if (pComp == pSplitter1 && y != 1)
                            {
                                rcTextBox.top    = rectEdgeRgn.top + g_EditBoxSpaceFromBorder;
                                rcTextBox.bottom = (y - rect.top + offsetTop) * rectEdgeRgn.Height() / rect.Height();
                            }
                            else
                            {
                                rcTextBox.top    = rectEdgeRgn.top + g_EditBoxSpaceFromBorder;
                                rcTextBox.bottom = yPositionSplitter1;
                            }

                            rcTextBox.right = rcTextBox.left + rectEdgeRgn.Width() - g_EditBoxSpaceFromBorder;
                            pTextName->MoveTo(rcTextBox);
                        }
                        else
                        {
                            // move the text box in absolute coordinates
                            CODComponentPosition* pPosition = pTextName->GetPosition();
                            ASSERT(pPosition);

                            CRect rcTextBox = pPosition->GetBounds();
                            rcTextBox.left  = rect.left + g_EditBoxSpaceFromBorder - rectSymbol.left;

                            // check if applied to correct splitter
                            if (pComp == pSplitter1 && y != 1)
                            {
                                rcTextBox.top    = rect.top + g_EditBoxSpaceFromBorder - rectSymbol.top;
                                rcTextBox.bottom = y - rectSymbol.top;
                            }
                            else
                            {
                                rcTextBox.top    = rect.top + g_EditBoxSpaceFromBorder - rectSymbol.top;
                                rcTextBox.bottom = yPositionSplitter1 - rectSymbol.top;
                            }

                            rcTextBox.right = rect.right - g_EditBoxSpaceFromBorder - rectSymbol.left;
                            pTextName->MoveTo(rcTextBox);
                        }

                        doneFirst = true;
                    }
                }
                else
                {
                    // don't need to include this edit area, just resize it at the symbol bottom
                    CODTextComponent* pTextName = GetSymbolNameTextEdit();

                    if (pTextName)
                    {
                        if (m_RelativeCoordinates)
                        {
                            // move the text box in relative coordinates
                            CRect rcTextBox  = pTextName->GetEdgeRgn().GetBounds();
                            rcTextBox.left   = rectEdgeRgn.left     + g_EditBoxSpaceFromBorder;
                            rcTextBox.top    = rectEdgeRgn.Height() - g_EditBoxSpaceFromBorder - 2;
                            rcTextBox.bottom = rectEdgeRgn.Height() - g_EditBoxSpaceFromBorder;
                            rcTextBox.right  = rectEdgeRgn.Width()  - g_EditBoxSpaceFromBorder;
                            pTextName->MoveTo(rcTextBox);
                        }
                        else
                        {
                            // move the text box in absolute coordinates
                            CODComponentPosition* pPosition = pTextName->GetPosition();
                            ASSERT(pPosition);

                            CRect rcTextBox  = pPosition->GetBounds();
                            rcTextBox.left   = rect.left   + g_EditBoxSpaceFromBorder - rectSymbol.left;
                            rcTextBox.top    = rect.bottom - g_EditBoxSpaceFromBorder - rectSymbol.top;
                            rcTextBox.bottom = rect.bottom - 1                        - rectSymbol.top;
                            rcTextBox.right  = rect.right  - g_EditBoxSpaceFromBorder - rectSymbol.left;
                            pTextName->MoveTo(rcTextBox);
                        }
                    }
                }

                // the description is either the first or the last
                if (IsDescriptionsAreaVisible())
                {
                    CODTextComponent* pTextComment = GetCommentTextEdit();

                    if (pTextComment)
                    {
                        // show the symbol comment edit box
                        pTextComment->SetVisible(TRUE);

                        if (m_RelativeCoordinates)
                        {
                            // move the text box in relative coordinates
                            CRect rcTextBox = pTextComment->GetEdgeRgn().GetBounds();
                            rcTextBox.left  = rectEdgeRgn.left + g_EditBoxSpaceFromBorder;

                            // check if applied to correct splitter
                            if (pComp == pSplitter1 && y != 1)
                            {
                                if (doneFirst)
                                {
                                    rcTextBox.top    = (y - rect.top + offsetTop) * rectEdgeRgn.Height() / rect.Height();
                                    rcTextBox.bottom = rectEdgeRgn.Height() + offsetTop - g_EditBoxSpaceFromBorder;
                                }
                                else
                                {
                                    rcTextBox.top    = rectEdgeRgn.top + g_EditBoxSpaceFromBorder;
                                    rcTextBox.bottom = (y - rect.top + offsetTop) * rectEdgeRgn.Height() / rect.Height();
                                }
                            }
                            else
                            {
                                if (doneFirst)
                                {
                                    rcTextBox.top    = yPositionSplitter1;
                                    rcTextBox.bottom = rectEdgeRgn.Height() + offsetTop - g_EditBoxSpaceFromBorder;
                                }
                                else
                                {
                                    rcTextBox.top    = rectEdgeRgn.top + g_EditBoxSpaceFromBorder;
                                    rcTextBox.bottom = yPositionSplitter1;
                                }
                            }

                            rcTextBox.right = rcTextBox.left + rectEdgeRgn.Width() - g_EditBoxSpaceFromBorder;
                            pTextComment->MoveTo(rcTextBox);
                        }
                        else
                        {
                            // move the text box in absolute coordinates
                            CODComponentPosition* pPosition = pTextComment->GetPosition();
                            ASSERT(pPosition);

                            CRect rcTextBox = pPosition->GetBounds();
                            rcTextBox.left  = rect.left + g_EditBoxSpaceFromBorder - rectSymbol.left;

                            // check if applied to correct splitter
                            if (pComp == pSplitter1 && y != 1)
                            {
                                if (doneFirst)
                                {
                                    rcTextBox.top     = y - rectSymbol.top;
                                    rcTextBox.bottom -=     rectSymbol.top;
                                }
                                else
                                {
                                    rcTextBox.top   -=     rectSymbol.top;
                                    rcTextBox.bottom = y - rectSymbol.top;
                                }
                            }
                            else
                            if (doneFirst)
                            {
                                rcTextBox.top    = yPositionSplitter1 - rectSymbol.top;
                                rcTextBox.bottom = rect.bottom - g_EditBoxSpaceFromBorder - rectSymbol.top;
                            }
                            else
                            {
                                rcTextBox.top    = rect.top + g_EditBoxSpaceFromBorder - rectSymbol.top;
                                rcTextBox.bottom = yPositionSplitter1 - rectSymbol.top;
                            }

                            rcTextBox.right = rect.right - g_EditBoxSpaceFromBorder - rectSymbol.left;
                            pTextComment->MoveTo(rcTextBox);
                        }

                        doneFirst = true;
                    }
                }
                else
                {
                    // don't need to include this edit area, just resize it at the symbol bottom
                    CODTextComponent* pTextComment = GetCommentTextEdit();

                    if (pTextComment)
                        if (m_RelativeCoordinates)
                        {
                            // move the text box in relative coordinates
                            CRect rcTextBox  = pTextComment->GetEdgeRgn().GetBounds();
                            rcTextBox.left   = rectEdgeRgn.left     + g_EditBoxSpaceFromBorder;
                            rcTextBox.top    = rectEdgeRgn.Height() - g_EditBoxSpaceFromBorder - 2;
                            rcTextBox.bottom = rectEdgeRgn.Height() - g_EditBoxSpaceFromBorder;
                            rcTextBox.right  = rectEdgeRgn.Width()  - g_EditBoxSpaceFromBorder;
                            pTextComment->MoveTo(rcTextBox);
                        }
                        else
                        {
                            // move the text box in absolute coordinates
                            CODComponentPosition* pPosition = pTextComment->GetPosition();
                            ASSERT(pPosition);

                            CRect rcTextBox  = pPosition->GetBounds();
                            rcTextBox.left   = rect.left   + g_EditBoxSpaceFromBorder - rectSymbol.left;
                            rcTextBox.top    = rect.bottom - g_EditBoxSpaceFromBorder - rectSymbol.top;
                            rcTextBox.bottom = rect.bottom - 1                        - rectSymbol.top;
                            rcTextBox.right  = rect.right  - g_EditBoxSpaceFromBorder - rectSymbol.left;
                            pTextComment->MoveTo(rcTextBox);
                        }
                }

                // the attribute is always the last
                if (IsAttributeAreaVisible())
                {
                    CODTextComponent* pTextAttribute = GetAttributeTextEdit();

                    if (pTextAttribute)
                    {
                        // show the symbol attribute edit box
                        pTextAttribute->SetVisible(TRUE);

                        if (m_RelativeCoordinates)
                        {
                            // move the text box in relative coordinates
                            CRect rcTextBox = pTextAttribute->GetEdgeRgn().GetBounds();
                            rcTextBox.left  = rectEdgeRgn.left + g_EditBoxSpaceFromBorder;

                            // check if applied to correct splitter
                            if (pComp == pSplitter1 && y != 1)
                            {
                                rcTextBox.top    = (y - rect.top + offsetTop) * rectEdgeRgn.Height() / rect.Height();
                                rcTextBox.bottom = rectEdgeRgn.Height() + offsetTop - g_EditBoxSpaceFromBorder;
                            }
                            else
                            {
                                rcTextBox.top    = yPositionSplitter1;
                                rcTextBox.bottom = rectEdgeRgn.Height() + offsetTop - g_EditBoxSpaceFromBorder;
                            }

                            rcTextBox.right = rcTextBox.left + rectEdgeRgn.Width() - g_EditBoxSpaceFromBorder;
                            pTextAttribute->MoveTo(rcTextBox);
                        }
                        else
                        {
                            // move the text box in absolute coordinates
                            CODComponentPosition* pPosition = pTextAttribute->GetPosition();
                            ASSERT(pPosition);

                            CRect rcTextBox = pPosition->GetBounds();
                            rcTextBox.left  = rect.left + g_EditBoxSpaceFromBorder - rectSymbol.left;

                            // check if applied to correct splitter
                            if (pComp == pSplitter1 && y != 1)
                            {
                                rcTextBox.top    = y - rectSymbol.top;
                                rcTextBox.bottom = rect.bottom - g_EditBoxSpaceFromBorder - rectSymbol.top;
                            }
                            else
                            {
                                rcTextBox.top    = yPositionSplitter1 - rectSymbol.top;
                                rcTextBox.bottom = rect.bottom - g_EditBoxSpaceFromBorder - rectSymbol.top;
                            }

                            rcTextBox.right = rect.right - g_EditBoxSpaceFromBorder - rectSymbol.left;
                            pTextAttribute->MoveTo(rcTextBox);
                        }
                    }
                }
                else
                {
                    // don't need to include this edit area, just resize it at the symbol bottom
                    CODTextComponent* pTextAttribute = GetAttributeTextEdit();

                    if (pTextAttribute)
                        if (m_RelativeCoordinates)
                        {
                            // move the text box in relative coordinates
                            CRect rcTextBox  = pTextAttribute->GetEdgeRgn().GetBounds();
                            rcTextBox.left   = rectEdgeRgn.left     + g_EditBoxSpaceFromBorder;
                            rcTextBox.top    = rectEdgeRgn.Height() - g_EditBoxSpaceFromBorder - 2;
                            rcTextBox.bottom = rectEdgeRgn.Height() - g_EditBoxSpaceFromBorder;
                            rcTextBox.right  = rectEdgeRgn.Width()  - g_EditBoxSpaceFromBorder;
                            pTextAttribute->MoveTo(rcTextBox);
                        }
                        else
                        {
                            // move the text box in absolute coordinates
                            CODComponentPosition* pPosition = pTextAttribute->GetPosition();
                            ASSERT(pPosition);

                            CRect rcTextBox  = pPosition->GetBounds();
                            rcTextBox.left   = rect.left   + g_EditBoxSpaceFromBorder - rectSymbol.left;
                            rcTextBox.top    = rect.bottom - g_EditBoxSpaceFromBorder - rectSymbol.top;
                            rcTextBox.bottom = rect.bottom - 1                        - rectSymbol.top;
                            rcTextBox.right  = rect.right  - g_EditBoxSpaceFromBorder - rectSymbol.left;
                            pTextAttribute->MoveTo(rcTextBox);
                        }
                }
            }

            // need only one splitter
            if (GetSplitter2() && GetSplitter2()->IsVisible())
            {
                GetSplitter2()->SetVisible(FALSE);

                // do redraw the symbol
                redraw = true;
            }
        }
    }
    else
    {
        // don't need splitter
        if (GetSplitter1() && GetSplitter1()->IsVisible())
        {
            GetSplitter1()->SetVisible(FALSE);

            // do redraw the symbol
            redraw = true;
        }

        if (GetSplitter2() && GetSplitter2()->IsVisible())
        {
            GetSplitter2()->SetVisible(FALSE);

            // do redraw the symbol
            redraw = true;
        }

        // move the splitters
        CODComponent* pEditBoxArea = GetEditBoxArea();
        ASSERT(pEditBoxArea);

        std::unique_ptr<CODComponentPosition> pCompPosition(pEditBoxArea ? pEditBoxArea->GetPosition() : pSymComp->GetPosition());
        const CRect           rect          = pCompPosition->GetBounds();
        const CRect           rectEdgeRgn   = pEditBoxArea->GetEdgeRgn().GetBounds();

        // only resize edit control if the rect is not empty
        if (!rect.IsRectEmpty())
        {
            // check which component should be shown
            if (IsNameAreaVisible() && GetSymbolNameTextEdit())
            {
                CODTextComponent* pTextName = GetSymbolNameTextEdit();

                // show the symbol name edit box
                pTextName->SetVisible(TRUE);

                if (m_RelativeCoordinates)
                {
                    // move the text box in relative coordinates
                    CRect rcTextBox  = pTextName->GetEdgeRgn().GetBounds();
                    rcTextBox.left   = rectEdgeRgn.left     + g_EditBoxSpaceFromBorder;
                    rcTextBox.top    = rectEdgeRgn.top      + g_EditBoxSpaceFromBorder;
                    rcTextBox.right  = rcTextBox.left       + rectEdgeRgn.Width() - g_EditBoxSpaceFromBorder;
                    rcTextBox.bottom = rectEdgeRgn.Height() + offsetTop           - g_EditBoxSpaceFromBorder;
                    pTextName->MoveTo(rcTextBox);
                }
                else
                {
                    // move the text box in absolute coordinates
                    CODComponentPosition* pPosition = pTextName->GetPosition();
                    ASSERT(pPosition);

                    CRect rcTextBox  = pPosition->GetBounds();
                    rcTextBox.left   = rect.left   + g_EditBoxSpaceFromBorder - rectSymbol.left;
                    rcTextBox.top    = rect.top    + g_EditBoxSpaceFromBorder - rectSymbol.top;
                    rcTextBox.bottom = rect.bottom - g_EditBoxSpaceFromBorder - rectSymbol.top;
                    rcTextBox.right  = rect.right  - g_EditBoxSpaceFromBorder - rectSymbol.left;
                    pTextName->MoveTo(rcTextBox);
                }
            }
            else
            if (IsDescriptionsAreaVisible() && GetCommentTextEdit())
            {
                CODTextComponent* pTextComment = GetCommentTextEdit();

                // show the symbol comment edit box
                pTextComment->SetVisible(TRUE);

                if (m_RelativeCoordinates)
                {
                    // move the text box in relative coordinates
                    CRect rcTextBox  = pTextComment->GetEdgeRgn().GetBounds();
                    rcTextBox.left   = rectEdgeRgn.left     + g_EditBoxSpaceFromBorder;
                    rcTextBox.top    = rectEdgeRgn.top      + g_EditBoxSpaceFromBorder;
                    rcTextBox.right  = rcTextBox.left       + rectEdgeRgn.Width() - g_EditBoxSpaceFromBorder;
                    rcTextBox.bottom = rectEdgeRgn.Height() + offsetTop           - g_EditBoxSpaceFromBorder;
                    pTextComment->MoveTo(rcTextBox);
                }
                else
                {
                    // move the text box in absolute coordinates
                    CODComponentPosition* pPosition = pTextComment->GetPosition();
                    ASSERT(pPosition);

                    CRect rcTextBox  = pPosition->GetBounds();
                    rcTextBox.left   = rect.left   + g_EditBoxSpaceFromBorder - rectSymbol.left;
                    rcTextBox.top    = rect.top    + g_EditBoxSpaceFromBorder - rectSymbol.top;
                    rcTextBox.bottom = rect.bottom - g_EditBoxSpaceFromBorder - rectSymbol.top;
                    rcTextBox.right  = rect.right  - g_EditBoxSpaceFromBorder - rectSymbol.left;
                    pTextComment->MoveTo(rcTextBox);
                }
            }
            else
            if (IsAttributeAreaVisible() && GetAttributeTextEdit())
            {
                CODTextComponent* pTextAttribute = GetAttributeTextEdit();

                // show the symbol attribute edit box
                pTextAttribute->SetVisible(TRUE);

                if (m_RelativeCoordinates)
                {
                    // move the text box in relative coordinates
                    CRect rcTextBox  = pTextAttribute->GetEdgeRgn().GetBounds();
                    rcTextBox.left   = rectEdgeRgn.left     + g_EditBoxSpaceFromBorder;
                    rcTextBox.top    = rectEdgeRgn.top      + g_EditBoxSpaceFromBorder;
                    rcTextBox.right  = rcTextBox.left       + rectEdgeRgn.Width() - g_EditBoxSpaceFromBorder;
                    rcTextBox.bottom = rectEdgeRgn.Height() + offsetTop           - g_EditBoxSpaceFromBorder;
                    pTextAttribute->MoveTo(rcTextBox);
                }
                else
                {
                    // move the text box in absolute coordinates
                    CODComponentPosition* pPosition = pTextAttribute->GetPosition();
                    ASSERT(pPosition);

                    CRect rcTextBox  = pPosition->GetBounds();
                    rcTextBox.left   = rect.left   + g_EditBoxSpaceFromBorder - rectSymbol.left;
                    rcTextBox.top    = rect.top    + g_EditBoxSpaceFromBorder - rectSymbol.top;
                    rcTextBox.bottom = rect.bottom - g_EditBoxSpaceFromBorder - rectSymbol.top;
                    rcTextBox.right  = rect.right  - g_EditBoxSpaceFromBorder - rectSymbol.left;
                    pTextAttribute->MoveTo(rcTextBox);
                }
            }
        }
    }

    // check which text box to hide
    if (!IsNameAreaVisible() && GetSymbolNameTextEdit() && GetSymbolNameTextEdit()->IsVisible())
    {
        // hide the symbol name edit box
        GetSymbolNameTextEdit()->SetVisible(FALSE);

        // do redraw the symbol
        redraw = true;
    }

    if (!IsAttributeAreaVisible() && GetAttributeTextEdit() && GetAttributeTextEdit()->IsVisible())
    {
        // hide the symbol attribute edit box
        GetAttributeTextEdit()->SetVisible(FALSE);

        // do redraw the symbol
        redraw = true;
    }

    if (!IsDescriptionsAreaVisible() && GetCommentTextEdit() && GetCommentTextEdit()->IsVisible())
    {
        // hide the symbol comment edit box
        GetCommentTextEdit()->SetVisible(FALSE);

        // do redraw the symbol
        redraw = true;
    }

    // do redraw the symbol?
    if (redraw)
        m_pSymbol->RedrawSymbol();

    #ifdef _DEBUG
        // check the of text boxes position 
        std::unique_ptr<CODComponentPosition> pCompPosition(pSymComp->GetPosition());
        CRect                                 rectFinalText = pCompPosition->GetBounds();

        CString str;
        str.Format(_T("\nSymbol: top=%d left=%d bottom=%d right=%d\n"),
                   rectFinalText.top,
                   rectFinalText.left,
                   rectFinalText.bottom,
                   rectFinalText.right);

        TRACE(str);

        if (GetEditBoxArea())
        {
            std::unique_ptr<CODComponentPosition> pTextPosition(GetEditBoxArea()->GetPosition());
            rectFinalText = pTextPosition->GetBounds();

            str.Format(_T("AreaBox: top=%d left=%d bottom=%d right=%d\n"),
                       rectFinalText.top,
                       rectFinalText.left,
                       rectFinalText.bottom,
                       rectFinalText.right);

            TRACE(str);
        }

        if (GetSymbolNameTextEdit())
        {
            std::unique_ptr<CODComponentPosition> pTextPosition(GetSymbolNameTextEdit()->GetPosition());
            rectFinalText = pTextPosition->GetBounds();

            str.Format(_T("NameBox: top=%d left=%d bottom=%d right=%d\n"),
                       rectFinalText.top,
                       rectFinalText.left,
                       rectFinalText.bottom,
                       rectFinalText.right);

            TRACE(str);
        }

        if (GetCommentTextEdit())
        {
            std::unique_ptr<CODComponentPosition> pTextPosition(GetCommentTextEdit()->GetPosition());
            rectFinalText = pTextPosition->GetBounds();

            str.Format(_T("CommentBox: top=%d left=%d bottom=%d right=%d\n"),
                     rectFinalText.top,
                     rectFinalText.left,
                     rectFinalText.bottom,
                     rectFinalText.right);

            TRACE(str);
        }

        if (GetAttributeTextEdit())
        {
            std::unique_ptr<CODComponentPosition> pTextPosition(GetAttributeTextEdit()->GetPosition());
            rectFinalText = pTextPosition->GetBounds();

            str.Format(_T("AttributeBox: top=%d left=%d bottom=%d right=%d\n"),
                       rectFinalText.top,
                       rectFinalText.left,
                       rectFinalText.bottom,
                       rectFinalText.right);

            TRACE(str);
        }

        if (GetSplitter1())
        {
            std::unique_ptr<CODComponentPosition> pSplitterPosition(GetSplitter1()->GetPosition());
            rectFinalText = pSplitterPosition->GetBounds();

            str.Format(_T("Splitter1: top=%d left=%d bottom=%d right=%d\n"),
                     rectFinalText.top,
                     rectFinalText.left,
                     rectFinalText.bottom,
                     rectFinalText.right);

            TRACE(str);
        }

        if (GetSplitter2())
        {
            std::unique_ptr<CODComponentPosition> pSplitterPosition(GetSplitter2()->GetPosition());
            rectFinalText = pSplitterPosition->GetBounds();

            str.Format(_T("Splitter2: top=%d left=%d bottom=%d right=%d\n"),
                       rectFinalText.top,
                       rectFinalText.left,
                       rectFinalText.bottom,
                       rectFinalText.right);

            TRACE(str);
        }
    #endif
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributes::AdjustElementPosition()
{}
//---------------------------------------------------------------------------
CODComponent* PSS_SymbolAttributes::GetEditBoxArea()
{
    ASSERT(m_pSymbol);

    if (!m_pEditBoxArea)
    {
        CODComponent* pComp = dynamic_cast<CODComponent*>(m_pSymbol);

        if (pComp)
            m_pEditBoxArea = PSS_ODSymbolManipulator::FindSymbol(pComp, M_EditAreaComponentControlLabel);

        // if not found, locate label
        if (!m_pEditBoxArea)
        {
            CODSymbolComponent* pSymComp = dynamic_cast<CODSymbolComponent*>(m_pSymbol);

            if (pSymComp)
                m_pEditBoxArea = PSS_ODSymbolManipulator::FindLabel(pSymComp, M_EditAreaComponentControlLabel);
        }
    }

    return m_pEditBoxArea;
}
//---------------------------------------------------------------------------
CODTextComponent* PSS_SymbolAttributes::GetSymbolNameTextEdit()
{
    ASSERT(m_pSymbol);

    if (!m_pNameEditText)
    {
        CODComponent* pComp  = dynamic_cast<CODComponent*>(m_pSymbol);
        CODComponent* pFound = NULL;

        if (pComp)
            pFound = PSS_ODSymbolManipulator::FindSymbol(pComp, M_SymbolNameComponentControlLabel);

        if (pFound)
            m_pNameEditText = dynamic_cast<CODTextComponent*>(pFound);
    }

    return m_pNameEditText;
}
//---------------------------------------------------------------------------
CODTextComponent* PSS_SymbolAttributes::GetCommentTextEdit()
{
    ASSERT(m_pSymbol);

    if (!m_pCommentEditText)
    {
        CODComponent* pComp  = dynamic_cast<CODComponent*>(m_pSymbol);
        CODComponent* pFound = NULL;
        
        if (pComp)
            pFound = PSS_ODSymbolManipulator::FindSymbol(pComp, M_CommentComponentControlLabel);

        if (pFound)
            m_pCommentEditText = dynamic_cast<CODTextComponent*>(pFound);
    }

    return m_pCommentEditText;
}
//---------------------------------------------------------------------------
CODTextComponent* PSS_SymbolAttributes::GetAttributeTextEdit()
{
    ASSERT(m_pSymbol);

    if (!m_pAttributeEditText)
    {
        CODComponent* pComp  = dynamic_cast<CODComponent*>(m_pSymbol);
        CODComponent* pFound = NULL;

        if (pComp)
            pFound = PSS_ODSymbolManipulator::FindSymbol(pComp, M_AttributeAreaComponentLabel);

        if (pFound)
            m_pAttributeEditText = dynamic_cast<CODTextComponent*>(pFound);
    }

    return m_pAttributeEditText;
}
//---------------------------------------------------------------------------
CODLineComponent* PSS_SymbolAttributes::GetSplitter1()
{
    ASSERT(m_pSymbol);

    if (!m_pSplitterComponent1)
    {
        CODComponent* pComp  = dynamic_cast<CODComponent*>(m_pSymbol);
        CODComponent* pFound = NULL;

        if (pComp)
            pFound = PSS_ODSymbolManipulator::FindSymbol(pComp, M_SplitterComponentLine1);

        if (pFound)
            m_pSplitterComponent1 = dynamic_cast<CODLineComponent*>(pFound);
    }

    return m_pSplitterComponent1;
}
//---------------------------------------------------------------------------
CODLineComponent* PSS_SymbolAttributes::GetSplitter2()
{
    ASSERT(m_pSymbol);

    if (!m_pSplitterComponent2)
    {
        CODComponent* pComp  = dynamic_cast<CODComponent*>(m_pSymbol);
        CODComponent* pFound = NULL;

        if (pComp)
            pFound = PSS_ODSymbolManipulator::FindSymbol(pComp, M_SplitterComponentLine2);

        if (pFound)
            m_pSplitterComponent2 = dynamic_cast<CODLineComponent*>(pFound);
    }

    return m_pSplitterComponent2;
}
//---------------------------------------------------------------------------
bool PSS_SymbolAttributes::OnMouseMove(UINT flags, const CPoint& point, CODController& ctrl)
{
    if (!UseDynamicArea())
        return false;

    // check if splitter moving mode is enabled
    if (g_InMoveSplitterMode)
    {
        // get the device context to draw to
        CWnd* pWnd = ctrl.GetWnd();

        if (!pWnd)
            return true;

        CDC* pDC = pWnd->GetDC();

        if (!pDC)
            return true;

        try
        {
            // convert the mouse position
            CPoint pt(point);
            ctrl.VpLPtoDP(&pt);

            CPen  penMark(PS_DASH, 0, defCOLOR_BLACK);
            CPen* pPrevPen = (CPen*)pDC->SelectObject(&penMark);
            int   prevRop2 = pDC->SetROP2(R2_NOTXORPEN);

            // if not empty, erase the previous line
            if (g_LastPoint.x && g_LastPoint.y)
            {
                pDC->MoveTo(g_InitialSymbolRect.left,  g_LastPoint.y);
                pDC->LineTo(g_InitialSymbolRect.right, g_LastPoint.y);
            }

            // check the maximum and the minimum
            if (g_MaxUp && g_MaxDown)
                if (pt.y > g_MaxDown)
                    pt.y = g_MaxDown;
                else
                if (pt.y < g_MaxUp)
                    pt.y = g_MaxUp;

            pDC->MoveTo(g_InitialSymbolRect.left,  pt.y);
            pDC->LineTo(g_InitialSymbolRect.right, pt.y);

            pDC->SetROP2(prevRop2);
            pDC->SelectObject(pPrevPen);

            // save the current line position
            g_LastPoint = pt;
        }
        catch (...)
        {
            pWnd->ReleaseDC(pDC);
            throw;
        }

        // release the used dc
        pWnd->ReleaseDC(pDC);

        return true;
    }
    else
    {
        // check if the first splitter is visible and over
        if (GetSplitter1() && GetSplitter1()->IsVisible())
        {
            std::unique_ptr<CODComponentPosition> pPosition(GetSplitter1()->GetPosition());

            CRect rcSplitter1 = pPosition->GetBounds();
            rcSplitter1.InflateRect(0, 3);

            if (rcSplitter1.PtInRect(point))
            {
                ctrl.SetCustomCursor(IDC_SYM_SPLITTER_V);
                return true;
            }
        }

        // check if the second splitter is visible and over
        if (GetSplitter2() && GetSplitter2()->IsVisible())
        {
            std::unique_ptr<CODComponentPosition> pPosition(GetSplitter2()->GetPosition());

            CRect rcSplitter2 = pPosition->GetBounds();
            rcSplitter2.InflateRect(0, 3);

            if (rcSplitter2.PtInRect(point))
            {
                ctrl.SetCustomCursor(IDC_SYM_SPLITTER_V);
                return true;
            }
        }
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_SymbolAttributes::OnLButtonDown(UINT nFlags, const CPoint& point, CODController& ctrl)
{
    if (!UseDynamicArea())
        return false;

    CODComponent* pSymComp = dynamic_cast<CODComponent*>(m_pSymbol);
    ASSERT(pSymComp);

    // check if positioned above a splitter
    if (GetSplitter1() && GetSplitter1()->IsVisible())
    {
        std::unique_ptr<CODComponentPosition> pPosition(GetSplitter1()->GetPosition());

        CRect rcSplitter1 = pPosition->GetBounds();
        rcSplitter1.InflateRect(0, 3);

        if (rcSplitter1.PtInRect(point))
        {
            g_InMoveSplitterMode = true;
            g_MoveSplitter1      = true;

            CODComponent*                         pEditBoxArea  = GetEditBoxArea();
            std::unique_ptr<CODComponentPosition> pCompPosition(pEditBoxArea ? pEditBoxArea->GetPosition() : pSymComp->GetPosition());

            g_InitialSymbolRect = pCompPosition->GetBounds();
            g_InitialSymbolRect.DeflateRect(g_EditBoxSpaceFromBorder, g_EditBoxSpaceFromBorder);

            // convert the mouse position
            CPoint pt(point);
            ctrl.VpLPtoDP(&pt);

            // convert the start position
            CPoint start(g_InitialSymbolRect.left, g_InitialSymbolRect.top);
            ctrl.VpLPtoDP(&start);

            // convert the end position
            CPoint end(g_InitialSymbolRect.right, g_InitialSymbolRect.bottom);
            ctrl.VpLPtoDP(&end);

            g_InitialSymbolRect.left   = start.x;
            g_InitialSymbolRect.top    = start.y;
            g_InitialSymbolRect.right  = end.x;
            g_InitialSymbolRect.bottom = end.y;

            g_InitialPoint = pt;
            g_LastPoint.x  = 0;
            g_LastPoint.y  = 0;

            // check if the max limit was reached
            if (GetSplitter2() && GetSplitter2()->IsVisible())
            {
                std::unique_ptr<CODComponentPosition> pPosition(GetSplitter2()->GetPosition());

                CRect rcSplitter2 = pPosition->GetBounds();
                rcSplitter2.InflateRect(0, 3);

                // convert the point
                CPoint upPoint(rcSplitter2.left, rcSplitter2.top);
                ctrl.VpLPtoDP(&upPoint);

                g_MaxDown = upPoint.y;
                g_MaxUp   = g_InitialSymbolRect.top + g_EditBoxSpaceFromBorder;
            }
        }
    }

    // if not in move mode
    if (!g_InMoveSplitterMode && GetSplitter2() && GetSplitter2()->IsVisible())
    {
        std::unique_ptr<CODComponentPosition> pPosition(GetSplitter2()->GetPosition());

        CRect rcSplitter2 = pPosition->GetBounds();
        rcSplitter2.InflateRect(0, 3);

        if (rcSplitter2.PtInRect(point))
        {
            g_InMoveSplitterMode = true;
            g_MoveSplitter2      = true;

            CODComponent*                         pEditBoxArea  = GetEditBoxArea();
            std::unique_ptr<CODComponentPosition> pCompPosition(pEditBoxArea ? pEditBoxArea->GetPosition() : pSymComp->GetPosition());

            g_InitialSymbolRect = pCompPosition->GetBounds();
            g_InitialSymbolRect.DeflateRect(g_EditBoxSpaceFromBorder, g_EditBoxSpaceFromBorder);

            // convert the mouse position
            CPoint pt(point);
            ctrl.VpLPtoDP(&pt);

            // convert the start position
            CPoint start(g_InitialSymbolRect.left, g_InitialSymbolRect.top);
            ctrl.VpLPtoDP(&start);

            // convert the end position
            CPoint end(g_InitialSymbolRect.right, g_InitialSymbolRect.bottom);
            ctrl.VpLPtoDP(&end);

            g_InitialSymbolRect.left   = start.x;
            g_InitialSymbolRect.top    = start.y;
            g_InitialSymbolRect.right  = end.x;
            g_InitialSymbolRect.bottom = end.y;

            g_InitialPoint = pt;
            g_LastPoint.x  = 0;
            g_LastPoint.y  = 0;

            // check if the max limit reached
            if (GetSplitter1() && GetSplitter1()->IsVisible())
            {
                std::unique_ptr<CODComponentPosition> pPosition(GetSplitter1()->GetPosition());

                CRect rcSplitter1 = pPosition->GetBounds();
                rcSplitter1.InflateRect(0, 3);

                // convert the point
                CPoint upPoint(rcSplitter1.left, rcSplitter1.bottom);
                ctrl.VpLPtoDP(&upPoint);

                g_MaxUp   = upPoint.y;
                g_MaxDown = g_InitialSymbolRect.bottom - g_EditBoxSpaceFromBorder;
            }
        }
    }

    if (g_InMoveSplitterMode)
    {
        ctrl.SetCapture();
        CWnd* pWnd = ctrl.GetWnd();

        if (pWnd)
        {
            CRect rect(g_InitialSymbolRect);
            pWnd->ClientToScreen(&rect);
            ::ClipCursor(&rect);
        }
    }

    return g_InMoveSplitterMode;
}
//---------------------------------------------------------------------------
bool PSS_SymbolAttributes::OnLButtonUp(UINT nFlags, const CPoint& point, CODController& Ctrl)
{
    if (!UseDynamicArea())
        return false;

    // check if splitter moving mode is enabled
    if (g_InMoveSplitterMode)
    {
        // release the cursor capture
        Ctrl.ReleaseCapture();
        ::ClipCursor(NULL);

        // get the device context to draw to
        CWnd* pWnd = Ctrl.GetWnd();

        if (!pWnd)
            return true;

        CDC* pDC = pWnd->GetDC();

        if (!pDC)
            return true;

        try
        {
            // converts the mouse position
            CPoint pt(point);
            Ctrl.VpLPtoDP(&pt);

            CPen  penMark(PS_DASH, 0, defCOLOR_BLACK);
            CPen* pPrevPen = (CPen*)pDC->SelectObject(&penMark);
            int   prevRop2 = pDC->SetROP2(R2_NOTXORPEN);

            // if not empty, erase the previous line
            if (g_LastPoint.x && g_LastPoint.y)
            {
                pDC->MoveTo(g_InitialSymbolRect.left,  g_LastPoint.y);
                pDC->LineTo(g_InitialSymbolRect.right, g_LastPoint.y);
            }

            pDC->SetROP2(prevRop2);
            pDC->SelectObject(pPrevPen);

            // save the Y position
            if (g_MoveSplitter1)
                AdjustAreaPosition(GetSplitter1(), point.y);
            else
            if (g_MoveSplitter2)
                AdjustAreaPosition(GetSplitter2(), point.y);

            // reset the flags and the values
            g_InMoveSplitterMode =  false;
            g_SplitterPositionY  = -1;
            g_MoveSplitter1      =  false;
            g_MoveSplitter2      =  false;
            g_MaxUp              =  0;
            g_MaxDown            =  0;
        }
        catch (...)
        {
            pWnd->ReleaseDC(pDC);
            throw;
        }

        // release the used dc
        pWnd->ReleaseDC(pDC);
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributes::MoveTo(CODComponent& comp, const CPoint& pos)
{
    const CRect  rc = comp.GetPosition()->GetBounds();
    const CPoint ptOrigin(rc.left, rc.top);
    const CPoint ptTranslate(pos - ptOrigin);
    comp.Translate(ptTranslate.x, ptTranslate.y);
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributes::MoveTo(CODComponent& comp, const CRect& posRect)
{
    if (posRect.IsRectEmpty())
        return;

    const CRect boundsRect = comp.GetPosition()->GetBounds();
    const CSize translate  = posRect.TopLeft() - boundsRect.TopLeft();

    float originX;
    float originY;
    CODGlobal::GetControlPoint(boundsRect, OD_TOP_LEFT, originX, originY);

    const float scaleX = float(posRect.Width())  / float(boundsRect.Width());
    const float scaleY = float(posRect.Height()) / float(boundsRect.Height());

    CODTransform*                 pXTransform = comp.GetTransform();
    std::unique_ptr<CODTransform> pNewXTransform;

    if (!pXTransform)
    {
        pNewXTransform.reset(new CODTransform());
        pXTransform = pNewXTransform.get();
    }

    pXTransform->Scale(scaleX, scaleY, originX, originY);
    pXTransform->Translate(translate.cx, translate.cy);
    comp.SetTransform(pXTransform);
    comp.OnMove();

    if (pNewXTransform.get())
        pNewXTransform.release();
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributes::Scale(CODComponent& comp, const CSize& bounds, const OD_CONTROL_POINT controlPoint)
{
    if (bounds.cx || bounds.cy)
        return;

    float       originX;
    float       originY;
    const CRect boundsRect = comp.GetPosition()->GetBounds();
    CODGlobal::GetControlPoint(boundsRect, controlPoint, originX, originY);

    const float scaleX = float(bounds.cx) / float(boundsRect.Width());
    const float scaleY = float(bounds.cy) / float(boundsRect.Height());

    comp.Scale(scaleX, scaleY, originX, originY);
}
//---------------------------------------------------------------------------
