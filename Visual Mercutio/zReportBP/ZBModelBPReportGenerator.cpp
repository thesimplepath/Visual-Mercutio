// ZBModelBPReportGenerator.cpp: implementation of the ZBModelBPReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBModelBPReportGenerator.h"

#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModelBP\PSS_ProcessGraphModelMdlBP.h"
#include "zReport\PSS_GridDocument.h"

#include "zBaseLib\PSS_Global.h"

#include "zReport\zReportRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 7 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(ZBModelBPReportGenerator, PSS_GenericGridReportGenerator, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBModelBPReportGenerator::ZBModelBPReportGenerator(PSS_GridDocument*                pDoc        /*= NULL*/,
                                                   PSS_ProcessGraphModelMdlBP*    pModel        /*= NULL*/,
                                                   PSS_ProcessGraphModelDoc*        pSourceDoc    /*= NULL*/)
    : PSS_GenericGridReportGenerator(pDoc),
    m_pModel(pModel),
    m_pSourceDoc(pSourceDoc),
    m_InChargeOfClosingFile(false)
{
    // If a source document, assigns its path name
    if (m_pSourceDoc)
    {
        m_FileName = m_pSourceDoc->GetPathName();
    }

    // Fill the tab name array
    FillTabArray();
}

ZBModelBPReportGenerator::~ZBModelBPReportGenerator()
{
    if (m_InChargeOfClosingFile && m_pSourceDoc)
    {
        delete m_pSourceDoc;
    }

    m_pSourceDoc = NULL;
    m_pModel = NULL;
}

void ZBModelBPReportGenerator::Initialize(PSS_GridDocument*                pDoc,
                                          PSS_ProcessGraphModelMdlBP*    pModel,
                                          PSS_ProcessGraphModelDoc*        pSourceDoc)
{
    m_pDoc = pDoc;
    m_pModel = pModel;
    m_pSourceDoc = pSourceDoc;

    // If a source document, assigns its path name
    if (m_pSourceDoc)
    {
        m_FileName = m_pSourceDoc->GetPathName();
    }

    // Fill the tab name array
    FillTabArray();
}

bool ZBModelBPReportGenerator::ReportDataMustBeReloaded() const
{
    if (!m_FileName.IsEmpty())
    {
        SYSTEMTIME tm;

        if (PSS_File::GetLastWriteTime(m_FileName, tm))
        {
            return (PSS_Date(tm) > m_LastUpdateDateTime) ? true : false;
        }
    }

    return PSS_GenericGridReportGenerator::ReportDataMustBeReloaded();
}

void ZBModelBPReportGenerator::OnPostRead(CArchive& ar)
{
    if (m_pSourceDoc == NULL && !m_FileName.IsEmpty())
    {
        m_pSourceDoc = new PSS_ProcessGraphModelDoc();

        // If the document is valid, assign the right model pointer
        if (m_pSourceDoc &&
            m_pSourceDoc->ReadFromFile(m_FileName) &&
            m_pSourceDoc->GetModel() &&
            ISA(m_pSourceDoc->GetModel(), PSS_ProcessGraphModelMdlBP))
        {
            m_pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pSourceDoc->GetModel());
            m_InChargeOfClosingFile = true;
        }
    }
}

void ZBModelBPReportGenerator::OnPostDataFilled(size_t Index)
{
    if (!m_FileName.IsEmpty())
    {
        // Saves the last update date/time, this is set to the 
        // file name last write date/time
        SYSTEMTIME tm;

        if (PSS_File::GetLastWriteTime(m_FileName, tm))
        {
            m_LastUpdateDateTime = PSS_Date(tm);
        }
    }
    else
    {
        PSS_GenericGridReportGenerator::OnPostDataFilled(Index);
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBModelBPReportGenerator diagnostics

#ifdef _DEBUG
void ZBModelBPReportGenerator::AssertValid() const
{
    PSS_GenericGridReportGenerator::AssertValid();
}

void ZBModelBPReportGenerator::Dump(CDumpContext& dc) const
{
    PSS_GenericGridReportGenerator::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBModelBPReportGenerator serialization

void ZBModelBPReportGenerator::Serialize(CArchive& ar)
{
    PSS_GenericGridReportGenerator::Serialize(ar);

    // Serialize the tab name array
    m_TabNameArray.Serialize(ar);
}
