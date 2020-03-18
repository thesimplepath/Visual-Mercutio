/****************************************************************************
 * ==> PSS_PropertyItems ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides the property items                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PropertyItems.h"

// processsoft
#include "PSS_InPlaceDragEdit.h"
#include "PSS_InPlaceListBox.h"
#include "PSS_InPlaceExtendedEdit.h"
#include "PSS_InPlaceIntelliEdit.h"
#include "ZCInPlaceMultiLineEdit.h"
#include "ZCInPlaceSearchEdit.h"
#include "PSS_InPlaceDateEdit.h"
#include "ZCInPlaceTimeEdit.h"
#include "PSS_InPlaceDurationEdit.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_StringPropertyItem, PSS_PropertyItem)
//---------------------------------------------------------------------------
// PSS_StringPropertyItem
//---------------------------------------------------------------------------
PSS_StringPropertyItem::PSS_StringPropertyItem(const PSS_StringPropertyItem& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_StringPropertyItem& PSS_StringPropertyItem::operator = (const PSS_StringPropertyItem& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_StringPropertyItem::CreateInPlaceControl(CWnd*             pWndParent,
                                                  const CRect&      rect,
                                                  PSS_InPlaceEdit*& pWndInPlaceControl,
                                                  const CSize&      extendedSize)
{
    DestroyInPlaceControl(pWndInPlaceControl);

    std::unique_ptr<PSS_InPlacePropItemStringEdit> pControl(new PSS_InPlacePropItemStringEdit());
    pControl->InitializeInPlaceEditCtrl(this, m_StrValue, pWndParent, rect);
    pWndInPlaceControl = pControl.release();
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_ListPropertyItem, PSS_PropertyItem)
//---------------------------------------------------------------------------
// PSS_ListPropertyItem
//---------------------------------------------------------------------------
PSS_ListPropertyItem::PSS_ListPropertyItem(const PSS_ListPropertyItem& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ListPropertyItem& PSS_ListPropertyItem::operator = (const PSS_ListPropertyItem& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ListPropertyItem::SetData(const CString& value)
{
    m_StrValue = value;
}
//---------------------------------------------------------------------------
void PSS_ListPropertyItem::SetItemListData(PSS_InPlaceListBox* pWndInPlaceControl)
{
    LPCTSTR pStrText;

    for (int i = 0; (pStrText = GetItemData(i)) != NULL; ++i)
        pWndInPlaceControl->AddString(pStrText);
}
//---------------------------------------------------------------------------
void PSS_ListPropertyItem::CreateInPlaceControl(CWnd*             pWndParent,
                                                const CRect&      rect,
                                                PSS_InPlaceEdit*& pWndInPlaceControl,
                                                const CSize&      extendedSize)
{
    DestroyInPlaceControl(pWndInPlaceControl);

    std::unique_ptr<PSS_InPlaceListBox> pControl(new PSS_InPlaceListBox(IsReadOnly()));
    pControl->InitializeInPlaceEditCtrl(this, GetData(), pWndParent, rect);

    SetItemListData(pControl.get());
    pControl->SetCurSel(GetData(), false);
    pControl->ResetListBoxHeight();

    pWndInPlaceControl = pControl.release();
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_ExtendedPropertyItem, PSS_PropertyItem)
//---------------------------------------------------------------------------
// PSS_ExtendedPropertyItem
//---------------------------------------------------------------------------
PSS_ExtendedPropertyItem::PSS_ExtendedPropertyItem(const PSS_ExtendedPropertyItem& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ExtendedPropertyItem& PSS_ExtendedPropertyItem::operator = (const PSS_ExtendedPropertyItem& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ExtendedPropertyItem::CreateInPlaceControl(CWnd*             pWndParent,
                                                    const CRect&      rect,
                                                    PSS_InPlaceEdit*& pWndInPlaceControl,
                                                    const CSize&      extendedSize)
{
    DestroyInPlaceControl(pWndInPlaceControl);

    std::unique_ptr<PSS_InPlaceExtendedEdit> pControl(new PSS_InPlaceExtendedEdit(IsReadOnly()));

    // for processing extended command
    pControl->SetSearchType(PSS_SearchEditButton::IE_T_Extended);

    switch (m_Type)
    {
        case IE_NT_String: pControl->InitializeInPlaceEditCtrl(this, m_StrValue,    pWndParent, rect); break;
        case IE_NT_Double: pControl->InitializeInPlaceEditCtrl(this, m_DoubleValue, pWndParent, rect); break;
        case IE_NT_Float:  pControl->InitializeInPlaceEditCtrl(this, m_FloatValue,  pWndParent, rect); break;
    }

    pWndInPlaceControl = pControl.release();
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_IntelliEditPropertyItem, PSS_PropertyItem)
//---------------------------------------------------------------------------
// PSS_IntelliEditPropertyItem
//---------------------------------------------------------------------------
PSS_IntelliEditPropertyItem::PSS_IntelliEditPropertyItem(const PSS_IntelliEditPropertyItem& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_IntelliEditPropertyItem& PSS_IntelliEditPropertyItem::operator = (const PSS_IntelliEditPropertyItem& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_IntelliEditPropertyItem::SetData(const CString& value)
{
    m_StrValue = value;
}
//---------------------------------------------------------------------------
void PSS_IntelliEditPropertyItem::CreateInPlaceControl(CWnd*             pWndParent,
                                                       const CRect&      rect,
                                                       PSS_InPlaceEdit*& pWndInPlaceControl,
                                                       const CSize&      extendedSize)
{
    DestroyInPlaceControl(pWndInPlaceControl);

    std::unique_ptr<PSS_InPlaceIntelliEdit> pControl(new PSS_InPlaceIntelliEdit(IsReadOnly()));

    switch (m_Type)
    {
        case IE_NT_String: pControl->InitializeInPlaceEditCtrl(this, m_StrValue,    pWndParent, rect); break;
        case IE_NT_Double: pControl->InitializeInPlaceEditCtrl(this, m_DoubleValue, pWndParent, rect); break;
        case IE_NT_Float:  pControl->InitializeInPlaceEditCtrl(this, m_FloatValue,  pWndParent, rect); break;
    }

    // Initialize the control array of values
    pControl->Initialize(m_pData, (extendedSize.cx && extendedSize.cy) ? const_cast<CSize*>(&extendedSize) : NULL);

    pWndInPlaceControl = pControl.release();
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_MultiLineEditPropertyItem, PSS_PropertyItem)
//---------------------------------------------------------------------------
// PSS_MultiLineEditPropertyItem
//---------------------------------------------------------------------------
PSS_MultiLineEditPropertyItem::PSS_MultiLineEditPropertyItem(const PSS_MultiLineEditPropertyItem& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_MultiLineEditPropertyItem& PSS_MultiLineEditPropertyItem::operator = (const PSS_MultiLineEditPropertyItem& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_MultiLineEditPropertyItem::SetData(const CString& value)
{
    m_StrValue = value;
}
//---------------------------------------------------------------------------
void PSS_MultiLineEditPropertyItem::CreateInPlaceControl(CWnd*             pWndParent,
                                                         const CRect&      rect,
                                                         PSS_InPlaceEdit*& pWndInPlaceControl,
                                                         const CSize&      extendedSize)
{
    DestroyInPlaceControl(pWndInPlaceControl);

    std::unique_ptr<ZCInPlaceMultiLineEdit> pControl(new ZCInPlaceMultiLineEdit(IsReadOnly()));

    switch (m_Type)
    {
        case IE_NT_String: pControl->InitializeInPlaceEditCtrl(this, m_StrValue,    pWndParent, rect); break;
        case IE_NT_Double: pControl->InitializeInPlaceEditCtrl(this, m_DoubleValue, pWndParent, rect); break;
        case IE_NT_Float:  pControl->InitializeInPlaceEditCtrl(this, m_FloatValue,  pWndParent, rect); break;
    }

    // initialize the control
    if (extendedSize.cx && extendedSize.cy)
        pControl->Initialize(extendedSize);
    else
        pControl->Initialize();

    pWndInPlaceControl = pControl.release();
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_DatePropertyItem, PSS_PropertyItem)
//---------------------------------------------------------------------------
// PSS_DatePropertyItem
//---------------------------------------------------------------------------
PSS_DatePropertyItem::PSS_DatePropertyItem(const PSS_DatePropertyItem& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_DatePropertyItem& PSS_DatePropertyItem::operator = (const PSS_DatePropertyItem& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_DatePropertyItem::CreateInPlaceControl(CWnd*             pWndParent,
                                                const CRect&      rect,
                                                PSS_InPlaceEdit*& pWndInPlaceControl,
                                                const CSize&      extendedSize)
{
    DestroyInPlaceControl(pWndInPlaceControl);

    std::unique_ptr<PSS_InPlaceDateEdit> pControl(new PSS_InPlaceDateEdit(IsReadOnly()));

    // for processing extended command
    pControl->SetSearchType(PSS_SearchEditButton::IE_T_Extended);

    switch (m_Type)
    {
        case IE_NT_String: pControl->InitializeInPlaceEditCtrl(this, m_StrValue,  pWndParent, rect); break;
        case IE_NT_Date:   pControl->InitializeInPlaceEditCtrl(this, m_DateValue, pWndParent, rect); break;
    }

    pWndInPlaceControl = pControl.release();
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_TimePropertyItem, PSS_PropertyItem)
//---------------------------------------------------------------------------
// PSS_TimePropertyItem
//---------------------------------------------------------------------------
PSS_TimePropertyItem::PSS_TimePropertyItem(const PSS_TimePropertyItem& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_TimePropertyItem& PSS_TimePropertyItem::operator = (const PSS_TimePropertyItem& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_TimePropertyItem::CreateInPlaceControl(CWnd*           pWndParent,
                                              const CRect&    rect,
                                              PSS_InPlaceEdit*& pWndInPlaceControl,
                                              const CSize&    extendedSize)
{
    DestroyInPlaceControl(pWndInPlaceControl);

    std::unique_ptr<ZCInPlaceTimeEdit> pControl(new ZCInPlaceTimeEdit(IsReadOnly()));

    // for processing extended command
    pControl->SetSearchType(PSS_SearchEditButton::IE_T_Extended);

    switch (m_Type)
    {
        case IE_NT_String: pControl->InitializeInPlaceEditCtrl(this, m_StrValue,  pWndParent, rect); break;
        case IE_NT_Time:   pControl->InitializeInPlaceEditCtrl(this, m_TimeValue, pWndParent, rect); break;
    }

    pWndInPlaceControl = pControl.release();
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_DurationPropertyItem, PSS_PropertyItem)
//---------------------------------------------------------------------------
// PSS_DurationPropertyItem
//---------------------------------------------------------------------------
PSS_DurationPropertyItem::PSS_DurationPropertyItem(const PSS_DurationPropertyItem& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_DurationPropertyItem& PSS_DurationPropertyItem::operator = (const PSS_DurationPropertyItem& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_DurationPropertyItem::CreateInPlaceControl(CWnd*             pWndParent,
                                                    const CRect&      rect,
                                                    PSS_InPlaceEdit*& pWndInPlaceControl,
                                                    const CSize&      extendedSize)
{
    DestroyInPlaceControl(pWndInPlaceControl);

    std::unique_ptr<PSS_InPlaceDurationEdit> pControl(new PSS_InPlaceDurationEdit(IsReadOnly()));

    // for processing extended command
    pControl->SetSearchType(PSS_SearchEditButton::IE_T_Extended);

    switch (m_Type)
    {
        case IE_NT_String:   pControl->InitializeInPlaceEditCtrl(this, m_StrValue,      pWndParent, rect); break;
        case IE_NT_Duration: pControl->InitializeInPlaceEditCtrl(this, m_DurationValue, pWndParent, rect); break;
    }

    pWndInPlaceControl = pControl.release();
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_MenuFileDirPropertyItem, PSS_PropertyItem)
//---------------------------------------------------------------------------
// PSS_MenuFileDirPropertyItem
//---------------------------------------------------------------------------
PSS_MenuFileDirPropertyItem::PSS_MenuFileDirPropertyItem(const PSS_MenuFileDirPropertyItem& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_MenuFileDirPropertyItem& PSS_MenuFileDirPropertyItem::operator = (const PSS_MenuFileDirPropertyItem& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_MenuFileDirPropertyItem::CreateInPlaceControl(CWnd*             pWndParent,
                                                       const CRect&      rect,
                                                       PSS_InPlaceEdit*& pWndInPlaceControl,
                                                       const CSize&      extendedSize)
{
    DestroyInPlaceControl(pWndInPlaceControl);

    std::unique_ptr<ZCInPlaceSearchEdit> pControl(new ZCInPlaceSearchEdit(IsReadOnly()));

    switch (m_ControlType)
    {
        case IE_IT_Menu:      pControl->SetSearchType(PSS_SearchEditButton::IE_T_Popup, m_pMenu, true, true); break;
        case IE_IT_File:      pControl->SetSearchType(PSS_SearchEditButton::IE_T_File);                       break;
        case IE_IT_Directory: pControl->SetSearchType(PSS_SearchEditButton::IE_T_Directory);                  break;
    }

    switch (m_Type)
    {
        case IE_NT_String: pControl->InitializeInPlaceEditCtrl(this, m_StrValue,    pWndParent, rect); break;
        case IE_NT_Double: pControl->InitializeInPlaceEditCtrl(this, m_DoubleValue, pWndParent, rect); break;
        case IE_NT_Float:  pControl->InitializeInPlaceEditCtrl(this, m_FloatValue,  pWndParent, rect); break;
    }

    pWndInPlaceControl = pControl.release();
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_NumberPropertyItem, PSS_PropertyItem)
//---------------------------------------------------------------------------
// PSS_NumberPropertyItem
//---------------------------------------------------------------------------
PSS_NumberPropertyItem::PSS_NumberPropertyItem(const PSS_NumberPropertyItem& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_NumberPropertyItem& PSS_NumberPropertyItem::operator = (const PSS_NumberPropertyItem& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_NumberPropertyItem::CreateInPlaceControl(CWnd*             pWndParent,
                                                  const CRect&      rect,
                                                  PSS_InPlaceEdit*& pWndInPlaceControl,
                                                  const CSize&      extendedSize)
{
    DestroyInPlaceControl(pWndInPlaceControl);

    switch (m_Type)
    {
        case IE_NT_Float:
        {
            std::unique_ptr<PSS_InPlacePropItemNumberEdit> pControl(new PSS_InPlacePropItemNumberEdit(m_FloatValue, IsReadOnly()));
            pControl->InitializeInPlaceEditCtrl(this, m_FloatValue, pWndParent, rect);
            pWndInPlaceControl = pControl.release();
            return;
        }

        case IE_NT_Double:
        {
            std::unique_ptr<PSS_InPlacePropItemNumberEdit> pControl(new PSS_InPlacePropItemNumberEdit(m_DoubleValue, IsReadOnly()));
            pControl->InitializeInPlaceEditCtrl(this, m_DoubleValue, pWndParent, rect);
            pWndInPlaceControl = pControl.release();
            return;
        }
    }
}
//---------------------------------------------------------------------------
