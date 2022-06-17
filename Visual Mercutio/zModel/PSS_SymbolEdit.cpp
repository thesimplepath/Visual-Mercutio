/****************************************************************************
 * ==> PSS_SymbolEdit ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol edit                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SymbolEdit.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_SymbolEdit, PSS_BasicTextComponent, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_SymbolEdit
//---------------------------------------------------------------------------
PSS_SymbolEdit::PSS_SymbolEdit() :
    PSS_BasicTextComponent(),
    m_AutoSizeProp(TRUE),
    m_AllowEmptyText(true)
{}
//---------------------------------------------------------------------------
PSS_SymbolEdit::~PSS_SymbolEdit()
{}
//---------------------------------------------------------------------------
bool PSS_SymbolEdit::GetAllowEmptyText() const
{
    return m_AllowEmptyText;
}
//---------------------------------------------------------------------------
void PSS_SymbolEdit::SetAllowEmptyText(bool value)
{
    m_AllowEmptyText = value;
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolEdit::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case OD_PROP_AUTOSIZE: value = m_AutoSizeProp;
        default:               return CODTextComponent::GetValue(propId, value);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolEdit::GetValue(const int propId, UINT& value) const
{
    switch (propId)
    {
        case OD_PROP_AUTOSIZE: value = m_AutoSizeProp;
        default:               return CODTextComponent::GetValue(propId, value);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolEdit::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case OD_PROP_AUTOSIZE: value = m_AutoSizeProp;
        default:               return CODTextComponent::GetValue(propId, value);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolEdit::GetValue(const int nPropId, float& value) const
{
    return CODTextComponent::GetValue(nPropId, value);
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolEdit::GetValue(const int propId, CString& strValue) const
{
    return CODTextComponent::GetValue(propId, strValue);
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolEdit::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case OD_PROP_AUTOSIZE: m_AutoSizeProp = value;
        default:               return CODTextComponent::SetValue(propId, value);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolEdit::SetValue(const int propId, const UINT value)
{
    switch (propId)
    {
        case OD_PROP_AUTOSIZE: m_AutoSizeProp = value;
        default:               return CODTextComponent::SetValue(propId, value);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolEdit::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case OD_PROP_AUTOSIZE: m_AutoSizeProp = value;
        default:               return CODTextComponent::SetValue(propId, value);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolEdit::SetValue(const int propId, const float value)
{
    return CODTextComponent::SetValue(propId, value);
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolEdit::SetValue(const int propId, LPCTSTR pValue)
{
    return CODTextComponent::SetValue(propId, pValue);
}
//---------------------------------------------------------------------------
