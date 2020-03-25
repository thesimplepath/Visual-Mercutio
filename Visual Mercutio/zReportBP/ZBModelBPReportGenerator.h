// ZBModelBPReportGenerator.h: interface for the ZBModelBPReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBModelBPReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_)
#define AFX_ZBModelBPReportGenerator_H__92F0037B_1EAF_4F26_BE0A_CFBCC6D7C6FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zReport\PSS_GenericGridReportGenerator.h"
#include "zReport\PSS_OStreamGrid.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
#define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif
#ifndef PSS_ProcessGraphModelMdlBP
#define PSS_ProcessGraphModelMdlBP ZDProcessGraphModelMdlBP
#endif

// forward class declaration
class PSS_GridDocument;
class PSS_ProcessGraphModelMdlBP;
class PSS_ProcessGraphModelDoc;

#ifdef _ZREPORTBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 7 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBModelBPReportGenerator : public PSS_GenericGridReportGenerator
{
    DECLARE_SERIAL(ZBModelBPReportGenerator)

public:

    ZBModelBPReportGenerator(PSS_GridDocument*            pDoc = NULL,
                             PSS_ProcessGraphModelMdlBP*    pModel = NULL,
                             PSS_ProcessGraphModelDoc*    pSourceDoc = NULL);

    virtual ~ZBModelBPReportGenerator();

    virtual void Initialize(PSS_GridDocument*            pDoc,
                            PSS_ProcessGraphModelMdlBP*    pModel,
                            PSS_ProcessGraphModelDoc*    pSourceDoc);

    /////////////////////////////////////////////////////////////////////////////
    // ZIGridReportGenerator methods

    // Initialization method
    virtual bool Initialize()
    {
        FillTabArray();
        return true;
    };

    // Returns the number of tabs
    virtual size_t GetGeneratorTabCount() const
    {
        return m_TabNameArray.GetSize();
    };

    // Returns the tab name corresponding to the index
    virtual const CString GetGeneratorTabName(size_t Index)
    {
        return (Index < GetGeneratorTabCount()) ? m_TabNameArray.GetAt(Index) : _T("");
    };

    // Returns 0. No special ID for this report
    virtual int GetReportTypeID() const
    {
        return 0;
    };

    // Yes, the data depends on the model
    virtual bool IsReportDataExternal() const
    {
        return true;
    };

    virtual bool ReportDataMustBeReloaded() const;

    // Request the system to ask before reloading information
    // thus return false
    virtual bool UseAutomaticReload() const
    {
        return false;
    };

    // Serialization call-back
    virtual void OnPostRead(CArchive& ar);
    virtual void OnPostWrite(CArchive& ar)
    {};

    // Call-back methods
    virtual void OnPostDataFilled(size_t Index);

    // Serialization
    virtual void Serialize(CArchive& ar);

    // Implementation
public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    // The derived class must implement this method
    // to fill the tabs.
    virtual void FillTabArray()
    {};

protected:

    PSS_ProcessGraphModelDoc*        m_pSourceDoc;
    PSS_ProcessGraphModelMdlBP*    m_pModel;
    CStringArray                m_TabNameArray;
    bool                        m_InChargeOfClosingFile;
};

#endif
