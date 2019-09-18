/****************************************************************************
 * ==> PSS_DocumentObserverMsg ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a message for the document observer               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DocumentObserverMsgH
#define PSS_DocumentObserverMsgH

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

#include "ZIObserverMsg.h"

#ifdef _ZBASELIBEXPORT
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
class AFX_EXT_CLASS PSS_DocumentObserverMsg : public ZIObserverMsg
{
    DECLARE_DYNAMIC(PSS_DocumentObserverMsg)

    public:
        /**
        * Constructor
        *@param messageID - message identifier
        *@param pDoc - document
        */
        PSS_DocumentObserverMsg(UINT messageID = 0, CDocument* pDoc = NULL);

        /**
        * Constructor
        *@param messageID - message identifier
        *@param pView - view
        */
        PSS_DocumentObserverMsg(UINT messageID, CView* pView);

        /**
        * Constructor
        *@param messageID - message identifier
        *@param pDoc - document
        *@param pView - view
        */
        PSS_DocumentObserverMsg(UINT messageID, CDocument* pDoc, CView* pView);

        virtual ~PSS_DocumentObserverMsg();

        /**
        * Gets the document
        *@return the document
        */
        virtual inline CDocument* GetDocument() const;

        /**
        * Sets the document
        *@param pDoc - the document
        */
        virtual inline void SetDocument(CDocument* pDoc);

        /**
        * Gets the view
        *@return the view
        */
        virtual inline CView* GetView() const;

        /**
        * Sets the view
        *@param pView - the view
        */
        virtual inline void SetView(CView* pView);

        /**
        * Gets the message identifier
        *@return the message identifier
        */
        virtual inline UINT GetMessageID() const;

        /**
        * Sets the message identifier
        *@param messageID - the message identifier
        */
        virtual inline void SetMessageID(UINT messageID);

    private:
        CDocument* m_pDoc;
        CView*     m_pView;
        UINT       m_MessageID;
};

//---------------------------------------------------------------------------
// PSS_DocumentObserverMsg
//---------------------------------------------------------------------------
CDocument* PSS_DocumentObserverMsg::GetDocument() const
{
    return m_pDoc;
}
//---------------------------------------------------------------------------
void PSS_DocumentObserverMsg::SetDocument(CDocument* pDoc)
{
    m_pDoc = pDoc;
}
//---------------------------------------------------------------------------
CView* PSS_DocumentObserverMsg::GetView() const
{
    return m_pView;
}
//---------------------------------------------------------------------------
void PSS_DocumentObserverMsg::SetView(CView* pView)
{
    m_pView = pView;
}
//---------------------------------------------------------------------------
UINT PSS_DocumentObserverMsg::GetMessageID() const
{
    return m_MessageID;
}
//---------------------------------------------------------------------------
void PSS_DocumentObserverMsg::SetMessageID(UINT messageID)
{
    m_MessageID = messageID;
}
//---------------------------------------------------------------------------

#endif
