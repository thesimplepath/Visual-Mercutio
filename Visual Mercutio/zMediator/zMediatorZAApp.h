// **********************************************************************************************************************
// *                                            Classe zMediatorZAApp                                                    *
// **********************************************************************************************************************
// * Cette classe permet de rendre certaines fonctions de haut niveau dans la classe ZAApp accessible depuis n'importe    *
// * quelle classe de n'importe quel projet.                                                                            *
// **********************************************************************************************************************

#if !defined(AFX_ZMEDIATORZAAPP_H__C1668594_D42A_4E45_B15E_918C63D31752__INCLUDED_)
#define AFX_ZMEDIATORZAAPP_H__C1668594_D42A_4E45_B15E_918C63D31752__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZMEDIATOREXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class ZVRiskTypeContainer;
class ZVRiskImpactContainer;
class ZVRiskProbabilityContainer;

class AFX_EXT_CLASS zMediatorZAApp : public CWinApp
{
public:

    zMediatorZAApp();
    ~zMediatorZAApp();

// Implementation
public:

    //{{AFX_MSG(ZASingleInstanceApplication)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

// Fonctions virtuelles pour l'héritage et l'utilisation dans le médiateur.
public:

    // JMR-MODIF - Le 16 octobre 2007 - Ces 2 fonctions permettent la mise à jour des symboles et des propriétés.
    virtual void DoRefreshProperties() = 0;
    virtual void DoRefreshSymbolsAndProperties() = 0;

    // JMR-MODIF - Le 16 octobre 2007 - Cette fonction permet d'accéder au nom du répertoire d'installation de Mecutio.
    virtual CString GetApplicationDirectory() const = 0;

    // JMR-MODIF - Le 16 octobre 2007 - Cette fonction permet d'accéder au nom du fichier d'initialisation de Mecutio.
    virtual CString GetApplicationIniFilename() const = 0;

    // JMR-MODIF - Le 16 octobre 2007 - Cette fonction permet de mettre à jour le nom du dernier fichier chargé.
    virtual void UpdateLastLoadedFile( CString Filename ) = 0;

    // JMR-MODIF - Le 16 octobre 2007 - Ajout de ces 3 fonctions pour la prise en charge des risques.
    virtual ZVRiskTypeContainer* GetRiskTypeContainer() = 0;
    virtual ZVRiskImpactContainer* GetRiskImpactContainer() = 0;
    virtual ZVRiskProbabilityContainer* GetRiskProbabilityContainer() = 0;

    // JMR-MODIF - Le 16 octobre 2007 - Ajout de cette fonction pour corriger un bug du menu "Fichiers récents".
    virtual void OnAfterOpenDocument( CDocument* pDoc, CString Filename ) = 0;
};

#endif // !defined(AFX_ZMEDIATORZAAPP_H__C1668594_D42A_4E45_B15E_918C63D31752__INCLUDED_)