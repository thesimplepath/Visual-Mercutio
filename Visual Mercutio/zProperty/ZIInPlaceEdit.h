// ZIInPlaceEdit.h: interface for the ZIInPlaceEdit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ZIINPLACEEDIT_H__)
#define _ZIINPLACEEDIT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\ZISubject.h"
#include "zBaseLib\ZIObserver.h"

#include "zBaseLib\ZBDuration.h"
#include "zBaseLib\ZBDate.h"
//RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
#include "zBaseLib\ZBTimeSpan.h"

// Forward class declaration
class ZBPropertyItem;



#ifdef _ZPROPERTYEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif



class AFX_EXT_CLASS ZIInPlaceEdit : public ZISubject, public ZIObserver  
{
public:
    enum InPlaceEditType
    {
        IPE_STRING,
        IPE_DOUBLE,
        IPE_FLOAT,
        IPE_DATE,
        IPE_TIME,
        IPE_DURATION
    };

public:
    ZIInPlaceEdit();
    ZIInPlaceEdit(const CString& srtInitText, bool IsReadOnly = false);
    ZIInPlaceEdit(double dInitValue, bool IsReadOnly = false);
    ZIInPlaceEdit(float fInitValue, bool IsReadOnly = false);
    ZIInPlaceEdit(ZBDuration& DurationInitValue, bool IsReadOnly = false);
    ZIInPlaceEdit(ZBDate& DateInitValue, bool IsReadOnly = false);
    //RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
    ZIInPlaceEdit(ZBTimeSpan& TimeInitValue, bool IsReadOnly = false);
    

    virtual ~ZIInPlaceEdit();

    InPlaceEditType GetEditType() const
    {
        return m_type;
    };


    // Initialize the edit control
    virtual BOOL InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, const CString& strInitText, CWnd* pWndParent, CRect& rect, DWORD exDwStyle = 0)
    {
        return FALSE;
    };
    virtual BOOL InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, double dInitValue, CWnd* pWndParent, CRect& rect, DWORD exDwStyle = 0)
    {
        return FALSE;
    };
    virtual BOOL InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, float fInitValue, CWnd* pWndParent, CRect& rect, DWORD exDwStyle = 0)
    {
        return FALSE;
    };
    virtual BOOL InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, ZBDuration& DurationInitValue, CWnd* pWndParent, CRect& rect, DWORD exDwStyle = 0)
    {
        return FALSE;
    };
    virtual BOOL InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, ZBDate& DateInitValue, CWnd* pWndParent, CRect& rect, DWORD exDwStyle = 0)
    {
        return FALSE;
    };
    //RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
    virtual BOOL InitializeInPlaceEditCtrl(ZBPropertyItem* pItem, ZBTimeSpan& TimeInitValue, CWnd* pWndParent, CRect& rect, DWORD exDwStyle = 0)
    {
        return FALSE;
    };
    virtual void SetNewPropertyItem( ZBPropertyItem* pItem )
    {
        m_pItem = pItem;
    };
    // Initialize the edit text value
    virtual void SetEditText(const CString& strText)
    {
    };
    virtual void SetEditText(double dValue)
    {
    };
    virtual void SetEditText(float fValue)
    {
    };
    virtual void SetEditText(ZBDuration& DurationValue)
    {
    };
    virtual void SetEditText(ZBDate& DateValue)
    {
    };
    //RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
    virtual void SetEditText(ZBTimeSpan& TimeValue)
    {
    };
    virtual CString GetEditText() const
    {
        return _T("");
    };
    // Virtual function to cancel and save the edition
    virtual void CancelEdit()
    {
    };
    virtual void SaveValue()
    {
    };

    // ZIObserver OnUpdate call-back function
    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg )
    {
        // Does nothing
    };

    // Returns the size of the edit
    virtual CSize GetSize() const
    {
        return CSize(0,0);
    };
    // Returns the extended size of the edit
    virtual CSize GetExtendedSize() const
    {
        return CSize(0,0);
    };
    // Returns true if the edit has a value that has changed
    bool GetHasChanged() const
    {
        return m_HasChanged;
    };

