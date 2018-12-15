//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//    Source file: ZCInputAttributesList.cpp

//#include <StdAfx.h>
#include "StdAfx.h"

#include "ZCInputAttributesList.h"
#include "ZBInputAttributes.h"

#include "zProperty\ZBDynamicPropertiesManager.h"
#include "zModel\ProcGraphModelDoc.h"
#include "ProcGraphModelMdlBP.h"

#include "zBaseLib\ZBDocumentObserverMsg.h"
#include "zModel\ZBSymbolObserverMsg.h"

#include "zModelBPRes.h"
#include "zModel\zModelRes.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"

#include "zBaseLib\ZBTokenizer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(ZCInputAttributesList, CListCtrl)


BEGIN_MESSAGE_MAP(ZCInputAttributesList, ZIListCtrl)
    //{{AFX_MSG_MAP(ZCInputAttributesList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCInputAttributesList 

#include "zRes32\ZRes.h"

static int _gInputAttributesColText[] = {    IDS_NOCOLUMNHEADER, 
                                            IDS_INPUTATTRIB_NAME_COLUMN,
                                            IDS_INPUTATTRIB_FLAG_COLUMN, 
                                            IDS_INPUTATTRIB_DEFVALUE_COLUMN, 
                                            IDS_INPUTATTRIB_ATTACHEDSYMBOL_COLUMN };
static int _gInputAttributesColSize[] = {    60,
                                            120, 
                                            100, 
                                            100,
                                            60 };

ZCInputAttributesList::ZCInputAttributesList ()
: m_pInputManager(NULL), 
  m_pPropManager(NULL),
  m_pComp(NULL),
  m_pDoc(NULL),
  m_ShowAll(false),
  m_SymbolRef(-1),
  m_ColumnsBuilt(FALSE)
{
}


ZCInputAttributesList::~ZCInputAttributesList()
{
    DeleteAllItems( TRUE );
}


void    ZCInputAttributesList::BuildColumns()
{
    if (m_ColumnsBuilt)
        return;
    // Load images
    ZIListCtrl::LoadImageList( IDB_IL_INPUTATTRIBUTELIST, 17, 1, RGB( 255, 255, 255 ) );
    SetImageList(m_pImageList, LVSIL_SMALL);    /* set extended stlyes*/

    ZIListCtrl::BuildColumns(5, _gInputAttributesColSize, _gInputAttributesColText );
    ZIListCtrl::SetFullRowSelect( TRUE );
    ZIListCtrl::EnableSort( TRUE );

    m_ColumnsBuilt = TRUE;
}

int ZCInputAttributesList::Initialize (ZBInputAttributeManager* pInputManager, ZBDynamicPropertiesManager* pPropManager, 
                                       bool ShowAll /*= false*/, int SymbolRef /*= -1*/)
{
    m_pInputManager = pInputManager;
    m_pPropManager = pPropManager;
    m_ShowAll = ShowAll;
    m_SymbolRef = SymbolRef;
    ZCInputAttributesList::BuildColumns();

    return ZCInputAttributesList::Refresh();
}

int ZCInputAttributesList::Refresh ()
{
    DeleteAllItems();

    if (!m_pInputManager)
        return 0;
    size_t        LineCounter = 0;
    size_t        ColumnCounter;

    ZBInputAttributeIterator i(&m_pInputManager->GetInputAttributeSet());
    for (ZBInputAttribute* pInputAttrib = i.GetFirst(); pInputAttrib; pInputAttrib = i.GetNext())
    {
        // Check if necessary to display
        if (m_ShowAll == false &&
            m_SymbolRef != -1 && 
            pInputAttrib->GetSymbolRef() != m_SymbolRef)
            continue;

        // Add the symbol type icon
        InsertItem( LVIF_IMAGE | LVIF_PARAM, LineCounter, 
                    NULL,
                    0, 0, 
                    (pInputAttrib->GetSymbolRef() == -1) ? 0 : 1, 
                    (LPARAM)pInputAttrib);
        ColumnCounter = 1;

        ZBProperty* pProp = (m_pPropManager) ? m_pPropManager->GetPropertyItem( pInputAttrib->GetCategoryID(), pInputAttrib->GetItemID() ) : NULL;
            
        SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
                 (pProp) ? pProp->GetLabel() : _T(""),
                 0, 0, 0, 0 );

        CString strValues;
        // Data type combo.
        strValues.LoadString( IDS_PROPTYPE_LIST );
        // Retreive the right type string
        ZBTokenizer token( strValues );

        CString s;
        int Index = -1;
        if (pProp)
        {
            switch (pProp->GetPTType())
            {
                case ZBProperty::PT_EDIT_STRING:
                {
                    Index = 0;
                    break;
                }
                case ZBProperty::PT_EDIT_MULTILINE:
                {
                    Index = 1;
                    break;
                }
                case ZBProperty::PT_EDIT_NUMBER:
                {
                    Index = 2;
                    break;
                }
                case ZBProperty::PT_EDIT_DATE:
                {
                    Index = 3;
                    break;
                }
                case ZBProperty::PT_EDIT_TIME:
                {
                    Index = 4;
                    break;
                }
                case ZBProperty::PT_EDIT_DURATION:
                {
                    Index = 5;
                    break;
                }
                default: break;
            }
            if (Index >= 0)
                token.GetTokenAt( Index, s );
        }
        else
        {
            s = _T("#err");
        }

        SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
                 s,
                 0, 0, 0, 0 );

        SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
                 pInputAttrib->GetDefaultValue(),
                 0, 0, 0, 0 );

        if (pInputAttrib->GetSymbolRef() != -1)
        {
            CODComponentSet* pSet = m_pDoc->GetModel()->FindSymbolByRefNumber( pInputAttrib->GetSymbolRef() );
            if (pSet && pSet->GetSize() > 0)
            {
                SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
                         dynamic_cast<ZIBasicSymbol*>(pSet->GetAt(0))->GetSymbolName(),
                         0, 0, 0, 0 );
            }
            else
            {
                SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
                         _T(""),
                         0, 0, 0, 0 );
            }
        }
        else
        {
            SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
                     _T(""),
                     0, 0, 0, 0 );
        }
        // Increment Line counter
        ++LineCounter;
    }

    return LineCounter;
}

