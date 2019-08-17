/****************************************************************************
 * ==> PSS_CommandLineDialog -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a command line dialog box                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_CommandLineDialog.h"

// processsoft
#include "zBaseLib\PSS_FileDialog.h"
#include "zBaseLib\ZAGlobal.h"
#include "zBaseLib\PSS_File.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "PSS_OpenDirDialog.h"
#include "PSS_SysVarDialog.h"

// resources
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_CommandLineDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_CommandLineDialog)
    ON_COMMAND(ID_FILE_ARG, OnFileArg)
    ON_COMMAND(ID_DIR_ARG, OnDirArg)
    ON_COMMAND(ID_SYSVAR_ARG, OnSysVarArg)
    ON_EN_CHANGE(IDC_CMD_JOBNAME, OnChangeJobName)
    ON_EN_CHANGE(IDC_CMD_APPLICATION, OnChangeApplication)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
PSS_CommandLineDialog::PSS_CommandLineDialog(const CString& jobName,
                                             const CString& commandLine,
                                             const CString& parameters,
                                             const CString& startupDir,
                                             int            priority,
                                             int            windowMode,
                                             CWnd*          pParent) :
    CDialog(PSS_CommandLineDialog::IDD, pParent),
    m_JobName(jobName),
    m_CommandLine(commandLine),
    m_Parameters(parameters),
    m_StartupDir(startupDir),
    m_Priority(priority),
    m_WindowMode(windowMode),
    m_JobNameHasChanged(false)
{
    m_StartupDirectory.SetSearchType(PSS_SearchEditButton::IE_T_Directory, "");
    m_Application.SetSearchType(PSS_SearchEditButton::IE_T_File);
    m_Arguments.SetSearchType(PSS_SearchEditButton::IE_T_Popup, IDR_ARGUMENTS);
}
//---------------------------------------------------------------------------
void PSS_CommandLineDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_CommandLineDialog)
    DDX_Control(pDX, IDC_CMD_ARGUMENTS,        m_Arguments);
    DDX_Control(pDX, IDC_CMD_PRIORITY,         m_PriorityList);
    DDX_Control(pDX, IDC_CMD_WINDOWMODE,       m_WindowModeList);
    DDX_Control(pDX, IDC_CMD_STARTUPDIRECTORY, m_StartupDirectory);
    DDX_Control(pDX, IDC_CMD_APPLICATION,      m_Application);
    DDX_Text   (pDX, IDC_CMD_JOBNAME,          m_JobName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_CommandLineDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_Application.SetWindowText(m_CommandLine);
    m_StartupDirectory.SetWindowText(m_StartupDir);
    m_Arguments.SetWindowText(m_Parameters);

    std::size_t count = (ZAGlobal::GetArrayJobPriority()) ? ZAGlobal::GetArrayJobPriority()->GetSize() : 0;

    // fill the priority list box
    for (std::size_t i = 0; i < count; ++i)
        m_PriorityList.AddString(ZAGlobal::GetArrayJobPriority()->GetAt(i));

    count = (ZAGlobal::GetArrayWindowMode() ? ZAGlobal::GetArrayWindowMode()->GetSize() : 0);

    // fill the window mode list box
    for (std::size_t i = 0; i < count; ++i)
        m_WindowModeList.AddString(ZAGlobal::GetArrayWindowMode()->GetAt(i));

    // set the right job priority
    m_PriorityList.SelectString(-1, ZAGlobal::GetJobPriorityString(m_Priority));

    // set the right window mode
    m_WindowModeList.SelectString(-1, ZAGlobal::GetWindowModeString(m_WindowMode));

    UpdateData(FALSE);
    CheckControlState();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_CommandLineDialog::OnOK()
{
    if (IsOK())
    {
        SaveValuesToObject();
        CDialog::OnOK();
    }
}
//---------------------------------------------------------------------------
void PSS_CommandLineDialog::OnFileArg()
{
    CString title;
    VERIFY(title.LoadString(IDS_SELECT_A_FILE));

    CString strFilter;

    // set the "*.*" files filter
    VERIFY(strFilter.LoadString(AFX_IDS_ALLFILTER));
    strFilter += (char)'\0';
    strFilter += "*.*";
    strFilter += (char)'\0';

    PSS_FileDialog fileDialog(title, strFilter, 1);

    if (fileDialog.DoModal() == IDOK)
    {
        CString text;
        m_Arguments.GetWindowText(text);

        if (!text.IsEmpty())
            text += " ";

        text += fileDialog.GetFileName();
        m_Arguments.SetWindowText(text);
    }
}
//---------------------------------------------------------------------------
void PSS_CommandLineDialog::OnDirArg()
{
    PSS_OpenDirDialog openDirDialog;

    if (openDirDialog.ProcessDirectory() != "")
    {
        CString text;
        m_Arguments.GetWindowText(text);

        if (!text.IsEmpty())
            text += " ";

        text += openDirDialog.GetDirectory();
        m_Arguments.SetWindowText(text);
    }
}
//---------------------------------------------------------------------------
void PSS_CommandLineDialog::OnSysVarArg()
{
    PSS_SysVarDialog sysVarDialog;

    if (sysVarDialog.DoModal() == IDOK)
    {
        CString text;
        m_Arguments.GetWindowText(text);

        if (!text.IsEmpty())
            text += " ";

        text += sysVarDialog.GetKeyword();
        m_Arguments.SetWindowText(text);
    }
}
//---------------------------------------------------------------------------
void PSS_CommandLineDialog::OnChangeJobName()
{
    // todo -cFeature -oJean: if this is a RICHEDIT control, it will not send this notification unless overridding
    //                        the ZIDialog::OnInitDialog() function and calling CRichEditCtrl().SetEventMask()
    //                        with the ENM_CHANGE flag set in the mask
    m_JobNameHasChanged = true;
}
//---------------------------------------------------------------------------
void PSS_CommandLineDialog::OnChangeApplication()
{
    // todo -cFeature -oJean: if this is a RICHEDIT control, it will not send this notification unless overridding
    //                        the ZIDialog::OnInitDialog() function and calling CRichEditCtrl().SetEventMask()
    //                        with the ENM_CHANGE flag set in the mask
    if (!m_JobNameHasChanged)
        return;

    m_Application.GetWindowText(m_CommandLine);

    if (m_CommandLine.IsEmpty())
        return;

    PSS_File file(m_CommandLine);
    m_JobName = file.GetDisplayName();

    // if not empty, update the control data
    if (!m_JobName.IsEmpty())
        UpdateData(FALSE);
}
//---------------------------------------------------------------------------
BOOL PSS_CommandLineDialog::IsOK()
{
    UpdateData();

    CString text;
    m_Application.GetWindowText(text);

    if (text.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.ShowMsgBox(IDS_APPLICATIONMISSING, MB_OK);

        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_CommandLineDialog::SaveValuesToObject()
{
    // get information
    m_Application.GetWindowText(m_CommandLine);
    m_StartupDirectory.GetWindowText(m_StartupDir);
    m_Arguments.GetWindowText(m_Parameters);

    // get the priority
    int curSel = m_PriorityList.GetCurSel();

    if (curSel != LB_ERR)
    {
        CString text;
        m_PriorityList.GetLBText(curSel, text);

        m_Priority = ZAGlobal::GetJobPriority(text);
    }

    // get the window mode
    curSel = m_WindowModeList.GetCurSel();

    if (curSel != LB_ERR)
    {
        CString text;
        m_WindowModeList.GetLBText(curSel, text);

        m_WindowMode = ZAGlobal::GetWindowMode(text);
    }
}
//---------------------------------------------------------------------------
void PSS_CommandLineDialog::CheckControlState()
{}
//---------------------------------------------------------------------------
