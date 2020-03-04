/****************************************************************************
 * ==> PSS_CheckMessengerValidUnit -----------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to check Messenger valid unit         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CheckMessengerValidUnitH
#define PSS_CheckMessengerValidUnitH

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
#include "PSS_ProcessNavigation.h"

// class name mapping
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif

// forward class declaration
class PSS_UserGroupEntity;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Navigator to check Messenger valid unit
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_CheckMessengerValidUnit : public PSS_ProcessNavigation
{
    public:
        /**
        * Constructor
        *@param pModel - the model to navigate
        *@param pClass - the custom data class, can be NULL
        */
        PSS_CheckMessengerValidUnit(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);

        virtual ~PSS_CheckMessengerValidUnit();

        /**
        * Called when the navigation starts
        *@return true on success, otherwise false
        */
        virtual bool OnStart();

        /**
        * Called when the navigation ends
        *@return true on success, otherwise false
        */
        virtual bool OnFinish();

        /**
        * Called when a procedure symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);

        /**
        * Called when a start symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnStartSymbol(PSS_StartSymbolBP* pSymbol);

        /**
        * Called when a stop symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnStopSymbol(PSS_StopSymbolBP* pSymbol);
};

#endif
