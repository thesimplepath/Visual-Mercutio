/****************************************************************************
 * ==> PSS_ActivityComboBox ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity combo box                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityComboBox.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ActivityComboBox
//---------------------------------------------------------------------------
PSS_ActivityComboBox::PSS_ActivityComboBox(ZProcess*      pProcess,
                                           int            activityType,
                                           const CString& excludedActivity,
                                           BOOL           stopOnFound,
                                           BOOL           attributedActivityOnly) :
    #ifdef _WIN32
        // 32 bit version
        CCJFlatComboBox(),
    #else
        // 16 bit version
        CComboBox(),
    #endif
    m_pProcess(pProcess),
    m_ExcludedActivity(excludedActivity),
    m_ActivityType(activityType),
    m_StopOnFound(stopOnFound),
    m_AttributedActivityOnly(attributedActivityOnly)
{}
//---------------------------------------------------------------------------
PSS_ActivityComboBox::PSS_ActivityComboBox(const PSS_ActivityComboBox& other)
{
    THROW("Copy constructor is prohibited for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityComboBox::~PSS_ActivityComboBox()
{}
//---------------------------------------------------------------------------
const PSS_ActivityComboBox& PSS_ActivityComboBox::operator = (const PSS_ActivityComboBox& other)
{
    THROW("Copy operator is prohibited for this class");
}
//---------------------------------------------------------------------------
int PSS_ActivityComboBox::Initialize(ZProcess*      pProcess,
                                     int            activityType,
                                     const CString& excludedActivity,
                                     BOOL           stopOnFound,
                                     BOOL           attributedActivityOnly)
{
    m_pProcess               = pProcess;
    m_ActivityType           = activityType;
    m_ExcludedActivity       = excludedActivity;
    m_StopOnFound            = stopOnFound;
    m_AttributedActivityOnly = attributedActivityOnly;

    return Refresh();
}
//---------------------------------------------------------------------------
CString PSS_ActivityComboBox::GetSelectedActivity()
{
    const int index = GetCurSel();

    if (index != CB_ERR)
    {
        CString text;
        GetLBText(index, text);
        return text;
    }

    return "";
}
//---------------------------------------------------------------------------
void PSS_ActivityComboBox::SelectActivity(const CString& activityName)
{
    const int index = FindString(-1, activityName);

    if (index != CB_ERR)
        SetCurSel(index);
}
//---------------------------------------------------------------------------
int PSS_ActivityComboBox::Refresh()
{
    CStringArray activityArray;

    ResetContent();

    const int count = m_pProcess->GetActivityNameArray(activityArray,
                                                       m_ActivityType,
                                                       m_ExcludedActivity,
                                                       m_StopOnFound,
                                                       m_AttributedActivityOnly);

    for (register std::size_t index = 0; index < std::size_t(count); ++index)
        AddString(activityArray[index]);

    return count;
}
//---------------------------------------------------------------------------
