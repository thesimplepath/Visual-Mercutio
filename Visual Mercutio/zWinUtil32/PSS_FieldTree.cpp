/****************************************************************************
 * ==> PSS_FieldTree -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a field tree                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_FieldTree.h"

// processsoft
#include "zBaseLib\PSS_DocumentData.h"
#include "zBaseLib\PSS_ObjectUtility.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#endif
#ifdef _WIN32
    #include "zWinUtil32Res.h"
#endif
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_FieldTree
//---------------------------------------------------------------------------
PSS_FieldTree::PSS_FieldTree(ZITreeCtrl* pTreeCtrl, ZDDocument* pDoc, PSS_FieldRepository* pFieldRepository) :
    m_pTreeCtrl(pTreeCtrl), 
    m_pDoc(pDoc), 
    m_pFieldRepository(pFieldRepository),
    m_HasBeenInitialized(FALSE)
{}
//---------------------------------------------------------------------------
PSS_FieldTree::PSS_FieldTree(const PSS_FieldTree& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_FieldTree::~PSS_FieldTree()
{}
//---------------------------------------------------------------------------
const PSS_FieldTree& PSS_FieldTree::operator = (const PSS_FieldTree& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_FieldTree::Initialize(ZITreeCtrl* pTreeCtrl, ZDDocument* pDoc, PSS_FieldRepository* pFieldRepository)
{
    m_pTreeCtrl        = pTreeCtrl;
    m_pDoc             = pDoc;
    m_pFieldRepository = pFieldRepository;

    InitializeTree();
    Refresh();
}
//---------------------------------------------------------------------------
void PSS_FieldTree::Empty()
{
    m_pDoc = NULL;

    if (m_pTreeCtrl)
        m_pTreeCtrl->DeleteAllItems();
}
//---------------------------------------------------------------------------
void PSS_FieldTree::Refresh()
{
    if (!m_pTreeCtrl)
        return;

    m_pTreeCtrl->DeleteAllItems();
    CreateTree();
}
//---------------------------------------------------------------------------
PSS_FieldObjectDefinition* PSS_FieldTree::GetSelectedRepositoryField()
{
    if (!m_pTreeCtrl)
        return NULL;

    HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();

    if (hSelected)
        return dynamic_cast<PSS_FieldObjectDefinition*>((CObject*)m_pTreeCtrl->GetItemData(hSelected));

    return NULL;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_FieldTree::GetSelectedDocumentField()
{
    if (!m_pTreeCtrl)
        return NULL;

    HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();

    if (hSelected)
        return dynamic_cast<PSS_PlanFinObject*>((CObject*)m_pTreeCtrl->GetItemData(hSelected));

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_FieldTree::OnFieldListChanged()
{
    Refresh();
}
//---------------------------------------------------------------------------
HTREEITEM PSS_FieldTree::AddTypeItem(const CString& fieldType, int iconIndex, HTREEITEM hParentTreeItem)
{
    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)fieldType);
    curTreeItem.item.lParam         = LPARAM(NULL);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_FieldTree::AddDocumentItem(PSS_DocumentData* pData, HTREEITEM hParentTreeItem, int iconIndex)
{
    if (!pData)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)pData->GetStamp().GetTitle());
    curTreeItem.item.lParam         = LPARAM(NULL);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
void PSS_FieldTree::AddRepositoryFieldItem(PSS_FieldObjectDefinition* pField, HTREEITEM hParentTreeItem)
{
    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = GetItemIndex(pField->GetObject());
    curTreeItem.item.iSelectedImage = GetItemIndex(pField->GetObject());
    curTreeItem.item.pszText        = (char*)((const char*)pField->GetFieldName());
    curTreeItem.item.lParam         = LPARAM(pField);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    m_pTreeCtrl->InsertItem(&curTreeItem);

}
//---------------------------------------------------------------------------
HTREEITEM PSS_FieldTree::AddDocumentFieldItem(PSS_PlanFinObject* pObj, HTREEITEM hParentTreeItem)
{
    if (!pObj)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = GetItemIndex(pObj);
    curTreeItem.item.iSelectedImage = GetItemIndex(pObj);
    curTreeItem.item.pszText        = (char*)((const char*)pObj->GetObjectName());
    curTreeItem.item.lParam         = LPARAM(pObj);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
int PSS_FieldTree::GetItemIndex(PSS_PlanFinObject* pObj)
{
    switch (PSS_ObjectUtility::GetClassNameID(pObj))
    {
        case IDS_STATICTEXT_CLASS:       return 6;
        case IDS_DATE_CLASS:             return 9;
        case IDS_CALCULATED_CLASS:       return 10;
        case IDS_HISTOAMOUNT_CLASS:
        case IDS_AMOUNT_CLASS:           return 11;
        case IDS_MULTITEXTSTATIC_CLASS:
        case IDS_MULTITEXT_CLASS:        return 8;
        case IDS_HISTOTEXT_CLASS:
        case IDS_TEXT_CLASS:             return 7;
        case IDS_SQUARETEXT_CLASS:       return 15;
        case IDS_NUMBEREDSECTION_CLASS:  return 17;
        case IDS_LINE_CLASS:             return 3;
        case IDS_RECTANGLEROUNDED_CLASS: return 19;
        case IDS_RECTANGLE_CLASS:        return 5;
        case IDS_BITMAP_CLASS:           return 18;
        case IDS_CHECK_CLASS:            return 14;
        case IDS_RADIO_CLASS:            return 13;
        case IDS_MASKSTRING_CLASS:
        case IDS_MASKSTRINGHISTO_CLASS:  return 12;
        case IDS_MULTICOLUMN_CLASS:      return 16;
        default: break;
    }

    return -1;
}
//---------------------------------------------------------------------------
void PSS_FieldTree::CreateTree()
{
    HTREEITEM hRootDocument   = AddTypeItem(m_DocumentType,   0);
    HTREEITEM hRootRepository = AddTypeItem(m_RepositoryType, 1);
    HTREEITEM hDocument       = NULL;

    if (!m_pDoc)
        AddTypeItem (m_NoDocument, -1, hRootDocument);
    else
    {
        const std::size_t docDataCount = m_pDoc->GetDocumentDataCount();

        // iterate through document data
        for (std::size_t i = 0; m_pDoc && i < docDataCount; ++i)
        {
            PSS_DocumentData* pDocData = m_pDoc->GetDocumentDataAt(i);

            if (pDocData && !pDocData->IsBinaryDataValid())
            {
                hDocument = AddDocumentItem(pDocData, hRootDocument, 2);

                POSITION           pPosition;
                PSS_PlanFinObject* pObjTemp = NULL;

                pPosition = pDocData->GetObjectList().GetHeadPosition();

                while (pPosition)
                {
                    pObjTemp = (PSS_PlanFinObject*)pDocData->GetObjectList().GetNext(pPosition);
                    AddDocumentFieldItem(pObjTemp, hDocument);
                }
            }
        }
    }

    if (m_pFieldRepository)
    {
        const std::size_t fieldCount = m_pFieldRepository->GetFieldCount();

        // iterate through fields
        for (std::size_t index = 0; index < fieldCount; ++index)
            AddRepositoryFieldItem(m_pFieldRepository->GetFieldAt(index), hRootRepository);
    }
    else
        AddTypeItem (m_NoRepository, -1, hRootRepository);

    m_pTreeCtrl->ExpandRoot(TRUE);
}
//---------------------------------------------------------------------------
void PSS_FieldTree::InitializeTree()
{
    if (m_HasBeenInitialized || !m_pTreeCtrl)
        return;

    // set styles
    m_pTreeCtrl->HasButtons();
    m_pTreeCtrl->HasLines();
    m_pTreeCtrl->LinesAtRoot();

    // load images
    m_pTreeCtrl->LoadImageList(IDB_FIELDDOCUMENT_TYPES, 17, 1, RGB(255, 255, 255));
    m_DocumentType.LoadString(IDS_FIELDDOCUMENTTYPE);
    m_RepositoryType.LoadString(IDS_REPOSITORYDOCUMENTTYPE);
    m_NoDocument.LoadString(IDS_NODOCUMENTSELECTED);
    m_NoRepository.LoadString(IDS_NOREPOSITORYFIELDS);

    m_HasBeenInitialized = TRUE;
}
//---------------------------------------------------------------------------
