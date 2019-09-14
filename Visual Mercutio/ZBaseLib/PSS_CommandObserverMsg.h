/****************************************************************************
 * ==> PSS_CommandObserverMsg ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a message for the command observer                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CommandObserverMsgH
#define PSS_CommandObserverMsgH

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
* Message for command observer
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_CommandObserverMsg : public ZIObserverMsg
{
    DECLARE_DYNAMIC(PSS_CommandObserverMsg)

    public:
        /**
        * Constructor
        *@param commandID - command message identifier
        */
        PSS_CommandObserverMsg(int commandID = 0);

        virtual ~PSS_CommandObserverMsg();

        /**
        * Gets the command identifier
        *@return the command identifier
        */
        virtual inline int GetCommandID() const;

        /**
        * Sets the command identifier
        *@param value - the command identifier
        */
        virtual inline void SetCommandID(int value);

    private:
        int m_CommandID;
};

//---------------------------------------------------------------------------
// PSS_CommandObserverMsg
//---------------------------------------------------------------------------
int PSS_CommandObserverMsg::GetCommandID() const
{
    return m_CommandID;
}
//---------------------------------------------------------------------------
void PSS_CommandObserverMsg::SetCommandID(int value)
{
    m_CommandID = value;
}
//---------------------------------------------------------------------------

#endif
