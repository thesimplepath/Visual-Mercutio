//## begin module%334FC46302E9.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC46302E9.cm

//## begin module%334FC46302E9.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%334FC46302E9.cp

//## Module: ZAObject%334FC46302E9; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZAObject.h

#ifndef ZAObject_h
#define ZAObject_h 1

//## begin module%334FC46302E9.additionalIncludes preserve=no
//## end module%334FC46302E9.additionalIncludes

//## begin module%334FC46302E9.includes preserve=yes
// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include <FLOAT.H>
#include <MATH.H>

class ZIView;
class ZDDocument;
class ZBFieldColumn;
//## end module%334FC46302E9.includes

// ZAMath
#include "ZAMath.h"

// ZBNotes
#include "ZBNotes.h"

// ZBRect
#include "ZBRect.h"

// ZAStyle
#include "ZAStyle.h"

// ZAFont
#include "ZAFont.h"

//## begin module%334FC46302E9.declarations preserve=no
//## end module%334FC46302E9.declarations

#include "ZABorder.h"

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 20 août 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//## begin module%334FC46302E9.additionalDeclarations preserve=yes
// Defines the constants for object property pages
const    UINT    PropertyGeneralPage =             0x00000001;
const    UINT    PropertySizePage =                 0x00000002;
const    UINT    PropertyCheckBoxPage =            0x00000004;
const    UINT    PropertyRadioPage =                0x00000008;
const    UINT    PropertyNumberedPage =            0x00000010;
const    UINT    PropertyGeneralTextPage=        0x00000020;
const    UINT    PropertySquarePage =            0x00000040;
const    UINT    PropertyBoundTextPage =            0x00000080;
const    UINT    PropertyLongPage =                0x00000100;
const    UINT    PropertyGraphicPage =            0x00000200;
const    UINT    PropertyRectPage =                0x00000400;
const    UINT    PropertyGeneralBasicPage =        0x00000800;
const    UINT    PropertyGeneralDatePage =        0x00001000;
const    UINT    PropertyGeneralBoundTextPage =    0x00002000;
const    UINT    PropertyGeneralStaticPage =        0x00004000;
const    UINT    PropertyMaskTextPage =            0x00008000;
const    UINT    PropertyMultiColumnPage =        0x00010000;

// Defines tabs positions
const    size_t    PropertyTabGeneral = 0;
const    size_t    PropertyTabSize = 1;
const    size_t    PropertyTabCheckBox = 2;
const    size_t    PropertyTabRadio = 2;
const    size_t    PropertyTabNumbered = 2;
const    size_t    PropertyTabSquare = 2;
const    size_t    PropertyTabBoundText = 2;
const    size_t    PropertyTabLong = 2;
const    size_t    PropertyTabGraphic = 2;
const    size_t    PropertyTabRect = 3;
const    size_t    PropertyMaskText = 2;
const    size_t    PropertyMultiColumn = 3;
//## end module%334FC46302E9.additionalDeclarations

//## Class: PlanFinObject%334FC4610180; Abstract
//    Visual objects functionnalities.
//## Category: ZBaseLib::Base objects%37E9429A0111
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%33D79D2701D6;ZAFont { -> }
//## Uses: <unnamed>%33DBA5BF026C;ZAStyle { -> }
//## Uses: <unnamed>%371399600163;ZBRect { -> }
//## Uses: <unnamed>%37E4D0E300B2;ZBNotes { -> }

class AFX_EXT_CLASS PlanFinObject : public ObjectParser  //## Inherits: <unnamed>%334FC4610181
{
//## begin PlanFinObject%334FC4610180.initialDeclarations preserve=yes
protected:

    DECLARE_SERIAL( PlanFinObject )

public:

    // Inherited feature
    typedef ObjectParser inherited;

    //## Constructors (generated)
    PlanFinObject();

    PlanFinObject( const PlanFinObject &right );

    //## Destructor (generated)
    virtual ~PlanFinObject();

    //## Assignment Operation (generated)
    const PlanFinObject & operator=( const PlanFinObject &right );

    //## Other Operations (specified)
    //## Operation: operator =%829516133
    // A copy constructor with a pointer.
    const PlanFinObject& operator = ( const PlanFinObject* right );

public:

    // Return the value of the object. By default return 0.
    virtual double GetRealValue() const
    {
        return 0;
    };

    // Defines if the field is static or not. Implemented in PLFNText class
    virtual const BOOL GetIsStatic() const
    {
        return TRUE;
    };

    virtual void SetIsStatic( BOOL value )
    {
    };
    //## end PlanFinObject%334FC4610180.initialDeclarations

    //## Operation: IsEmpty%829516134
    // Is it an empty field.
    BOOL IsEmpty() const;

    //## Operation: EmptyObject%846024742
    // This function empties the object.
    void EmptyObject();

    //## Operation: ClearEmptyObjectFlag%922093645
    // This function clear the empty object flag.
    void ClearEmptyObjectFlag();

    //## Operation: SelectObject%829516138
    // Pass the object to selected state.
    void SelectObject( CWnd* wnd, CDC* pDC, BOOL bState, BOOL bErase = TRUE );

    //## Operation: IsSelectObject%829516139
    // Is this object selected
    BOOL IsSelectObject() const;

    //## Operation: GetClientRect%829516143
    //    Return the bounds of the object.
    CRect& GetClientRect();

    //## Operation: GetObjectPage%829516144
    // Return the object page
    int GetObjectPage() const;

    //## Operation: GetFormatType%829516145
    // Return the format type.
    FormatType GetFormatType() const;

    //## Operation: CopyObject%863615075
    virtual void CopyObject( PlanFinObject* pSrc );

    //## Operation: SetFormatType%829516146
    // Assign a format type.
    void SetFormatType( FormatType Fmt );

    //## Operation: FormatObject%829516140
    // Format the object with a string.
    void FormatObject( const char* szBuf );

    //## Operation: FormatObject%829516141
    // Format the object with a time.
    void FormatObject( CTime* time );

    //## Operation: FormatObject%829516142
    // Format the object with a DOUBLE.
    void FormatObject( DOUBLE dValue );

