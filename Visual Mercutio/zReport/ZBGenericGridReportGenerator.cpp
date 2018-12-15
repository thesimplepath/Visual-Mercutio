// ZBGenericGridReportGenerator.cpp: implementation of the ZBGenericGridReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBGenericGridReportGenerator.h"

#include "ZDGridDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 10 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZBGenericGridReportGenerator, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBGenericGridReportGenerator::ZBGenericGridReportGenerator( ZDGridDocument* pDoc /*= NULL*/ )
    : m_pDoc    ( pDoc ),
      m_TypeID    ( -1 )
{
}

ZBGenericGridReportGenerator::~ZBGenericGridReportGenerator()
{
}

CDocTemplate* ZBGenericGridReportGenerator::GetDocTemplate() const
{
    return ( m_pDoc ) ? m_pDoc->GetDocTemplate() : NULL;
}

void ZBGenericGridReportGenerator::OnPostDataFilled( size_t Index )
{
    // Saves the last update date/time
    m_LastUpdateDateTime.SetToday();
}

/////////////////////////////////////////////////////////////////////////////
// ZBGenericGridReportGenerator diagnostics

#ifdef _DEBUG
void ZBGenericGridReportGenerator::AssertValid() const
{
    CObject::AssertValid();
}

void ZBGenericGridReportGenerator::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBGenericGridReportGenerator serialization

void ZBGenericGridReportGenerator::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        // Write the filename
        ar << m_Filename;

        // Write the report type
        ar << m_TypeID;

        // Write the last update date
        ar << m_LastUpdateDateTime;

        // Call-back
        OnPostWrite( ar );
    }
    else
    {
        // Read the filename
        ar >> m_Filename;

        // Read the report type
        ar >> m_TypeID;

        // Read the last update date
        ar >> m_LastUpdateDateTime;

        // Call-back
        OnPostRead( ar );
    }
}
