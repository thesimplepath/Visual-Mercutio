//---------------------------------------------------------------------------
// Author    : Dominique Aigroz
// SourceFile: edit.cpp
// Created   : 14.12.1994
// Modify    :
//
// Classes Edit,  StrEdit, StrEditHistoric
// in charge of edition.
//
//---------------------------------------------------------------------------

#include "stdafx.h"

#include "Edit.h"
#include "planfobj.h"
#include "ZDDoc.h"

// ZAMStr
#include "ZAMStr.h"
#include "ZAMultiC.h"

#include "ToolBarx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 14 août 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

const int MIN_EDIT_WIDTH    = 150;
const int MIN_EDIT_HEIGHT    = 20;

/////////////////////////////////////////////////////////////////////////////
// Edit

Edit::Edit()
    : m_pParentWnd    ( NULL ),
      m_pEditedObj    ( NULL ),
      m_ReadOnly    ( FALSE ),
      m_pSpecialHelp( NULL ),
      m_IsSorted    ( FALSE )
{
}

Edit::~Edit()
{
    if ( m_pSpecialHelp )
    {
        delete m_pSpecialHelp;
        m_pSpecialHelp = NULL;
    }
}

void Edit::PreCreateEdit( BOOL                    DesignerMode,
                          CWnd                    *pParentWnd,
                          CDC                    *pDC,
                          ZDDocument*            pDoc,
                          PlanFinObject*        pEditedObj,
                          ZBFieldRepository*    pFieldRepository,
                          BOOL                    AutoCalculateOption,
                          BOOL                    GoNextEditOption )
{
    m_pParentWnd            = pParentWnd;
    m_pEditedObj            = pEditedObj;
    m_pFieldRepository        = pFieldRepository;
    m_AutoCalculateOption    = AutoCalculateOption;
    m_GoNextEditOption        = GoNextEditOption;
    m_pDoc                    = pDoc;
    
    ZAHistoryField* pField    = NULL;

    if ( m_pFieldRepository && ( pField = m_pFieldRepository->FindFieldHistory( m_pEditedObj->GetObjectName() ) ) )
    {
        m_ReadOnly = pField->IsReadOnly();
    }

    ZAObjectDefinition* pObjectDefinition = NULL;

    if ( m_pFieldRepository &&
         ( pObjectDefinition = m_pFieldRepository->FindField( m_pEditedObj->GetObjectName() ) ) )
    {
        m_IsSorted = pObjectDefinition->IsSorted();
    }

    AfxGetMainWnd()->SendMessageToDescendants( UM_NOTIFY_OBJECTSELECTED,
                                               UM_NOTIFY_OBJECTSELECTED,
                                               (LPARAM)m_pEditedObj );

    m_Rect = CheckBounds( pDC, pParentWnd, m_pEditedObj->GetClientRect() );

    if ( !m_ReadOnly )
    {
        CreateSpecialHelp( DesignerMode );
    }
}

CRect Edit::CheckBounds( CDC* pDC, CWnd *pParentWnd, CRect& rct )
{
    m_GoNext = FALSE;
    SetModify( TRUE );

    // Translate the rectangle in device coordinates
    CRect Rect( rct );

    // Check if the rectangle is not too small
    // If necessary change it before creating
    // the edit box.
    if( Rect.Width() < MIN_EDIT_WIDTH )
    {
        Rect.right = Rect.left + MIN_EDIT_WIDTH;
    }

    if( Rect.Height() < MIN_EDIT_HEIGHT )
    {
        Rect.top = Rect.bottom - MIN_EDIT_HEIGHT;
    }

    pDC->LPtoDP( &Rect );

    return Rect;
}

void Edit::CreateSpecialHelp( BOOL Designer )
{
    if ( m_pEditedObj->IsKindOf( RUNTIME_CLASS( PLFNTime ) ) )
    {
        if ( Designer )
        {
            m_pSpecialHelp = new SpecialHelpDateDesigner;
        }
        else
        {
            m_pSpecialHelp = new SpecialHelpDate;
        }
    }
    else if ( m_pEditedObj->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) )
    {
        if ( ( (PLFNLong*)m_pEditedObj )->GetAssociations().GetCount() )
        {
            if ( Designer )
            {
                m_pSpecialHelp = new SpecialHelpNumberScenarioDesigner;
            }
            else
            {
                m_pSpecialHelp = new SpecialHelpNumberScenario;
            }
        }
        else
        {
            if ( Designer )
            {
                m_pSpecialHelp = new SpecialHelpNumberDesigner;
            }
            else
            {
                m_pSpecialHelp = new SpecialHelpNumber;
            }
        }
    }
    else
    {
        if ( Designer )
        {
            m_pSpecialHelp = new SpecialHelpDefaultDesigner;
        }
        else
        {
            m_pSpecialHelp = new SpecialHelpDefault;
        }
    }

    // Create the special helper
    m_pSpecialHelp->Create( m_pParentWnd, &m_Rect, m_pEditedObj, m_AutoCalculateOption );
}

void Edit::AddToHistoric( CString str )
{
    // If global historic field value manager is defined, try to add the field value there.
    if ( m_pFieldRepository && m_pFieldRepository->FindFieldHistory( m_pEditedObj->GetObjectName() ) )
    {
        // Field exists in the global histo value and is not read only
        if ( m_ReadOnly == FALSE )
        {
            m_pFieldRepository->AddFieldHistoryValue( m_pEditedObj->GetObjectName(), str );
        }

        return;
    }
    
    // If not found nor does not exists, add it to the local file.
    m_pDoc->GetHistoryValueManager().AddFieldHistoryValue( m_pEditedObj->GetObjectName(), str );
}

