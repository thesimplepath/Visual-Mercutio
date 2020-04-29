/****************************************************************************
 * ==> PSS_DocumentExport --------------------------------------------------*
 ****************************************************************************
 * Description : Provides an interface to import and export document info   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_DocumentExport.h"

 // processsoft
#include "PSS_PLFNAutoNumbered.h"
#include "PSS_PLFNTwoStates.h"
#include "PSS_Document.h"
#include "PSS_DocumentData.h"
#include "PSS_MsgBox.h"

//---------------------------------------------------------------------------
// PSS_DocumentExport
//---------------------------------------------------------------------------
PSS_DocumentExport::PSS_DocumentExport(const CString&                fileName,
                                       PSS_Document*                 pDoc,
                                       BOOL                          generateHeader,
                                       ESynchronizationSeparatorType separatorType,
                                       const CString&                schema,
                                       int                           propagationMode,
                                       BOOL                          emptyWhenZero,
                                       PSS_StatusBar*                pStatusBar) :
    PSS_Export(fileName, generateHeader, separatorType, schema, propagationMode, emptyWhenZero, pStatusBar),
    m_pDoc(pDoc),
    m_ObjectCounter(0)
{}
//---------------------------------------------------------------------------
PSS_DocumentExport::PSS_DocumentExport(const PSS_DocumentExport& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_DocumentExport::~PSS_DocumentExport()
{}
//---------------------------------------------------------------------------
const PSS_DocumentExport& PSS_DocumentExport::operator = (const PSS_DocumentExport& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
CString PSS_DocumentExport::GetExportedLine(CObject* pObj)
{
    PSS_PlanFinObject* pPlanFinObj = dynamic_cast<PSS_PlanFinObject*>(pObj);
    PSS_Assert(pPlanFinObj);

    CString lineBuffer;

    switch (GetSeparatorType())
    {
        case E_SS_Comma:      lineBuffer.Format("%s,%s\r\n",         (const char*)pPlanFinObj->GetObjectName(), (const char*)pPlanFinObj->GetUnformattedObject()); break;
        case E_SS_SemiColumn: lineBuffer.Format("%s;%s\r\n",         (const char*)pPlanFinObj->GetObjectName(), (const char*)pPlanFinObj->GetUnformattedObject()); break;
        case E_SS_Quote:      lineBuffer.Format("\"%s\" \"%s\"\r\n", (const char*)pPlanFinObj->GetObjectName(), (const char*)pPlanFinObj->GetUnformattedObject()); break;
        default:              lineBuffer.Format("%s\t%s\r\n",        (const char*)pPlanFinObj->GetObjectName(), (const char*)pPlanFinObj->GetUnformattedObject()); break;
    }

    return lineBuffer;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentExport::IsExportedField(CObject* pObj) const
{
    PSS_PlanFinObject* pPlanFinObj = dynamic_cast<PSS_PlanFinObject*>(pObj);
    PSS_Assert(pPlanFinObj);
    
    // is the object exportable?
    if (!pPlanFinObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNAscii))        &&
        !pPlanFinObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNAutoNumbered)) &&
        !pPlanFinObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNTwoStates)))
        return FALSE;

    PSS_PLFNText* pText = dynamic_cast<PSS_PLFNText*>(pObj);

    if (pText && pText->GetIsStatic())
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentExport::ProcessLine(const CString& line)
{
    // the received line is exactly the same as the exported one
    CString srcLine = line;
    CString name;
    CString value;

    char* pCurrent = srcLine.GetBuffer(srcLine.GetLength() + 2);
    char* pNext;
    char  separatorChar;

    switch (GetSeparatorType())
    {
        case E_SS_Quote:
        {
            separatorChar = '"';

            // skip the first Quote char
            if (*pCurrent != '"')
                return FALSE;

            ++pCurrent;
            break;
        }

        case E_SS_Tab:        separatorChar = '\t'; break;
        case E_SS_Comma:      separatorChar = ',';  break;
        case E_SS_SemiColumn: separatorChar = ';';  break;
        default:              separatorChar = '\t'; break;
    }

    // extract the object name, locates the separator char 
    pNext = std::strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    // copy the name
    name = pCurrent;

    // set current to the next char after the next pointer
    pCurrent = ++pNext;

    // on quote skips the "
    if (GetSeparatorType() == E_SS_Quote)
    {
        // find the first quote char
        pNext = std::strchr(pCurrent, separatorChar);

        if (!pNext)
            return FALSE;

        pCurrent = ++pNext;

        // find the end quote char
        pNext = std::strchr(pCurrent, separatorChar);

        if (!pNext)
            return FALSE;

        // wWhere next is found, put end of string char
        *pNext = 0x00;
    }

    // extract the object value. It's the last field, just copy it
    value = pCurrent;

    if (!m_pDoc)
        return FALSE;

    const std::size_t docDataCount = m_pDoc->GetDocumentDataCount();

    // call the document to change the object value
    for (std::size_t i = 0; i < docDataCount; ++i)
        m_pDoc->GetDocumentDataAt(i)->AssignObjectValue(name, value, 0, GetPropagationMode(), GetEmptyWhenZero());

    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_DocumentExport::GetHeaderLine()
{
    switch (GetSeparatorType())
    {
        case E_SS_Automatic:
        case E_SS_Tab:        return "Nom\tValeur\r\n";
        case E_SS_Comma:      return "Nom,Valeur\r\n";
        case E_SS_SemiColumn: return "Nom;Valeur\r\n";
        case E_SS_Quote:      return "\"Nom\" \"Valeur\"\r\n";
        default:              break;
    }

    return "Nom\tValeur\r\n";
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentExport::Export()
{
    return PSS_Export::Export();
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentExport::Import()
{
    return PSS_Export::Import();
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentExport::ExportAdditionalInfo()
{
    if (!m_pDoc)
        return FALSE;

    if (m_pDoc->GetDocumentStamp().GetDocumentFileType() == PSS_Stamp::IE_FT_ProcessDocument)
    {
        WriteLine(BuildLine(g_ExportProcessNameKey, m_pDoc->GetDocumentStamp().GetTitle()));
        WriteLine(BuildLine(g_ExportTemplateNameKey, ""));
        WriteLine(BuildLine(g_ExportProcessExchangeFileNameKey, m_pDoc->GetDocumentStamp().GetKey1()));
    }
    else
    {
        WriteLine(BuildLine(g_ExportProcessNameKey, ""));
        WriteLine(BuildLine(g_ExportTemplateNameKey, m_pDoc->GetDocumentStamp().GetTitle()));
    }

    WriteLine(BuildLine(g_ExportFolderNameKey, m_pDoc->GetDocumentStamp().GetFolderName()));

    // if only keep FLF, do not export the file name
    if (m_pDoc->GetKeepOnlyFLF())
        WriteLine(BuildLine(g_ExportFileNameKey, ""));
    else
        WriteLine(BuildLine(g_ExportFileNameKey, m_pDoc->GetPathName()));

    WriteLine(BuildLine(g_ExportKeepOnlyFLFKey, m_pDoc->GetKeepOnlyFLF() ? "1" : "0"));

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentExport::ImportAdditionalInfo()
{
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentExport::PreImport()
{
    if (!m_pDoc)
        return FALSE;

    // save the current schema name to be able to restore it after import
    m_PreviousSchema = m_pDoc->GetCurrentSchema();

    // change the schema only if it is not the same as the current
    if (!GetSchemaName().IsEmpty() && m_PreviousSchema != GetSchemaName())
        m_pDoc->ChangeCurrentSchema(GetSchemaName(), TRUE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentExport::PostImport()
{
    if (!m_pDoc)
        return FALSE;

    // restore the previous schema name only if it was not the same as the current
    if (!GetSchemaName().IsEmpty() && m_PreviousSchema != GetSchemaName())
        m_pDoc->ChangeCurrentSchema(m_PreviousSchema, TRUE);

    // start the timer to clear color on field
    m_pDoc->StartCalcTimer();

    return TRUE;
}
//---------------------------------------------------------------------------
double PSS_DocumentExport::GetForecastedTotalObject() const
{
    return double(m_pDoc->GetObjectCount());
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentExport::DoExportLoop()
{
    if (!m_pDoc)
        return FALSE;

    // for each object, assign  the new matching font handle
    PSS_PlanFinObject* pObj;
    CString            line;
    double             count = 0;

    // initialize the object counter
    m_ObjectCounter = 1;

    const std::size_t docDataCount = m_pDoc->GetDocumentDataCount();

    for (std::size_t i = 0; i < docDataCount; ++i)
        if ((pObj = m_pDoc->GetDocumentDataAt(i)->GetHead()) != NULL)
            do
            {
                // is the object is exportable?
                if (IsExportedField(pObj))
                {
                    line = GetExportedLine(pObj);
                    WriteLine(line);
                }

                if (m_pStatusBar)
                    m_pStatusBar->SetCurrentPercentage(int((++count / double(m_pDoc->GetObjectCount())) * 100.0));

                ++m_ObjectCounter;
            }
            while ((pObj = m_pDoc->GetDocumentDataAt(i)->GetNext()) != NULL);

    return TRUE;
}
//---------------------------------------------------------------------------
