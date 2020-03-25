/****************************************************************************
 * ==> PSS_GridGroup -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid group                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GridGroupH
#define PSS_GridGroupH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_GridGroup
    #define PSS_GridGroup ZCGridGroup
#endif

#ifdef _ZREPORTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Grid group
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GridGroup : public CObject
{
    DECLARE_SERIAL(PSS_GridGroup)

    public:
        /**
        * Constructor
        *@param pGridCore - the grid core
        */
        PSS_GridGroup(CGXGridCore* pGrid = NULL);

        /**
        * Constructor
        *@param pGridCore - the grid core
        *@param row - the row
        *@param col - the column
        *@param coveringCells - the covering cell count
        *@param horizontal - if true, the layer will be horizontal instead of vertical
        *@param collapsed - if true, the group is collapsed
        *@param label - the label
        *@param tooltipText - the tooltip text
        */
        PSS_GridGroup(CGXGridCore*   pGrid,
                      ROWCOL         row,
                      ROWCOL         col,
                      int            coveringCells,
                      bool           horizontal,
                      bool           collapsed,
                      const CString& label       = _T(""),
                      const CString& tooltipText = _T(""));

        virtual ~PSS_GridGroup();

        /**
        * Creates the control
        */
        virtual void CreateControl();

        /**
        * Creates the control
        *@param row - the row
        *@param col - the column
        *@param coveringCells - the covering cell count
        *@param horizontal - if true, the layer will be horizontal instead of vertical
        *@param collapsed - if true, the group is collapsed
        *@param label - the label
        *@param tooltipText - the tooltip text
        */
        virtual void CreateControl(ROWCOL         row,
                                   ROWCOL         col,
                                   int            coveringCells,
                                   bool           horizontal,
                                   bool           collapsed,
                                   const CString& label       = _T(""),
                                   const CString& tooltipText = _T(""));

        /**
        * Gets the grid core
        *@return the grid core
        */
        virtual inline CGXGridCore* GetGridCore() const;

        /**
        * Sets the grid core
        *@param pGrid - the grid core
        */
        virtual inline void SetGridCore(CGXGridCore* pGrid);

        /**
        * Gets the row
        *@return the row
        */
        virtual inline ROWCOL GetRow() const;

        /**
        * Gets the column
        *@return the column
        */
        virtual inline ROWCOL GetCol() const;

        /**
        * Gets if the group is collapsed
        *@return true if the group is collapsed, otherwise false
        */
        virtual inline bool GetCollapsed() const;

        /**
        * Sets the group as collapsed
        *@bool value - if true, the group is collapsed
        */
        virtual void SetCollapsed(bool value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        /**
        * Applies the state
        */
        virtual void ApplyState();

    private:
        CGXGridCore* m_pGrid;
        ROWCOL       m_Row;
        ROWCOL       m_Col;
        CString      m_Label;
        CString      m_TooltipText;
        int          m_CoveringCells;
        bool         m_Horizontal;
        bool         m_Collapsed;
};

//---------------------------------------------------------------------------
// PSS_GridGroup
//---------------------------------------------------------------------------
CGXGridCore* PSS_GridGroup::GetGridCore() const
{
    return m_pGrid;
}
//---------------------------------------------------------------------------
void PSS_GridGroup::SetGridCore(CGXGridCore* pGrid)
{
    m_pGrid = pGrid;
}
//---------------------------------------------------------------------------
ROWCOL PSS_GridGroup::GetRow() const
{
    return m_Row;
}
//---------------------------------------------------------------------------
ROWCOL PSS_GridGroup::GetCol() const
{
    return m_Col;
}
//---------------------------------------------------------------------------
bool PSS_GridGroup::GetCollapsed() const
{
    return m_Collapsed;
}
//---------------------------------------------------------------------------

#endif
