// ZBOStreamGrid.h: interface for the ZBOStreamGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBOStreamGrid_H__740834E6_6619_441A_B258_D92693F63D64__INCLUDED_)
#define AFX_ZBOStreamGrid_H__740834E6_6619_441A_B258_D92693F63D64__INCLUDED_

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

#include "ZBIOSGrid.h"

#ifdef _ZREPORTEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBOStreamGrid : virtual public ZBIOSGrid
{
public:

	ZBOStreamGrid( CGXGridCore* pGridCore = NULL );
	virtual ~ZBOStreamGrid();

	//////////////////////////////////////////////////////////////////////
	// Writing information operators

	//////////////////////////////////////////////////////////////////////
	// Cell values
	ZBOStreamGrid& operator<<( const char* cpChar );
	ZBOStreamGrid& operator<<( float value );
	ZBOStreamGrid& operator<<( double value );
	ZBOStreamGrid& operator<<( DWORD value );
	ZBOStreamGrid& operator<<( UINT value );
	ZBOStreamGrid& operator<<( WORD value );
	ZBOStreamGrid& operator<<( short value );
	ZBOStreamGrid& operator<<( LONG value );

	//////////////////////////////////////////////////////////////////////
	// Cell position and selection
	ZBOStreamGrid& operator<<( CPoint& pt );
	ZBOStreamGrid& operator<<( CRect& rc );

	//////////////////////////////////////////////////////////////////////
	// Cell size
	ZBOStreamGrid& operator<<( CSize& sz );

	void SetCurSelRowHeight( int Height );
	void SetCurSelColWidth( int Width );

	//////////////////////////////////////////////////////////////////////
	// Cell formatting
	ZBOStreamGrid& operator<<( CGXStyle& style );
	ZBOStreamGrid& operator<<( CGXFont& font );

private:

	// *****************************************************************************************************
	// JMR-MODIF - Le 10 avril 2006 - Ajout des fonctions permettant de sélectionner le style approprié pour
	// l'affichage des données numériques dans les cellules des rapports.

	// Cette fonction permet d'initialiser le style à appliquer à la valeur à inscrire.
	CGXStyle InitNumberStyle()
	{
		return CGXStyle()
			  .SetControl( GX_IDS_CTRL_CURRENCY )
			  .SetUserAttribute( GX_IDS_UA_CURRENCYDEF, _T( "11 0" ) )
			  .SetUserAttribute( GX_IDS_UA_CURMON, _T( "0" ) )
			  .SetUserAttribute( GX_IDS_UA_CURSEP, _T( "'." ) )
			  .SetUserAttribute( GX_IDS_UA_CURNUMFRACT, _T( "0" ) );
	}

	// Convertit la valeur et prépare le style d'affichage pour une valeur de type float.
	CGXStyle ConvertNumber( float Value )
	{
		CString m_StringVal			= _T( "" );
		CString m_StringValLength	= _T( "" );
		int		Length				= 0;

		m_StringVal.Format( _T( "%f" ), Value );

		for ( int i = 0; i < m_StringVal.GetLength(); i++ )
		{
			if ( m_StringVal.GetAt( i ) == _T( '.' ) )
			{
				Length = i;
				break;
			}
		}

		m_StringValLength.Format( _T( "%d" ), Length );

		return InitNumberStyle().SetUserAttribute( GX_IDS_UA_CURNUMDECIMALS, m_StringValLength ).SetValue( Value );
	}

	// Convertit la valeur et prépare le style d'affichage pour une valeur de type double.
	CGXStyle ConvertNumber( double Value )
	{
		CString m_StringVal			= _T( "" );
		CString m_StringValLength	= _T( "" );
		int		Length				= 0;

		m_StringVal.Format( _T( "%lf" ), Value );

		for ( int i = 0; i < m_StringVal.GetLength(); i++ )
		{
			if ( m_StringVal.GetAt( i ) == _T( '.' ) )
			{
				Length = i;
				break;
			}
		}

		m_StringValLength.Format( _T( "%d" ), Length );

		return InitNumberStyle().SetUserAttribute( GX_IDS_UA_CURNUMDECIMALS, m_StringValLength ).SetValue( Value );
	}

	// Convertit la valeur et prépare le style d'affichage pour une valeur de type DWORD.
	CGXStyle ConvertNumber( DWORD Value )
	{
		CString m_StringVal			= _T( "" );
		CString m_StringValLength	= _T( "" );

		m_StringVal.Format( _T( "%lu" ), Value );
		m_StringValLength.Format( _T( "%d" ), m_StringVal.GetLength() );

		return InitNumberStyle().SetUserAttribute( GX_IDS_UA_CURNUMDECIMALS, m_StringValLength ).SetValue( Value );
	}

	// Convertit la valeur et prépare le style d'affichage pour une valeur de type UINT.
	CGXStyle ConvertNumber( UINT Value )
	{
		CString m_StringVal			= _T( "" );
		CString m_StringValLength	= _T( "" );

		m_StringVal.Format( _T( "%u" ), Value );
		m_StringValLength.Format( _T( "%d" ), m_StringVal.GetLength() );

		return InitNumberStyle().SetUserAttribute( GX_IDS_UA_CURNUMDECIMALS, m_StringValLength ).SetValue( Value );
	}

	// Convertit la valeur et prépare le style d'affichage pour une valeur de type WORD.
	CGXStyle ConvertNumber( WORD Value )
	{
		CString m_StringVal			= _T( "" );
		CString m_StringValLength	= _T( "" );

		m_StringVal.Format( _T( "%hu" ), Value );
		m_StringValLength.Format( _T( "%d" ), m_StringVal.GetLength() );

		return InitNumberStyle().SetUserAttribute( GX_IDS_UA_CURNUMDECIMALS, m_StringValLength ).SetValue( Value );
	}

	// Convertit la valeur et prépare le style d'affichage pour une valeur de type short.
	CGXStyle ConvertNumber( short Value )
	{
		CString m_StringVal			= _T( "" );
		CString m_StringValLength	= _T( "" );

		m_StringVal.Format( _T( "%hd" ), Value );
		m_StringValLength.Format( _T( "%d" ), m_StringVal.GetLength() );

		return InitNumberStyle().SetUserAttribute( GX_IDS_UA_CURNUMDECIMALS, m_StringValLength ).SetValue( Value );
	}

	// Convertit la valeur et prépare le style d'affichage pour une valeur de type LONG.
	CGXStyle ConvertNumber( LONG Value )
	{
		CString m_StringVal			= _T( "" );
		CString m_StringValLength	= _T( "" );

		m_StringVal.Format( _T( "%ld" ), Value );
		m_StringValLength.Format( _T( "%d" ), m_StringVal.GetLength() );

		return InitNumberStyle().SetUserAttribute( GX_IDS_UA_CURNUMDECIMALS, m_StringValLength ).SetValue( Value );
	}
	// *****************************************************************************************************
};

