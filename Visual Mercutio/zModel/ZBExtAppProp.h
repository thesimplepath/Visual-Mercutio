/////////////////////////////////////////////////////////////////////////////
//@doc ZBExtAppProperties
//@module ZBExtAppProp.h | Interface of the <c ZBExtAppProperties> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:         07/2001
// <nl>Description:  ZBExtAppProperties external application properties
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __ZBExtAppProp_H__
#define __ZBExtAppProp_H__

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "PSS_PropIDs.h"

#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 27 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Process change flags

//@topic Process Properties Change Flags | Different aspects of the Process
// properties that can be changed individually.
//@flag Z_CHANGE_COMMAND_TITLE | Change the task list.
#define Z_CHANGE_COMMAND_TITLE        0x0001
//@flag Z_CHANGE_COMMAND_LINE | Change the decision list.
#define Z_CHANGE_COMMAND_LINE        0x0002
//@flag Z_CHANGE_COMMAND_PARAM | Change the decision list.
#define Z_CHANGE_COMMAND_PARAM        0x0004
//@flag Z_CHANGE_COMMAND_STARTUPDIR | Change the decision list.
#define Z_CHANGE_COMMAND_STARTUPDIR    0x0008
//@flag Z_CHANGE_PRIORITY_LEVEL | Change the decision list.
#define Z_CHANGE_PRIORITY_LEVEL        0x0010
//@flag Z_CHANGE_WINDOW_STARTMODE | Change the decision list.
#define Z_CHANGE_WINDOW_STARTMODE    0x0020

/////////////////////////////////////////////////////////////////////////////
// Fill property IDs

//@topic Fill Property Identifiers | Identify the properties contained by
// <c ZBExtAppProperties> objects. The ZBExtAppProperties class is a property
// container for these sub-properties. These property identifiers are
// unique within a process properties container. These identifiers are used
// in conjunction with the <c IODPropertyContainer> interface implemented
// by the process property container.
//@flag Z_COMMAND_TITLE | Identifier for the task list property.
#define Z_COMMAND_TITLE                1
//@flag Z_COMMAND_LINE | Identifier for the decision list property.
#define Z_COMMAND_LINE                2
//@flag Z_COMMAND_PARAM | Identifier for the decision list property.
#define Z_COMMAND_PARAM                3
//@flag Z_COMMAND_STARTUPDIR | Identifier for the decision list property.
#define Z_COMMAND_STARTUPDIR        4
//@flag Z_PRIORITY_LEVEL | Identifier for the decision list property.
#define Z_PRIORITY_LEVEL            5
//@flag Z_WINDOW_STARTMODE | Identifier for the decision list property.
#define Z_WINDOW_STARTMODE            6

/////////////////////////////////////////////////////////////////////////////
// ZBExtAppProperties
//
//@class This set of properties determines how a component is filled. Normally,
// the component is either not filled or filled with a solid color. You can also
// specify hatching and patterns.
//
//@base public | CObject

class AFX_EXT_CLASS ZBExtAppProperties : public CObject
{
    DECLARE_SERIAL( ZBExtAppProperties )

// Construction/Destruction
public:

    //@cmember
    /* Constructor. */
    ZBExtAppProperties();

    //@cmember
    /* Copy constructor. */
    ZBExtAppProperties( const ZBExtAppProperties& propProcess );

    //@cmember
    /* Destructor. */
    virtual ~ZBExtAppProperties();

public:

    //@cmember
    /* Gets the combination name. */
    CString GetCommandTitle() const;

    //@cmember
    /* Sets the combination name. */
    void SetCommandTitle( LPCTSTR lpszValue );

    //@cmember
    /* Gets the list of deliberables. */
    CString GetCommandLine() const;

    //@cmember
    /* Sets the list of deliberables. */
    void SetCommandLine( LPCTSTR lpszValue );

    //@cmember
    /* Gets the list of deliberables. */
    CString GetCommandParameters() const;

    //@cmember
    /* Sets the list of deliberables. */
    void SetCommandParameters( LPCTSTR lpszValue );

    //@cmember
    /* Gets the list of deliberables. */
    CString GetCommandStartupDirectory() const;

    //@cmember
    /* Sets the list of deliberables. */
    void SetCommandStartupDirectory( LPCTSTR lpszValue );

    //@cmember
    /* Gets the combination percentage. */
    int GetPriorityLevel() const;

    //@cmember
    /* Sets the combination percentage. */
    void SetPriorityLevel( const int value );

    //@cmember
    /* Gets the activation type. */
    int GetWindowStartMode() const;

    //@cmember
    /* Sets the activation type. */
    void SetWindowStartMode( const int value );

// Operations
public:

