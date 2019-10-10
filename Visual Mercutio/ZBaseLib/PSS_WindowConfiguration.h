/****************************************************************************
 * ==> PSS_WindowConfiguration ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a windows position and state configuration system *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WindowConfigurationH
#define PSS_WindowConfigurationH

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZUSystemOption.h"

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
* Windows position and state configuration system
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WindowConfiguration
{
    public:
        /**
        * Constructor
        *@param iniFile - the ini file name
        */
        PSS_WindowConfiguration(const CString& iniFile = "");

        virtual ~PSS_WindowConfiguration();

        /**
        * Creates the default configuration
        *@param iniFile - the ini file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(const CString& iniFile = "");

        /**
        * Sets the ini file name
        *@param iniFile - the ini file name
        */
        virtual inline void SetIniFile(const CString& file);

        /**
        * Reads the window size, position and attribute, and saves these values
        *@param pWnd - the target window
        *@param wndName - the target window name
        *@param positionOnly - if TRUE, only the window position will be saved
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveWindowPosition(CWnd* pWnd, const CString& wndName, BOOL positionOnly = FALSE);

        /**
        * Reads the saved values and restores the size, position and attributes to the Window
        *@param pWnd - the target window
        *@param wndName - the target window name
        *@param positionOnly - if TRUE, only the window position will be saved
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RestoreWindowPosition(CWnd* pWnd, const CString& wndName, BOOL positionOnly = FALSE);

        /**
        * Reads the desktop and saves all windows size, position and attribute values
        *@param pDesktopWnd - the desktop window
        *@param wndName - the target window name
        *@param positionOnly - if TRUE, only the window position will be saved
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveWindowDesktop(CWnd* pDesktopWnd, const CString& wndName = "", BOOL positionOnly = FALSE);

        /**
        * Reads the values of desktop windows and restores it
        *@param pDesktopWnd - the desktop window
        *@param wndName - the target window name
        *@param positionOnly - if TRUE, only the window position will be saved
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RestoreWindowDesktop(CWnd* pDesktopWnd, const CString& wndName = "", BOOL positionOnly = FALSE);

    protected:
        /**
        * Reads the window placement
        *@param pWP - window placement
        *@param wndName - the target window name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ReadWindowPlacement(LPWINDOWPLACEMENT pWP, const CString& wndName);

        /**
        * Writes the window placement
        *@param pWP - window placement
        *@param wndName - the target window name
        */
        virtual void WriteWindowPlacement(LPWINDOWPLACEMENT pWP, const CString& wndName);

    private:
        ZUSystemOption m_SystemOption;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_WindowConfiguration(const PSS_WindowConfiguration& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_WindowConfiguration& operator = (const PSS_WindowConfiguration& other);
};

//---------------------------------------------------------------------------
// PSS_WindowConfiguration
//---------------------------------------------------------------------------
void PSS_WindowConfiguration::SetIniFile(const CString& file)
{
    m_SystemOption.SetIniFile(file);
}
//---------------------------------------------------------------------------

#endif
