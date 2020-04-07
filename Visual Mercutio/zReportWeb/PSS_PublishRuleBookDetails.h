/****************************************************************************
 * ==> PSS_PublishRuleBookDetails ------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will publish the rule book      *
 *               details to html files                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishRuleBookDetailsH
#define PSS_PublishRuleBookDetailsH

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
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_ProcessGraphPage.h"
#include "zModelBP\PSS_ProcessGraphModelMdlBP.h"
#include "zModelBP\PSS_ProcedureSymbolBP.h"
#include "zModelBP\PSS_ProcessSymbolBP.h"
#include "zModelBP\PSS_StartSymbolBP.h"
#include "zModelBP\PSS_StopSymbolBP.h"
#include "zModelBP\PSS_DeliverableLinkSymbolBP.h"
#include "zModelWeb\PSS_PublishModelGenerateDialog.h"
#include "zWeb\PSS_HtmlFile.h"

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
* Publishes the rule book details to html files
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PublishRuleBookDetails
{
    public:
        /**
        * Constructor
        *@param pModel - the model, can be NULL
        */
        PSS_PublishRuleBookDetails(PSS_ProcessGraphModelMdlBP* pModel = NULL);

        virtual ~PSS_PublishRuleBookDetails();

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
        int                            m_Level;
        int                            m_Lvl1Counter;
        int                            m_Lvl2Counter;
        int                            m_Lvl3Counter;

        /**
        * Creates the file system
        *@param pRules - the rules
        *@param dir - the directory in which the report should be published
        *@return true on success, otherwise false
        */
        bool CreateFileSystem(PSS_LogicalRulesEntity* pRules, const CString& dir);

        /**
        * Creates the report
        *@param pRules - the rules
        */
        void CreateReport(PSS_LogicalRulesEntity* pRules);

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
        * Generates the html document header
        */
        void GenerateHTMLDocumentHeader();

        /**
        * Generates the section
        *@param ruleNumber - the rule number
        *@param ruleName - the rule name
        *@param objType - the object type
        *@param objName - the object name
        *@param unitName - the unit name
        */
        void GenerateSection(const CString& ruleNumber,
                             const CString& ruleName,
                             const CString& objType,
                             const CString& objName,
                             const CString& unitName);

        /**
        * Explores the process hierarchy
        *@param ruleNumber - the rule number
        *@param ruleName - the rule name
        *@param pStartRootModel - the start model to search from, if NULL the root model will be used instead
        */
        void ExploreProcessHierarchy(const CString&              ruleNumber,
                                     const CString&              ruleName,
                                     PSS_ProcessGraphModelMdlBP* pStartRootModel = NULL);

        /**
        * Generates a file name for the report page
        *@param dir - the directory in which the report should be published
        *@return the newly generated file name
        */
        CString GenerateFileName(const CString& dir);

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
};

#endif
