/****************************************************************************
 * ==> PSS_FieldObserverMsg ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a message for the field observer                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FieldObserverMsgH
#define PSS_FieldObserverMsgH

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
#include "ZIObserverMsg.h"

// class name mapping
#ifndef PSS_PlanFinObject
    #define PSS_PlanFinObject PlanFinObject
#endif

// forward class declaration
class PSS_PlanFinObject;

#ifdef _ZBASELIBEXPORT
    //put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Field observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FieldObserverMsg : public ZIObserverMsg  
{
    DECLARE_DYNAMIC(PSS_FieldObserverMsg)

    public:
        /**
        * Constructor
        *@param messageID - message identifier
        *@param pObject - owning object
        */
        PSS_FieldObserverMsg(UINT messageID = 0, PSS_PlanFinObject* pObject = NULL);

        virtual ~PSS_FieldObserverMsg();

        /**
        * Gets the message identifier
        *@return the message identifier
        */
        virtual inline UINT GetMessageID() const;

        /**
        * Sets the message identifier
        *@param value - the message identifier
        */
        virtual inline void SetMessageID(UINT value);

        /**
        * Gets the owning object
        *@return the owning object
        */
        virtual inline PSS_PlanFinObject* GetObject() const;

        /**
        * Sets the owning object
        *@param pObject - the owning object
        */
        virtual inline void SetObject(PSS_PlanFinObject* pObject);

    private:
        UINT               m_MessageID;
        PSS_PlanFinObject* m_pObject;
        CView*             m_pView;
};

//---------------------------------------------------------------------------
// PSS_FieldObserverMsg
//---------------------------------------------------------------------------
UINT PSS_FieldObserverMsg::GetMessageID() const
{
    return m_MessageID;
}
//---------------------------------------------------------------------------
void PSS_FieldObserverMsg::SetMessageID(UINT value)
{
    m_MessageID = value;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_FieldObserverMsg::GetObject() const
{
    return m_pObject;
}
//---------------------------------------------------------------------------
void PSS_FieldObserverMsg::SetObject(PSS_PlanFinObject* pObject)
{
    m_pObject = pObject;
}
//---------------------------------------------------------------------------

#endif
