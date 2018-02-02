// ZIBasicSymbolAcceptVisitor.h: interface for the ZIBasicSymbolAcceptVisitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZIBASICSYMBOLACCEPTVISITOR_H__05928EFC_242B_431A_929E_1AA99167F242__INCLUDED_)
#define AFX_ZIBASICSYMBOLACCEPTVISITOR_H__05928EFC_242B_431A_929E_1AA99167F242__INCLUDED_

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


// Forward declaration
class ZIBasicSymbolVisitor;



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

//////////////////////////////////////////////////////////////////////
// ZIBasicSymbolAcceptVisitor
// Define the basic interface for accepting Visitors
//

class AFX_EXT_CLASS ZIBasicSymbolAcceptVisitor  
{
public:
	ZIBasicSymbolAcceptVisitor();
	virtual ~ZIBasicSymbolAcceptVisitor();

	/* AcceptVisitor method let the object be visited
	   by concreted derived ZIBasicSymbolVisitor classes */
	virtual bool AcceptVisitor( ZIBasicSymbolVisitor& Visitor ) = 0;

};

#endif // !defined(AFX_ZIBASICSYMBOLACCEPTVISITOR_H__05928EFC_242B_431A_929E_1AA99167F242__INCLUDED_)
