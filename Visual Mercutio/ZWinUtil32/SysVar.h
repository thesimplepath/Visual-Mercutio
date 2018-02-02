//## begin module%387B026701F3.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%387B026701F3.cm

//## begin module%387B026701F3.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%387B026701F3.cp

//## Module: SysVar%387B026701F3; Package specification
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\SysVar.h

#ifndef SysVar_h
#define SysVar_h 1

//## begin module%387B026701F3.additionalIncludes preserve=no
//## end module%387B026701F3.additionalIncludes

//## begin module%387B026701F3.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%387B026701F3.includes

// ZProcess
#include "zEvent\ZProcess.h"
// ZDDoc
#include "zBaseLib\ZDDoc.h"
//## begin module%387B026701F3.declarations preserve=no
//## end module%387B026701F3.declarations

//## begin module%387B026701F3.additionalDeclarations preserve=yes
const	char szToday[] = "$$Today$$";
const	char szFilename[] = "$$Filename$$";
const	char szExchFilename[] = "$$ExchFilename$$";
const	char szProcExchFilename[] = "$$ProcExchFilename$$";
const	char szAuthor[] = "$$Author$$";
const	char szModifier[] = "$$Modifier$$";
const	char szCreationDate[] = "$$CreationDate$$";
const	char szModificationDate[] = "$$ModificationDate$$";
const	char szPublishDate[] = "$$PublishDate$$";
const	char szFileVer[] = "$$FileVer$$";



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

//## end module%387B026701F3.additionalDeclarations


//## Class: ZSystemVar%387AFE9F0147
//	This utility class converts system variables to its
//	content.
//## Category: ZWinUtil library::System variables%387AFE900145
//## Subsystem: ZWinUtil%36DEE1730346
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%387B0DD0029D;ZDDocument { -> }
//## Uses: <unnamed>%387B0DF300F9;ZProcess { -> }

class AFX_EXT_CLASS ZSystemVar 
{
  //## begin ZSystemVar%387AFE9F0147.initialDeclarations preserve=yes
  //## end ZSystemVar%387AFE9F0147.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZSystemVar%947585841
      //	Default constructor.
      ZSystemVar (ZDDocument* pDoc = NULL, ZProcess* pProcess = NULL);

    //## Destructor (generated)
      ~ZSystemVar();


    //## Other Operations (specified)
      //## Operation: Initialize%947585842
      //	Initialize the class.
      void Initialize (ZDDocument* pDoc = NULL, ZProcess* pProcess = NULL);

      //## Operation: Parse%947585843
      //	Parse the string and replace keywords with its value.
      CString Parse (CString Line);

    // Additional Public Declarations
      //## begin ZSystemVar%387AFE9F0147.public preserve=yes
      //## end ZSystemVar%387AFE9F0147.public

  protected:
    // Additional Protected Declarations
      //## begin ZSystemVar%387AFE9F0147.protected preserve=yes
      //## end ZSystemVar%387AFE9F0147.protected

  private:
    //## Constructors (generated)
      ZSystemVar(const ZSystemVar &right);

    //## Assignment Operation (generated)
      const ZSystemVar & operator=(const ZSystemVar &right);


    //## Other Operations (specified)
      //## Operation: GetVariableContent%947585844
      //	Return the variable content.
      CString GetVariableContent (const CString Variable);

      //## Operation: FindKeyword%947609381
      //	Find a keyword. If found, return the keyword and the
      //	start and end position.
      CString FindKeyword (const CString& Line, int* StartPos, int* EndPos);

    // Data Members for Class Attributes

      //## Attribute: pDoc%387B02B50367
      //## begin ZSystemVar::pDoc%387B02B50367.attr preserve=no  private: ZDDocument* {U} 
      ZDDocument* m_pDoc;
      //## end ZSystemVar::pDoc%387B02B50367.attr

      //## Attribute: pProcess%387B02E200AF
      //## begin ZSystemVar::pProcess%387B02E200AF.attr preserve=no  private: ZProcess* {U} 
      ZProcess* m_pProcess;
      //## end ZSystemVar::pProcess%387B02E200AF.attr

    // Additional Private Declarations
      //## begin ZSystemVar%387AFE9F0147.private preserve=yes
      //## end ZSystemVar%387AFE9F0147.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZSystemVar%387AFE9F0147.implementation preserve=yes
      //## end ZSystemVar%387AFE9F0147.implementation

};

//## begin ZSystemVar%387AFE9F0147.postscript preserve=yes
//## end ZSystemVar%387AFE9F0147.postscript

// Class ZSystemVar 

//## begin module%387B026701F3.epilog preserve=yes
//## end module%387B026701F3.epilog


#endif
