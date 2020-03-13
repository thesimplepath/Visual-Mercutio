/****************************************************************************
 * ==> PSS_InPlaceEdit -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an in-place edit                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InPlaceEditH
#define PSS_InPlaceEditH

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
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_Duration.h"
#include "zBaseLib\PSS_Date.h"
#include "zBaseLib\PSS_TimeSpan.h"

// forward class declaration
class PSS_PropertyItem;

#ifdef _ZPROPERTYEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* In-place edit
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InPlaceEdit : public PSS_Subject,
                                      public PSS_Observer
{
    public:
        /**
        * In-place edit type
        */
        enum IEType
        {
            IE_T_String,
            IE_T_Double,
            IE_T_Float,
            IE_T_Date,
            IE_T_Time,
            IE_T_Duration
        };

        inline PSS_InPlaceEdit();

        /**
        * Constructor
        *@param initValue - the initial value
        *@param isReadOnly- if true, the edit will be read-only
        */
        inline PSS_InPlaceEdit(float               initValue, bool isReadOnly = false);
        inline PSS_InPlaceEdit(double              initValue, bool isReadOnly = false);
        inline PSS_InPlaceEdit(const PSS_Date&     initValue, bool isReadOnly = false);
        inline PSS_InPlaceEdit(const PSS_TimeSpan& initValue, bool isReadOnly = false);
        inline PSS_InPlaceEdit(const PSS_Duration& initValue, bool isReadOnly = false);
        inline PSS_InPlaceEdit(const CString&      initValue, bool isReadOnly = false);

        virtual inline ~PSS_InPlaceEdit();

        /**
        * Gets the edit type
        *@return the edit type
        */
        virtual inline IEType GetEditType() const;

        /**
        * Initializes the edit control
        *@param pItem - the owning property item
        *@param initValue - the initial value
        *@param pWndParent- the parent window
        *@param rect - the rectangle surrounding the edit
        *@param style - the edit style
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                               float             initValue,
                                               CWnd*             pWndParent,
                                               const CRect&      rect,
                                               DWORD             style = 0);
        virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                               double            initValue,
                                               CWnd*             pWndParent,
                                               const CRect&      rect,
                                               DWORD             style = 0);
        virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                               PSS_Date&         initValue,
                                               CWnd*             pWndParent,
                                               const CRect&      rect,
                                               DWORD             style = 0);
        virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                               PSS_TimeSpan&     initValue,
                                               CWnd*             pWndParent,
                                               const CRect&      rect,
                                               DWORD             style = 0);
        virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                               PSS_Duration&     initValue,
                                               CWnd*             pWndParent,
                                               const CRect&      rect,
                                               DWORD             style = 0);
        virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                               const CString&    initValue,
                                               CWnd*             pWndParent,
                                               const CRect&      rect,
                                               DWORD             style = 0);

        /**
        * Sets a new property item
        *@param pItem - the new property item to set
        */
        virtual void SetNewPropertyItem(PSS_PropertyItem* pItem);

        /**
        * Gets the edit text
        *@return the edit text
        */
        virtual CString GetEditText() const;

        /**
        * Sets the edit text value
        *@param value - the edit text value
        */
        virtual void SetEditText(float          value);
        virtual void SetEditText(double         value);
        virtual void SetEditText(PSS_Date&      value);
        virtual void SetEditText(PSS_TimeSpan&  value);
        virtual void SetEditText(PSS_Duration&  value);
        virtual void SetEditText(const CString& value);

        /**
        * Cancels the edition
        */
        virtual void CancelEdit();

        /**
        * Saves the edited value
        */
        virtual void SaveValue();

        /**
        * Gets the edit size
        *@return the edit size
        */
        virtual CSize GetSize() const;

        /**
        * Gets the edit extended size
        *@return the edit extended size
        */
        virtual CSize GetExtendedSize() const;

        /**
        * Checks if the edit value changed
        *@return true if the edit value changed, otherwise false
        */
        virtual inline bool GetHasChanged() const;

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        PSS_PropertyItem* m_pItem;
        IEType            m_Type;
        PSS_Date          m_DateValue;
        PSS_Date          m_InitialDateValue;
        PSS_TimeSpan      m_TimeValue;
        PSS_TimeSpan      m_InitialTimeValue;
        PSS_Duration      m_DurationValue;
        PSS_Duration      m_InitialDurationValue;
        CString           m_StrValue;
        CString           m_StrInitialValue;
        double            m_DoubleValue;
        double            m_DoubleInitialValue;
        float             m_FloatValue;
        float             m_FloatInitialValue;
        bool              m_IsReadOnly;
        bool              m_HasChanged;

        /**
        * Notifies that the edit has changed
        *@param value - if true, the edit has changed
        */
        virtual inline void SetHasChanged(bool value);

        /**
        * Checks if the edit is read-only
        *@return true if the edit is read-only, otherwise false
        */
        virtual inline bool IsReadOnly() const;

        /**
        * Sets the edit as read-only
        *@param value - if true, the edit is read-only
        */
        virtual inline void SetIsReadOnly(bool value);
};

