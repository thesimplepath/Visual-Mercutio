// ZUODSymbolManipulator.cpp: implementation of the ZUODSymbolManipulator class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUODSymbolManipulator.h"

#include "ZBSymbolEdit.h"
#include "ZBSymbolLabel.h"
#include "zBaseSym\PSS_BasicSymbol.h"

// JMR-MODIF - Le 10 mai 2006 - Ajout de l'en-tête MsgBox.h
#include "zBaseLib\PSS_MsgBox.h"

// JMR-MODIF - Le 10 mai 2006 - Ajout de l'en-tête zModelRes.h
#include "zModelRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// ZUODSymbolManipulator
//---------------------------------------------------------------------------
ZUODSymbolManipulator::ZUODSymbolManipulator()
{}
//---------------------------------------------------------------------------
ZUODSymbolManipulator::~ZUODSymbolManipulator()
{}
//---------------------------------------------------------------------------
ZBSymbolEdit* ZUODSymbolManipulator::CreateEditText(CODComponent*  pSymbol,
                                                    const CString& AreaName,
                                                    const CString& EditName,
                                                    CODComponent*  pParent)
{
    CODComponent* pAreaComp = ZUODSymbolManipulator::FindSymbol(pSymbol, AreaName);

    if (!pAreaComp)
    {
        return NULL;
    }

    CODComponent* pComp = ZUODSymbolManipulator::FindSymbol(pSymbol, EditName);

    if (pComp != NULL)
    {
        return NULL;
    }

    return NULL;
}

ZBSymbolEdit* ZUODSymbolManipulator::CreateAndReplaceEditText(CODComponent*    pSymbol,
                                                              const CString    EditName,
                                                              CODComponent*    pParent        /*= NULL*/)
{
    CODComponent* pComp = ZUODSymbolManipulator::FindSymbol(pSymbol, EditName);

    if (!pComp || !ISA(pComp, CODTextComponent))
    {
        if (pSymbol && ISA(pSymbol, CODSymbolComponent))
        {
            pComp = ZUODSymbolManipulator::FindLabel(dynamic_cast<CODSymbolComponent*>(pSymbol), EditName);
        }
    }

    // Create the new symbol
    ZBSymbolEdit* pEdit = new ZBSymbolEdit;

    // Set its size
    pEdit->Create((pComp) ? pComp->GetBounds() : pSymbol->GetBounds(), NULL);

    if (pParent)
    {
        pParent->AppendChild(pEdit);
    }
    else
    {
        pSymbol->AppendChild(pEdit);
    }

    // Set its properties
    if (pComp)
    {
        if (pComp->GetProperty(OD_PROP_EDIT))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_EDIT));
        }

        if (pComp->GetProperty(OD_PROP_ORIENTATION))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_ORIENTATION));
        }

        if (pComp->GetProperty(OD_PROP_FONT))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_FONT));
        }

        if (pComp->GetProperty(OD_PROP_FILL))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_FILL));
        }

        if (pComp->GetProperty(OD_PROP_LINE))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_LINE));
        }

        if (pComp->GetProperty(OD_PROP_WORDBREAK))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_WORDBREAK));
        }

        if (pComp->GetProperty(OD_PROP_MULTILINE))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_MULTILINE));
        }

        if (pComp->GetProperty(OD_PROP_HORZ_ALIGNMENT))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_HORZ_ALIGNMENT));
        }

        if (pComp->GetProperty(OD_PROP_VERT_ALIGNMENT))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_VERT_ALIGNMENT));
        }

        if (pComp->GetProperty(OD_PROP_TRANSPARENT))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_TRANSPARENT));
        }

        if (pComp->GetProperty(OD_PROP_TRANSPARENT_COLOR))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_TRANSPARENT_COLOR));
        }

        pEdit->SetText(((CODTextComponent*)pComp)->GetText());
    }

    // Now, set the new symbol name.
    pEdit->SetName(EditName);

    // Now remove the previous edit.
    if (pComp)
    {
        ZUODSymbolManipulator::RemoveSymbol(pSymbol, pComp);
    }

    return pEdit;
}

