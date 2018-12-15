// BaseTMDI.h : header file
//

#ifndef BaseTMDI_h
#define BaseTMDI_h 1


#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZISubject.h"
#include "ZIObserver.h"



#ifdef _ZBASELIBEXPORT
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
// ZIBaseTitleMDIPage frame

class AFX_EXT_CLASS ZIBaseTitleMDIPage : public SECMDIChildWnd, 
                                         public ZISubject, 
                                         public ZIObserver
{
    DECLARE_DYNCREATE(ZIBaseTitleMDIPage)
protected:
    ZIBaseTitleMDIPage();            // protected constructor used by dynamic creation

// Operations
public:
    void UpdateFrameTitle(BOOL bAddToTitle);
    virtual void ActivateFrame(int nCmdShow);

    ///////////////////////////////////////////////////////////
    // ZIObserver call-back method
    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

// Implementation
protected:
    virtual ~ZIBaseTitleMDIPage();
    virtual void OnUpdateFrameTitle(BOOL bAddToTitle);

    // Generated message map functions
    //{{AFX_MSG(ZIBaseTitleMDIPage)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:
    CString    m_sTemplateDef;
    CString    m_sTypeFile;

};

/////////////////////////////////////////////////////////////////////////////

inline void ZIBaseTitleMDIPage::UpdateFrameTitle(BOOL bAddToTitle) 
{  
    OnUpdateFrameTitle(bAddToTitle); 
}


#endif // BaseTMDI_h