//*************************************************************************
//FontCombo.h

#if !defined(AFX_FONTCOMBO_H__F8528B4F_396E_11D1_9384_00A0248F6145__INCLUDED_)
#define AFX_FONTCOMBO_H__F8528B4F_396E_11D1_9384_00A0248F6145__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FontCombo.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


// BE CAREFULL
// Set the Owner draw to "Variable" and check the "Has strings". 
//


#ifdef _ZWINUTIL32EXPORT
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

///////////////////////////////////////////////////////////////////////////
//
// ZCFontComboBox window

typedef enum {FONTS} STYLE;      //Why have I enumerated, Cos, Maybe I might want something other than Fonts here


class AFX_EXT_CLASS ZCFontComboBox : public CComboBox
{
// Construction
public:
     ZCFontComboBox();
     ZCFontComboBox (STYLE);

// Attributes
public:
     void SetHilightColors (COLORREF hilight,COLORREF hilightText)
     {
          m_clrHilight = hilight;
          m_clrHilightText = hilightText;
     };
     void SetNormalColors (COLORREF clrBkgnd,COLORREF clrText)
     {
          m_clrNormalText = clrText;
          m_clrBkgnd = clrBkgnd;
     };
     BOOL SetCurrentFont( LPLOGFONT lplf );
     BOOL SetCurrentFont( LPCTSTR lpszFontName );

     static BOOL CALLBACK EnumFontProc (LPLOGFONT lplf, LPTEXTMETRIC lptm, DWORD dwType, LPARAM lpData);
     void FillFonts ();
     int  GetSelFont (LOGFONT&);


// Operations
public:

// Overrides
     // ClassWizard generated virtual function overrides
     //{{AFX_VIRTUAL(ZCFontComboBox)
     public:
     virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
     virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
     protected:
     virtual void PreSubclassWindow();
     //}}AFX_VIRTUAL

// Implementation
public:
     virtual ~ZCFontComboBox();

     // Generated message map functions
protected:
     STYLE m_enStyle;
     COLORREF m_clrHilight;
     COLORREF m_clrNormalText;
     COLORREF m_clrHilightText;
     COLORREF m_clrBkgnd;
     BOOL m_bInitOver;


     void DrawDefault (LPDRAWITEMSTRUCT);
     void DrawFont(LPDRAWITEMSTRUCT);

     void InitFonts ();
     //{{AFX_MSG(ZCFontComboBox)
     afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
     afx_msg void OnDestroy();
     //}}AFX_MSG
     afx_msg   long OnInitFonts (WPARAM, LPARAM);
     DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////////////
//

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif //!defined(AFX_FONTCOMBO_H__F8528B4F_396E_11D1_9384_00A0248F6145__INCLUDED_)



