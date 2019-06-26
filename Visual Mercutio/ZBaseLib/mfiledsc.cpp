#include <StdAfx.h>

// MFileDsc
#include "MFileDsc.h"

//---------------------------------------------------------------------------
// ZUMailFileDescription 
//---------------------------------------------------------------------------
ZUMailFileDescription::ZUMailFileDescription() :
    m_MapiFileDescPtr(NULL),
    m_AttachementType(InsertedFile)
{}
//---------------------------------------------------------------------------
ZUMailFileDescription::ZUMailFileDescription (CStringArray& fileList, AttachementType attachType) :
    m_MapiFileDescPtr(NULL),
    m_AttachementType(attachType)
{
    Fill(fileList, attachType);
}
//---------------------------------------------------------------------------
ZUMailFileDescription::ZUMailFileDescription (ZFileManager& fileList, AttachementType attachType) :
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
void ZUMailFileDescription::Fill(CStringArray& FileList, AttachementType AttachType)
{
    RemoveAllFiles();

    for (register int i = 0; i < FileList.GetSize(); ++i)
        AddFile(FileList[i]);
}
//---------------------------------------------------------------------------
void ZUMailFileDescription::Fill(ZFileManager& FileList, AttachementType AttachType)
{
    RemoveAllFiles();
    
    for (register size_t i = 0; i < FileList.GetCount(); ++i)
        AddFile( *FileList.GetAt(i) );
}
//---------------------------------------------------------------------------
BOOL ZUMailFileDescription::AddFile(ZFile& File, AttachementType AttachType)
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
// Additional Declarations
  //## begin ZUMailFileDescription%366EBAA60269.declarations preserve=yes
  //## end ZUMailFileDescription%366EBAA60269.declarations

//## begin module%366EBC140324.epilog preserve=yes
//## end module%366EBC140324.epilog
