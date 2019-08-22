/****************************************************************************
 * ==> PSS_PaintOperations -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a paint operations helper class                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PaintOperationsH
#define PSS_PaintOperationsH

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
* Paint operations helper class
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PaintOperations
{
    public:
        PSS_PaintOperations();
        virtual ~PSS_PaintOperations();

        /**
        * Gets the logical basic units
        *@return the logical basic units
        */
        static inline const CSize& GetLogicalBasicUnits();

        /**
        * Sets the basic logical units
        *@param logicalBasicUnits - the logical basic units to set
        */
        static inline void SetLogicalBasicUnits(const CSize& logicalBasicUnits);

        /**
        * Converts logical units in millimeters
        *@param logicalUnits - units to convert
        *@return converted units
        */
        static inline CSize ConvertLogicalUnitsMillimeters(const CSize& logicalUnits);

        /**
        * Converts millimeters to logical units
        *@param millimeters - units to convert
        *@return converted units
        */
        static inline CSize ConvertMillimetersLogicalUnits(const CSize& millimeters);

    private:
        static CSize m_LogicalBasicUnits;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PaintOperations(const PSS_PaintOperations& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PaintOperations& operator = (const PSS_PaintOperations& other);
};

//---------------------------------------------------------------------------
// PSS_PaintOperations
//---------------------------------------------------------------------------
void PSS_PaintOperations::SetLogicalBasicUnits(const CSize& logicalBasicUnits)
{
    m_LogicalBasicUnits = logicalBasicUnits;
}
//---------------------------------------------------------------------------
const CSize& PSS_PaintOperations::GetLogicalBasicUnits()
{
    return m_LogicalBasicUnits;
}
//---------------------------------------------------------------------------
CSize PSS_PaintOperations::ConvertLogicalUnitsMillimeters(const CSize& logicalUnits)
{
    return CSize(int(double(logicalUnits.cx) / (double(m_LogicalBasicUnits.cx) / 2540.0)),
                 int(double(logicalUnits.cy) / (double(m_LogicalBasicUnits.cy) / 2540.0)));
}
//---------------------------------------------------------------------------
CSize PSS_PaintOperations::ConvertMillimetersLogicalUnits(const CSize& millimeters)
{
    return CSize(int(double(millimeters.cx) * (double(m_LogicalBasicUnits.cx) / 2540.0)),
                 int(double(millimeters.cy) * (double(m_LogicalBasicUnits.cy) / 2540.0)));
}
//---------------------------------------------------------------------------

#endif
