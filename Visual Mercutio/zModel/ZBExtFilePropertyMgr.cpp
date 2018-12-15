// ZBExtFilePropertyMgr.cpp: implementation of the ZBExtFilePropertyMgr class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBExtFilePropertyMgr.h"

#include "ProcGraphModelMdl.h"

#include "zBaseLib\ZAGlobal.h"
#include "zBaseLib\ZBTokenizer.h"

#include "zWinUtil32\ZVReferenceFileDlg.h"

#include "zBaseLib\ZNetResourceWrapper.h"
#include "zBaseLib\TmplFile.h"
#include "zBaseLib\File.h"

#include "zModelRes.h"
#include "zRBProp.h"
#include "zFormsRes\zFormsRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 12 juin 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Static variables
static CMenu gExtFilesMenu;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBExtFilePropertyMgr::ZBExtFilePropertyMgr()
{
}

ZBExtFilePropertyMgr::~ZBExtFilePropertyMgr()
{
}

ZBExtFilePropertyMgr::ZBExtFilePropertyMgr( const ZBExtFilePropertyMgr& src )
{
    *this = src;
}

ZBExtFilePropertyMgr& ZBExtFilePropertyMgr::operator=( const ZBExtFilePropertyMgr& src )
{
    m_ExternalFiles = src.m_ExternalFiles;
    return *this;
}

bool ZBExtFilePropertyMgr::FillProperties( ZBPropertySet&    PropSet,
                                           bool                NumericValue    /*= false*/,
                                           bool                GroupValue        /*= false*/)
{    
    // If the menu is not loaded, load it
    if ( gExtFilesMenu.GetSafeHmenu() == NULL )
    {
        gExtFilesMenu.LoadMenu( IDR_EXTFILES_MENU );
    }

    // Run through all combination properties
    CString    FinalPropTitle;
    CString    PropTitle;
    CString    PropName;
    CString    PropDesc;
    size_t    Count                = GetExtFileCount();

    PropTitle.LoadString( IDS_ZS_BP_PROP_EXTFILE_TITLE );

    for ( size_t i = 0; i < Count; ++i )
    {
        FinalPropTitle.Format( _T( "%s (%d)" ), PropTitle, i + 1 );

        PropName.LoadString( IDS_Z_FILE_TITLE_NAME );
        PropDesc.LoadString( IDS_Z_FILE_TITLE_DESC );

        // Propriété "Titre lien" du groupe "Lien externe"
        ZBProperty* pCombination = new ZBProperty( FinalPropTitle,
                                                   ( GroupValue == true ) ? ZS_BP_PROP_EXTFILE : ( ZS_BP_PROP_EXTFILE + i ),
                                                   PropName,
                                                   ( GroupValue == true ) ? Z_FILE_TITLE : ( Z_FILE_TITLE + ( i * 40 ) ),
                                                   PropDesc,
                                                   GetFileTitle( i ),
                                                   ZBProperty::PT_EDIT_MENU,
                                                   true,
                                                   ZBStringFormat( ZBStringFormat::General ),
                                                   NULL,
                                                   &gExtFilesMenu );

        PropSet.Add( pCombination );

        PropName.LoadString( IDS_Z_FILE_NAME_NAME );
        PropDesc.LoadString( IDS_Z_FILE_NAME_DESC );

        // Propriété "Lien" du groupe "Lien externe"
        pCombination = new ZBProperty( FinalPropTitle,
                                       ( GroupValue == true ) ? ZS_BP_PROP_EXTFILE : ( ZS_BP_PROP_EXTFILE + i ),
                                       PropName,
                                       ( GroupValue == true ) ? Z_FILE_NAME : ( Z_FILE_NAME + ( i * 40 ) ),
                                       PropDesc,
                                       GetFilename( i ),
                                       ZBProperty::PT_EDIT_EXTENDED );

        PropSet.Add( pCombination );

        // RS-MODIF appears only if messenger activated (call to next function)
        /*
            PropName.LoadString( IDS_Z_INSERTION_TYPE_NAME );
            PropDesc.LoadString( IDS_Z_INSERTION_TYPE_DESC );

            if ( NumericValue )
            {
                pCombination = new ZBProperty( FinalPropTitle,
                                              ( GroupValue == true ) ? ZS_BP_PROP_EXTFILE : ( ZS_BP_PROP_EXTFILE + i ),
                                              PropName,
                                              ( GroupValue == true ) ? Z_INSERTION_TYPE : ( Z_INSERTION_TYPE + ( i * 40 ) ),
                                              PropDesc,
                                              (double)GetInsertionType( i ),
                                              ZBProperty::PT_EDIT_NUMBER );
            }
            else
            {
                pCombination = new ZBProperty( FinalPropTitle,
                                               ( GroupValue == true ) ? ZS_BP_PROP_EXTFILE : ( ZS_BP_PROP_EXTFILE + i ),
                                               PropName,
                                               ( GroupValue == true ) ? Z_INSERTION_TYPE : ( Z_INSERTION_TYPE + ( i * 40 ) ),
                                               PropDesc,
                                               ZAGlobal::GetInsertionTypeString( GetInsertionType( i ) ),
                                               ZBProperty::PT_COMBO_STRING_READONLY,
                                               true,
                                               ZBStringFormat( ZBStringFormat::General ),
                                               ZAGlobal::GetArrayInsertionType() );
            }

            PropSet.Add( pCombination );

            PropName.LoadString( IDS_Z_ACTIVATION_TYPE_NAME );
            PropDesc.LoadString( IDS_Z_ACTIVATION_TYPE_DESC );

            if ( NumericValue )
            {
                pCombination = new ZBProperty( FinalPropTitle,
                                               ( GroupValue == true ) ? ZS_BP_PROP_EXTFILE : ( ZS_BP_PROP_EXTFILE + i ),
                                               PropName,
                                               ( GroupValue == true ) ? Z_ACTIVATION_TYPE : ( Z_ACTIVATION_TYPE + ( i * 40 ) ),
                                               PropDesc,
                                               (double)GetActivationType( i ),
                                               ZBProperty::PT_EDIT_NUMBER );
            }
            else
            {
                pCombination = new ZBProperty( FinalPropTitle,
                                               ( GroupValue == true ) ? ZS_BP_PROP_EXTFILE : ( ZS_BP_PROP_EXTFILE + i ),
                                               PropName,
                                               ( GroupValue == true ) ? Z_ACTIVATION_TYPE : ( Z_ACTIVATION_TYPE + ( i * 40 ) ),
                                               PropDesc,
                                               ZAGlobal::GetActivationTypeString( GetActivationType( i ) ),
                                               ZBProperty::PT_COMBO_STRING_READONLY,
                                               true,
                                               ZBStringFormat( ZBStringFormat::General ),
                                               ZAGlobal::GetArrayActivationType() );
            }

            PropSet.Add( pCombination );
            */
    }

    return true;
}

