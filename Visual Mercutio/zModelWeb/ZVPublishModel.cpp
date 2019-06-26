// ZVPublishModel.cpp : implementation file.

#include <StdAfx.h>

// ZVPublishModel
#include "ZVPublishModel.h"

#include "ZVPublishModelWelcome.h"
#include "ZVPublishModelSelDir.h"
#include "ZVPublishModelBanner.h"
#include "ZVPublishModelAttributes.h"
#include "ZVPublishModelOptions.h"

#include "zBaseLib\ZUSystemOption.h"

// RS-MODIF 12.12.04 we need token to save attributes
#include "zBaseLib\ZBTokenizer.h"
#include "zProperty\zBPropertyAttributes.h"

// JMR-MODIF - Le 27 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// **************************************************************************************************************
// * JMR-MODIF - Le 4 juillet 2005 - Supprimé l'option de publication HTML en chemin relatif ou absolu. Ajouté    *
// * l'option de publication du rapport Conceptor.                                                                *
// **************************************************************************************************************

// **************************************************************************************************************
// * JMR-MODIF - Le 6 mars 2006 - Ajouté l'option de publication du rapport processus.                            *
// **************************************************************************************************************

// **************************************************************************************************************
// * JMR-MODIF - Le 16 janvier 2007 - Ajouté l'option de publication du livre des règles.                        *
// **************************************************************************************************************

//////////////////////////////////////////////////////////////////////
// Global definitions

const CString gPublishModelHTMLSectionName                    = _T( "PublishModelToHTML" );
const CString gPublishModelHTMLAddressEntityName            = _T( "PublishAddress" );
const CString gPublishModelHTMLLastLanguageEntityName        = _T( "LastPublishLanguage" );
const CString gPublishModelHTMLPublishConceptor                = _T( "PublishConceptor" );
const CString gPublishModelHTMLPublishConceptorDetails        = _T( "PublishConceptorDetails" );
const CString gPublishModelHTMLPublishConceptorDeliverables    = _T( "PublishConceptorDeliverables" );
const CString gPublishModelHTMLPublishProcess                = _T( "PublishProcess" );
const CString gPublishModelHTMLPublishRuleBook                = _T( "PublishRuleBook" );
const CString gPublishModelHTMLVisualizeEntityName            = _T( "Visualize" );
const CString gPublishModelHTMLLogoFilenameEntityName        = _T( "LogoFilename" );
const CString gPublishModelHTMLLogoRefHTMLEntityName        = _T( "LogoRef" );

ZVPublishModel::ZVPublishModel( ZBPropertyAttributes*    pAttributes    /*= NULL*/,
                                ZBPropertySet*            pSet        /*= NULL*/,
                                const CString            IniFile        /*= ""*/ )
    : m_IniFile            ( IniFile ),
      m_pPropAttributes    ( pAttributes ),
      m_pPropSet        ( pSet )
{
}

ZVPublishModel::~ZVPublishModel()
{
}

