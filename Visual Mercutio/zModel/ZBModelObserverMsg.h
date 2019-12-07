// ZBModelObserverMsg.h: interface for the ZBModelObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBModelObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBModelObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
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
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward declarations
class PSS_ProcessGraphModelDoc;
class PSS_ProcessGraphModelMdl;
class ZDProcessGraphPage;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZBModelObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(ZBModelObserverMsg)
public:
    enum MessageActionType
    {
        NoAction, RedrawElement, RedrawElementSet, RemoveElement, RemoveElementSet, AddElement, AddElementSet, BrowseElement, EnsureElementVisible, SelectElement
    };

public:
    ZBModelObserverMsg(MessageActionType ActionType = NoAction, PSS_ProcessGraphModelDoc* pDoc = NULL, PSS_ProcessGraphModelMdl* pModel = NULL, CODComponent* pElement = NULL);
    ZBModelObserverMsg(MessageActionType ActionType, PSS_ProcessGraphModelDoc* pDoc, PSS_ProcessGraphModelMdl* pModel, ZDProcessGraphPage* pPage);
    ZBModelObserverMsg(MessageActionType ActionType, PSS_ProcessGraphModelDoc* pDoc, PSS_ProcessGraphModelMdl* pModel, CODComponentSet* pElementSet);
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

    PSS_ProcessGraphModelMdl* GetModel() const
    {
        return m_pModel;
    };
    void SetModel(PSS_ProcessGraphModelMdl* value)
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
    PSS_ProcessGraphModelMdl* m_pModel;
    CODComponent*             m_pElement;
    CODComponentSet*          m_pElementSet;
    ZDProcessGraphPage*       m_pPage;
};

#endif
