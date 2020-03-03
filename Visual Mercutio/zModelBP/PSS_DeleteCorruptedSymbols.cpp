/****************************************************************************
 * ==> PSS_DeleteCorruptedSymbols ------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to delete the corrupted symbols       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DeleteCorruptedSymbols.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_DeleteCorruptedSymbols
//---------------------------------------------------------------------------
PSS_DeleteCorruptedSymbols::PSS_DeleteCorruptedSymbols()
{}
//---------------------------------------------------------------------------
PSS_DeleteCorruptedSymbols::~PSS_DeleteCorruptedSymbols()
{}
//---------------------------------------------------------------------------
void PSS_DeleteCorruptedSymbols::CheckModel(PSS_ProcessGraphModelMdlBP* pRootModel)
{
    if (!pRootModel)
        return;

    // get the pages contained in the model controller
    PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = pRootModel->GetPageSet();

    if (!pSet)
        return;

    PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(pSet);

    // iterate through the children pages contained in the model controller
    for (PSS_ProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
    {
        // get the current page model controller
        PSS_ProcessGraphModelMdlBP* pCurModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

        if (!pCurModel)
            continue;

        // get the symbols contained in the model controller
        CODComponentSet* pCompSet = pCurModel->GetComponents();

        if (!pCompSet)
            continue;

        const int symbolCount = pCompSet->GetSize();

        // iterate through the symbols contained in the model controller
        for (int i = 0; i < symbolCount; ++i)
        {
            CODComponent* pComponent = pCompSet->GetAt(i);

            if (!pComponent)
                continue;

            PSS_ProcedureSymbolBP* pProcedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pComponent);

            // is a procedure?
            if (pProcedure)
            {
                if (IsCorrupted(pProcedure))
                    m_CorruptedSymbols.Add(pProcedure);

                continue;
            }

            PSS_StartSymbolBP* pStart = dynamic_cast<PSS_StartSymbolBP*>(pComponent);

            // is a start symbol?
            if (pStart)
            {
                if (IsCorrupted(pStart))
                    m_CorruptedSymbols.Add(pStart);

                continue;
            }

            PSS_StopSymbolBP* pStop = dynamic_cast<PSS_StopSymbolBP*>(pComponent);

            // is a stop symbol?
            if (pComponent && ISA(pComponent, PSS_StopSymbolBP))
            {
                if (IsCorrupted(pStop))
                    m_CorruptedSymbols.Add(pStop);

                continue;
            }

            PSS_DoorSymbolBP* pDoor = dynamic_cast<PSS_DoorSymbolBP*>(pComponent);

            // is a door symbol?
            if (pDoor)
            {
                if (IsCorrupted(pDoor))
                    m_CorruptedSymbols.Add(pDoor);

                continue;
            }

            PSS_DeliverableLinkSymbolBP* pLink = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pComponent);

            // is a deliverable link symbol?
            if (pLink)
            {
                if (IsCorrupted(pLink))
                    m_CorruptedSymbols.Add(pLink);

                continue;
            }

            PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pComponent);

            // is a process?
            if (pProcess)
                if (IsCorrupted(pProcess))
                    m_CorruptedSymbols.Add(pProcess);
                else
                {
                    // get the process model controller
                    PSS_ProcessGraphModelMdlBP* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pProcess->GetModel());

                    // call the CheckModel() function recursively until all the pages contained
                    // in the children processes were visited
                    CheckModel(pChildModel);
                }
        }
    }
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_DeleteCorruptedSymbols::GetCorruptedSymbolList()
{
    return &m_CorruptedSymbols;
}
//---------------------------------------------------------------------------
BOOL PSS_DeleteCorruptedSymbols::IsCorrupted(PSS_ProcessSymbolBP* pSymbol)
{
    if (!pSymbol)
        return FALSE;

    // if the symbol is a duplicate, it should provide its original symbol. If not possible,
    // the original was deleted, so the symbol is corrupted
    return (!pSymbol->IsLocal() && !pSymbol->GetLocalSymbol());
}
//---------------------------------------------------------------------------
BOOL PSS_DeleteCorruptedSymbols::IsCorrupted(PSS_ProcedureSymbolBP* pSymbol)
{
    if (!pSymbol)
        return FALSE;

    // if the symbol is a duplicate, it should provide its original symbol. If not possible,
    // the original was deleted, so the symbol is corrupted
    return (!pSymbol->IsLocal() && !pSymbol->GetLocalSymbol());
}
//---------------------------------------------------------------------------
BOOL PSS_DeleteCorruptedSymbols::IsCorrupted(PSS_StartSymbolBP* pSymbol)
{
    if (!pSymbol)
        return FALSE;

    // if the symbol is a duplicate, it should provide its original symbol. If not possible,
    // the original was deleted, so the symbol is corrupted
    return (!pSymbol->IsLocal() && !pSymbol->GetLocalSymbol());
}
//---------------------------------------------------------------------------
BOOL PSS_DeleteCorruptedSymbols::IsCorrupted(PSS_StopSymbolBP* pSymbol)
{
    if (!pSymbol)
        return FALSE;

    // if the symbol is a duplicate, it should provide its original symbol. If not possible,
    // the original was deleted, so the symbol is corrupted
    return (!pSymbol->IsLocal() && !pSymbol->GetLocalSymbol());
}
//---------------------------------------------------------------------------
BOOL PSS_DeleteCorruptedSymbols::IsCorrupted(PSS_DoorSymbolBP* pSymbol)
{
    if (pSymbol)
        return FALSE;

    // if the symbol is a duplicate, it should provide its original symbol. If not possible,
    // the original was deleted, so the symbol is corrupted
    if (!pSymbol->IsLocal() && !pSymbol->GetLocalSymbol())
        return TRUE;

    // if a door can no longer provide its twin, then the twin symbol was deleted. If it's the case,
    // the symbol is corrupted, because a door cannot exists without its twin
    if (!pSymbol->GetTwinDoorSymbol())
        return TRUE;

    // if the twin door contains a link which doesn't match with the starting door symbol,
    // then the twin door is corrupted
    if (pSymbol->GetTwinDoorSymbol() && pSymbol->GetTwinDoorSymbol()->GetTwinDoorSymbol() != pSymbol)
        return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_DeleteCorruptedSymbols::IsCorrupted(PSS_PageSymbolBP* pSymbol)
{
    if (pSymbol)
        return FALSE;

    // if the symbol is a duplicate, it should provide its original symbol. If not possible,
    // the original was deleted, so the symbol is corrupted
    if (!pSymbol->IsLocal() && !pSymbol->GetLocalSymbol())
        return TRUE;

    // if a page can no longer provide its twin, then the twin symbol was deleted. If it's the case,
    // the symbol is corrupted, because a page cannot exists without its twin
    if (!pSymbol->GetTwinPageSymbol())
        return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_DeleteCorruptedSymbols::IsCorrupted(PSS_PackageSymbolBP* pSymbol)
{
    if (!pSymbol)
        return FALSE;

    // if the symbol is a duplicate, it should provide its original symbol. If not possible,
    // the original was deleted, so the symbol is corrupted
    return (!pSymbol->IsLocal() && !pSymbol->GetLocalSymbol());
}
//---------------------------------------------------------------------------
BOOL PSS_DeleteCorruptedSymbols::IsCorrupted(PSS_DeliverableLinkSymbolBP* pSymbol)
{
    if (!pSymbol)
        return FALSE;

    // if the symbol is a duplicate, it should provide its original symbol. If not possible,
    // the original was deleted, so the symbol is corrupted
    return (!pSymbol->IsLocal() && !pSymbol->GetLocalSymbol());
}
//---------------------------------------------------------------------------
