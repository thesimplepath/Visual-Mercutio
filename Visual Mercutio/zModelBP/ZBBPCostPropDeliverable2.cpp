// ***********************************************************************************
// * ZBBPCostPropDeliverable2.cpp : Implementation of ZBBPCostPropertiesDeliverable2 *
// *                                                                                 *
// * ProcessSoft Classes                                                             *
// * <nl>Copyright <cp> 2001 - ProcessSoft SA,                                         *
// * All rights reserved.                                                             *
// *                                                                                 *
// * This source code is only intended as a supplement to                             *
// * the ProcessSoft Class Reference and related                                     *
// * electronic documentation provided with the library.                             *
// * See these sources for detailed information regarding                             *
// * ProcessSoft products.                                                             *
// *                                                                                 *
// * Author:       Dom                                                                 *
// * Created:         05/2001                                                         *
// * Description:  ZBBPCostPropertiesDeliverable2 cost properties for deliverables     *
// ***********************************************************************************

#include "stdafx.h"
#include "ZBBPCostPropDeliverable2.h"

#include "zBaseLib\PSS_BaseDocument.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 8 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// **********************************************************************************************************
// *                          ZBBPCostPropertiesDeliverable2 construction/destruction                        *
// **********************************************************************************************************

IMPLEMENT_SERIAL(ZBBPCostPropertiesDeliverable2, CObject, g_DefVersion)

using namespace sfl;

//@mfunc | ZBBPCostPropertiesDeliverable2 | ZBBPCostPropertiesDeliverable2 | Constructor.

//@syntax ZBBPCostPropertiesDeliverable2::ZBBPCostPropertiesDeliverable2(int nId);
//@syntax ZBBPCostPropertiesDeliverable2::ZBBPCostPropertiesDeliverable2(const ZBBPCostPropertiesDeliverable2& propBasic);

//@parmopt int | nId | OD_PROP_ORIENTATION | The identifier of the property.
//@parm ZBBPCostPropertiesDeliverable2& | propBasic | The orientation property to copy.
ZBBPCostPropertiesDeliverable2::ZBBPCostPropertiesDeliverable2()
{
    m_ProcessingTime        = 0;
    m_InWorkloadPercent        = 1;
    m_OutWorkloadPercent    = 1;
    m_UnitaryCost            = 0;
    m_CaseDuration            = 0;
    m_CaseDurationMax        = 0;
    m_TargetDuration        = 0;
    m_GreenLineDuration        = 0;
}

ZBBPCostPropertiesDeliverable2::ZBBPCostPropertiesDeliverable2( const ZBBPCostPropertiesDeliverable2& propBasic )
{
    *this = propBasic;
}

//@mfunc Destructor.
ZBBPCostPropertiesDeliverable2::~ZBBPCostPropertiesDeliverable2()
{
}

