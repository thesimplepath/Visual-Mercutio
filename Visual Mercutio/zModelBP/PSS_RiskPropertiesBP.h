/****************************************************************************
 * ==> PSS_RiskPropertiesBP ------------------------------------------------*
 ****************************************************************************
 * Description : Provides the risk properties for banking process           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RiskPropertiesBPH
#define PSS_RiskPropertiesBPH

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
#ifndef PSS_RiskPropertiesBP
    #define PSS_RiskPropertiesBP ZBBPRiskProperties
#endif

// resources
#include "PSS_PropIDs.h"

#ifdef _ZMODELBPEXPORT
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
#define M_Risk_Name_ID        1
#define M_Risk_Desc_ID        2
#define M_Risk_Type_ID        3
#define M_Risk_Impact_ID      4
#define M_Risk_Probability_ID 5
#define M_Risk_Severity_ID    6
#define M_Risk_UE_ID          7
#define M_Risk_POA_ID         8
#define M_Risk_Action_ID      9
//---------------------------------------------------------------------------

/**
* Risk properties for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_RiskPropertiesBP : public CObject
{
    DECLARE_SERIAL(PSS_RiskPropertiesBP)

    public:
        /**
        * Change type
        *@note These items may be combinated
        */
        enum IEChangeType
        {
            IE_CT_Change_Risk_Name        = 0x0001,
            IE_CT_Change_Risk_Desc        = 0x0002,
            IE_CT_Change_Risk_Type        = 0x0004,
            IE_CT_Change_Risk_Impact      = 0x0008,
            IE_CT_Change_Risk_Probability = 0x0010,
            IE_CT_Change_Risk_Severity    = 0x0020,
            IE_CT_Change_Risk_UE          = 0x0040,
            IE_CT_Change_Risk_POA         = 0x0080,
            IE_CT_Change_Risk_Action      = 0x0100,
            IE_CT_All                     = OD_CHANGE_ALL
        };

        PSS_RiskPropertiesBP();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_RiskPropertiesBP(const PSS_RiskPropertiesBP& other);

        virtual ~PSS_RiskPropertiesBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_RiskPropertiesBP& operator = (const PSS_RiskPropertiesBP& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_RiskPropertiesBP& other) const;

        /**
        * Makes a copy of this properties object
        *@return a copy of this properties object, NULL on error
        */
        virtual inline PSS_RiskPropertiesBP* Dup() const;

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(PSS_RiskPropertiesBP* pProp, DWORD changeFlags = IE_CT_All);

        /**
        * Checks if another set of properties is equal to this one
        *@param pProp - other property set to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        virtual BOOL IsEqual(PSS_RiskPropertiesBP* pProp);

        /**
        * Gets the risk name
        *@return the risk name
        */
        virtual inline CString GetRiskName() const;

        /**
        * Sets the risk name
        *@param value - the risk name
        */
        virtual void SetRiskName(LPCTSTR pValue);

        /**
        * Gets the risk description
        *@return the risk description
        */
        virtual inline CString GetRiskDesc() const;

        /**
        * Sets the risk description
        *@param value - the risk description
        */
        virtual void SetRiskDesc(LPCTSTR pValue);

        /**
        * Gets the risk type
        *@return the risk type
        */
        virtual inline CString GetRiskType() const;

        /**
        * Sets the risk type
        *@param value - the risk type
        */
        virtual void SetRiskType(LPCTSTR pValue);

        /**
        * Gets the risk impact
        *@return the risk impact
        */
        virtual inline int GetRiskImpact() const;

        /**
        * Sets the risk impact
        *@param value - the risk impact
        */
        virtual inline void SetRiskImpact(const int value);

        /**
        * Gets the risk probability
        *@return the risk probability
        */
        virtual inline int GetRiskProbability() const;

        /**
        * Sets the risk probability
        *@param value - the risk probability
        */
        virtual inline void SetRiskProbability(const int value);

        /**
        * Gets the risk severity
        *@return the risk severity
        */
        virtual inline int GetRiskSeverity() const;

        /**
        * Sets the risk severity
        *@param value - the risk severity
        */
        virtual inline void SetRiskSeverity(const int value);

        /**
        * Gets the risk unitary estimation
        *@return the risk unitary estimation
        */
        virtual inline float GetRiskUE() const;

        /**
        * Sets the risk unitary estimation
        *@param value - the risk unitary estimation
        */
        virtual inline void SetRiskUE(const float value);

        /**
        * Gets the risk annual operating loss (perte opérationnelle annuelle in French)
        *@return the risk annual operating loss (perte opérationnelle annuelle in French)
        */
        virtual inline float GetRiskPOA() const;

        /**
        * Sets the risk annual operating loss (perte opérationnelle annuelle in French)
        *@param value - the risk annual operating loss (perte opérationnelle annuelle in French)
        */
        virtual inline void SetRiskPOA(const float value);

        /**
        * Gets the risk action
        *@return the risk action
        */
        virtual inline bool GetRiskAction() const;

        /**
        * Sets the risk action
        *@param value - the risk action
        */
        virtual inline void SetRiskAction(const bool value);

        /**
        * Gets the property value
        *@param propId - the property identifier
        *@param[out] value - the property value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL GetValue(const int propId, int&     value) const;
        virtual BOOL GetValue(const int propId, UINT&    value) const;
        virtual BOOL GetValue(const int propId, DWORD&   value) const;
        virtual BOOL GetValue(const int propId, float&   value) const;
        virtual BOOL GetValue(const int propId, bool&    value) const;
        virtual BOOL GetValue(const int propId, CString& value) const;

        /**
        * Sets the property value
        *@param propId - the property identifier
        *@param value/pValue - the property value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetValue(const int propId, const int   value);
        virtual BOOL SetValue(const int propId, const UINT  value);
        virtual BOOL SetValue(const int propId, const DWORD value);
        virtual BOOL SetValue(const int propId, const float value);
        virtual BOOL SetValue(const int propId, const bool  value);
        virtual BOOL SetValue(const int propId, LPCTSTR     pValue);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        CString m_RiskName;
        CString m_RiskDesc;
        CString m_RiskType;
        int     m_RiskImpact;
        int     m_RiskProbability;
        int     m_RiskSeverity;
        float   m_RiskUE;
        float   m_RiskPOA;
        bool    m_RiskAction;

    private:
        /**
        * Sets the risk name (advanced)
        *@param value - the risk name
        */
        void SetRiskNameEx(const CString value);

        /**
        * Sets the risk description (advanced)
        *@param value - the risk description
        */
        void SetRiskDescEx(const CString value);

        /**
        * Sets the risk type (advanced)
        *@param value - the risk type
        */
        void SetRiskTypeEx(const CString value);
};

