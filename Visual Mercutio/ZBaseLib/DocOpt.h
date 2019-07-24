//## begin module%351657DC033E.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%351657DC033E.cm

//## begin module%351657DC033E.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%351657DC033E.cp

//## Module: DocOpt%351657DC033E; Package specification
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\ZProcess\DocOpt.h

#ifndef DocOpt_h
#define DocOpt_h 1


#ifdef _AFXEXT
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
#endif


//#include "ZAObject.h"


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



class AFX_EXT_CLASS ZDDocumentOptions 
{
  //## begin ZDDocumentOptions%351656F90334.initialDeclarations preserve=yes
  //## end ZDDocumentOptions%351656F90334.initialDeclarations

  public:
    //## Constructors (generated)
      ZDDocumentOptions();

      ZDDocumentOptions(const ZDDocumentOptions &right);

    //## Destructor (generated)
      virtual ~ZDDocumentOptions();

    //## Assignment Operation (generated)
      const ZDDocumentOptions & operator=(const ZDDocumentOptions &right);


    //## Other Operations (specified)
      //## Operation: operator >>%890656168
      //    Store from the archive to the object Document Option.
      AFX_EXT_API friend CArchive& operator >> (CArchive& ar, ZDDocumentOptions& DocOptions);

      //## Operation: operator <<%890656169
      //    Store the object Document Option to the archive.
      AFX_EXT_API friend CArchive& operator << (CArchive& ar, const ZDDocumentOptions& DocOptions);

      //## Operation: BuildSynchronizationFileName%931459606
      CString BuildSynchronizationFileName (CString DocumentFilename);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: EmptyStyle%351657670046
      //    Defines the empty style when the controls are empty.
      const ELineType GetEmptyStyle() const;
      void SetEmptyStyle(ELineType value);

      //## Attribute: IsSynchronizeExchangeFeedFile%36501278034D
      //    Specifiy if it is necessary to synchronize the feed data
      //    file.
      const BOOL GetIsSynchronizeExchangeFeedFile () const;
      void SetIsSynchronizeExchangeFeedFile (BOOL value);

      //## Attribute: SynchronizeTimeSequence%365012BB03A4
      //    Defines if the synchronization time (in seconds).
      const int GetSynchronizeTimeSequence () const;
      void SetSynchronizeTimeSequence (int value);

      //## Attribute: ShowHiddenField%3650151D02C4
      //    Specifiy if hidden fields must be shown.
      const EOptionType GetShowHiddenField() const;
      void SetShowHiddenField(EOptionType value);

      //## Attribute: ShowEmptyLine%3650154403C5
      //    Specify if empty lines must be shown if there are emty.
      const EOptionType GetShowEmptyLine() const;
      void SetShowEmptyLine(EOptionType value);

      //## Attribute: AutomaticSynchronizeFilename%366A4F5A03BF
      //    Is the filename automatically created.
      const ESynchronizationFileType GetAutomaticSynchronizeFilename() const;
      void SetAutomaticSynchronizeFilename(ESynchronizationFileType value);

      //## Attribute: SynchronizeFilename%366A4F7802C8
      //    The synchronization filename if not automatic.
      const CString GetSynchronizeFilename () const;
      void SetSynchronizeFilename (CString value);

      //## Attribute: SynchronizationHeader%366A55DB01C5
      //    Ceates or not a synchronization header
      const BOOL GetSynchronizationHeader () const;
      void SetSynchronizationHeader (BOOL value);

      //## Attribute: SynchronizationSeparator%366A5603008C
      //    Defines the seperator type.
      const ESynchronizationSeparatorType GetSynchronizationSeparator() const;
      void SetSynchronizationSeparator(ESynchronizationSeparatorType value);

    // Additional Public Declarations
      //## begin ZDDocumentOptions%351656F90334.public preserve=yes
      BOOL GetPrintEmptyStyleWhenEmpty() const { return m_PrintEmptyStyleWhenEmpty; };
      void    SetPrintEmptyStyleWhenEmpty( BOOL value ) { m_PrintEmptyStyleWhenEmpty = value; };
      //## end ZDDocumentOptions%351656F90334.public

  protected:
    // Additional Protected Declarations
      //## begin ZDDocumentOptions%351656F90334.protected preserve=yes
      //## end ZDDocumentOptions%351656F90334.protected

  private:
    // Data Members for Class Attributes

      //## begin ZDDocumentOptions::EmptyStyle%351657670046.attr preserve=no  public: LineType {V} DashLine
      ELineType m_EmptyStyle;
      //## end ZDDocumentOptions::EmptyStyle%351657670046.attr