CStringArray* Edit::GetArrayOfValues()
{
    // If global historic field value manager is defined, try to add the field value there.
    if ( m_pFieldRepository && m_pFieldRepository->FindFieldHistory( m_pEditedObj->GetObjectName() ) )
    {
        return m_pFieldRepository->GetFieldHistory( m_pEditedObj->GetObjectName() );
    }
    else
    {
        if ( m_pEditedObj->IsMemberOfMultiColumn() )
        {
            // Force the read only for member of multi-column field
            m_ReadOnly = TRUE;

            return (CStringArray*)&( m_pEditedObj->GetpColumn()->GetValueArray() );
        }
        else
        {
            // If not found nor does not exists
            return m_pDoc->GetHistoryValueManager().GetFieldHistory( m_pEditedObj->GetObjectName() );
        }
    }

    return NULL;
}

void Edit::LoadFromHistoric( CComboBox& Combo )
{
    CStringArray* pValueArray = Edit::GetArrayOfValues();

    // No values found neither in Global historic manager nor in local historic manager
    if ( !pValueArray )
    {
        return;
    }

    for ( register i = 0; i < pValueArray->GetSize() ; i++ )
    {
        if ( !pValueArray->GetAt( i ).IsEmpty() )
        {
            Combo.AddString( pValueArray->GetAt( i ) );
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// StrEdit

BEGIN_MESSAGE_MAP( StrEdit, ZBDragEdit )
    //{{AFX_MSG_MAP(StrEdit)
    ON_WM_CHAR()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

StrEdit::StrEdit( BOOL bMultiLine, int iMaxChar )
    : Edit            (),
      ZBDragEdit    (),
      m_bMultiLine    ( bMultiLine ),
      m_iMaxChar    ( iMaxChar )
{
}

StrEdit::~StrEdit()
{
    if ( IsWindow( GetSafeHwnd() ) )
    {
        HideCaret();
    }

    Edit::~Edit();
}

// Create ----------------------------------------------------
//
// Author        :    Aigroz Dominique
// Date            :    14/12/1994
// Description    :    This function create an edit box on the
//                    PlanFin on the object place.
//
// Parameters    :    strName        the name to search in the list.
// Return        :    the object value.
//
// Remarks        :    
// Modifications:    04/04/1995    Aigroz Dominique
//                        Set a minimum size for the edit box.
//
//----------------------------------------------------------------------------
void StrEdit::Create( BOOL                    DesignerMode,
                      CWnd                    *pParentWnd,
                      CDC                    *pDC,
                      ZDDocument*            pDoc,
                      PlanFinObject*        pEditedObj,
                      ZBFieldRepository*    pFieldRepository,
                      BOOL                    AutoCalculateOption,
                      BOOL                    GoNextEditOption )
{
    PreCreateEdit( DesignerMode,
                   pParentWnd,
                   pDC,
                   pDoc,
                   pEditedObj,
                   pFieldRepository,
                   AutoCalculateOption,
                   GoNextEditOption );

    DWORD dwStyle;

    if ( m_bMultiLine )
    {
        dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_MULTILINE;
    }
    else
    {
        dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;
    }

    if ( m_ReadOnly )
    {
        dwStyle |= ES_READONLY;
    }

    if ( ZBDragEdit::Create( dwStyle, m_Rect, pParentWnd, 0 ) == FALSE )
    {
        return;
    }

    // Initialize drag & drop facilities
    ZBDragEdit::Init();

    SetWindowText( m_pEditedObj->GetFormatedObject() );
    SetSel( 0, -1 );
    ShowWindow( SW_SHOW );
    SetFocus();
    ShowCaret();
}

void StrEdit::DestroyEdit()
{
    // Save Only if required
    if( m_Save )
    {
        CString strTemp;

        GetWindowText( strTemp );
        m_pEditedObj->ConvertFormatedObject( strTemp, FALSE );

        // To notify the view that on field change
        // Pass the adress of the object
        // then the routine that proceed the message
        // can know wich object has changed
        AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)m_pEditedObj );

        // Save Only one time
        m_Save = FALSE;

        if ( m_GoNext )
        {
            AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_EDITNEXT, 0, (LPARAM)m_pEditedObj );
        }
    }

    // Hide the window and the DestroyWindow function
    // is used in the destructor
    ShowWindow( SW_HIDE );

    if ( m_pSpecialHelp )
    {
        m_pSpecialHelp->ShowWindow( SW_HIDE );
    }
}

/////////////////////////////////////////////////////////////////////////////
// Edit message handlers

void StrEdit::OnKillFocus( CWnd* pNewWnd )
{
    ZBDragEdit::OnKillFocus( pNewWnd );
    DestroyEdit();
}

void StrEdit::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    if( nChar == 0x0D )
    {
        Edit::SetModify( TRUE );

        if ( m_GoNextEditOption )
        {
            m_GoNext = TRUE;
        }

        DestroyEdit();
        return;
    }

    // If Tab go to next
    if( nChar == 0x09 )
    {
        Edit::SetModify( TRUE );
        m_GoNext = TRUE;
        DestroyEdit();
        return;
    }

    if( nChar == 0x1B )
    {
        Edit::SetModify( FALSE );
        DestroyEdit();
        return;
    }

    // Test if it is necessary to check the length
    // do not check if backspace
    if ( m_iMaxChar > 0 && nChar != 0x08 )
    {
        CString strTemp;
        GetWindowText( strTemp );

        // If outside of the maximum char,
        // play a sound and ignore the char typed.
        if ( strTemp.GetLength() + 1 > m_iMaxChar )
        {
            MessageBeep( MB_ICONEXCLAMATION );
            return;
        }
    }

    ZBDragEdit::OnChar( nChar, nRepCnt, nFlags );
}

/////////////////////////////////////////////////////////////////////////////
// NumEdit

BEGIN_MESSAGE_MAP( NumEdit, ZBDragEdit )
    //{{AFX_MSG_MAP(NumEdit)
    ON_WM_CHAR()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

NumEdit::NumEdit()
    : Edit(),
      ZBDragEdit()
{
}