BOOL ZVPublishModel::Choose()
{
    ZVPublishModelWelcome Welcome;

    if ( Welcome.DoModal() == IDCANCEL )
    {
        return FALSE;
    }

    // Load the last state
    LoadStateFromIniFile();

    // RS-MODIF load attributes
    LoadAttributesFromIniFile();

    ZVPublishModelSelectDirectory Select( m_Directory, &m_ArrayOfAddress );

    if ( Select.DoModal() == IDCANCEL )
    {
        return FALSE;
    }

    // No directory selected
    if ( Select.GetDirectory().IsEmpty() )
    {
        return FALSE;
    }

    m_Directory = Select.GetDirectory();

    ZVPublishModelBanner Banner( m_HyperLink, m_ImageFilename );

    if ( Banner.DoModal() == IDCANCEL )
    {
        return FALSE;
    }

    m_ImageFilename    = Banner.GetImageFilename();
    m_HyperLink        = Banner.GetHyperLink();

    CWaitCursor cursor;

    ZVPublishModelAttributes Attributes( m_pPropAttributes, m_pPropSet );

    if ( Attributes.DoModal() == IDCANCEL )
    {
        return FALSE;
    }

    ZVPublishModelOptions Options( m_VisualizeResult,
                                   m_PublishConceptor,
                                   m_PublishConceptorDetails,
                                   m_PublishConceptorDeliverables,
                                   m_PublishProcess,
                                   m_PublishRuleBook,
                                   m_Language );

    if ( Options.DoModal() == IDCANCEL )
    {
        return FALSE;
    }

    // JMR-MODIF - Le 6 juillet 2005 - Ajout des options pour le rapport Conceptor.
    // JMR-MODIF - Le 2 mars 2006 - Ajout des options pour le rapport processus.
    // JMR-MODIF - Le 14 janvier 2007 - Ajout des options pour le livre des règles.
    m_VisualizeResult                = ( Options.GetVisualize() )                    ? true : false;
    m_PublishConceptor                = ( Options.GetPublishConceptor() )                ? true : false;
    m_PublishConceptorDetails        = ( Options.GetPublishConceptorDetails() )        ? true : false;
    m_PublishConceptorDeliverables    = ( Options.GetPublishConceptorDeliverables() )    ? true : false;
    m_PublishProcess                = ( Options.GetPublishProcess() )                ? true : false;
    m_PublishRuleBook                = ( Options.GetPublishRuleBook() )                ? true : false;
    m_Language                        = Options.GetLanguage();

    // Saves the state
    SaveStateToIniFile();

    // RS-MODIF 12.12.04 save attributes also
    SaveAttributesToIniFile();

    return TRUE;
}

