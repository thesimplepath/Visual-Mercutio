// ******************************************************************************************************************
// *                                             Class ZDBaseDocument                                                *
// ******************************************************************************************************************

//## begin module%36CBF364022D.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%36CBF364022D.cm

//## begin module%36CBF364022D.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%36CBF364022D.cp

//## Module: BaseDoc%36CBF364022D; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\BaseDoc.h

#ifndef BaseDoc_h
#define BaseDoc_h 1

//## begin module%36CBF364022D.additionalIncludes preserve=no
//## end module%36CBF364022D.additionalIncludes

//## begin module%36CBF364022D.includes preserve=yes
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%36CBF364022D.includes

// FldStamp
#include "FldStamp.h"

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// ******************************************************************************************************************
// *                                                Class declaration                                                *
// ******************************************************************************************************************

class AFX_EXT_CLASS ZDBaseDocument : public CDocument    //## Inherits: <unnamed>%36CBF3220174
{
protected:

    DECLARE_SERIAL( ZDBaseDocument )

    //## Constructors (generated)
    ZDBaseDocument();

private:

    //## Constructors (generated)
    ZDBaseDocument( const ZDBaseDocument &right );

    //## Assignment Operation (generated)
    const ZDBaseDocument & operator=( const ZDBaseDocument &right );

public:

    //## begin ZDBaseDocument%36CBF30603A4.initialDeclarations preserve=yes
    // Inherited feature
    typedef CDocument inherited;
    //## end ZDBaseDocument%36CBF30603A4.initialDeclarations

    //## Destructor (generated)
    virtual ~ZDBaseDocument();

    //    Serialize document information.
    virtual void Serialize( CArchive& ar );

    //## Other Operations (specified)
    //## Operation: SerializeStampRead%919330581
    //    Read the file stamp.
    static int SerializeStampRead( CArchive& ar, ZDFolderStamp& Stamp );

    //## Operation: SerializeStampWrite%919330582
    //    Write the file stamp.
    static void SerializeStampWrite( CArchive& ar, ZDFolderStamp& Stamp );

    //## Operation: SaveDocument%939754011
    //    Save the document without prompt.
    virtual BOOL SaveDocument();

    //## Operation: ReadDocument%939754012
    //    Read the document.
    virtual BOOL ReadDocument( const CString Filename );

    //## Get and Set Operations for Class Attributes (generated)

    //## Attribute: DocumentStamp%36CBF3B00381
    //    Contains the document file stamp.
    ZDFolderStamp& GetDocumentStamp();

    // Additional Public Declarations
    //## begin ZDBaseDocument%36CBF30603A4.public preserve=yes

    BOOL DocumentTypeIsForm() const;
    BOOL DocumentTypeIsProcess() const;
    BOOL DocumentTypeIsModel() const;
    BOOL DocumentIsDocument() const;
    BOOL DocumentIsTemplate() const;
    BOOL DocumentIsLibrary() const;

    // return TRUE if the document is read-only.
    BOOL IsReadOnly();

    // Set the file as read-only.
    void SetAsReadOnly( BOOL value = TRUE );

    // Clear the existing password.
    BOOL ClearPassword();

    // Set a new password.
    BOOL SetPassword( const CString Password );

    // Return true if the document is password protected.
    BOOL HasPassword();

    // return TRUE if the form is standard.
    BOOL IsStandardForm();

    // return TRUE if the key is equal to the standard form.
    BOOL IsInternalKeyEqualTo( const CString Key );

    // Change the document type of the file.
    void SetDocumentType( const DocumentFileType value );

    // Change the type of the file.
    void SetFileType( const FileTypeDefinition value );

    // Clear the path name.
    void ClearPathName();

    // Fill the document information stamp during the document
    // creation.
    virtual void FillDocumentStampInformationForCreation( CString UserName );

    // Fill the document information stamp during the document
    // modification.
    virtual void FillDocumentStampInformationForModification( CString UserName );

    // Fill the document information stamp during the document
    // publication.
    virtual void FillDocumentStampInformationForPublication( CString UserName, LONG Version );

    // Fill the folder information stamp during the document
    // creation.
    virtual void FillFolderStampInformationForCreation( CString UserName );

