
#ifndef __ZCLanguageCombo_h__
#define __ZCLanguageCombo_h__ 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zLanguageDef.h"


#ifdef _ZWINUTIL32EXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZCLanguageCombo : public CCJFlatComboBox  
{
//    DECLARE_DYNAMIC(ZCLanguageCombo)
public:
    ZCLanguageCombo( Language InitialLanguage = UnknownLang );
    virtual ~ZCLanguageCombo();

    int Initialize();
    int Initialize( Language InitialLanguage )
    {
        m_Language = InitialLanguage;
        return Initialize();
    };

    Language    GetLanguage() const
    {
        return static_cast<Language>(GetCurSel());
    };
    void    SelectLanguage( Language NewLanguage )
    {
        SetCurSel( NewLanguage );
    }



    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCLanguageCombo)
    //}}AFX_VIRTUAL
  protected:
    //{{AFX_MSG(ZCLanguageCombo)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  private:
      ZCLanguageCombo(const ZCLanguageCombo &right);
      const ZCLanguageCombo & operator=(const ZCLanguageCombo &right);

private: 
    Language m_Language;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif      // __ZCLanguageCombo_h__
