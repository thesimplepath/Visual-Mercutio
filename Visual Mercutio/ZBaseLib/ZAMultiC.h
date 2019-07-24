//## begin module%38818567009E.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%38818567009E.cm

//## begin module%38818567009E.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%38818567009E.cp

//## Module: ZAMultiC%38818567009E; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZAMultiC.h

#ifndef ZAMultiC_h
#define ZAMultiC_h 1

//## begin module%38818567009E.additionalIncludes preserve=no
//## end module%38818567009E.additionalIncludes

//## begin module%38818567009E.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%38818567009E.includes

// ZAObject
#include "ZAObject.h"
// ZBFldColMg
#include "ZBFldClM.h"
//## begin module%38818567009E.declarations preserve=no
//## end module%38818567009E.declarations

//## begin module%38818567009E.additionalDeclarations preserve=yes
#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS
//## end module%38818567009E.additionalDeclarations


//## Class: PLFNMultiColumn%388185310245
//    Graphic object functionnalities.
//## Category: ZBaseLib::Base objects%37E9429A0111
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%38819AC003D2;ZBFieldColumnManager { -> }

class AFX_EXT_CLASS PLFNMultiColumn : public PlanFinObject  //## Inherits: <unnamed>%388185310263
{
  //## begin PLFNMultiColumn%388185310245.initialDeclarations preserve=yes
    public:
    // Inherited feature
        typedef PlanFinObject inherited;
  //## end PLFNMultiColumn%388185310245.initialDeclarations

  public:
    //## Constructors (generated)
      PLFNMultiColumn();

      PLFNMultiColumn(const PLFNMultiColumn &right);

    //## Destructor (generated)
      virtual ~PLFNMultiColumn();

    //## Assignment Operation (generated)
      const PLFNMultiColumn & operator=(const PLFNMultiColumn &right);


    //## Other Operations (specified)
      //## Operation: operator =%948017479
      //    A copy constructor with a pointer.
      const PLFNMultiColumn& operator = (const PLFNMultiColumn* right);

      //## Operation: Serialize%948017480
      //    Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: Clone%948017481
      //    Make a clone of the object.
      virtual PlanFinObject* Clone ();

      //## Operation: CopyObject%948017482
      virtual void CopyObject (PlanFinObject* pSrc);

      //## Operation: GetRightSubMenu%948017483
      //    Return the number of the submenu when the user click the
      //    right mouse button.
      virtual UINT GetRightSubMenu () const;

      //## Operation: GetPropertyTabs%948017484
      //    Return the list of tabs that should be displayed when
      //    the user asks for object properties.
      virtual UINT GetPropertyTabs () const;

      //## Operation: DrawObject%948017512
      //    Draw the object with the current DC.
      virtual void DrawObject (CDC* pDC, ZIView* pView);

      //## Operation: GetColumnCount%948017513
      //    Return the number of columns
      size_t GetColumnCount () const;

      //## Operation: AddColumn%948017514
      //    Add a new column into the column array.
      void AddColumn (ZBFieldColumn* pColumn);

      //## Operation: AddColumn%948017515
      //    Add a new column into the column array.
      void AddColumn (const CString HeaderName, const CStringArray& Values);

      //## Operation: RemoveColumn%948017516
      //    Remove a specific column from the manager.
      bool RemoveColumn (const CString& HeaderName);

      //## Operation: RemoveColumn%948017517
      //    Remove a specific column from the manager.
      bool RemoveColumn (ZBFieldColumn* pColumn);

      //## Operation: RemoveAllColumns%948017518
      //    remove all columns.
      void RemoveAllColumns ();

      //## Operation: FindColumn%948017519
      //    Find a column by its header name.
      ZBFieldColumn* FindColumn (const CString& HeaderName);

      //## Operation: FindColumn%948017520
      //    Find a column by its column pointer.
      bool FindColumn (ZBFieldColumn* pColumn);

