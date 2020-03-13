/****************************************************************************
 * ==> PSS_PropertyItemObserverMsg -----------------------------------------*
 ****************************************************************************
 * Description : Provides a property item observer message                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PropertyItemObserverMsgH
#define PSS_PropertyItemObserverMsgH

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

// old class name mapping
#ifndef PSS_Property
    #define PSS_Property ZBProperty
#endif

// forward class declarations
class PSS_Property;

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
* Property item observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PropertyItemObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(PSS_PropertyItemObserverMsg)

    public:
        /**
        * Constructor
        *@param pProp - the property
        */
        PSS_PropertyItemObserverMsg(PSS_Property* pProp = NULL);

        virtual ~PSS_PropertyItemObserverMsg();

        /**
        * Gets the property
        *@return the property
        */
        virtual inline PSS_Property* GetProperty() const;

        /**
        * Sets the property
        *@param pProp - the property
        */
        virtual inline void SetProperty(PSS_Property* pProp);

    private:
        PSS_Property* m_pProperty;
};

//---------------------------------------------------------------------------
// PSS_PropertyItemObserverMsg
//---------------------------------------------------------------------------
PSS_Property* PSS_PropertyItemObserverMsg::GetProperty() const
{
    return m_pProperty;
}
//---------------------------------------------------------------------------
void PSS_PropertyItemObserverMsg::SetProperty(PSS_Property* pProp)
{
    m_pProperty = pProp;
}
//---------------------------------------------------------------------------

#endif
