// ZUDatabaseManipulator.cpp: implementation of the ZUDatabaseManipulator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUDatabaseManipulator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUDatabaseManipulator::ZUDatabaseManipulator(const CString Databasename /*= ""*/, DatabaseType tp /*= MSAccess*/)
: m_Databasename(Databasename), m_tp(tp)
{

}

ZUDatabaseManipulator::~ZUDatabaseManipulator()
{

}


bool ZUDatabaseManipulator::CreateDatabase()
{
    return true;
}

bool ZUDatabaseManipulator::GetTableList( CStringArray& TableArray )
{
    return true;
}

