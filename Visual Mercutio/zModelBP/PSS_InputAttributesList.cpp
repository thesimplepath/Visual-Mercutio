/****************************************************************************
 * ==> PSS_InputAttributesList ---------------------------------------------*
 ****************************************************************************
 * Description : Provides an input attributes list                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_InputAttributesList.h"

// processsoft
#include "zBaseLib\PSS_DocumentObserverMsg.h"
#include "zBaseLib\PSS_Tokenizer.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_SymbolObserverMsg.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zProperty\PSS_DynamicPropertiesManager.h"
#include "PSS_InputAttributes.h"
#include "PSS_ProcessGraphModelMdlBP.h"

// resources
#include "zModelBPRes.h"
#include "zModel\zModelRes.h"
#include "zRes32\ZRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static int g_InputAttributesColText[] =
{
    IDS_NOCOLUMNHEADER,
    IDS_INPUTATTRIB_NAME_COLUMN,
    IDS_INPUTATTRIB_FLAG_COLUMN,
    IDS_INPUTATTRIB_DEFVALUE_COLUMN,
    IDS_INPUTATTRIB_ATTACHEDSYMBOL_COLUMN
};

static int g_InputAttributesColSize[] = {60, 120, 100, 100, 60};
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_InputAttributesList, CListCtrl)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InputAttributesList, PSS_ListCtrl)
    //{{AFX_MSG_MAP(PSS_InputAttributesList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InputAttributesList
//---------------------------------------------------------------------------
PSS_InputAttributesList::PSS_InputAttributesList() :
    PSS_ListCtrl(),
    m_pInputManager(NULL),
    m_pPropManager(NULL),
    m_pDoc(NULL),
    m_pComp(NULL),
    m_SymbolRef(-1),
    m_ColumnsBuilt(FALSE),
    m_ShowAll(false)
{}
//---------------------------------------------------------------------------
PSS_InputAttributesList::PSS_InputAttributesList(const PSS_InputAttributesList& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_InputAttributesList::~PSS_InputAttributesList()
{
    // NOTE use the fully qualified name here to avoid to call a pure virtual function on destruction
    PSS_ListCtrl::DeleteAllItems(TRUE);
}
//---------------------------------------------------------------------------
const PSS_InputAttributesList& PSS_InputAttributesList::operator = (const PSS_InputAttributesList& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
int PSS_InputAttributesList::Initialize(PSS_InputAttributeManager*    pInputManager,
                                        PSS_DynamicPropertiesManager* pPropManager,
                                        bool                          showAll,
                                        int                           symbolRef)
{
    m_pInputManager = pInputManager;
    m_pPropManager  = pPropManager;
    m_SymbolRef     = symbolRef;
    m_ShowAll       = showAll;

    BuildColumns();

    return Refresh();
}
//---------------------------------------------------------------------------
PSS_InputAttribute* PSS_InputAttributesList::GetSelectedInputAttribute()
{
    POSITION pPos = GetFirstSelectedItemPosition();

    if (pPos)
    {
        const int           index  = GetNextSelectedItem(pPos);
        PSS_InputAttribute* pInput = dynamic_cast<PSS_InputAttribute*>(reinterpret_cast<CObject*>(GetItemData(index)));

        if (pInput)
            return pInput;
    }

    return NULL;
}
//---------------------------------------------------------------------------
int PSS_InputAttributesList::Refresh()
{
    DeleteAllItems();

    if (!m_pInputManager)
        return 0;

    PSS_InputAttributeManager::IInputAttributeIterator it(&m_pInputManager->GetInputAttributeSet());
    std::size_t                                        lineCounter = 0;
    std::size_t                                        columnCounter;

    for (PSS_InputAttribute* pInputAttrib = it.GetFirst(); pInputAttrib; pInputAttrib = it.GetNext())
    {
        // check if necessary to show
        if (!m_ShowAll && m_SymbolRef != -1 && pInputAttrib->GetSymbolRef() != m_SymbolRef)
            continue;

        // add the symbol type icon
        InsertItem(LVIF_IMAGE | LVIF_PARAM,
                   lineCounter,
                   NULL,
                   0,
                   0,
                   pInputAttrib->GetSymbolRef() == -1 ? 0 : 1,
                   LPARAM(pInputAttrib));

        columnCounter = 1;

        PSS_Property* pProp =
                m_pPropManager ? m_pPropManager->GetPropertyItem(pInputAttrib->GetCategoryID(), pInputAttrib->GetItemID()) : NULL;

        SetItem(lineCounter, columnCounter, LVIF_TEXT, pProp ? pProp->GetLabel() : _T(""), 0, 0, 0, 0);
        ++columnCounter;

        // data type combo
        CString values;
        values.LoadString(IDS_PROPTYPE_LIST);

        // get the type string
        PSS_Tokenizer token(values);

        CString str;
        int     index = -1;

        if (pProp)
        {
            switch (pProp->GetType())
            {
                case PSS_Property::IE_T_EditString:    index = 0; break;
                case PSS_Property::IE_T_EditMultiline: index = 1; break;
                case PSS_Property::IE_T_EditNumber:    index = 2; break;
                case PSS_Property::IE_T_EditDate:      index = 3; break;
                case PSS_Property::IE_T_EditTime:      index = 4; break;
                case PSS_Property::IE_T_EditDuration:  index = 5; break;
                default:                                          break;
            }

            if (index >= 0)
                token.GetTokenAt(index, str);
        }
        else
            str = _T("#err");

        SetItem(lineCounter, columnCounter, LVIF_TEXT, str, 0, 0, 0, 0);
        ++columnCounter;

        SetItem(lineCounter, columnCounter, LVIF_TEXT, pInputAttrib->GetDefaultValue(), 0, 0, 0, 0);
        ++columnCounter;

        if (pInputAttrib->GetSymbolRef() != -1)
        {
            CODComponentSet* pSet = m_pDoc->GetModel()->FindSymbolByRefNumber(pInputAttrib->GetSymbolRef());

            if (pSet && pSet->GetSize() > 0)
            {
                PSS_BasicSymbol* pSymbol = dynamic_cast<PSS_BasicSymbol*>(pSet->GetAt(0));

                if (pSymbol)
                {
                    SetItem(lineCounter, columnCounter, LVIF_TEXT, pSymbol->GetSymbolName(), 0, 0, 0, 0);
                    ++columnCounter;
                }
            }
            else
            {
                SetItem(lineCounter, columnCounter, LVIF_TEXT, _T(""), 0, 0, 0, 0);
                ++columnCounter;
            }
        }
        else
        {
            SetItem(lineCounter, columnCounter, LVIF_TEXT, _T(""), 0, 0, 0, 0);
            ++columnCounter;
        }

        // increment the line counter
        ++lineCounter;
    }

    return lineCounter;
}
//---------------------------------------------------------------------------
void PSS_InputAttributesList::Empty()
{
    if (::IsWindow(GetSafeHwnd()))
        DeleteAllItems();
}
//---------------------------------------------------------------------------
void PSS_InputAttributesList::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
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
void PSS_InputAttributesList::BuildColumns()
{
    if (m_ColumnsBuilt)
        return;

    // load images
    PSS_ListCtrl::LoadImageList(IDB_IL_INPUTATTRIBUTELIST, 17, 1, RGB(255, 255, 255));
    SetImageList(m_pImageList, LVSIL_SMALL);

    PSS_ListCtrl::BuildColumns(5, g_InputAttributesColSize, g_InputAttributesColText);
    PSS_ListCtrl::SetFullRowSelect(TRUE);
    PSS_ListCtrl::EnableSort(TRUE);

    m_ColumnsBuilt = TRUE;
}
//---------------------------------------------------------------------------
void PSS_InputAttributesList::DocumentActivated(PSS_ProcessGraphModelDoc* pDoc)
{
    m_pDoc = pDoc;

    if (!pDoc)
        Empty();

    PSS_ProcessGraphModelMdlBP* pProcessGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDoc->GetModel());

    if (!pProcessGraphModel || !pProcessGraphModel->GetInputAttributes())
    {
        Initialize(NULL, NULL);
        return;
    }

    bool hasChanged = false;

    if (pDoc->GetDynamicPropertiesManager() != m_pPropManager)
        hasChanged = true;

    if (pProcessGraphModel && pProcessGraphModel->GetInputAttributes() != m_pInputManager)
        hasChanged = true;

    if (hasChanged)
        Initialize(pProcessGraphModel->GetInputAttributes(), pDoc->GetDynamicPropertiesManager());
}
//---------------------------------------------------------------------------
