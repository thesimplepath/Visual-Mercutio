// docoptdg.cpp : implementation file
//

#include "stdafx.h"

#include "DocOptDG.h"
#include "zBaseLib\MsgBox.h"
#ifndef _WIN32
	#include "Opendird.h"
#endif
#ifdef _WIN32
	#include "Opendird32.h"
#endif
#include "zBaseLib\FileDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZADocOptionDLG dialog


ZADocOptionDLG::ZADocOptionDLG(ZDDocumentOptions* pDocOptions, CWnd* pParent /*=NULL*/)
	: CDialog(ZADocOptionDLG::IDD, pParent), m_pDocOptions( pDocOptions )
{
	//{{AFX_DATA_INIT(ZADocOptionDLG)
	m_EmtyStyle = -1;
	m_SynchronisationYesNo = -1;
	m_ShowHiddenFieldYesNoDoc = -1;
	m_ShowEmptyLineYesNoDoc = -1;
	m_SynchronizationTime = 0;
	m_FLF_Filename = "";
	m_GenerateHeader = -1;
	m_SeparatorType = -1;
	m_AutomaticFilenameGeneration = -1;
	m_PrintEmptyStyleWhenEmpty = FALSE;
	//}}AFX_DATA_INIT
	switch (m_pDocOptions->GetEmptyStyle())
	{
		case DottedLine : 		m_EmtyStyle = 1;
								break;
		case SmallLine :		m_EmtyStyle = 2;
								break;
		case DashLine : 		m_EmtyStyle = 3;
								break;
		case SolidLine : 		m_EmtyStyle = 4;
								break;
//		Nothing (NoEmpty) and default is m_EmtyStyle = 0;
		default: m_EmtyStyle = 0;
	}
	
	switch (m_pDocOptions->GetShowEmptyLine())
	{
		case YesOption : 		m_ShowEmptyLineYesNoDoc = 0;
								break;
		case NoOption :			m_ShowEmptyLineYesNoDoc = 1;
								break;
		case ApplicationOption : 	m_ShowEmptyLineYesNoDoc = 2;
									break;
		default: m_ShowEmptyLineYesNoDoc = 2;
	}

	m_PrintEmptyStyleWhenEmpty = m_pDocOptions->GetPrintEmptyStyleWhenEmpty();

	switch (m_pDocOptions->GetShowHiddenField())
	{
		case YesOption : 		m_ShowHiddenFieldYesNoDoc = 0;
								break;
		case NoOption :			m_ShowHiddenFieldYesNoDoc = 1;
								break;
		case ApplicationOption : 	m_ShowHiddenFieldYesNoDoc = 2;
									break;
		default: m_ShowHiddenFieldYesNoDoc = 2;
	}

	if (m_pDocOptions->GetIsSynchronizeExchangeFeedFile())
		m_SynchronisationYesNo = 0;
	else
		m_SynchronisationYesNo = 1;

	m_SynchronizationTime = m_pDocOptions->GetSynchronizeTimeSequence();
	
	m_FLF_Filename = m_pDocOptions->GetSynchronizeFilename();
	
	switch (m_pDocOptions->GetAutomaticSynchronizeFilename())
	{
		case AutomaticName : 		m_AutomaticFilenameGeneration = 0;
							 		break;
		case FilenameSpecified :	m_AutomaticFilenameGeneration = 1;
									break;
		case FolderSpecified : 		m_AutomaticFilenameGeneration = 2;
									break;
		default: m_AutomaticFilenameGeneration = 0;
	}
	
	
	m_GenerateHeader = (m_pDocOptions->GetSynchronizationHeader() == TRUE ) ? 0 : 1;

	switch (m_pDocOptions->GetSynchronizationSeparator())
	{
		case AutomaticSeparator : 	m_SeparatorType = 0;
							 		break;
		case TabSeparator :			m_SeparatorType = 1;
									break;
		case CommaSeparator : 		m_SeparatorType = 2;
									break;
		case SemiColumnSeparator :	m_SeparatorType = 3;
									break;
		case QuoteSeparator : 		m_SeparatorType = 4;
									break;
		default: m_SeparatorType = 0;
	}
	
	
	
}

void ZADocOptionDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZADocOptionDLG)
	DDX_Control(pDX, IDC_SMALLLINE, m_SmallLineCtrl);
	DDX_Control(pDX, IDC_DASHEDLINE, m_DashedLineCtrl);
	DDX_Control(pDX, IDC_POINT, m_DottedCtrl);
	DDX_Control(pDX, IDC_LINED, m_LinedCtrl);
	DDX_Radio(pDX, IDC_EMPTYSTYLES, m_EmtyStyle);
	DDX_Radio(pDX, IDC_SYNCHRONIZATION, m_SynchronisationYesNo);
	DDX_Radio(pDX, IDC_HIDDENFIELDS_SHOW, m_ShowHiddenFieldYesNoDoc);
	DDX_Radio(pDX, IDC_SHOWEMPTYLINE, m_ShowEmptyLineYesNoDoc);
	DDX_Text(pDX, IDC_SYNCHRO_TIME, m_SynchronizationTime);
	DDX_Text(pDX, IDC_FLF_FILENAME, m_FLF_Filename);
	DDX_Radio(pDX, IDC_HEADER, m_GenerateHeader);
	DDX_Radio(pDX, IDC_SEPARATOR, m_SeparatorType);
	DDX_Radio(pDX, IDC_AUTOMATICFILENAME, m_AutomaticFilenameGeneration);
	DDX_Check(pDX, IDC_PRINTEMPTYLINE, m_PrintEmptyStyleWhenEmpty);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZADocOptionDLG, CDialog)
	//{{AFX_MSG_MAP(ZADocOptionDLG)
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


/////////////////////////////////////////////////////////////////////////////
// ZADocOptionDLG message handlers

BOOL ZADocOptionDLG::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CheckControlState();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void ZADocOptionDLG::OnOK()
{
	UpdateData( TRUE );
	
	if (m_SynchronizationTime < 0 || m_SynchronizationTime > 9999)
	{          
		// Do not accept this range.
		MsgBox		mbox;
		mbox.DisplayMsgBox( IDS_SYNCHRO_TIMERANGE, MB_OK );
		return;
	}
	CDialog::OnOK();

	switch (m_EmtyStyle)
	{
		case 1: m_pDocOptions->SetEmptyStyle( DottedLine );
				break;
		case 2: m_pDocOptions->SetEmptyStyle( SmallLine );
				break;
		case 3: m_pDocOptions->SetEmptyStyle( DashLine );
				break;
		case 4: m_pDocOptions->SetEmptyStyle( SolidLine );
				break;
//		Nothing (NoEmpty) and default is m_EmtyStyle = 0;
		default: m_pDocOptions->SetEmptyStyle( NoLine );
	}
	
	switch (m_ShowEmptyLineYesNoDoc)
	{
		case 0 : m_pDocOptions->SetShowEmptyLine( YesOption );
 				 break;
		case 1 : m_pDocOptions->SetShowEmptyLine( NoOption );
				 break;
		case 2 : m_pDocOptions->SetShowEmptyLine( ApplicationOption );
				 break;
		default: m_pDocOptions->SetShowEmptyLine( ApplicationOption );
	}

	m_pDocOptions->SetPrintEmptyStyleWhenEmpty( m_PrintEmptyStyleWhenEmpty );

	switch (m_ShowHiddenFieldYesNoDoc)
	{
		case 0 : m_pDocOptions->SetShowHiddenField( YesOption );
 				 break;
		case 1 : m_pDocOptions->SetShowHiddenField( NoOption );
				 break;
		case 2 : m_pDocOptions->SetShowHiddenField( ApplicationOption );
				 break;
		default: m_pDocOptions->SetShowHiddenField( ApplicationOption );
	}

	if (m_SynchronisationYesNo == 0)
		m_pDocOptions->SetIsSynchronizeExchangeFeedFile( TRUE );
	else
		m_pDocOptions->SetIsSynchronizeExchangeFeedFile( FALSE );
	
	m_pDocOptions->SetSynchronizeTimeSequence( m_SynchronizationTime );
	
	
	m_pDocOptions->SetSynchronizeFilename( m_FLF_Filename );
	
	switch (m_AutomaticFilenameGeneration)
	{
		case 1 : 	m_pDocOptions->SetAutomaticSynchronizeFilename( FilenameSpecified );
					break;
		case 2 : 	m_pDocOptions->SetAutomaticSynchronizeFilename( FolderSpecified );
					break;
		case 0 : 	
		default: 	m_pDocOptions->SetAutomaticSynchronizeFilename( AutomaticName );
	}
	
	
	if (m_GenerateHeader == 0)
		m_pDocOptions->SetSynchronizationHeader( TRUE );
	else
		m_pDocOptions->SetSynchronizationHeader( FALSE );

	switch (m_SeparatorType)
	{
		case 1 : 	m_pDocOptions->SetSynchronizationSeparator( TabSeparator );
					break;
		case 2 : 	m_pDocOptions->SetSynchronizationSeparator( CommaSeparator );
					break;
		case 3 : 	m_pDocOptions->SetSynchronizationSeparator( SemiColumnSeparator );
					break;
		case 4 : 	m_pDocOptions->SetSynchronizationSeparator( QuoteSeparator );
					break;
		case 0:
		default: m_pDocOptions->SetSynchronizationSeparator( AutomaticSeparator );
	}
	
}