// RS-MODIF 11.12.04 fill properties only for Messenger
bool ZBExtFilePropertyMgr::FillPropertiesMessenger( ZBPropertySet&    PropSet,
                                                    bool            NumericValue    /*= false*/,
                                                    bool            GroupValue        /*= false*/ )
{    
    // If the menu is not loaded, load it
    if ( gExtFilesMenu.GetSafeHmenu() == NULL )
    {
        gExtFilesMenu.LoadMenu( IDR_EXTFILES_MENU );
    }

    // Run through all combination properties
    CString    FinalPropTitle;
    CString    PropTitle;
    CString    PropName;
    CString    PropDesc;
    size_t    Count            = GetExtFileCount();

    PropTitle.LoadString( IDS_ZS_BP_PROP_EXTFILE_TITLE );

    for ( size_t i = 0; i < Count; ++i )
    {
        FinalPropTitle.Format( _T( "%s (%d)" ), PropTitle, i + 1 );

        ZBProperty* pCombination;

        PropName.LoadString( IDS_Z_INSERTION_TYPE_NAME );
        PropDesc.LoadString( IDS_Z_INSERTION_TYPE_DESC );

        // Propriété "Mode d'insertion" du groupe "Lien externe"
        if ( NumericValue )
        {
            pCombination = new ZBProperty( FinalPropTitle,
                                           ( GroupValue == true ) ? ZS_BP_PROP_EXTFILE : ( ZS_BP_PROP_EXTFILE + i ),
                                           PropName,
                                           ( GroupValue == true ) ? Z_INSERTION_TYPE : ( Z_INSERTION_TYPE + ( i * 40 ) ),
                                           PropDesc,
                                           (double)GetInsertionType( i ),
                                           ZBProperty::PT_EDIT_NUMBER );
        }
        else
        {
            pCombination = new ZBProperty( FinalPropTitle,
                                           ( GroupValue == true ) ? ZS_BP_PROP_EXTFILE : ( ZS_BP_PROP_EXTFILE + i ),
                                           PropName,
                                           ( GroupValue == true ) ? Z_INSERTION_TYPE : ( Z_INSERTION_TYPE + ( i * 40 ) ),
                                           PropDesc,
                                           ZAGlobal::GetInsertionTypeString( GetInsertionType( i ) ),
                                           ZBProperty::PT_COMBO_STRING_READONLY,
                                           true,
                                           ZBStringFormat( ZBStringFormat::General ),
                                           ZAGlobal::GetArrayInsertionType() );
        }

        PropSet.Add( pCombination );

        PropName.LoadString( IDS_Z_ACTIVATION_TYPE_NAME );
        PropDesc.LoadString( IDS_Z_ACTIVATION_TYPE_DESC );

        // Propriété "Mode d'activation" du groupe "Lien externe"
        if ( NumericValue )
        {
                pCombination = new ZBProperty( FinalPropTitle,
                                               ( GroupValue == true ) ? ZS_BP_PROP_EXTFILE : ( ZS_BP_PROP_EXTFILE + i ),
                                               PropName,
                                               ( GroupValue == true ) ? Z_ACTIVATION_TYPE : ( Z_ACTIVATION_TYPE + ( i * 40 ) ),
                                               PropDesc,
                                               (double)GetActivationType( i ),
                                               ZBProperty::PT_EDIT_NUMBER);
        }
        else
        {
                pCombination = new ZBProperty( FinalPropTitle,
                                               ( GroupValue == true ) ? ZS_BP_PROP_EXTFILE : ( ZS_BP_PROP_EXTFILE + i ),
                                               PropName,
                                               ( GroupValue == true ) ? Z_ACTIVATION_TYPE : ( Z_ACTIVATION_TYPE + ( i * 40 ) ),
                                               PropDesc,
                                               ZAGlobal::GetActivationTypeString( GetActivationType( i ) ),
                                               ZBProperty::PT_COMBO_STRING_READONLY,
                                               true,
                                               ZBStringFormat( ZBStringFormat::General ),
                                               ZAGlobal::GetArrayActivationType() );
        }

        PropSet.Add( pCombination );
    }

    return true;
}

