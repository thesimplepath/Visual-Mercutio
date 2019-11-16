/****************************************************************************
 * ==> PSS_MathParser ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a mathematical formulas parser                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MathParserH
#define PSS_MathParserH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_ParserStackSize 20
#define M_MaxFuncNameLen  5
//---------------------------------------------------------------------------

/**
* Mathematical formula object parser
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FormulaObjectParser : public CObject
{
    public:
        typedef CObject inherited;

        PSS_FormulaObjectParser();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FormulaObjectParser(const PSS_FormulaObjectParser& other);

        virtual ~PSS_FormulaObjectParser();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        inline const PSS_FormulaObjectParser& operator = (const PSS_FormulaObjectParser& other);

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        inline const PSS_FormulaObjectParser& operator = (const PSS_FormulaObjectParser* pOther);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_FormulaObjectParser* CloneObject() const;

        /**
        * Gets the value
        *@return the value
        */
        virtual inline double GetValue() const;

        /**
        * Gets the object name
        *@return the object name
        */
        virtual inline const CString& GetObjectName();

        /**
        * Sets the object name
        *@param name - the object name
        */
        virtual inline void SetObjectName(const CString& name);

        /**
        * Compare objects by name
        *@param pName - object name to compare with
        *@return true if object names match, otherwise false
        */
        virtual inline bool CompareByName(const char* pName) const;

    private:
        CString m_ObjName;
};

//---------------------------------------------------------------------------
// PSS_FormulaObjectParser
//---------------------------------------------------------------------------
const PSS_FormulaObjectParser& PSS_FormulaObjectParser::operator = (const PSS_FormulaObjectParser& other)
{
    m_ObjName = other.m_ObjName; return *this;
}
//---------------------------------------------------------------------------
const PSS_FormulaObjectParser& PSS_FormulaObjectParser::operator = (const PSS_FormulaObjectParser* pOther)
{
    m_ObjName = pOther->m_ObjName; return *this;
}
//---------------------------------------------------------------------------
double PSS_FormulaObjectParser::GetValue() const
{
    return 0;
}
//---------------------------------------------------------------------------
const CString& PSS_FormulaObjectParser::GetObjectName()
{
    return m_ObjName;
}
//---------------------------------------------------------------------------
void PSS_FormulaObjectParser::SetObjectName(const CString& name)
{
    m_ObjName = name;
}
//---------------------------------------------------------------------------
bool PSS_FormulaObjectParser::CompareByName(const char* pName) const
{
    return (!std::strcmp((const char*)m_ObjName, pName));
}
//---------------------------------------------------------------------------

/**
* Mathematical formula parser
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FormulaParser
{
    public:
        PSS_FormulaParser();
        virtual ~PSS_FormulaParser();

        /**
        * Parses a string
        *@param pStr - string to parse
        *@param pObjParser - object parser
        *@return parse result
        */
        #ifndef _WIN32
            virtual double FAR PASCAL StringParser(const char* pStr, CObList* pObjParser);
        #else
            virtual double StringParser(const char* pStr, CObList* pObjParser);
        #endif

    private:
        /**
        * Token record
        */
        struct PSS_TokenRec
        {
            double m_Value;
            char   m_FuncName[M_MaxFuncNameLen + 1];
        };

        struct PSS_TokenRec m_Stack[M_ParserStackSize];
        struct PSS_TokenRec m_CurToken;
        CObList*            m_pObjParser;
        const char*         m_pInput;
        long                m_Memleft;
        int                 m_StackTop;
        int                 m_LookAhead;
        char                m_Error;

        /**
        * Parses a factor
        */
        void ParseFactor();

        /**
        * Parses a term
        */
        void ParseTerm();

        /**
        * Parses an expression
        */
        void ParseExpression();

        /**
        * Moves to the next input symbol
        */
        void MoveNext();

        /**
        * Selects the next token
        *@return next selected token
        */
        int SelectNextToken();

        /**
        * Compare a token with the current one
        *@param token - token to compare with
        *@return 1 if the token matches with the current one, otherwise 0
        */
        int Match(int token);

        /**
        * Legal look ahead
        *@param firstArg - first argument, followed by an argument list
        */
        int LegalLookAhead(int firstArg, ...);

        /**
        * Gets the value matching with the name
        *@param pName - name
        *@return value
        */
        double GetValue(const char* pName);

        /**
        * Checks if a string contains a legal function
        *@param pStr - string
        *@return 1 if the string contains a legal function, otherwise 0
        */
        int IsFunc(char* pStr);

        /**
        * Pushes a token on the stack
        *@param pToken - token to push on the stack
        */
        void Push(struct PSS_TokenRec* pToken);

        /**
        * Popes a token from the stack
        *@return the popped token
        */
        struct PSS_TokenRec Pop();
};

#endif
