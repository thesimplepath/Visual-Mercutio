/****************************************************************************
 * ==> PSS_BasicTextComponent ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic text editor which implements filtering    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_BasicTextComponent.h"

// processsoft
#include "PSS_CharFilters.h"

//---------------------------------------------------------------------------
// PSS_BasicTextComponent::ITextEdit
//---------------------------------------------------------------------------
PSS_BasicTextComponent::ITextEdit::ITextEdit(PSS_BasicTextComponent* pTextComp) :
    CODTextCompEdit(pTextComp),
    m_FilterChars(false)
{}
//---------------------------------------------------------------------------
PSS_BasicTextComponent::ITextEdit::~ITextEdit()
{}
//---------------------------------------------------------------------------
void PSS_BasicTextComponent::ITextEdit::EnableCharFilter(bool value)
{
    m_FilterChars = value;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicTextComponent::ITextEdit::PreTranslateMessage(MSG* pMsg)
{
    // dispatch received message
    switch (pMsg->message)
    {
        case WM_CHAR:
            // do filter chars and char is allowed?
            if (m_FilterChars && PSS_CharFilters::DoEscape(pMsg->wParam))
                // eat it
                return 1;

            break;
    }

    return CODTextCompEdit::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_BasicTextComponent, CODTextComponent, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_BasicTextComponent
//---------------------------------------------------------------------------
PSS_BasicTextComponent::PSS_BasicTextComponent() :
    CODTextComponent(),
    m_FilterChars(false)
{}
//---------------------------------------------------------------------------
PSS_BasicTextComponent::~PSS_BasicTextComponent()
{}
//---------------------------------------------------------------------------
void PSS_BasicTextComponent::EnableCharFilter(bool value)
{
    m_FilterChars = value;

    ITextEdit* pEdit = dynamic_cast<ITextEdit*>(m_pEdit);

    if (pEdit)
        pEdit->EnableCharFilter(value);
}
//---------------------------------------------------------------------------
BOOL PSS_BasicTextComponent::BeginEdit(sfl::MvcViewport* pContainer)
{
    BOOL multiLine;
    GetValue(OD_PROP_MULTILINE, multiLine);

    BOOL wordBreak;
    GetValue(OD_PROP_WORDBREAK, wordBreak);

    CODIntProperty* pHAlign = dynamic_cast<CODIntProperty*>(GetProperty(OD_PROP_HORZ_ALIGNMENT));
    DWORD           dwStyle = WS_CHILD | WS_CLIPSIBLINGS | ES_MULTILINE | ES_AUTOVSCROLL;

    // get alignment
    if (pHAlign)
    {
        const int hAlign = pHAlign->GetValue();

        // update the style
        if (hAlign == DT_LEFT)
            dwStyle |= ES_LEFT;
        else
        if (hAlign == DT_RIGHT)
            dwStyle |= ES_RIGHT;
        else
            dwStyle |= ES_CENTER;
    }
    else
        dwStyle |= ES_CENTER;

    if (!multiLine || (multiLine && !wordBreak))
        dwStyle |= ES_AUTOHSCROLL;

    CRect rcEdit(0, 0, 0, 0);

    ASSERT(m_pEdit == NULL);

    std::unique_ptr<ITextEdit> pBasicTextEdit(new ITextEdit(this));

    // override the default editor
    m_pEdit = pBasicTextEdit.get();

    ITextEdit* pEdit = pBasicTextEdit.release();

    // update the char filtering
    pEdit->EnableCharFilter(m_FilterChars);

    // initialize it
    if (!m_pEdit->Create(dwStyle, rcEdit, pContainer->GetWnd(), IDC_OD_TEXTEDIT))
    {
        delete m_pEdit;
        m_pEdit = NULL;
        return FALSE;
    }

    // set the text
    m_pEdit->FmtLines(TRUE);
    m_pEdit->SetWindowText(GetText());

    // get font container property
    CODProperty* pFontProp = GetProperty(OD_PROP_FONT);

    // found it?
    if (pFontProp)
    {
        // get font properties
        std::unique_ptr<CODFontProperties> pFontProps(dynamic_cast<CODFontProperties*>(pFontProp->Dup()));

        // found them?
        if (pFontProps.get())
        {
            // get scaling level from viewport
            const CSize szMag           = pContainer->GetMagnification();
            const int   scaledPointSize = (pFontProps->GetPointSize() * szMag.cy) / 100;

            // set scaling level
            pFontProps->SetPointSize(scaledPointSize);

            // create the font to use
            m_pEditFont = pFontProps->CreateFont();

            // set the font
            if (m_pEditFont)
                m_pEdit->SetFont(m_pEditFont);
        }
    }

    // select all content
    m_pEdit->SetSel((DWORD)MAKELONG(0, -1));

    // get the current angle
    m_nSaveAngle = GetAngle();

    // rotate the text component back to 0 degrees
    if (m_nSaveAngle != 0)
    {
        float fCenterX;
        float fCenterY;

        GetControlPoint(OD_CENTER, fCenterX, fCenterY);
        Rotate(-m_nSaveAngle, fCenterX, fCenterY);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
