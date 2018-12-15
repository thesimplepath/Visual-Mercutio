#if !defined(_ZBSMARTSTRING_H)
#define _ZBSMARTSTRING_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZBSmartString.h : header file
//

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

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

/////////////////////////////////////////////////////////////////////////////
// ZBSmartString

class AFX_EXT_CLASS ZBSmartString
{
    // Constuctors and d-tor
public:
    ZBSmartString(LPCTSTR pText = NULL);
    ZBSmartString(UINT nIdText);
    ZBSmartString(const ZBSmartString& d);

    ~ZBSmartString();

    // Operators
    ZBSmartString& operator=(const ZBSmartString& data);
    ZBSmartString& operator=(LPCTSTR pData);

    operator LPCTSTR() const;

    // Operations
protected:
    void SetCString(const CString& strText);
    void SetLPCTSTR(LPCTSTR pText);
    void Clear();
    
    // Data
private:
    union 
    {
        CString* m_pStrText;
        LPCTSTR m_pText;
    };
    bool m_bCString;
};

inline ZBSmartString::ZBSmartString(LPCTSTR pText)
{    
    SetLPCTSTR(pText);
}

#endif // !defined(_ZBSMARTSTRING_H)