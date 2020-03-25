/****************************************************************************
 * ==> PSS_GenericGridReportGenerator --------------------------------------*
 ****************************************************************************
 * Description : Provides a generic report generator                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GenericGridReportGeneratorH
#define PSS_GenericGridReportGeneratorH

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
#ifndef PSS_GenericGridReportGenerator
    #define PSS_GenericGridReportGenerator ZBGenericGridReportGenerator
#endif

// processsoft
#include "zBaseLib\PSS_Date.h"
#include "ZIGridReportGenerator.h"

// forward class declaration
class ZDGridDocument;

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
* Generic report generator
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GenericGridReportGenerator : public CObject, public ZIGridReportGenerator
{
    DECLARE_SERIAL(PSS_GenericGridReportGenerator)

    public:
        /**
        * Constructor
        *@param pDoc - the document from which the report should be generated
        */
        PSS_GenericGridReportGenerator(ZDGridDocument* pDoc = NULL);

        virtual ~PSS_GenericGridReportGenerator();

        /**
        * Initialize the report generator
        *@return true on success, otherwise false
        */
        virtual bool Initialize();

        /**
        * Gets the document
        *@return the document
        */
        virtual inline ZDGridDocument* GetDocument() const;

        /**
        * Sets the document
        *@param pDoc - the document
        */
        virtual inline void SetDocument(ZDGridDocument* pDoc);

        /**
        * Gets the document template
        *@return the document template
        */
        virtual CDocTemplate* GetDocTemplate() const;

        /**
        * Gets the tab count
        *@return the tab count
        */
        virtual inline std::size_t GetGeneratorTabCount() const;

        /**
        * Gets the tab name matching with the index
        *@param index - the index
        *@return the tab name, empty string if not found or on error
        */
        virtual inline const CString GetGeneratorTabName(std::size_t index);

        /**
        * Fills the grid
        *@param gridCore - the grid to fill
        *@param index - the generator tab index
        */
        virtual inline bool FillGrid(CGXGridCore& gridCore, std::size_t index);

        /**
        * Gets the report type identifier
        *@return the report type identifier
        */
        virtual inline int GetReportTypeID() const;

        /**
        * Sets the report type identifier
        *@param typeID - the report type identifier
        */
        virtual inline void SetReportTypeID(int typeID);

        /**
        * Gets the report title
        *@return the report title
        */
        virtual inline const CString GetReportTitle() const;

        /**
        * Checks if the report data are located outside the generator
        *@return true if the report data are located outside the generator, otherwise false
        */
        virtual inline bool IsReportDataExternal() const;

        /**
        * Checks if the report data should be reloaded
        *@return true if the report data should be reloaded, otherwise false
        */
        virtual inline bool ReportDataMustBeReloaded() const;

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
        * Called before the data are filled
        *@param index - the index
        */
        virtual void OnPreDataFilled(std::size_t index);

        /**
        * Called after the data are filled
        *@param index - the index
        */
        virtual void OnPostDataFilled(std::size_t index);

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

    protected:
        ZDGridDocument* m_pDoc;
        PSS_Date        m_LastUpdateDateTime;
        CString         m_FileName;
        int             m_TypeID;
};

//---------------------------------------------------------------------------
// PSS_GenericGridReportGenerator
//---------------------------------------------------------------------------
ZDGridDocument* PSS_GenericGridReportGenerator::GetDocument() const
{
    return m_pDoc;
}
//---------------------------------------------------------------------------
void PSS_GenericGridReportGenerator::SetDocument(ZDGridDocument* pDoc)
{
    m_pDoc = pDoc;
}
//---------------------------------------------------------------------------
std::size_t PSS_GenericGridReportGenerator::GetGeneratorTabCount() const
{
    return 1;
}
//---------------------------------------------------------------------------
const CString PSS_GenericGridReportGenerator::GetGeneratorTabName(std::size_t index)
{
    return _T("Tab 1");
}
//---------------------------------------------------------------------------
bool PSS_GenericGridReportGenerator::FillGrid(CGXGridCore& gridCore, std::size_t index)
{
    return true;
}
//---------------------------------------------------------------------------
int PSS_GenericGridReportGenerator::GetReportTypeID() const
{
    return m_TypeID;
}
//---------------------------------------------------------------------------
void PSS_GenericGridReportGenerator::SetReportTypeID(int typeID)
{
    m_TypeID = typeID;
}
//---------------------------------------------------------------------------
const CString PSS_GenericGridReportGenerator::GetReportTitle() const
{
    return _T("");
}
//---------------------------------------------------------------------------
bool PSS_GenericGridReportGenerator::IsReportDataExternal() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_GenericGridReportGenerator::ReportDataMustBeReloaded() const
{
    return (PSS_Date::GetToday() > m_LastUpdateDateTime);
}
//---------------------------------------------------------------------------
bool PSS_GenericGridReportGenerator::UseAutomaticReload() const
{
    return true;
}
//---------------------------------------------------------------------------

#endif
