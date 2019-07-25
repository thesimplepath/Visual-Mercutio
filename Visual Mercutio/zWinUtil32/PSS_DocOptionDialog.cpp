/****************************************************************************
 * ==> PSS_DocOptionDialog -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a document options dialog box                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DocOptionDialog.h"

// processsoft
#include "zBaseLib\MsgBox.h"
#include "zBaseLib\FileDlg.h"
#ifdef _WIN32
    #include "Opendird32.h"
#else
    #include "Opendird.h"
#endif

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DocOptionDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_DocOptionDialog)
    ON_WM_PAINT()
    ON_BN_CLICKED(IDC_SYNCHRONIZATION, OnClicked)
    ON_BN_CLICKED(IDC_SYNCHRONIZATION2, OnClicked)
    ON_BN_CLICKED(IDC_EMPTYSTYLES, OnClicked)
    ON_BN_CLICKED(IDC_EMPTYSTYLES2, OnClicked)
    ON_BN_CLICKED(IDC_EMPTYSTYLES3, OnClicked)
    ON_BN_CLICKED(IDC_EMPTYSTYLES4, OnClicked)
    ON_BN_CLICKED(IDC_EMPTYSTYLES5, OnClicked)
    ON_BN_CLICKED(IDC_AUTOMATICFILENAME, OnClicked)
    ON_BN_CLICKED(IDC_AUTOMATICFILENAME2, OnClicked)
    ON_BN_CLICKED(IDC_AUTOMATICFILENAME3, OnClicked)
    ON_BN_CLICKED(IDC_SELECT_FLF, OnSelectFLF)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DocOptionDialog
//---------------------------------------------------------------------------
PSS_DocOptionDialog::PSS_DocOptionDialog(ZDDocumentOptions* pDocOptions, CWnd* pParent) :
    CDialog(PSS_DocOptionDialog::IDD, pParent),
    m_pDocOptions(pDocOptions),
    m_EmptyStyle(-1),
    m_SynchronisationYesNo(-1),
    m_ShowHiddenFieldYesNoDoc(-1),
    m_ShowEmptyLineYesNoDoc(-1),
    m_SynchronizationTime(0),
    m_GenerateHeader(-1),
    m_SeparatorType(-1),
    m_AutomaticFileNameGeneration(-1),
    m_PrintEmptyStyleWhenEmpty(FALSE)
{
    switch (m_pDocOptions->GetEmptyStyle())
    {
        case E_LT_Dotted: m_EmptyStyle = 1; break;
        case E_LT_Small:  m_EmptyStyle = 2; break;
        case E_LT_Dash:   m_EmptyStyle = 3; break;
        case E_LT_Solid:  m_EmptyStyle = 4; break;
        default:          m_EmptyStyle = 0;
    }

    switch (m_pDocOptions->GetShowEmptyLine())
    {
        case E_OT_Yes: m_ShowEmptyLineYesNoDoc = 0; break;
        case E_OT_No:  m_ShowEmptyLineYesNoDoc = 1; break;
        default:       m_ShowEmptyLineYesNoDoc = 2;
    }

    m_PrintEmptyStyleWhenEmpty = m_pDocOptions->GetPrintEmptyStyleWhenEmpty();

    switch (m_pDocOptions->GetShowHiddenField())
    {
        case E_OT_Yes: m_ShowHiddenFieldYesNoDoc = 0; break;
        case E_OT_No:  m_ShowHiddenFieldYesNoDoc = 1; break;
        default:       m_ShowHiddenFieldYesNoDoc = 2;
    }

    if (m_pDocOptions->GetIsSynchronizeExchangeFeedFile())
        m_SynchronisationYesNo = 0;
    else
        m_SynchronisationYesNo = 1;

    m_SynchronizationTime = m_pDocOptions->GetSynchronizeTimeSequence();
    m_FLF_FileName        = m_pDocOptions->GetSynchronizeFilename();

    switch (m_pDocOptions->GetAutomaticSynchronizeFilename())
    {
        case E_ST_FileNameSpecified: m_AutomaticFileNameGeneration = 1; break;
        case E_ST_FolderSpecified:   m_AutomaticFileNameGeneration = 2; break;
        default:                     m_AutomaticFileNameGeneration = 0;
    }

    m_GenerateHeader = (m_pDocOptions->GetSynchronizationHeader() == TRUE) ? 0 : 1;

    switch (m_pDocOptions->GetSynchronizationSeparator())
    {
        case E_SS_Tab:        m_SeparatorType = 1; break;
        case E_SS_Comma:      m_SeparatorType = 2; break;
        case E_SS_SemiColumn: m_SeparatorType = 3; break;
        case E_SS_Quote:      m_SeparatorType = 4; break;
        default:              m_SeparatorType = 0;
    }
}
//---------------------------------------------------------------------------
void PSS_DocOptionDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_DocOptionDialog)
    DDX_Control(pDX, IDC_SMALLLINE,         m_SmallLineCtrl);
    DDX_Control(pDX, IDC_DASHEDLINE,        m_DashedLineCtrl);
    DDX_Control(pDX, IDC_POINT,             m_DottedCtrl);
    DDX_Control(pDX, IDC_LINED,             m_LinedCtrl);
    DDX_Radio  (pDX, IDC_EMPTYSTYLES,       m_EmptyStyle);
    DDX_Radio  (pDX, IDC_SYNCHRONIZATION,   m_SynchronisationYesNo);
    DDX_Radio  (pDX, IDC_HIDDENFIELDS_SHOW, m_ShowHiddenFieldYesNoDoc);
    DDX_Radio  (pDX, IDC_SHOWEMPTYLINE,     m_ShowEmptyLineYesNoDoc);
    DDX_Text   (pDX, IDC_SYNCHRO_TIME,      m_SynchronizationTime);
    DDX_Text   (pDX, IDC_FLF_FILENAME,      m_FLF_FileName);
    DDX_Radio  (pDX, IDC_HEADER,            m_GenerateHeader);
    DDX_Radio  (pDX, IDC_SEPARATOR,         m_SeparatorType);
    DDX_Radio  (pDX, IDC_AUTOMATICFILENAME, m_AutomaticFileNameGeneration);
    DDX_Check  (pDX, IDC_PRINTEMPTYLINE,    m_PrintEmptyStyleWhenEmpty);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------

BOOL PSS_DocOptionDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    CheckControlState();

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DocOptionDialog::OnPaint()
{
    // device context for painting
    CPaintDC dc(this);

    CPen  pen(PS_SOLID, 1, defCOLOR_BLACK);
    CPen* pOldPen;

    pOldPen = dc.SelectObject(&pen);

    // draw the different empty styles
    CRect dashedLineRect, linedRect, pointRect, smallLineRect;

    m_DashedLineCtrl.GetClientRect(&dashedLineRect);
    m_DashedLineCtrl.MapWindowPoints(this, &dashedLineRect);

    for (register int i = dashedLineRect.left; i < dashedLineRect.right; i += 4)
    {
        dc.MoveTo(i,     dashedLineRect.bottom - 2);
        dc.LineTo(i + 2, dashedLineRect.bottom - 2);
    }

    m_DottedCtrl.GetClientRect(&pointRect);
    m_DottedCtrl.MapWindowPoints(this, &pointRect);

    for (register int i = pointRect.left; i < pointRect.right; i += 2)
    {
        dc.MoveTo(i,     pointRect.bottom - 2);
        dc.LineTo(i + 1, pointRect.bottom - 2);
    }

    m_SmallLineCtrl.GetClientRect(&smallLineRect);
    m_SmallLineCtrl.MapWindowPoints(this, &smallLineRect);

    for (register int i = smallLineRect.left; i < smallLineRect.right; i += 8)
    {
        dc.MoveTo(i,     smallLineRect.bottom - 2);
        dc.LineTo(i + 4, smallLineRect.bottom - 2);
    }

    m_LinedCtrl.GetClientRect(&linedRect);
    m_LinedCtrl.MapWindowPoints(this, &linedRect);
    dc.MoveTo(linedRect.left,  linedRect.bottom - 2);
    dc.LineTo(linedRect.right, linedRect.bottom - 2);
}
//---------------------------------------------------------------------------
void PSS_DocOptionDialog::OnClicked()
{
    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_DocOptionDialog::OnSelectFLF()
{
    switch (m_AutomaticFileNameGeneration)
    {
        case 2:
        {
            ZIOpenDirDlg dlgDirectory;

            if (dlgDirectory.ProcessDirectory() != "")
            {
                m_FLF_FileName = dlgDirectory.GetDirectory();
                UpdateData(FALSE);
            }

            break;
        }

        case 1:
        {
            CString file;
            file.LoadString(IDS_DOCUMENTFEEDFILTER);
            file = "*" + file;

            CString title;
            VERIFY(title.LoadString(IDS_FEEDFILE_CHOOSETITLE));

            CString filter;

            // set the first file filter
            VERIFY(filter.LoadString(IDS_FEEDFILE_FILTERTXT));
            filter += (char)'\0';
            filter += file;
            filter += (char)'\0';

            CString allFilter;

            // append the "*.*" all files filter
            VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
            filter += allFilter;
            filter += (char)'\0';
            filter += "*.*";
            filter += (char)'\0';

            ZIFileDialog fileDialog(title, filter, 2);

            if (fileDialog.DoModal() == IDOK)
            {
                m_FLF_FileName = fileDialog.GetFilename();
                UpdateData(FALSE);
            }

            break;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_DocOptionDialog::OnOK()
{
    UpdateData(TRUE);

    if (m_SynchronizationTime < 0 || m_SynchronizationTime > 9999)
    {
        // do not accept this range
        ::MsgBox mbox;
        mbox.DisplayMsgBox(IDS_SYNCHRO_TIMERANGE, MB_OK);
        return;
    }

    CDialog::OnOK();

    switch (m_EmptyStyle)
    {
        case 1:  m_pDocOptions->SetEmptyStyle(E_LT_Dotted); break;
        case 2:  m_pDocOptions->SetEmptyStyle(E_LT_Small);  break;
        case 3:  m_pDocOptions->SetEmptyStyle(E_LT_Dash);   break;
        case 4:  m_pDocOptions->SetEmptyStyle(E_LT_Solid);  break;
        default: m_pDocOptions->SetEmptyStyle(E_LT_No);
    }

    switch (m_ShowEmptyLineYesNoDoc)
    {
        case 0:  m_pDocOptions->SetShowEmptyLine(E_OT_Yes);         break;
        case 1:  m_pDocOptions->SetShowEmptyLine(E_OT_No);          break;
        case 2:  m_pDocOptions->SetShowEmptyLine(E_OT_Application); break;
        default: m_pDocOptions->SetShowEmptyLine(E_OT_Application);
    }

    m_pDocOptions->SetPrintEmptyStyleWhenEmpty(m_PrintEmptyStyleWhenEmpty);

    switch (m_ShowHiddenFieldYesNoDoc)
    {
        case 0:  m_pDocOptions->SetShowHiddenField(E_OT_Yes);         break;
        case 1:  m_pDocOptions->SetShowHiddenField(E_OT_No);          break;
        case 2:  m_pDocOptions->SetShowHiddenField(E_OT_Application); break;
        default: m_pDocOptions->SetShowHiddenField(E_OT_Application);
    }

    if (!m_SynchronisationYesNo)
        m_pDocOptions->SetIsSynchronizeExchangeFeedFile(TRUE);
    else
        m_pDocOptions->SetIsSynchronizeExchangeFeedFile(FALSE);

    m_pDocOptions->SetSynchronizeTimeSequence(m_SynchronizationTime);
    m_pDocOptions->SetSynchronizeFilename(m_FLF_FileName);

    switch (m_AutomaticFileNameGeneration)
    {
        case 1:  m_pDocOptions->SetAutomaticSynchronizeFilename(E_ST_FileNameSpecified); break;
        case 2:  m_pDocOptions->SetAutomaticSynchronizeFilename(E_ST_FolderSpecified);   break;
        default: m_pDocOptions->SetAutomaticSynchronizeFilename(E_ST_AutomaticName);
    }

    if (!m_GenerateHeader)
        m_pDocOptions->SetSynchronizationHeader(TRUE);
    else
        m_pDocOptions->SetSynchronizationHeader(FALSE);

    switch (m_SeparatorType)
    {
        case 1:  m_pDocOptions->SetSynchronizationSeparator(E_SS_Tab);        break;
        case 2:  m_pDocOptions->SetSynchronizationSeparator(E_SS_Comma);      break;
        case 3:  m_pDocOptions->SetSynchronizationSeparator(E_SS_SemiColumn); break;
        case 4:  m_pDocOptions->SetSynchronizationSeparator(E_SS_Quote);      break;
        default: m_pDocOptions->SetSynchronizationSeparator(E_SS_Automatic);
    }
}
//---------------------------------------------------------------------------
void PSS_DocOptionDialog::CheckControlState()
{
    UpdateData(TRUE);

    // check control states for empty style
    if (GetDlgItem(IDC_EMPTYLINE_STATIC))
        GetDlgItem(IDC_EMPTYLINE_STATIC)->ShowWindow(!m_EmptyStyle ? SW_SHOW : SW_HIDE);

    if (GetDlgItem(IDC_SHOWEMPTYLINE))
        GetDlgItem(IDC_SHOWEMPTYLINE)->ShowWindow(!m_EmptyStyle ? SW_SHOW : SW_HIDE);

    if (GetDlgItem(IDC_SHOWEMPTYLINE2))
        GetDlgItem(IDC_SHOWEMPTYLINE2)->ShowWindow(!m_EmptyStyle ? SW_SHOW : SW_HIDE);

    // check control states for synchronization
    if (GetDlgItem(IDC_STATIC_TIME))
        GetDlgItem(IDC_STATIC_TIME)->EnableWindow(!m_SynchronisationYesNo);

    if (GetDlgItem(IDC_SYNCHRO_TIME))
        GetDlgItem(IDC_SYNCHRO_TIME)->EnableWindow(!m_SynchronisationYesNo);

    if (GetDlgItem(IDC_STATIC_FILE))
        GetDlgItem(IDC_STATIC_FILE)->ShowWindow(!m_SynchronisationYesNo ? SW_SHOW : SW_HIDE);

    if (GetDlgItem(IDC_AUTOMATICFILENAME))
        GetDlgItem(IDC_AUTOMATICFILENAME)->ShowWindow(!m_SynchronisationYesNo ? SW_SHOW : SW_HIDE);

    if (GetDlgItem(IDC_AUTOMATICFILENAME2))
        GetDlgItem(IDC_AUTOMATICFILENAME2)->ShowWindow(!m_SynchronisationYesNo ? SW_SHOW : SW_HIDE);

    if (GetDlgItem(IDC_AUTOMATICFILENAME3))
        GetDlgItem(IDC_AUTOMATICFILENAME3)->ShowWindow(!m_SynchronisationYesNo ? SW_SHOW : SW_HIDE);
       
    if (GetDlgItem(IDC_FLF_FILENAME))
        GetDlgItem(IDC_FLF_FILENAME)->ShowWindow(!m_AutomaticFileNameGeneration ? SW_HIDE : SW_SHOW);

    if (GetDlgItem(IDC_SELECT_FLF))
        GetDlgItem(IDC_SELECT_FLF)->ShowWindow(!m_AutomaticFileNameGeneration ? SW_HIDE : SW_SHOW);
}
//---------------------------------------------------------------------------
