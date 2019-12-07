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

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// scope symbols in stingray foundation library
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
