//---------------------------------------------------------------------------
// Author    : Dominique Aigroz            
// HeaderFile: planfobj.h
// Created   : 14.12.1994
// Modify    :           
//
//
// Call      : 
//
//---------------------------------------------------------------------------


#if !defined(__PLANFOBJ_H)
#define __PLANFOBJ_H

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#include "zaconst.h"
#include "zamath.h"

#include <FLOAT.H>
#include <MATH.H>

#include "ZAObject.h"
#include "ZAText.h"
#include "ZAString.h"
#include "ZAGraphc.h"
#include "Formula.h"
#include "ZBPoint.h"
#include "ZBDate.h"



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


// This is the Rect object
class AFX_EXT_CLASS PLFNRect : public PLFNGraphic
{
public:
// Inherited feature
    typedef PLFNGraphic inherited;
public:
    PLFNRect(const PLFNRect &right);
    const PLFNRect & operator=(const PLFNRect *right);
    const PLFNRect & operator=(const PLFNRect &right);
    PLFNRect( BOOL bRound = FALSE );
    WORD    GetArcOffset() const { return m_ArcOffset; };
    void    SetArcOffset( const WORD value ) { m_ArcOffset = value; };
    BOOL    IsRounded() const { return m_bRound; };
    void    SetRounded( BOOL bValue ) { m_bRound = bValue; };
    
    //    Make a clone of the object.
    virtual PlanFinObject* Clone();
    virtual void CopyObject(PlanFinObject* pSrc);

    virtual BOOL IsHint(CPoint& point) const;

    //    Return the list of tabs that should be displayed when
    //    the user asks for object properties.
    virtual UINT GetPropertyTabs() const;

private:
    BOOL    m_bRound;
    WORD    m_ArcOffset;
// Implementation
protected:
    DECLARE_SERIAL(PLFNRect)
    virtual ~PLFNRect();
    virtual    void DrawObject(CDC* pDC, ZIView* pView);        // overridden to draw this object
    
// Implementation
public:
    virtual void     Serialize(CArchive& ar);      // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};

inline BOOL PLFNRect::IsHint(CPoint& point) const
{
      // Copy the object rectangle and inflate it by -3, -3
      // This operation to test if the cursor is on the rectangle
      // but not inside
      CRect    MinRect = m_rctObject;
      CRect    MaxRect = m_rctObject;
      MinRect.InflateRect( -3, -3 );
      MaxRect.InflateRect( 3, 3 );
      if (MaxRect.PtInRect( point ) && !MinRect.PtInRect( point ))
          return TRUE;
    return FALSE;
}
 

inline UINT PLFNRect::GetPropertyTabs() const
{
      return PropertyGeneralBasicPage | PropertySizePage | PropertyGraphicPage | PropertyRectPage;
}


// This is the line object
class AFX_EXT_CLASS PLFNLine : public PLFNGraphic
{
public:
// Inherited feature
    typedef PLFNGraphic inherited;
public:
    PLFNLine();
    PLFNLine(const PLFNLine &right);
    const PLFNLine & operator=(const PLFNLine *right);
    const PLFNLine & operator=(const PLFNLine &right);
    //    Make a clone of the object.
    virtual PlanFinObject* Clone();
    virtual void CopyObject(PlanFinObject* pSrc);
    
    const    CPoint&    GetStartPoint() const;
    const    CPoint&    GetEndPoint() const;
    void    SetStartPoint( const CPoint& value );
    void    SetEndPoint( const CPoint& value );

    //    Notify when the object size and/or position has changed.
    virtual void SizePositionHasChanged();

    //    Return the list of tabs that should be displayed when
    //    the user asks for object properties.
    virtual UINT GetPropertyTabs() const;
    