// Create ----------------------------------------------------
//
// Author        :    Aigroz Dominique
// Date            :    14/12/1994
// Description    :    This function create an edit box on the
//                    PlanFin on the object place.
//
// Parameters    :    strName        the name to search in the list.
// Return        :    the object value.
//
// Remarks        :    
// Modifications:    04/04/1995    Aigroz Dominique
//                        Set a minimum size for the edit box.
//
//----------------------------------------------------------------------------
void NumEdit::Create( BOOL                    DesignerMode,
                      CWnd*                    pParentWnd,
                      CDC*                    pDC,
                      ZDDocument*            pDoc,
                      PlanFinObject*        pEditedObj,
                      ZBFieldRepository*    pFieldRepository,
                      BOOL                    AutoCalculateOption,
                      BOOL                    GoNextEditOption )
{
    PreCreateEdit( DesignerMode,
                   pParentWnd,
                   pDC,
                   pDoc,
                   pEditedObj,
                   pFieldRepository,
                   AutoCalculateOption,
                   GoNextEditOption );

    DWORD dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

    if ( m_ReadOnly )
    {
        dwStyle |= ES_READONLY;
    }

    if ( ZBDragEdit::Create( dwStyle, m_Rect, pParentWnd, 0 ) == FALSE )
    {
        return;
    }

    SetWindowText( m_pEditedObj->GetFormatedObject() );

    // Initialize drag & drop facilities
    ZBDragEdit::Init();

    SetSel( 0, -1 );
    ShowWindow( SW_SHOW );
    SetFocus();
    ShowCaret();
}

NumEdit::~NumEdit()
{
    if ( IsWindow( GetSafeHwnd() ) )
    {
        HideCaret();
    }

    Edit::~Edit();
}

void NumEdit::DestroyEdit()
{
    // Save Only if required
    if( m_Save )
    {
        CString strTemp;

        GetWindowText( strTemp );

        if ( strTemp.IsEmpty() )
        {
            m_pEditedObj->EmptyObject();
        }
        else
        {
            m_pEditedObj->ConvertFormatedObject( strTemp, FALSE );
        }

        if ( m_AutoCalculateOption )
        {
            AfxGetMainWnd()->SendMessageToDescendants( ID_CALCULATE_MESSAGE, 0, 0 );
        }

        // To notify the view that on field change
        // Pass the adress of the object
        // then the routine that proceed the message
        // can know wich object has changed
        AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)m_pEditedObj );

        // Save Only one time
        m_Save = FALSE;

        if ( m_GoNext )
        {
            AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_EDITNEXT, 0, (LPARAM)m_pEditedObj );
        }
    }

    // Hide the window and the DestroyWindow function
    // is used in the destructor
    ShowWindow( SW_HIDE );

    if ( m_pSpecialHelp )
    {
        m_pSpecialHelp->ShowWindow( SW_HIDE );
    }
}

/////////////////////////////////////////////////////////////////////////////
// NumEdit message handlers

void NumEdit::OnKillFocus( CWnd* pNewWnd )
{
    ZBDragEdit::OnKillFocus( pNewWnd );
    DestroyEdit();
}

// OnChar ----------------------------------------------------
//
// Modifications:    04/04/1995    Aigroz Dominique
//                        Add the char 0x08 for Backspace in the test.
//
//----------------------------------------------------------------------------
void NumEdit::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    if( nChar == 0x0D )
    {
        Edit::SetModify( TRUE );

        if ( m_GoNextEditOption )
        {
            m_GoNext = TRUE;
        }

        DestroyEdit();
        return;
    }

    // If Tab go to next
    if( nChar == 0x09 )
    {
        Edit::SetModify( TRUE );
        m_GoNext = TRUE;
        DestroyEdit();
        return;
    }

    if( nChar == 0x1B )
    {
        Edit::SetModify( FALSE );
        DestroyEdit();
        return;
    }

    // Check the validity of the char
    if( !isdigit( nChar )    &&
        nChar != '.'        &&
        nChar != '-'        &&
        nChar != '+'        &&
        nChar != '\''        &&
        nChar != ','        &&
        nChar != '%'        &&
        nChar != 0x08 )
    {
        return;
    }

    ZBDragEdit::OnChar( nChar, nRepCnt, nFlags );
}

/////////////////////////////////////////////////////////////////////////////
// CalcEdit

BEGIN_MESSAGE_MAP( CalcEdit, ZBDragEdit )
    //{{AFX_MSG_MAP(CalcEdit)
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CalcEdit::CalcEdit()
    : Edit(),
      ZBDragEdit()
{
}

CalcEdit::~CalcEdit()
{
    if ( IsWindow( GetSafeHwnd() ) )
    {
        HideCaret();
    }

    Edit::~Edit();
}

// Create ----------------------------------------------------
//
// Author        :    Aigroz Dominique
// Date            :    14/12/1994
// Description    :    This function create an edit box on the
//                    PlanFin on the object place.
//
// Parameters    :    strName        the name to search in the list.
// Return        :    the object value.
//
// Remarks        :    
// Modifications:    04/04/1995    Aigroz Dominique
//                        Set a minimum size for the edit box.
//
//----------------------------------------------------------------------------
void CalcEdit::Create( BOOL                    DesignerMode,
                       CWnd*                pParentWnd,
                       CDC*                    pDC,
                       ZDDocument*            pDoc,
                       PlanFinObject*        pEditedObj,
                       ZBFieldRepository*    pFieldRepository,
                       BOOL                    AutoCalculateOption,
                       BOOL                    GoNextEditOption )
{
    PreCreateEdit( DesignerMode,
                   pParentWnd,
                   pDC,
                   pDoc,
                   pEditedObj,
                   pFieldRepository,
                   AutoCalculateOption,
                   GoNextEditOption );

    DWORD dwStyle = WS_CHILD;

    if ( m_ReadOnly )
    {
        dwStyle |= ES_READONLY;
    }

    if ( ZBDragEdit::Create( dwStyle, m_Rect, pParentWnd, 0 ) == FALSE )
    {
        return;
    }

    // Initialize drag & drop facilities
    ZBDragEdit::Init();

    SetFocus();
}

