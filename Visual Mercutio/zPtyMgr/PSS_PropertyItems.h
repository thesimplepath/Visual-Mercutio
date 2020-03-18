/****************************************************************************
 * ==> PSS_PropertyItems ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides the property items                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PropertyItemsH
#define PSS_PropertyItemsH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zProperty\PSS_PropertyItem.h"

// forward class declaration
class PSS_InPlaceListBox;
class PSS_InPlaceIntelliEdit;
class ZCInPlaceMultiLineEdit;

#ifdef _ZPTYMGREXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* String property item
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_StringPropertyItem : public PSS_PropertyItem
{
    DECLARE_DYNAMIC(PSS_StringPropertyItem)

    public:
        /**
        * Constructor
        *@param pName - the item name
        *@param isReadOnly - if true, the item is read-only
        *@param canBeEdited - if true, the item can be edited
        */
        inline PSS_StringPropertyItem(LPCTSTR pName = NULL, bool isReadOnly = false, bool canBeEdited = true);

        virtual inline ~PSS_StringPropertyItem();

        /**
        * Draws the value
        *@param pDc - device context to draw on
        *@param rect - the rect surrounding the value to draw
        */
        virtual inline void DrawValue(CDC* pDC, CRect& rect);

        /**
        * Creates an in-place control
        *@param pWndParent - the parent window
        *@param rect - the rectangle surrounding the control to create
        *@param[out] pWndInPlaceControl - the newly created in-place control window on function ends
        *@param extendedSize - the control extended size
        */
        virtual void CreateInPlaceControl(CWnd*             pWndParent,
                                          const CRect&      rect,
                                          PSS_InPlaceEdit*& pWndInPlaceControl,
                                          const CSize&      extendedSize = CSize(0, 0));

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_StringPropertyItem(const PSS_StringPropertyItem& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_StringPropertyItem& operator = (const PSS_StringPropertyItem& other);
};

//---------------------------------------------------------------------------
// PSS_StringPropertyItem
//---------------------------------------------------------------------------
PSS_StringPropertyItem::PSS_StringPropertyItem(LPCTSTR pName, bool isReadOnly, bool canBeEdited) :
    PSS_PropertyItem(pName, isReadOnly, canBeEdited)
{}
//---------------------------------------------------------------------------
PSS_StringPropertyItem::~PSS_StringPropertyItem()
{}
//---------------------------------------------------------------------------
void PSS_StringPropertyItem::DrawValue(CDC* pDC, CRect& rect)
{
    pDC->DrawText(m_StrValue, &rect, DT_SINGLELINE | DT_VCENTER);
}
//---------------------------------------------------------------------------

/**
* List property item
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ListPropertyItem : public PSS_PropertyItem
{
    DECLARE_DYNAMIC(PSS_ListPropertyItem)

    public:
        /**
        * Constructor
        *@param pName - the item name
        *@param isReadOnly - if true, the item is read-only
        *@param canBeEdited - if true, the item can be edited
        */
        inline PSS_ListPropertyItem(LPCTSTR pName = NULL, bool isReadOnly = false, bool canBeEdited = true);

        virtual inline ~PSS_ListPropertyItem();

        /**
        * Gets the data
        *@return the data
        */
        virtual inline CString GetData() const;

        /**
        * Gets the data
        *@param[in, out] item - the item
        */
        virtual inline void GetData(bool& item) const;

        /**
        * Gets the data
        *@param pStrArray - the string array to populate with the result
        */
        virtual inline void GetData(CStringArray* pStrArray) const;

        /**
        * Gets the item data
        *@param item - the item index
        *@return the item data
        */
        virtual inline LPCTSTR GetItemData(int item) const;

        /**
        * Sets the data
        *@param value - the data
        */
        virtual void SetData(const CString& value);

        /**
        * Sets the item data
        *@param pStrArray - the string array containing the item data
        */
        virtual inline void SetData(CStringArray* pStrArray);

        /**
        * Sets the item list data
        *@param pWndInPlaceControl - the window in-place control
        */
        virtual void SetItemListData(PSS_InPlaceListBox* pWndInPlaceControl);

        /**
        * Draws the value
        *@param pDc - device context to draw on
        *@param rect - the rect surrounding the value to draw
        */
        virtual inline void DrawValue(CDC* pDC, CRect& rect);

        /**
        * Creates an in-place control
        *@param pWndParent - the parent window
        *@param rect - the rectangle surrounding the control to create
        *@param[out] pWndInPlaceControl - the newly created in-place control window on function ends
        *@param extendedSize - the control extended size
        */
        virtual void CreateInPlaceControl(CWnd*             pWndParent,
                                          const CRect&      rect,
                                          PSS_InPlaceEdit*& pWndInPlaceControl,
                                          const CSize&      extendedSize = CSize(0, 0));

    private:
        CStringArray* m_pData;
        int           m_Item;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ListPropertyItem(const PSS_ListPropertyItem& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ListPropertyItem& operator = (const PSS_ListPropertyItem& other);
};

