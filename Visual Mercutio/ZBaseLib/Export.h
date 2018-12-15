//## begin module%35BCB061033D.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%35BCB061033D.cm

//## begin module%35BCB061033D.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%35BCB061033D.cp

//## Module: Export%35BCB061033D; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\Export.h

#ifndef Export_h
#define Export_h 1

//## begin module%35BCB061033D.additionalIncludes preserve=no
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%35BCB061033D.additionalIncludes

//## begin module%35BCB061033D.includes preserve=yes
//## end module%35BCB061033D.includes

// Mfc
#include "Mfc.h"
//## begin module%35BCB061033D.declarations preserve=no
//## end module%35BCB061033D.declarations

//## begin module%35BCB061033D.additionalDeclarations preserve=yes
#include "AniLoad.h"


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

//## end module%35BCB061033D.additionalDeclarations


//## Class: ZUExport%35BCB0140007
//    This class provides the export interface.
//## Category: ZUtil library::Export classes%36F7CCFF024A
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZUExport : public CWnd  //## Inherits: <unnamed>%3652B4BF0188
{
  //## begin ZUExport%35BCB0140007.initialDeclarations preserve=yes
  //## end ZUExport%35BCB0140007.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZUExport%901558644
      //    Constructs an export class with the filename and the
      //    document pointer
      ZUExport (CString Filename = "", BOOL GenerateHeader = FALSE, SynchronizationSeparatorType SeparatorType = AutomaticSeparator, CString Schema = szOriginalSchema, int PropagationMode = LocatePageOnly, BOOL EmptyWhenZero = FALSE, ZIStatusBar* pStatusBar = NULL);

    //## Destructor (generated)
      ~ZUExport();


    //## Other Operations (specified)
      //## Operation: Create%901558643
      //    Create the export class.
      virtual void Create (CString Filename, BOOL GenerateHeader = FALSE, SynchronizationSeparatorType SeparatorType = AutomaticSeparator, CString Schema = szOriginalSchema, int PropagationMode = LocatePageOnly, BOOL EmptyWhenZero = FALSE, ZIStatusBar* pStatusBar = NULL);

      //## Operation: Export%901558645
      //    This function exports the records to a file.
      virtual BOOL Export ();

      //## Operation: Import%901558646
      //    This function imports the file to the document.
      virtual BOOL Import ();

      //## Operation: Synchronize%901558647
      //    This function synchronizes the document records and the
      //    file.
      virtual BOOL Synchronize ();

      //## Operation: GetExportedLine%901558648
      //    Build the export line and return it.
      virtual CString GetExportedLine (CObject* pObj);

      //## Operation: IsExportedField%901558649
      //    Tests if the field is to be exported.
      virtual BOOL IsExportedField (CObject* pObj) const;

      //## Operation: ProcessLine%901641547
      //    Process the line and updates the document.
      virtual BOOL ProcessLine (CString Line);

      //## Operation: GetHeaderLine%903091424
      //    This function builds the header line.
      virtual CString GetHeaderLine ();

      //## Operation: StartSynchronization%911381915
      //    Starts the real time synchronization.
      BOOL StartSynchronization (int TimeValue = 5);

      //## Operation: EndSynchronization%911381916
      //    End the synchronization process.
      void EndSynchronization ();

      //## Operation: SourceHasBeenModified%911404698
      //    Called when the document has just been modified.
      virtual void SourceHasBeenModified ();

      //## Operation: ExportAdditionalInfo%916336042
      virtual BOOL ExportAdditionalInfo ();

      //## Operation: ImportAdditionalInfo%916336043
      virtual BOOL ImportAdditionalInfo ();

      //## Operation: PreImport%922203356
      //    This function imports the file to the document.
      virtual BOOL PreImport ();

      //## Operation: PostImport%922203357
      //    This function imports the file to the document.
      virtual BOOL PostImport ();

      //## Operation: ForecastedTotalObject%922203364
      //    This function should return the forecasted total object.
      virtual double ForecastedTotalObject ();

      //## Operation: DoExportLoop%922203367
      //    This function do the loop for export.
      virtual BOOL DoExportLoop ();

      //## Operation: PreExport%933007940
      //    This function is called before exporting data.
      virtual BOOL PreExport ();

      //## Operation: PostExport%933007941
      //    This function is called after the export is end before
      //    closing the file.
      virtual BOOL PostExport ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: GenerateHeader%35D4173C0103
      //    Flags for which a header generation should be done.
      const BOOL GetGenerateHeader () const;

      //## Attribute: SeparatorType%366A57D800CC
      //    Defines the separator type.
      const SynchronizationSeparatorType GetSeparatorType () const;

      //## Attribute: SchemaName%35DAB0060145
      //    The schema name used for exportation.
      const CString GetSchemaName () const;

      //## Attribute: PropagationMode%35DAB0470289
      //    The propagation mode for imports.
      const int GetPropagationMode () const;

      //## Attribute: EmptyWhenZero%35DD28CD0297
      //    Defines if during the import, numbers must be emptied if
      //    zero.
      const BOOL GetEmptyWhenZero () const;

      //## Attribute: LastFileDate%3652AD7D02EF
      //    Saves the last file date for the synchronization process.
      const CTime GetLastFileDate () const;
      void SetLastFileDate (CTime value);

      //## Attribute: TimeSynchronizationValue%3652B071027D
      //    Defines the time sequence for synchronization.
      const int GetTimeSynchronizationValue () const;
      void SetTimeSynchronizationValue (int value);

    // Additional Public Declarations
      //## begin ZUExport%35BCB0140007.public preserve=yes
      //## end ZUExport%35BCB0140007.public

  protected:

    //## Other Operations (specified)
      //## Operation: ReadLine%901558650
      //    Returns one line of the file buffer.
      //    Once the return value is zero, the file has been
      //    completely processed.
      //    If the return code is -1, an error occured.
      int ReadLine (CString& Line);

      //## Operation: WriteLine%901558651
      //    Writes one line of the file buffer.
      void WriteLine (CString& Line);

      //## Operation: OpenFileCreate%901558652
      //    Open the file in write mode with creation.
      BOOL OpenFileCreate ();

      //## Operation: OpenFileRead%901558653
      //    Open the file in read mode.
      BOOL OpenFileRead ();

      //## Operation: CloseFile%901558654
      //    Close the file.
      BOOL CloseFile ();

      //## Operation: SynchronizationFileUpdated%911404699
      //    Tests if the synchronization file is more recent.
      BOOL SynchronizationFileUpdated ();

      //## Operation: AssignSynchronizationFileDate%911404700
      void AssignSynchronizationFileDate ();

      //## Operation: BuildLine%916336044
      CString BuildLine (CString Key, CString Value);

    // Data Members for Class Attributes

      //## Attribute: Filename%35BCB4750081
      //    Defines the filename used to import/export the
      //    information
      //## begin ZUExport::Filename%35BCB4750081.attr preserve=no  protected: CString {U} 
      CString m_Filename;
      //## end ZUExport::Filename%35BCB4750081.attr

      //## Attribute: pStatusBar%36501976018E
      //    Points to the status bar used to display progress bar.
      //## begin ZUExport::pStatusBar%36501976018E.attr preserve=no  public: ZIStatusBar* {U} 
      ZIStatusBar* m_pStatusBar;
      //## end ZUExport::pStatusBar%36501976018E.attr

      //## Attribute: SourceIsModified%3652EE5301BA
      //    Specify if the source needs to be exported.
      //## begin ZUExport::SourceIsModified%3652EE5301BA.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_SourceIsModified;
      //## end ZUExport::SourceIsModified%3652EE5301BA.attr

    // Additional Protected Declarations
      //## begin ZUExport%35BCB0140007.protected preserve=yes
    // message handlers
    //{{AFX_MSG(ZUExport)
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
      //## end ZUExport%35BCB0140007.protected
  private:
    //## Constructors (generated)
      ZUExport(const ZUExport &right);

    //## Assignment Operation (generated)
      const ZUExport & operator=(const ZUExport &right);


    //## Other Operations (specified)
      //## Operation: ReadFileBuffer%901641546
      //    Read a char buffer from the file.
      //    Once the return value is zero, the file has been
      //    completely processed.
      //    If the return code is -1, an error occured.
      int ReadFileBuffer ();

    // Data Members for Class Attributes

      //## Attribute: pCurrent%35BCB4B700C2
      //    This pointer is used when extracting the line from the
      //    file.
      //## begin ZUExport::pCurrent%35BCB4B700C2.attr preserve=no  private: char* {U} NULL
      char* m_pCurrent;
      //## end ZUExport::pCurrent%35BCB4B700C2.attr

      //## Attribute: FileBuffer%35BCB4F20348
      //    Used to read information from file.
      //## begin ZUExport::FileBuffer%35BCB4F20348.attr preserve=no  private: char[300] {U} 
      char m_FileBuffer[300];
      //## end ZUExport::FileBuffer%35BCB4F20348.attr

      //## Attribute: File%35BCBD7600EA
      //    Points to the CFile member class.
      //## begin ZUExport::File%35BCBD7600EA.attr preserve=no  private: CFile {U} 
      CFile m_File;
      //## end ZUExport::File%35BCBD7600EA.attr

      //## Attribute: pNext%35BCC86D0172
      //    Pointer to the next valid return line.
      //## begin ZUExport::pNext%35BCC86D0172.attr preserve=no  private: char* {U} 
      char* m_pNext;
      //## end ZUExport::pNext%35BCC86D0172.attr

      //## begin ZUExport::GenerateHeader%35D4173C0103.attr preserve=no  public: BOOL {U} 
      BOOL m_GenerateHeader;
      //## end ZUExport::GenerateHeader%35D4173C0103.attr

      //## begin ZUExport::SeparatorType%366A57D800CC.attr preserve=no  public: SynchronizationSeparatorType {U} 
      SynchronizationSeparatorType m_SeparatorType;
      //## end ZUExport::SeparatorType%366A57D800CC.attr

      //## begin ZUExport::SchemaName%35DAB0060145.attr preserve=no  public: CString {U} 
      CString m_SchemaName;
      //## end ZUExport::SchemaName%35DAB0060145.attr

      //## begin ZUExport::PropagationMode%35DAB0470289.attr preserve=no  public: int {U} 
      int m_PropagationMode;
      //## end ZUExport::PropagationMode%35DAB0470289.attr

      //## begin ZUExport::EmptyWhenZero%35DD28CD0297.attr preserve=no  public: BOOL {U} 
      BOOL m_EmptyWhenZero;
      //## end ZUExport::EmptyWhenZero%35DD28CD0297.attr

      //## begin ZUExport::LastFileDate%3652AD7D02EF.attr preserve=no  public: CTime {U} 
      CTime m_LastFileDate;
      //## end ZUExport::LastFileDate%3652AD7D02EF.attr

      //## begin ZUExport::TimeSynchronizationValue%3652B071027D.attr preserve=no  public: int {U} 5
      int m_TimeSynchronizationValue;
      //## end ZUExport::TimeSynchronizationValue%3652B071027D.attr

    // Additional Private Declarations
      //## begin ZUExport%35BCB0140007.private preserve=yes
      //## end ZUExport%35BCB0140007.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZUExport%35BCB0140007.implementation preserve=yes
      //## end ZUExport%35BCB0140007.implementation

};

