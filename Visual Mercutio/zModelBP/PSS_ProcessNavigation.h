/****************************************************************************
 * ==> PSS_ProcessNavigation -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to visit the proces symbols           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessNavigationH
#define PSS_ProcessNavigationH

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

// class name mapping
#ifndef PSS_Symbol
    #define PSS_Symbol ZBSymbol
#endif
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif
#ifndef PSS_DoorSymbolBP
    #define PSS_DoorSymbolBP ZBBPDoorSymbol
#endif
#ifndef PSS_PageSymbolBP
    #define PSS_PageSymbolBP ZBBPPageSymbol
#endif
#ifndef PSS_ProcedureSymbolBP
    #define PSS_ProcedureSymbolBP ZBBPProcedureSymbol
#endif
#ifndef PSS_ProcessSymbolBP
    #define PSS_ProcessSymbolBP ZBBPProcessSymbol
#endif
#ifndef PSS_StartSymbolBP
    #define PSS_StartSymbolBP ZBBPStartSymbol
#endif
#ifndef PSS_StopSymbolBP
    #define PSS_StopSymbolBP ZBBPStopSymbol
#endif
#ifndef PSS_DeliverableLinkSymbolBP
    #define PSS_DeliverableLinkSymbolBP ZBDeliverableLinkSymbol
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_Log;
class PSS_Symbol;
class PSS_LinkSymbol;
class PSS_DoorSymbolBP;
class PSS_PageSymbolBP;
class PSS_ProcedureSymbolBP;
class PSS_ProcessSymbolBP;
class PSS_StartSymbolBP;
class PSS_StopSymbolBP;
class PSS_DeliverableLinkSymbolBP;
class PSS_ProcessGraphModelMdl;
class PSS_Log;

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
* Navigator to visit the proces symbols
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessNavigation : public PSS_BasicSymbolVisitor
{
public:
    /**
    * Constructor
    *@param pModel - the model
    *@param pClass - the class
    */
    PSS_ProcessNavigation(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);

    virtual ~PSS_ProcessNavigation();

    /**
    * Navigates in the model
    *@param pModel - the model
    *@param pClass - the class
    */
    bool Navigate(PSS_ProcessGraphModelMdl* pModel, void* pClass);
    bool Navigate(PSS_ProcessGraphModelMdl* pModel);
    bool Navigate();

    /**
    * Called when the navigation starts
    *@return true on success, otherwise false
    */
    virtual inline bool OnStart();

    /**
    * Called when the navigation ends
    *@return true on success, otherwise false
    */
    virtual inline bool OnFinish();

    /**
    * Called when a door symbol is visited
    *@param pSymbol - the visited symbol
    *@return true on success, otherwise false
    */
    virtual inline bool OnDoorSymbol(PSS_DoorSymbolBP* pSymbol);

    /**
    * Called when a page symbol is visited
    *@param pSymbol - the visited symbol
    *@return true on success, otherwise false
    */
    virtual inline bool OnPageSymbol(PSS_PageSymbolBP* pSymbol);

    /**
    * Called when a procedure symbol is visited
    *@param pSymbol - the visited symbol
    *@return true on success, otherwise false
    */
    virtual inline bool OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);

    /**
    * Called when a process symbol is visited
    *@param pSymbol - the visited symbol
    *@return true on success, otherwise false
    */
    virtual inline bool OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol);

    /**
    * Called when a start symbol is visited
    *@param pSymbol - the visited symbol
    *@return true on success, otherwise false
    */
    virtual inline bool OnStartSymbol(PSS_StartSymbolBP* pSymbol);

    /**
    * Called when a stop symbol is visited
    *@param pSymbol - the visited symbol
    *@return true on success, otherwise false
    */
    virtual inline bool OnStopSymbol(PSS_StopSymbolBP* pSymbol);

    /**
    * Called when a deliverable link symbol is visited
    *@param pSymbol - the visited symbol
    *@return true on success, otherwise false
    */
    virtual inline bool OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol);

    /**
    * Called when a symbol is visited
    *@param pSymbol - the visited symbol
    *@return true on success, otherwise false
    */
    virtual inline bool OnSymbol(PSS_Symbol* pSymbol);

    /**
    * Called when a link symbol is visited
    *@param pSymbol - the visited symbol
    *@return true on success, otherwise false
    */
    virtual inline bool OnLink(PSS_LinkSymbol* pLink);

    /**
    * Sets the logger to use
    *@param pLog - the logger to use
    */
    virtual inline void SetLog(PSS_Log* pLog);

    /**
    * Visits the target symbol
    *@param component - target symbol component to visit
    *@return true if visit succeeded, otherwise false
    */
    virtual bool Visit(CODComponent& component);

    /**
    * Gets the error counter
    *@return the error counter
    */
    virtual inline std::size_t GetErrorCounter() const;

    /**
    * Gets the warning counter
    *@return the warning counter
    */
    virtual inline std::size_t GetWarningCounter() const;

protected:
    PSS_ProcessGraphModelMdl* m_pModel;
    PSS_Log*                  m_pLog;
    void*                     m_pClass;
    std::size_t               m_ErrorCounter;
    std::size_t               m_WarningCounter;
};

//---------------------------------------------------------------------------
// PSS_ProcessNavigation
//---------------------------------------------------------------------------
bool PSS_ProcessNavigation::OnStart()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessNavigation::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessNavigation::OnDoorSymbol(PSS_DoorSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessNavigation::OnPageSymbol(PSS_PageSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessNavigation::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessNavigation::OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessNavigation::OnStartSymbol(PSS_StartSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessNavigation::OnStopSymbol(PSS_StopSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessNavigation::OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessNavigation::OnSymbol(PSS_Symbol* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessNavigation::OnLink(PSS_LinkSymbol* pLink)
{
    return true;
}
//---------------------------------------------------------------------------
void PSS_ProcessNavigation::SetLog(PSS_Log* pLog)
{
    m_pLog = pLog;
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessNavigation::GetErrorCounter() const
{
    return m_ErrorCounter;
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessNavigation::GetWarningCounter() const
{
    return m_WarningCounter;
}
//---------------------------------------------------------------------------

#endif
