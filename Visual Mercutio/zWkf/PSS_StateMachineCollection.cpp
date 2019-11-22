/****************************************************************************
 * ==> PSS_StateMachineCollection ------------------------------------------*
 ****************************************************************************
 * Description : Provides a collection which keeps the complete state of a  *
 *               model                                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_StateMachineCollection.h"

// processsoft
#include "zModel\ProcGraphModelMdl.h"
#include "PSS_StateMachine.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_StateMachineCollection, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_StateMachineCollection
//---------------------------------------------------------------------------
PSS_StateMachineCollection::PSS_StateMachineCollection(ZDProcessGraphModelMdl* pModel) :
    CObject(),
    m_pModel(pModel)
{}
//---------------------------------------------------------------------------
PSS_StateMachineCollection::PSS_StateMachineCollection(const PSS_StateMachineCollection& other) :
    CObject()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_StateMachineCollection::~PSS_StateMachineCollection()
{
    RemoveAllObjects();
}
//---------------------------------------------------------------------------
PSS_StateMachineCollection& PSS_StateMachineCollection::operator = (const PSS_StateMachineCollection& other)
{
    m_pModel = other.m_pModel;

    // copy all state objects
    PSS_StateMachineIterator it(&other.GetStateMachineSetConst());

    for (PSS_StateMachine* pStateMachine = it.GetFirst(); pStateMachine; pStateMachine = it.GetNext())
        AddStateMachine(pStateMachine->Clone());

    return *this;
}
//---------------------------------------------------------------------------
PSS_StateMachineCollection* PSS_StateMachineCollection::Clone() const
{
    return new PSS_StateMachineCollection(*this);
}
//---------------------------------------------------------------------------
void PSS_StateMachineCollection::AssignModel(ZDProcessGraphModelMdl* pModel)
{
    // assign the model
    m_pModel = pModel;

    // assign the model to all state machines
    AssignModelToStateMachines();
}
//---------------------------------------------------------------------------
PSS_StateMachineHandle PSS_StateMachineCollection::CreateNewStateMachine(ZBSymbol*                      pSymbol,
                                                                         PSS_LinkSymbol*                pLinkSymbol,
                                                                         PSS_StateLink::IELinkDirection direction)
{
    PSS_StateMachine* pNewStateMachine = new PSS_StateMachine(m_pModel);
    ASSERT(pNewStateMachine);

    pNewStateMachine->PushSymbol(pSymbol, pLinkSymbol, direction);
    return AddStateMachine(pNewStateMachine);
}
//---------------------------------------------------------------------------
PSS_StateMachineHandle PSS_StateMachineCollection::CreateNewStateMachine(PSS_StateObject* pStateObj)
{
    PSS_StateMachine* pNewStateMachine = new PSS_StateMachine(m_pModel);
    ASSERT(pNewStateMachine);

    pNewStateMachine->PushStateObject(pStateObj);
    return AddStateMachine(pNewStateMachine);
}
//---------------------------------------------------------------------------
bool PSS_StateMachineCollection::DeleteStateMachine(PSS_StateMachineHandle hStateMachine)
{
    // handle doesn't exists?
    if (hStateMachine >= int(GetStateMachineCount()))
        return false;

    // get state machine
    PSS_StateMachine* pStateMachine = m_Set.GetAt(hStateMachine);

    // delete it
    if (pStateMachine)
        delete pStateMachine;

    // remove its handle from state machine set
    m_Set.RemoveAt(hStateMachine);

    return true;
}
//---------------------------------------------------------------------------
ZBSymbol* PSS_StateMachineCollection::GetCurrentStateMachineSymbol(PSS_StateMachineHandle hStateMachine)
{
    // handle doesn't exists?
    if (hStateMachine >= int(GetStateMachineCount()))
        return NULL;

    // get state machine symbol
    PSS_StateMachine* pStateMachine = m_Set.GetAt(hStateMachine);
    return (pStateMachine ? pStateMachine->GetCurrentSymbol() : NULL);
}
//---------------------------------------------------------------------------
PSS_StateObject* PSS_StateMachineCollection::GetCurrentStateMachineObject(PSS_StateMachineHandle hStateMachine)
{
    // handle doesn't exists?
    if (hStateMachine >= int(GetStateMachineCount()))
        return NULL;

    // get state machine object
    PSS_StateMachine* pStateMachine = m_Set.GetAt(hStateMachine);
    return (pStateMachine ? pStateMachine->GetCurrentStateObject() : NULL);
}
//---------------------------------------------------------------------------
bool PSS_StateMachineCollection::PushSymbol(PSS_StateMachineHandle         hStateMachine,
                                            ZBSymbol*                      pSymbol,
                                            PSS_LinkSymbol*                pLinkSymbol,
                                            PSS_StateLink::IELinkDirection direction)
{
    PSS_StateMachine* pStateMachine = GetStateMachine(hStateMachine);

    if (!pStateMachine)
        return false;

    pStateMachine->PushSymbol(pSymbol, pLinkSymbol, direction);
    return true;
}
//---------------------------------------------------------------------------
bool PSS_StateMachineCollection::PushStateObject(PSS_StateMachineHandle hStateMachine, PSS_StateObject* pStateObj)
{
    PSS_StateMachine* pStateMachine = GetStateMachine(hStateMachine);

    if (!pStateMachine)
        return false;

    pStateMachine->PushStateObject(pStateObj);
    return true;
}
//---------------------------------------------------------------------------
bool PSS_StateMachineCollection::CopyCurrentStateObjects(const PSS_StateMachineCollection& src, bool mergeObjectsFirst)
{
    PSS_StateMachineIterator it(&src.GetStateMachineSetConst());

    // copy all state objects
    for (PSS_StateMachine* pStateMachine = it.GetFirst(); pStateMachine; pStateMachine = it.GetNext())
    {
        PSS_StateObject* pStateObj = NULL;

        if (mergeObjectsFirst)
        {
            // clone the state machine
            PSS_StateMachine* pStateMachineClone = pStateMachine->Clone();
            ASSERT(pStateMachineClone);
            pStateMachineClone->MergeAllStates();

            if (pStateMachineClone->GetCurrentStateObject())
                pStateObj = pStateMachineClone->GetCurrentStateObject()->Clone();

            // delete cloned state machine, useless since now
            delete pStateMachineClone;
        }
        else
        if (pStateMachine->GetCurrentStateObject())
            pStateObj = pStateMachine->GetCurrentStateObject()->Clone();

        // no state object?
        if (!pStateObj)
            return false;

        // create a new state machine
        if (CreateNewStateMachine(pStateObj) == -1)
            return false;
    }

    return true;
}
//---------------------------------------------------------------------------
int PSS_StateMachineCollection::AddStateMachine(PSS_StateMachine* pStateMachine)
{
    if (!pStateMachine)
        return -1;

    m_Set.Add(pStateMachine);

    // return the index
    return GetStateMachineCount() - 1;
}
//---------------------------------------------------------------------------
void PSS_StateMachineCollection::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements, serialize the set size
        ar << m_Set.GetSize();

        PSS_StateMachineIterator it(&m_Set);

        // serialize the state machines
        for (PSS_StateMachine* pStateMachine = it.GetFirst(); pStateMachine; pStateMachine = it.GetNext())
            ar << pStateMachine;
    }
    else
    {
        // clear all previously existing objects
        RemoveAllObjects();

        // read the elements, deserialize the set size
        int count;
        ar >> count;

        PSS_StateMachine* pStateMachine;

        // deserialize the state machines
        for (int i = 0; i < count; ++i)
        {
            ar >> pStateMachine;
            AddStateMachine(pStateMachine);
        }

        if (m_pModel)
            AssignModelToStateMachines();
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_StateMachineCollection::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_StateMachineCollection::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_StateMachineCollection::AssignModelToStateMachines()
{
    PSS_StateMachineIterator it(&m_Set);

    for (PSS_StateMachine* pStateMachine = it.GetFirst(); pStateMachine; pStateMachine = it.GetNext())
        pStateMachine->AssignModel(m_pModel);
}
//---------------------------------------------------------------------------
void PSS_StateMachineCollection::RemoveAllObjects()
{
    PSS_StateMachineIterator it(&m_Set);

    for (PSS_StateMachine* pStateMachine = it.GetFirst(); pStateMachine; pStateMachine = it.GetNext())
        delete pStateMachine;

    // remove all elements
    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
