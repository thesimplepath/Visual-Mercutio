//## begin module%334FC46302F8.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%334FC46302F8.cm

//## begin module%334FC46302F8.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%334FC46302F8.cp

//## Module: VTools%334FC46302F8; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\VTools.h

#ifndef VTools_h
#define VTools_h 1

//## begin module%334FC46302F8.additionalIncludes preserve=no
//## end module%334FC46302F8.additionalIncludes

//## begin module%334FC46302F8.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%334FC46302F8.includes

// ZIView
#include "ZIView.h"
//## begin module%334FC46302F8.declarations preserve=no
//## end module%334FC46302F8.declarations

//## begin module%334FC46302F8.additionalDeclarations preserve=yes
#ifndef _WIN32
#include "ToolBarx.h"
#endif

enum ToolType
{
	VToolSelect,
	VToolEdit,
	VToolLine,
	VToolRect,
	VToolRoundRect,
	VToolBoundEdit,
	VToolDate,
	VToolNumber,
	VToolSquareText,
	VToolCheckBox,
	VToolRadioButton,
	VToolStaticText,
	VToolText,
	VToolCircle,
	VToolBitmap,
	VToolNumbered,
	VToolDesignEdit,
	VToolDesignEditFieldName,
	VToolMaskText,
	VToolTabOrder,
	VToolMultiColumn,
};

enum VisualToolModes
{
	NormalMode,
	NoCreateMode,
};

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

//## end module%334FC46302F8.additionalDeclarations

//## Class: ZIVisualTool%334FC46103DF; Abstract
//	Base class for visual tool. These tools can be select,
//	edit, add new rectangle, line, text, etc.
//## Category: ZBaseLib::Visual Tools%334FC46103DE
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%334FC46103E0;ZIView { -> }

class AFX_EXT_CLASS ZIVisualTool 
{
//## begin ZIVisualTool%334FC46103DF.initialDeclarations preserve=yes
//## end ZIVisualTool%334FC46103DF.initialDeclarations
public:

	//## Constructors (specified)
	//## Operation: ZIVisualTool%832040471
	//	The constructor of the VisualToolDesignEdit. It is
	//	necessary to specifiy wich tool type it is necessary to
	//	create.
	ZIVisualTool ( ToolType ObjectToolType );

	//## Destructor (generated)
	~ZIVisualTool();

	//## Other Operations (specified)
	//## Operation: OnLButtonDown%832038253
	//	On left button down.
	virtual void OnLButtonDown ( ZIView* pView, UINT nFlags, const CPoint& point );

	//## Operation: OnLButtonDblClk%832038254
	//	On left button double click.
	virtual void OnLButtonDblClk ( ZIView* pView, UINT nFlags, const CPoint& point );

	//## Operation: OnLButtonUp%832038255
	//	On left button up.
	virtual void OnLButtonUp ( ZIView* pView, UINT nFlags, const CPoint& point );

	//## Operation: OnMouseMove%832038256
	//	On mouse move.
	virtual void OnMouseMove ( ZIView* pView, UINT nFlags, const CPoint& point );

	//## Operation: OnCancel%832038257
	//	When cancel the current action.
	virtual void OnCancel ();

	//## Operation: FindTool%832040472
	//	Return a pointer to a class that correspond the Object
	//	ToolType.
	static ZIVisualTool* FindTool ( ToolType ObjectToolType );

	//## Get and Set Operations for Class Attributes (generated)

	//## Attribute: ObjectToolType%334FC4620031
	//	Defines the tool type. Can be Select, Edit, BoundText,
	//	etc.
	const ToolType& GetObjectToolType () const;

	// Data Members for Class Attributes

	//## Attribute: CurrentToolType%334FC4620032
	//	The current selected tool type.
	//## begin ZIVisualTool::CurrentToolType%334FC4620032.attr preserve=no  public: static ToolType {V} VToolEdit
	static ToolType m_CurrentToolType;
	//## end ZIVisualTool::CurrentToolType%334FC4620032.attr