void CalcEdit::DestroyEdit()
{
    // Hide the window and the DestroyWindow function
    // is used in the destructor
    ShowWindow( SW_HIDE );

    if ( m_pSpecialHelp )
    {
        m_pSpecialHelp->ShowWindow( SW_HIDE );
    }
}

/////////////////////////////////////////////////////////////////////////////
// CalcEdit message handlers

void CalcEdit::OnKillFocus( CWnd* pNewWnd )
{
    ZBDragEdit::OnKillFocus( pNewWnd );
    DestroyEdit();
}

/////////////////////////////////////////////////////////////////////////////
// TimeEdit

BEGIN_MESSAGE_MAP( TimeEdit, ZBDragEdit )
    //{{AFX_MSG_MAP(TimeEdit)
    ON_WM_CHAR()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

TimeEdit::TimeEdit()
    : Edit(),
      ZBDragEdit()
{
}

TimeEdit::~TimeEdit()
{
    if ( IsWindow( GetSafeHwnd() ) )
    {
        HideCaret();
    }

    Edit::~Edit();
}

// Create ----------------------------------------------------
//
// Author        :    Aigroz Dominique
// Date            :    14/12/1994
// Description    :    This function create an edit box on the
//                    PlanFin on the object place for time editing.
//
// Parameters    :    strName        the name to search in the list.
// Return        :    the object value.
//
// Remarks        :    
// Modifications:    04/04/1995    Aigroz Dominique
//                        Set a minimum size for the edit box.
//
//----------------------------------------------------------------------------
void TimeEdit::Create( BOOL                    DesignerMode,
                       CWnd*                pParentWnd,
                       CDC*                    pDC,
                       ZDDocument*            pDoc,
                       PlanFinObject*        pEditedObj,
                       ZBFieldRepository*    pFieldRepository,
                       BOOL                    AutoCalculateOption,
                       BOOL                    GoNextEditOption )
{
    PreCreateEdit( DesignerMode,
                   pParentWnd,
                   pDC,
                   pDoc,
                   pEditedObj,
                   pFieldRepository,
                   AutoCalculateOption,
                   GoNextEditOption );

    DWORD dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

    if ( m_ReadOnly )
    {
        dwStyle |= ES_READONLY;
    }

    if ( ZBDragEdit::Create( dwStyle, m_Rect, pParentWnd, 0 ) == FALSE )
    {
        return;
    }

    CString strFormat( _T( " " ) );

    if( m_pEditedObj->IsKindOf( RUNTIME_CLASS( PLFNTime ) ) && ( (PLFNTime*)m_pEditedObj )->IsEmpty() == FALSE )
    {
        sprintf( strFormat.GetBuffer( 100 ),
                 _T( "%d.%d.%04d" ),
                 ( (PLFNTime*)m_pEditedObj )->m_Time.GetDay(),
                 ( (PLFNTime*)m_pEditedObj )->m_Time.GetMonth(),
                 ( (PLFNTime*)m_pEditedObj )->m_Time.GetYear() );

        strFormat.ReleaseBuffer();
    }

    SetWindowText( (const char*)strFormat );

    // Initialize drag & drop facilities
    ZBDragEdit::Init();

    SetSel( 0, -1 );
    ShowWindow( SW_SHOW );
    SetFocus();
    ShowCaret();
}

void TimeEdit::DestroyEdit()
{
    // Save Only if required
    while ( m_Save )
    {
        CString strTemp;
        GetWindowText( strTemp );

        if ( strTemp.IsEmpty() )
        {
            m_pEditedObj->EmptyObject();
        }
        else
        {
            m_pEditedObj->ConvertFormatedObject( strTemp, FALSE );
        }

        // To notify the view that on field change
        // Pass the adress of the object
        // then the routine that proceed the message
        // can know wich object has changed
        AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)m_pEditedObj );

        // Save Only one time
        m_Save = FALSE;

        if ( m_GoNext )
        {
            AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_EDITNEXT, 0, (LPARAM)m_pEditedObj );
        }

        break;
    }

    // Hide the window and the DestroyWindow function
    // is used in the destructor
    ShowWindow( SW_HIDE );

    if ( m_pSpecialHelp )
    {
        m_pSpecialHelp->ShowWindow( SW_HIDE );
    }
}

/////////////////////////////////////////////////////////////////////////////
// TimeEdit message handlers

void TimeEdit::OnKillFocus( CWnd* pNewWnd )
{
    ZBDragEdit::OnKillFocus( pNewWnd );
    DestroyEdit();
}

// OnChar ----------------------------------------------------
//
// Modifications:    04/04/1995    Aigroz Dominique
//                        Add the char 0x08 for Backspace in the test.
//
//----------------------------------------------------------------------------
void TimeEdit::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    if( nChar == 0x0D )
    {
        Edit::SetModify( TRUE );

        if ( m_GoNextEditOption )
        {
            m_GoNext = TRUE;
        }

        DestroyEdit();
        return;
    }

    // If Tab go to next
    if( nChar == 0x09 )
    {
        Edit::SetModify( TRUE );
        m_GoNext = TRUE;
        DestroyEdit();
        return;
    }

    if( nChar == 0x1B )
    {
        Edit::SetModify( FALSE );
        DestroyEdit();
        return;
    }

    // Check the validity of the char
    if( !isdigit( nChar ) && nChar != '.' && nChar != '/' && nChar != 0x08 )
    {
        return;
    }

    ZBDragEdit::OnChar( nChar, nRepCnt, nFlags );
}

/////////////////////////////////////////////////////////////////////////////
// StrEditHistoric

BEGIN_MESSAGE_MAP( StrEditHistoric, ZCIntelliEdit )
    //{{AFX_MSG_MAP(StrEditHistoric)
    ON_WM_CHAR()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

StrEditHistoric::StrEditHistoric( int iMaxChar )
    : Edit(),
      ZCIntelliEdit(),
      m_iMaxChar( iMaxChar )
{
}

