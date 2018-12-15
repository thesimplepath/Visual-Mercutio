// MskEdit.cpp : implementation file
//

#include "stdafx.h"
#include "MskEdit.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZMaskEdit

void AFXAPI DDX_ZMaskEdit(CDataExchange* pDX, int nIDC, ZMaskEdit& rControl, CString& data)
{
    DDX_Control(pDX, nIDC, (CWnd&)rControl);
    if (!pDX->m_bSaveAndValidate)
    {
        rControl.SetData(data);
    }
    else
    {
        data = rControl.GetData();
    }
}

IMPLEMENT_DYNCREATE(ZMaskEdit, CEdit)

ZMaskEdit::ZMaskEdit()
  : m_bInit(false),
    m_strPrompt("_"),
    m_iNumChars(0),
    m_iCurrentChar(0),
    m_bShiftDown(false)
{
    for (int i = 0; i < MAX_CHARS; i++)
        m_Char[i] = NULL;

    //SubclassWindow(pParent->m_hWnd);
    //pParent->SubclassWindow(this->m_hWnd);
}

ZMaskEdit::~ZMaskEdit()
{
    for (int i = 0; i < MAX_CHARS; i++)
        if (m_Char[i] != NULL)
        {
            delete m_Char[i];
            m_Char[i] = NULL;
        }
}


BEGIN_MESSAGE_MAP(ZMaskEdit, CEdit)
    //{{AFX_MSG_MAP(ZMaskEdit)
    ON_WM_CHAR()
    ON_WM_KEYDOWN()
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_SETFOCUS()
    ON_WM_LBUTTONUP()
    ON_WM_KEYUP()
    ON_WM_LBUTTONDBLCLK()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZMaskEdit message handlers

int ZMaskEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CEdit::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    return 0;
}

void ZMaskEdit::OnDestroy() 
{
    CEdit::OnDestroy();


}

BOOL ZMaskEdit::PreCreateWindow(CREATESTRUCT& cs) 
{
    cs.style |= WS_TABSTOP | WS_VISIBLE | WS_DISABLED | ES_AUTOHSCROLL;
    cs.dwExStyle |= WS_EX_OVERLAPPEDWINDOW;
    
    return CEdit::PreCreateWindow(cs);
}

CString ZMaskEdit::GetFormatedBuffer(CString strMask, CString strInitialData)
{
    if (!Parse(strMask))
    {
        return "";
    }

    if (!SetValidChars(strMask, false))
    {
        return "";
    }
    
    return FormatedBuffer(strInitialData);
}

CString ZMaskEdit::FormatedBuffer(const CString& data)
{
    CString strWindowText;
    CString strData;
    int     iNextDataChar = 0;
    
    for (int i = 1; i <= m_iNumChars; i++)
    {
        if (m_Char[i - 1]->m_bStaticChar)
        {
            strWindowText += m_Char[i - 1]->m_strValids;
        }
        else
        {
            if (iNextDataChar < data.GetLength())
            {
                strData = data[iNextDataChar++];
                if (m_Char[i - 1]->m_strValids.Find(strData[0]) < 0)
                    strData = m_strPrompt;
            }
            else
            {
                strData = m_strPrompt;
            }
            
            strWindowText += strData[0];
        }
    }
    return strWindowText;
}

void ZMaskEdit::SetData(const CString& data)
{

    SetWindowText( FormatedBuffer( data ) );
}

CString ZMaskEdit::GetData()
{
    CString strWindowText;
    GetWindowText(strWindowText);
    CString strData;
    
    for (int i = 1; i <= m_iNumChars; i++)
    {
        if (!m_Char[i - 1]->m_bStaticChar)
        {
            if (strWindowText.GetLength() >= i)
            {
                if (strWindowText[i - 1] != m_strPrompt)
                    strData += strWindowText[i - 1];
            }
            else
                strData += m_strPrompt;
        }
    }

    return strData;
}

void ZMaskEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    switch (nChar)
    {
    case VK_TAB:
                //(((CWnd*)GetParent())->GetNextDlgTabItem(this, m_bShiftDown))->SetFocus();
                break;
    
    case VK_BACK:
                if (m_iCurrentChar > 0)
                {
                    int iNewNext = FindNextChar(m_iCurrentChar - 1, false, false);
                    if (iNewNext >= 0)
                    {
                        SetSel(iNewNext, iNewNext + 1);
                        ReplaceSel(m_strPrompt);
                        m_iCurrentChar = iNewNext;
                        SetSel(m_iCurrentChar, m_iCurrentChar);
                    }
                }
                break;

    default:    
                int x, y, z;
                GetSel(x,y);
                if (x != y)
                {
                    CString szReplaceText = "";
                    for (z = x; z < y; z++)
                    {
                        if (m_Char[z]->m_bStaticChar)
                        {
                            szReplaceText += m_Char[z]->m_strValids;
                        }
                        else
                        {
                            szReplaceText += m_strPrompt;
                        }
                    }
                    ReplaceSel(szReplaceText);
                    m_iCurrentChar = FindNextChar(x, false, true);
                    SetSel(m_iCurrentChar, m_iCurrentChar);
                }
        
        
                if (m_iCurrentChar < m_iNumChars)
                {
                    if (m_iCurrentChar >= 0 && m_Char[m_iCurrentChar]->m_strValids.Find((TCHAR)nChar) >= 0 )
                    {
                        int iNewNext = FindNextChar(m_iCurrentChar + 1, false, true);
                        SetSel(m_iCurrentChar, m_iCurrentChar + 1);
                        ReplaceSel((CString)(char)nChar);
                        if (iNewNext >= 0)
                        {
                            m_iCurrentChar = iNewNext;
                        }
                        else
                        {
                            m_iCurrentChar++;
                        }
                        SetSel(m_iCurrentChar, m_iCurrentChar);
                    }
                }
                break;
    }

    //CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void ZMaskEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    switch (nChar)
    {
    case VK_SHIFT:
                m_bShiftDown = false;
                break;
    
    default:
                break;
    }
    
    CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}

void ZMaskEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    int iNext = 0;
    CWnd* pNextItem = NULL;
    
    switch (nChar)
    {
    // Tab key
    case VK_TAB:
                pNextItem = (((CWnd*)GetParent())->GetNextDlgTabItem(this, (m_bShiftDown) ? TRUE : FALSE));
                if (pNextItem->IsKindOf(RUNTIME_CLASS(ZMaskEdit)))
                    ((ZMaskEdit*)pNextItem)->m_bShiftDown = m_bShiftDown;
                (((CWnd*)GetParent())->GetNextDlgTabItem(this, (m_bShiftDown) ? TRUE : FALSE))->SetFocus();
                break;
        
    // Shift key
    case VK_SHIFT:
                m_bShiftDown = true;
                break;
        
    // Left arrow key
    case VK_LEFT:
                iNext = FindNextChar(m_iCurrentChar - 1, false, false);
                if (iNext >= 0)
                {
                    m_iCurrentChar = iNext;
                    SetSel(m_iCurrentChar, m_iCurrentChar);
                }
                break;
    
    // Right arrow key
    case VK_RIGHT:
                iNext = FindNextChar(m_iCurrentChar + 1, false, true);
                if (iNext >= 0)
                    m_iCurrentChar = iNext;
                else
                {
                    m_iCurrentChar = FindNextChar(m_iNumChars - 1, false, false) + 1;
                }
                SetSel(m_iCurrentChar, m_iCurrentChar);
                break;

    // Home key
    case VK_HOME:
                if (m_bShiftDown)
                {
                    SetSel(0, m_iCurrentChar);
                }
                else
                {
                    m_iCurrentChar = FindNextChar(0, false, true);
                    SetSel(m_iCurrentChar, m_iCurrentChar);
                }
                break;

    // End key
    case VK_END:
                if (m_bShiftDown)
                {
                    int iLast = FindNextChar(m_iNumChars - 1, false, false) + 1;
                    SetSel(m_iCurrentChar, iLast);
                }
                else
                {
                    m_iCurrentChar = FindNextChar(m_iNumChars - 1, false, false) + 1;
                    SetSel(m_iCurrentChar, m_iCurrentChar);
                }
                break;

    // Insert key
    case VK_INSERT:

                break;

    // Delete key
    case VK_DELETE:
                int x, y, z;
                GetSel(x,y);
                if (x != y)
                {
                    CString szReplaceText = "";
                    for (z = x; z < y; z++)
                    {
                        if (m_Char[z]->m_bStaticChar)
                        {
                            szReplaceText += m_Char[z]->m_strValids;
                        }
                        else
                        {
                            szReplaceText += m_strPrompt;
                        }
                    }
                    ReplaceSel(szReplaceText);
                    m_iCurrentChar = FindNextChar(x, false, true);
                    SetSel(m_iCurrentChar, m_iCurrentChar);
                }
                else if (m_iCurrentChar <= FindNextChar(m_iNumChars - 1, false, false))
                {
                    SetSel(m_iCurrentChar, m_iCurrentChar + 1);
                    ReplaceSel(m_strPrompt);
                    iNext = FindNextChar(m_iCurrentChar + 1, false, true);
                    if (iNext >= 0)
                        m_iCurrentChar = iNext;
                    else
                        m_iCurrentChar++;
                    SetSel(m_iCurrentChar, m_iCurrentChar);
                }
                break;

    default:
                break;

    }

    //CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

