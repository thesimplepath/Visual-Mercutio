// Source file: fieldtreei.h

#ifndef FieldTreeI_h
#define FieldTreeI_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\ZITreeCtl.h"
#include "zBaseLib\ZDDoc.h"
#include "zBaseLib\FieldRep.h"


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



class AFX_EXT_CLASS ZIFieldTree
{
  public:
      ZIFieldTree (ZITreeCtrl* pTreeCtrl = NULL, ZDDocument* pDoc = NULL, ZBFieldRepository* pFieldRepository = NULL);
      virtual ~ZIFieldTree();
      void Initialize(ZITreeCtrl* pTreeCtrl, ZDDocument* pDoc, ZBFieldRepository* pFieldRepository = NULL);
      void Empty();
      void Refresh();
      ZAObjectDefinition* GetSelectedRepositoryField ();
      PlanFinObject* GetSelectedDocumentField ();


  public:
    void    OnFieldListChanged();

  private:
      ZIFieldTree(const ZIFieldTree &right);
      const ZIFieldTree & operator=(const ZIFieldTree &right);
      void    CreateTree();
      void    InitializeTree();

  protected:
    HTREEITEM    AddTypeItem (const CString FieldType, int IconIndex, HTREEITEM hParentTreeItem = NULL);
    HTREEITEM    AddDocumentItem (ZDDocumentData* pData, HTREEITEM hParentTreeItem, int IconIndex);
    void        AddRepositoryFieldItem (ZAObjectDefinition* pField, HTREEITEM hParentTreeItem);
    HTREEITEM    AddDocumentFieldItem( PlanFinObject* pObj, HTREEITEM hParentTreeItem );
    int            GetItemIndex( PlanFinObject* pObj );

  protected: 
    ZDDocument*            m_pDoc;
    ZBFieldRepository*    m_pFieldRepository;
    BOOL                m_HasBeenInitialized;
    CString                m_DocumentType;
    CString                m_RepositoryType;
    CString                m_NoDocument;
    CString                m_NoRepository;
    ZITreeCtrl*            m_pTreeCtrl;

};

//#undef  AFX_DATA
//#define AFX_DATA

#endif