protected:
    void SetHasChanged( bool value )
    {
        m_HasChanged = value;
    };

    bool IsReadOnly() const
    {
        return m_IsReadOnly;
    };
    void SetIsReadOnly( bool value )
    {
        m_IsReadOnly = value;
    };


protected:
    ZBPropertyItem* m_pItem;

    InPlaceEditType m_type;

    CString            m_strText;
    CString            m_strInitialValueText;
    double            m_dValue;
    double            m_dInitialValue;
    float            m_fValue;
    float            m_fInitialValue;
    ZBDuration        m_DurationValue;
    ZBDuration        m_InitialDurationValue;
    ZBDate            m_DateValue;
    ZBDate            m_InitialDateValue;
    //RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
    ZBTimeSpan        m_TimeValue;
    ZBTimeSpan        m_InitialTimeValue;

    bool            m_IsReadOnly;
    bool            m_HasChanged;


};

inline ZIInPlaceEdit::ZIInPlaceEdit()
    : m_IsReadOnly(false), m_HasChanged(false)
{
    // Sets the type
    m_type = ZIInPlaceEdit::IPE_DOUBLE;
    m_dInitialValue = 0;

}

inline ZIInPlaceEdit::ZIInPlaceEdit(const CString& strInitText, bool IsReadOnly /*= false*/)
    : m_strText(strInitText), m_IsReadOnly(IsReadOnly), m_HasChanged(false)
{
    // Sets the type
    m_type = ZIInPlaceEdit::IPE_STRING;
    m_strInitialValueText = strInitText;
}

inline ZIInPlaceEdit::ZIInPlaceEdit(double dInitValue, bool IsReadOnly /*= false*/)
    : m_dValue(dInitValue), m_IsReadOnly(IsReadOnly), m_HasChanged(false)
{
    // Sets the type
    m_type = ZIInPlaceEdit::IPE_DOUBLE;
    m_dInitialValue = dInitValue;
}

inline ZIInPlaceEdit::ZIInPlaceEdit(float fInitValue, bool IsReadOnly /*= false*/)
    : m_fValue(fInitValue), m_IsReadOnly(IsReadOnly), m_HasChanged(false)
{
    // Sets the type
    m_type = ZIInPlaceEdit::IPE_FLOAT;
    m_fInitialValue = fInitValue;
}

inline ZIInPlaceEdit::ZIInPlaceEdit(ZBDuration& DurationInitValue, bool IsReadOnly /*= false*/)
    : m_DurationValue(DurationInitValue), m_IsReadOnly(IsReadOnly), m_HasChanged(false)
{
    // Sets the type
    m_type = ZIInPlaceEdit::IPE_DURATION;
    m_InitialDurationValue = DurationInitValue;
}

inline ZIInPlaceEdit::ZIInPlaceEdit(ZBDate& DateInitValue, bool IsReadOnly /*= false*/)
    : m_DateValue(DateInitValue), m_IsReadOnly(IsReadOnly), m_HasChanged(false)
{
    // Sets the type
    m_type = ZIInPlaceEdit::IPE_DATE;
    m_InitialDateValue = DateInitValue;
}


//RS-MODIF 08.08.2005 ajout de l'attribut dynamique "temps"
inline ZIInPlaceEdit::ZIInPlaceEdit(ZBTimeSpan& TimeInitValue, bool IsReadOnly /*= false*/)
    : m_TimeValue(TimeInitValue), m_IsReadOnly(IsReadOnly), m_HasChanged(false)
{
    // Sets the type
    m_type = ZIInPlaceEdit::IPE_TIME;
    m_InitialTimeValue = TimeInitValue;
}

inline ZIInPlaceEdit::~ZIInPlaceEdit()
{

}

#endif // !defined(_ZIINPLACEEDIT_H__)
