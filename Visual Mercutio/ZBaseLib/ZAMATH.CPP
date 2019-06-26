//---------------------------------------------------------------------------
// Project     :     Math Functions
// Author    :     Dominique Aigroz            
// Filename  :     zamath.cpp
// Exe       :     zamath.dll
// Created   :     23.09.1994
// Modify    :     15/2/95    Dominique Aigroz
//                        Create C++ classe for the parser.
//
// Comments  :     This DLL contain a group of mathematics functions.
//                
//
// Call      : 
//
//---------------------------------------------------------------------------

#include <StdAfx.h>

#include "zamath.h"

#include <MATH.H>
#include <CTYPE.H>

// JMR-MODIF - Le 14 juin 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Local variables
LOCAL double (*mfncGetValue)(char *);    // Point the the Get value function.
                                        // When the parser found a name that is
                                        // not a token, not a number and not a
                                        // function he calls this function to 
                                        // retrieve the corresponding value.

/////////////////////////////////////////////////////////////////////////////
// ObjectParser

ObjectParser::ObjectParser()
{
}

ObjectParser::ObjectParser( const ObjectParser &right )
{
    *this = right;
}

ObjectParser::~ObjectParser()
{
}

ObjectParser* ObjectParser::CloneObject()
{
    ObjectParser* pObject = new ObjectParser( *this );
    return pObject;
}

/////////////////////////////////////////////////////////////////////////////
// Parser

Parser::Parser()
{
    m_pObjParser = NULL;
}

Parser::~Parser()
{
}

void Parser::vFactor()
{
    /* factor  -> num_or_id | FUNC | LP expression RP      */
    if ( !miLegalLookAhead( NUM, OPAREN, FUNC, 0 ) )
    {
        return;
    }

    if ( match( NUM ) )
    {
        vPush ( &curtoken );
        advance ();
    }
    else if ( match( OPAREN ) )
    {
        advance();
        vExpression();

        if ( match( CPAREN ) )
        {
            advance ();
        }
    }
    else if ( match( FUNC ) )
    {
        advance();
        advance();
        vExpression();

        if ( strcmp( curtoken.funcname, _T( "ABS" ) ) == 0 )
        {
            curtoken.value = fabs( curtoken.value );
        }
        else if ( strcmp( curtoken.funcname, _T( "ACOS" ) ) == 0 )
        {
            curtoken.value = acos( curtoken.value );
        }
        else if ( strcmp( curtoken.funcname, _T( "ASIN" ) ) == 0 )
        {
            curtoken.value = asin( curtoken.value );
        }
        else if ( strcmp( curtoken.funcname, _T( "ATAN" ) ) == 0 )
        {
            curtoken.value = atan( curtoken.value );
        }
        else if ( strcmp( curtoken.funcname, _T( "COSH" ) ) == 0 )
        {
            curtoken.value = cosh( curtoken.value );
        }
        else if ( strcmp( curtoken.funcname, _T( "COS" ) ) == 0 )
        {
            curtoken.value = cos( curtoken.value );
        }
        else if ( strcmp( curtoken.funcname, _T( "EXP" ) ) == 0 )
        {
            curtoken.value = exp( curtoken.value );
        }
        else if ( strcmp( curtoken.funcname, _T( "LOG10" ) ) == 0 )
        {
            curtoken.value = log10( curtoken.value );
        }
        else if ( strcmp( curtoken.funcname, _T( "LOG" ) ) == 0 )
        {
            curtoken.value = log( curtoken.value );
        }
        else if ( strcmp( curtoken.funcname, _T( "ROUND" ) ) == 0 )
        {
            curtoken.value = (int)( curtoken.value + 0.5 );
        }
        else if ( strcmp( curtoken.funcname, _T( "POW10" ) ) == 0 )
        {
            curtoken.value =pow( curtoken.value, 10 );
        }
        else if ( strcmp( curtoken.funcname, _T( "POW2" ) ) == 0 )
        {
            curtoken.value =pow( curtoken.value, 2 );
        }
        else if ( strcmp( curtoken.funcname, _T( "SINH" ) ) == 0 )
        {
            curtoken.value = sinh( curtoken.value );
        }
        else if ( strcmp( curtoken.funcname, _T( "SIN" ) ) == 0 )
        {
            curtoken.value = sin( curtoken.value );
        }
        else if ( strcmp( curtoken.funcname, _T( "SQRT" ) ) == 0 )
        {
            curtoken.value = sqrt( curtoken.value );
        }
        else if ( strcmp( curtoken.funcname, _T( "SQR" ) ) == 0 )
        {
            curtoken.value *= curtoken.value;
        }
        else if ( strcmp( curtoken.funcname, _T( "TANH" ) ) == 0 )
        {
            curtoken.value = tanh( curtoken.value );
        }
        else if ( strcmp( curtoken.funcname, _T( "TAN" ) ) == 0 )
        {
            curtoken.value = tan( curtoken.value );
        }
        else if ( strcmp( curtoken.funcname, _T( "TRUNC" ) ) == 0 )
        {
            curtoken.value = (int)curtoken.value;
        }

        vPop();
        vPush( &curtoken );

        if ( match( CPAREN ) )
        {
            advance();
        }
    }
}

