/****************************************************************************
 * ==> PSS_SymbolEdit ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol edit                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SymbolEditH
#define PSS_SymbolEditH

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
#include "zBaseLib\PSS_BasicTextComponent.h"

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_SymbolEdit
    #define PSS_SymbolEdit ZBSymbolEdit
#endif

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Symbol edit
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SymbolEdit : public PSS_BasicTextComponent
{
    DECLARE_SERIAL(PSS_SymbolEdit)

    public:
        PSS_SymbolEdit();
        virtual ~PSS_SymbolEdit();

        /**
        * Gets if empty text is allowed after edition
        *@return true if empty text is allowed, otherwise false
        */
        virtual bool GetAllowEmptyText() const;

        /**
        * Sets if empty text is allowed after edition
        *@param value - if true, empty text is allowed
        */
        virtual void SetAllowEmptyText(bool value);

        /**
        * Gets the property value
        *@param propID - the property identifier
        *@param[out] value - the value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL GetValue(const int propId, int&     value) const;
        virtual BOOL GetValue(const int propId, UINT&    value) const;
        virtual BOOL GetValue(const int propId, DWORD&   value) const;
        virtual BOOL GetValue(const int propId, float&   value) const;
        virtual BOOL GetValue(const int propId, CString& value) const;

        /**
        * Sets the property value
        *@param propID - the property identifier
        *@param value/pValue - the value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetValue(const int propId, const int   value);
        virtual BOOL SetValue(const int propId, const UINT  value);
        virtual BOOL SetValue(const int propId, const DWORD value);
        virtual BOOL SetValue(const int propId, const float value);
        virtual BOOL SetValue(const int propId, LPCTSTR     pValue);

    private:
        BOOL m_AutoSizeProp;
        bool m_AllowEmptyText;
};

#endif