bool ZMaskEdit::Init(CString strMask, CString strInitialData)
{
    m_bInit = false;
    
    if (!Parse(strMask))
    {
        SetWindowText("Init failed.");
        EnableWindow(FALSE);
        return false;
    }

    if (!SetValidChars(strMask))
    {
        SetWindowText("SetValidChars failed.");
        EnableWindow(FALSE);
        return false;                          
    }
    
    SetData(strInitialData);
    m_iCurrentChar = FindNextChar(0, false, true);
    this->SetFocus();
    SetSel(m_iCurrentChar, m_iCurrentChar);

    EnableWindow(TRUE);  // this line is important!
    m_bInit = true;

    return true;
}

int ZMaskEdit::FindNextChar(int iStartPos, bool bStatic, bool bForward)
{
    int iIndex = 0;
    int iReturnVal = -1;
    
    if (bForward)
    {
        for (int iIndex = iStartPos; iIndex < m_iNumChars; iIndex++)
        {
            if (m_Char[iIndex]->m_bStaticChar == bStatic)
            {
                iReturnVal = iIndex;
                break;
            }
        }
    }
    else
    {
        for (int iIndex = iStartPos; iIndex >= 0; iIndex--)
        {
            if (m_Char[iIndex]->m_bStaticChar == bStatic)
            {
                iReturnVal = iIndex;
                break;
            }
        }
    }

    return iReturnVal;
}

