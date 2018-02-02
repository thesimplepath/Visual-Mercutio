//## begin module%36CE9A9F0369.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%36CE9A9F0369.cm

//## begin module%36CE9A9F0369.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%36CE9A9F0369.cp

//## Module: BObjUtil%36CE9A9F0369; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\BObjUtil.cpp

//## begin module%36CE9A9F0369.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%36CE9A9F0369.additionalIncludes

//## begin module%36CE9A9F0369.includes preserve=yes
//## end module%36CE9A9F0369.includes

#include "BObjUtil.h"

#include "zBaseLib\ZUSystemOption.h"
#include "File.h"
#include "ZARadio.h"
#include "ZASquare.h"
#include "ZABnText.h"
#include "ZANumbrd.h"
#include "ZABitmap.h"
#include "ZACheck.h"
#include "ZAMStr.h"
#include "ZAMultiC.h"

// JMR-MODIF - Le 21 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

const char szSectionKey[]	= _T( "Keys" );
const char szTypeEntry[]	= _T( "Entry" );
const char szLineEntry[]	= _T( "Line" );

const UINT ZBObjectUtility::ClassResourceBitmapIDArrary[] =
{
	IDB_AMOUNT_BITMAP,
	IDB_AMOUNT_BITMAP,
	IDB_CALC_BITMAP,
	IDB_DATE_BITMAP,
	IDB_TEXT_BITMAP,
	IDB_TEXT_BITMAP,
	IDB_STEXT_BITMAP,
	IDB_MULTILINE_BITMAP,
	IDB_SMULTILINE_BITMAP,
	IDB_SECTION_BITMAP,
	IDB_SQUARE_BITMAP,
	IDB_LINE_BITMAP,
	IDB_RECT_BITMAP,
	IDB_RECTROUNDED_BITMAP,
	IDB_IMAGE_BITMAP,
	IDB_IMAGE_BITMAP,
	IDB_IMAGE_BITMAP,
	0
};

const UINT ZBObjectUtility::EditionClassResourceIDArrary[] =
{
	IDS_AMOUNT_CLASS,
	IDS_HISTOAMOUNT_CLASS,
	IDS_CALCULATED_CLASS,
	IDS_DATE_CLASS,
	IDS_TEXT_CLASS,
	IDS_HISTOTEXT_CLASS,
	IDS_STATICTEXT_CLASS,
	IDS_MULTITEXT_CLASS,
	IDS_MULTITEXTSTATIC_CLASS,
	IDS_NUMBEREDSECTION_CLASS,
	IDS_SQUARETEXT_CLASS,
	IDS_CHECK_CLASS,
	IDS_RADIO_CLASS,
	IDS_MASKSTRING_CLASS,
	IDS_MASKSTRINGHISTO_CLASS,
	IDS_MULTICOLUMN_CLASS,
	0
};

const UINT ZBObjectUtility::ClassResourceIDArrary[] =
{
	IDS_AMOUNT_CLASS,
	IDS_HISTOAMOUNT_CLASS,
	IDS_CALCULATED_CLASS,
	IDS_DATE_CLASS,
	IDS_TEXT_CLASS,
	IDS_HISTOTEXT_CLASS,
	IDS_STATICTEXT_CLASS,
	IDS_MULTITEXT_CLASS,
	IDS_MULTITEXTSTATIC_CLASS,
	IDS_NUMBEREDSECTION_CLASS,
	IDS_SQUARETEXT_CLASS,
	IDS_LINE_CLASS,
	IDS_RECTANGLE_CLASS,
	IDS_RECTANGLEROUNDED_CLASS,
	IDS_BITMAP_CLASS,
	IDS_CHECK_CLASS,
	IDS_RADIO_CLASS,
	IDS_MASKSTRING_CLASS,
	IDS_MASKSTRINGHISTO_CLASS,
	IDS_MULTICOLUMN_CLASS,
	0
};
//## end module%36CE9A9F0369.additionalDeclarations

