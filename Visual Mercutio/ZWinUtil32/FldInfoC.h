//## begin module%373A831303C3.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%373A831303C3.cm

//## begin module%373A831303C3.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%373A831303C3.cp

//## Module: FldInfoC%373A831303C3; Package specification
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\FldInfoC.h

#ifndef FldInfoC_h
#define FldInfoC_h 1

//## begin module%373A831303C3.additionalIncludes preserve=no
//## end module%373A831303C3.additionalIncludes

//## begin module%373A831303C3.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

//## end module%373A831303C3.includes

// FldStamp
#include "zBaseLib\FldStamp.h"
// Mfc
#include "Mfc.h"
//## begin module%373A831303C3.declarations preserve=no
//## end module%373A831303C3.declarations

//## begin module%373A831303C3.additionalDeclarations preserve=yes
#include "zBaseLib\ZIListCtrl.h"


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

//## end module%373A831303C3.additionalDeclarations


//## Class: ZCFolderInformation%373A81F402E4
//## Category: ZWinUtil library::Controls%3747C0280312
//## Subsystem: ZWinUtil%36DEE1730346
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%373A83B900AB;ZDFolderStamp { -> }

class AFX_EXT_CLASS ZCFolderInformation : public ZIListCtrl  //## Inherits: <unnamed>%373A82E10104
{
  //## begin ZCFolderInformation%373A81F402E4.initialDeclarations preserve=yes
  //## end ZCFolderInformation%373A81F402E4.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZCFolderInformation%926579193
      //	Default constructor with FolderStamp pointer.
      ZCFolderInformation (ZDFolderStamp* pFolderStamp = NULL, BOOL CanModify = FALSE);

    //## Destructor (generated)
      virtual ~ZCFolderInformation();


    //## Other Operations (specified)
      //## Operation: Initialize%926579194
      //	Initialize the control with Folder Information.
      void Initialize (ZDFolderStamp* pFolderStamp, BOOL RemoveAll = TRUE, BOOL CanModify = FALSE);

      //## Operation: Refresh%926579197
      //	Initialize the control with Folder Information.
      void Refresh ();

    // Additional Public Declarations
      //## begin ZCFolderInformation%373A81F402E4.public preserve=yes
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZCFolderInformation)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(ZCFolderInformation)
	afx_msg BOOL OnDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
      //## end ZCFolderInformation%373A81F402E4.public
  protected:
    // Additional Protected Declarations
      //## begin ZCFolderInformation%373A81F402E4.protected preserve=yes
      //## end ZCFolderInformation%373A81F402E4.protected

  private:
    //## Constructors (generated)
      ZCFolderInformation(const ZCFolderInformation &right);

    //## Assignment Operation (generated)
      const ZCFolderInformation & operator=(const ZCFolderInformation &right);

    // Data Members for Class Attributes

      //## Attribute: pFolderStamp%373A83DA0198
      //## begin ZCFolderInformation::pFolderStamp%373A83DA0198.attr preserve=no  public: ZDFolderStamp* {U} 
      ZDFolderStamp* m_pFolderStamp;
      //## end ZCFolderInformation::pFolderStamp%373A83DA0198.attr

      //## Attribute: IsColumnBuilt%37850B16020F
      //## begin ZCFolderInformation::IsColumnBuilt%37850B16020F.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_IsColumnBuilt;
      //## end ZCFolderInformation::IsColumnBuilt%37850B16020F.attr

      //## Attribute: CanModify%382682640152
      //	Determine if the control can be modified.
      //## begin ZCFolderInformation::CanModify%382682640152.attr preserve=no  private: BOOL {U} 
      BOOL m_CanModify;
      //## end ZCFolderInformation::CanModify%382682640152.attr

      //## Attribute: FolderNameTitle%38268169013D
      //	String used for titles.
      //## begin ZCFolderInformation::FolderNameTitle%38268169013D.attr preserve=no  private: CString {U} 
      CString m_FolderNameTitle;
      //## end ZCFolderInformation::FolderNameTitle%38268169013D.attr

      //## Attribute: FolderDescriptionTitle%382681900233
      //	String used for titles.
      //## begin ZCFolderInformation::FolderDescriptionTitle%382681900233.attr preserve=no  private: CString {U} 
      CString m_FolderDescriptionTitle;
      //## end ZCFolderInformation::FolderDescriptionTitle%382681900233.attr

      //## Attribute: CreationUserTitle%382681A00345
      //	String used for titles.
      //## begin ZCFolderInformation::CreationUserTitle%382681A00345.attr preserve=no  private: CString {U} 
      CString m_CreationUserTitle;
      //## end ZCFolderInformation::CreationUserTitle%382681A00345.attr

      //## Attribute: CreationDateTitle%382681B50092
      //	String used for titles.
      //## begin ZCFolderInformation::CreationDateTitle%382681B50092.attr preserve=no  private: CString {U} 
      CString m_CreationDateTitle;
      //## end ZCFolderInformation::CreationDateTitle%382681B50092.attr

      //## Attribute: PublishVersionTitle%382681C30074
      //	String used for titles.
      //## begin ZCFolderInformation::PublishVersionTitle%382681C30074.attr preserve=no  private: CString {U} 
      CString m_PublishVersionTitle;
      //## end ZCFolderInformation::PublishVersionTitle%382681C30074.attr

      //## Attribute: TypeTitle%382681D002AE
      //	String used for titles.
      //## begin ZCFolderInformation::TypeTitle%382681D002AE.attr preserve=no  private: CString {U} 
      CString m_TypeTitle;
      //## end ZCFolderInformation::TypeTitle%382681D002AE.attr

      //## Attribute: TemplateNameTitle%382681EE00DA
      //	String used for titles.
      //## begin ZCFolderInformation::TemplateNameTitle%382681EE00DA.attr preserve=no  private: CString {U} 
      CString m_TemplateNameTitle;
      //## end ZCFolderInformation::TemplateNameTitle%382681EE00DA.attr

      //## Attribute: TemplateFilenameTitle%382681FA020E
      //	String used for titles.
      //## begin ZCFolderInformation::TemplateFilenameTitle%382681FA020E.attr preserve=no  private: CString {U} 
      CString m_TemplateFilenameTitle;
      //## end ZCFolderInformation::TemplateFilenameTitle%382681FA020E.attr

    // Additional Private Declarations
      //## begin ZCFolderInformation%373A81F402E4.private preserve=yes
      //## end ZCFolderInformation%373A81F402E4.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZCFolderInformation%373A81F402E4.implementation preserve=yes
      //## end ZCFolderInformation%373A81F402E4.implementation

};

//## begin ZCFolderInformation%373A81F402E4.postscript preserve=yes
//#undef  AFX_DATA
//#define AFX_DATA
//## end ZCFolderInformation%373A81F402E4.postscript

// Class ZCFolderInformation 

//## begin module%373A831303C3.epilog preserve=yes
//## end module%373A831303C3.epilog


#endif
