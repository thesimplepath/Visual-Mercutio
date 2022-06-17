/****************************************************************************
 * ==> PSS_StateLink -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a state link for a state machine                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_StateLink.h"

// processsoft
#include "zModel\PSS_ProcessGraphModelMdl.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_StateLink, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_StateLink
//---------------------------------------------------------------------------
PSS_StateLink::PSS_StateLink(PSS_LinkSymbol*           pLinkSymbol,
                             IELinkDirection           direction,
                             PSS_ProcessGraphModelMdl* pModel) :
    CObject(),
    m_pModel(pModel),
    m_pLinkSymbol(pLinkSymbol),
    m_Direction(direction)
{}
//---------------------------------------------------------------------------
PSS_StateLink::PSS_StateLink(const PSS_StateLink& other) :
    CObject(),
    m_pModel(NULL),
    m_pLinkSymbol(NULL),
    m_Direction(IELinkDirection::IE_LD_EnteringUp)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_StateLink::~PSS_StateLink()
{}
//---------------------------------------------------------------------------
PSS_StateLink& PSS_StateLink::operator = (const PSS_StateLink& other)
{
    m_pModel      = other.m_pModel;
    m_pLinkSymbol = other.m_pLinkSymbol;
    m_Direction   = other.m_Direction;

    return *this;
}
//---------------------------------------------------------------------------
PSS_StateLink* PSS_StateLink::Clone() const
{
    return new PSS_StateLink(*this);
}
//---------------------------------------------------------------------------
bool PSS_StateLink::IsEqual(const PSS_StateLink& other) const
{
    return (m_pLinkSymbol                                                                                  &&
            other.GetLinkSymbol()                                                                          &&
            m_pLinkSymbol->GetSymbolReferenceNumber() == other.GetLinkSymbol()->GetSymbolReferenceNumber() &&
            GetDirection()                            == other.GetDirection());
}
//---------------------------------------------------------------------------
bool PSS_StateLink::IsEqual(const PSS_LinkSymbol& linkSymbol) const
{
    return (m_pLinkSymbol &&
            m_pLinkSymbol->GetSymbolReferenceNumber() == const_cast<PSS_LinkSymbol&>(linkSymbol).GetSymbolReferenceNumber());
}
//---------------------------------------------------------------------------
void PSS_StateLink::Serialize(CArchive& ar)
{
    // is currently storing?
    if (ar.IsStoring())
    {
        // write the elements, serialize the current object reference number
        if (m_pLinkSymbol)
            ar << m_pLinkSymbol->GetSymbolReferenceNumberStr();
        else
        {
            CString emptyString;
            emptyString.Empty();

            ar << emptyString;
        }
    }
    else
    {
        // read the elements, get the object reference number
        CString referenceNumberStr;
        ar >> referenceNumberStr;

        // initialize current object to null
        m_pLinkSymbol = NULL;

        if (!referenceNumberStr.IsEmpty() && m_pModel)
        {
            // find back the right symbol pointer
            const int        refNumber = std::atoi(referenceNumberStr);
            CODComponentSet* pSet      = m_pModel->FindSymbolByRefNumber(refNumber, true);

            if (pSet && pSet->GetSize() > 0)
                m_pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pSet->GetAt(0));
        }
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_StateLink::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_StateLink::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
