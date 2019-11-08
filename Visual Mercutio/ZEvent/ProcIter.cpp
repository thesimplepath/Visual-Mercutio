//## begin module%379033CE027E.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%379033CE027E.cm

//## begin module%379033CE027E.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%379033CE027E.cp

//## Module: ProcIter%379033CE027E; Package body
//## Subsystem: ZEvent%378A5F7E02DB
//## Source file: z:\adsoft~1\ZEvent\ProcIter.cpp

//## begin module%379033CE027E.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%379033CE027E.additionalIncludes

//## begin module%379033CE027E.includes preserve=yes
//## end module%379033CE027E.includes

// ProcIter
#include "ProcIter.h"
//## begin module%379033CE027E.declarations preserve=no
//## end module%379033CE027E.declarations

//## begin module%379033CE027E.additionalDeclarations preserve=yes
#include "ZProcess.h"
#include "PSS_Activity.h"
//## end module%379033CE027E.additionalDeclarations


// Class ZProcessIterator 



ZProcessIterator::ZProcessIterator (ZProcess* pProcess)
  //## begin ZProcessIterator::ZProcessIterator%932194635.hasinit preserve=no
      : m_IteratorActivityPointer(NULL)
  //## end ZProcessIterator::ZProcessIterator%932194635.hasinit
  //## begin ZProcessIterator::ZProcessIterator%932194635.initialization preserve=yes
  , m_pProcess(pProcess)
  //## end ZProcessIterator::ZProcessIterator%932194635.initialization
{
  //## begin ZProcessIterator::ZProcessIterator%932194635.body preserve=yes
  //## end ZProcessIterator::ZProcessIterator%932194635.body
}


ZProcessIterator::~ZProcessIterator()
{
  //## begin ZProcessIterator::~ZProcessIterator%.body preserve=yes
  //## end ZProcessIterator::~ZProcessIterator%.body
}



//## Other Operations (implementation)
ZBaseActivity* ZProcessIterator::GetFirstBaseActivity ()
{
  //## begin ZProcessIterator::GetFirstBaseActivity%932194644.body preserve=yes
    if (!m_pProcess)
        return NULL;
    m_IteratorActivityPointer = m_pProcess->GetFirstBaseActivity();
    return m_IteratorActivityPointer;
  //## end ZProcessIterator::GetFirstBaseActivity%932194644.body
}

ZBaseActivity* ZProcessIterator::GetLastBaseActivity ()
{
  //## begin ZProcessIterator::GetLastBaseActivity%932278212.body preserve=yes
    if (!m_pProcess && !m_pProcess->GetFirstValidActivity())
        return NULL;
    m_IteratorActivityPointer = m_pProcess->GetFirstBaseActivity();
    while (m_IteratorActivityPointer->GetNextBaseActivity())
        m_IteratorActivityPointer = m_IteratorActivityPointer->GetNextBaseActivity();
    return m_IteratorActivityPointer;
  //## end ZProcessIterator::GetLastBaseActivity%932278212.body
}

ZBaseActivity* ZProcessIterator::GetFirstValidActivity ()
{
  //## begin ZProcessIterator::GetFirstValidActivity%932314503.body preserve=yes
    if (!m_pProcess)
        return NULL;
    m_IteratorActivityPointer = m_pProcess->GetFirstValidActivity();
    return m_IteratorActivityPointer;
  //## end ZProcessIterator::GetFirstValidActivity%932314503.body
}

ZBaseActivity* ZProcessIterator::GetFirstValidBaseActivity ()
{
  //## begin ZProcessIterator::GetFirstValidBaseActivity%937152025.body preserve=yes
    if (!m_pProcess)
        return NULL;
    m_IteratorActivityPointer = m_pProcess->GetFirstValidBaseActivity();
    return m_IteratorActivityPointer;
  //## end ZProcessIterator::GetFirstValidBaseActivity%937152025.body
}

