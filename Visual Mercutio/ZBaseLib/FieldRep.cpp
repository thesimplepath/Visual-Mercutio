//## begin module%37EC7CFC0257.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%37EC7CFC0257.cm

//## begin module%37EC7CFC0257.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%37EC7CFC0257.cp

//## Module: FieldRep%37EC7CFC0257; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\FieldRep.cpp

//## begin module%37EC7CFC0257.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%37EC7CFC0257.additionalIncludes

//## begin module%37EC7CFC0257.includes preserve=yes
//## end module%37EC7CFC0257.includes

// FieldRep
#include "FieldRep.h"
//## begin module%37EC7CFC0257.declarations preserve=no
//## end module%37EC7CFC0257.declarations

//## begin module%37EC7CFC0257.additionalDeclarations preserve=yes
#include "File.h"
//## end module%37EC7CFC0257.additionalDeclarations

// Class ZBFieldRepository 

ZBFieldRepository::ZBFieldRepository()
	: m_GlobalFieldManager	( NULL ),
	  m_HistoryValueManager	( NULL ),
	  m_Document			( NULL ),
	  //## begin ZBFieldRepository::ZBFieldRepository%.hasinit preserve=no
	  m_IsValid				( FALSE ),
	  //## end ZBFieldRepository::ZBFieldRepository%.hasinit
	  //## begin ZBFieldRepository::ZBFieldRepository%.initialization preserve=yes
	  m_ReadOnly			( TRUE )
	  //## end ZBFieldRepository::ZBFieldRepository%.initialization
{
	//## begin ZBFieldRepository::ZBFieldRepository%.body preserve=yes
	m_GlobalFieldManager	= new ZAGlobalFieldManager();
	m_HistoryValueManager	= new ZAHistoryFieldManager();
	m_Document				= new ZDGlobalFieldDocument();
	//## end ZBFieldRepository::ZBFieldRepository%.body
}

ZBFieldRepository::~ZBFieldRepository()
{
	//## begin ZBFieldRepository::~ZBFieldRepository%.body preserve=yes
	if ( m_GlobalFieldManager != NULL )
	{
		delete m_GlobalFieldManager;
		m_GlobalFieldManager = NULL;
	}

	if ( m_HistoryValueManager != NULL )
	{
		delete m_HistoryValueManager;
		m_HistoryValueManager = NULL;
	}

	if ( m_Document != NULL )
	{
		delete m_Document;
		m_Document = NULL;
	}
	//## end ZBFieldRepository::~ZBFieldRepository%.body
}

//## Other Operations (implementation)
BOOL ZBFieldRepository::InitializeEmpty ()
{
	//## begin ZBFieldRepository::InitializeEmpty%938959792.body preserve=yes
	m_IsValid	= TRUE;
	m_ReadOnly	= FALSE;

	return m_IsValid;
	//## end ZBFieldRepository::InitializeEmpty%938959792.body
}

BOOL ZBFieldRepository::OpenRepository ( const CString Filename, BOOL ReadOnly )
{
	//## begin ZBFieldRepository::OpenRepository%938242425.body preserve=yes
	m_ReadOnly = ReadOnly;

	ZFile File( Filename );

	// Keep repository filename
	m_Filename = Filename;

	if ( Filename.IsEmpty() || !File.Exist() )
	{
		if ( m_ReadOnly == FALSE )
		{
			// Sets the pathname for 
			m_Document->Initialize( m_GlobalFieldManager, m_HistoryValueManager );
			m_Document->SetPathName( Filename, FALSE );

			return m_IsValid = TRUE;
		}
		else
			return m_IsValid = FALSE;
	}

	return m_IsValid = m_Document->ReadDocument( Filename, m_GlobalFieldManager, m_HistoryValueManager );
	//## end ZBFieldRepository::OpenRepository%938242425.body
}