	//## Attribute: ToolMode%3546151F00B6
	//## begin ZIVisualTool::ToolMode%3546151F00B6.attr preserve=no  public: static VisualToolModes {U} NormalMode
	static VisualToolModes m_ToolMode;
	//## end ZIVisualTool::ToolMode%3546151F00B6.attr

	//## Attribute: Rect%35461F590396
	//## begin ZIVisualTool::Rect%35461F590396.attr preserve=no  public: static CRect {U} 
	static CRect m_Rect;
	//## end ZIVisualTool::Rect%35461F590396.attr

	// Additional Public Declarations
	//## begin ZIVisualTool%334FC46103DF.public preserve=yes
	//## end ZIVisualTool%334FC46103DF.public

protected:

	// Data Members for Class Attributes

	//## Attribute: DownPoint%334FC4620034
	//	The point when the user starts with the tool.
	//## begin ZIVisualTool::DownPoint%334FC4620034.attr preserve=no  public: static CPoint {V} 
	static CPoint m_DownPoint;
	//## end ZIVisualTool::DownPoint%334FC4620034.attr

	//## Attribute: LastPoint%334FC4620035
	//	The point when the user terminates with the tool.
	//## begin ZIVisualTool::LastPoint%334FC4620035.attr preserve=no  public: static CPoint {V} 
	static CPoint m_LastPoint;
	//## end ZIVisualTool::LastPoint%334FC4620035.attr

	//## Attribute: hcurNormal%334FC4620037
	//	The handle of the normal cursor.
	//## begin ZIVisualTool::hcurNormal%334FC4620037.attr preserve=no  public: HCURSOR {V} 
	HCURSOR m_hcurNormal;
	//## end ZIVisualTool::hcurNormal%334FC4620037.attr

	// Additional Protected Declarations
	//## begin ZIVisualTool%334FC46103DF.protected preserve=yes
	//## end ZIVisualTool%334FC46103DF.protected

private:

	//## Constructors (generated)
	ZIVisualTool( const ZIVisualTool &right );

	//## Assignment Operation (generated)
	const ZIVisualTool & operator=( const ZIVisualTool &right );

	// Data Members for Class Attributes

	//## begin ZIVisualTool::ObjectToolType%334FC4620031.attr preserve=no  public: ToolType {V} 
	ToolType m_ObjectToolType;
	//## end ZIVisualTool::ObjectToolType%334FC4620031.attr

	//## Attribute: ToolsList%334FC4620033
	//	The list of all created list. This list is updated by
	//	the constructor.
	//## begin ZIVisualTool::ToolsList%334FC4620033.attr preserve=no  public: static CPtrList {V} 
	static CPtrList m_ToolsList;
	//## end ZIVisualTool::ToolsList%334FC4620033.attr

	//## Attribute: nDownFlags%334FC4620036
	//	The flags saved when down.
	//## begin ZIVisualTool::nDownFlags%334FC4620036.attr preserve=no  public: static UINT {V} 
	static UINT m_nDownFlags;
	//## end ZIVisualTool::nDownFlags%334FC4620036.attr

	// Additional Private Declarations
	//## begin ZIVisualTool%334FC46103DF.private preserve=yes
	//## end ZIVisualTool%334FC46103DF.private

private:  //## implementation

	// Additional Implementation Declarations
	//## begin ZIVisualTool%334FC46103DF.implementation preserve=yes
	//## end ZIVisualTool%334FC46103DF.implementation
};

//## begin ZIVisualTool%334FC46103DF.postscript preserve=yes
//## end ZIVisualTool%334FC46103DF.postscript