bool ZBExtFilePropertyMgr::SaveProperties( ZBPropertySet& PropSet )
{
    // Now run through the list of data and fill the property set of external files
    ZBPropertyIterator i( &PropSet );
    ZBProperty* pProp;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->GetCategoryID() >= ZS_BP_PROP_EXTFILE &&
             pProp->GetCategoryID() <= ( ZS_BP_PROP_EXTFILE + (int)GetExtFileCount() ) )
        {
            SaveProperty( *pProp );
        }
    }

    return true;
}

bool ZBExtFilePropertyMgr::SaveProperty( ZBProperty& Property )
{
    if ( Property.GetCategoryID() >= ZS_BP_PROP_EXTFILE &&
         Property.GetCategoryID() <= ( ZS_BP_PROP_EXTFILE + (int)GetExtFileCount() ) )
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_EXTFILE;

        switch( Property.GetItemID() - ( i * 40 ) )
        {
            case Z_FILE_TITLE:
            {
                SetFileTitle( i, Property.GetValueString() );
                break;
            }

            case Z_FILE_NAME:
            {
                SetFilename( i, Property.GetValueString() );
                break;
            }

            case Z_INSERTION_TYPE:
            {
                SetInsertionType( i,  ZAGlobal::GetInsertionType( Property.GetValueString() ) );
                break;
            }

            case Z_ACTIVATION_TYPE:
            {
                SetActivationType( i,  ZAGlobal::GetActivationType( Property.GetValueString() ) );
                break;
            }
        }
    }

    return true;
}

bool ZBExtFilePropertyMgr::ProcessExtendedInput( ZBProperty&    Property,
                                                 CString&        value,
                                                 ZBPropertySet&    Properties,
                                                 bool&            Refresh )
{
    if ( Property.GetCategoryID() >= ZS_BP_PROP_EXTFILE &&
         Property.GetCategoryID() <= ( ZS_BP_PROP_EXTFILE + (int)GetExtFileCount() ) )
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_EXTFILE;

        // Call the dialog
        ZVReferenceFileDlg dlg( GetFilename( i ),
                                GetInsertionType( i ),
                                GetActivationType( i ) );

        if ( dlg.DoModal() == IDOK )
        {
            value = dlg.GetReference();
            ZFile file( dlg.GetReference() );

            if ( file.Exist() )
            {
                SetFileTitle( i, file.GetDisplayName() );
            }
            else
            {
                SetFileTitle( i, dlg.GetReference() );
            }

            SetFilename( i, dlg.GetReference() );
            SetInsertionType( i, dlg.GetInsertionType() );
            SetActivationType( i, dlg.GetActivationType() );

            Refresh = true;
            return true;
        }
    }

    return false;
}

