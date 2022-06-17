/****************************************************************************
 * ==> PSS_DatabaseManipulator ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a database manipulator                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DatabaseManipulatorH
#define PSS_DatabaseManipulatorH

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

#ifdef _ZDBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Database manipulator
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_DatabaseManipulator
{
    public:
        enum class IEType
        {
            IE_DT_MSAccess,
            IE_DT_dBaseIII,
            IE_DT_dBaseIV,
            IE_DT_dBase5,
            IE_DT_Paradox3x,
            IE_DT_Paradox4x,
            IE_DT_Paradox5x,
            IE_DT_FoxPro2,
            IE_DT_FoxPro25,
            IE_DT_FoxPro26,
            IE_DT_Excel3,
            IE_DT_Excel4,
            IE_DT_Excel5,
            IE_DT_Excel97,
            IE_DT_HTMLExport,
            IE_DT_HTMLImport,
            IE_DT_Text,
            IE_DT_LotusWks,
            IE_DT_LotusWk1,
            IE_DT_LotusWk3,
            IE_DT_LotusWk4,
            IE_DT_Oracle8i
        };

        /**
        * Constructor
        *@param name - database name
        *@param type - database type
        */
        PSS_DatabaseManipulator(const CString& name = "", IEType type = IEType::IE_DT_MSAccess);

        virtual ~PSS_DatabaseManipulator();

        /**
        * Creates a database
        *@return true on success, otherwise false
        */
        virtual bool CreateDatabase();

        /**
        * Gets the table list
        *@param[out] tableArray - table array to populate with result
        *@return true on success, otherwise false
        */
        virtual bool GetTableList(CStringArray& tableArray);

    private:
        CString m_Name;
        IEType  m_Type;
};

#endif