//---------------------------------------------------------------------------
// PSS_ListPropertyItem
//---------------------------------------------------------------------------
PSS_ListPropertyItem::PSS_ListPropertyItem(LPCTSTR pName, bool isReadOnly, bool canBeEdited) :
    PSS_PropertyItem(pName, isReadOnly, canBeEdited),
    m_pData(NULL),
    m_Item(0)
{}
//---------------------------------------------------------------------------
PSS_ListPropertyItem::~PSS_ListPropertyItem()
{}
//---------------------------------------------------------------------------
CString PSS_ListPropertyItem::GetData() const
{
    return m_StrValue;
}
//---------------------------------------------------------------------------
void PSS_ListPropertyItem::GetData(bool& item) const
{
    item = ToBool(m_Item);
}
//---------------------------------------------------------------------------
void PSS_ListPropertyItem::GetData(CStringArray* pStrArray) const
{
    pStrArray = m_pData;
}
//---------------------------------------------------------------------------
LPCTSTR PSS_ListPropertyItem::GetItemData(int item) const
{
    return (m_pData && item < m_pData->GetSize()) ? static_cast<const char*>(m_pData->GetAt(item)) : NULL;
}
//---------------------------------------------------------------------------
void PSS_ListPropertyItem::SetData(CStringArray* pStrArray)
{
    m_pData = pStrArray;
}
//---------------------------------------------------------------------------
void PSS_ListPropertyItem::DrawValue(CDC* pDC, CRect& rect)
{
    pDC->DrawText(GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER);
}
//---------------------------------------------------------------------------

/**
* Extended property item
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ExtendedPropertyItem : public PSS_PropertyItem
{
    DECLARE_DYNAMIC(PSS_ExtendedPropertyItem)

    public:
        /**
        * Constructor
        *@param pName - the item name
        *@param isReadOnly - if true, the item is read-only
        *@param canBeEdited - if true, the item can be edited
        */
        inline PSS_ExtendedPropertyItem(LPCTSTR pStrName = NULL, bool isReadOnly = false, bool canBeEdited = true);

        virtual inline ~PSS_ExtendedPropertyItem();

        /**
        * Draws the value
        *@param pDc - device context to draw on
        *@param rect - the rect surrounding the value to draw
        */
        virtual inline void DrawValue(CDC* pDC, CRect& rect);

        /**
        * Creates an in-place control
        *@param pWndParent - the parent window
        *@param rect - the rectangle surrounding the control to create
        *@param[out] pWndInPlaceControl - the newly created in-place control window on function ends
        *@param extendedSize - the control extended size
        */
        virtual void CreateInPlaceControl(CWnd*             pWndParent,
                                          const CRect&      rect,
                                          PSS_InPlaceEdit*& pWndInPlaceControl,
                                          const CSize&      extendedSize = CSize(0, 0));

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ExtendedPropertyItem(const PSS_ExtendedPropertyItem& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ExtendedPropertyItem& operator = (const PSS_ExtendedPropertyItem& other);
};

//---------------------------------------------------------------------------
// PSS_ExtendedPropertyItem
//---------------------------------------------------------------------------
PSS_ExtendedPropertyItem::PSS_ExtendedPropertyItem(LPCTSTR pName, bool isReadOnly, bool canBeEdited) :
    PSS_PropertyItem(pName, isReadOnly, canBeEdited)
{}
//---------------------------------------------------------------------------
PSS_ExtendedPropertyItem::~PSS_ExtendedPropertyItem()
{}
//---------------------------------------------------------------------------
void PSS_ExtendedPropertyItem::DrawValue(CDC* pDC, CRect& rect)
{
    pDC->DrawText(GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER);
}
//---------------------------------------------------------------------------

