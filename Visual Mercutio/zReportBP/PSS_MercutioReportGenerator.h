/****************************************************************************
 * ==> PSS_MercutioReportGenerator -----------------------------------------*
 ****************************************************************************
 * Description : Provides a Mercutio report generator                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MercutioReportGeneratorH
#define PSS_MercutioReportGeneratorH

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
#ifndef PSS_MercutioReportGenerator
    #define PSS_MercutioReportGenerator ZBMercutioReportGenerator
#endif

// processsoft
#include "PSS_ModelBPReportGenerator.h"

// class name mapping
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif
#ifndef PSS_UserRoleEntity
    #define PSS_UserRoleEntity ZBUserRoleEntity
#endif

// forward class declaration
class PSS_UserGroupEntity;
class PSS_UserRoleEntity;

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
* Mercutio report generator
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MercutioReportGenerator : public PSS_ModelBPReportGenerator
{
    DECLARE_SERIAL(PSS_MercutioReportGenerator)

    public:
        /**
        * Constructor
        *@param pDoc - the document
        *@param pModel - the model
        *@param pSourceDoc - the source document
        */
        PSS_MercutioReportGenerator(PSS_GridDocument*           pDoc       = NULL,
                                    PSS_ProcessGraphModelMdlBP* pModel     = NULL,
                                    PSS_ProcessGraphModelDoc*   pSourceDoc = NULL);

        virtual ~PSS_MercutioReportGenerator();

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
        * Gets the report title
        *@return the report title
        */
        virtual const CString GetReportTitle() const;

        /**
        * Fills the grid
        *@param gridCore - the grid to fill
        *@param index - the generator tab index
        */
        virtual bool FillGrid(CGXGridCore& GridCore, size_t Index);

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
        * Called after the report was read
        *@param ar - the archive from which the report was read
        */
        virtual void OnPostRead(CArchive& ar);

    protected:
        /**
        * Fills the tab array
        */
        virtual void FillTabArray();

    private:
        CString m_SubModelName;

        /**
        * Fills the grid procedures at index
        *@param ostream - the output stream
        *@param index - the index
        */
        bool FillGridProcedures(CGXGridCore& gridCore, std::size_t index);

        /**
        * Fills the grid deliverables at index
        *@param ostream - the output stream
        *@param index - the index
        */
        bool FillGridDeliverables(CGXGridCore& gridCore, std::size_t index);
};

#endif