ZBSymbolLabel* ZUODSymbolManipulator::CreateAndReplaceLabelText(CODComponent*    pSymbol,
                                                                const CString    EditName,
                                                                bool            NotifyParent,
                                                                CODComponent*    pParent            /*= NULL*/)
{
    CODComponent* pComp = ZUODSymbolManipulator::FindSymbol(pSymbol, EditName);

    if (!pComp || !ISA(pComp, CODTextComponent))
    {
        if (pSymbol && ISA(pSymbol, CODSymbolComponent))
        {
            pComp = ZUODSymbolManipulator::FindLabel(dynamic_cast<CODSymbolComponent*>(pSymbol), EditName);
        }
    }

    // Create the new symbol
    ZBSymbolLabel* pEdit = new ZBSymbolLabel(NotifyParent);

    // Set its size
    dynamic_cast<CODTextComponent*>(pEdit)->Create((pComp) ? pComp->GetBounds() : pSymbol->GetBounds(), NULL);

    if (pParent)
    {
        if (pParent && ISA(pParent, CODSymbolComponent))
        {
            dynamic_cast<CODSymbolComponent*>(pParent)->AddLabel(pEdit);
        }
        else
        {
            pParent->AppendChild(pEdit);
        }
    }
    else
    {
        if (pSymbol && ISA(pSymbol, CODSymbolComponent))
        {
            dynamic_cast<CODSymbolComponent*>(pSymbol)->AddLabel(pEdit);
        }
        else
        {
            pSymbol->AppendChild(pEdit);
        }
    }

    // Set its properties
    if (pComp)
    {
        if (pComp->GetProperty(OD_PROP_EDIT))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_EDIT));
        }

        if (pComp->GetProperty(OD_PROP_ORIENTATION))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_ORIENTATION));
        }

        if (pComp->GetProperty(OD_PROP_FONT))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_FONT));
        }

        if (pComp->GetProperty(OD_PROP_FILL))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_FILL));
        }

        if (pComp->GetProperty(OD_PROP_LINE))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_LINE));
        }

        if (pComp->GetProperty(OD_PROP_WORDBREAK))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_WORDBREAK));
        }

        if (pComp->GetProperty(OD_PROP_MULTILINE))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_MULTILINE));
        }

        if (pComp->GetProperty(OD_PROP_HORZ_ALIGNMENT))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_HORZ_ALIGNMENT));
        }

        if (pComp->GetProperty(OD_PROP_VERT_ALIGNMENT))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_VERT_ALIGNMENT));
        }

        if (pComp->GetProperty(OD_PROP_TRANSPARENT))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_TRANSPARENT));
        }

        if (pComp->GetProperty(OD_PROP_TRANSPARENT_COLOR))
        {
            pEdit->SetProperty(pComp->GetProperty(OD_PROP_TRANSPARENT_COLOR));
        }

        pEdit->SetText(((CODTextComponent*)pComp)->GetText());
    }
    // Now, set the new symbol name.
    pEdit->SetName(EditName);

    // Now remove the previous edit.
    if (pComp)
    {
        ZUODSymbolManipulator::RemoveSymbol(pSymbol, pComp);
    }

    return pEdit;
}

BOOL ZUODSymbolManipulator::IsSymbolVisible(CODComponent* pSymbol, const CString SymbolName)
{
    CODComponent* pComp = ZUODSymbolManipulator::FindSymbol(pSymbol, SymbolName);

    if (pComp)
    {
        return pComp->IsVisible();
    }

    // If does not exist, then not visible
    return FALSE;
}