    //## Operation: Recalculate%829516154
    // Recalculate the object.
    virtual void Recalculate( ZDDocument* pDoc );

    //## Operation: SetValue%829516155
    // Set a value. By default set nothing.
    virtual void SetValue( double dValue );

    //## Operation: GetValue%829516156
    // Return the value of the object. By default return 0.
    virtual double GetValue() const;

    //## Operation: GetFormatedObject%829516158
    // Format the object with the current object's attributes.
    //## Semantics:
    // This function return the string
    // represented the object formated
    // with the current format type
    // this function is virtual
    // The base function returns an empty string
    virtual CString GetFormatedObject();

    //## Operation: GetUnformatedObject%901298461
    // Return an unformated string of the object image.
    virtual CString GetUnformatedObject();

    //## Operation: ConvertFormatedObject%829516157
    // Convert a formatted object to numeric, date, string, etc.
    // Returns true if the value has changed.
    //## Semantics:
    // This function convert the string
    // and set the object with the right value
    // For the base class nothing to d
    virtual BOOL ConvertFormatedObject( const CString&    sValue,
                                        BOOL            bLocateFormat = TRUE,
                                        BOOL            EmptyWhenZero = FALSE );

    //## Operation: GetObjectAdress%829516159
    // Return the memory adress of the object.
    virtual void* GetObjectAdress() const;

    //## Operation: GetFormatChoice%829516161
    // Return the format array of choices.
    virtual CStringArray& GetFormatChoice();

    //## Operation: SetFormatWithChoice%829516162
    // Assign a choice to the object by passing a string that
    // represent the object with a certain choice.
    virtual void SetFormatWithChoice( const CString& sValue );

    // Change the object origin
    void SetOrigin( CPoint& pt );

    //## Operation: GetRectTop%829516165
    // Set a square on the rect top for resizing object
    // functionnality.
    void GetRectTop( CRect* pRect ) const;

    //## Operation: GetRectBottom%829516166
    // Set a square on the rect top for resizing object
    // functionnality.
    void GetRectBottom( CRect* pRect ) const;

    //## Operation: GetRectLeft%829516167
    // Set a square on the rect top for resizing object
    // functionnality.
    void GetRectLeft( CRect* pRect ) const;

    //## Operation: GetRectRight%829516168
    // Set a square on the rect top for resizing object
    // functionnality.
    void GetRectRight( CRect* pRect ) const;

    //## Operation: IsRectTop%829516169
    // Test if the point is on the square for resizing the
    // object.
    BOOL IsRectTop( const CPoint& Point ) const;

    //## Operation: IsRectBottom%829516170
    // Test if the point is on the square for resizing the
    // object.
    BOOL IsRectBottom( const CPoint& Point ) const;

    //## Operation: IsRectLeft%829516171
    // Test if the point is on the square for resizing the
    // object.
    BOOL IsRectLeft( const CPoint& Point ) const;

    //## Operation: IsRectRight%829516172
    // Test if the point is on the square for resizing the
    // object.
    BOOL IsRectRight( const CPoint& Point ) const;

    //## Operation: DrawObject%829516173
    // Draw the object with the current DC.
    virtual void DrawObject( CDC* pDC, ZIView* pView );

    //## Operation: DrawEmpty%829516174
    // Draw an empty object with the current DC.
    virtual void DrawEmpty( CDC* pDC, ZIView* pView );

    //## Operation: DrawHiddenSymbol%944215345
    // Draw the hidden symbol for the object.
    void DrawHiddenSymbol( CDC* pDC );

    //## Operation: DrawHiddenOnPrintSymbol%944215346
    // Draw the hidden on print symbol for the object.
    void DrawHiddenOnPrintSymbol( CDC* pDC );

    //## Operation: DrawCalculatedSymbol%944215347
    // Draw the calculated symbol for the object.
    virtual void DrawCalculatedSymbol( CDC* pDC );

    //## Operation: DrawNoteSymbol%944215348
    // Draw the note symbol for the object.
    void DrawNoteSymbol( CDC* pDC );

    //## Operation: DrawObjectRectangle%944215349
    // Draw the object rectangle.
    void DrawObjectRectangle( CDC* pDC );

    //## Operation: DrawTabOrder%947360848
    // Draw the tab order number
    void DrawTabOrder( CDC* pDC );

    //## Operation: IsSelected%829516175
    // Is this object selected.
    virtual BOOL IsSelected( const CPoint& point ) const;

    //## Operation: IsHint%829516177
    // If the point value is contained in the object and can be
    // edited.
    virtual BOOL IsHint( CPoint& point ) const;

    //## Operation: GetFormatedBuffer%829516180
    // Return the formated buffer where operations for
    // displayed have been made.
    const char* GetFormatedBuffer() const;

    //## Operation: DisplayCodeName%829516178
    // Display the code name of the field.
    void DisplayCodeName( CDC* pDC, ZIView* pView, BOOL bDisplay = TRUE, CWnd* pWnd = NULL );

    //## Operation: Serialize%829516183
    // Serialization function required for MFC mecanism.
    virtual void Serialize( CArchive& ar );

    //## Operation: InvalidateObjectRect%831175686
    // Invalidate the object area. When the next draw is
    // initiated, the object's rectangle will be redrawn.
    void InvalidateObjectRect( CDC* pDC, CWnd* pWnd, CRect* pRect = NULL );

    //## Operation: GetJustify%833261592
    virtual UINT GetJustify( ZDDocument* pDoc ) const;

    //## Operation: SetJustify%833261593
    virtual void SetJustify( UINT nValue );

    //## Operation: SetClientRect%833930834
    void SetClientRect( const CRect& rect );

    //## Operation: SetObjectPage%833930835
    void SetObjectPage( int iPage );

    //## Operation: DisplayColorForNumber%840085276
    // Display the object with a specific color and shade.
    void DisplayColorForNumber( CDC* pDC, ZIView* pView );

    //## Operation: DrawBoundRect%846024741
    // Draw the bounded rect of the object.
    void DrawBoundRect( CDC* pDC );

    //## Operation: Clone%849755977
    // Make a clone of the object.
    virtual PlanFinObject* Clone();

