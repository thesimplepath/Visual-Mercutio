// ZBInputScenario.h: interface for the ZBInputScenario class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBINPUTSCENARIO_H__19EC6EE3_FC91_11D3_96EC_0000B45D7C6F__INCLUDED_)
#define AFX_ZBINPUTSCENARIO_H__19EC6EE3_FC91_11D3_96EC_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ZBFieldInputScenario.h"

class ZBInputScenario : public CObject  
{
    DECLARE_SERIAL(ZBInputScenario)
public:
    // Inherited feature
    typedef CObject inherited;

public:
    ZBInputScenario( const CString Name = "" );
    virtual ~ZBInputScenario();

    void Initialize( const CString Name );

    // Get and Set methods
    CString    GetName() const { return m_Name; };
    void    SetName( CString        value ) { m_Name = value; };


    ZBInputScenario(const ZBInputScenario &right);
    const ZBInputScenario& operator=(const ZBInputScenario &right);

    void    RemoveAllField();
    size_t    GetFieldCount() const { return m_InputFieldSet.GetSize(); };
    ZBFieldInputScenario*    GetFieldAt( size_t Index ) const;
    ZBFieldInputScenario*    FindFieldname( const CString Fieldname ) const;
    int        FindFieldnameIndex( const CString Fieldname ) const;
    bool    AddField( ZBFieldInputScenario* pField );
    bool    AddField( const CString Fieldname, const CString Username = "", int Order = -1 );
    bool    DeleteFieldname( const CString Fieldname );
    bool    DeleteFieldnameAt( size_t Index );
    bool    RemoveFieldnameAt( size_t Index );

    size_t    GetScenarioForUser( const CString Username, ZBInputScenario& Scenario );

    ZBInputScenario* Clone();

    //    Serialization function required for MFC mecanism.
    virtual void Serialize (CArchive& ar);

private:
    CObArray    m_InputFieldSet;
    CString        m_Name;

};


inline ZBFieldInputScenario*    ZBInputScenario::GetFieldAt( size_t Index )    const
{
    if (Index < GetFieldCount())
        return static_cast<ZBFieldInputScenario*>(m_InputFieldSet.GetAt(Index));
    return NULL;
}

inline bool ZBInputScenario::AddField( ZBFieldInputScenario* pField )
{
    try
    {
        m_InputFieldSet.Add( pField );
    }
    catch( CMemoryException e() )
    {
        return false;
    }
    return true;
}

inline bool ZBInputScenario::RemoveFieldnameAt( size_t Index )
{
    if (Index < GetFieldCount())
        m_InputFieldSet.RemoveAt( Index );
    return false;
}

#endif // !defined(AFX_ZBINPUTSCENARIO_H__19EC6EE3_FC91_11D3_96EC_0000B45D7C6F__INCLUDED_)
