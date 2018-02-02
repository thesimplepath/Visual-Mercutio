/////////////////////////////////////////////////////////////////////////////
//@doc ZAWindowConfiguration
//@module ZConfigW.h | Interface of the <c ZAWindowConfiguration> class.
//
// Advanced Dedicated Software Classes
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software,
// All rights reserved.
// Contact:
// mailto:dominique.aigroz@adsoft-form.com
// http://www.adsoft-form.com
//
// This source code is part of the zForms library.
// See these sources for detailed information regarding
// zForms libraries.
//
// Author:       Dom
// <nl>Created:		 03/2000
// <nl>Description:  ZAWindowConfiguration windows position and state configuration
//

#ifndef ZConfigW_h
#define ZConfigW_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// ZUSystemOption
#include "zBaseLib\ZUSystemOption.h"



const	char	WindowsConfigSectionName[] = "WindowsConfigValues";




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


class AFX_EXT_CLASS ZAWindowConfiguration 
{

  public:
      ZAWindowConfiguration (CString IniFile = "");
      ~ZAWindowConfiguration();


      BOOL Create (CString IniFile = "");

      //	Sets the ini file.
      void SetIniFile (const CString& File);

      //	Read the Window size, position and attribute, and saves
      //	this values.
      BOOL SaveWindowPosition (CWnd* pWnd, const CString WndName, BOOL PositionOnly = FALSE);

      //	Read saved values and restore the size, position and
      //	attributes to the Window.
      BOOL RestoreWindowPosition (CWnd* pWnd, const CString WndName, BOOL PositionOnly = FALSE);

      //	Read the desktop and saves all windows size, position
      //	and attribute, and saves these values.
      BOOL SaveWindowDesktop (CWnd* pDesktopWnd, const CString WndName = "", BOOL PositionOnly = FALSE);

      //	Read the values of desktop windows and restores it.
      BOOL RestoreWindowDesktop (CWnd* pDesktopWnd, const CString WndName = "", BOOL PositionOnly = FALSE);


  protected:
	  BOOL ReadWindowPlacement(LPWINDOWPLACEMENT pwp, const CString WndName);
	  void WriteWindowPlacement(LPWINDOWPLACEMENT pwp, const CString WndName);

  private:
      ZAWindowConfiguration(const ZAWindowConfiguration &right);
      const ZAWindowConfiguration & operator=(const ZAWindowConfiguration &right);


  private:
      ZUSystemOption m_SystemOption;


};


// Class ZAWindowConfiguration 


inline void ZAWindowConfiguration::SetIniFile (const CString& File)
{
  	m_SystemOption.SetIniFile( File );
}



#endif