    //## Operation: DrawFillObject%850768723
    // Fill the background of the object.
    void DrawFillObject( CDC* pDC, ZIView* pView );

    //## Operation: SelectObject%853480522
    void SelectObject( BOOL bState = TRUE );

    //## Operation: DisplayObjectName%862512873
    // Display the object name. This function is used to by
    // ZIViewCode.
    void DisplayObjectName( CDC* pDC );

    //## Operation: SizePositionHasChanged%863883948
    // Notify when the object size and/or position has changed.
    virtual void SizePositionHasChanged();

    //## Operation: GetRightSubMenu%864330568
    // Return the number of the submenu when the user click the
    // right mouse button.
    virtual UINT GetRightSubMenu() const;

    //## Operation: GetFont%870032842
    // Return the right font for the object. Depends on the
    // Style or the defined Font.
    ZAFont* GetFont( ZIView* pView );

    //## Operation: GetColor%873634803
    // Return the color that should be used to draw the object.
    // Can be the object color, the font color or the style
    // color.
    COLORREF GetColor( ZIView* pView );

    //## Operation: SethStyle%873638112
    // Assign a new style handle
    //## Postconditions:
    // After having assigned the handle, remove the font
    // handle, the object color and the object alignement.
    virtual void SethStyle( HandleStyle value );

    //## Operation: SetiAngle%880663111
    // Set the angle. After having set the angle, if it has
    // changed, call the OnAngleChanged function to alert the
    // object that his angle has changed.
    void SetiAngle( int iAngle, ZDDocument* pDoc );

    //## Operation: GetTextExtent%881694196
    // Calculate the Text Extent function of the angle.
    CSize GetTextExtent( CDC* pDC, const CString& Str, int Angle = 0 );

    //## Operation: GetTextExtentOrg%881701325
    // Calculate the Text Extent and the Text Origini, it is
    // function of the angle.
    void GetTextExtentOrg( CDC* pDC, const CString& Str, CSize& Size, CPoint& Org, int Angle = 0 );

    //## Operation: GetPropertyTabs%885128487
    // Return the list of tabs that should be displayed when
    // the user asks for object properties.
    virtual UINT GetPropertyTabs() const;

    //## Operation: GetFillColor%892746528
    // Return the fill color. Depends on the style and the
    // object's fill color.
    COLORREF GetFillColor( ZIView* pView ) const;

    //## Operation: MoveObject%901975364
    // This function move the object. The argument MovePt
    // passed as paramater defined the move in point. The
    // second parameter defines if the move must be done in
    // relative or absolute position.
    virtual void MoveObject( CPoint& MovePt, BOOL RelativeMove = TRUE );

    //## Operation: NotifyObjectHasChanged%903688630
    // Notify the mainframe, that object has changed.
    void NotifyObjectHasChanged();

    //## Operation: GetBorder%908815225
    // Returns the pointer to the border.
    const ZABorder* GetBorder( ZIView* pView ) const;

    //## Operation: HasBeenChanged%917889604
    BOOL HasBeenChanged() const;

    //## Operation: IsReadOnly%936435176
    // return TRUE if the document is read-only.
    BOOL IsReadOnly() const;

    //## Operation: SetAsReadOnly%936435177
    // Set the file as read-only.
    void SetAsReadOnly( BOOL value = TRUE );

    //## Operation: IsReadOnlyAtRuntime%936435178
    // return TRUE if the document data is read-only at runtime.
    BOOL IsReadOnlyAtRuntime();

    //## Operation: SetReadOnlyAtRuntime%936435179
    // Set the read-only flag at runtime.
    void SetReadOnlyAtRuntime( BOOL value = TRUE );

    //## Operation: ClearNotes%937733878
    // Clear the field notes.
    void ClearNotes();

    //## Operation: AddNotes%937741726
    // Add a new notes. If already one, this function replace
    // it.
    BOOL AddNotes( const CString Comment, const CString Username = _T( "" ) );

    //## Operation: DeleteNotes%937741727
    // Delete the note object.
    void DeleteNotes();

    //## Operation: GetNotesPointer%937741728
    // Return the notes pointer.
    ZBNotes* GetNotesPointer() const;

    //## Operation: IsMemberOfMultiColumn%948318239
    // Define if the field is a member of a multi-column field.
    BOOL IsMemberOfMultiColumn() const;

    //## Get and Set Operations for Class Attributes (generated)

    //## Attribute: bIsVisible%334FC46102A0
    // To know if the object is visible.
    const BOOL GetbIsVisible() const;
    void SetbIsVisible( BOOL value );

    //## Attribute: bMustBePrinted%334FC46102A1
    // To know if the object must be printed.
    const BOOL GetbMustBePrinted() const;
    void SetbMustBePrinted( BOOL value );

    //## Attribute: pRectTracker%334FC461029F
    CRectTracker* GetpRectTracker();
    void SetpRectTracker( CRectTracker* value );

    //## Attribute: Color%334FC46102A2
    // Represents the color for the object.
    const COLORREF GetColor() const;
    void SetColor( COLORREF value );

    //## Attribute: FillColor%334FC46102A3
    // Represents the fill color for the object.
    virtual const COLORREF GetFillColor() const;
    virtual void SetFillColor( COLORREF value );

    //## Attribute: uGroupNumber%3378863002E4
    const unsigned long GetuGroupNumber() const;
    void SetuGroupNumber( unsigned long value );

    //## Attribute: hFont%33D79AA702B2
    // The handle of the font used to display the font.
    virtual const HandleFont GethFont() const;
    virtual void SethFont( HandleFont value );

    //## Attribute: hStyle%33D9DF7F032A
    virtual const HandleStyle GethStyle() const;

    //## Attribute: iAngle%347C59770320
    // Specifies the angle, in tenths of degrees, between the
    // base line of an object and the x-axis. The angle is
    // measured in a counterclockwise direction from the x-axis
    // for left-handed coordinate systems and in a clockwise
    // direction from the x-axis for right-handed coordinate
    // systems (in which the y direction is up)
    const int GetiAngle() const;

    //## Attribute: EmptyStyle%35139C250384
    // Defines the empty style when the control is empty.
    const LineType GetEmptyStyle() const;
    void SetEmptyStyle( LineType value );

