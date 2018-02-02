//## begin module%35D41FE6024D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%35D41FE6024D.cm

//## begin module%35D41FE6024D.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%35D41FE6024D.cp

//## Module: FileDlg%35D41FE6024D; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\FileDlg.h

#ifndef FileDlg_h
#define FileDlg_h 1

//## begin module%35D41FE6024D.additionalIncludes preserve=no
//## end module%35D41FE6024D.additionalIncludes

//## begin module%35D41FE6024D.includes preserve=yes
// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%35D41FE6024D.includes

// Mfc
#include "Mfc.h"
//## begin module%35D41FE6024D.declarations preserve=no
//## end module%35D41FE6024D.declarations

//## begin module%35D41FE6024D.additionalDeclarations preserve=yes
#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif
//## end module%35D41FE6024D.additionalDeclarations

// JMR-MODIF - Le 27 juin 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

//## Class: ZIFileDialog%35D41E3D00F7
//## Category: ZUtil library::Options & Configuration\rclasses%35D41E2C02C0
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZIFileDialog : public CFileDialog	//## Inherits: <unnamed>%35D41EA7019A
{
//## begin ZIFileDialog%35D41E3D00F7.initialDeclarations preserve=yes
//## end ZIFileDialog%35D41E3D00F7.initialDeclarations

public:

	//## Constructors (specified)
	//## Operation: ZIFileDialog%903091426
	// Constructs a filedialog.
	ZIFileDialog( const CString	Title		= _T( "" ),
				  const CString	Filter		= _T( "" ),
				  int			FilterCount	= 0,
				  const CString	InitialDir	= _T( "" ) );

	//## Operation: ZIFileDialog%918051898
	//	Constructs a filedialog.
	ZIFileDialog( UINT			nIDTitle,
				  const CString	Filter		= _T( "" ),
				  int			FilterCount	= 0,
				  const CString	InitialDir	= _T( "" ) );

	//## Destructor (generated)
	~ZIFileDialog();

	//## Other Operations (specified)
	//## Operation: DoModal%903091427
	virtual int DoModal();

	//## Operation: GetDirectory%918998216
	CString GetDirectory() const;

	//## Get and Set Operations for Class Attributes (generated)

	//## Attribute: Filename%35D41F6A00C8
	// Contains the selected filename.
	const CString GetFilename() const;

	// Additional Public Declarations
	//## begin ZIFileDialog%35D41E3D00F7.public preserve=yes
	//## end ZIFileDialog%35D41E3D00F7.public

protected:

	// Additional Protected Declarations
	//## begin ZIFileDialog%35D41E3D00F7.protected preserve=yes
	// Generated message map functions
	//{{AFX_MSG(ZIFileDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

#ifdef _WIN32
		virtual BOOL OnFileNameOK();
#endif
	//## end ZIFileDialog%35D41E3D00F7.protected

private:

	//## Constructors (generated)
	ZIFileDialog( const ZIFileDialog &right );

	//## Assignment Operation (generated)
	const ZIFileDialog & operator=( const ZIFileDialog &right );

// Data Members for Class Attributes
private:

	//## begin ZIFileDialog::Filename%35D41F6A00C8.attr preserve=no  public: CString {U}
	CString m_Filename;
	//## end ZIFileDialog::Filename%35D41F6A00C8.attr

	//## Attribute: Filter%35D41F90002C
	//## begin ZIFileDialog::Filter%35D41F90002C.attr preserve=no  private: CString {U} 
	CString m_Filter;
	//## end ZIFileDialog::Filter%35D41F90002C.attr

	//## Attribute: Title%35D41FA702BA
	//## begin ZIFileDialog::Title%35D41FA702BA.attr preserve=no  private: CString {U} 
	CString m_Title;
	//## end ZIFileDialog::Title%35D41FA702BA.attr

	//## Attribute: InitialDir%35D41FBE0296
	//## begin ZIFileDialog::InitialDir%35D41FBE0296.attr preserve=no  private: CString {U} 
	CString m_InitialDir;
	//## end ZIFileDialog::InitialDir%35D41FBE0296.attr

	//## Attribute: FilterCount%35D422E5020A
	//## begin ZIFileDialog::FilterCount%35D422E5020A.attr preserve=no  private: int {U} 
	int m_FilterCount;
	//## end ZIFileDialog::FilterCount%35D422E5020A.attr

	// Additional Private Declarations
	//## begin ZIFileDialog%35D41E3D00F7.private preserve=yes
	CString m_PathName;
	//## end ZIFileDialog%35D41E3D00F7.private
};

//## begin ZIFileDialog%35D41E3D00F7.postscript preserve=yes
//## end ZIFileDialog%35D41E3D00F7.postscript

// Class ZIFileDialog

//## Other Operations (inline)
inline CString ZIFileDialog::GetDirectory() const
{
	//## begin ZIFileDialog::GetDirectory%918998216.body preserve=yes
	return m_PathName;
	//## end ZIFileDialog::GetDirectory%918998216.body
}

//## Get and Set Operations for Class Attributes (inline)
inline const CString ZIFileDialog::GetFilename() const
{
	//## begin ZIFileDialog::GetFilename%35D41F6A00C8.get preserve=no
	return m_Filename;
	//## end ZIFileDialog::GetFilename%35D41F6A00C8.get
}

//## begin module%35D41FE6024D.epilog preserve=yes
//## end module%35D41FE6024D.epilog

#endif