void Parser::vTerm()
{
    /* term  -> factor term'                                *
     * term' -> TIMES factor term' | DIVIDE factor term' |    *
     * term' -> EXP factor term'   | epsilon                */

    struct TOKENREC tempvar, tempvar2;

    int wlookahead;

    if ( !miLegalLookAhead( NUM, OPAREN, FUNC, 0 ) )
    {
        return;
    }

    vFactor();

    while( match( TIMES ) || match( DIVIDE ) || match( EXP ) ||
           match( GT )    || match( LT )     || match( EQ )  || match( GTE ) ||
           match( LTE )   || match( NEQ )    || match( OR )  || match( AND ) )
    {
        wlookahead = miLookAhead;

        advance();
        vFactor();

        tempvar = vPop ();
        tempvar2 = vPop ();

        // Insert assertion to avoid the mathematic errors.
        TRY
        {
            switch ( wlookahead )
            {
                case TIMES :
                {
                    curtoken.value = tempvar.value * tempvar2.value;
                    break;
                }

                case DIVIDE :
                {
                    if ( tempvar.value == 0 )
                    {
                        curtoken.value = 0;
                    }
                    else
                    {
                        curtoken.value = tempvar2.value / tempvar.value;
                    }

                    break;
                }

                case EXP :
                {
                    curtoken.value = pow ( tempvar2.value, tempvar.value );
                    break;
                }

                case GT :
                {
                    curtoken.value = ( tempvar2.value > tempvar.value ) ? 1 : 0;
                    break;
                }

                case LT :
                {
                    curtoken.value = ( tempvar2.value < tempvar.value ) ? 1 : 0;
                    break;
                }

                case EQ :
                {
                    curtoken.value = ( tempvar2.value == tempvar.value ) ? 1 : 0;
                    break;
                }

                case GTE :
                {
                    curtoken.value = ( tempvar2.value >= tempvar.value ) ? 1 : 0;
                    break;
                }

                case LTE :
                {
                    curtoken.value = ( tempvar2.value <= tempvar.value ) ? 1 : 0;
                    break;
                }

                case NEQ :
                {
                    curtoken.value = ( tempvar2.value != tempvar.value ) ? 1 : 0;
                    break;
                }

                case OR :
                {
                    curtoken.value = ( tempvar2.value || tempvar.value ) ? 1 : 0;
                    break;
                }

                case AND :
                {
                    curtoken.value = ( tempvar2.value && tempvar.value ) ? 1 : 0;
                    break;
                }
            }
        }
        CATCH( CException, e )
        {
            CString str;
            str.LoadString( IDS_MATHERROR );
            AfxMessageBox( str );
            return;
        }
        END_CATCH

        vPush ( &curtoken );
    }
}

void Parser::vExpression()
{
    /* expression -> term expression' *
     * expression' -> PLUS term expression' | MINUS term expression' | epsilon */

    struct TOKENREC tempvar, tempvar2;

    int wlookahead;

    if ( !miLegalLookAhead( NUM, OPAREN, FUNC, 0 ) )
    {
        return;
    }

    vTerm();

    while ( match( PLUS ) || match( MINUS ) )
    {
        wlookahead = miLookAhead;

        advance();
        vTerm();

        tempvar = vPop();
        tempvar2 = vPop();

        // Insert assertion to avoid the mathematic errors.
        TRY
        {
            switch ( wlookahead )
            {
                case PLUS :
                {
                    curtoken.value = tempvar.value + tempvar2.value;
                    break;
                }

                case MINUS :
                {
                    curtoken.value = tempvar2.value - tempvar.value;
                    break;
                }
            }
        }
        CATCH(CException, e)
        {
            CString str;
            str.LoadString( IDS_MATHERROR );
            AfxMessageBox( str );
            return;
        }
        END_CATCH

        vPush (&curtoken);
    }
}

