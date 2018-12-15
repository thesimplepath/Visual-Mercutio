//## begin module%33D8FD70006E.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%33D8FD70006E.cm

//## begin module%33D8FD70006E.cp preserve=no
//## end module%33D8FD70006E.cp

//## Module: ZAStylMg%33D8FD70006E; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZAStylMg.h

#ifndef ZAStylMg_h
#define ZAStylMg_h 1

//## begin module%33D8FD70006E.additionalIncludes preserve=no
//## end module%33D8FD70006E.additionalIncludes

//## begin module%33D8FD70006E.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%33D8FD70006E.includes

// ZAStyle
#include "ZAStyle.h"
// ZAFont
#include "ZAFont.h"




//## begin module%33D8FD70006E.additionalDeclarations preserve=yes
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
//## end module%33D8FD70006E.additionalDeclarations


//## begin ZAStyleManager%33D8FD2D021C.preface preserve=yes
//## end ZAStyleManager%33D8FD2D021C.preface

//## Class: ZAStyleManager%33D8FD2D021C
//    Manage the styles created by the user.
//## Category: ZUtil library::Font & Style classes%36F91D94013C
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%33D8FD2D021F;ZAFont { -> }
//## Uses: <unnamed>%33D8FD4700BE;ZAStyle { -> }

class AFX_EXT_CLASS ZAStyleManager : public CObject  //## Inherits: <unnamed>%33D8FD2D021E
{
  //## begin ZAStyleManager%33D8FD2D021C.initialDeclarations preserve=yes
    public:
    // Inherited feature
        typedef CObject inherited;
  //## end ZAStyleManager%33D8FD2D021C.initialDeclarations

  public:
    //## Constructors (generated)
      ZAStyleManager();

      ZAStyleManager(const ZAStyleManager &right);

    //## Destructor (generated)
      virtual ~ZAStyleManager();

    //## Assignment Operation (generated)
      const ZAStyleManager & operator=(const ZAStyleManager &right);


    //## Other Operations (specified)
      //## Operation: AddStyle%869857714
      //    Add a new font into the FontArray.
      HandleStyle AddStyle (ZAStyle* pStyle);

      //## Operation: RemoveStyle%869857715
      //    Remove a specific font from the manager.
      BOOL RemoveStyle (HandleStyle hStyle);

      //## Operation: FindStyle%869857716
      //    Search a specific font with the name.
      //    .
      HandleStyle FindStyle (CString Name);

      //## Operation: GetStyle%869857717
      //    Get the pointer of a font by passing the handle of the
      //    font.
      ZAStyle* GetStyle (HandleStyle hStyle);

      //## Operation: Serialize%869857718
      //    Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: GetElements%870446013
      //    Return the number of elements of the StyletManager.
      size_t GetElements ();

      //## Operation: GetStyleAt%914161847
      //    Get the pointer of a style by passing the index.
      ZAStyle* GetStyleAt (int Index);

    // Additional Public Declarations
      //## begin ZAStyleManager%33D8FD2D021C.public preserve=yes
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
      //## end ZAStyleManager%33D8FD2D021C.public
  protected:
    // Additional Protected Declarations
      //## begin ZAStyleManager%33D8FD2D021C.protected preserve=yes
    DECLARE_SERIAL(ZAStyleManager)
      //## end ZAStyleManager%33D8FD2D021C.protected
  private:
    // Additional Private Declarations
      //## begin ZAStyleManager%33D8FD2D021C.private preserve=yes
      //## end ZAStyleManager%33D8FD2D021C.private

  private: //## implementation
    // Data Members for Has Relationships

      //## Documentation ZAStyleManager::StyleArray.has
      //    Contains the styles created.
      //## begin ZAStyleManager::StyleArray%33D8FD2D021D.has preserve=no  public: CObArray {1 -> 1VO}
      CObArray m_StyleArray;
      //## end ZAStyleManager::StyleArray%33D8FD2D021D.has

    // Additional Implementation Declarations
      //## begin ZAStyleManager%33D8FD2D021C.implementation preserve=yes
      //## end ZAStyleManager%33D8FD2D021C.implementation

};

//## begin ZAStyleManager%33D8FD2D021C.postscript preserve=yes
//## end ZAStyleManager%33D8FD2D021C.postscript

// Class ZAStyleManager 


//## Other Operations (inline)
inline HandleStyle ZAStyleManager::AddStyle (ZAStyle* pStyle)
{
  //## begin ZAStyleManager::AddStyle%869857714.body preserve=yes
      // Scans the array to know if empty place to store the new style
      for (register i = 0; i < m_StyleArray.GetSize(); ++i)
      {
          // Check if an empty place
          if (m_StyleArray[i] == NULL)
          {
              m_StyleArray.SetAt( i, pStyle );    
              pStyle->SethStyleNumber( i );
              return i;
          }
      }
      pStyle->SethStyleNumber( m_StyleArray.Add( pStyle ) );
      return pStyle->GethStyleNumber();
  //## end ZAStyleManager::AddStyle%869857714.body
}

inline ZAStyle* ZAStyleManager::GetStyle (HandleStyle hStyle)
{
  //## begin ZAStyleManager::GetStyle%869857717.body preserve=yes
    // Return the pointer
    return (hStyle == NoStyleDefined || hStyle >= m_StyleArray.GetSize()) ? NULL : ((ZAStyle*)(m_StyleArray[(int)hStyle]));
  //## end ZAStyleManager::GetStyle%869857717.body
}

inline size_t ZAStyleManager::GetElements ()
{
  //## begin ZAStyleManager::GetElements%870446013.body preserve=yes
      return m_StyleArray.GetSize();
  //## end ZAStyleManager::GetElements%870446013.body
}

inline ZAStyle* ZAStyleManager::GetStyleAt (int Index)
{
  //## begin ZAStyleManager::GetStyleAt%914161847.body preserve=yes
    // Return the pointer
    return (Index == NoStyleDefined || Index >= m_StyleArray.GetSize()) ? NULL : ((ZAStyle*)(m_StyleArray[(int)Index]));
  //## end ZAStyleManager::GetStyleAt%914161847.body
}

//## begin module%33D8FD70006E.epilog preserve=yes
//## end module%33D8FD70006E.epilog


#endif
