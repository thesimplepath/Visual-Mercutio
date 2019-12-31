/****************************************************************************
 * ==> PSS_SymbolLogObserverMsg --------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol log observer message                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SymbolLogObserverMsgH
#define PSS_SymbolLogObserverMsgH

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
#include "PSS_GenericSymbolErrorLine.h"

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
* Symbol log observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SymbolLogObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(PSS_SymbolLogObserverMsg)

    public:
        PSS_SymbolLogObserverMsg();

        /**
        * Constructor
        *@param errorLine - the error line
        */
        PSS_SymbolLogObserverMsg(const PSS_GenericSymbolErrorLine& errorLine);

        virtual ~PSS_SymbolLogObserverMsg();

        /**
        * Gets the error line
        *@return the error line
        */
        virtual inline PSS_GenericSymbolErrorLine& GetErrorLine();

        /**
        * Sets the error line
        *@param value - the error line
        */
        virtual inline void SetErrorLine(const PSS_GenericSymbolErrorLine& value);

    private:
        PSS_GenericSymbolErrorLine m_ErrorLine;
};

//---------------------------------------------------------------------------
// PSS_SymbolLogObserverMsg
//---------------------------------------------------------------------------
PSS_GenericSymbolErrorLine& PSS_SymbolLogObserverMsg::GetErrorLine()
{
    return m_ErrorLine;
}
//---------------------------------------------------------------------------
void PSS_SymbolLogObserverMsg::SetErrorLine(const PSS_GenericSymbolErrorLine& value)
{
    m_ErrorLine = value;
}
//---------------------------------------------------------------------------

#endif
