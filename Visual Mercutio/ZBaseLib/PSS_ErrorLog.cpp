/****************************************************************************
 * ==> PSS_ErrorLog --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an error log                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ErrorLog.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ErrorLog
//---------------------------------------------------------------------------
PSS_ErrorLog::PSS_ErrorLog() :
    m_CurrentSelection(-1)
{}
//---------------------------------------------------------------------------
PSS_ErrorLog::~PSS_ErrorLog()
{}
//---------------------------------------------------------------------------
bool PSS_ErrorLog::InitializeLog()
{
    // do nothing
    return true;
}
//---------------------------------------------------------------------------
void PSS_ErrorLog::ClearLog()
{
    m_LogArray.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_ErrorLog::AddLine(const CString& line)
{
    m_LogArray.Add(line);
}
//---------------------------------------------------------------------------
std::size_t PSS_ErrorLog::GetCount() const
{
    return m_LogArray.GetSize();
}
//---------------------------------------------------------------------------
CString PSS_ErrorLog::GetLineAt(std::size_t index) const
{
    return m_LogArray.GetAt(index);
}
//---------------------------------------------------------------------------
int PSS_ErrorLog::GetCurrentSelection() const
{
    return m_CurrentSelection;
}
//---------------------------------------------------------------------------
void PSS_ErrorLog::SetCurrentSelection(std::size_t index)
{
    m_CurrentSelection = index;
}
//---------------------------------------------------------------------------
void PSS_ErrorLog::ClearCurrentSelection()
{
    m_CurrentSelection = -1;
}
//---------------------------------------------------------------------------
int PSS_ErrorLog::GetCurrentItem(CString& s) const
{
    int i = GetCurrentSelection();

    if (i != LB_ERR)
        s = GetLineAt(i);

    return i;
}
//---------------------------------------------------------------------------
bool PSS_ErrorLog::SelectLast() const
{
    return false;
}
//---------------------------------------------------------------------------
void PSS_ErrorLog::SetSelectLast(bool value)
{
    // do nothing
}
//---------------------------------------------------------------------------
