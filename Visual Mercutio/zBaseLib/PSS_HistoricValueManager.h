/****************************************************************************
 * ==> PSS_HistoricValueManager --------------------------------------------*
 ****************************************************************************
 * Description : Provides an historic value manager                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_HistoricValueManagerH
#define PSS_HistoricValueManagerH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_HistoricValue.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

using namespace sfl;

/**
* Historic value array
*/
typedef CCArray_T<PSS_HistoricValue*, PSS_HistoricValue*> PSS_HistoricValueSet;

/**
* Historic value iterator
*/
typedef Iterator_T<PSS_HistoricValue*> PSS_HistoricValueIterator;

/**
* Historic value manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_HistoricValueManager
{
    public:
        PSS_HistoricValueManager();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_HistoricValueManager(const PSS_HistoricValueManager& other);

        virtual ~PSS_HistoricValueManager();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_HistoricValueManager& operator = (const PSS_HistoricValueManager& other);

        /**
        * Adds an historic value
        *@param pValue - value
        */
        virtual inline void Add(PSS_HistoricValue* pValue);

        /**
        * Adds an historic value
        *@param fieldName - field name
        *@param value - value
        */
        virtual void AddHistoryValue(const CString& fieldName, const CString& value);

        /**
        * Removes an historic value
        *@param pValue - value
        *@return true on success, otherwise false
        */
        virtual bool Remove(PSS_HistoricValue* pValue);

        /**
        * Removes an historic value
        *@param fieldName - field name
        *@param value - value
        *@return true on success, otherwise false
        */
        virtual bool RemoveHistoryValue(const CString& fieldName, const CString& value);

        /**
        * Removes all the values belonging to a field
        *@param fieldName - field name
        *@return true on success, otherwise false
        */
        virtual bool RemoveFullHistory(const CString& fieldName);

        /**
        * Searches an historic entity (or field) index
        *@param fieldName - entity (or field) name
        *@return the entity index, -1 if not found or on error
        */
        virtual int SearchHistoricEntityIndex(const CString& fieldName) const;

        /**
        * Searches a field
        *@param fieldName - field name
        *@return the field, NULL if not found or on error
        */
        virtual inline PSS_HistoricValue* SearchHistoricEntity(const CString& fieldName) const;

        /**
        * Gets the field history
        *@param fieldName - field name
        *@return the field history, NULL if not found or on error
        */
        virtual CStringArray* GetFieldHistory(const CString& fieldName);

        /**
        * Gets the element count
        *@return the element count
        */
        virtual inline std::size_t GetCount() const;

        /**
        * Gets the historic entity set
        *@return the historic entity set
        */
        virtual inline PSS_HistoricValueSet& GetHistoricEntitySet();

        /**
        * Gets the historic entity set
        *@return the historic entity set
        */
        virtual inline const PSS_HistoricValueSet& GetHistoricEntitySetConst() const;

        /**
        * Clears the historic
        */
        virtual void ClearHistoric();

    private:
        PSS_HistoricValueSet m_HistoricValueSet;

        /**
        * Removes the historic value at index
        *@param index - index
        */
        void RemoveAt(std::size_t index);

        /**
        * Gets the historic value at index
        *@param index - index
        *@return the historic value at index, NULL if not found or on error
        */
        inline PSS_HistoricValue* GetHistoricEntityAt(std::size_t index) const;
};

/**
* Stores from the archive to the historic manager
*@param ar - archive
*@param historicManager - historic manager
*@return archive, to allow operator to be chained with other items, e.g a >> b >> c
*/
CArchive& AFXAPI operator << (CArchive& ar, const PSS_HistoricValueManager& historicManager);

/**
* Stores the historic manager to the archive
*@param ar - archive
*@param historicManager - historic manager
*@return archive, to allow operator to be chained with other items, e.g a << b << c
*/
CArchive& AFXAPI operator >> (CArchive& ar, PSS_HistoricValueManager& historicManager);

/**
* Dumps the historic manager content
*@param dc - dump context
*@param historicManager - historic manager
*@return archive, to allow operator to be chained with other items, e.g a >> b >> c
*/
#ifdef _DEBUG
    CDumpContext& AFXAPI operator << (CDumpContext& dc, const PSS_HistoricValueManager& historicManager);
#endif

//---------------------------------------------------------------------------
// PSS_HistoricValueManager
//---------------------------------------------------------------------------
void PSS_HistoricValueManager::Add(PSS_HistoricValue* pValue)
{
    m_HistoricValueSet.Add(pValue);
}
//---------------------------------------------------------------------------
PSS_HistoricValue* PSS_HistoricValueManager::SearchHistoricEntity(const CString& fieldName) const
{
    const int index = SearchHistoricEntityIndex(fieldName);
    return (index != -1 ? GetHistoricEntityAt(index) : NULL);
}
//---------------------------------------------------------------------------
std::size_t PSS_HistoricValueManager::GetCount() const
{
    return m_HistoricValueSet.GetSize();
}
//---------------------------------------------------------------------------
PSS_HistoricValueSet& PSS_HistoricValueManager::GetHistoricEntitySet()
{
    return m_HistoricValueSet;
}
//---------------------------------------------------------------------------
const PSS_HistoricValueSet& PSS_HistoricValueManager::GetHistoricEntitySetConst() const
{
    return m_HistoricValueSet;
};
//---------------------------------------------------------------------------
PSS_HistoricValue* PSS_HistoricValueManager::GetHistoricEntityAt(std::size_t index) const
{
    return (index < GetCount() ? m_HistoricValueSet.GetAt(index) : NULL);
}
//---------------------------------------------------------------------------

#endif
