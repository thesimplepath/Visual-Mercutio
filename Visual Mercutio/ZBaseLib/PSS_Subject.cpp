/****************************************************************************
 * ==> PSS_Subject ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic subject                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_Subject.h"

// processsoft
#include "PSS_Observer.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_Subject
//---------------------------------------------------------------------------
PSS_Subject::PSS_Subject()
{}
//---------------------------------------------------------------------------
PSS_Subject::~PSS_Subject()
{
    // NOTE fully qualified name is used here to avoid to call a pure virtual function accidentally during the destruction
    PSS_Subject::DetachAllObservers();
}
//---------------------------------------------------------------------------
void PSS_Subject::AttachObserver(PSS_Observer* pObserver)
{
    if (!pObserver)
        return;

    // get observer count
    const register int observerCount = m_Observers.size();

    // iterate through registered observers
    for (register int i = 0; i < observerCount; ++i)
        // is observer already registered?
        if (m_Observers[i] == pObserver)
            return;

    // add observer only if still not registered
    m_Observers.push_back(pObserver);
}
//---------------------------------------------------------------------------
void PSS_Subject::DetachObserver(PSS_Observer* pObserver)
{
    if (!pObserver)
        return;

    // get observer count
    const register int observerCount = m_Observers.size();

    // iterate through registered observers
    for (register int i = 0; i < observerCount; ++i)
        // found observer to detach?
        if (m_Observers[i] == pObserver)
        {
            // detach it
            m_Observers.erase(m_Observers.begin() + i);
            return;
        }
}
//---------------------------------------------------------------------------
void PSS_Subject::DetachAllObservers()
{
    // iterate through registered observers and detach each of them
    while (m_Observers.size())
        m_Observers.erase(m_Observers.begin());
}
//---------------------------------------------------------------------------
void PSS_Subject::NotifyAllObservers(PSS_ObserverMsg* pMsg)
{
    // get observer count
    const register int observerCount = m_Observers.size();

    // iterate through registered observers and notify each of them about the message
    for (register int i = 0; i < observerCount; ++i)
    {
        // get the current observer
        PSS_Observer* pObserver = static_cast<PSS_Observer*>(m_Observers[i]);

        if (!pObserver)
            continue;
 
        pObserver->OnUpdate(this, pMsg);
    }
}
//---------------------------------------------------------------------------
