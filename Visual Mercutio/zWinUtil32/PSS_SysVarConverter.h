/****************************************************************************
 * ==> PSS_SysVarConverter -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a system variables converter to its content       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SysVarConverterH
#define PSS_SysVarConverterH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_Document.h"
#include "zEvent\PSS_Process.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

 //---------------------------------------------------------------------------
 // Global variables
 //---------------------------------------------------------------------------
const char g_Today[]            = "$$Today$$";
const char g_FileName[]         = "$$Filename$$";
const char g_ExchFileName[]     = "$$ExchFilename$$";
const char g_ProcExchFileName[] = "$$ProcExchFilename$$";
const char g_Author[]           = "$$Author$$";
const char g_Modifier[]         = "$$Modifier$$";
const char g_CreationDate[]     = "$$CreationDate$$";
const char g_ModificationDate[] = "$$ModificationDate$$";
const char g_PublishDate[]      = "$$PublishDate$$";
const char g_FileVer[]          = "$$FileVer$$";
//---------------------------------------------------------------------------

/**
* System variables converter to its content
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SysVarConverter
{
    public:
        /**
        * constructor
        *@param pDoc - document
        *@param pProcess - process
        */
        PSS_SysVarConverter(PSS_Document* pDoc = NULL, PSS_Process* pProcess = NULL);

        virtual ~PSS_SysVarConverter();

        /**
        * Initializes the converter
        *@param pDoc - document
        *@param pProcess - process
        */
        virtual void Initialize(PSS_Document* pDoc = NULL, PSS_Process* pProcess = NULL);

        /**
        * Parses the line and replace keywords with its value
        *@param line - line to parse
        *@return parsed line
        */
        virtual CString Parse(const CString& line);

    private:
        PSS_Document* m_pDoc;
        PSS_Process*  m_pProcess;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_SysVarConverter(const PSS_SysVarConverter& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_SysVarConverter& operator = (const PSS_SysVarConverter& other);

        /**
        * Gets the variable content
        *@param variable - variable for which content should be get
        *@return the variable content
        */
        CString GetVariableContent(const CString& variable);

        /**
        * Finds a keyword
        *@param line - line in which keyword should be found
        *@param pStartPos - found start position on function ends, if keyword was found
        *@param pEndPos - found end position on function ends, if keyword was found
        *@return the found keyword, empty string if not found or on error
        */
        CString FindKeyword(const CString& line, int* pStartPos, int* pEndPos);
};

#endif
