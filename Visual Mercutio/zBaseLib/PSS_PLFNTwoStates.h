/****************************************************************************
 * ==> PSS_PLFNTwoStates ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a two state for financial plan radio and check    *
 *               button object                                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PLFNTwoStatesH
#define PSS_PLFNTwoStatesH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNTwoStates
    #define PSS_PLFNTwoStates PLFNTwoStates
#endif

// processsoft
#include "PSS_PLFNGraphic.h"

#ifdef _ZBASELIBEXPORT
// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Two state for financial plan radio and check button object
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNTwoStates : public PSS_PLFNGraphic
{
    DECLARE_SERIAL(PSS_PLFNTwoStates)

    public:
        typedef PSS_PLFNGraphic inherited;

        PSS_PLFNTwoStates();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNTwoStates(const PSS_PLFNTwoStates& other);

        virtual ~PSS_PLFNTwoStates();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNTwoStates& operator = (const PSS_PLFNTwoStates& other);

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNTwoStates& operator = (const PSS_PLFNTwoStates* pOther);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_PlanFinObject* Clone() const;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PSS_PlanFinObject* pSrc);

        /**
        * Gets the right sub-menu
        *@return the right sub-menu identifier
        */
        virtual inline UINT GetRightSubMenu() const;

        /**
        * Gets if the field is static
        *@return TRUE if the field is static, otherwise FALSE
        */
        virtual inline const BOOL GetIsStatic() const;

        /**
        * Gets the unformatted string of the object image
        *@return the unformatted string of the object image
        */
        virtual CString GetUnformattedObject();

        /**
        * Converts a formatted object to numeric, date, string, etc.
        *@param value - value
        *@param locateFormat - if TRUE, format will use the locale
        *@param emptyWhenZero - if TRUE, the field will be emptied if the value is empty
        *@return TRUE if the value has changed, otherwise FALSE
        */
        virtual BOOL ConvertFormattedObject(const CString& value, BOOL locateFormat = TRUE, BOOL emptyWhenZero = FALSE);

        /**
        * Gets the check type
        *@return the check type
        */
        virtual inline const ECheckButtonType GetCheckType() const;

        /**
        * Sets the check type
        *@param value - the check type
        */
        virtual inline void SetCheckType(ECheckButtonType value);

        /**
        * Gets the check state
        *@return the check state
        */
        virtual inline const BOOL GetCheckState() const;

        /**
        * Sets the check state
        *@param value - the check state
        */
        virtual inline void SetCheckState(BOOL value);

        /**
        * Gets the size
        *@return the size
        */
        virtual inline const unsigned short GetSize() const;

        /**
        * Sets the size
        *@param value - the size
        */
        virtual inline void SetSize(unsigned short value);

        /**
        * Gets the text
        *@return the text
        */
        virtual inline const CString GetText() const;

        /**
        * Sets the text
        *@param value - the text
        */
        virtual inline void SetText(const CString& value);

        /**
        * Gets if the text is shown
        *@return TRUE if the text is shown, otherwise FALSE
        */
        virtual inline const BOOL GetShowText() const;

        /**
        * Sets if the text is shown
        *@param value - if TRUE, the text is shown
        */
        virtual inline void SetShowText(BOOL value);

        /**
        * Gets if the text acts as a control
        *@return TRUE if the text acts as a control, otherwise FALSE
        *@note If the text acts as a control, the control itself isn't shown
        */
        virtual inline const BOOL GetTextIsCtrl() const;

        /**
        * Sets if the text acts as a control
        *@param value - if TRUE, the text acts as a control
        *@note If the text acts as a control, the control itself isn't shown
        */
        virtual inline void SetTextIsCtrl(BOOL value);

        /**
        * Gets the text offset
        *@return the text offset
        */
        virtual inline const WORD GetOffsetText() const;

        /**
        * Sets the text offset
        *@param value - the text offset
        */
        virtual inline void SetOffsetText(WORD value);

        /**
        * Gets if the text should be shown on the control left
        *@return TRUE if the text should be shown on the control left, otherwise FALSE
        */
        virtual inline const BOOL GetLeftText() const;

        /**
        * Sets if the text should be shown on the control left
        *@param value - if TRUE, the text should be shown on the control left
        */
        virtual inline void SetLeftText(BOOL value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    private:
        ECheckButtonType m_CheckType;
        CString          m_Text;
        WORD             m_OffsetText;
        unsigned short   m_Size;
        BOOL             m_CheckState;
        BOOL             m_ShowText;
        BOOL             m_TextIsCtrl;
        BOOL             m_LeftText;
};

//---------------------------------------------------------------------------
// PSS_PLFNTwoStates
//---------------------------------------------------------------------------
UINT PSS_PLFNTwoStates::GetRightSubMenu() const
{
    return g_TwoStateRightSubMenu;
}
//---------------------------------------------------------------------------
const BOOL PSS_PLFNTwoStates::GetIsStatic() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
const ECheckButtonType PSS_PLFNTwoStates::GetCheckType() const
{
    return m_CheckType;
}
//---------------------------------------------------------------------------
void PSS_PLFNTwoStates::SetCheckType(ECheckButtonType value)
{
    m_CheckType = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_PLFNTwoStates::GetCheckState() const
{
    return m_CheckState;
}
//---------------------------------------------------------------------------
void PSS_PLFNTwoStates::SetCheckState(BOOL value)
{
    m_CheckState = value;
}
//---------------------------------------------------------------------------
const unsigned short PSS_PLFNTwoStates::GetSize() const
{
    return m_Size;
}
//---------------------------------------------------------------------------
void PSS_PLFNTwoStates::SetSize(unsigned short value)
{
    m_Size = value;
}
//---------------------------------------------------------------------------
const CString PSS_PLFNTwoStates::GetText() const
{
    return m_Text;
}
//---------------------------------------------------------------------------
void PSS_PLFNTwoStates::SetText(const CString& value)
{
    m_Text = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_PLFNTwoStates::GetShowText() const
{
    return m_ShowText;
}
//---------------------------------------------------------------------------
void PSS_PLFNTwoStates::SetShowText(BOOL value)
{
    m_ShowText = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_PLFNTwoStates::GetTextIsCtrl() const
{
    return m_TextIsCtrl;
}
//---------------------------------------------------------------------------
void PSS_PLFNTwoStates::SetTextIsCtrl(BOOL value)
{
    m_TextIsCtrl = value;
}
//---------------------------------------------------------------------------
const WORD PSS_PLFNTwoStates::GetOffsetText() const
{
    return m_OffsetText;
}
//---------------------------------------------------------------------------
void PSS_PLFNTwoStates::SetOffsetText(WORD value)
{
    m_OffsetText = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_PLFNTwoStates::GetLeftText() const
{
    return m_LeftText;
}
//---------------------------------------------------------------------------
void PSS_PLFNTwoStates::SetLeftText(BOOL value)
{
    m_LeftText = value;
}
//---------------------------------------------------------------------------

#endif
