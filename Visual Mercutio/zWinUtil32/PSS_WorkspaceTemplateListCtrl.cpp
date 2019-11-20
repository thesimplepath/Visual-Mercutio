/****************************************************************************
 * ==> PSS_WorkspaceTemplateListCtrl ---------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace template list control                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_WorkspaceTemplateListCtrl.h"

// processsoft
#include "zBaseLib\PSS_WorkspaceWizardTemplateManager.h"

// resources
#include "zWinUtil32Res.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static int g_WorkspaceTemplateListColText[] =
{
    IDS_NOCOLUMNHEADER,
    IDS_COLUMN1_WKSTEMPLATE
};

static int g_WorkspaceTemplateListColSize[] =
{
    20,
    200
};
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_WorkspaceTemplateListCtrl, PSS_ListCtrl)
    //{{AFX_MSG_MAP(PSS_WorkspaceTemplateListCtrl)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_WorkspaceTemplateListCtrl
//---------------------------------------------------------------------------
PSS_WorkspaceTemplateListCtrl::PSS_WorkspaceTemplateListCtrl(PSS_WorkspaceWizardTemplateManager* pWorkspaceTemplateManager) :
    PSS_ListCtrl(),
    m_pWorkspaceTemplateManager(pWorkspaceTemplateManager),
    m_ColumnsHasBeenBuilt(FALSE)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceTemplateListCtrl::PSS_WorkspaceTemplateListCtrl(const PSS_WorkspaceTemplateListCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_WorkspaceTemplateListCtrl::~PSS_WorkspaceTemplateListCtrl()
{}
//---------------------------------------------------------------------------
const PSS_WorkspaceTemplateListCtrl& PSS_WorkspaceTemplateListCtrl::operator = (const PSS_WorkspaceTemplateListCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_WorkspaceWizardTemplateItem& operator >> (PSS_WorkspaceWizardTemplateItem& templateItem, PSS_WorkspaceTemplateListCtrl& listCtrl)
{
    const int index      = listCtrl.GetItemCount();
    const int imageIndex = 1;

    // add the template icon
    listCtrl.InsertItem(LVIF_IMAGE | LVIF_PARAM, index, NULL, 0, 0, imageIndex, LPARAM(&templateItem));

    // add the template name
    listCtrl.SetItem(index, 1, LVIF_TEXT, templateItem.GetTemplateName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

    return templateItem;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTemplateListCtrl::Initialize(PSS_WorkspaceWizardTemplateManager* pWorkspaceTemplateManager)
{
    m_pWorkspaceTemplateManager = pWorkspaceTemplateManager;
    Refresh();
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTemplateListCtrl::Refresh()
{
    DeleteAllItems();

    // columns were built?
    if (!ColumnsHasBeenBuilt())
        BuildColumns();

    // if no manager defined, return
    if (!m_pWorkspaceTemplateManager)
        return;

    PSS_WorkspaceWizardTemplateItemIterator it(m_pWorkspaceTemplateManager->GetTemplateItemSet());

    // iterate through the template item list
    for (PSS_WorkspaceWizardTemplateItem* pItem = it.GetFirst(); pItem; pItem = it.GetNext())
        *pItem >> *this;
}
//---------------------------------------------------------------------------
PSS_WorkspaceWizardTemplateItem* PSS_WorkspaceTemplateListCtrl::GetSelectedItem() const
{
    POSITION pPos = GetFirstSelectedItemPosition();

    if (pPos)
        return (PSS_WorkspaceWizardTemplateItem*)GetItemData(GetNextSelectedItem(pPos));

    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_WorkspaceTemplateListCtrl::BuildColumns()
{
    // load images
    LoadImageList(IDB_WORKSPACE_TMPL_DEF, 17, 1, RGB(255, 255, 255));

    SetFullRowSelect(TRUE);
    EnableSort(TRUE);

    PSS_ListCtrl::BuildColumns(2, g_WorkspaceTemplateListColSize, g_WorkspaceTemplateListColText);

    m_ColumnsHasBeenBuilt = TRUE;

    return TRUE;
}
//---------------------------------------------------------------------------
