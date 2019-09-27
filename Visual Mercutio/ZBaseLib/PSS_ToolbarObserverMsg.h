/****************************************************************************
 * ==> PSS_ToolbarObserverMsg ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a toolbar observer message                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ToolbarObserverMsgH
#define PSS_ToolbarObserverMsgH

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
* Toolbar observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ToolbarObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(PSS_ToolbarObserverMsg)

    public:
        /**
        * Constructor
        *@param messageID - message identifier
        */
        PSS_ToolbarObserverMsg(UINT messageID = 0);

        virtual ~PSS_ToolbarObserverMsg();

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

    private:
        UINT m_MessageID;
};

//---------------------------------------------------------------------------
// PSS_ToolbarObserverMsg
//---------------------------------------------------------------------------
UINT PSS_ToolbarObserverMsg::GetMessageID() const
{
    return m_MessageID;
}
//---------------------------------------------------------------------------
void PSS_ToolbarObserverMsg::SetMessageID(UINT value)
{
    m_MessageID = value;
}
//---------------------------------------------------------------------------

#endif
