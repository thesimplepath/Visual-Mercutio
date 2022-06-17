/****************************************************************************
 * ==> PSS_ProcessGraphModelDoc --------------------------------------------*
 ****************************************************************************
 * Description : Provides a process graphic model document                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessGraphModelDocH
#define PSS_ProcessGraphModelDocH

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
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// processsoft
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_BaseDocument.h"
#include "zBaseLib\PSS_DocumentPageSetup.h"
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_UnitManager.h"
#include "PSS_ModelSet.h"
#include "PSS_PageUnits.h"
#include "PSS_WorkflowDefinition.h"
#include "PSS_LanguageDefs.h"
#include "PSS_Defines.h"

// class name mapping
#ifndef PSS_DynamicPropertiesManager
    #define PSS_DynamicPropertiesManager ZBDynamicPropertiesManager
#endif

// forward class declaration
class PSS_Log;
class PSS_ProcessGraphModelView;
class ZUUserManager;
class ZUMail;
class ZDTemplateManager;
class PSS_DynamicPropertiesManager;

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
* Process graphic model document
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessGraphModelDoc : public PSS_BaseDocument,
                                               public PSS_Subject,
                                               public PSS_Observer
{
    DECLARE_SERIAL(PSS_ProcessGraphModelDoc)

    public:
        typedef PSS_BaseDocument inherited;

        PSS_ProcessGraphModelDoc();
        virtual ~PSS_ProcessGraphModelDoc();

        /**
        * Initializes the class
        *@param pOutputLog - output log
        *@param pAnalyzerLog - analyser log
        *@param pSearchLog - search log
        *@param pWorflowLog - workflow log
        *@param pUserManager - user manager
        *@param pMail - email
        *@param pTemplateManager - template manager
        */
        virtual void Initialize(PSS_Log*           pOutputLog,
                                PSS_Log*           pAnalyzerLog,
                                PSS_Log*           pSearchLog,
                                PSS_Log*           pWorflowLog,
                                ZUUserManager*     pUserManager,
                                ZUMail*            pMail,
                                ZDTemplateManager* pTemplateManager);

        /**
        * Pre-closes the frame
        *@param pFrame - the frame
        */
        virtual void PreCloseFrame(CFrameWnd* pFrame);

        /**
        * Checks if the frame is closing
        *@return TRUE if the frame is closing, otherwise FALSE
        */
        virtual BOOL IsClosing();

        /**
        * Gets the user manager
        *@return the user manager
        */
        virtual inline ZUUserManager* GetUserManager() const;

        /**
        * Gets the email
        *@return the email
        */
        virtual inline ZUMail* GetMail() const;

        /**
        * Gets the template manager
        *@return the template manager
        */
        virtual inline ZDTemplateManager* GetTemplateManager() const;

        /**
        * Gets the file guid
        *@return the file guid
        */
        virtual inline CString GetGUID() const;

        /**
        * Gets if the user def guid is assigned
        *@return true if the user def guid is assigned, otherwise false
        */
        virtual inline bool HasUserDefAssigned() const;

        /**
        * Gets the user def guid
        *@return the user def guid
        */
        virtual inline CString GetUserDefGUID() const;

        /**
        * Assigns the user def guid
        *@param value - the user def guid
        */
        virtual inline void AssignUserDefGUID(const CString& value);

        /**
        * Assigns the current user def guid
        *@return true on success, otherwise false
        */
        virtual bool AssignCurrentUserDefGUID();

        /**
        * Reassigns the unit
        *@param pLog - the log
        */
        virtual void ReassignUnit(PSS_Log* pLog = NULL);

        /**
        * Gets if the system def guid is assigned
        *@return true if the system def guid is assigned, otherwise false
        */
        virtual inline bool HasSystemDefAssigned() const;

        /**
        * Gets the system def guid
        *@return the system def guid
        */
        virtual inline CString GetSystemDefGUID() const;

        /**
        * Assigns the system def guid
        *@param value - the system def guid
        */
        virtual inline void AssignSystemDefGUID(const CString& value);

        /**
        * Assigns the current system def guid
        *@return true on success, otherwise false
        */
        virtual bool AssignCurrentSystemDefGUID();

        /**
        * Reassigns the system
        *@param pLog - the log
        */
        virtual void ReassignSystem(PSS_Log* pLog = NULL);

        /**
        * Gets if the prestations def guid is assigned
        *@return true if the prestations def guid is assigned, otherwise false
        */
        virtual inline bool HasPrestationsDefsAssigned() const;

        /**
        * Gets the prestations def guid
        *@return the prestations def guid
        */
        virtual inline CString GetPrestationsDefGUID() const;

        /**
        * Assigns the prestations def guid
        *@param value - the prestations def guid
        */
        virtual inline void AssignPrestationsDefGUID(const CString& value);

        /**
        * Assigns the current prestations def guid
        *@return true on success, otherwise false
        */
        virtual bool AssignCurrentPrestationsDefGUID();

        /**
        * Reassigns the prestations
        *@param pLog - the log
        */
        virtual void ReassignPrestations(PSS_Log* pLog = NULL);

        /**
        * Gets if the rules def guid is assigned
        *@return true if the rules def guid is assigned, otherwise false
        */
        virtual inline bool HasRulesDefsAssigned() const;

        /**
        * Gets the rules def guid
        *@return the rules def guid
        */
        virtual inline CString GetRulesDefGUID() const;

        /**
        * Assigns the rules def guid
        *@param value - the rules def guid
        */
        virtual inline void AssignRulesDefGUID(const CString& value);

        /**
        * Assigns the current rules def guid
        *@return true on success, otherwise false
        */
        virtual bool AssignCurrentRulesDefGUID();

        /**
        * Reassigns the rules
        *@param pLog - the log
        */
        virtual void ReassignRules(PSS_Log* pLog = NULL);

        /**
        * Gets the page units
        *@return the page units
        */
        virtual inline PSS_PageUnits& GetPageUnits();

        /**
        * Sets the page units
        *@param value - the page units
        */
        virtual void SetPageUnits(PSS_PageUnits& value);
        virtual void SetPageUnits(CODRuler&      value);

        /**
        * Inserts units
        *@param fileName - units file name
        *@return true on success, otherwise false
        */
        virtual bool InsertUnit(const CString& fileName);

        /**
        * Loads all the units
        *@return true on success, otherwise false
        */
        virtual bool LoadAllUnits();

        /**
        * Checks if the document is units
        *@return true if the document is units, otherwise false
        */
        virtual inline bool IsUnit();

        /**
        * Checks if the document is has units
        *@return true if the document has units, otherwise false
        */
        virtual inline bool HasUnit() const;

        /**
        * Gets the notation
        *@return the notation
        */
        virtual inline EModelNotation GetNotation() const;

        /**
        * Sets the notation
        *@param value - the notation
        */
        virtual inline void SetNotation(EModelNotation value);

        /**
        * Checks if the model is in ABC notation
        *@return true if the model is in ABC notation, otherwise false
        */
        virtual inline bool IsModelInABCNotation() const;

        /**
        * Checks if the model is in UML notation
        *@return true if the model is in UML notation, otherwise false
        */
        virtual inline bool IsModelInUMLNotation() const;

        /**
        * Checks if the model is in Beryl notation
        *@return true if the model is in Beryl notation, otherwise false
        */
        virtual inline bool IsModelInBerylNotation() const;

        /**
        * Checks if the model notation is unknown
        *@return true if the model notation is unknown, otherwise false
        */
        virtual inline bool IsModelNotationUnknow() const;

        /**
        * Generates the model workflow
        *@return true on success, otherwise false
        */
        virtual bool GenerateModelWorkflow();

        /**
        * Checks the model workflow
        *@param modelIsClean - if TRUE, the model is clean
        *@return true if the model workflow check succeeded, otherwise false
        */
        virtual bool CheckModelWorkflow(BOOL modelIsClean);

        /**
        * Deletes the model workflow definition
        */
        virtual void DeleteWorkflowDefinition();

        /**
        * Gets if do browse in the same window
        *@return if do browse in the same window, otherwise false
        */
        virtual inline bool GetBrowseInSameWindow() const;

        /**
        * Sets if do browse in the same window
        *@param value - if true, do browse in the same window
        */
        virtual inline void SetBrowseInSameWindow(bool value);

        /**
        * Gets the workflow file name
        *@return the workflow file name
        */
        virtual inline CString GetWorkflowFileName() const;

        /**
        * Sets the workflow file name
        *@param value - the workflow file name
        */
        virtual inline void SetWorkflowFileName(const CString& value);

        /**
        * Clears the workflow file name
        */
        virtual inline void ClearWorkflowFileName();

        /**
        * Gets the workflow last update date
        *@return the workflow last update date
        */
        virtual inline PSS_Date* GetWorkflowLastUpdateDate();

        /**
        * Sets the workflow last update date
        *@param value - the workflow last update date
        */
        virtual inline void SetWorkflowLastUpdateDate(const PSS_Date& value);

        /**
        * Gets if the consistency should be checked
        *@return true if consistency should be checked, otherwise false
        */
        virtual inline bool GetCheckConsistency() const;

        /**
        * Sets if the consistency should be checked
        *@param value - if true, the consistency should be checked
        */
        virtual inline void SetCheckConsistency(bool value);

        /**
        * Gets if the cost simulation should be integrated
        *@return true if the cost simulation should be integrated, otherwise false
        */
        virtual inline bool GetIntegrateCostSimulation() const;

        /**
        * Sets if the cost simulation should be integrated
        *@param value - if true, the cost simulation should be integrated
        */
        virtual inline void SetIntegrateCostSimulation(bool value);

        /**
        * Gets if the workflow should be used
        *@return true if the workflow should be used, otherwise false
        */
        virtual inline bool GetUseWorkflow() const;

        /**
        * Sets if the workflow should be used
        *@param value - if true, the workflow should be used
        */
        virtual void SetUseWorkflow(bool value);

        /**
        * Gets the hour per day count
        *@return the hour per day count
        */
        virtual inline int GetHourPerDay() const;

        /**
        * Sets the hour per day count
        *@param value - the hour per day count
        */
        virtual inline void SetHourPerDay(int value);

        /**
        * Gets the day per week count
        *@return the day per week count
        */
        virtual inline int GetDayPerWeek() const;

        /**
        * Sets the day per week count
        *@param value - the day per week count
        */
        virtual inline void SetDayPerWeek(int value);

        /**
        * Gets the day per month count
        *@return the day per month count
        */
        virtual inline int GetDayPerMonth() const;

        /**
        * Sets the day per month count
        *@param value - the day per month count
        */
        virtual inline void SetDayPerMonth(int value);

        /**
        * Gets the day per year count
        *@return the day per year count
        */
        virtual inline int GetDayPerYear() const;

        /**
        * Sets the day per year count
        *@param value - the day per year count
        */
        virtual inline void SetDayPerYear(int value);

        /**
        * Gets the currency symbol
        *@return the currency symbol
        */
        virtual inline CString GetCurrencySymbol() const;

        /**
        * Sets the currency symbol
        *@param value - the currency symbol
        */
        virtual inline void SetCurrencySymbol(const CString& value);

        /**
        * Gets if the model should be saved in workflow
        *@return true if the model should be saved in workflow, otherwise false
        */
        virtual inline bool GetSaveModelInWorkflow() const;

        /**
        * Sets if the model should be saved in workflow
        *@param value - if true, the model should be saved in workflow
        */
        virtual inline void SetSaveModelInWorkflow(bool value);

        /**
        * Gets if the page border should be shown
        *@return true if the page border should be shown, otherwise false
        */
        virtual inline bool GetShowPageBorder() const;

        /**
        * Sets if the page border should be shown
        *@param value - if true, the page border should be shown
        */
        virtual inline void SetShowPageBorder(bool value);

        /**
        * Gets the language
        *@return the language
        */
        virtual inline const ELanguage GetLanguage() const;

        /**
        * Sets the language
        *@param value - the language
        */
        virtual inline void SetLanguage(const ELanguage value);

        /**
        * Gets if the document is read-only
        *@return true if the document is read-only, otherwise false
        */
        virtual inline BOOL IsReadOnly();

        /**
        * Sets the document as read-only
        *@param value - if true, the document will be read-only
        */
        virtual inline void SetReadOnly(BOOL value);

        /**
        * Gets the model output log
        *@return the model output log
        */
        virtual inline PSS_Log* GetModelOutputLog();

        /**
        * Gets the analyzer output log
        *@return the analyzer output log
        */
        virtual inline PSS_Log* GetAnalyzerOutputLog();

        /**
        * Gets the search output log
        *@return the search output log
        */
        virtual inline PSS_Log* GetSearchOutputLog();

        /**
        * Gets the workflow output log
        *@return the workflow output log
        */
        virtual inline PSS_Log* GetWorkflowOutputLog();

        /**
        * Gets the main user group
        *@return the main user group
        */
        virtual inline PSS_UserGroupEntity* GetMainUserGroup();

        /**
        * Assigns the main user group
        *@param pMainUserGroup - the main user group
        */
        virtual inline void AssignMainUserGroup(PSS_UserGroupEntity* pMainUserGroup);

        /**
        * Gets the main logical system
        *@return the main logical system
        */
        virtual inline PSS_LogicalSystemEntity* GetMainLogicalSystem();

        /**
        * Assigns the main logical system
        *@param pMainLogicalSystem - the main logical system
        */
        virtual inline void AssignMainLogicalSystem(PSS_LogicalSystemEntity* pMainLogicalSystem);

        /**
        * Gets the main logical prestations
        *@return the main logical prestations
        */
        virtual inline PSS_LogicalPrestationsEntity* GetMainLogicalPrestations();

        /**
        * Assigns the main logical prestations
        *@param pMainLogicalPrestations - the main logical prestations
        */
        virtual inline void AssignMainLogicalPrestations(PSS_LogicalPrestationsEntity* pMainLogicalPrestations);

        /**
        * Gets the main logical rules
        *@return the main logical rules
        */
        virtual inline PSS_LogicalRulesEntity* GetMainLogicalRules();

        /**
        * Assigns the main logical rules
        *@param pMainLogicalRules - the main logical rules
        */
        virtual inline void AssignMainLogicalRules(PSS_LogicalRulesEntity* pMainLogicalRules);

        /**
        * Gets the canvas model
        *@return the canvas model
        */
        virtual inline       PSS_ProcessGraphModelMdl* GetModel();
        virtual inline const PSS_ProcessGraphModelMdl* GetModel() const;

        /**
        * Sets a new model
        *@param pModel - model to set
        */
        virtual void SetNewModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Gets the document template
        *@return the document template
        */
        virtual inline CDocTemplate* GetDocTemplate() const;

        /**
        * Sets the modified flag
        *@param modified - if true, the document was modified
        */
        virtual inline void SetModifiedFlag(BOOL modified = TRUE);

        /**
        * Gets the printer page size
        *@return the printer page size
        */
        virtual PSS_DocumentPageSetup* GetPrinterPageSize();

        /**
        * Gets the first model view
        *@return the first model view
        */
        virtual PSS_ProcessGraphModelView* GetFirstModelView();

        /**
        * Finds the view
        *@param name - the view name to search
        *@return the view, NULL if not found or on error
        */
        virtual CView* FindView(const CString& name);

        /**
        * Activates the view
        *@param name - the view name to search
        *@return the view, NULL if not found or on error
        */
        virtual CView* ActivateView(const CString& name);

        /**
        * Switches the view
        *@param pNewView - the view to switch to
        *@param index - the view index
        *@return the view, NULL if not found or on error
        */
        virtual CView* SwitchView(CView* pNewView, std::size_t index = 0);

        /**
        * Checks if the canvas was modified
        *@return TRUE if the canvas was modified, otherwise FALSE
        */
        virtual BOOL IsModified();

        /**
        * Checks if is in model creation
        *@return true if is in model creation, otherwise false
        */
        virtual inline bool IsInModelCreation() const;

        /**
        * Gets the dynamic properties manager
        *@return the dynamic properties manager
        */
        virtual inline PSS_DynamicPropertiesManager* GetDynamicPropertiesManager();

        /**
        * Checks if the document has dynamic properties manager
        *@return true if the document has dynamic properties manager, otherwise false
        */
        virtual inline bool HasDynamicPropertiesManager() const;

        /**
        * Allocates the property manager
        *@param deleteFirst - if true, the previous property manager will be deleted first
        */
        virtual void AllocatePropertiesManager(bool deleteFirst = false);

        /**
        * Deletes the document content
        */
        virtual void DeleteContents();

        /**
        * Checks if the file should be saved
        *@return TRUE if the file should be saved, otherwise FALSE
        */
        virtual BOOL DoFileSave();

        /**
        * Sets the file as read-only
        *@param pPathName - the path name
        *@param value - if TRUE, the file will be written in read-only mode
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetFileReadOnly(const char* pPathName, BOOL value);

        /**
        * Reads the document content from file
        *@param fileName - the document file name to read from
        *@return true on success, otherwise false
        */
        virtual bool ReadFromFile(const CString& fileName);

        /**
        * Writes the document content to file
        *@param fileName - the document file name to write to
        *@return true on success, otherwise false
        */
        virtual bool SaveToFile(const CString& fileName);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

        /**
        * Called after the doucument was opened
        */
        virtual void OnPostOpenDocument();

        /**
        * Called when a new document is created
        *@return TRUE if the document can be created, otherwise FALSE
        */
        virtual BOOL OnNewDocument();

        /**
        * Called when a document is opened
        *@param pPathName - the document path name
        *@return TRUE if the document can be opened, otherwise FALSE
        */
        virtual BOOL OnOpenDocument(LPCTSTR pPathName);

        /**
        * Called when a document is saved
        *@param pPathName - the document path name
        *@return TRUE if the document can be saved, otherwise FALSE
        */
        virtual BOOL OnSaveDocument(const char* pPathName);

        /**
        * Called when a new document is closed
        */
        virtual void OnCloseDocument();

        /**
        * Called when the subject sent a message to this observer
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        PSS_ProcessGraphModelMdl  m_EmptyModel;
        PSS_ProcessGraphModelMdl* m_pModel;

        /// Generated message map functions
        //{{AFX_MSG(PSS_ProcessGraphModelDoc)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_PageUnits                 m_PageUnits;
        ZUUserManager*                m_pUserManager;
        ZUMail*                       m_pMail;
        ZDTemplateManager*            m_pTemplateManager;
        PSS_DynamicPropertiesManager* m_DynamicPropertiesManager;
        PSS_UnitManager*              m_pUnitManager;
        PSS_ModelSet                  m_DocumentModelSet;
        PSS_ModelSet                  m_UnitModelSet;
        PSS_WorkflowDefinition*       m_pWorkflowDefinition;
        PSS_Log*                      m_pOutputLog;
        PSS_Log*                      m_pAnalyzerLog;
        PSS_Log*                      m_pSearchLog;
        PSS_Log*                      m_pWorflowLog;
        CString                       m_GUID;
        CString                       m_UserDefGUID;
        CString                       m_SystemDefGUID;
        CString                       m_PrestationsDefGUID;
        CString                       m_RulesDefGUID;
        CString                       m_CurrencySymbol;
        CSize                         m_PaperSize;
        int                           m_HourPerDay;
        int                           m_DayPerWeek;
        int                           m_DayPerMonth;
        int                           m_DayPerYear;
        short                         m_StandardSize;
        short                         m_Orientation;
        BOOL                          m_IsDocumentClosing;
        BOOL                          m_IsReadOnly;
        bool                          m_IsInModelCreation;
        bool                          m_UseWorkflow;
        bool                          m_BrowseInSameWindow;
        bool                          m_IntegrateCostSimulation;
        bool                          m_CheckConsistency;
        bool                          m_ShowPageBorder;

        /**
        * Creates the unit manager
        *@return true on success, otherwise false
        */
        bool CreateUnitManager();
};

