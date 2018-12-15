/////////////////////////////////////////////////////////////////////////////
//@doc ZBStateMachineCollection
//@module ZBStateMachineCollection.h | Interface of the <c ZBStateMachineCollection> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:         06/2001
// <nl>Description:  ZBStateMachineCollection keeps the complete state of a model
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBStateMachineCollection_H__4D4782D2_413C_43FA_94DA_D4F56D3AEADE__INCLUDED_)
#define AFX_ZBStateMachineCollection_H__4D4782D2_413C_43FA_94DA_D4F56D3AEADE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "ZBStateLink.h"
#include "AutomationCollections.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBStateMachine;
class ZBStateObject;
class ZBSymbol;
class ZBLinkSymbol;
class ZDProcessGraphModelMdl;

#ifdef _ZWKFEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR- MODIF - Le 20 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBStateMachineCollection : public CObject
{
    DECLARE_SERIAL( ZBStateMachineCollection )

public:

    ZBStateMachineCollection( ZDProcessGraphModelMdl* pModel = NULL );
    virtual ~ZBStateMachineCollection();

    /* Copy constructor. */
    ZBStateMachineCollection( const ZBStateMachineCollection& src );

    /* Assignment operator. */
    ZBStateMachineCollection& operator=( const ZBStateMachineCollection& src );

    /* Create a duplicate copy of this object. */
    virtual ZBStateMachineCollection* Clone() const;

    // Assigns a model
    void AssignModel( ZDProcessGraphModelMdl* pModel );

    // Create a new state machine
    // returns the StateMachineHandle, or -1 if an error occured
    StateMachineHandle CreateNewStateMachine( ZBSymbol*                        pSymbol,
                                              ZBLinkSymbol*                    pLinkSymbol,
                                              ZBStateLink::LinkDirection    Direction = ZBStateLink::LinkDirection::UnknownDirection );

    StateMachineHandle CreateNewStateMachine( ZBStateObject* pStateObj );

    // Delete an existing state machine
    // returns true is successfully deleted
    bool DeleteStateMachine( StateMachineHandle hStateMachine );

    // Delete all existing state machines
    void DeleteAllStateMachines()
    {
        RemoveAllObjects();
    };

    // Retreive the current component of an existing state machine
    // returns the component if ok, otherwise NULL
    ZBSymbol* GetCurrentStateMachineSymbol( StateMachineHandle hStateMachine );

    // Retreive the current state object of an existing state machine
    // returns the state object if ok, otherwise NULL
    ZBStateObject* GetCurrentStateMachineObject( StateMachineHandle hStateMachine );

    // Push a new symbol to an existing state machine
    // return true if the symbol has been correctly pushed in the state machine
    bool PushSymbol( StateMachineHandle            hStateMachine,
                     ZBSymbol*                    pSymbol,
                     ZBLinkSymbol*                pLinkSymbol,
                     ZBStateLink::LinkDirection    Direction = ZBStateLink::LinkDirection::UnknownDirection );

    // Push a new state object to an existing state machine
    // return true if the symbol has been correctly pushed in the state machine
    bool PushStateObject( StateMachineHandle hStateMachine, ZBStateObject* pStateObj );

    // Copy only the current state object of each source machine state
    bool CopyCurrentStateObjects( const ZBStateMachineCollection& src, bool MergeObjectsFirst = false );

    // Return the counter of state machines
    size_t    GetStateMachineCount() const
    {
        return m_Set.GetSize();
    };

    // Add a new state machine
    int AddStateMachine( ZBStateMachine* pStateMachine );

    // Get the machine set to use with the iterator
    ZBStateMachineSet& GetStateMachineSet()
    {
        return m_Set;
    };

    const ZBStateMachineSet& GetStateMachineSetConst() const
    {
        return m_Set;
    };

    ZBStateMachine* GetStateMachine( StateMachineHandle hStateMachine )
    {
        return ( hStateMachine < (int)GetStateMachineCount() ) ? m_Set.GetAt( hStateMachine ) : NULL;
    };

    // Serialization mechanism
    virtual void Serialize( CArchive& ar );    // overridden for document i/o

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

private:

    void AssignModelToStateMachines();
    void RemoveAllObjects();

private:

    ZBStateMachineSet        m_Set;
    ZDProcessGraphModelMdl*    m_pModel;
};

#endif // !defined(AFX_ZBStateMachineCollection_H__4D4782D2_413C_43FA_94DA_D4F56D3AEADE__INCLUDED_)