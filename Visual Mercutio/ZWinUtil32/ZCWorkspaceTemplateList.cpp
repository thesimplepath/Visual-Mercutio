// Source file: ZCWorkspaceTemplateList.cpp

#include <StdAfx.h>

#include "ZCWorkspaceTemplateList.h"
#include "zBaseLib\ZBWorkspaceWizardTemplateMg.h"
#include "ZWinUtil32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int _gWorkspaceTemplateListColText[] = { IDS_NOCOLUMNHEADER,
												IDS_COLUMN1_WKSTEMPLATE };
static int _gWorkspaceTemplateListColSize[] = { 20,		// Icon
												200 }; 	// Project name


BEGIN_MESSAGE_MAP(ZCWorkspaceTemplateList, ZIListCtrl)
	//{{AFX_MSG_MAP(ZCWorkspaceTemplateList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCWorkspaceTemplateList 


ZCWorkspaceTemplateList::ZCWorkspaceTemplateList (ZBWorkspaceWizardTemplateMg* pWorkspaceTemplateManager)
      : m_pWorkspaceTemplateManager(pWorkspaceTemplateManager), m_ColumnsHasBeenBuilt(FALSE)
{
}


ZCWorkspaceTemplateList::~ZCWorkspaceTemplateList()
{
}



void ZCWorkspaceTemplateList::Initialize (ZBWorkspaceWizardTemplateMg* pWorkspaceTemplateManager)
{
    m_pWorkspaceTemplateManager = pWorkspaceTemplateManager;
	ZCWorkspaceTemplateList::Refresh();
}

void ZCWorkspaceTemplateList::Refresh ()
{
	DeleteAllItems();
	// If the columns were never built
	if (!ColumnsHasBeenBuilt())
		BuildColumns();
	// If no manager defined, return
	if (!m_pWorkspaceTemplateManager)
		return;
	// Run through the list of template items
	ZBWorkspaceWizardTemplateItemIterator i(m_pWorkspaceTemplateManager->GetTemplateItemSet());
	for (ZBWorkspaceWizardTemplateItem* pItem = i.GetFirst(); pItem != NULL; pItem = i.GetNext())
	{
		*pItem >> *this;
	}
}

ZBWorkspaceWizardTemplateItem*	ZCWorkspaceTemplateList::GetSelectedItem() const
{
	int	Index;
	POSITION pos = GetFirstSelectedItemPosition();
	if (pos != NULL)     
	{
		Index = GetNextSelectedItem( pos );
		return (ZBWorkspaceWizardTemplateItem*)GetItemData( Index );
	}
	return NULL;
}

BOOL	ZCWorkspaceTemplateList::BuildColumns()
{
	// Load images
	LoadImageList( IDB_WORKSPACE_TMPL_DEF, 17, 1, RGB( 255, 255, 255 ) );
//	ZIListCtrl::SetEnableOver( TRUE );
	ZIListCtrl::SetFullRowSelect( TRUE );
	ZIListCtrl::EnableSort( TRUE );


	ZIListCtrl::BuildColumns(2, _gWorkspaceTemplateListColSize, _gWorkspaceTemplateListColText);
	m_ColumnsHasBeenBuilt = TRUE;
	return TRUE;
}

ZBWorkspaceWizardTemplateItem&	operator>>( ZBWorkspaceWizardTemplateItem& left, ZCWorkspaceTemplateList& listCtrl )
{
	int	Index = listCtrl.GetItemCount();
	int	ImageIndex = 1;
	// Add the template icon
	listCtrl.InsertItem( LVIF_IMAGE | LVIF_PARAM, Index, 
						 NULL,
						 0, 0, ImageIndex, (LPARAM)&left);
	// Add the template name
	listCtrl.SetItem( Index, 1, LVIF_TEXT,
					  left.GetTemplateName(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	return left;
}

