/****************************************************************************
 * ==> PSS_GridSesterceProcessNavigation -----------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will navigate through the       *
 *               processes and write the Sesterce info to the report        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GridSesterceProcessNavigationH
#define PSS_GridSesterceProcessNavigationH

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
* Navigator which will navigate through the processes and write the Sesterce info to the report
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_GridSesterceProcessNavigation : public PSS_ProcessNavigation
{
    public:
        /**
        * Constructor
        *@param pModel - the model, can be NULL
        *@param pClass - the custom data class, can be NULL
        */
        PSS_GridSesterceProcessNavigation(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);

        virtual ~PSS_GridSesterceProcessNavigation();

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
        * Called when a procedure symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);

        /**
        * Called when a deliverable link symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol);

    private:
        PSS_OStreamGrid* m_pOStream;
        CGXStyle         m_NormalStyle;
        CGXStyle         m_BoldStyle;
        CGXStyle         m_RoseStyle;
        CGXStyle         m_BoldRoseStyle;
        CGXStyle         m_BlueStyle;
        CGXStyle         m_GreenStyle;
        CGXStyle         m_RedStyle;
        CGXStyle         m_GrayStyle;
        CGXStyle         m_LightGrayStyle;
        CGXStyle         m_BlackBorderStyle;
        CGXStyle         m_LeftOnlyBlackBorderStyle;
        CGXStyle         m_PercentFormatStyle;
        CGXStyle         m_AmountFormatStyle;
        CGXStyle         m_NumberTwoDecFormatStyle;
        CGXStyle         m_NumericCellStyle;
};

#endif