int Parser::match( int token )
{
    /* Return true if "token" matches the current lookahead symbol */

    if ( miLookAhead == -1 )
    {
        miLookAhead = nexttoken ();
    }

    return ( token == miLookAhead );
}

/*-----------------------*/
void Parser::advance()
{
    /* Advance the lookahead to the next input symbol */
    miLookAhead = nexttoken ();
}

int Parser::nexttoken()
{
    /* Gets the next token from the mcpInput stream */
    char *start, numstring[80];
    int decimal, len, numlen, sign;

    while ( *mcpInput == ' ' )
    {
        mcpInput++;
    }

    if ( *mcpInput == 0 )
    {
        return( EOI );
    }

    /* Test if the number is signed */
    sign = FALSE;

    if ( ( *mcpInput == '-' ) && ( isdigit( *( mcpInput + 1 ) ) ) )
    {
        /* Test if the previous token is an operator */
        if ( ( miLookAhead == -1 )    ||
             ( match( PLUS ) )        ||
             ( match( MINUS ) )        ||
             ( match( TIMES ) )        ||
             ( match( DIVIDE ) )    ||
             ( match( EXP ) ) )
        {
            sign = TRUE;
            mcpInput++;
        }
    }

    if ( strchr( _T( "0123456789." ), *mcpInput ) )
    {
        start    = (char *)mcpInput;
        len        = 0;
        decimal    = FALSE;

        while ( ( isdigit( *mcpInput ) ) || ( ( *mcpInput == '.' ) && ( !decimal ) ) )
        {
            if ( *mcpInput == '.' )
            {
                decimal = TRUE;
            }

            mcpInput++;
            len++;
        }

        if ( ( len == 1 ) && ( start[0] == '.' ) )
        {
            return( BAD );
        }

        if ( *mcpInput == 'E' )
        {
            mcpInput++;
            len++;

            if ( strchr( _T( "+-" ), *mcpInput ) != NULL )
            {
                mcpInput++;
                len++;
            }

            numlen = 0;

            while ( ( isdigit( *mcpInput ) ) && ( ++numlen <= 3 ) )
            {
                mcpInput++;
                len++;
            }
        }

        memmove( numstring, start, len );
        numstring[len] = 0;

        if ( sign == TRUE )
        {
            curtoken.value = 0 - atof( numstring );
        }
        else
        {
            curtoken.value = atof( numstring );
        }

        if ( errno == ERANGE )
        {
            return( BAD );
        }

        return( NUM );
    }
    else if( isalpha( *mcpInput ) || *mcpInput == '$' )
    {
        if ( isfunc( _T( "ABS" ) )        ||
            isfunc( _T( "ACOS" ) )        ||
            isfunc( _T( "ASIN" ) )        ||
            isfunc( _T( "ATAN" ) )        ||
            isfunc( _T( "COSH" ) )        ||
            isfunc( _T( "COS" ) )        ||
            isfunc( _T( "EXP" ) )        ||
            isfunc( _T( "LOG10" ) )    ||
            isfunc( _T( "LOG" ) )        ||
            isfunc( _T( "POW10" ) )    ||
            isfunc( _T( "ROUND" ) )    ||
            isfunc( _T( "SINH" ) )        ||
            isfunc( _T( "SIN" ) )        ||
            isfunc( _T( "SQRT" ) )        ||
            isfunc( _T( "SQR" ) )        ||
            isfunc( _T( "TANH" ) )        ||
            isfunc( _T( "TAN" ) )        ||
            isfunc( _T( "TRUNC" ) ) )
        {
            return( FUNC );
        }
        else
        {
            // See if it is a field
            start    = (char *)mcpInput;
            len        = 0;

            while ( ( *mcpInput != ' ' ) && *mcpInput )
            {
                mcpInput++;
                len++;
            }

            memmove ( numstring, start, len );
            numstring[len] = 0;

            // Check if any function has been given
            // otherwise the return is BAD
            if( m_pObjParser )
            {
                curtoken.value = GetValue( numstring );
            }
            else
            {
                return( BAD );
            }

            return( NUM );
        }

        return( BAD );
    }
    else
    {
        switch( *( mcpInput++ ) )
        {
            case '+' :
            {
                return( PLUS );
            }

            case '-' :
            {
                return( MINUS );
            }

            case '*' :
            {
                return( TIMES );
            }

            case '/' :
            {
                return( DIVIDE );
            }

            case '^' :
            {
                return( EXP );
            }

            case '(' :
            {
                return( OPAREN );
            }

            case ')' :
            {
                return( CPAREN );
            }

            case '>' :
            {
                // Before returning greater, test for greater and equal
                if ( *mcpInput == '=' )
                {
                    // Increment mcpInput
                    ++mcpInput;
                    return GTE;
                }

                return( GT );
            }

            case '<' :
            {
                // Before returning lessthan, test for lessthan equal and different
                switch ( *mcpInput )
                {
                    case '=' :
                    {
                        // Increment mcpInput
                        ++mcpInput;
                        return LTE;
                    }

                    case '>' :
                    {
                        // Increment mcpInput
                        ++mcpInput;
                        return NEQ;
                    }

                    default :
                    {
                        break;
                    }
                }

                return( LT );
            }

            case '=' :
            {
                return( EQ );
            }

            case '|' :
            {
                return( OR );
            }

            case '&' :
            {
                return( AND );
            }

            case '!' :
            {
                return( NOT );
            }

            default :
            {
                return( BAD );
            }
        }
    }
}

