/****************************************************************************
 * ==> PSS_RiskTypeContainer -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a risk type container                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RiskTypeContainer.h"

// processsoft
#include "zBaseLib\PSS_TextFile.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_RiskTypeContainer
//---------------------------------------------------------------------------
PSS_RiskTypeContainer::PSS_RiskTypeContainer() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_RiskTypeContainer::~PSS_RiskTypeContainer()
{
    RemoveAllElements();
}
//---------------------------------------------------------------------------
BOOL PSS_RiskTypeContainer::LoadFile(const CString& fileName)
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
CString PSS_RiskTypeContainer::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
CStringArray* PSS_RiskTypeContainer::GetElementsArray()
{
    return &m_Set;
}
//---------------------------------------------------------------------------
CString PSS_RiskTypeContainer::GetElementAt(std::size_t index) const
{
    if (index < GetElementCount())
        return m_Set.GetAt(index);

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_RiskTypeContainer::RemoveAllElements()
{
    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
