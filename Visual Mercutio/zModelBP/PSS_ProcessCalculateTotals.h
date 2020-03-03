/****************************************************************************
 * ==> PSS_ProcessCalculateTotals ------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to calculates the process totals      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessCalculateTotalsH
#define PSS_ProcessCalculateTotalsH

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
#include "PSS_ProcessNavigation.h"

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Navigator to calculates the process totals
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessCalculateTotals : public PSS_ProcessNavigation
{
    public:
        /**
        * Constructor
        *@param pModel - the model
        *@param pClass - the class
        */
        PSS_ProcessCalculateTotals(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);

        virtual ~PSS_ProcessCalculateTotals();

        /**
        * Gets the procedure cost
        *@return the procedure cost
        */
        virtual inline double GetProcedureCost() const;

        /**
        * Gets the procedure workload forecast
        *@return the procedure workload forecast
        */
        virtual inline double GetProcedureWorkloadForecast() const;

        /**
        * Gets the procedure cost forecast
        *@return the procedure cost forecast
        */
        virtual inline double GetProcedureCostForecast() const;

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
        * Called when a door symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnDoorSymbol(PSS_DoorSymbolBP* pSymbol);

        /**
        * Called when a page symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnPageSymbol(PSS_PageSymbolBP* pSymbol);

        /**
        * Called when a procedure symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);

        /**
        * Called when a process symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol);

        /**
        * Called when a start symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnStartSymbol(PSS_StartSymbolBP* pSymbol);

        /**
        * Called when a stop symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnStopSymbol(PSS_StopSymbolBP* pSymbol);

        /**
        * Called when a deliverable link symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol);

    private:
        double m_ProcedureCost;
        double m_ProcedureWorkloadForecast;
        double m_ProcedureCostForecast;
};

//---------------------------------------------------------------------------
// PSS_ProcessCalculateTotals
//---------------------------------------------------------------------------
double PSS_ProcessCalculateTotals::GetProcedureCost() const
{
    return m_ProcedureCost;
}
//---------------------------------------------------------------------------
double PSS_ProcessCalculateTotals::GetProcedureWorkloadForecast() const
{
    return m_ProcedureWorkloadForecast;
}
//---------------------------------------------------------------------------
double PSS_ProcessCalculateTotals::GetProcedureCostForecast() const
{
    return m_ProcedureCostForecast;
}
//---------------------------------------------------------------------------

#endif
