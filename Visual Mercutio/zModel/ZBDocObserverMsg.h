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

#include "zBaseLib\ZIObserverMsg.h"

// forward declarations
class ZBSymbol;
class ZDProcessGraphModelDoc;
class ZDProcessGraphModelMdl;

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

class AFX_EXT_CLASS ZBDocObserverMsg : public ZIObserverMsg
{
    DECLARE_DYNAMIC( ZBDocObserverMsg )

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

    ZBDocObserverMsg( MessageActionType            ActionType    = NoAction,
                      ZDProcessGraphModelDoc*    pDoc        = NULL,
                      ZDProcessGraphModelMdl*    pModel        = NULL,
                      CODSymbolComponent*        pElement    = NULL );

    virtual ~ZBDocObserverMsg();

    MessageActionType GetActionType() const
    {
        return m_ActionType;
    };

    void SetActionType( MessageActionType value )
    {
        m_ActionType = value;
    };

    ZDProcessGraphModelDoc* GetpDoc() const
    {
        return m_pDoc;
    };

    void SetpDoc( ZDProcessGraphModelDoc* value )
    {
        m_pDoc = value;
    };

    ZDProcessGraphModelMdl* GetpModel() const
    {
        return m_pModel;
    };

    void SetpModel( ZDProcessGraphModelMdl* value )
    {
        m_pModel = value;
    };

    CODSymbolComponent* GetpElement() const
    {
        return m_pElement;
    };

    void SetpElement( CODSymbolComponent* value )
    {
        m_pElement = value;
    };

private:

    MessageActionType            m_ActionType;
    ZDProcessGraphModelDoc*        m_pDoc;
    ZDProcessGraphModelMdl*        m_pModel;
    CODSymbolComponent*            m_pElement;
};

#endif // !defined(AFX_ZBDOCOBSERVERMSG_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)