/****************************************************************************
 * ==> PSS_PublishPrestationsReport ----------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will publish the prestations    *
 *               report to html files                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishPrestationsReportH
#define PSS_PublishPrestationsReportH

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

// processsoft
#include "zBaseLib\PSS_StringFormatter.h"
#include "zBaseLib\PSS_Tokenizer.h"
#include "zConversion\PSS_StringTools.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_ProcessGraphPage.h"
#include "zModelBP\PSS_ProcessGraphModelMdlBP.h"
#include "zModelBP\PSS_DoorSymbolBP.h"
#include "zModelBP\PSS_PageSymbolBP.h"
#include "zModelBP\PSS_ProcedureSymbolBP.h"
#include "zModelBP\PSS_ProcessSymbolBP.h"
#include "zModelBP\PSS_StartSymbolBP.h"
#include "zModelBP\PSS_StopSymbolBP.h"
#include "zModelBP\PSS_DeliverableLinkSymbolBP.h"
#include "zModelBP\PSS_UnitPropertiesBP.h"
#include "zModelWeb\PSS_PublishModelGenerateDialog.h"
#include "zWeb\PSS_HtmlFile.h"
#include "zProperty\PSS_PropertyAttributes.h"
#include "PSS_Constants.h"

#ifdef _ZREPORTWEBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Publishes the prestations report to html files
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PublishPrestationsReport
{
    public:
        /**
        * Constructor
        *@param pModel - the model, can be NULL
        */
        PSS_PublishPrestationsReport(PSS_ProcessGraphModelMdlBP* pModel = NULL);

        virtual ~PSS_PublishPrestationsReport();

        /**
        * Publishes the report
        *@param dir - the directory in which the report should be published
        *@return true on success, otherwise false
        */
        virtual bool Publish(const CString& dir);

    private:
        PSS_ProcessGraphModelMdl*      m_pRootModel;
        PSS_HtmlFile                   m_HtmlFile;
        PSS_PublishModelGenerateDialog m_FileGenerateWindow;

        /**
        * Creates the file system
        *@param pPrestations - the prestations
        *@param dir - the directory in which the report should be published
        *@return true on success, otherwise false
        */
        bool CreateFileSystem(PSS_LogicalPrestationsEntity* pPrestations, const CString& dir);

        /**
        * Creates the report
        *@param prestationName - the prestation name
        */
        void CreateReport(const CString& prestationName);

        /**
        * Generates the html page header
        *@param title - the report title
        */
        void GenerateHTMLPageHeader(const CString& title);

        /**
        * Generates the html page footer
        */
        void GenerateHTMLPageFooter();

        /**
        * Generates the html table header
        */
        void GenerateHTMLTableHeader();

        /**
        * Generates the html table footer
        */
        void GenerateHTMLTableFooter();

        /**
        * Generates the html report title
        *@param prestationName - the prestation name
        *@param description - the description
        */
        void GenerateHTMLReportTitle(const CString& prestationName, const CString& description);

        /**
        * Generates the html section title
        */
        void GenerateHTMLSectionTitle();

        /**
        * Generates the html section line
        *@param group - the group
        *@param process - the process
        *@param procedure - the procedure
        */
        void GenerateHTMLSectionLine(const CString& group, const CString& process, const CString& procedure);

        /**
        * Generates a file name for the report page
        *@param dir - the directory in which the report should be published
        *@param prestationName - the prestation name
        *@return the newly generated file name
        */
        CString GenerateFileName(const CString& dir, const CString& prestationName);

        /**
        * Writes a line in the report
        *@param text - the line text to write
        */
        void WriteLine(const CString& text);

        /**
        * Writes a line in the report
        *@param id - the text resource identifier to write
        */
        void WriteLine(int id);

        /**
        * Searches the procedures
        *@param processName - the process name
        *@param pStartModel - the start model to search from
        */
        void SearchProcedures(const CString& processName, PSS_ProcessGraphModelMdlBP* pStartModel);

        /**
        * Searches an unit in the group children
        *@param pGroup - the group to search in
        *@param propertyName - the property name
        *@param processName - the process name
        *@param procedureName - the procedure name
        *@param childMode - if TRUE, the search will continue in the child children
        *@param childLevel - the child level
        */
        void SearchUnitGroupChildren(PSS_UserGroupEntity* pGroup,
                                     const CString&       propertyName,
                                     const CString&       processName,
                                     const CString&       procedureName,
                                     BOOL                 childMode  = FALSE,
                                     int                  childLevel = 0);

        /**
        * Explores the process hierarchy
        *@param prestationName - the prestation name
        *@param pStartRootModel - the start model to explore from, if NULL will explore from the root model
        */
        void ExploreProcessHierarchy(const CString& prestationName, PSS_ProcessGraphModelMdlBP* pStartRootModel = NULL);
};

#endif
