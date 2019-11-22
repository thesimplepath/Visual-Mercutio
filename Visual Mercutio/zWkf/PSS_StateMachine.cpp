/****************************************************************************
 * ==> PSS_StateMachine ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a state machine                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_StateMachine.h"

// processsoft
#include "zBaseSym\PSS_BasicSymbol.h"
#include "zModel\ProcGraphModelMdl.h"
#include "zModel\ZBSymbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "PSS_StateObject.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_StateMachine, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_StateMachine
//---------------------------------------------------------------------------
PSS_StateMachine::PSS_StateMachine(ZDProcessGraphModelMdl* pModel) :
    CObject(),
    m_pModel(pModel)
{}
//---------------------------------------------------------------------------
PSS_StateMachine::PSS_StateMachine(const PSS_StateMachine& other) :
    CObject()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_StateMachine::~PSS_StateMachine()
{
    RemoveAllObjects();
}
//---------------------------------------------------------------------------
PSS_StateMachine& PSS_StateMachine::operator = (const PSS_StateMachine& other)
{
    m_pModel = other.m_pModel;

    PSS_StateObjectIterator it(&other.GetStateObjectSetConst());

    // copy all state objects
    for (PSS_StateObject* pStateObj = it.GetFirst(); pStateObj; pStateObj = it.GetNext())
        AddStateObject(pStateObj->Clone());

    return *this;
}
//---------------------------------------------------------------------------
PSS_StateMachine* PSS_StateMachine::Clone() const
{
    return new PSS_StateMachine(*this);
}
//---------------------------------------------------------------------------
void PSS_StateMachine::AssignModel(ZDProcessGraphModelMdl* pModel)
{
    // assign the model
    m_pModel = pModel;

    // reassign the model to all state machines
    AssignModelToStateObjects();
}
//---------------------------------------------------------------------------
bool PSS_StateMachine::IsEqual(PSS_StateMachine* pOther)
{
    // check if object number is the same
    if (!pOther || (GetStateObjectCount() != pOther->GetStateObjectCount()))
        return false;

    const int count = GetStateObjectCount();

    for (int i = 0; i < count; ++i)
    {
        PSS_StateObject* pStateLeft  = GetStateObjectAt(i);
        PSS_StateObject* pStateRight = pOther->GetStateObjectAt(i);

        // check if one of both objects are null, not equal if yes
        if (!pStateLeft || !pStateRight)
            return false;

        // check if left is not equal to right
        if (!pStateLeft->IsEqual(pStateRight))
            return false;
    }

    // if all objects are equal, the state machines are equal
    return true;
}
//---------------------------------------------------------------------------
void PSS_StateMachine::PushSymbol(ZBSymbol* pSymbol, PSS_LinkSymbol* pLinkSymbol, PSS_StateLink::IELinkDirection direction)
{
    PSS_StateObject* pStateObj = new PSS_StateObject(pSymbol, pLinkSymbol, direction, m_pModel);
    AddStateObject(pStateObj);
}
//---------------------------------------------------------------------------
void PSS_StateMachine::PushSymbol(ZBSymbol* pSymbol, PSS_StateLink* pStateLink)
{
    PSS_StateObject* pStateObj = new PSS_StateObject(pSymbol, pStateLink, m_pModel);
    AddStateObject( pStateObj );
}
//---------------------------------------------------------------------------
void PSS_StateMachine::PushStateObject(PSS_StateObject* pStateObj)
{
    if (pStateObj)
        AddStateObject( pStateObj );
}
//---------------------------------------------------------------------------
bool PSS_StateMachine::MergeAllStates()
{
    bool              error = false;
    const std::size_t count = GetStateObjectCount();

    for (int i = count - 1; i >= 0; --i)
    {
        PSS_StateObject* pStateObject = GetStateObjectAt(i);
        const int        similar      = FindSimilar(pStateObject);

        if (similar != -1)
            if (!MergeStates(i, similar))
                error = true;
    }

    return !error;
}
//---------------------------------------------------------------------------
bool PSS_StateMachine::Merge(PSS_StateMachine* pOther)
{
    // merge the states of both state machines
    if (!MergeAllStates())
        return false;

    if (!pOther || !pOther->MergeAllStates())
        return false;

    // merging two state machines means merging only the last state object. That means also,
    // the stack has no longer consistency
    PSS_StateObject* pStateLeft  = GetCurrentStateObject();
    PSS_StateObject* pStateRight = pOther->GetCurrentStateObject();

    if (!pStateLeft || !pStateRight)
        return false;

    if (!pStateLeft->Merge(pStateRight))
        return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_StateMachine::Merge(PSS_StateMachineSet& setRight)
{
    // merge the states of both state machines
    if (!MergeAllStates())
        return false;

    PSS_StateMachineIterator it(&setRight);

    for (PSS_StateMachine* pStateMachine = it.GetFirst(); pStateMachine; pStateMachine = it.GetNext())
        if (!Merge(pStateMachine))
            return false;

    return true;
}
//---------------------------------------------------------------------------
void PSS_StateMachine::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements, serialize the size of the set
        ar << m_Set.GetSize();

        PSS_StateObjectIterator it(&m_Set);

        for (PSS_StateObject* pStateObj = it.GetFirst(); pStateObj; pStateObj = it.GetNext())
            ar << pStateObj;
    }
    else
    {
        // read the elements, remove all objects from the set
        RemoveAllObjects();

        // read the size of the set
        int count;
        ar >> count;

        PSS_StateObject* pStateObj;

        for (int i = 0; i < count; ++i)
        {
            ar >> pStateObj;
            AddStateObject(pStateObj);
        }

        if (m_pModel)
            AssignModelToStateObjects();
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_StateMachine::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_StateMachine::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_StateMachine::AssignModelToStateObjects()
{
    PSS_StateObjectIterator it(&m_Set);

    for (PSS_StateObject* pStateObj = it.GetFirst(); pStateObj; pStateObj = it.GetNext())
        pStateObj->AssignModel(m_pModel);
}
//---------------------------------------------------------------------------
void PSS_StateMachine::RemoveAllObjects()
{
    PSS_StateObjectIterator it(&m_Set);

    for (PSS_StateObject* pStateObj = it.GetFirst(); pStateObj; pStateObj = it.GetNext())
        delete pStateObj;

    // remove all elements
    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
int PSS_StateMachine::AddStateObject(PSS_StateObject* pStateObj)
{
    if (pStateObj)
    {
        m_Set.Add(pStateObj);

        // return the index
        return GetStateObjectCount() - 1;
    }

    return -1;
}
//---------------------------------------------------------------------------
PSS_StateObject* PSS_StateMachine::PopStateObject(bool removeFromStack, std::size_t level)
{
    PSS_StateObject* pStateObj = NULL;

    // increment to one, because 0 means the current object
    ++level;

    if (GetStateObjectCount() >= level)
    {
        // get the state object
        pStateObj = m_Set.GetAt(GetStateObjectCount() - level);

        // Don't delete pStateObj, otherwise the returned object will be invalid.
        // If necessary to remove from stack, remove the element from the stack
        if (removeFromStack)
            m_Set.RemoveAt(GetStateObjectCount() - level);
    }

    return pStateObj;
}
//---------------------------------------------------------------------------
void PSS_StateMachine::RemoveStateObjectAt(std::size_t index, bool deleteObject)
{
    PSS_StateObject* pStateObject = GetStateObjectAt(index);

    if (pStateObject)
    {
        m_Set.RemoveAt(index);

        if (deleteObject)
            delete pStateObject;
    }
}
//---------------------------------------------------------------------------
int PSS_StateMachine::FindSimilar(PSS_StateObject* pStateObjectToFind)
{
    const std::size_t count = GetStateObjectCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_StateObject* pStateObj = GetStateObjectAt(i);

        // don't compare to itself and should be equals in terms of reference
        if ((pStateObj != pStateObjectToFind) && pStateObjectToFind->IsEqual(pStateObj))
            return i;
    }

    return -1;
}
//---------------------------------------------------------------------------
bool PSS_StateMachine::MergeStates(int iLeft, int iRight, bool deleteRight)
{
    PSS_StateObject* pLeft  = GetStateObjectAt(iLeft);
    PSS_StateObject* pRight = GetStateObjectAt(iRight);

    if (!pLeft || !pRight)
        return false;

    if (!pLeft->Merge(pRight))
        return false;

    if (deleteRight)
        RemoveStateObjectAt(iRight, true);

    return true;
}
//---------------------------------------------------------------------------
