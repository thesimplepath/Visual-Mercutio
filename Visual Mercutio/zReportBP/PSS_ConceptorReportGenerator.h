/****************************************************************************
 * ==> PSS_ConceptorReportGenerator ----------------------------------------*
 ****************************************************************************
 * Description : Provides a Conceptor report generator                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ConceptorReportGeneratorH
#define PSS_ConceptorReportGeneratorH

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
#ifndef PSS_ConceptorReportGenerator
    #define PSS_ConceptorReportGenerator ZBConceptorReportGenerator
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
* Conceptor report generator
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ConceptorReportGenerator : public PSS_ModelBPReportGenerator
{
    DECLARE_SERIAL(PSS_ConceptorReportGenerator)

    public:
        /**
        * Constructor
        *@param pDoc - the document
        *@param pModel - the model
        *@param pSourceDoc - the source document
        *@param includeSynthesis - if true, the synthesis will be included
        *@param includeDetail - if true, the details will be included
        *@param includeDeliverables - if true, the deliverabless will be included
        */
        PSS_ConceptorReportGenerator(PSS_GridDocument*           pDoc                = NULL,
                                     PSS_ProcessGraphModelMdlBP* pModel              = NULL,
                                     PSS_ProcessGraphModelDoc*   pSourceDoc          = NULL,
                                     BOOL                        includeSynthesis    = TRUE,
                                     BOOL                        includeDetail       = TRUE,
                                     BOOL                        includeDeliverables = TRUE);

        virtual ~PSS_ConceptorReportGenerator();

        /**
        * Initializes the generator
        *@param pDoc - the document
        *@param pModel - the model
        *@param pSourceDoc - the source document
        *@param includeSynthesis - if true, the synthesis will be included
        *@param includeDetail - if true, the details will be included
        *@param includeDeliverables - if true, the deliverabless will be included
        */
        virtual void Initialize(PSS_GridDocument*           pDoc,
                                PSS_ProcessGraphModelMdlBP* pModel,
                                PSS_ProcessGraphModelDoc*   pSourceDoc,
                                BOOL                        includeSynthesis    = TRUE,
                                BOOL                        includeDetail       = TRUE,
                                BOOL                        includeDeliverables = TRUE);

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
        virtual bool FillGrid(CGXGridCore& gridCore, std::size_t index);

        /**
        * Called after the report was read
        *@param ar - the archive from which the report was read
        */
        virtual void OnPostRead(CArchive& ar);

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
        /**
        * Fills the tab array
        */
        virtual void FillTabArray();

    private:
        CObArray     m_ModelArray;
        CStringArray m_ProcessNameArray;
        CStringArray m_UnitCommentArray;
        CGXStyle     m_BlueStyle;
        CGXStyle     m_OrangeStyle;
        CGXStyle     m_GrayStyle;
        CGXStyle     m_BlackBorderStyle;
        CGXStyle     m_LeftOnlyBlackBorderStyle;
        CGXStyle     m_RightOnlyBlackBorderStyle;
        CGXStyle     m_TopOnlyBlackBorderStyle;
        CGXStyle     m_BottomOnlyBlackBorderStyle;
        BOOL         m_IncludeSynthesis;
        BOOL         m_IncludeDetail;
        BOOL         m_IncludeDeliverables;

        /**
        * Removes all the data
        */
        void RemoveAllData();

        /**
        * Fills the tab unit group
        *@param pGroup - the group to fill
        */
        void FillTabUnitGroup(PSS_UserGroupEntity* pGroup);

        /**
        * Fills the synthesis at index
        *@param ostream - the output stream
        *@param index - the index
        */
        bool FillSynthesis(PSS_OStreamGrid& ostream, std::size_t index);

        /**
        * Fills all the processes in the grid at index
        *@param ostream - the output stream
        *@param index - the index
        */
        bool FillGridAllProcess(PSS_OStreamGrid& ostream, std::size_t index);
};

#endif
