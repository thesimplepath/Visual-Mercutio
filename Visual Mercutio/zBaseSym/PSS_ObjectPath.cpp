/****************************************************************************
 * ==> PSS_ObjectPath ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an object path interface                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ObjectPath.h"

// processsoft
#include "ZBaseLib\PSS_Tokenizer.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------
const char g_ObjectSeparatorChar = _T(':');
//---------------------------------------------------------------------------
// PSS_ObjectPath
//---------------------------------------------------------------------------
PSS_ObjectPath::PSS_ObjectPath()
{}
//---------------------------------------------------------------------------
PSS_ObjectPath::~PSS_ObjectPath()
{}
//---------------------------------------------------------------------------
void PSS_ObjectPath::AddMemberToPath(const CString& member)
{
    if (m_ObjectPath.IsEmpty())
        m_ObjectPath = member;
    else
    {
        m_ObjectPath += g_ObjectSeparatorChar;
        m_ObjectPath += member;
    }
}
//---------------------------------------------------------------------------
CString PSS_ObjectPath::GetRootMember()
{
    PSS_Tokenizer tokenizer(g_ObjectSeparatorChar);
    return tokenizer.GetFirstToken(m_ObjectPath);
}
//---------------------------------------------------------------------------