BOOL ZUODSymbolManipulator::SetSymbolVisible(CODComponent* pSymbol, const CString SymbolName, BOOL bVisible)
{
    CODComponent* pComp = ZUODSymbolManipulator::FindSymbol(pSymbol, SymbolName);

    if (pComp)
    {
        pComp->SetVisible(bVisible);
        return TRUE;
    }

    // If does not exist, then return false as an error
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL ZUODSymbolManipulator::RemoveSymbol(CODComponent* pSymbol, const CString& SymbolName)
{
    CODComponent* pComp = ZUODSymbolManipulator::FindSymbol(pSymbol, SymbolName);

    if (pComp)
        return ZUODSymbolManipulator::RemoveSymbol(pSymbol, pComp);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL ZUODSymbolManipulator::RemoveSymbol(CODComponent* pSymbol, CODComponent* pComponent)
{
    // Try to find the right symbol
    CODComponentSet* pSet = pSymbol->GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pCompLeft = pSet->GetAt(i);

        // is it the right component
        if (pCompLeft == pComponent)
        {
            pSet->RemoveAt(i);
            return TRUE;
        }

        // try to locate the components in its childs
        if (pCompLeft->RemoveChild(pComponent))
            return TRUE;
    }

    // if not found, try to locate a label
    if (pSymbol && ISA(pSymbol, CODSymbolComponent))
    {
        CODLabelComponent* pLabel;

        for (int i = 0; i < dynamic_cast<CODSymbolComponent*>(pSymbol)->GetNumLabels(); ++i)
        {
            pLabel = dynamic_cast<CODSymbolComponent*>(pSymbol)->GetLabel(i);

            // try to locate the components in its childs
            if (pLabel == pComponent)
            {
                dynamic_cast<CODSymbolComponent*>(pSymbol)->RemoveLabel(pLabel);
                return TRUE;
            }
        }
    }

    return FALSE;
}
//---------------------------------------------------------------------------
CODComponent* ZUODSymbolManipulator::FindLabel(CODSymbolComponent* pSymbol, const CString SymbolName)
{
    CODLabelComponent* pLabel;

    for (int i = 0; i < pSymbol->GetNumLabels(); ++i)
    {
        pLabel = pSymbol->GetLabel(i);

        if (pLabel->GetName() == SymbolName)
            return pLabel;
    }

    return NULL;
}
//---------------------------------------------------------------------------
CODComponent* ZUODSymbolManipulator::FindSymbol(CODComponent* pSymbol, const CString symbolName)
{
    // try to find the right label
    CODComponentSet* pSet = pSymbol->GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComponent = pSet->GetAt(i);

        // is it the right component?
        if (pComponent->GetName() == symbolName)
            return pComponent;

        // try to locate the symbol in the childs of components
        CODComponent* pInChildComponent = ZUODSymbolManipulator::FindSymbolInChild(pComponent, symbolName);

        if (pInChildComponent)
            return pInChildComponent;
    }

    // if not found, try to locate the symbol in labels
    if (ISA(pSymbol, CODSymbolComponent))
    {
        CODLabelComponent* pLabel;

        for (int i = 0; i < dynamic_cast<CODSymbolComponent*>(pSymbol)->GetNumLabels(); ++i)
        {
            pLabel = dynamic_cast<CODSymbolComponent*>(pSymbol)->GetLabel(i);

            if (pLabel->GetName() == symbolName)
                return pLabel;

            // ****************************************************************************************
            // JMR-MODIF - Le 17 mars 2006 - Permets la compatibilité des anciens modèles de documents.
            // Teste et convertit les composants de type Label utilisant un faux nom de composant.
            CString componentType = _T("");

            pLabel->GetValue(OD_PROP_TYPE, componentType);

            if (symbolName == M_SymbolNameComponentControlLabel && componentType == _T("Label"))
            {
                pLabel->SetName(M_SymbolNameComponentControlLabel);
                return pLabel;
            }
            // ****************************************************************************************

            CODComponent* pInChildComponent = ZUODSymbolManipulator::FindSymbolInChild(pLabel, symbolName);

            if (pInChildComponent)
                return pInChildComponent;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
// Create the symbol name label
CODComponent* ZUODSymbolManipulator::FindSymbolInChild(CODComponent* pSymbol, const CString SymbolName)
{
    // try to find the right symbol in childs
    const int childCount = pSymbol->GetChildCount();

    for (int i = 0; i < childCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (pComponent->GetName() == SymbolName)
            return pComponent;
    }

    return NULL;
}
//---------------------------------------------------------------------------
void ZUODSymbolManipulator::MatchSymbolAreaName(CODComponent* pSymbol, CODComponent* pSrcSymbol)
{
    // assign the component name
    CODComponentSet* pSet = pSymbol->GetComponents();
    CODComponentSet* pSrcSet = pSrcSymbol->GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComponent = pSet->GetAt(i);
        CODComponent* pSrcComponent = pSrcSet->GetAt(i);

        if (!pComponent || !pSrcComponent)
            continue;

        // if we do have specific name from the source
        if (pSrcComponent->GetName().Left(3) == _T("ZC_"))
            // assign the source name to the destination component
            pComponent->SetName(pSrcComponent->GetName());

        // match symbol name also in child of components
        ZUODSymbolManipulator::MatchSymbolAreaNameInChild(pComponent, pSrcComponent);
    }

    // match for labels
    if (ISA(pSymbol, CODSymbolComponent))
        for (int i = 0; i < dynamic_cast<CODSymbolComponent*>(pSymbol)->GetNumLabels(); ++i)
        {
            CODLabelComponent* pLabel = dynamic_cast<CODSymbolComponent*>(pSymbol)->GetLabel(i);
            CODLabelComponent* pSrcLabel = dynamic_cast<CODSymbolComponent*>(pSrcSymbol)->GetLabel(i);

            if (!pLabel || !pSrcLabel)
                continue;

            // if we do have specific name from the source
            if (pSrcLabel->GetName().Left(3) == _T("ZC_"))
                // assign the source name to the destination component
                pLabel->SetName(pSrcLabel->GetName());

            ZUODSymbolManipulator::MatchSymbolAreaNameInChild(pLabel, pSrcLabel);
        }
}
//---------------------------------------------------------------------------
// Create the symbol name label
void ZUODSymbolManipulator::MatchSymbolAreaNameInChild(CODComponent* pSymbol, CODComponent* pSrcSymbol)
{
    // Match symbol names in childs
    int ChildCount = pSymbol->GetChildCount();

    for (int i = 0; i < ChildCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);
        CODComponent* pSrcComponent = pSrcSymbol->GetChild(i);

        if (!pComponent || !pSrcComponent)
        {
            continue;
        }

        if (pSrcComponent->GetName().Left(3) == _T("ZC_"))
        {
            // Assign the source name to the destination component
            pComponent->SetName(pSrcComponent->GetName());
        }
    }
}

// JMR-MODIF - Le 22 juillet 2007 - Cette fonction permet de mettre ou enlever la propriété italique d'un label de symbole.
BOOL ZUODSymbolManipulator::SetLabelItalic(CODSymbolComponent*    pSymbol,
                                           BOOL                DoSetTextItalic,
                                           const CString        LabelName /*= ""*/)
{
    BOOL retValue = FALSE;
    int LabelCount = pSymbol->GetNumLabels();

    for (int i = 0; i < LabelCount; ++i)
    {
        CODLabelComponent* pLabel = pSymbol->GetLabel(i);

        if (!pLabel)
        {
            continue;
        }

        if (LabelName.IsEmpty() || pLabel->GetName() == LabelName)
        {
            retValue = pLabel->SetValue(OD_PROP_FONT + OD_FONT_ITALIC, DoSetTextItalic);
        }
    }

    return retValue;
}

// JMR-MODIF - Le 22 juillet 2007 - Cette fonction permet de changer la couleur du label d'un symbole.
BOOL ZUODSymbolManipulator::ChangeLabelTextColor(CODSymbolComponent*    pSymbol,
                                                 COLORREF                col,
                                                 const CString            LabelName /*= ""*/)
{
    BOOL retValue = FALSE;
    int LabelCount = pSymbol->GetNumLabels();

    for (int i = 0; i < LabelCount; ++i)
    {
        CODLabelComponent* pLabel = pSymbol->GetLabel(i);

        if (!pLabel)
        {
            continue;
        }

        if (LabelName.IsEmpty() || pLabel->GetName() == LabelName)
        {
            retValue = pLabel->SetValue(OD_PROP_FONT + OD_FONT_COLOR, col);
        }
    }

    return retValue;
}

// JMR-MODIF - Le 22 juillet 2007 - Cette fonction permet de mettre ou enlever la propriété italique d'un texte de symbole.
BOOL ZUODSymbolManipulator::SetTextItalic(CODComponent*    pSymbol,
                                          BOOL                DoSetTextItalic,
                                          const CString    SymbolName        /*= ""*/)
{
    BOOL retValue = FALSE;

    // Try to find the right symbol in childs
    int ChildCount = pSymbol->GetChildCount();

    for (int i = 0; i < ChildCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (!pComponent)
        {
            continue;
        }

        if (SymbolName.IsEmpty() || pComponent->GetName() == SymbolName)
        {
            if (pComponent->GetName() != _T("Texte1"))
            {
                if (pComponent->SetValue(OD_PROP_FONT + OD_FONT_ITALIC, DoSetTextItalic))
                {
                    // Sets the right value
                    retValue = TRUE;
                }
            }
        }

        // If has child components
        if (pComponent->GetChildCount() > 0)
        {
            retValue = ZUODSymbolManipulator::SetTextItalic(pComponent, DoSetTextItalic, SymbolName);
        }
    }

    return retValue;
}

// JMR-MODIF - Le 22 juillet 2007 - Cette fonction permet de changer la couleur du texte d'un symbole.
BOOL ZUODSymbolManipulator::ChangeTextColor(CODComponent*    pSymbol,
                                            COLORREF        col,
                                            const CString    SymbolName            /*= _T( "" )*/)
{
    BOOL retValue = FALSE;

    // Try to find the right symbol in childs
    int ChildCount = pSymbol->GetChildCount();

    for (int i = 0; i < ChildCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (!pComponent)
        {
            continue;
        }

        if (SymbolName.IsEmpty() || pComponent->GetName() == SymbolName)
        {
            if (pComponent->GetName() != _T("Texte1"))
            {
                if (pComponent->SetValue(OD_PROP_FONT + OD_FONT_COLOR, col))
                {
                    // Sets the right value
                    retValue = TRUE;
                }
            }
        }

        // If has child components
        if (pComponent->GetChildCount() > 0)
        {
            retValue = ZUODSymbolManipulator::ChangeTextColor(pComponent, col, SymbolName);
        }
    }

    return retValue;
}

// JMR-MODIF - Le 22 juillet 2007 - Cette fonction permet d'obtenir la couleur du texte d'un symbole.
COLORREF ZUODSymbolManipulator::GetTextColor(CODComponent*    pSymbol,
                                             const CString    SymbolName    /*= ""*/)
{
    DWORD Color;

    // Try to find the right symbol in childs
    int ChildCount = pSymbol->GetChildCount();

    for (int i = 0; i < ChildCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (!pComponent)
        {
            continue;
        }

        if (SymbolName.IsEmpty() || pComponent->GetName() == SymbolName)
        {
            if (pComponent->GetValue(OD_PROP_FONT + OD_FONT_COLOR, Color))
            {
                return (COLORREF)Color;
            }
        }

        // If has child components
        if (pComponent->GetChildCount() > 0)
        {
            ZUODSymbolManipulator::GetTextColor(pComponent, SymbolName);
        }
    }

    return RGB(0, 0, 0);
}

BOOL ZUODSymbolManipulator::ChangeComponentLineColor(CODComponent* pSymbol, COLORREF col)
{
    return pSymbol->SetValue(OD_PROP_LINE + OD_LINE_COLOR, col);
}

BOOL ZUODSymbolManipulator::ChangeComponentLineWidth(CODComponent* pSymbol, int width)
{
    return pSymbol->SetValue(OD_PROP_LINE + OD_LINE_WIDTH, width);
}

BOOL ZUODSymbolManipulator::ChangeComponentLineColorWidth(CODComponent* pSymbol, COLORREF col, int width)
{
    BOOL bSuccess = pSymbol->SetValue(OD_PROP_LINE + OD_LINE_COLOR, col);

    if (!pSymbol->SetValue(OD_PROP_LINE + OD_LINE_WIDTH, width))
    {
        bSuccess = FALSE;
    }

    return bSuccess;
}

// Cette fonction permet de changer la couleur de toutes les lignes d'un symbole.
BOOL ZUODSymbolManipulator::ChangeLineColor(CODComponent*    pSymbol,
                                            COLORREF        col,
                                            const CString    SymbolName    /*= ""*/)
{
    BOOL retValue = FALSE;

    // Try to find the right symbol in childs
    int ChildCount = pSymbol->GetChildCount();

    for (int i = 0; i < ChildCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (!pComponent)
        {
            continue;
        }

        if (SymbolName.IsEmpty() || pComponent->GetName() == SymbolName)
        {
            if (pComponent->SetValue(OD_PROP_LINE + OD_LINE_COLOR, col))
            {
                // Sets the right value
                retValue = TRUE;
            }
        }

        // If has child components
        if (pComponent->GetChildCount() > 0)
        {
            retValue = ZUODSymbolManipulator::ChangeLineColor(pComponent, col, SymbolName);
        }
    }

    return retValue;
}

// Cette fonction permet de changer la largeur de toutes les lignes d'un symbole.
BOOL ZUODSymbolManipulator::ChangeLineWidth(CODComponent* pSymbol, int width, const CString SymbolName /*= ""*/)
{
    BOOL retValue = FALSE;

    // Try to find the right symbol in childs
    int ChildCount = pSymbol->GetChildCount();

    for (int i = 0; i < ChildCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (!pComponent)
        {
            continue;
        }

        if (SymbolName.IsEmpty() || pComponent->GetName() == SymbolName)
        {
            if (pComponent->SetValue(OD_PROP_LINE + OD_LINE_WIDTH, width))
            {
                // Sets the right value
                retValue = TRUE;
            }
        }

        // If has child components
        if (pComponent->GetChildCount() > 0)
        {
            retValue = ZUODSymbolManipulator::ChangeLineWidth(pComponent, width, SymbolName);
        }
    }

    return retValue;
}

// Cette fonction permet de changer la couleur et la largeur de toutes les lignes d'un symbole.
BOOL ZUODSymbolManipulator::ChangeLineColorWidth(CODComponent*    pSymbol,
                                                 COLORREF        col,
                                                 int            width,
                                                 const CString    SymbolName /*= ""*/)
{
    BOOL retValue = FALSE;

    // Try to find the right symbol in childs
    int ChildCount = pSymbol->GetChildCount();

    for (int i = 0; i < ChildCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (!pComponent)
        {
            continue;
        }

        if (SymbolName.IsEmpty() || pComponent->GetName() == SymbolName)
        {
            retValue = pComponent->SetValue(OD_PROP_LINE + OD_LINE_COLOR, col);

            if (!pComponent->SetValue(OD_PROP_LINE + OD_LINE_WIDTH, width))
            {
                retValue = FALSE;
            }
        }

        // If has child components
        if (pComponent->GetChildCount() > 0)
        {
            retValue = ZUODSymbolManipulator::ChangeLineColorWidth(pComponent, col, width, SymbolName);
        }
    }

    return retValue;
}

// JMR-MODIF - Le 24 juin 2005 - Ajout de la fonction ChangeLineStyle, afin de permettre la manipulation de
// l'attribut du style de trait de la ligne.
// Cette fonction permet de changer le style de toutes les lignes d'un symbole.
BOOL ZUODSymbolManipulator::ChangeLineStyle(CODComponent* pSymbol, int style, const CString SymbolName /*= ""*/)
{
    BOOL retValue = FALSE;

    // Try to find the right symbol in childs
    int ChildCount = pSymbol->GetChildCount();

    for (int i = 0; i < ChildCount; ++i)
    {
        CODComponent* pComponent = pSymbol->GetChild(i);

        if (!pComponent)
        {
            continue;
        }

        if (SymbolName.IsEmpty() || pComponent->GetName() == SymbolName)
        {
            if (pComponent->SetValue(OD_PROP_LINE + OD_LINE_STYLE, style))
            {
                // Sets the right value
                retValue = TRUE;
            }
        }

        // If has child components
        if (pComponent->GetChildCount() > 0)
        {
            retValue = ZUODSymbolManipulator::ChangeLineStyle(pComponent, style, SymbolName);
        }
    }

    return retValue;
}

BOOL ZUODSymbolManipulator::ChangeLabelLineColor(CODSymbolComponent*    pSymbol,
                                                 COLORREF                col,
                                                 const CString            LabelName /*= ""*/)
{
    BOOL retValue = FALSE;
    int LabelCount = pSymbol->GetNumLabels();

    for (int i = 0; i < LabelCount; ++i)
    {
        CODLabelComponent* pLabel = pSymbol->GetLabel(i);

        if (!pLabel)
        {
            continue;
        }

        if (LabelName.IsEmpty() || pLabel->GetName() == LabelName)
        {
            retValue = pLabel->SetValue(OD_PROP_LINE + OD_LINE_COLOR, col);
        }
    }

    return retValue;
}

BOOL ZUODSymbolManipulator::ChangeLabelLineWidth(CODSymbolComponent*    pSymbol,
                                                 int                    width,
                                                 const CString            LabelName /*= ""*/)
{
    BOOL retValue = FALSE;
    int LabelCount = pSymbol->GetNumLabels();

    for (int i = 0; i < LabelCount; ++i)
    {
        CODLabelComponent* pLabel = pSymbol->GetLabel(i);

        if (!pLabel)
        {
            continue;
        }

        if (LabelName.IsEmpty() || pLabel->GetName() == LabelName)
        {
            retValue = pLabel->SetValue(OD_PROP_LINE + OD_LINE_WIDTH, width);
        }
    }

    return retValue;
}

BOOL ZUODSymbolManipulator::ChangeLabelLineColorWidth(CODSymbolComponent*    pSymbol,
                                                      COLORREF                col,
                                                      int                    width,
                                                      const CString        LabelName /*= ""*/)
{
    BOOL retValue = FALSE;
    int LabelCount = pSymbol->GetNumLabels();

    for (int i = 0; i < LabelCount; ++i)
    {
        CODLabelComponent* pLabel = pSymbol->GetLabel(i);

        if (!pLabel)
        {
            continue;
        }

        if (LabelName.IsEmpty() || pLabel->GetName() == LabelName)
        {
            retValue = pLabel->SetValue(OD_PROP_LINE + OD_LINE_COLOR, col);

            if (!pLabel->SetValue(OD_PROP_LINE + OD_LINE_WIDTH, width))
            {
                // Sets the right value
                retValue = FALSE;
            }
        }
    }
    return retValue;
}

void ZUODSymbolManipulator::ApplyFormatFromObject(CODComponent*    pSymbol,
                                                  CODComponent&    Object,
                                                  bool                Font    /*= true*/,
                                                  bool                Fill    /*= true*/,
                                                  bool                Line    /*= true*/)
{
    if (pSymbol)
    {
        if (Object.GetProperty(OD_PROP_EDIT))
        {
            pSymbol->SetProperty(Object.GetProperty(OD_PROP_EDIT));
        }

        if (Object.GetProperty(OD_PROP_ORIENTATION))
        {
            pSymbol->SetProperty(Object.GetProperty(OD_PROP_ORIENTATION));
        }

        if (Object.GetProperty(OD_PROP_FONT))
        {
            pSymbol->SetProperty(Object.GetProperty(OD_PROP_FONT));
        }

        if (Object.GetProperty(OD_PROP_FILL))
        {
            pSymbol->SetProperty(Object.GetProperty(OD_PROP_FILL));
        }

        if (Object.GetProperty(OD_PROP_LINE))
        {
            pSymbol->SetProperty(Object.GetProperty(OD_PROP_LINE));
        }

        if (Object.GetProperty(OD_PROP_WORDBREAK))
        {
            pSymbol->SetProperty(Object.GetProperty(OD_PROP_WORDBREAK));
        }

        if (Object.GetProperty(OD_PROP_MULTILINE))
        {
            pSymbol->SetProperty(Object.GetProperty(OD_PROP_MULTILINE));
        }

        if (Object.GetProperty(OD_PROP_HORZ_ALIGNMENT))
        {
            pSymbol->SetProperty(Object.GetProperty(OD_PROP_HORZ_ALIGNMENT));
        }

        if (Object.GetProperty(OD_PROP_VERT_ALIGNMENT))
        {
            pSymbol->SetProperty(Object.GetProperty(OD_PROP_VERT_ALIGNMENT));
        }

        if (Object.GetProperty(OD_PROP_TRANSPARENT))
        {
            pSymbol->SetProperty(Object.GetProperty(OD_PROP_TRANSPARENT));
        }

        if (Object.GetProperty(OD_PROP_TRANSPARENT_COLOR))
        {
            pSymbol->SetProperty(Object.GetProperty(OD_PROP_TRANSPARENT_COLOR));
        }
    }

    // Try to find the right symbol in childs
    int ChildCount = Object.GetChildCount();

    for (int i = 0; i < ChildCount; ++i)
    {
        CODComponent* pComponent = Object.GetChild(i);

        if (!pComponent)
        {
            continue;
        }

        ZUODSymbolManipulator::ApplyFormatFromObject(pSymbol, *pComponent, Font, Fill, Line);
    }
}

// JMR-MODIF - Le 4 mai 2006 - Cette fonction permet de copier le style d'un objet source vers un autre objet.
BOOL ZUODSymbolManipulator::CopySymbolStyle(CODComponent* pSrcSymbol, CODComponent* pTrgSymbol)
{
    BOOL b_Result = TRUE;

    if (pSrcSymbol != NULL && pTrgSymbol != NULL)
    {
        if (pSrcSymbol->GetProperty(OD_PROP_EDIT))
        {
            pTrgSymbol->SetProperty(pSrcSymbol->GetProperty(OD_PROP_EDIT));
        }

        if (pSrcSymbol->GetProperty(OD_PROP_ORIENTATION))
        {
            pTrgSymbol->SetProperty(pSrcSymbol->GetProperty(OD_PROP_ORIENTATION));
        }

        if (pSrcSymbol->GetProperty(OD_PROP_FONT))
        {
            pTrgSymbol->SetProperty(pSrcSymbol->GetProperty(OD_PROP_FONT));
        }

        if (pSrcSymbol->GetProperty(OD_PROP_FILL))
        {
            pTrgSymbol->SetProperty(pSrcSymbol->GetProperty(OD_PROP_FILL));
        }

        if (pSrcSymbol->GetProperty(OD_PROP_LINE))
        {
            pTrgSymbol->SetProperty(pSrcSymbol->GetProperty(OD_PROP_LINE));
        }

        if (pSrcSymbol->GetProperty(OD_PROP_WORDBREAK))
        {
            pTrgSymbol->SetProperty(pSrcSymbol->GetProperty(OD_PROP_WORDBREAK));
        }

        if (pSrcSymbol->GetProperty(OD_PROP_MULTILINE))
        {
            pTrgSymbol->SetProperty(pSrcSymbol->GetProperty(OD_PROP_MULTILINE));
        }

        if (pSrcSymbol->GetProperty(OD_PROP_HORZ_ALIGNMENT))
        {
            pTrgSymbol->SetProperty(pSrcSymbol->GetProperty(OD_PROP_HORZ_ALIGNMENT));
        }

        if (pSrcSymbol->GetProperty(OD_PROP_VERT_ALIGNMENT))
        {
            pTrgSymbol->SetProperty(pSrcSymbol->GetProperty(OD_PROP_VERT_ALIGNMENT));
        }

        if (pSrcSymbol->GetProperty(OD_PROP_TRANSPARENT))
        {
            pTrgSymbol->SetProperty(pSrcSymbol->GetProperty(OD_PROP_TRANSPARENT));
        }

        if (pSrcSymbol->GetProperty(OD_PROP_TRANSPARENT_COLOR))
        {
            pTrgSymbol->SetProperty(pSrcSymbol->GetProperty(OD_PROP_TRANSPARENT_COLOR));
        }

        // Try to find the right symbol in childs
        int SrcChildCount = pSrcSymbol->GetChildCount();
        int TrgChildCount = pTrgSymbol->GetChildCount();

        if (SrcChildCount == TrgChildCount)
        {
            for (int i = 0; i < SrcChildCount; ++i)
            {
                CODComponent* pSrcComponent = pSrcSymbol->GetChild(i);
                CODComponent* pTrgComponent = pTrgSymbol->GetChild(i);

                if (pSrcComponent == NULL || pTrgComponent == NULL)
                {
                    continue;
                }

                b_Result = ZUODSymbolManipulator::CopySymbolStyle(pSrcComponent, pTrgComponent);
            }
        }
        else
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTCOPYSTYLE, MB_OK);
            b_Result = FALSE;
        }
    }

    return b_Result;
}

