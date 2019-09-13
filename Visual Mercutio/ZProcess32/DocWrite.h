//## begin module%35CC45530279.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%35CC45530279.cm

//## begin module%35CC45530279.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%35CC45530279.cp

//## Module: DocWrite%35CC45530279; Package specification
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\ZDesigner\DocWrite.h

#ifndef DocWrite_h
#define DocWrite_h 1

// ZDDocument
#include "zBaseLib\ZDDoc.h"

// JMR-MODIF - Le 11 mai 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Class ZDDocumentReadWrite

class ZDDocumentReadWrite : public ZDDocument
{
    DECLARE_SERIAL( ZDDocumentReadWrite )

//## begin ZDDocumentReadWrite%35CC443703C5.initialDeclarations preserve=yes
public:

    // Inherited feature
    typedef ZDDocument inherited;
//## end ZDDocumentReadWrite%35CC443703C5.initialDeclarations

public:

    //## Destructor (generated)
    virtual ~ZDDocumentReadWrite();

    BOOL DeletePage( int iPage, int DocumentIndex = -1 );

    BOOL CopyPage( ZDDocumentReadWrite*    pDocumentDst,
                   int                    iPage,
                   int                    DocumentIndexSource    = -1,
                   int                    DocumentIndexDest    = -1 );

    BOOL CopyPageOnlyObjects( ZDDocumentReadWrite*    pDocumentDst,
                              int                    iPage,
                              int                    DocumentIndexSource    = -1,
                              int                    DocumentIndexDest    = -1 );

    BOOL CopyPageOnlyFormula( ZDDocumentReadWrite*    pDocumentDst,
                              int                    iPage,
                              int                    DocumentIndexSource    = -1,
                              int                    DocumentIndexDest    = -1 );

    void MoveContents( ZDDocumentReadWrite*    pDocument,
                       BOOL                    bCopyFormat,
                       int                    DocumentIndexSource    = -1,
                       int                    DocumentIndexDest    = -1 );

    void SetCurrentStyle( const CString& sName, int DocumentIndex = -1 );
    void StyleHasBeenDeleted( PSS_Style::Handle hStyle, int DocumentIndex = -1 );

public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

protected:

    //## Constructors (generated)
    ZDDocumentReadWrite();

    BOOL BuildTemplateName( CString& str );

    // Data Members for Class Attributes

    //## Attribute: strEdit%38063C50002C
    //    Points to the Edit control.
    //## begin ZDDocumentReadWrite::strEdit%38063C50002C.attr preserve=no  protected: Edit* {U} 
    //## end ZDDocumentReadWrite::strEdit%38063C50002C.attr

    // Additional Protected Declarations
    //## begin ZDDocumentReadWrite%35CC443703C5.protected preserve=yes
    //{{AFX_MSG(ZDDocumentReadWrite)
    afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
    afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
    afx_msg void OnImport();
    afx_msg void OnExport();
    afx_msg void OnFileOptions();
    afx_msg void OnFileProperty();
    afx_msg void OnFileSave();
    afx_msg void OnFileSaveAs();
    afx_msg void OnFormulaScenarioAssociate();
    afx_msg void OnFormulaScenarioCopy();
    afx_msg void OnFormulaScenarioCreation();
    afx_msg void OnFormulaScenarioDelete();
    afx_msg void OnDefineStyle();
    afx_msg void OnChangeStyle();
    afx_msg void OnInsertNewPage();
    afx_msg void OnFormAttach();
    afx_msg void OnPageDelete();
    afx_msg void OnFormManage();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    virtual BOOL OnNewDocument();
    virtual BOOL OnOpenDocument( const char* pszPathName );
    virtual BOOL SaveModified();
    virtual BOOL OnSaveDocument( const char* pszPathName );

    //## end ZDDocumentReadWrite%35CC443703C5.protected

private:

    //## Constructors (generated)
    ZDDocumentReadWrite( const ZDDocumentReadWrite &right );

    //## Assignment Operation (generated)
    const ZDDocumentReadWrite & operator=( const ZDDocumentReadWrite &right );

    //## Other Operations (specified)

    // Additional Private Declarations
    //## begin ZDDocumentReadWrite%35CC443703C5.private preserve=yes
    //## end ZDDocumentReadWrite%35CC443703C5.private

//## implementation
private:

    // Additional Implementation Declarations
    //## begin ZDDocumentReadWrite%35CC443703C5.implementation preserve=yes
    //## end ZDDocumentReadWrite%35CC443703C5.implementation
};

//## begin ZDDocumentReadWrite%35CC443703C5.postscript preserve=yes
//## end ZDDocumentReadWrite%35CC443703C5.postscript

//## begin module%35CC45530279.epilog preserve=yes
//## end module%35CC45530279.epilog

#endif