/****************************************************************************
 * ==> PSS_TemplateFile ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a template file                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_TemplateFile.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_TemplateFile, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_TemplateFile
//---------------------------------------------------------------------------
PSS_TemplateFile::PSS_TemplateFile(const CString& fileName) :
    CObject(),
    m_Persistent(FALSE)
{
    Create(fileName);
}
//---------------------------------------------------------------------------
PSS_TemplateFile::PSS_TemplateFile(const PSS_TemplateFile& other) :
    CObject(),
    m_Persistent(FALSE)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_TemplateFile::~PSS_TemplateFile()
{}
//---------------------------------------------------------------------------
const PSS_TemplateFile& PSS_TemplateFile::operator = (const PSS_TemplateFile& other)
{
    m_Stamp      = other.m_Stamp;
    m_FileName   = other.m_FileName;
    m_Persistent = other.m_Persistent;

    return *this;
}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_TemplateFile& templateFile)
{
    ar >> templateFile.m_FileName;
    ar >> templateFile.m_Stamp;

    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_TemplateFile& templateFile)
{
    ar << templateFile.m_FileName;
    ar << templateFile.m_Stamp;

    return ar;
}
//---------------------------------------------------------------------------
BOOL PSS_TemplateFile::Create(const CString& fileName)
{
    // save the file name
    m_FileName = fileName;

    if (!m_Stamp.ReadFromFile(m_FileName))
        return FALSE;

    return m_Persistent = (m_Stamp.GetInternalVersion() != -1 && m_Stamp.GetFileType() == PSS_Stamp::IEFileTypeDefinition::IE_FD_TemplateType);
}
//---------------------------------------------------------------------------
PSS_TemplateFile* PSS_TemplateFile::Clone()
{
    std::unique_ptr< PSS_TemplateFile> pTemplateFile(new PSS_TemplateFile(*this));
    return pTemplateFile.release();
}
//---------------------------------------------------------------------------
void PSS_TemplateFile::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
        // write the elements
        ar << *this;
    else
        // read the elements
        ar >> *this;
}
//---------------------------------------------------------------------------
