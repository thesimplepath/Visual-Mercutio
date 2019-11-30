//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//    Source file: ZCDistributionAttributesList.cpp

//#include <StdAfx.h>
#include "StdAfx.h"

#include "ZCDistributionAttributesList.h"
#include "ZBDistributionAttributes.h"

#include "zProperty\ZBDynamicPropertiesManager.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "ProcGraphModelMdlBP.h"

#include "zModel\ZBUserGroupEntity.h"
#include "zBaseLib\PSS_DocumentObserverMsg.h"
#include "zModel\ZBSymbolObserverMsg.h"

#include "zModelBPRes.h"

#include "zModel\ZBSymbol.h"
#include "zModel\PSS_LinkSymbol.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(ZCDistributionAttributesList, CListCtrl)


BEGIN_MESSAGE_MAP(ZCDistributionAttributesList, PSS_TreeListCtrl)
    //{{AFX_MSG_MAP(ZCDistributionAttributesList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCDistributionAttributesList 

#include "zRes32\ZRes.h"

static int _gDistributionAttributesColText[] = {IDS_DISTRIBUTIONATTRIB_ROLENAME_COLUMN,
                                                    IDS_DISTRIBUTION_OPERATOR_COLUMN,
                                                    IDS_DISTRIBUTION_VALUE_COLUMN,
                                                    IDS_DISTRIBUTION_BOOLEANOPERATOR_COLUMN};
static int _gDistributionAttributesColSize[] = {150,
                                                    50,
                                                    100,
                                                    40};

ZCDistributionAttributesList::ZCDistributionAttributesList()
    : m_pDistributionManager(NULL),
    m_pPropManager(NULL),
    m_pMainUserGroup(NULL),
    m_pDistributionAttribute(NULL),
    m_pComp(NULL),
    m_ShowAll(false),
    m_SymbolRef(-1),
    m_ColumnsBuilt(FALSE)
{}


ZCDistributionAttributesList::~ZCDistributionAttributesList()
{
    DeleteAllItems(TRUE);
}


void    ZCDistributionAttributesList::BuildColumns()
{
    if (m_ColumnsBuilt)
        return;
    // Load images
    PSS_ListCtrl::LoadImageList(IDB_IL_DISTRIBUTIONATTRIBUTELIST, 17, 1, RGB(255, 255, 255));
    SetImageList(m_pImageList, LVSIL_SMALL);    /* set extended stlyes*/

    PSS_ListCtrl::BuildColumns(4, _gDistributionAttributesColSize, _gDistributionAttributesColText);
    PSS_ListCtrl::SetFullRowSelect(TRUE);
    PSS_ListCtrl::EnableSort(TRUE);

    m_ColumnsBuilt = TRUE;
}

int ZCDistributionAttributesList::Initialize(ZBDistributionAttributeManager* pDistributionManager,
                                             ZBDynamicPropertiesManager* pPropManager,
                                             ZBUserGroupEntity* pMainUserGroup,
                                             ZBDistributionAttribute* pDistributionAttribute /*= NULL*/,
                                             bool ShowAll /*= false*/, int SymbolRef /*= -1*/)
{
    m_pDistributionManager = pDistributionManager;
    m_pPropManager = pPropManager;
    m_pMainUserGroup = pMainUserGroup;
    m_pDistributionAttribute = pDistributionAttribute;
    m_ShowAll = ShowAll;
    m_SymbolRef = SymbolRef;
    ZCDistributionAttributesList::BuildColumns();

    return ZCDistributionAttributesList::Refresh();
}

int ZCDistributionAttributesList::Refresh()
{
    DeleteAllItems();

    if (!m_pDistributionManager)
        return 0;
    size_t        LineCounter = 0;
    size_t        Level = 0;

    // If only one distribution attribute to show
    if (m_pDistributionAttribute)
    {
        LineCounter = InsertDistributionAttribute(m_pDistributionAttribute, Level);
    }
    else
    {
        ZBDistributionAttributeIterator i(&m_pDistributionManager->GetDistributionAttributeSet());
        for (ZBDistributionAttribute* pAttrib = i.GetFirst(); pAttrib; pAttrib = i.GetNext())
        {
            // If we have to show this attribute
            if (m_ShowAll ||
                m_SymbolRef == -1 ||
                pAttrib->GetSymbolRef() == m_SymbolRef)
            {
                // Find the usergroup name
                ZBUserEntity* pEntity = (m_pMainUserGroup) ? m_pMainUserGroup->FindGroupByGUID(pAttrib->GetUserGroupGUID(), true) : NULL;
                int iItem = AddItem((pEntity) ? pEntity->GetEntityName() : _T(""), 4, Level, (LPARAM)pAttrib);

                ZBProperty* pProp = (m_pPropManager) ? m_pPropManager->GetPropertyItem(pAttrib->GetCategoryID(), pAttrib->GetItemID()) : NULL;
                SetItemText(iItem, 1, (pProp) ? pProp->GetLabel() : _T(""));

                LineCounter += InsertDistributionAttribute(pAttrib, Level + 1);
            }
        }
    }
    return LineCounter;
}

