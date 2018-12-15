//## Source file: ZBCriptedFileInfo.h

#ifndef ZBCriptedFileInfo_h
#define ZBCriptedFileInfo_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include <fstream> 
#include <share.h>

// ZBCriptedLine
#include "ZBCriptedLine.h"

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

using namespace std;

class AFX_EXT_CLASS ZBCriptedFileInfo 
{
    public:

    ZBCriptedFileInfo(size_t TableEntries = 40);
    ZBCriptedFileInfo(const CString sFileName, size_t TableEntries = 40);

    ~ZBCriptedFileInfo();

    // Create an empty cripted file
    BOOL CreateEmpty();

    // Create an empty cripted file specifying its name
    BOOL CreateEmptyFile(const CString sFileName);
    
    // Basic manipulation functions
    BOOL SetString(CString value, size_t Index);

    BOOL SetDate(CTime& Date, size_t Index);
    BOOL SetDate(ZBDate& Date, size_t Index);

    BOOL SetInt(int value, size_t Index);

    CString GetString( size_t Index );
      
    CTime      GetCTime( size_t Index );
    ZBDate  GetDate( size_t Index );
      
    int      GetInt( size_t Index );

    const CString GetFilename() const;
    void SetFilename(const CString value);

    protected:

    BOOL    SetValidFileDate();
    BOOL    IsFileDateValid();

    const fstream GetFileStream() const;

    //    Error flag
    const BOOL GetErrorStatus() const;
    void SetErrorStatus(const BOOL value);
    void ClearErrorStatus();
    
    BOOL EntityTableExist() const;

    BOOL AllocateEntityTable();

    // Write the entity table to disk.
    void WriteEntityTable();

    // Load the security entities from the file to the table.
    void LoadEntityTable();

    private:
    
    CString                                    m_sFilename;
    fstream                                    m_FileStream;
    CArray<ZBCriptedLine,ZBCriptedLine>        m_EntityTable;
    BOOL                                    m_bError;
    size_t                                    m_TableEntries;
};

// Class ZBCriptedFileInfo 

inline BOOL ZBCriptedFileInfo::EntityTableExist() const
{
    return m_EntityTable.GetSize();
}

// JMR-MODIF - le 19 mai 2005 - GetFileStream supprimé, car incompilable et non utilisé.
//inline const fstream ZBCriptedFileInfo::GetFileStream() const
//{
//    return m_FileStream;
//}

inline const CString ZBCriptedFileInfo::GetFilename() const
{
    return m_sFilename;
}

inline void ZBCriptedFileInfo::SetFilename(const CString value)
{
    m_sFilename = value;
}

inline const BOOL ZBCriptedFileInfo::GetErrorStatus() const
{
    return m_bError;
}

inline void ZBCriptedFileInfo::SetErrorStatus(const BOOL value)
{
    m_bError = value;
}

inline void ZBCriptedFileInfo::ClearErrorStatus()
{
    m_bError = FALSE;
}

#endif    // ZBCriptedFileInfo_h
