//## begin module%334FC46302EA.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC46302EA.cm

//## begin module%334FC46302EA.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%334FC46302EA.cp

//## Module: Stamp%334FC46302EA; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\Stamp.cpp

//## begin module%334FC46302EA.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%334FC46302EA.additionalIncludes

//## begin module%334FC46302EA.includes preserve=yes
//## end module%334FC46302EA.includes

// Stamp
#include "Stamp.h"
//## begin module%334FC46302EA.declarations preserve=no
//## end module%334FC46302EA.declarations

//## begin module%334FC46302EA.additionalDeclarations preserve=yes
//## end module%334FC46302EA.additionalDeclarations


// Class ZDStamp 

















ZDStamp::ZDStamp()
  //## begin ZDStamp::ZDStamp%.hasinit preserve=no
  //## end ZDStamp::ZDStamp%.hasinit
  //## begin ZDStamp::ZDStamp%.initialization preserve=yes
    : m_Stamp("ADSoft"), m_InternalVersion(-1), 
      m_FileType(E_FD_DocumentType), m_DocumentDataType(FormDataType),
      m_PublishVersion(0), m_ReadOnly(FALSE),
      m_DocumentFileType(FormDocumentFileType)
  //## end ZDStamp::ZDStamp%.initialization
{
  //## begin ZDStamp::ZDStamp%.body preserve=yes
  //## end ZDStamp::ZDStamp%.body
}

ZDStamp::ZDStamp(const ZDStamp &right)
  //## begin ZDStamp::ZDStamp%copy.hasinit preserve=no
  //## end ZDStamp::ZDStamp%copy.hasinit
  //## begin ZDStamp::ZDStamp%copy.initialization preserve=yes
  //## end ZDStamp::ZDStamp%copy.initialization
{
  //## begin ZDStamp::ZDStamp%copy.body preserve=yes
  *this = right;
  //## end ZDStamp::ZDStamp%copy.body
}


ZDStamp::~ZDStamp()
{
  //## begin ZDStamp::~ZDStamp%.body preserve=yes
  //## end ZDStamp::~ZDStamp%.body
}


const ZDStamp & ZDStamp::operator=(const ZDStamp &right)
{
  //## begin ZDStamp::operator=%.body preserve=yes
    m_Stamp = right.m_Stamp;    
    m_InternalVersion = right.m_InternalVersion;
    m_Title = right.m_Title;
    m_Explanation = right.m_Explanation;
    m_Template = right.m_Template;        
    m_StampCreationDate = right.m_StampCreationDate;    
    m_StampModificationDate = right.m_StampModificationDate;
    m_ProgramGenerator = right.m_ProgramGenerator;
    m_FileType = right.m_FileType;
    m_PublishVersion = right.m_PublishVersion;
    m_PublishDate = right.m_PublishDate;
    m_PublishUser = right.m_PublishUser;
    m_ReadOnly = right.m_ReadOnly;
    m_InternalKey = right.m_InternalKey;
    m_DocumentDataType = right.m_DocumentDataType;
    m_DocumentFileType = right.m_DocumentFileType;
    return *this;
  //## end ZDStamp::operator=%.body
}



//## Other Operations (implementation)
CArchive& operator >> (CArchive& ar, ZDStamp& Stamp)
{
  //## begin ZDStamp::operator >>%831614623.body preserve=yes
      CString    Dummy;
      
    ar >> Stamp.m_Stamp;
    ar >> Stamp.m_InternalVersion;
    ar >> Stamp.m_Title;
    ar >> Stamp.m_Explanation;
    if (Stamp.m_InternalVersion <= 11)
        ar >> Dummy;    // In place of Formula Template
    ar >> Stamp.m_Template;
    // Not yet in ZBDate
    CTime    time;
    if (Stamp.m_InternalVersion < 14)
    {
        ar >> time;
        if (time.GetTime() >= 0)
            Stamp.SetStampCreationDate( time );
        ar >> time;
        if (time.GetTime() >= 0)
            Stamp.SetStampModificationDate( time );
    }
    else
    {
        ar >> Stamp.m_StampCreationDate;
        ar >> Stamp.m_StampModificationDate;
    }
    if (Stamp.m_InternalVersion <= 11)
    {
        ar >> Dummy;    // In place of Reserved 1 & 2
        ar >> Dummy;
    }
    ar >> Stamp.m_ProgramGenerator;
    WORD    wValue;
    ar >> wValue;
    Stamp.m_FileType = EFileTypeDefinition(wValue);
    if (Stamp.m_InternalVersion >= 13)
    {
        ar >> Stamp.m_PublishVersion;
        // Not yet in ZBDate
        if (Stamp.m_InternalVersion < 14)
        {
            ar >> time;
            if (time.GetTime() >= 0)
                Stamp.SetPublishDate( time );
        }
        else
            ar >> Stamp.m_PublishDate;
        ar >> Stamp.m_PublishUser;
    }

    if (Stamp.m_InternalVersion >= 14)
    {
        ar >> wValue;
        Stamp.m_ReadOnly = (BOOL)wValue;
        ar >> Stamp.m_InternalKey;
        ar >> wValue;
        Stamp.m_DocumentDataType = (DocumentDataType)wValue;
    }
    else
        Stamp.m_ReadOnly = FALSE;
    if (Stamp.m_InternalVersion >= 15)
    {
        ar >> wValue;
        Stamp.m_DocumentFileType = (DocumentFileType)wValue;
    }
    return ar;
  //## end ZDStamp::operator >>%831614623.body
}

