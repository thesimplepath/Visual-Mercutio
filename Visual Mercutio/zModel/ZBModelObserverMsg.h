// ZBModelObserverMsg.h: interface for the ZBModelObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBModelObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBModelObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

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

// processsoft
#include "zBaseLib\PSS_ObserverMsg.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// forward declarations
class PSS_ProcessGraphModelDoc;
class ZDProcessGraphModelMdl;
class ZDProcessGraphPage;

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


class AFX_EXT_CLASS ZBModelObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(ZBModelObserverMsg)
public:
    enum MessageActionType
    {
        NoAction, RedrawElement, RedrawElementSet, RemoveElement, RemoveElementSet, AddElement, AddElementSet, BrowseElement, EnsureElementVisible, SelectElement
    };

public:
    ZBModelObserverMsg(MessageActionType ActionType = NoAction, PSS_ProcessGraphModelDoc* pDoc = NULL, ZDProcessGraphModelMdl* pModel = NULL, CODComponent* pElement = NULL);
    ZBModelObserverMsg(MessageActionType ActionType, PSS_ProcessGraphModelDoc* pDoc, ZDProcessGraphModelMdl* pModel, ZDProcessGraphPage* pPage);
    ZBModelObserverMsg(MessageActionType ActionType, PSS_ProcessGraphModelDoc* pDoc, ZDProcessGraphModelMdl* pModel, CODComponentSet* pElementSet);
    virtual ~ZBModelObserverMsg();

    MessageActionType GetActionType() const
    {
        return m_ActionType;
    };
    void SetActionType(MessageActionType value)
    {
        m_ActionType = value;
    };

    PSS_ProcessGraphModelDoc* GetDoc() const
    {
        return m_pDoc;
    };
    void SetDoc(PSS_ProcessGraphModelDoc* value)
    {
        m_pDoc = value;
    };

    ZDProcessGraphModelMdl* GetModel() const
    {
        return m_pModel;
    };
    void SetModel(ZDProcessGraphModelMdl* value)
    {
        m_pModel = value;
    };

    CODComponent* GetElement() const
    {
        return m_pElement;
    };
    void SetElement(CODComponent* value)
    {
        m_pElement = value;
    };

    CODComponentSet* GetElementSet() const
    {
        return m_pElementSet;
    };
    void SetElementSet(CODComponentSet* value)
    {
        m_pElementSet = value;
    };

    ZDProcessGraphPage* GetPage() const
    {
        return m_pPage;
    };
    void SetPage(ZDProcessGraphPage* value)
    {
        m_pPage = value;
    };

private:
    MessageActionType         m_ActionType;
    PSS_ProcessGraphModelDoc* m_pDoc;
    ZDProcessGraphModelMdl*   m_pModel;
    CODComponent*             m_pElement;
    CODComponentSet*          m_pElementSet;
    ZDProcessGraphPage*       m_pPage;
};

#endif
