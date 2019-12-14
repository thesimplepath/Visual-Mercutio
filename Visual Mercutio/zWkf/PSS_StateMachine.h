/****************************************************************************
 * ==> PSS_StateMachine ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a state machine                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_StateMachineH
#define PSS_StateMachineH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_StateMachine
    #define PSS_StateMachine ZBStateMachine
#endif

// processsoft
#include "zModel\ZBSymbol.h"
#include "PSS_AutomationCollections.h"
#include "PSS_StateObject.h"

// class name mapping
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_LinkSymbol;
class PSS_ProcessGraphModelMdl;

#ifdef _ZWKFEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Provides a state machine
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_StateMachine : public CObject
{
    DECLARE_SERIAL(PSS_StateMachine)

    public:
        /**
        * Constructor
        *@param pModel - model
        */
        PSS_StateMachine(PSS_ProcessGraphModelMdl* pModel = NULL);

        /**
        * Copy constructor
        *@param other - other state machine to copy from
        */
        PSS_StateMachine(const PSS_StateMachine& other);

        virtual ~PSS_StateMachine();

        /**
        * Assignment operator
        *@param other - other state machine to copy from
        *@retrurn itself
        */
        PSS_StateMachine& operator = (const PSS_StateMachine& other);

        /**
        * Clones the state machine
        *@return cloned state machine
        */
        virtual PSS_StateMachine* Clone() const;

        /**
        * Assigns a model
        *@param pModel - model to assign
        */
        virtual void AssignModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Gets the current symbol
        *@return the current symbol
        */
        virtual inline PSS_Symbol* GetCurrentSymbol() const;

        /**
        * Gets the current state object
        *@return the current state object
        */
        virtual inline PSS_StateObject* GetCurrentStateObject() const;

        /**
        * Checks if last object is equals to a state machine
        *@param pStateMachine - state machine to check against the last object
        *@return true if the last object is equal to the state machine, otherwise false
        */
        virtual inline bool IsLastObjectEqual(PSS_StateMachine* pStateMachine) const;

        /**
        * Checks if state machine is equals to another
        *@param pOther - other state machine to compare with
        *@return true if the state machines are equals, otherwise false
        */
        virtual bool IsEqual(PSS_StateMachine* pRight);

        /**
        * Pushes a symbol on the stack
        *@param pSymbol - symbol to push on the stack
        *@param pLinkSymbol - link symbol to push on the stack
        *@param direction - link direction
        */
        virtual void PushSymbol(PSS_Symbol*                    pSymbol,
                                PSS_LinkSymbol*                pLinkSymbol,
                                PSS_StateLink::IELinkDirection direction);

        /**
        * Pushes a symbol on the stack
        *@param pSymbol - symbol to push on the stack
        *@param pStateLink - state link to push on the stack
        */
        virtual void PushSymbol(PSS_Symbol* pSymbol, PSS_StateLink* pStateLink);

        /**
        * Pushes state object on the stack
        *@param pStateObj - state object to push on the stack
        */
        virtual void PushStateObject(PSS_StateObject* pStateObj);

        /**
        * Popes a state object from the stack
        *@param level - level
        *@return stack object
        */
        virtual inline PSS_StateObject* PopStateObject(std::size_t level = 0);

        /**
        * Popes a state object from the stack, but without removing it
        *@param level - level
        *@return stack object
        */
        virtual inline PSS_StateObject* PopStateObjectNoRemove(std::size_t level = 0);

        /**
        * Gets the state objects set
        *@return the state objects set
        */
        virtual inline const PSS_StateObjectSet& GetStateObjectSetConst() const;
        virtual inline       PSS_StateObjectSet& GetStateObjectSet();

        /**
        * Merges all the states
        *@return true on success, otherwise false
        */
        virtual bool MergeAllStates();

        /**
        * Merges a state machine to another
        *@return true on success, otherwise false
        */
        virtual bool Merge(PSS_StateMachine* pRight);

        /**
        * Merges a state machine set to another
        *@return true on success, otherwise false
        */
        virtual bool Merge(PSS_StateMachineSet& setRight);

        /**
        * Serializes the state machine content
        *@param ar - archive in which the content will be serialized
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the state link validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the state link content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    private:
        PSS_StateObjectSet        m_Set;
        PSS_ProcessGraphModelMdl* m_pModel;

        /**
        * Assigns a model to a state object
        */
        void AssignModelToStateObjects();

        /**
        * Removes all the objects
        */
        void RemoveAllObjects();

        /**
        * Adds a state object
        *@param pStateObj - state object to add
        *@return the object count
        */
        int AddStateObject(PSS_StateObject* pStateObj);

        /**
        * Gets the state object count
        *@return the state object count
        */
        inline std::size_t GetStateObjectCount() const;

        /**
        * Popes a state object from the stack
        *@param removeFromStack - if true, object will be removed from stack
        *@param level - level
        *@return stack object
        */
        PSS_StateObject* PopStateObject(bool removeFromStack, std::size_t level);

        /**
        * Gets a state object at index
        *@param index - index
        *@return the state object at index
        */
        inline PSS_StateObject* GetStateObjectAt(std::size_t index);

        /**
        * Removes a state object at index
        *@param index - index
        *@param deleteObject - if true, object will also be deleted
        */
        void RemoveStateObjectAt(std::size_t index, bool deleteObject = true);

        /**
        * Finds a similar object
        *@param pStateObjectToFind - state object to find
        *@return matching index, -1 if not found or on error
        */
        int FindSimilar(PSS_StateObject* pStateObjectToFind);

        /**
        * Merges states
        *@param iLeft - left state index
        *@param iRight - right state index
        *@param deleteRight - if true, right state will be deleted after merged
        *@return true on success, otherwise false
        */
        bool MergeStates(int iLeft, int iRight, bool deleteRight = true);
};

