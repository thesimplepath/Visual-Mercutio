/****************************************************************************
 * ==> PSS_WorkspaceTemplateListCtrl ---------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace template list control                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_WorkspaceTemplateListCtrl.h"

// processsoft
#include "zBaseLib\ZBWorkspaceWizardTemplateMg.h"

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
BEGIN_MESSAGE_MAP(PSS_WorkspaceTemplateListCtrl, ZIListCtrl)
    //{{AFX_MSG_MAP(PSS_WorkspaceTemplateListCtrl)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_WorkspaceTemplateListCtrl
//---------------------------------------------------------------------------
PSS_WorkspaceTemplateListCtrl::PSS_WorkspaceTemplateListCtrl(ZBWorkspaceWizardTemplateMg* pWorkspaceTemplateManager) :
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
ZBWorkspaceWizardTemplateItem& operator >> (ZBWorkspaceWizardTemplateItem& left, PSS_WorkspaceTemplateListCtrl& listCtrl)
{
    int    Index = listCtrl.GetItemCount();
    int    ImageIndex = 1;
    // Add the template icon
    listCtrl.InsertItem(LVIF_IMAGE | LVIF_PARAM, Index,
                        NULL,
                        0, 0, ImageIndex, (LPARAM)&left);
    // Add the template name
    listCtrl.SetItem(Index, 1, LVIF_TEXT,
                     left.GetTemplateName(),
                     0, LVIF_TEXT, LVIF_TEXT, 0);
    return left;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTemplateListCtrl::Initialize(ZBWorkspaceWizardTemplateMg* pWorkspaceTemplateManager)
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

    ZBWorkspaceWizardTemplateItemIterator it(m_pWorkspaceTemplateManager->GetTemplateItemSet());

    // iterate through the template item list
    for (ZBWorkspaceWizardTemplateItem* pItem = it.GetFirst(); pItem; pItem = it.GetNext())
        *pItem >> *this;
}
//---------------------------------------------------------------------------
ZBWorkspaceWizardTemplateItem* PSS_WorkspaceTemplateListCtrl::GetSelectedItem() const
{
    POSITION pPos = GetFirstSelectedItemPosition();

    if (pPos)
        return (ZBWorkspaceWizardTemplateItem*)GetItemData(GetNextSelectedItem(pPos));

    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_WorkspaceTemplateListCtrl::BuildColumns()
{
    // load images
    LoadImageList(IDB_WORKSPACE_TMPL_DEF, 17, 1, RGB(255, 255, 255));

    SetFullRowSelect(TRUE);
    EnableSort(TRUE);

    ZIListCtrl::BuildColumns(2, g_WorkspaceTemplateListColSize, g_WorkspaceTemplateListColText);

    m_ColumnsHasBeenBuilt = TRUE;

    return TRUE;
}
//---------------------------------------------------------------------------
