/****************************************************************************
 * ==> PSS_StateMachineCollection ------------------------------------------*
 ****************************************************************************
 * Description : Provides a collection which keeps the complete state of a  *
 *               model                                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_StateMachineCollectionH
#define PSS_StateMachineCollectionH

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

// processsoft
#include "PSS_AutomationCollections.h"
#include "PSS_StateLink.h"

// forward class declaration
class PSS_StateMachine;
class PSS_StateObject;
class ZBSymbol;
class ZBLinkSymbol;
class ZDProcessGraphModelMdl;

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
* Provides a collection which keeps the complete state of a model
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_StateMachineCollection : public CObject
{
    DECLARE_SERIAL(PSS_StateMachineCollection)

public:
    /**
    * Constructor
    *@param pModel - model for which state collection should be created
    */
    PSS_StateMachineCollection(ZDProcessGraphModelMdl* pModel = NULL);

    /**
    * Copy constructor
    *@param other - other state collection to copy from
    */
    PSS_StateMachineCollection(const PSS_StateMachineCollection& other);

    virtual ~PSS_StateMachineCollection();

    /**
    * Assignment operator
    *@param other - other state collection to copy from
    */
    PSS_StateMachineCollection& operator = (const PSS_StateMachineCollection& other);

    /**
    * Clones the state model collection
    *@return cloned state model collection
    */
    virtual PSS_StateMachineCollection* Clone() const;

    /**
    * Assigns a model
    *@param pModel - model to assign
    */
    virtual void AssignModel(ZDProcessGraphModelMdl* pModel);

    /**
    * Creates a new state machine
    *@param pSymbol - symbol
    *@param pLinkSymbol - link symbol
    *@param directiopn - link direction
    *@return newly created state machine handle, -1 on error
    */
    virtual PSS_StateMachineHandle CreateNewStateMachine(ZBSymbol*                      pSymbol,
                                                         ZBLinkSymbol*                  pLinkSymbol,
                                                         PSS_StateLink::IELinkDirection direction = PSS_StateLink::IE_LD_UnknownDirection);

    /**
    * Creates a new state machine
    *@param pStateObj - state object
    *@return newly created state machine handle, -1 on error
    */
    virtual PSS_StateMachineHandle CreateNewStateMachine(PSS_StateObject* pStateObj);

    /**
    * Deletes an existing state machine
    *@return true is on success, otherwise false
    */
    virtual bool DeleteStateMachine(PSS_StateMachineHandle hStateMachine);

    /**
    * Deletes all existing state machines
    */
    virtual inline void DeleteAllStateMachines();

    /**
    * Gets the current component of an existing state machine
    *@param hStateMachine - state machine handle
    *@return the component, NULL if not found or on error
    */
    virtual ZBSymbol* GetCurrentStateMachineSymbol(PSS_StateMachineHandle hStateMachine);

    /**
    * Gets the current state object of an existing state machine
    *@param hStateMachine - state machine handle
    *@return the state machine object, NULL if not found or on error
    */
    virtual PSS_StateObject* GetCurrentStateMachineObject(PSS_StateMachineHandle hStateMachine);

    /**
    * Pushes a new symbol to an existing state machine
    *@param hStateMachine - state machine handle
    *@param pSymbol - symbol
    *@param pLinkSymbol - link symbol
    *@return true on success, otherwise false
    */
    virtual bool PushSymbol(PSS_StateMachineHandle         hStateMachine,
                            ZBSymbol*                      pSymbol,
                            ZBLinkSymbol*                  pLinkSymbol,
                            PSS_StateLink::IELinkDirection direction = PSS_StateLink::IE_LD_UnknownDirection);

    /**
    * Pushes a new state object to an existing state machine
    *@param hStateMachine - state machine handle
    *@param pStateObj- state object
    *@return true on success, otherwise false
    */
    virtual bool PushStateObject(PSS_StateMachineHandle hStateMachine, PSS_StateObject* pStateObj);

    /**
    * Copies only the current state object of each source machine state
    *@param src - source state machine collection to copy from
    *@param mergeObjectsFirst - if true the objects will be merged first
    *@return true on success, otherwise false
    */
    virtual bool CopyCurrentStateObjects(const PSS_StateMachineCollection& src, bool mergeObjectsFirst = false);

    /**
    * Gets the state machine count
    *@return the state machine count
    */
    virtual inline std::size_t GetStateMachineCount() const;

    /**
    * Adds a new state machine
    *@param pStateMachine - state machine to add
    *@return newly added state machine index
    */
    virtual int AddStateMachine(PSS_StateMachine* pStateMachine);

    /**
    * Gets the machine set to use with the iterator
    *@return iterator
    */
    virtual inline       PSS_StateMachineSet& GetStateMachineSet();
    virtual inline const PSS_StateMachineSet& GetStateMachineSetConst() const;

    /**
    * Gets a state machine
    *@param hStateMachine - state machine handle to get
    *@return the state machine, NULL if not found or on error
    */
    virtual inline PSS_StateMachine* GetStateMachine(PSS_StateMachineHandle hStateMachine);

    /**
    * Serializes the state machine collection
    *@param ar - archive in which the content will be serialized
    */
    virtual void Serialize(CArchive& ar);

    /**
    * Asserts the state machine collection validity
    */
    #ifdef _DEBUG
        virtual void AssertValid() const;
    #endif

    /**
    * Dumps the state machine collection content
    *@param dc - dump context
    */
    #ifdef _DEBUG
        virtual void Dump(CDumpContext& dc) const;
    #endif

private:
    PSS_StateMachineSet     m_Set;
    ZDProcessGraphModelMdl* m_pModel;

    /**
    * Assigns the model to the state machine
    */
    void AssignModelToStateMachines();

    /**
    * Removes all the objects
    */
    void RemoveAllObjects();
};

//---------------------------------------------------------------------------
// PSS_StateMachineCollection
//---------------------------------------------------------------------------
void PSS_StateMachineCollection::DeleteAllStateMachines()
{
    RemoveAllObjects();
}
//---------------------------------------------------------------------------
std::size_t PSS_StateMachineCollection::GetStateMachineCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------
PSS_StateMachineSet& PSS_StateMachineCollection::GetStateMachineSet()
{
    return m_Set;
}
//---------------------------------------------------------------------------
const PSS_StateMachineSet& PSS_StateMachineCollection::GetStateMachineSetConst() const
{
    return m_Set;
}
//---------------------------------------------------------------------------
PSS_StateMachine* PSS_StateMachineCollection::GetStateMachine(PSS_StateMachineHandle hStateMachine)
{
    return (hStateMachine < int(GetStateMachineCount()) ? m_Set.GetAt(hStateMachine) : NULL);
}
//---------------------------------------------------------------------------

#endif
