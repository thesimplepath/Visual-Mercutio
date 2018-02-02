// ZIGridReportGenerator.h: interface for the ZIGridReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZIGRIDREPORTGENERATOR_H__C9F88B98_024B_4CC6_B5E1_E9FD65970C95__INCLUDED_)
#define AFX_ZIGRIDREPORTGENERATOR_H__C9F88B98_024B_4CC6_B5E1_E9FD65970C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZREPORTEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 7 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZIGridReportGenerator
{
public:

	ZIGridReportGenerator();
	virtual ~ZIGridReportGenerator();

	// Initialization method
	virtual bool Initialize() = 0;

	// Returns the number of tabs
	virtual size_t GetGeneratorTabCount() const = 0;

	// Returns the tab name corresponding to the index
	virtual const CString GetGeneratorTabName( size_t Index ) = 0;

	// Fills the grid objects passes as parameters for a given index.
	// If fails, returns false
	// Called by the grid MVC framework when necessary to fill the tab
	virtual bool FillGrid( CGXGridCore& GridCore, size_t Index ) = 0;

	// Report identifier methods
	virtual void SetReportTypeID( int TypeID ) = 0;
	virtual int GetReportTypeID() const = 0;
	virtual const CString GetReportTitle() const = 0;

	// Refresh document methods
	virtual bool IsReportDataExternal() const = 0;
	virtual bool ReportDataMustBeReloaded() const = 0;
	virtual bool UseAutomaticReload() const = 0;

	// Call-back methods
	virtual void OnPreDataFilled( size_t Index ) = 0;
	virtual void OnPostDataFilled( size_t Index ) = 0;
};

#endif // !defined(AFX_ZIGRIDREPORTGENERATOR_H__C9F88B98_024B_4CC6_B5E1_E9FD65970C95__INCLUDED_)