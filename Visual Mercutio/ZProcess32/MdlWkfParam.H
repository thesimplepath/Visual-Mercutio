// MdlWkfParam.h : header file
//

#ifndef MdlWkfParam_h
#define MdlWkfParam_h 1


#include "zBaseLib\FldStamp.h"
#include "zBaseLib\ZWizard.h"

#include "Resource.h"

// Forward declaration
class ZDProcessGraphModelDoc;
class ZDTemplateManager;

/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowParameters class

class ZVModelWorkflowParameters
{
// Construction
public:
    ZVModelWorkflowParameters(BOOL Modify, ZDProcessGraphModelDoc* pDoc, ZDTemplateManager* pTemplateManager, CString FileExtension, CWnd* pParent = NULL);    // standard constructor

    // Get methods
    ZDFolderStamp&    GetFolderStamp() { return m_FolderStamp; };
    bool            GetCheckConsistency() const { return m_CheckConsistency; };
    bool            GetSaveModelInWorkflow() const { return m_SaveModelInWkfFile; };
    bool            FileChooseExists() const { return m_FileExist; };

    int        DoModal();

private:
    ZDProcessGraphModelDoc* m_pDoc;
    BOOL                    m_Modify;
    ZDTemplateManager*        m_pTemplateManager;
    CString                    m_FileExtension;
// the folder stamp used to save information
    ZDFolderStamp            m_FolderStamp;
    bool                    m_CheckConsistency;
    bool                    m_SaveModelInWkfFile;
    bool                    m_FileExist;
};





/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowParametersWelcome dialog

class ZVModelWorkflowParametersWelcome : public ZIWizardDialog
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

class ZVModelWorkflowParametersOptions : public ZIWizardDialog
{
// Construction
public:
    ZVModelWorkflowParametersOptions(BOOL Modify, ZDProcessGraphModelDoc& Doc, CWnd* pParent = NULL);    // standard constructor
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
    ZDProcessGraphModelDoc& m_Doc;
    BOOL m_Modify;
};



#endif
