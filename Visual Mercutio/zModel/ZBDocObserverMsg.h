// ZBDocObserverMsg.h: interface for the ZBDocObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBDOCOBSERVERMSG_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBDOCOBSERVERMSG_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\PSS_ObserverMsg.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward declarations
class ZBSymbol;
class PSS_ProcessGraphModelDoc;
class PSS_ProcessGraphModelMdl;

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 21 août 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBDocObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(ZBDocObserverMsg)

public:

    enum MessageActionType
    {
        NoAction,
        OpenDocument,
        CloseDocument,
        ActivateDocument,
        AddElement,
        RemoveElement,
        ChangedElement
    };

public:

    ZBDocObserverMsg(MessageActionType         actionType = NoAction,
                     PSS_ProcessGraphModelDoc* pDoc = NULL,
                     PSS_ProcessGraphModelMdl* pModel = NULL,
                     CODSymbolComponent*       pElement = NULL);

    virtual ~ZBDocObserverMsg();

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

    CODSymbolComponent* GetElement() const
    {
        return m_pElement;
    };

    void SetElement(CODSymbolComponent* value)
    {
        m_pElement = value;
    };

private:
    PSS_ProcessGraphModelDoc* m_pDoc;
    PSS_ProcessGraphModelMdl* m_pModel;
    CODSymbolComponent*       m_pElement;
    MessageActionType         m_ActionType;
};

#endif
