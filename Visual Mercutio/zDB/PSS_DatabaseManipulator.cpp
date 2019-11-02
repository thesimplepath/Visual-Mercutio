/****************************************************************************
 * ==> PSS_DatabaseManipulator ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a database manipulator                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DatabaseManipulator.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_DatabaseManipulator
//---------------------------------------------------------------------------
PSS_DatabaseManipulator::PSS_DatabaseManipulator(const CString& name, IEType type) :
    m_Name(name),
    m_Type(type)
{}
//---------------------------------------------------------------------------
PSS_DatabaseManipulator::~PSS_DatabaseManipulator()
{}
//---------------------------------------------------------------------------
bool PSS_DatabaseManipulator::CreateDatabase()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DatabaseManipulator::GetTableList(CStringArray& tableArray)
{
    return true;
}
//---------------------------------------------------------------------------