inline ZBOStreamGrid& ZBOStreamGrid::operator<<( const char* cpChar )
{
	if ( m_pGridCore )
	{
		const char* cpCurrent	= cpChar;
		const char* cpLast		= cpChar;

		while ( *cpCurrent )
		{
			if ( *cpCurrent == '\t' )
			{
				// Copy the sub-string
				CString s( cpLast, cpCurrent - cpLast );

				if ( !s.IsEmpty() )
				{
					// Assign the cell string
					m_pGridCore->SetStyleRange( ConvertToCGXRange(),
												CGXStyle().SetValue( s ) );
				}

				// Move right
				Right();

				// Set the new cpLast pointer and move forward one char
				cpLast = ++cpCurrent;
			}
			else if ( *cpCurrent == '\n' )
			{
				// Copy the sub-string
				CString s( cpLast, cpCurrent - cpLast );

				if ( !s.IsEmpty() )
				{
					// Assign the cell string
					m_pGridCore->SetStyleRange( ConvertToCGXRange(),
												CGXStyle().SetValue( s ) );
				}

				// Move down
				Down();

				// Move home left
				HomeLeft();

				// Set the new cpLast pointer and move forward one char
				cpLast = ++cpCurrent;
			}
			else
			{
				// Move forward one char
				++cpCurrent;
			}
		}

		// Process the last string
		CString s( cpLast, cpCurrent - cpLast );

		if ( !s.IsEmpty() )
		{
			// Assign the cell string
			m_pGridCore->SetStyleRange( ConvertToCGXRange(),
										CGXStyle().SetValue( cpChar ) );
		}
	}

	return *this;
}

inline ZBOStreamGrid& ZBOStreamGrid::operator<<( float value )
{
	if ( m_pGridCore )
	{
		// ********************************************************************************************************
		// JMR-MODIF - Le 10 avril 2006 - Changement du style à appliquer aux valeurs. 1,000,000 devient 1'000'000.

		// Assign the cell float value
/*		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									CGXStyle().SetValue( value ) );
*/

		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									ConvertNumber( value ) );
		// ********************************************************************************************************
	}

	return *this;
}

inline ZBOStreamGrid& ZBOStreamGrid::operator<<( double value )
{
	if ( m_pGridCore )
	{
		// ********************************************************************************************************
		// JMR-MODIF - Le 10 avril 2006 - Changement du style à appliquer aux valeurs. 1,000,000 devient 1'000'000.

		// Assign the cell float value
/*		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									CGXStyle().SetValue( value ).SetFormat( GX_FMT_GEN ) );
*/

		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									ConvertNumber( value ) );
		// ********************************************************************************************************
	}

	return *this;
}

