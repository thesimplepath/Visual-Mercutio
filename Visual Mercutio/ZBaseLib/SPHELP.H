// sphelp.h : header file
//
#if !defined(__SPHELP_H)
#define __SPHELP_H


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#include "ZAObject.h"



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


/////////////////////////////////////////////////////////////////////////////
// SpecialHelp window

class SpecialHelp : public CWnd
{
// Construction
public:
	//SpecialHelp();
	SpecialHelp( );

// Attributes
private:
  	static CString near m_strClassName;  		// the special help window class name
// Operations
public:
	// Create function pure virtual
	virtual BOOL	Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption = FALSE ) = 0;
	BOOL	CreateSpecialHelp( CWnd *pParentWnd,  
							   CRect *rct, PlanFinObject* pObj, 
							   UINT uiRes, size_t NumberOfButton, 
							   BOOL AutoCalculateOption = FALSE );	// create the special help window
  	BOOL	DestroyWindow();  					// destroy the window
	void	SetWizardCursor();
	void	SetEmptyCursor();
	void	SetPropertyCursor();
	void	SetScenarioCursor();
	void	SetNumberCursor();
	void	SetCalendarCursor();
	void	SetNoteCursor();
	PlanFinObject* 	GetObjectPointer() const;
	size_t			GetNumberOfButton() const;
	int				GetButtonPosition(CPoint& point) const;

// Implementation
private:
	HCURSOR			m_hcurWizard;
	HCURSOR			m_hcurEmpty;
	HCURSOR			m_hcurProperty;
	HCURSOR			m_hcurScenario;
	HCURSOR			m_hcurNumber;
	HCURSOR			m_hcurCalendar;
	HCURSOR			m_hcurNote;
	CPoint			m_BitmapPoint;
	size_t			m_NumberOfButton;
	PlanFinObject* 	m_pObj;
	UINT			m_uiRes;

	BOOL			m_AutoCalculateOption;

protected:
#ifdef _WIN32
	CMonthCalCtrl*	m_pMonthCal;
#endif
	
protected:
	void OnObjectProperty(CPoint point);
	void OnAssociationMenu(CPoint point);
	void OnWizard(CPoint point);
	void OnCalendar(CPoint point);
	void OnEmpty(CPoint point);
	void OnNote(CPoint point);

	virtual void LButtonDown(UINT nFlags, CPoint point) = 0;
	virtual void MouseMove(UINT nFlags, CPoint point) = 0;

// Implementation
public:
	virtual ~SpecialHelp();

protected:
	// Generated message map functions
	//{{AFX_MSG(SpecialHelp)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LONG OnMenuSelected(UINT message, LONG wParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


inline	PlanFinObject* 	SpecialHelp::GetObjectPointer() const 
{ 
	return m_pObj; 
}

inline	size_t			SpecialHelp::GetNumberOfButton() const 
{ 
	return m_NumberOfButton; 
}

inline	int				SpecialHelp::GetButtonPosition( CPoint& point ) const 
{ 
	return point.x / ( m_BitmapPoint.x / GetNumberOfButton() );
}


inline	void	SpecialHelp::SetWizardCursor()
{
	SetCursor( m_hcurWizard );
}

inline	void	SpecialHelp::SetEmptyCursor()
{
	SetCursor( m_hcurEmpty );
}

inline	void	SpecialHelp::SetPropertyCursor()
{
	SetCursor( m_hcurProperty );
}

inline	void	SpecialHelp::SetScenarioCursor()
{
	SetCursor( m_hcurScenario );
}

inline	void	SpecialHelp::SetNumberCursor()
{
	SetCursor( m_hcurNumber );
}

inline	void	SpecialHelp::SetCalendarCursor()
{
	SetCursor( m_hcurCalendar );
}

inline	void	SpecialHelp::SetNoteCursor()
{
	SetCursor( m_hcurNote );
}


/////////////////////////////////////////////////////////////////////////////
// SpecialHelpNumber specialized window

class AFX_EXT_CLASS SpecialHelpNumber : public SpecialHelp
{
// Construction
public:
	SpecialHelpNumber();
	virtual BOOL	Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption = FALSE );	// create the special help window

// Attributes
private:
// Operations
public:

// Implementation
protected:
	virtual void LButtonDown(UINT nFlags, CPoint point);
	virtual void MouseMove(UINT nFlags, CPoint point);


