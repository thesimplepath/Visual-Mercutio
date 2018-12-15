// Source file: ProjectI.h

#ifndef ProjectI_h
#define ProjectI_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


/////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZDDocument;
class ZDDocumentData;
class ZITreeCtrl;




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



class AFX_EXT_CLASS ZIProjectTree
{
  public:
      ZIProjectTree (ZITreeCtrl* pTreeCtrl = NULL, ZDDocument* pDoc = NULL, BOOL OnlyVisible = TRUE);
      virtual ~ZIProjectTree();
      void Initialize(ZITreeCtrl* pTreeCtrl, ZDDocument* pDoc, BOOL OnlyVisible = TRUE);
      void Empty();
      void Refresh();
      ZDDocumentData*    GetSelectedDocument();
      CString            GetSelectedDocumentTitle();


  public:
    void    OnFileListChanged();

  private:
      ZIProjectTree(const ZIProjectTree &right);
      const ZIProjectTree & operator=(const ZIProjectTree &right);
      void    CreateTree();
      void    InitializeTree();

  protected:
    HTREEITEM    AddDocumentTypeItem (const CString DocumentType, int IconIndex, HTREEITEM hParent = NULL);
    HTREEITEM    AddDocumentItem (ZDDocumentData* pData, HTREEITEM hParentTreeItem, int IconIndex);

  protected: 
    ZDDocument*        m_pDoc;
    BOOL            m_OnlyVisible;
    BOOL            m_HasBeenInitialized;
    CString            m_InternalDocumentType;
    CString            m_ExternalDocumentType;
    ZITreeCtrl*        m_pTreeCtrl;

};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
