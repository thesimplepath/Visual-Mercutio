/****************************************************************************
 * ==> PSS_ImagePreviewFileDialog ------------------------------------------*
 ****************************************************************************
 * Description : Provides an image preview file dialog box                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ImagePreviewFileDialogH
#define PSS_ImagePreviewFileDialogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "ZPreviewFileDialog.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Preview bitmap
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PreviewDIB : public ZAbstractPreview
{
    public:
        /**
        * Sets the preview file
        *@param fileName - preview file name
        */
        virtual void SetPreviewFile(const CString& fileName);

        /**
        * Draws the preview
        *@param pDC - device context to paint to
        *@param x - x start position in pixels
        *@param y - y start position in pixels
        *@param width - canvas width in pixels
        *@param height - canvas height in pixels
        */
        virtual void DrawPreview(CDC* pDC, int x, int y, int width, int height);

    private:
        ZDIB m_Dib;
};

/**
* Image preview file dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ImagePreviewFileDialog : public ZIPreviewFileDialog
{
    DECLARE_DYNAMIC(PSS_ImagePreviewFileDialog)

    public:
        /**
        * Constructor
        *@param openFileDialog - if TRUE, file open dialog box will be shown, otherwise file save as dialog box will be shown
        *@param title - dialog title
        *@param initialDir - initial directory to start from
        *@param pParentWnd - parent window, can be NULL
        */
        PSS_ImagePreviewFileDialog(BOOL           openFileDialog,
                                   const CString& title      = "",
                                   const CString& initialDir = "",
                                   CWnd*          pParentWnd = NULL);

    protected:
        //{{AFX_MSG(PSS_ImagePreviewFileDialog)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_PreviewDIB m_Preview;
};

#endif
