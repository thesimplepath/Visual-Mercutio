/****************************************************************************
 * ==> PSS_FieldDefinitionDataFeed -----------------------------------------*
 ****************************************************************************
 * Description : Provides a data feed for field definition                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_FieldDefinitionDataFeed.h"

 // processsoft
#include "PSS_Tokenizer.h"
#include "PSS_ObjectUtility.h"

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const char g_FieldNameKey[]        = "$$FieldName$$";
const char g_FieldDescriptionKey[] = "$$FieldDescription$$";
const char g_FieldUserHelpKey[]    = "$$FieldUserHelp$$";
const char g_FieldReadOnlyKey[]    = "$$FieldReadOnly$$";
const char g_FieldListSortedKey[]  = "$$FieldListSorted$$";
const char g_FieldClassNameKey[]   = "$$FieldClassName$$";
const char g_FieldMultiColumnKey[] = "$$FieldIsMultiColumn$$";
const char g_FieldHeaderNameKey[]  = "$$FieldHeaderName$$";
//---------------------------------------------------------------------------
// PSS_FieldDefinitionDataFeed::IFieldExport
//---------------------------------------------------------------------------
PSS_FieldDefinitionDataFeed::IFieldExport::IFieldExport(const CString& key, const CString& value) :
    CObject(),
    m_Key(key),
    m_Value(value)
{}
//---------------------------------------------------------------------------
PSS_FieldDefinitionDataFeed::IFieldExport::~IFieldExport()
{}
//---------------------------------------------------------------------------
// PSS_FieldDefinitionDataFeed
//---------------------------------------------------------------------------
PSS_FieldDefinitionDataFeed::PSS_FieldDefinitionDataFeed(const CString&                fileName,
                                                         PSS_FieldRepository*          pFieldRepository,
                                                         PSS_FieldObjectDefinition*    pObjectDefinition,
                                                         BOOL                          generateHeader,
                                                         ESynchronizationSeparatorType separatorType,
                                                         const CString&                schema,
                                                         int                           propagationMode,
                                                         BOOL                          emptyWhenZero,
                                                         PSS_StatusBar*                pStatusBar) :
    PSS_Export(fileName, generateHeader, separatorType, schema, propagationMode, emptyWhenZero, pStatusBar),
    m_pObjectDefinition(pObjectDefinition),
    m_pSourceFieldRepository(pFieldRepository),
    m_pImportedFieldRepository(NULL)
{}
//---------------------------------------------------------------------------
PSS_FieldDefinitionDataFeed::PSS_FieldDefinitionDataFeed(const CString&                fileName,
                                                         PSS_FieldRepository*          pFieldRepository,
                                                         BOOL                          generateHeader,
                                                         ESynchronizationSeparatorType separatorType,
                                                         const CString&                schema,
                                                         int                           propagationMode,
                                                         BOOL                          emptyWhenZero,
                                                         PSS_StatusBar*                pStatusBar) :
    PSS_Export(fileName, generateHeader, separatorType, schema, propagationMode, emptyWhenZero, pStatusBar),
    m_pObjectDefinition(NULL),
    m_pSourceFieldRepository(pFieldRepository),
    m_pImportedFieldRepository(NULL)
{}
//---------------------------------------------------------------------------
PSS_FieldDefinitionDataFeed::PSS_FieldDefinitionDataFeed(const PSS_FieldDefinitionDataFeed& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_FieldDefinitionDataFeed::~PSS_FieldDefinitionDataFeed()
{
    DeleteLineArray();
}
//---------------------------------------------------------------------------
const PSS_FieldDefinitionDataFeed& PSS_FieldDefinitionDataFeed::operator = (const PSS_FieldDefinitionDataFeed& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_FieldDefinitionDataFeed::ProcessLine(const CString& line)
{
    // the received line is exactly the same as the exported one
    CString       key;
    CString       value;
    PSS_Tokenizer tokenizer;

    switch (GetSeparatorType())
    {
        case E_SS_Comma:      tokenizer.SetSeparator(',');  break;
        case E_SS_SemiColumn: tokenizer.SetSeparator(';');  break;
        default:              tokenizer.SetSeparator('\t'); break;
    }

    // extract the key
    key = tokenizer.GetFirstToken(line);

    // if no key, end
    if (key.IsEmpty())
        return FALSE;

    // extract the value
    value = tokenizer.GetNextToken();

    std::unique_ptr<IFieldExport> pFieldExport(new IFieldExport(key, value));
    m_LineArray.Add(pFieldExport.get());
    pFieldExport.release();

    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_FieldDefinitionDataFeed::GetExportedLine(CObject* pObj) const
{
    PSS_FieldObjectDefinition* pObjectDefinition = (PSS_FieldObjectDefinition*)pObj;

    if (!pObjectDefinition)
        return "";

    PSS_HistoryField* pObjectHistory = NULL;

    if (m_pSourceFieldRepository)
        pObjectHistory = m_pSourceFieldRepository->FindFieldHistory(pObjectDefinition->GetFieldName());

    PSS_Tokenizer tokenizer;

    switch (GetSeparatorType())
    {
        case E_SS_Comma:      tokenizer.SetSeparator(',');  break;
        case E_SS_SemiColumn: tokenizer.SetSeparator(';');  break;
        default:              tokenizer.SetSeparator('\t'); break;
    }

    CString line;

    // add the field name
    tokenizer.AddToken(g_FieldNameKey);
    tokenizer.AddToken(pObjectDefinition->GetFieldName());
    line  = tokenizer.GetString();
    line += "\r\n";
    tokenizer.ClearAllTokens();

    // add the field description
    tokenizer.AddToken(g_FieldDescriptionKey);
    tokenizer.AddToken(pObjectDefinition->GetDescription());
    line += tokenizer.GetString();
    line += "\r\n";
    tokenizer.ClearAllTokens();

    // add the field user description
    tokenizer.AddToken(g_FieldUserHelpKey);
    tokenizer.AddToken(pObjectDefinition->GetHelpUserDescription());
    line += tokenizer.GetString();
    line += "\r\n";
    tokenizer.ClearAllTokens();

    // add the read only flag
    tokenizer.AddToken(g_FieldReadOnlyKey);
    tokenizer.AddToken((pObjectHistory && pObjectHistory->IsReadOnly()) ? "1" : "0");
    line += tokenizer.GetString();
    line += "\r\n";
    tokenizer.ClearAllTokens();

    // add the read only flag
    tokenizer.AddToken(g_FieldListSortedKey);
    tokenizer.AddToken((pObjectHistory && pObjectDefinition->IsSorted()) ? "1" : "0");
    line += tokenizer.GetString();
    line += "\r\n";
    tokenizer.ClearAllTokens();

    // add the class name 
    tokenizer.AddToken(g_FieldClassNameKey);
    tokenizer.AddToken(pObjectDefinition->GetClassName());
    line += tokenizer.GetString();
    line += "\r\n";
    tokenizer.ClearAllTokens();

    const std::size_t objectCount = pObjectHistory->GetCount();

    // export the field history
    for (std::size_t i = 0; pObjectHistory && i < objectCount; ++i)
    {
        // add the field history value
        tokenizer.AddToken(pObjectHistory->GetValueArray().GetAt(i));
        line += tokenizer.GetString();
        line += "\r\n";
        tokenizer.ClearAllTokens();
    }

    return line;
}
//---------------------------------------------------------------------------
CString PSS_FieldDefinitionDataFeed::GetHeaderLine() const
{
    return "";
}
//---------------------------------------------------------------------------
double PSS_FieldDefinitionDataFeed::GetForecastedTotalObject() const
{
    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_FieldDefinitionDataFeed::DoExportLoop()
{
    // if not object to export, do nothing
    if (!m_pObjectDefinition)
        return FALSE;

    CString line;

    // only one object to export
    line = GetExportedLine(m_pObjectDefinition);
    WriteLine(line);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_FieldDefinitionDataFeed::PreImport()
{
    DeleteLineArray();
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_FieldDefinitionDataFeed::PostImport()
{
    CString fieldName;
    CString description;
    CString helpUser;
    CString className;
    CString headerNames;
    int     i             = 0;
    BOOL    readOnly      = FALSE;
    BOOL    sorted        = TRUE;
    BOOL    isMultiColumn = FALSE;

    // iterate through line objects and find the fields
    for (; i < m_LineArray.GetSize(); ++i)
    {
        IFieldExport* pFieldExport = dynamic_cast<IFieldExport*>(m_LineArray.GetAt(i));

        if (!pFieldExport)
            break;

        if (pFieldExport->m_Key == g_FieldNameKey)
            fieldName = pFieldExport->m_Value;
        else
        if (pFieldExport->m_Key == g_FieldDescriptionKey)
            description = pFieldExport->m_Value;
        else
        if (pFieldExport->m_Key == g_FieldUserHelpKey)
            helpUser = pFieldExport->m_Value;
        else
        if (pFieldExport->m_Key == g_FieldReadOnlyKey)
            readOnly = (pFieldExport->m_Value == "1" ? 1 : 0);
        else
        if (pFieldExport->m_Key == g_FieldListSortedKey)
            sorted = (pFieldExport->m_Value == "1" ? 1 : 0);
        else
        if (pFieldExport->m_Key == g_FieldClassNameKey)
            className = pFieldExport->m_Value;
        else
        if (pFieldExport->m_Key == g_FieldMultiColumnKey)
            isMultiColumn = (pFieldExport->m_Value == "1" ? 1 : 0);
        else
        if (pFieldExport->m_Key == g_FieldHeaderNameKey)
            headerNames = pFieldExport->m_Value;
        else
            break;
    }

    // no field name found, error
    if (fieldName.IsEmpty())
        return FALSE;

    PSS_FieldObjectDefinition* pObjectDefinition = m_pSourceFieldRepository->FindField(fieldName);

    if (!pObjectDefinition)
    {
        // otherwise create the class and add it to the repository
        pObjectDefinition = new PSS_FieldObjectDefinition;

        if (!pObjectDefinition)
            return FALSE;

        pObjectDefinition->SetFieldName(fieldName);

        if (className.IsEmpty())
            pObjectDefinition->SetObject(NULL);
        else
        {
            // set the class name
            pObjectDefinition->SetClassName(className);

            // create a new object with the class name
            PSS_PlanFinObject* pObj = PSS_ObjectUtility::BuildObject(className);

            // set the field name
            pObj->SetObjectName(fieldName);

            // assign it
            pObjectDefinition->SetObject(pObj);
        }

        // add the field to the repository
        m_pSourceFieldRepository->AddField(pObjectDefinition);
    }

    // assign values to object definition
    pObjectDefinition->SetDescription(description);
    pObjectDefinition->SetHelpUserDescription(helpUser);
    pObjectDefinition->SetSorted(sorted);

    // go back to the previous element
    --i;

    // values should be added to history?
    if (m_LineArray.GetSize() >= i)
    {
        // iterate through the remaining and add them to the history
        for (; i < m_LineArray.GetSize(); ++i)
        {
            IFieldExport* pFieldExport = dynamic_cast<IFieldExport*>(m_LineArray.GetAt(i));

            if (!pFieldExport)
                continue;

            m_pSourceFieldRepository->AddFieldHistoryValue(fieldName, pFieldExport->m_Key);
        }

        PSS_HistoryField* pObjectHistory = m_pSourceFieldRepository->FindFieldHistory(fieldName);

        if (pObjectHistory)
            pObjectHistory->SetReadOnly(readOnly);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_FieldDefinitionDataFeed::DeleteLineArray()
{
    for (int i = 0; i < m_LineArray.GetSize(); ++i)
        if (m_LineArray.GetAt(i))
            delete m_LineArray.GetAt(i);

    m_LineArray.RemoveAll();
}
//---------------------------------------------------------------------------
