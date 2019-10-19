//## begin module%36DEE3DE0256.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%36DEE3DE0256.cm

//## begin module%36DEE3DE0256.cp preserve=no
//## end module%36DEE3DE0256.cp

//## Module: ZMessage%36DEE3DE0256; Package specification
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\ZMessage.h

#ifndef ZMessage_h
#define ZMessage_h 1

//## begin module%36DEE3DE0256.additionalIncludes preserve=no
//## end module%36DEE3DE0256.additionalIncludes

//## begin module%36DEE3DE0256.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "PSS_FlatButton.h"

extern AFX_EXTENSION_MODULE g_zBaseLibDLL;

#define    ID_TIMERMESSAGE 16
#define    NUMBER_OF_MESSAGE_ICON 16


//## end module%36DEE3DE0256.includes

// ZIDialog
#include "PSS_Dialog.h"
//## begin module%36DEE3DE0256.declarations preserve=no
//## end module%36DEE3DE0256.declarations

//## begin module%36DEE3DE0256.additionalDeclarations preserve=yes
//## end module%36DEE3DE0256.additionalDeclarations


//## begin ZIMessage%36DEE2420330.preface preserve=yes
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


//## end ZIMessage%36DEE2420330.preface

//## Class: ZIMessage%36DEE2420330
//## Category: ZWinUtil library%36DEE1510293
//## Subsystem: ZWinUtil%36DEE1730346
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZIMessage : public PSS_Dialog
{
public:
    //## Constructors (specified)
      //## Operation: ZIMessage%920577013
      //    Constructs a Message Window.
    ZIMessage(CWnd* pWnd = NULL);

    //## Destructor (generated)
    ~ZIMessage();


    //## Other Operations (specified)
      //## Operation: DisplayMessage%920577014
      //    Display the message
    void DisplayMessage(const CString Text, CString Title = "", UINT IDBitmap = 0);

    //## Operation: DisplayMessage%920577015
    //    Display the message
    void DisplayMessage(UINT IDText, UINT IDTitle = 0, UINT IDBitmap = 0);

    // Additional Public Declarations
      //## begin ZIMessage%36DEE2420330.public preserve=yes
      //## end ZIMessage%36DEE2420330.public

protected:
    // Additional Protected Declarations
      //## begin ZIMessage%36DEE2420330.protected preserve=yes
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(ZIMessage)
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnPaint();
    afx_msg void OnCloseWindow();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    //## end ZIMessage%36DEE2420330.protected
private:
    //## Constructors (generated)
    ZIMessage(const ZIMessage &right);

    //## Assignment Operation (generated)
    const ZIMessage & operator=(const ZIMessage &right);

    // Data Members for Class Attributes

      //## Attribute: Text%36DEE4BF0231
      //## begin ZIMessage::Text%36DEE4BF0231.attr preserve=no  public: CString {U} 
    CString m_Text;
    //## end ZIMessage::Text%36DEE4BF0231.attr

    //## Attribute: Title%36DEE4E402A3
    //## begin ZIMessage::Title%36DEE4E402A3.attr preserve=no  public: CString {U} 
    CString m_Title;
    //## end ZIMessage::Title%36DEE4E402A3.attr

    //## Attribute: IDBitmap%36DEE4F100DF
    //## begin ZIMessage::IDBitmap%36DEE4F100DF.attr preserve=no  public: UINT {U} 0
    UINT m_IDBitmap;
    //## end ZIMessage::IDBitmap%36DEE4F100DF.attr

    //## Attribute: hInst%36DEF4480140
    //## begin ZIMessage::hInst%36DEF4480140.attr preserve=no  public: HINSTANCE {U} 0
    HINSTANCE m_hInst;
    //## end ZIMessage::hInst%36DEF4480140.attr

    //## Attribute: TextFont%36DEF76E03CA
    //## begin ZIMessage::TextFont%36DEF76E03CA.attr preserve=no  public: CFont {U} 
    CFont m_TextFont;
    //## end ZIMessage::TextFont%36DEF76E03CA.attr

    //## Attribute: TitleFont%36DEF7810309
    //## begin ZIMessage::TitleFont%36DEF7810309.attr preserve=no  public: CFont {U} 
    CFont m_TitleFont;
    //## end ZIMessage::TitleFont%36DEF7810309.attr

  // Additional Private Declarations
    //## begin ZIMessage%36DEE2420330.private preserve=yes
    //## end ZIMessage%36DEE2420330.private

private: //## implementation
  // Additional Implementation Declarations
    //## begin ZIMessage%36DEE2420330.implementation preserve=yes

    void CloseWindow();

    // Dialog Data
    //{{AFX_DATA(ZIMessage)
    enum
    {
        IDD = IDD_MESSAGEDLG
    };
    PSS_FlatButton m_CloseButton;
    CStatic        m_icnApp;
    //}}AFX_DATA

    HCURSOR            m_Cursor;
    int        m_iIcon;
    UINT    m_uTimerID;
    HICON    m_pIcon[NUMBER_OF_MESSAGE_ICON];

    //## end ZIMessage%36DEE2420330.implementation
};

#endif
