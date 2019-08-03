/****************************************************************************
 * ==> PSS_FilePreviewDialog -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a file preview dialog box                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FilePreviewDialogH
#define PSS_FilePreviewDialogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZDib.h"

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
* Abstract preview form interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_AbstractPreviewForm
{
    public:
        /**
        * Sets the preview file
        *@param fileName - file name
        */
        virtual void SetPreviewFile(const CString& fileName) = 0;

        /**
        * Draws the preview content
        *@param pDC - device context to draw to
        *@param x - x start position in pixels
        *@param y - y start position in pixels
        *@param width - canvas width in pixels
        *@param height - canvas height in pixels
        */
        virtual void DrawPreview(CDC* pDC, int x, int y, int width, int height) = 0;

        /**
        * Calculates the preview rectangle
        *@param bmpWidth - bitmap width in pixels
        *@param bmpHeight - bitmap height in pixels
        *@param wndWidth - window width in pixels
        *@param wndHeight - window height in pixels
        *@return calculated rectangle
        */
        virtual CRect Calc(int bmpWidth, int bmpHeight, int wndWidth, int wndHeight);
};

/**
* File preview dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FilePreviewDialog : public CFileDialog
{
    DECLARE_DYNAMIC(PSS_FilePreviewDialog)

    public:
        /**
        * Constructor
        *@param pPreview - preview form
        *@param openFileDialog - if TRUE, file open dialog box will be shown, otherwise file save as dialog box will be shown
        *@param title - title
        *@param initialDir - initial directory to start from
        *@param pDefExt - default extension, can be empty
        *@param pFileName - default file name, can be empty
        *@param flags - flags
        *@param filters - filters, can be empty
        *@param pParentWnd - parent window, can be NULL
        */
        PSS_FilePreviewDialog(PSS_AbstractPreviewForm* pPreview,
                              BOOL                     openFileDialog,
                              const CString&           title      = "",
                              const CString&           initialDir = "", 
                              LPCTSTR                  pDefExt    = NULL,
                              LPCTSTR                  pFileName  = NULL,
                              DWORD                    flags      = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                              LPCTSTR                  pFilters   = NULL,
                              CWnd*                    pParentWnd = NULL);

    protected:
        PSS_AbstractPreviewForm* m_pPreview;
        CRgn                     m_Region;
        CButton                  m_CheckBox;
        CRect                    m_PreviewRect;
        CString                  m_Title;
        CString                  m_InitialDir;
        CString                  m_FileName;
        BOOL                     m_Preview;
        BOOL                     m_Changed;
        BOOL                     m_RegionHasBeenCreated;

        //{{AFX_MSG(PSS_FilePreviewDialog)
        virtual BOOL OnInitDialog();
        virtual void OnInitDone();
        afx_msg void OnClickedPreview();
        afx_msg void OnPaint();
        afx_msg void OnSize(UINT nType, int cx, int cy);
        virtual void OnFileNameChange();
        virtual void OnFolderChange();
        virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
