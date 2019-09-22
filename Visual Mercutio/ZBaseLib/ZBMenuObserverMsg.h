/****************************************************************************
 * ==> PSS_MenuObserverMsg -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a menu observer message                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MenuObserverMsgH
#define PSS_MenuObserverMsgH

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
* Menu observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MenuObserverMsg : public ZIObserverMsg
{
    DECLARE_DYNAMIC(PSS_MenuObserverMsg)

    public:
        /**
        * Constructor
        *@param commandID - command identifier
        */
        PSS_MenuObserverMsg(int commandID = 0);

        virtual ~PSS_MenuObserverMsg();

        /**
        * Gets the message identifier
        *@return the message identifier
        */
        virtual inline int GetMessageID() const;

        /**
        * Sets the message identifier
        *@param value - the message identifier
        */
        virtual inline void SetMessageID(int value);

    private:
        int m_CommandID;
};

//---------------------------------------------------------------------------
// PSS_MenuObserverMsg
//---------------------------------------------------------------------------
int PSS_MenuObserverMsg::GetMessageID() const
{
    return m_CommandID;
}
//---------------------------------------------------------------------------
void PSS_MenuObserverMsg::SetMessageID(int value)
{
    m_CommandID = value;
}
//---------------------------------------------------------------------------

#endif
