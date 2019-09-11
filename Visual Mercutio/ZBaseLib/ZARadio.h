//## begin module%336D05E0032A.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%336D05E0032A.cm

//## begin module%336D05E0032A.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%336D05E0032A.cp

//## Module: ZARadio%336D05E0032A; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZARadio.h

#ifndef ZARadio_h
#define ZARadio_h 1

//## begin module%336D05E0032A.additionalIncludes preserve=no
//## end module%336D05E0032A.additionalIncludes

//## begin module%336D05E0032A.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%336D05E0032A.includes

// ZATwoSts
#include "ZATwoSts.h"
//## begin module%336D05E0032A.declarations preserve=no
//## end module%336D05E0032A.declarations

//## begin module%336D05E0032A.additionalDeclarations preserve=yes
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
//## end module%336D05E0032A.additionalDeclarations


//## Class: PLFNRadio%336D05C30096
//    Manage the radio button.
//## Category: ZBaseLib::Base objects%37E9429A0111
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS PLFNRadio : public PLFNTwoStates  //## Inherits: <unnamed>%336D05CE03C0
{
    DECLARE_SERIAL(PLFNRadio)

public:
    typedef PLFNTwoStates inherited;

    PLFNRadio();

    PLFNRadio(const PLFNRadio &right);

    virtual ~PLFNRadio();

    //## Assignment Operation (generated)
    const PLFNRadio & operator=(const PLFNRadio &right);

    //## Other Operations (specified)
      //## Operation: operator =%862783357
      //    A copy constructor with a pointer.
    const PLFNRadio& operator = (const PLFNRadio* right);

    //## Operation: Clone%862783361
    //    Make a clone of the object.
    virtual PSS_PlanFinObject* Clone() const ;

    //## Operation: DrawObject%862783363
    //    Draw the object with the current DC.
    virtual void DrawObject(CDC* pDC, ZIView* pView);

    //## Operation: EditObject%862847762
    //    Edit the object.
    void EditObject(CWnd* pParentWnd, CDC* pDC, ZDDocument* pDoc);

    //## Operation: IsSelected%863265785
    //    Is this object selected.
    virtual BOOL IsSelected(const CPoint& point) const;

    //## Operation: CopyObject%863615078
    virtual void CopyObject(PSS_PlanFinObject* pSrc);

    //## Operation: GetPropertyTabs%885128489
    //    Return the list of tabs that should be displayed when
    //    the user asks for object properties.
    virtual UINT GetPropertyTabs() const;

    //## Operation: Serialize%862783362
    //    Serialization function required for MFC mecanism.
    virtual void Serialize(CArchive& ar);

    // Additional Public Declarations
      //## begin PLFNRadio%336D05C30096.public preserve=yes
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};

inline BOOL PLFNRadio::IsSelected(const CPoint& point) const
{
    return(m_ObjectRect.PtInRect(point));
}
inline UINT PLFNRadio::GetPropertyTabs() const
{
    return (g_PropertyGeneralBasicPage | g_PropertySizePage | g_PropertyRadioPage);
}

#endif
