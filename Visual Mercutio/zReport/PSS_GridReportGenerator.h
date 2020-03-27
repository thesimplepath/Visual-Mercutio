/****************************************************************************
 * ==> PSS_GridReportGenerator ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid report generator interface                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GridReportGeneratorH
#define PSS_GridReportGeneratorH

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

#ifdef _ZREPORTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Grid report generator interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GridReportGenerator
{
    public:
        PSS_GridReportGenerator();
        virtual ~PSS_GridReportGenerator();

        /**
        * Initializes the report generator
        *@return true on success, otherwise false
        */
        virtual bool Initialize() = 0;

        /**
        * Gets the tab name matching with the index
        *@param index - the index
        *@return the tab name, empty string if not found or on error
        */
        virtual const CString GetGeneratorTabName(std::size_t index) = 0;

        /**
        * Gets the tab count
        *@return the tab count
        */
        virtual std::size_t GetGeneratorTabCount() const = 0;

        /**
        * Fills the grid at index
        *@param gridCore - the grid core
        *@param index - the index
        *@return true on success, otherwise false
        */
        virtual bool FillGrid(CGXGridCore& gridCore, std::size_t index) = 0;

        /**
        * Gets the report type identifier
        *@return the report type identifier
        */
        virtual int GetReportTypeID() const = 0;

        /**
        * Sets the report type identifier
        *@param typeID - the report type identifier
        */
        virtual void SetReportTypeID(int typeID) = 0;

        /**
        * Gets the report title
        *@return the report title
        */
        virtual const CString GetReportTitle() const = 0;

        /**
        * Checks if the report data are located outside the generator
        *@return true if the report data are located outside the generator, otherwise false
        */
        virtual bool IsReportDataExternal() const = 0;

        /**
        * Checks if the report data should be reloaded
        *@return true if the report data should be reloaded, otherwise false
        */
        virtual bool ReportDataMustBeReloaded() const = 0;

        /**
        * Checks if the automatic reload is enabled
        *@return true if the automatic reload is enabled, otherwise false
        */
        virtual bool UseAutomaticReload() const = 0;

        /**
        * Called before the data are filled
        *@param index - the index
        */
        virtual void OnPreDataFilled(std::size_t index) = 0;

        /**
        * Called after the data are filled
        *@param index - the index
        */
        virtual void OnPostDataFilled(std::size_t index) = 0;
};

#endif
