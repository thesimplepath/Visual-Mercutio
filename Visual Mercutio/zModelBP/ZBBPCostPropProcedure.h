/****************************************************************************
 * ==> PSS_CostPropertiesProcedureBP ---------------------------------------*
 ****************************************************************************
 * Description : Provides the cost properties for procedures                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CostPropertiesProcedureBPH
#define PSS_CostPropertiesProcedureBPH

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
#ifndef PSS_CostPropertiesProcedureBP
    //#define PSS_CostPropertiesProcedureBP ZBBPCostPropertiesProcedure
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
#define Z_COST_MULTIPLIER      1
#define Z_COST_PROCESSING_TIME 2
#define Z_COST_UNITARY_COST    3
//---------------------------------------------------------------------------

#define Z_CHANGE_COST_MULTIPLIER                    0x0001
#define Z_CHANGE_COST_PROCESSING_TIME                0x0002
#define Z_CHANGE_COST_UNITARY_COST                    0x0004

/**
* Cost properties for procedures
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZBBPCostPropertiesProcedure : public CODIntProperty,
                                        public sfl::CPropertyContainer<IODPropertyContainer, CODPropertyAccessor<ZBBPCostPropertiesProcedure> >
{
    DECLARE_SERIAL(ZBBPCostPropertiesProcedure)

// Construction/Destruction
public:
    //@cmember
    /* Constructor. */
    ZBBPCostPropertiesProcedure(int nId = ZS_BP_PROP_PROCEDURE_COST);
    //@cmember
    /* Copy constructor. */
    ZBBPCostPropertiesProcedure(const ZBBPCostPropertiesProcedure& propBasic);
    //@cmember
    /* Destructor. */
    virtual ~ZBBPCostPropertiesProcedure();

// Attributes
protected:

    //@cmember
    /* the cost multiplier factor. */
    float m_Multiplier;

    //@cmember
    /* the processing time. */
    double m_ProcessingTime;

    //@cmember
    /* the unitary cost. */
    float m_UnitaryCost;


public:
    //@cmember
    /* Gets the cost multiplier factor. */
    float GetMultiplier() const;

    //@cmember
    /* Sets the cost multiplier factor. */
    void SetMultiplier(const float value);

    //@cmember
    /* Gets the processing time. */
    double GetProcessingTime() const;

    //@cmember
    /* Sets the processing time. */
    void SetProcessingTime(const double value);

    //@cmember
    /* Gets the unitary cost. */
    float GetUnitaryCost() const;

    //@cmember
    /* Sets the unitary cost. */
    void SetUnitaryCost(const float value);


// Operations
public:
    /**
    * Compares the property identifier with another identifier
    *@param id - the property identifier to compare with
    *@return TRUE if the property identifiers are equals, otherwise FALSE
    */
    virtual BOOL CompareId(const int nId) const;

    //@cmember
    /* Assigns another property to this property. */
    ZBBPCostPropertiesProcedure& operator=(const ZBBPCostPropertiesProcedure& propBasic);

    //@cmember
    /* Compares two orientation properties. */
    BOOL operator==(const ZBBPCostPropertiesProcedure propBasic) const;

    //@cmember
    /* Makes a copy of this properties object. */
    virtual CODProperty* Dup();
    //@cmember
    /* Merges another set of properties with this one. */
    virtual void Merge(CODProperty* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL);
    //@cmember
    /* Determines if another set of properties is equal to this one. */
    virtual BOOL IsEqual(CODProperty* pProp);

    /////////////////////////////////////////////////////////////////////////
    // IODObject interface

    BEGIN_GUID_MAP(ZBBPCostPropertiesProcedure)
        GUID_ENTRY(IODPropertyContainer)
        GUID_ENTRY(sfl::IPropertyContainer)
        GUID_CHAIN_ENTRY(CODIntProperty)
    END_GUID_MAP

    //@cmember
    /* Add a reference to this object. */
    ULONG STDMETHODCALLTYPE AddRef();
    //@cmember
    /* Release a reference to this object. */
    ULONG STDMETHODCALLTYPE Release();

    /////////////////////////////////////////////////////////////////////////
    // IODPropertyContainer interface

    //@cmember
    /* Gets the value of the given string property. */
    virtual BOOL GetValue(const int nPropId, CString& strValue) const;
    //@cmember
    /* Gets the value of the given integer property. */
    virtual BOOL GetValue(const int nPropId, int& nValue) const;
    //@cmember
    /* Gets the value of the given unsigned integer property. */
    virtual BOOL GetValue(const int nPropId, UINT& nValue) const;
    //@cmember
    /* Gets the value of the given DWORD property. */
    virtual BOOL GetValue(const int nPropId, DWORD& dwValue) const;
    //@cmember
    /* Gets the value of the given float property. */
    virtual BOOL GetValue(const int nPropId, float& fValue) const;
    //@cmember
    /* Gets the value of the given double property. */
    virtual BOOL GetValue(const int nPropId, double& dValue) const;

    //@cmember
    /* Sets the value of the given string property. */
    virtual BOOL SetValue(const int nPropId, LPCTSTR lpszValue);
    //@cmember
    /* Sets the value of the given integer property. */
    virtual BOOL SetValue(const int nPropId, const int nValue);
    //@cmember
    /* Sets the value of the given unsigned integer property. */
    virtual BOOL SetValue(const int nPropId, const UINT nValue);
    //@cmember
    /* Sets the value of the given unsigned DWORD property. */
    virtual BOOL SetValue(const int nPropId, const DWORD dwValue);
    //@cmember
    /* Sets the value of the given float property. */
    virtual BOOL SetValue(const int nPropId, const float fValue);
    //@cmember
    /* Sets the value of the given double property. */
    virtual BOOL SetValue(const int nPropId, const double dValue);

    //@cmember
    /* Serializes the orientation properties. */
    virtual void Serialize(CArchive& ar);

    /////////////////////////////////////////////////////////////////////////
    // Internal helper functions subject to change.
private:

    /* Registers the basic property meta-data. */
    bool RegisterProperties();

// Implementation
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// ZBBPCostPropertiesProcedure inline methods

//@mfunc Add a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPCostPropertiesProcedure::AddRef()
{
    return CODIntProperty::AddRef();
}

//@mfunc Release a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPCostPropertiesProcedure::Release()
{
    return CODIntProperty::Release();
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline float ZBBPCostPropertiesProcedure::GetMultiplier() const
{
    return m_Multiplier;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPCostPropertiesProcedure::SetMultiplier(const float value)
{
    m_Multiplier = value;
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline double ZBBPCostPropertiesProcedure::GetProcessingTime() const
{
    return m_ProcessingTime;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPCostPropertiesProcedure::SetProcessingTime(const double value)
{
    m_ProcessingTime = value;
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline float ZBBPCostPropertiesProcedure::GetUnitaryCost() const
{
    return m_UnitaryCost;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPCostPropertiesProcedure::SetUnitaryCost(const float value)
{
    m_UnitaryCost = value;
}


//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline CODProperty* ZBBPCostPropertiesProcedure::Dup()
{
    return new ZBBPCostPropertiesProcedure(*this);
}

#endif
