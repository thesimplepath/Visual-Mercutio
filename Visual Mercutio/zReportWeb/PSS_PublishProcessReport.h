/****************************************************************************
 * ==> PSS_PublishProcessReport --------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will publish the process report *
 *               to html files                                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishProcessReportH
#define PSS_PublishProcessReportH

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
* Publishes the process report to html files
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PublishProcessReport
{
    public:
        /**
        * Constructor
        *@param pModel - the model, can be NULL
        *@param pPropAttributes - the properties attributes
        */
        PSS_PublishProcessReport(PSS_ProcessGraphModelMdlBP* pModel          = NULL,
                                 PSS_PropertyAttributes*     pPropAttributes = NULL);

        virtual ~PSS_PublishProcessReport();

        /**
        * Publishes the report
        *@param dir - the directory in which the report should be published
        *@return true on success, otherwise false
        */
        virtual bool Publish(const CString& dir);

    private:
        /**
        * Symbol entity
        */
        class AFX_EXT_CLASS ISymbolEntity : public CObject
        {
            public:
                ISymbolEntity();

                /**
                * Constructor
                *@param ref - the reference index
                *@param name - the name
                *@param description - the description
                */
                ISymbolEntity(int ref, const CString& name, const CString& description);

                virtual ~ISymbolEntity();

                /**
                * Gets the reference index
                *@return the reference index
                */
                int GetRef() const;

                /**
                * Sets the reference index
                *@param ref - the reference index
                */
                void SetRef(int ref);

                /**
                * Gets the name
                *@return the name
                */
                CString GetName() const;

                /**
                * Sets the name
                *@param name - the name
                */
                void SetName(const CString& name);

                /**
                * Gets the description
                *@return the description
                */
                CString GetDescription() const;

                /**
                * Sets the description
                *@param description - the description
                */
                void SetDescription(const CString& description);

            private:
                CString m_Name;
                CString m_Description;
                int     m_Ref;
        };

        /**
        * Symbol container
        */
        class AFX_EXT_CLASS ISymbolContainer
        {
            public:
                ISymbolContainer();
                ~ISymbolContainer();

                /**
                * Adds a symbol
                *@param pSymbolEntity - the symbol entity to add
                */
                void AddSymbol(ISymbolEntity* pSymbolEntity);

                /**
                * Removes all the symbols
                */
                void RemoveAll();

                /**
                * Sorts the symbols
                */
                void Sort();

                /**
                * Gets a symbol at position
                *@param pPos - the position
                *@return the symbol, NULL if not found or on error
                */
                ISymbolEntity* GetAt(POSITION pPos);

                /**
                * Gets the head position
                *@return the head position, NULL if not found or on error
                */
                POSITION GetHeadPosition();

                /**
                * Gets the tail position
                *@return the tail position, NULL if not found or on error
                */
                POSITION GetTailPosition();

                /**
                * Gets the previous position
                *@return the previous position, NULL if not found or on error
                */
                POSITION GetPrevPosition();

                /**
                * Gets the next position
                *@return the next position, NULL if not found or on error
                */
                POSITION GetNextPosition();

            private:
                CObList  m_SymbolList;
                POSITION m_pPos;

                /**
                * Trim the string and removes the redundant empty chars
                *@param str - the string to trim
                *@return the trimmed string
                */
                CString Trim(const CString& str) const;
        };

        PSS_PropertyAttributes*        m_pPropAttributes;
        PSS_ProcessGraphModelMdl*      m_pRootModel;
        PSS_HtmlFile                   m_HtmlFile;
        PSS_PublishModelGenerateDialog m_FileGenerateWindow;
        ISymbolContainer               m_StartContainer;
        ISymbolContainer               m_StopContainer;
        ISymbolContainer               m_ProcedureContainer;
        ISymbolContainer               m_DoorContainer;

        /**
        * Creates the file system
        *@param dir - the directory in which the report should be published
        *@param pStartRootModel - the start model, if NULL will start from the root model
        *@return true on success, otherwise false
        */
        bool CreateFileSystem(const CString& dir, PSS_ProcessGraphModelMdlBP* pStartRootModel = NULL);

        /**
        * Searches a symbol
        *@param symbolName - the symbol name to search
        *@param pStartRootModel - the start model, if NULL will start from the root model
        *@return the symbol, NULL if not found or on error
        */
        PSS_Symbol* SearchSymbol(const CString& symbolName, PSS_ProcessGraphModelMdlBP* pStartRootModel = NULL);

        /**
        * Searches a link symbol
        *@param symbolName - the symbol name to search
        *@param pStartRootModel - the start model, if NULL will start from the root model
        *@return the symbol, NULL if not found or on error
        */
        PSS_LinkSymbol* SearchLinkSymbol(const CString& symbolName, PSS_ProcessGraphModelMdlBP* pStartRootModel = NULL);

        /**
        * Creates the report
        *@param pProcessSymbol - the process symbol
        */
        void CreateReport(PSS_ProcessSymbolBP* pProcessSymbol);

        /**
        * Generates a section
        *@param propSet - the property set
        */
        void GenerateSection(PSS_Properties::IPropertySet& propSet);

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
        *@param domainName - the domain name
        *@param title - the symbol title
        */
        void GenerateHTMLReportTitle(const CString& domainName, const CString& title);

        /**
        * Generates the html symbol title
        *@param ref - the reference index
        *@param title - the symbol title
        *@param objectType - the object type
        *@param colorTitle - the title color
        */
        void GenerateHTMLSymbolTitle(int ref, const CString& title, const CString& objectType, COLORREF colorTitle);
        void GenerateHTMLSymbolTitle(int ref, const CString& title, COLORREF colorTitle);

        /**
        * Generates the html section title
        *@param title - the symbol title
        */
        void GenerateHTMLSectionTitle(const CString& title);

        /**
        * Generates the html section line
        *@param ref - the reference index
        *@param title - the symbol title
        *@param description - the symbol description
        */
        void GenerateHTMLSectionLine(const CString& ref, const CString& title, const CString& description);

        /**
        * Generates a black line
        */
        void GenerateBlackLine();

        /**
        * Generates a separation
        */
        void GenerateSeparation();

        /**
        * Generates a file name for the report page
        *@param dir - the directory in which the report should be published
        *@param processName - the process name
        *@return the newly generated file name
        */
        CString GenerateFileName(const CString& dir, const CString& processName);

        /**
        * Writes a line in the report
        *@param text - the line text to write
        */
        void WriteLine(const CString& text);

        /**
        * Writes a line in the report
        *@param id - the text resource identifier to write
        */
        void WriteLine(int nID);

        /**
        * Resets the data
        */
        void ResetData();
};

#endif
