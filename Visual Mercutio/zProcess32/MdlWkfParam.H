// MdlWkfParam.h : header file
//

#ifndef MdlWkfParam_h
#define MdlWkfParam_h 1


#include "zBaseLib\PSS_FolderStamp.h"
#include "zBaseLib\PSS_WizardDialog.h"

#include "Resource.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// forward class declaration
class PSS_ProcessGraphModelDoc;
class PSS_TemplateManager;

/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowParameters class

class ZVModelWorkflowParameters
{
// Construction
public:
    ZVModelWorkflowParameters(BOOL Modify, PSS_ProcessGraphModelDoc* pDoc, PSS_TemplateManager* pTemplateManager, CString FileExtension, CWnd* pParent = NULL);    // standard constructor

    // Get methods
    PSS_FolderStamp&    GetFolderStamp() { return m_FolderStamp; };
    bool            GetCheckConsistency() const { return m_CheckConsistency; };
    bool            GetSaveModelInWorkflow() const { return m_SaveModelInWkfFile; };
    bool            FileChooseExists() const { return m_FileExist; };

    int        DoModal();

private:
    PSS_ProcessGraphModelDoc* m_pDoc;
    BOOL                    m_Modify;
    PSS_TemplateManager*        m_pTemplateManager;
    CString                    m_FileExtension;
// the folder stamp used to save information
    PSS_FolderStamp            m_FolderStamp;
    bool                    m_CheckConsistency;
    bool                    m_SaveModelInWkfFile;
    bool                    m_FileExist;
};





/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowParametersWelcome dialog

class ZVModelWorkflowParametersWelcome : public PSS_WizardDialog
{
// Construction
public:
    ZVModelWorkflowParametersWelcome(CWnd* pParent = NULL);    // standard constructor
    virtual ~ZVModelWorkflowParametersWelcome(); // standard destructor

// Dialog Data
    //{{AFX_DATA(ZVModelWorkflowParametersWelcome)
    enum { IDD = IDD_WZ_MODELWKF_START };
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(ZVModelWorkflowParametersWelcome)
    virtual void OnOK();
    afx_msg void OnNext();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
};





/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowParametersOptions dialog

class ZVModelWorkflowParametersOptions : public PSS_WizardDialog
{
// Construction
public:
    ZVModelWorkflowParametersOptions(BOOL Modify, PSS_ProcessGraphModelDoc& Doc, CWnd* pParent = NULL);    // standard constructor
    virtual ~ZVModelWorkflowParametersOptions(); // standard destructor

    BOOL    GetCheckConsistency() const { return m_CheckConsistency; };
    BOOL    GetSaveModelInWorkflow() const { return m_SaveModelInWkfFile; };

private:
// Dialog Data
    //{{AFX_DATA(ZVModelWorkflowParametersOptions)
    enum { IDD = IDD_WZ_MODELWKF_OPTIONS };
    BOOL    m_CheckConsistency;
    BOOL    m_SaveModelInWkfFile;
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(ZVModelWorkflowParametersOptions)
    virtual void OnOK();
    afx_msg void OnNext();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    PSS_ProcessGraphModelDoc& m_Doc;
    BOOL m_Modify;
};



#endif
