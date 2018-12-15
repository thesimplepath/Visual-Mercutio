//## begin module%351BE004014A.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%351BE004014A.cm

//## begin module%351BE004014A.cp preserve=no
//## end module%351BE004014A.cp

//## Module: ZIDialog%351BE004014A; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZIDialog.h

#ifndef ZIDialog_h
#define ZIDialog_h 1

//## begin module%351BE004014A.additionalIncludes preserve=no
//## end module%351BE004014A.additionalIncludes

//## begin module%351BE004014A.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%351BE004014A.includes

// Mfc
#include "Mfc.h"
//## begin module%351BE004014A.declarations preserve=no
//## end module%351BE004014A.declarations

//## begin module%351BE004014A.additionalDeclarations preserve=yes
//put the values back to make AFX_EXT_CLASS export again
#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif
//## end module%351BE004014A.additionalDeclarations

// JMR-MODIF - Le 17 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//## Class: ZIDialog%351BDE69006E
//    Implements a dialog automatically centered.
//## Category: ZUtil library::Tools classes%35D41E2C02C0
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZIDialog : public CDialog //## Inherits: <unnamed>%351BDEC1028A
{
//## begin ZIDialog%351BDE69006E.initialDeclarations preserve=yes
//## end ZIDialog%351BDE69006E.initialDeclarations

public:

    //## Constructors (specified)
    //## Operation: ZIDialog%891019436
    //    The default constructor has one default parameter. This
    //    parameter specifies if the dialog is automatically
    //    centered.
    ZIDialog ( UINT nIDTemplate = -1, BOOL AutoCenter = TRUE, CWnd* pParentWnd = NULL );

    //## Operation: ZIDialog%891019437
    //    The default constructor has one default parameter. This
    //    parameter specifies if the dialog is automatically
    //    centered.
    ZIDialog ( LPCSTR lpszTemplateName, BOOL AutoCenter = TRUE, CWnd* pParentWnd = NULL );

    ZIDialog ( UINT        nIDTemplate,
               BOOL        AutoCenter,
               COLORREF    BackCol,
               COLORREF    StaticCol,
               COLORREF    EditCol,
               CWnd*    pParentWnd = NULL );

    ZIDialog ( LPCSTR    lpszTemplateName,
               BOOL        AutoCenter,
               COLORREF    BackCol,
               COLORREF    StaticCol,
               COLORREF    EditCol,
               CWnd*    pParentWnd = NULL );

    //## Destructor (generated)
    virtual ~ZIDialog();

    //## Other Operations (specified)
    //## Operation: Create%919330579
    //    The create fonction for modeless dialogr. This parameter
    //    specifies if the dialog is automatically centered.
    void Create ( UINT nIDTemplate, BOOL AutoCenter = TRUE, CWnd* pParentWnd = NULL );

    //## Operation: Create%919330580
    //    The create fonction for modeless dialogr. This parameter
    //    specifies if the dialog is automatically centered.
    void Create ( LPCSTR lpszTemplateName, BOOL AutoCenter = TRUE, CWnd* pParentWnd = NULL );

    void Create ( UINT        nIDTemplate,
                  BOOL        AutoCenter,
                  COLORREF    BackCol,
                  COLORREF    StaticCol,
                  COLORREF    EditCol,
                  CWnd*        pParentWnd = NULL );

    void Create ( LPCSTR    lpszTemplateName,
                  BOOL        AutoCenter,
                  COLORREF    BackCol,
                  COLORREF    StaticCol,
                  COLORREF    EditCol,
                  CWnd*        pParentWnd = NULL );


    void SetBackGroundColor( COLORREF col );
    void SetEditControlColor( COLORREF col );
    void SetStaticControlColor( COLORREF col );

    // Additional Public Declarations
    //## begin ZIDialog%351BDE69006E.public preserve=yes
    //## end ZIDialog%351BDE69006E.public

protected:

    // Additional Protected Declarations
    //## begin ZIDialog%351BDE69006E.protected preserve=yes
    // Generated message map functions
    //{{AFX_MSG(ZIDialog)
    virtual BOOL OnInitDialog();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
    //## end ZIDialog%351BDE69006E.protected

private:

    //## Constructors (generated)
    ZIDialog( const ZIDialog &right );

    //## Assignment Operation (generated)
    const ZIDialog & operator=( const ZIDialog &right );

    //## Get and Set Operations for Class Attributes (generated)

    //## Attribute: bAutoCenter%351BE1E9017C
    //    Saves the AutoCenter parameter when the dialog is
    //    constructed.
    const BOOL GetbAutoCenter () const;
    void SetbAutoCenter ( BOOL value );

    // Additional Private Declarations
    //## begin ZIDialog%351BDE69006E.private preserve=yes
    // JMR-MODIF - Le 20 octobre 2005 - Ajout des fonctions SetDialogBkColor et SetActiveBgColorMode.
    void SetDialogBkColor( COLORREF clrCtlBk = RGB( 192, 192, 192 ), COLORREF clrCtlText = RGB( 0, 0, 0 ) );
    //## end ZIDialog%351BDE69006E.private

//## implementation
private:

    // Data Members for Class Attributes

    //## begin ZIDialog::bAutoCenter%351BE1E9017C.attr preserve=no  private: BOOL {U}
    BOOL        m_bAutoCenter;
    //## end ZIDialog::bAutoCenter%351BE1E9017C.attr

    // Additional Implementation Declarations
    //## begin ZIDialog%351BDE69006E.implementation preserve=yes
    bool        m_ColorHasBeenSuperseed;

    HBRUSH        m_HbrClrCtlBk;

    CBrush        m_Brush;

    COLORREF    m_BackCol;
    COLORREF    m_StaticCol;
    COLORREF    m_EditCol;

    // JMR-MODIF - Le 20 octobre 2005 - Ajout des variables m_ClrCtlText et m_ClrCtlBk.
    COLORREF    m_ClrCtlText;
    COLORREF    m_ClrCtlBk;
    //## end ZIDialog%351BDE69006E.implementation
};

//## begin ZIDialog%351BDE69006E.postscript preserve=yes
//## end ZIDialog%351BDE69006E.postscript

// Class ZIDialog 

//## Get and Set Operations for Class Attributes (inline)

inline const BOOL ZIDialog::GetbAutoCenter () const
{
    //## begin ZIDialog::GetbAutoCenter%351BE1E9017C.get preserve=no
    return m_bAutoCenter;
    //## end ZIDialog::GetbAutoCenter%351BE1E9017C.get
}

inline void ZIDialog::SetbAutoCenter ( BOOL value )
{
    //## begin ZIDialog::SetbAutoCenter%351BE1E9017C.set preserve=no
    m_bAutoCenter = value;
    //## end ZIDialog::SetbAutoCenter%351BE1E9017C.set
}

//## begin module%351BE004014A.epilog preserve=yes
//## end module%351BE004014A.epilog

#endif