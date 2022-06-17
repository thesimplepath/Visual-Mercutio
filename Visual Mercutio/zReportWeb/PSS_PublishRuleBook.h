/****************************************************************************
 * ==> PSS_PublishRuleBook -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will publish the rule book to   *
 *               html files                                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishRuleBookH
#define PSS_PublishRuleBookH

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
* Publishes the rule book to html files
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PublishRuleBook
{
    public:
        /**
        * Constructor
        *@param pModel - the model, can be NULL
        */
        PSS_PublishRuleBook(PSS_ProcessGraphModelMdlBP* pModel = NULL);

        virtual ~PSS_PublishRuleBook();

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
        int                            m_Lvl4Counter;
        int                            m_Lvl5Counter;
        int                            m_Lvl6Counter;

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
        *@param ruleName - the rule name
        *@param ruleDesc - the rule description
        */
        void GenerateHTMLDocumentHeader(const CString& ruleName, const CString& ruleDesc);

        /**
        * Generates the first html table
        *@param ruleName - the rule name
        *@param ruleDesc - the rule description
        */
        void GenerateHTMLTable1(const CString& ruleName, const CString& ruleDesc);

        /**
        * Generates the second html table
        *@param ruleName - the rule name
        *@param ruleDesc - the rule description
        */
        void GenerateHTMLTable2(const CString& ruleName, const CString& ruleDesc);

        /**
        * Generates the third html table
        *@param ruleName - the rule name
        *@param ruleDesc - the rule description
        */
        void GenerateHTMLTable3(const CString& ruleName, const CString& ruleDesc);

        /**
        * Generates the fourth html table
        *@param ruleName - the rule name
        *@param ruleDesc - the rule description
        */
        void GenerateHTMLTable4(const CString& ruleName, const CString& ruleDesc);

        /**
        * Generates the fifth html table
        *@param ruleName - the rule name
        *@param ruleDesc - the rule description
        */
        void GenerateHTMLTable5(const CString& ruleName, const CString& ruleDesc);

        /**
        * Generates the sixth html table
        *@param ruleName - the rule name
        *@param ruleDesc - the rule description
        */
        void GenerateHTMLTable6(const CString& ruleName, const CString& ruleDesc);

        /**
        * Generates a file name for the report page
        *@param dir - the directory in which the report should be published
        *@return the newly generated file name
        */
        CString GenerateFileName(const CString& dir);

        /**
        * Checks if a rule is still in use
        *@param ruleName - the rule name to check
        *@param pStartRootModel - the start root model to start from
        *@return TRUE if the rule is still in use, otherwise FALSE
        */
        BOOL IsRuleInUse(const CString& ruleName, ZDProcessGraphModelMdlBP* pStartRootModel = NULL);

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
