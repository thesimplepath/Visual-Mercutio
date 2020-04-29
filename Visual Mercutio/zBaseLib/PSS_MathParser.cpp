/****************************************************************************
 * ==> PSS_MathParser ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a mathematical formulas parser                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_MathParser.h"

// std
#include <Math.h>
#include <Ctype.h>

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_Plus_Func   0
#define M_Minus_Func  1
#define M_Times_Func  2
#define M_Divide_Func 3
#define M_Exp_Func    4
#define M_Oparen_Func 5
#define M_Cparen_Func 6
#define M_Num_Func    7
#define M_Func_Func   8
#define M_Gt_Func     9
#define M_Lt_Func     10
#define M_Eq_Func     11
#define M_Gte_Func    12
#define M_Lte_Func    13
#define M_Neq_Func    14
#define M_Or_Func     15
#define M_And_Func    16
#define M_Not_Func    17
#define M_Field_Func  21
#define M_Eoi_Func    22
#define M_Bad_Func    23
#define M_Synch_Func  M_Eoi_Func
#define M_MaxFirst    16
//---------------------------------------------------------------------------
// Callbacks
//---------------------------------------------------------------------------
// point the the Get value function. When the parser found a name that is not a token,
// not a number and not a function, he calls this function to retrieve the corresponding
// value
LOCAL double (*fMfncGetValue)(char*); 
//---------------------------------------------------------------------------
// PSS_FormulaObjectParser
//---------------------------------------------------------------------------
PSS_FormulaObjectParser::PSS_FormulaObjectParser() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_FormulaObjectParser::PSS_FormulaObjectParser(const PSS_FormulaObjectParser& other) :
    CObject()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_FormulaObjectParser::~PSS_FormulaObjectParser()
{}
//---------------------------------------------------------------------------
PSS_FormulaObjectParser* PSS_FormulaObjectParser::CloneObject() const
{
    std::unique_ptr<PSS_FormulaObjectParser> pObject(new PSS_FormulaObjectParser(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
// PSS_FormulaParser
//---------------------------------------------------------------------------
PSS_FormulaParser::PSS_FormulaParser() :
    m_pObjParser(NULL),
    m_pInput(NULL),
    m_Memleft(0),
    m_StackTop(0),
    m_LookAhead(0),
    m_Error(0x0)
{
    m_pObjParser = NULL;
}
//---------------------------------------------------------------------------
PSS_FormulaParser::~PSS_FormulaParser()
{}
//---------------------------------------------------------------------------
#ifndef _WIN32
    double FAR PASCAL PSS_FormulaParser::StringParser(const char* pStr, CObList* pObjParser)
#else
    double PSS_FormulaParser::StringParser(const char* pStr, CObList* pObjParser)
#endif
{
    m_pObjParser =  pObjParser;
    m_pInput     =  pStr;
    m_StackTop   = -1;
    m_LookAhead  = -1;
    m_Error      =  0x0;

    ParseExpression();

    if (m_Error)
        return 0;

    return m_CurToken.m_Value;
}
//---------------------------------------------------------------------------
void PSS_FormulaParser::ParseFactor()
{
    // factor -> num_or_id | FUNC | LP expression RP
    if (!LegalLookAhead(M_Num_Func, M_Oparen_Func, M_Func_Func, 0))
        return;

    if (Match(M_Num_Func))
    {
        Push(&m_CurToken);
        MoveNext();
    }
    else
    if (Match(M_Oparen_Func))
    {
        MoveNext();
        ParseExpression();

        if (Match(M_Cparen_Func))
            MoveNext();
    }
    else
    if (Match(M_Func_Func))
    {
        MoveNext();
        MoveNext();
        ParseExpression();

        if (!std::strcmp(m_CurToken.m_FuncName, _T("ABS")))
            m_CurToken.m_Value = std::fabs(m_CurToken.m_Value);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("ACOS")))
            m_CurToken.m_Value = std::acos(m_CurToken.m_Value);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("ASIN")))
            m_CurToken.m_Value = std::asin(m_CurToken.m_Value);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("ATAN")))
            m_CurToken.m_Value = std::atan(m_CurToken.m_Value);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("COSH")))
            m_CurToken.m_Value = std::cosh(m_CurToken.m_Value);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("COS")))
            m_CurToken.m_Value = std::cos(m_CurToken.m_Value);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("EXP")))
            m_CurToken.m_Value = std::exp(m_CurToken.m_Value);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("LOG10")))
            m_CurToken.m_Value = std::log10(m_CurToken.m_Value);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("LOG")))
            m_CurToken.m_Value = std::log(m_CurToken.m_Value);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("ROUND")))
            m_CurToken.m_Value = int(m_CurToken.m_Value + 0.5);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("POW10")))
            m_CurToken.m_Value = std::pow(m_CurToken.m_Value, 10);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("POW2")))
            m_CurToken.m_Value = std::pow(m_CurToken.m_Value, 2);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("SINH")))
            m_CurToken.m_Value = std::sinh(m_CurToken.m_Value);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("SIN")))
            m_CurToken.m_Value = std::sin(m_CurToken.m_Value);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("SQRT")))
            m_CurToken.m_Value = std::sqrt(m_CurToken.m_Value);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("SQR")))
            m_CurToken.m_Value *= m_CurToken.m_Value;
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("TANH")))
            m_CurToken.m_Value = std::tanh(m_CurToken.m_Value);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("TAN")))
            m_CurToken.m_Value = std::tan(m_CurToken.m_Value);
        else
        if (!std::strcmp(m_CurToken.m_FuncName, _T("TRUNC")))
            m_CurToken.m_Value = int(m_CurToken.m_Value);

        Pop();
        Push(&m_CurToken);

        if (Match(M_Cparen_Func))
            MoveNext();
    }
}
//---------------------------------------------------------------------------
void PSS_FormulaParser::ParseTerm()
{
    // term  -> factor term'
    // term' -> TIMES factor term' | DIVIDE factor term' |
    // term' -> EXP factor term'   | epsilon
    if (!LegalLookAhead(M_Num_Func, M_Oparen_Func, M_Func_Func, 0))
        return;

    ParseFactor();

    while (Match(M_Times_Func) || Match(M_Divide_Func) || Match(M_Exp_Func) ||
           Match(M_Gt_Func)    || Match(M_Lt_Func)     || Match(M_Eq_Func)  || Match(M_Gte_Func) ||
           Match(M_Lte_Func)   || Match(M_Neq_Func)    || Match(M_Or_Func)  || Match(M_And_Func))
    {
        const int lookAhead = m_LookAhead;

        MoveNext();
        ParseFactor();

        const struct PSS_TokenRec tempVar  = Pop();
        const struct PSS_TokenRec tempVar2 = Pop();

        // insert assertion to avoid the mathematic errors
        TRY
        {
            switch (lookAhead)
            {
                case M_Times_Func:  m_CurToken.m_Value = (tempVar.m_Value * tempVar2.m_Value);                        break;
                case M_Divide_Func: m_CurToken.m_Value = (!tempVar.m_Value ? 0 : tempVar2.m_Value / tempVar.m_Value); break;
                case M_Exp_Func:    m_CurToken.m_Value = std::pow(tempVar2.m_Value, tempVar.m_Value);                 break;
                case M_Gt_Func:     m_CurToken.m_Value = (tempVar2.m_Value >  tempVar.m_Value ? 1 : 0);               break;
                case M_Lt_Func:     m_CurToken.m_Value = (tempVar2.m_Value <  tempVar.m_Value ? 1 : 0);               break;
                case M_Eq_Func:     m_CurToken.m_Value = (tempVar2.m_Value == tempVar.m_Value ? 1 : 0);               break;
                case M_Gte_Func:    m_CurToken.m_Value = (tempVar2.m_Value >= tempVar.m_Value ? 1 : 0);               break;
                case M_Lte_Func:    m_CurToken.m_Value = (tempVar2.m_Value <= tempVar.m_Value ? 1 : 0);               break;
                case M_Neq_Func:    m_CurToken.m_Value = (tempVar2.m_Value != tempVar.m_Value ? 1 : 0);               break;
                case M_Or_Func:     m_CurToken.m_Value = (tempVar2.m_Value || tempVar.m_Value ? 1 : 0);               break;
                case M_And_Func:    m_CurToken.m_Value = (tempVar2.m_Value && tempVar.m_Value ? 1 : 0);               break;
            }
        }
        CATCH (CException, e)
        {
            CString str;
            str.LoadString(IDS_MATHERROR);
            AfxMessageBox(str);
            return;
        }
        END_CATCH

        Push(&m_CurToken);
    }
}
//---------------------------------------------------------------------------
void PSS_FormulaParser::ParseExpression()
{
    // expression  -> term expression'
    // expression' -> PLUS term expression' | MINUS term expression' | epsilon
    if (!LegalLookAhead(M_Num_Func, M_Oparen_Func, M_Func_Func, 0))
        return;

    ParseTerm();

    while (Match(M_Plus_Func) || Match(M_Minus_Func))
    {
        const int lookAhead = m_LookAhead;

        MoveNext();
        ParseTerm();

        const struct PSS_TokenRec tempVar  = Pop();
        const struct PSS_TokenRec tempVar2 = Pop();

        // insert assertion to avoid the mathematic errors
        TRY
        {
            switch (lookAhead)
            {
                case M_Plus_Func:
                    m_CurToken.m_Value = tempVar.m_Value + tempVar2.m_Value;
                    break;

                case M_Minus_Func:
                    m_CurToken.m_Value = tempVar2.m_Value - tempVar.m_Value;
                    break;
            }
        }
        CATCH(CException, e)
        {
            CString str;
            str.LoadString(IDS_MATHERROR);
            AfxMessageBox(str);
            return;
        }
        END_CATCH

        Push(&m_CurToken);
    }
}
//---------------------------------------------------------------------------
void PSS_FormulaParser::MoveNext()
{
    m_LookAhead = SelectNextToken();
}
//---------------------------------------------------------------------------
int PSS_FormulaParser::SelectNextToken()
{
    // get the next token from the input stream
    while (*m_pInput == ' ')
        ++m_pInput;

    if (*m_pInput == 0)
        return(M_Eoi_Func);

    // check if the number is signed
    int sign = 0;

    if (*m_pInput == '-' && isdigit(*(m_pInput + 1)))
        // check if the previous token is an operator
        if ((m_LookAhead == -1)    ||
            (Match(M_Plus_Func))   ||
            (Match(M_Minus_Func))  ||
            (Match(M_Times_Func))  ||
            (Match(M_Divide_Func)) ||
            (Match(M_Exp_Func)))
        {
            sign = 1;
            ++m_pInput;
        }

    if (std::strchr(_T("0123456789."), *m_pInput))
    {
        char* pStart  = (char*)m_pInput;
        int   len     = 0;
        int   decimal = 0;

        while (isdigit(*m_pInput) || (*m_pInput == '.' && !decimal))
        {
            if (*m_pInput == '.')
                decimal = 1;

            ++m_pInput;
            ++len;
        }

        if (len == 1 && pStart[0] == '.')
            return M_Bad_Func;

        if (*m_pInput == 'E')
        {
            ++m_pInput;
            ++len;

            if (std::strchr(_T("+-"), *m_pInput))
            {
                ++m_pInput;
                ++len;
            }

            int numLen = 0;

            while (isdigit(*m_pInput) && (++numLen <= 3))
            {
                ++m_pInput;
                ++len;
            }
        }

        char numString[80];
        std::memmove(numString, pStart, len);
        numString[len] = 0;

        if (sign)
            m_CurToken.m_Value = 0 - std::atof(numString);
        else
            m_CurToken.m_Value = std::atof(numString);

        if (errno == ERANGE)
            return M_Bad_Func;

        return M_Num_Func;
    }
    else
    if (isalpha(*m_pInput) || *m_pInput == '$')
    {
        if (IsFunc(_T("ABS"))   ||
            IsFunc(_T("ACOS"))  ||
            IsFunc(_T("ASIN"))  ||
            IsFunc(_T("ATAN"))  ||
            IsFunc(_T("COSH"))  ||
            IsFunc(_T("COS"))   ||
            IsFunc(_T("EXP"))   ||
            IsFunc(_T("LOG10")) ||
            IsFunc(_T("LOG"))   ||
            IsFunc(_T("POW10")) ||
            IsFunc(_T("ROUND")) ||
            IsFunc(_T("SINH"))  ||
            IsFunc(_T("SIN"))   ||
            IsFunc(_T("SQRT"))  ||
            IsFunc(_T("SQR"))   ||
            IsFunc(_T("TANH"))  ||
            IsFunc(_T("TAN"))   ||
            IsFunc(_T("TRUNC")))
            return(M_Func_Func);

        // check if it's a field
        char* pStart = (char*)m_pInput;
        int   len    = 0;

        while ((*m_pInput != ' ') && *m_pInput)
        {
            ++m_pInput;
            ++len;
        }

        char numString[80];
        std::memmove(numString, pStart, len);
        numString[len] = 0;

        // check if a function was defined, otherwise return a failure
        if (m_pObjParser)
            m_CurToken.m_Value = GetValue(numString);
        else
            return(M_Bad_Func);

        return M_Num_Func;
    }
    else
    {
        const char input = *m_pInput;
        ++m_pInput;

        switch (input)
        {
            case '+': return M_Plus_Func;
            case '-': return M_Minus_Func;
            case '*': return M_Times_Func;
            case '/': return M_Divide_Func;
            case '^': return M_Exp_Func;
            case '(': return M_Oparen_Func;
            case ')': return M_Cparen_Func;

            case '>':
                // before returning greater, check for greater and equal
                if (*m_pInput == '=')
                {
                    // increment input position
                    ++m_pInput;
                    return M_Gte_Func;
                }

                return M_Gt_Func;

            case '<':
            {
                // before returning less than, check for less than equal and different
                switch (*m_pInput)
                {
                    case '=':
                        // increment input position
                        ++m_pInput;
                        return M_Lte_Func;

                    case '>':
                        // increment input position
                        ++m_pInput;
                        return M_Neq_Func;

                    default:
                        break;
                }

                return M_Lt_Func;
            }

            case '=': return M_Eq_Func;
            case '|': return M_Or_Func;
            case '&': return M_And_Func;
            case '!': return M_Not_Func;
            default:  return M_Bad_Func;
        }
    }
}
//---------------------------------------------------------------------------
int PSS_FormulaParser::Match(int token)
{
    // return true if "token" matches the current look ahead symbol
    if (m_LookAhead == -1)
        m_LookAhead = SelectNextToken();

    return (token == m_LookAhead);
}
//---------------------------------------------------------------------------

int PSS_FormulaParser::LegalLookAhead(int firstArg, ...)
{
    // simple error detection and recovery. Arguments are a 0-terminated, list of those tokens that
    // can legitimately come next in the input. If the list is empty, the end of file must come next.
    // Print an error message if necessary. Error recovery is performed by discording all input symbols
    // until one that's in the input list is found. Return true if there's no error or if we recovered
    // from the error, false if can't recover.
    va_list args;
    int     tok;
    int     lookAheads[M_MaxFirst];
    int*    pPtr     = lookAheads;
    int*    pCurrent = NULL;
    int     result   = 0;

    va_start(args, firstArg);

    if (!firstArg)
    {
        if (Match(M_Eoi_Func))
            result = 1;
    }
    else
    {
        *pPtr = firstArg;
        ++pPtr;

        while ((tok = va_arg(args, int)) && pPtr < &lookAheads[M_MaxFirst])
        {
            *pPtr = tok;
            ++pPtr;
        }

        while (!Match(M_Synch_Func))
        {
            for (pCurrent = lookAheads; pCurrent < pPtr; ++pCurrent)
                if (Match(*pCurrent))
                {
                    result = 1;
                    va_end(args);
                    return result;
                }

            MoveNext();
        }
    }

    va_end(args);
    return result;
}
//---------------------------------------------------------------------------
double PSS_FormulaParser::GetValue(const char* pName)
{
    // this function use the list global pointer. This pointer is set by the CalculateAllFormula() function
    POSITION pPosition = m_pObjParser->GetHeadPosition();

    while (pPosition)
    {
        PSS_FormulaObjectParser* pObj = static_cast<PSS_FormulaObjectParser*>(m_pObjParser->GetNext(pPosition));
        PSS_Assert(pObj);

        if (pObj->CompareByName(pName))
            return pObj->GetValue();
    }

    return 0;
}
//---------------------------------------------------------------------------
int PSS_FormulaParser::IsFunc(char* pStr)
{
    const    int len = std::strlen(pStr);
    register int i;

    for (i = 0; i < len; ++i)
        if (*(pStr + i) != toupper(*(m_pInput + i)))
            break;

    if (i < len)
        return 0;

    for (i = 0; i < len; ++i)
        m_CurToken.m_FuncName[i] = toupper(*(m_pInput + i));

    m_CurToken.m_FuncName[len] = 0;
    m_pInput += len;

    return 1;
}
//---------------------------------------------------------------------------
void PSS_FormulaParser::Push(struct PSS_TokenRec* pToken)
{
    // push a new token onto the stack
    if (m_StackTop == M_ParserStackSize - 1)
        m_Error = 1;
    else
        m_Stack[++m_StackTop] = *pToken;
}
//---------------------------------------------------------------------------
struct PSS_FormulaParser::PSS_TokenRec PSS_FormulaParser::Pop()
{
    // pop the top token off of the stack
    return m_Stack[m_StackTop--];
}
//---------------------------------------------------------------------------
