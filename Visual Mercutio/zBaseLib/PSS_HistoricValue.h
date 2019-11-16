/****************************************************************************
 * ==> PSS_HistoricValue ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an historic value, which keeps an historic for a  *
 *               specific name                                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_HistoricValueH
#define PSS_HistoricValueH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Historic value
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_HistoricValue
{
    public:
        /**
        * Constructor
        *@param entityName - entity name for which the historic should be kept
        */
        PSS_HistoricValue(const CString& entityName = "");

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_HistoricValue(const PSS_HistoricValue& other);

        virtual ~PSS_HistoricValue();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_HistoricValue& operator = (const PSS_HistoricValue& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_HistoricValue* Clone() const;

        /**
        * Gets the historic value count
        *@return the historic value count
        */
        virtual inline std::size_t GetCount() const;

        /**
        * Gets an historic value item index
        *@return the historic value item index, -1 if not found or on error
        */
        virtual int SearchHistoricValueIndex(const CString& value) const;

        /**
        * Checks if the historic value exists
        *@return true if the historic value exists, otherwise false
        */
        virtual inline bool HistoricValueExist(const CString& value) const;

        /**
        * Adds a new historic value
        *@param value - value to add
        */
        virtual void AddHistoricValue(const CString& value);

        /**
        * Removes a specific historic value
        *@param value - historic value to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveHistoricValue(const CString& value);

        /**
        * Gets an historic value at index
        *@param index - index
        *@return the historic value, empty string if not found or on error
        */
        virtual inline CString GetValueAt(std::size_t index) const;

        /**
        * Gets the historic value array
        *@return the historic value array
        */
        virtual inline const CStringArray& GetValueArray() const;

        /**
        * Clears the historic
        */
        virtual void ClearHistoric();

        /**
        * Gets the entity name
        *@return the entity name
        */
        virtual inline const CString GetEntityName() const;

        /**
        * Sets the entity name
        *@param value - the entity name
        */
        virtual inline void SetEntityName(const CString& value);

    private:
        CString      m_EntityName;
        CStringArray m_ValueHistoryArray;
};

/**
* Stores from the archive to the historic
*@param ar - archive
*@param historic - historic
*@return archive, to allow operator to be chained with other items, e.g a >> b >> c
*/
CArchive& AFXAPI operator << (CArchive& ar, const PSS_HistoricValue& historic);

/**
* Stores the historic to the archive
*@param ar - archive
*@param historic - historic
*@return archive, to allow operator to be chained with other items, e.g a << b << c
*/
CArchive& AFXAPI operator >> (CArchive& ar, PSS_HistoricValue& historic);

/**
* Dumps the historic content
*@param dc - dump context
*@param historic - historic
*@return archive, to allow operator to be chained with other items, e.g a >> b >> c
*/
#ifdef _DEBUG
    CDumpContext& AFXAPI operator << (CDumpContext& dc, const PSS_HistoricValue& src);
#endif

//---------------------------------------------------------------------------
// PSS_HistoricValue
//---------------------------------------------------------------------------
std::size_t PSS_HistoricValue::GetCount() const
{
    return m_ValueHistoryArray.GetSize();
}
//---------------------------------------------------------------------------
bool PSS_HistoricValue::HistoricValueExist(const CString& value) const
{
    return (SearchHistoricValueIndex(value) != -1);
}
//---------------------------------------------------------------------------
CString PSS_HistoricValue::GetValueAt(std::size_t index) const
{
    return (index < GetCount() ? m_ValueHistoryArray.GetAt(index) : _T(""));
}
//---------------------------------------------------------------------------
const CStringArray& PSS_HistoricValue::GetValueArray() const
{
    return m_ValueHistoryArray;
}
//---------------------------------------------------------------------------
const CString PSS_HistoricValue::GetEntityName() const
{
    return m_EntityName;
}
//---------------------------------------------------------------------------
void PSS_HistoricValue::SetEntityName(const CString& value)
{
    m_EntityName = value;
}
//---------------------------------------------------------------------------

#endif
