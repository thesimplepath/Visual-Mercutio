// Source file: ZBCriptedLine.h


#ifndef ZBCriptedLine_h
#define ZBCriptedLine_h 1



//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZBDate.h"


#ifdef _ZBASELIBEXPORT
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



class AFX_EXT_CLASS ZBCriptedLine : public CObject
{
    DECLARE_DYNCREATE( ZBCriptedLine );

    public:
        ZBCriptedLine();

        ZBCriptedLine(const ZBCriptedLine &right);

        ~ZBCriptedLine();

        const ZBCriptedLine & operator=(const ZBCriptedLine &right);

        // This function generates a random line.
        CString GenerateRandomLine();

        CString GenerateLine(const CString& value);

        CString GenerateLine(CTime& date);
        CString GenerateLine(ZBDate& date);

        CString GenerateLine(int value);

        // Decript the string and return it.
        CString GetString();

        // Decript the int and return it.
        int GetInt();

        // Decript the date and return it.
        CTime GetCTime();

        // Decript the date and return it.
        ZBDate GetDate();

        //## Get and Set Operations for Has Relationships (generated)

        //## Documentation ZBCriptedLine::sEntity.has
        //    The entity
        const CString GetEntity() const;
        void SetEntity(const CString& value);

    private:
        CString m_sEntity;

        // Take the key and cript it.
        void CriptEntity(const CString& line);

        CString GenerateRandomLine(int size);
};

//---------------------------------------------------------------------------
// ZBCriptedLine 
//---------------------------------------------------------------------------
inline const CString ZBCriptedLine::GetEntity() const
{
    return m_sEntity;
}
//---------------------------------------------------------------------------
inline void ZBCriptedLine::SetEntity(const CString& value)
{
    m_sEntity = value;
}
//---------------------------------------------------------------------------

#endif
