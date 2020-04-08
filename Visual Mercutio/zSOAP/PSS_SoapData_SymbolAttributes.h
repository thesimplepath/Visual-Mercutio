/****************************************************************************
 * ==> PSS_SoapData_SymbolAttributes ---------------------------------------*
 ****************************************************************************
 * Description : SOAP data containing the symbol attributes                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapData_SymbolAttributeH
#define PSS_SoapData_SymbolAttributeH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zConversion\PSS_String16.h"
#include "zConversion\PSS_StringTools.h"

#ifdef _ZSOAPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* SOAP data containing a symbol attribute
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapData_SymbolAttributes
{
    public:
        int         m_PdAttribID;
        int         m_Prow;
        int         m_AttribDefID;
        std::string m_MValue;
        int         m_StatICyn;

        /**
        * Constructor
        */
        PSS_SoapData_SymbolAttributes() :
            m_PdAttribID(-1),
            m_Prow(-1),
            m_AttribDefID(-1),
            m_StatICyn(-1)
        {}

        /**
        * Constructor
        *@param attribID - the attribute identifier
        *@param row - the row count
        *@param attribDefID - the attribute default identifier
        *@param value - the value
        *@param isStatOrDyn - if 0 the attribute is static, if 1 the attribute is dynamic
        */
        PSS_SoapData_SymbolAttributes(int attribID, int row, int attribDefID, const PSS_String16& value, int isStatOrDyn) :
            m_PdAttribID(attribID),
            m_Prow(row),
            m_AttribDefID(attribDefID),
            m_MValue(PSS_StringTools::ConvertTo(value)),
            m_StatICyn(isStatOrDyn)
        {}
};

#endif
