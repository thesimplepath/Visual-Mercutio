/****************************************************************************
 * ==> PSS_RiskImpactContainer ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a risk impact container                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RiskImpactContainer.h"

// processsoft
#include "zBaseLib\PSS_TextFile.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_RiskImpactContainer
//---------------------------------------------------------------------------
PSS_RiskImpactContainer::PSS_RiskImpactContainer()
{}
//---------------------------------------------------------------------------
PSS_RiskImpactContainer::~PSS_RiskImpactContainer()
{
    // NOTE use the fully qualified name to avoid to call a pure virtual function on destruction
    PSS_RiskImpactContainer::RemoveAllElements();
}
//---------------------------------------------------------------------------
BOOL PSS_RiskImpactContainer::LoadFile(const CString& fileName)
{
    if (fileName.IsEmpty())
        return FALSE;

    m_FileName = fileName;

    PSS_TextFile textFile;

    if (!textFile.OpenRead(m_FileName))
        return FALSE;

    BOOL    endReached = FALSE;
    CString text       = _T("");

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
CString PSS_RiskImpactContainer::GetFileName()
{
    return m_FileName;
}
//---------------------------------------------------------------------------
CStringArray* PSS_RiskImpactContainer::GetElementsArray()
{
    return &m_Set;
}
//---------------------------------------------------------------------------
CString PSS_RiskImpactContainer::GetElementAt(std::size_t index) const
{
    if (index < GetElementCount())
        return m_Set.GetAt(index);

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_RiskImpactContainer::RemoveAllElements()
{
    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
