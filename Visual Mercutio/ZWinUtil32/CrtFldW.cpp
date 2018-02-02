// CrtFldW.cpp: implementation of the ZICreateFolderWizard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrtFldW.h"
#include "CrtFldS.h"
#include "CrtFldE.h"

#include "opendird32.h"

// File
#include "zBaseLib\File.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZICreateFolderWizard::ZICreateFolderWizard(BOOL UseFolderNameAsFilename, CString FileDirectory, CString FileExtension, CString FolderName, CString FolderDescription)
:	m_FileDirectory(FileDirectory),
	m_FolderName(FolderName),
	m_FolderDescription(FolderDescription),
	m_FileExtension(FileExtension),
	m_UseFolderNameAsFilename(UseFolderNameAsFilename)

{

}

ZICreateFolderWizard::~ZICreateFolderWizard()
{

}



BOOL ZICreateFolderWizard::PlayWizard()
{

	ZICreateFolderWizardStart	CreateFolderWizardStart( m_UseFolderNameAsFilename, m_FileDirectory, m_FolderName, m_FolderDescription, "", m_FileExtension );

	if (CreateFolderWizardStart.DoModal() == IDCANCEL)
		return FALSE;

	// If the file directory is empty, requests the directory
	if (m_FileDirectory.IsEmpty())
	{
		ZIOpenDirDlg	OpenDirDlg( IDS_CHOOSEDIRECTORYFORFOLDER );
		m_FileDirectory = OpenDirDlg.ProcessDirectory();
		if (m_FileDirectory.IsEmpty())
			return FALSE;
	}
	
	// Check if the filename already exists
	m_FolderName = CreateFolderWizardStart.GetFolderName();
	// Create filename empty
	CString	Filename;
	if (!m_UseFolderNameAsFilename)
		Filename = CreateFolderWizardStart.GetFilename();

	ZICreateFolderWizardExist::FldExistInitialChoice	InitialChoice = ZICreateFolderWizardExist::FolderNameChoice;
	while (CheckFolderExist( Filename ) == TRUE)
	{
		if (m_UseFolderNameAsFilename)
		{
			ZICreateFolderWizardExist	CreateFolderWizardExist( m_FolderName, m_FileDirectory, m_CompleteFilename, InitialChoice );

			if (CreateFolderWizardExist.DoModal() == IDCANCEL)
				return FALSE;


			if (CreateFolderWizardExist.IsFolderNameChoosed())
			{
				// Assign the new folder name
				m_FolderName = CreateFolderWizardExist.GetFolderName();
				// Empty the filename
				Filename.Empty();
				// Keep choice for next use
				InitialChoice = ZICreateFolderWizardExist::FolderNameChoice;
			}
			else
				if (CreateFolderWizardExist.IsDirectoryChoosed())
				{
					// Assign the new directory
					m_FileDirectory = CreateFolderWizardExist.GetFileDirectory();
					// Empty the filename
					Filename.Empty();
					// Keep choice for next use
					InitialChoice = ZICreateFolderWizardExist::DirectoryChoice;
				}
				else
					if (CreateFolderWizardExist.IsFilenameChoosed())
					{
						// Assign the new filename
						Filename = CreateFolderWizardExist.GetFilename();
						// Keep choice for next use
						InitialChoice = ZICreateFolderWizardExist::FilenameChoice;
					}
					else
						if (CreateFolderWizardExist.IsReWriteChoosed())
						{
							// OK continue, break the loop
							break;
						}
		}
		else
		{
			ZICreateFolderWizardStart	CorrectCreateFolderWizardStart( m_UseFolderNameAsFilename, m_FileDirectory, m_FolderName, m_FolderDescription, Filename, m_FileExtension );

			if (CorrectCreateFolderWizardStart.DoModal() == IDCANCEL)
				return FALSE;
			// Assign the new filename
			Filename = CorrectCreateFolderWizardStart.GetFilename();

		}
	}
	return TRUE;
}



BOOL ZICreateFolderWizard::CheckFolderExist( const CString Filename )
{
	// Build the complete filename
	if (Filename.IsEmpty())
		m_CompleteFilename = m_FileDirectory + "\\" + m_FolderName + "." + m_FileExtension;
	else
		m_CompleteFilename = Filename;

	ZFile	File( m_CompleteFilename );
	return File.Exist();
}
