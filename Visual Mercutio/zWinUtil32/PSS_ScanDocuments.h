/****************************************************************************
 * ==> PSS_ScanDocuments ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a scan documents manager                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ScanDocumentsH
#define PSS_ScanDocumentsH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Scan documents manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ScanDocuments
{
    public:
        /**
        * Document
        */
        class IDocument
        {
            public:
                CString m_FileName;
                CString m_Name;
                CString m_Description;

                /**
                * Constructor
                *@param fileName - file name
                *@param name - name
                *@param description - description
                */
                IDocument(const CString& fileName = "", const CString& name = "", const CString& description = "");

                virtual ~IDocument();
        };

        PSS_ScanDocuments();
        virtual ~PSS_ScanDocuments();

        /**
        * Selects the documents
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SelectDocuments();

        /**
        * Gets the document count
        *@return the document count
        */
        virtual inline std::size_t GetDocumentCount() const;

        /**
        * Gets the document at index
        *@param index - index
        *@return the document at index, NULL if not found or on error
        */
        virtual IDocument* GetDocumentAt(std::size_t index);

    private:
        CObArray m_Doc;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ScanDocuments(const PSS_ScanDocuments& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ScanDocuments & operator = (const PSS_ScanDocuments& other);

        /**
        * Adds a document
        *@param fileName - file name
        *@param name - name
        *@param description - description
        */
        void AddDocument(const CString& fileName, const CString& name, const CString& description = "");

        /**
        * Processes to the selection
        *@return TRUE on sucess, otherwise FASLE
        */
        BOOL ProcessSelection();
};

//---------------------------------------------------------------------------
// PSS_ScanDocuments
//---------------------------------------------------------------------------
std::size_t PSS_ScanDocuments::GetDocumentCount() const
{
    return m_Doc.GetSize();
}
//---------------------------------------------------------------------------

#endif
