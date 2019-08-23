/****************************************************************************
 * ==> PSS_WizardDialog ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic Wizard dialog box                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WizardDialog.h"

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
    m_hInst(NULL),
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
    m_hInst(NULL),
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
    m_TitleWindow = titleWindow;
    m_TitleWizard = titleWizard;
    m_TextWizard  = textWizard;
    m_ID          = id;
    m_BitmapID    = bitmapID;
    m_IconID      = iconID;
    m_Standalone  = standalone;

    ZIDialog::Create(id, autoCenter, pParent);
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_WizardDialog::Create(UINT  id,
                              UINT  bitmapID,
                              UINT  iconID,
                              UINT  titleWindowID,
                              UINT  titleWizardID,
                              UINT  textWizardID,
                              BOOL  autoCenter,
                              BOOL  standalone,
                              CWnd* pParent)
{
    m_ID         = id;
    m_BitmapID   = bitmapID;
    m_IconID     = iconID;
    m_Standalone = standalone;

    m_TitleWindow.LoadString(titleWindowID),
    m_TitleWizard.LoadString(titleWizardID),
    m_TextWizard.LoadString (textWizardID),

    ZIDialog::Create(id, autoCenter, pParent);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_WizardDialog::Create(UINT           id,
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
                              CWnd*          pParent)
{
    m_TitleWindow = titleWindow;
    m_TitleWizard = titleWizard;
    m_TextWizard  = textWizard;
    m_ID          = id;
    m_BitmapID    = bitmapID;
    m_IconID      = iconID;
    m_Standalone  = standalone;

    ZIDialog::Create(id, autoCenter, backCol, staticCol, editCol, pParent);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_WizardDialog::Create(UINT     id,
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
                              CWnd*    pParent)
{
    m_ID         = id;
    m_BitmapID   = bitmapID;
    m_IconID     = iconID;
    m_Standalone = standalone;

    m_TitleWindow.LoadString(titleWindowID),
    m_TitleWizard.LoadString(titleWizardID),
    m_TextWizard.LoadString (textWizardID),

    ZIDialog::Create(id, autoCenter, backCol, staticCol, editCol, pParent);

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_WizardDialog::SetWizardWindowTitle(UINT id)
{
    CString text;
    text.LoadString(id);
    SetWizardWindowTitle(text);
}
//---------------------------------------------------------------------------
void PSS_WizardDialog::SetWizardSubjectText(UINT id)
{
    CString text;
    text.LoadString(id);
    SetWizardSubjectText(text);
}
//---------------------------------------------------------------------------
void PSS_WizardDialog::SetWizardBodyText(UINT id)
{
    CString text;
    text.LoadString(id);
    SetWizardBodyText(text);
}
//---------------------------------------------------------------------------
void PSS_WizardDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_WizardDialog)
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
void PSS_WizardDialog::Paint(CDC& dc)
{
    CBrush newBrush(defCOLOR_WHITE);
    CRect  whiteRect(m_DialogRect.left  + 1,
                     m_DialogRect.top   + 1,
                     m_DialogRect.right - 2,
                     m_DialogRect.top   + g_WhiteBoxHeight);

    CBrush* pOldBrush = dc.SelectObject(&newBrush);
    dc.FillRect(whiteRect, &newBrush);

    CPen  penGray(PS_SOLID, 1, defCOLOR_GRAY);
    CPen* pOldPen = dc.SelectObject(&penGray);

    dc.MoveTo(m_DialogRect.right, m_DialogRect.top);
    dc.LineTo(m_DialogRect.left, m_DialogRect.top);
    dc.LineTo(m_DialogRect.left, m_DialogRect.top + g_WhiteBoxHeight);
    dc.SelectObject(pOldPen);

    CPen penBlack(PS_SOLID, 1, defCOLOR_BLACK);
    pOldPen = dc.SelectObject(&penBlack);

    dc.MoveTo(m_DialogRect.left,      m_DialogRect.top + g_WhiteBoxHeight);
    dc.LineTo(m_DialogRect.right - 1, m_DialogRect.top + g_WhiteBoxHeight);
    dc.LineTo(m_DialogRect.right - 1, m_DialogRect.top);
    dc.SelectObject(pOldPen);

    ::Draw3DLine(dc.m_hDC,
                 0,
                 whiteRect.left   + 2,
                 whiteRect.bottom + 2,
                 whiteRect.right  - 2,
                 whiteRect.bottom + 2);

    // show the wizard title
    CFont* pOldFont = dc.SelectObject(&m_TitleFont);

    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(defCOLOR_BLACK);
    dc.SetTextAlign(TA_LEFT | TA_BOTTOM);
    dc.TextOut(m_DialogRect.left + 7, m_DialogRect.top + 20, m_TitleWizard);
    dc.SelectObject(pOldFont);

    // show the wizard text
    CRect textRect(m_DialogRect.left  + 50,
                   m_DialogRect.top   + 25,
                   m_DialogRect.right - 55,
                   m_DialogRect.top   + g_WhiteBoxHeight - 2);

    pOldFont = dc.SelectObject(&m_TextFont);

    dc.SetTextColor(defCOLOR_GRAY);
    dc.SetTextAlign(0);
    dc.DrawText(m_TextWizard, -1, &textRect, DT_LEFT | DT_BOTTOM | DT_WORDBREAK);

    ::Draw3DLine(dc.m_hDC,
                 0,
                 whiteRect.left      + 2,
                 m_DialogRect.bottom - 30,
                 whiteRect.right     - 2,
                 m_DialogRect.bottom - 30);

    dc.SelectObject(pOldFont);
    dc.SelectObject(pOldBrush);

    if (m_BitmapID != 0)
    {
        ShowBitmapFile(MAKEINTRESOURCE(m_BitmapID),
                                       dc.m_hDC,
                                       m_hInst,
                                       m_DialogRect.right - 52,
                                       m_DialogRect.top   + 6);
    }
    else
    if (m_hIcon)
        dc.DrawIcon(m_DialogRect.right - 50, m_DialogRect.top + 6, m_hIcon);
}
//---------------------------------------------------------------------------
BOOL PSS_WizardDialog::OnInitDialog()
{
    if (m_Standalone)
        GetDlgItem(IDNEXT)->ShowWindow(SW_HIDE);

    m_BtnHelp.AutoLoad(ID_HELP, this);

    if (m_IconID)
    {
        m_hInst = AfxFindResourceHandle(MAKEINTRESOURCE(m_IconID), RT_ICON);
        m_hIcon = ::LoadIcon(m_hInst, MAKEINTRESOURCE(m_IconID));
    }

    // find resources
    m_hInst = AfxFindResourceHandle(MAKEINTRESOURCE(m_BitmapID), RT_BITMAP);

    ZIDialog::OnInitDialog();

    GetClientRect(&m_DialogRect);

    // is title defined?
    if (!m_TitleWindow.IsEmpty())
        SetWindowText(m_TitleWindow);

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_WizardDialog::OnPaint()
{
    // device context for painting
    CPaintDC dc(this);
    Paint(dc);
}
//---------------------------------------------------------------------------
void PSS_WizardDialog::OnNext()
{}
//---------------------------------------------------------------------------
void PSS_WizardDialog::CreateFont()
{
    // create the text font
    VERIFY(m_TextFont.CreateFont(10,
                                 8,
                                 0,
                                 0,
                                 FW_LIGHT,
                                 0,
                                 0,
                                 0,
                                 DEFAULT_CHARSET,
                                 OUT_DEVICE_PRECIS,
                                 CLIP_TT_ALWAYS,
                                 PROOF_QUALITY,
                                 DEFAULT_PITCH,
                                 _T("MS Sans Serif")));

    // create the title font
    VERIFY(m_TitleFont.CreateFont(15,
                                  10,
                                  0,
                                  0,
                                  FW_BOLD,
                                  0,
                                  0,
                                  0,
                                  DEFAULT_CHARSET,
                                  OUT_DEVICE_PRECIS,
                                  CLIP_TT_ALWAYS,
                                  PROOF_QUALITY,
                                  DEFAULT_PITCH,
                                  _T("System")));
}
//---------------------------------------------------------------------------