// Class ZBObjectUtility 

//## begin ZBObjectUtility::ClassNameArray%36CE9C0901CE.attr preserve=no  public: static CStringArray {V} 
CStringArray ZBObjectUtility::m_ClassNameArray;
//## end ZBObjectUtility::ClassNameArray%36CE9C0901CE.attr

//## begin ZBObjectUtility::EditionClassNameArray%36CE9C0E0121.attr preserve=no  public: static CStringArray {V} 
CStringArray ZBObjectUtility::m_EditionClassNameArray;
//## end ZBObjectUtility::EditionClassNameArray%36CE9C0E0121.attr

//## begin ZBObjectUtility::FieldTypeDescriptionArray%37E67C5B0370.attr preserve=no  private: static CObArray {V} 
CObArray ZBObjectUtility::m_FieldTypeDescriptionArray;
//## end ZBObjectUtility::FieldTypeDescriptionArray%37E67C5B0370.attr

ZBObjectUtility::ZBObjectUtility()
  //## begin ZBObjectUtility::ZBObjectUtility%.hasinit preserve=no
  //## end ZBObjectUtility::ZBObjectUtility%.hasinit
  //## begin ZBObjectUtility::ZBObjectUtility%.initialization preserve=yes
  //## end ZBObjectUtility::ZBObjectUtility%.initialization
{
  //## begin ZBObjectUtility::ZBObjectUtility%.body preserve=yes
  //## end ZBObjectUtility::ZBObjectUtility%.body
}

ZBObjectUtility::~ZBObjectUtility()
{
	//## begin ZBObjectUtility::~ZBObjectUtility%.body preserve=yes

	// JMR-MODIF - Le 23 août 2005 - Le destructeur est maintenant remplaçé par la fonction Release.
	Release();

	//## end ZBObjectUtility::~ZBObjectUtility%.body
}

// JMR-MODIF - Le 23 août 2005 - Ajouté la fonction statique Release, pour permettre un nettoyage de l'objet.
void ZBObjectUtility::Release()
{
	for ( int i = 0; i < m_FieldTypeDescriptionArray.GetSize(); ++i )
	{
		if ( m_FieldTypeDescriptionArray.GetAt( i ) )
		{
			delete (ObjectDefinition*)( m_FieldTypeDescriptionArray.GetAt( i ) );
		}
	}
}

//## Other Operations (implementation)
const CString ZBObjectUtility::GetFieldTypeDescription ( PlanFinObject* pObj )
{
  //## begin ZBObjectUtility::GetFieldTypeDescription%919498958.body preserve=yes
	switch ( GetClassNameID( pObj ) )
	{
		case IDS_STATICTEXT_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNStatic" ) );
		}

		case IDS_DATE_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNTime" ) );
		}

		case IDS_CALCULATED_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNCalculated" ) );
		}

		case IDS_HISTOAMOUNT_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNLongHistory" ) );
		}

		case IDS_AMOUNT_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNLong" ) );
		}

		case IDS_MULTITEXTSTATIC_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNBondTextStatic" ) );
		}

		case IDS_MULTITEXT_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNBondText" ) );
		}

		case IDS_HISTOTEXT_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNStringHistory" ) );
		}

		case IDS_TEXT_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNString" ) );
		}

		case IDS_SQUARETEXT_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNSquare" ) );
		}

		case IDS_NUMBEREDSECTION_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNAutoNumbered" ) );
		}

		case IDS_LINE_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNLine" ) );
		}

		case IDS_RECTANGLEROUNDED_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNRectRounded" ) );
		}

		case IDS_RECTANGLE_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNRect" ) );
		}

		case IDS_BITMAP_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNBitmap" ) );
		}

		case IDS_CHECK_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNCheck" ) );
		}

		case IDS_RADIO_CLASS: 
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNRadio" ) );
		}

		case IDS_MASKSTRING_CLASS:
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNMaskString" ) );
		}

		case IDS_MASKSTRINGHISTO_CLASS:
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNMaskStringHisto" ) );
		}

		case IDS_MULTICOLUMN_CLASS:
		{
			return GetFieldTypeDescriptionIniFile( _T( "$$$PLFNMultiColumn" ) );
		}

		default: break;
	}

	return _T( "" );
	//## end ZBObjectUtility::GetFieldTypeDescription%919498958.body
}

