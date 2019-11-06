// EventFl.h: interface for the ZBEventFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBEventFile_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_)
#define AFX_ZBEventFile_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_

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


#include "ZBEvent.h"

#ifdef _ZEVENTEXPORT
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


class AFX_EXT_CLASS ZBEventFile
{
public:
    ZBEventFile();
    BOOL                ExportActivityToFile( const CString Filename, ZBEvent* pActivity );
    ZBEvent*            ImportActivityFromFile( const CString Filename );
    
    virtual ~ZBEventFile();

private:
    ZBEventFile(const ZBEventFile &right);
    const ZBEventFile & operator=(const ZBEventFile &right);

protected:
    /**
    * Builds a line
    *@param path - path
    *@param fileName - file name
    */
    virtual void BuildLine(const CString& path, const CString& fileName) = 0;

    virtual BOOL ParseLine() = 0;

    virtual ZBEvent* AllocateEvent() const = 0;

private:
    BOOL    OpenFileCreate();
    BOOL    OpenFileRead();
    BOOL    CloseFile();
    int        ReadFileBuffer();
    void    WriteLine();
    BOOL    ImportLine();
    void    ExportLine();

protected:
    ZBEvent*            m_pEvent;
    char*                m_pCurrent;
    char*                m_pNext;
    CString                m_FileBuffer;
    int                    m_BufferSize;

private:
    CString                m_Filename;
    CFile                m_File;
};

inline void ZBEventFile::WriteLine ()
{
    m_File.Write( m_FileBuffer, m_FileBuffer.GetLength() );
}

#endif
