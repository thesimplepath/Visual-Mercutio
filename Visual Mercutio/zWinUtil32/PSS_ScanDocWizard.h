/****************************************************************************
 * ==> PSS_ScanDocWizard ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a scan documents Wizard                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ScanDocWizardH
#define PSS_ScanDocWizardH

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
* Scan documents Wizard
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ScanDocWizard
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

        PSS_ScanDocWizard();
        virtual ~PSS_ScanDocWizard();

        /**
        * Executes the wizard
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Execute();

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
        PSS_ScanDocWizard(const PSS_ScanDocWizard& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ScanDocWizard & operator = (const PSS_ScanDocWizard& other);

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
// PSS_ScanDocWizard
//---------------------------------------------------------------------------
std::size_t PSS_ScanDocWizard::GetDocumentCount() const
{
    return m_Doc.GetSize();
}
//---------------------------------------------------------------------------

#endif
