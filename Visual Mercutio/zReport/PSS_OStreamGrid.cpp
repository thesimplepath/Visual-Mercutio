/****************************************************************************
 * ==> PSS_OStreamGrid -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an output stream grid                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_OStreamGrid.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_OStreamGrid
//---------------------------------------------------------------------------
PSS_OStreamGrid::PSS_OStreamGrid(CGXGridCore* pGridCore) :
    PSS_IOSGrid(pGridCore)
{}
//---------------------------------------------------------------------------
PSS_OStreamGrid::~PSS_OStreamGrid()
{}
//---------------------------------------------------------------------------

CGXStyle PSS_OStreamGrid::ConvertNumber(float value) const
{
    CString strVal       = _T("");
    CString strValLength = _T("");
    int     length       = 0;

    strVal.Format(_T("%f"), value);

    for (int i = 0; i < strVal.GetLength(); ++i)
        if (strVal.GetAt(i) == _T('.'))
        {
            length = i;
            break;
        }

    strValLength.Format(_T("%d"), length);

    return InitNumberStyle().SetUserAttribute(GX_IDS_UA_CURNUMDECIMALS, strValLength).SetValue(value);
}
//---------------------------------------------------------------------------
CGXStyle PSS_OStreamGrid::ConvertNumber(double value) const
{
    CString strVal       = _T("");
    CString strValLength = _T("");
    int     length       = 0;

    strVal.Format(_T("%lf"), value);

    for (int i = 0; i < strVal.GetLength(); ++i)
        if (strVal.GetAt(i) == _T('.'))
        {
            length = i;
            break;
        }

    strValLength.Format(_T("%d"), length);

    return InitNumberStyle().SetUserAttribute(GX_IDS_UA_CURNUMDECIMALS, strValLength).SetValue(value);
}
//---------------------------------------------------------------------------
CGXStyle PSS_OStreamGrid::ConvertNumber(DWORD value) const
{
    CString strVal       = _T("");
    CString strValLength = _T("");

    strVal.Format(_T("%lu"), value);
    strValLength.Format(_T("%d"), strVal.GetLength());

    return InitNumberStyle().SetUserAttribute(GX_IDS_UA_CURNUMDECIMALS, strValLength).SetValue(value);
}
//---------------------------------------------------------------------------
CGXStyle PSS_OStreamGrid::ConvertNumber(UINT value) const
{
    CString strVal       = _T("");
    CString strValLength = _T("");

    strVal.Format(_T("%u"), value);
    strValLength.Format(_T("%d"), strVal.GetLength());

    return InitNumberStyle().SetUserAttribute(GX_IDS_UA_CURNUMDECIMALS, strValLength).SetValue(value);
}
//---------------------------------------------------------------------------
CGXStyle PSS_OStreamGrid::ConvertNumber(WORD value) const
{
    CString strVal       = _T("");
    CString strValLength = _T("");

    strVal.Format(_T("%hu"), value);
    strValLength.Format(_T("%d"), strVal.GetLength());

    return InitNumberStyle().SetUserAttribute(GX_IDS_UA_CURNUMDECIMALS, strValLength).SetValue(value);
}
//---------------------------------------------------------------------------
CGXStyle PSS_OStreamGrid::ConvertNumber(short value) const
{
    CString strVal       = _T("");
    CString strValLength = _T("");

    strVal.Format(_T("%hd"), value);
    strValLength.Format(_T("%d"), strVal.GetLength());

    return InitNumberStyle().SetUserAttribute(GX_IDS_UA_CURNUMDECIMALS, strValLength).SetValue(value);
}
//---------------------------------------------------------------------------
CGXStyle PSS_OStreamGrid::ConvertNumber(LONG value) const
{
    CString strVal       = _T("");
    CString strValLength = _T("");

    strVal.Format(_T("%ld"), value);
    strValLength.Format(_T("%d"), strVal.GetLength());

    return InitNumberStyle().SetUserAttribute(GX_IDS_UA_CURNUMDECIMALS, strValLength).SetValue(value);
}
//---------------------------------------------------------------------------