      //## Operation: GetColumnAt%948017521
      //    Get a column at a specific position.
      ZBFieldColumn* GetColumnAt (size_t Index) const;

      //## Operation: InsertColumnAt%948017522
      //    Insert a new column at a specific position.
      void InsertColumnAt (ZBFieldColumn* pColumn, size_t Index);

      //## Operation: RemoveColumnAt%948017523
      //    Remove a column at a specific position.
      bool RemoveColumnAt (size_t Index);

      //## Operation: GetRowValues%948017524
      //    Get row, fill a string value array.
      bool GetRowValues (CStringArray& RowValues, size_t RowIndex);

      //## Operation: GetColumnRowValue%948017525
      //    Get the value of a specific column and row. Return by
      //    reference the value. If not found, return false.
      bool GetColumnRowValue (const CString ColumnName, size_t RowIndex, CString& Value);

      //## Operation: GetColumnRowValue%948017526
      //    Get the value of a specific column and row. Return by
      //    reference the value. If not found, return false.
      bool GetColumnRowValue (size_t ColumnIndex, size_t RowIndex, CString& Value);

      //## Operation: SetColumnRowValue%948222414
      //    Set the value of a specific column and row. Return by
      //    reference the value. If not found, return false.
      bool SetColumnRowValue (size_t ColumnIndex, size_t RowIndex, CString Value);

      //## Operation: SetColumnRowValue%948222415
      //    Set the value of a specific column and row. Return by
      //    reference the value. If not found, return false.
      bool SetColumnRowValue (const CString ColumnName, size_t RowIndex, CString Value);

      //## Operation: IsSelected%948017528
      //    Is this object selected.
      virtual BOOL IsSelected (const CPoint& point) const;

      //## Operation: AutoSizeColumn%948017538
      //    Auto size a specific column from the manager.
      bool AutoSizeColumn (const CString& HeaderName);

      //## Operation: AutoSizeColumn%948017539
      //    Auto size a specific column from the manager.
      bool AutoSizeColumn (ZBFieldColumn* pColumn);

      //## Operation: AutoSizeColumnAt%948017540
      //    Auto size a specific column from the manager.
      bool AutoSizeColumnAt (size_t Index);

      //## Operation: AutoSizeAllColumns%948017541
      //    Auto size all columns from the manager.
      bool AutoSizeAllColumns ();

      //## Operation: SizeColumn%948017542
      //    Size a specific column from the manager.
      bool SizeColumn (const CString& HeaderName, size_t Width);

      //## Operation: SizeColumn%948017543
      //    Size a specific column from the manager.
      bool SizeColumn (ZBFieldColumn* pColumn, size_t Width);

      //## Operation: SizeColumnAt%948017544
      //    Size a specific column from the manager.
      bool SizeColumnAt (size_t Index, size_t Width);

      //## Operation: SizeAllColumns%948017545
      //    Size all columns from the manager.
      bool SizeAllColumns (size_t Width);

      //## Operation: GetHeaderNames%948017547
      //    Get the header names and fill a string value array.
      bool GetHeaderNames (CStringArray& HeaderNames);

      //## Operation: CreateColumnWithHeaderNames%948222397
      //    Create new columns with the header names filled in a
      //    string value array.
      bool CreateColumnWithHeaderNames (CStringArray& HeaderNames);

      //## Operation: AddRowValues%948222398
      //    Add a complete row values with a string value array.
      bool AddRowValues (CStringArray& RowValues);

      //## Operation: InsertRowValuesAt%948222399
      //    Insert a complete row values at a specific index with a
      //    string value array. If the row already exists, replace
      //    values.
      bool InsertRowValuesAt (CStringArray& RowValues, size_t RowIndex);

      //## Operation: SetRowValuesAt%948222407
      //    Set a complete row values at a specific index with a
      //    string value array. If the row already exists, replace
      //    values.
      bool SetRowValuesAt (CStringArray& RowValues, size_t RowIndex);