ZBaseActivity* ZProcessIterator::GetLastValidActivity ()
{
  //## begin ZProcessIterator::GetLastValidActivity%932314504.body preserve=yes
    if (!m_pProcess && !m_pProcess->GetFirstValidActivity())
        return NULL;
    m_IteratorActivityPointer = m_pProcess->GetFirstValidActivity();
    while (m_IteratorActivityPointer->GetNextValidActivity())
        m_IteratorActivityPointer = m_IteratorActivityPointer->GetNextValidActivity();
    return m_IteratorActivityPointer;
  //## end ZProcessIterator::GetLastValidActivity%932314504.body
}

PSS_Activity* ZProcessIterator::GetLastActivityWithinProcess ()
{
  //## begin ZProcessIterator::GetLastActivityWithinProcess%932314505.body preserve=yes
    if (!m_pProcess && !m_pProcess->GetFirstValidActivity())
        return NULL;
    m_IteratorActivityPointer = m_pProcess->GetFirstValidActivity();
    while (m_IteratorActivityPointer->GetNextBaseActivity() && m_IteratorActivityPointer->GetNextBaseActivity()->IsKindOf(RUNTIME_CLASS(PSS_Activity)))
        m_IteratorActivityPointer = m_IteratorActivityPointer->GetNextBaseActivity();
    return (PSS_Activity*)m_IteratorActivityPointer;
  //## end ZProcessIterator::GetLastActivityWithinProcess%932314505.body
}

ZBaseActivity* ZProcessIterator::GetParent (ZBaseActivity* pActivity)
{
  //## begin ZProcessIterator::GetParent%932278211.body preserve=yes
    if (!pActivity)
        return NULL;
    m_IteratorActivityPointer = pActivity->GetParent();
    return m_IteratorActivityPointer;
  //## end ZProcessIterator::GetParent%932278211.body
}

ZProcess* ZProcessIterator::GetParentProcess (ZBaseActivity* pActivity)
{
  //## begin ZProcessIterator::GetParent%932278211.body preserve=yes
    if (!pActivity)
        return NULL;
    m_IteratorActivityPointer = pActivity->GetParentProcess();
    return (ZProcess*)m_IteratorActivityPointer;
  //## end ZProcessIterator::GetParent%932278211.body
}

ZBaseActivity* ZProcessIterator::GetNextValidActivity ()
{
  //## begin ZProcessIterator::GetNextValidActivity%932194636.body preserve=yes
    if (!m_IteratorActivityPointer)
        return NULL;
    m_IteratorActivityPointer = m_IteratorActivityPointer->GetNextValidActivity();
    return (PSS_Activity*)m_IteratorActivityPointer;
  //## end ZProcessIterator::GetNextValidActivity%932194636.body
}

ZBaseActivity* ZProcessIterator::GetPreviousValidActivity ()
{
  //## begin ZProcessIterator::GetPreviousValidActivity%932194637.body preserve=yes
    if (!m_IteratorActivityPointer)
        return NULL;
    m_IteratorActivityPointer = m_IteratorActivityPointer->GetPreviousValidActivity();
    return (PSS_Activity*)m_IteratorActivityPointer;
  //## end ZProcessIterator::GetPreviousValidActivity%932194637.body
}

ZBaseActivity* ZProcessIterator::GetNextBaseActivity ()
{
  //## begin ZProcessIterator::GetNextBaseActivity%933094114.body preserve=yes
    if (!m_IteratorActivityPointer)
        return NULL;
    m_IteratorActivityPointer = m_IteratorActivityPointer->GetNextBaseActivity();
    return m_IteratorActivityPointer;
  //## end ZProcessIterator::GetNextBaseActivity%933094114.body
}