inline ZBOStreamGrid& ZBOStreamGrid::operator<<( DWORD value )
{
	if ( m_pGridCore )
	{
		// ********************************************************************************************************
		// JMR-MODIF - Le 10 avril 2006 - Changement du style à appliquer aux valeurs. 1,000,000 devient 1'000'000.

		// Assign the cell float value
/*		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									CGXStyle().SetValue( value ) );
*/

		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									ConvertNumber( value ) );
		// ********************************************************************************************************
	}

	return *this;
}

inline ZBOStreamGrid& ZBOStreamGrid::operator<<( UINT value )
{
	if ( m_pGridCore )
	{
		// ********************************************************************************************************
		// JMR-MODIF - Le 10 avril 2006 - Changement du style à appliquer aux valeurs. 1,000,000 devient 1'000'000.

		// Assign the cell float value
/*		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									CGXStyle().SetValue( value ) );
*/

		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									ConvertNumber( value ) );
		// ********************************************************************************************************
	}

	return *this;
}

inline ZBOStreamGrid& ZBOStreamGrid::operator<<( WORD value )
{
	if ( m_pGridCore )
	{
		// ********************************************************************************************************
		// JMR-MODIF - Le 10 avril 2006 - Changement du style à appliquer aux valeurs. 1,000,000 devient 1'000'000.

		// Assign the cell float value
/*		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									CGXStyle().SetValue( value ) );
*/

		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									ConvertNumber( value ) );
		// ********************************************************************************************************
	}

	return *this;
}

inline ZBOStreamGrid& ZBOStreamGrid::operator<<( short value )
{
	if ( m_pGridCore )
	{
		// ********************************************************************************************************
		// JMR-MODIF - Le 10 avril 2006 - Changement du style à appliquer aux valeurs. 1,000,000 devient 1'000'000.

		// Assign the cell float value
/*		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									CGXStyle().SetValue( value ) );
*/

		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									ConvertNumber( value ) );
		// ********************************************************************************************************
	}

	return *this;
}

inline ZBOStreamGrid& ZBOStreamGrid::operator<<( LONG value )
{
	if ( m_pGridCore )
	{
		// ********************************************************************************************************
		// JMR-MODIF - Le 10 avril 2006 - Changement du style à appliquer aux valeurs. 1,000,000 devient 1'000'000.

		// Assign the cell float value
/*		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									CGXStyle().SetValue( value ) );
*/

		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									ConvertNumber( value ) );
		// ********************************************************************************************************
	}

	return *this;
}

// Set the current selection
inline ZBOStreamGrid& ZBOStreamGrid::operator<<( CPoint& pt )
{
	SetCurSel( pt );
	
	return *this;
}

inline ZBOStreamGrid& ZBOStreamGrid::operator<<( CRect& rc )
{
	SetCurSel( rc );

	return *this;
}

// Set the new size for the current selection
inline ZBOStreamGrid& ZBOStreamGrid::operator<<( CSize& sz )
{
	if ( m_pGridCore )
	{
		int left;
		int top;
		int right;
		int bottom;

		GetCurSel( left, top, right, bottom );

		// Set the column width if different from 0
		if ( sz.cx != 0 )
		{
			m_pGridCore->SetColWidth(left, right, sz.cx );
		}

		// Set the row height if different from 0
		if ( sz.cy != 0 )
		{
			m_pGridCore->SetRowHeight(top, bottom, sz.cy );
		}
	}

	return *this;
}

// Formatting cell
inline ZBOStreamGrid& ZBOStreamGrid::operator<<( CGXStyle& style )
{
	if ( m_pGridCore )
	{
		// Assign the cell float value
		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									style );
	}

	return *this;
}

inline ZBOStreamGrid& ZBOStreamGrid::operator<<( CGXFont& font )
{
	if ( m_pGridCore )
	{
		// Assign the cell float value
		m_pGridCore->SetStyleRange( ConvertToCGXRange(),
									CGXStyle().SetFont( font ) );
	}

	return *this;
}

inline void ZBOStreamGrid::SetCurSelRowHeight( int Height )
{
	if ( m_pGridCore )
	{
		int left;
		int top;
		int right;
		int bottom;

		GetCurSel( left, top, right, bottom );

		m_pGridCore->SetRowHeight( top, bottom, Height );
	}
}

inline void ZBOStreamGrid::SetCurSelColWidth( int Width )
{
	if ( m_pGridCore )
	{
		int left;
		int top;
		int right;
		int bottom;

		GetCurSel( left, top, right, bottom );

		m_pGridCore->SetColWidth( left, right, Width );
	}
}

#endif // !defined(AFX_ZBOStreamGrid_H__740834E6_6619_441A_B258_D92693F63D64__INCLUDED_)