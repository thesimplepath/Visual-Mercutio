#if !defined(AFX_ZCSymbolAttributesTreeCtrl_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_)
#define AFX_ZCSymbolAttributesTreeCtrl_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZCSymbolAttributesTreeCtrl.h : header file
//


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#include "zBaseLib\ZISubject.h"
#include "zBaseLib\ZIObserver.h"
#include "zBaseLib\ZITreeCtl.h"
#include "zProperty\ZIProperties.h"

/////////////////////////////////////////////////////////////////////////////
// Forward declaration
class ZBPropertyAttributes;
class _ZBPropertyAttribute;


#ifdef _ZMODELEXPORT
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


// Encapsulate information for the modeltree
class _ZInternalPropertyTreeData : public CObject
{
public:
    enum UserGroupTreeDataType { patp_Category, 
                                 patp_Item, 
                                 patp_Unknown };

    _ZInternalPropertyTreeData();
    _ZInternalPropertyTreeData(_ZBPropertyAttribute* pPropAttribute);
    _ZInternalPropertyTreeData(int Category, int Item = -1);
    ~_ZInternalPropertyTreeData();

    // Data member
    UserGroupTreeDataType m_dtp;
    _ZBPropertyAttribute* m_pPropAttribute;
};

/////////////////////////////////////////////////////////////////////////////
// ZCSymbolAttributesTreeCtrl window

class AFX_EXT_CLASS ZCSymbolAttributesTreeCtrl : public ZITreeCtrl, public ZISubject, public ZIObserver
{
// Construction
public:
    ZCSymbolAttributesTreeCtrl(ZBPropertyAttributes* pPropAttributes = NULL, 
                               ZBPropertySet* pPropSet = NULL);

    virtual ~ZCSymbolAttributesTreeCtrl();

// Operations
public:
    void Initialize();
    void Initialize(ZBPropertyAttributes* pPropAttributes, ZBPropertySet* pPropSet);
    void Refresh();

    bool FillCorrespondingCheckedItems();

    ////////////////////////////////////////////////////////////////////
    // ZIObserver call back
    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

protected:
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCSymbolAttributesTreeCtrl)
    virtual BOOL DestroyWindow();
    //}}AFX_VIRTUAL



    // Generated message map functions
protected:
    //{{AFX_MSG(ZCSymbolAttributesTreeCtrl)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnItemExpanded(LPNMHDR pnmhdr, LRESULT *pLResult);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

protected:
    virtual int GetIndexOfNoDropImage() const;
    virtual CObject* GetDragObject( HTREEITEM DragItem );

private:
    bool                 m_HasBeenInitialized;

private:
    void CreateTree();
    void LoadTree();
    void DestroyTree();


  private:

    bool ProcessProperty( ZBProperty* pProp );
    HTREEITEM GetParentProperty( ZBProperty* pProp );
    void CheckAttribute( _ZBPropertyAttribute* pAttribute );

    HTREEITEM AddPropertyItem (const CString Label, int Category, int Item = -1, HTREEITEM hParentTreeItem = NULL);


    void EmptyDataSet();
    _ZInternalPropertyTreeData* FindElementFromDataSet(int Category, int Item = -1);
    _ZInternalPropertyTreeData* FindElementFromDataSet(_ZBPropertyAttribute* pPropAttribute);

    _ZInternalPropertyTreeData* AddDataToSet(int Category, int Item = -1);
    _ZInternalPropertyTreeData* AddDataToSet(_ZBPropertyAttribute* pPropAttribute);

  private:
    //@type ZBProcessGraphPageSet | An array of _ZInternalPropertyTreeData pointers.
    //@iex typedef CCArray_T<_ZInternalPropertyTreeData*,_ZInternalPropertyTreeData*> _ZInternalPropertyTreeDataSet;
    typedef sfl::CCArray_T<_ZInternalPropertyTreeData*,_ZInternalPropertyTreeData*> _ZInternalPropertyTreeDataSet;

    //@type _ZInternalPropertyTreeDataIterator | An iterator for _ZInternalPropertyTreeDataSet collections.
    //@iex typedef Iterator_T<_ZInternalPropertyTreeData*> _ZInternalPropertyTreeDataIterator;
    typedef sfl::Iterator_T<_ZInternalPropertyTreeData*> _ZInternalPropertyTreeDataIterator;

    _ZInternalPropertyTreeDataSet    m_DataSet;


    ZBPropertyAttributes* m_pPropAttributes;
    ZBPropertySet* m_pPropSet;

};


inline int ZCSymbolAttributesTreeCtrl::GetIndexOfNoDropImage() const
{
    return 4;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZCSymbolAttributesTreeCtrl_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_)