//## begin ZUExport%35BCB0140007.postscript preserve=yes
//## end ZUExport%35BCB0140007.postscript

// Class ZUExport 


//## Other Operations (inline)
inline void ZUExport::Create (CString Filename, BOOL GenerateHeader, SynchronizationSeparatorType SeparatorType, CString Schema, int PropagationMode, BOOL EmptyWhenZero, ZIStatusBar* pStatusBar)
{
  //## begin ZUExport::Create%901558643.body preserve=yes
      m_Filename = Filename;
      m_GenerateHeader = GenerateHeader;
      m_SeparatorType = SeparatorType;
    m_SchemaName = Schema;
    m_PropagationMode = PropagationMode;
    m_EmptyWhenZero = EmptyWhenZero;
    m_pStatusBar = pStatusBar;
  //## end ZUExport::Create%901558643.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const BOOL ZUExport::GetGenerateHeader () const
{
  //## begin ZUExport::GetGenerateHeader%35D4173C0103.get preserve=no
  return m_GenerateHeader;
  //## end ZUExport::GetGenerateHeader%35D4173C0103.get
}

inline const SynchronizationSeparatorType ZUExport::GetSeparatorType () const
{
  //## begin ZUExport::GetSeparatorType%366A57D800CC.get preserve=no
  return m_SeparatorType;
  //## end ZUExport::GetSeparatorType%366A57D800CC.get
}

inline const CString ZUExport::GetSchemaName () const
{
  //## begin ZUExport::GetSchemaName%35DAB0060145.get preserve=no
  return m_SchemaName;
  //## end ZUExport::GetSchemaName%35DAB0060145.get
}

inline const int ZUExport::GetPropagationMode () const
{
  //## begin ZUExport::GetPropagationMode%35DAB0470289.get preserve=no
  return m_PropagationMode;
  //## end ZUExport::GetPropagationMode%35DAB0470289.get
}

inline const BOOL ZUExport::GetEmptyWhenZero () const
{
  //## begin ZUExport::GetEmptyWhenZero%35DD28CD0297.get preserve=no
  return m_EmptyWhenZero;
  //## end ZUExport::GetEmptyWhenZero%35DD28CD0297.get
}

inline const CTime ZUExport::GetLastFileDate () const
{
  //## begin ZUExport::GetLastFileDate%3652AD7D02EF.get preserve=no
  return m_LastFileDate;
  //## end ZUExport::GetLastFileDate%3652AD7D02EF.get
}

inline void ZUExport::SetLastFileDate (CTime value)
{
  //## begin ZUExport::SetLastFileDate%3652AD7D02EF.set preserve=no
  m_LastFileDate = value;
  //## end ZUExport::SetLastFileDate%3652AD7D02EF.set
}

inline const int ZUExport::GetTimeSynchronizationValue () const
{
  //## begin ZUExport::GetTimeSynchronizationValue%3652B071027D.get preserve=no
  return m_TimeSynchronizationValue;
  //## end ZUExport::GetTimeSynchronizationValue%3652B071027D.get
}

inline void ZUExport::SetTimeSynchronizationValue (int value)
{
  //## begin ZUExport::SetTimeSynchronizationValue%3652B071027D.set preserve=no
  m_TimeSynchronizationValue = value;
  //## end ZUExport::SetTimeSynchronizationValue%3652B071027D.set
}

//## begin module%35BCB061033D.epilog preserve=yes
//## end module%35BCB061033D.epilog


#endif
