//## begin module%366437AF034D.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%366437AF034D.cm

//## begin module%366437AF034D.cp preserve=no
//## end module%366437AF034D.cp

//## Module: FileOpt%366437AF034D; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZUSystemOption.h

#ifndef FileOpt_h
#define FileOpt_h 1

//## begin module%366437AF034D.additionalIncludes preserve=no
//## end module%366437AF034D.additionalIncludes

//## begin module%366437AF034D.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%366437AF034D.includes

//## begin module%366437AF034D.declarations preserve=no
//## end module%366437AF034D.declarations

//## begin module%366437AF034D.additionalDeclarations preserve=yes
#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif
//## end module%366437AF034D.additionalDeclarations

// JMR-MODIF - Le 9 avril 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Class ZUSystemOption

//## Class: ZUSystemOption%366435D40245
//## Category: PlanFin::Options::Utility Options Classes%366435B002A8
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZUSystemOption
{
public:

    // Constructs a system option class.
    ZUSystemOption( CString IniFile = _T( "" ), CString SectionName = _T( "" ) );
    ~ZUSystemOption();

    BOOL Create( CString IniFile = _T( "" ), CString SectionName = _T( "" ) );

    // Read a system option. Returns a String.
    CString ReadOption( CString EntityKey, LPCTSTR DefaultValue = NULL );

    // Read a system option. Returns a String.
    CString ReadOption( CString EntityKey, CString DefaultValue = _T( "" ) );

    // Read a system option. Returns an Integer.
    int ReadOption( CString EntityKey, int DefaultValue = 0 );

    // Read a system option. Returns a bool.
    bool ReadOption( CString EntityKey, bool DefaultValue = false );

    // Read a system option. Returns a double.
    double ReadOption( CString EntityKey, double DefaultValue = 0 );

    // Read a system option. Returns a float.
    float ReadOption( CString EntityKey, float DefaultValue = 0 );

    // Write a system option. Write a char pointer.
    BOOL WriteOption( CString EntityKey, LPCTSTR Value );

    // Write a system option. Write a String.
    BOOL WriteOption( CString EntityKey, CString Value );

    // Write a system option. Write an Integer.
    BOOL WriteOption( CString EntityKey, int Value );

    // Write a system option. Write a boolean.
    BOOL WriteOption( CString EntityKey, bool Value );

    // Write a system option. Write a double.
    BOOL WriteOption( CString EntityKey, double Value );

    // Write a system option. Write a float.
    BOOL WriteOption( CString EntityKey, float Value );

    // The ini file.
    const CString GetIniFile() const;
    void SetIniFile( CString value );

    // The section name of the ini file.
    const CString GetSectionName() const;
    void SetSectionName( CString value );

private:

    ZUSystemOption( const ZUSystemOption &right );
    const ZUSystemOption & operator=( const ZUSystemOption &right );

private:

    CString m_IniFile;
    CString m_SectionName;
};

inline const CString ZUSystemOption::GetIniFile() const
{
    return m_IniFile;
}

inline void ZUSystemOption::SetIniFile( CString value )
{
    m_IniFile = value;
}

inline const CString ZUSystemOption::GetSectionName() const
{
    return m_SectionName;
}

inline void ZUSystemOption::SetSectionName( CString value )
{
    m_SectionName = value;
}

#endif