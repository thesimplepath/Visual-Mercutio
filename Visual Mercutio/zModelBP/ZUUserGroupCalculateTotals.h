/////////////////////////////////////////////////////////////////////////////
//@doc ZUUserGroupCalculateTotals
//@module ZUUserGroupCalculateTotals.h | Interface of the <c ZUUserGroupCalculateTotals> class.
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
// <nl>Created:		 07/2001
// <nl>Description:  ZUUserGroupCalculateTotals navigates through the process and
//					 write process information to the grid
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUUserGroupCalculateTotals_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUUserGroupCalculateTotals_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "ZUProcessNavigation.h"
#include "ZBBPAnnualNumberProp.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBUserGroupEntity;

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 9 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZBUserGroupCalculateTotalsInformation

class AFX_EXT_CLASS ZBUserGroupCalculateTotalsInformation
{
public:

	ZBUserGroupCalculateTotalsInformation( bool Consolidated, ZBUserGroupEntity* pGroup = NULL )
	{
		m_Consolidated	= Consolidated;
		m_pGroup		= pGroup;
	};

	virtual ~ZBUserGroupCalculateTotalsInformation()
	{
	};

public:

	bool				m_Consolidated;
	ZBUserGroupEntity*	m_pGroup;
};

/////////////////////////////////////////////////////////////////////////////
// ZBUserGroupCalculateTotalsInformation

class _ZBUserGroupTotal
{
public:
	_ZBUserGroupTotal( const CString GroupName = _T( "" ) )
		: m_GroupName( GroupName )
	{
		m_ProcedureCost					= 0;
		m_ProcedureWorkloadForecast		= 0;
		m_ProcedureCostForecast			= 0;
		m_ProcedureWorkloadPerActivity	= 0;
		m_ProcedureCostPerActivity		= 0;
	};

	virtual ~_ZBUserGroupTotal()
	{
	};

public:

	CString						m_GroupName;
	ZBBPAnnualNumberProperties	m_ProcedureCost;
	ZBBPAnnualNumberProperties	m_ProcedureWorkloadForecast;
	ZBBPAnnualNumberProperties	m_ProcedureCostForecast;
	double						m_ProcedureWorkloadPerActivity;
	double						m_ProcedureCostPerActivity;
};

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBUserGroupTotalSet | An array of _ZBUserGroupTotal pointers.
//@iex typedef CCArray_T<_ZBUserGroupTotal*,_ZBUserGroupTotal*> ZBUserGroupTotalSet;
typedef CCArray_T<_ZBUserGroupTotal*, _ZBUserGroupTotal*> ZBUserGroupTotalSet;

//@type ZBUserGroupTotalIterator | An iterator for ZBUserGroupTotalSet collections.
//@iex typedef Iterator_T<_ZBUserGroupTotal*> ZBUserEntityIterator;
typedef Iterator_T<_ZBUserGroupTotal*> ZBUserGroupTotalIterator;

/////////////////////////////////////////////////////////////////////////////
// ZUUserGroupCalculateTotals

class AFX_EXT_CLASS ZUUserGroupCalculateTotals : public ZUProcessNavigation
{
public:

	ZUUserGroupCalculateTotals( ZDProcessGraphModelMdl* pModel = NULL, void* pClass = NULL );
	virtual ~ZUUserGroupCalculateTotals();

	ZBBPAnnualNumberProperties* GetProcedureCost( const CString GroupName );
	ZBBPAnnualNumberProperties* GetProcedureWorkloadForecast( const CString GroupName );
	ZBBPAnnualNumberProperties* GetProcedureCostForecast( const CString GroupName );
	double GetProcedureWorkloadPerActivity( const CString GroupName ) const;
	double GetProcedureCostPerActivity( const CString GroupName ) const;

	// Call-back methods
	virtual bool OnStart();
	virtual bool OnFinish();
	virtual bool OnProcedureSymbol( ZBBPProcedureSymbol* pSymbol );


private:

	void AddProcedureToTotal( ZBBPProcedureSymbol* pSymbol, _ZBUserGroupTotal& Total );
	void CreateInitialGroupSet();
	void EmptySet();
	_ZBUserGroupTotal* FindTotal( const CString GroupName );

private:

	CString				m_UnitName;
	bool				m_Consolidated;
	ZBUserGroupEntity*	m_pGroup;
	ZBUserGroupTotalSet	m_TotalSet;
};

#endif // !defined(AFX_ZUUserGroupCalculateTotals_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)