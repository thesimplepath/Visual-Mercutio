// ZVURLFormView.cpp : implementation file
//

#include "stdafx.h"
#include "ZVURLFormView.h"

#include "zRes32\ZRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVURLFormView

IMPLEMENT_DYNCREATE(ZVURLFormView, CFormView)

ZVURLFormView::ZVURLFormView()
	: CFormView(ZVURLFormView::IDD),
	m_pBrowser(NULL)
{
	//{{AFX_DATA_INIT(ZVURLFormView)
	m_URL = _T("");
	//}}AFX_DATA_INIT
}

ZVURLFormView::~ZVURLFormView()
{
	if (m_pBrowser)
		delete m_pBrowser;
	m_pBrowser = NULL;
}

void ZVURLFormView::OnInitialUpdate( )
{
	CFormView::OnInitialUpdate( );

	m_GoButton.SetIcon(IDI_GOWEB);
	m_GoButton.SetAlign( ZCFlatButton::ST_ALIGN_HORIZ_RIGHT );
	m_GoButton.SetTooltipText(IDS_GOWEB);

	m_GoButton.DrawTransparent();

	// Create web control
	if (GetDlgItem(IDC_WEBCTRL))
	{
		CRect rect;
		GetDlgItem(IDC_WEBCTRL)->GetClientRect (&rect);
		GetDlgItem(IDC_WEBCTRL)->MapWindowPoints( this, &rect );

		// Create the control.
		m_pBrowser = new ZWebBrowser;
		ASSERT (m_pBrowser);
		if (!m_pBrowser->Create(NULL,NULL,WS_VISIBLE,rect,this,NULL))
		{
			TRACE("failed to create browser\n");
			delete m_pBrowser;
			m_pBrowser = NULL;
			return;
		}

		// Initialize the first URL.
		COleVariant noArg;
		if (!m_URL.IsEmpty())
			m_pBrowser->Navigate( m_URL );

	}
	// Assign the parent's toolbar
	m_FlatToolBar.SetParent( this );
	// Assign the pointer to the value array
	m_URLEdit.Initialize( &m_ValueArray );
	// Assign the parent's edit
	m_URLEdit.SetParent( this );
}


void ZVURLFormView::SizeControl() 
{
	if (GetDlgItem(IDC_WEBCTRL) &&
		::IsWindow(GetDlgItem(IDC_WEBCTRL)->GetSafeHwnd()))
	{
		CRect rect;
		GetClientRect(&rect);
		// If the rect is empty, nothing to do.
		if (rect.IsRectEmpty())
			return;
		if (GetDlgItem(IDC_URL))
		{
			CRect EditRect;
			GetDlgItem(IDC_URL)->GetClientRect(&EditRect);
			int cx = EditRect.Width();
			int cy = __max(EditRect.Height(), 20);
			EditRect.top = rect.top + 25;
			EditRect.bottom = EditRect.top + cy;
			EditRect.left = rect.left + 2;
			EditRect.right = rect.right - 25;
			GetDlgItem(IDC_URL)->MoveWindow( &EditRect );
		}
		if (GetDlgItem(IDC_GOWEB))
		{
			CRect ButtonRect;
			GetDlgItem(IDC_GOWEB)->GetClientRect(&ButtonRect);
			int cx = ButtonRect.Width();
			int cy = ButtonRect.Height();
			ButtonRect.top = rect.top + 25;
			ButtonRect.bottom = ButtonRect.top + cy;
			ButtonRect.right = rect.right - 2;
			ButtonRect.left = ButtonRect.right - cx;
			GetDlgItem(IDC_GOWEB)->MoveWindow( &ButtonRect );
		}
		if (m_pBrowser)
		{
			CRect BrowserRect;
			m_pBrowser->GetClientRect(&BrowserRect);
			int cx = BrowserRect.Width();
			int cy = BrowserRect.Height();
			BrowserRect.bottom = rect.bottom - 2;
			BrowserRect.right = rect.right - 2;
			BrowserRect.top = rect.top + 50;
			BrowserRect.left = rect.left + 2;
			m_pBrowser->MoveWindow( &BrowserRect );
		}
	}	
}

void ZVURLFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZVURLFormView)
	DDX_Control(pDX, IDC_URL, m_URLEdit);
	DDX_Control(pDX, IDC_GOWEB, m_GoButton);
	DDX_Control(pDX, IDC_FLATTOOLBAR, m_FlatToolBar);
	DDX_Text(pDX, IDC_URL, m_URL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVURLFormView, CFormView)
	//{{AFX_MSG_MAP(ZVURLFormView)
	ON_BN_CLICKED(IDC_GOWEB, OnGo)
	ON_WM_SIZE()
	ON_MESSAGE(UM_STOPWEB, OnStopWebButton)
	ON_MESSAGE(UM_REFRESHWEB, OnRefreshWebButton)
	ON_MESSAGE(UM_PREVWEB, OnPrevWebButton)
	ON_MESSAGE(UM_NEXTWEB, OnNextWebButton)
	ON_MESSAGE(UM_GOWEB, OnGoMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVURLFormView diagnostics

#ifdef _DEBUG
void ZVURLFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void ZVURLFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZVURLFormView message handlers

LRESULT ZVURLFormView::OnStopWebButton( WPARAM wParam, LPARAM lParam )
{
	if (m_pBrowser)
		m_pBrowser->Stop();
	return 1;
}

LRESULT ZVURLFormView::OnRefreshWebButton( WPARAM wParam, LPARAM lParam )
{
	if (m_pBrowser)
		m_pBrowser->Refresh();
	return 1;
}

LRESULT ZVURLFormView::OnPrevWebButton( WPARAM wParam, LPARAM lParam ) 
{
	if (m_pBrowser)
		m_pBrowser->GoBack();
	return 1;
}

LRESULT ZVURLFormView::OnNextWebButton( WPARAM wParam, LPARAM lParam ) 
{
	if (m_pBrowser)
		m_pBrowser->GoForward();
	return 1;
}


LRESULT ZVURLFormView::OnGoMessage( WPARAM wParam, LPARAM lParam ) 
{
	OnGo();
	return 1;
}

void ZVURLFormView::OnGo()
{
	UpdateData();
	bool	Found = false;
	for (int i = 0; i < m_ValueArray.GetSize(); ++i)
	{
		if (m_ValueArray.GetAt(i) == m_URL)
		{
			Found = true;
			break;
		}
	}
	if (!Found)
		m_ValueArray.Add( m_URL );
	if (!m_URL.IsEmpty())
		m_pBrowser->Navigate( m_URL );
}


void ZVURLFormView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	SizeControl();
}





/////////////////////////////////////////////////////////////////////////////
// _ZVURLFormViewButtonToolBar

_ZVURLFormViewButtonToolBar::_ZVURLFormViewButtonToolBar(CWnd* pParent /*=NULL*/)
: m_pParent(pParent)
{
		m_ImageList.Create(IDB_URL_FV_BUTTONS, 14, 1, RGB(255,0,255));
}

_ZVURLFormViewButtonToolBar::~_ZVURLFormViewButtonToolBar()
{
}

void	_ZVURLFormViewButtonToolBar::SetParent(CWnd* pParent)
{
	m_pParent = pParent;
}

BEGIN_MESSAGE_MAP(_ZVURLFormViewButtonToolBar, CStatic)
	//{{AFX_MSG_MAP(_ZVURLFormViewButtonToolBar)
	ON_BN_CLICKED(IDC_STOPWEB, OnStopWebButton)
	ON_BN_CLICKED(IDC_REFRESHWEB, OnRefreshWebButton)
	ON_BN_CLICKED(IDC_PREVWEB, OnPrevWebButton)
	ON_BN_CLICKED(IDC_NEXTWEB, OnNextWebButton)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// _ZVURLFormViewButtonToolBar message handlers

int _ZVURLFormViewButtonToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

void _ZVURLFormViewButtonToolBar::PreSubclassWindow() 
{
	CStatic::PreSubclassWindow();

	int	IconIndex = 0;

	CRect rc;
	GetWindowRect(&rc);
	ScreenToClient(&rc);
	rc.top+=1; rc.bottom-=1;
	rc.left+=1;
	rc.right = rc.left+20;

	
	if (!m_PrevWebButton.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
		rc, this, IDC_PREVWEB))
	{
		TRACE0("Unable to create button.\n");
		return;
	}
	m_PrevWebButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(14,14));
	rc.OffsetRect(20,0);

	if (!m_NextWebButton.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
		rc, this, IDC_NEXTWEB))
	{
		TRACE0("Unable to create button.\n");
		return;
	}
	m_NextWebButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(14,14));
	rc.OffsetRect(20,0);

	if (!m_StopWebButton.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
		rc, this, IDC_STOPWEB))
	{
		TRACE0("Unable to create button.\n");
		return;
	}
	m_StopWebButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(14,14));
	rc.OffsetRect(20,0);

	if (!m_RefreshWebButton.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
		rc, this, IDC_REFRESHWEB))
	{
		TRACE0("Unable to create button.\n");
		return;
	}
	m_RefreshWebButton.SetIcon(m_ImageList.ExtractIcon(IconIndex++), CSize(14,14));

	
	// Create the ToolTip control.
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);

	m_tooltip.AddTool(GetDlgItem(IDC_PREVWEB), IDS_PREVWEB);
	m_tooltip.AddTool(GetDlgItem(IDC_NEXTWEB), IDS_NEXTWEB);
	m_tooltip.AddTool(GetDlgItem(IDC_STOPWEB), IDS_STOPWEB);
	m_tooltip.AddTool(GetDlgItem(IDC_REFRESHWEB), IDS_REFRESHWEB);
}


void _ZVURLFormViewButtonToolBar::OnStopWebButton()
{
	if (m_pParent)
		m_pParent->SendMessage( UM_STOPWEB );
}

void _ZVURLFormViewButtonToolBar::OnRefreshWebButton()
{
	if (m_pParent)
		m_pParent->SendMessage( UM_REFRESHWEB );
}

void _ZVURLFormViewButtonToolBar::OnPrevWebButton() 
{
	if (m_pParent)
		m_pParent->SendMessage( UM_PREVWEB );
}

void _ZVURLFormViewButtonToolBar::OnNextWebButton() 
{
	if (m_pParent)
		m_pParent->SendMessage( UM_NEXTWEB );
}


BOOL _ZVURLFormViewButtonToolBar::PreTranslateMessage(MSG* pMsg) 
{
	// Let the ToolTip process this message.
	m_tooltip.RelayEvent(pMsg);
	return CStatic::PreTranslateMessage(pMsg);
}




/////////////////////////////////////////////////////////////////////////////
// _ZCAddressIntelliEdit

_ZCAddressIntelliEdit::_ZCAddressIntelliEdit(CWnd* pParent /*=NULL*/, CStringArray* pArrayOfValues /*= NULL*/ )
: ZCIntelliEdit(pArrayOfValues),
  m_pParent(pParent)
{
}

_ZCAddressIntelliEdit::~_ZCAddressIntelliEdit()
{
}

void	_ZCAddressIntelliEdit::SetParent(CWnd* pParent)
{
	m_pParent = pParent;
}


void	_ZCAddressIntelliEdit::OnEnter()
{
	if (m_pParent)
		m_pParent->SendMessage( UM_GOWEB );
}


BEGIN_MESSAGE_MAP(_ZCAddressIntelliEdit, ZCIntelliEdit)
	//{{AFX_MSG_MAP(_ZCAddressIntelliEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// _ZCAddressIntelliEdit message handlers

