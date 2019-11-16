/****************************************************************************
 * ==> PSS_ProcessIterator -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a process iterator                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ProcessIterator.h"

// processsoft
#include "PSS_Process.h"
#include "PSS_Activity.h"

//---------------------------------------------------------------------------
// PSS_ProcessIterator
//---------------------------------------------------------------------------
PSS_ProcessIterator::PSS_ProcessIterator(PSS_Process* pProcess) :
    m_IteratorActivityPointer(NULL),
    m_pProcess(pProcess)
{}
//---------------------------------------------------------------------------
PSS_ProcessIterator::PSS_ProcessIterator(const PSS_ProcessIterator& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ProcessIterator::~PSS_ProcessIterator()
{}
//---------------------------------------------------------------------------
const PSS_ProcessIterator& PSS_ProcessIterator::operator = (const PSS_ProcessIterator& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_ProcessIterator::GetFirstBaseActivity()
{
    if (!m_pProcess)
        return NULL;

    m_IteratorActivityPointer = m_pProcess->GetFirstBaseActivity();

    return m_IteratorActivityPointer;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_ProcessIterator::GetFirstValidActivity()
{
    if (!m_pProcess)
        return NULL;

    m_IteratorActivityPointer = m_pProcess->GetFirstValidActivity();

    return m_IteratorActivityPointer;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_ProcessIterator::GetFirstValidBaseActivity()
{
    if (!m_pProcess)
        return NULL;

    m_IteratorActivityPointer = m_pProcess->GetFirstValidBaseActivity();

    return m_IteratorActivityPointer;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_ProcessIterator::GetLastBaseActivity()
{
    if (!m_pProcess || !m_pProcess->GetFirstValidActivity())
        return NULL;

    m_IteratorActivityPointer = m_pProcess->GetFirstBaseActivity();

    while (m_IteratorActivityPointer->GetNextBaseActivity())
        m_IteratorActivityPointer = m_IteratorActivityPointer->GetNextBaseActivity();

    return m_IteratorActivityPointer;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_ProcessIterator::GetLastValidActivity()
{
    if (!m_pProcess || !m_pProcess->GetFirstValidActivity())
        return NULL;

    m_IteratorActivityPointer = m_pProcess->GetFirstValidActivity();

    while (m_IteratorActivityPointer->GetNextValidActivity())
        m_IteratorActivityPointer = m_IteratorActivityPointer->GetNextValidActivity();

    return m_IteratorActivityPointer;
}
//---------------------------------------------------------------------------
PSS_Activity* PSS_ProcessIterator::GetLastActivityWithinProcess()
{
    if (!m_pProcess || !m_pProcess->GetFirstValidActivity())
        return NULL;

    m_IteratorActivityPointer = m_pProcess->GetFirstValidActivity();

    while (m_IteratorActivityPointer->GetNextBaseActivity() && m_IteratorActivityPointer->GetNextBaseActivity()->IsKindOf(RUNTIME_CLASS(PSS_Activity)))
        m_IteratorActivityPointer = m_IteratorActivityPointer->GetNextBaseActivity();

    return static_cast<PSS_Activity*>(m_IteratorActivityPointer);
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_ProcessIterator::GetParent(PSS_BaseActivity* pActivity)
{
    if (!pActivity)
        return NULL;

    m_IteratorActivityPointer = pActivity->GetParent();

    return m_IteratorActivityPointer;
}
//---------------------------------------------------------------------------
PSS_Process* PSS_ProcessIterator::GetParentProcess(PSS_BaseActivity* pActivity)
{
    if (!pActivity)
        return NULL;

    m_IteratorActivityPointer = pActivity->GetParentProcess();

    return static_cast<PSS_Process*>(m_IteratorActivityPointer);
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_ProcessIterator::GetPreviousValidActivity()
{
    if (!m_IteratorActivityPointer)
        return NULL;

    m_IteratorActivityPointer = m_IteratorActivityPointer->GetPreviousValidActivity();

    return static_cast<PSS_Activity*>(m_IteratorActivityPointer);
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_ProcessIterator::GetPreviousBaseActivity()
{
    if (!m_IteratorActivityPointer)
        return NULL;

    m_IteratorActivityPointer = m_IteratorActivityPointer->GetPreviousBaseActivity();

    return m_IteratorActivityPointer;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_ProcessIterator::GetPreviousValidBaseActivity()
{
    if (!m_IteratorActivityPointer)
        return NULL;

    m_IteratorActivityPointer = m_IteratorActivityPointer->GetPreviousValidBaseActivity();

    return m_IteratorActivityPointer;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_ProcessIterator::GetNextValidActivity()
{
    if (!m_IteratorActivityPointer)
        return NULL;

    m_IteratorActivityPointer = m_IteratorActivityPointer->GetNextValidActivity();

    return static_cast<PSS_Activity*>(m_IteratorActivityPointer);
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_ProcessIterator::GetNextBaseActivity()
{
    if (!m_IteratorActivityPointer)
        return NULL;

    m_IteratorActivityPointer = m_IteratorActivityPointer->GetNextBaseActivity();

    return m_IteratorActivityPointer;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_ProcessIterator::GetNextValidBaseActivity()
{
    if (!m_IteratorActivityPointer)
        return NULL;

    m_IteratorActivityPointer = m_IteratorActivityPointer->GetNextValidBaseActivity();

    return m_IteratorActivityPointer;
}
//---------------------------------------------------------------------------
PSS_Process* PSS_ProcessIterator::GetPreviousProcess()
{
    if (!m_IteratorActivityPointer)
        return NULL;

    m_IteratorActivityPointer = m_IteratorActivityPointer->GetPreviousProcess();

    return static_cast<PSS_Process*>(m_IteratorActivityPointer);
}
//---------------------------------------------------------------------------
PSS_Process* PSS_ProcessIterator::GetNextProcess()
{
    if (!m_IteratorActivityPointer)
        return NULL;

    m_IteratorActivityPointer = m_IteratorActivityPointer->GetNextProcess();

    return static_cast<PSS_Process*>(m_IteratorActivityPointer);
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_ProcessIterator::StartIterator(PSS_BaseActivity* pActivity, PSS_Process* pProcess)
{
    if (pProcess)
        m_pProcess = pProcess;

    if (!m_pProcess)
        return NULL;

    // set the iterator activity
    m_IteratorActivityPointer = (!pActivity ? GetFirstValidActivity() : pActivity);

    return m_IteratorActivityPointer;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_ProcessIterator::StartIterator(const CString& activityName, PSS_Process* pProcess)
{
    if (pProcess)
        m_pProcess = pProcess;

    if (!m_pProcess)
        return NULL;

    // find the activity name to set the right iterator activity
    m_IteratorActivityPointer = FindActivity(activityName);

    return m_IteratorActivityPointer;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_ProcessIterator::FindActivity(const CString& activityName)
{
    if (!m_pProcess)
        return NULL;

    m_IteratorActivityPointer = m_pProcess->FindActivity(activityName);

    return m_IteratorActivityPointer;
}
//---------------------------------------------------------------------------