    //## Attribute: TabOrder%35192AEA03A2
    // Define the tab order.
    const double GetTabOrder() const;
    void SetTabOrder( double value );

    //## Attribute: LineNumber%35B8BE2700A4
    // Defines the line number of the object.
    const DWORD GetLineNumber() const;
    void SetLineNumber( DWORD value );

    //## Attribute: pBorder%362B6ADB0248
    // It points to the border class, if one is defined.
    ZABorder* GetpBorder();
    void SetpBorder( ZABorder* value );

    //## Attribute: DefaultValue%36331C3D0323
    // If there is a default value.
    const BOOL GetDefaultValue() const;
    void SetDefaultValue( BOOL value );

    //## Attribute: HasBeenChanged%36B5E69900F1
    // This flag is used for object that has been. We use it
    // for calculated object or imported object.
    void SetHasBeenChanged( BOOL value );

    //## Attribute: pColumn%38862FF000CE
    // If the field is a member of a multi-column field, this
    // pointer is valid.
    const ZBFieldColumn* GetpColumn() const;
    void SetpColumn( ZBFieldColumn* value );

    CString GetUserHelp() const
    {
        return m_UserHelp;
    };

    void SetUserHelp( CString value )
    {
        m_UserHelp = value;
    };

    // Additional Public Declarations
    //## begin PlanFinObject%334FC4610180.public preserve=yes
    //    Format the object with a time.
    void FormatObject( COleDateTime* time );
    //## end PlanFinObject%334FC4610180.public

    // Serialization debug features
    #ifdef _DEBUG
        virtual void AssertValid() const;
        virtual void Dump( CDumpContext& dc ) const;
    #endif

protected:

    //## Other Operations (specified)
    //## Operation: OnAngleChanged%880663112
    // When the angle has changed, this function is called.
    virtual void OnAngleChanged( ZDDocument* pDoc );

    //## Operation: RotateFont%880893868
    // Rotate the font in use. Call the rotatefont function
    // coming from the FontManager. The angle used is the
    // member attribute m_iAngle.
    void RotateFont( ZDDocument* pDoc );

    // Additional Protected Declarations
    //## begin PlanFinObject%334FC4610180.protected preserve=yes
    void DrawRightCorner( CDC* pDC );
    //## end PlanFinObject%334FC4610180.protected

//## implementation
private:

    //## Other Operations (specified)
    //## Operation: AssignFont%829516181
    // Assign the font for this object.
    void AssignFont();

    //## Operation: DCDrawMoveObject%829516182
    // Draw the object with the pDC.
    void DCDrawMoveObject( CDC* pDC );

// Protected data Members for Class Attributes
protected:

    //## Attribute: rctObject%334FC4610294
    // The object bounds.
    //## begin PlanFinObject::rctObject%334FC4610294.attr preserve=no  public: ZBRect {V} 
    ZBRect m_rctObject;
    //## end PlanFinObject::rctObject%334FC4610294.attr

    //## Attribute: FormatType%334FC461029B
    // Define the display format.
    //## begin PlanFinObject::FormatType%334FC461029B.attr preserve=no  public: FormatType {V} 
    FormatType m_FormatType;
    //## end PlanFinObject::FormatType%334FC461029B.attr

    //## Attribute: FormatChoice%334FC461029D
    // An array of format.
    //## begin PlanFinObject::FormatChoice%334FC461029D.attr preserve=no  public: static CStringArray {V} 
    static CStringArray m_FormatChoice;
    //## end PlanFinObject::FormatChoice%334FC461029D.attr

    //## Attribute: szFormatBuffer%334FC461029E
    // A buffer used during formatting of objects.
    //## begin PlanFinObject::szFormatBuffer%334FC461029E.attr preserve=no  implementation: static char[300] {V} ""
    static char m_szFormatBuffer[300];
    //## end PlanFinObject::szFormatBuffer%334FC461029E.attr

    //## Attribute: IsEmpty%36F393C80058
    //## begin PlanFinObject::IsEmpty%36F393C80058.attr preserve=no  public: BOOL {U} TRUE
    BOOL m_IsEmpty;
    //## end PlanFinObject::IsEmpty%36F393C80058.attr

    //## Attribute: pNotes%37E4AE6D00DF
    // Contains the field notes.
    //## begin PlanFinObject::pNotes%37E4AE6D00DF.attr preserve=no  public: ZBNotes* {U} 
    ZBNotes* m_pNotes;
    //## end PlanFinObject::pNotes%37E4AE6D00DF.attr

// Private data Members for Class Attributes
private:

    //## Attribute: iPage%334FC4610296
    // The object page.
    //## begin PlanFinObject::iPage%334FC4610296.attr preserve=no  public: int {V} 
    int m_iPage;
    //## end PlanFinObject::iPage%334FC4610296.attr

    //## Attribute: bSelected%334FC4610298
    // A flag for selection.
    //## begin PlanFinObject::bSelected%334FC4610298.attr preserve=no  public: BOOL {V} FALSE
    BOOL m_bSelected;
    //## end PlanFinObject::bSelected%334FC4610298.attr

    //## begin PlanFinObject::bIsVisible%334FC46102A0.attr preserve=no  public: BOOL {V} TRUE
    BOOL m_bIsVisible;
    //## end PlanFinObject::bIsVisible%334FC46102A0.attr

    //## begin PlanFinObject::bMustBePrinted%334FC46102A1.attr preserve=no  public: BOOL {V} TRUE
    BOOL m_bMustBePrinted;
    //## end PlanFinObject::bMustBePrinted%334FC46102A1.attr

    //## begin PlanFinObject::pRectTracker%334FC461029F.attr preserve=no  public: CRectTracker* {V} NULL
    CRectTracker* m_pRectTracker;
    //## end PlanFinObject::pRectTracker%334FC461029F.attr

    //## begin PlanFinObject::Color%334FC46102A2.attr preserve=no  public: COLORREF {V} 
    COLORREF m_Color;
    //## end PlanFinObject::Color%334FC46102A2.attr

