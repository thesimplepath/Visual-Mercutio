/****************************************************************************
 * ==> PSS_GridCheckBox ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid checkbox                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GridCheckBoxH
#define PSS_GridCheckBoxH

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
* Grid checkbox
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GridCheckBox : public CGXCheckBox
{
    public:
        /**
        * Constructor
        *@param pGridCore - the grid core
        */
        PSS_GridCheckBox(CGXGridCore* pGrid);

        virtual ~PSS_GridCheckBox();

        /**
        * Gets the color value
        *@param rgb - the source rgb color
        *@param print - if true, the grid is printing
        *@return the color value
        */
        virtual COLORREF GetColorValue(COLORREF rgb, BOOL print);
};

#endif
