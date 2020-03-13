/****************************************************************************
 * ==> PSS_FriendPropertyListCtrl ------------------------------------------*
 ****************************************************************************
 * Description : Provides a friend property list controller                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FriendPropertyListCtrlH
#define PSS_FriendPropertyListCtrlH

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

#ifdef _ZPTYMGREXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Friend property list controller
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_FriendPropertyListCtrl : public CListCtrl
{
    public:
        PSS_FriendPropertyListCtrl();
        virtual ~PSS_FriendPropertyListCtrl();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_FriendPropertyListCtrl)
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_FriendPropertyListCtrl)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
