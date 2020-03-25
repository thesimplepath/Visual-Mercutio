// ZDGridReportDoc.h : interface of the ZDGridReportDocument class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZDGridReportDoc_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_)
#define AFX_ZDGridReportDoc_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "PSS_GridDocument.h"
#include "ZIGridReportGenerator.h"

// old class name mapping
#ifndef PSS_GenericGridReportGenerator
    #define PSS_GenericGridReportGenerator ZBGenericGridReportGenerator
#endif

// forward class declaration
class PSS_GenericGridReportGenerator;

#ifdef _ZREPORTEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 7 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZDGridReportDocument : public PSS_GridDocument, public ZIGridReportGenerator
{
protected:

    GXDECLARE_DYNCREATE(ZDGridReportDocument)

        // Create from serialization only
        ZDGridReportDocument();

public:

    virtual ~ZDGridReportDocument();

    // Operations
public:

    bool SetNewReportGridGenerator(PSS_GenericGridReportGenerator* pGenerator);
    PSS_GenericGridReportGenerator* GetReportGridGenerator()
    {
        if (GetPrimaryDocument() == this)
        {
            return m_pGenerator;
        }

        return (GetPrimaryDocument() &&
                ISA(GetPrimaryDocument(), ZDGridReportDocument)) ?
            dynamic_cast<ZDGridReportDocument*>(GetPrimaryDocument())->GetReportGridGenerator() : NULL;
    };

    void AssignGeneratorPtr(PSS_GenericGridReportGenerator* pGenerator)
    {
        m_pGenerator = pGenerator;
    }

    bool ViewRequireDataRefresh() const
    {
        if (GetPrimaryDocument() == const_cast<ZDGridReportDocument*>(this))
        {
            return m_ViewRequireDataRefresh;
        }

        return (GetPrimaryDocument() &&
                ISA(GetPrimaryDocument(), ZDGridReportDocument)) ?
            dynamic_cast<ZDGridReportDocument*>(GetPrimaryDocument())->ViewRequireDataRefresh() : false;
    };

    /////////////////////////////////////////////////////////////////////////////
    // ZIGridReportGenerator methods

    // Initialization method
    virtual bool Initialize()
    {
        return InitializeGrid();
    };

    // Returns the number of tabs
    virtual size_t GetGeneratorTabCount() const;

    // Returns the tab name corresponding to the index
    virtual const CString GetGeneratorTabName(size_t Index);

    // Called by the framework to request a grid to be filled
    // The implementation uses the delegation
    virtual bool FillGrid(CGXGridCore& GridCore, size_t Index);

    // Report identifier methods
    virtual void SetReportTypeID(int TypeID);
    virtual int GetReportTypeID() const;
    virtual const CString GetReportTitle() const;

    // Refresh report methods
    virtual bool IsReportDataExternal() const;
    virtual bool ReportDataMustBeReloaded() const;
    virtual bool UseAutomaticReload() const;

    // Call-back methods
    virtual void OnPreDataFilled(size_t Index);
    virtual void OnPostDataFilled(size_t Index);

    virtual bool OnPostInitialized(CGXTabWndMgr* pMgr, CGXAppAdapter* pAppAdapt, bool NewFile);

    // Reload all tab names from the generator
    bool SetAllTabNameToGrid();

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDGridReportDocument)
public:
    virtual void WorkBookSerialize(CArchive& ar);
    //}}AFX_VIRTUAL

    virtual BOOL OnOpenDocument(LPCTSTR pszPathName);

    // Implementation
public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
protected:

    //{{AFX_MSG(ZDGridReportDocument)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    // Used to initialize the grid using the generator
    virtual bool InitializeGenerator();
    virtual bool InitializeGrid();

private:
    PSS_GenericGridReportGenerator* m_pGenerator;
    bool                            m_ViewRequireDataRefresh;
};

#endif
