//## begin module%33CA790C035C.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%33CA790C035C.cm

//## begin module%33CA790C035C.cp preserve=no
//## end module%33CA790C035C.cp

//## Module: ZAFontMg%33CA790C035C; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZAFontMg.h

#ifndef ZAFontMg_h
#define ZAFontMg_h 1

//## begin module%33CA790C035C.additionalIncludes preserve=no
//## end module%33CA790C035C.additionalIncludes

//## begin module%33CA790C035C.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%33CA790C035C.includes

// ZAFont
#include "PSS_Font.h"



//## begin module%33CA790C035C.additionalDeclarations preserve=yes
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

//## end module%33CA790C035C.additionalDeclarations


//## begin ZAFontManager%33CA5F860104.preface preserve=yes
//## end ZAFontManager%33CA5F860104.preface

//## Class: ZAFontManager%33CA5F860104
//    Manage the fonts created by the user.
//## Category: ZUtil library::Font & Style classes%36F91D94013C
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%33D78F0F015E;ZAFont { -> }

class AFX_EXT_CLASS ZAFontManager : public CObject  //## Inherits: <unnamed>%33D78EB00302
{
  //## begin ZAFontManager%33CA5F860104.initialDeclarations preserve=yes
    public:
    // Inherited feature
        typedef CObject inherited;
  //## end ZAFontManager%33CA5F860104.initialDeclarations

  public:
    //## Constructors (generated)
      ZAFontManager();

      ZAFontManager(const ZAFontManager &right);

    //## Destructor (generated)
      virtual ~ZAFontManager();

    //## Assignment Operation (generated)
      const ZAFontManager & operator=(const ZAFontManager &right);


    //## Other Operations (specified)
      //## Operation: AddFont%868907715
      //    Add a new font into the FontArray.
      PSS_Font::FontHandle AddFont (PSS_Font* pFont);

      //## Operation: RemoveFont%868907716
      //    Remove a specific font from the manager.
      BOOL RemoveFont (PSS_Font::FontHandle hFont);

      //## Operation: FindFont%868907717
      //    Search a specific font with the LogFont and the color
      //    .
      PSS_Font::FontHandle FindFont (LOGFONT* pLogFont, COLORREF Col);

      //## Operation: FindFont%869402481
      //    Search a specific font with a ZAFont pointer.
      //    .
      PSS_Font::FontHandle FindFont (PSS_Font* pFont);

      //## Operation: GetFont%869402482
      //    Get the pointer of a font by passing the handle of the
      //    font.
      PSS_Font* GetFont (PSS_Font::FontHandle hFont);

      //## Operation: Serialize%869764511
      //    Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: GetElements%870446012
      //    Return the number of elements of the FontManager.
      size_t GetElements ();

      //## Operation: RotateFont%880893867
      //    Takes an initial font and rotate it by the specified
      //    angle.
      PSS_Font::FontHandle RotateFont (PSS_Font::FontHandle hFont, int iAngle);

    // Additional Public Declarations
      //## begin ZAFontManager%33CA5F860104.public preserve=yes
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
      //## end ZAFontManager%33CA5F860104.public
  protected:
    // Additional Protected Declarations
      //## begin ZAFontManager%33CA5F860104.protected preserve=yes
    DECLARE_SERIAL(ZAFontManager)
      //## end ZAFontManager%33CA5F860104.protected
  private:
    // Additional Private Declarations
      //## begin ZAFontManager%33CA5F860104.private preserve=yes
      //## end ZAFontManager%33CA5F860104.private

  private: //## implementation
    // Data Members for Has Relationships

      //## Documentation ZAFontManager::FontArray.has
      //    Contains the fonts created.
      //## begin ZAFontManager::FontArray%33CA78D000DC.has preserve=no  public: CObArray {1 -> 1VO}
      CObArray m_FontArray;
      //## end ZAFontManager::FontArray%33CA78D000DC.has

    // Additional Implementation Declarations
      //## begin ZAFontManager%33CA5F860104.implementation preserve=yes
      //## end ZAFontManager%33CA5F860104.implementation

};

//## begin ZAFontManager%33CA5F860104.postscript preserve=yes
//## end ZAFontManager%33CA5F860104.postscript

// Class ZAFontManager 


//## Other Operations (inline)
inline PSS_Font::FontHandle ZAFontManager::AddFont (PSS_Font* pFont)
{
  //## begin ZAFontManager::AddFont%868907715.body preserve=yes
      pFont->SetFontHandle( m_FontArray.Add( pFont ) );
      return pFont->GetFontHandle();
  //## end ZAFontManager::AddFont%868907715.body
}

inline PSS_Font* ZAFontManager::GetFont (PSS_Font::FontHandle hFont)
{
  //## begin ZAFontManager::GetFont%869402482.body preserve=yes
    // Return the pointer
    return (hFont == g_NoFontDefined || hFont >= m_FontArray.GetSize()) ? NULL : ((PSS_Font*)(m_FontArray[(int)hFont]));
  //## end ZAFontManager::GetFont%869402482.body
}

inline size_t ZAFontManager::GetElements ()
{
  //## begin ZAFontManager::GetElements%870446012.body preserve=yes
      return m_FontArray.GetSize();
  //## end ZAFontManager::GetElements%870446012.body
}

//## begin module%33CA790C035C.epilog preserve=yes
//## end module%33CA790C035C.epilog


#endif