    //## begin PlanFinObject::FillColor%334FC46102A3.attr preserve=no  public: COLORREF {V} 
    COLORREF m_FillColor;
    //## end PlanFinObject::FillColor%334FC46102A3.attr

    //## begin PlanFinObject::uGroupNumber%3378863002E4.attr preserve=no  public: unsigned long {U} 0
    unsigned long m_uGroupNumber;
    //## end PlanFinObject::uGroupNumber%3378863002E4.attr

    //## begin PlanFinObject::hFont%33D79AA702B2.attr preserve=no  public: HandleFont {U} -1
    HandleFont m_hFont;
    //## end PlanFinObject::hFont%33D79AA702B2.attr

    //## begin PlanFinObject::hStyle%33D9DF7F032A.attr preserve=no  public: HandleStyle {U} 
    HandleStyle m_hStyle;
    //## end PlanFinObject::hStyle%33D9DF7F032A.attr

    //## begin PlanFinObject::iAngle%347C59770320.attr preserve=no  public: int {V} 0
    int m_iAngle;
    //## end PlanFinObject::iAngle%347C59770320.attr

    //## begin PlanFinObject::EmptyStyle%35139C250384.attr preserve=no  public: LineType {U} AutomaticLine
    LineType m_EmptyStyle;
    //## end PlanFinObject::EmptyStyle%35139C250384.attr

    //## begin PlanFinObject::TabOrder%35192AEA03A2.attr preserve=no  public: double {U} 0
    double m_TabOrder;
    //## end PlanFinObject::TabOrder%35192AEA03A2.attr

    //## begin PlanFinObject::LineNumber%35B8BE2700A4.attr preserve=no  public: DWORD {U} 
    DWORD m_LineNumber;
    //## end PlanFinObject::LineNumber%35B8BE2700A4.attr

    //## begin PlanFinObject::pBorder%362B6ADB0248.attr preserve=no  public: ZABorder* {U} NULL
    ZABorder* m_pBorder;
    //## end PlanFinObject::pBorder%362B6ADB0248.attr

    //## begin PlanFinObject::DefaultValue%36331C3D0323.attr preserve=no  public: BOOL {U} FALSE
    BOOL m_DefaultValue;
    //## end PlanFinObject::DefaultValue%36331C3D0323.attr

    //## begin PlanFinObject::HasBeenChanged%36B5E69900F1.attr preserve=no  public: BOOL {U} 
    BOOL m_HasBeenChanged;
    //## end PlanFinObject::HasBeenChanged%36B5E69900F1.attr

    //## Attribute: ReadOnly%37D0DD9D0218
    // Defines if the document is read-only.
    //## begin PlanFinObject::ReadOnly%37D0DD9D0218.attr preserve=no  private: BOOL {U} 
    BOOL m_ReadOnly;
    //## end PlanFinObject::ReadOnly%37D0DD9D0218.attr

    //## Attribute: ReadOnlyAtRuntime%37D0E1D2007C
    // is TRUE if the document is read-only at runtime.
    //## begin PlanFinObject::ReadOnlyAtRuntime%37D0E1D2007C.attr preserve=no  public: BOOL {U} 
    BOOL m_ReadOnlyAtRuntime;
    //## end PlanFinObject::ReadOnlyAtRuntime%37D0E1D2007C.attr

    //## begin PlanFinObject::pColumn%38862FF000CE.attr preserve=no  public: ZBFieldColumn* {U} 
    ZBFieldColumn* m_pColumn;
    //## end PlanFinObject::pColumn%38862FF000CE.attr

    // Additional Private Declarations
    //## begin PlanFinObject%334FC4610180.private preserve=yes
    // Version 17
    CString m_UserHelp;
    //## end PlanFinObject%334FC4610180.private

// Additional Implementation Declarations
    //## begin PlanFinObject%334FC4610180.implementation preserve=yes
    //## end PlanFinObject%334FC4610180.implementation
};

//## begin PlanFinObject%334FC4610180.postscript preserve=yes
//## end PlanFinObject%334FC4610180.postscript

// Class PlanFinObject 


//## Other Operations (inline)
inline BOOL PlanFinObject::IsEmpty () const
{
  //## begin PlanFinObject::IsEmpty%829516134.body preserve=yes
    return m_IsEmpty;  
  //## end PlanFinObject::IsEmpty%829516134.body
}

inline void PlanFinObject::EmptyObject ()
{
  //## begin PlanFinObject::EmptyObject%846024742.body preserve=yes
      m_IsEmpty = TRUE;
  //## end PlanFinObject::EmptyObject%846024742.body
}

inline void PlanFinObject::ClearEmptyObjectFlag ()
{
  //## begin PlanFinObject::ClearEmptyObjectFlag%922093645.body preserve=yes
      m_IsEmpty = FALSE;
  //## end PlanFinObject::ClearEmptyObjectFlag%922093645.body
}

inline BOOL PlanFinObject::IsSelectObject () const
{
  //## begin PlanFinObject::IsSelectObject%829516139.body preserve=yes
  return m_bSelected;
  //## end PlanFinObject::IsSelectObject%829516139.body
}

inline CRect& PlanFinObject::GetClientRect ()
{
  //## begin PlanFinObject::GetClientRect%829516143.body preserve=yes
      return m_rctObject;
  //## end PlanFinObject::GetClientRect%829516143.body
}

inline int PlanFinObject::GetObjectPage () const
{
  //## begin PlanFinObject::GetObjectPage%829516144.body preserve=yes
      return m_iPage;
  //## end PlanFinObject::GetObjectPage%829516144.body
}

inline FormatType PlanFinObject::GetFormatType () const
{
  //## begin PlanFinObject::GetFormatType%829516145.body preserve=yes
      return m_FormatType;
  //## end PlanFinObject::GetFormatType%829516145.body
}

inline void PlanFinObject::SetFormatType (FormatType Fmt)
{
  //## begin PlanFinObject::SetFormatType%829516146.body preserve=yes
      m_FormatType = Fmt;
  //## end PlanFinObject::SetFormatType%829516146.body
}

inline void PlanFinObject::Recalculate (ZDDocument* pDoc)
{
  //## begin PlanFinObject::Recalculate%829516154.body preserve=yes
  //## end PlanFinObject::Recalculate%829516154.body
}