ZBaseActivity* ZProcessIterator::GetNextValidBaseActivity ()
{
  //## begin ZProcessIterator::GetNextValidBaseActivity%937152026.body preserve=yes
    if (!m_IteratorActivityPointer)
        return NULL;
    m_IteratorActivityPointer = m_IteratorActivityPointer->GetNextValidBaseActivity();
    return m_IteratorActivityPointer;
  //## end ZProcessIterator::GetNextValidBaseActivity%937152026.body
}

ZBaseActivity* ZProcessIterator::GetPreviousBaseActivity ()
{
  //## begin ZProcessIterator::GetPreviousBaseActivity%933094115.body preserve=yes
    if (!m_IteratorActivityPointer)
        return NULL;
    m_IteratorActivityPointer = m_IteratorActivityPointer->GetPreviousBaseActivity();
    return m_IteratorActivityPointer;
  //## end ZProcessIterator::GetPreviousBaseActivity%933094115.body
}

ZBaseActivity* ZProcessIterator::GetPreviousValidBaseActivity ()
{
  //## begin ZProcessIterator::GetPreviousValidBaseActivity%937152027.body preserve=yes
    if (!m_IteratorActivityPointer)
        return NULL;
    m_IteratorActivityPointer = m_IteratorActivityPointer->GetPreviousValidBaseActivity();
    return m_IteratorActivityPointer;
  //## end ZProcessIterator::GetPreviousValidBaseActivity%937152027.body
}

ZProcess* ZProcessIterator::GetNextProcess ()
{
  //## begin ZProcessIterator::GetNextProcess%932194638.body preserve=yes
    if (!m_IteratorActivityPointer)
        return NULL;
    m_IteratorActivityPointer = m_IteratorActivityPointer->GetNextProcess();
    return (ZProcess*)m_IteratorActivityPointer;
  //## end ZProcessIterator::GetNextProcess%932194638.body
}

ZProcess* ZProcessIterator::GetPreviousProcess ()
{
  //## begin ZProcessIterator::GetPreviousProcess%932194639.body preserve=yes
    if (!m_IteratorActivityPointer)
        return NULL;
    m_IteratorActivityPointer = m_IteratorActivityPointer->GetPreviousProcess();
    return (ZProcess*)m_IteratorActivityPointer;
  //## end ZProcessIterator::GetPreviousProcess%932194639.body
}

ZBaseActivity* ZProcessIterator::StartIterator (ZBaseActivity* pActivity, ZProcess* pProcess)
{
  //## begin ZProcessIterator::StartIterator%932194640.body preserve=yes
    if (pProcess)
        m_pProcess = pProcess;
    
    if (!m_pProcess)
        return NULL;
    // Sets the iterator activity pointer
    m_IteratorActivityPointer = (!pActivity) ? GetFirstValidActivity() : pActivity;
    return m_IteratorActivityPointer;
  //## end ZProcessIterator::StartIterator%932194640.body
}

ZBaseActivity* ZProcessIterator::StartIterator (const CString& ActivityName, ZProcess* pProcess)
{
  //## begin ZProcessIterator::StartIterator%932194641.body preserve=yes
    if (pProcess)
        m_pProcess = pProcess;

    if (!m_pProcess)
        return NULL;
    // Find the activity name to set the right iterator activity index
    m_IteratorActivityPointer = FindActivity( ActivityName );
    return m_IteratorActivityPointer;
  //## end ZProcessIterator::StartIterator%932194641.body
}

ZBaseActivity* ZProcessIterator::FindActivity (const CString& ActivityName)
{
  //## begin ZProcessIterator::FindActivity%932194643.body preserve=yes
    if (!m_pProcess)
        return NULL;

    m_IteratorActivityPointer = m_pProcess->FindActivity( ActivityName );
    return m_IteratorActivityPointer;
  //## end ZProcessIterator::FindActivity%932194643.body
}

// Additional Declarations
  //## begin ZProcessIterator%379031B90231.declarations preserve=yes
  //## end ZProcessIterator%379031B90231.declarations

//## begin module%379033CE027E.epilog preserve=yes
//## end module%379033CE027E.epilog