CArchive& operator << (CArchive& ar, const ZDStamp& Stamp)
{
  //## begin ZDStamp::operator <<%831614624.body preserve=yes
    ar << Stamp.m_Stamp;
    ar << Stamp.m_InternalVersion;
    ar << Stamp.m_Title;
    ar << Stamp.m_Explanation;
    ar << Stamp.m_Template;
    ar << Stamp.m_StampCreationDate;
    ar << Stamp.m_StampModificationDate;
    ar << Stamp.m_ProgramGenerator;
    ar << (WORD)Stamp.m_FileType;
    ar << Stamp.m_PublishVersion;
    ar << Stamp.m_PublishDate;
    ar << Stamp.m_PublishUser;
    ar << (WORD)Stamp.m_ReadOnly;
    ar << Stamp.m_InternalKey;
    ar << (WORD)Stamp.m_DocumentDataType;
    ar << (WORD)Stamp.m_DocumentFileType;
    return ar;
  //## end ZDStamp::operator <<%831614624.body
}

BOOL ZDStamp::ReadFromFile (CString Filename)
{
  //## begin ZDStamp::ReadFromFile%927439022.body preserve=yes
    BOOL            RetValue = FALSE;
    CFile            file;
    CFileException    fe;
    if (!file.Open( Filename, CFile::modeRead | CFile::shareDenyWrite, &fe ))
        return FALSE;
    // Create the archive
    CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);
    loadArchive.m_pDocument = NULL;
    loadArchive.m_bForceFlat = FALSE;
    WORD    wStamp = 0;
    TRY
    {
        loadArchive >> wStamp;
    }
    CATCH( CArchiveException, e )
    {
        return FALSE;
    }
    END_CATCH
    // Test if the stamp has been set correctly
    // for next generation of files
    if (wStamp == 0xFFFF)
    {
        loadArchive >> *this;
        RetValue = TRUE;
    }
    // Now close the archive
    loadArchive.Close();
    file.Close();
    return RetValue;
  //## end ZDStamp::ReadFromFile%927439022.body
}