bool ZVPublishModel::LoadStateFromIniFile()
{
    ZUSystemOption SystemOption( m_IniFile, gPublishModelHTMLSectionName );

    // JMR-MODIF - Le 6 juillet 2005 - Ajout des options pour le rapport Conceptor.
    // JMR-MODIF - Le 2 mars 2006 - Ajout des options pour le rapport processus.
    // JMR-MODIF - Le 14 janvier 2007 - Ajout des options pour le livre des règles.
    // Read the options
    m_PublishConceptor                = SystemOption.ReadOption( gPublishModelHTMLPublishConceptor,                true );
    m_PublishConceptorDetails        = SystemOption.ReadOption( gPublishModelHTMLPublishConceptorDetails,        true );
    m_PublishConceptorDeliverables    = SystemOption.ReadOption( gPublishModelHTMLPublishConceptorDeliverables,    true );
    m_PublishProcess                = SystemOption.ReadOption( gPublishModelHTMLPublishProcess,                    true );
    m_PublishRuleBook                = SystemOption.ReadOption( gPublishModelHTMLPublishRuleBook,                true );
    m_VisualizeResult                = SystemOption.ReadOption( gPublishModelHTMLVisualizeEntityName,            true );

    m_Language                        = static_cast<Language>( SystemOption.ReadOption( gPublishModelHTMLLastLanguageEntityName, 0 ) );

    m_Directory                        = SystemOption.ReadOption( gPublishModelHTMLAddressEntityName,        _T( "" ) );
    m_ImageFilename                    = SystemOption.ReadOption( gPublishModelHTMLLogoFilenameEntityName,    _T( "" ) );
    m_HyperLink                        = SystemOption.ReadOption( gPublishModelHTMLLogoRefHTMLEntityName,    _T( "" ) );

    CString KeyName;
    CString Addr;
    size_t Idx = 0;

    // Remove all elements
    m_ArrayOfAddress.RemoveAll();

    do
    {
        // Format the key
        KeyName.Format( _T( "%s_%d" ), (const char*)gPublishModelHTMLAddressEntityName, Idx );
        Addr = SystemOption.ReadOption( KeyName, _T( "" ) );

        if ( Addr.IsEmpty() )
        {
            break;
        }

        // Add element to the table
        m_ArrayOfAddress.Add( Addr );

        ++Idx;
    }
    while ( Idx < 1000 );    // Sets the maximum loop at thousand objects
                            // which is big already

    return true;
}
//---------------------------------------------------------------------------
bool ZVPublishModel::SaveStateToIniFile()
{
    ZUSystemOption SystemOption(m_IniFile, gPublishModelHTMLSectionName);

    // JMR-MODIF - Le 6 juillet 2005 - Ajout des options pour le rapport Conceptor.
    // JMR-MODIF - Le 2 mars 2006 - Ajout des options pour le rapport processus.
    // JMR-MODIF - Le 14 janvier 2007 - Ajout des options pour le livre des règles.
    // Saves the options
    SystemOption.WriteOption( gPublishModelHTMLPublishConceptor,             m_PublishConceptor );
    SystemOption.WriteOption( gPublishModelHTMLPublishConceptorDetails,      m_PublishConceptorDetails );
    SystemOption.WriteOption( gPublishModelHTMLPublishConceptorDeliverables, m_PublishConceptorDeliverables );
    SystemOption.WriteOption( gPublishModelHTMLPublishProcess,               m_PublishProcess );
    SystemOption.WriteOption( gPublishModelHTMLPublishRuleBook,              m_PublishRuleBook );
    SystemOption.WriteOption( gPublishModelHTMLVisualizeEntityName,          m_VisualizeResult );
    SystemOption.WriteOption( gPublishModelHTMLLastLanguageEntityName,       m_Language );
    SystemOption.WriteOption( gPublishModelHTMLAddressEntityName,            m_Directory );
    SystemOption.WriteOption( gPublishModelHTMLLogoFilenameEntityName,       m_ImageFilename );
    SystemOption.WriteOption( gPublishModelHTMLLogoRefHTMLEntityName,        m_HyperLink );

    CString keyName;

    // Add the address to the array
    bool found = false;

    for (int idx = 0; idx < m_ArrayOfAddress.GetSize(); ++idx)
        if (m_ArrayOfAddress.GetAt(idx) == m_Directory)
            found = true;

    if (!found)
        m_ArrayOfAddress.Add(m_Directory);

    for (int idx = 0; idx < m_ArrayOfAddress.GetSize(); ++idx)
    {
        // format the key
        keyName.Format(_T("%s_%d"), (const char*)gPublishModelHTMLAddressEntityName, idx);

        // write the string to the ini file
        SystemOption.WriteOption(keyName, m_ArrayOfAddress.GetAt(idx));
    }

    return true;
}
//---------------------------------------------------------------------------
// RS-MODIF 12.12.04 save attributes to ini file
bool ZVPublishModel::SaveAttributesToIniFile()
{
    CString EntityName = _T( "_PropertyDefaultAttributeSaveStateWeb" );
    
    ZUSystemOption    SystemOption( m_IniFile, EntityName );

    // we need to delete all records before saving
    DeleteAttributesFromIniFile();

    size_t Idx = 0;
    CString KeyName;

    ZBPropertyAttributes* pPropTemp = GetPropAttributes();
    
    _ZBPropertyAttributeIterator i( &( pPropTemp->GetAttributeSet() ) );

    for ( _ZBPropertyAttribute* pAtt = i.GetFirst(); pAtt != NULL; pAtt = i.GetNext(), ++Idx )
    {
        // Format the key
        KeyName.Format( _T( "%s%d" ), _T( "_PropertyDefaultAttributeSaveStateWeb" ), Idx );
        ZBTokenizer token;

        // Build the string
        token.AddToken( pAtt->GetCategoryID() );
        token.AddToken( pAtt->GetItemID() );

        // Write the string to the ini file
        SystemOption.WriteOption( KeyName, token.GetString() );
    }

    return true;
}