// Find ports having the name specified, copy their pointer to the set.
size_t ZUODSymbolManipulator::GetPortName(CODSymbolComponent*    pSymbol,
                                          const CString        PortName,
                                          CODPortSet&            Ports)
{
    ASSERT(pSymbol != NULL);

    // Retreive all ports
    CODPortSet setPorts;
    pSymbol->GetAllPorts(setPorts);

    CODPortIterator i(&setPorts);

    for (CODPortComponent* pPortComp = i.GetFirst(); pPortComp != NULL; pPortComp = i.GetNext())
    {
        if (pPortComp->GetName() == PortName)
        {
            Ports.Add(pPortComp);
        }
    }

    return Ports.GetSize();
}

size_t ZUODSymbolManipulator::KeepOnlySymbolsISA(CODNodeArray& Nodes, const CRuntimeClass* pClass)
{
    for (int nNodeIdx = 0; nNodeIdx < Nodes.GetSize(); ++nNodeIdx)
    {
        IODNode* pINode = Nodes.GetAt(nNodeIdx);
        CODSymbolComponent* pComp = static_cast<CODSymbolComponent*>(pINode);

        if (!pComp)
        {
            // Log problem
            return 0;
        }

        if (!pComp->IsKindOf(pClass))
        {
            // Remove the symbol from the array
            Nodes.RemoveAt(nNodeIdx);
            --nNodeIdx;
        }
    }

    return Nodes.GetSize();
}

