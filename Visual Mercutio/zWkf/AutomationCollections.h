/////////////////////////////////////////////////////////////////////////////
//@doc Collection definition
//@module AutomationCollections.h | Collection and Iterator definition.
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
// <nl>Created:		 06/2001
// <nl>Description:  Collection and Iterator definition
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_AUTOMATIONCOLLECTIONS_H__)
#define AFX_AUTOMATIONCOLLECTIONS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBSymbol;
class ZBLinkSymbol;
class ZBStateLink;
class ZBStateObject;
class ZBStateMachine;


/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;


///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBSymbolSet | An array of ZBSymbol pointers.
//@iex typedef CCArray_T<ZBSymbol*,ZBSymbol*> ZBSymbolSet;
typedef CCArray_T<ZBSymbol*,ZBSymbol*> ZBSymbolSet;

//@type ZBSymbolIterator | An iterator for ZBSymbolSet collections.
//@iex typedef Iterator_T<ZBSymbol*> ZBSymbolIterator;
typedef Iterator_T<ZBSymbol*> ZBSymbolIterator;



//@type ZBLinkSymbolSet | An array of ZBLinkSymbol pointers.
//@iex typedef CCArray_T<ZBLinkSymbol*,ZBLinkSymbol*> ZBLinkSymbolSet;
typedef CCArray_T<ZBLinkSymbol*,ZBLinkSymbol*> ZBLinkSymbolSet;

//@type ZBLinkSymbolIterator | An iterator for ZBLinkSymbolSet collections.
//@iex typedef Iterator_T<ZBLinkSymbol*> ZBLinkSymbolIterator;
typedef Iterator_T<ZBLinkSymbol*> ZBLinkSymbolIterator;


//@type ZBStateMachineHandleSet | An array of int.
//@iex typedef CArray<int,int> ZBStateMachineHandleSet;
typedef CArray<int,int> ZBStateMachineHandleSet;



//@type ZBStateObjectSet | An array of ZBStateObject pointers.
//@iex typedef CCArray_T<ZBStateObject*,ZBStateObject*> ZBStateObjectSet;
typedef CCArray_T<ZBStateObject*,ZBStateObject*> ZBStateObjectSet;

//@type ZBStateObjectIterator | An iterator for ZBStateObjectSet collections.
//@iex typedef Iterator_T<ZBStateObject*> ZBStateObjectIterator;
typedef Iterator_T<ZBStateObject*> ZBStateObjectIterator;




//@type ZBStateMachineSet | An array of ZBStateMachine pointers.
//@iex typedef CCArray_T<ZBStateMachine*,ZBStateMachine*> ZBStateMachineSet;
typedef CCArray_T<ZBStateMachine*,ZBStateMachine*> ZBStateMachineSet;

//@type ZBStateMachineIterator | An iterator for ZBStateMachineSet collections.
//@iex typedef Iterator_T<ZBStateMachine*> ZBStateMachineIterator;
typedef Iterator_T<ZBStateMachine*> ZBStateMachineIterator;



//@type ZBStateLinksSet | An array of ZBStateLink pointers.
//@iex typedef CCArray_T<ZBStateLink*,ZBStateLink*> ZBStateLinksSet;
typedef CCArray_T<ZBStateLink*,ZBStateLink*> ZBStateLinksSet;

//@type ZBStateLinksIterator | An iterator for ZBStateLinksSet collections.
//@iex typedef Iterator_T<ZBStateLink*> ZBStateLinksIterator;
typedef Iterator_T<ZBStateLink*> ZBStateLinksIterator;



///////////////////////////////////////////////////////////////////////////
// Typedef definitions

//@type StateMachineHandle | the handle of a state machine.
typedef int StateMachineHandle;


#endif // !defined(AFX_AUTOMATIONCOLLECTIONS_H__)