    virtual BOOL IsHint(CPoint& point) const;
// Implementation
protected:
    DECLARE_SERIAL(PLFNLine)
    virtual ~PLFNLine();
    virtual    void DrawObject(CDC* pDC, ZIView* pView);        // overridden to draw this object
      
private:
    ZBPoint    m_StartPoint;
    ZBPoint    m_EndPoint;      
// Implementation
public:
    virtual void     Serialize(CArchive& ar);      // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};


inline const    CPoint&    PLFNLine::GetStartPoint() const 
{ 
    return m_StartPoint; 
}

inline const    CPoint&    PLFNLine::GetEndPoint() const 
{ 
    return m_EndPoint; 
}

inline void                PLFNLine::SetStartPoint( const CPoint& value ) 
{ 
    m_StartPoint = value; 
}

inline void                PLFNLine::SetEndPoint( const CPoint& value ) 
{ 
    m_EndPoint = value; 
}
 
inline BOOL PLFNLine::IsHint(CPoint& point) const
{
      // Copy the object rectangle and inflate it by 3, 3
      // This operation to test if the cursor is on the line
      // because line are very small
      CRect    rect = m_rctObject;
      rect.InflateRect( 3, 3 );
      if (rect.PtInRect( point ))
          return TRUE;
    return FALSE;
}


inline UINT PLFNLine::GetPropertyTabs() const
{
      return PropertyGeneralBasicPage | PropertySizePage | PropertyGraphicPage;
}

                                        
class AFX_EXT_CLASS PLFNStatic : public PLFNText
{
public:
// Inherited feature
    typedef PLFNText inherited;
public:
    PLFNStatic();
    PLFNStatic(const PLFNStatic &right);
    const PLFNStatic & operator=(const PLFNStatic *right);
    const PLFNStatic & operator=(const PLFNStatic &right);
    //    Make a clone of the object.
    virtual PlanFinObject* Clone();
    virtual void CopyObject(PlanFinObject* pSrc);

    //    Return the list of tabs that should be displayed when
    //    the user asks for object properties.
    virtual UINT GetPropertyTabs () const;

// Implementation
protected:
    DECLARE_SERIAL(PLFNStatic)
    virtual ~PLFNStatic();
    virtual    void DrawObject(CDC* pDC, ZIView* pView);        // overridden to draw this object
    //    When the angle has changed, this function is called.
    virtual void OnAngleChanged(ZDDocument* pDoc);
};



 
inline UINT PLFNStatic::GetPropertyTabs () const
{
      return PropertyGeneralStaticPage | PropertySizePage;
}


 
class AFX_EXT_CLASS PLFNTime : public PLFNAscii
{
public:
// Inherited feature
    typedef PLFNAscii inherited;
public:
    PLFNTime();
    PLFNTime(const PLFNTime &right);
    const PLFNTime & operator=(const PLFNTime *right);
    const PLFNTime & operator=(const PLFNTime &right);
    //    Make a clone of the object.
    virtual PlanFinObject* Clone();
    virtual void CopyObject(PlanFinObject* pSrc);
    virtual const BOOL GetIsStatic () const { return FALSE; };

    //    This function empties the object.
    virtual BOOL     IsSelected( const CPoint& point ) const;

#ifdef _WIN32
    void                    SetToday(){ m_Time = ZBDate::GetToday(); };
    virtual void            SetTimeValue( ZBDate tm );
    virtual ZBDate             GetTimeValue(){return(m_Time);};
#endif

    virtual void   *GetObjectAdress() const {return((void*)&m_Time);};

    virtual    CString    GetFormatedObject( );
    //    Return an unformated string of the object image.
    virtual CString GetUnformatedObject();
    
    virtual    BOOL    ConvertFormatedObject( const CString& sValue, BOOL bLocateFormat = TRUE, BOOL EmptyWhenZero = FALSE );

//    virtual CStringArray&    GetInitialChoice();
    virtual CStringArray&    GetFormatChoice();
    virtual void            SetFormatWithChoice( const CString& sValue );

    //    Return the number of the submenu when the user click the
    //    right mouse button.
    virtual UINT GetRightSubMenu() const { return g_DateRightSubMenu; };
    
    //    Return the list of tabs that should be displayed when
    //    the user asks for object properties.
    virtual UINT GetPropertyTabs () const;

// Member Data
public:
    ZBDate    m_Time;

    // Implementation
protected:
    DECLARE_SERIAL(PLFNTime)
    virtual ~PLFNTime();
    virtual    void DrawObject(CDC* pDC, ZIView* pView);        // overridden to draw this object
    
// Implementation
public:
    virtual void     Serialize(CArchive& ar);      // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};

inline void    PLFNTime::SetTimeValue(ZBDate tm)
{
    m_Time = tm;
    ClearEmptyObjectFlag();      
}

inline UINT PLFNTime::GetPropertyTabs () const
{
      return PropertyGeneralDatePage | PropertySizePage;
}

enum IconDisplayType
{
    NoIcon,
    AssociationIcon,
};


class AFX_EXT_CLASS PLFNLong : public PLFNAscii
{
public:
// Inherited feature
    typedef PLFNAscii inherited;
public:
    PLFNLong();
    PLFNLong(const PLFNLong &right);
    const PLFNLong & operator=(const PLFNLong *right);
    const PLFNLong & operator=(const PLFNLong &right);
    //    Make a clone of the object.
    virtual PlanFinObject* Clone();
    virtual void CopyObject(PlanFinObject* pSrc);

