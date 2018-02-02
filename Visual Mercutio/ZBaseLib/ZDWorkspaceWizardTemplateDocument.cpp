// ZDWorkspaceWizardTemplateDocument.cpp : implementation file
//

#include "stdafx.h"
#include "ZDWorkspaceWizardTemplateDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDWorkspaceWizardTemplateDocument

IMPLEMENT_DYNCREATE(ZDWorkspaceWizardTemplateDocument, CDocument)

ZDWorkspaceWizardTemplateDocument::ZDWorkspaceWizardTemplateDocument()
: m_IsLoaded(false)
{
}

BOOL ZDWorkspaceWizardTemplateDocument::OnNewDocument()
{
	ASSERT(FALSE);
	return FALSE;
/*
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
*/
}

ZDWorkspaceWizardTemplateDocument::~ZDWorkspaceWizardTemplateDocument()
{
}


bool ZDWorkspaceWizardTemplateDocument::ReadFromFile( const CString Filename )
{
	bool			RetValue = false;
	CFile			file;
	CFileException	fe;
	if (!file.Open( Filename, CFile::modeRead | CFile::shareDenyWrite, &fe ))
		return FALSE;
	CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);
	loadArchive.m_pDocument = this;
	loadArchive.m_bForceFlat = FALSE;
	TRY
	{
		Serialize( loadArchive );
		RetValue = TRUE;
	}
	CATCH( CArchiveException, e )
	{
		RetValue = FALSE;
	}
	END_CATCH

	loadArchive.Close();
	file.Close();
	// If everything is ok, set the pathname.
	if (RetValue)
		SetPathName( Filename, FALSE );
	// Set IsLoaded member
	m_IsLoaded = (RetValue) ? true : false;
	return RetValue;
}


bool ZDWorkspaceWizardTemplateDocument::SaveToFile( const CString Filename )
{
	bool			RetValue = false;
	CFile			file;
	CFileException	fe;
	if (!file.Open( Filename, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite, &fe ))
		return FALSE;
	CArchive saveArchive(&file, CArchive::store | CArchive::bNoFlushOnDelete);
	saveArchive.m_pDocument = this;
	saveArchive.m_bForceFlat = FALSE;
	TRY
	{
		Serialize( saveArchive );
		RetValue = TRUE;
	}
	CATCH( CArchiveException, e )
	{
		RetValue = FALSE;
	}
	END_CATCH

	saveArchive.Close();
	file.Close();
	return RetValue;
}


BEGIN_MESSAGE_MAP(ZDWorkspaceWizardTemplateDocument, CDocument)
	//{{AFX_MSG_MAP(ZDWorkspaceWizardTemplateDocument)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZDWorkspaceWizardTemplateDocument diagnostics

#ifdef _DEBUG
void ZDWorkspaceWizardTemplateDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void ZDWorkspaceWizardTemplateDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZDWorkspaceWizardTemplateDocument serialization

void ZDWorkspaceWizardTemplateDocument::Serialize(CArchive& ar)
{
	// Serialize the workspace template set
	m_WorkspaceTemplates.Serialize(ar);

	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// ZDWorkspaceWizardTemplateDocument commands
