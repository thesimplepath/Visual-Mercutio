//## begin module%351657D400C8.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%351657D400C8.cm

//## begin module%351657D400C8.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%351657D400C8.cp

//## Module: DocOpt%351657D400C8; Package body
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\ZProcess\DocOpt.cpp

//## begin module%351657D400C8.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%351657D400C8.additionalIncludes

//## begin module%351657D400C8.includes preserve=yes
#include "ZDDoc.h"
//## end module%351657D400C8.includes

// DocOpt
#include "DocOpt.h"
//## begin module%351657D400C8.declarations preserve=no
//## end module%351657D400C8.declarations

//## begin module%351657D400C8.additionalDeclarations preserve=yes
//## end module%351657D400C8.additionalDeclarations


// Class ZDDocumentOptions 










ZDDocumentOptions::ZDDocumentOptions()
  //## begin ZDDocumentOptions::ZDDocumentOptions%.hasinit preserve=no
      : m_EmptyStyle(E_LT_Dash), m_IsSynchronizeExchangeFeedFile(FALSE), m_SynchronizeTimeSequence(5), m_ShowHiddenField(E_OT_Application), m_ShowEmptyLine(E_OT_Application)
  //## end ZDDocumentOptions::ZDDocumentOptions%.hasinit
  //## begin ZDDocumentOptions::ZDDocumentOptions%.initialization preserve=yes
  , m_AutomaticSynchronizeFilename(E_ST_AutomaticName), m_SynchronizationHeader(FALSE), m_SynchronizationSeparator(E_SS_Automatic),
  m_PrintEmptyStyleWhenEmpty(FALSE)
  //## end ZDDocumentOptions::ZDDocumentOptions%.initialization
{
  //## begin ZDDocumentOptions::ZDDocumentOptions%.body preserve=yes
  //## end ZDDocumentOptions::ZDDocumentOptions%.body
}

ZDDocumentOptions::ZDDocumentOptions(const ZDDocumentOptions &right)
  //## begin ZDDocumentOptions::ZDDocumentOptions%copy.hasinit preserve=no
      : m_EmptyStyle(E_LT_Dash), m_IsSynchronizeExchangeFeedFile(FALSE), m_SynchronizeTimeSequence(5), m_ShowHiddenField(E_OT_Application), m_ShowEmptyLine(E_OT_Application)
  //## end ZDDocumentOptions::ZDDocumentOptions%copy.hasinit
  //## begin ZDDocumentOptions::ZDDocumentOptions%copy.initialization preserve=yes
  , m_PrintEmptyStyleWhenEmpty(FALSE)
  //## end ZDDocumentOptions::ZDDocumentOptions%copy.initialization
{
  //## begin ZDDocumentOptions::ZDDocumentOptions%copy.body preserve=yes
  *this = right;
  //## end ZDDocumentOptions::ZDDocumentOptions%copy.body
}


ZDDocumentOptions::~ZDDocumentOptions()
{
  //## begin ZDDocumentOptions::~ZDDocumentOptions%.body preserve=yes
  //## end ZDDocumentOptions::~ZDDocumentOptions%.body
}


const ZDDocumentOptions & ZDDocumentOptions::operator=(const ZDDocumentOptions &right)
{
  //## begin ZDDocumentOptions::operator=%.body preserve=yes
    m_EmptyStyle = right.m_EmptyStyle;
    m_IsSynchronizeExchangeFeedFile = right.m_IsSynchronizeExchangeFeedFile;
    m_SynchronizeTimeSequence = right.m_SynchronizeTimeSequence;
    m_ShowHiddenField = right.m_ShowHiddenField;
    m_ShowEmptyLine = right.m_ShowEmptyLine;
    m_AutomaticSynchronizeFilename = right.m_AutomaticSynchronizeFilename;
    m_SynchronizationHeader = right.m_SynchronizationHeader;
    m_SynchronizationSeparator = right.m_SynchronizationSeparator;
    m_SynchronizeFilename = right.m_SynchronizeFilename;
    m_PrintEmptyStyleWhenEmpty = right.m_PrintEmptyStyleWhenEmpty;
    return *this;
  //## end ZDDocumentOptions::operator=%.body
}



