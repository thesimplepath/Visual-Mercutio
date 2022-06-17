/****************************************************************************
 * ==> PSS_StringFormat ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a string format                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_StringFormat.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_StringFormat, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_StringFormat
//---------------------------------------------------------------------------
PSS_StringFormat::PSS_StringFormat(IEFormatType   formatType,
                                   bool           useSeparator,
                                   int            decimalPlace,
                                   const CString& currency,
                                   LCID           lcid) :
    CObject(),
    m_FormatType(formatType),
    m_Currency(currency),
    m_LCID(lcid),
    m_DecimalPlace(decimalPlace),
    m_UseSeparator(useSeparator)
{
    if (!m_LCID)
        m_LCID = ::GetUserDefaultLCID();
}
//---------------------------------------------------------------------------
PSS_StringFormat::PSS_StringFormat(const CString& customFormat, LCID lcid) :
    CObject(),
    m_FormatType(IEFormatType::IE_FT_Custom),
    m_CustomFormat(customFormat),
    m_LCID(lcid),
    m_DecimalPlace(-1),
    m_UseSeparator(false)
{
    if (!m_LCID)
        m_LCID = ::GetUserDefaultLCID();
}
//---------------------------------------------------------------------------
PSS_StringFormat::PSS_StringFormat(const PSS_StringFormat& other) :
    CObject(),
    m_FormatType(IEFormatType::IE_FT_General),
    m_LCID(0),
    m_DecimalPlace(-1),
    m_UseSeparator(false)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_StringFormat::~PSS_StringFormat()
{
    // NOTE the fully qualified name is required to avoid to call a pure virtual function on parent
    PSS_StringFormat::Release();
}
//---------------------------------------------------------------------------
const PSS_StringFormat& PSS_StringFormat::operator = (const PSS_StringFormat& other)
{
    m_FormatType   = other.m_FormatType;
    m_Currency     = other.m_Currency;
    m_CustomFormat = other.m_CustomFormat;
    m_LCID         = other.m_LCID;
    m_DecimalPlace = other.m_DecimalPlace;
    m_UseSeparator = other.m_UseSeparator;

    return *this;
}
//---------------------------------------------------------------------------
void PSS_StringFormat::Release()
{
    m_Currency.Empty();
    m_CustomFormat.Empty();
}
//---------------------------------------------------------------------------
void PSS_StringFormat::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements
        ar << int(m_FormatType);
        ar << int(m_UseSeparator);
        ar << m_DecimalPlace;
        ar << m_Currency;
        ar << m_CustomFormat;
        ar << m_LCID;
    }
    else
    {
        // read the elements
        int value;
        ar >> value;
        m_FormatType = IEFormatType(value);

        ar >> value;
        m_UseSeparator = bool(value);

        ar >> m_DecimalPlace;
        ar >> m_Currency;
        ar >> m_CustomFormat;
        ar >> m_LCID;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_StringFormat::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_StringFormat::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
