/****************************************************************************
 * ==> PSS_PrestationsPropertiesBP -----------------------------------------*
 ****************************************************************************
 * Description : Provides the prestations properties for banking process    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PrestationsPropertiesBP.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_Prestation, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_Prestation
//---------------------------------------------------------------------------
PSS_Prestation::PSS_Prestation() :
    CObject(),
    m_PercentageActivity(0.0f)
{}
//---------------------------------------------------------------------------
PSS_Prestation::PSS_Prestation(const PSS_Prestation& other)
{
    m_Name = other.GetName();
    m_GUID = other.GetGUID();

    other.GetValue(M_Prestation_Percentage, m_PercentageActivity);
}
//---------------------------------------------------------------------------
PSS_Prestation::~PSS_Prestation()
{}
//---------------------------------------------------------------------------
CString PSS_Prestation::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void PSS_Prestation::SetName(LPCTSTR pValue)
{
    if (pValue)
        m_Name = pValue;
    else
    {
        TRACE0("PSS_Prestation - Invalid name!\n");
        ASSERT(FALSE);
    }
}
//---------------------------------------------------------------------------
CString PSS_Prestation::GetGUID() const
{
    return m_GUID;
}
//---------------------------------------------------------------------------
void PSS_Prestation::SetGUID(LPCTSTR pValue)
{
    if (pValue)
        m_GUID = pValue;
    else
    {
        TRACE0("PSS_Prestation - Invalid GUID!\n");
        ASSERT(FALSE);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_Prestation::GetValue(int propID, float &value) const
{
    switch (propID)
    {
        case M_Prestation_Percentage: value = m_PercentageActivity; return TRUE;
        default:                                                    return FALSE;
    }
}
//---------------------------------------------------------------------------
void PSS_Prestation::SetValue(int propID, float value)
{
    switch (propID)
    {
        case M_Prestation_Percentage: m_PercentageActivity = value; break;
        default:                                                    break;
    }
}
//---------------------------------------------------------------------------
void PSS_Prestation::Serialize(CArchive& ar)
{
    CObject::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE("PSS_Prestation::Serialize - Start save\n");

        PUT_SCHEMA(ar, PSS_Prestation);

        ar << m_Name;
        ar << m_GUID;
        ar << m_PercentageActivity;

        TRACE("PSS_Prestation::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_Prestation::Serialize - Start read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);

        ar >> m_Name;
        ar >> m_GUID;
        ar >> m_PercentageActivity;

        TRACE("PSS_Prestation::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
// PSS_PrestationsPropertiesBP
//---------------------------------------------------------------------------
PSS_PrestationsPropertiesBP::PSS_PrestationsPropertiesBP() :
    m_pPos(NULL)
{}
//---------------------------------------------------------------------------
PSS_PrestationsPropertiesBP::~PSS_PrestationsPropertiesBP()
{}
//---------------------------------------------------------------------------
PSS_PrestationsPropertiesBP& PSS_PrestationsPropertiesBP::operator = (const PSS_PrestationsPropertiesBP& other)
{
    POSITION pPos = other.m_Prestations.GetHeadPosition();

    while (pPos)
    {
        // get the prestation to copy
        CObject*        pObject        = const_cast<CObject*>(other.m_Prestations.GetAt(pPos));
        PSS_Prestation* pSrcPrestation = dynamic_cast<PSS_Prestation*>(pObject);

        // copy the prestation and add it to the local properties
        std::unique_ptr<PSS_Prestation> pPrestation(new PSS_Prestation(*pSrcPrestation));
        m_Prestations.AddTail(pPrestation.get());
        pPrestation.release();

        other.m_Prestations.GetNext(pPos);
    }

    m_pPos = other.m_pPos;

    return *this;
}
//---------------------------------------------------------------------------
void PSS_PrestationsPropertiesBP::AddPrestation(PSS_Prestation* pPrestation)
{
    m_pPos = m_Prestations.AddTail(pPrestation);
}
//---------------------------------------------------------------------------
void PSS_PrestationsPropertiesBP::RemovePrestation(POSITION pPos)
{
    if (!pPos)
        return;

    PSS_Prestation* pNode = GetAt(pPos);

    if (pNode)
        delete pNode;

    m_Prestations.RemoveAt(pPos);
}
//---------------------------------------------------------------------------
void PSS_PrestationsPropertiesBP::RemoveAll()
{
    POSITION pPos = GetHeadPosition();

    while (pPos)
    {
        PSS_Prestation* pPrestation = dynamic_cast<PSS_Prestation*>(m_Prestations.GetAt(pPos));

        if (pPrestation)
            delete pPrestation;

        GetNextPosition();

        m_Prestations.RemoveAt(pPos);

        pPos = m_pPos;
    }
}
//---------------------------------------------------------------------------
PSS_Prestation* PSS_PrestationsPropertiesBP::GetAt(POSITION pPos)
{
    if (pPos)
        return dynamic_cast<PSS_Prestation*>(m_Prestations.GetAt(pPos));

    return NULL;
}
//---------------------------------------------------------------------------
POSITION PSS_PrestationsPropertiesBP::GetHeadPosition()
{
    m_pPos = m_Prestations.GetHeadPosition();

    return m_pPos;
}
//---------------------------------------------------------------------------
POSITION PSS_PrestationsPropertiesBP::GetTailPosition()
{
    m_pPos = m_Prestations.GetTailPosition();

    return m_pPos;
}
//---------------------------------------------------------------------------
POSITION PSS_PrestationsPropertiesBP::GetPrevPosition()
{
    if (m_pPos)
        m_Prestations.GetPrev(m_pPos);

    return m_pPos;
}
//---------------------------------------------------------------------------
POSITION PSS_PrestationsPropertiesBP::GetNextPosition()
{
    if (m_pPos)
        m_Prestations.GetNext(m_pPos);

    return m_pPos;
}
//---------------------------------------------------------------------------
void PSS_PrestationsPropertiesBP::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        TRACE("PSS_PrestationsPropertiesBP::Serialize - Start save\n");

        ar << m_Prestations.GetCount();

        GetHeadPosition();

        while (m_pPos)
        {
            PSS_Prestation* pPrestation = dynamic_cast<PSS_Prestation*>(m_Prestations.GetAt(m_pPos));

            if (pPrestation)
                pPrestation->Serialize(ar);

            GetNextPosition();
        }

        GetHeadPosition();

        TRACE("PSS_PrestationsPropertiesBP::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_PrestationsPropertiesBP::Serialize - Start read\n");

        INT_PTR prestations;
        ar >> prestations;

        for (INT_PTR i = 0; i < prestations; ++i)
        {
            std::unique_ptr<PSS_Prestation> pPrestation(new PSS_Prestation());
            pPrestation->Serialize(ar);

            AddPrestation(pPrestation.get());
            pPrestation.release();
        }

        GetHeadPosition();

        TRACE("PSS_PrestationsPropertiesBP::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
