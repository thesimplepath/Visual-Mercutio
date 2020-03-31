/****************************************************************************
 * ==> PSS_DistributionAttributesList --------------------------------------*
 ****************************************************************************
 * Description : Provides a distribution attributes list                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_DistributionAttributesList.h"

// processsoft
#include "zBaseLib\PSS_DocumentObserverMsg.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_UserGroupEntity.h"
#include "zModel\PSS_SymbolObserverMsg.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zProperty\PSS_DynamicPropertiesManager.h"
#include "PSS_DistributionAttributes.h"
#include "PSS_ProcessGraphModelMdlBP.h"

// resources
#include "zModelBPRes.h"
#include "zRes32\ZRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static int g_DistributionAttributesColText[] =
{
    IDS_DISTRIBUTIONATTRIB_ROLENAME_COLUMN,
    IDS_DISTRIBUTION_OPERATOR_COLUMN,
    IDS_DISTRIBUTION_VALUE_COLUMN,
    IDS_DISTRIBUTION_BOOLEANOPERATOR_COLUMN
};

static int g_DistributionAttributesColSize[] = {150, 50, 100, 40};
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_DistributionAttributesList, CListCtrl)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DistributionAttributesList, PSS_TreeListCtrl)
    //{{AFX_MSG_MAP(PSS_DistributionAttributesList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DistributionAttributesList
//---------------------------------------------------------------------------
PSS_DistributionAttributesList::PSS_DistributionAttributesList() :
    PSS_TreeListCtrl(),
    m_pDistributionAttribute(NULL),
    m_pDistributionManager(NULL),
    m_pPropManager(NULL),
    m_pMainUserGroup(NULL),
    m_pComp(NULL),
    m_SymbolRef(-1),
    m_ColumnsBuilt(FALSE),
    m_ShowAll(false)
{}
//---------------------------------------------------------------------------
PSS_DistributionAttributesList::PSS_DistributionAttributesList(const PSS_DistributionAttributesList& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_DistributionAttributesList::~PSS_DistributionAttributesList()
{
    // NOTE use the fully qualified name here to avoid to call a pure virtual function on destruction
    PSS_TreeListCtrl::DeleteAllItems(TRUE);
}
//---------------------------------------------------------------------------
const PSS_DistributionAttributesList& PSS_DistributionAttributesList::operator = (const PSS_DistributionAttributesList& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
int PSS_DistributionAttributesList::Initialize(PSS_DistributionAttributeManager* pDistributionManager,
                                               PSS_DynamicPropertiesManager*     pPropManager,
                                               PSS_UserGroupEntity*              pMainUserGroup,
                                               PSS_DistributionAttribute*        pDistributionAttribute,
                                               bool                              showAll,
                                               int                               symbolRef)
{
    m_pDistributionAttribute = pDistributionAttribute;
    m_pDistributionManager   = pDistributionManager;
    m_pPropManager           = pPropManager;
    m_pMainUserGroup         = pMainUserGroup;
    m_SymbolRef              = symbolRef;
    m_ShowAll                = showAll;

    BuildColumns();

    return Refresh();
}
//---------------------------------------------------------------------------
PSS_DistributionAttribute* PSS_DistributionAttributesList::GetSelectedDistributionAttribute()
{
    POSITION pPos = GetFirstSelectedItemPosition();

    if (pPos)
    {
        const int                  index      = GetNextSelectedItem(pPos);
        const int                  item       = int(GetItemData(index));
        PSS_DistributionAttribute* pAttribute = dynamic_cast<PSS_DistributionAttribute*>(reinterpret_cast<CObject*>(GetParam(item)));

        if (pAttribute)
            return pAttribute;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_DistributionRulesForRole* PSS_DistributionAttributesList::GetSelectedDistributionRuleForRole()
{
    POSITION pPos = GetFirstSelectedItemPosition();

    if (pPos)
    {
        const int                     index  = GetNextSelectedItem(pPos);
        const int                     item   = int(GetItemData(index));
        PSS_DistributionRulesForRole* pRules = dynamic_cast<PSS_DistributionRulesForRole*>(reinterpret_cast<CObject*>(GetParam(item)));

        if (pRules)
            return pRules;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_DistributionRule* PSS_DistributionAttributesList::GetSelectedDistributionRule()
{
    POSITION pPos = GetFirstSelectedItemPosition();

    if (pPos)
    {
        const int             index = GetNextSelectedItem(pPos);
        const int             item  = int(GetItemData(index));
        PSS_DistributionRule* pRule = dynamic_cast<PSS_DistributionRule*>(reinterpret_cast<CObject*>(GetParam(item)));

        if (pRule)
            return pRule;
    }

    return NULL;
}
//---------------------------------------------------------------------------
int PSS_DistributionAttributesList::Refresh()
{
    DeleteAllItems();

    if (!m_pDistributionManager)
        return 0;

    std::size_t lineCounter = 0;
    std::size_t level       = 0;

    // if only one distribution attribute to show
    if (m_pDistributionAttribute)
        lineCounter = InsertDistributionAttribute(m_pDistributionAttribute, level);
    else
    {
        PSS_DistributionAttributeManager::IDistributionAttributeIterator it(&m_pDistributionManager->GetDistributionAttributeSet());

        // iterate through attributes
        for (PSS_DistributionAttribute* pAttrib = it.GetFirst(); pAttrib; pAttrib = it.GetNext())
            // if this attribute should be shown
            if (m_ShowAll || m_SymbolRef == -1 || pAttrib->GetSymbolRef() == m_SymbolRef)
            {
                // find the user group name
                PSS_UserEntity* pEntity =
                        (m_pMainUserGroup ? m_pMainUserGroup->FindGroupByGUID(pAttrib->GetUserGroupGUID(), true) : NULL);
                const int       item    = AddItem(pEntity ? pEntity->GetEntityName() : _T(""), 4, level, LPARAM(pAttrib));
                PSS_Property*   pProp   =
                        (m_pPropManager ? m_pPropManager->GetPropertyItem(pAttrib->GetCategoryID(), pAttrib->GetItemID()) : NULL);
                SetItemText(item, 1, pProp ? pProp->GetLabel() : _T(""));

                lineCounter += InsertDistributionAttribute(pAttrib, level + 1);
            }
    }

    return lineCounter;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesList::Empty()
{
    if (::IsWindow(GetSafeHwnd()))
        DeleteAllItems();
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesList::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    if (!pMsg)
        return;

    PSS_SymbolObserverMsg* pObserverMsg = dynamic_cast<PSS_SymbolObserverMsg*>(pMsg);

    if (pObserverMsg)
    {
        if (pObserverMsg->GetActionType() == PSS_SymbolObserverMsg::IE_AT_ElementSelected)
        {
            m_pComp = pObserverMsg->GetElement();

            if (m_pComp && (ISA(m_pComp, PSS_Symbol) || ISA(m_pComp, PSS_LinkSymbol)))
            {
                PSS_BasicSymbol* pSymbol = dynamic_cast<PSS_BasicSymbol*>(m_pComp);

                if (pSymbol)
                    SetSymbolRef(pSymbol->GetSymbolReferenceNumber());
            }
            else
                SetSymbolRef(-1);
        }
    }
    else
    {
        PSS_DocumentObserverMsg* pDocObserverMsg = dynamic_cast<PSS_DocumentObserverMsg*>(pMsg);

        // check for document status
        if (pDocObserverMsg)
        {
            PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDocObserverMsg->GetDocument());

            if (pDoc)
                switch (pDocObserverMsg->GetMessageID())
                {
                    case UM_REFRESHDOCUMENT:
                    case UM_OPENDOCUMENT:                                   break;
                    case UM_CLOSEDOCUMENT:         Empty();                 break;
                    case UM_FRAMEHASBEENACTIVATED: DocumentActivated(pDoc); break;
                }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesList::BuildColumns()
{
    if (m_ColumnsBuilt)
        return;

    // load images
    PSS_ListCtrl::LoadImageList(IDB_IL_DISTRIBUTIONATTRIBUTELIST, 17, 1, RGB(255, 255, 255));
    SetImageList(m_pImageList, LVSIL_SMALL);

    PSS_ListCtrl::BuildColumns(4, g_DistributionAttributesColSize, g_DistributionAttributesColText);
    PSS_ListCtrl::SetFullRowSelect(TRUE);
    PSS_ListCtrl::EnableSort(TRUE);

    m_ColumnsBuilt = TRUE;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesList::DocumentActivated(PSS_ProcessGraphModelDoc* pDoc)
{
    if (!pDoc)
        Empty();

    PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDoc->GetModel());

    if (!pModel || !pModel->GetDistributionAttributes())
    {
        Initialize(NULL, NULL, NULL, NULL);
        return;
    }

    bool hasChanged = false;

    if (pDoc->GetDynamicPropertiesManager() != m_pPropManager)
        hasChanged = true;

    if (pDoc->GetMainUserGroup() != m_pMainUserGroup)
        hasChanged = true;

    if (pModel && pModel->GetDistributionAttributes() != m_pDistributionManager)
        hasChanged = true;

    if (hasChanged)
        Initialize(pModel->GetDistributionAttributes(),
                   pDoc->GetDynamicPropertiesManager(),
                   pDoc->GetMainUserGroup(),
                   NULL,
                   m_ShowAll, m_SymbolRef);
}
//---------------------------------------------------------------------------
int PSS_DistributionAttributesList::InsertDistributionAttribute(PSS_DistributionAttribute* pDistributionAttribute, int Level)
{
    if (!pDistributionAttribute || !m_pMainUserGroup)
        return 0;

    PSS_DistributionAttribute::IDistributionRulesForRoleIterator itRole(&pDistributionAttribute->GetDistributionRulesForRoleSet());
    std::size_t                                                  lineCounter = 0;

    for (PSS_DistributionRulesForRole* pRole = itRole.GetFirst(); pRole; pRole = itRole.GetNext())
    {
        // first level is the role name
        PSS_UserEntity* pEntity = m_pMainUserGroup->FindRoleByGUID(pRole->GetRoleGUID(), true);
        AddItem(pEntity ? pEntity->GetEntityName() : _T(""), 2, Level, LPARAM(pRole));

        // increment line counter
        ++lineCounter;

        PSS_DistributionRuleManager::IDistributionRuleIterator itRule(&pRole->GetDistributionRuleset());

        // second level is all the rules
        for (PSS_DistributionRule* pDistribRule = itRule.GetFirst(); pDistribRule; pDistribRule = itRule.GetNext())
        {
            const int item = AddItem(_T(""), 3, Level + 1, LPARAM(pDistribRule));
            SetItemText(item, 1, pDistribRule->GetOperatorString());
            SetItemText(item, 2, pDistribRule->GetValue());
            SetItemText(item, 3, pDistribRule->GetLogicalOperatorString());

            // increment line counter
            ++lineCounter;
        }
    }

    return lineCounter;
}
//---------------------------------------------------------------------------