      //## Operation: RemoveColumnValues%948222408
      //    Remove all values of a specific column from the manager.
      bool RemoveColumnValues (const CString& HeaderName);

      //## Operation: RemoveColumnValues%948222409
      //    Remove all values of a specific column from the manager.
      bool RemoveColumnValues (ZBFieldColumn* pColumn);

      //## Operation: RemoveAllValues%948222410
      //    remove all values of all columns.
      void RemoveAllValues ();

      //## Operation: RemoveColumnValuesAt%948222411
      //    Remove all values of a column at a specific position.
      bool RemoveColumnValuesAt (size_t Index);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ShowHeader%3881F0610378
      //    Flag for showing or not the header.
      const BOOL GetShowHeader () const;
      void SetShowHeader (BOOL value);

    // Additional Public Declarations
      //## begin PLFNMultiColumn%388185310245.public preserve=yes
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
      //## end PLFNMultiColumn%388185310245.public
  protected:
    // Additional Protected Declarations
      //## begin PLFNMultiColumn%388185310245.protected preserve=yes
    DECLARE_SERIAL(PLFNMultiColumn)
      //## end PLFNMultiColumn%388185310245.protected
  private:
    // Data Members for Class Attributes

      //## Attribute: MultiColumnManager%3881AE8C02CB
      //    The multi column manager object.
      //## begin PLFNMultiColumn::MultiColumnManager%3881AE8C02CB.attr preserve=no  private: ZBFieldColumnManager {U} 
      ZBFieldColumnManager m_MultiColumnManager;
      //## end PLFNMultiColumn::MultiColumnManager%3881AE8C02CB.attr

      //## begin PLFNMultiColumn::ShowHeader%3881F0610378.attr preserve=no  public: BOOL {U} 
      BOOL m_ShowHeader;
      //## end PLFNMultiColumn::ShowHeader%3881F0610378.attr

    // Additional Private Declarations
      //## begin PLFNMultiColumn%388185310245.private preserve=yes
      //## end PLFNMultiColumn%388185310245.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin PLFNMultiColumn%388185310245.implementation preserve=yes
      //## end PLFNMultiColumn%388185310245.implementation

};

//## begin PLFNMultiColumn%388185310245.postscript preserve=yes
//## end PLFNMultiColumn%388185310245.postscript

// Class PLFNMultiColumn 


//## Other Operations (inline)
inline UINT PLFNMultiColumn::GetRightSubMenu () const
{
  //## begin PLFNMultiColumn::GetRightSubMenu%948017483.body preserve=yes
      return g_MultiColumnRightSubMenu;
  //## end PLFNMultiColumn::GetRightSubMenu%948017483.body
}

inline UINT PLFNMultiColumn::GetPropertyTabs () const
{
  //## begin PLFNMultiColumn::GetPropertyTabs%948017484.body preserve=yes
      return PropertyGeneralBasicPage | PropertySizePage | PropertyMultiColumnPage;
  //## end PLFNMultiColumn::GetPropertyTabs%948017484.body
}

inline size_t PLFNMultiColumn::GetColumnCount () const
{
  //## begin PLFNMultiColumn::GetColumnCount%948017513.body preserve=yes
    return m_MultiColumnManager.GetCount();
  //## end PLFNMultiColumn::GetColumnCount%948017513.body
}

inline void PLFNMultiColumn::AddColumn (ZBFieldColumn* pColumn)
{
  //## begin PLFNMultiColumn::AddColumn%948017514.body preserve=yes
    m_MultiColumnManager.AddColumn( pColumn );
  //## end PLFNMultiColumn::AddColumn%948017514.body
}

inline void PLFNMultiColumn::AddColumn (const CString HeaderName, const CStringArray& Values)
{
  //## begin PLFNMultiColumn::AddColumn%948017515.body preserve=yes
    m_MultiColumnManager.AddColumn( HeaderName, Values );
  //## end PLFNMultiColumn::AddColumn%948017515.body
}

