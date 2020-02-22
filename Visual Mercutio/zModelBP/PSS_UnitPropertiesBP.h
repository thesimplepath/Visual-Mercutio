/****************************************************************************
 * ==> PSS_UnitPropertiesBP ------------------------------------------------*
 ****************************************************************************
 * Description : Provides the unit properties for banking process           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UnitPropertiesBPH
#define PSS_UnitPropertiesBPH

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
#ifndef PSS_UnitPropertiesBP
    #define PSS_UnitPropertiesBP ZBBPUnitProperties2
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
#define M_Unit_Name_ID              1
#define M_Unit_Cost_ID              2
#define M_Unit_GUID_ID              3
#define M_Unit_Double_Validation_ID 4
//---------------------------------------------------------------------------

/**
* Unit properties for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UnitPropertiesBP : public CObject
{
    DECLARE_SERIAL(PSS_UnitPropertiesBP)

    public:
        /**
        * Change type
        *@note These items may be combinated
        */
        enum IEChangeType
        {
            IE_CT_Change_Unit_Name              = 0x0001,
            IE_CT_Change_Unit_Cost              = 0x0002,
            IE_CT_Change_Unit_GUID              = 0x0004,
            IE_CT_Change_Unit_Double_Validation = 0x0008,
            IE_CT_All                           = OD_CHANGE_ALL
        };

        PSS_UnitPropertiesBP();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UnitPropertiesBP(const PSS_UnitPropertiesBP& other);

        virtual ~PSS_UnitPropertiesBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_UnitPropertiesBP& operator = (const PSS_UnitPropertiesBP& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_UnitPropertiesBP& other) const;

        /**
        * Makes a copy of this properties object
        *@return a copy of this properties object, NULL on error
        */
        virtual inline PSS_UnitPropertiesBP* Dup() const;

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(PSS_UnitPropertiesBP* pProp, DWORD changeFlags = IE_CT_All);

        /**
        * Checks if another set of properties is equal to this one
        *@param pProp - other property set to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        virtual BOOL IsEqual(PSS_UnitPropertiesBP* pProp);

        /**
        * Gets the unit name
        *@return the unit name
        */
        virtual inline CString GetUnitName() const;

        /**
        * Sets the unit name
        *@param pValue - the unit name
        */
        virtual void SetUnitName(LPCTSTR pValue);

        /**
        * Gets the unit cost
        *@return the unit cost
        */
        virtual inline float GetUnitCost() const;

        /**
        * Sets the unit cost
        *@param value - the unit cost
        */
        virtual inline void SetUnitCost(const float value);

        /**
        * Gets the unit GUID
        *@return the unit GUID
        */
        virtual inline CString GetUnitGUID() const;

        /**
        * Sets the unit GUID
        *@param pValue - the unit GUID
        */
        virtual void SetUnitGUID(LPCTSTR pValue);

        /**
        * Gets the unit double validation type
        *@return the unit double validation type
        */
        virtual inline int GetUnitDoubleValidationType() const;

        /**
        * Sets the unit double validation type
        *@param value - the unit double validation type
        */
        virtual inline void SetUnitDoubleValidationType(const int value);

        /**
        * Gets the unit double validation type as a string array
        *@param[out] strArray - the string array which will contain the unit double validation type
        */
        virtual void GetUnitDoubleValidationTypeStringArray(CStringArray& strArray) const;

        /**
        * Converts the unit double validation string to type
        *@param type - the string containing the type to convert
        *@return the converted type
        */
        virtual int ConvertUnitDoubleValidationString2Type(const CString& type) const;

        /**
        * Gets the unit double validation type as a string
        *@param value - the unit double validation type to convert
        *@return the converted string
        */
        virtual CString GetUnitDoubleValidationTypeString(const int value) const;

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
        CString m_UnitName;
        CString m_UnitGUID;
        float   m_UnitCost;
        int     m_DoubleValidationType;

    private:
        /**
        * Sets the unit name (advanced)
        *@param value - the unit name
        */
        void SetUnitNameEx(const CString value);

        /**
        * Sets the unit guid (advanced)
        *@param value - the unit guid
        */
        void SetUnitGUIDEx(const CString value);
};

//---------------------------------------------------------------------------
// PSS_UnitPropertiesBP
//---------------------------------------------------------------------------
PSS_UnitPropertiesBP* PSS_UnitPropertiesBP::Dup() const
{
    return new PSS_UnitPropertiesBP(*this);
}
//---------------------------------------------------------------------------
CString PSS_UnitPropertiesBP::GetUnitName() const
{
    return m_UnitName;
}
//---------------------------------------------------------------------------
float PSS_UnitPropertiesBP::GetUnitCost() const
{
    return m_UnitCost;
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP::SetUnitCost(const float value)
{
    m_UnitCost = value;
}
//---------------------------------------------------------------------------
CString PSS_UnitPropertiesBP::GetUnitGUID() const
{
    return m_UnitGUID;
}
//---------------------------------------------------------------------------
int PSS_UnitPropertiesBP::GetUnitDoubleValidationType() const
{
    return m_DoubleValidationType;
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP::SetUnitDoubleValidationType(const int value)
{
    m_DoubleValidationType = value;
}
//---------------------------------------------------------------------------

#endif
