/****************************************************************************
 * ==> PSS_ProcRisk --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the procedures for risks                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcRiskH
#define PSS_ProcRiskH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_ProcRisk
    //#define PSS_ProcRisk ZBProcRisk
#endif

// old class name mapping
#ifndef PSS_RiskPropertiesBP
    #define PSS_RiskPropertiesBP ZBBPRiskProperties
#endif

class PSS_RiskPropertiesBP;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// scope symbols in stingray foundation library
using namespace sfl;

typedef CCArray_T<PSS_RiskPropertiesBP*, PSS_RiskPropertiesBP*> ZBBPRiskPropertiesSet;
typedef Iterator_T<PSS_RiskPropertiesBP*> ZBBPRiskPropertiesIterator;

/**
* Procedures for risks
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZBProcRisk : public CObject
{
    DECLARE_SERIAL(ZBProcRisk)

public:

    ZBProcRisk(CODSymbolComponent* pParent = NULL);
    virtual ~ZBProcRisk();

    ZBProcRisk(const ZBProcRisk& src);

    ZBProcRisk& operator=(const ZBProcRisk& src);

    virtual ZBProcRisk* Dup() const;

    void SetParent(CODSymbolComponent* pParent);

    int AddNewRisk();
    int AddRisk(PSS_RiskPropertiesBP* pProperty);

    bool CreateInitialProperties();
    bool DeleteRisk(size_t Index);
    bool DeleteRisk(PSS_RiskPropertiesBP* pProperty);
    bool RiskNameExist(const CString Name) const;

    CString GetNextRiskValidName() const;

    // Obtient le pointeur du groupe des propriétés.
    ZBBPRiskPropertiesSet& GetRiskSet()
    {
        return m_Set;
    };

    // Obtient le nombre de propriétés contenues dans l'ensemble.
    size_t GetRiskCount() const
    {
        return m_Set.GetSize();
    };

    // Obtient la propriété contenue à l'index spécifié.
    PSS_RiskPropertiesBP* GetProperty(size_t Index) const
    {
        if (Index < GetRiskCount())
        {
            return m_Set.GetAt(Index);
        }

        return NULL;
    };

    void RemoveAllRisks();

    CString GetRiskName(size_t Index) const;
    void SetRiskName(size_t Index, CString Value);

    CString GetRiskDesc(size_t Index) const;
    void SetRiskDesc(size_t Index, CString Value);

    CString GetRiskType(size_t Index) const;
    void SetRiskType(size_t Index, CString Value);

    int GetRiskImpact(size_t Index) const;
    void SetRiskImpact(size_t Index, int Value);

    int GetRiskProbability(size_t Index) const;
    void SetRiskProbability(size_t Index, int Value);

    int GetRiskSeverity(size_t Index) const;
    void SetRiskSeverity(size_t Index, int Value);

    float GetRiskUE(size_t Index) const;
    void SetRiskUE(size_t Index, float Value);

    float GetRiskPOA(size_t Index) const;
    void SetRiskPOA(size_t Index, float Value);

    bool GetRiskAction(size_t Index) const;
    void SetRiskAction(size_t Index, bool Value);

    virtual void Serialize(CArchive& ar);

private:
    CODSymbolComponent*   m_pParent;
    ZBBPRiskPropertiesSet m_Set;
};

#endif
