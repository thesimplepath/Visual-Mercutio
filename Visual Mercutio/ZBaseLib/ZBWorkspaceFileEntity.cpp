// ZBWorkspaceFileEntity.cpp: implementation of the ZBWorkspaceFileEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBWorkspaceFileEntity.h"

#include "ZBWorkspaceGroupEntity.h"
#include "ZVWorkspaceFileProperties.h"

#include "ZUFileLauncher.h"

#include "PSS_FileDialog.h"

#include "zBaseLibRes.h"
#include "PSS_MsgBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 18 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(ZBWorkspaceFileEntity, ZBWorkspaceEntity, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBWorkspaceFileEntity::ZBWorkspaceFileEntity( const CString Name /*= ""*/, ZBWorkspaceEntity* pParent /*= NULL*/ )
    : ZBWorkspaceEntity( Name, pParent )
{
    m_File.SetCompleteFileName( Name );
    SetEntityName( m_File.GetFileTitle() + m_File.GetFileExt() );
}

ZBWorkspaceFileEntity::~ZBWorkspaceFileEntity()
{
}

HICON ZBWorkspaceFileEntity::GetFilenameIcon() const
{
    int IconIndex = const_cast<PSS_File&>( m_File ).GetIconIndex();

    if ( IconIndex < 0 )
    {
        return NULL;
    }

    return ::ExtractIcon( ::AfxGetInstanceHandle(), GetFilename(), IconIndex );
}

// Cette fonction est appelée lorsqu'un fichier associé au projet doit être ouvert.
bool ZBWorkspaceFileEntity::OpenFile()
{
    if ( !m_File.Exist() )
    {
        PSS_MsgBox mBox;

        if ( mBox.ShowMsgBox( IDS_WKS_FILENAME_DEXIST, MB_YESNO ) == IDYES )
        {
            CString title;
            VERIFY( title.LoadString( IDS_WORKSPACE_FILESELECT_T ) );

            // Set the "*.*" files filter
            CString strFilter;
            VERIFY( strFilter.LoadString( AFX_IDS_ALLFILTER ) );

            strFilter += (char)'\0';            // Next string please
            strFilter += _T( "*.*" );
            strFilter += (char)'\0';            // Last string

            PSS_FileDialog fileDialog( title, strFilter, 1 );

            if ( fileDialog.DoModal() == IDOK )
            {
                // Assigns the new file name
                m_File.SetCompleteFileName( fileDialog.GetFileName() );
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    // Launch the file
    ZUFileLauncher fl;

    return ( fl.Launch( m_File.GetCompleteFileName() ) == TRUE ) ? true : false;
}

bool ZBWorkspaceFileEntity::DisplayProperties()
{
    ZVWorkspaceFileProperties dlg( ( GetParent() && ISA( GetParent(), ZBWorkspaceGroupEntity ) ) ? dynamic_cast<ZBWorkspaceGroupEntity*>( GetParent() ) : NULL,
                                   GetEntityName(),
                                   GetFilename() );

    if ( dlg.DoModal() == IDOK )
    {
        SetEntityName( dlg.GetFileTitle() );
        SetFilename( dlg.GetFilename() );
        return true;
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////
// ZBWorkspaceFileEntity diagnostics

#ifdef _DEBUG
void ZBWorkspaceFileEntity::AssertValid() const
{
    ZBWorkspaceEntity::AssertValid();
}

void ZBWorkspaceFileEntity::Dump( CDumpContext& dc ) const
{
    ZBWorkspaceEntity::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBWorkspaceFileEntity serialization

void ZBWorkspaceFileEntity::Serialize ( CArchive& ar )
{
    ZBWorkspaceEntity::Serialize( ar );

    if ( ar.IsStoring() )
    {
        // Write the elements
        ar << m_File;
    }
    else
    {
        // Read the elements
        ar >> m_File;
    }
}
