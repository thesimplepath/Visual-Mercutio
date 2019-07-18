/****************************************************************************
 * ==> PSS_ActivityCombo ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity combo box                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityCombo.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ActivityCombo
//---------------------------------------------------------------------------
PSS_ActivityCombo::PSS_ActivityCombo(ZProcess*      pProcess,
                                     int            activityType,
                                     const CString& excludedActivity,
                                     BOOL           stopOnFound,
                                     BOOL           attributedActivityOnly) :
    m_pProcess(pProcess),
    m_ExcludedActivity(excludedActivity),
    m_ActivityType(activityType),
    m_StopOnFound(stopOnFound),
    m_AttributedActivityOnly(attributedActivityOnly)
{}
//---------------------------------------------------------------------------
PSS_ActivityCombo::PSS_ActivityCombo(const PSS_ActivityCombo& other)
{
    THROW("Copy constructor is prohibited for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityCombo::~PSS_ActivityCombo()
{}
//---------------------------------------------------------------------------
const PSS_ActivityCombo& PSS_ActivityCombo::operator = (const PSS_ActivityCombo& other)
{
    THROW("Copy operator is prohibited for this class");
}
//---------------------------------------------------------------------------
int PSS_ActivityCombo::Initialize(ZProcess*      pProcess,
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
CString PSS_ActivityCombo::GetSelectedActivity()
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
void PSS_ActivityCombo::SelectActivity(const CString& activityName)
{
    const int index = FindString(-1, activityName);

    if (index != CB_ERR)
        SetCurSel(index);
}
//---------------------------------------------------------------------------
int PSS_ActivityCombo::Refresh()
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