size_t ZUODSymbolManipulator::KeepOnlyLinksISA(CODEdgeArray& Edges, const CRuntimeClass* pClass)
{
    for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
    {
        IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
        CODLinkComponent* pComp = static_cast<CODLinkComponent*>(pIEdge);

        if (!pComp)
        {
            // Log problem
            return 0;
        }

        if (!pComp->IsKindOf(pClass))
        {
            // Remove the link from the array
            Edges.RemoveAt(nEdgeIdx);
            --nEdgeIdx;
        }
    }

    return Edges.GetSize();
}

bool ZUODSymbolManipulator::HasSymbolsISA(CODNodeArray& Nodes, const CRuntimeClass* pClass)
{
    for (int nNodeIdx = 0; nNodeIdx < Nodes.GetSize(); ++nNodeIdx)
    {
        IODNode* pINode = Nodes.GetAt(nNodeIdx);
        CODSymbolComponent* pComp = static_cast<CODSymbolComponent*>(pINode);

        if (!pComp)
        {
            continue;
        }

        // Same class type, return true
        if (pComp->IsKindOf(pClass))
        {
            return true;
        }
    }

    // Not found
    return false;
}

bool ZUODSymbolManipulator::HasLinksISA(CODEdgeArray& Edges, const CRuntimeClass* pClass)
{
    for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
    {
        IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
        CODLinkComponent* pComp = static_cast<CODLinkComponent*>(pIEdge);

        if (!pComp)
        {
            continue;
        }

        // Same class type, return true
        if (pComp->IsKindOf(pClass))
        {
            return true;
        }
    }

    // not found
    return false;
}

// Get all the following symbols attached to the port specified as parameter. Copy the pointer to the set.
size_t ZUODSymbolManipulator::GetPortFollowingSymbols(CODPortComponent& Port, CODComponentSet& Set)
{
    // Retreive the owner
    CODSymbolComponent* pComp = Port.GetOwner();

    // And then 
    return Set.GetSize();
}

size_t ZUODSymbolManipulator::KeepFollowingSymbolsByPortName(const CString PortName, CODNodeArray& Nodes)
{
    return Nodes.GetSize();
}

bool ZUODSymbolManipulator::IsSymbolFollowingByPortName(CODSymbolComponent* pSymbol, const CString PortName)
{
    return false;
}
