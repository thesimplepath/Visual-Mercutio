/****************************************************************************
 * ==> PSS_GridReportDocument ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid report document                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GridReportDocumentH
#define PSS_GridReportDocumentH

#if _MSC_VER >= 1000
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
#include "PSS_GridDocument.h"
#include "PSS_GridReportGenerator.h"

// old class name mapping
#ifndef PSS_GenericGridReportGenerator
    #define PSS_GenericGridReportGenerator ZBGenericGridReportGenerator
#endif

// forward class declaration
class PSS_GenericGridReportGenerator;

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
* Grid report document
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GridReportDocument : public PSS_GridDocument, public PSS_GridReportGenerator
{
    DECLARE_DYNCREATE(PSS_GridReportDocument)

    public:
        virtual ~PSS_GridReportDocument();

        /**
        * Initializes the document
        *@return true on success, otherwise false
        */
        virtual inline bool Initialize();

        /**
        * Gets the report grid generator
        *@param pGenerator - the new report grid generator to use
        *@return true on success, otherwise false
        */
        virtual inline PSS_GenericGridReportGenerator* GetReportGridGenerator();

        /**
        * Sets the new report grid generator to use
        *@param pGenerator - the new report grid generator to use
        *@return true on success, otherwise false
        */
        virtual bool SetNewReportGridGenerator(PSS_GenericGridReportGenerator* pGenerator);

        /**
        * Assigns the report grid generator
        *@param pGenerator - the report grid generator to assign
        *@return true on success, otherwise false
        */
        virtual inline void AssignGenerator(PSS_GenericGridReportGenerator* pGenerator);

        /**
        * Checks if the view requires a data refresh
        *@return true if the view requires a data refresh, otherwise false
        */
        virtual inline bool ViewRequireDataRefresh() const;

        /**
        * Gets the tab name matching with the index
        *@param index - the index
        *@return the tab name, empty string if not found or on error
        */
        virtual const CString GetGeneratorTabName(std::size_t index);

        /**
        * Gets the tab count
        *@return the tab count
        */
        virtual inline std::size_t GetGeneratorTabCount() const;

        /**
        * Fills the grid at index
        *@param gridCore - the grid core
        *@param index - the index
        *@return true on success, otherwise false
        */
        virtual bool FillGrid(CGXGridCore& gridCore, std::size_t index);

        /**
        * Gets the report type identifier
        *@return the report type identifier
        */
        virtual int GetReportTypeID() const;

        /**
        * Sets the report type identifier
        *@param typeID - the report type identifier
        */
        virtual void SetReportTypeID(int typeID);

        /**
        * Gets the report title
        *@return the report title
        */
        virtual const CString GetReportTitle() const;

        /**
        * Checks if the report data are located outside the generator
        *@return true if the report data are located outside the generator, otherwise false
        */
        virtual bool IsReportDataExternal() const;

        /**
        * Checks if the report data should be reloaded
        *@return true if the report data should be reloaded, otherwise false
        */
        virtual bool ReportDataMustBeReloaded() const;

        /**
        * Checks if the automatic reload is enabled
        *@return true if the automatic reload is enabled, otherwise false
        */
        virtual bool UseAutomaticReload() const;

        /**
        * Sets all the tab names to the grid from the generator
        *@return true on success, otherwise false
        */
        virtual bool SetAllTabNameToGrid();

        /**
        * Called after the document is initialized
        *@param pMgr - the tab window manager
        *@param pAppAdapt - the application adapter
        *@param newFile - if true, a new document was created, otherwise the document was opened from file
        */
        virtual bool OnPostInitialized(CGXTabWndMgr* pMgr, CGXAppAdapter* pAppAdapt, bool newFile);

        /**
        * Called when a document is opened
        *@param pPathName - the document path name
        *@return TRUE if document may be opened, otherwise FALSE
        */
        virtual BOOL OnOpenDocument(LPCTSTR pPathName);

        /**
        * Called before the data are filled
        *@param index - the index
        */
        virtual void OnPreDataFilled(size_t Index);

        /**
        * Called after the data are filled
        *@param index - the index
        */
        virtual void OnPostDataFilled(size_t Index);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_GridReportDocument)
        virtual void WorkBookSerialize(CArchive& ar);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_GridReportDocument)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        PSS_GridReportDocument();

        /**
        * Initializes the grid using the generator
        *@return true on success, otherwise false
        */
        virtual bool InitializeGenerator();

        /**
        * Initializes the grid
        *@return true on success, otherwise false
        */
        virtual bool InitializeGrid();

    private:
        PSS_GenericGridReportGenerator* m_pGenerator;
        bool                            m_ViewRequireDataRefresh;
};

//---------------------------------------------------------------------------
// PSS_GridReportDocument
//---------------------------------------------------------------------------
bool PSS_GridReportDocument::Initialize()
{
    return InitializeGrid();
}
//---------------------------------------------------------------------------
PSS_GenericGridReportGenerator* PSS_GridReportDocument::GetReportGridGenerator()
{
    if (GetPrimaryDocument() == this)
        return m_pGenerator;

    PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

    return (pReportDoc ? pReportDoc->GetReportGridGenerator() : NULL);
}
//---------------------------------------------------------------------------
void PSS_GridReportDocument::AssignGenerator(PSS_GenericGridReportGenerator* pGenerator)
{
    m_pGenerator = pGenerator;
}
//---------------------------------------------------------------------------
bool PSS_GridReportDocument::ViewRequireDataRefresh() const
{
    if (GetPrimaryDocument() == this)
        return m_ViewRequireDataRefresh;

    PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

    return (pReportDoc ? pReportDoc->ViewRequireDataRefresh() : false);
}
//---------------------------------------------------------------------------

#endif
