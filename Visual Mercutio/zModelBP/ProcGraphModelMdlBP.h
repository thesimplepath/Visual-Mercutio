// ProcGraphModelMdlBP.h : interface of the ZDProcessGraphModelMdlBP class

#if !defined(AFX_ProcGraphModelMdlBP_H__720C6641_0BFA_4FCA_A706_6D6312331D23__INCLUDED_)
#define AFX_ProcGraphModelMdlBP_H__720C6641_0BFA_4FCA_A706_6D6312331D23__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zModel\ProcGraphModelMdl.h"

// forward class declaration
class ZBInputAttributeManager;
class ZBDistributionAttributeManager;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 27 septembre 2005 - Ajout de la décoration unicode _T( )

class AFX_EXT_CLASS ZDProcessGraphModelMdlBP : public PSS_ProcessGraphModelMdl
{
    DECLARE_SERIAL(ZDProcessGraphModelMdlBP)

public:

    ZDProcessGraphModelMdlBP(const CString Name = _T(""), ZDProcessGraphModelMdlBP* pParent = NULL);
    virtual ~ZDProcessGraphModelMdlBP();

    // This method creates the associated controller
    virtual PSS_ProcessGraphModelController* CreateController(ZIProcessGraphModelViewport* pVp);

    virtual void            SetDefaultWkfProperty(bool RedefineOnExisting = false);
    virtual void            DeleteAllActivitiesLinkedToWorkflow();

    // Called to create the adequate model
    virtual PSS_ProcessGraphModelMdl* CreateEmptyModel(const CString                Name = _T(""),
                                                       PSS_ProcessGraphModelMdl*    pParent = NULL)
    {
        return reinterpret_cast<PSS_ProcessGraphModelMdl*>(new ZDProcessGraphModelMdlBP(Name, reinterpret_cast<ZDProcessGraphModelMdlBP*>(pParent)));
    }

    // the OnPostOpenDocument method is called once the framework has 
    // open the document
    virtual    void    OnPostOpenDocument(long DocumentVersion);

    // Called to recalculate all assigned page symbols
    virtual void            RecalculateSymbolReferences();

    // Get symbol type from model
    size_t    GetBPPageSymbols(CODNodeArray& Nodes, bool Deep = false);
    size_t    GetBPDoorSymbols(CODNodeArray& Nodes, bool Deep = false);
    size_t    GetBPStartSymbols(CODNodeArray& Nodes, bool Deep = false);
    size_t    GetBPStopSymbols(CODNodeArray& Nodes, bool Deep = false);
    size_t    GetBPProcedureSymbols(CODNodeArray& Nodes, bool Deep = false);
    size_t    GetBPProcessSymbols(CODNodeArray& Nodes, bool Deep = false);

    // Returns the Image Resource ID for symbols
    virtual UINT    GetSymbolImageIDRes() const;

    //////////////////////////////////////////////////////////////////////
    // Model generation methods
    // JMR-MODIF - Le 5 novembre 2006 - Ajout du paramètre ModelIsClean.
    virtual bool            CheckModelWorkflow(PSS_Log* pLog, BOOL ModelIsClean);
    virtual bool            GenerateModelWorkflow(PSS_Log* pLog, PSS_ProcessGraphModelDoc* pDoc);

    ///////////////////////////////////////////////////////
    // ZINavigableModel methods

    // Methods to obtain start symbols
    virtual size_t GetStartSymbols(CODNodeArray& Nodes, bool Deep = false);

    // Unit and System 
    virtual void ReassignUnit(PSS_Log* pLog = NULL);
    virtual void ReassignSystem(PSS_Log* pLog = NULL);

    virtual void NotifyDeletePage(ZDProcessGraphPage* pPage);

    // Input attribute accessors
    bool HasInputAttributes()
    {
        return (GetInputAttributes() != NULL) ? true : false;
    };

    ZBInputAttributeManager* AllocateInputAttributes(bool DeleteExisting = false);

    ZBInputAttributeManager* GetInputAttributes()
    {
        if (GetRoot() == this)
        {
            return m_InputAttributes;
        }

        return dynamic_cast<ZDProcessGraphModelMdlBP*>(GetRoot())->GetInputAttributes();
    };

    // Distribution attribute accessors
    bool HasDistributionAttributes()
    {
        return (GetDistributionAttributes() != NULL) ? true : false;
    };

    ZBDistributionAttributeManager* AllocateDistributionAttributes(bool DeleteExisting = false);

    ZBDistributionAttributeManager* GetDistributionAttributes()
    {
        if (GetRoot() == this)
        {
            return m_pDistributionAttributes;
        }

        return dynamic_cast<ZDProcessGraphModelMdlBP*>(GetRoot())->GetDistributionAttributes();
    };

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDProcessGraphModelMdlBP)
public:
    virtual void Serialize(CArchive& ar);
    //}}AFX_VIRTUAL

protected:

    void RecalculatePageReference();
    void RecalculateDoorReference();

    size_t GetStartSymbolInStartProcess(CODNodeArray& Nodes, bool Deep = false);

    void MigrateProperties();
    void MigrateUnitGUID();
    void ConvertDeliverables();

private:

    ZBInputAttributeManager*        m_InputAttributes;
    ZBDistributionAttributeManager*    m_pDistributionAttributes;
};

#endif
