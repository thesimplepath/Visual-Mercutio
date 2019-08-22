#include <StdAfx.h>

// MFileDsc
#include "MFileDsc.h"

//---------------------------------------------------------------------------
// ZUMailFileDescription 
//---------------------------------------------------------------------------
ZUMailFileDescription::ZUMailFileDescription() :
    m_MapiFileDescPtr(NULL),
    m_AttachementType(PSS_File::IE_AT_InsertedFile)
{}
//---------------------------------------------------------------------------
ZUMailFileDescription::ZUMailFileDescription (CStringArray& fileList, PSS_File::IEAttachementType attachType) :
    m_MapiFileDescPtr(NULL),
    m_AttachementType(attachType)
{
    Fill(fileList, attachType);
}
//---------------------------------------------------------------------------
ZUMailFileDescription::ZUMailFileDescription(PSS_FileManager& fileList, PSS_File::IEAttachementType attachType) :
    m_MapiFileDescPtr(NULL)
{
    Fill(fileList, attachType);
}
//---------------------------------------------------------------------------
ZUMailFileDescription::~ZUMailFileDescription()
{
    if (m_MapiFileDescPtr)
        delete[] m_MapiFileDescPtr;
}
//---------------------------------------------------------------------------
void ZUMailFileDescription::Fill(CStringArray& FileList, PSS_File::IEAttachementType AttachType)
{
    RemoveAllFiles();

    for (register int i = 0; i < FileList.GetSize(); ++i)
        AddFile(FileList[i]);
}
//---------------------------------------------------------------------------
void ZUMailFileDescription::Fill(PSS_FileManager& FileList, PSS_File::IEAttachementType AttachType)
{
    RemoveAllFiles();
    
    for (register size_t i = 0; i < FileList.GetCount(); ++i)
        AddFile( *FileList.GetAt(i) );
}
//---------------------------------------------------------------------------
BOOL ZUMailFileDescription::AddFile(PSS_File& File, PSS_File::IEAttachementType AttachType)
{
    SetAttachementType(File.GetAttachementType());
    return (m_FileArray.Add(File.GetCompleteFileName()) >= 0);
}
//---------------------------------------------------------------------------
MapiFileDesc* ZUMailFileDescription::GetMapiFileDescPtr()
{
    if (m_MapiFileDescPtr)
        delete[] m_MapiFileDescPtr;
      
    m_MapiFileDescPtr = new FAR MapiFileDesc[GetCount()];
      
    for (register int i = 0; i < m_FileArray.GetSize(); ++i)
    {
        std::memset(lpMapiFileDesc(&m_MapiFileDescPtr[i]), 0, sizeof(MapiFileDesc));
        m_MapiFileDescPtr[i].nPosition    = ULONG(-1);
        m_MapiFileDescPtr[i].lpszPathName = (char*)((const char*)m_FileArray[i]);
    }

    return m_MapiFileDescPtr;
}
//---------------------------------------------------------------------------
const CString& ZUMailFileDescription::GetHyperLinkText()
{
    m_HyperLinkText.Empty();

    for (register int i = 0; i < m_FileArray.GetSize(); ++i)
    {
        m_HyperLinkText += "\n";
        m_HyperLinkText += "<file://" + m_FileArray[i];
        m_HyperLinkText += ">";
    }

    m_HyperLinkText += "\n";

    return m_HyperLinkText;
}
//---------------------------------------------------------------------------