      //## begin ZDDocumentOptions::IsSynchronizeExchangeFeedFile%36501278034D.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_IsSynchronizeExchangeFeedFile;
      //## end ZDDocumentOptions::IsSynchronizeExchangeFeedFile%36501278034D.attr

      //## begin ZDDocumentOptions::SynchronizeTimeSequence%365012BB03A4.attr preserve=no  public: int {U} 5
      int m_SynchronizeTimeSequence;
      //## end ZDDocumentOptions::SynchronizeTimeSequence%365012BB03A4.attr

      //## begin ZDDocumentOptions::ShowHiddenField%3650151D02C4.attr preserve=no  public: OptionType {U} ApplicationOption
      EOptionType m_ShowHiddenField;
      //## end ZDDocumentOptions::ShowHiddenField%3650151D02C4.attr

      //## begin ZDDocumentOptions::ShowEmptyLine%3650154403C5.attr preserve=no  public: OptionType {U} ApplicationOption
      EOptionType m_ShowEmptyLine;
      //## end ZDDocumentOptions::ShowEmptyLine%3650154403C5.attr

      //## begin ZDDocumentOptions::AutomaticSynchronizeFilename%366A4F5A03BF.attr preserve=no  public: SynchronizationFileType {U} 
      ESynchronizationFileType m_AutomaticSynchronizeFilename;
      //## end ZDDocumentOptions::AutomaticSynchronizeFilename%366A4F5A03BF.attr

      //## begin ZDDocumentOptions::SynchronizeFilename%366A4F7802C8.attr preserve=no  public: CString {U} 
      CString m_SynchronizeFilename;
      //## end ZDDocumentOptions::SynchronizeFilename%366A4F7802C8.attr

      //## begin ZDDocumentOptions::SynchronizationHeader%366A55DB01C5.attr preserve=no  public: BOOL {U} 
      BOOL m_SynchronizationHeader;
      //## end ZDDocumentOptions::SynchronizationHeader%366A55DB01C5.attr

      //## begin ZDDocumentOptions::SynchronizationSeparator%366A5603008C.attr preserve=no  public: SynchronizationSeparatorType {U} 
      ESynchronizationSeparatorType m_SynchronizationSeparator;
      //## end ZDDocumentOptions::SynchronizationSeparator%366A5603008C.attr

    // Additional Private Declarations
      //## begin ZDDocumentOptions%351656F90334.private preserve=yes
      BOOL    m_PrintEmptyStyleWhenEmpty;
      //## end ZDDocumentOptions%351656F90334.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZDDocumentOptions%351656F90334.implementation preserve=yes
      //## end ZDDocumentOptions%351656F90334.implementation

};

//## begin ZDDocumentOptions%351656F90334.postscript preserve=yes
//## end ZDDocumentOptions%351656F90334.postscript

// Class ZDDocumentOptions 

//## Get and Set Operations for Class Attributes (inline)

inline const ELineType ZDDocumentOptions::GetEmptyStyle() const
{
  //## begin ZDDocumentOptions::GetEmptyStyle%351657670046.get preserve=no
  return m_EmptyStyle;
  //## end ZDDocumentOptions::GetEmptyStyle%351657670046.get
}

inline void ZDDocumentOptions::SetEmptyStyle(ELineType value)
{
  //## begin ZDDocumentOptions::SetEmptyStyle%351657670046.set preserve=no
  m_EmptyStyle = value;
  //## end ZDDocumentOptions::SetEmptyStyle%351657670046.set
}

inline const BOOL ZDDocumentOptions::GetIsSynchronizeExchangeFeedFile () const
{
  //## begin ZDDocumentOptions::GetIsSynchronizeExchangeFeedFile%36501278034D.get preserve=no
  return m_IsSynchronizeExchangeFeedFile;
  //## end ZDDocumentOptions::GetIsSynchronizeExchangeFeedFile%36501278034D.get
}

inline void ZDDocumentOptions::SetIsSynchronizeExchangeFeedFile (BOOL value)
{
  //## begin ZDDocumentOptions::SetIsSynchronizeExchangeFeedFile%36501278034D.set preserve=no
  m_IsSynchronizeExchangeFeedFile = value;
  //## end ZDDocumentOptions::SetIsSynchronizeExchangeFeedFile%36501278034D.set
}

inline const int ZDDocumentOptions::GetSynchronizeTimeSequence () const
{
  //## begin ZDDocumentOptions::GetSynchronizeTimeSequence%365012BB03A4.get preserve=no
  return m_SynchronizeTimeSequence;
  //## end ZDDocumentOptions::GetSynchronizeTimeSequence%365012BB03A4.get
}