StrEditHistoric::~StrEditHistoric()
{
    if ( IsWindow( GetSafeHwnd() ) )
    {
        HideCaret();
    }

    Edit::~Edit();
}

// Create ----------------------------------------------------
//
// Author        :    Aigroz Dominique
// Date            :    14/12/1994
// Description    :    This function create an edit box on the
//                    PlanFin on the object place.
//
// Parameters    :    strName        the name to search in the list.
// Return        :    the object value.
//
// Remarks        :    
// Modifications:    04/04/1995    Aigroz Dominique
//                        Set a minimum size for the edit box.
//
//----------------------------------------------------------------------------
void StrEditHistoric::Create( BOOL                    DesignerMode,
                              CWnd*                    pParentWnd,
                              CDC*                    pDC,
                              ZDDocument*            pDoc,
                              PlanFinObject*        pEditedObj,
                              ZBFieldRepository*    pFieldRepository,
                              BOOL                    AutoCalculateOption,
                              BOOL                    GoNextEditOption )
{
    PreCreateEdit( DesignerMode,
                   pParentWnd,
                   pDC,
                   pDoc,
                   pEditedObj,
                   pFieldRepository,
                   AutoCalculateOption,
                   GoNextEditOption );

    DWORD dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

    if ( ZCIntelliEdit::Create( dwStyle, m_Rect, pParentWnd, 0 ) == FALSE )
    {
        return;
    }

    ZCIntelliEdit::Initialize( GetArrayOfValues() );

    CString sStr = m_pEditedObj->GetFormatedObject();
    SetWindowText( sStr );

    SetFocus();
    ShowCaret();
}

void StrEditHistoric::DestroyEdit()
{
    // Only if required
    if( m_Save )
    {
        CString strTemp;

        GetWindowText( strTemp );
        m_pEditedObj->ConvertFormatedObject( strTemp, FALSE );

        // Keep the historical changes
        AddToHistoric( strTemp );

        // To notify the view that on field change
        // Pass the adress of the object
        // then the routine that proceed the message
        // can know wich object has changed
        AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)m_pEditedObj );

        // Save Only one time
        m_Save = FALSE;

        if ( m_GoNext )
        {
            AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_EDITNEXT, 0, (LPARAM)m_pEditedObj );
        }
    }

    // Hide the window and the DestroyWindow function
    // is used in the destructor
    ShowWindow( SW_HIDE );

    if ( m_pSpecialHelp )
    {
        m_pSpecialHelp->ShowWindow( SW_HIDE );
    }
}

/////////////////////////////////////////////////////////////////////////////
// StrEditHistoric message handlers

void StrEditHistoric::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    // Go in only if we are in read only
    // On Return
    if( nChar == 0x0D )
    {
        Edit::SetModify( TRUE );
        SetGoNext( TRUE );
        DestroyEdit();
        return;
    }

    // If Tab go to next
    if( nChar == 0x09 )
    {
        Edit::SetModify( TRUE );
        SetGoNext( TRUE );
        DestroyEdit();
        return;
    }

    // On Esc
    if( nChar == 0x1B )
    {
        Edit::SetModify( FALSE );
        DestroyEdit();
        return;
    }

    // Test if it is necessary to check the length
    // do not check if backspace
    if ( GetMaxChar() > 0 && nChar != 0x08 )
    {
        CString strTemp;
        GetWindowText( strTemp );

        // If outside of the maximum char,
        // play a sound and ignore the char typed.
        if ( strTemp.GetLength() + 1 > GetMaxChar() )
        {
            MessageBeep( MB_ICONEXCLAMATION );
            return;
        }
    }

    ZCIntelliEdit::OnChar( nChar, nRepCnt, nFlags );
}

void StrEditHistoric::OnKillFocus( CWnd* pNewWnd )
{
    ZCIntelliEdit::OnKillFocus( pNewWnd );

    if ( !HasFocus() )
    {
        DestroyEdit();
    }
}

/////////////////////////////////////////////////////////////////////////////
// NumEditHistoric

BEGIN_MESSAGE_MAP( NumEditHistoric, ZCIntelliEdit )
    //{{AFX_MSG_MAP(NumEditHistoric)
    ON_WM_CHAR()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

NumEditHistoric::NumEditHistoric()
    : Edit(),
      ZCIntelliEdit()
{
}

NumEditHistoric::~NumEditHistoric()
{
    if ( IsWindow( GetSafeHwnd() ) )
    {
        HideCaret();
    }

    Edit::~Edit();
}

// Create ----------------------------------------------------
//
// Author        :    Aigroz Dominique
// Date            :    14/12/1994
// Description    :    This function create an edit box on the
//                    PlanFin on the object place.
//
// Parameters    :    strName        the name to search in the list.
// Return        :    the object value.
//
// Remarks        :    
// Modifications:    04/04/1995    Aigroz Dominique
//                        Set a minimum size for the edit box.
//
//----------------------------------------------------------------------------
void NumEditHistoric::Create( BOOL                    DesignerMode,
                              CWnd*                    pParentWnd,
                              CDC*                    pDC,
                              ZDDocument*            pDoc,
                              PlanFinObject*        pEditedObj,
                              ZBFieldRepository*    pFieldRepository,
                              BOOL                    AutoCalculateOption,
                              BOOL                    GoNextEditOption )
{
    PreCreateEdit( DesignerMode,
                   pParentWnd,
                   pDC,
                   pDoc,
                   pEditedObj,
                   pFieldRepository,
                   AutoCalculateOption,
                   GoNextEditOption );

    DWORD dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

    if ( ZCIntelliEdit::Create( dwStyle, m_Rect, pParentWnd, 0 ) == FALSE )
    {
        return;
    }

    ZCIntelliEdit::Initialize( GetArrayOfValues() );

    CString sStr = m_pEditedObj->GetFormatedObject();
    SetWindowText( sStr );

    SetFocus();
    ShowCaret();
}

