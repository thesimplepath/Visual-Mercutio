#include "StdAfx.h"

// ProcOpt
#include "ProcOpt.h"


// Class ZDProcessDocumentOptions 










ZDProcessDocumentOptions::ZDProcessDocumentOptions()
      : m_IsSynchronizeExchangeFeedFile(FALSE), m_SynchronizeTimeSequence(5),
        m_AutomaticSynchronizeFilename(E_ST_AutomaticName), m_SynchronizationHeader(FALSE), m_SynchronizationSeparator(E_SS_Automatic)
{}

ZDProcessDocumentOptions::ZDProcessDocumentOptions(const ZDProcessDocumentOptions &right)
{
  *this = right;
}


ZDProcessDocumentOptions::~ZDProcessDocumentOptions()
{
}


const ZDProcessDocumentOptions & ZDProcessDocumentOptions::operator=(const ZDProcessDocumentOptions &right)
{
    m_IsSynchronizeExchangeFeedFile = right.m_IsSynchronizeExchangeFeedFile;
    m_SynchronizeTimeSequence = right.m_SynchronizeTimeSequence;
    m_AutomaticSynchronizeFilename = right.m_AutomaticSynchronizeFilename;
    m_SynchronizationHeader = right.m_SynchronizationHeader;
    m_SynchronizationSeparator = right.m_SynchronizationSeparator;
    m_SynchronizeFilename = right.m_SynchronizeFilename;
    return *this;
}


CString ZDProcessDocumentOptions::BuildSynchronizationFileName (CString DocumentFilename)
{
      // If the document option specifies a document filename, assigns it
      if (GetAutomaticSynchronizeFilename() == E_ST_FileNameSpecified)
        return m_SynchronizeFilename;
      // If the filename does not exists, do nothing
    if (DocumentFilename.IsEmpty())
        return "";
        
      // If the synchro filename does not exist, build it
    // Extract the filename
    char         drive[_MAX_DRIVE];
    char         dir[_MAX_DIR];
    char         fname[_MAX_FNAME];
    char         ext[_MAX_EXT];

    _splitpath( (const char*)DocumentFilename, drive, dir, fname, ext );

    CString    Filename;
      // If the document option specifies a folder, create the filename with the folder
      if (GetAutomaticSynchronizeFilename() == E_ST_FolderSpecified)
      {
          // In case where it is a folder, the GetSynchronizeFilename returns a folder
        Filename = m_SynchronizeFilename;
        Filename += "\\";
        Filename += fname;
        Filename += g_ProcessDataFeedExtension;
        return Filename;
      }

    Filename = drive;
    Filename += dir;
    Filename += fname;
    Filename += g_ProcessDataFeedExtension;
    return Filename;
}


CArchive& operator >> (CArchive& ar, ZDProcessDocumentOptions& DocOptions)
{
    WORD    wValue;
    ar >> wValue;
    DocOptions.m_IsSynchronizeExchangeFeedFile = BOOL(wValue);

    LONG    lValue;
    ar >> lValue;
    DocOptions.m_SynchronizeTimeSequence = int(lValue);

    ar >> wValue;
      DocOptions.m_AutomaticSynchronizeFilename = ESynchronizationFileType(wValue);
      
    ar >> wValue;
      DocOptions.m_SynchronizationHeader = BOOL(wValue);

    ar >> wValue;
      DocOptions.m_SynchronizationSeparator = ESynchronizationSeparatorType(wValue);
    
    ar >> DocOptions.m_SynchronizeFilename;

    return ar;
}

CArchive& operator << (CArchive& ar, const ZDProcessDocumentOptions& DocOptions)
{
    ar << (WORD)DocOptions.m_IsSynchronizeExchangeFeedFile;
    ar << (LONG)DocOptions.m_SynchronizeTimeSequence;
    ar << (WORD)DocOptions.m_AutomaticSynchronizeFilename;
    ar << (WORD)DocOptions.m_SynchronizationHeader;
    ar << (WORD)DocOptions.m_SynchronizationSeparator;
    ar << DocOptions.m_SynchronizeFilename;
    
    return ar;
}

