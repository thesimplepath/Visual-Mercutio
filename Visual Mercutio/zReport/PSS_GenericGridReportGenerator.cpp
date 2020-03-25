/****************************************************************************
 * ==> PSS_GenericGridReportGenerator --------------------------------------*
 ****************************************************************************
 * Description : Provides a generic report generator                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GenericGridReportGenerator.h"

// processsoft
#include "ZDGridDoc.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_GenericGridReportGenerator, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_GenericGridReportGenerator
//---------------------------------------------------------------------------
PSS_GenericGridReportGenerator::PSS_GenericGridReportGenerator(ZDGridDocument* pDoc) :
    CObject(),
    ZIGridReportGenerator(),
    m_pDoc(pDoc),
    m_TypeID(-1)
{}
//---------------------------------------------------------------------------
PSS_GenericGridReportGenerator::~PSS_GenericGridReportGenerator()
{}
//---------------------------------------------------------------------------
bool PSS_GenericGridReportGenerator::Initialize()
{
    return true;
}
//---------------------------------------------------------------------------
CDocTemplate* PSS_GenericGridReportGenerator::GetDocTemplate() const
{
    return (m_pDoc ? m_pDoc->GetDocTemplate() : NULL);
}
//---------------------------------------------------------------------------
void PSS_GenericGridReportGenerator::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the file name
        ar << m_FileName;

        // write the report type
        ar << m_TypeID;

        // write the last update date
        ar << m_LastUpdateDateTime;

        OnPostWrite(ar);
    }
    else
    {
        // read the file name
        ar >> m_FileName;

        // read the report type
        ar >> m_TypeID;

        // read the last update date
        ar >> m_LastUpdateDateTime;

        OnPostRead(ar);
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GenericGridReportGenerator::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GenericGridReportGenerator::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_GenericGridReportGenerator::OnPreDataFilled(std::size_t index)
{}
//---------------------------------------------------------------------------
void PSS_GenericGridReportGenerator::OnPostDataFilled(size_t Index)
{
    // save the last update date/time
    m_LastUpdateDateTime.SetToday();
}
//---------------------------------------------------------------------------
void PSS_GenericGridReportGenerator::OnPostRead(CArchive& ar)
{}
//---------------------------------------------------------------------------
void PSS_GenericGridReportGenerator::OnPostWrite(CArchive& ar)
{}
//---------------------------------------------------------------------------
