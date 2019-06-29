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
        PSS_SoapData_SymbolAttributes()
        {}

        PSS_SoapData_SymbolAttributes(int pdAttribID, int prow, int attribDefID, const PSS_String16& mValue, int statICyn) :
            m_PdAttribID(pdAttribID),
            m_Prow(prow),
            m_AttribDefID(attribDefID),
            m_MValue(PSS_StringTools::ConvertTo(mValue)),
            m_StatICyn(statICyn)
        {}
};

#endif
