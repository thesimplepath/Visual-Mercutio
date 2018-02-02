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

#if !defined(AFX_MATHS_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)
#define AFX_MATHS_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// Classe Vector2D. Cette classe représente un vecteur représenté par deux dimensions x et y.
class AFX_EXT_CLASS Vector2D
{
private:

	float xCoord;
	float yCoord;

public:

	Vector2D()
	{
		xCoord = 0.0f;
		yCoord = 0.0f;
	}

	Vector2D( float x, float y )
	{
		xCoord = x;
		yCoord = y;
	}

	void setX( float x )
	{
		xCoord = x;
	}

	float getX()
	{
		return xCoord;
	}

	void setY( float y )
	{
		yCoord = y;
	}

	float getY()
	{
		return yCoord;
	}
};

// Classe Triangle : Cette classe représente un triangle dont chaque sommet est une paire de points x et y.
class AFX_EXT_CLASS Triangle
{
private:

	Vector2D v1;
	Vector2D v2;
	Vector2D v3;

public:

	Triangle()
	{
		v1.setX( 0.0f );
		v1.setY( 0.0f );
		v2.setX( 0.0f );
		v2.setY( 0.0f );
		v3.setX( 0.0f );
		v3.setY( 0.0f );
	}

	Triangle( float v1x, float v1y, float v2x, float v2y, float v3x, float v3y )
	{
		v1.setX( v1x );
		v1.setY( v1y );
		v2.setX( v2x );
		v2.setY( v2y );
		v3.setX( v3x );
		v3.setY( v3y );
	}

	Triangle( Vector2D Vertex1, Vector2D Vertex2, Vector2D Vertex3 )
	{
		v1 = Vertex1;
		v2 = Vertex2;
		v3 = Vertex3;
	}

	void setVertex1( Vector2D Vertex1 )
	{
		v1 = Vertex1;
	}

	void setVertex1( float v1x, float v1y )
	{
		v1.setX( v1x );
		v1.setY( v1y );
	}

	Vector2D getVertex1()
	{
		return v1;
	}

	void setVertex2( Vector2D Vertex2 )
	{
		v2 = Vertex2;
	}

	void setVertex2( float v2x, float v2y )
	{
		v2.setX( v2x );
		v2.setY( v2y );
	}

	Vector2D getVertex2()
	{
		return v2;
	}

	void setVertex3( Vector2D Vertex3 )
	{
		v3 = Vertex3;
	}

	void setVertex3( float v3x, float v3y )
	{
		v3.setX( v3x );
		v3.setY( v3y );
	}

	Vector2D getVertex3()
	{
		return v3;
	}
};

// Classe Maths : Cette classe mets à disposition des algorythmes standards de mathématiques.
class AFX_EXT_CLASS Maths
{
public:

	Maths();
	~Maths();

	Vector2D* getNormalizedVector2D( Vector2D* toNormalize );

	float getDotProduct( Vector2D* v1, Vector2D* v2 );

	BOOL IsTriPointCollision( Triangle* aTriangle, Vector2D* aPoint);
};

#endif // !defined(AFX_MATHS_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)