bool ZBExtFilePropertyMgr::ProcessMenuCommand( int                MenuCommand,
                                               ZBProperty&        Property,
                                               CString&            value,
                                               ZBPropertySet&    Properties,
                                               bool&            Refresh )
{
    if ( Property.GetCategoryID() >= ZS_BP_PROP_EXTFILE &&
         Property.GetCategoryID() <= ( ZS_BP_PROP_EXTFILE + (int)GetExtFileCount() ) )
    {
        switch( MenuCommand )
        {
            case ID_ADD_NEWEXTFILE:
            {
                OnAddNewExtFile( Property, value, Properties, Refresh );
                break;
            }

            case ID_DEL_CURRENTEXTFILE:
            {
                OnDelCurrentExtFile( Property, value, Properties, Refresh );
                break;
            }

            default:
                break;
        }

        return true;
    }

    return false;
}

bool ZBExtFilePropertyMgr::DoInsertExtFile( bool DisplayDialog /*= true*/ )
{
    int Idx = AddNewExtFile();

    // Add a new external file
    if ( Idx >= 0 )
    {
        if ( DisplayDialog )
        {
            // Call the dialog
            ZVReferenceFileDlg dlg( GetFilename( Idx ),
                                    GetInsertionType( Idx ),
                                    GetActivationType( Idx ) );

            if ( dlg.DoModal() == IDOK )
            {
                ZFile file( dlg.GetReference() );

                if ( file.Exist() )
                {
                    SetFileTitle( Idx, file.GetDisplayName() );
                }
                else
                {
                    SetFileTitle( Idx, dlg.GetReference() );
                }

                SetFilename( Idx, dlg.GetReference() );
                SetInsertionType( Idx, dlg.GetInsertionType() );
                SetActivationType( Idx, dlg.GetActivationType() );
            }
        }

        return true;
    }

    return false;
}

// Drag and drop methods
bool ZBExtFilePropertyMgr::AcceptDropItem( CObject* pObj, CPoint pt )
{
    // Accept drop of file, scriptor template file and URL only
    if ( pObj && ISA( pObj, ZDTemplateFile ) ||
         ( ISA( pObj, ZNetResourceWrapper ) && !( (ZNetResourceWrapper*)pObj )->GetFilename().IsEmpty() &&
         ( (ZNetResourceWrapper*)pObj )->IsFile() ) )
    {
        // If is a template, check if we accept external file
        if ( ISA( pObj, ZDTemplateFile ) )
        {
            return true;
        }

        // If it is a file, check what kind of file
        if ( ISA( pObj, ZNetResourceWrapper ) )
        {
            // If an executable, not allowed
            ZFile file( ( (ZNetResourceWrapper*)pObj )->GetFilename() );

            if ( file.GetFileExt().CompareNoCase( _T( ".exe" ) ) == 0 ||
                 file.GetFileExt().CompareNoCase( _T( ".com" ) ) == 0 ||
                 file.GetFileExt().CompareNoCase( _T( ".bat" ) ) == 0 )
            {
                return false;
            }

            // Otherwise, ok
            return true;
        }
    }

    return false;
}

bool ZBExtFilePropertyMgr::DropItem( CObject* pObj, CPoint pt )
{
    if ( pObj && ISA( pObj, ZDTemplateFile ) ||
         ( ISA( pObj, ZNetResourceWrapper ) && !( (ZNetResourceWrapper*)pObj )->GetFilename().IsEmpty() &&
         ( (ZNetResourceWrapper*)pObj )->IsFile() ) )
    {
        // Add a new external file
        // First, check if there is an empty one.
        // If there is, use it
        int Idx = LocateFirstEmptyExtFile();

        if ( Idx == -1 )
        {
            Idx = AddNewExtFile();
        }

        // If is a template, add it
        if ( Idx >= 0 && ISA( pObj, ZDTemplateFile ) )
        {
            SetFileTitle( Idx, ( (ZDTemplateFile*)pObj )->GetTitle() );
            SetFilename( Idx, ( (ZDTemplateFile*)pObj )->GetFilename() );
            SetInsertionType( Idx, 0 );
            SetActivationType( Idx, 0 );

            return true;
        }

        // If it is a file, add it
        if ( Idx >= 0 && ISA( pObj, ZNetResourceWrapper ) )
        {
            ZFile file( ( (ZNetResourceWrapper*)pObj )->GetFilename() );

            if ( file.Exist() )
            {
                SetFileTitle( Idx, file.GetDisplayName() );
            }
            else
            {
                SetFileTitle( Idx, ( (ZNetResourceWrapper*)pObj )->GetFilename() );
            }

            SetFilename( Idx, ( (ZNetResourceWrapper*)pObj )->GetFilename() );
            SetInsertionType( Idx, 0 );
            SetActivationType( Idx, 0 );

            return true;
        }
    }

    return false;
}

void ZBExtFilePropertyMgr::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        // Before storing elements,
        // removes all empty elements
        RemoveAllEmptyExtFiles();
    }

    m_ExternalFiles.Serialize( ar );
}
