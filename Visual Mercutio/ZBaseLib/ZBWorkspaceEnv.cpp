// ZBWorkspaceEnv.cpp: implementation of the ZBWorkspaceEnv class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBWorkspaceEnv.h"

#include "PSS_File.h"
#include "ZUFileLauncher.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 18 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(ZBWorkspaceEnv, ZBWorkspaceGroupEntity, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBWorkspaceEnv::ZBWorkspaceEnv( const CString Name /*= ""*/, ZBWorkspaceEntity* pParent /*= NULL*/ )
    : ZBWorkspaceGroupEntity( Name, pParent ),
      m_bModified            ( FALSE )
{
}

ZBWorkspaceEnv::~ZBWorkspaceEnv()
{
}

void ZBWorkspaceEnv::SetOpenedFiles( CStringArray& OpenedFiles )
{
    // Clear the array
    m_OpenedFileArray.RemoveAll();

    // Copy files
    int Count = OpenedFiles.GetSize();

    for ( int i= 0; i < Count; ++i )
    {
        m_OpenedFileArray.Add( OpenedFiles.GetAt( i ) );
    }
}

void ZBWorkspaceEnv::OpenLastFiles()
{
    // Copy files
    int Count = m_OpenedFileArray.GetSize();

    for ( int i= 0; i < Count; ++i )
    {
        // Check if the file exists
        if (PSS_File::Exist( m_OpenedFileArray.GetAt( i ) ) )
        {
            ZUFileLauncher fl;

            if ( fl.Launch( m_OpenedFileArray.GetAt( i ) ) )
            {
                // Display error message
            }
        }
        else
        {
            // Display warning message
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBWorkspaceEnv diagnostics

#ifdef _DEBUG
void ZBWorkspaceEnv::AssertValid() const
{
    ZBWorkspaceGroupEntity::AssertValid();
}

void ZBWorkspaceEnv::Dump( CDumpContext& dc ) const
{
    ZBWorkspaceGroupEntity::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBWorkspaceEnv serialization

void ZBWorkspaceEnv::Serialize( CArchive& ar )
{
    ZBWorkspaceGroupEntity::Serialize( ar );

    // Serialize the opened file array
    m_OpenedFileArray.Serialize( ar );

    if ( ar.IsStoring() )
    {
        // TODO: add storing code here
        // After a save, clear the modified flag
        m_bModified = FALSE;
    }
    else
    {
        // TODO: add loading code here

        // Recalculate all parent pointers
        RecalculateParent();

        // Open files
        OpenLastFiles();
    }
}