    virtual const BOOL GetIsStatic () const { return FALSE; };

    virtual UINT GetRightSubMenu() const;

    //    Return the list of tabs that should be displayed when
    //    the user asks for object properties.
    virtual UINT GetPropertyTabs() const;

    void    GetContains( CString& strLine );
    virtual BOOL     IsSelected( const CPoint& point ) const;

    virtual void   *GetObjectAdress() const {return ((void*)&m_Long);};

    virtual double     GetValue() const;
    virtual double     GetRealValue() const{ return m_Long; };
    virtual void    SetValue( double dValue );

    virtual    CString    GetFormatedObject( );
    //    Return an unformated string of the object image.
    virtual CString GetUnformatedObject();
    
    virtual    BOOL    ConvertFormatedObject( const CString& sValue, BOOL bLocateFormat = TRUE, BOOL EmptyWhenZero = FALSE );
    virtual void    SetFormatWithChoice( const CString& sValue );

    virtual CStringArray&    GetFormatChoice();
    
    virtual void     Recalculate(ZDDocument*    pDoc);
    
    BOOL            IsRounded() const { return m_IsRounded; };
    void            SetRounded( BOOL value = TRUE ) { m_IsRounded = value; }
    
    double            GetRoundedValue() const { return m_dRounded; };
    void            SetRoundedValue( double value ) { m_dRounded = value; };

    BOOL            IsCalculatedField() const { return m_bIsCalculatedField; };
    void            SetCalculatedField( BOOL bValue = TRUE ){ m_bIsCalculatedField = bValue; };
    BOOL            KeepTheValue() const { return m_bKeepTheValue; };
    void            SetKeepTheValue( BOOL bValue = TRUE ){ m_bKeepTheValue = bValue; };
    
    // Icon display type
    void            SetIconDisplayType( IconDisplayType Type = NoIcon ) { m_IconDisplayType = Type; };
    
    // Associations
    ZAFormulaAssociationManager&    GetAssociations() { return m_Associations; };
    ZAFormulaAssociation*    GetCurrentAssociation() { return m_Associations.GetCurrentAssociation(); };
    void                    ClearCurrentAssociation() { m_Associations.ClearCurrentAssociation(); };
    void                    SetCurrentAssociation( ZAFormulaAssociation* pAssociation ) { m_Associations.SetCurrentAssociation(pAssociation); };
    void                    SetCurrentAssociation( const CString Name ) { m_Associations.SetCurrentAssociation(Name); };

    // Draw the calculated symbol for the object.
    virtual void DrawCalculatedSymbol (CDC* pDC);

// Member Data
public:
    double            m_Long;                // The long object
private:
    BOOL            m_bIsCalculatedField;
    BOOL            m_bKeepTheValue;
    BOOL            m_IsRounded;        // Defines if the field is rounded.
    double            m_dRounded;            // The rounded value
    
    IconDisplayType    m_IconDisplayType;    // Defines the icon display type
    
    // Since file version 5
    ZAFormulaAssociationManager    m_Associations;    // The Associations
    
// Implementation
protected:
    DECLARE_SERIAL(PLFNLong)
    virtual ~PLFNLong();
    virtual    void DrawObject(CDC* pDC, ZIView* pView);        // overridden to draw this object
    
// Implementation
public:
    virtual void     Serialize(CArchive& ar);      // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};


inline     void    PLFNLong::SetValue( double dValue )
{ 
    m_Long = dValue; 
    if (IsCalculatedField())
        SetHasBeenChanged( TRUE ); 
    ClearEmptyObjectFlag();      
}



// Return the object value
inline double PLFNLong::GetValue( ) const
{
    return m_Long;
}

inline UINT PLFNLong::GetRightSubMenu() const
{
    if (IsCalculatedField())
        return g_CalculatedRightSubMenu;

    return g_NumberRightSubMenu;
}

inline UINT PLFNLong::GetPropertyTabs() const
{
      return (IsCalculatedField()) ? PropertyGeneralBasicPage | PropertySizePage | PropertyLongPage : PropertyGeneralTextPage | PropertySizePage;
}

inline     BOOL     PLFNLong::IsSelected( const CPoint& point ) const
{
    return( m_rctObject.PtInRect( point ) );
}
                






#endif // __PLANFOBJ_H

