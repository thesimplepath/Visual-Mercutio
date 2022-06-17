/****************************************************************************
 * ==> PSS_FilteredDialog --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a dialog which provides input filters             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FilteredDialog.h"

// processsoft
#include "PSS_CharFilters.h"

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FilteredDialog, PSS_Dialog)
//{{AFX_MSG_MAP(PSS_FilteredDialog)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FilteredDialog
//---------------------------------------------------------------------------
PSS_FilteredDialog::PSS_FilteredDialog(UINT templateID, BOOL autoCenter, CWnd* pParentWnd) :
    PSS_Dialog(templateID, autoCenter, pParentWnd)
{}
//---------------------------------------------------------------------------
PSS_FilteredDialog::PSS_FilteredDialog(LPCSTR pTemplateName, BOOL autoCenter, CWnd* pParentWnd) :
    PSS_Dialog(pTemplateName, autoCenter, pParentWnd)
{}
//---------------------------------------------------------------------------
PSS_FilteredDialog::PSS_FilteredDialog(UINT     templateID,
                                       BOOL     autoCenter,
                                       COLORREF bgCol,
                                       COLORREF staticCol,
                                       COLORREF editCol,
                                       CWnd*    pParentWnd) :
    PSS_Dialog(templateID, autoCenter, bgCol, staticCol, editCol, pParentWnd)
{}
//---------------------------------------------------------------------------
PSS_FilteredDialog::PSS_FilteredDialog(LPCSTR   pTemplateName,
                                       BOOL     autoCenter,
                                       COLORREF bgCol,
                                       COLORREF staticCol,
                                       COLORREF editCol,
                                       CWnd*    pParentWnd) :
    PSS_Dialog(pTemplateName, autoCenter, bgCol, staticCol, editCol, pParentWnd)
{}
//---------------------------------------------------------------------------
PSS_FilteredDialog::~PSS_FilteredDialog()
{}
//---------------------------------------------------------------------------
BOOL PSS_FilteredDialog::PreTranslateMessage( MSG* pMsg )
{
    // dispatch received message
    switch (pMsg->message)
    {
        case WM_CHAR:
            // do filter chars and char is allowed?
            if (PSS_CharFilters::DoEscape(pMsg->wParam))
                // eat it
                return 1;

            break;
    }

    return CDialog::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------
