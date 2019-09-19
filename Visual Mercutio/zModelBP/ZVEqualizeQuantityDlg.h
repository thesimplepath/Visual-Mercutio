#if !defined(AFX_ZVEQUALIZEQUANTITYDLG_H__0AC21D1A_6D5C_4037_BB0F_ACB29BFF4A04__INCLUDED_)
#define AFX_ZVEQUALIZEQUANTITYDLG_H__0AC21D1A_6D5C_4037_BB0F_ACB29BFF4A04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVEqualizeQuantityDlg.h : header file
//

#include "zBaseLib\PSS_NumbersEqualizer.h"
#include "zProperty\ZIProperties.h"

#include "zModelBPRes.h"


/////////////////////////////////////////////////////////////////////////////
// ZVEqualizeQuantityDlg dialog

class ZVEqualizeQuantityDlg : public CDialog
{
// Construction
public:
    ZVEqualizeQuantityDlg(ZBPropertySet* pPropertySet = NULL, CWnd* pParent = NULL);   // standard constructor

    BOOL GetLockApril() const
    {
        return m_LockApril;
    };
    BOOL GetLockAugust() const
    {
        return m_LockAugust;
    };
    BOOL GetLockDecember() const
    {
        return m_LockDecember;
    };
    BOOL    GetLockFebruary() const
    {
        return m_LockFebruary;
    };
    BOOL    GetLockJanuary() const
    {
        return m_LockJanuary;
    };
    BOOL    GetLockJuly() const
    {
        return m_LockJuly;
    };
    BOOL    GetLockJune() const
    {
        return m_LockJune;
    };
    BOOL    GetLockMarch() const
    {
        return m_LockMarch;
    };
    BOOL    GetLockMay() const
    {
        return m_LockMay;
    };
    BOOL    GetLockNovember() const
    {
        return m_LockNovember;
    };
    BOOL    GetLockOctober() const
    {
        return m_LockOctober;
    };
    BOOL    GetLockSeptember() const
    {
        return m_LockSeptember;
    };
    BOOL    GetLockYear() const
    {
        return m_LockYear;
    };

    double    GetfQuantityApril() const
    {
        bool bError;
        return m_Equalizer.GetNumberAt(g_IndexApril, bError);
    };
    double    GetfQuantityAugust() const
    {
            bool bError;
            return m_Equalizer.GetNumberAt(g_IndexAugust, bError);
    };
    double    GetfQuantityDecember() const
    {
            bool bError;
            return m_Equalizer.GetNumberAt(g_IndexDecember, bError);
    };
    double    GetfQuantityFebruary() const
    {
            bool bError;
            return m_Equalizer.GetNumberAt(g_IndexFebruary, bError);
    };
    double    GetfQuantityJanuary() const
    {
            bool bError;
            return m_Equalizer.GetNumberAt(g_IndexJanuary, bError);
    };
    double    GetfQuantityJuly() const
    {
            bool bError;
            return m_Equalizer.GetNumberAt(g_IndexJuly, bError);
    };
    double    GetfQuantityJune() const
    {
            bool bError;
            return m_Equalizer.GetNumberAt(g_IndexJune, bError);
    };
    double    GetfQuantityMarch() const
    {
            bool bError;
            return m_Equalizer.GetNumberAt(g_IndexMarch, bError);
    };
    double    GetfQuantityMay() const
    {
            bool bError;
            return m_Equalizer.GetNumberAt(g_IndexMay, bError);
    };
    double    GetfQuantityNovember() const
    {
            bool bError;
            return m_Equalizer.GetNumberAt(g_IndexNovember, bError);
    };
    double    GetfQuantityOctober() const
    {
            bool bError;
            return m_Equalizer.GetNumberAt(g_IndexOctober, bError);
    };
    double    GetfQuantitySeptember() const
    {
            bool bError;
            return m_Equalizer.GetNumberAt(g_IndexSeptember, bError);
    };
    double    GetfQuantityYear() const
    {
        return m_Equalizer.GetTotal();
    };


    BOOL    GetForceEqualizer() const
    {
        return m_ForceEqualizer;
    };

private:
// Dialog Data
    //{{AFX_DATA(ZVEqualizeQuantityDlg)
    enum { IDD = IDD_EQUALIZE_QUANTITY };
    CSliderCtrl    m_SliderSeptember;
    CSliderCtrl    m_SliderOctober;
    CSliderCtrl    m_SliderNovember;
    CSliderCtrl    m_SliderMay;
    CSliderCtrl    m_SliderMarch;
    CSliderCtrl    m_SliderJune;
    CSliderCtrl    m_SliderJuly;
    CSliderCtrl    m_SliderJanuary;
    CSliderCtrl    m_SliderFebruary;
    CSliderCtrl    m_SliderDecember;
    CSliderCtrl    m_SliderAugust;
    CSliderCtrl    m_SliderApril;
    BOOL    m_LockApril;
    BOOL    m_LockAugust;
    BOOL    m_LockDecember;
    BOOL    m_LockFebruary;
    BOOL    m_LockJanuary;
    BOOL    m_LockJuly;
    BOOL    m_LockJune;
    BOOL    m_LockMarch;
    BOOL    m_LockMay;
    BOOL    m_LockNovember;
    BOOL    m_LockOctober;
    BOOL    m_LockSeptember;
    BOOL    m_LockYear;
    CString    m_QuantityApril;
    CString    m_QuantityAugust;
    CString    m_QuantityDecember;
    CString    m_QuantityFebruary;
    CString    m_QuantityJanuary;
    CString    m_QuantityJuly;
    CString    m_QuantityJune;
    CString    m_QuantityMarch;
    CString    m_QuantityMay;
    CString    m_QuantityNovember;
    CString    m_QuantityOctober;
    CString    m_QuantitySeptember;
    CString    m_QuantityYear;
    BOOL    m_ForceEqualizer;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVEqualizeQuantityDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVEqualizeQuantityDlg)
    virtual void OnOK();
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
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    void InitializeVariables();
    void SaveVariables();
    void ApplyEqualizerToControls();
    void CheckControlState();

private:
    ZBPropertySet* m_pPropertySet;

    PSS_NumbersEqualizer m_Equalizer;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVEQUALIZEQUANTITYDLG_H__0AC21D1A_6D5C_4037_BB0F_ACB29BFF4A04__INCLUDED_)