inline bool PLFNMultiColumn::RemoveColumn (const CString& HeaderName)
{
  //## begin PLFNMultiColumn::RemoveColumn%948017516.body preserve=yes
    return m_MultiColumnManager.RemoveColumn( HeaderName );
  //## end PLFNMultiColumn::RemoveColumn%948017516.body
}

inline bool PLFNMultiColumn::RemoveColumn (ZBFieldColumn* pColumn)
{
  //## begin PLFNMultiColumn::RemoveColumn%948017517.body preserve=yes
    return m_MultiColumnManager.RemoveColumn( pColumn );
  //## end PLFNMultiColumn::RemoveColumn%948017517.body
}

inline void PLFNMultiColumn::RemoveAllColumns ()
{
  //## begin PLFNMultiColumn::RemoveAllColumns%948017518.body preserve=yes
    m_MultiColumnManager.RemoveAll();
  //## end PLFNMultiColumn::RemoveAllColumns%948017518.body
}

inline ZBFieldColumn* PLFNMultiColumn::FindColumn (const CString& HeaderName)
{
  //## begin PLFNMultiColumn::FindColumn%948017519.body preserve=yes
    return m_MultiColumnManager.FindColumn( HeaderName );
  //## end PLFNMultiColumn::FindColumn%948017519.body
}

inline bool PLFNMultiColumn::FindColumn (ZBFieldColumn* pColumn)
{
  //## begin PLFNMultiColumn::FindColumn%948017520.body preserve=yes
    return m_MultiColumnManager.FindColumn( pColumn );
  //## end PLFNMultiColumn::FindColumn%948017520.body
}

inline ZBFieldColumn* PLFNMultiColumn::GetColumnAt (size_t Index) const
{
  //## begin PLFNMultiColumn::GetColumnAt%948017521.body preserve=yes
    return m_MultiColumnManager.GetColumnAt( Index );
  //## end PLFNMultiColumn::GetColumnAt%948017521.body
}

inline void PLFNMultiColumn::InsertColumnAt (ZBFieldColumn* pColumn, size_t Index)
{
  //## begin PLFNMultiColumn::InsertColumnAt%948017522.body preserve=yes
    m_MultiColumnManager.InsertColumnAt( pColumn, Index );
  //## end PLFNMultiColumn::InsertColumnAt%948017522.body
}

inline bool PLFNMultiColumn::RemoveColumnAt (size_t Index)
{
  //## begin PLFNMultiColumn::RemoveColumnAt%948017523.body preserve=yes
    return m_MultiColumnManager.RemoveColumnAt( Index );
  //## end PLFNMultiColumn::RemoveColumnAt%948017523.body
}

inline bool PLFNMultiColumn::GetRowValues (CStringArray& RowValues, size_t RowIndex)
{
  //## begin PLFNMultiColumn::GetRowValues%948017524.body preserve=yes
    return m_MultiColumnManager.GetRowValues( RowValues, RowIndex );
  //## end PLFNMultiColumn::GetRowValues%948017524.body
}

inline bool PLFNMultiColumn::GetColumnRowValue (const CString ColumnName, size_t RowIndex, CString& Value)
{
  //## begin PLFNMultiColumn::GetColumnRowValue%948017525.body preserve=yes
    return m_MultiColumnManager.GetColumnRowValue( ColumnName, RowIndex, Value );
  //## end PLFNMultiColumn::GetColumnRowValue%948017525.body
}

inline bool PLFNMultiColumn::GetColumnRowValue (size_t ColumnIndex, size_t RowIndex, CString& Value)
{
  //## begin PLFNMultiColumn::GetColumnRowValue%948017526.body preserve=yes
    return m_MultiColumnManager.GetColumnRowValue( ColumnIndex, RowIndex, Value );
  //## end PLFNMultiColumn::GetColumnRowValue%948017526.body
}

