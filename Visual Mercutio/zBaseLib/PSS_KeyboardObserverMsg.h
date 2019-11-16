/****************************************************************************
 * ==> PSS_KeyboardObserverMsg ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a keyboard observer message                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_KeyboardObserverMsgH
#define PSS_KeyboardObserverMsgH

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
#include "PSS_ObserverMsg.h"

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
* Keyboard observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_KeyboardObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(PSS_KeyboardObserverMsg)

    public:
        /**
        * Constructor
        *@param messageID - message identifier
        *@param key - key
        */
        PSS_KeyboardObserverMsg(UINT messageID = 0, UINT key = 0);

        virtual ~PSS_KeyboardObserverMsg();

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
        * Gets the key
        *@return the key
        */
        virtual inline UINT GetKey() const;

        /**
        * Sets the key
        *@param value - the key
        */
        virtual inline void SetKey(UINT value);

    private:
        UINT m_MessageID;
        UINT m_Key;
};

//---------------------------------------------------------------------------
// PSS_KeyboardObserverMsg
//---------------------------------------------------------------------------
UINT PSS_KeyboardObserverMsg::GetMessageID() const
{
    return m_MessageID;
}
//---------------------------------------------------------------------------
void PSS_KeyboardObserverMsg::SetMessageID(UINT value)
{
    m_MessageID = value;
}
//---------------------------------------------------------------------------
UINT PSS_KeyboardObserverMsg::GetKey() const
{
    return m_Key;
}
//---------------------------------------------------------------------------
void PSS_KeyboardObserverMsg::SetKey(UINT value)
{
    m_Key = value;
}
//---------------------------------------------------------------------------

#endif
