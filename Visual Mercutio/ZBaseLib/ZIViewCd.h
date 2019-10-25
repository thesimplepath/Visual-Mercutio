/****************************************************************************
 * ==> PSS_CodeView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a code view                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CodeViewH
#define PSS_CodeViewH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_View.h"

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
* Code view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZIViewCode : public PSS_View
{
    DECLARE_DYNCREATE(ZIViewCode)

public:
    typedef PSS_View inherited;

    virtual inline EClassType GetDisplayCode();

    virtual inline void SetDisplayCode(EClassType Type);

protected:
    ZIViewCode();
    virtual ~ZIViewCode();

    virtual void OnDraw(CDC* pDC);

    //## Operation: OnInitialUpdate%862261466
    virtual void OnInitialUpdate();

    //## Operation: OnPrint%901710585
    virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

    //## Operation: OnPreparePrinting%901710586
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

    //## Operation: OnBeginPrinting%901710587
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);

    //## Operation: OnEndPrinting%901710588
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

    /// Generated message map functions
    //{{AFX_MSG(ZIViewCode)
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnOnlyNumericFields();
    afx_msg void OnUpdateOnlyNumericFields(CCmdUI* pCmdUI);
    afx_msg LONG OnDisplayFieldType(UINT message, LONG lParam);
    afx_msg LONG OnSynchronizeVScroll(UINT message, LONG lParam);
    afx_msg LONG OnSynchronizeHScroll(UINT message, LONG lParam);
    afx_msg void OnDisplayCalculatedCode();
    afx_msg void OnUpdateDisplayCalculatedCode(CCmdUI* pCmdUI);
    afx_msg void OnDisplayallCode();
    afx_msg void OnUpdateDisplayallCode(CCmdUI* pCmdUI);
    afx_msg void OnDisplayStaticCode();
    afx_msg void OnUpdateDisplayStaticCode(CCmdUI* pCmdUI);
    afx_msg void OnDisplayTextCode();
    afx_msg void OnUpdateDisplayTextCode(CCmdUI* pCmdUI);
    afx_msg void OnDisplayGraphicCode();
    afx_msg void OnUpdateDisplayGraphicCode(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    EClassType m_iCodeType;
    int        m_iSavePageForPrinting;

    /**
    * Copy constructor
    *@param other - other object to copy from
    */
    ZIViewCode(const ZIViewCode& other);

    /**
    * Copy operator
    *@param other - other object to copy from
    *@return copy of itself
    */
    const ZIViewCode& operator = (const ZIViewCode& other);
};

//---------------------------------------------------------------------------
// PSS_CodeView
//---------------------------------------------------------------------------
EClassType ZIViewCode::GetDisplayCode()
{
    return m_iCodeType;
}
//---------------------------------------------------------------------------
void ZIViewCode::SetDisplayCode(EClassType Type)
{
    m_iCodeType = Type;
}
//---------------------------------------------------------------------------

#endif
