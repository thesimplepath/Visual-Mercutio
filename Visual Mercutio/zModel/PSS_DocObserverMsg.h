/****************************************************************************
 * ==> PSS_DocObserverMsg --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a document observer message                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DocObserverMsgH
#define PSS_DocObserverMsgH

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
#ifndef PSS_Symbol
    #define PSS_Symbol ZBSymbol
#endif
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward declarations
class PSS_Symbol;
class PSS_ProcessGraphModelDoc;
class PSS_ProcessGraphModelMdl;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Document observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DocObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(PSS_DocObserverMsg)

    public:
        /**
        * Message action type
        */
        enum IEActionType
        {
            IE_AT_No,
            IE_AT_OpenDocument,
            IE_AT_CloseDocument,
            IE_AT_ActivateDocument,
            IE_AT_AddElement,
            IE_AT_RemoveElement,
            IE_AT_ChangedElement
        };

        /**
        * Constructor
        *@param actionType - the action type
        *@param pDoc - the document
        *@param pModel - the model
        *@param pElement - the element
        */
        PSS_DocObserverMsg(IEActionType              actionType = IE_AT_No,
                           PSS_ProcessGraphModelDoc* pDoc       = NULL,
                           PSS_ProcessGraphModelMdl* pModel     = NULL,
                           CODSymbolComponent*       pElement   = NULL);

        virtual ~PSS_DocObserverMsg();

        /**
        * Gets the action type
        *@return the action type
        */
        virtual inline IEActionType GetActionType() const;

        /**
        * Sets the action type
        *@param value - the action type
        */
        virtual inline void SetActionType(IEActionType value);

        /**
        * Gets the document
        *@return the document
        */
        virtual inline PSS_ProcessGraphModelDoc* GetDoc() const;

        /**
        * Sets the document
        *@param pDoc - the document
        */
        virtual inline void SetDoc(PSS_ProcessGraphModelDoc* pDoc);

        /**
        * Gets the model
        *@return the model
        */
        virtual inline PSS_ProcessGraphModelMdl* GetModel() const;

        /**
        * Sets the model
        *@param pModel - the model
        */
        virtual inline void SetModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Gets the element
        *@return the element
        */
        virtual inline CODSymbolComponent* GetElement() const;

        /**
        * Sets the element
        *@param pElement - the element
        */
        virtual inline void SetElement(CODSymbolComponent* pElement);

    private:
        IEActionType              m_ActionType;
        PSS_ProcessGraphModelDoc* m_pDoc;
        PSS_ProcessGraphModelMdl* m_pModel;
        CODSymbolComponent*       m_pElement;
};

//---------------------------------------------------------------------------
// PSS_DocObserverMsg
//---------------------------------------------------------------------------
PSS_DocObserverMsg::IEActionType PSS_DocObserverMsg::GetActionType() const
{
    return m_ActionType;
}
//---------------------------------------------------------------------------
void PSS_DocObserverMsg::SetActionType(IEActionType value)
{
    m_ActionType = value;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelDoc* PSS_DocObserverMsg::GetDoc() const
{
    return m_pDoc;
}
//---------------------------------------------------------------------------
void PSS_DocObserverMsg::SetDoc(PSS_ProcessGraphModelDoc* pDoc)
{
    m_pDoc = pDoc;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_DocObserverMsg::GetModel() const
{
    return m_pModel;
}
//---------------------------------------------------------------------------
void PSS_DocObserverMsg::SetModel(PSS_ProcessGraphModelMdl* pModel)
{
    m_pModel = pModel;
}
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_DocObserverMsg::GetElement() const
{
    return m_pElement;
}
//---------------------------------------------------------------------------
void PSS_DocObserverMsg::SetElement(CODSymbolComponent* pElement)
{
    m_pElement = pElement;
}
//---------------------------------------------------------------------------

#endif
