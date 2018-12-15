// ZBFieldInputScenario.h: interface for the ZBFieldInputScenario class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBFIELDINPUTSCENARIO_H__19EC6EE4_FC91_11D3_96EC_0000B45D7C6F__INCLUDED_)
#define AFX_ZBFIELDINPUTSCENARIO_H__19EC6EE4_FC91_11D3_96EC_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ZBFieldInputScenario : public CObject  
{
    DECLARE_SERIAL(ZBFieldInputScenario)
public:
    // Inherited feature
    typedef CObject inherited;
public:
    ZBFieldInputScenario(const CString Fieldname = "", const CString Username = "", int Order = -1);
    virtual ~ZBFieldInputScenario();

    void Initialize(const CString Fieldname, const CString Username = "", int Order = -1);

    ZBFieldInputScenario(const ZBFieldInputScenario &right);
    const ZBFieldInputScenario& operator=(const ZBFieldInputScenario &right);

    bool    IsOrdered() const { return m_Order != -1; };
    bool    EveryoneAllowed() const { return m_Username.IsEmpty(); };

    ZBFieldInputScenario* Clone();

    int        GetOrder() const { return m_Order; };
    void    SetOrder( int value ) { m_Order = value; };

    CString GetUsername() const { return m_Username; };
    void    SetUsername( CString value ) { m_Username = value; };

    CString GetFieldname() const { return m_Fieldname; };
    void    SetFieldname( CString value ) { m_Fieldname = value; };


    //    Serialization function required for MFC mecanism.
    virtual void Serialize (CArchive& ar);


private:
    int m_Order;
    CString m_Username;
    CString m_Fieldname;
};

#endif // !defined(AFX_ZBFIELDINPUTSCENARIO_H__19EC6EE4_FC91_11D3_96EC_0000B45D7C6F__INCLUDED_)
