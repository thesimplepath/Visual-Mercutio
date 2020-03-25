/****************************************************************************
 * ==> PSS_GridGroup -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid group                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GridGroup.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_GridGroup, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_GridGroup
//---------------------------------------------------------------------------
PSS_GridGroup::PSS_GridGroup(CGXGridCore* pGrid) :
    CObject(),
    m_pGrid(pGrid),
    m_Row(0),
    m_Col(0),
    m_CoveringCells(0),
    m_Horizontal(true),
    m_Collapsed(false)
{}
//---------------------------------------------------------------------------
PSS_GridGroup::PSS_GridGroup(CGXGridCore*   pGrid,
                             ROWCOL         row,
                             ROWCOL         col,
                             int            coveringCells,
                             bool           horizontal,
                             bool           collapsed,
                             const CString& label,
                             const CString& tooltipText) :
    CObject(),
    m_pGrid(pGrid),
    m_Row(row),
    m_Col(col),
    m_Label(label),
    m_TooltipText(tooltipText),
    m_CoveringCells(coveringCells),
    m_Horizontal(horizontal),
    m_Collapsed(collapsed)
{
    CreateControl();
}
//---------------------------------------------------------------------------
PSS_GridGroup::~PSS_GridGroup()
{}
//---------------------------------------------------------------------------
void PSS_GridGroup::CreateControl()
{
    if (!m_pGrid)
        return;

    if (m_Row > m_pGrid->GetRowCount())
        m_pGrid->SetRowCount(m_Row + 5);

    if (m_Col > m_pGrid->GetColCount())
        m_pGrid->SetColCount(m_Col + 5);

    m_pGrid->SetStyleRange(CGXRange(m_Row, m_Col),
                           CGXStyle()
                                   .SetControl          (GX_IDS_CTRL_CHECKBOX)
                                   .SetValue            (m_Collapsed ? 0L : 1L)
                                   .SetChoiceList       (m_Label)
                                   .SetUserAttribute    (GX_IDS_UA_TOOLTIPTEXT, m_TooltipText)
                                   .SetVerticalAlignment(DT_VCENTER));

    // if the initial state is collapsed, apply it
    if (m_Collapsed)
        ApplyState();
}
//---------------------------------------------------------------------------
void PSS_GridGroup::CreateControl(ROWCOL         row,
                                  ROWCOL         col,
                                  int            coveringCells,
                                  bool           horizontal,
                                  bool           collapsed,
                                  const CString& label,
                                  const CString& tooltipText)
{
    m_Row           = row;
    m_Col           = col;
    m_Label         = label;
    m_TooltipText   = tooltipText;
    m_CoveringCells = coveringCells;
    m_Horizontal    = horizontal;
    m_Collapsed     = collapsed;

    CreateControl();
}
//---------------------------------------------------------------------------
void PSS_GridGroup::SetCollapsed(bool value)
{
    if (!m_pGrid)
        return;

    // if no change, return
    if (m_Collapsed == value)
        return;

    m_Collapsed = value;
    ApplyState();
}
//---------------------------------------------------------------------------
void PSS_GridGroup::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements
        ar << m_CoveringCells;
        ar << m_Row;
        ar << m_Col;

        ar << WORD(m_Horizontal);
        ar << WORD(m_Collapsed);

        ar << m_Label;
        ar << m_TooltipText;
    }
    else
    {
        ar >> m_CoveringCells;
        ar >> m_Row;
        ar >> m_Col;

        WORD wValue;
        ar >> wValue;
        m_Horizontal = bool(wValue == 1);

        ar >> wValue;
        m_Collapsed = bool(wValue == 1);

        ar >> m_Label;
        ar >> m_TooltipText;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GridGroup::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GridGroup::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_GridGroup::ApplyState()
{
    // if should collpase, hide the cells
    if (m_Collapsed)
    {
        if (m_Horizontal)
            m_pGrid->HideCols(m_Col + 1, m_Col + m_CoveringCells, TRUE);
        else
            m_pGrid->HideRows(m_Row + 1, m_Row + m_CoveringCells, TRUE);
    }
    else
    // otherwise, unhide cells
    if (m_Horizontal)
        m_pGrid->HideCols(m_Col + 1, m_Col + m_CoveringCells, FALSE);
    else
        m_pGrid->HideRows(m_Row + 1, m_Row + m_CoveringCells, FALSE);
}
//---------------------------------------------------------------------------
