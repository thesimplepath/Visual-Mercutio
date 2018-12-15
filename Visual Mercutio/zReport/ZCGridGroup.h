// ZCGridGroup.h: interface for the ZCGridGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZCGRIDGROUP_H__83BBC2E6_D2F9_44B9_9EF0_9811A3D294A5__INCLUDED_)
#define AFX_ZCGRIDGROUP_H__83BBC2E6_D2F9_44B9_9EF0_9811A3D294A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZREPORTEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZCGridGroup : public CObject
{
    DECLARE_SERIAL( ZCGridGroup )

public:

    ZCGridGroup( CGXGridCore* pGrid = NULL );

    ZCGridGroup( CGXGridCore*    pGrid,
                 ROWCOL            Row,
                 ROWCOL            Col,
                 int            CoveringCells,
                 bool            Horizontal,
                 bool            Collapsed,
                 const CString    Label            = _T( "" ),
                 const CString    ToolTipText        = _T( "" ) );

    virtual ~ZCGridGroup();

    ROWCOL GetRow() const
    {
        return m_Row;
    };

    ROWCOL GetCol() const
    {
        return m_Col;
    };

    bool GetCollapsed() const;
    void SetCollapsed( bool value );

    CGXGridCore* GetGridCore() const
    {
        return m_pGrid;
    };

    void SetGridCore( CGXGridCore* pGrid )
    {
        m_pGrid = pGrid;
    };

    void CreateControl();
    void CreateControl( ROWCOL            Row,
                        ROWCOL            Col,
                        int                CoveringCells,
                        bool            Horizontal,
                        bool            Collapsed,
                        const CString    Label            = _T( "" ),
                        const CString    ToolTipText        = _T( "" ) );

    virtual void Serialize( CArchive& ar );

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

protected:

    void ApplyState();

private:

    int                m_CoveringCells;
    ROWCOL            m_Row;
    ROWCOL            m_Col;
    bool            m_Horizontal;
    bool            m_Collapsed;
    CString            m_Label;
    CString            m_ToolTipText;

    CGXGridCore*    m_pGrid;
};

inline bool ZCGridGroup::GetCollapsed() const
{
    return m_Collapsed;
}

#endif // !defined(AFX_ZCGRIDGROUP_H__83BBC2E6_D2F9_44B9_9EF0_9811A3D294A5__INCLUDED_)