const CString ZBObjectUtility::GetFieldTypeDescription ( const CString ClassName )
{
	//## begin ZBObjectUtility::GetFieldTypeDescription%919592606.body preserve=yes
  	CString			FieldExplanation;
	PlanFinObject*	pTempObj = ZBObjectUtility::ConstructObject( ClassName );

	if ( pTempObj )
	{
		FieldExplanation = ZBObjectUtility::GetFieldTypeDescription( pTempObj );
		delete pTempObj;
	}

	return FieldExplanation;
	//## end ZBObjectUtility::GetFieldTypeDescription%919592606.body
}

const CString ZBObjectUtility::GetFieldTypeDescriptionIniFile ( const char* cpKey )
{
	//## begin ZBObjectUtility::GetFieldTypeDescriptionIniFile%919498962.body preserve=yes
	for ( int i = 0; i < m_FieldTypeDescriptionArray.GetSize(); ++i )
	{
		if ( m_FieldTypeDescriptionArray.GetAt( i ) &&
			 ( (ObjectDefinition*)m_FieldTypeDescriptionArray.GetAt( i ) )->m_Key == cpKey )
		{
			return ( (ObjectDefinition*)m_FieldTypeDescriptionArray.GetAt( i ) )->m_Description;
		}
	}

	return _T( "" );
	//## end ZBObjectUtility::GetFieldTypeDescriptionIniFile%919498962.body
}

const CString ZBObjectUtility::GetClassName ( PlanFinObject* pObj )
{
	//## begin ZBObjectUtility::GetClassName%919498959.body preserve=yes
  	CString	sText;
  	sText.LoadString( GetClassNameID( pObj ) );
  	
	return sText;
	//## end ZBObjectUtility::GetClassName%919498959.body
}

UINT ZBObjectUtility::GetBitmapClass ( const CString className )
{
	//## begin ZBObjectUtility::GetBitmapClass%919498960.body preserve=yes
	// Fill the list with all objects' type
	const CStringArray& Array = GetClassNameArray();

	for ( int i = 0; i < Array.GetSize(); ++i )
	{
		if ( className == Array.GetAt( i ) )
		{
			return ClassResourceBitmapIDArrary[i];
		}
	}

	return 0;
	//## end ZBObjectUtility::GetBitmapClass%919498960.body
}

