/****************************************************************************
 * ==> PSS_RiskProbabilityContainer ----------------------------------------*
 ****************************************************************************
 * Description : Provides a risk probability container                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "ZVRiskProbabilityContainer.h"

// processsoft
#include "zBaseLib\PSS_TextFile.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_RiskProbabilityContainer
//---------------------------------------------------------------------------
PSS_RiskProbabilityContainer::PSS_RiskProbabilityContainer() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_RiskProbabilityContainer::~PSS_RiskProbabilityContainer()
{
    RemoveAllElements();
}
//---------------------------------------------------------------------------
BOOL PSS_RiskProbabilityContainer::LoadFile(const CString& fileName)
{
    if (fileName.IsEmpty())
        return FALSE;

    m_FileName = fileName;

    PSS_TextFile textFile;

    if (!textFile.OpenRead(m_FileName))
        return FALSE;

    BOOL    endReached = FALSE;
    CString text;

    while (!endReached)
    {
        textFile >> text;

        if (!text.IsEmpty())
            m_Set.Add(text);
        else
            endReached = TRUE;
    }

    textFile.CloseFile();

    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_RiskProbabilityContainer::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
CStringArray* PSS_RiskProbabilityContainer::GetElementsArray()
{
    return &m_Set;
}
//---------------------------------------------------------------------------
CString PSS_RiskProbabilityContainer::GetElementAt(std::size_t index) const
{
    if (index < GetElementCount())
        return m_Set.GetAt(index);

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_RiskProbabilityContainer::RemoveAllElements()
{
    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
