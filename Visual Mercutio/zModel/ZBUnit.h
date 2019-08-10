// ZBUnit.h: interface for the ZBUnit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBUNIT_H__C267AE1B_E6C2_4678_A8D8_CD5CA2644DC7__INCLUDED_)
#define AFX_ZBUNIT_H__C267AE1B_E6C2_4678_A8D8_CD5CA2644DC7__INCLUDED_

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
#include "zBaseLib\PSS_ProcessModelDocTmpl.h"

// forward class declaration
class ZDProcessGraphModelDoc;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZBUnit : public CObject  
{
    DECLARE_SERIAL(ZBUnit)

public:
    ZBUnit( const CString Name = "", const CString Filename = "" );
    virtual ~ZBUnit();

    bool    Create( const CString Name );
    bool    Create( const CString Name, const CString Filename );
    CString    CreateUniqueKey();
    bool    LoadUnit(PSS_ProcessModelDocTmpl* pDocTmpl);
    bool    UnloadUnit();

    bool    IsLoaded() const { return m_pUnitDoc != NULL; };

    ZDProcessGraphModelDoc* GetUnitDocumentPtr() { return m_pUnitDoc; };

    CString GetName() const { return m_Name; };
    void SetName( CString value ) { m_Name = value; };

    CString GetKey() const { return m_Key; };
    void SetKey( CString value ) { m_Key = value; };

    CString GetFilename() const { return m_Filename; };
    void SetFilename( CString value ) { m_Filename = value; };

//    ZBUnit*    Clone();

    // Serializes the unit
    virtual void Serialize(CArchive& ar);

private:
    // Copy constructor
    ZBUnit(const ZBUnit& right);
    // Assignment operator
    ZBUnit& operator=(const ZBUnit& right);

protected:
    ZDProcessGraphModelDoc* m_pUnitDoc;
    CString m_Name;
    CString m_Key;
    CString m_Filename;
};

#endif // !defined(AFX_ZBUNIT_H__C267AE1B_E6C2_4678_A8D8_CD5CA2644DC7__INCLUDED_)
