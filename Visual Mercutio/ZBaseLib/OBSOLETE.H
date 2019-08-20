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


#if !defined(__OBSOLETE_H)
#define __OBSOLETE_H


#ifdef _AFXEXT
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
#endif



#include "zamath.h"

//#include <FLOAT.H>
//#include <MATH.H>

#include "planfobj.h"
#include "ZAObject.h"
#include "ZAText.h"
#include "ZAString.h"
#include "ZAGraphc.h"
#include "PSS_Formula.h"

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


class AFX_EXT_CLASS PLFNStringHistory : public PLFNString
{
public:
// Inherited feature
    typedef PLFNString inherited;
public:
    PLFNStringHistory();
    PLFNStringHistory(const PLFNStringHistory &right);
    const PLFNStringHistory & operator=(const PLFNStringHistory *right);
    const PLFNStringHistory & operator=(const PLFNStringHistory &right);
    //    Make a clone of the object.
    virtual PlanFinObject* Clone();
    virtual void CopyObject(PlanFinObject* pSrc);


    void    GetContains( CString& strLine );
    virtual BOOL     IsSelected( const CPoint& point ) const;

//    virtual CStringArray&    GetInitialChoice();

// Member Data
public:

// Implementation
protected:
    DECLARE_SERIAL(PLFNStringHistory)
    virtual ~PLFNStringHistory();

// Implementation
public:
    virtual void     Serialize(CArchive& ar);      // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};


class AFX_EXT_CLASS PLFNNumbered : public PLFNStatic
{
public:
// Inherited feature
    typedef PLFNStatic inherited;
public:
    PLFNNumbered();
    PLFNNumbered(const PLFNNumbered &right);
    const PLFNNumbered & operator=(const PLFNNumbered *right);
    const PLFNNumbered & operator=(const PLFNNumbered &right);
    //    Make a clone of the object.
    virtual PlanFinObject* Clone();
    virtual void CopyObject(PlanFinObject* pSrc);
    //    Return the list of tabs that should be displayed when
    //    the user asks for object properties.
    virtual UINT GetPropertyTabs () const;

// Member Data
public:
    int            m_iChapter;            // The number of the paragraph
    int            m_iParagraph;
// Implementation
protected:
    DECLARE_SERIAL(PLFNNumbered)
    virtual ~PLFNNumbered();
    virtual    void DrawObject(CDC* pDC, ZIView* pView);        // overridden to draw this object
    
// Implementation
public:
    virtual void     Serialize(CArchive& ar);      // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};
 
inline UINT PLFNNumbered::GetPropertyTabs () const
{
      return PropertyGeneralStaticPage | PropertySizePage;
}
 


class AFX_EXT_CLASS PLFNNumbEdit : public PLFNString
{
public:
// Inherited feature
    typedef PLFNString inherited;
friend class PLFNNumbered;
public:
    PLFNNumbEdit();
    PLFNNumbEdit(const PLFNNumbEdit &right);
    const PLFNNumbEdit & operator=(const PLFNNumbEdit *right);
    const PLFNNumbEdit & operator=(const PLFNNumbEdit &right);
    //    Make a clone of the object.
    virtual PlanFinObject* Clone();
    virtual void CopyObject(PlanFinObject* pSrc);
    //    Return the list of tabs that should be displayed when
    //    the user asks for object properties.
    virtual UINT GetPropertyTabs () const;

// Member Data
public:
    int            m_iChapter;            // The number of the paragraph
    int            m_iParagraph;
// Implementation
protected:
    DECLARE_SERIAL(PLFNNumbEdit)
    virtual ~PLFNNumbEdit();
    virtual    void DrawObject(CDC* pDC, ZIView* pView);        // overridden to draw this object
    
// Implementation
public:
    virtual void     Serialize(CArchive& ar);      // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};

inline UINT PLFNNumbEdit::GetPropertyTabs () const
{
      return PropertyGeneralStaticPage | PropertySizePage;
}
 

// Valid only in version -1 and 0
// After in version 1 it has been replaced
// by the PLFNLong with a flag
class AFX_EXT_CLASS PLFNCalculated : public PLFNLong
{
public:
// Inherited feature
    typedef PLFNLong inherited;
public:
    PLFNCalculated();
    PLFNCalculated(const PLFNCalculated &right);
    const PLFNCalculated & operator=(const PLFNCalculated *right);
    const PLFNCalculated & operator=(const PLFNCalculated &right);
    //    Make a clone of the object.
    virtual PlanFinObject* Clone();
    virtual void CopyObject(PlanFinObject* pSrc);


//    virtual BOOL    IsEmpty() const { return( FALSE ); };    // The calculated field are never empty.

    virtual    CString    GetFormatedObject( );

    virtual void     Recalculate(ZDDocument* pDoc);

private:
// Implementation
protected:
    DECLARE_SERIAL(PLFNCalculated)
    virtual ~PLFNCalculated();
    
// Implementation
public:
    virtual void     Serialize(CArchive& ar);      // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};




class AFX_EXT_CLASS PLFNNumHistory : public PLFNLong
{
public:
// Inherited feature
    typedef PLFNLong inherited;
public:
    PLFNNumHistory();
    PLFNNumHistory(const PLFNNumHistory &right);
    const PLFNNumHistory & operator=(const PLFNNumHistory *right);
    const PLFNNumHistory & operator=(const PLFNNumHistory &right);
    //    Make a clone of the object.
    virtual PlanFinObject* Clone();
    virtual void CopyObject(PlanFinObject* pSrc);
    
    
    void    GetContains( CString& strLine );
    virtual BOOL     IsSelected( const CPoint& point ) const;
    //    Return the list of tabs that should be displayed when
    //    the user asks for object properties.
    virtual UINT GetPropertyTabs () const;

//    virtual CStringArray&    GetInitialChoice();

// Member Data
public:

// Implementation
protected:
    DECLARE_SERIAL(PLFNNumHistory)
    virtual ~PLFNNumHistory();

// Implementation
public:
    virtual void     Serialize(CArchive& ar);      // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};

inline UINT PLFNNumHistory::GetPropertyTabs () const
{
      return PropertyGeneralStaticPage | PropertySizePage;
}



class AFX_EXT_CLASS PLFNNumbNumEdit : public PLFNLong
{
public:
// Inherited feature
    typedef PLFNLong inherited;
friend class PLFNNumbered;
public:
    PLFNNumbNumEdit();
    PLFNNumbNumEdit(const PLFNNumbNumEdit &right);
    const PLFNNumbNumEdit & operator=(const PLFNNumbNumEdit *right);
    const PLFNNumbNumEdit & operator=(const PLFNNumbNumEdit &right);
    //    Make a clone of the object.
    virtual PlanFinObject* Clone();
    virtual void CopyObject(PlanFinObject* pSrc);
    //    Return the list of tabs that should be displayed when
    //    the user asks for object properties.
    virtual UINT GetPropertyTabs () const;
    
// Member Data
public:
    int            m_iChapter;            // The number of the paragraph
    int            m_iParagraph;
// Implementation
protected:
    DECLARE_SERIAL(PLFNNumbNumEdit)
    virtual ~PLFNNumbNumEdit();
    virtual    void DrawObject(CDC* pDC, ZIView* pView);        // overridden to draw this object
    
// Implementation
public:
    virtual void     Serialize(CArchive& ar);      // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};

 
inline UINT PLFNNumbNumEdit::GetPropertyTabs () const
{
      return PropertyGeneralStaticPage | PropertySizePage;
}




#endif // __OBSOLETE_H

