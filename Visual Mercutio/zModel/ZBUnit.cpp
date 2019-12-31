/****************************************************************************
 * ==> PSS_Unit ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a document unit                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "ZBUnit.h"

// processsoft
#include "zBaseLib\PSS_File.h"
#include "PSS_ProcessGraphModelDoc.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_Unit, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_Unit
//---------------------------------------------------------------------------
PSS_Unit::PSS_Unit(const CString& name, const CString& fileName) :
    CObject(),
    m_pUnitDoc(NULL),
    m_Name(name),
    m_FileName(fileName)
{}
//---------------------------------------------------------------------------
PSS_Unit::PSS_Unit(const PSS_Unit& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_Unit::~PSS_Unit()
{}
//---------------------------------------------------------------------------
PSS_Unit& PSS_Unit::operator = (const PSS_Unit& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
bool PSS_Unit::Create(const CString& name)
{
    m_Name = name;
    m_Key  = CreateUniqueKey();

    return !m_Key.IsEmpty();
}
//---------------------------------------------------------------------------
bool PSS_Unit::Create(const CString& name, const CString& fileName)
{
    m_Name     = name;
    m_FileName = fileName;
    m_Key      = CreateUniqueKey();

    return !m_Key.IsEmpty();
}
//---------------------------------------------------------------------------
CString PSS_Unit::CreateUniqueKey()
{
    GUID    guid;
    HRESULT result = ::CoCreateGuid(&guid);

    if (result == S_OK)
    {
        CString key;
        key.Format(_T("%d-%d"), guid.Data1, guid.Data2);
        return key;
    }

    return _T("");
}
//---------------------------------------------------------------------------
bool PSS_Unit::LoadUnit(PSS_ProcessModelDocTmpl* pDocTmpl)
{
    // check if the file exists
    PSS_File file(m_FileName);

    if (!file.Exist())
        return false;

    if (m_pUnitDoc)
        if (!UnloadUnit())
            return false;

    CDocument*                pDoc      = pDocTmpl->OpenDocumentFile(m_FileName, FALSE);
    PSS_ProcessGraphModelDoc* pModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc);

    if (pModelDoc)
    {
        m_pUnitDoc = pModelDoc;

        ZDProcessGraphModelMdl* pModel = pModelDoc->GetModel();

        // assign the name
        if (pModel)
            m_Name = pModel->GetModelName();
    }
    else
    if (pDoc)
    {
        pDoc->OnCloseDocument();
        delete pDoc;
    }

    return m_pUnitDoc;
}
//---------------------------------------------------------------------------
bool PSS_Unit::UnloadUnit()
{
    if (m_pUnitDoc)
    {
        m_pUnitDoc->OnCloseDocument();
        delete m_pUnitDoc;
        m_pUnitDoc = NULL;

        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_Unit::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        ar << m_Key;
        ar << m_Name;
        ar << m_FileName;
    }
    else
    {
        ar >> m_Key;
        ar >> m_Name;
        ar >> m_FileName;
    }
}
//---------------------------------------------------------------------------