// Modifications:    06/04/1995    Aigroz Dominique
//                        Add the notification when the field change.
//                        I did that on the NumEdit standard but not
//                        in the NumEditHistoric.
//
void NumEditHistoric::DestroyEdit()
{
    // Only if required
    if( m_Save )
    {
        CString strTemp;
        GetWindowText( strTemp );

        if ( strTemp.IsEmpty() )
        {
            m_pEditedObj->EmptyObject();
        }
        else
        {
            // Keep the historical changes
            AddToHistoric( strTemp );
            m_pEditedObj->ConvertFormatedObject( strTemp, FALSE );
        }

        // To notify the application that a number changed.
        if ( m_AutoCalculateOption )
        {
            AfxGetMainWnd()->SendMessageToDescendants( ID_CALCULATE_MESSAGE, 0, 0 );
        }

        // To notify the view that on field change
        // Pass the adress of the object
        // then the routine that proceed the message
        // can know wich object has changed
        AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)m_pEditedObj );

        // Save Only one time
        m_Save = FALSE;

        if ( m_GoNext )
        {
            AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_EDITNEXT, 0, (LPARAM)m_pEditedObj );
        }
    }

    // Hide the window and the DestroyWindow function
    // is used in the destructor
    ShowWindow( SW_HIDE );

    if ( m_pSpecialHelp )
    {
        m_pSpecialHelp->ShowWindow( SW_HIDE );
    }
}

/////////////////////////////////////////////////////////////////////////////
// NumEditHistoric message handlers

void NumEditHistoric::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    // Go in only if we are in read only
    // On Return
    if( nChar == 0x0D )
    {
        Edit::SetModify( TRUE );
        SetGoNext( TRUE );
        DestroyEdit();
        return;
    }

    // If Tab go to next
    if( nChar == 0x09 )
    {
        Edit::SetModify( TRUE );
        SetGoNext( TRUE );
        DestroyEdit();
        return;
    }

    // On Esc
    if( nChar == 0x1B )
    {
        Edit::SetModify( FALSE );
        DestroyEdit();
        return;
    }

    // Check the validity of the char
    if( !isdigit( nChar ) && nChar != '.' && nChar != ',' && nChar != '\'' && nChar != '%' && nChar != 0x08 )
    {
        return;
    }

    ZCIntelliEdit::OnChar( nChar, nRepCnt, nFlags );
}

void NumEditHistoric::OnKillFocus( CWnd* pNewWnd )
{
    ZCIntelliEdit::OnKillFocus( pNewWnd );

    if ( !HasFocus() )
    {
        DestroyEdit();
    }
}

/////////////////////////////////////////////////////////////////////////////
// FieldNameEdit

BEGIN_MESSAGE_MAP( FieldNameEdit, ZCIntelliEdit )
    //{{AFX_MSG_MAP(FieldNameEdit)
    ON_WM_CHAR()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

FieldNameEdit::FieldNameEdit( int iMaxChar )
    : Edit(),
      ZCIntelliEdit(),
      m_iMaxChar( iMaxChar )
{
}

FieldNameEdit::~FieldNameEdit()
{
    if ( IsWindow( GetSafeHwnd() ) )
    {
        HideCaret();
    }

    Edit::~Edit();
}

// Create ----------------------------------------------------
//
// Author        :    Aigroz Dominique
// Date            :    14/12/1994
// Description    :    This function create an edit box on the
//                    PlanFin on the object place.
//
// Parameters    :    strName        the name to search in the list.
// Return        :    the object value.
//
// Remarks        :    
// Modifications:    04/04/1995    Aigroz Dominique
//                        Set a minimum size for the edit box.
//
//----------------------------------------------------------------------------
void FieldNameEdit::Create( BOOL                DesignerMode,
                            CWnd*                pParentWnd,
                            CDC*                pDC,
                            ZDDocument*            pDoc,
                            PlanFinObject*        pEditedObj,
                            ZBFieldRepository*    pFieldRepository,
                            BOOL                AutoCalculateOption,
                            BOOL                GoNextEditOption )
{
    PreCreateEdit( DesignerMode,
                   pParentWnd,
                   pDC,
                   pDoc,
                   pEditedObj,
                   pFieldRepository,
                   AutoCalculateOption,
                   GoNextEditOption );

    DWORD dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

    if ( ZCIntelliEdit::Create( dwStyle, m_Rect, pParentWnd, 0 ) == FALSE )
    {
        return;
    }

    ZCIntelliEdit::Initialize( pDoc->GetObjectFieldNameArray() );

    SetWindowText( m_pEditedObj->GetObjectName() );
    SetSel( 0, -1 );
    ShowWindow( SW_SHOW );
    SetFocus();
    ShowCaret();
}

void FieldNameEdit::DestroyEdit()
{
    // Save Only if required
    if( m_Save )
    {
        CString strTemp;

        GetWindowText( strTemp );
        m_pEditedObj->SetObjectName( strTemp );

        // Check field name
        m_pDoc->CheckMultiColumnMemberField( m_pEditedObj );
        m_pDoc->AddFieldNameInObectArray( strTemp );

        // Save Only one time
        m_Save = FALSE;
    }

    // Hide the window and the DestroyWindow function
    // is used in the destructor
    ShowWindow( SW_HIDE );

    if ( m_pSpecialHelp )
    {
        m_pSpecialHelp->ShowWindow( SW_HIDE );
    }
}

/////////////////////////////////////////////////////////////////////////////
// FieldNameEdit message handlers

void FieldNameEdit::OnKillFocus( CWnd* pNewWnd )
{
    ZCIntelliEdit::OnKillFocus( pNewWnd );

    // Test if the control still have the focus,
    // if not, destroy the edit
    if ( HasFocus() == false )
    {
        DestroyEdit();
    }
}