/**
* Intellisense edit property item
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_IntelliEditPropertyItem : public PSS_PropertyItem
{
    DECLARE_DYNAMIC(PSS_IntelliEditPropertyItem)

    public:
        /**
        * Constructor
        *@param pName - the item name
        *@param isReadOnly - if true, the item is read-only
        *@param canBeEdited - if true, the item can be edited
        */
        inline PSS_IntelliEditPropertyItem(LPCTSTR pName = NULL, bool isReadOnly = false, bool canBeEdited = true);

        virtual inline ~PSS_IntelliEditPropertyItem();

        /**
        * Gets the data
        *@return the data
        */
        virtual inline CString GetData() const;

        /**
        * Gets the data
        *@param pStrArray - the string array to populate with the result
        */
        virtual inline void GetData(CStringArray* pStrArray) const;

        /**
        * Sets the data
        *@param value - the data
        */
        virtual void SetData(const CString& value);

        /**
        * Sets the item data
        *@param pStrArray - the string array containing the item data
        */
        virtual inline void SetData(CStringArray* pStrArray);

        /**
        * Draws the value
        *@param pDc - device context to draw on
        *@param rect - the rect surrounding the value to draw
        */
        virtual inline void DrawValue(CDC* pDC, CRect& rect);

        /**
        * Creates an in-place control
        *@param pWndParent - the parent window
        *@param rect - the rectangle surrounding the control to create
        *@param[out] pWndInPlaceControl - the newly created in-place control window on function ends
        *@param extendedSize - the control extended size
        */
        virtual void CreateInPlaceControl(CWnd*             pWndParent,
                                          const CRect&      rect,
                                          PSS_InPlaceEdit*& pWndInPlaceControl,
                                          const CSize&      extendedSize = CSize(0, 0));

    private:
        CStringArray* m_pData;
        int           m_Item;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_IntelliEditPropertyItem(const PSS_IntelliEditPropertyItem& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_IntelliEditPropertyItem& operator = (const PSS_IntelliEditPropertyItem& other);
};

//---------------------------------------------------------------------------
// PSS_IntelliEditPropertyItem
//---------------------------------------------------------------------------
PSS_IntelliEditPropertyItem::PSS_IntelliEditPropertyItem(LPCTSTR pName, bool isReadOnly, bool canBeEdited) :
    PSS_PropertyItem(pName, isReadOnly, canBeEdited),
    m_pData(NULL),
    m_Item(0)
{}
//---------------------------------------------------------------------------
PSS_IntelliEditPropertyItem::~PSS_IntelliEditPropertyItem()
{}
//---------------------------------------------------------------------------
CString PSS_IntelliEditPropertyItem::GetData() const
{
    return m_StrValue;
}
//---------------------------------------------------------------------------
void PSS_IntelliEditPropertyItem::GetData(CStringArray* pStrArray) const
{
    pStrArray = m_pData;
}
//---------------------------------------------------------------------------
void PSS_IntelliEditPropertyItem::SetData(CStringArray* pStrArray)
{
    m_pData = pStrArray;
}
//---------------------------------------------------------------------------
void PSS_IntelliEditPropertyItem::DrawValue(CDC* pDC, CRect& rect)
{
    pDC->DrawText(GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER);
}
//---------------------------------------------------------------------------

/**
* Multiline edit property item
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MultiLineEditPropertyItem : public PSS_PropertyItem
{
    DECLARE_DYNAMIC(PSS_MultiLineEditPropertyItem)

    public:
        /**
        * Constructor
        *@param pName - the item name
        *@param isReadOnly - if true, the item is read-only
        *@param canBeEdited - if true, the item can be edited
        */
        inline PSS_MultiLineEditPropertyItem(LPCTSTR pName = NULL, bool isReadOnly = false, bool canBeEdited = true);

        virtual inline ~PSS_MultiLineEditPropertyItem();

        /**
        * Gets the data
        *@return the data
        */
        virtual inline CString GetData() const;

        /**
        * Sets the data
        *@param value - the data
        */
        virtual void SetData(const CString& value);

        /**
        * Draws the value
        *@param pDc - device context to draw on
        *@param rect - the rect surrounding the value to draw
        */
        virtual inline void DrawValue(CDC* pDC, CRect& rect);

        /**
        * Creates an in-place control
        *@param pWndParent - the parent window
        *@param rect - the rectangle surrounding the control to create
        *@param[out] pWndInPlaceControl - the newly created in-place control window on function ends
        *@param extendedSize - the control extended size
        */
        virtual void CreateInPlaceControl(CWnd*             pWndParent,
                                          const CRect&      rect,
                                          PSS_InPlaceEdit*& pWndInPlaceControl,
                                          const CSize&      extendedSize = CSize(0, 0));

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_MultiLineEditPropertyItem(const PSS_MultiLineEditPropertyItem& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_MultiLineEditPropertyItem& operator = (const PSS_MultiLineEditPropertyItem& other);
};

