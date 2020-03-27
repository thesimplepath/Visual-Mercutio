/****************************************************************************
 * ==> PSS_ModelBPReportGenerator ------------------------------------------*
 ****************************************************************************
 * Description : Provides a banking process model report generator          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ModelBPReportGenerator.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModelBP\PSS_ProcessGraphModelMdlBP.h"
#include "zReport\PSS_GridDocument.h"

// resources
#include "zReport\zReportRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ModelBPReportGenerator, PSS_GenericGridReportGenerator, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ModelBPReportGenerator
//---------------------------------------------------------------------------
PSS_ModelBPReportGenerator::PSS_ModelBPReportGenerator(PSS_GridDocument*           pDoc,
                                                       PSS_ProcessGraphModelMdlBP* pModel,
                                                       PSS_ProcessGraphModelDoc*   pSourceDoc) :
    PSS_GenericGridReportGenerator(pDoc),
    m_pSourceDoc(pSourceDoc),
    m_pModel(pModel),
    m_InChargeOfClosingFile(false)
{
    // if a source document, assign its path name
    if (m_pSourceDoc)
        m_FileName = m_pSourceDoc->GetPathName();

    // fill the tab name array
    FillTabArray();
}
//---------------------------------------------------------------------------
PSS_ModelBPReportGenerator::~PSS_ModelBPReportGenerator()
{
    if (m_InChargeOfClosingFile && m_pSourceDoc)
        delete m_pSourceDoc;

    m_pSourceDoc = NULL;
    m_pModel     = NULL;
}
//---------------------------------------------------------------------------
void PSS_ModelBPReportGenerator::Initialize(PSS_GridDocument*           pDoc,
                                            PSS_ProcessGraphModelMdlBP* pModel,
                                            PSS_ProcessGraphModelDoc*   pSourceDoc)
{
    m_pDoc       = pDoc;
    m_pSourceDoc = pSourceDoc;
    m_pModel     = pModel;

    // if a source document, assign its path name
    if (m_pSourceDoc)
        m_FileName = m_pSourceDoc->GetPathName();

    // fill the tab name array
    FillTabArray();
}
//---------------------------------------------------------------------------
bool PSS_ModelBPReportGenerator::ReportDataMustBeReloaded() const
{
    if (!m_FileName.IsEmpty())
    {
        ::SYSTEMTIME tm;

        if (PSS_File::GetLastWriteTime(m_FileName, tm))
            return (PSS_Date(tm) > m_LastUpdateDateTime) ? true : false;
    }

    return PSS_GenericGridReportGenerator::ReportDataMustBeReloaded();
}
//---------------------------------------------------------------------------
void PSS_ModelBPReportGenerator::Serialize(CArchive& ar)
{
    PSS_GenericGridReportGenerator::Serialize(ar);

    // serialize the tab name array
    m_TabNameArray.Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ModelBPReportGenerator::AssertValid() const
    {
        PSS_GenericGridReportGenerator::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ModelBPReportGenerator::Dump(CDumpContext& dc) const
    {
        PSS_GenericGridReportGenerator::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_ModelBPReportGenerator::OnPostRead(CArchive& ar)
{
    if (!m_pSourceDoc && !m_FileName.IsEmpty())
    {
        m_pSourceDoc = new PSS_ProcessGraphModelDoc();

        // if the document is valid, assign the model
        if (m_pSourceDoc && m_pSourceDoc->ReadFromFile(m_FileName))
        {
            PSS_ProcessGraphModelMdlBP* pGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pSourceDoc->GetModel());

            if (pGraphModel)
            {
                m_pModel                = pGraphModel;
                m_InChargeOfClosingFile = true;
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ModelBPReportGenerator::OnPostWrite(CArchive& ar)
{}
//---------------------------------------------------------------------------
void PSS_ModelBPReportGenerator::OnPostDataFilled(std::size_t index)
{
    if (!m_FileName.IsEmpty())
    {
        // save the last update date/time, this is set to the file name last write date/time
        ::SYSTEMTIME tm;

        if (PSS_File::GetLastWriteTime(m_FileName, tm))
            m_LastUpdateDateTime = PSS_Date(tm);
    }
    else
        PSS_GenericGridReportGenerator::OnPostDataFilled(index);
}
//---------------------------------------------------------------------------