//## Class: ZIVisualToolEdit%334FC4620038
//	This tools is used to edit objects.
//## Category: ZBaseLib::Visual Tools%334FC46103DE
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZIVisualToolEdit : public ZIVisualTool  //## Inherits: <unnamed>%334FC4620039
{
//## begin ZIVisualToolEdit%334FC4620038.initialDeclarations preserve=yes
public:

	// Inherited feature
	typedef ZIVisualTool inherited;
	//## end ZIVisualToolEdit%334FC4620038.initialDeclarations

public:

	//## Constructors (generated)
	ZIVisualToolEdit();

	//## Destructor (generated)
	~ZIVisualToolEdit();

	//## Other Operations (specified)
	//## Operation: OnLButtonDown%832038253
	//	On left button down.
	virtual void OnLButtonDown ( ZIView* pView, UINT nFlags, const CPoint& point );

	//## Operation: OnLButtonUp%832038255
	//	On left button up.
	virtual void OnLButtonUp ( ZIView* pView, UINT nFlags, const CPoint& point );

	//## Operation: OnMouseMove%832038256
	//	On mouse move.
	virtual void OnMouseMove ( ZIView* pView, UINT nFlags, const CPoint& point );

	// Additional Public Declarations
	//## begin ZIVisualToolEdit%334FC4620038.public preserve=yes
	//## end ZIVisualToolEdit%334FC4620038.public

protected:

	// Additional Protected Declarations
	//## begin ZIVisualToolEdit%334FC4620038.protected preserve=yes
	//## end ZIVisualToolEdit%334FC4620038.protected

private:

	//## Constructors (generated)
	ZIVisualToolEdit( const ZIVisualToolEdit &right );

	//## Assignment Operation (generated)
	const ZIVisualToolEdit & operator=(const ZIVisualToolEdit &right);

	// Data Members for Class Attributes

	//## Attribute: hcurEdit%38228178018D
	//	The handle of the edit cursor.
	//## begin ZIVisualToolEdit::hcurEdit%38228178018D.attr preserve=no  public: HCURSOR {U} 
	HCURSOR m_hcurEdit;
	//## end ZIVisualToolEdit::hcurEdit%38228178018D.attr

	// Additional Private Declarations
	//## begin ZIVisualToolEdit%334FC4620038.private preserve=yes
	//## end ZIVisualToolEdit%334FC4620038.private

private:  //## implementation

	// Additional Implementation Declarations
	//## begin ZIVisualToolEdit%334FC4620038.implementation preserve=yes
	//## end ZIVisualToolEdit%334FC4620038.implementation
};

//## begin ZIVisualToolEdit%334FC4620038.postscript preserve=yes
//## end ZIVisualToolEdit%334FC4620038.postscript

