/****************************************************************************
 * ==> PSS_SelectProcessWizard ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a select process Wizard                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_SELPROCW_H__B6801F55_4E39_11D3_9604_0000B45D7C6F__INCLUDED_)
#define AFX_SELPROCW_H__B6801F55_4E39_11D3_9604_0000B45D7C6F__INCLUDED_

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

// processsoft
#include "zEvent\ZProcess.h"

// resources
#ifndef _WIN32
    #include "ZWinUtilRes.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32Res.h"
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

/**
* Select process Wizard
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SelectProcessWizard
{
public:
    PSS_SelectProcessWizard( ZProcess& Process );

    virtual ~PSS_SelectProcessWizard();

    /**
    * Starts the wizard
    *@return TRUE on success, otherwise FALSE
    */
    virtual BOOL PlayWizard();

    /**
    * Gets the base activity name
    *@return the base activity name
    */
    virtual inline CString GetBaseActivityName() const;

private:
    ZProcess& m_Process;
    CString   m_BaseActivityName;
};

//---------------------------------------------------------------------------
// PSS_SelectProcessWizard
//---------------------------------------------------------------------------
CString PSS_SelectProcessWizard::GetBaseActivityName() const
{
    return m_BaseActivityName;
}
//---------------------------------------------------------------------------

#endif