int ZCDistributionAttributesList::InsertDistributionAttribute(ZBDistributionAttribute* pDistributionAttribute, int Level)
{
    if (!pDistributionAttribute ||
        !m_pMainUserGroup)
        return 0;
    size_t        LineCounter = 0;

    ZBDistributionRulesForRoleIterator i(&pDistributionAttribute->GetDistributionRulesForRoleSet());
    for (ZBDistributionRulesForRole* pRole = i.GetFirst(); pRole; pRole = i.GetNext())
    {

        // First level is the role name
        ZBUserEntity* pEntity = m_pMainUserGroup->FindRoleByGUID(pRole->GetRoleGUID(), true);
        AddItem((pEntity) ? pEntity->GetEntityName() : _T(""), 2, Level, (LPARAM)pRole);
        // Increment Line counter
        ++LineCounter;

        // Second level is all the rules
        ZBDistributionRuleIterator j(&pRole->GetDistributionRuleSet());
        for (ZBDistributionRule* pDistribRule = j.GetFirst(); pDistribRule; pDistribRule = j.GetNext())
        {
            int iItem = AddItem(_T(""), 3, Level + 1, (LPARAM)pDistribRule);
            SetItemText(iItem, 1, pDistribRule->GetOperatorString());
            SetItemText(iItem, 2, pDistribRule->GetValue());
            SetItemText(iItem, 3, pDistribRule->GetLogicalOperatorString());

            // Increment Line counter
            ++LineCounter;
        }
    }

    return LineCounter;
}

void ZCDistributionAttributesList::Empty()
{
    if (::IsWindow(GetSafeHwnd()))
        DeleteAllItems();
}

ZBDistributionAttribute*    ZCDistributionAttributesList::GetSelectedDistributionAttribute()
{
    int    Index;
    POSITION pos = GetFirstSelectedItemPosition();
    if (pos != NULL)
    {
        Index = GetNextSelectedItem(pos);
        int nItem = (int)GetItemData(Index);
        CObject* pObj = (CObject*)GetParam(nItem);
        if (pObj && ISA(pObj, ZBDistributionAttribute))
            return dynamic_cast<ZBDistributionAttribute*>(pObj);
    }
    return NULL;
}

ZBDistributionRulesForRole*    ZCDistributionAttributesList::GetSelectedDistributionRuleForRole()
{
    int    Index;
    POSITION pos = GetFirstSelectedItemPosition();
    if (pos != NULL)
    {
        Index = GetNextSelectedItem(pos);
        int nItem = (int)GetItemData(Index);
        CObject* pObj = (CObject*)GetParam(nItem);
        if (pObj && ISA(pObj, ZBDistributionRulesForRole))
            return dynamic_cast<ZBDistributionRulesForRole*>(pObj);
    }
    return NULL;
}

ZBDistributionRule*    ZCDistributionAttributesList::GetSelectedDistributionRule()
{
    int    Index;
    POSITION pos = GetFirstSelectedItemPosition();
    if (pos != NULL)
    {
        Index = GetNextSelectedItem(pos);
        int nItem = (int)GetItemData(Index);
        CObject* pObj = (CObject*)GetParam(nItem);
        if (pObj && ISA(pObj, ZBDistributionRule))
            return dynamic_cast<ZBDistributionRule*>(pObj);
    }
    return NULL;
}


void ZCDistributionAttributesList::DocumentActivated(PSS_ProcessGraphModelDoc* pDoc)
{
    if (!pDoc)
        Empty();

    if (!pDoc->GetModel() || !ISA(pDoc->GetModel(), ZDProcessGraphModelMdlBP) ||
        !dynamic_cast<ZDProcessGraphModelMdlBP*>(pDoc->GetModel())->GetDistributionAttributes())
    {
        Initialize(NULL,
                   NULL,
                   NULL,
                   NULL);
        return;
    }

    bool HasChanged = false;
    if (//pDoc->GetDynamicPropertiesManager() &&
        pDoc->GetDynamicPropertiesManager() != m_pPropManager)
        HasChanged = true;

    if (//pDoc->GetMainUserGroup() &&
        pDoc->GetMainUserGroup() != m_pMainUserGroup)
        HasChanged = true;

    if (pDoc->GetModel() &&
        ISA(pDoc->GetModel(), ZDProcessGraphModelMdlBP) &&
        //        dynamic_cast<ZDProcessGraphModelMdlBP*>(pDoc->GetModel())->GetDistributionAttributes() &&
        dynamic_cast<ZDProcessGraphModelMdlBP*>(pDoc->GetModel())->GetDistributionAttributes() != m_pDistributionManager)
        HasChanged = true;

    if (HasChanged)
        Initialize(dynamic_cast<ZDProcessGraphModelMdlBP*>(pDoc->GetModel())->GetDistributionAttributes(),
                   pDoc->GetDynamicPropertiesManager(),
                   pDoc->GetMainUserGroup(),
                   NULL,
                   m_ShowAll, m_SymbolRef);


}


void ZCDistributionAttributesList::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    if (pMsg && ISA(pMsg, ZBSymbolObserverMsg))
    {
        if (dynamic_cast<ZBSymbolObserverMsg*>(pMsg)->GetActionType() == ZBSymbolObserverMsg::ElementSelected)
        {
            m_pComp = dynamic_cast<ZBSymbolObserverMsg*>(pMsg)->GetElement();
            if (m_pComp &&
                (ISA(m_pComp, ZBSymbol) || ISA(m_pComp, PSS_LinkSymbol)))
                SetSymbolRef(dynamic_cast<PSS_BasicSymbol*>(m_pComp)->GetSymbolReferenceNumber());
            else
                SetSymbolRef(-1);
        }
    }
    else
        // Check about document close
        if (pMsg && ISA(pMsg, PSS_DocumentObserverMsg) &&
            ISA(dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetDocument(), PSS_ProcessGraphModelDoc))
        {
            switch (dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetMessageID())
            {
                case UM_REFRESHDOCUMENT:
                case UM_OPENDOCUMENT: break;

                case UM_CLOSEDOCUMENT:
                {
                    Empty();
                    break;
                }
                case UM_FRAMEHASBEENACTIVATED:
                {
                    DocumentActivated(dynamic_cast<PSS_ProcessGraphModelDoc*>(dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetDocument()));
                }

            }
        }


}