//---------------------------------------------------------------------------
// PSS_InPlaceEdit
//---------------------------------------------------------------------------
PSS_InPlaceEdit::PSS_InPlaceEdit() :
    PSS_Subject(),
    PSS_Observer(),
    m_pItem(NULL),
    m_Type(IE_T_Double),
    m_DoubleValue(0.0),
    m_DoubleInitialValue(0.0),
    m_FloatValue(0.0f),
    m_FloatInitialValue(0.0f),
    m_IsReadOnly(false),
    m_HasChanged(false)
{}
//---------------------------------------------------------------------------
PSS_InPlaceEdit::PSS_InPlaceEdit(float initValue, bool isReadOnly) :
    PSS_Subject(),
    PSS_Observer(),
    m_pItem(NULL),
    m_Type(IE_T_Float),
    m_DoubleValue(0.0),
    m_DoubleInitialValue(0.0),
    m_FloatValue(initValue),
    m_FloatInitialValue(initValue),
    m_IsReadOnly(isReadOnly),
    m_HasChanged(false)
{}
//---------------------------------------------------------------------------
PSS_InPlaceEdit::PSS_InPlaceEdit(double initValue, bool isReadOnly) :
    PSS_Subject(),
    PSS_Observer(),
    m_pItem(NULL),
    m_Type(IE_T_Double),
    m_DoubleValue(initValue),
    m_DoubleInitialValue(initValue),
    m_FloatValue(0.0f),
    m_FloatInitialValue(0.0f),
    m_IsReadOnly(isReadOnly),
    m_HasChanged(false)
{}
//---------------------------------------------------------------------------
PSS_InPlaceEdit::PSS_InPlaceEdit(const PSS_Date& initValue, bool isReadOnly) :
    PSS_Subject(),
    PSS_Observer(),
    m_pItem(NULL),
    m_Type(IE_T_Date),
    m_DateValue(initValue),
    m_InitialDateValue(initValue),
    m_DoubleValue(0.0),
    m_DoubleInitialValue(0.0),
    m_FloatValue(0.0f),
    m_FloatInitialValue(0.0f),
    m_IsReadOnly(isReadOnly),
    m_HasChanged(false)
{}
//---------------------------------------------------------------------------
PSS_InPlaceEdit::PSS_InPlaceEdit(const PSS_TimeSpan& initValue, bool isReadOnly) :
    PSS_Subject(),
    PSS_Observer(),
    m_pItem(NULL),
    m_Type(IE_T_Time),
    m_TimeValue(initValue),
    m_InitialTimeValue(initValue),
    m_DoubleValue(0.0),
    m_DoubleInitialValue(0.0),
    m_FloatValue(0.0f),
    m_FloatInitialValue(0.0f),
    m_IsReadOnly(isReadOnly),
    m_HasChanged(false)
{}
//---------------------------------------------------------------------------
PSS_InPlaceEdit::PSS_InPlaceEdit(const PSS_Duration& initValue, bool isReadOnly) :
    PSS_Subject(),
    PSS_Observer(),
    m_pItem(NULL),
    m_Type(IE_T_Duration),
    m_DurationValue(initValue),
    m_InitialDurationValue(initValue),
    m_DoubleValue(0.0),
    m_DoubleInitialValue(0.0),
    m_FloatValue(0.0f),
    m_FloatInitialValue(0.0f),
    m_IsReadOnly(isReadOnly),
    m_HasChanged(false)
{}
//---------------------------------------------------------------------------
PSS_InPlaceEdit::PSS_InPlaceEdit(const CString& initValue, bool isReadOnly) :
    PSS_Subject(),
    PSS_Observer(),
    m_pItem(NULL),
    m_Type(IE_T_String),
    m_StrValue(initValue),
    m_StrInitialValue(initValue),
    m_DoubleValue(0.0),
    m_DoubleInitialValue(0.0),
    m_FloatValue(0.0f),
    m_FloatInitialValue(0.0f),
    m_IsReadOnly(isReadOnly),
    m_HasChanged(false)
{}
//---------------------------------------------------------------------------
PSS_InPlaceEdit::~PSS_InPlaceEdit()
{}
//---------------------------------------------------------------------------
PSS_InPlaceEdit::IEType PSS_InPlaceEdit::GetEditType() const
{
    return m_Type;
}
//---------------------------------------------------------------------------
bool PSS_InPlaceEdit::GetHasChanged() const
{
    return m_HasChanged;
}
//---------------------------------------------------------------------------
void PSS_InPlaceEdit::SetHasChanged(bool value)
{
    m_HasChanged = value;
}
//---------------------------------------------------------------------------
bool PSS_InPlaceEdit::IsReadOnly() const
{
    return m_IsReadOnly;
}
//---------------------------------------------------------------------------
void PSS_InPlaceEdit::SetIsReadOnly(bool value)
{
    m_IsReadOnly = value;
}
//---------------------------------------------------------------------------

#endif
