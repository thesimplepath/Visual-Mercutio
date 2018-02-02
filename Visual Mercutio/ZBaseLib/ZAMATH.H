// -------------------------------------------------------
// Project	 : 	Math Functions
// Author    : 	Dominique Aigroz            
// Filename  : 	zamath.h
// Created   : 	23.09.1994
// Comments	 : 	This header contains the Parser Class
//				and the C function for parsering.
// Modify    :           
//---------------------------------------------------------------------------

/* Expression Grammar */
/*                                                              *
 *    expression    ->  term expression'                        *
 *    expression'   ->  + term expression'                      *
 *                  |   - term expression'                      *
 *                  |   Epsilon                                 *
 *                                                              *
 *    term          ->  factor term'                            *
 *    term'         ->  * factor term'                          *
 *                  |   / factor term'                          *
 *                  |   ^ factor term'                          *
 *                  |   Epsilon                                 *
 *                                                              *
 *    factor        ->  number                                  *
 *                  |   function                                *
 *                  |   fieldname                               *
 *                  |   (expression)                            *
 *                                                              *
 *                                                              *
 *                                                              */

#if !defined(__ZAMATH_H)
#define __ZAMATH_H

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 14 juin 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// The size of the stack for the parser
#define PARSERSTACKSIZE	20

// Definition of constants
#define PLUS			0
#define MINUS			1
#define TIMES			2
#define DIVIDE			3
#define EXP				4
#define OPAREN			5
#define CPAREN			6
#define NUM				7
#define FUNC			8
#define GT				9
#define LT				10
#define EQ				11
#define GTE				12
#define LTE				13
#define NEQ				14
#define OR				15
#define AND				16
#define NOT				17

#define FIELD			21
#define EOI				22	// End if input
#define BAD				23
#define MAXFUNCNAMELEN	5

struct TOKENREC				// To store the tokens
{
	double value;
	char funcname[MAXFUNCNAMELEN + 1];
};

/////////////////////////////////////////////////////////////////////////////
// Parser class

class AFX_EXT_CLASS ObjectParser : public CObject
{
public:

	// Inherited feature
	typedef CObject inherited;

// Construction
public:

	ObjectParser();
	ObjectParser( const ObjectParser &right );
	virtual ~ObjectParser();

	const ObjectParser & operator=( const ObjectParser *right )
	{
		m_strObjName = right->m_strObjName; return *this;
	};

	const ObjectParser & operator=( const ObjectParser &right )
	{
		m_strObjName = right.m_strObjName; return *this;
	};

	ObjectParser* CloneObject();

	virtual double GetValue() const
	{
		return 0;
	};

	const CString& GetObjectName()
	{
		return( m_strObjName );
	};

	void SetObjectName( const CString sName )
	{
		m_strObjName = sName;
	};

// Data
public:

	CString m_strObjName;
};

class AFX_EXT_CLASS Parser
{
// Construction
public:

	Parser();
	virtual ~Parser();

// Operations
public:

#if (_MFC_VER >= 0x0250)
	double StringParser( const char *s, CObList* pObjParser );
#endif

// Implementation
private:

	void			vFactor();
	void			vTerm();
	void			vExpression();
	void			vPush(struct TOKENREC *);
	void			advance();

	int				match(int token);
	int				nexttoken();
	int				miLegalLookAhead(int first_arg, ...);

	struct TOKENREC	vPop();

	virtual double	GetValue( const char *cpName );
	int				isfunc( char *s );

// Data
private:

	int 			miStackTop;
	int 			miLookAhead;	// Lookahead token

	long			memleft;

	const char*		mcpInput;

	char			mcError;

	struct TOKENREC	stack[PARSERSTACKSIZE], curtoken;

	CObList*		m_pObjParser;
};

#endif // __ZAMATH_H