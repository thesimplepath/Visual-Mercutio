/****************************************************************************
 * ==> PSS_MaskEditBase ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic mask edit                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MaskEditBaseH
#define PSS_MaskEditBaseH

#if _MSC_VER >= 1000
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

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_Max_Chars 256
//---------------------------------------------------------------------------

/**
* Mask edit char
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_MaskEditChar
{
public:
    CString m_Data;
    bool    m_StaticChar;

    inline PSS_MaskEditChar();

    /**
    * Constructor
    *@param chars - chars
    */
    inline PSS_MaskEditChar(const CString& chars);

    /**
    * Constructor
    *@param chars - chars
    *@param staticChar - if true, the char is static
    */
    inline PSS_MaskEditChar(const CString chars, bool staticChar);
};

//---------------------------------------------------------------------------
// PSS_MaskEditChar
//---------------------------------------------------------------------------
PSS_MaskEditChar::PSS_MaskEditChar() :
    m_StaticChar(false)
{}
//---------------------------------------------------------------------------
PSS_MaskEditChar::PSS_MaskEditChar(const CString& chars) :
    m_Data(chars),
    m_StaticChar(false)
{}
//---------------------------------------------------------------------------
PSS_MaskEditChar::PSS_MaskEditChar(const CString chars, bool staticChar) :
    m_Data(chars),
    m_StaticChar(staticChar)
{}
//---------------------------------------------------------------------------

/**
* Basic mask edit
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MaskEditBase : public CEdit
{
    DECLARE_DYNCREATE(PSS_MaskEditBase)

    public:
        PSS_MaskEditBase();
        virtual ~PSS_MaskEditBase();

        /**
        * Initializes the edit
        *@param mask - mask
        *@param initialData - initial data
        *@return true on success, otherwise false
        */
        virtual bool Init(const CString& mask, const CString& initialData = "");

        /**
        * Gets the formatted buffer
        *@param mask - mask
        *@param initialData - initial data
        *@return the formatted buffer
        */
        virtual CString GetFormattedBuffer(const CString& mask, const CString& initialData = "");

        /**
        * Sets the prompt char
        *@param promptChar - prompt char
        *@return true on success, otherwise false
        */
        virtual bool SetPromptChar(const CString& promptChar);

        /**
        * Gets the data
        *@return the data
        */
        virtual CString GetData() const;

        /**
        * Sets the data
        *@param data - the data
        */
        virtual void SetData(const CString& data);

    protected:
        PSS_MaskEditChar* m_Char[M_Max_Chars];
        CString           m_Prompt;
        int               m_NumChars;
        int               m_CurrentChar;
        bool              m_Init;
        bool              m_ShiftDown;

        /**
        * Pre-creates the window
        *@param cs - create structure
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

        /**
        * Parses the edit content
        *@param mask - mask
        *@return true on success, otherwise false
        */
        virtual bool Parse(const CString& mask);

        /**
        * Sets the valid chars
        *@param mask - mask
        *@param onWindow - if true, the chars will be limited as those visible on the window
        *@return true on success, otherwise false
        */
        virtual bool SetValidChars(const CString& mask, bool onWindow = true);

        /**
        * Gets the range
        *@param low - low
        *@return high - high
        *@return the range
        */
        virtual CString GetRange(const CString& low, const CString& high) const;

        /**
        * Gets the formatted buffer
        *@param data - data
        *@return the formatted buffer
        */
        virtual CString FormattedBuffer(const CString& data) const;

        /**
        * Finds the next char
        *@param startPos - start position
        *@param staticChars - if true, the next char to find should be static
        *@param forward - if true, the search will be done in the forward direction
        *@return found position, -1 if not found or on error
        */
        virtual int FindNextChar(int startPos, bool staticChars, bool forward) const;

        //{{AFX_MSG(PSS_MaskEditBase)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnDestroy();
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
        afx_msg void OnSetFocus(CWnd* pOldWnd);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

/**
* Mask edit DDX/DDV support
*@param pDX - DDX/DDV data
*@param nIDC - control identifier
*@param rControl - mask edit control
*@param data - data
*/
AFX_EXT_API void AFXAPI DDX_MaskEditBase(CDataExchange* pDX, int nIDC, PSS_MaskEditBase& rControl, CString& data);

#endif
