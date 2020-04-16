/****************************************************************************
 * ==> PSS_UnitInfoDlg -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an unit info dialog                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UnitInfoH
#define PSS_UnitInfoH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "Resources.h"
#include "zWinUtil32\PSS_SearchEdit.h"

/**
* Unit info
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_UnitInfoDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param name - the name
        *@param directory - the diretory
        *@param showOnly - if true, the unit info will be shown only, but will not be editable
        *@param pParent - the parent window, can be NULL
        */
        PSS_UnitInfoDlg(const CString& name      = "",
                        const CString& directory = "",
                        bool           showOnly  = false,
                        CWnd*          pParent   = NULL);

        virtual ~PSS_UnitInfoDlg();

        /**
        * Gets the unit name
        *@return the unit name
        */
        virtual inline CString GetUnitName() const;

        /**
        * Gets the directory
        *@return the directory
        */
        virtual inline CString GetDirectory() const;

    protected:
        /// Generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_UnitInfoDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map
        //{{AFX_MSG(PSS_UnitInfoDlg)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog data
        */
        enum
        {
            IDD = IDD_UNIT_INFO
        };

        PSS_SearchEdit m_UnitDirectory;
        CString        m_UnitName;
        CString        m_Directory;
        bool           m_ShowOnly;
};

//---------------------------------------------------------------------------
// PSS_UnitInfoDlg
//---------------------------------------------------------------------------
CString PSS_UnitInfoDlg::GetUnitName() const
{
    return m_UnitName;
}
//---------------------------------------------------------------------------
CString PSS_UnitInfoDlg::GetDirectory() const
{
    return m_Directory;
}
//---------------------------------------------------------------------------

#endif