protected:
	// Generated message map functions
	//{{AFX_MSG(SpecialHelpNumber)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// SpecialHelpNumberDesigner specialized window

class AFX_EXT_CLASS SpecialHelpNumberDesigner : public SpecialHelp
{
// Construction
public:
	SpecialHelpNumberDesigner();
	virtual BOOL	Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption = FALSE );	// create the special help window

// Attributes
private:
// Operations
public:

// Implementation
protected:
	virtual void LButtonDown(UINT nFlags, CPoint point);
	virtual void MouseMove(UINT nFlags, CPoint point);


protected:
	// Generated message map functions
	//{{AFX_MSG(SpecialHelpNumberDesigner)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// SpecialHelpNumberScenario specialized window

class AFX_EXT_CLASS SpecialHelpNumberScenario : public SpecialHelp
{
// Construction
public:
	SpecialHelpNumberScenario();
	virtual BOOL	Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption = FALSE );	// create the special help window

// Attributes
private:
// Operations
public:

// Implementation
protected:
	virtual void LButtonDown(UINT nFlags, CPoint point);
	virtual void MouseMove(UINT nFlags, CPoint point);


protected:
	// Generated message map functions
	//{{AFX_MSG(SpecialHelpNumberScenario)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// SpecialHelpNumberScenarioDesigner specialized window

class AFX_EXT_CLASS SpecialHelpNumberScenarioDesigner : public SpecialHelp
{
// Construction
public:
	SpecialHelpNumberScenarioDesigner();
	virtual BOOL	Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption = FALSE );	// create the special help window

// Attributes
private:
// Operations
public:

// Implementation
protected:
	virtual void LButtonDown(UINT nFlags, CPoint point);
	virtual void MouseMove(UINT nFlags, CPoint point);


protected:
	// Generated message map functions
	//{{AFX_MSG(SpecialHelpNumberScenarioDesigner)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// SpecialHelpDate specialized window

class AFX_EXT_CLASS SpecialHelpDate : public SpecialHelp
{
// Construction
public:
	SpecialHelpDate();
	virtual BOOL	Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption = FALSE );	// create the special help window

// Attributes
private:
// Operations
public:

// Implementation
protected:
	virtual void LButtonDown(UINT nFlags, CPoint point);
	virtual void MouseMove(UINT nFlags, CPoint point);


protected:
	// Generated message map functions
	//{{AFX_MSG(SpecialHelpDate)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// SpecialHelpDateDesigner specialized window

class AFX_EXT_CLASS SpecialHelpDateDesigner : public SpecialHelp
{
// Construction
public:
	SpecialHelpDateDesigner();
	virtual BOOL	Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption = FALSE );	// create the special help window

// Attributes
private:
// Operations
public:

// Implementation
protected:
	virtual void LButtonDown(UINT nFlags, CPoint point);
	virtual void MouseMove(UINT nFlags, CPoint point);


protected:
	// Generated message map functions
	//{{AFX_MSG(SpecialHelpDateDesigner)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};




/////////////////////////////////////////////////////////////////////////////
// SpecialHelpDefault specialized window

class AFX_EXT_CLASS SpecialHelpDefault : public SpecialHelp
{
// Construction
public:
	SpecialHelpDefault();
	virtual BOOL	Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption = FALSE );	// create the special help window

// Attributes
private:
// Operations
public:

// Implementation
protected:
	virtual void LButtonDown(UINT nFlags, CPoint point);
	virtual void MouseMove(UINT nFlags, CPoint point);


protected:
	// Generated message map functions
	//{{AFX_MSG(SpecialHelpDefault)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// SpecialHelpDefaultDesigner specialized window

class AFX_EXT_CLASS SpecialHelpDefaultDesigner : public SpecialHelp
{
// Construction
public:
	SpecialHelpDefaultDesigner();
	virtual BOOL	Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption = FALSE );	// create the special help window

// Attributes
private:
// Operations
public:

// Implementation
protected:
	virtual void LButtonDown(UINT nFlags, CPoint point);
	virtual void MouseMove(UINT nFlags, CPoint point);


protected:
	// Generated message map functions
	//{{AFX_MSG(SpecialHelpDefaultDesigner)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

#endif // __SPHELP_H
