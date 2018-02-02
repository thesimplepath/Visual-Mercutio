// ******************************************************************************************************
// *											  Classe Maths											*
// ******************************************************************************************************
// * JMR-MODIF - Le 18 janvier 2006 - Création de la nouvelle classe Maths.								*
// ******************************************************************************************************
// * Description	: Cette classe mets à disposition des outils mathématiques standards.				*
// * Créateur		: Jean-Milost Reymond																*
// * Date			: Le 18 janvier 2006																*
// * Modification	:																					*
// * Date			:																					*
// ******************************************************************************************************

#include "stdafx.h"
#include "Maths.h"

// ******************************************************************************************************
// *										  Construction et destruction								*
// ******************************************************************************************************

// Constructeur par défaut de la classe Maths.
Maths::Maths()
{
}

// Destructeur de la classe Maths.
Maths::~Maths()
{
}

// ******************************************************************************************************
// *							  Fonctions publiques de la classe ZVPublishReport						*
// ******************************************************************************************************

// Retourne le vecteur normalisé. L'utilisateur a la responsabilité de détruire le vecteur retourné après utilisation.
Vector2D* Maths::getNormalizedVector2D( Vector2D* toNormalize )
{
	float n = sqrt( ( toNormalize->getX() * toNormalize->getX() ) + ( toNormalize->getY() * toNormalize->getY() ) );

	return new Vector2D( toNormalize->getX() / n, toNormalize->getY() / n );
}

// Retourne le produit scalaire de deux vecteurs.
float Maths::getDotProduct( Vector2D* v1, Vector2D* v2 )
{
	return ( v1->getX() * v2->getX() + v1->getY() * v2->getY() );
}

// Teste si la coordonnée d'un point donné se trouve à l'intérieur d'un triangle donné.
BOOL Maths::IsTriPointCollision( Triangle* aTriangle, Vector2D* aPoint)
{
	BOOL myResult = FALSE;

	Vector2D* PToV1 = new Vector2D( aTriangle->getVertex1().getX() - aPoint->getX(),
									aTriangle->getVertex1().getY() - aPoint->getY() );
	Vector2D* PToV2 = new Vector2D( aTriangle->getVertex2().getX() - aPoint->getX(),
									aTriangle->getVertex2().getY() - aPoint->getY() );
	Vector2D* PToV3 = new Vector2D( aTriangle->getVertex3().getX() - aPoint->getX(),
									aTriangle->getVertex3().getY() - aPoint->getY() );

	Vector2D* NormalizedPToV1 = getNormalizedVector2D( PToV1 );
	Vector2D* NormalizedPToV2 = getNormalizedVector2D( PToV2 );
	Vector2D* NormalizedPToV3 = getNormalizedVector2D( PToV3 );

	// Obtient les trois produits vectoriels, afin de calculer l'angle total entre les 3 vecteurs.
	float A1 = getDotProduct( NormalizedPToV1, NormalizedPToV2 );
	float A2 = getDotProduct( NormalizedPToV2, NormalizedPToV3 );
	float A3 = getDotProduct( NormalizedPToV3, NormalizedPToV1 );

	// Corrige une erreur d'arrondi du processeur. Parfois, le résultat peut être de 1.0000000000000000000001f,
	// et cela suffit à faire échouer les fonctions acosf ci-après.
	if ( A1 < ( -1.0f ) )	A1 = -1.0f;
	if ( A2 < ( -1.0f ) )	A2 = -1.0f;
	if ( A3 < ( -1.0f ) )	A3 = -1.0f;

	if ( A1 > 1.0f )		A1 = 1.0f;
	if ( A2 > 1.0f )		A2 = 1.0f;
	if ( A3 > 1.0f )		A3 = 1.0f;

	// Calcule l'angle total.
	float AngleResult = acosf( A1 ) + acosf( A2 ) + acosf( A3 );

	// Si l'angle vaut 360 degrés, on se trouve au centre du triangle. Sinon, tant pis...
	if ( AngleResult >= 6.28f )
	{
		myResult = TRUE;
	}

	// Nettoyage de la mémoire.
	delete PToV1;
	delete PToV2;
	delete PToV3;
	delete NormalizedPToV1;
	delete NormalizedPToV2;
	delete NormalizedPToV3;

	return myResult;
}
