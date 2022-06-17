/****************************************************************************
 * ==> PSS_PackageSymbolBP -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a package symbol for banking process              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PackageSymbolBP.h"

// processsoft
#include "zBaseLib\PSS_File.h"
#include "zBaseSym\zBaseSymRes.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "PSS_ProcessGraphModelMdlBP.h"

// resources
#include "zModelBPRes.h"
#include "zBaseLib\PSS_DrawFunctions.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
PSS_Bitmap PSS_PackageSymbolBP::m_LinkedToFileBitmap;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PackageSymbolBP, PSS_Symbol, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PackageSymbolBP
//---------------------------------------------------------------------------
PSS_PackageSymbolBP::PSS_PackageSymbolBP(const CString& name, const CString& fileName) :
    PSS_Symbol(),
    m_pPackageDoc(NULL),
    m_FileNameLinkedTo(fileName),
    m_ShowPreview(false)
{
    PSS_Symbol::SetSymbolName(name);

    if (!m_LinkedToFileBitmap.IsValid())
        m_LinkedToFileBitmap.LoadBitmap(IDB_LINKTOMODEL);
}
//---------------------------------------------------------------------------
PSS_PackageSymbolBP::PSS_PackageSymbolBP(const PSS_PackageSymbolBP& other) :
    PSS_Symbol(),
    m_pPackageDoc(NULL),
    m_ShowPreview(false)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PackageSymbolBP::~PSS_PackageSymbolBP()
{}
//---------------------------------------------------------------------------
PSS_PackageSymbolBP& PSS_PackageSymbolBP::operator = (const PSS_PackageSymbolBP& other)
{
    PSS_Symbol::operator = ((const PSS_Symbol&)other);

    m_FileNameLinkedTo = other.m_FileNameLinkedTo;
    m_ShowPreview      = other.m_ShowPreview;

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_PackageSymbolBP::Create(const CString& name, const CString& fileName)
{
    BOOL result = FALSE;

    try
    {
        m_IsInCreationProcess = true;

        if (!fileName.IsEmpty())
            m_FileNameLinkedTo = fileName;

        result = PSS_Symbol::Create(IDR_PACKAGE_SYM,
                                    ::AfxFindResourceHandle(MAKEINTRESOURCE(IDR_PACKAGE_SYM), _T("Symbol")),
                                    name);

        if (!CreateSymbolProperties())
            result = FALSE;
    }
    catch (...)
    {
        m_IsInCreationProcess = false;
        throw;
    }

    m_IsInCreationProcess = false;
    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_PackageSymbolBP::CreateEmptyChildModel(CODModel* pParent)
{
    if (!m_pModel)
    {
        m_pModel = new PSS_ProcessGraphModelMdlBP(GetSymbolName(), reinterpret_cast<PSS_ProcessGraphModelMdlBP*>(pParent));
    }
    else
        return FALSE;
    return m_pModel != NULL;
}
//---------------------------------------------------------------------------
CODComponent* PSS_PackageSymbolBP::Dup() const
{
    return new PSS_PackageSymbolBP(*this);
}
//---------------------------------------------------------------------------
void PSS_PackageSymbolBP::CopySymbolDefinitionFrom(const CODSymbolComponent& src)
{
    PSS_Symbol::CopySymbolDefinitionFrom(src);

    const PSS_PackageSymbolBP* pOther = dynamic_cast<const PSS_PackageSymbolBP*>(&src);

    if (pOther)
    {
        m_pPackageDoc      = pOther->m_pPackageDoc;
        m_CommentRect      = pOther->m_CommentRect;
        m_FileNameLinkedTo = pOther->m_FileNameLinkedTo;
        m_ShowPreview      = pOther->m_ShowPreview;
    }
}
//---------------------------------------------------------------------------
BOOL PSS_PackageSymbolBP::SetSymbolName(const CString& value)
{
    const BOOL result = PSS_Symbol::SetSymbolName(value);

    if (m_pModel)
        m_pModel->SetName(value);

    return result;
}
//---------------------------------------------------------------------------
bool PSS_PackageSymbolBP::LoadPackage(PSS_ProcessModelDocTmpl* pDocTmpl, PSS_ProcessGraphModelMdl* pParent)
{
    PSS_File file(m_FileNameLinkedTo);

    // check if the file exists
    if (!file.Exist())
        return false;

    if (m_pPackageDoc)
        if (!UnloadPackage())
            return false;

    CDocument*                pDoc      = pDocTmpl->OpenDocumentFile(m_FileNameLinkedTo, FALSE);
    PSS_ProcessGraphModelDoc* pModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc);

    if (pModelDoc)
    {
        m_pPackageDoc = pModelDoc;

        PSS_ProcessGraphModelMdl* pModel = pModelDoc->GetModel();

        // assign the name
        if (pModel)
            PSS_Symbol::SetSymbolName(pModel->GetModelName());

        // assign the model
        m_pModel = pModel;

        // assign the model parent
        if (m_pModel && pParent)
            m_pModel->SetParent(pParent);
    }
    else
    if (pDoc)
    {
        pDoc->OnCloseDocument();
        delete pDoc;
    }

    return m_pPackageDoc;
}
//---------------------------------------------------------------------------
bool PSS_PackageSymbolBP::UnloadPackage()
{
    if (!m_pPackageDoc)
        return false;

    m_pPackageDoc->OnCloseDocument();
    m_pPackageDoc = NULL;
    m_pModel      = NULL;
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PackageSymbolBP::AcceptDropItem(CObject* pObj, const CPoint& point)
{
    // don't allow the drop if the symbol isn't local
    if (!IsLocal())
        return false;

    return PSS_Symbol::AcceptDropItem(pObj, point);
}
//---------------------------------------------------------------------------
bool PSS_PackageSymbolBP::DropItem(CObject* pObj, const CPoint& point)
{
    return PSS_Symbol::DropItem(pObj, point);
}
//---------------------------------------------------------------------------
void PSS_PackageSymbolBP::Serialize(CArchive& ar)
{
    PSS_Symbol::Serialize(ar);

    // only if the object is serialized from or to a document
    if (ar.m_pDocument)
    {
        if (ar.IsStoring())
        {
            TRACE("PSS_PackageSymbolBP::Serialize - Start save\n");

            ar << WORD(m_ShowPreview);
            ar << m_FileNameLinkedTo;

            TRACE("PSS_PackageSymbolBP::Serialize - End save\n");
        }
        else
        {
            TRACE("PSS_PackageSymbolBP::Serialize - Start read\n");

            WORD wValue;
            ar >> wValue;
            m_ShowPreview = bool(wValue);

            ar >> m_FileNameLinkedTo;

            // if linked to file name, serialize an empty model pointer
            if (IsLinkedToFileName())
                m_pModel = NULL;

            TRACE("PSS_PackageSymbolBP::Serialize - End read\n");
        }

        if (m_pModel)
            m_pModel->SetName(GetSymbolName());
    }
}
//---------------------------------------------------------------------------
BOOL PSS_PackageSymbolBP::OnDoubleClick()
{
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PackageSymbolBP::OnDraw(CDC* pDC)
{
    PSS_Symbol::OnDraw(pDC);

    if (IsLinkedToFileName() && m_LinkedToFileBitmap.IsValid())
        ShowBitmap(HBITMAP(m_LinkedToFileBitmap),
                   pDC->m_hDC,
                   AfxGetInstanceHandle(),
                   m_LinkedToFileBitmapPosition.x,
                   m_LinkedToFileBitmapPosition.y);
}
//---------------------------------------------------------------------------
bool PSS_PackageSymbolBP::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    toolTipText.Format(IDS_FS_BPPACKAGE_TOOLTIP, (const char*)GetSymbolName());

    if (IsLinkedToFileName())
    {
        CString linkToFile;
        linkToFile.Format(IDS_FS_BPPACKAGE_LINKTF_TOOLTIP, m_FileNameLinkedTo);
        toolTipText += linkToFile;
    }

    if (mode == PSS_Symbol::IEToolTipMode::IE_TT_Design)
    {
        // todo -cFeature -oJean: need to implement the result of the control checking
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_PackageSymbolBP::AdjustElementPosition()
{
    PSS_Symbol::AdjustElementPosition();

    // calculate the symbol position
    const CRect symbolPosition     = GetBounds();
    m_LinkedToFileBitmapPosition.x = symbolPosition.right - 25;
    m_LinkedToFileBitmapPosition.y = symbolPosition.top;
}
//---------------------------------------------------------------------------
