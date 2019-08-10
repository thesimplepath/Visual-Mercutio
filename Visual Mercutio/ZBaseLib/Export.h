/****************************************************************************
 * ==> PSS_Export ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an export interface                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ExportH
#define PSS_ExportH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#include "Mfc.h"

// processsoft
#include "PSS_StatusBar.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Export interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZUExport : public CWnd
{
public:
    /** Constructor
    *@param fileName - file name
    *@param generateHeader - if TRUE, header will be generated
    *@param separatorType - separator type
    *@param schema - schema
    *@param propagationMode - propagation mode
    *@param emptyWhenZero - if TRUE, empty fields will be filled with 0
    *@param pStatusBar - status bar, can be NULL
    */
    ZUExport(const CString&                fileName        = "",
             BOOL                          generateHeader  = FALSE,
             ESynchronizationSeparatorType separatorType   = E_SS_Automatic,
             const CString&                schema          = g_OriginalSchema,
             int                           propagationMode = g_LocatePageOnly,
             BOOL                          emptyWhenZero   = FALSE,
             PSS_StatusBar*                pStatusBar      = NULL);

    virtual ~ZUExport();


    /**
    * Creates the export class
    *@param fileName - file name
    *@param generateHeader - if TRUE, header will be generated
    *@param separatorType - separator type
    *@param schema - schema
    *@param propagationMode - propagation mode
    *@param emptyWhenZero - if TRUE, empty fields will be filled with 0
    *@param pStatusBar - status bar, can be NULL
    */
    virtual inline void Create(const CString&                fileName,
                               BOOL                          generateHeader  = FALSE,
                               ESynchronizationSeparatorType separatorType   = E_SS_Automatic,
                               const CString&                schema          = g_OriginalSchema,
                               int                           propagationMode = g_LocatePageOnly,
                               BOOL                          emptyWhenZero   = FALSE,
                               PSS_StatusBar*                pStatusBar      = NULL);

    /**
    * Exports the records to a file
    *@return TRUE on success, otherwise FALSE
    */
    virtual BOOL Export();

    //## Operation: Import%901558646
    //    This function imports the file to the document.
    virtual BOOL Import();

    //## Operation: Synchronize%901558647
    //    This function synchronizes the document records and the
    //    file.
    virtual BOOL Synchronize();

    //## Operation: GetExportedLine%901558648
    //    Build the export line and return it.
    virtual CString GetExportedLine(CObject* pObj);

    //## Operation: IsExportedField%901558649
    //    Tests if the field is to be exported.
    virtual BOOL IsExportedField(CObject* pObj) const;

    //## Operation: ProcessLine%901641547
    //    Process the line and updates the document.
    virtual BOOL ProcessLine(CString Line);

    //## Operation: GetHeaderLine%903091424
    //    This function builds the header line.
    virtual CString GetHeaderLine();

    //## Operation: StartSynchronization%911381915
    //    Starts the real time synchronization.
    BOOL StartSynchronization(int TimeValue = 5);

    //## Operation: EndSynchronization%911381916
    //    End the synchronization process.
    void EndSynchronization();

    //## Operation: SourceHasBeenModified%911404698
    //    Called when the document has just been modified.
    virtual void SourceHasBeenModified();

    //## Operation: ExportAdditionalInfo%916336042
    virtual BOOL ExportAdditionalInfo();

    //## Operation: ImportAdditionalInfo%916336043
    virtual BOOL ImportAdditionalInfo();

    //## Operation: PreImport%922203356
    //    This function imports the file to the document.
    virtual BOOL PreImport();

    //## Operation: PostImport%922203357
    //    This function imports the file to the document.
    virtual BOOL PostImport();

    //## Operation: ForecastedTotalObject%922203364
    //    This function should return the forecasted total object.
    virtual double ForecastedTotalObject();

    //## Operation: DoExportLoop%922203367
    //    This function do the loop for export.
    virtual BOOL DoExportLoop();

    //## Operation: PreExport%933007940
    //    This function is called before exporting data.
    virtual BOOL PreExport();

    //## Operation: PostExport%933007941
    //    This function is called after the export is end before
    //    closing the file.
    virtual BOOL PostExport();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: GenerateHeader%35D4173C0103
      //    Flags for which a header generation should be done.
    const BOOL GetGenerateHeader() const;

    //## Attribute: SeparatorType%366A57D800CC
    //    Defines the separator type.
    const ESynchronizationSeparatorType GetSeparatorType() const;

    //## Attribute: SchemaName%35DAB0060145
    //    The schema name used for exportation.
    const CString GetSchemaName() const;

    //## Attribute: PropagationMode%35DAB0470289
    //    The propagation mode for imports.
    const int GetPropagationMode() const;

    //## Attribute: EmptyWhenZero%35DD28CD0297
    //    Defines if during the import, numbers must be emptied if
    //    zero.
    const BOOL GetEmptyWhenZero() const;

    //## Attribute: LastFileDate%3652AD7D02EF
    //    Saves the last file date for the synchronization process.
    const CTime GetLastFileDate() const;
    void SetLastFileDate(CTime value);

    //## Attribute: TimeSynchronizationValue%3652B071027D
    //    Defines the time sequence for synchronization.
    const int GetTimeSynchronizationValue() const;
    void SetTimeSynchronizationValue(int value);

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
    int ReadLine(CString& Line);

    //## Operation: WriteLine%901558651
    //    Writes one line of the file buffer.
    void WriteLine(CString& Line);

    //## Operation: OpenFileCreate%901558652
    //    Open the file in write mode with creation.
    BOOL OpenFileCreate();

    //## Operation: OpenFileRead%901558653
    //    Open the file in read mode.
    BOOL OpenFileRead();

    //## Operation: CloseFile%901558654
    //    Close the file.
    BOOL CloseFile();

    //## Operation: SynchronizationFileUpdated%911404699
    //    Tests if the synchronization file is more recent.
    BOOL SynchronizationFileUpdated();

    //## Operation: AssignSynchronizationFileDate%911404700
    void AssignSynchronizationFileDate();

    //## Operation: BuildLine%916336044
    CString BuildLine(CString Key, CString Value);

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
    PSS_StatusBar* m_pStatusBar;
    //## end ZUExport::pStatusBar%36501976018E.attr

    //## Attribute: SourceIsModified%3652EE5301BA
    //    Specify if the source needs to be exported.
    //## begin ZUExport::SourceIsModified%3652EE5301BA.attr preserve=no  public: BOOL {U} FALSE
    BOOL m_SourceIsModified;
    //## end ZUExport::SourceIsModified%3652EE5301BA.attr

    /// Generated message map
    //{{AFX_MSG(ZUExport)
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    /**
    * Copy constructor
    *@param other - other object to copy from
    */
    ZUExport(const ZUExport& other);

    /**
    * Copy operator
    *@param other - other object to copy from
    *@return copy of itself
    */
    const ZUExport& operator = (const ZUExport& other);


    //## Other Operations (specified)
      //## Operation: ReadFileBuffer%901641546
      //    Read a char buffer from the file.
      //    Once the return value is zero, the file has been
      //    completely processed.
      //    If the return code is -1, an error occured.
    int ReadFileBuffer();

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
    ESynchronizationSeparatorType m_SeparatorType;
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
};