inline void PlanFinObject::SetValue (double dValue)
{
  //## begin PlanFinObject::SetValue%829516155.body preserve=yes
  //## end PlanFinObject::SetValue%829516155.body
}

inline double PlanFinObject::GetValue () const
{
  //## begin PlanFinObject::GetValue%829516156.body preserve=yes
      return 0;
  //## end PlanFinObject::GetValue%829516156.body
}

inline void* PlanFinObject::GetObjectAdress () const
{
  //## begin PlanFinObject::GetObjectAdress%829516159.body preserve=yes
      return NULL;
  //## end PlanFinObject::GetObjectAdress%829516159.body
}

inline CStringArray& PlanFinObject::GetFormatChoice ()
{
  //## begin PlanFinObject::GetFormatChoice%829516161.body preserve=yes
      m_FormatChoice.RemoveAll();
      return m_FormatChoice;
  //## end PlanFinObject::GetFormatChoice%829516161.body
}

inline void PlanFinObject::SetFormatWithChoice (const CString& sValue)
{
  //## begin PlanFinObject::SetFormatWithChoice%829516162.body preserve=yes
  //## end PlanFinObject::SetFormatWithChoice%829516162.body
}

inline void PlanFinObject::GetRectTop (CRect* pRect) const
{
  //## begin PlanFinObject::GetRectTop%829516165.body preserve=yes
    pRect->left = m_rctObject.left+(m_rctObject.right - m_rctObject.left)/2-2;
    pRect->top = m_rctObject.top-2;
    pRect->right = m_rctObject.left+(m_rctObject.right - m_rctObject.left)/2+2;
    pRect->bottom = m_rctObject.top+2;
  //## end PlanFinObject::GetRectTop%829516165.body
}

inline void PlanFinObject::GetRectBottom (CRect* pRect) const
{
  //## begin PlanFinObject::GetRectBottom%829516166.body preserve=yes
    pRect->left = m_rctObject.left+(m_rctObject.right - m_rctObject.left)/2-2;
    pRect->top = m_rctObject.bottom-2;
    pRect->right = m_rctObject.left+(m_rctObject.right - m_rctObject.left)/2+2;
    pRect->bottom = m_rctObject.bottom+2;
  //## end PlanFinObject::GetRectBottom%829516166.body
}

inline void PlanFinObject::GetRectLeft (CRect* pRect) const
{
  //## begin PlanFinObject::GetRectLeft%829516167.body preserve=yes
    pRect->left = m_rctObject.left-2;
    pRect->top = m_rctObject.top+(m_rctObject.bottom - m_rctObject.top)/2-2;
    pRect->right = m_rctObject.left+2;
    pRect->bottom = m_rctObject.top+(m_rctObject.bottom - m_rctObject.top)/2+2;
  //## end PlanFinObject::GetRectLeft%829516167.body
}

inline void PlanFinObject::GetRectRight (CRect* pRect) const
{
  //## begin PlanFinObject::GetRectRight%829516168.body preserve=yes
    pRect->left = m_rctObject.right-2;
    pRect->top = m_rctObject.top+(m_rctObject.bottom - m_rctObject.top)/2-2;
    pRect->right = m_rctObject.right+2;
    pRect->bottom = m_rctObject.top+(m_rctObject.bottom - m_rctObject.top)/2+2;
  //## end PlanFinObject::GetRectRight%829516168.body
}

inline BOOL PlanFinObject::IsRectTop (const CPoint& Point) const
{
  //## begin PlanFinObject::IsRectTop%829516169.body preserve=yes
    CRect    rect;
    GetRectTop( &rect );
    return( rect.PtInRect( Point ) );
  //## end PlanFinObject::IsRectTop%829516169.body
}

inline BOOL PlanFinObject::IsRectBottom (const CPoint& Point) const
{
  //## begin PlanFinObject::IsRectBottom%829516170.body preserve=yes
    CRect    rect;
    GetRectBottom( &rect );
    return( rect.PtInRect( Point ) );
  //## end PlanFinObject::IsRectBottom%829516170.body
}

inline BOOL PlanFinObject::IsRectLeft (const CPoint& Point) const
{
  //## begin PlanFinObject::IsRectLeft%829516171.body preserve=yes
    CRect    rect;
    GetRectLeft( &rect );
    return( rect.PtInRect( Point ) );
  //## end PlanFinObject::IsRectLeft%829516171.body
}

inline BOOL PlanFinObject::IsRectRight (const CPoint& Point) const
{
  //## begin PlanFinObject::IsRectRight%829516172.body preserve=yes
    CRect    rect;
    GetRectRight( &rect );
    return( rect.PtInRect( Point ) );
  //## end PlanFinObject::IsRectRight%829516172.body
}

inline BOOL PlanFinObject::IsSelected (const CPoint& point) const
{
  //## begin PlanFinObject::IsSelected%829516175.body preserve=yes
      return FALSE;
  //## end PlanFinObject::IsSelected%829516175.body
}

inline BOOL PlanFinObject::IsHint (CPoint& point) const
{
  //## begin PlanFinObject::IsHint%829516177.body preserve=yes
    return( m_rctObject.PtInRect( point ) );
  //## end PlanFinObject::IsHint%829516177.body
}

inline const char* PlanFinObject::GetFormatedBuffer () const
{
  //## begin PlanFinObject::GetFormatedBuffer%829516180.body preserve=yes
      return m_szFormatBuffer;
  //## end PlanFinObject::GetFormatedBuffer%829516180.body
}

inline UINT PlanFinObject::GetJustify (ZDDocument* pDoc) const
{
  //## begin PlanFinObject::GetJustify%833261592.body preserve=yes
      return DT_LEFT | DT_BOTTOM | DT_SINGLELINE;
  //## end PlanFinObject::GetJustify%833261592.body
}

inline void PlanFinObject::SetJustify (UINT nValue)
{
  //## begin PlanFinObject::SetJustify%833261593.body preserve=yes
  //## end PlanFinObject::SetJustify%833261593.body
}

