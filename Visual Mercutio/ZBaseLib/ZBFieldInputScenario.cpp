// ZBFieldInputScenario.cpp: implementation of the ZBFieldInputScenario class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBFieldInputScenario.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(ZBFieldInputScenario, CObject, g_DefVersion)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBFieldInputScenario::ZBFieldInputScenario(const CString Fieldname /*= ""*/, const CString Username /*= ""*/, int Order /*= -1*/)
: m_Fieldname(Fieldname), m_Username(Username), m_Order(Order)
{

}

ZBFieldInputScenario::~ZBFieldInputScenario()
{

}

ZBFieldInputScenario::ZBFieldInputScenario(const ZBFieldInputScenario &right)
{
  *this = right;
}

const ZBFieldInputScenario & ZBFieldInputScenario::operator=(const ZBFieldInputScenario &right)
{
    m_Order = right.m_Order;
    m_Username = right.m_Username;
    m_Fieldname = right.m_Fieldname;
    return *this;
}


void ZBFieldInputScenario::Initialize(const CString Fieldname, const CString Username /*= ""*/, int Order /*= -1*/)
{
    m_Fieldname = Fieldname;
    m_Username = Username;
    m_Order = Order;
}

ZBFieldInputScenario* ZBFieldInputScenario::Clone()
{
    ZBFieldInputScenario*    pNewObject = new ZBFieldInputScenario( *this );
    return pNewObject;
}


void ZBFieldInputScenario::Serialize (CArchive& ar)
{
    if (ar.IsStoring())
    {    // Write the elements
        ar << (DWORD)m_Order;
        ar << m_Username;
          ar << m_Fieldname;
    }
    else
    {    // Read the elements
        DWORD    dwValue;
        ar >> dwValue;
        m_Order = (int)dwValue;

        ar >> m_Username;
        ar >> m_Fieldname;
    }
}
