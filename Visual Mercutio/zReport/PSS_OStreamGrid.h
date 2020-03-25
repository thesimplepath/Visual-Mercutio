/****************************************************************************
 * ==> PSS_OStreamGrid -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an output stream grid                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_OStreamGridH
#define PSS_OStreamGridH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_IOSGrid.h"

#ifdef _ZREPORTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Output stream grid
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_OStreamGrid : virtual public PSS_IOSGrid
{
    public:
        /**
        * Constructor
        *@param pGridCore - the grid core
        */
        PSS_OStreamGrid(CGXGridCore* pGridCore = NULL);

        virtual ~PSS_OStreamGrid();

        /**
        * Write stream operator
        *@param pValue - the value to write
        *@return itself, to allow operator to be chained with other items, e.g a << b << c
        */
        inline PSS_OStreamGrid& operator << (const char* pValue);

        /**
        * Write stream operator
        *@param value - the value to write
        *@return itself, to allow operator to be chained with other items, e.g a << b << c
        */
        inline PSS_OStreamGrid& operator << (float           value);
        inline PSS_OStreamGrid& operator << (double          value);
        inline PSS_OStreamGrid& operator << (WORD            value);
        inline PSS_OStreamGrid& operator << (DWORD           value);
        inline PSS_OStreamGrid& operator << (UINT            value);
        inline PSS_OStreamGrid& operator << (short           value);
        inline PSS_OStreamGrid& operator << (LONG            value);
        inline PSS_OStreamGrid& operator << (const CPoint&   value);
        inline PSS_OStreamGrid& operator << (const CRect&    value);
        inline PSS_OStreamGrid& operator << (const CSize&    value);
        inline PSS_OStreamGrid& operator << (const CGXStyle& value);
        inline PSS_OStreamGrid& operator << (const CGXFont&  value);

        /**
        * Sets the currently selected row width
        *@param height - the row width
        */
        virtual inline void SetCurSelColWidth(int width);

        /**
        * Sets the currently selected row height
        *@param height - the row height
        */
        virtual inline void SetCurSelRowHeight(int height);

    private:
        /**
        * Initializes the style to apply to the value to write
        *@return the style
        */
        inline CGXStyle InitNumberStyle() const;

        /**
        * Converts the number and prepares the style to apply to a float value
        *@param value - number value to convert and show
        *@return the style to use to show the value
        */
        CGXStyle ConvertNumber(float  value) const;
        CGXStyle ConvertNumber(double value) const;
        CGXStyle ConvertNumber(DWORD  value) const;
        CGXStyle ConvertNumber(UINT   value) const;
        CGXStyle ConvertNumber(WORD   value) const;
        CGXStyle ConvertNumber(short  value) const;
        CGXStyle ConvertNumber(LONG   value) const;
};