//## Class: ZIVisualToolObjectCreator%334FC462007F
//	This tools is used to create objects.
//## Category: ZBaseLib::Visual Tools%334FC46103DE
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZIVisualToolObjectCreator : public ZIVisualTool  //## Inherits: <unnamed>%334FC4620096
{
//## begin ZIVisualToolObjectCreator%334FC462007F.initialDeclarations preserve=yes
public:

	// Inherited feature
	typedef ZIVisualTool inherited;
	//## end ZIVisualToolObjectCreator%334FC462007F.initialDeclarations

public:

	//## Constructors (specified)
	//## Operation: ZIVisualToolObjectCreator%833838851
	ZIVisualToolObjectCreator ( ToolType ObjectToolType );

	//## Destructor (generated)
	~ZIVisualToolObjectCreator();

	//## Other Operations (specified)
	//## Operation: OnLButtonDown%832038253
	//	On left button down.
	virtual void OnLButtonDown ( ZIView* pView, UINT nFlags, const CPoint& point );

	//## Operation: OnLButtonUp%832038255
	//	On left button up.
	virtual void OnLButtonUp ( ZIView* pView, UINT nFlags, const CPoint& point );

	//## Operation: OnMouseMove%832038256
	//	On mouse move.
	virtual void OnMouseMove ( ZIView* pView, UINT nFlags, const CPoint& point );

	// Additional Public Declarations
	//## begin ZIVisualToolObjectCreator%334FC462007F.public preserve=yes
	//## end ZIVisualToolObjectCreator%334FC462007F.public

protected:

	//## Other Operations (specified)
	//## Operation: CreateObject%833838850
	//	After using this tool. When the left mouse button is up,
	//	this tool is called. This function is pure abstract.
	virtual void CreateObject ( CRect& rect ) = 0;

	// Data Members for Class Attributes

	//## Attribute: hcurCreation%334FC46200A7
	//	The creation cursor. Used to show when a field is
	//	editable.
	//## begin ZIVisualToolObjectCreator::hcurCreation%334FC46200A7.attr preserve=no  public: HCURSOR {U} 
	HCURSOR m_hcurCreation;
	//## end ZIVisualToolObjectCreator::hcurCreation%334FC46200A7.attr

	//## Attribute: CreationStarted%334FC46200A8
	//	Flag to know when the creation is started
	//## begin ZIVisualToolObjectCreator::CreationStarted%334FC46200A8.attr preserve=no  public: BOOL {U} FALSE
	BOOL m_CreationStarted;
	//## end ZIVisualToolObjectCreator::CreationStarted%334FC46200A8.attr

	// Additional Protected Declarations
	//## begin ZIVisualToolObjectCreator%334FC462007F.protected preserve=yes
	//## end ZIVisualToolObjectCreator%334FC462007F.protected

private:

	//## Constructors (generated)
	ZIVisualToolObjectCreator( const ZIVisualToolObjectCreator &right );

	//## Assignment Operation (generated)
	const ZIVisualToolObjectCreator & operator=( const ZIVisualToolObjectCreator &right );

	// Additional Private Declarations
	//## begin ZIVisualToolObjectCreator%334FC462007F.private preserve=yes
	//## end ZIVisualToolObjectCreator%334FC462007F.private

private:  //## implementation

	// Additional Implementation Declarations
	//## begin ZIVisualToolObjectCreator%334FC462007F.implementation preserve=yes
	//## end ZIVisualToolObjectCreator%334FC462007F.implementation
};

//## begin ZIVisualToolObjectCreator%334FC462007F.postscript preserve=yes
//## end ZIVisualToolObjectCreator%334FC462007F.postscript

// Class ZIVisualTool 

//## Get and Set Operations for Class Attributes (inline)

inline const ToolType& ZIVisualTool::GetObjectToolType () const
{
	//## begin ZIVisualTool::GetObjectToolType%334FC4620031.get preserve=no
	return m_ObjectToolType;
	//## end ZIVisualTool::GetObjectToolType%334FC4620031.get
}

// Class ZIVisualToolEdit 

// Class ZIVisualToolObjectCreator 

//## begin module%334FC46302F8.epilog preserve=yes
//## end module%334FC46302F8.epilog

#endif

// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin ZIVisualToolSelection%334FC462006B.initialDeclarations preserve=no
//## end ZIVisualToolSelection%334FC462006B.initialDeclarations

//## begin ZIVisualToolDesignEdit%38227BF102FB.initialDeclarations preserve=no
	public:
	// Inherited feature
		typedef ZIVisualTool inherited;
//## end ZIVisualToolDesignEdit%38227BF102FB.initialDeclarations

//## begin ZIVisualToolFieldNameEdit%38228AD30083.initialDeclarations preserve=no
	public:
	// Inherited feature
		typedef ZIVisualTool inherited;
//## end ZIVisualToolFieldNameEdit%38228AD30083.initialDeclarations

//## begin ZIVisualToolTabOrder%3877524502B4.initialDeclarations preserve=no
	public:
	// Inherited feature
		typedef ZIVisualTool inherited;
//## end ZIVisualToolTabOrder%3877524502B4.initialDeclarations

#endif