//## Other Operations (implementation)
CArchive& operator >> (CArchive& ar, ZDDocumentOptions& DocOptions)
{
  //## begin ZDDocumentOptions::operator >>%890656168.body preserve=yes
    WORD    wValue;
    ar >> wValue;
    DocOptions.m_EmptyStyle = ELineType(wValue);
    // If before Version 4 read the FontType
    // And assign the font
    if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 10)
    {
        ar >> wValue;
        DocOptions.m_IsSynchronizeExchangeFeedFile = (BOOL)wValue;

        LONG    lValue;
        ar >> lValue;
        DocOptions.m_SynchronizeTimeSequence = (int)lValue;

        ar >> wValue;
        DocOptions.m_ShowHiddenField = EOptionType(wValue);

        ar >> wValue;
        DocOptions.m_ShowEmptyLine = EOptionType(wValue);
        
        ar >> wValue;
          DocOptions.m_AutomaticSynchronizeFilename = ESynchronizationFileType(wValue);
          
        ar >> wValue;
          DocOptions.m_SynchronizationHeader = BOOL(wValue);

        ar >> wValue;
          DocOptions.m_SynchronizationSeparator = ESynchronizationSeparatorType(wValue);
        
        ar >> DocOptions.m_SynchronizeFilename;

    }
    // Version 17
    if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 17)
    {
        ar >> wValue;
        DocOptions.m_PrintEmptyStyleWhenEmpty = (BOOL)wValue;
    }
    return ar;
  //## end ZDDocumentOptions::operator >>%890656168.body
}

CArchive& operator << (CArchive& ar, const ZDDocumentOptions& DocOptions)
{
  //## begin ZDDocumentOptions::operator <<%890656169.body preserve=yes
    ar << (WORD)DocOptions.m_EmptyStyle;
    ar << (WORD)DocOptions.m_IsSynchronizeExchangeFeedFile;
    ar << (LONG)DocOptions.m_SynchronizeTimeSequence;
    ar << (WORD)DocOptions.m_ShowHiddenField;
    ar << (WORD)DocOptions.m_ShowEmptyLine;
    ar << (WORD)DocOptions.m_AutomaticSynchronizeFilename;
    ar << (WORD)DocOptions.m_SynchronizationHeader;
    ar << (WORD)DocOptions.m_SynchronizationSeparator;
    ar << DocOptions.m_SynchronizeFilename;
    ar << (WORD)DocOptions.m_PrintEmptyStyleWhenEmpty;
    return ar;
  //## end ZDDocumentOptions::operator <<%890656169.body
}

CString ZDDocumentOptions::BuildSynchronizationFileName (CString DocumentFilename)
{
  //## begin ZDDocumentOptions::BuildSynchronizationFileName%931459606.body preserve=yes
      // If the document option specifies a document filename, assigns it
      if (GetAutomaticSynchronizeFilename() == E_ST_FileNameSpecified)
        return m_SynchronizeFilename;
      // If the filename does not exists, do nothing
    if (DocumentFilename.IsEmpty())
        return "";
        
      // If the synchro filename does not exist, build it
    // Extract the filename
    CString        Extension;
    char         drive[_MAX_DRIVE];
    char         dir[_MAX_DIR];
    char         fname[_MAX_FNAME];
    char         ext[_MAX_EXT];

    _splitpath( (const char*)DocumentFilename, drive, dir, fname, ext );
    Extension.LoadString( IDS_DOCUMENTFEEDFILTER );

    CString    Filename;
      // If the document option specifies a folder, create the filename with the folder
      if (GetAutomaticSynchronizeFilename() == E_ST_FolderSpecified)
      {
          // In case where it is a folder, the GetSynchronizeFilename returns a folder
        Filename = m_SynchronizeFilename;
        Filename += "\\";
        Filename += fname;
        Filename += Extension;
        return Filename;
      }

    Filename = drive;
    Filename += dir;
    Filename += fname;
    Filename += Extension;
    return Filename;
  //## end ZDDocumentOptions::BuildSynchronizationFileName%931459606.body
}

// Additional Declarations
  //## begin ZDDocumentOptions%351656F90334.declarations preserve=yes
  //## end ZDDocumentOptions%351656F90334.declarations

//## begin module%351657D400C8.epilog preserve=yes
//## end module%351657D400C8.epilog