void FieldNameEdit::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    if( nChar == 0x0D )
    {
        Edit::SetModify( TRUE );

        if ( m_GoNextEditOption )
        {
            m_GoNext = TRUE;
        }

        DestroyEdit();
        return;
    }

    // If Tab go to next
    if( nChar == 0x09 )
    {
        Edit::SetModify( TRUE );
        m_GoNext = TRUE;
        DestroyEdit();
        return;
    }

    if( nChar == 0x1B )
    {
        Edit::SetModify( FALSE );
        DestroyEdit();
        return;
    }

    ZCIntelliEdit::OnChar( nChar, nRepCnt, nFlags );
}

/////////////////////////////////////////////////////////////////////////////
// MaskEdit

BEGIN_MESSAGE_MAP( MaskEdit, ZMaskEdit )
    //{{AFX_MSG_MAP(MaskEdit)
    ON_WM_KILLFOCUS()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

MaskEdit::MaskEdit()
    : Edit(),
      ZMaskEdit()
{
}

MaskEdit::~MaskEdit()
{
    if ( IsWindow( GetSafeHwnd() ) )
    {
        HideCaret();
    }

    Edit::~Edit();
}

// Create ----------------------------------------------------
//
// Author        :    Aigroz Dominique
// Date            :    14/12/1994
// Description    :    This function create an edit box on the
//                    PlanFin on the object place.
//
// Parameters    :    strName        the name to search in the list.
// Return        :    the object value.
//
// Remarks        :    
// Modifications:    04/04/1995    Aigroz Dominique
//                        Set a minimum size for the edit box.
//
//----------------------------------------------------------------------------
void MaskEdit::Create( BOOL                    DesignerMode,
                       CWnd*                pParentWnd,
                       CDC*                    pDC,
                       ZDDocument*            pDoc,
                       PlanFinObject*        pEditedObj,
                       ZBFieldRepository*    pFieldRepository,
                       BOOL                    AutoCalculateOption,
                       BOOL                    GoNextEditOption )
{
    if ( !pEditedObj->IsKindOf( RUNTIME_CLASS( PLFNMaskString ) ) )
    {
        return;
    }

    PreCreateEdit( DesignerMode,
                   pParentWnd,
                   pDC,
                   pDoc,
                   pEditedObj,
                   pFieldRepository,
                   AutoCalculateOption,
                   GoNextEditOption );

    DWORD dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

    if ( m_ReadOnly )
    {
        dwStyle |= ES_READONLY;
    }

    if ( ZMaskEdit::Create( dwStyle, m_Rect, pParentWnd, 0 ) == FALSE )
    {
        return;
    }

    ZMaskEdit::Init( ( (PLFNMaskString*)m_pEditedObj )->GetMask(), m_pEditedObj->GetUnformatedObject() );
    SetSel( 0, -1 );
    ShowWindow( SW_SHOW );
    SetFocus();
    ShowCaret();
}

void MaskEdit::DestroyEdit()
{
    // Save Only if required
    if( m_Save )
    {
        CString strTemp = GetData();
        m_pEditedObj->ConvertFormatedObject( strTemp, FALSE );

        // To notify the view that on field change
        // Pass the adress of the object
        // then the routine that proceed the message
        // can know wich object has changed
        AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)m_pEditedObj );

        // Save Only one time
        m_Save = FALSE;

        if ( m_GoNext )
        {
            AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_EDITNEXT, 0, (LPARAM)m_pEditedObj );
        }
    }

    // Hide the window and the DestroyWindow function
    // is used in the destructor
    ShowWindow( SW_HIDE );

    if ( m_pSpecialHelp )
    {
        m_pSpecialHelp->ShowWindow( SW_HIDE );
    }
}

/////////////////////////////////////////////////////////////////////////////
// Edit message handlers

void MaskEdit::OnKillFocus( CWnd* pNewWnd )
{
    ZMaskEdit::OnKillFocus( pNewWnd );
    DestroyEdit();
}

void MaskEdit::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    if( nChar == 0x0D )
    {
        Edit::SetModify( TRUE );

        if ( m_GoNextEditOption )
        {
            m_GoNext = TRUE;
        }

        DestroyEdit();
        return;
    }

    // If Tab go to next
    if( nChar == 0x09 )
    {
        Edit::SetModify( TRUE );
        m_GoNext = TRUE;
        DestroyEdit();
        return;
    }

    if( nChar == 0x1B )
    {
        Edit::SetModify( FALSE );
        DestroyEdit();
        return;
    }

    ZMaskEdit::OnChar( nChar, nRepCnt, nFlags );
}

/////////////////////////////////////////////////////////////////////////////
// MultiColumnEdit

BEGIN_MESSAGE_MAP( MultiColumnEdit, ZCGridCtrl )
    //{{AFX_MSG_MAP(MultiColumnEdit)
    ON_WM_KILLFOCUS()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

MultiColumnEdit::MultiColumnEdit()
    : Edit(),
      ZCGridCtrl()
{
    m_cx            = 0;
    m_nEdit            = -1;
    m_ColumnsBuilt    = FALSE;
}

MultiColumnEdit::~MultiColumnEdit()
{
    if ( IsWindow( GetSafeHwnd() ) )
    {
        HideCaret();
    }

    Edit::~Edit();
}

// Create ----------------------------------------------------
//
// Author        :    Aigroz Dominique
// Date            :    14/12/1994
// Description    :    This function create an edit box on the
//                    PlanFin on the object place.
//
// Parameters    :    strName        the name to search in the list.
// Return        :    the object value.
//
// Remarks        :    
// Modifications:    04/04/1995    Aigroz Dominique
//                        Set a minimum size for the edit box.
//
//----------------------------------------------------------------------------
void MultiColumnEdit::Create( BOOL                    DesignerMode,
                              CWnd*                    pParentWnd,
                              CDC*                    pDC,
                              ZDDocument*            pDoc,
                              PlanFinObject*        pEditedObj,
                              ZBFieldRepository*    pFieldRepository,
                              BOOL                    AutoCalculateOption,
                              BOOL                    GoNextEditOption )
{
    if ( !pEditedObj->IsKindOf( RUNTIME_CLASS( PLFNMultiColumn ) ) )
    {
        return;
    }

    PreCreateEdit( DesignerMode,
                   pParentWnd,
                   pDC,
                   pDoc,
                   pEditedObj,
                   pFieldRepository,
                   AutoCalculateOption,
                   GoNextEditOption );

    DWORD dwStyle = WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS;

    // If not readonly, allow edit labels
    if ( m_ReadOnly == FALSE )
    {
        dwStyle |= LVS_EDITLABELS;
    }

    if ( ZCGridCtrl::Create( dwStyle, m_Rect, pParentWnd, 0 ) == FALSE )
    {
        return;
    }

    // Set the extended styles
    SetExtendedStyle( LVS_EX_GRIDLINES );

    MultiColumnEdit::BuildColumns();
    MultiColumnEdit::FillControl();

    ShowWindow( SW_SHOW );
    SetFocus();
    ShowCaret();

    // Initialize the cell edition flag
    m_StartEditCell = false;
}