//---------------------------------------------------------------------------
// PSS_StateMachine
//---------------------------------------------------------------------------
PSS_Symbol* PSS_StateMachine::GetCurrentSymbol() const
{
    return (GetCurrentStateObject() ? GetCurrentStateObject()->GetSymbol() : NULL);
}
//---------------------------------------------------------------------------
PSS_StateObject* PSS_StateMachine::GetCurrentStateObject() const
{
    return (GetStateObjectCount() > 0 ? m_Set.GetAt(GetStateObjectCount() - 1) : NULL);
};
//---------------------------------------------------------------------------
bool PSS_StateMachine::IsLastObjectEqual(PSS_StateMachine* pStateMachine) const
{
    return (GetCurrentStateObject() && pStateMachine && pStateMachine->GetCurrentStateObject()) ?
            GetCurrentStateObject()->IsEqual(pStateMachine->GetCurrentStateObject()) : false;
}
//---------------------------------------------------------------------------
PSS_StateObject* PSS_StateMachine::PopStateObject(std::size_t level)
{
    return PopStateObject(true, level);
}
//---------------------------------------------------------------------------
PSS_StateObject* PSS_StateMachine::PopStateObjectNoRemove(std::size_t level)
{
    return PopStateObject(false, level);
}
//---------------------------------------------------------------------------
const PSS_StateObjectSet& PSS_StateMachine::GetStateObjectSetConst() const
{
    return m_Set;
}
//---------------------------------------------------------------------------
PSS_StateObjectSet& PSS_StateMachine::GetStateObjectSet()
{
    return m_Set;
}
//---------------------------------------------------------------------------
std::size_t PSS_StateMachine::GetStateObjectCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------
PSS_StateObject* PSS_StateMachine::GetStateObjectAt(std::size_t index)
{
    return (index < GetStateObjectCount() ? m_Set.GetAt(index) : NULL);
}
//---------------------------------------------------------------------------

#endif
