// ZVCommandLineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVCommandLineDlg.h"


#include "zBaseLib\FileDlg.h"
#include "PSS_OpenDirDialog.h"
#include "SysVarDlg.h"

#include "zBaseLib\ZAGlobal.h"

#include "zBaseLib\File.h"

#include "zBaseLib\MsgBox.h"
#include "zRes32\Zres.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVCommandLineDlg dialog


ZVCommandLineDlg::ZVCommandLineDlg(const CString JobName /*= ""*/,
                                   const CString CommandLine /*= ""*/,
                                   const CString Parameters /*= ""*/,
                                   const CString StartupDir /*= ""*/,
                                   int Priority /*= 0*/,
                                   int WindowMode /*= 0*/,
                                   CWnd* pParent /*=NULL*/)
    : CDialog(ZVCommandLineDlg::IDD, pParent),
    m_JobNameHasChanged(false)
{
    //{{AFX_DATA_INIT(ZVCommandLineDlg)
    m_JobName = JobName;
    //}}AFX_DATA_INIT

    m_CommandLine = CommandLine;
    m_Parameters = Parameters;
    m_StartupDir = StartupDir;
    m_Priority = Priority;
    m_WindowMode = WindowMode;

    m_StartupDirectory.SetSearchType(ZSEARCHEDIT_DIRECTORY, "");
    m_Application.SetSearchType(ZSEARCHEDIT_FILE);
    m_Arguments.SetSearchType(ZSEARCHEDIT_POPUP, IDR_ARGUMENTS);

}

void ZVCommandLineDlg::CheckControlState()
{
    // Do nothing
}

BOOL ZVCommandLineDlg::IsOK()
{
    UpdateData();
    CString Text;
    m_Application.GetWindowText( Text );
    if (Text.IsEmpty())
    {
        MsgBox        mbox;
        mbox.DisplayMsgBox( IDS_APPLICATIONMISSING, MB_OK );
        return FALSE;
    }
    return TRUE;
}


void ZVCommandLineDlg::SaveValuesToObject()
{
    // Retreive information
    m_Application.GetWindowText( m_CommandLine );
    m_StartupDirectory.GetWindowText( m_StartupDir );
    m_Arguments.GetWindowText( m_Parameters );

    // Retreive the priority
    int CurSel = m_PriorityList.GetCurSel();
    if (CurSel != LB_ERR)
    {
        CString Text;
        m_PriorityList.GetLBText( CurSel, Text );

        m_Priority = ZAGlobal::GetJobPriority( Text );
    }


    // Retreive the window mode
    CurSel = m_WindowModeList.GetCurSel();
    if (CurSel != LB_ERR)
    {
        CString Text;
        m_WindowModeList.GetLBText( CurSel, Text );

        m_WindowMode = ZAGlobal::GetWindowMode( Text );
    }
}

void ZVCommandLineDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVCommandLineDlg)
    DDX_Control(pDX, IDC_CMD_ARGUMENTS, m_Arguments);
    DDX_Control(pDX, IDC_CMD_PRIORITY, m_PriorityList);
    DDX_Control(pDX, IDC_CMD_WINDOWMODE, m_WindowModeList);
    DDX_Control(pDX, IDC_CMD_STARTUPDIRECTORY, m_StartupDirectory);
    DDX_Control(pDX, IDC_CMD_APPLICATION, m_Application);
    DDX_Text(pDX, IDC_CMD_JOBNAME, m_JobName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(ZVCommandLineDlg, CDialog)
    //{{AFX_MSG_MAP(ZVCommandLineDlg)
    ON_COMMAND(ID_FILE_ARG, OnFileArg)
    ON_COMMAND(ID_DIR_ARG, OnDirArg)
    ON_COMMAND(ID_SYSVAR_ARG, OnSysVarArg)
    ON_EN_CHANGE(IDC_CMD_JOBNAME, OnChangeJobname)
    ON_EN_CHANGE(IDC_CMD_APPLICATION, OnChangeApplication)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
BOOL ZVCommandLineDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_Application.SetWindowText(m_CommandLine);
    m_StartupDirectory.SetWindowText(m_StartupDir);
    m_Arguments.SetWindowText(m_Parameters);

    std::size_t count = (ZAGlobal::GetArrayJobPriority()) ? ZAGlobal::GetArrayJobPriority()->GetSize() : 0;

    // fill the priority list box
    for (std::size_t i = 0; i < count; ++i)
        m_PriorityList.AddString(ZAGlobal::GetArrayJobPriority()->GetAt(i));

    count = (ZAGlobal::GetArrayWindowMode()) ? ZAGlobal::GetArrayWindowMode()->GetSize() : 0;

    // fill the window mode list box
    for (std::size_t i = 0; i < count; ++i)
        m_WindowModeList.AddString(ZAGlobal::GetArrayWindowMode()->GetAt(i));

    // set the right job priority
    m_PriorityList.SelectString(-1, ZAGlobal::GetJobPriorityString(m_Priority));

    // set the right window mode
    m_WindowModeList.SelectString(-1, ZAGlobal::GetWindowModeString(m_WindowMode));
        
    UpdateData(FALSE);
    CheckControlState();

    // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void ZVCommandLineDlg::OnFileArg()
{
    CString title;
    VERIFY(title.LoadString(IDS_SELECT_A_FILE));

    // set the "*.*" files filter
    CString strFilter;
    VERIFY(strFilter.LoadString(AFX_IDS_ALLFILTER));
    strFilter += (char)'\0';        // next string please
    strFilter += "*.*";
    strFilter += (char)'\0';        // last string

    ZIFileDialog    FileDialog( title, strFilter, 1 );
    if (FileDialog.DoModal() == IDOK)
    {
        CString Text;
        m_Arguments.GetWindowText( Text );
        if (!Text.IsEmpty())
            Text += " ";
        Text += FileDialog.GetFilename();
        m_Arguments.SetWindowText( Text );
    }
}

void ZVCommandLineDlg::OnDirArg()
{
    PSS_OpenDirDialog openDirDialog;
    
    if (openDirDialog.ProcessDirectory() != "")
    {
        CString Text;
        m_Arguments.GetWindowText( Text );
        if (!Text.IsEmpty())
            Text += " ";
        Text += openDirDialog.GetDirectory();
        m_Arguments.SetWindowText( Text );
    }
}

void ZVCommandLineDlg::OnSysVarArg()
{
    ZISysVarDlg    SysVarDlg;

    
    if (SysVarDlg.DoModal() == IDOK)
    {
        CString Text;
        m_Arguments.GetWindowText( Text );
        if (!Text.IsEmpty())
            Text += " ";
        Text += SysVarDlg.GetKeyword();
        m_Arguments.SetWindowText( Text );
    }
}



void ZVCommandLineDlg::OnOK()
{
    if (IsOK())
    {
        SaveValuesToObject();
        CDialog::OnOK();
    }
}



void ZVCommandLineDlg::OnChangeJobname() 
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.
    
    m_JobNameHasChanged = true;
    
}

void ZVCommandLineDlg::OnChangeApplication() 
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.
    
    if (m_JobNameHasChanged == false)
    {
        m_Application.GetWindowText( m_CommandLine );
        
        if (!m_CommandLine.IsEmpty())
        {
            ZFile file(m_CommandLine);
            m_JobName = file.GetDisplayName();
            // If it is not empty, Update the control data
            if (!m_JobName.IsEmpty())
                UpdateData(FALSE);
        }
    }
}