PlanFinObject* ZBObjectUtility::ConstructObject ( const CString& sClassName )
{
	//## begin ZBObjectUtility::ConstructObject%919498961.body preserve=yes
	PlanFinObject*	pObj = NULL;
	
	// Fill the list with all objects' type
	const CStringArray& Array = GetClassNameArray();

	for ( int i = 0; i < Array.GetSize(); ++i )
	{
		if ( sClassName == Array.GetAt( i ) )
		{
			break;
		}
	}

	switch( i )
	{
		case 0:
		{
			pObj = new PLFNLong;
			break;
		}

		case 1:
		{
			pObj = new PLFNLong;
			( (PLFNLong*)pObj )->SetKeepHistory( TRUE );
			break;
		}

		case 2:
		{
			pObj = new PLFNLong;
			( (PLFNLong*)pObj )->SetCalculatedField();
			break;
		}

		case 3:
		{
			pObj = new PLFNTime;
			break;
		}

		case 4:
		{
			pObj = new PLFNString;
			break;
		}

		case 5:
		{
			pObj = new PLFNString;
			( (PLFNString*)pObj )->SetKeepHistory( TRUE );
			break;
		}

		case 6:
		{
			pObj = new PLFNStatic;
			break;
		}

		case 7:
		{
			pObj = new PLFNBoundText;
			break;
		}

		case 8:
		{
			pObj = new PLFNBoundText( TRUE );	// TRUE is for static bound text
			break;
		}

		case 9:
		{
			pObj = new PLFNAutoNumbered;
			break;
		}

		case 10:
		{
			pObj = new PLFNSquare;
			break;
		}

		case 11:
		{
			pObj = new PLFNLine;
			break;
		}

		case 12:
		{
			pObj = new PLFNRect;
			break;
		}

		case 13:
		{
			pObj = new PLFNRect( TRUE );
			break;
		}

		case 14:
		{
			pObj = new PLFNBitmap;
			break;
		}

		case 15:
		{
			pObj = new PLFNCheck;
			break;
		}

		case 16:
		{
			pObj = new PLFNRadio;
			break;
		}

		case 17:
		{
			pObj = new PLFNMaskString;
			break;
		}

		case 18:
		{
			pObj = new PLFNMaskString;
			( (PLFNMaskString*)pObj )->SetKeepHistory( TRUE );
			break;
		}

		case 19:
		{
			pObj = new PLFNMultiColumn;
			break;
		}

		default: ASSERT( FALSE );
	}

	return pObj;
	//## end ZBObjectUtility::ConstructObject%919498961.body
}

void ZBObjectUtility::LoadResource ()
{
	//## begin ZBObjectUtility::LoadResource%919592602.body preserve=yes
	// Assign the Edition class name
	if ( m_EditionClassNameArray.GetSize() <= 0 )
	{
		CString	sLabel;

		for ( register i = 0; EditionClassResourceIDArrary[i]; ++i )
		{
			sLabel.LoadString( EditionClassResourceIDArrary[i] );
			m_EditionClassNameArray.Add( sLabel );
		}
	}

	// Assign the class name
	if ( m_ClassNameArray.GetSize() <= 0 )
	{
		CString	sLabel;
		for ( register i = 0; ClassResourceIDArrary[i]; ++i )
		{
			sLabel.LoadString( ClassResourceIDArrary[i] );
			m_ClassNameArray.Add( sLabel );
		}
	}
	//## end ZBObjectUtility::LoadResource%919592602.body
}

BOOL ZBObjectUtility::InitializeDefinition ( const CString IniFile )
{
	//## begin ZBObjectUtility::InitializeDefinition%937851058.body preserve=yes
    ZUSystemOption	m_SystemOption;

	m_FieldTypeDescriptionArray.RemoveAll();

	// Check if the file exists
	ZFile File( IniFile );

	if ( !File.Exist() )
		return FALSE;

	// Create the ini reader
	if ( !m_SystemOption.Create( IniFile, szSectionKey ) )
		return FALSE;

	char	Buffer[100];
	CString	FieldKey;
	CString	Description;

	for ( int i = 0; TRUE ;++i )
	{
		// Build the key
		sprintf( Buffer, _T( "%s%d" ), szTypeEntry, i );
		FieldKey = m_SystemOption.ReadOption( Buffer, _T( "" ) );

		// If no more entry
		if ( FieldKey.IsEmpty() )
			break;

		Description				= LoadFieldDefinition( IniFile, FieldKey );
		ObjectDefinition* pDef	= new ObjectDefinition( FieldKey, Description );

		m_FieldTypeDescriptionArray.Add( (CObject*)pDef );
	}

	return TRUE;
	//## end ZBObjectUtility::InitializeDefinition%937851058.body
}