//---------------------------------------------------------------------------
// PSS_MultiLineEditPropertyItem
//---------------------------------------------------------------------------
PSS_MultiLineEditPropertyItem::PSS_MultiLineEditPropertyItem(LPCTSTR pName, bool isReadOnly, bool canBeEdited) :
    PSS_PropertyItem(pName, isReadOnly, canBeEdited)
{}
//---------------------------------------------------------------------------
PSS_MultiLineEditPropertyItem::~PSS_MultiLineEditPropertyItem()
{}
//---------------------------------------------------------------------------
CString PSS_MultiLineEditPropertyItem::GetData() const
{
    return m_StrValue;
}
//---------------------------------------------------------------------------
void PSS_MultiLineEditPropertyItem::DrawValue(CDC* pDC, CRect& rect)
{
    pDC->DrawText(GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER);
}
//---------------------------------------------------------------------------

/**
* Date property item
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DatePropertyItem : public PSS_PropertyItem
{
    DECLARE_DYNAMIC(PSS_DatePropertyItem)

    public:
        /**
        * Constructor
        *@param pName - the item name
        *@param isReadOnly - if true, the item is read-only
        *@param canBeEdited - if true, the item can be edited
        */
        inline PSS_DatePropertyItem(LPCTSTR pName = NULL, bool isReadOnly = false, bool canBeEdited = true);

        inline virtual ~PSS_DatePropertyItem();

        /**
        * Draws the value
        *@param pDc - device context to draw on
        *@param rect - the rect surrounding the value to draw
        */
        virtual inline void DrawValue(CDC* pDC, CRect& rect);

        /**
        * Creates an in-place control
        *@param pWndParent - the parent window
        *@param rect - the rectangle surrounding the control to create
        *@param[out] pWndInPlaceControl - the newly created in-place control window on function ends
        *@param extendedSize - the control extended size
        */
        virtual void CreateInPlaceControl(CWnd*             pWndParent,
                                          const CRect&      rect,
                                          PSS_InPlaceEdit*& pWndInPlaceControl,
                                          const CSize&      extendedSize = CSize(0, 0));

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DatePropertyItem(const PSS_DatePropertyItem& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DatePropertyItem& operator = (const PSS_DatePropertyItem& other);
};

//---------------------------------------------------------------------------
// PSS_DatePropertyItem
//---------------------------------------------------------------------------
inline PSS_DatePropertyItem::PSS_DatePropertyItem(LPCTSTR pName, bool isReadOnly, bool canBeEdited) :
    PSS_PropertyItem(pName, isReadOnly, canBeEdited)
{}
//---------------------------------------------------------------------------
inline PSS_DatePropertyItem::~PSS_DatePropertyItem()
{}
//---------------------------------------------------------------------------
void PSS_DatePropertyItem::DrawValue(CDC* pDC, CRect& rect)
{
    pDC->DrawText(GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER);
}
//---------------------------------------------------------------------------

/**
* Time property item
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TimePropertyItem : public PSS_PropertyItem
{
    DECLARE_DYNAMIC(PSS_TimePropertyItem)

    public:
        /**
        * Constructor
        *@param pName - the item name
        *@param isReadOnly - if true, the item is read-only
        *@param canBeEdited - if true, the item can be edited
        */
        inline PSS_TimePropertyItem(LPCTSTR pName = NULL, bool isReadOnly = false, bool canBeEdited = true);

        virtual inline ~PSS_TimePropertyItem();

        /**
        * Draws the value
        *@param pDc - device context to draw on
        *@param rect - the rect surrounding the value to draw
        */
        virtual inline void DrawValue(CDC* pDC, CRect& rect);

        /**
        * Creates an in-place control
        *@param pWndParent - the parent window
        *@param rect - the rectangle surrounding the control to create
        *@param[out] pWndInPlaceControl - the newly created in-place control window on function ends
        *@param extendedSize - the control extended size
        */
        virtual void CreateInPlaceControl(CWnd*             pWndParent,
                                          const CRect&      rect,
                                          PSS_InPlaceEdit*& pWndInPlaceControl,
                                          const CSize&      extendedSize = CSize(0, 0));

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_TimePropertyItem(const PSS_TimePropertyItem& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_TimePropertyItem& operator = (const PSS_TimePropertyItem& other);
};