void ZADocOptionDLG::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CPen	pen( PS_SOLID, 1, defCOLOR_BLACK );
	CPen   *OldPen;
	register i;
		
	OldPen = dc.SelectObject( &pen );

	// Draw the different empty styles
	CRect		DashedLineRect, LinedRect, PointRect, SmallLineRect;

	m_DashedLineCtrl.GetClientRect( &DashedLineRect );
	m_DashedLineCtrl.MapWindowPoints( this, &DashedLineRect );
	for (i = DashedLineRect.left; i < DashedLineRect.right; i += 4)
	{
		dc.MoveTo( i, DashedLineRect.bottom-2 );
		dc.LineTo( i + 2, DashedLineRect.bottom-2 );
	}
	
	m_DottedCtrl.GetClientRect( &PointRect );
	m_DottedCtrl.MapWindowPoints( this, &PointRect );
	for (i = PointRect.left; i < PointRect.right; i += 2)
	{
		dc.MoveTo( i, PointRect.bottom-2 );
		dc.LineTo( i + 1, PointRect.bottom-2 );
	}

	m_SmallLineCtrl.GetClientRect( &SmallLineRect );
	m_SmallLineCtrl.MapWindowPoints( this, &SmallLineRect );
	for (i = SmallLineRect.left; i < SmallLineRect.right; i += 8)
	{
		dc.MoveTo( i, SmallLineRect.bottom-2 );
		dc.LineTo( i + 4, SmallLineRect.bottom-2 );
	}

	m_LinedCtrl.GetClientRect( &LinedRect );
	m_LinedCtrl.MapWindowPoints( this, &LinedRect );
	dc.MoveTo( LinedRect.left, LinedRect.bottom-2 );
	dc.LineTo( LinedRect.right, LinedRect.bottom-2 );
}


