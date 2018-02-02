// Source file: fieldtreei.cpp

#include <StdAfx.h>

#include "fieldtreei.h"
#include "zRes32\ZRes.h"

#include "zBaseLib\DocData.h"

// BObjUtil
#include "zBaseLib\BObjUtil.h"

#ifndef _WIN32
	#include "ZWinUtil.h"
#endif
#ifdef _WIN32
	#include "ZWinUtil32.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




// Class ZIFieldTree 

ZIFieldTree::ZIFieldTree (ZITreeCtrl* pTreeCtrl, ZDDocument* pDoc, ZBFieldRepository* pFieldRepository)
      : m_pTreeCtrl(pTreeCtrl), 
	    m_pDoc(pDoc), 
        m_pFieldRepository(pFieldRepository),
		m_HasBeenInitialized(FALSE)
{
}


ZIFieldTree::~ZIFieldTree()
{
}



void ZIFieldTree::Empty()
{
	m_pDoc = NULL;
	if (m_pTreeCtrl)
		m_pTreeCtrl->DeleteAllItems();
}


void ZIFieldTree::Initialize (ZITreeCtrl* pTreeCtrl, ZDDocument* pDoc, ZBFieldRepository* pFieldRepository)
{
	m_pTreeCtrl = pTreeCtrl;
    m_pDoc = pDoc;
    m_pFieldRepository = pFieldRepository;
	InitializeTree();
	ZIFieldTree::Refresh();
}

void ZIFieldTree::Refresh ()
{
	if (m_pTreeCtrl)
	{
//		m_pTreeCtrl->SaveCollapsedState();

		m_pTreeCtrl->DeleteAllItems();
		ZIFieldTree::CreateTree();

//		m_pTreeCtrl->RestoreCollapsedStateToTreeCtrl();
	}
}

void ZIFieldTree::InitializeTree ()
{
	if (m_HasBeenInitialized || !m_pTreeCtrl)
		return;
	// Sets styles
	m_pTreeCtrl->HasButtons();
	m_pTreeCtrl->HasLines();
	m_pTreeCtrl->LinesAtRoot();
	// Load images
	m_pTreeCtrl->LoadImageList( IDB_FIELDDOCUMENT_TYPES, 17, 1, RGB( 255, 255, 255 ) );
	m_DocumentType.LoadString( IDS_FIELDDOCUMENTTYPE );
	m_RepositoryType.LoadString( IDS_REPOSITORYDOCUMENTTYPE );
	m_NoDocument.LoadString( IDS_NODOCUMENTSELECTED );
	m_NoRepository.LoadString( IDS_NOREPOSITORYFIELDS );
	m_HasBeenInitialized = TRUE;
}

void ZIFieldTree::CreateTree ()
{
	HTREEITEM hRootDocument = AddTypeItem (m_DocumentType, 0);

	HTREEITEM hRootRepository = AddTypeItem (m_RepositoryType, 1);

	HTREEITEM hDocument = NULL;

	if (!m_pDoc)
	{
		AddTypeItem (m_NoDocument, -1, hRootDocument);
	}
	else
	{
		// Run through document data
		for (size_t i = 0; m_pDoc && i < m_pDoc->GetDocumentDataCount(); ++i)
		{
			if (!m_pDoc->GetDocumentDataAt(i)->IsBinaryDataValid())
			{
				hDocument = AddDocumentItem( m_pDoc->GetDocumentDataAt(i), hRootDocument, 2 );

				ZDDocumentData*	pDocData = m_pDoc->GetDocumentDataAt(i);

				POSITION		Position;
				PlanFinObject  *objTemp = NULL;

				Position = pDocData->GetObjectList().GetHeadPosition();
				while (Position != NULL)
				{
					objTemp = (PlanFinObject *)pDocData->GetObjectList().GetNext( Position );
					AddDocumentFieldItem( objTemp, hDocument );

				}
			}
		}
	}
	// Run through fields
	if (m_pFieldRepository)
	{
		for (size_t Index = 0; Index < m_pFieldRepository->GetFieldCount(); ++Index)
			AddRepositoryFieldItem( m_pFieldRepository->GetFieldAt(Index), hRootRepository );
	}
	else
	{
		AddTypeItem (m_NoRepository, -1, hRootRepository);
	}

	m_pTreeCtrl->ExpandRoot(TRUE);
}


HTREEITEM ZIFieldTree::AddTypeItem (const CString FieldType, int IconIndex, HTREEITEM hParentTreeItem)
{
	TV_INSERTSTRUCT     curTreeItem;

	curTreeItem.hParent = hParentTreeItem; 
	curTreeItem.hInsertAfter = TVI_LAST ;
	curTreeItem.item.iImage = IconIndex;
	curTreeItem.item.iSelectedImage = IconIndex;
	curTreeItem.item.pszText = (char*)((const char*)FieldType);
	curTreeItem.item.lParam = (LPARAM)NULL;	// Does not represent a selectable item
	curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	return m_pTreeCtrl->InsertItem( &curTreeItem );
}

