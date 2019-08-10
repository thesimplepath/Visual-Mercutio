/****************************************************************************
 * ==> PSS_DocumentOptions -------------------------------------------------*
 ****************************************************************************
 * Description : Provides document options                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_DocumentOptions.h"

 // processsoft
#include "ZDDoc.h"

 //---------------------------------------------------------------------------
 // PSS_DocumentOptions
 //---------------------------------------------------------------------------
PSS_DocumentOptions::PSS_DocumentOptions() :
    m_ShowHiddenField(E_OT_Application),
    m_ShowEmptyLine(E_OT_Application),
    m_EmptyStyle(E_LT_Dash),
    m_AutomaticSynchronizeFileName(E_ST_AutomaticName),
    m_SynchronizationSeparator(E_SS_Automatic),
    m_SynchronizeTimeSequence(5),
    m_IsSynchronizeExchangeFeedFile(FALSE),
    m_SynchronizationHeader(FALSE),
    m_PrintEmptyStyleWhenEmpty(FALSE)
{}
//---------------------------------------------------------------------------
PSS_DocumentOptions::PSS_DocumentOptions(const PSS_DocumentOptions& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_DocumentOptions::~PSS_DocumentOptions()
{}
//---------------------------------------------------------------------------
const PSS_DocumentOptions& PSS_DocumentOptions::operator = (const PSS_DocumentOptions& other)
{
    m_ShowHiddenField               = other.m_ShowHiddenField;
    m_ShowEmptyLine                 = other.m_ShowEmptyLine;
    m_EmptyStyle                    = other.m_EmptyStyle;
    m_AutomaticSynchronizeFileName  = other.m_AutomaticSynchronizeFileName;
    m_SynchronizationSeparator      = other.m_SynchronizationSeparator;
    m_SynchronizeFileName           = other.m_SynchronizeFileName;
    m_SynchronizeTimeSequence       = other.m_SynchronizeTimeSequence;
    m_IsSynchronizeExchangeFeedFile = other.m_IsSynchronizeExchangeFeedFile;
    m_SynchronizationHeader         = other.m_SynchronizationHeader;
    m_PrintEmptyStyleWhenEmpty      = other.m_PrintEmptyStyleWhenEmpty;
    return *this;
}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_DocumentOptions& docOptions)
{
    WORD value;
    ar >> value;
    docOptions.m_EmptyStyle = ELineType(value);

    // version 10
    if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 10)
    {
        ar >> value;
        docOptions.m_IsSynchronizeExchangeFeedFile = BOOL(value);

        LONG timeSeq;
        ar >> timeSeq;
        docOptions.m_SynchronizeTimeSequence = int(timeSeq);

        ar >> value;
        docOptions.m_ShowHiddenField = EOptionType(value);

        ar >> value;
        docOptions.m_ShowEmptyLine = EOptionType(value);

        ar >> value;
        docOptions.m_AutomaticSynchronizeFileName = ESynchronizationFileType(value);

        ar >> value;
        docOptions.m_SynchronizationHeader = BOOL(value);

        ar >> value;
        docOptions.m_SynchronizationSeparator = ESynchronizationSeparatorType(value);

        ar >> docOptions.m_SynchronizeFileName;

    }

    // version 17
    if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 17)
    {
        ar >> value;
        docOptions.m_PrintEmptyStyleWhenEmpty = BOOL(value);
    }

    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_DocumentOptions& docOptions)
{
    ar << WORD(docOptions.m_EmptyStyle);
    ar << WORD(docOptions.m_IsSynchronizeExchangeFeedFile);
    ar << LONG(docOptions.m_SynchronizeTimeSequence);
    ar << WORD(docOptions.m_ShowHiddenField);
    ar << WORD(docOptions.m_ShowEmptyLine);
    ar << WORD(docOptions.m_AutomaticSynchronizeFileName);
    ar << WORD(docOptions.m_SynchronizationHeader);
    ar << WORD(docOptions.m_SynchronizationSeparator);
    ar <<      docOptions.m_SynchronizeFileName;
    ar << WORD(docOptions.m_PrintEmptyStyleWhenEmpty);
    return ar;
}
//---------------------------------------------------------------------------
CString PSS_DocumentOptions::BuildSynchronizationFileName(const CString& documentFileName)
{
    // if the document option specifies a document filename, assigns it
    if (GetAutomaticSynchronizeFileName() == E_ST_FileNameSpecified)
        return m_SynchronizeFileName;

    // if the filename does not exists, do nothing
    if (documentFileName.IsEmpty())
        return "";

    // if the synchronization file name doesn't exist, build it
    CString extension;
    char    drive   [_MAX_DRIVE];
    char    dir     [_MAX_DIR];
    char    fnBuffer[_MAX_FNAME];
    char    ext     [_MAX_EXT];

    // extract the file name
    ::_splitpath((const char*)documentFileName, drive, dir, fnBuffer, ext);
    extension.LoadString(IDS_DOCUMENTFEEDFILTER);

    CString fileName;

    // if the document option specifies a folder, create the file name with the folder
    if (m_AutomaticSynchronizeFileName == E_ST_FolderSpecified)
    {
        // in case where it is a folder, the GetSynchronizeFilename returns a folder
        fileName  = m_SynchronizeFileName;
        fileName += "\\";
        fileName += fnBuffer;
        fileName += extension;
        return fileName;
    }

    fileName  = drive;
    fileName += dir;
    fileName += fnBuffer;
    fileName += extension;
    return fileName;
}
//---------------------------------------------------------------------------
