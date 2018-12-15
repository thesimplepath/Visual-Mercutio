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

#if !defined(AFX_ZBMEDIATOR_H__C1668594_D42A_4E45_B15E_918C63D31752__INCLUDED_)
#define AFX_ZBMEDIATOR_H__C1668594_D42A_4E45_B15E_918C63D31752__INCLUDED_

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

#include "zMediatorZAApp.h"

#ifdef _ZMEDIATOREXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZBMediator
{
public:

    static ZBMediator*    Instance();
    static void            Release();

    void Register( zMediatorZAApp* p_Class );

    void UnregisterMainApp();

    zMediatorZAApp* GetMainApp();

    // Fonctions de rafraîchissement de l'affichage.
    void RefreshPropertiesWorkspace();
    void RefreshSelectedSymbolAndProperties();

private:

    ZBMediator()
    {
    }

    ~ZBMediator()
    {
    }

private:

    static ZBMediator*    p_Instance;

    zMediatorZAApp*        p_MainApp;
};

#endif // !defined(AFX_ZBMEDIATOR_H__C1668594_D42A_4E45_B15E_918C63D31752__INCLUDED_)