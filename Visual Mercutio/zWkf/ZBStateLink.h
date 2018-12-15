/////////////////////////////////////////////////////////////////////////////
//@doc ZBStateLink
//@module ZBStateLink.h | Interface of the <c ZBStateLink> class.
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
// <nl>Created:         06/2001
// <nl>Description:  ZBStateLink link state object class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBStateLink_H__25BFD0A3_6A6B_4D54_A479_E70548004E60__INCLUDED_)
#define AFX_ZBStateLink_H__25BFD0A3_6A6B_4D54_A479_E70548004E60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "AutomationCollections.h"
#include "zModel\ZBLinkSymbol.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZDProcessGraphModelMdl;


#ifdef _ZWKFEXPORT
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


class AFX_EXT_CLASS ZBStateLink : public CObject  
{
    DECLARE_SERIAL(ZBStateLink)
public:
    enum LinkDirection { EnteringUp, EnteringLeft, EnteringRight, EnteringDown,
                         LeavingUp, LeavingLeft, LeavingRight, LeavingDown,
                         UnknownDirection };
public:
    ZBStateLink(ZBLinkSymbol* pLinkSymbol = NULL, LinkDirection Direction = EnteringUp, ZDProcessGraphModelMdl* pModel = NULL);
    virtual ~ZBStateLink();
    /* Copy constructor. */
    ZBStateLink(const ZBStateLink& src);
    /* Assignment operator. */
    ZBStateLink& operator=(const ZBStateLink& src);
    /* Create a duplicate copy of this object. */
    virtual ZBStateLink* Clone() const;

    void AssignModel( ZDProcessGraphModelMdl* pModel )
    {
        m_pModel = pModel;
    };

    ZBLinkSymbol* GetpLinkSymbol() const;
    void SetpLinkSymbol( ZBLinkSymbol* value );

    LinkDirection GetDirection() const;
    void SetDirection( LinkDirection value );

    // Return true if the object is equal
    bool IsEqual( const ZBStateLink& Right );
    // Return true if the object is equal to the link symbol
    bool IsEqual( const ZBLinkSymbol& LinkSymbol );

    // Serialization mechanism
    virtual void Serialize(CArchive& ar);   // overridden for document i/o

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

private:
    ZBLinkSymbol* m_pLinkSymbol;
    LinkDirection m_Direction;
    ZDProcessGraphModelMdl* m_pModel;

};


inline ZBLinkSymbol* ZBStateLink::GetpLinkSymbol() const 
{
    return m_pLinkSymbol;
}
inline void ZBStateLink::SetpLinkSymbol( ZBLinkSymbol* value )
{
    m_pLinkSymbol = value;
}

inline ZBStateLink::LinkDirection ZBStateLink::GetDirection() const 
{
    return m_Direction;
}
inline void ZBStateLink::SetDirection( ZBStateLink::LinkDirection value )
{
    m_Direction = value;
}

#endif // !defined(AFX_ZBStateLink_H__25BFD0A3_6A6B_4D54_A479_E70548004E60__INCLUDED_)