// RS-MODIF 12.12.04 remove attributes before loading
void ZVPublishModel::RemoveAllAttributes()
{
    ZBPropertyAttributes* pPropTemp = GetPropAttributes();
    
    _ZBPropertyAttributeIterator i( &( pPropTemp->GetAttributeSet() ) );

    for ( _ZBPropertyAttribute* pAtt = i.GetFirst(); pAtt != NULL; pAtt = i.GetNext() )
    {
        delete pAtt;
    }

    ( pPropTemp->GetAttributeSet() ).RemoveAll();
}

// RS-MODIF 12.12.04 add attributes function
void ZVPublishModel::AddAttribute( _ZBPropertyAttribute* pAttribute )
{
    ZBPropertyAttributes* pPropTemp = GetPropAttributes();

    if ( pAttribute )
    {
        if ( !FindAttribute( pAttribute->GetCategoryID(), pAttribute->GetItemID() ) )
        {
            ( pPropTemp->GetAttributeSet() ).Add( pAttribute );
        }
        else
        {
            // Otherwise, delete the attribute
            delete pAttribute;
        }
    }
}

// RS-MODIF 12.12.04 find attributes function
_ZBPropertyAttribute* ZVPublishModel::FindAttribute( int CategoryID, int ItemID )
{
    ZBPropertyAttributes* pPropTemp = GetPropAttributes();
    
    _ZBPropertyAttributeIterator i( &( pPropTemp->GetAttributeSet() ) );

    for ( _ZBPropertyAttribute* pAtt = i.GetFirst(); pAtt != NULL; pAtt = i.GetNext() )
    {
        if ( pAtt->GetCategoryID() == CategoryID && pAtt->GetItemID() == ItemID )
        {
            return pAtt;
        }
    }

    return NULL;
}

// RS-MODIF 12.12.04 load attributes from ini file
bool ZVPublishModel::LoadAttributesFromIniFile()
{
    // First, delete all attributes
    RemoveAllAttributes();

    CString EntityName = _T( "_PropertyDefaultAttributeSaveStateWeb" );
    
    ZUSystemOption SystemOption( m_IniFile, EntityName );

    CString KeyName;
    CString Line;
    size_t Idx = 0;

    do
    {
        // Format the key
        KeyName.Format( _T( "%s%d" ), _T( "_PropertyDefaultAttributeSaveStateWeb" ), Idx );
        Line = SystemOption.ReadOption( KeyName, _T( "" ) );

        if ( Line.IsEmpty() )
        {
            break;
        }

        ++Idx;

        CString str;
        ZBTokenizer token;

        // Extract the category ID
        str = token.GetFirstToken( Line );

        if ( str.IsEmpty() )
        {
            continue;
        }

        int CategoryID = atoi( (const char*)str );

        // Extract the item ID
        str = token.GetNextToken();

        if ( str.IsEmpty() )
        {
            continue;
        }

        int ItemID = atoi( (const char*)str );


        // If we are here, all objects have been extracted
        // Create the object state
        _ZBPropertyAttribute* pAtt = new _ZBPropertyAttribute( CategoryID, ItemID );

        // Add it to the array of value
        AddAttribute( pAtt );
    }
    while ( Idx < 1000000 );    // Sets the maximum loop at 1 million objects
                                // which is big already

    return true;
}

// RS-MODIF 12.12.04 delete all attributes from ini file
bool ZVPublishModel::DeleteAttributesFromIniFile()
{
    CString EntityName = _T( "_PropertyDefaultAttributeSaveStateWeb" );
    
    ZUSystemOption SystemOption( m_IniFile, EntityName );

    CString KeyName;
    CString Line;
    size_t Idx = 0;

    do
    {
        // Format the key
        KeyName.Format( _T( "%s%d" ), _T( "_PropertyDefaultAttributeSaveStateWeb" ), Idx );
        Line = SystemOption.ReadOption( KeyName, _T( "" ) );

        if ( Line.IsEmpty() )
        {
            break;
        }

        ++Idx;

        // Easier to set the value to null than to delete the line
        SystemOption.WriteOption( KeyName, _T( "0;0" ) );
    }
    while ( Idx < 1000000 );    // Sets the maximum loop at 1 million objects
                                // which is big already

    return true;
}