void ZCInputAttributesList::Empty()
{
    if (::IsWindow(GetSafeHwnd()))
        DeleteAllItems();
}

ZBInputAttribute*    ZCInputAttributesList::GetSelectedInputAttribute()
{
    int    Index;
    POSITION pos = GetFirstSelectedItemPosition();
    if (pos != NULL)     
    {
        Index = GetNextSelectedItem( pos );
        CObject* pObj = (CObject*)GetItemData( Index );
        if (pObj && ISA(pObj,ZBInputAttribute))
            return dynamic_cast<ZBInputAttribute*>(pObj);
    }
    return NULL;
}


void ZCInputAttributesList::DocumentActivated( ZDProcessGraphModelDoc* pDoc )
{
    m_pDoc = pDoc;
    if (!pDoc)
        Empty();

    if (!pDoc->GetModel() || !ISA(pDoc->GetModel(),ZDProcessGraphModelMdlBP) ||
        !dynamic_cast<ZDProcessGraphModelMdlBP*>(pDoc->GetModel())->GetInputAttributes())
    {
        Initialize( NULL, NULL );
        return;
    }

    bool HasChanged = false;
    if (//pDoc->GetDynamicPropertiesManager() &&
        pDoc->GetDynamicPropertiesManager() != m_pPropManager)
        HasChanged = true;

    if (pDoc->GetModel() &&
        ISA(pDoc->GetModel(),ZDProcessGraphModelMdlBP) &&
//        dynamic_cast<ZDProcessGraphModelMdlBP*>(pDoc->GetModel())->GetInputAttributes() &&
        dynamic_cast<ZDProcessGraphModelMdlBP*>(pDoc->GetModel())->GetInputAttributes() != m_pInputManager)
        HasChanged = true;

    if (HasChanged)
        Initialize( dynamic_cast<ZDProcessGraphModelMdlBP*>(pDoc->GetModel())->GetInputAttributes(), pDoc->GetDynamicPropertiesManager() );



}


void ZCInputAttributesList::OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg )
{
    if (pMsg && ISA(pMsg,ZBSymbolObserverMsg))
    {
        if (dynamic_cast<ZBSymbolObserverMsg*>(pMsg)->GetActionType() == ZBSymbolObserverMsg::ElementSelected)
        {
            m_pComp = dynamic_cast<ZBSymbolObserverMsg*>(pMsg)->GetpElement();
            if (m_pComp &&
                (ISA(m_pComp,ZBSymbol) || ISA(m_pComp,ZBLinkSymbol)))
                SetSymbolRef( dynamic_cast<ZIBasicSymbol*>(m_pComp)->GetSymbolReferenceNumber() );
            else
                SetSymbolRef( -1 );
        }
    }
    else
    // Check about document close
    if (pMsg && ISA(pMsg,ZBDocumentObserverMsg) &&
        ISA(dynamic_cast<ZBDocumentObserverMsg*>(pMsg)->GetpDocument(),ZDProcessGraphModelDoc))
    {
        switch (dynamic_cast<ZBDocumentObserverMsg*>(pMsg)->GetMessageID())
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
                DocumentActivated( dynamic_cast<ZDProcessGraphModelDoc*>( dynamic_cast<ZBDocumentObserverMsg*>(pMsg)->GetpDocument() ) );
            }

        }
    }


}