void MultiColumnEdit::BuildColumns()
{
    if ( m_ColumnsBuilt )
    {
        return;
    }

    if ( ( (PLFNMultiColumn*)m_pEditedObj )->GetColumnCount() > 0 )
    {
        LV_COLUMN lvColumn;
        lvColumn.mask    = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvColumn.fmt    = LVCFMT_LEFT;

        // Set up columns
        for( size_t i = 0; i < ( (PLFNMultiColumn*)m_pEditedObj )->GetColumnCount(); i++ )
        {
            ZBFieldColumn* pColumn = ( (PLFNMultiColumn*)m_pEditedObj )->GetColumnAt( i );

            if ( pColumn )
            {
                // Retreive the width
                lvColumn.cx = pColumn->GetWidth();

                // Retreive the column name
                int        len            = pColumn->GetHeaderName().GetLength();
                CString    temp        = pColumn->GetHeaderName();
                TCHAR*    szBuffer    = new TCHAR[len + 1];

                strcpy( szBuffer, temp.GetBuffer( len ) );
                temp.ReleaseBuffer();

                lvColumn.pszText = szBuffer;

                // Insert column
                InsertColumn( i, &lvColumn );

                delete szBuffer;
            }
        }
    }

    m_ColumnsBuilt = TRUE;
}

void MultiColumnEdit::FillControl()
{
    if ( !( ( (PLFNMultiColumn*)m_pEditedObj )->GetColumnCount() > 0 ) )
    {
        return;
    }

    size_t RowCount = ( (PLFNMultiColumn*)m_pEditedObj )->GetColumnAt( 0 )->GetValueCount();

    // Fill all columns with all values
    // Set up columns
    for( size_t i = 0; i < RowCount; i++ )
    {
        CStringArray Values;
        ( (PLFNMultiColumn*)m_pEditedObj )->GetRowValues( Values, i );

        size_t        Item        = 0;
        CItemInfo*    lpItemInfo    = new CItemInfo();

        // Add items text
        lpItemInfo->SetItemText( Values.GetAt( Item ) );

        for ( ++Item; Item < (size_t)Values.GetSize(); ++Item )
        {
            lpItemInfo->SetSubItemText( Item - 1, Values.GetAt( Item ), -1 );
        }

        InsertRootItem( lpItemInfo );
    }
}

void MultiColumnEdit::DestroyEdit()
{
    // Save Only if required
    if( m_Save )
    {
        // Get the size of each header
        CHeaderCtrl* pHeader = GetHeaderCtrl();

        int nColCount = pHeader->GetItemCount();

        // Saves the column width
        for ( int i = 0; i < nColCount; i++ )
        {
            ZBFieldColumn* pColumn = ( (PLFNMultiColumn*)m_pEditedObj )->GetColumnAt( i );

            if ( pColumn )
            {
                pColumn->SetWidth( GetColumnWidth( i ) );
            }
        }

        // To notify the view that on field change
        // Pass the adress of the object
        // then the routine that proceed the message
        // can know wich object has changed
        AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)m_pEditedObj );

        // Save Only one time
        m_Save = FALSE;

        if ( m_GoNext )
        {
            AfxGetMainWnd()->SendMessageToDescendants( ID_FIELD_EDITNEXT, 0, (LPARAM)m_pEditedObj );
        }
    }

    // Hide the window and the DestroyWindow function
    // is used in the destructor
    ShowWindow( SW_HIDE );

    if ( m_pSpecialHelp )
    {
        m_pSpecialHelp->ShowWindow( SW_HIDE );
    }
}

// Called before editing the cell
void MultiColumnEdit::OnBeginLabelEdit( int iItem, int iSubItem )
{
    m_StartEditCell = true;
}

// called after having updated the cell
void MultiColumnEdit::OnEndLabelEdit( LPCSTR pszText, int iItem, int iSubItem )
{
    // Set the value to the object
    ( (PLFNMultiColumn*)m_pEditedObj )->SetColumnRowValue( iSubItem, iItem, pszText );
    m_StartEditCell = false;
}

/////////////////////////////////////////////////////////////////////////////
// MultiColumnEdit message handlers

void MultiColumnEdit::OnKillFocus( CWnd* pNewWnd )
{
    ZCGridCtrl::OnKillFocus( pNewWnd );

    // Only if we are not in cell edition
    if ( m_StartEditCell == false )
    {
        DestroyEdit();
    }
}

void MultiColumnEdit::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    if( nChar == 0x0D )
    {
        Edit::SetModify( TRUE );

        if ( m_GoNextEditOption )
        {
            m_GoNext = TRUE;
        }

        DestroyEdit();
        return;
    }

    // If Tab go to next
    if( nChar == 0x09 )
    {
        Edit::SetModify( TRUE );
        m_GoNext = TRUE;
        DestroyEdit();
        return;
    }

    if( nChar == 0x1B )
    {
        Edit::SetModify( FALSE );
        DestroyEdit();
        return;
    }

    ZCGridCtrl::OnChar( nChar, nRepCnt, nFlags );
}
