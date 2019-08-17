/****************************************************************************
 * ==> PSS_FLFDataFeed -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a class used to import additional information     *
 *               coming from FLF file                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_FLFDataFeed.h"

// processsoft
#include "ZBTokenizer.h"

//---------------------------------------------------------------------------
// PSS_FLFDataFeed
//---------------------------------------------------------------------------
PSS_FLFDataFeed::PSS_FLFDataFeed() :
    m_KeepOnlyFLF(FALSE)
{}
//---------------------------------------------------------------------------
PSS_FLFDataFeed::~PSS_FLFDataFeed()
{}
//---------------------------------------------------------------------------
BOOL PSS_FLFDataFeed::ProcessLine(const CString& line)
{
    ZBTokenizer tokenizer;

    // the received line is exactly the same as exported
    switch (GetSeparatorType())
    {
        case E_SS_Comma:      tokenizer.SetSeparator(',');  break;
        case E_SS_SemiColumn: tokenizer.SetSeparator(';');  break;
        default:              tokenizer.SetSeparator('\t'); break;
    }

    // get the key
    const CString key = tokenizer.GetFirstToken(line);

    // no key? End
    if (key.IsEmpty())
        return FALSE;

    // get the value
    const CString value = tokenizer.GetNextToken();

    if (!key.CompareNoCase(g_ExportProcessNameKey))
        m_ProcessName = value;
    else
    if (!key.CompareNoCase(g_ExportTemplateNameKey))
        m_FormName = value;
    else
    if (!key.CompareNoCase(g_ExportFolderNameKey))
        m_FolderName = value;
    else
    if (!key.CompareNoCase(g_ExportFileNameKey))
        m_FileName = value;
    else
    if (key.CompareNoCase(g_ExportProcessExchangeFileNameKey))
        m_ProcessExchangeFileName = value;
    else
    if (key.CompareNoCase(g_ExportKeepOnlyFLFKey))
        m_KeepOnlyFLF = std::atoi(value);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_FLFDataFeed::ImportAdditionalInfo()
{
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_FLFDataFeed::PreImport()
{
    return TRUE;
}
//---------------------------------------------------------------------------
