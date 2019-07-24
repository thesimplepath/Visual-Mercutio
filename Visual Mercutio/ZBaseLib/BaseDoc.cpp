//## begin module%36CBF3570347.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%36CBF3570347.cm

//## begin module%36CBF3570347.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%36CBF3570347.cp

//## Module: BaseDoc%36CBF3570347; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\BaseDoc.cpp

//## begin module%36CBF3570347.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%36CBF3570347.additionalIncludes

//## begin module%36CBF3570347.includes preserve=yes
//## end module%36CBF3570347.includes

// BaseDoc
#include "BaseDoc.h"

//## begin module%36CBF3570347.declarations preserve=no
//## end module%36CBF3570347.declarations

//## begin module%36CBF3570347.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZDBaseDocument, CDocument, g_DefVersion )

BEGIN_MESSAGE_MAP( ZDBaseDocument, CDocument )
    //{{AFX_MSG_MAP(ZDDocumentRead)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//## end module%36CBF3570347.additionalDeclarations

ZDBaseDocument::ZDBaseDocument()
    //## begin ZDBaseDocument::ZDBaseDocument%.hasinit preserve=no
    //## end ZDBaseDocument::ZDBaseDocument%.hasinit
    //## begin ZDBaseDocument::ZDBaseDocument%.initialization preserve=yes
    //## end ZDBaseDocument::ZDBaseDocument%.initialization
{
    //## begin ZDBaseDocument::ZDBaseDocument%.body preserve=yes
    //## end ZDBaseDocument::ZDBaseDocument%.body
}

ZDBaseDocument::~ZDBaseDocument()
{
    //## begin ZDBaseDocument::~ZDBaseDocument%.body preserve=yes
    //## end ZDBaseDocument::~ZDBaseDocument%.body
}

//## Other Operations (implementation)
int ZDBaseDocument::SerializeStampRead( CArchive& ar, ZDFolderStamp& Stamp )
{
    //## begin ZDBaseDocument::SerializeStampRead%919330581.body preserve=yes
    WORD wStamp = 0;

    TRY
    {
        ar >> wStamp;
    }
    CATCH( CArchiveException, e )
    {
        return 0;
    }
    END_CATCH

    // Test if the stamp has been set
    // for next generation of files
    if ( wStamp == 0xFFFF )
    {
        ar >> Stamp;
    }

    return wStamp;
    //## end ZDBaseDocument::SerializeStampRead%919330581.body
}

void ZDBaseDocument::SerializeStampWrite( CArchive& ar, ZDFolderStamp& Stamp )
{
    //## begin ZDBaseDocument::SerializeStampWrite%919330582.body preserve=yes
    // First, sets the new version before writing to disk
    Stamp.SetInternalVersion(g_VersionFile);
    WORD wTemp = 0xFFFF;

    // Put the stamp for differentiate
    // the new generation of files
    ar << wTemp;
    ar << Stamp;
    //## end ZDBaseDocument::SerializeStampWrite%919330582.body
}

BOOL ZDBaseDocument::SaveDocument()
{
    //## begin ZDBaseDocument::SaveDocument%939754011.body preserve=yes
    return ( GetPathName().IsEmpty() ) ? FALSE : DoSave( GetPathName() );
    //## end ZDBaseDocument::SaveDocument%939754011.body
}

BOOL ZDBaseDocument::ReadDocument( const CString Filename )
{
    //## begin ZDBaseDocument::ReadDocument%939754012.body preserve=yes
    BOOL            RetValue = FALSE;
    CFile            file;
    CFileException    fe;

    if ( !file.Open( Filename, CFile::modeRead | CFile::shareDenyWrite, &fe ) )
    {
        return FALSE;
    }

    CArchive loadArchive( &file, CArchive::load | CArchive::bNoFlushOnDelete );

    loadArchive.m_pDocument        = this;
    loadArchive.m_bForceFlat    = FALSE;

    TRY
    {
        Serialize( loadArchive );
        RetValue = TRUE;
    }
    CATCH( CArchiveException, e )
    {
        RetValue = FALSE;
    }
    END_CATCH

    loadArchive.Close();
    file.Close();

    // If everything is ok, set the pathname.
    if ( RetValue )
    {
        SetPathName( Filename, FALSE );
    }

    return RetValue;
    //## end ZDBaseDocument::ReadDocument%939754012.body
}

// Additional Declarations
//## begin ZDBaseDocument%36CBF30603A4.declarations preserve=yes
//## end ZDBaseDocument%36CBF30603A4.declarations

//## begin module%36CBF3570347.epilog preserve=yes

void ZDBaseDocument::FillDocumentStampInformationForCreation( CString UserName )
{
    // Update dynamic information of the file stamp
    GetDocumentStamp().SetStampCreationDate( CTime::GetCurrentTime() );
}

void ZDBaseDocument::FillDocumentStampInformationForModification( CString UserName )
{
    // Update dynamic information of the file stamp
    GetDocumentStamp().SetStampModificationDate( CTime::GetCurrentTime() );
}

void ZDBaseDocument::FillDocumentStampInformationForPublication( CString UserName, LONG Version )
{
    // And therefore, updates the folder information for publishing
    GetDocumentStamp().SetPublishVersion( Version );
    GetDocumentStamp().SetPublishUser( UserName );
    GetDocumentStamp().SetPublishDate( CTime::GetCurrentTime() );
}

void ZDBaseDocument::FillFolderStampInformationForCreation( CString UserName )
{
    // And therefore, updates the folder information
    GetDocumentStamp().SetCreationUserName( UserName );
    GetDocumentStamp().SetCreationDate( CTime::GetCurrentTime() );
}

void ZDBaseDocument::FillFolderStampInformationForModification( CString UserName )
{
    // And therefore, updates the folder information
    GetDocumentStamp().SetModificationUserName( UserName );
    GetDocumentStamp().SetModificationDate( CTime::GetCurrentTime() );
}

/////////////////////////////////////////////////////////////////////////////
// ZDBaseDocument diagnostics

#ifdef _DEBUG
void ZDBaseDocument::AssertValid() const
{
    CDocument::AssertValid();
}

void ZDBaseDocument::Dump( CDumpContext& dc ) const
{
    CDocument::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZDBaseDocument serialization

void ZDBaseDocument::Serialize( CArchive& ar )
{
    // do write?
    if (ar.IsStoring())
        // write data
        SerializeStampWrite(ar, GetDocumentStamp());
    else
    {
        // read data
        const WORD wStamp = SerializeStampRead(ar, GetDocumentStamp());

        if (wStamp != 0xFFFF)
            AfxThrowArchiveException(CArchiveException::generic);

        if (GetDocumentStamp().GetInternalVersion() > g_VersionFile)
            AfxThrowArchiveException(CArchiveException::badSchema);
    }
}
