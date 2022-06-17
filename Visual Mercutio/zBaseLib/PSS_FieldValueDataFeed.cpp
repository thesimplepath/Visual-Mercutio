/****************************************************************************
 * ==> PSS_FieldValueDataFeed ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a data feed for field values only                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_FieldValueDataFeed.h"

// processsoft
#include "PSS_Tokenizer.h"
#include "PSS_ObjectUtility.h"

//---------------------------------------------------------------------------
// PSS_FieldValueDataFeed
//---------------------------------------------------------------------------
PSS_FieldValueDataFeed::PSS_FieldValueDataFeed(const CString&                fileName,
                                               PSS_FieldRepository*          pFieldRepository,
                                               PSS_FieldObjectDefinition*    pObjectDefinition,
                                               BOOL                          generateHeader,
                                               ESynchronizationSeparatorType separatorType,
                                               const CString&                schema,
                                               int                           propagationMode,
                                               BOOL                          emptyWhenZero,
                                               PSS_StatusBar*                pStatusBar) :
    PSS_Export(fileName, generateHeader, separatorType, schema, propagationMode, emptyWhenZero, pStatusBar),
    m_pValueArray(NULL),
    m_pObjectDefinition(pObjectDefinition),
    m_pSourceFieldRepository(pFieldRepository)
{}
//---------------------------------------------------------------------------
PSS_FieldValueDataFeed::PSS_FieldValueDataFeed(const CString&                fileName,
                                               CStringArray*                 pValueArray,
                                               BOOL                          generateHeader,
                                               ESynchronizationSeparatorType separatorType,
                                               const CString&                schema,
                                               int                           propagationMode,
                                               BOOL                          emptyWhenZero,
                                               PSS_StatusBar*                pStatusBar) :
    PSS_Export(fileName, generateHeader, separatorType, schema, propagationMode, emptyWhenZero, pStatusBar),
    m_pValueArray(pValueArray),
    m_pObjectDefinition(NULL),
    m_pSourceFieldRepository(NULL)
{}
//---------------------------------------------------------------------------
PSS_FieldValueDataFeed::PSS_FieldValueDataFeed(const PSS_FieldValueDataFeed& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_FieldValueDataFeed::~PSS_FieldValueDataFeed()
{}
//---------------------------------------------------------------------------
const PSS_FieldValueDataFeed& PSS_FieldValueDataFeed::operator = (const PSS_FieldValueDataFeed& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_FieldValueDataFeed::ProcessLine(const CString& line)
{
    // if no value array, do nothing
    if (!m_pValueArray)
        return FALSE;

    // the received line is a history value
    m_pValueArray->Add(line);
    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_FieldValueDataFeed::GetExportedLine(CObject* pObj) const
{
    PSS_FieldObjectDefinition* pObjectDefinition = dynamic_cast<PSS_FieldObjectDefinition*>(pObj);

    if (!pObjectDefinition || !m_pSourceFieldRepository)
        return "";

    PSS_HistoryField* pObjectHistory = m_pSourceFieldRepository->FindFieldHistory(pObjectDefinition->GetFieldName());
    PSS_Tokenizer     tokenizer;

    switch (GetSeparatorType())
    {
        case ESynchronizationSeparatorType::E_SS_Comma:     tokenizer.SetSeparator(',');  break;
        case ESynchronizationSeparatorType::E_SS_Semicolon: tokenizer.SetSeparator(';');  break;
        default:                                            tokenizer.SetSeparator('\t'); break;
    }

    const std::size_t objectCount = pObjectHistory->GetCount();
          CString     line;

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
CString PSS_FieldValueDataFeed::GetHeaderLine() const
{
    return "";
}
//---------------------------------------------------------------------------
double PSS_FieldValueDataFeed::GetForecastedTotalObject() const
{
    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_FieldValueDataFeed::DoExportLoop()
{
    // if no object to export, do nothing
    if (!m_pObjectDefinition || !m_pSourceFieldRepository)
        return FALSE;

    // only one object to export
    const CString line = GetExportedLine(m_pObjectDefinition);
    WriteLine(line);
    return TRUE;
}
//---------------------------------------------------------------------------