inline bool PLFNMultiColumn::SetColumnRowValue (size_t ColumnIndex, size_t RowIndex, CString Value)
{
  //## begin PLFNMultiColumn::SetColumnRowValue%948222414.body preserve=yes
    return m_MultiColumnManager.SetColumnRowValue( ColumnIndex, RowIndex, Value );
  //## end PLFNMultiColumn::SetColumnRowValue%948222414.body
}

inline bool PLFNMultiColumn::SetColumnRowValue (const CString ColumnName, size_t RowIndex, CString Value)
{
  //## begin PLFNMultiColumn::SetColumnRowValue%948222415.body preserve=yes
    return m_MultiColumnManager.SetColumnRowValue( ColumnName, RowIndex, Value );
  //## end PLFNMultiColumn::SetColumnRowValue%948222415.body
}

inline BOOL PLFNMultiColumn::IsSelected (const CPoint& point) const
{
  //## begin PLFNMultiColumn::IsSelected%948017528.body preserve=yes
    return( m_rctObject.PtInRect( point ) );
  //## end PLFNMultiColumn::IsSelected%948017528.body
}

inline bool PLFNMultiColumn::AutoSizeColumn (const CString& HeaderName)
{
  //## begin PLFNMultiColumn::AutoSizeColumn%948017538.body preserve=yes
    return m_MultiColumnManager.AutoSizeColumn( HeaderName );
  //## end PLFNMultiColumn::AutoSizeColumn%948017538.body
}

inline bool PLFNMultiColumn::AutoSizeColumn (ZBFieldColumn* pColumn)
{
  //## begin PLFNMultiColumn::AutoSizeColumn%948017539.body preserve=yes
    return m_MultiColumnManager.AutoSizeColumn( pColumn );
  //## end PLFNMultiColumn::AutoSizeColumn%948017539.body
}

inline bool PLFNMultiColumn::AutoSizeColumnAt (size_t Index)
{
  //## begin PLFNMultiColumn::AutoSizeColumnAt%948017540.body preserve=yes
    return m_MultiColumnManager.AutoSizeColumnAt( Index );
  //## end PLFNMultiColumn::AutoSizeColumnAt%948017540.body
}

inline bool PLFNMultiColumn::AutoSizeAllColumns ()
{
  //## begin PLFNMultiColumn::AutoSizeAllColumns%948017541.body preserve=yes
    return m_MultiColumnManager.AutoSizeAllColumns();
  //## end PLFNMultiColumn::AutoSizeAllColumns%948017541.body
}

inline bool PLFNMultiColumn::SizeColumn (const CString& HeaderName, size_t Width)
{
  //## begin PLFNMultiColumn::SizeColumn%948017542.body preserve=yes
    return m_MultiColumnManager.SizeColumn( HeaderName, Width );
  //## end PLFNMultiColumn::SizeColumn%948017542.body
}

inline bool PLFNMultiColumn::SizeColumn (ZBFieldColumn* pColumn, size_t Width)
{
  //## begin PLFNMultiColumn::SizeColumn%948017543.body preserve=yes
    return m_MultiColumnManager.SizeColumn( pColumn, Width );
  //## end PLFNMultiColumn::SizeColumn%948017543.body
}

inline bool PLFNMultiColumn::SizeColumnAt (size_t Index, size_t Width)
{
  //## begin PLFNMultiColumn::SizeColumnAt%948017544.body preserve=yes
    return m_MultiColumnManager.SizeColumnAt( Index, Width );
  //## end PLFNMultiColumn::SizeColumnAt%948017544.body
}

inline bool PLFNMultiColumn::SizeAllColumns (size_t Width)
{
  //## begin PLFNMultiColumn::SizeAllColumns%948017545.body preserve=yes
    return m_MultiColumnManager.SizeAllColumns( Width );
  //## end PLFNMultiColumn::SizeAllColumns%948017545.body
}

