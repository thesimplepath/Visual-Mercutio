/****************************************************************************
 * ==> PSS_ODSymbolManipulator ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a helper to manipulate the Objective View symbols *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ODSymbolManipulator.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseSym\PSS_BasicSymbol.h"
#include "PSS_SymbolEdit.h"
#include "PSS_SymbolLabel.h"

// resources
#include "zModelRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ODSymbolManipulator
//---------------------------------------------------------------------------
PSS_SymbolEdit* PSS_ODSymbolManipulator::CreateEditText(CODComponent*  pSymbol,
                                                        const CString& areaName,
                                                        const CString& editName,
                                                        CODComponent*  pParent)
{
    if (!pSymbol)
        return NULL;

    CODComponent* pAreaComp = FindSymbol(pSymbol, areaName);

    if (!pAreaComp)
        return NULL;

    CODComponent* pComp = FindSymbol(pSymbol, editName);

    if (pComp)
        return NULL;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_SymbolEdit* PSS_ODSymbolManipulator::CreateAndReplaceEditText(CODComponent*  pSymbol,
                                                                  const CString& editName,
                                                                  CODComponent*  pParent)
{
    if (!pSymbol)
        return NULL;

    CODComponent* pComp = FindSymbol(pSymbol, editName);

    if (!pComp || !ISA(pComp, CODTextComponent))
    {
        CODSymbolComponent* pSymComp = dynamic_cast<CODSymbolComponent*>(pSymbol);

        if (pSymComp)
            pComp = FindLabel(pSymComp, editName);
    }

    // create the new symbol edit
    std::unique_ptr<PSS_SymbolEdit> pEdit(new PSS_SymbolEdit());

    // set its size
    pEdit->Create(pComp ? pComp->GetBounds() : pSymbol->GetBounds(), NULL);

    if (pParent)
        pParent->AppendChild(pEdit.get());
    else
        pSymbol->AppendChild(pEdit.get());

    // set its properties
    if (pComp)
    {
        CopyProperties(static_cast<CODEditProperties*>       (pComp->GetProperty(OD_PROP_EDIT)),              pEdit.get());
        CopyProperties(static_cast<CODOrientationProperties*>(pComp->GetProperty(OD_PROP_ORIENTATION)),       pEdit.get());
        CopyProperties(static_cast<CODFontProperties*>       (pComp->GetProperty(OD_PROP_FONT)),              pEdit.get());
        CopyProperties(static_cast<CODFillProperties*>       (pComp->GetProperty(OD_PROP_FILL)),              pEdit.get());
        CopyProperties(static_cast<CODLineProperties*>       (pComp->GetProperty(OD_PROP_LINE)),              pEdit.get());
        CopyProperty  (static_cast<CODBoolProperty*>         (pComp->GetProperty(OD_PROP_WORDBREAK)),         pEdit.get());
        CopyProperty  (static_cast<CODBoolProperty*>         (pComp->GetProperty(OD_PROP_MULTILINE)),         pEdit.get());
        CopyProperty  (static_cast<CODIntProperty*>          (pComp->GetProperty(OD_PROP_HORZ_ALIGNMENT)),    pEdit.get());
        CopyProperty  (static_cast<CODIntProperty*>          (pComp->GetProperty(OD_PROP_VERT_ALIGNMENT)),    pEdit.get());
        CopyProperty  (static_cast<CODBoolProperty*>         (pComp->GetProperty(OD_PROP_TRANSPARENT)),       pEdit.get());
        CopyProperty  (static_cast<CODDWordProperty*>        (pComp->GetProperty(OD_PROP_TRANSPARENT_COLOR)), pEdit.get());

        CODTextComponent* pTextComp = dynamic_cast<CODTextComponent*>(pComp);

        if (pTextComp)
            pEdit->SetText(pTextComp->GetText());
    }

    // set the new symbol name
    pEdit->SetName(editName);

    // remove the previous edit
    if (pComp)
        RemoveSymbol(pSymbol, pComp);

    return pEdit.release();
}
//---------------------------------------------------------------------------
PSS_SymbolLabel* PSS_ODSymbolManipulator::CreateAndReplaceLabelText(CODComponent*  pSymbol,
                                                                    const CString& editName,
                                                                    bool           notifyParent,
                                                                    CODComponent*  pParent)
{
    if (!pSymbol)
        return NULL;

    CODComponent* pComp = FindSymbol(pSymbol, editName);

    if (!pComp || !ISA(pComp, CODTextComponent))
    {
        CODSymbolComponent* pSymComp = dynamic_cast<CODSymbolComponent*>(pSymbol);

        if (pSymComp)
            pComp = FindLabel(pSymComp, editName);
    }

    // create the new symbol
    std::unique_ptr<PSS_SymbolLabel> pLabel(new PSS_SymbolLabel(notifyParent));

    CODTextComponent* pEditComp = dynamic_cast<CODTextComponent*>(pLabel.get());

    // set its size
    if (pEditComp)
        pEditComp->Create(pComp ? pComp->GetBounds() : pSymbol->GetBounds(), NULL);

    if (pParent)
    {
        CODSymbolComponent* pParentSym = dynamic_cast<CODSymbolComponent*>(pParent);

        if (pParentSym)
            pParentSym->AddLabel(pLabel.get());
        else
            pParent->AppendChild(pLabel.get());
    }
    else
    {
        CODSymbolComponent* pSymComp = dynamic_cast<CODSymbolComponent*>(pSymbol);

        if (pSymComp)
            pSymComp->AddLabel(pLabel.get());
        else
            pSymbol->AppendChild(pLabel.get());
    }

    // set its properties
    if (pComp)
    {
        CopyProperties(static_cast<CODEditProperties*>       (pComp->GetProperty(OD_PROP_EDIT)),              pLabel.get());
        CopyProperties(static_cast<CODOrientationProperties*>(pComp->GetProperty(OD_PROP_ORIENTATION)),       pLabel.get());
        CopyProperties(static_cast<CODFontProperties*>       (pComp->GetProperty(OD_PROP_FONT)),              pLabel.get());
        CopyProperties(static_cast<CODFillProperties*>       (pComp->GetProperty(OD_PROP_FILL)),              pLabel.get());
        CopyProperties(static_cast<CODLineProperties*>       (pComp->GetProperty(OD_PROP_LINE)),              pLabel.get());
        CopyProperty  (static_cast<CODBoolProperty*>         (pComp->GetProperty(OD_PROP_WORDBREAK)),         pLabel.get());
        CopyProperty  (static_cast<CODBoolProperty*>         (pComp->GetProperty(OD_PROP_MULTILINE)),         pLabel.get());
        CopyProperty  (static_cast<CODIntProperty*>          (pComp->GetProperty(OD_PROP_HORZ_ALIGNMENT)),    pLabel.get());
        CopyProperty  (static_cast<CODIntProperty*>          (pComp->GetProperty(OD_PROP_VERT_ALIGNMENT)),    pLabel.get());
        CopyProperty  (static_cast<CODBoolProperty*>         (pComp->GetProperty(OD_PROP_TRANSPARENT)),       pLabel.get());
        CopyProperty  (static_cast<CODDWordProperty*>        (pComp->GetProperty(OD_PROP_TRANSPARENT_COLOR)), pLabel.get());

        CODTextComponent* pTextComp = dynamic_cast<CODTextComponent*>(pComp);

        if (pTextComp)
            pLabel->SetText(pTextComp->GetText());
    }

    // set the new symbol name
    pLabel->SetName(editName);

    // remove the previous edit
    if (pComp)
        RemoveSymbol(pSymbol, pComp);

    return pLabel.release();
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::RemoveSymbol(CODComponent* pSymbol, const CString& componentName)
{
    CODComponent* pComp = FindSymbol(pSymbol, componentName);

    if (pComp)
        return RemoveSymbol(pSymbol, pComp);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::RemoveSymbol(CODComponent* pSymbol, CODComponent* pComponent)
{
    if (!pSymbol)
        return FALSE;

    // find the component set
    CODComponentSet* pSet    = pSymbol->GetComponents();
    const int        setSize = pSet->GetSize();

    for (int i = 0; i < setSize; ++i)
    {
        CODComponent* pCompLeft = pSet->GetAt(i);

        // is the right component?
        if (pCompLeft == pComponent)
        {
            pSet->RemoveAt(i);
            return TRUE;
        }

        // locate the components in its children
        if (pCompLeft->RemoveChild(pComponent))
            return TRUE;
    }

    CODSymbolComponent* pSymComp = dynamic_cast<CODSymbolComponent*>(pSymbol);

    // if not found, locate the child label
    if (pSymComp)
    {
        const int labelCount = pSymComp->GetNumLabels();

        for (int i = 0; i < labelCount; ++i)
        {
            CODLabelComponent* pLabel = pSymComp->GetLabel(i);

            // locate the components in its children
            if (pLabel == pComponent)
            {
                pSymComp->RemoveLabel(pLabel);
                return TRUE;
            }
        }
    }

    return FALSE;
}
//---------------------------------------------------------------------------
CODComponent* PSS_ODSymbolManipulator::FindSymbol(CODComponent* pSymbol, const CString& componentName)
{
    if (!pSymbol)
        return NULL;

    // find the matching label
    CODComponentSet* pSet    = pSymbol->GetComponents();
    const int        setSize = pSet->GetSize();

    for (int i = 0; i < setSize; ++i)
    {
        CODComponent* pComponent = pSet->GetAt(i);

        // is the right component?
        if (pComponent->GetName() == componentName)
            return pComponent;

        // locate the symbol in the components children
        CODComponent* pInChildComponent = FindSymbolInChild(pComponent, componentName);

        if (pInChildComponent)
            return pInChildComponent;
    }

    CODSymbolComponent* pSymComp = dynamic_cast<CODSymbolComponent*>(pSymbol);

    // if not found, locate the symbol in labels
    if (pSymComp)
    {
        CODLabelComponent* pLabel;

        for (int i = 0; i < pSymComp->GetNumLabels(); ++i)
        {
            pLabel = pSymComp->GetLabel(i);

            if (pLabel->GetName() == componentName)
                return pLabel;

            CString componentType = _T("");

            pLabel->GetValue(OD_PROP_TYPE, componentType);

            if (componentName == M_SymbolNameComponentControlLabel && componentType == _T("Label"))
            {
                pLabel->SetName(M_SymbolNameComponentControlLabel);
                return pLabel;
            }

            CODComponent* pInChildComponent = FindSymbolInChild(pLabel, componentName);

            if (pInChildComponent)
                return pInChildComponent;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
CODComponent* PSS_ODSymbolManipulator::FindSymbolInChild(CODComponent* pSymbol, const CString& componentName)
{
    if (!pSymbol)
        return NULL;

    // find the matching symbol in children
    const int childCount = pSymbol->GetChildCount();

    for (int i = 0; i < childCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (pComponent->GetName() == componentName)
            return pComponent;
    }

    return NULL;
}
//---------------------------------------------------------------------------
CODComponent* PSS_ODSymbolManipulator::FindLabel(CODSymbolComponent* pSymbol, const CString& labelName)
{
    if (!pSymbol)
        return NULL;

    const int labelCount = pSymbol->GetNumLabels();

    for (int i = 0; i < labelCount; ++i)
    {
        CODLabelComponent* pLabel = pSymbol->GetLabel(i);

        if (pLabel->GetName() == labelName)
            return pLabel;
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_ODSymbolManipulator::MatchSymbolAreaName(CODComponent* pSymbol, CODComponent* pSrcSymbol)
{
    if (!pSymbol || !pSrcSymbol)
        return;

    // assign the component name
    CODComponentSet* pSet    = pSymbol->GetComponents();
    CODComponentSet* pSrcSet = pSrcSymbol->GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComponent    = pSet->GetAt(i);
        CODComponent* pSrcComponent = pSrcSet->GetAt(i);

        if (!pComponent || !pSrcComponent)
            continue;

        // if found a matching name in the source
        if (pSrcComponent->GetName().Left(3) == _T("ZC_"))
            // assign the source name to the destination component
            pComponent->SetName(pSrcComponent->GetName());

        // match symbol name also in components children
        MatchSymbolAreaNameInChild(pComponent, pSrcComponent);
    }

    CODSymbolComponent* pSymComp = dynamic_cast<CODSymbolComponent*>(pSymbol);

    // match for labels
    if (pSymComp)
    {
        const int labelCount = pSymComp->GetNumLabels();

        for (int i = 0; i < labelCount; ++i)
        {
            CODLabelComponent* pLabel    = dynamic_cast<CODSymbolComponent*>(pSymbol)->GetLabel(i);
            CODLabelComponent* pSrcLabel = dynamic_cast<CODSymbolComponent*>(pSrcSymbol)->GetLabel(i);

            if (!pLabel || !pSrcLabel)
                continue;

            // if found a matching name in the source
            if (pSrcLabel->GetName().Left(3) == _T("ZC_"))
                // assign the source name to the destination component
                pLabel->SetName(pSrcLabel->GetName());

            MatchSymbolAreaNameInChild(pLabel, pSrcLabel);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ODSymbolManipulator::MatchSymbolAreaNameInChild(CODComponent* pSymbol, CODComponent* pSrcSymbol)
{
    if (!pSymbol || !pSrcSymbol)
        return;

    // match symbol names in children
    const int childCount = pSymbol->GetChildCount();

    for (int i = 0; i < childCount; ++i)
    {
        CODComponent* pComponent    = pSymbol->GetChild(i);
        CODComponent* pSrcComponent = pSrcSymbol->GetChild(i);

        if (!pComponent || !pSrcComponent)
            continue;

        // if found a matching name in the source
        if (pSrcComponent->GetName().Left(3) == _T("ZC_"))
            // assign the source name to the destination component
            pComponent->SetName(pSrcComponent->GetName());
    }
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::IsSymbolVisible(CODComponent* pSymbol, const CString& symbolName)
{
    CODComponent* pComp = FindSymbol(pSymbol, symbolName);

    if (pComp)
        return pComp->IsVisible();

    // if doesn't exist, then not visible
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::SetSymbolVisible(CODComponent* pSymbol, const CString& symbolName, BOOL visible)
{
    CODComponent* pComp = FindSymbol(pSymbol, symbolName);

    if (pComp)
    {
        pComp->SetVisible(visible);
        return TRUE;
    }

    // if doen't exist, then return false as an error
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::ChangeComponentLineColor(CODComponent* pSymbol, COLORREF color)
{
    if (!pSymbol)
        return FALSE;

    return pSymbol->SetValue(OD_PROP_LINE + OD_LINE_COLOR, color);
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::ChangeComponentLineWidth(CODComponent* pSymbol, int width)
{
    if (!pSymbol)
        return FALSE;

    return pSymbol->SetValue(OD_PROP_LINE + OD_LINE_WIDTH, width);
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::ChangeComponentLineColorWidth(CODComponent* pSymbol, COLORREF color, int width)
{
    if (!pSymbol)
        return FALSE;

    BOOL success = pSymbol->SetValue(OD_PROP_LINE + OD_LINE_COLOR, color);

    if (!pSymbol->SetValue(OD_PROP_LINE + OD_LINE_WIDTH, width))
        success = FALSE;

    return success;
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::ChangeLineColor(CODComponent* pSymbol, COLORREF color, const CString& symbolName)
{
    if (!pSymbol)
        return FALSE;

    BOOL result = FALSE;

    const int childCount = pSymbol->GetChildCount();

    // find the matching symbol in children
    for (int i = 0; i < childCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (!pComponent)
            continue;

        if (symbolName.IsEmpty() || pComponent->GetName() == symbolName)
            if (pComponent->SetValue(OD_PROP_LINE + OD_LINE_COLOR, color))
                result = TRUE;

        // if has children components
        if (pComponent->GetChildCount() > 0)
            result = ChangeLineColor(pComponent, color, symbolName);
    }

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::ChangeLineWidth(CODComponent* pSymbol, int width, const CString& symbolName)
{
    if (!pSymbol)
        return FALSE;

    BOOL result = FALSE;

    const int childCount = pSymbol->GetChildCount();

    // find the matching symbol in children
    for (int i = 0; i < childCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (!pComponent)
            continue;

        if (symbolName.IsEmpty() || pComponent->GetName() == symbolName)
            if (pComponent->SetValue(OD_PROP_LINE + OD_LINE_WIDTH, width))
                result = TRUE;

        // if contains children components
        if (pComponent->GetChildCount() > 0)
            result = ChangeLineWidth(pComponent, width, symbolName);
    }

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::ChangeLabelLineWidth(CODSymbolComponent* pSymbol, int width, const CString& labelName)
{
    if (!pSymbol)
        return FALSE;

    BOOL      result     = FALSE;
    const int labelCount = pSymbol->GetNumLabels();

    for (int i = 0; i < labelCount; ++i)
    {
        CODLabelComponent* pLabel = pSymbol->GetLabel(i);

        if (!pLabel)
            continue;

        if (labelName.IsEmpty() || pLabel->GetName() == labelName)
            result = pLabel->SetValue(OD_PROP_LINE + OD_LINE_WIDTH, width);
    }

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::ChangeLineStyle(CODComponent* pSymbol, int style, const CString& symbolName)
{
    if (!pSymbol)
        return FALSE;

    BOOL      result     = FALSE;
    const int childCount = pSymbol->GetChildCount();

    // find the matching symbol in children
    for (int i = 0; i < childCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (!pComponent)
            continue;

        if (symbolName.IsEmpty() || pComponent->GetName() == symbolName)
            if (pComponent->SetValue(OD_PROP_LINE + OD_LINE_STYLE, style))
                result = TRUE;

        // if has children components
        if (pComponent->GetChildCount() > 0)
            result = ChangeLineStyle(pComponent, style, symbolName);
    }

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::SetLabelItalic(CODSymbolComponent* pSymbol, BOOL doSetTextItalic, const CString& labelName)
{
    if (!pSymbol)
        return FALSE;

    BOOL      result     = FALSE;
    const int labelCount = pSymbol->GetNumLabels();

    for (int i = 0; i < labelCount; ++i)
    {
        CODLabelComponent* pLabel = pSymbol->GetLabel(i);

        if (!pLabel)
            continue;

        if (labelName.IsEmpty() || pLabel->GetName() == labelName)
            result = pLabel->SetValue(OD_PROP_FONT + OD_FONT_ITALIC, doSetTextItalic);
    }

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::ChangeLabelTextColor(CODSymbolComponent* pSymbol, COLORREF color, const CString& labelName)
{
    if (!pSymbol)
        return FALSE;

    BOOL      result     = FALSE;
    const int labelCount = pSymbol->GetNumLabels();

    for (int i = 0; i < labelCount; ++i)
    {
        CODLabelComponent* pLabel = pSymbol->GetLabel(i);

        if (!pLabel)
            continue;

        if (labelName.IsEmpty() || pLabel->GetName() == labelName)
            result = pLabel->SetValue(OD_PROP_FONT + OD_FONT_COLOR, color);
    }

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::SetTextItalic(CODComponent* pSymbol, BOOL doSetTextItalic, const CString& symbolName)
{
    if (!pSymbol)
        return FALSE;

    BOOL result = FALSE;

    const int childCount = pSymbol->GetChildCount();

    // find the matching symbol in children
    for (int i = 0; i < childCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (!pComponent)
            continue;

        if (symbolName.IsEmpty() || pComponent->GetName() == symbolName)
            if (pComponent->GetName() != _T("Texte1"))
                if (pComponent->SetValue(OD_PROP_FONT + OD_FONT_ITALIC, doSetTextItalic))
                    result = TRUE;

        // if contains children components
        if (pComponent->GetChildCount() > 0)
            result = SetTextItalic(pComponent, doSetTextItalic, symbolName);
    }

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::ChangeTextColor(CODComponent* pSymbol, COLORREF color, const CString& symbolName)
{
    if (!pSymbol)
        return FALSE;

    BOOL      result     = FALSE;
    const int childCount = pSymbol->GetChildCount();

    // find the matching symbol in children
    for (int i = 0; i < childCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (!pComponent)
            continue;

        if (symbolName.IsEmpty() || pComponent->GetName() == symbolName)
            if (pComponent->GetName() != _T("Texte1"))
                if (pComponent->SetValue(OD_PROP_FONT + OD_FONT_COLOR, color))
                    result = TRUE;

        // If has child components
        if (pComponent->GetChildCount() > 0)
            result = ChangeTextColor(pComponent, color, symbolName);
    }

    return result;
}
//---------------------------------------------------------------------------
COLORREF PSS_ODSymbolManipulator::GetTextColor(CODComponent* pSymbol, const CString& symbolName)
{
    if (!pSymbol)
        return RGB(0, 0, 0);

    DWORD     color;
    const int childCount = pSymbol->GetChildCount();

    // find the matching symbol in children
    for (int i = 0; i < childCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (!pComponent)
            continue;

        if (symbolName.IsEmpty() || pComponent->GetName() == symbolName)
            if (pComponent->GetValue(OD_PROP_FONT + OD_FONT_COLOR, color))
                return COLORREF(color);

        // if contains children components
        if (pComponent->GetChildCount() > 0)
            GetTextColor(pComponent, symbolName);
    }

    return RGB(0, 0, 0);
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::ChangeLabelLineColor(CODSymbolComponent* pSymbol, COLORREF color, const CString& labelName)
{
    if (!pSymbol)
        return FALSE;

    BOOL      result     = FALSE;
    const int labelCount = pSymbol->GetNumLabels();

    for (int i = 0; i < labelCount; ++i)
    {
        CODLabelComponent* pLabel = pSymbol->GetLabel(i);

        if (!pLabel)
            continue;

        if (labelName.IsEmpty() || pLabel->GetName() == labelName)
            result = pLabel->SetValue(OD_PROP_LINE + OD_LINE_COLOR, color);
    }

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::ChangeLineColorWidth(CODComponent*  pSymbol,
                                                   COLORREF       color,
                                                   int            width,
                                                   const CString& symbolName)
{
    if (!pSymbol)
        return FALSE;

    BOOL      result     = FALSE;
    const int childCount = pSymbol->GetChildCount();

    // find the matching symbol in children
    for (int i = 0; i < childCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (!pComponent)
            continue;

        if (symbolName.IsEmpty() || pComponent->GetName() == symbolName)
        {
            result = pComponent->SetValue(OD_PROP_LINE + OD_LINE_COLOR, color);

            if (!pComponent->SetValue(OD_PROP_LINE + OD_LINE_WIDTH, width))
                result = FALSE;
        }

        // if contains children components
        if (pComponent->GetChildCount() > 0)
            result = ChangeLineColorWidth(pComponent, color, width, symbolName);
    }

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::ChangeLabelLineColorWidth(CODSymbolComponent* pSymbol,
                                                        COLORREF            color,
                                                        int                 width,
                                                        const CString&      labelName)
{
    if (!pSymbol)
        return FALSE;

    BOOL      result     = FALSE;
    const int labelCount = pSymbol->GetNumLabels();

    for (int i = 0; i < labelCount; ++i)
    {
        CODLabelComponent* pLabel = pSymbol->GetLabel(i);

        if (!pLabel)
            continue;

        if (labelName.IsEmpty() || pLabel->GetName() == labelName)
        {
            result = pLabel->SetValue(OD_PROP_LINE + OD_LINE_COLOR, color);

            if (!pLabel->SetValue(OD_PROP_LINE + OD_LINE_WIDTH, width))
                result = FALSE;
        }
    }

    return result;
}
//---------------------------------------------------------------------------
void PSS_ODSymbolManipulator::ApplyFormatFromObject(CODComponent* pSymbol, CODComponent& object, bool font, bool fill, bool line)
{
    if (pSymbol)
    {
        CopyProperties(static_cast<CODEditProperties*>       (object.GetProperty(OD_PROP_EDIT)),              pSymbol);
        CopyProperties(static_cast<CODOrientationProperties*>(object.GetProperty(OD_PROP_ORIENTATION)),       pSymbol);
        CopyProperties(static_cast<CODFontProperties*>       (object.GetProperty(OD_PROP_FONT)),              pSymbol);
        CopyProperties(static_cast<CODFillProperties*>       (object.GetProperty(OD_PROP_FILL)),              pSymbol);
        CopyProperties(static_cast<CODLineProperties*>       (object.GetProperty(OD_PROP_LINE)),              pSymbol);
        CopyProperty  (static_cast<CODBoolProperty*>         (object.GetProperty(OD_PROP_WORDBREAK)),         pSymbol);
        CopyProperty  (static_cast<CODBoolProperty*>         (object.GetProperty(OD_PROP_MULTILINE)),         pSymbol);
        CopyProperty  (static_cast<CODIntProperty*>          (object.GetProperty(OD_PROP_HORZ_ALIGNMENT)),    pSymbol);
        CopyProperty  (static_cast<CODIntProperty*>          (object.GetProperty(OD_PROP_VERT_ALIGNMENT)),    pSymbol);
        CopyProperty  (static_cast<CODBoolProperty*>         (object.GetProperty(OD_PROP_TRANSPARENT)),       pSymbol);
        CopyProperty  (static_cast<CODDWordProperty*>        (object.GetProperty(OD_PROP_TRANSPARENT_COLOR)), pSymbol);
    }

    // find the matching symbol in children
    const int childCount = object.GetChildCount();

    for (int i = 0; i < childCount; ++i)
    {
        CODComponent* pComponent = object.GetChild(i);

        if (!pComponent)
            continue;

        ApplyFormatFromObject(pSymbol, *pComponent, font, fill, line);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_ODSymbolManipulator::CopySymbolStyle(CODComponent* pSrcSymbol, CODComponent* pDstSymbol)
{
    BOOL result = TRUE;

    if (pSrcSymbol && pDstSymbol)
    {
        CopyProperties(static_cast<CODEditProperties*>       (pSrcSymbol->GetProperty(OD_PROP_EDIT)),              pDstSymbol);
        CopyProperties(static_cast<CODOrientationProperties*>(pSrcSymbol->GetProperty(OD_PROP_ORIENTATION)),       pDstSymbol);
        CopyProperties(static_cast<CODFontProperties*>       (pSrcSymbol->GetProperty(OD_PROP_FONT)),              pDstSymbol);
        CopyProperties(static_cast<CODFillProperties*>       (pSrcSymbol->GetProperty(OD_PROP_FILL)),              pDstSymbol);
        CopyProperties(static_cast<CODLineProperties*>       (pSrcSymbol->GetProperty(OD_PROP_LINE)),              pDstSymbol);
        CopyProperty  (static_cast<CODBoolProperty*>         (pSrcSymbol->GetProperty(OD_PROP_WORDBREAK)),         pDstSymbol);
        CopyProperty  (static_cast<CODBoolProperty*>         (pSrcSymbol->GetProperty(OD_PROP_MULTILINE)),         pDstSymbol);
        CopyProperty  (static_cast<CODIntProperty*>          (pSrcSymbol->GetProperty(OD_PROP_HORZ_ALIGNMENT)),    pDstSymbol);
        CopyProperty  (static_cast<CODIntProperty*>          (pSrcSymbol->GetProperty(OD_PROP_VERT_ALIGNMENT)),    pDstSymbol);
        CopyProperty  (static_cast<CODBoolProperty*>         (pSrcSymbol->GetProperty(OD_PROP_TRANSPARENT)),       pDstSymbol);
        CopyProperty  (static_cast<CODDWordProperty*>        (pSrcSymbol->GetProperty(OD_PROP_TRANSPARENT_COLOR)), pDstSymbol);

        // find the matching symbol in children
        const int srcChildCount = pSrcSymbol->GetChildCount();
        const int dstChildCount = pDstSymbol->GetChildCount();

        if (srcChildCount == dstChildCount)
        {
            for (int i = 0; i < srcChildCount; ++i)
            {
                CODComponent* pSrcComponent = pSrcSymbol->GetChild(i);
                CODComponent* pDstComponent = pDstSymbol->GetChild(i);

                if (!pSrcComponent || !pDstComponent)
                    continue;

                result = CopySymbolStyle(pSrcComponent, pDstComponent);
            }
        }
        else
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTCOPYSTYLE, MB_OK);
            result = FALSE;
        }
    }

    return result;
}
//---------------------------------------------------------------------------
std::size_t PSS_ODSymbolManipulator::KeepOnlySymbolsISA(CODNodeArray& nodes, const CRuntimeClass* pClass)
{
    const int nodeCount = nodes.GetSize();

    for (int i = 0; i < nodeCount; ++i)
    {
        IODNode*            pINode = nodes.GetAt(i);
        CODSymbolComponent* pComp  = static_cast<CODSymbolComponent*>(pINode);

        if (!pComp)
            return 0;

        // remove the symbol from the array
        if (!pComp->IsKindOf(pClass))
        {
            nodes.RemoveAt(i);
            --i;
        }
    }

    return nodes.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_ODSymbolManipulator::KeepOnlyLinksISA(CODEdgeArray& edges, const CRuntimeClass* pClass)
{
    for (int i = 0; i < edges.GetSize(); ++i)
    {
        IODEdge*          pIEdge = edges.GetAt(i);
        CODLinkComponent* pComp  = static_cast<CODLinkComponent*>(pIEdge);

        if (!pComp)
            return 0;

        // remove the link from the array
        if (!pComp->IsKindOf(pClass))
        {
            edges.RemoveAt(i);
            --i;
        }
    }

    return edges.GetSize();
}
//---------------------------------------------------------------------------
bool PSS_ODSymbolManipulator::HasSymbolsISA(const CODNodeArray& nodes, const CRuntimeClass* pClass)
{
    const int nodeCount = nodes.GetSize();

    for (int i = 0; i < nodeCount; ++i)
    {
        IODNode*            pINode = nodes.GetAt(i);
        CODSymbolComponent* pComp  = static_cast<CODSymbolComponent*>(pINode);

        if (!pComp)
            continue;

        // same class type, return true
        if (pComp->IsKindOf(pClass))
            return true;
    }

    // not found
    return false;
}
//---------------------------------------------------------------------------
bool PSS_ODSymbolManipulator::HasLinksISA(const CODEdgeArray& edges, const CRuntimeClass* pClass)
{
    const int edgeCount = edges.GetSize();

    for (int i = 0; i < edgeCount; ++i)
    {
        IODEdge*          pIEdge = edges.GetAt(i);
        CODLinkComponent* pComp  = static_cast<CODLinkComponent*>(pIEdge);

        if (!pComp)
            continue;

        // same class type, return true
        if (pComp->IsKindOf(pClass))
            return true;
    }

    // not found
    return false;
}
//---------------------------------------------------------------------------
std::size_t PSS_ODSymbolManipulator::KeepFollowingSymbolsByPortName(const CString& portName, CODNodeArray& nodes)
{
    return nodes.GetSize();
}
//---------------------------------------------------------------------------
bool PSS_ODSymbolManipulator::IsSymbolFollowingByPortName(CODSymbolComponent* pSymbol, const CString& portName)
{
    return false;
}
//---------------------------------------------------------------------------
std::size_t PSS_ODSymbolManipulator::GetPortName(CODSymbolComponent* pSymbol, const CString& portName, CODPortSet& ports)
{
    PSS_Assert(pSymbol);

    CODPortSet setPorts;

    // get all ports
    pSymbol->GetAllPorts(setPorts);

    CODPortIterator it(&setPorts);

    for (CODPortComponent* pPortComp = it.GetFirst(); pPortComp; pPortComp = it.GetNext())
        if (pPortComp->GetName() == portName)
            ports.Add(pPortComp);

    return ports.GetSize();
}
//---------------------------------------------------------------------------
std::size_t PSS_ODSymbolManipulator::GetPortFollowingSymbols(CODPortComponent& port, CODComponentSet& set)
{
    // get the owner
    CODSymbolComponent* pComp = port.GetOwner();
    return set.GetSize();
}
//---------------------------------------------------------------------------
void PSS_ODSymbolManipulator::CopyProperties(CODEditProperties* pProps, CODComponent* pComp)
{
    if (!pProps || !pComp)
        return;

    // copy the properties and set them to the target edit
    std::unique_ptr<CODEditProperties> pNewEditProps(new CODEditProperties(*pProps));
    pComp->SetProperty(pNewEditProps.get());
    pNewEditProps.release();
}
//---------------------------------------------------------------------------
void PSS_ODSymbolManipulator::CopyProperties(CODOrientationProperties* pProps, CODComponent* pComp)
{
    if (!pProps || !pComp)
        return;

    // copy the properties and set them to the target edit
    std::unique_ptr<CODOrientationProperties> pNewOrientationProps(new CODOrientationProperties(*pProps));
    pComp->SetProperty(pNewOrientationProps.get());
    pNewOrientationProps.release();
}
//---------------------------------------------------------------------------
void PSS_ODSymbolManipulator::CopyProperties(CODFontProperties* pProps, CODComponent* pComp)
{
    if (!pProps || !pComp)
        return;

    // copy the properties and set them to the target edit
    std::unique_ptr<CODFontProperties> pNewFontProps(new CODFontProperties(*pProps));
    pComp->SetProperty(pNewFontProps.get());
    pNewFontProps.release();
}
//---------------------------------------------------------------------------
void PSS_ODSymbolManipulator::CopyProperties(CODFillProperties* pProps, CODComponent* pComp)
{
    if (!pProps || !pComp)
        return;

    // copy the properties and set them to the target edit
    std::unique_ptr<CODFillProperties> pNewFillProps(new CODFillProperties(*pProps));
    pComp->SetProperty(pNewFillProps.get());
    pNewFillProps.release();
}
//---------------------------------------------------------------------------
void PSS_ODSymbolManipulator::CopyProperties(CODLineProperties* pProps, CODComponent* pComp)
{
    if (!pProps || !pComp)
        return;

    // copy the properties and set them to the target edit
    std::unique_ptr<CODLineProperties> pNewLineProps(new CODLineProperties(*pProps));
    pComp->SetProperty(pNewLineProps.get());
    pNewLineProps.release();
}
//---------------------------------------------------------------------------
void PSS_ODSymbolManipulator::CopyProperty(CODBoolProperty* pProp, CODComponent* pComp)
{
    if (!pProp || !pComp)
        return;

    // copy the properties and set them to the target edit
    std::unique_ptr<CODBoolProperty> pNewBoolProp(new CODBoolProperty(*pProp));
    pComp->SetProperty(pNewBoolProp.get());
    pNewBoolProp.release();
}
//---------------------------------------------------------------------------
void PSS_ODSymbolManipulator::CopyProperty(CODIntProperty* pProp, CODComponent* pComp)
{
    if (!pProp || !pComp)
        return;

    // copy the properties and set them to the target edit
    std::unique_ptr<CODIntProperty> pNewIntProp(new CODIntProperty(*pProp));
    pComp->SetProperty(pNewIntProp.get());
    pNewIntProp.release();
}
//---------------------------------------------------------------------------
void PSS_ODSymbolManipulator::CopyProperty(CODDWordProperty* pProp, CODComponent* pComp)
{
    if (!pProp || !pComp)
        return;

    // copy the properties and set them to the target edit
    std::unique_ptr<CODDWordProperty> pNewDWordProp(new CODDWordProperty(*pProp));
    pComp->SetProperty(pNewDWordProp.get());
    pNewDWordProp.release();
}
//---------------------------------------------------------------------------
