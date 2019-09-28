/****************************************************************************
 * ==> PSS_Observer --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic observer                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_Observer.h"

// processsoft
#include "PSS_Subject.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_Observer
//---------------------------------------------------------------------------
PSS_Observer::PSS_Observer()
{}
//---------------------------------------------------------------------------
PSS_Observer::~PSS_Observer()
{
    // get the subject count
    const std::size_t subjectCount = m_Subjects.size();

    // iterate through subjects
    for (std::size_t i = 0; i < subjectCount; ++i)
        m_Subjects[i]->DetachObserver(this);
}
//---------------------------------------------------------------------------
void PSS_Observer::OnSubjectAttaching(PSS_Subject* pSubject)
{
    // get the subject count
    const std::size_t subjectCount = m_Subjects.size();

    // iterate through subjects
    for (std::size_t i = 0; i < subjectCount; ++i)
        // is subject already registered?
        if (m_Subjects[i] == pSubject)
            return;

    // attach the subject to this observer
    m_Subjects.push_back(pSubject);
}
//---------------------------------------------------------------------------
void PSS_Observer::OnSubjectDetaching(PSS_Subject* pSubject)
{
    // get the subject count
    const std::size_t subjectCount = m_Subjects.size();

    // iterate through subjects
    for (std::size_t i = 0; i < subjectCount; ++i)
        // found subject to remove?
        if (m_Subjects[i] == pSubject)
        {
            // remove it
            m_Subjects.erase(m_Subjects.begin() + i);
            return;
        }
}
//---------------------------------------------------------------------------
