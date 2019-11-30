// ZBModelBPReportGenerator.cpp: implementation of the ZBModelBPReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBModelBPReportGenerator.h"

#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModelBP\ProcGraphModelMdlBP.h"
#include "zReport\ZDGridDoc.h"

#include "zBaseLib\PSS_Global.h"

#include "zReport\zReportRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 7 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(ZBModelBPReportGenerator, ZBGenericGridReportGenerator, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBModelBPReportGenerator::ZBModelBPReportGenerator( ZDGridDocument*                pDoc        /*= NULL*/,
                                                    ZDProcessGraphModelMdlBP*    pModel        /*= NULL*/,
                                                   PSS_ProcessGraphModelDoc*        pSourceDoc    /*= NULL*/ )
    : ZBGenericGridReportGenerator    ( pDoc ),
      m_pModel                        ( pModel ),
      m_pSourceDoc                    ( pSourceDoc ),
      m_InChargeOfClosingFile        ( false )
{
    // If a source document, assigns its path name
    if ( m_pSourceDoc )
    {
        m_FileName = m_pSourceDoc->GetPathName();
    }

    // Fill the tab name array
    FillTabArray();
}

ZBModelBPReportGenerator::~ZBModelBPReportGenerator()
{
    if ( m_InChargeOfClosingFile && m_pSourceDoc )
    {
        delete m_pSourceDoc;
    }

    m_pSourceDoc    = NULL;
    m_pModel        = NULL;
}

void ZBModelBPReportGenerator::Initialize( ZDGridDocument*                pDoc,
                                           ZDProcessGraphModelMdlBP*    pModel,
                                          PSS_ProcessGraphModelDoc*        pSourceDoc )
{
    m_pDoc            = pDoc;
    m_pModel        = pModel;
    m_pSourceDoc    = pSourceDoc;

    // If a source document, assigns its path name
    if ( m_pSourceDoc )
    {
        m_FileName = m_pSourceDoc->GetPathName();
    }

    // Fill the tab name array
    FillTabArray();
}

bool ZBModelBPReportGenerator::ReportDataMustBeReloaded() const
{
    if ( !m_FileName.IsEmpty() )
    {
        SYSTEMTIME tm;

        if (PSS_File::GetLastWriteTime( m_FileName, tm ) )
        {
            return (PSS_Date( tm ) > m_LastUpdateDateTime ) ? true : false;
        }
    }

    return ZBGenericGridReportGenerator::ReportDataMustBeReloaded();
}

void ZBModelBPReportGenerator::OnPostRead( CArchive& ar )
{
    if ( m_pSourceDoc == NULL && !m_FileName.IsEmpty() )
    {
        m_pSourceDoc = new PSS_ProcessGraphModelDoc();

        // If the document is valid, assign the right model pointer
        if ( m_pSourceDoc &&
             m_pSourceDoc->ReadFromFile( m_FileName ) &&
             m_pSourceDoc->GetModel() &&
             ISA( m_pSourceDoc->GetModel(), ZDProcessGraphModelMdlBP ) )
        {
            m_pModel = dynamic_cast<ZDProcessGraphModelMdlBP*>( m_pSourceDoc->GetModel() );
            m_InChargeOfClosingFile = true;
        }
    }
}

void ZBModelBPReportGenerator::OnPostDataFilled( size_t Index )
{
    if ( !m_FileName.IsEmpty() )
    {
        // Saves the last update date/time, this is set to the 
        // file name last write date/time
        SYSTEMTIME tm;

        if (PSS_File::GetLastWriteTime( m_FileName, tm ) )
        {
            m_LastUpdateDateTime = PSS_Date( tm );
        }
    }
    else
    {
        ZBGenericGridReportGenerator::OnPostDataFilled( Index );
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBModelBPReportGenerator diagnostics

#ifdef _DEBUG
void ZBModelBPReportGenerator::AssertValid() const
{
    ZBGenericGridReportGenerator::AssertValid();
}

void ZBModelBPReportGenerator::Dump( CDumpContext& dc ) const
{
    ZBGenericGridReportGenerator::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBModelBPReportGenerator serialization

void ZBModelBPReportGenerator::Serialize( CArchive& ar )
{
    ZBGenericGridReportGenerator::Serialize( ar );

    // Serialize the tab name array
    m_TabNameArray.Serialize( ar );
}
