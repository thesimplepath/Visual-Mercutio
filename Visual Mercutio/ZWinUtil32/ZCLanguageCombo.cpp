#include <StdAfx.h>

#include "ZCLanguageCombo.h"

#include "zBaseLib\ZBTokenizer.h"
#include "zRes32\zRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZCLanguageCombo, CCJFlatComboBox)
	//{{AFX_MSG_MAP(ZCLanguageCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCLanguageCombo 


ZCLanguageCombo::ZCLanguageCombo( Language InitialLanguage /*= UnknownLang*/ )
:	m_Language(InitialLanguage)
{
}


ZCLanguageCombo::~ZCLanguageCombo()
{
}



int ZCLanguageCombo::Initialize ()
{
	CString s;
	s.LoadString( IDS_LANGUAGE_LIST );

	ZBTokenizer token;	// Initialize the token with ; as separator

	CString str = token.GetFirstToken( s );
	
	// Run through all tokens
	while (!str.IsEmpty())
	{
		// Add the string to the list
		AddString(str);
		// Get the next token
		str = token.GetNextToken();
	}

	SelectLanguage( m_Language );
	return 1;
}



