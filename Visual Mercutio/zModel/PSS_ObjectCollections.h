/****************************************************************************
 * ==> PSS_ObjectCollections -----------------------------------------------*
 ****************************************************************************
 * Description : Provides object collections and iterators                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ObjectCollectionsH
#define PSS_ObjectCollectionsH

#if _MSC_VER > 1000
    #pragma once
#endif

using namespace sfl;

/**
* Runtime class collection
*/
typedef CCArray_T<const CRuntimeClass*, const CRuntimeClass*> PSS_RuntimeClassSet;

/**
* Runtime class collection iterator
*/
typedef Iterator_T<const CRuntimeClass*> PSS_RuntimeClassIterator;

#endif
