/****************************************************************************
 * ==> PSS_PrestationsPropertiesBP -----------------------------------------*
 ****************************************************************************
 * Description : Provides the prestations properties for banking process    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PrestationsPropertiesBPH
#define PSS_PrestationsPropertiesBPH

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
#ifndef PSS_Prestation
    #define PSS_Prestation ZBBPPrestationNode
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
#define M_Prestation_Name          1
#define M_Prestation_Percentage    2
#define M_Prestation_Prest_Process 3
#define M_Prestation_Identifier    4
//---------------------------------------------------------------------------

/**
* Prestation
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Prestation : public CObject
{
    DECLARE_SERIAL(PSS_Prestation)

    public:
        PSS_Prestation();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Prestation(const PSS_Prestation& other);

        virtual ~PSS_Prestation();

        /**
        * Gets the prestation name
        *@return the prestation name
        */
        virtual CString GetName() const;

        /**
        * Sets the prestation name
        *@param pValue - the prestation name
        */
        virtual void SetName(LPCTSTR pValue);

        /**
        * Gets the prestation GUID
        *@return the prestation GUID
        */
        virtual CString GetGUID() const;

        /**
        * Sets the prestation GUID
        *@param pValue - the prestation GUID
        */
        virtual void SetGUID(LPCTSTR pValue);

        /**
        * Gets the property value
        *@param propId - the property identifier
        *@param[out] value - the property value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL GetValue(int propID, float &value) const;

        /**
        * Sets the property value
        *@param propId - the property identifier
        *@param value/pValue - the property value
        *@return TRUE on success, otherwise FALSE
        */
        virtual void SetValue(int propID, float value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CString m_Name;
        CString m_GUID;
        float   m_PercentageActivity;
};

/**
* Prestations properties for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PrestationsPropertiesBP
{
    public:
        PSS_PrestationsPropertiesBP();
        virtual ~PSS_PrestationsPropertiesBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_PrestationsPropertiesBP& operator = (const PSS_PrestationsPropertiesBP& other);

        /**
        * Adds a prestation
        *@param pPrestation - the prestation to add
        */
        virtual void AddPrestation(PSS_Prestation* pPrestation);

        /**
        * Removes a prestation
        *@param pPos - the position at which the prestation should be removed
        */
        virtual void RemovePrestation(POSITION pPos);

        /**
        * Removes all the prestations
        */
        virtual void RemoveAll();

        /**
        * Gets a prestation at position
        *@param pPos - the position at which the prestation should be get
        *@return the prestation, NULL if not found or on error
        */
        virtual PSS_Prestation* GetAt(POSITION pPos);

        /**
        * Gets the head position
        *@return the head position, NULL on error
        */
        virtual POSITION GetHeadPosition();

        /**
        * Gets the tail position
        *@return the tail position, NULL on error
        */
        virtual POSITION GetTailPosition();

        /**
        * Gets the previous position
        *@return the previous position, NULL if no previous position or on error
        */
        virtual POSITION GetPrevPosition();

        /**
        * Gets the next position
        *@return the next position, NULL if no next position or on error
        */
        virtual POSITION GetNextPosition();

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CObList  m_Prestations;
        POSITION m_pPos;
};

#endif
