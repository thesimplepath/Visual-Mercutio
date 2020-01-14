/****************************************************************************
 * ==> PSS_ModelObserverMsg ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a model observer message                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ModelObserverMsgH
#define PSS_ModelObserverMsgH

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
#ifndef PSS_ProcessGraphPage
    #define PSS_ProcessGraphPage ZDProcessGraphPage
#endif

// forward declarations
class PSS_ProcessGraphModelDoc;
class PSS_ProcessGraphModelMdl;
class PSS_ProcessGraphPage;

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
* Logical system observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ModelObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(PSS_ModelObserverMsg)

    public:
        /**
        * Action type
        */
        enum IEActionType
        {
            IE_AT_None,
            IE_AT_RedrawElement,
            IE_AT_RedrawElementSet,
            IE_AT_RemoveElement,
            IE_AT_RemoveElementSet,
            IE_AT_AddElement,
            IE_AT_AddElementSet,
            IE_AT_BrowseElement,
            IE_AT_EnsureElementVisible,
            IE_AT_SelectElement
        };

        /**
        * Constructor
        *@param actionType - the action type
        *@param pDoc - the model document
        *@param pModel - the model
        *@param pElement - the element
        */
        PSS_ModelObserverMsg(IEActionType              actionType = IE_AT_None,
                             PSS_ProcessGraphModelDoc* pDoc       = NULL,
                             PSS_ProcessGraphModelMdl* pModel     = NULL,
                             CODComponent*             pElement   = NULL);

        /**
        * Constructor
        *@param actionType - the action type
        *@param pDoc - the model document
        *@param pModel - the model
        *@param pPage - the model page
        */
        PSS_ModelObserverMsg(IEActionType              actionType,
                             PSS_ProcessGraphModelDoc* pDoc,
                             PSS_ProcessGraphModelMdl* pModel,
                             PSS_ProcessGraphPage*     pPage);

        /**
        * Constructor
        *@param actionType - the action type
        *@param pDoc - the model document
        *@param pModel - the model
        *@param pElementSet - the element set
        */
        PSS_ModelObserverMsg(IEActionType              actionType,
                             PSS_ProcessGraphModelDoc* pDoc,
                             PSS_ProcessGraphModelMdl* pModel,
                             CODComponentSet*          pElementSet);

        virtual ~PSS_ModelObserverMsg();

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
        virtual inline CODComponent* GetElement() const;

        /**
        * Sets the element
        *@param pElement - the element
        */
        virtual inline void SetElement(CODComponent* pElement);

        /**
        * Gets the element set
        *@return the element set
        */
        virtual inline CODComponentSet* GetElementSet() const;

        /**
        * Sets the element set
        *@param pSet - the element set
        */
        virtual inline void SetElementSet(CODComponentSet* pSet);

        /**
        * Gets the page
        *@return the page
        */
        virtual inline PSS_ProcessGraphPage* GetPage() const;

        /**
        * Sets the page
        *@param pPage - the page
        */
        virtual inline void SetPage(PSS_ProcessGraphPage* pPage);

    private:
        PSS_ProcessGraphModelDoc* m_pDoc;
        PSS_ProcessGraphModelMdl* m_pModel;
        PSS_ProcessGraphPage*     m_pPage;
        CODComponent*             m_pElement;
        CODComponentSet*          m_pElementSet;
        IEActionType              m_ActionType;
};

//---------------------------------------------------------------------------
// PSS_ModelObserverMsg
//---------------------------------------------------------------------------
PSS_ModelObserverMsg::IEActionType PSS_ModelObserverMsg::GetActionType() const
{
    return m_ActionType;
}
//---------------------------------------------------------------------------
void PSS_ModelObserverMsg::SetActionType(IEActionType value)
{
    m_ActionType = value;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelDoc* PSS_ModelObserverMsg::GetDoc() const
{
    return m_pDoc;
}
//---------------------------------------------------------------------------
void PSS_ModelObserverMsg::SetDoc(PSS_ProcessGraphModelDoc* pDoc)
{
    m_pDoc = pDoc;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ModelObserverMsg::GetModel() const
{
    return m_pModel;
}
//---------------------------------------------------------------------------
void PSS_ModelObserverMsg::SetModel(PSS_ProcessGraphModelMdl* pModel)
{
    m_pModel = pModel;
}
//---------------------------------------------------------------------------
CODComponent* PSS_ModelObserverMsg::GetElement() const
{
    return m_pElement;
}
//---------------------------------------------------------------------------
void PSS_ModelObserverMsg::SetElement(CODComponent* pElement)
{
    m_pElement = pElement;
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_ModelObserverMsg::GetElementSet() const
{
    return m_pElementSet;
}
//---------------------------------------------------------------------------
void PSS_ModelObserverMsg::SetElementSet(CODComponentSet* pSet)
{
    m_pElementSet = pSet;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphPage* PSS_ModelObserverMsg::GetPage() const
{
    return m_pPage;
}
//---------------------------------------------------------------------------
void PSS_ModelObserverMsg::SetPage(PSS_ProcessGraphPage* pPage)
{
    m_pPage = pPage;
}
//---------------------------------------------------------------------------

#endif