    // Fill the folder information stamp during the document
    // modification.
    virtual void FillFolderStampInformationForModification( CString UserName );

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif
    //## end ZDBaseDocument%36CBF30603A4.public

// Additional Protected Declarations
protected:

    //## begin ZDBaseDocument%36CBF30603A4.protected preserve=yes
    //{{AFX_MSG(ZDBaseDocument)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    //    Request to save the template.
    virtual BOOL RequestSaveTemplate( CString UserName = _T( "" ) )
    {
        return FALSE;
    };
    //## end ZDBaseDocument%36CBF30603A4.protected

// Data Members for Class Attributes
private:

    //## begin ZDBaseDocument::DocumentStamp%36CBF3B00381.attr preserve=no  public: ZDFolderStamp {U}
    ZDFolderStamp m_DocumentStamp;
    //## end ZDBaseDocument::DocumentStamp%36CBF3B00381.attr

// Additional Private Declarations
private:

    //## begin ZDBaseDocument%36CBF30603A4.private preserve=yes
    //## end ZDBaseDocument%36CBF30603A4.private

// Additional Implementation Declarations
private:

    //## begin ZDBaseDocument%36CBF30603A4.implementation preserve=yes
    //## end ZDBaseDocument%36CBF30603A4.implementation
};

// ******************************************************************************************************************
// *                                Get and Set Operations for Class Attributes (inline)                            *
// ******************************************************************************************************************

inline ZDFolderStamp& ZDBaseDocument::GetDocumentStamp()
{
    //## begin ZDBaseDocument::GetDocumentStamp%36CBF3B00381.get preserve=no
    return m_DocumentStamp;
    //## end ZDBaseDocument::GetDocumentStamp%36CBF3B00381.get
}

inline void ZDBaseDocument::SetDocumentType( const DocumentFileType value )
{
    GetDocumentStamp().SetDocumentFileType( value );
}

inline void ZDBaseDocument::SetFileType( const FileTypeDefinition value )
{
    GetDocumentStamp().SetFileType( value );
}

inline void ZDBaseDocument::ClearPathName()
{
    m_strPathName.Empty();
}

inline BOOL ZDBaseDocument::DocumentTypeIsForm() const
{
    return m_DocumentStamp.GetDocumentFileType() == FormDocumentFileType;
}

inline BOOL ZDBaseDocument::DocumentTypeIsProcess() const
{
    return m_DocumentStamp.GetDocumentFileType() == ProcessDocumentFileType;
}

inline BOOL ZDBaseDocument::DocumentTypeIsModel() const
{
    return m_DocumentStamp.GetDocumentFileType() == ModelDocumentFileType;
}

inline BOOL ZDBaseDocument::DocumentIsDocument() const
{
    return m_DocumentStamp.GetFileType() == DocumentType;
}

inline BOOL ZDBaseDocument::DocumentIsTemplate() const
{
    return m_DocumentStamp.GetFileType() == TemplateType;
}

inline BOOL ZDBaseDocument::DocumentIsLibrary() const
{
    return m_DocumentStamp.GetFileType() == LibraryType;
}

inline BOOL ZDBaseDocument::IsReadOnly()
{
    return GetDocumentStamp().IsReadOnly();
}

inline void ZDBaseDocument::SetAsReadOnly( BOOL value )
{
    GetDocumentStamp().SetAsReadOnly( value );
}

inline BOOL ZDBaseDocument::ClearPassword()
{
    return GetDocumentStamp().ClearPassword();
}

inline BOOL ZDBaseDocument::SetPassword( const CString Password )
{
    return GetDocumentStamp().SetPassword( Password );
}

inline BOOL ZDBaseDocument::HasPassword()
{
    return GetDocumentStamp().HasPassword();
}

inline BOOL ZDBaseDocument::IsStandardForm()
{
    return GetDocumentStamp().IsStandardForm();
}

inline BOOL ZDBaseDocument::IsInternalKeyEqualTo( const CString Key )
{
    return GetDocumentStamp().IsInternalKeyEqualTo( Key );
}

//## begin module%36CBF364022D.epilog preserve=yes
//## end module%36CBF364022D.epilog

#endif

// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin ZDBaseDocument%36CBF30603A4.preface preserve=no

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_DATA
//## end ZDBaseDocument%36CBF30603A4.preface
#endif
