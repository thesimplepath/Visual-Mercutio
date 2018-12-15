//## begin module%38819B0C002E.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%38819B0C002E.cm

//## begin module%38819B0C002E.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%38819B0C002E.cp

//## Module: ZBFldColMg%38819B0C002E; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZBFldClM.h

#ifndef ZBFldClM_h
#define ZBFldClM_h 1

//## begin module%38819B0C002E.additionalIncludes preserve=no
//## end module%38819B0C002E.additionalIncludes

//## begin module%38819B0C002E.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%38819B0C002E.includes

// ZBFldCol
#include "ZBFldCol.h"
// Mfc
#include "Mfc.h"
//## begin module%38819B0C002E.declarations preserve=no
//## end module%38819B0C002E.declarations

//## begin module%38819B0C002E.additionalDeclarations preserve=yes
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
//## end module%38819B0C002E.additionalDeclarations


//## Class: ZBFieldColumnManager%38819AA402EB
//## Category: ZBaseLib::Base objects%37E9429A0111
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%38819ABA01E8;ZBFieldColumn { -> }

class AFX_EXT_CLASS ZBFieldColumnManager : public CObject  //## Inherits: <unnamed>%38819B4E0231
{
  //## begin ZBFieldColumnManager%38819AA402EB.initialDeclarations preserve=yes
    public:
    // Inherited feature
        typedef CObject inherited;
  //## end ZBFieldColumnManager%38819AA402EB.initialDeclarations

  public:
    //## Constructors (generated)
      ZBFieldColumnManager();

      ZBFieldColumnManager(const ZBFieldColumnManager &right);

    //## Destructor (generated)
      virtual ~ZBFieldColumnManager();

    //## Assignment Operation (generated)
      const ZBFieldColumnManager & operator=(const ZBFieldColumnManager &right);


    //## Other Operations (specified)
      //## Operation: Serialize%948017486
      //    Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: Clone%948017488
      //    Make a clone of the object.
      virtual ZBFieldColumnManager* Clone ();

      //## Operation: GetCount%948017489
      //    Return the number of columns
      size_t GetCount () const;

      //## Operation: AddColumn%948017490
      //    Add a new column into the column array.
      void AddColumn (ZBFieldColumn* pColumn);

      //## Operation: AddColumn%948017508
      //    Add a new column into the column array.
      void AddColumn (const CString HeaderName, const CStringArray& Values);

      //## Operation: RemoveColumn%948017491
      //    Remove a specific column from the manager.
      bool RemoveColumn (const CString& HeaderName);

      //## Operation: RemoveColumn%948017492
      //    Remove a specific column from the manager.
      bool RemoveColumn (ZBFieldColumn* pColumn);

      //## Operation: RemoveAll%948017493
      //    remove all columns.
      void RemoveAll ();

      //## Operation: FindColumn%948017494
      //    Find a column by its header name.
      ZBFieldColumn* FindColumn (const CString& HeaderName);

      //## Operation: FindColumn%948017495
      //    Find a column by its column pointer.
      bool FindColumn (ZBFieldColumn* pColumn);

      //## Operation: GetColumnAt%948017496
      //    Get a column at a specific position.
      ZBFieldColumn* GetColumnAt (size_t Index) const;

      //## Operation: InsertColumnAt%948017497
      //    Insert a new column at a specific position.
      void InsertColumnAt (ZBFieldColumn* pColumn, size_t Index);

      //## Operation: RemoveColumnAt%948017498
      //    Remove a column at a specific position.
      bool RemoveColumnAt (size_t Index);

      //## Operation: GetRowValues%948017509
      //    Get row, fill a string value array.
      bool GetRowValues (CStringArray& RowValues, size_t RowIndex);

      //## Operation: GetColumnRowValue%948017510
      //    Get the value of a specific column and row. Return by
      //    reference the value. If not found, return false.
      bool GetColumnRowValue (const CString ColumnName, size_t RowIndex, CString& Value);

      //## Operation: GetColumnRowValue%948017511
      //    Get the value of a specific column and row. Return by
      //    reference the value. If not found, return false.
      bool GetColumnRowValue (size_t ColumnIndex, size_t RowIndex, CString& Value);

      //## Operation: SetColumnRowValue%948222412
      //    Set the value of a specific column and row. Return by
      //    reference the value. If not found, return false.
      bool SetColumnRowValue (const CString ColumnName, size_t RowIndex, CString Value);

      //## Operation: SetColumnRowValue%948222413
      //    Set the value of a specific column and row. Return by
      //    reference the value. If not found, return false.
      bool SetColumnRowValue (size_t ColumnIndex, size_t RowIndex, CString Value);

