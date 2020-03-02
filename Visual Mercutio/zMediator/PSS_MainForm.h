/****************************************************************************
 * ==> PSS_MainForm --------------------------------------------------------*
 ****************************************************************************
 * Description : Application main form interface (may be shared between all *
 *               DLLs). This is where the common functions related to the   *
 *               main form should be declared                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MainFormH
#define PSS_MainFormH

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

#ifdef _ZMEDIATOREXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// class prototypes
class PSS_RiskTypeContainer;
class ZVRiskImpactContainer;
class PSS_RiskProbabilityContainer;

/**
* Application main form interface
*@author Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MainForm : public CWinApp
{
    public:
        PSS_MainForm();
        virtual ~PSS_MainForm();

        /**
        * Sends a notification to refresh properties
        */
        virtual void DoRefreshProperties() = 0;

        /**
        * Sends a notification to refresh symbols and properties
        */
        virtual void DoRefreshSymbolsAndProperties() = 0;

        /**
        * Gets the application installation dir
        *@return Mercutio installation dir
        */
        virtual CString GetApplicationDir() const = 0;

        /**
        * Gets the application ini file
        *@return Mercutio ini file
        */
        virtual CString GetApplicationIniFileName() const = 0;

        /**
        * Updates the last loaded file
        *@param fileName - file name to upload
        */
        virtual void UpdateLastLoadedFile(const CString& fileName) = 0;

        /**
        * Gets the Risk type container
        *@return the Risk type container
        */
        virtual PSS_RiskTypeContainer* GetRiskTypeContainer() = 0;

        /**
        * Gets the Risk impact container
        *@return the Risk impact container
        */
        virtual ZVRiskImpactContainer* GetRiskImpactContainer() = 0;

        /**
        * Gets the Risk probability container
        *@return the Risk probability container
        */
        virtual PSS_RiskProbabilityContainer* GetRiskProbabilityContainer() = 0;

        // JMR-MODIF - Le 16 octobre 2007 - Ajout de cette fonction pour corriger un bug du menu "Fichiers récents".
        /**
        * Called after document is opened
        *@param pDoc - opened document
        *@param fileName - opened document file name
        */
        virtual void OnAfterOpenDocument(CDocument* pDoc, const CString& fileName) = 0;

        /// Message map
        //{{AFX_MSG(PSS_MainForm)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