inline void PlanFinObject::SetClientRect (const CRect& rect)
{
  //## begin PlanFinObject::SetClientRect%833930834.body preserve=yes
      (CRect&)m_rctObject = rect;
  //## end PlanFinObject::SetClientRect%833930834.body
}

inline void PlanFinObject::SetObjectPage (int iPage)
{
  //## begin PlanFinObject::SetObjectPage%833930835.body preserve=yes
      m_iPage = iPage;
  //## end PlanFinObject::SetObjectPage%833930835.body
}

inline void PlanFinObject::SelectObject (BOOL bState)
{
  //## begin PlanFinObject::SelectObject%853480522.body preserve=yes
    m_bSelected = bState;
  //## end PlanFinObject::SelectObject%853480522.body
}

inline UINT PlanFinObject::GetRightSubMenu () const
{
  //## begin PlanFinObject::GetRightSubMenu%864330568.body preserve=yes
      return ObjectRightSubMenu;
  //## end PlanFinObject::GetRightSubMenu%864330568.body
}

inline void PlanFinObject::SetiAngle (int iAngle, ZDDocument* pDoc)
{
  //## begin PlanFinObject::SetiAngle%880663111.body preserve=yes
      if (iAngle == m_iAngle)
          return;
      // Assign the angle value
      m_iAngle = iAngle;
      OnAngleChanged(pDoc);
  //## end PlanFinObject::SetiAngle%880663111.body
}

inline UINT PlanFinObject::GetPropertyTabs () const
{
  //## begin PlanFinObject::GetPropertyTabs%885128487.body preserve=yes
      // By default, General and Size Pages
    return PropertyGeneralPage | PropertySizePage;
  //## end PlanFinObject::GetPropertyTabs%885128487.body
}

inline void PlanFinObject::NotifyObjectHasChanged ()
{
  //## begin PlanFinObject::NotifyObjectHasChanged%903688630.body preserve=yes
    // To notify the view that on field change
    // Pass the adress of the object
    // then the routine that proceed the message
    // can know wich object has changed
    AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)this );
  //## end PlanFinObject::NotifyObjectHasChanged%903688630.body
}

inline BOOL PlanFinObject::HasBeenChanged () const
{
  //## begin PlanFinObject::HasBeenChanged%917889604.body preserve=yes
      return m_HasBeenChanged;
  //## end PlanFinObject::HasBeenChanged%917889604.body
}

inline BOOL PlanFinObject::IsReadOnly () const
{
  //## begin PlanFinObject::IsReadOnly%936435176.body preserve=yes
    return m_ReadOnly;
  //## end PlanFinObject::IsReadOnly%936435176.body
}

inline void PlanFinObject::SetAsReadOnly (BOOL value)
{
  //## begin PlanFinObject::SetAsReadOnly%936435177.body preserve=yes
    m_ReadOnly = value;
  //## end PlanFinObject::SetAsReadOnly%936435177.body
}

inline BOOL PlanFinObject::IsReadOnlyAtRuntime ()
{
  //## begin PlanFinObject::IsReadOnlyAtRuntime%936435178.body preserve=yes
    return m_ReadOnlyAtRuntime || m_ReadOnly;
  //## end PlanFinObject::IsReadOnlyAtRuntime%936435178.body
}

inline void PlanFinObject::SetReadOnlyAtRuntime (BOOL value)
{
  //## begin PlanFinObject::SetReadOnlyAtRuntime%936435179.body preserve=yes
    m_ReadOnlyAtRuntime = value;
  //## end PlanFinObject::SetReadOnlyAtRuntime%936435179.body
}

inline void PlanFinObject::ClearNotes ()
{
  //## begin PlanFinObject::ClearNotes%937733878.body preserve=yes
    if (m_pNotes)
        m_pNotes->ClearNotes();
  //## end PlanFinObject::ClearNotes%937733878.body
}

inline ZBNotes* PlanFinObject::GetNotesPointer () const
{
  //## begin PlanFinObject::GetNotesPointer%937741728.body preserve=yes
    return m_pNotes;
  //## end PlanFinObject::GetNotesPointer%937741728.body
}