BOOL ZDStamp::WriteToFile (CString Filename)
{
  //## begin ZDStamp::WriteToFile%939754019.body preserve=yes
    ZDStamp        DummyStamp;
    // First, read bytes coming from the file.
    BOOL            RetValue = FALSE;
    UINT            EffectiveSize = 0;
    CFile            file;
    CFileException    fe;
    if (!file.Open( Filename, CFile::modeRead | CFile::shareDenyWrite, &fe ))
        return FALSE;
    // File is now open, read the status
    CFileStatus        rStatus;
    if (!file.GetStatus( rStatus ))
        return FALSE;
    // Create the archive
    CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);
    loadArchive.m_pDocument = NULL;
    loadArchive.m_bForceFlat = FALSE;
    WORD    wStamp = 0;
    TRY
    {
        loadArchive >> wStamp;
    }
    CATCH( CArchiveException, e )
    {
        return FALSE;
    }
    END_CATCH
    // Test if the stamp has been set correctly
    // for next generation of files
    if (wStamp == 0xFFFF)
    {
        loadArchive >> DummyStamp;
        RetValue = TRUE;
    }
    // Now, read the rest of the information
    void* pFileBuffer;
    // Allocate a new buffer with the file size
    pFileBuffer = malloc( (size_t)rStatus.m_size );
    if (pFileBuffer == 0)
        return FALSE;
    // Clear the buffer
    memset( pFileBuffer, 0, (size_t)rStatus.m_size );
    TRY
    {
        // Now read the information
        EffectiveSize = loadArchive.Read( pFileBuffer, (UINT)rStatus.m_size );
    }
    CATCH( CFileException, e )
    {
        if (pFileBuffer)
            delete pFileBuffer;
        // Close the file and the archive
        loadArchive.Close();
        file.Close();
        return FALSE;
    }
    END_CATCH
    // Close the file and the archive
    loadArchive.Close();
    file.Close();

    // Now write the new stamp
    if (!file.Open( Filename, CFile::modeWrite | CFile::shareDenyWrite, &fe ))
        return FALSE;
    // Create the save archive
    CArchive saveArchive(&file, CArchive::store | CArchive::bNoFlushOnDelete);
    saveArchive.m_pDocument = NULL;
    saveArchive.m_bForceFlat = FALSE;
    TRY
    {
        saveArchive << wStamp;
    }
    CATCH( CArchiveException, e )
    {
        return FALSE;
    }
    END_CATCH
    // Test if the stamp has been set correctly
    // for next generation of files
    if (wStamp == 0xFFFF)
    {
        saveArchive << *this;
        RetValue = TRUE;
    }
    TRY
    {
        // Now save the information
        saveArchive.Write( pFileBuffer, EffectiveSize );
    }
    CATCH( CFileException, e )
    {
        if (pFileBuffer)
            delete pFileBuffer;
        // Close the file and the archive
        saveArchive.Close();
        file.Close();
        return FALSE;
    }
    END_CATCH
    saveArchive.Flush();
    // Close the file and the archive
    saveArchive.Close();
    file.Close();
    // Free the buffer
    if (pFileBuffer)
        delete pFileBuffer;

    return TRUE;
  //## end ZDStamp::WriteToFile%939754019.body
}

BOOL ZDStamp::IsInternalKeyEqualTo (const CString Key)
{
  //## begin ZDStamp::IsInternalKeyEqualTo%936298260.body preserve=yes
    return m_InternalKey == Key;
  //## end ZDStamp::IsInternalKeyEqualTo%936298260.body
}

LONG ZDStamp::IncrementPublishVersionOfFile (const CString Filename)
{
  //## begin ZDStamp::IncrementPublishVersionOfFile%939754015.body preserve=yes
    // If unable to read file, return error
    if (!ReadFromFile( Filename ))
        return -1;
    // And now, write the new version to the file.
    ++m_PublishVersion;
    // If unable to write file, return error
    if (!WriteToFile( Filename ))
        return -1;
    return m_PublishVersion;
  //## end ZDStamp::IncrementPublishVersionOfFile%939754015.body
}

LONG ZDStamp::DecrementPublishVersionOfFile (const CString Filename)
{
  //## begin ZDStamp::DecrementPublishVersionOfFile%939754016.body preserve=yes
    // If unable to read file, return error
    if (!ReadFromFile( Filename ))
        return -1;
    // And now, write the new version to the file.
    --m_PublishVersion;
    // If unable to write file, return error
    if (!WriteToFile( Filename ))
        return -1;
    return m_PublishVersion;
  //## end ZDStamp::DecrementPublishVersionOfFile%939754016.body
}

BOOL ZDStamp::SetPublishVersionOfFile (const CString Filename, LONG Version)
{
  //## begin ZDStamp::SetPublishVersionOfFile%939754017.body preserve=yes
    // If unable to read file, return error
    if (!ReadFromFile( Filename ))
        return FALSE;
    // And now, write the new version to the file.
    m_PublishVersion = Version;
    // If unable to write file, return error
    if (!WriteToFile( Filename ))
        return FALSE;
    return m_PublishVersion;
  //## end ZDStamp::SetPublishVersionOfFile%939754017.body
}

LONG ZDStamp::GetPublishVersionOfFile (const CString Filename)
{
  //## begin ZDStamp::GetPublishVersionOfFile%939754018.body preserve=yes
    // If reading the file is ok, return the publish version
    if (ReadFromFile( Filename ))
        return m_PublishVersion;
    // Otherwise, return -1;
    return -1;
  //## end ZDStamp::GetPublishVersionOfFile%939754018.body
}

ZDStamp* ZDStamp::Clone ()
{
  //## begin ZDStamp::Clone%939754020.body preserve=yes
    ZDStamp*    pNewStamp = new ZDStamp(*this);
    return pNewStamp;
  //## end ZDStamp::Clone%939754020.body
}

// Additional Declarations
  //## begin ZDStamp%334FC4600382.declarations preserve=yes
  //## end ZDStamp%334FC4600382.declarations

//## begin module%334FC46302EA.epilog preserve=yes
//## end module%334FC46302EA.epilog
