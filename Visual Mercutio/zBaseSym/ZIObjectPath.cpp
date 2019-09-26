// ZIObjectPath.cpp: implementation of the ZIObjectPath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZIObjectPath.h"
#include "ZBaseLib\PSS_Tokenizer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZIObjectPath::ZIObjectPath()
{

}

ZIObjectPath::~ZIObjectPath()
{

}


void ZIObjectPath::AddMemberToPath( const CString Member )
{
    if (m_ObjectPath.IsEmpty())
        m_ObjectPath = Member;
    else
    {
        m_ObjectPath += ObjectSeparatorChar;
        m_ObjectPath += Member;
    }
}


CString ZIObjectPath::GetRootMember()
{
    PSS_Tokenizer    Tokenizer( ObjectSeparatorChar );
    return Tokenizer.GetFirstToken(m_ObjectPath);
}
