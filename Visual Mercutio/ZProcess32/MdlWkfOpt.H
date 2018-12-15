// MdlWkfOpt.h : header file

#ifndef MdlWkfOpt_h
#define MdlWkfOpt_h 1

#include "zBaseLib\ZWizard.h"
#include "zWinUtil32\ZCLanguageCombo.h"
#include "Resource.h"

// JMR-MODIF - Le 18 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Forward declaration
class ZDProcessGraphModelDoc;

// Dialogs' data
typedef struct _ModelOptionData
{
    BOOL        m_Modify;
    BOOL        m_CheckConsistency;
    BOOL        m_IntegrateCostSimulation;
    BOOL        m_UseModelAsWorkflow;
    BOOL        m_BrowseInSameModel;
    int            m_Notation;
    int            m_HourPerDay;
    int            m_DayPerWeek;
    int            m_DayPerMonth;
    int            m_DayPerYear;
    CString        m_CurrencySymbol;
    Language    m_Language;
} MODELOPTIONDATA;

/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowOptions class

class ZVModelWorkflowOptions
{
// Construction
public:

    // standard constructor
    ZVModelWorkflowOptions( BOOL Modify, ZDProcessGraphModelDoc* pDoc, CWnd* pParent = NULL );

    // Get methods
    Language GetLanguage() const
    {
        return m_Data.m_Language;
    }

    int DoModal();

private:

    ZDProcessGraphModelDoc* m_pDoc;
    BOOL                    m_Modify;
    MODELOPTIONDATA            m_Data;
};

/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowOptionsNotation dialog

class ZVModelWorkflowOptionsNotation : public ZIWizardDialog
{
// Construction
public:

    // standard constructor
    ZVModelWorkflowOptionsNotation( MODELOPTIONDATA& Data, CWnd* pParent = NULL );
    virtual ~ZVModelWorkflowOptionsNotation(); // standard destructor

    // Dialog Data
    //{{AFX_DATA(ZVModelWorkflowOptionsNotation)
    enum { IDD = IDD_WZ_MODELTYPE_NOTATION };
    int        m_Notation;
    //}}AFX_DATA

// Implementation
protected:

    // DDX/DDV support
    virtual void DoDataExchange( CDataExchange* pDX );

    // Generated message map functions
    //{{AFX_MSG(ZVModelWorkflowOptionsNotation)
    virtual void OnOK();
    afx_msg void OnNext();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    void SaveToData();

private:

    MODELOPTIONDATA& m_Data;
};

/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowOptionsOptions dialog

class ZVModelWorkflowOptionsOptions : public ZIWizardDialog
{
// Construction
public:

    // standard constructor
    ZVModelWorkflowOptionsOptions( MODELOPTIONDATA& Data, CWnd* pParent = NULL );
    virtual ~ZVModelWorkflowOptionsOptions(); // standard destructor

private:

    // Dialog Data
    //{{AFX_DATA(ZVModelWorkflowOptionsOptions)
    enum { IDD = IDD_WZ_MODELTYPE_OPTIONS };
    ZCLanguageCombo    m_cbLanguage;
    BOOL    m_CheckConsistency;
    BOOL    m_IntegrateCostSimulation;
    BOOL    m_UseModelAsWorkflow;
    BOOL    m_BrowseInSameModel;
    //}}AFX_DATA

// Implementation
protected:

    // DDX/DDV support
    virtual void DoDataExchange( CDataExchange* pDX );

    // Generated message map functions
    //{{AFX_MSG(ZVModelWorkflowOptionsOptions)
    virtual void OnOK();
    afx_msg void OnNext();
    virtual BOOL OnInitDialog();
    afx_msg void OnIntegrateCostsimulation();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    void SaveToData();
    void CheckStates();

private:

    MODELOPTIONDATA& m_Data;
};

/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowOptionsCosts dialog

class ZVModelWorkflowOptionsCosts : public ZIWizardDialog
{
// Construction
public:

    // standard constructor
    ZVModelWorkflowOptionsCosts( MODELOPTIONDATA& Data, CWnd* pParent = NULL );

private:

    // Dialog Data
    //{{AFX_DATA(ZVModelWorkflowOptionsCosts)
    enum { IDD = IDD_WZ_MODELTYPE_COSTOPT };
    CComboBox    m_CurrencySymbol;
    CString    m_DayPerMonth;
    CString    m_DayPerWeek;
    CString    m_DayPerYear;
    CString    m_HourPerDay;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVModelWorkflowOptionsCosts)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVModelWorkflowOptionsCosts)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnNext();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    void SaveToData();
    bool CheckData();

private:

    MODELOPTIONDATA& m_Data;
};

#endif    // MdlWkfOpt_h