// **********************************************************************************************************
// *                                    ZBBPCostPropertiesDeliverable2 operations                            *
// **********************************************************************************************************

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPCostPropertiesDeliverable2& ZBBPCostPropertiesDeliverable2::operator=( const ZBBPCostPropertiesDeliverable2& propBasic )
{
    SetProcessingTime        ( propBasic.GetProcessingTime() );
    SetInWorkloadPercent    ( propBasic.GetInWorkloadPercent() );
    SetOutWorkloadPercent    ( propBasic.GetOutWorkloadPercent() );
    SetUnitaryCost            ( propBasic.GetUnitaryCost() );
    SetCaseDuration            ( propBasic.GetCaseDuration() );
    SetCaseDurationMax        ( propBasic.GetCaseDurationMax() );
    SetTargetDuration        ( propBasic.GetTargetDuration() );
    SetGreenLineDuration    ( propBasic.GetGreenLineDuration() );

    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPCostPropertiesDeliverable2::operator==( const ZBBPCostPropertiesDeliverable2 propBasic ) const
{
    return ( GetProcessingTime()        == propBasic.GetProcessingTime()        &&
             GetInWorkloadPercent()        == propBasic.GetInWorkloadPercent()        &&
             GetOutWorkloadPercent()    == propBasic.GetOutWorkloadPercent()    &&
             GetUnitaryCost()            == propBasic.GetUnitaryCost()            &&
             GetCaseDuration()            == propBasic.GetCaseDuration()            &&
             GetCaseDurationMax()        == propBasic.GetCaseDurationMax()        &&
             GetTargetDuration()        == propBasic.GetTargetDuration()        &&
             GetGreenLineDuration()        == propBasic.GetGreenLineDuration() );
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPCostPropertiesDeliverable2::Merge( ZBBPCostPropertiesDeliverable2* pProperty, DWORD dwChangeFlags )
{
    if ( pProperty )
    {
        if ( dwChangeFlags & Z_CHANGE_COST_PROCESSING_TIME )
        {
            m_ProcessingTime = pProperty->GetProcessingTime();
        }

        if ( dwChangeFlags & Z_CHANGE_COST_IN_WORKLOAD_PERCENT )
        {
            m_InWorkloadPercent = pProperty->GetInWorkloadPercent();
        }

        if ( dwChangeFlags & Z_CHANGE_COST_OUT_WORKLOAD_PERCENT )
        {
            m_OutWorkloadPercent = pProperty->GetOutWorkloadPercent();
        }

        if ( dwChangeFlags & Z_CHANGE_COST_UNITARY_COST )
        {
            m_UnitaryCost = pProperty->GetUnitaryCost();
        }

        if ( dwChangeFlags & Z_CHANGE_COST_CASE_DURATION )
        {
            m_CaseDuration = pProperty->GetCaseDuration();
        }

        if ( dwChangeFlags & Z_CHANGE_COST_CASE_DURATIONMAX )
        {
            m_CaseDurationMax = pProperty->GetCaseDurationMax();
        }

        if ( dwChangeFlags & Z_CHANGE_COST_TARGET_DURATION )
        {
            m_TargetDuration = pProperty->GetTargetDuration();
        }

        if ( dwChangeFlags & Z_CHANGE_COST_GREENLINE_DURATION )
        {
            m_GreenLineDuration = pProperty->GetGreenLineDuration();
        }
    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf CODFillProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPCostPropertiesDeliverable2::IsEqual( ZBBPCostPropertiesDeliverable2* pProp )
{
    if ( pProp )
    {
        return ( *this == *pProp );
    }

    return FALSE;
}

// **********************************************************************************************************
// *                                       IODPropertyContainer interface                                    *
// **********************************************************************************************************

//@mfunc | ZBBPCostPropertiesDeliverable2 | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPCostPropertiesDeliverable2::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPCostPropertiesDeliverable2::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPCostPropertiesDeliverable2::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPCostPropertiesDeliverable2::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPCostPropertiesDeliverable2::GetValue(const int nPropId, float& fValue) const
//@syntax BOOL ZBBPCostPropertiesDeliverable2::GetValue(const int nPropId, double& dValue) const
//
//@rdesc TRUE if the property identifier is supported by this property
// container. FALSE if the property identifier is invalid.
//@parm const int | nPropId | ID of property to retrieve.
//@parm CString& | strValue | Variable to assign return value to.
//@parm int& | nValue | Variable to assign return value to.
//@parm UINT& | nValue | Variable to assign return value to.
//@parm DWORD& | dwValue | Variable to assign return value to.
//@parm float& | fValue | Variable to assign return value to.
//
//@comm See <t Orientation Property Identifiers> for a list property IDs
// supported. This function will throw a <c CODPropertyConversionException>
// exception if the data type of the argument passed in is not compatible
// with the given property identifier.

BOOL ZBBPCostPropertiesDeliverable2::GetValue( const int nPropId, CString& strValue ) const
{
    switch ( nPropId )
    {
        case Z_COST_PROCESSING_TIME:
        {
            strValue.Format( _T( "%.0f" ), m_ProcessingTime );
            break;
        }

        case Z_COST_IN_WORKLOAD_PERCENT:
        {
            strValue.Format( _T( "%.0f" ), m_InWorkloadPercent * (float)100 );
            break;
        }

        case Z_COST_OUT_WORKLOAD_PERCENT:
        {
            strValue.Format( _T( "%.0f" ), m_OutWorkloadPercent * (float)100 );
            break;
        }

        case Z_COST_UNITARY_COST:
        {
            strValue.Format( _T( "%.0f" ), m_UnitaryCost );
            break;
        }

        case Z_COST_CASE_DURATION:
        {
            strValue.Format( _T( "%.0f" ), m_CaseDuration );
            break;
        }

        case Z_COST_CASE_DURATIONMAX:
        {
            strValue.Format( _T( "%.0f" ), m_CaseDurationMax );
            break;
        }

        case Z_COST_TARGET_DURATION:
        {
            strValue.Format( _T( "%.0f" ), m_TargetDuration );
            break;
        }

        case Z_COST_GREENLINE_DURATION:
        {
            strValue.Format( _T( "%.0f" ), m_GreenLineDuration );
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPCostPropertiesDeliverable2::GetValue( const int nPropId, int& nValue ) const
{
    // Unused
    nValue;

    if ( nPropId >= Z_COST_PROCESSING_TIME && nPropId <= Z_COST_CASE_DURATIONMAX )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPCostPropertiesDeliverable2::GetValue( const int nPropId, UINT& nValue ) const
{
    // Unused
    nValue;

    if ( nPropId >= Z_COST_PROCESSING_TIME && nPropId <= Z_COST_CASE_DURATIONMAX )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPCostPropertiesDeliverable2::GetValue( const int nPropId, DWORD& dwValue ) const
{
    // Unused
    dwValue;

    if ( nPropId >= Z_COST_PROCESSING_TIME && nPropId <= Z_COST_CASE_DURATIONMAX )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPCostPropertiesDeliverable2::GetValue( const int nPropId, float& fValue ) const
{
    switch ( nPropId )
    {
        case Z_COST_IN_WORKLOAD_PERCENT:
        {
            fValue = m_InWorkloadPercent;
            break;
        }

        case Z_COST_OUT_WORKLOAD_PERCENT:
        {
            fValue = m_OutWorkloadPercent;
            break;
        }

        case Z_COST_UNITARY_COST:
        {
            fValue = m_UnitaryCost;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPCostPropertiesDeliverable2::GetValue( const int nPropId, double& dValue ) const
{
    switch ( nPropId )
    {
        case Z_COST_PROCESSING_TIME:
        {
            dValue = m_ProcessingTime;
            break;
        }

        case Z_COST_CASE_DURATION:
        {
            dValue = m_CaseDuration;
            break;
        }

        case Z_COST_CASE_DURATIONMAX:
        {
            dValue = m_CaseDurationMax;
            break;
        }

        case Z_COST_TARGET_DURATION:
        {
            dValue = m_TargetDuration;
            break;
        }

        case Z_COST_GREENLINE_DURATION:
        {
            dValue = m_GreenLineDuration;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

//@mfunc | ZBBPCostPropertiesDeliverable2 | SetValue | Sets the value of the given property.

//@syntax BOOL ZBBPCostPropertiesDeliverable2::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPCostPropertiesDeliverable2::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPCostPropertiesDeliverable2::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPCostPropertiesDeliverable2::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPCostPropertiesDeliverable2::SetValue(const int nPropId, const float fValue)
//@syntax BOOL ZBBPCostPropertiesDeliverable2::SetValue(const int nPropId, const double dValue)

//@rdesc TRUE if the property identifier is supported by this property
// container. FALSE if the property identifier is invalid.
//@parm const int | nPropId | ID of property to set.
//@parm LPCTSTR | lpszValue | Input value to assign to the specified property.
//@parm const int | nValue | Input value to assign to the specified property.
//@parm const UINT | nValue | Input value to assign to the specified property.
//@parm const DWORD | dwValue | Input value to assign to the specified property.
//@parm const float | fValue | Input value to assign to the specified property.

//@comm See <t Orientation Property Identifiers> for a list property IDs
// supported. This function will throw a <c CODPropertyConversionException>
// exception if the data type of the argument passed in is not compatible
// with the given property identifier.

BOOL ZBBPCostPropertiesDeliverable2::SetValue( const int nPropId, LPCTSTR lpszValue )
{
    switch ( nPropId )
    {
        case Z_COST_PROCESSING_TIME:
        {
            m_ProcessingTime = atof(lpszValue);
            break;
        }

        case Z_COST_IN_WORKLOAD_PERCENT:
        {
            m_InWorkloadPercent = static_cast<float>( atof( lpszValue ) / (float)100 );
            break;
        }

        case Z_COST_OUT_WORKLOAD_PERCENT:
        {
            m_OutWorkloadPercent = static_cast<float>( atof( lpszValue ) / (float)100 );
            break;
        }

        case Z_COST_UNITARY_COST:
        {
            m_UnitaryCost = static_cast<float>( atof( lpszValue ) );
            break;
        }

        case Z_COST_CASE_DURATION:
        {
            m_CaseDuration = atof( lpszValue );
            break;
        }

        case Z_COST_CASE_DURATIONMAX:
        {
            m_CaseDurationMax = atof( lpszValue );
            break;
        }

        case Z_COST_TARGET_DURATION:
        {
            m_TargetDuration = atof( lpszValue );
            break;
        }

        case Z_COST_GREENLINE_DURATION:
        {
            m_GreenLineDuration = atof( lpszValue );
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPCostPropertiesDeliverable2::SetValue( const int nPropId, const int nValue )
{
    // Unused
    nValue;

    if ( nPropId >= Z_COST_PROCESSING_TIME && nPropId <= Z_COST_CASE_DURATIONMAX )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPCostPropertiesDeliverable2::SetValue( const int nPropId, const UINT nValue )
{
    // Unused
    nValue;

    if ( nPropId >= Z_COST_PROCESSING_TIME && nPropId <= Z_COST_CASE_DURATIONMAX )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPCostPropertiesDeliverable2::SetValue( const int nPropId, const DWORD dwValue )
{
    // Unused
    dwValue;

    if ( nPropId >= Z_COST_PROCESSING_TIME && nPropId <= Z_COST_CASE_DURATIONMAX )
    {
        throw new CODPropertyConversionException();
    }

    return FALSE;
}

BOOL ZBBPCostPropertiesDeliverable2::SetValue( const int nPropId, const float fValue )
{
    switch ( nPropId )
    {
        case Z_COST_IN_WORKLOAD_PERCENT:
        {
            m_InWorkloadPercent = fValue;
            break;
        }

        case Z_COST_OUT_WORKLOAD_PERCENT:
        {
            m_OutWorkloadPercent = fValue;
            break;
        }

        case Z_COST_UNITARY_COST:
        {
            m_UnitaryCost = fValue;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL ZBBPCostPropertiesDeliverable2::SetValue( const int nPropId, const double dValue )
{
    switch ( nPropId )
    {
        case Z_COST_PROCESSING_TIME:
        {
            m_ProcessingTime = dValue;
            break;
        }

        case Z_COST_CASE_DURATION:
        {
            m_CaseDuration = dValue;
            break;
        }

        case Z_COST_CASE_DURATIONMAX:
        {
            m_CaseDurationMax = dValue;
            break;
        }

        case Z_COST_TARGET_DURATION:
        {
            m_TargetDuration = dValue;
            break;
        }

        case Z_COST_GREENLINE_DURATION:
        {
            m_GreenLineDuration = dValue;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

// **********************************************************************************************************
// *                                  ZBBPCostPropertiesDeliverable2 diagnostics                            *
// **********************************************************************************************************

#ifdef _DEBUG
void ZBBPCostPropertiesDeliverable2::AssertValid() const
{
    CObject::AssertValid();
}

void ZBBPCostPropertiesDeliverable2::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );
}
#endif //_DEBUG

// **********************************************************************************************************
// *                                 ZBBPCostPropertiesDeliverable2 serialization                            *
// **********************************************************************************************************

//@mfunc Serializes the orientation properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBPCostPropertiesDeliverable2::Serialize( CArchive& ar )
{
    CObject::Serialize( ar );

    if ( ar.IsStoring() )
    {
        TRACE( _T( "ZBBPCostPropertiesDeliverable2::Serialize : Start Save\n" ) );

        PUT_SCHEMA( ar, ZBBPCostPropertiesDeliverable2 );
        ar << m_ProcessingTime;
        ar << m_InWorkloadPercent;
        ar << m_OutWorkloadPercent;
        ar << m_UnitaryCost;
        ar << m_CaseDuration;
        ar << m_CaseDurationMax;
        ar << m_TargetDuration;
        ar << m_GreenLineDuration;

        TRACE( _T( "ZBBPCostPropertiesDeliverable2::Serialize : End Save\n" ) );
    }
    else
    {
        TRACE( _T( "ZBBPCostPropertiesDeliverable2::Serialize : Start Read\n" ) );

        UINT nSchema;
        GET_SCHEMA( ar, nSchema );
        ar >> m_ProcessingTime;
        ar >> m_InWorkloadPercent;
        ar >> m_OutWorkloadPercent;
        ar >> m_UnitaryCost;

        if ( ar.m_pDocument &&
             ( (PSS_BaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 20 )
        {
            ar >> m_CaseDuration;
        }

        if ( ar.m_pDocument &&
             ( (PSS_BaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 21 )
        {
            ar >> m_CaseDurationMax;
        }

        if ( ar.m_pDocument &&
             ( (PSS_BaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 20 )
        {
            ar >> m_TargetDuration;
            ar >> m_GreenLineDuration;
        }

        TRACE( _T( "ZBBPCostPropertiesDeliverable2::Serialize : End Read\n" ) );
    }
}
