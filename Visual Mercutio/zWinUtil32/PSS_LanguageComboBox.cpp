/****************************************************************************
 * ==> PSS_LanguageComboBox ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a combo box allowing to select a language         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_LanguageComboBox.h"

// processsoft
#include "zBaseLib\ZBTokenizer.h"
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_LanguageComboBox, CCJFlatComboBox)
    //{{AFX_MSG_MAP(PSS_LanguageComboBox)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_LanguageComboBox
//---------------------------------------------------------------------------
PSS_LanguageComboBox::PSS_LanguageComboBox(ELanguage initialLanguage) :
    CCJFlatComboBox(),
    m_Language(initialLanguage)
{}
//---------------------------------------------------------------------------
PSS_LanguageComboBox::PSS_LanguageComboBox(const PSS_LanguageComboBox& other)
{
    THROW("Copy constructor is prohibited");
}
//---------------------------------------------------------------------------
PSS_LanguageComboBox::~PSS_LanguageComboBox()
{}
//---------------------------------------------------------------------------
const PSS_LanguageComboBox& PSS_LanguageComboBox::operator = (const PSS_LanguageComboBox& other)
{
    THROW("Copy constructor is prohibited");
}
//---------------------------------------------------------------------------
int PSS_LanguageComboBox::Initialize ()
{
    CString languages;
    languages.LoadString(IDS_LANGUAGE_LIST);

    // initialize the token with ; as separator
    ZBTokenizer token;

    // get the first available language
    CString language = token.GetFirstToken(languages);

    // iterate through all tokens
    while (!language.IsEmpty())
    {
        // add the language string to the list
        AddString(language);

        // get the next token
        language = token.GetNextToken();
    }

    // select the current language
    SelectLanguage(m_Language);

    return 1;
}
//---------------------------------------------------------------------------