//---------------------------------------------------------------------------
// PSS_TimePropertyItem
//---------------------------------------------------------------------------
PSS_TimePropertyItem::PSS_TimePropertyItem(LPCTSTR pName, bool isReadOnly, bool canBeEdited) :
    PSS_PropertyItem(pName, isReadOnly, canBeEdited)
{}
//---------------------------------------------------------------------------
PSS_TimePropertyItem::~PSS_TimePropertyItem()
{}
//---------------------------------------------------------------------------
void PSS_TimePropertyItem::DrawValue(CDC* pDC, CRect& rect)
{
    pDC->DrawText(GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER);
}
//---------------------------------------------------------------------------

/**
* Duration property item
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DurationPropertyItem : public PSS_PropertyItem
{
    DECLARE_DYNAMIC(PSS_DurationPropertyItem)

    public:
        /**
        * Constructor
        *@param pName - the item name
        *@param isReadOnly - if true, the item is read-only
        *@param canBeEdited - if true, the item can be edited
        */
        inline PSS_DurationPropertyItem(LPCTSTR pName = NULL, bool isReadOnly = false, bool canBeEdited = true);

        virtual inline ~PSS_DurationPropertyItem();

        /**
        * Draws the value
        *@param pDc - device context to draw on
        *@param rect - the rect surrounding the value to draw
        */
        virtual inline void DrawValue(CDC* pDC, CRect& rect);

        /**
        * Creates an in-place control
        *@param pWndParent - the parent window
        *@param rect - the rectangle surrounding the control to create
        *@param[out] pWndInPlaceControl - the newly created in-place control window on function ends
        *@param extendedSize - the control extended size
        */
        virtual void CreateInPlaceControl(CWnd*             pWndParent,
                                          const CRect&      rect,
                                          PSS_InPlaceEdit*& pWndInPlaceControl,
                                          const CSize&      extendedSize = CSize(0, 0));

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DurationPropertyItem(const PSS_DurationPropertyItem& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DurationPropertyItem& operator = (const PSS_DurationPropertyItem& other);
};

//---------------------------------------------------------------------------
// PSS_DurationPropertyItem
//---------------------------------------------------------------------------
PSS_DurationPropertyItem::PSS_DurationPropertyItem(LPCTSTR pName, bool isReadOnly, bool canBeEdited) :
    PSS_PropertyItem(pName, isReadOnly, canBeEdited)
{}
//---------------------------------------------------------------------------
PSS_DurationPropertyItem::~PSS_DurationPropertyItem()
{}
//---------------------------------------------------------------------------
void PSS_DurationPropertyItem::DrawValue(CDC* pDC, CRect& rect)
{
    pDC->DrawText(GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER);
}
//---------------------------------------------------------------------------

/**
* Menu file directory property item
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MenuFileDirPropertyItem : public PSS_PropertyItem
{
    DECLARE_DYNAMIC(PSS_MenuFileDirPropertyItem)

    public:
        /**
        * Constructor
        *@param pName - the item name
        *@param asFile - if true, the item is opened for a file
        *@param isReadOnly - if true, the item is read-only
        *@param canBeEdited - if true, the item can be edited
        */
        inline PSS_MenuFileDirPropertyItem(LPCTSTR pName       = NULL,
                                           bool    asFile      = true,
                                           bool    isReadOnly  = false,
                                           bool    canBeEdited = true);

        /**
        * Constructor
        *@param pMenu - the menu
        *@param isReadOnly - if true, the item is read-only
        *@param canBeEdited - if true, the item can be edited
        */
        inline PSS_MenuFileDirPropertyItem(CMenu* pMenu, bool isReadOnly = false, bool canBeEdited = true);

        virtual inline ~PSS_MenuFileDirPropertyItem();

        /**
        * Draws the value
        *@param pDc - device context to draw on
        *@param rect - the rect surrounding the value to draw
        */
        virtual inline void DrawValue(CDC* pDC, CRect& rect);

        /**
        * Creates an in-place control
        *@param pWndParent - the parent window
        *@param rect - the rectangle surrounding the control to create
        *@param[out] pWndInPlaceControl - the newly created in-place control window on function ends
        *@param extendedSize - the control extended size
        */
        virtual void CreateInPlaceControl(CWnd*             pWndParent,
                                          const CRect&      rect,
                                          PSS_InPlaceEdit*& pWndInPlaceControl,
                                          const CSize&      extendedSize = CSize(0, 0));

    private:
        /**
        * The item type
        */
        enum IEItemType
        {
            IE_IT_Menu,
            IE_IT_File,
            IE_IT_Directory
        };

        IEItemType m_ControlType;
        CMenu*     m_pMenu;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_MenuFileDirPropertyItem(const PSS_MenuFileDirPropertyItem& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_MenuFileDirPropertyItem& operator = (const PSS_MenuFileDirPropertyItem& other);
};

