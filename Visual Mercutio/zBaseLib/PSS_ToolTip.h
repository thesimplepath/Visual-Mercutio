/****************************************************************************
 * ==> PSS_ToolTip ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a tooltip interface                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ToolTipH
#define PSS_ToolTipH

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

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Tooltip interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ToolTip
{
    public:
        /**
        * Tooltip mode
        */
        enum class IEToolTipMode
        {
            IE_TT_Normal,
            IE_TT_Design
        };

        PSS_ToolTip();
        virtual ~PSS_ToolTip();

        /**
        * Called when a tooltip is required
        *@param[in, out] toolTipText - tooltip text, formatted tooltip text on function ends
        *@param point - hit point
        *@param mode - tooltip mode
        *@return true if tooltip can be shown, otherwise false
        */
        virtual bool OnToolTip(CString& toolTipText, const CPoint& point, IEToolTipMode mode = IEToolTipMode::IE_TT_Normal) = 0;
};

#endif
