/****************************************************************************
 * ==> PSS_Application -----------------------------------------------------*
 ****************************************************************************
 * Description : Basic application interface (may be shared between all     *
 *               DLLs). This is where the common functions, like those who  *
 *               refresh the interface, should be declared                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ApplicationH
#define PSS_ApplicationH

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
#include "PSS_MainForm.h"

#ifdef _ZMEDIATOREXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Basic application interface
*@author Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Application
{
    public:
        /**
        * Gets the application instance, creates one if still not exists
        *@return application instance, NULL on error
        */
        static PSS_Application* Instance();

        /**
        * Releases the application instance
        */
        // todo -cImprovement -oJean: an unique_ptr may be used to avoid worrying about the singleton destruction
        static void Release();

        /**
        * Registers the main form class
        *@param pForm - main form to register
        */
        void RegisterMainForm(PSS_MainForm* pForm);

        /**
        * Unregisters the main form class
        */
        void UnregisterMainForm();

        /**
        * Gets the main form class
        *@return the main form class, NULL if no class registered
        */
        PSS_MainForm* GetMainForm();

        /**
        * Refreshes the properties workspace
        */
        void RefreshPropertiesWorkspace();

        /**
        * Refreshes the selected symbols and properties
        */
        void RefreshSelectedSymbolAndProperties();

    private:
        static PSS_Application* m_pInstance;
               PSS_MainForm*    m_pMainForm;

        /**
        * Constructor
        *@note Private to forbid any construction outside the singleton
        */
        PSS_Application() :
            m_pMainForm(NULL)
        {}

        /**
        * Destructor
        *@note Private to forbid any destruction outside the singleton
        */
        ~PSS_Application()
        {}

        /**
        * Copy operator
        *@param other - other instance to copy from
        *@note Private to forbid any copy outside the singleton
        */
        PSS_Application& operator = (const PSS_Application& other)
        {
            THROW("Copy of the PSS_Application singleton is prohibited");
        }
};

#endif
