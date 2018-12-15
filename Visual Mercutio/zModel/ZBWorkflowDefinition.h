// ZBWorkflowDefinition.h: interface for the ZBWorkflowDefinition class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBWORKFLOWDEFINITION_H__CEAF3A15_5BDA_4083_A524_CC2A20C65C65__INCLUDED_)
#define AFX_ZBWORKFLOWDEFINITION_H__CEAF3A15_5BDA_4083_A524_CC2A20C65C65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\ZBDate.h"


#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZBWorkflowDefinition : public CObject  
{
    DECLARE_SERIAL(ZBWorkflowDefinition)
public:
    ZBWorkflowDefinition();
    virtual ~ZBWorkflowDefinition();

    // Copy constructor
    ZBWorkflowDefinition(const ZBWorkflowDefinition& right);
    // Assignment operator
    ZBWorkflowDefinition& operator=(const ZBWorkflowDefinition& right);

    ZBWorkflowDefinition*    Clone();


    CString        GetWorkflowFilename() const { return m_WorkflowFilename; };
    void        ClearWorkflowFilename();
    void        SetWorkflowFilename( CString value ) { m_WorkflowFilename = value; };

    ZBDate&        GetWorkflowLastUpdateDate() { return m_WorkflowLastUpdateDate; };
    void        SetWorkflowLastUpdateDate( ZBDate value ) { m_WorkflowLastUpdateDate = value; };

    bool        GetCheckConsistency() const { return m_CheckConsistency; };
    void        SetCheckConsistency( bool value ) { m_CheckConsistency = value; };

    bool        GetSaveModelInWorkflow() const { return m_SaveModelInWorkflow; };
    void        SetSaveModelInWorkflow( bool value ) { m_SaveModelInWorkflow = value; };


    // Serializes the unit
    virtual void Serialize(CArchive& ar);

private:
    CString            m_WorkflowFilename;
    ZBDate            m_WorkflowLastUpdateDate;
    bool            m_CheckConsistency;
    bool            m_SaveModelInWorkflow;

};

inline void    ZBWorkflowDefinition::ClearWorkflowFilename()
{
    m_WorkflowFilename.Empty();
}

#endif // !defined(AFX_ZBWORKFLOWDEFINITION_H__CEAF3A15_5BDA_4083_A524_CC2A20C65C65__INCLUDED_)