BOOL ZBFieldRepository::CloseRepository ()
{
	//## begin ZBFieldRepository::CloseRepository%938242426.body preserve=yes
	if ( !m_IsValid )
		return FALSE;

	if ( m_ReadOnly )
		return TRUE;

	m_Document->SetModifiedFlag( TRUE );

	return m_Document->SaveDocument();
	//## end ZBFieldRepository::CloseRepository%938242426.body
}

BOOL ZBFieldRepository::SaveRepositoryToFile ( const CString Filename )
{
	//## begin ZBFieldRepository::SaveRepositoryToFile%938959793.body preserve=yes
	m_Document->Initialize( Filename, m_GlobalFieldManager, m_HistoryValueManager );

	return m_Document->SaveDocument();
	//## end ZBFieldRepository::SaveRepositoryToFile%938959793.body
}

BOOL ZBFieldRepository::ReloadRepository ( BOOL SaveBefore )
{
	//## begin ZBFieldRepository::ReloadRepository%939925866.body preserve=yes
	if ( !m_IsValid )
		return FALSE;

	// If save is requested, 
	// close the repository with save effect if not read-only
	if ( SaveBefore )
		CloseRepository();

	return m_IsValid = m_Document->ReadDocument( m_Filename, m_GlobalFieldManager, m_HistoryValueManager );
	//## end ZBFieldRepository::ReloadRepository%939925866.body
}

BOOL ZBFieldRepository::Import ( ZBFieldRepository& FieldRepository, BOOL ReplaceExisting )
{
	//## begin ZBFieldRepository::Import%939069932.body preserve=yes
	for ( int i = 0; i < FieldRepository.GetFieldCount(); ++i )
	{
		ZAObjectDefinition* pObjectDefinition = FieldRepository.GetFieldAt( i );

		if ( pObjectDefinition )
		{
			ZAObjectDefinition* pSourceObjectDefinition = FindField( pObjectDefinition->GetFieldName() );

			// If a source already exists and the replace flag is false
			// Do nothing
			if ( pSourceObjectDefinition && ReplaceExisting == FALSE )
				continue;

			// If no source
			if ( !pSourceObjectDefinition )
			{
				// Add a new one
				AddField( pObjectDefinition->Clone() );
			}
			else
			{
				// Copy values
				pSourceObjectDefinition->SetDescription			( pObjectDefinition->GetDescription() );
				pSourceObjectDefinition->SetHelpUserDescription	( pObjectDefinition->GetHelpUserDescription() );
				pSourceObjectDefinition->SetSorted				( pObjectDefinition->IsSorted() );

				// If no object included
				if ( pSourceObjectDefinition->GetpObject() == NULL )
				{
					// Assign the object
					pSourceObjectDefinition->SetClassName( pObjectDefinition->GetClassName() );
					pSourceObjectDefinition->SetpObject( ( pObjectDefinition->GetpObject() ) ? pObjectDefinition->GetpObject()->Clone() : NULL );
				}
			}

			// Now process the history
			ZAHistoryField*	pObjectHistory = FieldRepository.FindFieldHistory( pObjectDefinition->GetFieldName() );

			if ( pObjectHistory )
			{
				const CStringArray&	Values = pObjectHistory->GetValueArray();

				for ( int Index = 0; Index < Values.GetSize(); ++Index )
					AddFieldHistoryValue( pObjectDefinition->GetFieldName(), Values.GetAt( Index ) );
			}

			// Now set the read-only flag
			ZAHistoryField*	pHistory = FindFieldHistory( pObjectDefinition->GetFieldName() );

			if ( pHistory )
				pHistory->SetReadOnly( pObjectHistory->IsReadOnly() );
		}
	}

	return TRUE;
	//## end ZBFieldRepository::Import%939069932.body
}

// Additional Declarations
//## begin ZBFieldRepository%37EC7ACB0296.declarations preserve=yes
//## end ZBFieldRepository%37EC7ACB0296.declarations

//## begin module%37EC7CFC0257.epilog preserve=yes
//## end module%37EC7CFC0257.epilog
