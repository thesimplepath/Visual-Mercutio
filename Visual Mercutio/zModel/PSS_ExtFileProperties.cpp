/****************************************************************************
 * ==> PSS_ExtFileProperties -----------------------------------------------*
 ****************************************************************************
 * Description : Provides external file properties                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ExtFileProperties.h"

// resources
#include "zModelRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

using namespace sfl;

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ExtFileProperties, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ExtFileProperties
//---------------------------------------------------------------------------
PSS_ExtFileProperties::PSS_ExtFileProperties() :
    CObject(),
    m_InsertionType(0),
    m_ActivationType(0)
{}
//---------------------------------------------------------------------------
PSS_ExtFileProperties::PSS_ExtFileProperties(const PSS_ExtFileProperties& other)
{
    m_FileTitle      = other.GetFileTitle();
    m_FileName       = other.GetFileName();
    m_InsertionType  = other.GetInsertionType();
    m_ActivationType = other.GetActivationType();
}
//---------------------------------------------------------------------------
PSS_ExtFileProperties::~PSS_ExtFileProperties()
{}
//---------------------------------------------------------------------------
PSS_ExtFileProperties& PSS_ExtFileProperties::operator = (const PSS_ExtFileProperties& other)
{
    SetFileTitle     (other.GetFileTitle());
    SetFileName      (other.GetFileName());
    SetInsertionType (other.GetInsertionType());
    SetActivationType(other.GetActivationType());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtFileProperties::operator == (const PSS_ExtFileProperties& other) const
{
    return (GetFileTitle()      == other.GetFileTitle()     &&
            GetFileName()       == other.GetFileName()      &&
            GetInsertionType()  == other.GetInsertionType() &&
            GetActivationType() == other.GetActivationType());
}
//---------------------------------------------------------------------------
void PSS_ExtFileProperties::Merge(PSS_ExtFileProperties* pProp, DWORD changeFlags)
{
    if (pProp)
    {
        if (changeFlags & IE_CT_File_Title)
            m_FileTitle = pProp->GetFileTitle();

        if (changeFlags & IE_CT_File_Name)
            m_FileName = pProp->GetFileName();

        if (changeFlags & IE_CT_Insertion_Type)
            m_InsertionType = pProp->GetInsertionType();

        if (changeFlags & IE_CT_Activation_Type)
            m_ActivationType = pProp->GetActivationType();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_ExtFileProperties::IsEqual(PSS_ExtFileProperties* pProp)
{
    if (pProp)
        return (*this == *pProp);

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_ExtFileProperties::SetFileTitle(LPCTSTR pValue)
{
    if (pValue)
        m_FileTitle = pValue;
    else
    {
        TRACE0(_T("Z -> Invalid Task List pointer!\n"));
        ASSERT(FALSE);
    }
}
//---------------------------------------------------------------------------
void PSS_ExtFileProperties::SetFileName(LPCTSTR pValue)
{
    if (pValue)
        m_FileName = pValue;
    else
    {
        TRACE0(_T("Z -> Invalid Decision List pointer!\n"));
        ASSERT(FALSE);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_ExtFileProperties::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case M_File_Title_ID:
        case M_File_Name_ID:       throw new CODPropertyConversionException();
        case M_Insertion_Type_ID:  value = m_InsertionType;  break;
        case M_Activation_Type_ID: value = m_ActivationType; break;
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtFileProperties::GetValue(const int propId, UINT& value) const
{
    switch (propId)
    {
        case M_File_Title_ID:
        case M_File_Name_ID:       throw new CODPropertyConversionException();
        case M_Insertion_Type_ID:  value = UINT(m_InsertionType);  break;
        case M_Activation_Type_ID: value = UINT(m_ActivationType); break;
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtFileProperties::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case M_File_Title_ID:
        case M_File_Name_ID:
        case M_Insertion_Type_ID:
        case M_Activation_Type_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtFileProperties::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_File_Title_ID:
        case M_File_Name_ID:
        case M_Insertion_Type_ID:
        case M_Activation_Type_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtFileProperties::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_File_Title_ID: value = m_FileTitle; break;
        case M_File_Name_ID:  value = m_FileName;  break;
        default:              throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtFileProperties::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_File_Title_ID:
        case M_File_Name_ID:       throw new CODPropertyConversionException();
        case M_Insertion_Type_ID:  m_InsertionType  = value; break;
        case M_Activation_Type_ID: m_ActivationType = value; break;
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtFileProperties::SetValue(const int propId, const UINT value)
{
    switch (propId)
    {
        case M_File_Title_ID:
        case M_File_Name_ID:       throw new CODPropertyConversionException();
        case M_Insertion_Type_ID:  m_InsertionType  = int(value); break;
        case M_Activation_Type_ID: m_ActivationType = int(value); break;
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtFileProperties::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case M_File_Title_ID:
        case M_File_Name_ID:
        case M_Insertion_Type_ID:
        case M_Activation_Type_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtFileProperties::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_File_Title_ID:
        case M_File_Name_ID:
        case M_Insertion_Type_ID:
        case M_Activation_Type_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtFileProperties::SetValue(const int propId, LPCTSTR pValue)
{
    if (!pValue)
        return FALSE;

    switch (propId)
    {
        case M_File_Title_ID: m_FileTitle = pValue; break;
        case M_File_Name_ID:  m_FileName  = pValue; break;
        default:              throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ExtFileProperties::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        ar << m_FileTitle;
        ar << m_FileName;
        ar << m_InsertionType;
        ar << m_ActivationType;
    }
    else
    {
        ar >> m_FileTitle;
        ar >> m_FileName;
        ar >> m_InsertionType;
        ar >> m_ActivationType;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ExtFileProperties::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ExtFileProperties::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);

        dc << _T("Name = ")            << m_FileTitle      << _T("\n");
        dc << _T("Deliverables = ")    << m_FileName       << _T("\n");
        dc << _T("Insertion Type = ")  << m_InsertionType  << _T("\n");
        dc << _T("Activation Type = ") << m_ActivationType << _T("\n");
    }
#endif
//---------------------------------------------------------------------------
void PSS_ExtFileProperties::SetFileTitleEx(const CString& value)
{
    SetFileTitle(value);
}
//---------------------------------------------------------------------------
void PSS_ExtFileProperties::SetFileNameEx(const CString& value)
{
    SetFileName(value);
}
//---------------------------------------------------------------------------