//---------------------------------------------------------------------------
// PSS_RiskPropertiesBP
//---------------------------------------------------------------------------
PSS_RiskPropertiesBP* PSS_RiskPropertiesBP::Dup() const
{
    return new PSS_RiskPropertiesBP(*this);
}
//---------------------------------------------------------------------------
CString PSS_RiskPropertiesBP::GetRiskName() const
{
    return m_RiskName;
}
//---------------------------------------------------------------------------
CString PSS_RiskPropertiesBP::GetRiskDesc() const
{
    return m_RiskDesc;
}
//---------------------------------------------------------------------------
CString PSS_RiskPropertiesBP::GetRiskType() const
{
    return m_RiskType;
}
//---------------------------------------------------------------------------
int PSS_RiskPropertiesBP::GetRiskImpact() const
{
    return m_RiskImpact;
}
//---------------------------------------------------------------------------
void PSS_RiskPropertiesBP::SetRiskImpact(const int value)
{
    m_RiskImpact = value;
}
//---------------------------------------------------------------------------
int PSS_RiskPropertiesBP::GetRiskProbability() const
{
    return m_RiskProbability;
}
//---------------------------------------------------------------------------
void PSS_RiskPropertiesBP::SetRiskProbability(const int value)
{
    m_RiskProbability = value;
}
//---------------------------------------------------------------------------
int PSS_RiskPropertiesBP::GetRiskSeverity() const
{
    return m_RiskSeverity;
}
//---------------------------------------------------------------------------
void PSS_RiskPropertiesBP::SetRiskSeverity(const int value)
{
    m_RiskSeverity = value;
}
//---------------------------------------------------------------------------
float PSS_RiskPropertiesBP::GetRiskUE() const
{
    return m_RiskUE;
}
//---------------------------------------------------------------------------
void PSS_RiskPropertiesBP::SetRiskUE(const float value)
{
    m_RiskUE = value;
}
//---------------------------------------------------------------------------
float PSS_RiskPropertiesBP::GetRiskPOA() const
{
    return m_RiskPOA;
}
//---------------------------------------------------------------------------
void PSS_RiskPropertiesBP::SetRiskPOA(const float value)
{
    m_RiskPOA = value;
}
//---------------------------------------------------------------------------
bool PSS_RiskPropertiesBP::GetRiskAction() const
{
    return m_RiskAction;
}
//---------------------------------------------------------------------------
void PSS_RiskPropertiesBP::SetRiskAction(const bool value)
{
    m_RiskAction = value;
}
//---------------------------------------------------------------------------

#endif
