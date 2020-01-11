/****************************************************************************
 * ==> PSS_SymbolListCtrl --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol list controller                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_SymbolListCtrl.h"

// processsoft
#include "zModelRes.h"
#include "PSS_Symbol.h"
#include "PSS_LinkSymbol.h"

// resources
#include "zRes32\ZRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
static int g_WkfSymbolColText[] = {IDS_NOCOLUMNHEADER,
                                   IDS_SYMBOLNAME_COLUMN,
                                   IDS_SYMBOLCOMMENT_COLUMN,
                                   IDS_SYMBOLPATH_COLUMN,
                                   IDS_SYMBOLLOCAL_COLUMN};
static int g_WkfSymbolColSize[] = {20, 250, 200, 200, 60};
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_SymbolListCtrl, CListCtrl)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SymbolListCtrl, PSS_ListCtrl)
    //{{AFX_MSG_MAP(PSS_SymbolListCtrl)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SymbolListCtrl
//---------------------------------------------------------------------------
PSS_SymbolListCtrl::PSS_SymbolListCtrl() :
    m_pSet(NULL),
    m_ColumnsBuilt(FALSE)
{}
//---------------------------------------------------------------------------
PSS_SymbolListCtrl::PSS_SymbolListCtrl(const PSS_SymbolListCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_SymbolListCtrl::~PSS_SymbolListCtrl()
{
    // NOTE use fully qualified name here to avoid to call a pure virtual function during the destruction
    PSS_ListCtrl::DeleteAllItems(TRUE);
}
//---------------------------------------------------------------------------
const PSS_SymbolListCtrl& PSS_SymbolListCtrl::operator = (const PSS_SymbolListCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
int PSS_SymbolListCtrl::Initialize(CODComponentSet* pSet, UINT resID)
{
    m_pSet = pSet;
    BuildColumns(resID);

    return Refresh();
}
//---------------------------------------------------------------------------
int PSS_SymbolListCtrl::Refresh()
{
    DeleteAllItems();

    if (!m_pSet)
        return 0;

    const std::size_t count       = m_pSet->GetSize();
          std::size_t lineCounter = 0;
          std::size_t columnCounter;

    for (std::size_t index = 0; index < count; ++index)
    {
        CODComponent*   pComp       = m_pSet->GetAt(index);
        PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pComp);
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

        // if a kind of symbol
        if (pSymbol || pLinkSymbol)
        {
            // add the symbol type icon
            InsertItem(LVIF_IMAGE | LVIF_PARAM,
                       lineCounter,
                       NULL,
                       0,
                       0,
                       GetItemIndex(dynamic_cast<CODSymbolComponent*>(pComp)),
                       LPARAM(pComp));

            columnCounter = 1;

            if (pSymbol)
            {
                SetItem(lineCounter, columnCounter, LVIF_TEXT, pSymbol->GetSymbolName(),       0, 0, 0, 0); ++columnCounter;
                SetItem(lineCounter, columnCounter, LVIF_TEXT, pSymbol->GetSymbolComment(),    0, 0, 0, 0); ++columnCounter;
                SetItem(lineCounter, columnCounter, LVIF_TEXT, pSymbol->GetAbsolutePath(),     0, 0, 0, 0); ++columnCounter;
                SetItem(lineCounter, columnCounter, LVIF_TEXT, pSymbol->IsLocal() ? "1" : "0", 0, 0, 0, 0); ++columnCounter;
            }
            else
            {
                SetItem(lineCounter, columnCounter, LVIF_TEXT, pLinkSymbol->GetSymbolName(),       0, 0, 0, 0); ++columnCounter;
                SetItem(lineCounter, columnCounter, LVIF_TEXT, pLinkSymbol->GetSymbolComment(),    0, 0, 0, 0); ++columnCounter;
                SetItem(lineCounter, columnCounter, LVIF_TEXT, pLinkSymbol->GetAbsolutePath(),     0, 0, 0, 0); ++columnCounter;
                SetItem(lineCounter, columnCounter, LVIF_TEXT, pLinkSymbol->IsLocal() ? "1" : "0", 0, 0, 0, 0); ++columnCounter;
            }

            // increment line counter
            ++lineCounter;
        }
    }

    return count;
}
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_SymbolListCtrl::GetSelectedSymbol()
{
    POSITION pPos = GetFirstSelectedItemPosition();

    if (pPos)
        return dynamic_cast<CODSymbolComponent*>(reinterpret_cast<CObject*>(GetItemData(GetNextSelectedItem(pPos))));

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_SymbolListCtrl::BuildColumns(UINT nIDRes)
{
    if (m_ColumnsBuilt)
        return;

    // load images
    PSS_ListCtrl::LoadImageList(nIDRes, 17, 1, RGB(255, 255, 255));
    SetImageList(m_pImageList, LVSIL_SMALL);

    PSS_ListCtrl::BuildColumns(5, g_WkfSymbolColSize, g_WkfSymbolColText);
    PSS_ListCtrl::SetFullRowSelect(TRUE);
    PSS_ListCtrl::EnableSort(TRUE);

    m_ColumnsBuilt = TRUE;
}
//---------------------------------------------------------------------------
int PSS_SymbolListCtrl::GetItemIndex(CODSymbolComponent* pComponent)
{
    PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pComponent);

    if (pSymbol)
        return pSymbol->GetIconIndex();

    PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pComponent);

    if (pLinkSymbol)
        return pLinkSymbol->GetIconIndex();

    return -1;
}
//---------------------------------------------------------------------------
