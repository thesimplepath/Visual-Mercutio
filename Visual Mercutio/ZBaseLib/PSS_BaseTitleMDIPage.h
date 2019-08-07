/****************************************************************************
 * ==> PSS_BaseTitleMDIPage ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic title multiple document interface page    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BaseTitleMDIPageH
#define PSS_BaseTitleMDIPageH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "ZISubject.h"
#include "ZIObserver.h"

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
* Basic title multiple document interface page
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BaseTitleMDIPage : public SECMDIChildWnd,
                                           public ZISubject,
                                           public ZIObserver
{
    DECLARE_DYNCREATE(PSS_BaseTitleMDIPage)

    public:
        /**
        * Updates the frame title
        *@param addToTitle - if TRUE, the frame title will be added to the application title
        */
        virtual inline void UpdateFrameTitle(BOOL addToTitle);

        /**
        * Activates the frame
        *@param cmdShow - show window parameter
        */
        virtual void ActivateFrame(int cmdShow);

        /**
        * Called when the frame is updated
        *@param pSubject - subject
        *@param pMSg - message
        */
        virtual void OnUpdate(ZISubject* pSubject, ZIObserverMsg* pMsg);

    protected:
        CString m_TemplateDef;
        CString m_TypeFile;

        PSS_BaseTitleMDIPage();
        virtual ~PSS_BaseTitleMDIPage();

        /**
        * Called when the frame title is updated
        *@param addToTitle - if TRUE, the frame title will be added to the application title
        */
        virtual void OnUpdateFrameTitle(BOOL addToTitle);

        /// Generated message map functions
        //{{AFX_MSG(PSS_BaseTitleMDIPage)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
// PSS_BaseTitleMDIPage
//---------------------------------------------------------------------------
void PSS_BaseTitleMDIPage::UpdateFrameTitle(BOOL addToTitle)
{
    OnUpdateFrameTitle(addToTitle);
}
//---------------------------------------------------------------------------

#endif
