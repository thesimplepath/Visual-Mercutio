// **************************************************************************************************************
// *										  Fichier zMacros.h													*
// **************************************************************************************************************
// * JMR-MODIF - Le 30 mars 2006 - Ajout du fichier zMacros.h													*
// **************************************************************************************************************
// * Ce fichier contient l'ensemble des macros à définir ou redéfinir dans les projets.							*
// **************************************************************************************************************

#if !defined(__ZMACROS_H)
#define __ZMACROS_H

// JMR-MODIF - Le 30 mars 2006 - Déplaçé la macro ISA depuis le fichier ZAConst.
// Macro to shorten runtime type information calls
#if !defined(ISA)
#define ISA( pObj, className ) pObj->IsKindOf( RUNTIME_CLASS( className ) )
#endif //(ISA)

#endif // __ZMACROS_H