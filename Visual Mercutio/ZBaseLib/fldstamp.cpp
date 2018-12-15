//## begin module%367B896A0345.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%367B896A0345.cm

//## begin module%367B896A0345.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%367B896A0345.cp

//## Module: FldStamp%367B896A0345; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\FldStamp.cpp

//## begin module%367B896A0345.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%367B896A0345.additionalIncludes

//## begin module%367B896A0345.includes preserve=yes
//## end module%367B896A0345.includes

// FldStamp
#include "FldStamp.h"
//## begin module%367B896A0345.declarations preserve=no
//## end module%367B896A0345.declarations

//## begin module%367B896A0345.additionalDeclarations preserve=yes
//## end module%367B896A0345.additionalDeclarations


// Class ZDFolderStamp

ZDFolderStamp::ZDFolderStamp()
      //## begin ZDFolderStamp::ZDFolderStamp%.hasinit preserve=no
      //## end ZDFolderStamp::ZDFolderStamp%.hasinit
      //## begin ZDFolderStamp::ZDFolderStamp%.initialization preserve=yes
      //## end ZDFolderStamp::ZDFolderStamp%.initialization
{
    //## begin ZDFolderStamp::ZDFolderStamp%.body preserve=yes
    //## end ZDFolderStamp::ZDFolderStamp%.body
}

ZDFolderStamp::ZDFolderStamp( const ZDFolderStamp &right )
      //## begin ZDFolderStamp::ZDFolderStamp%copy.hasinit preserve=no
      //## end ZDFolderStamp::ZDFolderStamp%copy.hasinit
      //## begin ZDFolderStamp::ZDFolderStamp%copy.initialization preserve=yes
      //## end ZDFolderStamp::ZDFolderStamp%copy.initialization
{
    //## begin ZDFolderStamp::ZDFolderStamp%copy.body preserve=yes
    *this = right;
    //## end ZDFolderStamp::ZDFolderStamp%copy.body
}

ZDFolderStamp::~ZDFolderStamp()
{
    //## begin ZDFolderStamp::~ZDFolderStamp%.body preserve=yes
    //## end ZDFolderStamp::~ZDFolderStamp%.body
}

const ZDFolderStamp & ZDFolderStamp::operator=( const ZDFolderStamp &right )
{
    //## begin ZDFolderStamp::operator=%.body preserve=yes
    this->ZDStamp::operator=( (inherited&)right );

    m_FolderName            = right.m_FolderName;
    m_FolderDescription        = right.m_FolderDescription;
    m_CreationUserName        = right.m_CreationUserName;
    m_CreationDate            = right.m_CreationDate;
    m_ModificationUserName    = right.m_ModificationUserName;
    m_ModificationDate        = right.m_ModificationDate;
    m_Password                = right.m_Password;
    m_Key1                    = right.m_Key1;

    return *this;
    //## end ZDFolderStamp::operator=%.body
}

//## Other Operations (implementation)
CArchive& operator >> ( CArchive& ar, ZDFolderStamp& Stamp )
{
    //## begin ZDFolderStamp::operator >>%914061095.body preserve=yes
    ar >> (ZDStamp&)Stamp;

    if ( Stamp.GetInternalVersion() >= 11 )
    {
        ar >> Stamp.m_FolderName;
        ar >> Stamp.m_FolderDescription;
        ar >> Stamp.m_CreationUserName;

        // Not yet in ZBDate
        CTime time;

        if ( Stamp.GetInternalVersion() < 14 )
        {
            ar >> time;

            if ( time.GetTime() >= 0 )
            {
                Stamp.SetCreationDate( time );
            }
        }
        else
        {
            ar >> Stamp.m_CreationDate;
        }

        ar >> Stamp.m_ModificationUserName;

        // Not yet in ZBDate
        if ( Stamp.GetInternalVersion() < 14 )
        {
            ar >> time;

            if ( time.GetTime() >= 0 )
            {
                Stamp.SetModificationDate( time );
            }
        }
        else
        {
            ar >> Stamp.m_ModificationDate;
        }

        if ( Stamp.GetInternalVersion() < 13 )
        {
            LONG    lValue;
            CString    sValue;

            ar >> lValue;
            Stamp.SetPublishVersion( lValue );

            ar >> time;

            if ( time.GetTime() >= 0 )
            {
                Stamp.SetPublishDate( time );
            }

            ar >> sValue;
            Stamp.SetPublishUser( sValue );
        }
    }

    if ( Stamp.GetInternalVersion() >= 14 )
    {
        ar >> Stamp.m_Password;
    }

    if ( Stamp.GetInternalVersion() >= 15 )
    {
        ar >> Stamp.m_Key1;
    }

    return ar;
    //## end ZDFolderStamp::operator >>%914061095.body
}

CArchive& operator << ( CArchive& ar, const ZDFolderStamp& Stamp )
{
    //## begin ZDFolderStamp::operator <<%914061096.body preserve=yes
    ar << (ZDStamp&)Stamp;
    ar << Stamp.m_FolderName;
    ar << Stamp.m_FolderDescription;
    ar << Stamp.m_CreationUserName;
    ar << Stamp.m_CreationDate;
    ar << Stamp.m_ModificationUserName;
    ar << Stamp.m_ModificationDate;
    ar << Stamp.m_Password;
    ar << Stamp.m_Key1;

    return ar;
    //## end ZDFolderStamp::operator <<%914061096.body
}

BOOL ZDFolderStamp::ReadFromFile( CString Filename )
{
    //## begin ZDFolderStamp::ReadFromFile%927439023.body preserve=yes
    BOOL            RetValue = FALSE;
    CFile            file;
    CFileException    fe;

    if ( !file.Open( Filename, CFile::modeRead | CFile::shareDenyWrite, &fe ) )
    {
        return FALSE;
    }

    CArchive loadArchive( &file, CArchive::load | CArchive::bNoFlushOnDelete );

    loadArchive.m_pDocument        = NULL;
    loadArchive.m_bForceFlat    = FALSE;

    WORD wStamp = 0;

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
    if ( wStamp == 0xFFFF )
    {
        loadArchive >> *this;
        RetValue = TRUE;
    }

    loadArchive.Close();
    file.Close();

    return RetValue;
    //## end ZDFolderStamp::ReadFromFile%927439023.body
}

BOOL ZDFolderStamp::ClearPassword()
{
    //## begin ZDFolderStamp::ClearPassword%936298261.body preserve=yes
    m_Password.Empty();
    return TRUE;
    //## end ZDFolderStamp::ClearPassword%936298261.body
}

BOOL ZDFolderStamp::SetPassword( const CString Password )
{
    //## begin ZDFolderStamp::SetPassword%936298262.body preserve=yes
    m_Password = Password;
    return TRUE;
    //## end ZDFolderStamp::SetPassword%936298262.body
}

ZDFolderStamp* ZDFolderStamp::Clone()
{
    //## begin ZDFolderStamp::Clone%939754021.body preserve=yes
    ZDFolderStamp* pNewStamp = new ZDFolderStamp(*this);
    return pNewStamp;
    //## end ZDFolderStamp::Clone%939754021.body
}

// Additional Declarations
//## begin ZDFolderStamp%367B892D02BB.declarations preserve=yes
//## end ZDFolderStamp%367B892D02BB.declarations

//## begin module%367B896A0345.epilog preserve=yes
//## end module%367B896A0345.epilog
