/////////////////////////////////////////////////////////////////////////////
//@doc ZBKeepStringUsage
//@module ZBKeepStringUsage.h | Interface of the <c ZBKeepStringUsage> class.
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
// <nl>Created:         04/2002
// <nl>Description:  ZBKeepStringUsage this class keep usage of strings
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_ZBKEEPSTRINGUSAGE_H__F3E5D74F_DE45_467A_B48D_1042B850E770__INCLUDED_)
#define AFX_ZBKEEPSTRINGUSAGE_H__F3E5D74F_DE45_467A_B48D_1042B850E770__INCLUDED_

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




#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif



class AFX_EXT_CLASS ZBKeepStringUsage  
{
public:
    ZBKeepStringUsage();
    virtual ~ZBKeepStringUsage();


    bool    StringAlreadyGenerated( const CString str )
    {
        int size = m_StringsArray.GetSize();
        for (int i = 0; i < size; ++i)
        {
            if (m_StringsArray.GetAt(i) == str)
                return true;
        }
        m_StringsArray.Add( str );
        return false;
    };
    void    ResetStringsArray()
    {
        m_StringsArray.RemoveAll();
    };


private:
    CStringArray m_StringsArray;

};

#endif // !defined(AFX_ZBKEEPSTRINGUSAGE_H__F3E5D74F_DE45_467A_B48D_1042B850E770__INCLUDED_)