HTREEITEM ZIFieldTree::AddDocumentItem (ZDDocumentData* pData, HTREEITEM hParentTreeItem, int IconIndex)
{
	if (!pData)
		return NULL;
	TV_INSERTSTRUCT     curTreeItem;

	curTreeItem.hParent = hParentTreeItem; 
	curTreeItem.hInsertAfter = TVI_LAST ;
	curTreeItem.item.iImage = IconIndex;
	curTreeItem.item.iSelectedImage = IconIndex;
	curTreeItem.item.pszText = (char*)((const char*)pData->GetStamp().GetTitle());
	curTreeItem.item.lParam = (LPARAM)NULL;	// Does not represent a selectable item
	curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	return m_pTreeCtrl->InsertItem(&curTreeItem);
}

HTREEITEM ZIFieldTree::AddDocumentFieldItem( PlanFinObject* pObj, HTREEITEM hParentTreeItem )
{
	if (!pObj)
		return NULL;
	TV_INSERTSTRUCT     curTreeItem;

	curTreeItem.hParent = hParentTreeItem; 
	curTreeItem.hInsertAfter = TVI_LAST ;
	curTreeItem.item.iImage = GetItemIndex(pObj);
	curTreeItem.item.iSelectedImage = GetItemIndex(pObj);
	curTreeItem.item.pszText = (char*)((const char*)pObj->GetObjectName());
	curTreeItem.item.lParam = (LPARAM)pObj;	// Does not represent a selectable item
	curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	return m_pTreeCtrl->InsertItem(&curTreeItem);
}


void ZIFieldTree::AddRepositoryFieldItem (ZAObjectDefinition* pField, HTREEITEM hParentTreeItem)
{
	TV_INSERTSTRUCT     curTreeItem;

	curTreeItem.hParent = hParentTreeItem; 
	curTreeItem.hInsertAfter = TVI_LAST ;
	curTreeItem.item.iImage = GetItemIndex(pField->GetpObject());
	curTreeItem.item.iSelectedImage = GetItemIndex(pField->GetpObject());
	curTreeItem.item.pszText = (char*)((const char*)pField->GetFieldName());
	curTreeItem.item.lParam = (LPARAM)pField;	// Represent the field item
	curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	m_pTreeCtrl->InsertItem( &curTreeItem );

}


int	ZIFieldTree::GetItemIndex( PlanFinObject* pObj )
{
	switch (ZBObjectUtility::GetClassNameID(pObj))
	{
		case IDS_STATICTEXT_CLASS: 
		{
			return 6;
		}
		case IDS_DATE_CLASS: 
		{
			return 9;
		}
		case IDS_CALCULATED_CLASS: 
		{
			return 10;
		}
		case IDS_HISTOAMOUNT_CLASS: 
		{
			return 11;
		}
		case IDS_AMOUNT_CLASS: 
		{
			return 11;
		}
		case IDS_MULTITEXTSTATIC_CLASS: 
		{
			return 8;
		}
		case IDS_MULTITEXT_CLASS: 
		{
			return 8;
		}
		case IDS_HISTOTEXT_CLASS: 
		{
			return 7;
		}
		case IDS_TEXT_CLASS: 
		{
			return 7;
		}
		case IDS_SQUARETEXT_CLASS: 
		{
			return 15;
		}
		case IDS_NUMBEREDSECTION_CLASS: 
		{
			return 17;
		}
		case IDS_LINE_CLASS: 
		{
			return 3;
		}
		case IDS_RECTANGLEROUNDED_CLASS: 
		{
			return 19;
		}
		case IDS_RECTANGLE_CLASS: 
		{
			return 5;
		}
		case IDS_BITMAP_CLASS: 
		{
			return 18;
		}
		case IDS_CHECK_CLASS: 
		{
			return 14;
		}
		case IDS_RADIO_CLASS: 
		{
			return 13;
		}
		case IDS_MASKSTRING_CLASS:
		{
			return 12;
		}
		case IDS_MASKSTRINGHISTO_CLASS:
		{
			return 12;
		}
		case IDS_MULTICOLUMN_CLASS:
		{
			return 16;
		}

		default: break;
	}
	return -1;
}

PlanFinObject* ZIFieldTree::GetSelectedDocumentField ()
{
	if (m_pTreeCtrl)
	{
		HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();
		if (hSelected)
		{
			CObject*	pObj = (CObject*)m_pTreeCtrl->GetItemData( hSelected );
			if (pObj != NULL && pObj->IsKindOf(RUNTIME_CLASS(PlanFinObject)))
				return reinterpret_cast<PlanFinObject*>( pObj );
		}
	}
	return NULL;
}

ZAObjectDefinition* ZIFieldTree::GetSelectedRepositoryField ()
{
	if (m_pTreeCtrl)
	{
		HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();
		if (hSelected)
		{
			CObject*	pObj = (CObject*)m_pTreeCtrl->GetItemData( hSelected );
			if (pObj != NULL && pObj->IsKindOf(RUNTIME_CLASS(ZAObjectDefinition)))
				return reinterpret_cast<ZAObjectDefinition*>( pObj );
		}
	}
	return NULL;
}


void ZIFieldTree::OnFieldListChanged()
{
	Refresh();
}
