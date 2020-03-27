/****************************************************************************
 * ==> PSS_ModelBPReportGenerator ------------------------------------------*
 ****************************************************************************
 * Description : Provides a banking process model report generator          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ModelBPReportGeneratorH
#define PSS_ModelBPReportGeneratorH

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

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_ModelBPReportGenerator
    #define PSS_ModelBPReportGenerator ZBModelBPReportGenerator
#endif

// processsoft
#include "zReport\PSS_GenericGridReportGenerator.h"
#include "zReport\PSS_OStreamGrid.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif
#ifndef PSS_ProcessGraphModelMdlBP
    #define PSS_ProcessGraphModelMdlBP ZDProcessGraphModelMdlBP
#endif

// forward class declaration
class PSS_GridDocument;
class PSS_ProcessGraphModelMdlBP;
class PSS_ProcessGraphModelDoc;

#ifdef _ZREPORTBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Banking process model report generator
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ModelBPReportGenerator : public PSS_GenericGridReportGenerator
{
    DECLARE_SERIAL(PSS_ModelBPReportGenerator)

    public:
        /**
        * Constructor
        *@param pDoc - the document
        *@param pModel - the model
        *@param pSourceDoc - the source document
        */
        PSS_ModelBPReportGenerator(PSS_GridDocument*           pDoc       = NULL,
                                   PSS_ProcessGraphModelMdlBP* pModel     = NULL,
                                   PSS_ProcessGraphModelDoc*   pSourceDoc = NULL);

        virtual ~PSS_ModelBPReportGenerator();

        /**
        * Initializes the generator
        */
        virtual inline bool Initialize();

        /**
        * Initializes the generator
        *@param pDoc - the document
        *@param pModel - the model
        *@param pSourceDoc - the source document
        */
        virtual void Initialize(PSS_GridDocument*           pDoc,
                                PSS_ProcessGraphModelMdlBP* pModel,
                                PSS_ProcessGraphModelDoc*   pSourceDoc);

        /**
        * Gets the generator tab name at index
        *@param index - the index
        *@return the generator tab name, empty string if not found or on error
        */
        virtual inline const CString GetGeneratorTabName(std::size_t index);

        /**
        * Gets the generator tab count
        *@return the generator tab count
        */
        virtual inline std::size_t GetGeneratorTabCount() const;

        /**
        * Gets the report type identifier
        *@return the report type identifier
        */
        virtual inline int GetReportTypeID() const;

        /**
        * Checks if the report data are located outside the generator
        *@return true if the report data are located outside the generator, otherwise false
        */
        virtual inline bool IsReportDataExternal() const;

        /**
        * Checks if the report data should be reloaded
        *@return true if the report data should be reloaded, otherwise false
        */
        virtual bool ReportDataMustBeReloaded() const;

        /**
        * Checks if the automatic reload is enabled
        *@return true if the automatic reload is enabled, otherwise false
        */
        virtual inline bool UseAutomaticReload() const;

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

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

        /**
        * Called after the data are read from an archive
        *@param ar - archive
        */
        virtual void OnPostRead(CArchive& ar);

        /**
        * Called after the data are written to an archive
        *@param ar - archive
        */
        virtual void OnPostWrite(CArchive& ar);

        /**
        * Called after the data are filled
        *@param index - the grid index
        */
        virtual void OnPostDataFilled(std::size_t Index);

    protected:
        PSS_ProcessGraphModelDoc*   m_pSourceDoc;
        PSS_ProcessGraphModelMdlBP* m_pModel;
        CStringArray                m_TabNameArray;
        bool                        m_InChargeOfClosingFile;

        /**
        * Fills the tab array
        */
        virtual inline void FillTabArray();
};

//---------------------------------------------------------------------------
// PSS_ModelBPReportGenerator
//---------------------------------------------------------------------------
bool PSS_ModelBPReportGenerator::Initialize()
{
    FillTabArray();
    return true;
}
//---------------------------------------------------------------------------
const CString PSS_ModelBPReportGenerator::GetGeneratorTabName(std::size_t index)
{
    return (index < GetGeneratorTabCount() ? m_TabNameArray.GetAt(index) : _T(""));
}
//---------------------------------------------------------------------------
std::size_t PSS_ModelBPReportGenerator::GetGeneratorTabCount() const
{
    return m_TabNameArray.GetSize();
}
//---------------------------------------------------------------------------
int PSS_ModelBPReportGenerator::GetReportTypeID() const
{
    return 0;
}
//---------------------------------------------------------------------------
bool PSS_ModelBPReportGenerator::IsReportDataExternal() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelBPReportGenerator::UseAutomaticReload() const
{
    return false;
}
//---------------------------------------------------------------------------
void PSS_ModelBPReportGenerator::FillTabArray()
{}
//---------------------------------------------------------------------------

#endif