//---------------------------------------------------------------------------
// PSS_OStreamGrid
//---------------------------------------------------------------------------
PSS_OStreamGrid& PSS_OStreamGrid::operator << (const char* pValue)
{
    if (!m_pGridCore)
        return *this;

    const char* pCurrent = pValue;
    const char* pLast    = pValue;

    while (*pCurrent)
        switch (*pCurrent)
        {
            case '\t':
            {
                // copy the substring
                const CString str(pLast, pCurrent - pLast);

                // assign the cell string
                if (!str.IsEmpty())
                    m_pGridCore->SetStyleRange(ConvertToCGXRange(), CGXStyle().SetValue(str));

                // move right
                Right();

                // update the last position and move forward one char
                pLast = ++pCurrent;

                continue;
            }

            case '\n':
            {
                // copy the substring
                const CString str(pLast, pCurrent - pLast);

                // assign the cell string
                if (!str.IsEmpty())
                    m_pGridCore->SetStyleRange(ConvertToCGXRange(), CGXStyle().SetValue(str));

                // move down
                Down();

                // move home left
                HomeLeft();

                // update the last position and move forward one char
                pLast = ++pCurrent;

                continue;
            }

            default:
                // move forward one char
                ++pCurrent;
                continue;
        }

    // process the last string
    const CString str(pLast, pCurrent - pLast);

    // assign the cell string
    if (!str.IsEmpty())
        m_pGridCore->SetStyleRange(ConvertToCGXRange(), CGXStyle().SetValue(pValue));

    return *this;
}
//---------------------------------------------------------------------------
PSS_OStreamGrid& PSS_OStreamGrid::operator << (float value)
{
    if (m_pGridCore)
        m_pGridCore->SetStyleRange(ConvertToCGXRange(), ConvertNumber(value));

    return *this;
}
//---------------------------------------------------------------------------
PSS_OStreamGrid& PSS_OStreamGrid::operator << (double value)
{
    if (m_pGridCore)
        m_pGridCore->SetStyleRange(ConvertToCGXRange(), ConvertNumber(value));

    return *this;
}
//---------------------------------------------------------------------------
PSS_OStreamGrid& PSS_OStreamGrid::operator << (WORD value)
{
    if (m_pGridCore)
        m_pGridCore->SetStyleRange(ConvertToCGXRange(), ConvertNumber(value));

    return *this;
}
//---------------------------------------------------------------------------
PSS_OStreamGrid& PSS_OStreamGrid::operator << (DWORD value)
{
    if (m_pGridCore)
        m_pGridCore->SetStyleRange(ConvertToCGXRange(), ConvertNumber(value));

    return *this;
}
//---------------------------------------------------------------------------
PSS_OStreamGrid& PSS_OStreamGrid::operator << (UINT value)
{
    if (m_pGridCore)
        m_pGridCore->SetStyleRange(ConvertToCGXRange(), ConvertNumber(value));

    return *this;
}
//---------------------------------------------------------------------------
PSS_OStreamGrid& PSS_OStreamGrid::operator << (short value)
{
    if (m_pGridCore)
        m_pGridCore->SetStyleRange(ConvertToCGXRange(), ConvertNumber(value));

    return *this;
}
//---------------------------------------------------------------------------
PSS_OStreamGrid& PSS_OStreamGrid::operator << (LONG value)
{
    if (m_pGridCore)
        m_pGridCore->SetStyleRange(ConvertToCGXRange(), ConvertNumber(value));

    return *this;
}
//---------------------------------------------------------------------------
PSS_OStreamGrid& PSS_OStreamGrid::operator << (const CPoint& value)
{
    SetCurSel(const_cast<CPoint&>(value));
    return *this;
}
//---------------------------------------------------------------------------
PSS_OStreamGrid& PSS_OStreamGrid::operator << (const CRect& value)
{
    SetCurSel(const_cast<CRect&>(value));
    return *this;
}
//---------------------------------------------------------------------------
PSS_OStreamGrid& PSS_OStreamGrid::operator << (const CSize& value)
{
    if (m_pGridCore)
    {
        int left;
        int top;
        int right;
        int bottom;

        GetCurSel(left, top, right, bottom);

        // set the column width if different from 0
        if (value.cx)
            m_pGridCore->SetColWidth(left, right, value.cx);

        // set the row height if different from 0
        if (value.cy)
            m_pGridCore->SetRowHeight(top, bottom, value.cy);
    }

    return *this;
}
//---------------------------------------------------------------------------
PSS_OStreamGrid& PSS_OStreamGrid::operator << (const CGXStyle& value)
{
    if (m_pGridCore)
        m_pGridCore->SetStyleRange(ConvertToCGXRange(), value);

    return *this;
}
//---------------------------------------------------------------------------
PSS_OStreamGrid& PSS_OStreamGrid::operator << (const CGXFont& value)
{
    if (m_pGridCore)
        m_pGridCore->SetStyleRange(ConvertToCGXRange(), CGXStyle().SetFont(value));

    return *this;
}
//---------------------------------------------------------------------------
void PSS_OStreamGrid::SetCurSelColWidth(int width)
{
    if (m_pGridCore)
    {
        int left;
        int top;
        int right;
        int bottom;

        GetCurSel(left, top, right, bottom);

        m_pGridCore->SetColWidth(left, right, width);
    }
}
//---------------------------------------------------------------------------
void PSS_OStreamGrid::SetCurSelRowHeight(int height)
{
    if (m_pGridCore)
    {
        int left;
        int top;
        int right;
        int bottom;

        GetCurSel(left, top, right, bottom);

        m_pGridCore->SetRowHeight(top, bottom, height);
    }
}
//---------------------------------------------------------------------------
CGXStyle PSS_OStreamGrid::InitNumberStyle() const
{
    return CGXStyle()
            .SetControl      (GX_IDS_CTRL_CURRENCY)
            .SetUserAttribute(GX_IDS_UA_CURRENCYDEF, _T("11 0"))
            .SetUserAttribute(GX_IDS_UA_CURMON,      _T("0"))
            .SetUserAttribute(GX_IDS_UA_CURSEP,      _T("'."))
            .SetUserAttribute(GX_IDS_UA_CURNUMFRACT, _T("0"));
}
//---------------------------------------------------------------------------

#endif
