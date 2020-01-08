/****************************************************************************
 * ==> PSS_WorkflowDefinition ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a workflow definition                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WorkflowDefinition.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_WorkflowDefinition, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_WorkflowDefinition
//---------------------------------------------------------------------------
PSS_WorkflowDefinition::PSS_WorkflowDefinition() :
    m_CheckConsistency(true),
    m_SaveModelInWorkflow(true)
{}
//---------------------------------------------------------------------------
PSS_WorkflowDefinition::PSS_WorkflowDefinition(const PSS_WorkflowDefinition& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_WorkflowDefinition::~PSS_WorkflowDefinition()
{}
//---------------------------------------------------------------------------
PSS_WorkflowDefinition& PSS_WorkflowDefinition::operator = (const PSS_WorkflowDefinition& other)
{
    m_WorkflowFileName       = other.m_WorkflowFileName;
    m_WorkflowLastUpdateDate = other.m_WorkflowLastUpdateDate;
    m_CheckConsistency       = other.m_CheckConsistency;
    m_SaveModelInWorkflow    = other.m_SaveModelInWorkflow;
    return *this;
}
//---------------------------------------------------------------------------
PSS_WorkflowDefinition* PSS_WorkflowDefinition::Clone() const
{
    return new PSS_WorkflowDefinition(*this);
}
//---------------------------------------------------------------------------
void PSS_WorkflowDefinition::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        ar << m_WorkflowFileName;
        ar << m_WorkflowLastUpdateDate;
        ar << WORD(m_CheckConsistency);
        ar << WORD(m_SaveModelInWorkflow);
    }
    else
    {
        ar >> m_WorkflowFileName;
        ar >> m_WorkflowLastUpdateDate;

        WORD wValue;
        ar >> wValue;
        m_CheckConsistency = bool(wValue);

        ar >> wValue;
        m_SaveModelInWorkflow = bool(wValue);
    }
}
//---------------------------------------------------------------------------
