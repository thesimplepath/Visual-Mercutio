// **************************************************************************************************************
// *                            Classe ZUExtractModelLogicalPrestationsAssigned                                    *
// **************************************************************************************************************
// * JMR-MODIF - Le 20 février 2006 - Ajout de la classe ZUExtractModelLogicalPrestationsAssigned.                *
// **************************************************************************************************************
// * Cette classe permet de déterminer quelle prestation est attibuée à quel symbole. A partir de cette liste,    *
// * il est possible de reconstruire la hiérarchie des liens existants entre symboles et prestations.            *
// **************************************************************************************************************

#if !defined(AFX_ZUExtractModelLogicalPrestationsAssigned_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUExtractModelLogicalPrestationsAssigned_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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

#include "zModel\ZUModelNavigation.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBPrestationsEntity;

#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZUExtractModelLogicalPrestationsAssigned : public ZUModelNavigation
{
public:

    ZUExtractModelLogicalPrestationsAssigned(ZDProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);
    virtual ~ZUExtractModelLogicalPrestationsAssigned();

    CODComponentSet& GetComponentSet()
    {
        return m_Set;
    };

    // Call-back methods
    virtual bool OnStart();
    virtual bool OnFinish();

    virtual bool OnSymbol(ZBSymbol* pSymbol);
    virtual bool OnLink(PSS_LinkSymbol* pLink);

private:

    ZBPrestationsEntity*    m_pPrestationsEntity;
    CODComponentSet            m_Set;
};

#endif // !defined(AFX_ZUExtractModelLogicalPrestationsAssigned_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)