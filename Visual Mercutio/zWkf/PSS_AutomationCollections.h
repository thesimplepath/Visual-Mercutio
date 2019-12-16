/****************************************************************************
 * ==> PSS_AutomationCollections -------------------------------------------*
 ****************************************************************************
 * Description : Defines the automation collections and iterators           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_AutomationCollectionsH
#define PSS_AutomationCollectionsH

#if _MSC_VER > 1000
    #pragma once
#endif

#include "StdAfx.h"

 // class name mapping
#ifndef PSS_Symbol
    #define PSS_Symbol ZBSymbol
#endif
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif
#ifndef PSS_StateObject
    #define PSS_StateObject ZBStateObject
#endif
#ifndef PSS_StateMachine
    #define PSS_StateMachine ZBStateMachine
#endif
#ifndef PSS_StateLink
    #define PSS_StateLink ZBStateLink
#endif

// forward class declaration
class PSS_Symbol;
class PSS_LinkSymbol;
class PSS_StateObject;
class PSS_StateMachine;
class PSS_StateLink;

// scope symbols in stingray foundation library
using namespace sfl;

/**
* PSS_Symbol collection
*/
typedef CCArray_T<PSS_Symbol*, PSS_Symbol*> PSS_SymbolSet;

/**
* PSS_Symbol collection iterator
*/
typedef Iterator_T<PSS_Symbol*> PSS_SymbolIterator;

/**
* PSS_LinkSymbol collection
*/
typedef CCArray_T<PSS_LinkSymbol*, PSS_LinkSymbol*> PSS_LinkSymbolSet;

/**
* PSS_LinkSymbol collection iterator
*/
typedef Iterator_T<PSS_LinkSymbol*> PSS_LinkSymbolIterator;

/**
* State machine handle collection
*/
typedef CArray<std::intptr_t, std::intptr_t> PSS_StateMachineHandleSet;

/**
* ZBStateObject collection
*/
typedef CCArray_T<PSS_StateObject*, PSS_StateObject*> PSS_StateObjectSet;

/**
* ZBStateObject collection iterator
*/
typedef Iterator_T<PSS_StateObject*> PSS_StateObjectIterator;

/**
* ZBStateMachine collection
*/
typedef CCArray_T<PSS_StateMachine*, PSS_StateMachine*> PSS_StateMachineSet;

/**
* ZBStateMachine collection iterator
*/
typedef Iterator_T<PSS_StateMachine*> PSS_StateMachineIterator;

/**
* PSS_StateLink collection
*/
typedef CCArray_T<PSS_StateLink*, PSS_StateLink*> PSS_StateLinksSet;

/**
* PSS_StateLink collection iterator
*/
typedef Iterator_T<PSS_StateLink*> PSS_StateLinksIterator;

/**
* State machine handle
*/
typedef std::intptr_t PSS_StateMachineHandle;

#endif
