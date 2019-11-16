/****************************************************************************
 * ==> PSS_SmartString -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a smart string                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SmartStringH
#define PSS_SmartStringH

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
* Smart string
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SmartString
{
    public:
        /**
        * Constructor
        *@param pText - text
        */
        inline PSS_SmartString(LPCTSTR pText = NULL);

        /**
        * Constructor
        *@param textID - text resource identifier
        */
        PSS_SmartString(UINT textID);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_SmartString(const PSS_SmartString& other);

        virtual ~PSS_SmartString();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_SmartString& operator = (const PSS_SmartString& data);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_SmartString& operator = (LPCTSTR pData);

        /**
        * Assignment operator
        *@return contained text
        */
        operator LPCTSTR() const;

    protected:
        /**
        * Sets string
        *@param str - string
        */
        virtual void SetCString(const CString& str);

        /**
        * Sets string
        *@param str - pText string text
        */
        void SetLPCTSTR(LPCTSTR pText);

        /**
        * Clears the string content
        */
        void Clear();

    private:
        union
        {
            CString* m_pStrText;
            LPCTSTR  m_pText;
        };

        bool m_CString;
};

//---------------------------------------------------------------------------
// PSS_SmartString
//---------------------------------------------------------------------------
PSS_SmartString::PSS_SmartString(LPCTSTR pText)
{
    SetLPCTSTR(pText);
}
//---------------------------------------------------------------------------

#endif
