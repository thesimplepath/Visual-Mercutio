#ifndef __ZIMAGEPREVIEWFILEDIALOG__
#define __ZIMAGEPREVIEWFILEDIALOG__
// ZPreviewFileDialog.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT




#include "ZPreviewFileDialog.h"


#ifdef _ZWINUTIL32EXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


/////////////////////////////////////////////////////////////////////////////
// ZIImagePreviewFileDialog dialog

class AFX_EXT_CLASS ZPreviewDIB : public ZAbstractPreview
{
public:
	virtual void SetPreviewFile(const CString& csFileName);
	virtual void DrawPreview(CDC *pDC,int x,int y,int width,int height);

private:
	ZDIB m_Dib;
};



class ZIImagePreviewFileDialog : public ZIPreviewFileDialog
{
	DECLARE_DYNAMIC(ZIImagePreviewFileDialog)

public:
	ZIImagePreviewFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
				    		 CString Title = "", CString InitialDir = "", 
							 CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(ZIImagePreviewFileDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	ZPreviewDIB m_Preview;

};

#endif	// __ZIMAGEPREVIEWFILEDIALOG__
