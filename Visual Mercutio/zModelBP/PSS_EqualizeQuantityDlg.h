/****************************************************************************
 * ==> PSS_EqualizeQuantityDlg ---------------------------------------------*
 ****************************************************************************
 * Description : Provides an equalize a quantity dialog box                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EqualizeQuantityDlgH
#define PSS_EqualizeQuantityDlgH

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
#include "zBaseLib\PSS_NumbersEqualizer.h"
#include "zProperty\PSS_Properties.h"

// resources
#include "zModelBPRes.h"

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Equalize a quantity dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_EqualizeQuantityDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param pPropertySet - the property set
        *@param pParent - the parent window, can be NULL
        */
        PSS_EqualizeQuantityDlg(PSS_Properties::IPropertySet* pPropertySet = NULL, CWnd* pParent = NULL);

        virtual ~PSS_EqualizeQuantityDlg();

        /**
        * Gets the quantity for the year
        *@return the quantity for the year
        */
        virtual inline double GetQuantityYear() const;

        /**
        * Gets the quantity for the month of January
        *@return the quantity for the month of January
        */
        virtual inline double GetQuantityJanuary() const;

        /**
        * Gets the quantity for the month of February
        *@return the quantity for the month of February
        */
        virtual inline double GetQuantityFebruary() const;

        /**
        * Gets the quantity for the month of March
        *@return the quantity for the month of March
        */
        virtual inline double GetQuantityMarch() const;

        /**
        * Gets the quantity for the month of April
        *@return the quantity for the month of April
        */
        virtual inline double GetQuantityApril() const;

        /**
        * Gets the quantity for the month of May
        *@return the quantity for the month of May
        */
        virtual inline double GetQuantityMay() const;

        /**
        * Gets the quantity for the month of June
        *@return the quantity for the month of June
        */
        virtual inline double GetQuantityJune() const;

        /**
        * Gets the quantity for the month of July
        *@return the quantity for the month of July
        */
        virtual inline double GetQuantityJuly() const;

        /**
        * Gets the quantity for the month of August
        *@return the quantity for the month of August
        */
        virtual inline double GetQuantityAugust() const;

        /**
        * Gets the quantity for the month of September
        *@return the quantity for the month of September
        */
        virtual inline double GetQuantitySeptember() const;

        /**
        * Gets the quantity for the month of October
        *@return the quantity for the month of October
        */
        virtual inline double GetQuantityOctober() const;

        /**
        * Gets the quantity for the month of November
        *@return the quantity for the month of November
        */
        virtual inline double GetQuantityNovember() const;

        /**
        * Gets the quantity for the month of December
        *@return the quantity for the month of December
        */
        virtual inline double GetQuantityDecember() const;

        /**
        * Gets the lock for the year
        *@return the lock for the year
        */
        virtual inline BOOL GetLockYear() const;

        /**
        * Gets the lock for the month of January
        *@return the lock for the month of January
        */
        virtual inline BOOL GetLockJanuary() const;

        /**
        * Gets the lock for the month of February
        *@return the lock for the month of February
        */
        virtual inline BOOL GetLockFebruary() const;

        /**
        * Gets the lock for the month of March
        *@return the lock for the month of March
        */
        virtual inline BOOL GetLockMarch() const;

        /**
        * Gets the lock for the month of April
        *@return the lock for the month of April
        */
        virtual inline BOOL GetLockApril() const;

        /**
        * Gets the lock for the month of May
        *@return the lock for the month of May
        */
        virtual inline BOOL GetLockMay() const;

        /**
        * Gets the lock for the month of June
        *@return the lock for the month of June
        */
        virtual inline BOOL GetLockJune() const;

        /**
        * Gets the lock for the month of July
        *@return the lock for the month of July
        */
        virtual inline BOOL GetLockJuly() const;

        /**
        * Gets the lock for the month of August
        *@return the lock for the month of August
        */
        virtual inline BOOL GetLockAugust() const;

        /**
        * Gets the lock for the month of September
        *@return the lock for the month of September
        */
        virtual inline BOOL GetLockSeptember() const;

        /**
        * Gets the lock for the month of October
        *@return the lock for the month of October
        */
        virtual inline BOOL GetLockOctober() const;

        /**
        * Gets the lock for the month of November
        *@return the lock for the month of November
        */
        virtual inline BOOL GetLockNovember() const;

        /**
        * Gets the lock for the month of December
        *@return the lock for the month of December
        */
        virtual inline BOOL GetLockDecember() const;

        /**
        * Gets if the equalizer is locked
        *@return TRUE if the equalizer is locked, otherwise FALSE
        */
        virtual inline BOOL GetForceEqualizer() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_EqualizeQuantityDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_EqualizeQuantityDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnAprActLock();
        afx_msg void OnReleasedcaptureAprActSlider(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnChangeAprActivation();
        afx_msg void OnAugActLock();
        afx_msg void OnReleasedcaptureAugActSlider(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnChangeAugActivation();
        afx_msg void OnDecActLock();
        afx_msg void OnReleasedcaptureDecActSlider(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnChangeDecActivation();
        afx_msg void OnFebActLock();
        afx_msg void OnReleasedcaptureFebActSlider(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnChangeFebActivation();
        afx_msg void OnJanActLock();
        afx_msg void OnReleasedcaptureJanActSlider(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnChangeJanActivation();
        afx_msg void OnJulActLock();
        afx_msg void OnReleasedcaptureJulActSlider(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnChangeJulActivation();
        afx_msg void OnJunActLock();
        afx_msg void OnReleasedcaptureJunActSlider(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnChangeJunActivation();
        afx_msg void OnMarActLock();
        afx_msg void OnReleasedcaptureMarActSlider(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnChangeMarActivation();
        afx_msg void OnMayActLock();
        afx_msg void OnReleasedcaptureMayActSlider(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnChangeMayActivation();
        afx_msg void OnNovActLock();
        afx_msg void OnReleasedcaptureNovActSlider(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnChangeNovActivation();
        afx_msg void OnOctActLock();
        afx_msg void OnReleasedcaptureOctActSlider(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnChangeOctActivation();
        afx_msg void OnSepActLock();
        afx_msg void OnReleasedcaptureSepActSlider(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnChangeSepActivation();
        afx_msg void OnChangeTotalActivation();
        afx_msg void OnYearActLock();
        afx_msg void OnDefault();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_EQUALIZE_QUANTITY
        };

        PSS_NumbersEqualizer          m_Equalizer;
        PSS_Properties::IPropertySet* m_pPropertySet;
        CSliderCtrl                   m_SliderJanuary;
        CSliderCtrl                   m_SliderFebruary;
        CSliderCtrl                   m_SliderMarch;
        CSliderCtrl                   m_SliderApril;
        CSliderCtrl                   m_SliderMay;
        CSliderCtrl                   m_SliderJune;
        CSliderCtrl                   m_SliderJuly;
        CSliderCtrl                   m_SliderAugust;
        CSliderCtrl                   m_SliderSeptember;
        CSliderCtrl                   m_SliderOctober;
        CSliderCtrl                   m_SliderNovember;
        CSliderCtrl                   m_SliderDecember;
        CString                       m_QuantityYear;
        CString                       m_QuantityJanuary;
        CString                       m_QuantityFebruary;
        CString                       m_QuantityMarch;
        CString                       m_QuantityApril;
        CString                       m_QuantityMay;
        CString                       m_QuantityJune;
        CString                       m_QuantityJuly;
        CString                       m_QuantityAugust;
        CString                       m_QuantitySeptember;
        CString                       m_QuantityOctober;
        CString                       m_QuantityNovember;
        CString                       m_QuantityDecember;
        BOOL                          m_LockYear;
        BOOL                          m_LockJanuary;
        BOOL                          m_LockFebruary;
        BOOL                          m_LockMarch;
        BOOL                          m_LockApril;
        BOOL                          m_LockMay;
        BOOL                          m_LockJune;
        BOOL                          m_LockJuly;
        BOOL                          m_LockAugust;
        BOOL                          m_LockSeptember;
        BOOL                          m_LockOctober;
        BOOL                          m_LockNovember;
        BOOL                          m_LockDecember;
        BOOL                          m_ForceEqualizer;

        /**
        * Initializes the variable
        */
        void InitializeVariables();

        /**
        * Saves the variables
        */
        void SaveVariables();

        /**
        * Applies the equalizers to the controls
        */
        void ApplyEqualizerToControls();

        /**
        * Checks the control state
        */
        void CheckControlState();
};

//---------------------------------------------------------------------------
// PSS_EqualizeQuantityDlg
//---------------------------------------------------------------------------
double PSS_EqualizeQuantityDlg::GetQuantityYear() const
{
    return m_Equalizer.GetTotal();
}
//---------------------------------------------------------------------------
double PSS_EqualizeQuantityDlg::GetQuantityJanuary() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexJanuary, error);
}
//---------------------------------------------------------------------------
double PSS_EqualizeQuantityDlg::GetQuantityFebruary() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexFebruary, error);
}
//---------------------------------------------------------------------------
double PSS_EqualizeQuantityDlg::GetQuantityMarch() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexMarch, error);
}
//---------------------------------------------------------------------------
double PSS_EqualizeQuantityDlg::GetQuantityApril() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexApril, error);
}
//---------------------------------------------------------------------------
double PSS_EqualizeQuantityDlg::GetQuantityMay() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexMay, error);
}
//---------------------------------------------------------------------------
double PSS_EqualizeQuantityDlg::GetQuantityJune() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexJune, error);
}
//---------------------------------------------------------------------------
double PSS_EqualizeQuantityDlg::GetQuantityJuly() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexJuly, error);
}
//---------------------------------------------------------------------------
double PSS_EqualizeQuantityDlg::GetQuantityAugust() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexAugust, error);
}
//---------------------------------------------------------------------------
double PSS_EqualizeQuantityDlg::GetQuantitySeptember() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexSeptember, error);
}
//---------------------------------------------------------------------------
double PSS_EqualizeQuantityDlg::GetQuantityOctober() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexOctober, error);
}
//---------------------------------------------------------------------------
double PSS_EqualizeQuantityDlg::GetQuantityNovember() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexNovember, error);
}
//---------------------------------------------------------------------------
double PSS_EqualizeQuantityDlg::GetQuantityDecember() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexDecember, error);
}
//---------------------------------------------------------------------------
BOOL PSS_EqualizeQuantityDlg::GetLockYear() const
{
    return m_LockYear;
}
//---------------------------------------------------------------------------
BOOL PSS_EqualizeQuantityDlg::GetLockJanuary() const
{
    return m_LockJanuary;
}
//---------------------------------------------------------------------------
BOOL PSS_EqualizeQuantityDlg::GetLockFebruary() const
{
    return m_LockFebruary;
}
//---------------------------------------------------------------------------
BOOL PSS_EqualizeQuantityDlg::GetLockMarch() const
{
    return m_LockMarch;
}
//---------------------------------------------------------------------------
BOOL PSS_EqualizeQuantityDlg::GetLockApril() const
{
    return m_LockApril;
}
//---------------------------------------------------------------------------
BOOL PSS_EqualizeQuantityDlg::GetLockMay() const
{
    return m_LockMay;
}
//---------------------------------------------------------------------------
BOOL PSS_EqualizeQuantityDlg::GetLockJune() const
{
    return m_LockJune;
}
//---------------------------------------------------------------------------
BOOL PSS_EqualizeQuantityDlg::GetLockJuly() const
{
    return m_LockJuly;
}
//---------------------------------------------------------------------------
BOOL PSS_EqualizeQuantityDlg::GetLockAugust() const
{
    return m_LockAugust;
}
//---------------------------------------------------------------------------
BOOL PSS_EqualizeQuantityDlg::GetLockSeptember() const
{
    return m_LockSeptember;
}
//---------------------------------------------------------------------------
BOOL PSS_EqualizeQuantityDlg::GetLockOctober() const
{
    return m_LockOctober;
}
//---------------------------------------------------------------------------
BOOL PSS_EqualizeQuantityDlg::GetLockNovember() const
{
    return m_LockNovember;
}
//---------------------------------------------------------------------------
BOOL PSS_EqualizeQuantityDlg::GetLockDecember() const
{
    return m_LockDecember;
}
//---------------------------------------------------------------------------
BOOL PSS_EqualizeQuantityDlg::GetForceEqualizer() const
{
    return m_ForceEqualizer;
}
//---------------------------------------------------------------------------

#endif