//---------------------------------------------------------------------------
// PSS_MenuFileDirPropertyItem
//---------------------------------------------------------------------------
PSS_MenuFileDirPropertyItem::PSS_MenuFileDirPropertyItem(LPCTSTR pName, bool asFile, bool isReadOnly, bool canBeEdited) :
    PSS_PropertyItem(pName, isReadOnly, canBeEdited),
    m_ControlType(asFile ? IE_IT_File : IE_IT_Directory),
    m_pMenu(NULL)
{}
//---------------------------------------------------------------------------
PSS_MenuFileDirPropertyItem::PSS_MenuFileDirPropertyItem(CMenu* pMenu, bool isReadOnly, bool canBeEdited) :
    PSS_PropertyItem(NULL, isReadOnly, canBeEdited),
    m_ControlType(IE_IT_Menu),
    m_pMenu(pMenu)
{}
//---------------------------------------------------------------------------
PSS_MenuFileDirPropertyItem::~PSS_MenuFileDirPropertyItem()
{}
//---------------------------------------------------------------------------
void PSS_MenuFileDirPropertyItem::DrawValue(CDC* pDC, CRect& rect)
{
    pDC->DrawText(GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER);
}
//---------------------------------------------------------------------------

/**
* Menu file directory property item
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_NumberPropertyItem : public PSS_PropertyItem
{
    DECLARE_DYNAMIC(PSS_NumberPropertyItem)

    public:
        /**
        * Constructor
        *@param value - the item value
        *@param isReadOnly - if true, the item is read-only
        *@param canBeEdited - if true, the item can be edited
        */
        inline PSS_NumberPropertyItem(float  value,       bool isReadOnly = false, bool canBeEdited = true);
        inline PSS_NumberPropertyItem(double value = 0.0, bool isReadOnly = false, bool canBeEdited = true);

        virtual inline ~PSS_NumberPropertyItem();

        /**
        * Draws the value
        *@param pDc - device context to draw on
        *@param rect - the rect surrounding the value to draw
        */
        virtual inline void DrawValue(CDC* pDC, CRect& rect);

        /**
        * Creates an in-place control
        *@param pWndParent - the parent window
        *@param rect - the rectangle surrounding the control to create
        *@param[out] pWndInPlaceControl - the newly created in-place control window on function ends
        *@param extendedSize - the control extended size
        */
        virtual void CreateInPlaceControl(CWnd*             pWndParent,
                                          const CRect&      rect,
                                          PSS_InPlaceEdit*& pWndInPlaceControl,
                                          const CSize&      extendedSize = CSize(0, 0));

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_NumberPropertyItem(const PSS_NumberPropertyItem& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_NumberPropertyItem& operator = (const PSS_NumberPropertyItem& other);
};

//---------------------------------------------------------------------------
// PSS_NumberPropertyItem
//---------------------------------------------------------------------------
PSS_NumberPropertyItem::PSS_NumberPropertyItem(float value, bool isReadOnly, bool canBeEdited) :
    PSS_PropertyItem(NULL, isReadOnly, canBeEdited)
{
    SetData(value);
}
//---------------------------------------------------------------------------
PSS_NumberPropertyItem::PSS_NumberPropertyItem(double value, bool isReadOnly, bool canBeEdited) :
    PSS_PropertyItem(NULL, isReadOnly, canBeEdited)
{
    SetData(value);
}
//---------------------------------------------------------------------------
PSS_NumberPropertyItem::~PSS_NumberPropertyItem()
{}
//---------------------------------------------------------------------------
void PSS_NumberPropertyItem::DrawValue(CDC* pDC, CRect& rect)
{
    pDC->DrawText(GetData(), -1, &rect, DT_SINGLELINE | DT_VCENTER);
}
//---------------------------------------------------------------------------

#endif
