/****************************************************************************
 * ==> PSS_BaseDocument ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic document                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BaseDocumentH
#define PSS_BaseDocumentH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_BaseDocument
    #define PSS_BaseDocument ZDBaseDocument
#endif

// processsoft
#include "PSS_FolderStamp.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Basic document
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BaseDocument : public CDocument
{
    DECLARE_SERIAL(PSS_BaseDocument)

    public:
        typedef CDocument inherited;

        virtual ~PSS_BaseDocument();

        /**
        * Reads the document
        *@param fileName - document file name to read
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ReadDocument(const CString& fileName);

        /**
        * Saves the document without prompt
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveDocument();

        /**
        * Gets the document file stamp
        *@return the document file stamp
        */
        virtual inline PSS_FolderStamp& GetDocumentStamp();

        /**
        * Clears the path name
        */
        virtual inline void ClearPathName();

        /**
        * Checks if document contains a form
        *@return TRUE if document contains a form, otherwise FALSE
        */
        virtual inline BOOL DocumentTypeIsForm() const;

        /**
        * Checks if document contains a process
        *@return TRUE if document contains a process, otherwise FALSE
        */
        virtual inline BOOL DocumentTypeIsProcess() const;

        /**
        * Checks if document contains a model
        *@return TRUE if document contains a model, otherwise FALSE
        */
        virtual inline BOOL DocumentTypeIsModel() const;

        /**
        * Checks if document contains a document
        *@return TRUE if document contains a document, otherwise FALSE
        */
        virtual inline BOOL DocumentIsDocument() const;

        /**
        * Checks if document contains a template
        *@return TRUE if document contains a template, otherwise FALSE
        */
        virtual inline BOOL DocumentIsTemplate() const;

        /**
        * Checks if document contains a library
        *@return TRUE if document contains a library, otherwise FALSE
        */
        virtual inline BOOL DocumentIsLibrary() const;

        /**
        * Checks if the document is read-only
        *@return TRUE if the document is read-only, otherwise FALSE
        */
        virtual inline BOOL IsReadOnly();

        /**
        * Sets the document as read-only
        *@param value - if TRUE, the document is read-only
        */
        virtual inline void SetAsReadOnly(BOOL value = TRUE);

        /**
        * Clears the existing password
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL ClearPassword();

        /**
        * Sets a new password
        *@param password - new password to set
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL SetPassword(const CString& password);

        /**
        * Checks if the document is password protected
        *@return true if the document is password protected, otherwise FALSE
        */
        virtual inline BOOL HasPassword();

        /**
        * Checks if the form is standard
        *@return TRUE if the form is standard, otherwise FALSE
        */
        virtual inline BOOL IsStandardForm();

        /**
        * Checks if the ke is equals to the standard form
        *@param key - key to check
        *@return TRUE if the key is equals to the standard form, otherwise FALSE
        */
        virtual inline BOOL IsInternalKeyEqualTo(const CString& key);

        /**
        * Sets the document type
        *@param value - new document type to set
        */
        virtual inline void SetDocumentType(const PSS_Stamp::IEDocumentFileType value);

        /**
        * Sets the file type
        *@param value - new file type to set
        */
        virtual inline void SetFileType(const PSS_Stamp::IEFileTypeDefinition value);

        /**
        * Fills the document information stamp during the document creation
        *@param userName - user name
        */
        virtual void FillDocumentStampInformationForCreation(const CString& userName);

        /**
        * Fills the document information stamp during the document modification
        *@param userName - user name
        */
        virtual void FillDocumentStampInformationForModification(const CString& userName);

        /**
        * Fills the document information stamp during the document publication
        *@param userName - user name
        *@param version - version
        */
        virtual void FillDocumentStampInformationForPublication(const CString& userName, LONG version);

        /**
        * Fills the folder information stamp during the document creation
        *@param userName - user name
        */
        virtual void FillFolderStampInformationForCreation(const CString& userName);

        /**
        * Fills the folder information stamp during the document modification
        *@param userName - user name
        */
        virtual void FillFolderStampInformationForModification(const CString& userName);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Reads the file stamp
        *@param archive - archive from which document should be read
        *@param[out] stamp - folder stamp to read
        *@return the file stamp
        */
        static int ReadFileStamp(CArchive& archive, PSS_FolderStamp& stamp);

        /**
        * Writes the file stamp
        *@param archive - archive in which file stamp should be written
        *@param stamp - file stamp to write
        */
        static void WriteFileStamp(CArchive& archive, PSS_FolderStamp& stamp);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        PSS_BaseDocument();

        /// Generated message map
        //{{AFX_MSG(PSS_BaseDocument)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Requests to save the template
        *@param userName - user name
        */
        virtual inline BOOL RequestSaveTemplate(const CString& userName = _T(""));

    private:
        PSS_FolderStamp m_DocumentStamp;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_BaseDocument(const PSS_BaseDocument& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_BaseDocument& operator = (const PSS_BaseDocument& other);
};

//---------------------------------------------------------------------------
// PSS_BaseDocument
//---------------------------------------------------------------------------
PSS_FolderStamp& PSS_BaseDocument::GetDocumentStamp()
{
    return m_DocumentStamp;
}
//---------------------------------------------------------------------------
void PSS_BaseDocument::SetDocumentType(const PSS_Stamp::IEDocumentFileType value)
{
    GetDocumentStamp().SetDocumentFileType(value);
}
//---------------------------------------------------------------------------
void PSS_BaseDocument::SetFileType(const PSS_Stamp::IEFileTypeDefinition value)
{
    GetDocumentStamp().SetFileType(value);
}
//---------------------------------------------------------------------------
void PSS_BaseDocument::ClearPathName()
{
    m_strPathName.Empty();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseDocument::DocumentTypeIsForm() const
{
    return m_DocumentStamp.GetDocumentFileType() == PSS_Stamp::IE_FT_FormDocument;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseDocument::DocumentTypeIsProcess() const
{
    return m_DocumentStamp.GetDocumentFileType() == PSS_Stamp::IE_FT_ProcessDocument;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseDocument::DocumentTypeIsModel() const
{
    return m_DocumentStamp.GetDocumentFileType() == PSS_Stamp::IE_FT_ModelDocument;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseDocument::DocumentIsDocument() const
{
    return m_DocumentStamp.GetFileType() == PSS_Stamp::IE_FD_DocumentType;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseDocument::DocumentIsTemplate() const
{
    return m_DocumentStamp.GetFileType() == PSS_Stamp::IE_FD_TemplateType;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseDocument::DocumentIsLibrary() const
{
    return m_DocumentStamp.GetFileType() == PSS_Stamp::IE_FD_LibraryType;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseDocument::IsReadOnly()
{
    return GetDocumentStamp().IsReadOnly();
}
//---------------------------------------------------------------------------
void PSS_BaseDocument::SetAsReadOnly(BOOL value)
{
    GetDocumentStamp().SetAsReadOnly(value);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseDocument::ClearPassword()
{
    return GetDocumentStamp().ClearPassword();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseDocument::SetPassword(const CString& password)
{
    return GetDocumentStamp().SetPassword(password);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseDocument::HasPassword()
{
    return GetDocumentStamp().HasPassword();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseDocument::IsStandardForm()
{
    return GetDocumentStamp().IsStandardForm();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseDocument::IsInternalKeyEqualTo(const CString& key)
{
    return GetDocumentStamp().IsInternalKeyEqualTo(key);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseDocument::RequestSaveTemplate(const CString& userName)
{
    return FALSE;
}
//---------------------------------------------------------------------------

#endif
