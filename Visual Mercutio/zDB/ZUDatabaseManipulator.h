// ZUDatabaseManipulator.h: interface for the ZUDatabaseManipulator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUDATABASEMANIPULATOR_H__FC3B1F3B_8E66_41D6_B4F7_FFE3CB8639A0__INCLUDED_)
#define AFX_ZUDATABASEMANIPULATOR_H__FC3B1F3B_8E66_41D6_B4F7_FFE3CB8639A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ZUDatabaseManipulator  
{
public:
    enum DatabaseType { MSAccess,
                        dBaseIII,
                        dBaseIV,
                        dBase5,
                        Paradox3x,
                        Paradox4x,
                        Paradox5x,
                        FoxPro2,
                        FoxPro25,
                        FoxPro26,
                        Excel3,
                        Excel4,
                        Excel5,
                        Excel97,
                        HTMLExport,
                        HTMLImport,
                        Text,
                        LotusWks,
                        LotusWk1,
                        LotusWk3,
                        LotusWk4,
                        Oracle8i };

public:
    ZUDatabaseManipulator( const CString Databasename = "", DatabaseType tp = MSAccess );
    virtual ~ZUDatabaseManipulator();

    bool CreateDatabase();

    bool GetTableList( CStringArray& TableArray );

private:
    CString            m_Databasename;
    DatabaseType    m_tp;
};

#endif // !defined(AFX_ZUDATABASEMANIPULATOR_H__FC3B1F3B_8E66_41D6_B4F7_FFE3CB8639A0__INCLUDED_)
