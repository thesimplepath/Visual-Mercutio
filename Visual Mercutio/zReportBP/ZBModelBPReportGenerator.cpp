// ZBModelBPReportGenerator.cpp: implementation of the ZBModelBPReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBModelBPReportGenerator.h"

#include "zModel\ProcGraphModelDoc.h"
#include "zModelBP\ProcGraphModelMdlBP.h"
#include "zReport\ZDGridDoc.h"

#include "zBaseLib\ZAGlobal.h"

#include "zReport\zReportRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 7 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZBModelBPReportGenerator, ZBGenericGridReportGenerator, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBModelBPReportGenerator::ZBModelBPReportGenerator( ZDGridDocument*                pDoc        /*= NULL*/,
                                                    ZDProcessGraphModelMdlBP*    pModel        /*= NULL*/,
                                                    ZDProcessGraphModelDoc*        pSourceDoc    /*= NULL*/ )
    : ZBGenericGridReportGenerator    ( pDoc ),
      m_pModel                        ( pModel ),
      m_pSourceDoc                    ( pSourceDoc ),
      m_InChargeOfClosingFile        ( false )
{
    // If a source document, assigns its path name
    if ( m_pSourceDoc )
    {
        m_Filename = m_pSourceDoc->GetPathName();
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
                                           ZDProcessGraphModelDoc*        pSourceDoc )
{
    m_pDoc            = pDoc;
    m_pModel        = pModel;
    m_pSourceDoc    = pSourceDoc;

    // If a source document, assigns its path name
    if ( m_pSourceDoc )
    {
        m_Filename = m_pSourceDoc->GetPathName();
    }

    // Fill the tab name array
    FillTabArray();
}

bool ZBModelBPReportGenerator::ReportDataMustBeReloaded() const
{
    if ( !m_Filename.IsEmpty() )
    {
        SYSTEMTIME tm;

        if ( ZFile::GetLastWriteTime( m_Filename, tm ) )
        {
            return ( ZBDate( tm ) > m_LastUpdateDateTime ) ? true : false;
        }
    }

    return ZBGenericGridReportGenerator::ReportDataMustBeReloaded();
}

void ZBModelBPReportGenerator::OnPostRead( CArchive& ar )
{
    if ( m_pSourceDoc == NULL && !m_Filename.IsEmpty() )
    {
        m_pSourceDoc = new ZDProcessGraphModelDoc();

        // If the document is valid, assign the right model pointer
        if ( m_pSourceDoc &&
             m_pSourceDoc->ReadFromFile( m_Filename ) &&
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
    if ( !m_Filename.IsEmpty() )
    {
        // Saves the last update date/time, this is set to the 
        // filename last write date/time
        SYSTEMTIME tm;

        if ( ZFile::GetLastWriteTime( m_Filename, tm ) )
        {
            m_LastUpdateDateTime = ZBDate( tm );
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

    if ( ar.IsStoring() )
    {
    }
    else
    {
    }
}
