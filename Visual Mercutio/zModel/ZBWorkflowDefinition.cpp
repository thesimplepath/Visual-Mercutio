// ZBWorkflowDefinition.cpp: implementation of the ZBWorkflowDefinition class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBWorkflowDefinition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(ZBWorkflowDefinition, CObject, def_Version)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBWorkflowDefinition::ZBWorkflowDefinition()
:	m_CheckConsistency(true),
	m_SaveModelInWorkflow(true)
{

}

ZBWorkflowDefinition::~ZBWorkflowDefinition()
{

}

ZBWorkflowDefinition::ZBWorkflowDefinition(const ZBWorkflowDefinition& src)
{
	*this = src;
}

ZBWorkflowDefinition& ZBWorkflowDefinition::operator=(const ZBWorkflowDefinition& src)
{
	m_WorkflowFilename = src.m_WorkflowFilename;
	m_WorkflowLastUpdateDate = src.m_WorkflowLastUpdateDate;
	m_CheckConsistency = src.m_CheckConsistency;
	m_SaveModelInWorkflow = src.m_SaveModelInWorkflow;
	return *this;
}

ZBWorkflowDefinition* ZBWorkflowDefinition::Clone()
{
	return (new ZBWorkflowDefinition(*this));
}



// Serializes the unit
void ZBWorkflowDefinition::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_WorkflowFilename;
		ar << m_WorkflowLastUpdateDate;
		ar << (WORD)m_CheckConsistency;
		ar << (WORD)m_SaveModelInWorkflow;
	}
	else
	{
		ar >> m_WorkflowFilename;
		ar >> m_WorkflowLastUpdateDate;

		WORD	wValue;
		ar >> wValue;
		m_CheckConsistency = (bool)wValue;

		ar >> wValue;
		m_SaveModelInWorkflow = (bool)wValue;
	}
}
