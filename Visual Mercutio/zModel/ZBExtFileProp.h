/////////////////////////////////////////////////////////////////////////////
//@doc ZBExtFileProperties
//@module ZBExtFileProp.h | Interface of the <c ZBExtFileProperties> class.
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
// <nl>Created:         03/2001
// <nl>Description:  ZBExtFileProperties combination property
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __ZBExtFileProp_H__
#define __ZBExtFileProp_H__


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "PSS_PropIDs.h"

/////////////////////////////////////////////////////////////////////////////
// Process change flags

//@topic Process Properties Change Flags | Different aspects of the Process
// properties that can be changed individually.
//@flag Z_CHANGE_FILE_TITLE | Change the task list.
#define Z_CHANGE_FILE_TITLE                0x0001
//@flag Z_CHANGE_FILE_NAME | Change the decision list.
#define Z_CHANGE_FILE_NAME        0x0002
//@flag Z_CHANGE_INSERTION_TYPE | Change the decision list.
#define Z_CHANGE_INSERTION_TYPE    0x0004
//@flag Z_CHANGE_ACTIVATION_TYPE | Change the decision list.
#define Z_CHANGE_ACTIVATION_TYPE    0x0008

/////////////////////////////////////////////////////////////////////////////
// Fill property IDs

//@topic Fill Property Identifiers | Identify the properties contained by
// <c ZBExtFileProperties> objects. The ZBExtFileProperties class is a property
// container for these sub-properties. These property identifiers are
// unique within a process properties container. These identifiers are used
// in conjunction with the <c IODPropertyContainer> interface implemented
// by the process property container.
//@flag Z_FILE_TITLE | Identifier for the task list property.
#define Z_FILE_TITLE                        1
//@flag Z_FILE_NAME | Identifier for the decision list property.
#define Z_FILE_NAME              2
//@flag Z_INSERTION_TYPE | Identifier for the decision list property.
#define Z_INSERTION_TYPE           3
//@flag Z_ACTIVATION_TYPE | Identifier for the decision list property.
#define Z_ACTIVATION_TYPE           4

///////////////////////////////////////////////////////
// process defaults


#ifdef _ZMODELEXPORT
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

/////////////////////////////////////////////////////////////////////////////
// ZBExtFileProperties
//
//@class This set of properties determines how a component is filled. Normally,
// the component is either not filled or filled with a solid color. You can also
// specify hatching and patterns.
//
//
//@base public | CObject
//





class AFX_EXT_CLASS ZBExtFileProperties : public CObject
{
    DECLARE_SERIAL(ZBExtFileProperties)

// Construction/Destruction
public:
    //@cmember
    /* Constructor. */
    ZBExtFileProperties();
    //@cmember
    /* Copy constructor. */
    ZBExtFileProperties(const ZBExtFileProperties& propProcess);
    //@cmember
    /* Destructor. */
    virtual ~ZBExtFileProperties();

// Attributes
protected:
    //@cmember
    /* The task list. */
    CString m_FileTitle;
    /* The decision list. */
    CString m_Filename;
    /* The activation percentage */
    int m_InsertionType;
    /* The activation type */
    int m_ActivationType;

public:
    //@cmember
    /* Gets the combination name. */
    CString GetFileTitle() const;

    //@cmember
    /* Sets the combination name. */
    void SetFileTitle(LPCTSTR lpszValue);

    //@cmember
    /* Gets the list of deliberables. */
    CString GetFilename() const;

    //@cmember
    /* Sets the list of deliberables. */
    void SetFilename(LPCTSTR lpszValue);

    //@cmember
    /* Gets the combination percentage. */
    int GetInsertionType() const;

    //@cmember
    /* Sets the combination percentage. */
    void SetInsertionType(const int value);

    //@cmember
    /* Gets the activation type. */
    int GetActivationType() const;

    //@cmember
    /* Sets the activation type. */
    void SetActivationType(const int value);

// Operations
public:

    //@cmember
    /* Sets this set of fill properties equal to another. */
    ZBExtFileProperties& operator=(const ZBExtFileProperties& propProcess);

    //@cmember
    /* Determines if another set of fill properties is equal to this one. */
    BOOL operator==(const ZBExtFileProperties propProcess) const;

    //@cmember
    /* Makes a copy of this properties object. */
    virtual ZBExtFileProperties* Dup();
    //@cmember
    /* Merges another set of properties with this one. */
    virtual void Merge(ZBExtFileProperties* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL);
    //@cmember
    /* Determines if another set of properties is equal to this one. */
    virtual BOOL IsEqual(ZBExtFileProperties* pProp);

    // Determines if the object is empty
    virtual BOOL IsEmpty() const
    {
        return m_FileTitle.IsEmpty() &&     
               m_Filename.IsEmpty();
    };
    /////////////////////////////////////////////////////////////////////////
    // GetValue and SetValue functions

    //@cmember
    /* Gets the value of the given string property. */
    virtual BOOL GetValue(const int nPropId, CString& strValue) const;
    //@cmember
    /* Gets the value of the given integer property. */
    virtual BOOL GetValue(const int nPropId, int& nValue) const;
    //@cmember
    /* Gets the value of the given unsigned integer property. */
    virtual BOOL GetValue(const int nPropId, UINT& nValue) const;
    //@cmember
    /* Gets the value of the given DWORD property. */
    virtual BOOL GetValue(const int nPropId, DWORD& dwValue) const;
    //@cmember
    /* Gets the value of the given float property. */
    virtual BOOL GetValue(const int nPropId, float& fValue) const;

    //@cmember
    /* Sets the value of the given string property. */
    virtual BOOL SetValue(const int nPropId, LPCTSTR lpszValue);
    //@cmember
    /* Sets the value of the given integer property. */
    virtual BOOL SetValue(const int nPropId, const int nValue);
    //@cmember
    /* Sets the value of the given unsigned integer property. */
    virtual BOOL SetValue(const int nPropId, const UINT nValue);
    //@cmember
    /* Sets the value of the given unsigned DWORD property. */
    virtual BOOL SetValue(const int nPropId, const DWORD dwValue);
    //@cmember
    /* Sets the value of the given float property. */
    virtual BOOL SetValue(const int nPropId, const float fValue);

    //@cmember
    /* Serializes the line properties. */
    virtual void Serialize(CArchive& ar);

    /////////////////////////////////////////////////////////////////////////
    // Internal helper functions subject to change.
private:

    /* Additional mutators for use with CODIntPropertyAccessor */
    void SetFileTitleEx(const CString value);
    void SetFilenameEx(const CString value);
    
// Implementation
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// ZBExtFileProperties inline methods

//@mfunc Gets the task list.
//@rdesc The task list.
inline CString ZBExtFileProperties::GetFileTitle() const
{
    return m_FileTitle;
}

//@mfunc Gets the decision list.
//@rdesc The decision list.
inline CString ZBExtFileProperties::GetFilename() const
{
    return m_Filename;
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline ZBExtFileProperties* ZBExtFileProperties::Dup()
{
    return new ZBExtFileProperties(*this);
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline int ZBExtFileProperties::GetInsertionType() const
{
    return m_InsertionType;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBExtFileProperties::SetInsertionType(const int value)
{
    m_InsertionType = value;
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline int ZBExtFileProperties::GetActivationType() const
{
    return m_ActivationType;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBExtFileProperties::SetActivationType(const int value)
{
    m_ActivationType = value;
}

/////////////////////////////////////////////////////////////////////////////
// ZBExtFileProperties member variable descriptions

/////////////////////////////////////////////////////////////////////////////


#endif // __ZBExtFileProp_H__

/////////////////////////////////////////////////////////////////////////////
