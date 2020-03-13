/****************************************************************************
 * ==> PSS_PropertyObserverMsg ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a property observer message                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PropertyObserverMsgH
#define PSS_PropertyObserverMsgH

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

// forward declarations
class PSS_Properties;

#ifdef _ZPROPERTYEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Property observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PropertyObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(PSS_PropertyObserverMsg)

    public:
        /**
        * Constructor
        *@param pProps - the properties
        */
        PSS_PropertyObserverMsg(PSS_Properties* pProps = NULL);

        virtual ~PSS_PropertyObserverMsg();

        /**
        * Gets the properties
        *@return the properties
        */
        virtual inline PSS_Properties* GetProperties() const;

        /**
        * Sets the properties
        *@param pProps - the properties
        */
        virtual inline void SetProperties(PSS_Properties* pProps);

    private:
        PSS_Properties* m_pProperties;
};

//---------------------------------------------------------------------------
// PSS_PropertyObserverMsg
//---------------------------------------------------------------------------
PSS_Properties* PSS_PropertyObserverMsg::GetProperties() const
{
    return m_pProperties;
}
//---------------------------------------------------------------------------
void PSS_PropertyObserverMsg::SetProperties(PSS_Properties* pProps)
{
    m_pProperties = pProps;
}
//---------------------------------------------------------------------------

#endif
