// ZBUnitManager.cpp: implementation of the ZBUnitManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBUnitManager.h"
#include "ProcGraphModelDoc.h"
#include "ZBModelSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(ZBUnitManager, CObject, def_Version)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBUnitManager::ZBUnitManager(ZDProcessModelDocTmpl* pDocTmpl)
: m_pDocTmpl(pDocTmpl)
{

}

ZBUnitManager::~ZBUnitManager()
{
	UnloadAllUnits();
}

void	ZBUnitManager::Initialize(ZDProcessModelDocTmpl* pDocTmpl)
{
	m_pDocTmpl = pDocTmpl;
}


size_t	ZBUnitManager::FillModelSet( ZBModelSet& Set )
{
	Set.RemoveAllModel();
	for (size_t i = 0; i < GetUnitCount(); ++i)
	{
		ZBUnit*	pU = GetUnitAt( i );
		if (pU && pU->GetUnitDocumentPtr()->GetModel())
			Set.AddModel( pU->GetUnitDocumentPtr()->GetModel() );
	}
	return Set.GetModelCount();
}

// Load and Unload unit functions

bool	ZBUnitManager::LoadAllUnits()
{
	// No document template, error
	if (!m_pDocTmpl)
		return false;

	bool	ContainsError = false;
	for (size_t i = 0; i < GetUnitCount(); ++i)
	{
		ZBUnit*	pU = GetUnitAt( i );
		if (!pU->LoadUnit( m_pDocTmpl ))
		{
			ContainsError = true;
		}
	}
	return ContainsError;
}

bool	ZBUnitManager::LoadUnit( ZBUnit* pUnit )
{
	// No document template, error
	if (!m_pDocTmpl)
		return false;
	return pUnit->LoadUnit( m_pDocTmpl );
}

bool	ZBUnitManager::LoadUnit( const CString Name )
{
	// No document template, error
	if (!m_pDocTmpl)
		return false;

	ZBUnit*	pU = FindUnit( Name );
	if (pU)
		return pU->LoadUnit( m_pDocTmpl );
	return false;
}

bool	ZBUnitManager::LoadUnitByKey( const CString Key )
{
	// No document template, error
	if (!m_pDocTmpl)
		return false;

	ZBUnit*	pU = FindUnitByKey( Key );
	if (pU)
		return pU->LoadUnit( m_pDocTmpl );
	return false;
}


bool	ZBUnitManager::UnloadAllUnits()
{
	bool	ContainsError = false;
	for (size_t i = 0; i < GetUnitCount(); ++i)
	{
		ZBUnit*	pU = GetUnitAt( i );
		if (!pU->UnloadUnit())
		{
			ContainsError = true;
		}
	}
	return ContainsError;
}

bool	ZBUnitManager::UnloadUnit( ZBUnit* pUnit )
{
	return pUnit->UnloadUnit();
}

bool	ZBUnitManager::UnloadUnit( const CString Name )
{
	ZBUnit*	pU = FindUnit( Name );
	if (pU)
		return pU->UnloadUnit();
	return false;
}

bool	ZBUnitManager::UnloadUnitByKey( const CString Key )
{
	ZBUnit*	pU = FindUnitByKey( Key );
	if (pU)
		return pU->UnloadUnit();
	return false;
}



// UnitSet management

void	ZBUnitManager::RemoveAllUnits()
{
	m_UnitSet.RemoveAll();
}


bool	ZBUnitManager::RemoveUnitAt( size_t Index )
{
	if (Index < GetUnitCount())
	{
		m_UnitSet.RemoveAt( Index );
		return true;
	}
	return false;
}

bool	ZBUnitManager::RemoveUnit( ZBUnit* pUnit )
{
	for (size_t i = 0; i < GetUnitCount(); ++i)
	{
		ZBUnit*	pU = GetUnitAt( i );
		if (pU == pUnit)
		{
			RemoveUnitAt( i );
			return true;
		}
	}
	return false;
}

bool	ZBUnitManager::RemoveUnit( const CString Name )
{
	for (size_t i = 0; i < GetUnitCount(); ++i)
	{
		ZBUnit*	pU = GetUnitAt( i );
		if (pU->GetName() == Name)
		{
			RemoveUnitAt( i );
			return true;
		}
	}
	return false;
}

bool	ZBUnitManager::RemoveUnitByKey( const CString Key )
{
	for (size_t i = 0; i < GetUnitCount(); ++i)
	{
		ZBUnit*	pU = GetUnitAt( i );
		if (pU->GetKey() == Key)
		{
			RemoveUnitAt( i );
			return true;
		}
	}
	return false;
}


ZBUnit*	ZBUnitManager::FindUnit( const CString Name )
{
	for (size_t i = 0; i < GetUnitCount(); ++i)
	{
		ZBUnit*	pU = GetUnitAt( i );
		if (pU->GetName() == Name)
			return pU;
	}
	return NULL;
}


ZBUnit*	ZBUnitManager::FindUnitByKey( const CString Key )
{
	for (size_t i = 0; i < GetUnitCount(); ++i)
	{
		ZBUnit*	pU = GetUnitAt( i );
		if (pU->GetKey() == Key)
			return pU;
	}
	return NULL;
}


int	ZBUnitManager::FindUnitIndex( const CString Name )
{
	for (size_t i = 0; i < GetUnitCount(); ++i)
	{
		ZBUnit*	pU = GetUnitAt( i );
		if (pU->GetName() == Name)
			return (int)i;
	}
	return -1;
}

int	ZBUnitManager::FindUnitIndexByKey( const CString Key )
{
	for (size_t i = 0; i < GetUnitCount(); ++i)
	{
		ZBUnit*	pU = GetUnitAt( i );
		if (pU->GetKey() == Key)
			return (int)i;
	}
	return -1;

}

ZBUnit*	ZBUnitManager::GetUnitAt( size_t Index )
{
	if (Index < GetUnitCount())
		return (ZBUnit*)m_UnitSet.GetAt( Index );
	return NULL;
}

bool	ZBUnitManager::AddUnit( ZBUnit* pUnit )
{
	size_t	PreviousCount = GetUnitCount();
	m_UnitSet.Add( pUnit );
	return GetUnitCount() > PreviousCount;
}

ZBUnit*	ZBUnitManager::CreateNewUnit( const CString Name, const CString Filename /*= ""*/ )
{
	ZBUnit*	pNewUnit = new ZBUnit;
	if (!pNewUnit->Create( Name, Filename ))
	{
		delete pNewUnit;
		pNewUnit = NULL;
	}
	if (!AddUnit( pNewUnit ))
	{
		delete pNewUnit;
		pNewUnit = NULL;
	}

	return pNewUnit;
}


// Serializes the unit
void ZBUnitManager::Serialize(CArchive& ar)
{
	m_UnitSet.Serialize( ar );
}
