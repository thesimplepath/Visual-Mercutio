// ZBGenericSymbolErrorLine.h: interface for the ZBGenericSymbolErrorLine class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBGenericSymbolErrorLine_H__74469948_01E4_477F_AE8E_F83A38064EE6__INCLUDED_)
#define AFX_ZBGenericSymbolErrorLine_H__74469948_01E4_477F_AE8E_F83A38064EE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_ErrorLine.h"

#ifdef _ZMODELEXPORT
// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 22 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBGenericSymbolErrorLine : public PSS_ErrorLine
{
public:

    ZBGenericSymbolErrorLine( const CString message = _T( "" ) );

    // Warning by default
    ZBGenericSymbolErrorLine( const CString    message,
                              const CString    symbolname,
                              const CString    symbolpath,
                              int            error        = -1,
                              int            type        = 0 );

    // Warning by default
    ZBGenericSymbolErrorLine( UINT            nIDSmessage,
                              const CString    symbolname,
                              const CString    symbolpath,
                              int            error        = -1,
                              int            type        = 0 );

    virtual ~ZBGenericSymbolErrorLine();

    ZBGenericSymbolErrorLine( const ZBGenericSymbolErrorLine& src );
    ZBGenericSymbolErrorLine& operator=( const ZBGenericSymbolErrorLine& src );

    virtual CString GetSymbolName() const
    {
        return m_SymbolName;
    }

    virtual void SetSymbolName( const CString& name )
    {
        m_SymbolName = name;
        BuildString();
    }

    virtual CString GetSymbolPath() const
    {
        return m_SymbolPath;
    }

    virtual void SetSymbolPath( const CString& path )
    {
        m_SymbolPath = path;
        BuildString();
    }

protected:

    virtual void BuildString();
    virtual void Parse();

private:
    CString m_SymbolName;
    CString m_SymbolPath;
};

#endif
