//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//	Source file: ZCSymbolList.cpp

#include <StdAfx.h>

#include "ZCSymbolList.h"

#include "zModelRes.h"

#include "ZBSymbol.h"
#include "ZBLinkSymbol.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(ZCSymbolList, CListCtrl)


BEGIN_MESSAGE_MAP(ZCSymbolList, ZIListCtrl)
	//{{AFX_MSG_MAP(ZCSymbolList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCSymbolList 

#include "zRes32\ZRes.h"

static int _gWkfSymbolColText[] = {	IDS_NOCOLUMNHEADER, 
									IDS_SYMBOLNAME_COLUMN,
									IDS_SYMBOLCOMMENT_COLUMN, 
									IDS_SYMBOLPATH_COLUMN, 
									IDS_SYMBOLLOCAL_COLUMN };
static int _gWkfSymbolColSize[] = {	20,
									250, 
									200, 
									200,
									60 };

ZCSymbolList::ZCSymbolList ()
 : m_pSet(NULL), m_ColumnsBuilt(FALSE)
{
}


ZCSymbolList::~ZCSymbolList()
{
	DeleteAllItems( TRUE );
}


void	ZCSymbolList::BuildColumns(UINT nIDRes)
{
	if (m_ColumnsBuilt)
		return;
	// Load images
	ZIListCtrl::LoadImageList( nIDRes, 17, 1, RGB( 255, 255, 255 ) );
//	m_pImageList = new CImageList();
//	m_pImageList->Create(nIDRes, 17, 1, RGB( 255, 255, 255 ));
	SetImageList(m_pImageList, LVSIL_SMALL);	/* set extended stlyes*/

	ZIListCtrl::BuildColumns(5, _gWkfSymbolColSize, _gWkfSymbolColText );
	ZIListCtrl::SetFullRowSelect( TRUE );
	ZIListCtrl::EnableSort( TRUE );

	m_ColumnsBuilt = TRUE;
}

int ZCSymbolList::Initialize (CODComponentSet* pSet, UINT nIDRes)
{
    m_pSet = pSet;
	ZCSymbolList::BuildColumns(nIDRes);

	return ZCSymbolList::Refresh();
}

int ZCSymbolList::Refresh ()
{
	DeleteAllItems();

	if (!m_pSet)
		return 0;
	size_t		Count = m_pSet->GetSize();
	size_t		LineCounter = 0;
	size_t		ColumnCounter;

	for (size_t Index = 0; Index < Count; ++Index)
	{
		CODComponent*	pComp = m_pSet->GetAt(Index);
		// If a symbol
		if (pComp && 
			(ISA(pComp,ZBSymbol) || ISA(pComp,ZBLinkSymbol)))
		{
			// Add the symbol type icon
			InsertItem( LVIF_IMAGE | LVIF_PARAM, LineCounter, 
						NULL,
						0, 0, 
						GetItemIndex( dynamic_cast<CODSymbolComponent*>(pComp) ), 
						(LPARAM)pComp);
			ColumnCounter = 1;
			if (ISA(pComp,ZBSymbol))
			{
				SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
						 ((ZBSymbol*)pComp)->GetSymbolName(),
						 0, 0, 0, 0 );
				SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
						 ((ZBSymbol*)pComp)->GetSymbolComment(),
						 0, 0, 0, 0 );
				SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
						 ((ZBSymbol*)pComp)->GetAbsolutePath(),
						 0, 0, 0, 0 );
				SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
						 (((ZBSymbol*)pComp)->IsLocal()) ? "1" : "0",
						 0, 0, 0, 0 );
			}
			else
			{
				SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
						 ((ZBLinkSymbol*)pComp)->GetSymbolName(),
						 0, 0, 0, 0 );
				SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
						 ((ZBLinkSymbol*)pComp)->GetSymbolComment(),
						 0, 0, 0, 0 );
				SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
						 ((ZBLinkSymbol*)pComp)->GetAbsolutePath(),
						 0, 0, 0, 0 );
				SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
						 (((ZBLinkSymbol*)pComp)->IsLocal()) ? "1" : "0",
						 0, 0, 0, 0 );
			}
			// Increment Line counter
			++LineCounter;
		}
	}

	return Count;
}


CODSymbolComponent*	ZCSymbolList::GetSelectedSymbol()
{
	int	Index;
	POSITION pos = GetFirstSelectedItemPosition();
	if (pos != NULL)     
	{
		Index = GetNextSelectedItem( pos );
		CObject* pObj = (CObject*)GetItemData( Index );
		if (pObj && ISA(pObj,CODSymbolComponent))
			return dynamic_cast<CODSymbolComponent*>(pObj);
	}
	return NULL;
}




int	ZCSymbolList::GetItemIndex( CODSymbolComponent* pSymbol )
{
	if (ISA(pSymbol, ZBSymbol))
		return dynamic_cast<ZBSymbol*>(pSymbol)->GetIconIndex();

	if (ISA(pSymbol, ZBLinkSymbol))
		return dynamic_cast<ZBLinkSymbol*>(pSymbol)->GetIconIndex();

	return -1;
}

