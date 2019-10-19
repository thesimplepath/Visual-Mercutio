/****************************************************************************
 * ==> PSS_InputValue ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an input value                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InputValueH
#define PSS_InputValueH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_Dialog.h"

// resources
#include "zRes32\ZRes.h"

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
* Input value
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InputValue : public PSS_Dialog
{
    public:
        /**
        * Constructor
        *@param title - title
        *@param value - value
        *@param pParent - parent window, can be NULL
        */
        PSS_InputValue(const CString& title = "", const CString& value = "", CWnd* pParent = NULL);

        /**
        * Constructor
        *@param titleID - title resource identifier
        *@param value - value
        *@param pParent - parent window, can be NULL
        */
        PSS_InputValue(UINT titleID, const CString& value = "", CWnd* pParent = NULL);

        /**
        * Gets the value
        *@return the value
        */
        virtual inline CString GetValue() const;

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_INPUT_VALUE
        };

        CString m_Title;
        CString m_Value;

    protected:
        /**
        * DDX/DDV support
        *@param pDX - DDX/DDV data
        */
        virtual void DoDataExchange(CDataExchange* pDX);

        /// Generated message map functions
        //{{AFX_MSG(PSS_InputValue)
        virtual BOOL OnInitDialog();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
// PSS_InputValue
//---------------------------------------------------------------------------
CString PSS_InputValue::GetValue() const
{
    return m_Value;
}
//---------------------------------------------------------------------------

#endif
