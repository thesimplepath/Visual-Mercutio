//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//    Source file: ZCDistributionAttributesList.cpp

//#include <StdAfx.h>
#include "StdAfx.h"

#include "ZCDistributionAttributesList.h"
#include "PSS_DistributionAttributes.h"

#include "zProperty\ZBDynamicPropertiesManager.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "PSS_ProcessGraphModelMdlBP.h"

#include "zModel\PSS_UserGroupEntity.h"
#include "zBaseLib\PSS_DocumentObserverMsg.h"
#include "zModel\PSS_SymbolObserverMsg.h"

#include "zModelBPRes.h"

#include "zModel\PSS_Symbol.h"
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

int ZCDistributionAttributesList::Initialize(PSS_DistributionAttributeManager* pDistributionManager,
                                             ZBDynamicPropertiesManager* pPropManager,
                                             PSS_UserGroupEntity* pMainUserGroup,
                                             PSS_DistributionAttribute* pDistributionAttribute /*= NULL*/,
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
        PSS_DistributionAttributeManager::IDistributionAttributeIterator it(&m_pDistributionManager->GetDistributionAttributeSet());

        for (PSS_DistributionAttribute* pAttrib = it.GetFirst(); pAttrib; pAttrib = it.GetNext())
        {
            // If we have to show this attribute
            if (m_ShowAll ||
                m_SymbolRef == -1 ||
                pAttrib->GetSymbolRef() == m_SymbolRef)
            {
                // Find the usergroup name
                PSS_UserEntity* pEntity = (m_pMainUserGroup) ? m_pMainUserGroup->FindGroupByGUID(pAttrib->GetUserGroupGUID(), true) : NULL;
                int iItem = AddItem((pEntity) ? pEntity->GetEntityName() : _T(""), 4, Level, (LPARAM)pAttrib);

                ZBProperty* pProp = (m_pPropManager) ? m_pPropManager->GetPropertyItem(pAttrib->GetCategoryID(), pAttrib->GetItemID()) : NULL;
                SetItemText(iItem, 1, (pProp) ? pProp->GetLabel() : _T(""));

                LineCounter += InsertDistributionAttribute(pAttrib, Level + 1);
            }
        }
    }
    return LineCounter;
}

int ZCDistributionAttributesList::InsertDistributionAttribute(PSS_DistributionAttribute* pDistributionAttribute, int Level)
{
    if (!pDistributionAttribute ||
        !m_pMainUserGroup)
        return 0;
    size_t        LineCounter = 0;

    PSS_DistributionAttribute::IDistributionRulesForRoleIterator itRole(&pDistributionAttribute->GetDistributionRulesForRoleSet());
    for (PSS_DistributionRulesForRole* pRole = itRole.GetFirst(); pRole; pRole = itRole.GetNext())
    {

        // First level is the role name
        PSS_UserEntity* pEntity = m_pMainUserGroup->FindRoleByGUID(pRole->GetRoleGUID(), true);
        AddItem((pEntity) ? pEntity->GetEntityName() : _T(""), 2, Level, (LPARAM)pRole);
        // Increment Line counter
        ++LineCounter;

        // Second level is all the rules
        PSS_DistributionRuleManager::IDistributionRuleIterator itRule(&pRole->GetDistributionRuleset());
        for (PSS_DistributionRule* pDistribRule = itRule.GetFirst(); pDistribRule; pDistribRule = itRule.GetNext())
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

PSS_DistributionAttribute* ZCDistributionAttributesList::GetSelectedDistributionAttribute()
{
    int    Index;
    POSITION pos = GetFirstSelectedItemPosition();
    if (pos != NULL)
    {
        Index = GetNextSelectedItem(pos);
        int nItem = (int)GetItemData(Index);
        CObject* pObj = (CObject*)GetParam(nItem);
        if (pObj && ISA(pObj, PSS_DistributionAttribute))
            return dynamic_cast<PSS_DistributionAttribute*>(pObj);
    }
    return NULL;
}

PSS_DistributionRulesForRole* ZCDistributionAttributesList::GetSelectedDistributionRuleForRole()
{
    int    Index;
    POSITION pos = GetFirstSelectedItemPosition();
    if (pos != NULL)
    {
        Index = GetNextSelectedItem(pos);
        int nItem = (int)GetItemData(Index);
        CObject* pObj = (CObject*)GetParam(nItem);
        if (pObj && ISA(pObj, PSS_DistributionRulesForRole))
            return dynamic_cast<PSS_DistributionRulesForRole*>(pObj);
    }
    return NULL;
}

PSS_DistributionRule* ZCDistributionAttributesList::GetSelectedDistributionRule()
{
    int    Index;
    POSITION pos = GetFirstSelectedItemPosition();
    if (pos != NULL)
    {
        Index = GetNextSelectedItem(pos);
        int nItem = (int)GetItemData(Index);
        CObject* pObj = (CObject*)GetParam(nItem);
        if (pObj && ISA(pObj, PSS_DistributionRule))
            return dynamic_cast<PSS_DistributionRule*>(pObj);
    }
    return NULL;
}


void ZCDistributionAttributesList::DocumentActivated(PSS_ProcessGraphModelDoc* pDoc)
{
    if (!pDoc)
        Empty();

    if (!pDoc->GetModel() || !ISA(pDoc->GetModel(), PSS_ProcessGraphModelMdlBP) ||
        !dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDoc->GetModel())->GetDistributionAttributes())
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
        ISA(pDoc->GetModel(), PSS_ProcessGraphModelMdlBP) &&
        //        dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDoc->GetModel())->GetDistributionAttributes() &&
        dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDoc->GetModel())->GetDistributionAttributes() != m_pDistributionManager)
        HasChanged = true;

    if (HasChanged)
        Initialize(dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDoc->GetModel())->GetDistributionAttributes(),
                   pDoc->GetDynamicPropertiesManager(),
                   pDoc->GetMainUserGroup(),
                   NULL,
                   m_ShowAll, m_SymbolRef);


}


void ZCDistributionAttributesList::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    if (pMsg && ISA(pMsg, PSS_SymbolObserverMsg))
    {
        if (dynamic_cast<PSS_SymbolObserverMsg*>(pMsg)->GetActionType() == PSS_SymbolObserverMsg::IE_AT_ElementSelected)
        {
            m_pComp = dynamic_cast<PSS_SymbolObserverMsg*>(pMsg)->GetElement();
            if (m_pComp &&
                (ISA(m_pComp, PSS_Symbol) || ISA(m_pComp, PSS_LinkSymbol)))
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
