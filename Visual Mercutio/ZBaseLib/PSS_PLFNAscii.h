/****************************************************************************
 * ==> PSS_PLFNAscii -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an ascii based financial plan object              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PLFNAsciiH
#define PSS_PLFNAsciiH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNAscii
    #define PSS_PLFNAscii PLFNAscii
#endif

// processsoft
#include "PSS_PlanFinObject.h"

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
* Ascii based financial plan object
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNAscii : public PSS_PlanFinObject
{
    DECLARE_SERIAL(PSS_PLFNAscii)

    public:
        /**
        * Strike styles
        */
        enum IEStrikeStyles
        {
            IE_SS_NormalStrike,
            IE_SS_UpDownStrike,
            IE_SS_CrossStrike,
            IE_SS_WaveStrike
        };

        typedef PSS_PlanFinObject inherited;

        PSS_PLFNAscii();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNAscii(const PSS_PLFNAscii& other);

        virtual ~PSS_PLFNAscii();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNAscii& operator = (const PSS_PLFNAscii& other);

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNAscii& operator = (const PSS_PLFNAscii* pOther);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_PlanFinObject* Clone() const;

        /**
        * Gets the justify layout
        *@param pDoc - document
        *@return the justify layout
        */
        virtual UINT GetJustify(ZDDocument* pDoc) const;

        /**
        * Sets the justify layout
        *@param value - the justify layout
        */
        virtual inline void SetJustify(UINT value);

        /**
        * Gets the tab list that should be shown when the user asks for object properties
        *@return the tab list identifier
        */
        virtual inline UINT GetPropertyTabs() const;

        /**
        * Gets if the object is striked
        *@return TRUE if the object is striked, otherwise FALSE
        */
        virtual inline const BOOL GetIsStriked() const;

        /**
        * Sets if the object is striked
        *@param value - if TRUE, the object is striked
        */
        virtual inline void SetIsStriked(BOOL value);

        /**
        * Gets the strike style
        *@param the strike style
        */
        virtual inline const IEStrikeStyles GetStrikeStyle() const;

        /**
        * Sets the strike style
        *@param value - the strike style
        */
        virtual inline void SetStrikeStyle(IEStrikeStyles value);

        /**
        * Gets if the field must keep a history of entered values
        *@return TRUE if the field must keep a history of entered values, otherwise FALSE
        */
        virtual inline const BOOL GetKeepHistory() const;

        /**
        * Sets if the field must keep a history of entered values
        *@param value - if TRUE, the field must keep a history of entered values
        */
        virtual inline void SetKeepHistory(BOOL value);

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
        IEStrikeStyles m_StrikeStyle;
        UINT           m_Justify;
        BOOL           m_IsStriked;
        BOOL           m_KeepHistory;
};

//---------------------------------------------------------------------------
// PSS_PLFNAscii
//---------------------------------------------------------------------------
void PSS_PLFNAscii::SetJustify(UINT nValue)
{
    m_Justify = nValue;
}
//---------------------------------------------------------------------------
UINT PSS_PLFNAscii::GetPropertyTabs() const
{
    return (g_PropertyGeneralTextPage | g_PropertySizePage);
}
//---------------------------------------------------------------------------
const BOOL PSS_PLFNAscii::GetIsStriked() const
{
    return m_IsStriked;
}
//---------------------------------------------------------------------------
void PSS_PLFNAscii::SetIsStriked(BOOL value)
{
    m_IsStriked = value;
}
//---------------------------------------------------------------------------
const PSS_PLFNAscii::IEStrikeStyles PSS_PLFNAscii::GetStrikeStyle() const
{
    return m_StrikeStyle;
}
//---------------------------------------------------------------------------
void PSS_PLFNAscii::SetStrikeStyle(IEStrikeStyles value)
{
    m_StrikeStyle = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_PLFNAscii::GetKeepHistory() const
{
    return m_KeepHistory;
}
//---------------------------------------------------------------------------
void PSS_PLFNAscii::SetKeepHistory(BOOL value)
{
    m_KeepHistory = value;
}
//---------------------------------------------------------------------------

#endif
