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

// forward class declaration
class ZBSymbol;
class ZBLinkSymbol;
class ZBStateLink;
class ZBStateObject;
class ZBStateMachine;

// scope symbols in stingray foundation library
using namespace sfl;

/**
* ZBSymbol collection
*/
typedef CCArray_T<ZBSymbol*, ZBSymbol*> ZBSymbolSet;

/**
* ZBSymbol collection iterator
*/
typedef Iterator_T<ZBSymbol*> ZBSymbolIterator;

/**
* ZBLinkSymbol collection
*/
typedef CCArray_T<ZBLinkSymbol*, ZBLinkSymbol*> ZBLinkSymbolSet;

/**
* ZBLinkSymbol collection iterator
*/
typedef Iterator_T<ZBLinkSymbol*> ZBLinkSymbolIterator;

/**
* State machine handle collection
*/
typedef CArray<int,int> ZBStateMachineHandleSet;

/**
* ZBStateObject collection
*/
typedef CCArray_T<ZBStateObject*, ZBStateObject*> ZBStateObjectSet;

/**
* ZBStateObject collection iterator
*/
typedef Iterator_T<ZBStateObject*> ZBStateObjectIterator;

/**
* ZBStateMachine collection
*/
typedef CCArray_T<ZBStateMachine*, ZBStateMachine*> ZBStateMachineSet;

/**
* ZBStateMachine collection iterator
*/
typedef Iterator_T<ZBStateMachine*> ZBStateMachineIterator;

/**
* ZBStateLink collection
*/
typedef CCArray_T<ZBStateLink*, ZBStateLink*> ZBStateLinksSet;

/**
* ZBStateLink collection iterator
*/
typedef Iterator_T<ZBStateLink*> ZBStateLinksIterator;

/**
* State machine handle
*/
typedef int StateMachineHandle;

#endif
