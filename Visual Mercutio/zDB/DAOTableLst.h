//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//	Source file: DAOTableLst.h

#ifndef DAOTableLst_h
#define DAOTableLst_h 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT




#ifdef _ZDBEXPORT
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


class AFX_EXT_CLASS ZCDAOTableList : public CListBox  
{
  public:
      ZCDAOTableList (CDaoDatabase* pDB = NULL);
      ~ZCDAOTableList();
	  CString	GetSelectedTable();
	  int		GetSelectedTables( CStringArray& Array );


      int	Initialize (CDaoDatabase* pDB);
      int	Refresh ();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZCDAOTableList)
	//}}AFX_VIRTUAL
  protected:
	//{{AFX_MSG(ZCDAOTableList)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
  private:
    ZCDAOTableList(const ZCDAOTableList &right);
    const	ZCDAOTableList & operator=(const ZCDAOTableList &right);

  private: //## implementation
	CDaoDatabase*	m_pDB;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif	// DAOTableLst_h
