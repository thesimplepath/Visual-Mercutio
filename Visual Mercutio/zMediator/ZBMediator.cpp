// **********************************************************************************************************************
// *                                               Classe ZBMediator                                                    *
// **********************************************************************************************************************
// * Type de la classe : Singleton                                                                                        *
// **********************************************************************************************************************
// * Cette classe joue le rôle de "chef d'orchestre" du programme. Ici viennent s'inscrire toutes les classes qui ont    *
// * des fonctions qui doivent être accessibles par n'importe quelle classe de n'importe quel projet. C'est le cas, par *
// * exemple, des fonctions de rafraîchissement, qui doivent pouvoir être ordonnée facilement depuis n'importe quel        *
// * point du programme.                                                                                                *
// **********************************************************************************************************************

#include "StdAfx.h"
#include "ZBMediator.h"

ZBMediator* ZBMediator::p_Instance = NULL;

// Cette fonction retourne l'instance unique du médiateur.
ZBMediator* ZBMediator::Instance()
{
    if ( p_Instance == NULL )
    {
        // Crée l'instance unique du médiateur.
        p_Instance = new ZBMediator();

        // Initialise toutes les données contenues dans le médiateur.
        p_Instance->p_MainApp = NULL;
    }

        return p_Instance;
}

// Cette fonction permet de libérer les ressources utilisées par le médiateur.
void ZBMediator::Release()
{
    if ( p_Instance != NULL )
    {
        delete p_Instance;
        p_Instance = NULL;
    }
}

// Cette fonction permet l'enregistrement d'une classe dans le médiateur.
void ZBMediator::Register( zMediatorZAApp* p_Class )
{
    p_MainApp = p_Class;
}

// Cette fonction permet d'annuler l'enregistrement de la classe principale de l'application dans le médiateur.
void ZBMediator::UnregisterMainApp()
{
    p_MainApp = NULL;
}

// Cette fonction permet d'obtenir la classe principale de l'application.
zMediatorZAApp* ZBMediator::GetMainApp()
{
    return p_MainApp;
}

// Cette fonction ordonne le rafraîchissement de l'espace des propriétés.
void ZBMediator::RefreshPropertiesWorkspace()
{
    if ( p_MainApp != NULL )
    {
        p_MainApp->DoRefreshProperties();
    }
}

// Cette fonction ordonne le rafraîchissement du symbole sélectionné, ainsi que des propriétés qui lui sont liées.
void ZBMediator::RefreshSelectedSymbolAndProperties()
{
    if ( p_MainApp != NULL )
    {
        p_MainApp->DoRefreshSymbolsAndProperties();
    }
}
