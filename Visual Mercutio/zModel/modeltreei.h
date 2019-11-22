/****************************************************************************
 * ==> PSS_ModelTree -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic model tree interface                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ModelTreeH
#define PSS_ModelTreeH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_ObjectCollections.h"

// class name mapping
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif

// forward class declaration
class ZDProcessGraphPage;
class PSS_TreeCtrl;
class ZBModelSet;
class ZBSymbol;
class PSS_LinkSymbol;
class ZDProcessGraphModelMdl;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 5 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Encapsulate information for the modeltree
class _ZInternalModelTreeData : public CObject
{
public:

    enum ModelTreeDataType
    {
        mdtp_Symbol,
        mdtp_LinkSymbol,
        mdtp_GraphPage,
        mdtp_Model,
        mdtp_String,
        mdtp_Unknown
    };

    _ZInternalModelTreeData();
    _ZInternalModelTreeData(ZBSymbol* pSymbol);
    _ZInternalModelTreeData(PSS_LinkSymbol* pLinkSymbol);
    _ZInternalModelTreeData(ZDProcessGraphPage* pGraphPage);
    _ZInternalModelTreeData(ZDProcessGraphModelMdl* pModel);
    _ZInternalModelTreeData(CString Str);
    ~_ZInternalModelTreeData();

    // Collapsed method. Used to keep the current state of an item
    bool IsCollapsed() const
    {
        return m_Collapsed;
    };

    void SetCollapsed(bool value = true)
    {
        m_Collapsed = value;
    };

    // Data member
    ModelTreeDataType       m_dtp;
    ZBSymbol*               m_pSymbol;
    PSS_LinkSymbol*         m_pLinkSymbol;
    ZDProcessGraphPage*     m_pGraphPage;
    ZDProcessGraphModelMdl* m_pModel;
    CString                 m_Str;
    bool                    m_Collapsed;
};

/**
* Basic model tree interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZIModelTree
{
public:

    ZIModelTree(PSS_TreeCtrl*        pTreeCtrl = NULL,
                const CString        RootName = _T(""),
                ZBModelSet*        pModelSet = NULL,
                UINT                nIDImageRes = -1,
                PSS_RuntimeClassSet*    pSet = NULL);

    virtual ~ZIModelTree();

    void Initialize(PSS_TreeCtrl*        pTreeCtrl,
                    const CString        RootName = _T(""),
                    ZBModelSet*        pModelSet = NULL,
                    UINT                nIDImageRes = -1,
                    PSS_RuntimeClassSet*    pSet = NULL);

    void SetRootName(const CString RootName);
    void Empty();
    void Refresh();

    ZDProcessGraphModelMdl*        GetSelectedModel();
    CODSymbolComponent*            GetSelectedSymbol();
    ZDProcessGraphPage*            GetSelectedPage();
    ZDProcessGraphModelMdl*        GetSelectedOwnerModel();

    bool IsRootSelected() const;
    bool IsDocumentSelected() const;

    void AddModel(ZDProcessGraphModelMdl* pModel);
    void RemoveModel(ZDProcessGraphModelMdl* pModel);

    void AddModelSet(ZBModelSet* pModelSet);
    void RemoveModelSet(ZBModelSet* pModelSet);

    void AddSymbol(CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel = NULL, bool CheckUnique = true);
    void RemoveSymbol(CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel = NULL);
    void ModifySymbol(CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel = NULL);

public:

    void OnModelChange();
    void OnDoubleClick();
    void DoSelectSymbol();

    CODSymbolComponent* GetSymbol(HTREEITEM hItem);
    ZDProcessGraphModelMdl* GetModel(HTREEITEM hItem);
    ZDProcessGraphPage* GetPage(HTREEITEM hItem);
    ZDProcessGraphModelMdl* GetOwnerModel(HTREEITEM hItem);

private:

    ZIModelTree(const ZIModelTree &right);
    const ZIModelTree & operator=(const ZIModelTree &right);

    void CreateTree();
    void InitializeTree();
    bool CreateEmptyModelSet();
    void FreeModelSet();

    bool ModelSetExist() const
    {
        return m_pModelSet != NULL;
    };

    bool SymbolIsPartOfSet(CODComponent* pSymbol) const;

protected:

    void ProcessModelSet(ZBModelSet* pModelSet, HTREEITEM hParentTreeItem);
    void ProcessRootModel(ZDProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem);
    void ProcessModelByPageSet(ZDProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem);
    void ProcessModel(ZDProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem);
    void ProcessSymbol(ZBSymbol* pSymbol, HTREEITEM hParentTreeItem);
    void ProcessLinkSymbol(PSS_LinkSymbol* pSymbol, HTREEITEM hParentTreeItem);

    HTREEITEM AddTypeItem(const CString Name, int IconIndex, HTREEITEM hParentTreeItem = NULL);
    HTREEITEM AddModelItem(ZDProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem);
    HTREEITEM AddSymbolItem(ZBSymbol* pSymbol, HTREEITEM hParentTreeItem);
    HTREEITEM AddLinkSymbolItem(PSS_LinkSymbol* pSymbol, HTREEITEM hParentTreeItem);
    HTREEITEM AddPageItem(ZDProcessGraphPage* pPage, HTREEITEM hParentTreeItem);

    BOOL ModifyModelItem(ZDProcessGraphModelMdl* pModel, HTREEITEM hItem);
    BOOL ModifySymbolItem(ZBSymbol* pSymbol, HTREEITEM hItem);
    BOOL ModifyLinkSymbolItem(PSS_LinkSymbol* pSymbol, HTREEITEM hItem);
    BOOL ModifyPageItem(ZDProcessGraphPage* pPage, HTREEITEM hItem);

private:

    void EmptyDataSet();

    _ZInternalModelTreeData* FindElementFromDataSet(CODSymbolComponent* pSymbol);
    _ZInternalModelTreeData* FindElementFromDataSet(ZBSymbol* pSymbol);
    _ZInternalModelTreeData* FindElementFromDataSet(PSS_LinkSymbol* pLinkSymbol);
    _ZInternalModelTreeData* FindElementFromDataSet(ZDProcessGraphPage* pGraphPage);
    _ZInternalModelTreeData* FindElementFromDataSet(ZDProcessGraphModelMdl* pModel);
    _ZInternalModelTreeData* FindElementFromDataSet(CString Str);

    _ZInternalModelTreeData* AddDataToSet(ZBSymbol* pSymbol);
    _ZInternalModelTreeData* AddDataToSet(PSS_LinkSymbol* pLinkSymbol);
    _ZInternalModelTreeData* AddDataToSet(ZDProcessGraphPage* pGraphPage);
    _ZInternalModelTreeData* AddDataToSet(ZDProcessGraphModelMdl* pModel);
    _ZInternalModelTreeData* AddDataToSet(CString Str);

    bool DeleteElementFromDataSet(CODSymbolComponent* pSymbol);
    bool DeleteElementFromDataSet(ZBSymbol* pSymbol);
    bool DeleteElementFromDataSet(PSS_LinkSymbol* pLinkSymbol);
    bool DeleteElementFromDataSet(ZDProcessGraphPage* pGraphPage);
    bool DeleteElementFromDataSet(ZDProcessGraphModelMdl* pModel);
    bool DeleteElementFromDataSet(CString Str);

protected:

    HTREEITEM                    m_hRootDocument;
    ZBModelSet*                    m_pModelSet;
    BOOL                        m_HasBeenInitialized;
    PSS_TreeCtrl*                  m_pTreeCtrl;
    CString                        m_RootName;
    UINT                        m_nIDImageRes;

private:

    //@type ZBProcessGraphPageSet | An array of _ZInternalModelTreeData pointers.
    //@iex typedef CCArray_T<_ZInternalModelTreeData*,_ZInternalModelTreeData*> _ZInternalModelTreeDataSet;
    typedef sfl::CCArray_T<_ZInternalModelTreeData*, _ZInternalModelTreeData*> _ZInternalModelTreeDataSet;

    //@type _ZInternalModelTreeDataIterator | An iterator for _ZInternalModelTreeDataSet collections.
    //@iex typedef Iterator_T<_ZInternalModelTreeData*> _ZInternalModelTreeDataIterator;
    typedef sfl::Iterator_T<_ZInternalModelTreeData*> _ZInternalModelTreeDataIterator;

    _ZInternalModelTreeDataSet    m_DataSet;

    // Set of elements that can be displayed in the tree
    PSS_RuntimeClassSet*            m_pSet;
};

#endif
