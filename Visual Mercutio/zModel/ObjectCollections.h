/////////////////////////////////////////////////////////////////////////////
//@doc Collection definition
//@module ObjectCollections.h | Collection and Iterator definition.
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
// <nl>Created:         02/2002
// <nl>Description:  Collection and Iterator definition
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(_OBJECTCOLLECTIONS_H__)
#define _OBJECTCOLLECTIONS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBRuntimeClassSet | An array of ZBRuntimeClass pointers.
//@iex typedef CCArray_T<ZBRuntimeClass*,ZBRuntimeClass*> ZBRuntimeClassSet;
typedef CCArray_T<const CRuntimeClass*, const CRuntimeClass*> ZBRuntimeClassSet;

//@type ZBRuntimeClassIterator | An iterator for ZBRuntimeClassSet collections.
//@iex typedef Iterator_T<ZBRuntimeClass*> ZBRuntimeClassIterator;
typedef Iterator_T<const CRuntimeClass*> ZBRuntimeClassIterator;

#endif // !defined(_OBJECTCOLLECTIONS_H__)