// ZBStateMachine.h: interface for the ZBStateMachine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSTATEMACHINE_H__CADE0EBB_8D70_4D36_9A55_E9D36691ED30__INCLUDED_)
#define AFX_ZBSTATEMACHINE_H__CADE0EBB_8D70_4D36_9A55_E9D36691ED30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZBStateObject.h"
#include "zModel\ZBSymbol.h"
#include "AutomationCollections.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
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

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS



class AFX_EXT_CLASS ZBStateMachine : public CObject  
{
	DECLARE_SERIAL(ZBStateMachine)

public:
	ZBStateMachine(ZDProcessGraphModelMdl* pModel = NULL);
	virtual ~ZBStateMachine();
	/* Copy constructor. */
	ZBStateMachine(const ZBStateMachine& src);
	/* Assignment operator. */
	ZBStateMachine& operator=(const ZBStateMachine& src);
	/* Create a duplicate copy of this object. */
	virtual ZBStateMachine* Clone() const;

	void AssignModel( ZDProcessGraphModelMdl* pModel );
	// Get the current symbol
	ZBSymbol* GetCurrentSymbol() const
	{
		return (GetCurrentStateObject()) ? GetCurrentStateObject()->GetpSymbol(): NULL;
	};
	// Get the current state object
	ZBStateObject* GetCurrentStateObject() const
	{
		return (GetStateObjectCount() > 0) ? m_Set.GetAt( GetStateObjectCount()-1 ) : NULL;
	};
	// Return true if the last element is equal 
	bool IsLastObjectEqual( ZBStateMachine* pStateMachine ) const
	{
		return (GetCurrentStateObject() && 
			    pStateMachine &&
				pStateMachine->GetCurrentStateObject()) ?
					GetCurrentStateObject()->IsEqual( pStateMachine->GetCurrentStateObject() ) :
					false;
	}
	// Return true if the object is equal
	bool IsEqual( ZBStateMachine* pRight );

	///////////////////////////////////////////////////////////////////////////
	// Stack functions
	void PushSymbol( ZBSymbol* pSymbol, ZBLinkSymbol* pLinkSymbol, ZBStateLink::LinkDirection Direction );
	void PushSymbol( ZBSymbol* pSymbol, ZBStateLink* pStateLink );
	void PushStateObject( ZBStateObject* pStateObj );
	ZBStateObject* PopStateObject( size_t Level = 0 )
	{
		return _PopStateObject( true, Level );
	};
	ZBStateObject* PopStateObjectNoRemove( size_t Level = 0 )
	{
		return _PopStateObject( false, Level );
	};

	ZBStateObjectSet& GetStateObjectSet()
	{
		return m_Set;
	};
	const ZBStateObjectSet& GetStateObjectSetConst() const
	{
		return m_Set;
	};

	/////////////////////////////////////////////////////////////////////////////
	// Merge functions
	bool MergeAllStates();
	bool Merge( ZBStateMachine* pRight );
	bool Merge( ZBStateMachineSet& SetRight );

	/////////////////////////////////////////////////////////////////////////////
	// Serialization mechanism
	virtual void Serialize(CArchive& ar);   // overridden for document i/o

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	void AssignModelToStateObjects();
	void RemoveAllObjects();
	int AddStateObject( ZBStateObject* pStateObj );
	// Return the counter of state objects
	size_t	GetStateObjectCount() const 
	{
		return m_Set.GetSize();
	};
	ZBStateObject* _PopStateObject( bool RemoveFromStack, size_t Level );
	// Return the state object at a specific index
	ZBStateObject* GetStateObjectAt( size_t Index )
	{
		return (Index < GetStateObjectCount()) ? m_Set.GetAt(Index) : NULL;
	};
	void RemoveStateObjectAt( size_t Index, bool DeleteObject = true);

	int FindSimilar( ZBStateObject* pStateObjectToFind );
	bool MergeStates( int iLeft, int iRight, bool DeleteRight = true );

private:
	ZBStateObjectSet m_Set;
	ZDProcessGraphModelMdl* m_pModel;

};

#endif // !defined(AFX_ZBSTATEMACHINE_H__CADE0EBB_8D70_4D36_9A55_E9D36691ED30__INCLUDED_)