//---------------------------------------------------------------------------
// PSS_ProcessGraphModelDoc
//---------------------------------------------------------------------------
ZUUserManager* PSS_ProcessGraphModelDoc::GetUserManager() const
{
    return m_pUserManager;
}
//---------------------------------------------------------------------------
ZUMail* PSS_ProcessGraphModelDoc::GetMail() const
{
    return m_pMail;
}
//---------------------------------------------------------------------------
ZDTemplateManager* PSS_ProcessGraphModelDoc::GetTemplateManager() const
{
    return m_pTemplateManager;
}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelDoc::GetGUID() const
{
    return m_GUID;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::HasUserDefAssigned() const
{
    return !m_UserDefGUID.IsEmpty();
}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelDoc::GetUserDefGUID() const
{
    return m_UserDefGUID;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::AssignUserDefGUID(const CString& value)
{
    m_UserDefGUID = value;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::HasSystemDefAssigned() const
{
    return !m_SystemDefGUID.IsEmpty();
}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelDoc::GetSystemDefGUID() const
{
    return m_SystemDefGUID;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::AssignSystemDefGUID(const CString& value)
{
    m_SystemDefGUID = value;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::HasPrestationsDefsAssigned() const
{
    return !m_PrestationsDefGUID.IsEmpty();
}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelDoc::GetPrestationsDefGUID() const
{
    return m_PrestationsDefGUID;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::AssignPrestationsDefGUID(const CString& value)
{
    m_PrestationsDefGUID = value;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::HasRulesDefsAssigned() const
{
    return !m_RulesDefGUID.IsEmpty();
}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelDoc::GetRulesDefGUID() const
{
    return m_RulesDefGUID;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::AssignRulesDefGUID(const CString& value)
{
    m_RulesDefGUID = value;
}
//---------------------------------------------------------------------------
PSS_PageUnits& PSS_ProcessGraphModelDoc::GetPageUnits()
{
    return m_PageUnits;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::IsUnit()
{
    return (GetDocumentStamp().GetFileType() == PSS_Stamp::IEFileTypeDefinition::IE_FD_LibraryType);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::HasUnit() const
{
    return m_pUnitManager;
}
//---------------------------------------------------------------------------
EModelNotation PSS_ProcessGraphModelDoc::GetNotation() const
{
    const PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return EModelNotation::E_MN_Unknown;

    return pModel->GetNotation();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetNotation(EModelNotation value)
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    pModel->SetNotation(value);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::IsModelInABCNotation() const
{
    const PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return false;

    return pModel->IsModelInABCNotation();
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::IsModelInUMLNotation() const
{
    const PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return false;

    return pModel->IsModelInUMLNotation();
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::IsModelInBerylNotation() const
{
    const PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return false;

    return pModel->IsModelInBerylNotation();
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::IsModelNotationUnknow() const
{
    const PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return false;

    return pModel->IsModelNotationUnknow();
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::GetBrowseInSameWindow() const
{
    return m_BrowseInSameWindow;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetBrowseInSameWindow(bool value)
{
    m_BrowseInSameWindow = value;
}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelDoc::GetWorkflowFileName() const
{
    return (m_pWorkflowDefinition ? m_pWorkflowDefinition->GetWorkflowFileName() : _T(""));
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetWorkflowFileName(const CString& value)
{
    if (m_pWorkflowDefinition)
        m_pWorkflowDefinition->SetWorkflowFileName(value);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::ClearWorkflowFileName()
{
    if (m_pWorkflowDefinition)
        m_pWorkflowDefinition->ClearWorkflowFileName();
}
//---------------------------------------------------------------------------
PSS_Date* PSS_ProcessGraphModelDoc::GetWorkflowLastUpdateDate()
{
    return (m_pWorkflowDefinition ? &m_pWorkflowDefinition->GetWorkflowLastUpdateDate() : NULL);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetWorkflowLastUpdateDate(const PSS_Date& value)
{
    if (m_pWorkflowDefinition)
        m_pWorkflowDefinition->SetWorkflowLastUpdateDate(value);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::GetCheckConsistency() const
{
    return m_CheckConsistency;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetCheckConsistency(bool value)
{
    m_CheckConsistency = value;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::GetIntegrateCostSimulation() const
{
    return m_IntegrateCostSimulation;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetIntegrateCostSimulation(bool value)
{
    m_IntegrateCostSimulation = value;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::GetUseWorkflow() const
{
    return m_UseWorkflow;
}
//---------------------------------------------------------------------------
int PSS_ProcessGraphModelDoc::GetHourPerDay() const
{
    return m_HourPerDay;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetHourPerDay(int value)
{
    m_HourPerDay = value;
}
//---------------------------------------------------------------------------
int PSS_ProcessGraphModelDoc::GetDayPerWeek() const
{
    return m_DayPerWeek;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetDayPerWeek(int value)
{
    m_DayPerWeek = value;
}
//---------------------------------------------------------------------------
int PSS_ProcessGraphModelDoc::GetDayPerMonth() const
{
    return m_DayPerMonth;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetDayPerMonth(int value)
{
    m_DayPerMonth = value;
}
//---------------------------------------------------------------------------
int PSS_ProcessGraphModelDoc::GetDayPerYear() const
{
    return m_DayPerYear;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetDayPerYear(int value)
{
    m_DayPerYear = value;
}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelDoc::GetCurrencySymbol() const
{
    return m_CurrencySymbol;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetCurrencySymbol(const CString& value)
{
    m_CurrencySymbol = value;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::GetSaveModelInWorkflow() const
{
    return (m_pWorkflowDefinition) ? m_pWorkflowDefinition->GetSaveModelInWorkflow() : false;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetSaveModelInWorkflow(bool value)
{
    if (m_pWorkflowDefinition)
        m_pWorkflowDefinition->SetSaveModelInWorkflow(value);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::GetShowPageBorder() const
{
    return m_ShowPageBorder;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetShowPageBorder(bool value)
{
    m_ShowPageBorder = value;
}
//---------------------------------------------------------------------------
const ELanguage PSS_ProcessGraphModelDoc::GetLanguage() const
{
    PSS_ProcessGraphModelMdl* pModel = const_cast<PSS_ProcessGraphModelMdl*>(GetModel());

    if (!pModel)
        return ELanguage::E_LN_Unknown;

    return pModel->GetLanguage();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetLanguage(const ELanguage value)
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    pModel->SetLanguage(value);
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelDoc::IsReadOnly()
{
    return m_IsReadOnly;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetReadOnly(BOOL value)
{
    m_IsReadOnly = value;
}
//---------------------------------------------------------------------------
PSS_Log* PSS_ProcessGraphModelDoc::GetModelOutputLog()
{
    return m_pOutputLog;
}
//---------------------------------------------------------------------------
PSS_Log* PSS_ProcessGraphModelDoc::GetAnalyzerOutputLog()
{
    return m_pAnalyzerLog;
}
//---------------------------------------------------------------------------
PSS_Log* PSS_ProcessGraphModelDoc::GetSearchOutputLog()
{
    return m_pSearchLog;
}
//---------------------------------------------------------------------------
PSS_Log* PSS_ProcessGraphModelDoc::GetWorkflowOutputLog()
{
    return m_pWorflowLog;
}
//---------------------------------------------------------------------------
PSS_UserGroupEntity* PSS_ProcessGraphModelDoc::GetMainUserGroup()
{
    const PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return NULL;

    return pModel->GetMainUserGroup();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::AssignMainUserGroup(PSS_UserGroupEntity* pMainUserGroup)
{
    const PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    pModel->AssignMainUserGroup(pMainUserGroup);
}
//---------------------------------------------------------------------------
PSS_LogicalSystemEntity* PSS_ProcessGraphModelDoc::GetMainLogicalSystem()
{
    const PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return NULL;

    return pModel->GetMainLogicalSystem();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::AssignMainLogicalSystem(PSS_LogicalSystemEntity* pMainLogicalSystem)
{
    const PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    pModel->AssignMainLogicalSystem(pMainLogicalSystem);
}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsEntity* PSS_ProcessGraphModelDoc::GetMainLogicalPrestations()
{
    const PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return NULL;

    return pModel->GetMainLogicalPrestations();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::AssignMainLogicalPrestations(PSS_LogicalPrestationsEntity* pMainLogicalPrestations)
{
    const PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    pModel->AssignMainLogicalPrestations(pMainLogicalPrestations);
}
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity* PSS_ProcessGraphModelDoc::GetMainLogicalRules()
{
    const PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return NULL;

    return pModel->GetMainLogicalRules();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::AssignMainLogicalRules(PSS_LogicalRulesEntity* pMainLogicalRules)
{
    const PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    pModel->AssignMainLogicalRules(pMainLogicalRules);
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelDoc::GetModel()
{
    return (m_pModel ? m_pModel : &m_EmptyModel);
}
//---------------------------------------------------------------------------
const PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelDoc::GetModel() const
{
    return (m_pModel ? m_pModel : &m_EmptyModel);
}
//---------------------------------------------------------------------------
CDocTemplate* PSS_ProcessGraphModelDoc::GetDocTemplate() const
{
    return PSS_BaseDocument::GetDocTemplate();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelDoc::SetModifiedFlag(BOOL modified)
{
    PSS_BaseDocument::SetModifiedFlag(modified);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::IsInModelCreation() const
{
    return m_IsInModelCreation;
}
//---------------------------------------------------------------------------
PSS_DynamicPropertiesManager* PSS_ProcessGraphModelDoc::GetDynamicPropertiesManager()
{
    return m_DynamicPropertiesManager;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelDoc::HasDynamicPropertiesManager() const
{
    return m_DynamicPropertiesManager != NULL;
}
//---------------------------------------------------------------------------

#endif
