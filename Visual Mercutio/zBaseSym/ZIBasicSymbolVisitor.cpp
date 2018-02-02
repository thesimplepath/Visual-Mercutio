// ******************************************************************************************************
// *										  Classe ZIBasicSymbolVisitor								*
// ******************************************************************************************************
// * Cette classe est une classe abstraite permettant la construction de classes prenant en charge la	*
// * navigation dans les documents.																		*
// ******************************************************************************************************

#include "stdafx.h"
#include "ZIBasicSymbolVisitor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 7 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

// ******************************************************************************************************
// *										  Construction/Destruction									*
// ******************************************************************************************************

// Constructeur par défaut de la classe ZIBasicSymbolVisitor.
ZIBasicSymbolVisitor::ZIBasicSymbolVisitor()
{
}

// Destructeur de la classe ZIBasicSymbolVisitor.
ZIBasicSymbolVisitor::~ZIBasicSymbolVisitor()
{
}
