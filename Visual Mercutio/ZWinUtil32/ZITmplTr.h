//## begin module%38B979EA003E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%38B979EA003E.cm

//## begin module%38B979EA003E.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%38B979EA003E.cp

//## Module: ZITmplTr%38B979EA003E; Package specification
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\ZITmplTr.h

#ifndef ZITmplTr_h
#define ZITmplTr_h 1

//## begin module%38B979EA003E.additionalIncludes preserve=no
//## end module%38B979EA003E.additionalIncludes

//## begin module%38B979EA003E.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\ZITreeCtl.h"
//## end module%38B979EA003E.includes

// TmplMng
#include "zBaseLib\TmplMng.h"
// Mfc
#include "Mfc.h"
//## begin module%38B979EA003E.declarations preserve=no
//## end module%38B979EA003E.declarations

//## begin module%38B979EA003E.additionalDeclarations preserve=yes
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
//## end module%38B979EA003E.additionalDeclarations


//## Class: ZITemplateTree%38B976C601E6
//	This control is automatically filled with a Template
//	manager object.
//## Category: ZWinUtil library::Controls%3747C0280312
//## Subsystem: ZWinUtil%36DEE1730346
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%38B976C601E8;ZDTemplateManager { -> }
//## Uses: <unnamed>%38B979C00337;ZITreeCtrl { -> }

class AFX_EXT_CLASS ZITemplateTree 
{
  //## begin ZITemplateTree%38B976C601E6.initialDeclarations preserve=yes
  //## end ZITemplateTree%38B976C601E6.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZITemplateTree%951679594
      ZITemplateTree (ZITreeCtrl* pTreeCtrl = NULL, ZDTemplateManager* pTemplateManager = NULL, BOOL IncludeFiles = FALSE);

    //## Destructor (generated)
      ~ZITemplateTree();


    //## Other Operations (specified)
      //## Operation: Initialize%951679595
      void Initialize (ZITreeCtrl* pTreeCtrl, ZDTemplateManager* pTemplateManager, BOOL IncludeFiles = FALSE);

      //## Operation: ReInitialize%951679596
      //	Re initialize the tree. It does not work if the tree has
      //	never been initialized.
      void ReInitialize (ZDTemplateManager* pTemplateManager, BOOL IncludeFiles = FALSE);

      //## Operation: Refresh%951679597
      //	Refresh the current tree.
      void Refresh ();

      //## Operation: AddRootItem%951679598
      //	Add the root item and returns its Handle.
      HTREEITEM AddRootItem (ZDTemplateDir* pData, int IconIndex = 0);

      //## Operation: AddSubItem%951679599
      //	Add a sub item and returns its handle.
      HTREEITEM AddSubItem (ZDTemplateDir* pData, HTREEITEM hParentTreeItem, int IconIndex = 0);

      //## Operation: AddSubItem%951679600
      //	Add a sub item and returns its handle.
      HTREEITEM AddSubItem (ZDTemplateFile* pData, HTREEITEM hParentTreeItem, int IconIndex = 0);

      //## Operation: AddFileItems%951679601
      void AddFileItems (ZDTemplateDir* pTemplateDir, HTREEITEM hParentTreeItem, int IconIndex = 0);

      //## Operation: GetNameSelectedItem%951679602
      //	Returns the selected item name.
      CString GetNameSelectedItem ();

      //## Operation: GetSelectedFolderItem%951679603
      //	Returns a pointer to the selected template directory. If
      //	no template directory selected, returns NULL.
      ZDTemplateDir* GetSelectedFolderItem ();

      //## Operation: GetSelectedFileItem%951679604
      //	Returns a pointer to the selected template file. If no
      //	template file selected, returns NULL.
      ZDTemplateFile* GetSelectedFileItem ();

      //## Operation: SelectItemName%951679605
      //	Select an item. If selected and found, returns true.
      //	Otherwise, returns false.
      BOOL SelectItemName (const CString Name);

    // Additional Public Declarations
      //## begin ZITemplateTree%38B976C601E6.public preserve=yes
      //## end ZITemplateTree%38B976C601E6.public

  protected:
    // Additional Protected Declarations
      //## begin ZITemplateTree%38B976C601E6.protected preserve=yes
      //## end ZITemplateTree%38B976C601E6.protected

  private:
    //## Constructors (generated)
      ZITemplateTree(const ZITemplateTree &right);

    //## Assignment Operation (generated)
      const ZITemplateTree & operator=(const ZITemplateTree &right);


    //## Other Operations (specified)
      //## Operation: InitializeTree%951679606
      //	Initialize the tree.
      void InitializeTree ();

    // Data Members for Class Attributes

      //## Attribute: pTemplateManager%38B976C60208
      //## begin ZITemplateTree::pTemplateManager%38B976C60208.attr preserve=no  public: ZDTemplateManager* {U} 
      ZDTemplateManager* m_pTemplateManager;
      //## end ZITemplateTree::pTemplateManager%38B976C60208.attr

      //## Attribute: IncludeFiles%38B976C60209
      //## begin ZITemplateTree::IncludeFiles%38B976C60209.attr preserve=no  public: BOOL {U} 
      BOOL m_IncludeFiles;
      //## end ZITemplateTree::IncludeFiles%38B976C60209.attr

      //## Attribute: pTreeCtrl%38B9796103E4
      //## begin ZITemplateTree::pTreeCtrl%38B9796103E4.attr preserve=no  private: ZITreeCtrl* {U} 
      ZITreeCtrl* m_pTreeCtrl;
      //## end ZITemplateTree::pTreeCtrl%38B9796103E4.attr

      //## Attribute: Invalid%38B97E060069
      //## begin ZITemplateTree::Invalid%38B97E060069.attr preserve=no  private: bool {U} 
      bool m_Invalid;
      //## end ZITemplateTree::Invalid%38B97E060069.attr

    // Additional Private Declarations
      //## begin ZITemplateTree%38B976C601E6.private preserve=yes
      //## end ZITemplateTree%38B976C601E6.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZITemplateTree%38B976C601E6.implementation preserve=yes
      //## end ZITemplateTree%38B976C601E6.implementation

};

//## begin ZITemplateTree%38B976C601E6.postscript preserve=yes
//## end ZITemplateTree%38B976C601E6.postscript

// Class ZITemplateTree 

//## begin module%38B979EA003E.epilog preserve=yes
//## end module%38B979EA003E.epilog


#endif