inline void ZDDocumentOptions::SetSynchronizeTimeSequence (int value)
{
  //## begin ZDDocumentOptions::SetSynchronizeTimeSequence%365012BB03A4.set preserve=no
  m_SynchronizeTimeSequence = value;
  //## end ZDDocumentOptions::SetSynchronizeTimeSequence%365012BB03A4.set
}

inline const EOptionType ZDDocumentOptions::GetShowHiddenField() const
{
  //## begin ZDDocumentOptions::GetShowHiddenField%3650151D02C4.get preserve=no
  return m_ShowHiddenField;
  //## end ZDDocumentOptions::GetShowHiddenField%3650151D02C4.get
}

inline void ZDDocumentOptions::SetShowHiddenField(EOptionType value)
{
  //## begin ZDDocumentOptions::SetShowHiddenField%3650151D02C4.set preserve=no
  m_ShowHiddenField = value;
  //## end ZDDocumentOptions::SetShowHiddenField%3650151D02C4.set
}

inline const EOptionType ZDDocumentOptions::GetShowEmptyLine() const
{
  //## begin ZDDocumentOptions::GetShowEmptyLine%3650154403C5.get preserve=no
  return m_ShowEmptyLine;
  //## end ZDDocumentOptions::GetShowEmptyLine%3650154403C5.get
}

inline void ZDDocumentOptions::SetShowEmptyLine(EOptionType value)
{
  //## begin ZDDocumentOptions::SetShowEmptyLine%3650154403C5.set preserve=no
  m_ShowEmptyLine = value;
  //## end ZDDocumentOptions::SetShowEmptyLine%3650154403C5.set
}

inline const ESynchronizationFileType ZDDocumentOptions::GetAutomaticSynchronizeFilename() const
{
  //## begin ZDDocumentOptions::GetAutomaticSynchronizeFilename%366A4F5A03BF.get preserve=no
  return m_AutomaticSynchronizeFilename;
  //## end ZDDocumentOptions::GetAutomaticSynchronizeFilename%366A4F5A03BF.get
}

inline void ZDDocumentOptions::SetAutomaticSynchronizeFilename(ESynchronizationFileType value)
{
  //## begin ZDDocumentOptions::SetAutomaticSynchronizeFilename%366A4F5A03BF.set preserve=no
  m_AutomaticSynchronizeFilename = value;
  //## end ZDDocumentOptions::SetAutomaticSynchronizeFilename%366A4F5A03BF.set
}

inline const CString ZDDocumentOptions::GetSynchronizeFilename () const
{
  //## begin ZDDocumentOptions::GetSynchronizeFilename%366A4F7802C8.get preserve=no
  return m_SynchronizeFilename;
  //## end ZDDocumentOptions::GetSynchronizeFilename%366A4F7802C8.get
}

inline void ZDDocumentOptions::SetSynchronizeFilename (CString value)
{
  //## begin ZDDocumentOptions::SetSynchronizeFilename%366A4F7802C8.set preserve=no
  m_SynchronizeFilename = value;
  //## end ZDDocumentOptions::SetSynchronizeFilename%366A4F7802C8.set
}

inline const BOOL ZDDocumentOptions::GetSynchronizationHeader () const
{
  //## begin ZDDocumentOptions::GetSynchronizationHeader%366A55DB01C5.get preserve=no
  return m_SynchronizationHeader;
  //## end ZDDocumentOptions::GetSynchronizationHeader%366A55DB01C5.get
}

inline void ZDDocumentOptions::SetSynchronizationHeader (BOOL value)
{
  //## begin ZDDocumentOptions::SetSynchronizationHeader%366A55DB01C5.set preserve=no
  m_SynchronizationHeader = value;
  //## end ZDDocumentOptions::SetSynchronizationHeader%366A55DB01C5.set
}

inline const ESynchronizationSeparatorType ZDDocumentOptions::GetSynchronizationSeparator() const
{
  //## begin ZDDocumentOptions::GetSynchronizationSeparator%366A5603008C.get preserve=no
  return m_SynchronizationSeparator;
  //## end ZDDocumentOptions::GetSynchronizationSeparator%366A5603008C.get
}

inline void ZDDocumentOptions::SetSynchronizationSeparator(ESynchronizationSeparatorType value)
{
  //## begin ZDDocumentOptions::SetSynchronizationSeparator%366A5603008C.set preserve=no
  m_SynchronizationSeparator = value;
  //## end ZDDocumentOptions::SetSynchronizationSeparator%366A5603008C.set
}

//## begin module%351657DC033E.epilog preserve=yes
//## end module%351657DC033E.epilog


#endif
