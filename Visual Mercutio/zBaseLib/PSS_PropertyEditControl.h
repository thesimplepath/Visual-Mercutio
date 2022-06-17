/****************************************************************************
 * ==> PSS_PropertyEditControl ---------------------------------------------*
 ****************************************************************************
 * Description : Override the CEdit class, in order to create a custom edit *
 *               control which allows to show properties                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PropertyEditControlH
#define PSS_PropertyEditControlH

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
* Override the CEdit class, in order to create a custom edit
* control which allows to show properties
*@author Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PropertyEditControl : public CEdit
{
    public:
        PSS_PropertyEditControl();
        virtual ~PSS_PropertyEditControl();

    protected:
        // generated message map functions
        //{{AFX_MSG(PSS_PropertyEditControl)
        afx_msg void OnCancel();
        afx_msg void OnCut();
        afx_msg void OnCopy();
        afx_msg void OnPaste();
        afx_msg void OnDelete();
        afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Called when the property value changed
        */
        virtual void OnPropertieValueChanged();

    private:
        CMenu m_pPropertiesMenu;
};

#endif
