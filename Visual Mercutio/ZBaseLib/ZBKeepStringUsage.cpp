/****************************************************************************
 * ==> PSS_KeepStringUsage -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a keep string usage class                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "ZBKeepStringUsage.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_KeepStringUsage
//---------------------------------------------------------------------------
PSS_KeepStringUsage::PSS_KeepStringUsage()
{}
//---------------------------------------------------------------------------
PSS_KeepStringUsage::~PSS_KeepStringUsage()
{
    // reset the array of strings
    m_StringsArray.RemoveAll();
}
//---------------------------------------------------------------------------
bool PSS_KeepStringUsage::StringAlreadyGenerated(const CString& str)
{
    const int size = m_StringsArray.GetSize();

    for (int i = 0; i < size; ++i)
        if (m_StringsArray.GetAt(i) == str)
            return true;

    m_StringsArray.Add(str);
    return false;
}
//---------------------------------------------------------------------------
