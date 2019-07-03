//    Advanced Dedicated Software
//    Dominique AIGROZ
//  Source file: ScanDoc.h

#ifndef SrvChoos_h
#define SrvChoos_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#ifdef _ZWINUTIL32EXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

class AFX_EXT_CLASS ZIScanDocuments 
{
  public:  
    class Document
    {
        public:
            Document( const CString Filename = "", const CString Name = "", const CString Description = "" );
            ~Document();

            CString m_Filename;
            CString m_Name;
            CString m_Description;
    };

  public:
    ZIScanDocuments();
    ~ZIScanDocuments();


    BOOL ChooseDocuments ();
    size_t    GetDocumentCount() { return m_Doc.GetSize(); };
    ZIScanDocuments::Document*    GetDocumentAt( size_t Index );


    
  protected:

  private:
    ZIScanDocuments(const ZIScanDocuments &right);
    const ZIScanDocuments & operator=(const ZIScanDocuments &right);


    BOOL ProcessChoose ();
    void AddDocument( const CString Filename, const CString Name, const CString Description = "" );


  private:
    CObArray    m_Doc;

};



#endif