inline BOOL PlanFinObject::IsMemberOfMultiColumn () const
{
  //## begin PlanFinObject::IsMemberOfMultiColumn%948318239.body preserve=yes
    return m_pColumn != NULL;
  //## end PlanFinObject::IsMemberOfMultiColumn%948318239.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const BOOL PlanFinObject::GetbIsVisible () const
{
  //## begin PlanFinObject::GetbIsVisible%334FC46102A0.get preserve=no
  return m_bIsVisible;
  //## end PlanFinObject::GetbIsVisible%334FC46102A0.get
}

inline void PlanFinObject::SetbIsVisible (BOOL value)
{
  //## begin PlanFinObject::SetbIsVisible%334FC46102A0.set preserve=no
  m_bIsVisible = value;
  //## end PlanFinObject::SetbIsVisible%334FC46102A0.set
}

inline const BOOL PlanFinObject::GetbMustBePrinted () const
{
  //## begin PlanFinObject::GetbMustBePrinted%334FC46102A1.get preserve=no
  return m_bMustBePrinted;
  //## end PlanFinObject::GetbMustBePrinted%334FC46102A1.get
}

inline void PlanFinObject::SetbMustBePrinted (BOOL value)
{
  //## begin PlanFinObject::SetbMustBePrinted%334FC46102A1.set preserve=no
  m_bMustBePrinted = value;
  //## end PlanFinObject::SetbMustBePrinted%334FC46102A1.set
}

inline CRectTracker* PlanFinObject::GetpRectTracker ()
{
  //## begin PlanFinObject::GetpRectTracker%334FC461029F.get preserve=no
  return m_pRectTracker;
  //## end PlanFinObject::GetpRectTracker%334FC461029F.get
}

inline void PlanFinObject::SetpRectTracker (CRectTracker* value)
{
  //## begin PlanFinObject::SetpRectTracker%334FC461029F.set preserve=no
  m_pRectTracker = value;
  //## end PlanFinObject::SetpRectTracker%334FC461029F.set
}

inline const COLORREF PlanFinObject::GetColor () const
{
  //## begin PlanFinObject::GetColor%334FC46102A2.get preserve=no
  return m_Color;
  //## end PlanFinObject::GetColor%334FC46102A2.get
}

inline void PlanFinObject::SetColor (COLORREF value)
{
  //## begin PlanFinObject::SetColor%334FC46102A2.set preserve=no
  m_Color = value;
  //## end PlanFinObject::SetColor%334FC46102A2.set
}

inline const COLORREF PlanFinObject::GetFillColor () const
{
  //## begin PlanFinObject::GetFillColor%334FC46102A3.get preserve=no
  return m_FillColor;
  //## end PlanFinObject::GetFillColor%334FC46102A3.get
}

inline void PlanFinObject::SetFillColor (COLORREF value)
{
  //## begin PlanFinObject::SetFillColor%334FC46102A3.set preserve=no
  m_FillColor = value;
  //## end PlanFinObject::SetFillColor%334FC46102A3.set
}

inline const unsigned long PlanFinObject::GetuGroupNumber () const
{
  //## begin PlanFinObject::GetuGroupNumber%3378863002E4.get preserve=no
  return m_uGroupNumber;
  //## end PlanFinObject::GetuGroupNumber%3378863002E4.get
}

inline void PlanFinObject::SetuGroupNumber (unsigned long value)
{
  //## begin PlanFinObject::SetuGroupNumber%3378863002E4.set preserve=no
  m_uGroupNumber = value;
  //## end PlanFinObject::SetuGroupNumber%3378863002E4.set
}

inline const HandleFont PlanFinObject::GethFont () const
{
  //## begin PlanFinObject::GethFont%33D79AA702B2.get preserve=no
  return m_hFont;
  //## end PlanFinObject::GethFont%33D79AA702B2.get
}

inline void PlanFinObject::SethFont (HandleFont value)
{
  //## begin PlanFinObject::SethFont%33D79AA702B2.set preserve=no
  m_hFont = value;
  //## end PlanFinObject::SethFont%33D79AA702B2.set
}

inline const HandleStyle PlanFinObject::GethStyle () const
{
  //## begin PlanFinObject::GethStyle%33D9DF7F032A.get preserve=no
  return m_hStyle;
  //## end PlanFinObject::GethStyle%33D9DF7F032A.get
}

inline const int PlanFinObject::GetiAngle () const
{
  //## begin PlanFinObject::GetiAngle%347C59770320.get preserve=no
  return m_iAngle;
  //## end PlanFinObject::GetiAngle%347C59770320.get
}

inline const LineType PlanFinObject::GetEmptyStyle () const
{
  //## begin PlanFinObject::GetEmptyStyle%35139C250384.get preserve=no
  return m_EmptyStyle;
  //## end PlanFinObject::GetEmptyStyle%35139C250384.get
}

inline void PlanFinObject::SetEmptyStyle (LineType value)
{
  //## begin PlanFinObject::SetEmptyStyle%35139C250384.set preserve=no
  m_EmptyStyle = value;
  //## end PlanFinObject::SetEmptyStyle%35139C250384.set
}

inline const double PlanFinObject::GetTabOrder () const
{
  //## begin PlanFinObject::GetTabOrder%35192AEA03A2.get preserve=no
  return m_TabOrder;
  //## end PlanFinObject::GetTabOrder%35192AEA03A2.get
}

inline void PlanFinObject::SetTabOrder (double value)
{
  //## begin PlanFinObject::SetTabOrder%35192AEA03A2.set preserve=no
  m_TabOrder = value;
  //## end PlanFinObject::SetTabOrder%35192AEA03A2.set
}

inline const DWORD PlanFinObject::GetLineNumber () const
{
  //## begin PlanFinObject::GetLineNumber%35B8BE2700A4.get preserve=no
  return m_LineNumber;
  //## end PlanFinObject::GetLineNumber%35B8BE2700A4.get
}

inline void PlanFinObject::SetLineNumber (DWORD value)
{
  //## begin PlanFinObject::SetLineNumber%35B8BE2700A4.set preserve=no
  m_LineNumber = value;
  //## end PlanFinObject::SetLineNumber%35B8BE2700A4.set
}

inline ZABorder* PlanFinObject::GetpBorder ()
{
  //## begin PlanFinObject::GetpBorder%362B6ADB0248.get preserve=no
  return m_pBorder;
  //## end PlanFinObject::GetpBorder%362B6ADB0248.get
}

inline void PlanFinObject::SetpBorder (ZABorder* value)
{
  //## begin PlanFinObject::SetpBorder%362B6ADB0248.set preserve=no
  m_pBorder = value;
  //## end PlanFinObject::SetpBorder%362B6ADB0248.set
}

inline const BOOL PlanFinObject::GetDefaultValue () const
{
  //## begin PlanFinObject::GetDefaultValue%36331C3D0323.get preserve=no
  return m_DefaultValue;
  //## end PlanFinObject::GetDefaultValue%36331C3D0323.get
}

inline void PlanFinObject::SetDefaultValue (BOOL value)
{
  //## begin PlanFinObject::SetDefaultValue%36331C3D0323.set preserve=no
  m_DefaultValue = value;
  //## end PlanFinObject::SetDefaultValue%36331C3D0323.set
}

inline void PlanFinObject::SetHasBeenChanged (BOOL value)
{
  //## begin PlanFinObject::SetHasBeenChanged%36B5E69900F1.set preserve=no
  m_HasBeenChanged = value;
  //## end PlanFinObject::SetHasBeenChanged%36B5E69900F1.set
}

inline const ZBFieldColumn* PlanFinObject::GetpColumn () const
{
  //## begin PlanFinObject::GetpColumn%38862FF000CE.get preserve=no
  return m_pColumn;
  //## end PlanFinObject::GetpColumn%38862FF000CE.get
}

inline void PlanFinObject::SetpColumn (ZBFieldColumn* value)
{
  //## begin PlanFinObject::SetpColumn%38862FF000CE.set preserve=no
  m_pColumn = value;
  //## end PlanFinObject::SetpColumn%38862FF000CE.set
}

//## begin module%334FC46302E9.epilog preserve=yes
//## end module%334FC46302E9.epilog


#endif
