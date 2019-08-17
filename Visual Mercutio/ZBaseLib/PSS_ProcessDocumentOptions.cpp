/****************************************************************************
 * ==> PSS_ProcessDocumentOptions ------------------------------------------*
 ****************************************************************************
 * Description : Provides the process document options                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_ProcessDocumentOptions.h"

//---------------------------------------------------------------------------
// PSS_ProcessDocumentOptions
//---------------------------------------------------------------------------
PSS_ProcessDocumentOptions::PSS_ProcessDocumentOptions() :
    m_AutomaticSynchronizeFileName(E_ST_AutomaticName),
    m_SynchronizationSeparator(E_SS_Automatic),
    m_SynchronizeTimeSequence(5),
    m_IsSynchronizeExchangeFeedFile(FALSE),
    m_SynchronizationHeader(FALSE)
{}
//---------------------------------------------------------------------------
PSS_ProcessDocumentOptions::PSS_ProcessDocumentOptions(const PSS_ProcessDocumentOptions& other)
{
  *this = other;
}
//---------------------------------------------------------------------------
PSS_ProcessDocumentOptions::~PSS_ProcessDocumentOptions()
{}
//---------------------------------------------------------------------------
const PSS_ProcessDocumentOptions& PSS_ProcessDocumentOptions::operator = (const PSS_ProcessDocumentOptions& other)
{
    m_AutomaticSynchronizeFileName  = other.m_AutomaticSynchronizeFileName;
    m_SynchronizationSeparator      = other.m_SynchronizationSeparator;
    m_SynchronizeFileName           = other.m_SynchronizeFileName;
    m_SynchronizeTimeSequence       = other.m_SynchronizeTimeSequence;
    m_IsSynchronizeExchangeFeedFile = other.m_IsSynchronizeExchangeFeedFile;
    m_SynchronizationHeader         = other.m_SynchronizationHeader;
    return *this;
}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_ProcessDocumentOptions& docOptions)
{
    WORD value;
    ar >> value;
    docOptions.m_IsSynchronizeExchangeFeedFile = BOOL(value);

    LONG lValue;
    ar >> lValue;
    docOptions.m_SynchronizeTimeSequence = int(lValue);

    ar >> value;
    docOptions.m_AutomaticSynchronizeFileName = ESynchronizationFileType(value);

    ar >> value;
    docOptions.m_SynchronizationHeader = BOOL(value);

    ar >> value;
    docOptions.m_SynchronizationSeparator = ESynchronizationSeparatorType(value);

    ar >> docOptions.m_SynchronizeFileName;

    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_ProcessDocumentOptions& docOptions)
{
    ar << WORD(docOptions.m_IsSynchronizeExchangeFeedFile);
    ar << LONG(docOptions.m_SynchronizeTimeSequence);
    ar << WORD(docOptions.m_AutomaticSynchronizeFileName);
    ar << WORD(docOptions.m_SynchronizationHeader);
    ar << WORD(docOptions.m_SynchronizationSeparator);
    ar << docOptions.m_SynchronizeFileName;

    return ar;
}
//---------------------------------------------------------------------------
CString PSS_ProcessDocumentOptions::BuildSynchronizationFileName(const CString& documentFileName)
{
    // if the document option specifies a document file name, assign it
    if (GetAutomaticSynchronizeFileName() == E_ST_FileNameSpecified)
        return m_SynchronizeFileName;

    // if the filename does not exists, do nothing
    if (documentFileName.IsEmpty())
        return "";

    // if the synchronization file name does not exist, build it
    char drive   [_MAX_DRIVE];
    char dir     [_MAX_DIR];
    char fnBuffer[_MAX_FNAME];
    char ext     [_MAX_EXT];

    // extract the file name
    ::_splitpath((const char*)documentFileName, drive, dir, fnBuffer, ext);

    CString fileName;

    // if the document option specifies a folder, use it to build the file name
    if (GetAutomaticSynchronizeFileName() == E_ST_FolderSpecified)
    {
        fileName  = m_SynchronizeFileName;
        fileName += "\\";
        fileName += fnBuffer;
        fileName += g_ProcessDataFeedExtension;
        return fileName;
    }

    fileName  = drive;
    fileName += dir;
    fileName += fnBuffer;
    fileName += g_ProcessDataFeedExtension;
    return fileName;
}
//---------------------------------------------------------------------------
