/****************************************************************************
 * ==> PSS_BasicLabelComponent ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic label editor which implements filtering   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_BasicLabelComponent.h"

// processsoft
#include "PSS_CharFilters.h"

//---------------------------------------------------------------------------
// PSS_BasicLabelComponent::ILabelEdit
//---------------------------------------------------------------------------
PSS_BasicLabelComponent::ILabelEdit::ILabelEdit(PSS_BasicLabelComponent* pTextComp) :
	CODTextCompEdit(pTextComp)
{}
//---------------------------------------------------------------------------
PSS_BasicLabelComponent::ILabelEdit::~ILabelEdit()
{}
//---------------------------------------------------------------------------
BOOL PSS_BasicLabelComponent::ILabelEdit::PreTranslateMessage(MSG* pMsg)
{
    // dispatch received message
    switch (pMsg->message)
    {
        case WM_CHAR:
            // is char allowed?
            if (PSS_CharFilters::DoEscape(pMsg->wParam))
                // eat it
                return 1;

            break;
    }

    return CODTextCompEdit::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_BasicLabelComponent, CODLabelComponent, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_BasicLabelComponent
//---------------------------------------------------------------------------
PSS_BasicLabelComponent::PSS_BasicLabelComponent() :
    CODLabelComponent(),
    m_AllowEmptyText(true)
{}
//---------------------------------------------------------------------------
PSS_BasicLabelComponent::PSS_BasicLabelComponent(const OD_CONTROL_POINT ctlPoint) :
    CODLabelComponent(ctlPoint),
    m_AllowEmptyText(true)
{}
//---------------------------------------------------------------------------
PSS_BasicLabelComponent::~PSS_BasicLabelComponent()
{}
//---------------------------------------------------------------------------
BOOL PSS_BasicLabelComponent::BeginEdit(sfl::MvcViewport* pContainer)
{
    if (!pContainer)
        return FALSE;

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

    // enable scrolling if required
    if (!multiLine || (multiLine && !wordBreak))
        dwStyle |= ES_AUTOHSCROLL;

    CRect rcEdit(0, 0, 0, 0);

    ASSERT(m_pEdit == NULL);

    // override the default editor
    m_pEdit = new ILabelEdit(this);

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
    m_pEdit->SetSel((DWORD)MAKELONG( 0, -1 ));

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
bool PSS_BasicLabelComponent::GetAllowEmptyText() const
{
    return m_AllowEmptyText;
}
//---------------------------------------------------------------------------
void PSS_BasicLabelComponent::SetAllowEmptyText(bool value)
{
    m_AllowEmptyText = value;
}
//---------------------------------------------------------------------------
