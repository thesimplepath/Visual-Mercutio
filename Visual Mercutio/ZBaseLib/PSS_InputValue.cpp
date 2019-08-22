/****************************************************************************
 * ==> PSS_InputValue ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an input value                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_InputValue.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InputValue, ZIDialog)
    //{{AFX_MSG_MAP(PSS_InputValue)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InputValue
//---------------------------------------------------------------------------
PSS_InputValue::PSS_InputValue(const CString& title, const CString& value, CWnd* pParent) :
    ZIDialog(PSS_InputValue::IDD, TRUE, pParent),
    m_Title(title),
    m_Value(value)
{}
//---------------------------------------------------------------------------
PSS_InputValue::PSS_InputValue(UINT titleID, const CString& value, CWnd* pParent) :
    ZIDialog(PSS_InputValue::IDD, TRUE, pParent),
    m_Value(value)
{
    m_Title.LoadString(titleID);
}
//---------------------------------------------------------------------------
void PSS_InputValue::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_InputValue)
    DDX_Text(pDX, IDC_VALUE, m_Value);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_InputValue::OnInitDialog()
{
    ZIDialog::OnInitDialog();

    if (!m_Title.IsEmpty())
        SetWindowText(m_Title);

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
