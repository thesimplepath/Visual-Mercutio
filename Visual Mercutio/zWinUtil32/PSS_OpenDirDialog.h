/****************************************************************************
 * ==> PSS_OpenDirDialog ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an open directory dialog box                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_OpenDirDialogH
#define PSS_OpenDirDialogH

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZIDialog.h"
#include "PSS_DirTreeCtrl.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

#ifndef _WIN32
    // 16 bit only
    extern "C" extern void WINAPI InitZWinUtilDLL();
    extern AFX_EXTENSION_MODULE NEAR extensionZWinUtilDLL;
    #define AFX_EXT_CLASS
#else
    // 32 bit only
    extern AFX_EXTENSION_MODULE extensionZWinUtil32DLL;
#endif

/**
* Open directory dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_OpenDirDialog
{
    public:
        /**
        * Constructor
        *@param title - dialog title
        *@param pParentWnd - parent window, can be NULL
        */
        PSS_OpenDirDialog(const CString& title = "", CWnd* pParentWnd = NULL);

        /**
        * Constructor
        *@param id - dialog resource identifier
        *@param pParentWnd - parent window, can be NULL
        */
        PSS_OpenDirDialog(UINT id, CWnd* pParentWnd = NULL);

        /**
        * Gets the selected directory
        *@return the selected directory
        */
        virtual inline CString GetDirectory() const;

        /**
        * Processes the selected directory
        *@return the processed selected directory
        */
        virtual CString ProcessDirectory();

    protected:
        CWnd*   m_pParentWnd;
        CString m_Title;
        CString m_Directory;
};

//---------------------------------------------------------------------------
// PSS_OpenDirDialog
//---------------------------------------------------------------------------
CString PSS_OpenDirDialog::GetDirectory() const
{
    return m_Directory; 
}
//---------------------------------------------------------------------------

#endif
