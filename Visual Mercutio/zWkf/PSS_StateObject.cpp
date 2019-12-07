/****************************************************************************
 * ==> PSS_StateObject -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a state object                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_StateObject.h"

// processsoft
#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zModel\ZBSymbol.h"
#include "zModel\PSS_LinkSymbol.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_StateObject, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_StateObject
//---------------------------------------------------------------------------
PSS_StateObject::PSS_StateObject(ZBSymbol*                      pSymbol,
                                 PSS_LinkSymbol*                pLinkSymbol,
                                 PSS_StateLink::IELinkDirection direction,
                                 PSS_ProcessGraphModelMdl*      pModel) :
    CObject(),
    m_pModel(pModel),
    m_pSymbol(pSymbol)
{
    if (pSymbol && pLinkSymbol)
        AddLink(pLinkSymbol, direction);
}
//---------------------------------------------------------------------------
PSS_StateObject::PSS_StateObject(ZBSymbol*                 pSymbol,
                                 PSS_StateLink*            pStateLink,
                                 PSS_ProcessGraphModelMdl* pModel) :
    CObject(),
    m_pModel(pModel),
    m_pSymbol(pSymbol)
{
    if (pStateLink)
        AddStateLink(pStateLink);
}
//---------------------------------------------------------------------------
PSS_StateObject::PSS_StateObject(const PSS_StateObject& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_StateObject::~PSS_StateObject()
{
    RemoveAllLinks();
}
//---------------------------------------------------------------------------
PSS_StateObject& PSS_StateObject::operator = (const PSS_StateObject& other)
{
    m_pSymbol = other.m_pSymbol;
    m_pModel  = other.m_pModel;

    // copy all state link objects
    PSS_StateLinksIterator it(&other.GetLinkSetConst());

    for (PSS_StateLink* pStateLink = it.GetFirst(); pStateLink; pStateLink = it.GetNext())
        AddStateLink(pStateLink->Clone());

    return *this;
}
//---------------------------------------------------------------------------
PSS_StateObject* PSS_StateObject::Clone() const
{
    return new PSS_StateObject(*this);
}
//---------------------------------------------------------------------------
void PSS_StateObject::AssignModel(PSS_ProcessGraphModelMdl* pModel)
{
    // assign the model
    m_pModel = pModel;

    // reassign the model to all state links
    AssignModelToStateLinks();
}
//---------------------------------------------------------------------------
bool PSS_StateObject::IsEqual(PSS_StateObject* pOther)
{
    return (pOther              &&
            pOther->GetSymbol() &&
            GetSymbol()         &&
            pOther->GetSymbol()->GetSymbolReferenceNumber() == GetSymbol()->GetSymbolReferenceNumber());
}
//---------------------------------------------------------------------------
bool PSS_StateObject::Exist(PSS_LinkSymbol& linkSymbol)
{
    PSS_StateLinksIterator it(&GetLinkSet());

    // iterate through all links and search for a matching link symbol
    for (PSS_StateLink* pStateLink = it.GetFirst(); pStateLink; pStateLink = it.GetNext())
        if (pStateLink->IsEqual(linkSymbol))
            return true;

    return false;
}
//---------------------------------------------------------------------------
std::size_t PSS_StateObject::EdgesExist(CODEdgeArray& edges)
{
    const std::size_t elementCount = edges.GetSize();
          std::size_t counter      = 0;

    for (std::size_t edgeIndex = 0; edgeIndex < elementCount; ++edgeIndex)
    {
        IODEdge* pIEdge = edges.GetAt(edgeIndex);

        if (!pIEdge)
            continue;

        PSS_LinkSymbol* pLink = dynamic_cast<PSS_LinkSymbol*>(pIEdge);

        if (!pLink)
            continue;

        if (Exist(*pLink))
            ++counter;
    }

    return counter;
}
//---------------------------------------------------------------------------
void PSS_StateObject::AddLink(PSS_LinkSymbol* pLinkSymbol, PSS_StateLink::IELinkDirection direction)
{
    PSS_StateLink* pStateLink = new PSS_StateLink(pLinkSymbol, direction, m_pModel);
    AddStateLink(pStateLink);
}
//---------------------------------------------------------------------------
bool PSS_StateObject::RemoveLink(PSS_LinkSymbol* pLinkSymbol)
{
    PSS_StateLinksIterator it(&m_Set);

    for (PSS_StateLink* pStateLink = it.GetFirst(); pStateLink; pStateLink = it.GetNext())
        if (pStateLink->GetLinkSymbol() == pLinkSymbol)
        {
            it.Remove();
            delete pStateLink;

            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_StateObject::RemoveLink(int refNb)
{
    PSS_StateLinksIterator it(&m_Set);

    for (PSS_StateLink* pStateLink = it.GetFirst(); pStateLink; pStateLink = it.GetNext())
        if (pStateLink->GetLinkSymbol() && pStateLink->GetLinkSymbol()->GetSymbolReferenceNumber() == refNb)
        {
            it.Remove();
            delete pStateLink;

            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
void PSS_StateObject::RemoveAllLinks()
{
    PSS_StateLinksIterator it(&m_Set);

    for (PSS_StateLink* pStateLink = it.GetFirst(); pStateLink; pStateLink = it.GetNext())
        delete pStateLink;

    // remove all elements
    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
bool PSS_StateObject::Merge(PSS_StateObject* pOther)
{
    if (!pOther)
        return false;

    PSS_StateLinksIterator it(&pOther->GetLinkSet());

    // iterate through all link and merge each of them
    for (PSS_StateLink* pStateLink = it.GetFirst(); pStateLink; pStateLink = it.GetNext())
        AddStateLink(pStateLink->Clone());

    return true;
}
//---------------------------------------------------------------------------
bool PSS_StateObject::Merge(PSS_StateObjectSet& others)
{
    PSS_StateObjectIterator it(&others);

    // iterate through all state objects and merge their links
    for (PSS_StateObject* pStateObj = it.GetFirst(); pStateObj; pStateObj = it.GetNext())
        if (!Merge(pStateObj))
            return false;

    return true;
}
//---------------------------------------------------------------------------
void PSS_StateObject::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements, serialize the current object reference number
        if (m_pSymbol)
            ar << m_pSymbol->GetSymbolReferenceNumberStr();
        else
        {
            CString emptyString;
            emptyString.Empty();

            ar << emptyString;
        }

        // serialize the set size
        ar << m_Set.GetSize();

        PSS_StateLinksIterator it(&m_Set);

        // serialize all objects
        for (PSS_StateLink* pStateLink = it.GetFirst(); pStateLink; pStateLink = it.GetNext())
            ar << pStateLink;
    }
    else
    {
        // read the elements, get the object reference number
        CString referenceNumberStr;
        ar >> referenceNumberStr;

        // initialize current object to null
        m_pSymbol = NULL;

        if (!referenceNumberStr.IsEmpty() && m_pModel)
        {
            // get back the symbol
            const int        refNumber = std::atoi(referenceNumberStr);
            CODComponentSet* pSet      = m_pModel->FindSymbolByRefNumber(refNumber, true);

            if (pSet && pSet->GetSize() > 0)
                m_pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(0));
        }

        // remove all previous existing objects from the set
        RemoveAllLinks();

        // read the set size
        int count;
        ar >> count;

        PSS_StateLink* pStateLink;

        for (int i = 0; i < count; ++i)
        {
            ar >> pStateLink;
            AddStateLink(pStateLink);
        }

        if (m_pModel)
            AssignModelToStateLinks();
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_StateObject::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_StateObject::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_StateObject::AssignModelToStateLinks()
{
    PSS_StateLinksIterator it(&m_Set);

    for (PSS_StateLink* pStateLink = it.GetFirst(); pStateLink; pStateLink = it.GetNext())
        pStateLink->AssignModel(m_pModel);
}
//---------------------------------------------------------------------------
int PSS_StateObject::AddStateLink(PSS_StateLink* pStateLink)
{
    if (!pStateLink)
        return -1;

    m_Set.Add(pStateLink);

    // return the index
    return GetStateLinkCount() - 1;
}
//---------------------------------------------------------------------------
