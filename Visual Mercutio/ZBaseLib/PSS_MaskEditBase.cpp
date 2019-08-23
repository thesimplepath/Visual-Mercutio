/****************************************************************************
 * ==> PSS_MaskEditBase ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic mask edit                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_MaskEditBase.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global functions
//---------------------------------------------------------------------------
void AFXAPI DDX_MaskEditBase(CDataExchange* pDX, int nIDC, PSS_MaskEditBase& rControl, CString& data)
{
    DDX_Control(pDX, nIDC, (CWnd&)rControl);

    if (!pDX->m_bSaveAndValidate)
        rControl.SetData(data);
    else
        data = rControl.GetData();
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_MaskEditBase, CEdit)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_MaskEditBase, CEdit)
    //{{AFX_MSG_MAP(PSS_MaskEditBase)
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
//---------------------------------------------------------------------------
// PSS_MaskEditBase
//---------------------------------------------------------------------------
PSS_MaskEditBase::PSS_MaskEditBase() :
    CEdit(),
    m_Prompt("_"),
    m_NumChars(0),
    m_CurrentChar(0),
    m_Init(false),
    m_ShiftDown(false)
{
    for (int i = 0; i < M_Max_Chars; ++i)
        m_Char[i] = NULL;
}
//---------------------------------------------------------------------------
PSS_MaskEditBase::~PSS_MaskEditBase()
{
    for (int i = 0; i < M_Max_Chars; ++i)
        if (m_Char[i])
            delete m_Char[i];
}
//---------------------------------------------------------------------------
bool PSS_MaskEditBase::Init(const CString& mask, const CString& initialData)
{
    m_Init = false;

    if (!Parse(mask))
    {
        SetWindowText("Init failed.");
        EnableWindow(FALSE);
        return false;
    }

    if (!SetValidChars(mask))
    {
        SetWindowText("SetValidChars failed.");
        EnableWindow(FALSE);
        return false;
    }

    SetData(initialData);
    m_CurrentChar = FindNextChar(0, false, true);
    SetFocus();
    SetSel(m_CurrentChar, m_CurrentChar);

    // this line is important!
    EnableWindow(TRUE);
    m_Init = true;

    return true;
}
//---------------------------------------------------------------------------
CString PSS_MaskEditBase::GetFormatedBuffer(const CString& mask, const CString& initialData)
{
    if (!Parse(mask))
        return "";

    if (!SetValidChars(mask, false))
        return "";

    return FormatedBuffer(initialData);
}
//---------------------------------------------------------------------------
bool PSS_MaskEditBase::SetPromptChar(const CString& promptChar)
{
    if (promptChar.GetLength() != 1)
        return false;

    m_Prompt = promptChar;
    return true;
}
//---------------------------------------------------------------------------
CString PSS_MaskEditBase::GetData() const
{
    CString windowText;
    GetWindowText(windowText);

    CString data;

    for (int i = 1; i <= m_NumChars; ++i)
        if (!m_Char[i - 1]->m_StaticChar)
            if (windowText.GetLength() >= i)
            {
                if (windowText[i - 1] != m_Prompt)
                    data += windowText[i - 1];
            }
            else
                data += m_Prompt;

    return data;
}
//---------------------------------------------------------------------------
void PSS_MaskEditBase::SetData(const CString& data)
{
    SetWindowText(FormatedBuffer(data));
}
//---------------------------------------------------------------------------
BOOL PSS_MaskEditBase::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style     |= WS_TABSTOP | WS_VISIBLE | WS_DISABLED | ES_AUTOHSCROLL;
    cs.dwExStyle |= WS_EX_OVERLAPPEDWINDOW;

    return CEdit::PreCreateWindow(cs);
}
//---------------------------------------------------------------------------
bool PSS_MaskEditBase::Parse(const CString& mask)
{
    bool valid        = true;
    int  bracketState = 0;

    for (int i = 1; i <= mask.GetLength(); ++i)
    {
        switch (mask[i - 1])
        {
            case '[': ++bracketState; break;
            case ']': --bracketState; break;
            default:                  break;
        }

        // make sure the [ ] are in sync
        if (bracketState < 0 || bracketState > 1)
            valid = false;
    }

    return (!bracketState && valid) ? true : false;
}
//---------------------------------------------------------------------------
bool PSS_MaskEditBase::SetValidChars(const CString& mask, bool onWindow)
{
    // clear valid chars
    for (int i = 0; i < M_Max_Chars; ++i)
        if (m_Char[i])
        {
            delete m_Char[i];
            m_Char[i] = NULL;
        }

    CString   chars;
    CString   rangeLow;
    bool      inside       = false;
    bool      insideEscape = false;
    bool      insideRange  = false;
    int       nextChar     = 0;
    const int maskLength   = mask.GetLength();

    // iterate through mask chars
    for (int i = 0; i < maskLength; ++i)
    {
        switch (mask[i])
        {
            case '[':
                inside = true;
                break;

            case ']':
                inside = false;
                m_Char[nextChar] = new PSS_MaskEditChar(chars, false);
                ++nextChar;
                chars = "";
                break;

            case '-':
                if (inside)
                {
                    if (insideEscape)
                    {
                        chars += "-";
                        insideEscape = false;
                    }
                    else
                    {
                        if (chars.GetLength() == 0)
                            return false;
    
                        insideRange = true;
                        rangeLow    = chars.Right(1);
                        chars       = chars.Left(chars.GetLength() - 1);
                    }
                }
                else
                {
                    m_Char[nextChar] = new PSS_MaskEditChar("-", true);
                    ++nextChar;
                }

                break;

            case '\\':
                if (inside)
                {
                    if (!insideEscape)
                        insideEscape = true;
                    else
                    if (insideRange)
                    {
                        chars += GetRange(rangeLow, "\\");
                        rangeLow    = "";
                        insideRange = false;
                    }
                    else
                    {
                        chars        += "\\";
                        insideEscape  = false;
                    }
                }
                else
                {
                    m_Char[nextChar] = new PSS_MaskEditChar("\\", true);
                    ++nextChar;
                }

                break;

            default:
                if (inside)
                {
                    if (insideEscape)
                        insideEscape = false;

                    if (insideRange)
                    {
                        chars       += GetRange(rangeLow, mask[i]);
                        rangeLow     = "";
                        insideRange  = false;
                    }
                    else
                        chars += mask[i];
                }
                else
                {
                    m_Char[nextChar] = new PSS_MaskEditChar(mask[i], true);
                    ++nextChar;
                }

                break;
        }
    }

    m_NumChars = nextChar;

    if (onWindow)
        SetLimitText(m_NumChars);

    return true;
}
//---------------------------------------------------------------------------
CString PSS_MaskEditBase::GetRange(const CString& low, const CString& high) const
{
    CString result = "";

    if (low.GetLength() == 1 && high.GetLength() == 1)
    {
        const char first = low[0];
        const char last  = high[0];

        for (int i = first; i <= last; ++i)
            result += CString(char(i));
    }

    return result;
}
//---------------------------------------------------------------------------
CString PSS_MaskEditBase::FormatedBuffer(const CString& data) const
{
    CString windowText;
    CString nextData;
    int     nextDataChar = 0;

    for (int i = 1; i <= m_NumChars; ++i)
        if (m_Char[i - 1]->m_StaticChar)
            windowText += m_Char[i - 1]->m_Data;
        else
        {
            if (nextDataChar < data.GetLength())
            {
                nextData = data[nextDataChar];
                ++nextDataChar;

                if (m_Char[i - 1]->m_Data.Find(nextData[0]) < 0)
                    nextData = m_Prompt;
            }
            else
                nextData = m_Prompt;

            windowText += nextData[0];
        }

    return windowText;
}
//---------------------------------------------------------------------------
int PSS_MaskEditBase::FindNextChar(int startPos, bool staticChars, bool forward) const
{
    int result = -1;

    if (forward)
    {
        for (int index = startPos; index < m_NumChars; ++index)
            if (m_Char[index]->m_StaticChar == staticChars)
            {
                result = index;
                break;
            }
    }
    else
        for (int index = startPos; index >= 0; --index)
            if (m_Char[index]->m_StaticChar == staticChars)
            {
                result = index;
                break;
            }

    return result;
}
//---------------------------------------------------------------------------
int PSS_MaskEditBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CEdit::OnCreate(lpCreateStruct) == -1)
        return -1;

    return 0;
}
//---------------------------------------------------------------------------
void PSS_MaskEditBase::OnDestroy()
{
    CEdit::OnDestroy();
}
//---------------------------------------------------------------------------
void PSS_MaskEditBase::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    switch (nChar)
    {
        case VK_TAB:
            break;
    
        case VK_BACK:
            if (m_CurrentChar > 0)
            {
                const int newNext = FindNextChar(m_CurrentChar - 1, false, false);

                if (newNext >= 0)
                {
                    SetSel(newNext, newNext + 1);
                    ReplaceSel(m_Prompt);
                    m_CurrentChar = newNext;
                    SetSel(m_CurrentChar, m_CurrentChar);
                }
            }

            break;

        default:
        {
            int x, y, z;
            GetSel(x, y);

            if (x != y)
            {
                CString replaceText = "";

                for (z = x; z < y; ++z)
                    if (m_Char[z]->m_StaticChar)
                        replaceText += m_Char[z]->m_Data;
                    else
                        replaceText += m_Prompt;

                ReplaceSel(replaceText);
                m_CurrentChar = FindNextChar(x, false, true);
                SetSel(m_CurrentChar, m_CurrentChar);
            }

            if (m_CurrentChar < m_NumChars)
                if (m_CurrentChar >= 0 && m_Char[m_CurrentChar]->m_Data.Find(TCHAR(nChar)) >= 0)
                {
                    const int newNext = FindNextChar(m_CurrentChar + 1, false, true);
                    SetSel(m_CurrentChar, m_CurrentChar + 1);
                    ReplaceSel(CString(char(nChar)));

                    if (newNext >= 0)
                        m_CurrentChar = newNext;
                    else
                        ++m_CurrentChar;

                    SetSel(m_CurrentChar, m_CurrentChar);
                }

            break;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_MaskEditBase::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    switch (nChar)
    {
        case VK_TAB:
        {
            CWnd* pNextItem = ((CWnd*)GetParent())->GetNextDlgTabItem(this, m_ShiftDown);

            if (!pNextItem)
                break;

            PSS_MaskEditBase* pEdit = dynamic_cast<PSS_MaskEditBase*>(pNextItem);

            if (pEdit)
                pEdit->m_ShiftDown = m_ShiftDown;

            pNextItem->SetFocus();
            break;
        }

        case VK_SHIFT:
            m_ShiftDown = true;
            break;

        case VK_LEFT:
        {
            const int next = FindNextChar(m_CurrentChar - 1, false, false);

            if (next >= 0)
            {
                m_CurrentChar = next;
                SetSel(m_CurrentChar, m_CurrentChar);
            }

            break;
        }
    
        case VK_RIGHT:
        {
            const int next = FindNextChar(m_CurrentChar + 1, false, true);

            if (next >= 0)
                m_CurrentChar = next;
            else
                m_CurrentChar = FindNextChar(m_NumChars - 1, false, false) + 1;

            SetSel(m_CurrentChar, m_CurrentChar);
            break;
        }

        case VK_HOME:
            if (m_ShiftDown)
                SetSel(0, m_CurrentChar);
            else
            {
                m_CurrentChar = FindNextChar(0, false, true);
                SetSel(m_CurrentChar, m_CurrentChar);
            }

            break;

        case VK_END:
            if (m_ShiftDown)
            {
                const int last = FindNextChar(m_NumChars - 1, false, false) + 1;
                SetSel(m_CurrentChar, last);
            }
            else
            {
                m_CurrentChar = FindNextChar(m_NumChars - 1, false, false) + 1;
                SetSel(m_CurrentChar, m_CurrentChar);
            }

            break;

        case VK_INSERT:
            break;

        case VK_DELETE:
        {
            int x, y, z;
            GetSel(x, y);

            if (x != y)
            {
                CString replaceText = "";

                for (z = x; z < y; ++z)
                    if (m_Char[z]->m_StaticChar)
                        replaceText += m_Char[z]->m_Data;
                    else
                        replaceText += m_Prompt;

                ReplaceSel(replaceText);
                m_CurrentChar = FindNextChar(x, false, true);
                SetSel(m_CurrentChar, m_CurrentChar);
            }
            else
            if (m_CurrentChar <= FindNextChar(m_NumChars - 1, false, false))
            {
                SetSel(m_CurrentChar, m_CurrentChar + 1);
                ReplaceSel(m_Prompt);
                
                const int next = FindNextChar(m_CurrentChar + 1, false, true);

                if (next >= 0)
                    m_CurrentChar = next;
                else
                    ++m_CurrentChar;

                SetSel(m_CurrentChar, m_CurrentChar);
            }

            break;
        }

        default:
            break;
    }
}
//---------------------------------------------------------------------------
void PSS_MaskEditBase::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar)
    {
        case VK_SHIFT: m_ShiftDown = false; break;
        default:                            break;
    }

    CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_MaskEditBase::OnLButtonUp(UINT nFlags, CPoint point) 
{
    int x, y;
    GetSel(x, y);

    if (x == y)
    {
        m_CurrentChar = x;
        SetSel(m_CurrentChar, m_CurrentChar);
    }

    CEdit::OnLButtonUp(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_MaskEditBase::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    SetSel(0, -1);
}
//---------------------------------------------------------------------------
void PSS_MaskEditBase::OnSetFocus(CWnd* pOldWnd)
{
    CEdit::OnSetFocus(pOldWnd);

    SetSel(0, -1);
}
//---------------------------------------------------------------------------
