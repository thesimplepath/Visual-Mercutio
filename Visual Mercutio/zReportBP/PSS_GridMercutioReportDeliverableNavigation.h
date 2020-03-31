/****************************************************************************
 * ==> PSS_GridMercutioRepDeliverableNavigation ----------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will navigate through the       *
 *               deliverables and write the Mercutio info to the report     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GridMercutioRepDeliverableNavigationH
#define PSS_GridMercutioRepDeliverableNavigationH

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
#include "zModelBP\PSS_ProcessNavigation.h"

// forward class declaration
class PSS_OStreamGrid;

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
* Navigator which will navigate through the deliverables and write the Mercutio info to the report
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_GridMercutioReportDeliverableNavigation : public PSS_ProcessNavigation
{
    public:
        /**
        * Constructor
        *@param pModel - the model
        *@param pClass - the custom data class
        */
        PSS_GridMercutioReportDeliverableNavigation(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);

        virtual ~PSS_GridMercutioReportDeliverableNavigation();

        /**
        * Called when the navigation starts
        *@return true on success, otherwise false
        */
        virtual bool OnStart();

        /**
        * Called when the navigation ends
        *@return true on success, otherwise false
        */
        virtual bool OnFinish();

        /**
        * Called when a deliverable link symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol);

    private:
        PSS_OStreamGrid* m_pOstream;
        CGXStyle         m_NormalStyle;
        CGXStyle         m_BoldStyle;
        CGXStyle         m_BlueStyle;
        CGXStyle         m_BoldBlueStyle;
        CGXStyle         m_GrayStyle;
        CGXStyle         m_LightGrayStyle;
        CGXStyle         m_BlackBorderStyle;
        CGXStyle         m_LeftOnlyBlackBorderStyle;
        CString          m_DescriptionLabel;
        CString          m_RuleListLabel;
        CString          m_KeyInfoLabel;
        CString          m_FormListLabel;
        CString          m_InputProcedureLabel;
        CString          m_OutputProcedureLabel;
        CString          m_ComingFromProcedureLabel;
        CString          m_GoingToProcedureLabel;
        CString          m_InitialProcedureLabel;
        CString          m_FinalProcedureLabel;
};

#endif
