// ZBGenericGridReportGenerator.h: interface for the ZBGenericGridReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBGENERICGRIDREPORTGENERATOR_H__9F9F4F11_EC1C_46C8_9324_965098AC7702__INCLUDED_)
#define AFX_ZBGENERICGRIDREPORTGENERATOR_H__9F9F4F11_EC1C_46C8_9324_965098AC7702__INCLUDED_

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

// processsoft
#include "zBaseLib\PSS_Date.h"
#include "ZIGridReportGenerator.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZDGridDocument;

#ifdef _ZREPORTEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBGenericGridReportGenerator : public CObject, public ZIGridReportGenerator
{
    DECLARE_SERIAL( ZBGenericGridReportGenerator )

public:

    ZBGenericGridReportGenerator( ZDGridDocument* pDoc = NULL );
    virtual ~ZBGenericGridReportGenerator();

    // Return the document and the associated document template pointer
    virtual ZDGridDocument* GetDocument() const
    {
        return m_pDoc;
    };

    virtual void SetDocument( ZDGridDocument* pDoc )
    {
        m_pDoc = pDoc;
    };

    virtual CDocTemplate* GetDocTemplate() const;

    /////////////////////////////////////////////////////////////////////////////
    // ZIGridReportGenerator methods
    
    // Initialization method
    virtual bool Initialize()
    {
        return true;
    };

    // Returns the number of tabs
    virtual size_t GetGeneratorTabCount() const
    {
        return 1;
    };

    // Returns the tab name corresponding to the index
    virtual const CString GetGeneratorTabName( size_t Index )
    {
        return _T( "Tab 1" );
    };

    // Called by the framework to request a grid param to be filled
    // The implementation uses the delegation
    virtual bool FillGrid( CGXGridCore& GridCore, size_t Index )
    {
        return true;
    };

    virtual void SetReportTypeID( int TypeID )
    {
        m_TypeID = TypeID;
    };

    virtual int GetReportTypeID() const
    {
        return m_TypeID;
    };

    virtual const CString GetReportTitle() const
    {
        return _T( "" );
    };

    virtual bool IsReportDataExternal() const
    {
        return true;
    };

    virtual bool ReportDataMustBeReloaded() const
    {
        return (PSS_Date::GetToday() > m_LastUpdateDateTime ) ? true : false;
    };

    virtual bool UseAutomaticReload() const
    {
        return true;
    };

    // Call-back methods
    virtual void OnPreDataFilled( size_t Index )
    {
    };

    virtual void OnPostDataFilled( size_t Index );

    // Serialization call-back
    virtual void OnPostRead( CArchive& ar )
    {
    };

    virtual void OnPostWrite( CArchive& ar )
    {
    };

    // Serialization
    virtual void Serialize( CArchive& ar );

// Implementation
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

protected:

    ZDGridDocument*    m_pDoc;
    CString            m_Filename;
    int                m_TypeID;
    PSS_Date           m_LastUpdateDateTime;
};

#endif // !defined(AFX_ZBGENERICGRIDREPORTGENERATOR_H__9F9F4F11_EC1C_46C8_9324_965098AC7702__INCLUDED_)