//## begin module%366EBC140324.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%366EBC140324.cm

//## begin module%366EBC140324.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%366EBC140324.cp

//## Module: MFileDsc%366EBC140324; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\MFileDsc.cpp

//## begin module%366EBC140324.additionalIncludes preserve=no
//## end module%366EBC140324.additionalIncludes

//## begin module%366EBC140324.includes preserve=yes
#include <StdAfx.h>
//## end module%366EBC140324.includes

// MFileDsc
#include "MFileDsc.h"
//## begin module%366EBC140324.declarations preserve=no
//## end module%366EBC140324.declarations

//## begin module%366EBC140324.additionalDeclarations preserve=yes
//## end module%366EBC140324.additionalDeclarations


// Class ZUMailFileDescription 





ZUMailFileDescription::ZUMailFileDescription()
  //## begin ZUMailFileDescription::ZUMailFileDescription%.hasinit preserve=no
      : m_MapiFileDescPtr(NULL)
  //## end ZUMailFileDescription::ZUMailFileDescription%.hasinit
  //## begin ZUMailFileDescription::ZUMailFileDescription%.initialization preserve=yes
  , m_AttachementType( InsertedFile )
  //## end ZUMailFileDescription::ZUMailFileDescription%.initialization
{
  //## begin ZUMailFileDescription::ZUMailFileDescription%.body preserve=yes
  //## end ZUMailFileDescription::ZUMailFileDescription%.body
}

ZUMailFileDescription::ZUMailFileDescription (CStringArray& FileList, AttachementType AttachType)
  //## begin ZUMailFileDescription::ZUMailFileDescription%913223370.hasinit preserve=no
      : m_MapiFileDescPtr(NULL)
  //## end ZUMailFileDescription::ZUMailFileDescription%913223370.hasinit
  //## begin ZUMailFileDescription::ZUMailFileDescription%913223370.initialization preserve=yes
  , m_AttachementType( AttachType )
  //## end ZUMailFileDescription::ZUMailFileDescription%913223370.initialization
{
  //## begin ZUMailFileDescription::ZUMailFileDescription%913223370.body preserve=yes
      Fill( FileList, AttachType );
  //## end ZUMailFileDescription::ZUMailFileDescription%913223370.body
}

ZUMailFileDescription::ZUMailFileDescription (ZFileManager& FileList, AttachementType AttachType)
  //## begin ZUMailFileDescription::ZUMailFileDescription%913659110.hasinit preserve=no
      : m_MapiFileDescPtr(NULL)
  //## end ZUMailFileDescription::ZUMailFileDescription%913659110.hasinit
  //## begin ZUMailFileDescription::ZUMailFileDescription%913659110.initialization preserve=yes
  //## end ZUMailFileDescription::ZUMailFileDescription%913659110.initialization
{
  //## begin ZUMailFileDescription::ZUMailFileDescription%913659110.body preserve=yes
      Fill( FileList, AttachType );
  //## end ZUMailFileDescription::ZUMailFileDescription%913659110.body
}


ZUMailFileDescription::~ZUMailFileDescription()
{
  //## begin ZUMailFileDescription::~ZUMailFileDescription%.body preserve=yes
      if (m_MapiFileDescPtr)
          delete [] m_MapiFileDescPtr;
  //## end ZUMailFileDescription::~ZUMailFileDescription%.body
}



//## Other Operations (implementation)
void ZUMailFileDescription::Fill (CStringArray& FileList, AttachementType AttachType)
{
  //## begin ZUMailFileDescription::Fill%913223371.body preserve=yes
      RemoveAllFiles();
      for (register i = 0; i < FileList.GetSize(); ++i)
          AddFile( FileList[i] );
  //## end ZUMailFileDescription::Fill%913223371.body
}

void ZUMailFileDescription::Fill (ZFileManager& FileList, AttachementType AttachType)
{
  //## begin ZUMailFileDescription::Fill%913659108.body preserve=yes
      RemoveAllFiles();
      for (register size_t i = 0; i < FileList.GetCount(); ++i)
          AddFile( *FileList.GetAt(i) );
  //## end ZUMailFileDescription::Fill%913659108.body
}

BOOL ZUMailFileDescription::AddFile (ZFile& File, AttachementType AttachType)
{
  //## begin ZUMailFileDescription::AddFile%913659109.body preserve=yes
      SetAttachementType( File.GetAttachementType() );
      return (m_FileArray.Add( File.GetCompleteFileName() ) >= 0 );
  //## end ZUMailFileDescription::AddFile%913659109.body
}

MapiFileDesc* ZUMailFileDescription::GetMapiFileDescPtr ()
{
  //## begin ZUMailFileDescription::GetMapiFileDescPtr%913223374.body preserve=yes
      if (m_MapiFileDescPtr)
          delete [] m_MapiFileDescPtr;
      
      m_MapiFileDescPtr = new FAR MapiFileDesc[GetCount()];
      
      for (register i = 0; i < m_FileArray.GetSize(); ++i)
      {
        memset((lpMapiFileDesc)(&m_MapiFileDescPtr[i]), 0, sizeof(MapiFileDesc));
        m_MapiFileDescPtr[i].nPosition = (ULONG)-1;
        m_MapiFileDescPtr[i].lpszPathName = (char*)((const char*)m_FileArray[i]);
//    fileDesc.lpszFileName = szTitle;
          
    }
    return m_MapiFileDescPtr;
  //## end ZUMailFileDescription::GetMapiFileDescPtr%913223374.body
}

const CString& ZUMailFileDescription::GetHyperLinkText ()
{
  //## begin ZUMailFileDescription::GetHyperLinkText%913459630.body preserve=yes
      m_HyperLinkText.Empty();
      
      for (register i = 0; i < m_FileArray.GetSize(); ++i)
      {
          m_HyperLinkText += "\n";
          m_HyperLinkText += "<file://" + m_FileArray[i];
        m_HyperLinkText += ">";
    }
    m_HyperLinkText += "\n";
    return m_HyperLinkText;
  //## end ZUMailFileDescription::GetHyperLinkText%913459630.body
}

// Additional Declarations
  //## begin ZUMailFileDescription%366EBAA60269.declarations preserve=yes
  //## end ZUMailFileDescription%366EBAA60269.declarations

//## begin module%366EBC140324.epilog preserve=yes
//## end module%366EBC140324.epilog
