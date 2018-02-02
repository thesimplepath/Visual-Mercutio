// ZINavigableSymbol.h: interface for the ZINavigableSymbol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZINavigableSymbol_H__3DBD0DC6_C74C_441F_A678_987A08ECEDF6__INCLUDED_)
#define AFX_ZINavigableSymbol_H__3DBD0DC6_C74C_441F_A678_987A08ECEDF6__INCLUDED_

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

class AFX_EXT_CLASS ZINavigableSymbol  
{
public:
	ZINavigableSymbol();
	virtual ~ZINavigableSymbol();

	// All methods to obtain following symbols
	virtual size_t GetFollowingSymbols( CODNodeArray& Nodes ) = 0;
	virtual size_t GetFollowingSymbols_Right( CODNodeArray& Nodes ) = 0;
	virtual size_t GetFollowingSymbols_Left( CODNodeArray& Nodes ) = 0;
	virtual size_t GetFollowingSymbols_Up( CODNodeArray& Nodes ) = 0;
	virtual size_t GetFollowingSymbols_Down( CODNodeArray& Nodes ) = 0;

	// All methods to obtain following symbols
	virtual size_t GetEnteringSymbols( CODNodeArray& Nodes ) = 0;
	virtual size_t GetEnteringSymbols_Right( CODNodeArray& Nodes ) = 0;
	virtual size_t GetEnteringSymbols_Left( CODNodeArray& Nodes ) = 0;
	virtual size_t GetEnteringSymbols_Up( CODNodeArray& Nodes ) = 0;
	virtual size_t GetEnteringSymbols_Down( CODNodeArray& Nodes ) = 0;

	// All methods to obtain leaving links
	virtual size_t GetEdgesLeaving( CODEdgeArray& Edges ) = 0;
	virtual size_t GetEdgesLeaving_Right( CODEdgeArray& Edges ) = 0;
	virtual size_t GetEdgesLeaving_Left( CODEdgeArray& Edges ) = 0;
	virtual size_t GetEdgesLeaving_Up( CODEdgeArray& Edges ) = 0;
	virtual size_t GetEdgesLeaving_Down( CODEdgeArray& Edges ) = 0;

	// All methods to obtain entering links
	virtual size_t GetEdgesEntering( CODEdgeArray& Edges ) = 0;
	virtual size_t GetEdgesEntering_Right( CODEdgeArray& Edges ) = 0;
	virtual size_t GetEdgesEntering_Left( CODEdgeArray& Edges ) = 0;
	virtual size_t GetEdgesEntering_Up( CODEdgeArray& Edges ) = 0;
	virtual size_t GetEdgesEntering_Down( CODEdgeArray& Edges ) = 0;

};

#endif // !defined(AFX_ZINavigableSymbol_H__3DBD0DC6_C74C_441F_A678_987A08ECEDF6__INCLUDED_)