CString ZBObjectUtility::LoadFieldDefinition ( const CString IniFile, const CString FieldKey )
{
	//## begin ZBObjectUtility::LoadFieldDefinition%937851059.body preserve=yes
    ZUSystemOption	m_SystemOptionField( IniFile, FieldKey );
	char			Buffer[100];
	CString			Line;
	CString			Description;

	for( int i=0; ; i++ )
	{
		// Build the key
		sprintf( Buffer, _T( "%s%d" ), szLineEntry, i );

		Line = m_SystemOptionField.ReadOption( Buffer, _T( "" ) );

		// If no more entry
		if ( Line.IsEmpty() )
			break;

		Description += Line;
    }

	return Description;
	//## end ZBObjectUtility::LoadFieldDefinition%937851059.body
}

size_t ZBObjectUtility::GetClassNameID ( PlanFinObject* pObj )
{
	//## begin ZBObjectUtility::GetClassNameID%938242424.body preserve=yes
  	size_t	nResourceID = IDS_UNMODIFIED_CLASS;

	if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNStatic ) ) )
	{
		nResourceID = IDS_STATICTEXT_CLASS;
	}
	else if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNTime ) ) )
	{
		nResourceID = IDS_DATE_CLASS;
	}
	else if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) )
	{
		if ( ( (PLFNLong*)pObj )->IsCalculatedField() )
		{
			nResourceID = IDS_CALCULATED_CLASS;
		}
		else
		{
			if ( ( (PLFNLong*)pObj )->GetKeepHistory() )
			{
				nResourceID = IDS_HISTOAMOUNT_CLASS;
			}
			else nResourceID = IDS_AMOUNT_CLASS;
		}
	}
	else if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNBoundText ) ) )
	{
		if ( ( (PLFNBoundText*)pObj )->GetIsStatic() )
		{
			nResourceID = IDS_MULTITEXTSTATIC_CLASS;
		}
		else nResourceID = IDS_MULTITEXT_CLASS;
	}
	else if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNMaskString ) ) )
	{
		if ( ( (PLFNString*)pObj )->GetKeepHistory() )
		{
			nResourceID = IDS_MASKSTRINGHISTO_CLASS;
		}
		else nResourceID = IDS_MASKSTRING_CLASS;
	}
	else if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNString ) ) )
	{
		if ( ( (PLFNString*)pObj )->GetKeepHistory() )
		{
			nResourceID = IDS_HISTOTEXT_CLASS;
		}
		else nResourceID = IDS_TEXT_CLASS;
	}
	else if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNSquare ) ) )
	{
		nResourceID = IDS_SQUARETEXT_CLASS;
	}
	else if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) ) )
	{
		nResourceID = IDS_NUMBEREDSECTION_CLASS;
	}
	else if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNLine ) ) )
	{
		nResourceID = IDS_LINE_CLASS;
	}
	else if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNRect ) ) )
	{
		if ( ( (PLFNRect*)pObj )->IsRounded() )
		{
			nResourceID = IDS_RECTANGLEROUNDED_CLASS;
		}
		else nResourceID = IDS_RECTANGLE_CLASS;
	}
	else if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNBitmap ) ) )
	{
		nResourceID = IDS_BITMAP_CLASS;
	}
	else if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNCheck ) ) )
	{
		nResourceID = IDS_CHECK_CLASS;
	}
	else if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNRadio ) ) )
	{
		nResourceID = IDS_RADIO_CLASS;
	}
	else if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNMultiColumn ) ) )
	{
		nResourceID = IDS_MULTICOLUMN_CLASS;
	}

	return nResourceID;
	//## end ZBObjectUtility::GetClassNameID%938242424.body
}

// Additional Declarations
//## begin ZBObjectUtility%36CE993103DA.declarations preserve=yes
ZBObjectUtility::ObjectDefinition::ObjectDefinition( const CString Key, const CString Description )
	: m_Key			( Key ),
	  m_Description	( Description )
{
}

ZBObjectUtility::ObjectDefinition::~ObjectDefinition()
{
}
//## end ZBObjectUtility%36CE993103DA.declarations

//## begin module%36CE9A9F0369.epilog preserve=yes
//## end module%36CE9A9F0369.epilog