void ZADocOptionDLG::CheckControlState()
{
	UpdateData( TRUE );
	// Check control states for empty style
   	if (GetDlgItem(IDC_EMPTYLINE_STATIC) != NULL)
   		GetDlgItem(IDC_EMPTYLINE_STATIC)->ShowWindow( (m_EmtyStyle == 0) ? SW_SHOW : SW_HIDE );

   	if (GetDlgItem(IDC_SHOWEMPTYLINE) != NULL)
   		GetDlgItem(IDC_SHOWEMPTYLINE)->ShowWindow( (m_EmtyStyle == 0) ? SW_SHOW : SW_HIDE );

   	if (GetDlgItem(IDC_SHOWEMPTYLINE2) != NULL)
   		GetDlgItem(IDC_SHOWEMPTYLINE2)->ShowWindow( (m_EmtyStyle == 0) ? SW_SHOW : SW_HIDE );
	
	// Check control states for synchronization
   	if (GetDlgItem(IDC_STATIC_TIME) != NULL)
   		GetDlgItem(IDC_STATIC_TIME)->EnableWindow( m_SynchronisationYesNo == 0 );

   	if (GetDlgItem(IDC_SYNCHRO_TIME) != NULL)
   		GetDlgItem(IDC_SYNCHRO_TIME)->EnableWindow( m_SynchronisationYesNo == 0 );

   	if (GetDlgItem(IDC_STATIC_FILE) != NULL)
		GetDlgItem(IDC_STATIC_FILE)->ShowWindow( (m_SynchronisationYesNo == 0) ? SW_SHOW : SW_HIDE );
   	if (GetDlgItem(IDC_AUTOMATICFILENAME) != NULL)
   		GetDlgItem(IDC_AUTOMATICFILENAME)->ShowWindow( (m_SynchronisationYesNo == 0) ? SW_SHOW : SW_HIDE );
   	if (GetDlgItem(IDC_AUTOMATICFILENAME2) != NULL)
   		GetDlgItem(IDC_AUTOMATICFILENAME2)->ShowWindow( (m_SynchronisationYesNo == 0) ? SW_SHOW : SW_HIDE );
   	if (GetDlgItem(IDC_AUTOMATICFILENAME3) != NULL)
   		GetDlgItem(IDC_AUTOMATICFILENAME3)->ShowWindow( (m_SynchronisationYesNo == 0) ? SW_SHOW : SW_HIDE );
   	
   	if (GetDlgItem(IDC_FLF_FILENAME) != NULL)
   		GetDlgItem(IDC_FLF_FILENAME)->ShowWindow( (m_AutomaticFilenameGeneration == 0) ? SW_HIDE : SW_SHOW );
   	
   	if (GetDlgItem(IDC_SELECT_FLF) != NULL)
   		GetDlgItem(IDC_SELECT_FLF)->ShowWindow( (m_AutomaticFilenameGeneration == 0) ? SW_HIDE : SW_SHOW );
}

void ZADocOptionDLG::OnClicked()
{
	CheckControlState();
}

void ZADocOptionDLG::OnSelectFLF()
{
	if (m_AutomaticFilenameGeneration == 2)
	{            
		ZIOpenDirDlg	dlgDirectory;
		
		if (dlgDirectory.ProcessDirectory() != "")
		{
			m_FLF_Filename = dlgDirectory.GetDirectory();
			UpdateData( FALSE );
		}
	}
	else
		if (m_AutomaticFilenameGeneration == 1)
		{
			CString	File;
			File.LoadString( IDS_DOCUMENTFEEDFILTER );
			File = "*" + File;
			
			CString title;
			VERIFY(title.LoadString(IDS_FEEDFILE_CHOOSETITLE));
		
			// set the first file filter
			CString strFilter;
			VERIFY(strFilter.LoadString(IDS_FEEDFILE_FILTERTXT));
			strFilter += (char)'\0';        // next string please
			strFilter += File;
			strFilter += (char)'\0';        // last string
		
			// append the "*.*" all files filter
			CString allFilter;
			VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
			strFilter += allFilter;
			strFilter += (char)'\0';        // next string please
			strFilter += "*.*";
			strFilter += (char)'\0';        // last string
		
			ZIFileDialog	FileDialog( title, strFilter, 2 );
			if (FileDialog.DoModal() == IDOK)
			{
				m_FLF_Filename = FileDialog.GetFilename();
				UpdateData( FALSE );
			}
		}
}

