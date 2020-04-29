/****************************************************************************
 * ==> PSS_ExtractProcessName ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to find and extract all process names *
 *               of a Mercutio model                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ExtractProcessName.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "PSS_ProcessSymbolBP.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ExtractProcessName
//---------------------------------------------------------------------------
PSS_ExtractProcessName::PSS_ExtractProcessName(PSS_ProcessGraphModelMdl* pModel, PSS_Log* pLog) :
    PSS_BasicSymbolVisitor(),
    m_pModel(pModel),
    m_pLog(pLog),
    m_pArray(NULL)
{}
//---------------------------------------------------------------------------
PSS_ExtractProcessName::~PSS_ExtractProcessName()
{}
//---------------------------------------------------------------------------
bool PSS_ExtractProcessName::FillProcessNameArray(CStringArray* pArray, int firstIndexToSort)
{
    m_pArray = pArray;

    if (m_pModel && m_pArray)
    {
        m_pModel->AcceptVisitor(*this);

        // sort the list by ascending alphabetical order
        Sort(firstIndexToSort);

        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ExtractProcessName::Visit(CODComponent& component)
{
    CODComponent*        pSymbol  = &component;
    PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pSymbol);

    if (pProcess)
        return AddProcessSymbol(pProcess);

    // nothing to do
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractProcessName::AddProcessSymbol(PSS_ProcessSymbolBP* pSymbol)
{
    PSS_Assert(pSymbol);
    PSS_Assert(m_pArray);

    if (!Exist(*m_pArray, pSymbol->GetSymbolName()))
        m_pArray->Add(pSymbol->GetSymbolName());

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractProcessName::Exist(const CStringArray& strArray, const CString& processName)
{
    const std::size_t counter = strArray.GetSize();

    for (size_t i = 0; i < counter; ++i)
        if (strArray.GetAt(i) == processName)
            return true;

    return false;
}
//---------------------------------------------------------------------------
void PSS_ExtractProcessName::Sort(int first)
{
    if (first >= m_pArray->GetUpperBound())
        return;

    std::size_t curPos  = first;
    std::size_t nextPos = first;

    while (curPos <= m_pArray->GetUpperBound())
    {
        nextPos = curPos + 1;

        if (nextPos <= m_pArray->GetUpperBound())
        {
            const CString curStr  = m_pArray->GetAt(curPos);
            const CString nextStr = m_pArray->GetAt(nextPos);

            if (!curStr.IsEmpty() && !nextStr.IsEmpty())
                if (curStr.Compare(nextStr) > 0)
                {
                    m_pArray->SetAt(curPos,  nextStr);
                    m_pArray->SetAt(nextPos, curStr);

                    Sort(first);
                    return;
                }
        }

        ++curPos;
    }
}
//---------------------------------------------------------------------------
