/****************************************************************************
 * ==> PSS_WorkflowDefinition ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a workflow definition                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkflowDefinitionH
#define PSS_WorkflowDefinitionH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_WorkflowDefinition
    #define PSS_WorkflowDefinition ZBWorkflowDefinition
#endif

// processsoft
#include "zBaseLib\PSS_Date.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Workflow definition
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WorkflowDefinition : public CObject
{
    DECLARE_SERIAL(PSS_WorkflowDefinition)

    public:
        PSS_WorkflowDefinition();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_WorkflowDefinition(const PSS_WorkflowDefinition& other);

        virtual ~PSS_WorkflowDefinition();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_WorkflowDefinition& operator = (const PSS_WorkflowDefinition& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_WorkflowDefinition* Clone() const;

        /**
        * Gets the workflow file name
        *@return the workflow file name
        */
        virtual inline CString GetWorkflowFileName() const;

        /**
        * Clears the workflow file name
        */
        virtual inline void ClearWorkflowFileName();

        /**
        * Sets the workflow file name
        *@param value - the workflow file name
        */
        virtual inline void SetWorkflowFileName(const CString& value);

        /**
        * Gets the workflow last update date
        *@return the workflow last update date
        */
        virtual inline PSS_Date& GetWorkflowLastUpdateDate();

        /**
        * Sets the workflow last update date
        *@param value - the workflow last update date
        */
        virtual inline void SetWorkflowLastUpdateDate(const PSS_Date& value);

        /**
        * Gets if the consistency should be checked
        *@return true if the consistency should be checked, otherwise false
        */
        virtual inline bool GetCheckConsistency() const;

        /**
        * Sets if the consistency should be checked
        *@param value - if true, the consistency should be checked
        */
        virtual inline void SetCheckConsistency(bool value);

        /**
        * Gets if save in workflow mode is enabled
        *@return true if save in workflow mode is enabled, otherwise false
        */
        virtual inline bool GetSaveModelInWorkflow() const;

        /**
        * Sets if save in workflow mode is enabled
        *@param value - if true, the save in workflow mode is enabled
        */
        virtual inline void SetSaveModelInWorkflow(bool value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CString  m_WorkflowFileName;
        PSS_Date m_WorkflowLastUpdateDate;
        bool     m_CheckConsistency;
        bool     m_SaveModelInWorkflow;
};

//---------------------------------------------------------------------------
// PSS_WorkflowDefinition
//---------------------------------------------------------------------------
CString PSS_WorkflowDefinition::GetWorkflowFileName() const
{
    return m_WorkflowFileName;
}
//---------------------------------------------------------------------------
void PSS_WorkflowDefinition::ClearWorkflowFileName()
{
    m_WorkflowFileName.Empty();
}
//---------------------------------------------------------------------------
void PSS_WorkflowDefinition::SetWorkflowFileName(const CString& value)
{
    m_WorkflowFileName = value;
}
//---------------------------------------------------------------------------
PSS_Date& PSS_WorkflowDefinition::GetWorkflowLastUpdateDate()
{
    return m_WorkflowLastUpdateDate;
}
//---------------------------------------------------------------------------
void PSS_WorkflowDefinition::SetWorkflowLastUpdateDate(const PSS_Date& value)
{
    m_WorkflowLastUpdateDate = value;
}
//---------------------------------------------------------------------------
bool PSS_WorkflowDefinition::GetCheckConsistency() const
{
    return m_CheckConsistency;
}
//---------------------------------------------------------------------------
void PSS_WorkflowDefinition::SetCheckConsistency(bool value)
{
    m_CheckConsistency = value;
}
//---------------------------------------------------------------------------
bool PSS_WorkflowDefinition::GetSaveModelInWorkflow() const
{
    return m_SaveModelInWorkflow;
}
//---------------------------------------------------------------------------
void PSS_WorkflowDefinition::SetSaveModelInWorkflow(bool value)
{
    m_SaveModelInWorkflow = value;
}
//---------------------------------------------------------------------------

#endif
