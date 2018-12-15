// ZBRegisterSetup.h: interface for the ZBRegisterSetup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__ZBRegisterSetup_H__)
#define __ZBRegisterSetup_H__

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

class AFX_EXT_CLASS ZBRegisterSetup  
{
public:
    ZBRegisterSetup();
    virtual ~ZBRegisterSetup();

    bool CreateEntry( const CString EntityName, const CString KeyName, const CString DefaultValue = "" );
    bool UpdateRegValue( const CString EntityName, const CString KeyName, const CString Value );
    bool GetRegValue( const CString EntityName, const CString KeyName, CString& Value, bool bCreateEntry = false );


};

#endif // !defined(__ZBRegisterSetup_H__)
