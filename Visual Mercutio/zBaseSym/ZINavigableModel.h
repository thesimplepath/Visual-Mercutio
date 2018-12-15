/////////////////////////////////////////////////////////////////////////////
//@doc ZINavigableModel
//@module ZINavigableModel.h | Interface of the <c ZINavigableModel> class.
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
// <nl>Description:  ZINavigableModel interface for model navigation
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZINAVIGABLEMODEL_H__97337226_74E0_4713_B3F9_60E67DA8060F__INCLUDED_)
#define AFX_ZINAVIGABLEMODEL_H__97337226_74E0_4713_B3F9_60E67DA8060F__INCLUDED_

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


//////////////////////////////////////////////////////////////////////
// Forward declaration



#ifdef _ZBASESYMEXPORT
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



class AFX_EXT_CLASS ZINavigableModel  
{
public:
    ZINavigableModel();
    virtual ~ZINavigableModel();

    // Methods to obtain start symbols
    virtual size_t GetStartSymbols( CODNodeArray& Nodes, bool Deep = false ) = 0;

};

#endif // !defined(AFX_ZINAVIGABLEMODEL_H__97337226_74E0_4713_B3F9_60E67DA8060F__INCLUDED_)