bool ZMaskEdit::SetValidChars(const CString& strMask, bool OnWindow)
{
    CString strChars;
    CString strRangeLow; 
    bool    bInside       = false;
    bool    bInsideEscape = false;
    bool    bInsideRange  = false;
    int     iNextChar     = 0;
    int     i;
    
    // Clear valid chars
    for (i = 0; i < MAX_CHARS; i++)
        if (m_Char[i] != NULL)
        {
            delete m_Char[i];
            m_Char[i] = NULL;
        }

    // Walk through mask string
    for (i = 0; i < strMask.GetLength(); i++)
    {
        switch (strMask[i])
        {
        case '[':   bInside = true;
                    break;            //done

        case ']':   bInside = false;
                    m_Char[iNextChar++] = new ZMaskEditChar(strChars, false);
                    strChars = "";
                    break;

        case '-':   if (bInside)
                    {
                        if (bInsideEscape)
                        {
                            strChars += "-";
                            bInsideEscape = false;  //done
                        }
                        else
                        {
                            if (strChars.GetLength() == 0)
                                return false;
                            bInsideRange = true;
                            strRangeLow = strChars.Right(1);
                            strChars = strChars.Left(strChars.GetLength() - 1); //done
                        }
                    }
                    else
                    {
                        m_Char[iNextChar++] = new ZMaskEditChar("-", true); //done
                    }
                    break;

        case '\\':  if (bInside)
                    {
                        if (!bInsideEscape)
                        {
                            bInsideEscape = true;  //done
                        }
                        else
                        {
                            if (bInsideRange)
                            {
                                strChars += GetRange(strRangeLow, "\\");
                                strRangeLow = "";
                                bInsideRange = false;  //done
                            }
                            else
                            {
                                strChars += "\\";
                                bInsideEscape = false;  //done
                            }
                        }
                    }
                    else
                    {
                        m_Char[iNextChar++] = new ZMaskEditChar("\\", true); //done
                    }
                    break;

        default:    if (bInside)
                    {
                        if (bInsideEscape)
                        {
                            bInsideEscape = false;        //done
                        }

                        if (bInsideRange)
                        {
                            strChars += GetRange(strRangeLow, strMask[i]);
                            strRangeLow = "";
                            bInsideRange = false;   //done
                        }
                        else
                        {
                            strChars += strMask[i]; //done
                        }
                    }
                    else
                    {
                        m_Char[iNextChar++] = new ZMaskEditChar(strMask[i], true); //done
                    }
                    break;
        }
    }

    m_iNumChars = iNextChar;
    if (OnWindow == true)
        SetLimitText(m_iNumChars);
    
    return true;
}

CString ZMaskEdit::GetRange(CString szLow, CString szHigh)
{
    CString szReturn = "";

    if (szLow.GetLength() == 1 && szHigh.GetLength() == 1)
    {
        char first = szLow[0];
        char last  = szHigh[0];

        for (int i = first; i <= last; i++)
            szReturn += (CString)(char)i;
    }

    return szReturn;
}

bool ZMaskEdit::Parse(const CString& strMask)
{
    bool bValid = true;
    int iBracketState = 0;
    //int iDashState = 0;
    
    for (int i = 1; i <= strMask.GetLength(); i++)
    {
        switch (strMask[i - 1])
        {
        case '[':   iBracketState++; break;

        case ']':   iBracketState--; break;

        //case '-':   if (iBracketState > 0)
        //                iDashState = 1;
        //            break;

        default:    //if (iBracketState > 0) && iDashState == 1)
                    //    iDashState = 0;
                    break;
        }

        // Make sure the [ ] are in sync
        if (iBracketState < 0 || iBracketState > 1)
            bValid = false;

        // Make sure there is a character after a '-' inside the [ ]
        //if (iBracketState == 0 && iDashState == 1)
        //    bValid = false;
    }

    return (iBracketState == 0 /*&& iDashState == 0*/ && bValid) ? true : false;
}

bool ZMaskEdit::SetPromptChar(CString strPromptChar)
{
    if (strPromptChar.GetLength() != 1)
        return false;

    m_strPrompt = strPromptChar;
    return true;
}


void ZMaskEdit::OnSetFocus(CWnd* pOldWnd) 
{
    CEdit::OnSetFocus(pOldWnd);
    
    //SetSel(m_iCurrentChar, m_iCurrentChar);
    SetSel(0, -1);
}

void ZMaskEdit::OnLButtonUp(UINT nFlags, CPoint point) 
{
    int x, y;
    GetSel(x, y);

    if (x == y)
    {
        m_iCurrentChar = x;
        SetSel(m_iCurrentChar, m_iCurrentChar);
    }
    
    CEdit::OnLButtonUp(nFlags, point);
}

void ZMaskEdit::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    SetSel(0, -1);
}
