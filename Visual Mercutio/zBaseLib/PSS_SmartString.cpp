/****************************************************************************
 * ==> PSS_SmartString -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a smart string                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SmartString.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_SmartString
//---------------------------------------------------------------------------
PSS_SmartString::PSS_SmartString(UINT textID) :
    m_pStrText(new CString()),
    m_CString(true)
{
    #ifdef _DEBUG
        if (!m_pStrText->LoadString(textID))
            TRACE("\nError loading string %d", textID);
    #else
        m_pStrText->LoadString(textID);
    #endif
}
//---------------------------------------------------------------------------
PSS_SmartString::PSS_SmartString(const PSS_SmartString& other) :
    m_pStrText(NULL),
    m_CString(false)
{
    if (other.m_CString)
        SetCString(*other.m_pStrText);
    else
        SetLPCTSTR(other.m_pText);
}
//---------------------------------------------------------------------------
PSS_SmartString::~PSS_SmartString()
{
    if (m_CString && m_pStrText)
        delete m_pStrText;
}
//---------------------------------------------------------------------------
PSS_SmartString& PSS_SmartString::operator = (const PSS_SmartString& data)
{
    Clear();

    if (data.m_CString)
        SetCString(*data.m_pStrText);
    else
        SetLPCTSTR(data.m_pText);

    return *this;
}
//---------------------------------------------------------------------------
PSS_SmartString& PSS_SmartString::operator = (LPCTSTR pData)
{
    Clear();
    SetLPCTSTR(pData);

    return *this;
}
//---------------------------------------------------------------------------
PSS_SmartString::operator LPCTSTR() const
{
    return (m_CString ? m_pStrText->operator LPCTSTR() : m_pText);
}
//---------------------------------------------------------------------------
void PSS_SmartString::SetCString(const CString& str)
{
    m_pStrText = new CString(str);
    m_CString  = true;
}
//---------------------------------------------------------------------------
void PSS_SmartString::SetLPCTSTR(LPCTSTR pText)
{
    m_pText   = pText;
    m_CString = false;
}
//---------------------------------------------------------------------------
void PSS_SmartString::Clear()
{
    if (m_CString && m_pStrText)
        delete m_pStrText;

    m_pStrText = NULL;
}
//---------------------------------------------------------------------------
