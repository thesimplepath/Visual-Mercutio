/****************************************************************************
 * ==> PSS_FormPreviewFileDialog -------------------------------------------*
 ****************************************************************************
 * Description : Provides a form preview file dialog box                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FormPreviewFileDialogH
#define PSS_FormPreviewFileDialogH

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
* Preview form
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PreviewForm : public ZAbstractPreview
{
    public:
        /**
        * Sets the preview file
        *@param fileName - file name
        */
        virtual void SetPreviewFile(const CString& fileName);

        /**
        * Draws the preview form content
        *@param pDC - device context to paint to
        *@param x - x start position in pixels
        *@param y - y start position in pixels
        *@param width - canvas width in pixels
        *@param height - canvas height in pixels
        */
        virtual void DrawPreview(CDC* pDC, int x, int y, int width, int height);
};

/**
* Form preview file dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_FormPreviewFileDialog : public ZIPreviewFileDialog
{
    DECLARE_DYNAMIC(PSS_FormPreviewFileDialog)

    public:
        /**
        * Constructor
        *@param openFileDialog - if TRUE, file open dialog box will be opened, otherwise file save as dialog box will be opened
        *@param title - dialog box title to show
        *@param initalDir - initial directory to start from
        *@param pPArentWnd - parent window, can be NULL
        */
        PSS_FormPreviewFileDialog(BOOL           openFileDialog,
                                  const CString& title      = "",
                                  const CString& initialDir = "",
                                  CWnd*          pParentWnd = NULL);

    protected:
        //{{AFX_MSG(PSS_FormPreviewFileDialog)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_PreviewForm m_Preview;
};

#endif
