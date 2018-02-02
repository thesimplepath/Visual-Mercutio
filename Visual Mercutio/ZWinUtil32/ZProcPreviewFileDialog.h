#ifndef __ZPROCPREVIEWFILEDIALOG__
#define __ZPROCPREVIEWFILEDIALOG__
// ZProcPreviewFileDialog.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#include "ZPreviewFileDialog.h"

class ZPreviewProcess : public ZAbstractPreview
{
public:
	virtual void SetPreviewFile(const CString& csFileName);
	virtual void DrawPreview(CDC *pDC,int x,int y,int width,int height);

private:
};



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
// ZIProcessPreviewFileDialog dialog


class AFX_EXT_CLASS ZIProcessPreviewFileDialog : public ZIPreviewFileDialog
{
	DECLARE_DYNAMIC(ZIProcessPreviewFileDialog)

public:
	ZIProcessPreviewFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
				    		   CString Title = "", CString InitialDir = "", 
				    		   CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(ZIProcessPreviewFileDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	ZPreviewProcess m_Preview;

};

#endif	// __ZFORMPREVIEWFILEDIALOG__