    //@cmember
    /* Sets this set of fill properties equal to another. */
    ZBExtAppProperties& operator=( const ZBExtAppProperties& propProcess );

    //@cmember
    /* Determines if another set of fill properties is equal to this one. */
    BOOL operator==( const ZBExtAppProperties propProcess ) const;

    //@cmember
    /* Makes a copy of this properties object. */
    virtual ZBExtAppProperties* Dup();

    //@cmember
    /* Merges another set of properties with this one. */
    virtual void Merge( ZBExtAppProperties* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL );

    //@cmember
    /* Determines if another set of properties is equal to this one. */
    virtual BOOL IsEqual( ZBExtAppProperties* pProp );

    // Determines if the object is empty
    virtual BOOL IsEmpty() const
    {
        return m_CommandTitle.IsEmpty()            &&
               m_CommandLine.IsEmpty()            &&
               m_CommandParameters.IsEmpty()    &&
               m_CommandStartupDirectory.IsEmpty();
    };

    /////////////////////////////////////////////////////////////////////////
    // GetValue and SetValue functions

    //@cmember
    /* Gets the value of the given string property. */
    virtual BOOL GetValue( const int nPropId, CString& strValue ) const;

    //@cmember
    /* Gets the value of the given integer property. */
    virtual BOOL GetValue( const int nPropId, int& nValue ) const;

    //@cmember
    /* Gets the value of the given unsigned integer property. */
    virtual BOOL GetValue( const int nPropId, UINT& nValue ) const;

    //@cmember
    /* Gets the value of the given DWORD property. */
    virtual BOOL GetValue( const int nPropId, DWORD& dwValue ) const;

    //@cmember
    /* Gets the value of the given float property. */
    virtual BOOL GetValue( const int nPropId, float& fValue ) const;

    //@cmember
    /* Sets the value of the given string property. */
    virtual BOOL SetValue( const int nPropId, LPCTSTR lpszValue );

    //@cmember
    /* Sets the value of the given integer property. */
    virtual BOOL SetValue( const int nPropId, const int nValue );

    //@cmember
    /* Sets the value of the given unsigned integer property. */
    virtual BOOL SetValue( const int nPropId, const UINT nValue );

    //@cmember
    /* Sets the value of the given unsigned DWORD property. */
    virtual BOOL SetValue( const int nPropId, const DWORD dwValue );

    //@cmember
    /* Sets the value of the given float property. */
    virtual BOOL SetValue( const int nPropId, const float fValue );

    //@cmember
    /* Serializes the line properties. */
    virtual void Serialize( CArchive& ar );

// Internal helper functions subject to change.
private:

    /* Additional mutators for use with CODIntPropertyAccessor */
    void SetCommandTitleEx( const CString value );
    void SetCommandLineEx( const CString value );
    void SetCommandParametersEx( const CString value );
    void SetCommandStartupDirectoryEx( const CString value );
    
    
// Implementation
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

// Attributes
protected:

    //@cmember
    /* The task list. */
    CString m_CommandTitle;

    /* The decision list. */
    CString m_CommandLine;

    /* The parameters. */
    CString m_CommandParameters;

    /* The startup directory. */
    CString m_CommandStartupDirectory;

    /* The activation percentage */
    int m_PriorityLevel;

    /* The activation type */
    int m_WindowStartMode;
};

/////////////////////////////////////////////////////////////////////////////
// ZBExtAppProperties inline methods

//@mfunc Gets the task list.
//@rdesc The task list.
inline CString ZBExtAppProperties::GetCommandTitle() const
{
    return m_CommandTitle;
}

//@mfunc Gets the decision list.
//@rdesc The decision list.
inline CString ZBExtAppProperties::GetCommandLine() const
{
    return m_CommandLine;
}

//@mfunc Gets the decision list.
//@rdesc The decision list.
inline CString ZBExtAppProperties::GetCommandParameters() const
{
    return m_CommandParameters;
}

//@mfunc Gets the decision list.
//@rdesc The decision list.
inline CString ZBExtAppProperties::GetCommandStartupDirectory() const
{
    return m_CommandStartupDirectory;
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline ZBExtAppProperties* ZBExtAppProperties::Dup()
{
    return new ZBExtAppProperties(*this);
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline int ZBExtAppProperties::GetPriorityLevel() const
{
    return m_PriorityLevel;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBExtAppProperties::SetPriorityLevel( const int value )
{
    m_PriorityLevel = value;
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline int ZBExtAppProperties::GetWindowStartMode() const
{
    return m_WindowStartMode;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBExtAppProperties::SetWindowStartMode( const int value )
{
    m_WindowStartMode = value;
}

#endif // __ZBExtAppProp_H__