//---------------------------------------------------------------------------
// PSS_Export
//---------------------------------------------------------------------------
void ZUExport::Create(const CString&                fileName,
                      BOOL                          generateHeader,
                      ESynchronizationSeparatorType separatorType,
                      const CString&                schema,
                      int                           propagationMode,
                      BOOL                          emptyWhenZero,
                      PSS_StatusBar*                pStatusBar)
{
    m_Filename = fileName;
    m_GenerateHeader = generateHeader;
    m_SeparatorType = separatorType;
    m_SchemaName = schema;
    m_PropagationMode = propagationMode;
    m_EmptyWhenZero = emptyWhenZero;
    m_pStatusBar = pStatusBar;
}

inline const BOOL ZUExport::GetGenerateHeader() const
{
    return m_GenerateHeader;
}

inline const ESynchronizationSeparatorType ZUExport::GetSeparatorType() const
{
    return m_SeparatorType;
}

inline const CString ZUExport::GetSchemaName() const
{
    return m_SchemaName;
}

inline const int ZUExport::GetPropagationMode() const
{
    return m_PropagationMode;
}

inline const BOOL ZUExport::GetEmptyWhenZero() const
{
    return m_EmptyWhenZero;
}

inline const CTime ZUExport::GetLastFileDate() const
{
    return m_LastFileDate;
}

inline void ZUExport::SetLastFileDate(CTime value)
{
    m_LastFileDate = value;
}

inline const int ZUExport::GetTimeSynchronizationValue() const
{
    return m_TimeSynchronizationValue;
}

inline void ZUExport::SetTimeSynchronizationValue(int value)
{
    m_TimeSynchronizationValue = value;
}

#endif
