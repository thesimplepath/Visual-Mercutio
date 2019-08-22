/****************************************************************************
 * ==> PSS_WizardDialog ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic Wizard dialog box                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "ZWizard.h"

 // processsoft
#include "PSS_DrawFunctions.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const int g_WhiteBoxHeight = 60;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_WizardDialog, ZIDialog)
    //{{AFX_MSG_MAP(PSS_WizardDialog)
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_WizardDialog
//---------------------------------------------------------------------------
PSS_WizardDialog::PSS_WizardDialog(UINT           id,
                                   UINT           bitmapID,
                                   UINT           iconID,
                                   const CString& titleWindow,
                                   const CString& titleWizard,
                                   const CString& textWizard,
                                   BOOL           autoCenter,
                                   BOOL           standalone,
                                   CWnd*          pParent) :
    ZIDialog(id, autoCenter, pParent),
    m_hIcon(NULL),
    m_TitleWindow(titleWindow),
    m_TitleWizard(titleWizard),
    m_TextWizard(textWizard),
    m_ID(id),
    m_BitmapID(bitmapID),
    m_IconID(iconID),
    m_Standalone(standalone)
{
    CreateFont();
}
//---------------------------------------------------------------------------
PSS_WizardDialog::PSS_WizardDialog(UINT  id,
                                   UINT  bitmapID,
                                   UINT  iconID,
                                   UINT  titleWindowID,
                                   UINT  titleWizardID,
                                   UINT  textWizardID,
                                   BOOL  autoCenter,
                                   BOOL  standalone,
                                   CWnd* pParent) :
    ZIDialog(id, autoCenter, pParent),
    m_hInst(NULL),
    m_hIcon(NULL),
    m_ID(id),
    m_BitmapID(bitmapID),
    m_IconID(iconID),
    m_Standalone(standalone)
{
    m_TitleWindow.LoadString(titleWindowID),
    m_TitleWizard.LoadString(titleWizardID),
    m_TextWizard.LoadString (textWizardID),

    CreateFont();
}
//---------------------------------------------------------------------------
PSS_WizardDialog::PSS_WizardDialog(UINT           id,
                                   UINT           bitmapID,
                                   UINT           iconID,
                                   const CString& titleWindow,
                                   const CString& titleWizard,
                                   const CString& textWizard,
                                   COLORREF       backCol,
                                   COLORREF       staticCol,
                                   COLORREF       editCol,
                                   BOOL           autoCenter,
                                   BOOL           standalone,
                                   CWnd*          pParent) :
    ZIDialog(id, autoCenter, backCol, staticCol, editCol, pParent),
    m_hIcon(NULL),
    m_TitleWindow(titleWindow),
    m_TitleWizard(titleWizard),
    m_TextWizard(textWizard),
    m_ID(id),
    m_BitmapID(bitmapID),
    m_IconID(iconID),
    m_Standalone(standalone)
{
    CreateFont();
}
//---------------------------------------------------------------------------
PSS_WizardDialog::PSS_WizardDialog(UINT     id,
                                   UINT     bitmapID,
                                   UINT     iconID,
                                   UINT     titleWindowID,
                                   UINT     titleWizardID,
                                   UINT     textWizardID,
                                   COLORREF backCol,
                                   COLORREF staticCol,
                                   COLORREF editCol,
                                   BOOL     autoCenter,
                                   BOOL     standalone,
                                   CWnd*    pParent) :
    ZIDialog(id, autoCenter, backCol, staticCol, editCol, pParent),
    m_hIcon(NULL),
    m_ID(id),
    m_BitmapID(bitmapID),
    m_IconID(iconID),
    m_Standalone(standalone)
{
    m_TitleWindow.LoadString(titleWindowID),
    m_TitleWizard.LoadString(titleWizardID),
    m_TextWizard.LoadString (textWizardID),

    CreateFont();
}
//---------------------------------------------------------------------------
BOOL PSS_WizardDialog::Create(UINT           id,
                              UINT           bitmapID,
                              UINT           iconID,
                              const CString& titleWindow,
                              const CString& titleWizard,
                              const CString& textWizard,
                              BOOL           autoCenter,
                              BOOL           standalone,
                              CWnd*          pParent)
{
    m_nID = nID;
    m_nBitmapID = nBitmapID;
    m_nIconID = nIconID;
    m_bStandAlone = bStandAlone;
    m_sTitleWindow = sTitleWindow;
    m_sTitleWizard = sTitleWizard;
    m_sTextWizard = sTextWizard;

    ZIDialog::Create(nID, bAutoCenter, pParent);
    return TRUE;
}

BOOL PSS_WizardDialog::Create(UINT    nID,
                            UINT    nBitmapID,
                            UINT    nIconID,
                            UINT    nTitleWindowID,
                            UINT    nTitleWizardID,
                            UINT    nTextWizardID,
                            BOOL    bAutoCenter,
                            BOOL    bStandAlone,
                            CWnd*    pParent)
{
    m_nID = nID;
    m_nBitmapID = nBitmapID;
    m_nIconID = nIconID;
    m_bStandAlone = bStandAlone;

    m_sTitleWindow.LoadString(nTitleWindowID),
        m_sTitleWizard.LoadString(nTitleWizardID),
        m_sTextWizard.LoadString(nTextWizardID),

        ZIDialog::Create(nID, bAutoCenter, pParent);
    return TRUE;
}

BOOL PSS_WizardDialog::Create(UINT        nID,
                            UINT        nBitmapID,
                            UINT        nIconID,
                              const CString    sTitleWindow,
                              const CString    sTitleWizard,
                              const CString    sTextWizard,
                            COLORREF    BackCol,
                            COLORREF    StaticCol,
                            COLORREF    EditCol,
                            BOOL        bAutoCenter,
                            BOOL        bStandAlone,
                            CWnd*        pParent)
{
    m_nID = nID;
    m_nBitmapID = nBitmapID;
    m_nIconID = nIconID;
    m_bStandAlone = bStandAlone;
    m_sTitleWindow = sTitleWindow;
    m_sTitleWizard = sTitleWizard;
    m_sTextWizard = sTextWizard;

    ZIDialog::Create(nID, bAutoCenter, BackCol, StaticCol, EditCol, pParent);
    return TRUE;
}

BOOL PSS_WizardDialog::Create(UINT        nID,
                            UINT        nBitmapID,
                            UINT        nIconID,
                            UINT        nTitleWindowID,
                            UINT        nTitleWizardID,
                            UINT        nTextWizardID,
                            COLORREF    BackCol,
                            COLORREF    StaticCol,
                            COLORREF    EditCol,
                            BOOL        bAutoCenter,
                            BOOL        bStandAlone,
                            CWnd*        pParent)
{
    m_nID = nID;
    m_nBitmapID = nBitmapID;
    m_nIconID = nIconID;
    m_bStandAlone = bStandAlone;

    m_sTitleWindow.LoadString(nTitleWindowID),
        m_sTitleWizard.LoadString(nTitleWizardID),
        m_sTextWizard.LoadString(nTextWizardID),

        ZIDialog::Create(nID, bAutoCenter, BackCol, StaticCol, EditCol, pParent);
    return TRUE;
}

void PSS_WizardDialog::CreateFont()
{
    // Create the text font
    VERIFY(m_TextFont.CreateFont(10,                // Size X
                                 8,                // Size Y
                                 0,                // Escapment
                                 0,                // Orientation
                                 FW_LIGHT,        // Weight
                                 0,                // Italic
                                 0,                // Underline
                                 0,                // StrikeOut
                                 DEFAULT_CHARSET,
                                 OUT_DEVICE_PRECIS,
                                 CLIP_TT_ALWAYS,
                                 PROOF_QUALITY,
                                 DEFAULT_PITCH,
                                 _T("MS Sans Serif")));

    // Create the title font
    VERIFY(m_TitleFont.CreateFont(15,                // Size X
                                  10,                // Size Y
                                  0,                // Escapment
                                  0,                // Orientation
                                  FW_BOLD,        // Weight
                                  0,                // Italic
                                  0,                // Underline
                                  0,                // StrikeOut
                                  DEFAULT_CHARSET,
                                  OUT_DEVICE_PRECIS,
                                  CLIP_TT_ALWAYS,
                                  PROOF_QUALITY,
                                  DEFAULT_PITCH,
                                  _T("System")));
}

void PSS_WizardDialog::SetWizardWindowTitle(UINT nID)
{
    CString Text;
    Text.LoadString(nID);
    SetWizardWindowTitle(Text);
}

void PSS_WizardDialog::SetWizardSubjectText(UINT nID)
{
    CString Text;
    Text.LoadString(nID);
    SetWizardSubjectText(Text);
}

void PSS_WizardDialog::SetWizardBodyText(UINT nID)
{
    CString Text;
    Text.LoadString(nID);
    SetWizardBodyText(Text);
}

void PSS_WizardDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PSS_WizardDialog)
    //}}AFX_DATA_MAP
}

void PSS_WizardDialog::Paint(CDC& dc)
{
    CFont*    OldFont;
    CBrush*    OldBrush;

    CBrush    NewBrush(defCOLOR_WHITE);
    CRect    WhiteRect(m_DialogRect.left + 1,
                       m_DialogRect.top + 1,
                       m_DialogRect.right - 2,
                       m_DialogRect.top + WhiteBoxHeight);

    OldBrush = dc.SelectObject(&NewBrush);
    dc.FillRect(WhiteRect, &NewBrush);

    CPen*    pOldPen = NULL;
    CPen    PenGray(PS_SOLID, 1, defCOLOR_GRAY);

    pOldPen = dc.SelectObject(&PenGray);

    dc.MoveTo(m_DialogRect.right, m_DialogRect.top);
    dc.LineTo(m_DialogRect.left, m_DialogRect.top);
    dc.LineTo(m_DialogRect.left, m_DialogRect.top + WhiteBoxHeight);

    dc.SelectObject(pOldPen);

    CPen    PenBlack(PS_SOLID, 1, defCOLOR_BLACK);

    pOldPen = dc.SelectObject(&PenBlack);

    dc.MoveTo(m_DialogRect.left, m_DialogRect.top + WhiteBoxHeight);
    dc.LineTo(m_DialogRect.right - 1, m_DialogRect.top + WhiteBoxHeight);
    dc.LineTo(m_DialogRect.right - 1, m_DialogRect.top);

    dc.SelectObject(pOldPen);

    Draw3DLine(dc.m_hDC,
               0,
               WhiteRect.left + 2,
               WhiteRect.bottom + 2,
               WhiteRect.right - 2,
               WhiteRect.bottom + 2);

    // Display the wizard title
    OldFont = dc.SelectObject(&m_TitleFont);

    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(defCOLOR_BLACK);
    dc.SetTextAlign(TA_LEFT | TA_BOTTOM);
    dc.TextOut(m_DialogRect.left + 7, m_DialogRect.top + 20, m_sTitleWizard);
    dc.SelectObject(OldFont);

    // Display the wizard text
    CRect TextRect(m_DialogRect.left + 50,
                   m_DialogRect.top + 25,
                   m_DialogRect.right - 55,
                   m_DialogRect.top + WhiteBoxHeight - 2);

    OldFont = dc.SelectObject(&m_TextFont);

    dc.SetTextColor(defCOLOR_GRAY);
    dc.SetTextAlign(0);
    dc.DrawText(m_sTextWizard, -1, &TextRect, DT_LEFT | DT_BOTTOM | DT_WORDBREAK);

    Draw3DLine(dc.m_hDC,
               0,
               WhiteRect.left + 2,
               m_DialogRect.bottom - 30,
               WhiteRect.right - 2,
               m_DialogRect.bottom - 30);

    dc.SelectObject(OldFont);
    dc.SelectObject(OldBrush);

    if (m_nBitmapID != 0)
    {
        ShowBitmapFile(MAKEINTRESOURCE(m_nBitmapID),
                       dc.m_hDC,
                       m_hInst,
                       m_DialogRect.right - 52,
                       m_DialogRect.top + 6);
    }
    else
        if (m_hIcon)
            dc.DrawIcon(m_DialogRect.right - 50, m_DialogRect.top + 6, m_hIcon);
}

/////////////////////////////////////////////////////////////////////////////
// PSS_WizardDialog message handlers

void PSS_WizardDialog::OnPaint()
{
    // Device context for painting
    CPaintDC dc(this);
    Paint(dc);
}

BOOL PSS_WizardDialog::OnInitDialog()
{
    if (m_bStandAlone)
    {
        GetDlgItem(IDNEXT)->ShowWindow(SW_HIDE);
    }

    m_btnHelp.AutoLoad(ID_HELP, this);

    if (m_nIconID)
    {
        m_hInst = AfxFindResourceHandle(MAKEINTRESOURCE(m_nIconID), RT_ICON);
        m_hIcon = ::LoadIcon(m_hInst, MAKEINTRESOURCE(m_nIconID));
    }

    // Find resources
    m_hInst = AfxFindResourceHandle(MAKEINTRESOURCE(m_nBitmapID), RT_BITMAP);

    ZIDialog::OnInitDialog();

    GetClientRect(&m_DialogRect);

    // If a title is defined
    if (!m_sTitleWindow.IsEmpty())
    {
        SetWindowText(m_sTitleWindow);
    }

    // Return TRUE  unless you set the focus to a control
    return TRUE;
}