inline bool PLFNMultiColumn::GetHeaderNames (CStringArray& HeaderNames)
{
  //## begin PLFNMultiColumn::GetHeaderNames%948017547.body preserve=yes
    return m_MultiColumnManager.GetHeaderNames( HeaderNames );
  //## end PLFNMultiColumn::GetHeaderNames%948017547.body
}

inline bool PLFNMultiColumn::CreateColumnWithHeaderNames (CStringArray& HeaderNames)
{
  //## begin PLFNMultiColumn::CreateColumnWithHeaderNames%948222397.body preserve=yes
    return m_MultiColumnManager.CreateColumnWithHeaderNames( HeaderNames );
  //## end PLFNMultiColumn::CreateColumnWithHeaderNames%948222397.body
}

inline bool PLFNMultiColumn::AddRowValues (CStringArray& RowValues)
{
  //## begin PLFNMultiColumn::AddRowValues%948222398.body preserve=yes
    return m_MultiColumnManager.AddRowValues( RowValues );
  //## end PLFNMultiColumn::AddRowValues%948222398.body
}

inline bool PLFNMultiColumn::InsertRowValuesAt (CStringArray& RowValues, size_t RowIndex)
{
  //## begin PLFNMultiColumn::InsertRowValuesAt%948222399.body preserve=yes
    return m_MultiColumnManager.InsertRowValuesAt( RowValues, RowIndex );
  //## end PLFNMultiColumn::InsertRowValuesAt%948222399.body
}

inline bool PLFNMultiColumn::SetRowValuesAt (CStringArray& RowValues, size_t RowIndex)
{
  //## begin PLFNMultiColumn::SetRowValuesAt%948222407.body preserve=yes
    return m_MultiColumnManager.SetRowValuesAt( RowValues, RowIndex );
  //## end PLFNMultiColumn::SetRowValuesAt%948222407.body
}

inline bool PLFNMultiColumn::RemoveColumnValues (const CString& HeaderName)
{
  //## begin PLFNMultiColumn::RemoveColumnValues%948222408.body preserve=yes
    return m_MultiColumnManager.RemoveColumnValues( HeaderName );
  //## end PLFNMultiColumn::RemoveColumnValues%948222408.body
}

inline bool PLFNMultiColumn::RemoveColumnValues (ZBFieldColumn* pColumn)
{
  //## begin PLFNMultiColumn::RemoveColumnValues%948222409.body preserve=yes
    return m_MultiColumnManager.RemoveColumnValues( pColumn );
  //## end PLFNMultiColumn::RemoveColumnValues%948222409.body
}

inline void PLFNMultiColumn::RemoveAllValues ()
{
  //## begin PLFNMultiColumn::RemoveAllValues%948222410.body preserve=yes
    m_MultiColumnManager.RemoveAllValues();
  //## end PLFNMultiColumn::RemoveAllValues%948222410.body
}

inline bool PLFNMultiColumn::RemoveColumnValuesAt (size_t Index)
{
  //## begin PLFNMultiColumn::RemoveColumnValuesAt%948222411.body preserve=yes
    return m_MultiColumnManager.RemoveColumnValuesAt( Index );
  //## end PLFNMultiColumn::RemoveColumnValuesAt%948222411.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const BOOL PLFNMultiColumn::GetShowHeader () const
{
  //## begin PLFNMultiColumn::GetShowHeader%3881F0610378.get preserve=no
  return m_ShowHeader;
  //## end PLFNMultiColumn::GetShowHeader%3881F0610378.get
}

inline void PLFNMultiColumn::SetShowHeader (BOOL value)
{
  //## begin PLFNMultiColumn::SetShowHeader%3881F0610378.set preserve=no
  m_ShowHeader = value;
  //## end PLFNMultiColumn::SetShowHeader%3881F0610378.set
}

//## begin module%38818567009E.epilog preserve=yes
//## end module%38818567009E.epilog


#endif
