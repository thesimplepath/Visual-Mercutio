/****************************************************************************
 * ==> PSS_InPlaceEdit -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an in-place edit                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InPlaceEdit.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_InPlaceEdit
//---------------------------------------------------------------------------
BOOL PSS_InPlaceEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                float             initValue,
                                                CWnd*             pWndParent,
                                                const CRect&      rect,
                                                DWORD             style)
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                double            initValue,
                                                CWnd*             pWndParent,
                                                const CRect&      rect,
                                                DWORD             style)
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                PSS_Date&         initValue,
                                                CWnd*             pWndParent,
                                                const CRect&      rect,
                                                DWORD             style)
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                PSS_TimeSpan&     initValue,
                                                CWnd*             pWndParent,
                                                const CRect&      rect,
                                                DWORD             style)
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                PSS_Duration&     initValue,
                                                CWnd*             pWndParent,
                                                const CRect&      rect,
                                                DWORD             style)
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_InPlaceEdit::InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                                const CString&    initValue,
                                                CWnd*             pWndParent,
                                                const CRect&      rect,
                                                DWORD             style)
{
    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_InPlaceEdit::SetNewPropertyItem(PSS_PropertyItem* pItem)
{
    m_pItem = pItem;
}
//---------------------------------------------------------------------------
CString PSS_InPlaceEdit::GetEditText() const
{
    return _T("");
}
//---------------------------------------------------------------------------
void PSS_InPlaceEdit::SetEditText(float value)
{}
//---------------------------------------------------------------------------
void PSS_InPlaceEdit::SetEditText(double value)
{}
//---------------------------------------------------------------------------
void PSS_InPlaceEdit::SetEditText(PSS_Date& value)
{}
//---------------------------------------------------------------------------
void PSS_InPlaceEdit::SetEditText(PSS_TimeSpan& value)
{}
//---------------------------------------------------------------------------
void PSS_InPlaceEdit::SetEditText(PSS_Duration& value)
{}
//---------------------------------------------------------------------------
void PSS_InPlaceEdit::SetEditText(const CString& value)
{}
//---------------------------------------------------------------------------
void PSS_InPlaceEdit::CancelEdit()
{}
//---------------------------------------------------------------------------
void PSS_InPlaceEdit::SaveValue()
{}
//---------------------------------------------------------------------------
CSize PSS_InPlaceEdit::GetSize() const
{
    return CSize(0, 0);
}
//---------------------------------------------------------------------------
CSize PSS_InPlaceEdit::GetExtendedSize() const
{
    return CSize(0, 0);
}
//---------------------------------------------------------------------------
void PSS_InPlaceEdit::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{}
//---------------------------------------------------------------------------
