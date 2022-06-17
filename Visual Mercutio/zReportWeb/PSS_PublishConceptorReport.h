/****************************************************************************
 * ==> PSS_PublishConceptorReport ------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will publish the Conceptor      *
 *               report to html files                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishConceptorReportH
#define PSS_PublishConceptorReportH

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
#include "zBaseSym\PSS_BasicSymbolVisitor.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_UserGroupEntity.h"
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
* Publishes the Conceptor report to html files
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PublishConceptorReport : public PSS_BasicSymbolVisitor
{
    public:
        /**
        * Export process
        */
        enum class IEExportProc
        {
            IE_EP_PublishConceptorHeaders,
            IE_EP_PublishConceptorDetails,
        };

        /**
        * Constructor
        *@param pModel - the model, can be NULL
        *@param showDetails - if true, the details will be shown
        *@param showDeliverables - if true, the deliverables will be shown
        */
        PSS_PublishConceptorReport(PSS_ProcessGraphModelMdlBP* pModel           = NULL,
                                   BOOL                        showDetails      = TRUE,
                                   BOOL                        showDeliverables = TRUE);

        virtual ~PSS_PublishConceptorReport();

        /**
        * Publishes the report
        *@param dir - the directory in which the report should be published
        *@return true on success, otherwise false
        */
        virtual bool Publish(const CString& dir);

    private:
        PSS_PublishModelGenerateDialog m_FileGenerateWindow;
        PSS_HtmlFile                   m_HtmlFile;
        PSS_ProcessGraphModelMdl*      m_pRootModel;
        PSS_ProcessGraphModelMdlBP*    m_pModel;
        PSS_ProcessGraphModelDoc*      m_pSourceDoc;
        PSS_ProcessSymbolBP*           m_pPreviousProcess;
        IEExportProc                   m_PublishProc;
        CString                        m_DomainName;
        CString                        m_UnitName;
        CString                        m_CurrentProcessName;
        BOOL                           m_ShowDetails;
        BOOL                           m_IncludeDeliverables;
        bool                           m_First;

        /**
        * Generates the page file
        *@param name - the name
        *@param description - the description
        */
        void GeneratePageFile(const CString& name, const CString& description);

        /**
        * Creates the file system
        *@param pGroup - the group
        *@param dir - the directory in which the report should be published
        *@return true on success, otherwise false
        */
        bool CreateFileSystem(PSS_UserGroupEntity* pGroup, const CString& dir);

        /**
        * Creates the process
        *@return true on success, otherwise false
        */
        bool CreateProcess();

        /**
        * Starts a section
        *@param nodes - the nodes to publish in the section
        *@return true on success, otherwise false
        */
        bool StartSection(CODNodeArray& nodes);

        /**
        * Called when a door symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        bool OnDoorSymbol(PSS_DoorSymbolBP* pSymbol);

        /**
        * Called when a page symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        bool OnPageSymbol(PSS_PageSymbolBP* pSymbol);

        /**
        * Called when a procedure symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        bool OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);

        /**
        * Called when a process symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        bool OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol);

        /**
        * Called when a start symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        bool OnStartSymbol(PSS_StartSymbolBP* pSymbol);

        /**
        * Called when a stop symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        bool OnStopSymbol(PSS_StopSymbolBP* pSymbol);

        /**
        * Called when a deliverable link symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        bool OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol);

        /**
        * Called when a symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        bool OnSymbol(PSS_Symbol* pSymbol);

        /**
        * Called when a link symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        bool OnLink(PSS_LinkSymbol* pLink);

        /**
        * Visits the target symbol
        *@param component - target symbol component to visit
        *@return true if visit succeeded, otherwise false
        */
        bool Visit(CODComponent& component);

        /**
        * Generates a file name for the report page
        *@param dir - the directory in which the report should be published
        *@param entityName - the entity name
        *@return the newly generated file name
        */
        CString GenerateFileName(const CString& dir, const CString& entityName);

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