/* Error Recovery for the Improved Parser */

#define MAXFIRST    16
#define SYNCH        EOI

int Parser::miLegalLookAhead( int first_arg, ... )
{
    /* Simple error detection and recovery. Arguments are a 0-terminated *
     * list of those tokens that can legitimately come next in the input *
     * If the list is empty, the end of file must come next. Print an    *
     * error message if necessary. Error recovery is performed by discd- *
     * ing all input symbols until one that's in the input list is found *
     * Return true if there's no error or if we recovered from the error *
     * , false if we can't recover.                                      */

    va_list    args;
    int        tok;
    int        lookaheads[MAXFIRST], *p = lookaheads, *current;
    int        rval = 0;

    va_start( args, first_arg );

    if ( !first_arg )
    {
        if ( match( EOI ) )
        {
            rval = 1;
        }
    }
    else
    {
        *p++ = first_arg;

        while ( ( ( tok = va_arg( args, int ) ) != 0 ) && ( p < &lookaheads[MAXFIRST] ) )
        {
            *p++ = tok;
        }

        while ( !match( SYNCH ) )
        {
            for ( current=lookaheads; current < p ;++current )
            {
                if ( match ( *current ) )
                {
                    rval = 1;
                    goto exit;
                }
            }

            advance ();
        }
    }

exit:

    va_end(args);

    return rval;
}
//---------------------------------------------------------------------------
/* Returns TRUE if the string is a legal function, FALSE otherwise. */
int Parser::isfunc(char* pStr)
{
             int len = strlen(pStr);
    register int i;

    for (i = 0; i < len ; ++i)
        if (*(pStr + i) != toupper (*(mcpInput + i)))
            break;

    if (i < len)
        return FALSE;

    for (i = 0; i < len ; ++i)
        curtoken.funcname[i] = toupper(*(mcpInput + i));

    curtoken.funcname[len]  = 0;
    mcpInput               += len;

    return TRUE;
}
//---------------------------------------------------------------------------
void Parser::vPush(struct TOKENREC* pToken)
{
    // push a new token onto the stack
    if (miStackTop == PARSERSTACKSIZE - 1)
        mcError = TRUE;
    else
        stack[++miStackTop] = *pToken;
}
//---------------------------------------------------------------------------
struct TOKENREC Parser::vPop()
{
    /* Pops the top token off of the stack */
    return( stack[miStackTop--] );
}

double Parser::GetValue( const char *cpName )
{
    ObjectParser    *obj;
    POSITION        Position;

    // This function use the global pointer
    // of the list.
    // This pointer is set by the CalculateAllFormula function.
    Position = m_pObjParser->GetHeadPosition();

    while( Position )
    {
        obj = (ObjectParser *)m_pObjParser->GetNext( Position );

        if( strcmp( (const char *)obj->m_strObjName, cpName ) == 0 )
        {
            return( obj->GetValue() );
        }
    }

    return( 0 );
}

#ifndef _WIN32
double FAR PASCAL Parser::StringParser( const char *s, CObList* pObjParser )
#else
double Parser::StringParser( const char *s, CObList* pObjParser )
#endif
{
    m_pObjParser    = pObjParser;
    miLookAhead        = -1;
    mcError            = FALSE;
    mcpInput        = s;
    miStackTop        = -1;

    vExpression();

    if ( mcError )
    {
        return( 0 );
    }

    return( curtoken.value );
}
