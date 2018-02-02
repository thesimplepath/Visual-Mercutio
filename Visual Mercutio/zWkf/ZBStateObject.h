// ZBStateObject.h: interface for the ZBStateObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSTATEOBJECT_H__25BFD0A3_6A6B_4D54_A479_E70548004E60__INCLUDED_)
#define AFX_ZBSTATEOBJECT_H__25BFD0A3_6A6B_4D54_A479_E70548004E60__INCLUDED_

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


#include "ZBStateLink.h"
#include "AutomationCollections.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZDProcessGraphModelMdl;
class ZBSymbol;
class ZBLinkSymbol;
class ZBStateLink;


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




class AFX_EXT_CLASS ZBStateObject : public CObject  
{
	DECLARE_SERIAL(ZBStateObject)

public:
	ZBStateObject(ZBSymbol* pSymbol = NULL, 
				  ZBLinkSymbol* pLinkSymbol = NULL, 
				  ZBStateLink::LinkDirection Direction = ZBStateLink::EnteringUp, 
				  ZDProcessGraphModelMdl* pModel = NULL);
	ZBStateObject(ZBSymbol* pSymbol, 
				  ZBStateLink* pStateLink, 
				  ZDProcessGraphModelMdl* pModel = NULL);
	virtual ~ZBStateObject();
	/* Copy constructor. */
	ZBStateObject(const ZBStateObject& src);
	/* Assignment operator. */
	ZBStateObject& operator=(const ZBStateObject& src);
	/* Create a duplicate copy of this object. */
	virtual ZBStateObject* Clone() const;

	void AssignModel( ZDProcessGraphModelMdl* pModel );

	ZBSymbol* GetpSymbol() const;
	void SetpSymbol( ZBSymbol* value );

	// Return true if the object is equal
	bool IsEqual( ZBStateObject* pRight );

	// Return true if the link exists in the stateobject
	bool Exist( ZBLinkSymbol& LinkSymbol );
	// Return the number of existing edges found in the stateobject
	size_t EdgesExist( CODEdgeArray& Edges );

	ZBStateLinksSet& GetLinkSet()
	{
		return m_Set;
	};
	const ZBStateLinksSet& GetLinkSetConst() const
	{
		return m_Set;
	};
	// Return the counter of state links
	size_t	GetStateLinkCount() const 
	{
		return m_Set.GetSize();
	};
	ZBStateLink* GetStateLinkAt( size_t Index ) const
	{
		return (Index < GetStateLinkCount()) ? m_Set.GetAt(Index) : NULL; 
	};
	void AddLink( ZBLinkSymbol* pLinkSymbol, ZBStateLink::LinkDirection Direction );
	bool RemoveLink( ZBLinkSymbol* pLinkSymbol );
	bool RemoveLink( int ReferenceNumber );
	void RemoveAllLinks();

	/////////////////////////////////////////////////////////////////////////////
	// Merge functions
	bool Merge( ZBStateObject* pRight );
	bool Merge( ZBStateObjectSet& SetRight );

	// Serialization mechanism
	virtual void Serialize(CArchive& ar);   // overridden for document i/o

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


private:
	void AssignModelToStateLinks();
	int  AddStateLink( ZBStateLink* pStateLink );

private:
	ZBSymbol*	m_pSymbol;
	ZBStateLinksSet m_Set;
	ZDProcessGraphModelMdl* m_pModel;


};


inline ZBSymbol* ZBStateObject::GetpSymbol() const 
{
	return m_pSymbol;
}
inline void ZBStateObject::SetpSymbol( ZBSymbol* value )
{
	m_pSymbol = value;
}


#endif // !defined(AFX_ZBSTATEOBJECT_H__25BFD0A3_6A6B_4D54_A479_E70548004E60__INCLUDED_)


