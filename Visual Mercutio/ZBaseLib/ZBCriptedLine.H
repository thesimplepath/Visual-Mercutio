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
    //## Constructors (generated)
      ZBCriptedLine();
    //## Destructor (generated)
      ~ZBCriptedLine();

      ZBCriptedLine(const ZBCriptedLine &right);
      const ZBCriptedLine & operator=(const ZBCriptedLine &right);

      // This function generates a random line.
      CString GenerateRandomLine();

      CString GenerateLine(CString value);

      CString GenerateLine(CTime& Date);
      CString GenerateLine(ZBDate& Date);

      CString GenerateLine(int value);

      // Decript the string and return it.
      CString GetString();

      // Decript the int and return it.
      int GetInt();

      // Decript the date and return it.
      CTime  GetCTime();
      // Decript the date and return it.
      ZBDate GetDate();

    //## Get and Set Operations for Has Relationships (generated)

      //## Documentation ZBCriptedLine::sEntity.has
      //	The entity
      const CString GetsEntity() const;
      void SetsEntity(const CString value);



  private:  

      //	Take the key and cript it.
      void CriptEntity(CString& Line);

	  CString GenerateRandomLine(int size);

  private:

      CString m_sEntity;

};

// Class ZBCriptedLine 


inline const CString ZBCriptedLine::GetsEntity() const
{
  return m_sEntity;
}

inline void ZBCriptedLine::SetsEntity(const CString value)
{
  m_sEntity = value;
}



#endif


