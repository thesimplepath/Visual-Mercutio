/****************************************************************************
 * ==> PSS_ObserverMsg -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic observer message                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ObserverMsgH
#define PSS_ObserverMsgH

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
* Observer message
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ObserverMsg : public CObject
{
    DECLARE_DYNAMIC(PSS_ObserverMsg)

    public:
        virtual ~PSS_ObserverMsg();

    protected:
        PSS_ObserverMsg();
};

#endif
