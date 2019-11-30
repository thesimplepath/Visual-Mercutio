// ZBBPPackageSymbol.cpp: implementation of the ZBBPPackageSymbol class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBBPPackageSymbol.h"

// processsoft
#include "zBaseLib\PSS_File.h"
#include "zBaseSym\zBaseSymRes.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "ProcGraphModelMdlBP.h"

// resources
#include "zModelBPRes.h"
#include "zBaseLib\PSS_DrawFunctions.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

PSS_Bitmap ZBBPPackageSymbol::m_LinkedToFileBitmap;

IMPLEMENT_SERIAL(ZBBPPackageSymbol, ZBSymbol, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBBPPackageSymbol::ZBBPPackageSymbol( const CString Name /*= ""*/, const CString fileName /*= ""*/ )
: m_FileNameLinkedTo(fileName), m_DisplayPreview(false), m_pPackageDoc(NULL)
{
    ZBSymbol::SetSymbolName(Name); 
    if (!m_LinkedToFileBitmap.IsValid())
        m_LinkedToFileBitmap.LoadBitmap( IDB_LINKTOMODEL );

}

ZBBPPackageSymbol::~ZBBPPackageSymbol()
{
}

ZBBPPackageSymbol::ZBBPPackageSymbol(const ZBBPPackageSymbol& src)
{
    *this = src;
}

ZBBPPackageSymbol& ZBBPPackageSymbol::operator=(const ZBBPPackageSymbol& src)
{
    // Call the base class assignement operator
    ZBSymbol::operator=( (const ZBSymbol&)src);
    m_DisplayPreview = src.m_DisplayPreview;
    m_FileNameLinkedTo = src.m_FileNameLinkedTo;
    return *this;
}


CODComponent* ZBBPPackageSymbol::Dup() const
{
    return (new ZBBPPackageSymbol(*this));
}

BOOL ZBBPPackageSymbol::SetSymbolName(const CString value)
{
    BOOL bResult = ZBSymbol::SetSymbolName(value);
    if (m_pModel)
        m_pModel->SetName(value);
    return bResult;
}


// Drag and drop methods
bool ZBBPPackageSymbol::AcceptDropItem( CObject* pObj, const CPoint& pt )
{
    // JMR-MODIF - Le 19 décembre 2006 - Si le symbole n'est pas local, interdit l'opération de glisser-coller.
    if ( !IsLocal() )
    {
        return false;
    }

    return ZBSymbol::AcceptDropItem( pObj, pt );
}

bool ZBBPPackageSymbol::DropItem( CObject* pObj, const CPoint& pt )
{
    return ZBSymbol::DropItem( pObj, pt );
}



void ZBBPPackageSymbol::CopySymbolDefinitionFrom( CODSymbolComponent& src )
{
    // Class the base class method
    ZBSymbol::CopySymbolDefinitionFrom( src );
    if (ISA((&src),ZBBPPackageSymbol))
    {
        m_DisplayPreview = ((ZBBPPackageSymbol&)src).m_DisplayPreview;
        m_FileNameLinkedTo = ((ZBBPPackageSymbol&)src).m_FileNameLinkedTo;

        m_CommentRect = ((ZBBPPackageSymbol&)src).m_CommentRect;
        // Used to link the package to a file name
        m_FileNameLinkedTo = ((ZBBPPackageSymbol&)src).m_FileNameLinkedTo;
        m_pPackageDoc = ((ZBBPPackageSymbol&)src).m_pPackageDoc;

    }
}

BOOL ZBBPPackageSymbol::Create( const CString Name /*= ""*/, const CString fileName /*= ""*/ )
{
    m_IsInCreationProcess = true;

    if (!fileName.IsEmpty())
        m_FileNameLinkedTo = fileName;

    BOOL RetValue = ZBSymbol::Create( IDR_PACKAGE_SYM, AfxFindResourceHandle(MAKEINTRESOURCE(IDR_PACKAGE_SYM), _T("Symbol")), Name );

    if (!CreateSymbolProperties())
        RetValue = FALSE;

    m_IsInCreationProcess = false;

    return RetValue;
}

void ZBBPPackageSymbol::AdjustElementPosition()
{
    ZBSymbol::AdjustElementPosition();
/*
    // Recalculate the comment rect
    CODTextComponent* pText = GetCommentTextEdit();
    if (pText)
    {
        m_CommentRect = pText->GetBounds();
        m_CommentRect.DeflateRect( 1, 1 );
    }
*/
    // Calculate the position of symbols
    CRect    SymbolPosition = GetBounds();
    m_LinkedToFileBitmapPosition.x = SymbolPosition.right - 25;
    m_LinkedToFileBitmapPosition.y = SymbolPosition.top;
}

bool    ZBBPPackageSymbol::LoadPackage(PSS_ProcessModelDocTmpl* pDocTmpl, ZDProcessGraphModelMdl* pParent)
{
    // Check if the file exists
    PSS_File File(m_FileNameLinkedTo);
    if (!File.Exist())
        return false;

    if (m_pPackageDoc)
    {
        if (!UnloadPackage())
            return false;
    }
    CDocument*    pDoc = pDocTmpl->OpenDocumentFile( m_FileNameLinkedTo, FALSE );
    if (pDoc && ISA(pDoc, PSS_ProcessGraphModelDoc))
    {
        m_pPackageDoc = (PSS_ProcessGraphModelDoc*)pDoc;
        // Assign the name.
        ZBSymbol::SetSymbolName( ((PSS_ProcessGraphModelDoc*)pDoc)->GetModel()->GetModelName() );
        // Assign the pointer to the model
        m_pModel = ((PSS_ProcessGraphModelDoc*)pDoc)->GetModel();
        // Assign the model parent
        if (m_pModel && pParent)
            m_pModel->SetParent( pParent );
    }
    else
    {
        if (pDoc)
        {
            pDoc->OnCloseDocument();
            delete pDoc;
        }
    }
    return m_pPackageDoc != NULL;
}

bool    ZBBPPackageSymbol::UnloadPackage()
{
    if (m_pPackageDoc)
    {
        m_pPackageDoc->OnCloseDocument();
//        delete m_pPackageDoc;
        m_pPackageDoc = NULL;
        // And the model points to NULL
        m_pModel = NULL;
        return true;
    }
    return false;
}


void ZBBPPackageSymbol::OnDraw(CDC* pDC)
{
    ZBSymbol::OnDraw(pDC);
//    if (m_pModel && ISA(m_pModel,ZDProcessGraphModelMdl) && m_DisplayPreview)
//        reinterpret_cast<ZDProcessGraphModelMdl*>(m_pModel)->DrawMetaFile(pDC, m_CommentRect);
    if (IsLinkedToFileName() && m_LinkedToFileBitmap.IsValid())
    {
        ShowBitmap(HBITMAP(m_LinkedToFileBitmap), pDC->m_hDC, AfxGetInstanceHandle(), m_LinkedToFileBitmapPosition.x, m_LinkedToFileBitmapPosition.y);
//        m_LinkedToFileBitmap.DrawBitmap( pDC, NULL, m_LinkedToFileBitmapPosition.x, m_LinkedToFileBitmapPosition.y );
    }
}


void ZBBPPackageSymbol::Serialize(CArchive& ar)
{

    // Serialize the canvas model.
    ZBSymbol::Serialize(ar);

    // Only if the object is serialize from and to a document
    if (ar.m_pDocument)
    {
        if (ar.IsStoring())
        {
            TRACE( "ZBBPPackageSymbol::Serialize : Start Save\n" );

            ar << (WORD)m_DisplayPreview;
            ar << m_FileNameLinkedTo;

            TRACE( "ZBBPPackageSymbol::Serialize : End Save\n" );
        }
        else
        {
            TRACE( "ZBBPPackageSymbol::Serialize : Start Read\n" );

            WORD wValue;
            ar >> wValue;
            m_DisplayPreview = (wValue == 0) ? false : true;
            ar >> m_FileNameLinkedTo;
            // If is linked to file name
            // serialize null as model pointer
            if (IsLinkedToFileName())
                m_pModel = NULL;

            TRACE( "ZBBPPackageSymbol::Serialize : End Read\n" );
        }
        if (m_pModel)
            m_pModel->SetName( GetSymbolName() );
    }
}

BOOL ZBBPPackageSymbol::CreateEmptyChildModel(CODModel* pParent)
{
    if (!m_pModel)
    {
        m_pModel = new ZDProcessGraphModelMdlBP( GetSymbolName(), reinterpret_cast<ZDProcessGraphModelMdlBP*>(pParent) );
    }
    else
        return FALSE;
    return m_pModel != NULL;
}


BOOL ZBBPPackageSymbol::OnDoubleClick()
{
    return TRUE;
}


bool ZBBPPackageSymbol::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    toolTipText.Format(IDS_FS_BPPACKAGE_TOOLTIP, (const char*)GetSymbolName());

    if (IsLinkedToFileName())
    {
        CString LinkToFile;
        LinkToFile.Format( IDS_FS_BPPACKAGE_LINKTF_TOOLTIP, m_FileNameLinkedTo );
        toolTipText += LinkToFile;
    }
    return true;
}
