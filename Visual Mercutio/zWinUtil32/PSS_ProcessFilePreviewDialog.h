/****************************************************************************
 * ==> PSS_ProcessFilePreviewDialog ----------------------------------------*
 ****************************************************************************
 * Description : Provides a process preview file dialog box                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessFilePreviewDialogH
#define PSS_ProcessFilePreviewDialogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_FilePreviewDialog.h"

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
* Process preview form
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ProcessPreviewForm : public PSS_AbstractPreviewForm
{
    public:
        /**
        * Sets the preview file
        *@param fileName - file name
        */
        virtual void SetPreviewFile(const CString& csFileName);

        /**
        * Draws the preview content
        *@param pDC - device context to draw to
        *@param x - x start position in pixels
        *@param y - y start position in pixels
        *@param width - canvas width in pixels
        *@param height - canvas height in pixels
        */
        virtual void DrawPreview(CDC* pDC, int x, int y, int width, int height);
};

/**
* Process preview file dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessFilePreviewDialog : public PSS_FilePreviewDialog
{
    DECLARE_DYNAMIC(PSS_ProcessFilePreviewDialog)

    public:
        /**
        * Constructor
        *@param openFileDialog - if TRUE, file open dialog box will be shown, otherwise file save as dialog box will be shown
        *@param title - title
        *@param initialDir - initial directory to start from
        *@param pParentWnd - parent window, can be NULL
        */
        PSS_ProcessFilePreviewDialog(BOOL           openFileDialog,
                                     const CString& title      = "",
                                     const CString& initialDir = "",
                                     CWnd*          pParentWnd = NULL);

    protected:
        //{{AFX_MSG(PSS_ProcessFilePreviewDialog)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_ProcessPreviewForm m_Preview;
};

#endif
