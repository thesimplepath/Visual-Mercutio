/****************************************************************************
 * ==> PSS_ProcessGraphModelMdlBP ------------------------------------------*
 ****************************************************************************
 * Description : Provides a process graphic model for banking process       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessGraphModelMdlBPH
#define PSS_ProcessGraphModelMdlBPH

#if _MSC_VER >= 1000
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
#ifndef PSS_ProcessGraphModelMdlBP
    #define PSS_ProcessGraphModelMdlBP ZDProcessGraphModelMdlBP
#endif

#include "zModel\PSS_ProcessGraphModelMdl.h"

// old class name mapping
#ifndef PSS_DistributionAttributeManager
    #define PSS_DistributionAttributeManager ZBDistributionAttributeManager
#endif

// forward class declaration
class ZBInputAttributeManager;
class PSS_DistributionAttributeManager;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Process graphic model for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessGraphModelMdlBP : public PSS_ProcessGraphModelMdl
{
    DECLARE_SERIAL(PSS_ProcessGraphModelMdlBP)

    public:
        /**
        * Constructor
        *@param name - the model name
        *@param pParent - the parent model, if NULL the model will be a root model
        */
        PSS_ProcessGraphModelMdlBP(const CString& name = _T(""), PSS_ProcessGraphModelMdlBP* pParent = NULL);

        virtual ~PSS_ProcessGraphModelMdlBP();

        /**
        * Creates an empty model
        *@param name - the model name
        *@param pParent - the parent model, if NULL the model will be a root model
        *@return the newly created model, NULL on error
        */
        virtual inline PSS_ProcessGraphModelMdl* CreateEmptyModel(const CString&            name    = _T(""),
                                                                  PSS_ProcessGraphModelMdl* pParent = NULL);

        /**
        * Creates the model controller
        *@param pVp - the model viewport
        *@return the newly created model controller, NULL on error
        */
        virtual PSS_ProcessGraphModelController* CreateController(PSS_ProcessGraphModelViewport* pVp);

        /**
        * Sets the default workflow property
        *@param redefineOnExisting - if true, the property will be redefined if already existing
        */
        virtual void SetDefaultWkfProperty(bool redefineOnExisting = false);

        /**
        * Deletes all the activities linked to the workflow
        */
        virtual void DeleteAllActivitiesLinkedToWorkflow();

        /**
        * Called to recalculate all assigned page symbol references
        */
        virtual void RecalculateSymbolReferences();

        /**
        * Gets the page symbols contained in the model
        *@param[out] nodes - the page symbols contained in the model
        *@param deep - if true, the search will continue in the model children
        *@return the found symbol count
        */
        virtual std::size_t GetBPPageSymbols(CODNodeArray& nodes, bool deep = false);

        /**
        * Gets the door symbols contained in the model
        *@param[out] nodes - the door symbols contained in the model
        *@param deep - if true, the search will continue in the model children
        *@return the found symbol count
        */
        virtual std::size_t GetBPDoorSymbols(CODNodeArray& nodes, bool deep = false);

        /**
        * Gets the start symbols contained in the model
        *@param[out] nodes - the start symbols contained in the model
        *@param deep - if true, the search will continue in the model children
        *@return the found symbol count
        */
        virtual std::size_t GetStartSymbols(CODNodeArray& nodes, bool deep = false);

        /**
        * Gets the start symbols contained in the model
        *@param[out] nodes - the start symbols contained in the model
        *@param deep - if true, the search will continue in the model children
        *@return the found symbol count
        */
        virtual std::size_t GetBPStartSymbols(CODNodeArray& nodes, bool deep = false);

        /**
        * Gets the stop symbols contained in the model
        *@param[out] nodes - the stop symbols contained in the model
        *@param deep - if true, the search will continue in the model children
        *@return the found symbol count
        */
        virtual std::size_t GetBPStopSymbols(CODNodeArray& nodes, bool deep = false);

        /**
        * Gets the procedure symbols contained in the model
        *@param[out] nodes - the procedure symbols contained in the model
        *@param deep - if true, the search will continue in the model children
        *@return the found symbol count
        */
        virtual std::size_t GetBPProcedureSymbols(CODNodeArray& nodes, bool deep = false);

        /**
        * Gets the process symbols contained in the model
        *@param[out] nodes - the process symbols contained in the model
        *@param deep - if true, the search will continue in the model children
        *@return the found symbol count
        */
        virtual std::size_t GetBPProcessSymbols(CODNodeArray& nodes, bool deep = false);

        /**
        * Gets the symbol image resource identifier
        *@return the symbol image resource identifier
        */
        virtual UINT GetSymbolImageIDRes() const;

        /**
        * Checks the model workflow
        *@param pLog - the log
        *@param modelIsClean - if TRUE, the model is clean
        *@return true on success, otherwise false
        */
        virtual bool CheckModelWorkflow(PSS_Log* pLog, BOOL modelIsClean);

        /**
        * Generates the model workflow
        *@param pLog - the log
        *@param pDoc - the model document
        *@return true on success, otherwise false
        */
        virtual bool GenerateModelWorkflow(PSS_Log* pLog, PSS_ProcessGraphModelDoc* pDoc);

        /**
        * Reassigns the unit
        *@param pLog - the log
        */
        virtual void ReassignUnit(PSS_Log* pLog = NULL);

        /**
        * Reassigns the system
        *@param pLog - the log
        */
        virtual void ReassignSystem(PSS_Log* pLog = NULL);

        /**
        * Notifies about the page deletion
        *@param pPage - the page about to be deleted
        */
        virtual void NotifyDeletePage(PSS_ProcessGraphPage* pPage);

        /**
        * Allocates the input attributes
        *@param deleteExisting - if true, the existing attributes will be deleted before assigning the new one
        *@return the newly created input attributes, NULL on error
        */
        virtual ZBInputAttributeManager* AllocateInputAttributes(bool deleteExisting = false);

        /**
        * Gets the input attributes
        *@return the input attributes
        */
        virtual inline ZBInputAttributeManager* GetInputAttributes();

        /**
        * Checks if the model contains input attributes
        *@return true if the model contains input attributes, otherwise false
        */
        virtual inline bool HasInputAttributes();

        /**
        * Allocates the distribution attributes
        *@param deleteExisting - if true, the existing attributes will be deleted before assigning the new one
        *@return the newly created input attributes, NULL on error
        */
        virtual PSS_DistributionAttributeManager* AllocateDistributionAttributes(bool deleteExisting = false);

        /**
        * Gets the distribution attributes
        *@return the distribution attributes
        */
        virtual inline PSS_DistributionAttributeManager* GetDistributionAttributes();

        /**
        * Checks if the model contains distribution attributes
        *@return true if the model contains distribution attributes, otherwise false
        */
        virtual inline bool HasDistributionAttributes();

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Called after the framework opened the document
        *@param version - the document version
        */
        virtual void OnPostOpenDocument(long version);

    protected:
        /**
        * Recalculates the page reference
        */
        virtual void RecalculatePageReference();

        /**
        * Recalculates the door reference
        */
        virtual void RecalculateDoorReference();

        /**
        * Gets the start symbols contained in a start process
        *@param[out] nodes - the start symbols contained in the process
        *@param deep - if true, the search will continue in the process children
        *@return the found symbol count
        */
        virtual std::size_t GetStartSymbolInStartProcess(CODNodeArray& nodes, bool deep = false);

        /**
        * Migrates the properties
        */
        virtual void MigrateProperties();

        /**
        * Migrates the unit GUID
        */
        virtual void MigrateUnitGUID();

        /**
        * Converts the deliverables
        */
        virtual void ConvertDeliverables();

    private:
        ZBInputAttributeManager*          m_pInputAttributes;
        PSS_DistributionAttributeManager* m_pDistributionAttributes;
};

//---------------------------------------------------------------------------
// PSS_ProcessGraphModelMdlBP
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelMdlBP::CreateEmptyModel(const CString& name, PSS_ProcessGraphModelMdl* pParent)
{
    return new PSS_ProcessGraphModelMdlBP(name, dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pParent));
}
//---------------------------------------------------------------------------
ZBInputAttributeManager* PSS_ProcessGraphModelMdlBP::GetInputAttributes()
{
    if (GetRoot() == this)
        return m_pInputAttributes;

    PSS_ProcessGraphModelMdlBP* pRoot = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(GetRoot());

    return (pRoot ? pRoot->GetInputAttributes() : NULL);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdlBP::HasInputAttributes()
{
    return GetInputAttributes();
}
//---------------------------------------------------------------------------
PSS_DistributionAttributeManager* PSS_ProcessGraphModelMdlBP::GetDistributionAttributes()
{
    if (GetRoot() == this)
        return m_pDistributionAttributes;

    PSS_ProcessGraphModelMdlBP* pRoot = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(GetRoot());

    return (pRoot ? pRoot->GetDistributionAttributes() : NULL);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdlBP::HasDistributionAttributes()
{
    return GetDistributionAttributes();
}
//---------------------------------------------------------------------------

#endif