      //## Operation: AutoSizeColumn%948017530
      //    Auto size a specific column from the manager.
      bool AutoSizeColumn (const CString& HeaderName);

      //## Operation: AutoSizeColumn%948017531
      //    Auto size a specific column from the manager.
      bool AutoSizeColumn (ZBFieldColumn* pColumn);

      //## Operation: AutoSizeColumnAt%948017532
      //    Auto size a specific column from the manager.
      bool AutoSizeColumnAt (size_t Index);

      //## Operation: AutoSizeAllColumns%948017533
      //    Auto size all columns from the manager.
      bool AutoSizeAllColumns ();

      //## Operation: SizeColumn%948017534
      //    Size a specific column from the manager.
      bool SizeColumn (const CString& HeaderName, size_t Width);

      //## Operation: SizeColumn%948017535
      //    Size a specific column from the manager.
      bool SizeColumn (ZBFieldColumn* pColumn, size_t Width);

      //## Operation: SizeColumnAt%948017536
      //    Size a specific column from the manager.
      bool SizeColumnAt (size_t Index, size_t Width);

      //## Operation: SizeAllColumns%948017537
      //    Size all columns from the manager.
      bool SizeAllColumns (size_t Width);

      //## Operation: GetHeaderNames%948017546
      //    Get the header names and fill a string value array.
      bool GetHeaderNames (CStringArray& HeaderNames);

      //## Operation: CreateColumnWithHeaderNames%948222394
      //    Create new columns with the header names filled in a
      //    string value array.
      bool CreateColumnWithHeaderNames (CStringArray& HeaderNames);

      //## Operation: AddRowValues%948222395
      //    Add a complete row values with a string value array.
      bool AddRowValues (CStringArray& RowValues);

      //## Operation: InsertRowValuesAt%948222396
      //    Insert a complete row values at a specific index with a
      //    string value array. If the row already exists, replace
      //    values.
      bool InsertRowValuesAt (CStringArray& RowValues, size_t RowIndex);

      //## Operation: SetRowValuesAt%948222402
      //    Set a complete row values at a specific index with a
      //    string value array. If the row already exists, replace
      //    values.
      bool SetRowValuesAt (CStringArray& RowValues, size_t RowIndex);

      //## Operation: RemoveColumnValues%948222403
      //    Remove all values of a specific column from the manager.
      bool RemoveColumnValues (const CString& HeaderName);

      //## Operation: RemoveColumnValues%948222404
      //    Remove all values of a specific column from the manager.
      bool RemoveColumnValues (ZBFieldColumn* pColumn);

      //## Operation: RemoveAllValues%948222405
      //    remove all values of all columns.
      void RemoveAllValues ();

      //## Operation: RemoveColumnValuesAt%948222406
      //    Remove all values of a column at a specific position.
      bool RemoveColumnValuesAt (size_t Index);

    // Additional Public Declarations
      //## begin ZBFieldColumnManager%38819AA402EB.public preserve=yes
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
      //## end ZBFieldColumnManager%38819AA402EB.public
  protected:
    // Additional Protected Declarations
      //## begin ZBFieldColumnManager%38819AA402EB.protected preserve=yes
    DECLARE_SERIAL(ZBFieldColumnManager)
      //## end ZBFieldColumnManager%38819AA402EB.protected
  private:
    // Data Members for Class Attributes

      //## Attribute: ColumnArray%3881A202027F
      //    This array contains the column object pointers.
      //## begin ZBFieldColumnManager::ColumnArray%3881A202027F.attr preserve=no  private: CObArray {U} 
      CObArray m_ColumnArray;
      //## end ZBFieldColumnManager::ColumnArray%3881A202027F.attr

    // Additional Private Declarations
      //## begin ZBFieldColumnManager%38819AA402EB.private preserve=yes
      //## end ZBFieldColumnManager%38819AA402EB.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZBFieldColumnManager%38819AA402EB.implementation preserve=yes
      //## end ZBFieldColumnManager%38819AA402EB.implementation

};

//## begin ZBFieldColumnManager%38819AA402EB.postscript preserve=yes
//## end ZBFieldColumnManager%38819AA402EB.postscript

// Class ZBFieldColumnManager 


//## Other Operations (inline)
inline size_t ZBFieldColumnManager::GetCount () const
{
  //## begin ZBFieldColumnManager::GetCount%948017489.body preserve=yes
    return m_ColumnArray.GetSize();
  //## end ZBFieldColumnManager::GetCount%948017489.body
}

//## begin module%38819B0C002E.epilog preserve=yes
//## end module%38819B0C002E.epilog


#endif
