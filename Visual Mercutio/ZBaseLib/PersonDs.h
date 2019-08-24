/****************************************************************************
 * ==> PSS_MailUser --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a mail user                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PersonDs_h
#define PersonDs_h 1

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#include "mfc.h"
#ifndef _WIN32
    #ifndef Mapi_h
        #define Mapi_h
        #include <mapi.h>
    #endif
#else
    #include <mapi.h>
#endif

// processsoft
#include "ZUser.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZBMailUser : public CObject
{
    DECLARE_SERIAL(ZBMailUser)

public:
    //## Constructors (generated)
    ZBMailUser(const ZBMailUser &right);

    //## Constructors (specified)
      //## Operation: ZBMailUser%913452742
    ZBMailUser(CString PersonName = "", ULONG RecipClass = MAPI_TO);

    //## Operation: ZBMailUser%913659111
    ZBMailUser(ZUser& PersonName, ULONG RecipClass = MAPI_TO);

    //## Destructor (generated)
    virtual ~ZBMailUser();

    //## Assignment Operation (generated)
    const ZBMailUser & operator=(const ZBMailUser &right);

    /**
    * Stores from the archive to the object stamp
    *@param ar - archive
    *@param user - mail user
    *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
    */
    friend CArchive& operator >> (CArchive& ar, ZBMailUser& user);

    /**
    * Stores the object stamp to the archive
    *@param ar - archive
    *@param user - mail user
    *@return archive, to allow operator to be chained with other items, e.g a << b << c
    */
    friend CArchive& operator << (CArchive& ar, ZBMailUser& user);

    //## Other Operations (specified)
      //## Operation: Clone%913452743
    ZBMailUser* Clone();

    //## Operation: Serialize%928263998
    //    Serialization function required for MFC mecanism.
    virtual void Serialize(CArchive& ar);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: PersonName%36722D2D00E8
    const CString& GetPersonName() const;
    void SetPersonName(const CString& value);

    //## Attribute: RecipClass%36722D45033C
    //    Define the recipicient class.
    const ULONG GetRecipClass() const;
    void SetRecipClass(ULONG value);

private:
    CString m_PersonName;
    ULONG m_RecipClass;
};

inline const CString& ZBMailUser::GetPersonName() const
{
    return m_PersonName;
}

inline void ZBMailUser::SetPersonName(const CString& value)
{
    m_PersonName = value;
}

inline const ULONG ZBMailUser::GetRecipClass() const
{
    return m_RecipClass;
}

inline void ZBMailUser::SetRecipClass(ULONG value)
{
    m_RecipClass = value;
}

#endif
