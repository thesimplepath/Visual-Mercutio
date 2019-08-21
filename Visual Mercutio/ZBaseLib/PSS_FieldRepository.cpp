/****************************************************************************
 * ==> PSS_FieldRepository -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a repository field                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_FieldRepository.h"

// processsoft
#include "PSS_File.h"

//---------------------------------------------------------------------------
// PSS_FieldRepository
//---------------------------------------------------------------------------
PSS_FieldRepository::PSS_FieldRepository() :
    m_GlobalFieldManager(NULL),
    m_HistoryValueManager(NULL),
    m_Document(NULL),
    m_ReadOnly(TRUE),
    m_IsValid(FALSE)
{
    m_GlobalFieldManager  = new PSS_GlobalFieldManager();
    m_HistoryValueManager = new ZAHistoryFieldManager();
    m_Document            = new PSS_GlobalFieldDocument();
}
//---------------------------------------------------------------------------
PSS_FieldRepository::PSS_FieldRepository(const PSS_FieldRepository& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_FieldRepository::~PSS_FieldRepository()
{
    if (m_GlobalFieldManager)
        delete m_GlobalFieldManager;

    if (m_HistoryValueManager)
        delete m_HistoryValueManager;

    if (m_Document)
        delete m_Document;
}
//---------------------------------------------------------------------------
const PSS_FieldRepository& PSS_FieldRepository::operator = (const PSS_FieldRepository& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_FieldRepository::InitializeEmpty()
{
    m_IsValid  = TRUE;
    m_ReadOnly = FALSE;

    return m_IsValid;
}
//---------------------------------------------------------------------------
BOOL PSS_FieldRepository::OpenRepository(const CString& fileName, BOOL readOnly)
{
    m_ReadOnly = readOnly;

    PSS_File file(fileName);

    // keep repository file name
    m_FileName = fileName;

    if (fileName.IsEmpty() || !file.Exist())
        if (!m_ReadOnly)
        {
            // set the document path name
            m_Document->Initialize(m_GlobalFieldManager, m_HistoryValueManager);
            m_Document->SetPathName(fileName, FALSE);

            return m_IsValid = TRUE;
        }
        else
            return m_IsValid = FALSE;

    return m_IsValid = m_Document->ReadDocument(fileName, m_GlobalFieldManager, m_HistoryValueManager);
}
//---------------------------------------------------------------------------
BOOL PSS_FieldRepository::CloseRepository()
{
    if (!m_IsValid)
        return FALSE;

    if (m_ReadOnly)
        return TRUE;

    m_Document->SetModifiedFlag(TRUE);

    return m_Document->SaveDocument();
}
//---------------------------------------------------------------------------
BOOL PSS_FieldRepository::SaveRepositoryToFile(const CString& fileName)
{
    m_Document->Initialize(fileName, m_GlobalFieldManager, m_HistoryValueManager);

    return m_Document->SaveDocument();
}
//---------------------------------------------------------------------------
BOOL PSS_FieldRepository::ReloadRepository(BOOL saveBefore)
{
    if (!m_IsValid)
        return FALSE;

    // if save is requested, close the repository with save effect if not read-only
    if (saveBefore)
        CloseRepository();

    return m_IsValid = m_Document->ReadDocument(m_FileName, m_GlobalFieldManager, m_HistoryValueManager);
}
//---------------------------------------------------------------------------
BOOL PSS_FieldRepository::Import(PSS_FieldRepository& fieldRepository, BOOL replaceExisting)
{
    const int fieldCount = fieldRepository.GetFieldCount();

    for (int i = 0; i < fieldCount; ++i)
    {
        PSS_FieldObjectDefinition* pObjectDefinition = fieldRepository.GetFieldAt(i);

        if (pObjectDefinition)
        {
            PSS_FieldObjectDefinition* pSourceObjectDefinition = FindField(pObjectDefinition->GetFieldName());

            // if a source already exists and the replace flag is false, do nothing
            if (pSourceObjectDefinition && replaceExisting == FALSE)
                continue;

            // if no source
            if (!pSourceObjectDefinition)
                // add a new one
                AddField(pObjectDefinition->Clone());
            else
            {
                // copy values
                pSourceObjectDefinition->SetDescription(pObjectDefinition->GetDescription());
                pSourceObjectDefinition->SetHelpUserDescription(pObjectDefinition->GetHelpUserDescription());
                pSourceObjectDefinition->SetSorted(pObjectDefinition->IsSorted());

                // if no object included
                if (!pSourceObjectDefinition->GetObject())
                {
                    // assign the object
                    pSourceObjectDefinition->SetClassName(pObjectDefinition->GetClassName());
                    pSourceObjectDefinition->SetObject(pObjectDefinition->GetObject() ? pObjectDefinition->GetObject()->Clone() : NULL);
                }
            }

            // process the history
            ZAHistoryField* pObjectHistory = fieldRepository.FindFieldHistory(pObjectDefinition->GetFieldName());

            if (pObjectHistory)
            {
                const CStringArray& values     = pObjectHistory->GetValueArray();
                const int           valueCount = values.GetSize();

                for (int index = 0; index < valueCount; ++index)
                    AddFieldHistoryValue(pObjectDefinition->GetFieldName(), values.GetAt(index));
            }

            // set the read-only flag
            ZAHistoryField* pHistory = FindFieldHistory(pObjectDefinition->GetFieldName());

            if (pHistory)
                pHistory->SetReadOnly(pObjectHistory->IsReadOnly());
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
