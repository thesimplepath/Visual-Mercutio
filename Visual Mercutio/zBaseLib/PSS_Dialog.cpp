/****************************************************************************
 * ==> PSS_Dialog ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic dialog                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Dialog.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_Dialog, CDialog)
    //{{AFX_MSG_MAP(PSS_Dialog)
    ON_WM_CTLCOLOR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_Dialog
//---------------------------------------------------------------------------
PSS_Dialog::PSS_Dialog(UINT templateID, BOOL autoCenter, CWnd* pParentWnd) :
    CDialog(templateID, pParentWnd),
    m_hBgBrush(NULL),
    m_BgCol(defCOLOR_WHITE),
    m_StaticCol(defCOLOR_BLACK),
    m_EditCol(defCOLOR_BLACK),
    m_CtlBgCol(defCOLOR_BLACK),
    m_CtlTextCol(defCOLOR_WHITE),
    m_AutoCenter(autoCenter),
    m_ColorHasBeenSuperseed(false)
{}
//---------------------------------------------------------------------------
PSS_Dialog::PSS_Dialog(LPCSTR pTemplateName, BOOL autoCenter, CWnd* pParentWnd) :
    CDialog(pTemplateName, pParentWnd),
    m_hBgBrush(NULL),
    m_BgCol(defCOLOR_WHITE),
    m_StaticCol(defCOLOR_BLACK),
    m_EditCol(defCOLOR_BLACK),
    m_CtlBgCol(defCOLOR_BLACK),
    m_CtlTextCol(defCOLOR_WHITE),
    m_AutoCenter(autoCenter),
    m_ColorHasBeenSuperseed(false)
{}
//---------------------------------------------------------------------------
PSS_Dialog::PSS_Dialog(UINT     templateID,
                       BOOL     autoCenter,
                       COLORREF bgCol,
                       COLORREF staticCol,
                       COLORREF editCol,
                       CWnd*    pParentWnd) :
    CDialog(templateID, pParentWnd),
    m_hBgBrush(NULL),
    m_BgCol(bgCol),
    m_StaticCol(staticCol),
    m_EditCol(editCol),
    m_CtlBgCol(defCOLOR_BLACK),
    m_CtlTextCol(defCOLOR_WHITE),
    m_AutoCenter(autoCenter),
    m_ColorHasBeenSuperseed(true)
{
    if (m_BgCol == -1 && m_StaticCol == -1 && m_EditCol == -1)
        m_ColorHasBeenSuperseed = false;
}
//---------------------------------------------------------------------------
PSS_Dialog::PSS_Dialog(LPCSTR   pTemplateName,
                       BOOL     autoCenter,
                       COLORREF bgCol,
                       COLORREF staticCol,
                       COLORREF editCol,
                       CWnd*    pParentWnd) :
    CDialog(pTemplateName, pParentWnd),
    m_hBgBrush(NULL),
    m_BgCol(bgCol),
    m_StaticCol(staticCol),
    m_EditCol(editCol),
    m_CtlBgCol(defCOLOR_BLACK),
    m_CtlTextCol(defCOLOR_WHITE),
    m_AutoCenter(autoCenter),
    m_ColorHasBeenSuperseed(true)
{
    if (m_BgCol == -1 && m_StaticCol == -1 && m_EditCol == -1)
        m_ColorHasBeenSuperseed = false;
}
//---------------------------------------------------------------------------
PSS_Dialog::PSS_Dialog(const PSS_Dialog& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_Dialog::~PSS_Dialog()
{
    if (m_hBgBrush)
        ::DeleteObject(m_hBgBrush);
}
//---------------------------------------------------------------------------
const PSS_Dialog& PSS_Dialog::operator = (const PSS_Dialog& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_Dialog::Create(UINT templateID, BOOL autoCenter, CWnd* pParentWnd)
{
    m_AutoCenter = autoCenter;
    CDialog::Create(templateID, pParentWnd);
}
//---------------------------------------------------------------------------
void PSS_Dialog::Create(LPCSTR pTemplateName, BOOL autoCenter, CWnd* pParentWnd)
{
    m_AutoCenter = autoCenter;
    CDialog::Create(pTemplateName, pParentWnd);
}
//---------------------------------------------------------------------------
void PSS_Dialog::Create(UINT     templateID,
                        BOOL     autoCenter,
                        COLORREF bgCol,
                        COLORREF staticCol,
                        COLORREF editCol,
                        CWnd*    pParentWnd)
{
    m_BgCol                 = bgCol;
    m_StaticCol             = staticCol;
    m_EditCol               = editCol;
    m_AutoCenter            = autoCenter;
    m_ColorHasBeenSuperseed = true;

    CDialog::Create(templateID, pParentWnd);
}
//---------------------------------------------------------------------------
void PSS_Dialog::Create(LPCSTR   pTemplateName,
                        BOOL     autoCenter,
                        COLORREF bgCol,
                        COLORREF staticCol,
                        COLORREF editCol,
                        CWnd*    pParentWnd)
{
    m_BgCol                 = bgCol;
    m_StaticCol             = staticCol;
    m_EditCol               = editCol;
    m_AutoCenter            = autoCenter;
    m_ColorHasBeenSuperseed = true;

    CDialog::Create(pTemplateName, pParentWnd);
}
//---------------------------------------------------------------------------
void PSS_Dialog::SetBackgroundColor(COLORREF col)
{
    m_BgCol                 = col;
    m_ColorHasBeenSuperseed = true;
}
//---------------------------------------------------------------------------
void PSS_Dialog::SetEditControlColor(COLORREF col)
{
    m_EditCol               = col;
    m_ColorHasBeenSuperseed = true;
}
//---------------------------------------------------------------------------
void PSS_Dialog::SetStaticControlColor(COLORREF col)
{
    m_StaticCol             = col;
    m_ColorHasBeenSuperseed = true;
}
//---------------------------------------------------------------------------
BOOL PSS_Dialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (m_AutoCenter)
        #ifndef _WIN32
            {
                // put the window in the center of the screen    
                CRect rect;
                GetClientRect(&rect);

                const UINT x = ::GetSystemMetrics(SM_CXFULLSCREEN);
                const UINT y = ::GetSystemMetrics(SM_CYFULLSCREEN);

                ::SetWindowPos(NULL, (x - rect.right) / 2, (y - rect.bottom) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
            }
        #else
                CenterWindow();
        #endif

    // background brush
    m_Brush.CreateSolidBrush(m_BgCol);

    SetDialogColors();

    // return TRUE unless you set the focus to a control
    return TRUE;
}
//---------------------------------------------------------------------------
HBRUSH PSS_Dialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    if (m_ColorHasBeenSuperseed)
    {
        switch (nCtlColor)
        {
            case CTLCOLOR_EDIT:
                // edit controls need a white background and a black text. NOTE the 'return hBrush'
                // is needed to draw the edit control's internal background (as opposed to text background)
                pDC->SetTextColor(m_EditCol);
                pDC->SetBkColor(RGB(255, 255, 255));
                return hBrush;

            case CTLCOLOR_STATIC:
            {
                // static controls need black text and same background as m_Brush
                LOGBRUSH logbrush;
                m_Brush.GetLogBrush(&logbrush);

                pDC->SetTextColor(m_StaticCol);
                pDC->SetBkColor(logbrush.lbColor);

                return m_Brush;
            }

            case CTLCOLOR_LISTBOX:
            case CTLCOLOR_SCROLLBAR:
            case CTLCOLOR_BTN:
            case CTLCOLOR_MSGBOX:
            case CTLCOLOR_DLG:
                // for listboxes, scrollbars, buttons, message boxes and dialogs, use the new brush (m_Brush)
                return m_Brush;

            default:
                // this shouldn't occur since we took all the cases, but JUST IN CASE, return the new brush
                return m_Brush;
        }
    }
    else
        switch (nCtlColor)
        {
            case CTLCOLOR_EDIT:
                // in normal mode, the edit boxes show a black text above a white background
                pDC->SetTextColor(m_EditCol);
                pDC->SetBkColor(RGB(255, 255, 255));
                break;

            default:
                // all other controls are shown in black above a grey background. The text background is transparent
                if (m_hBgBrush)
                {
                    pDC->SetTextColor(m_CtlTextCol);
                    pDC->SetBkMode(TRANSPARENT);
                    hBrush = m_hBgBrush;
                }

                break;
        }

    return hBrush;
}
//---------------------------------------------------------------------------
void PSS_Dialog::SetDialogColors(COLORREF bgColor, COLORREF textColor)
{
    if (m_hBgBrush)
        ::DeleteObject(m_hBgBrush);

    m_hBgBrush   = ::CreateSolidBrush(bgColor);
    m_CtlBgCol   = bgColor;
    m_CtlTextCol = textColor;
}
//---------------------------------------------------------------------------
