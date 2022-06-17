/****************************************************************************
 * ==> PSS_FilteredDialogBox -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a dialog box which provides input filters         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FilteredDialogBox.h"

// processsoft
#include "PSS_CharFilters.h"

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FilteredDialogBox, CDialog)
//{{AFX_MSG_MAP(PSS_FilteredDialogBox)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FilteredDialogBox
//---------------------------------------------------------------------------
PSS_FilteredDialogBox::PSS_FilteredDialogBox(UINT IDD, CWnd* pParent) :
    CDialog(IDD, pParent),
    m_FilterChars(false)
{}
//---------------------------------------------------------------------------
PSS_FilteredDialogBox::~PSS_FilteredDialogBox()
{}
//---------------------------------------------------------------------------
void PSS_FilteredDialogBox::EnableCharFilter(bool value)
{
    m_FilterChars = value;
}
//---------------------------------------------------------------------------
BOOL PSS_FilteredDialogBox::PreTranslateMessage( MSG* pMsg )
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

    return CDialog::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
