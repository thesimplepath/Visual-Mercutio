/****************************************************************************
 * ==> PSS_SymbolLabel -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol label                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SymbolLabel.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_SymbolLabel, CODLabelComponent, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_SymbolLabel
//---------------------------------------------------------------------------
PSS_SymbolLabel::PSS_SymbolLabel(bool notifyParent) :
    CODLabelComponent(),
    m_NotifyParent(notifyParent)
{}
//---------------------------------------------------------------------------
PSS_SymbolLabel::PSS_SymbolLabel(CODSymbolComponent* pOwner, bool notifyParent) :
    CODLabelComponent(pOwner),
    m_NotifyParent(notifyParent)
{}
//---------------------------------------------------------------------------
PSS_SymbolLabel::PSS_SymbolLabel(const OD_CONTROL_POINT align, bool notifyParent) :
    CODLabelComponent(align),
    m_NotifyParent(notifyParent)
{}
//---------------------------------------------------------------------------
PSS_SymbolLabel::PSS_SymbolLabel(const PSS_SymbolLabel& other) :
    CODLabelComponent(),
    m_NotifyParent(false)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_SymbolLabel::~PSS_SymbolLabel()
{}
//---------------------------------------------------------------------------
PSS_SymbolLabel& PSS_SymbolLabel::operator = (const PSS_SymbolLabel& other)
{
    CODLabelComponent::operator = ((const CODLabelComponent&)other);

    m_NotifyParent = other.m_NotifyParent;

    return *this;
}
//---------------------------------------------------------------------------
CODComponent* PSS_SymbolLabel::Dup() const
{
    return new PSS_SymbolLabel(*this);
}
//---------------------------------------------------------------------------
void PSS_SymbolLabel::Serialize(CArchive& ar)
{
    // serialize the label symbol
    CODLabelComponent::Serialize(ar);

    // only if the object is serialized from and to a document
    if (ar.m_pDocument)
        if (ar.IsStoring())
            ar << WORD(m_NotifyParent);
        else
        {
            WORD wValue;
            ar >> wValue;
            m_NotifyParent = bool(wValue);
        }
}
//---------------------------------------------------------------------------
