#ifndef ProcOpt_h
#define ProcOpt_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


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


class AFX_EXT_CLASS ZDProcessDocumentOptions 
{

  public:
      ZDProcessDocumentOptions();

      ZDProcessDocumentOptions(const ZDProcessDocumentOptions &right);

      virtual ~ZDProcessDocumentOptions();

      const ZDProcessDocumentOptions & operator=(const ZDProcessDocumentOptions &right);


      CString BuildSynchronizationFileName (CString DocumentFilename);

      //    Store from the archive to the object Document Option.
      AFX_EXT_API friend CArchive& operator >> (CArchive& ar, ZDProcessDocumentOptions& DocOptions);

      //    Store the object Document Option to the archive.
      AFX_EXT_API friend CArchive& operator << (CArchive& ar, const ZDProcessDocumentOptions& DocOptions);

      //    Specifiy if it is necessary to synchronize the feed data
      //    file.
      const BOOL GetIsSynchronizeExchangeFeedFile () const;
      void SetIsSynchronizeExchangeFeedFile (BOOL value);

      //    Defines if the synchronization time (in seconds).
      const int GetSynchronizeTimeSequence () const;
      void SetSynchronizeTimeSequence (int value);

      //## Attribute: AutomaticSynchronizeFilename%366A4F5A03BF
      //    Is the filename automatically created.
      const ESynchronizationFileType GetAutomaticSynchronizeFilename() const;
      void SetAutomaticSynchronizeFilename(ESynchronizationFileType value);

      //    The synchronization filename if not automatic.
      const CString GetSynchronizeFilename () const;
      void SetSynchronizeFilename (CString value);

      //    Ceates or not a synchronization header
      const BOOL GetSynchronizationHeader () const;
      void SetSynchronizationHeader (BOOL value);

      //    Defines the seperator type.
      const ESynchronizationSeparatorType GetSynchronizationSeparator() const;
      void SetSynchronizationSeparator(ESynchronizationSeparatorType value);


  protected:

  private:

      BOOL m_IsSynchronizeExchangeFeedFile;

      int m_SynchronizeTimeSequence;

      ESynchronizationFileType m_AutomaticSynchronizeFilename;

      CString m_SynchronizeFilename;

      BOOL m_SynchronizationHeader;

      ESynchronizationSeparatorType m_SynchronizationSeparator;

  private: 

};


// Class ZDProcessDocumentOptions 

// Get and Set Operations for Class Attributes (inline)


inline const BOOL ZDProcessDocumentOptions::GetIsSynchronizeExchangeFeedFile () const
{
  return m_IsSynchronizeExchangeFeedFile;
}

inline void ZDProcessDocumentOptions::SetIsSynchronizeExchangeFeedFile (BOOL value)
{
  m_IsSynchronizeExchangeFeedFile = value;
}

inline const int ZDProcessDocumentOptions::GetSynchronizeTimeSequence () const
{
  return m_SynchronizeTimeSequence;
}

inline void ZDProcessDocumentOptions::SetSynchronizeTimeSequence (int value)
{
  m_SynchronizeTimeSequence = value;
}

inline const ESynchronizationFileType ZDProcessDocumentOptions::GetAutomaticSynchronizeFilename() const
{
  return m_AutomaticSynchronizeFilename;
}

inline void ZDProcessDocumentOptions::SetAutomaticSynchronizeFilename(ESynchronizationFileType value)
{
  m_AutomaticSynchronizeFilename = value;
}

inline const CString ZDProcessDocumentOptions::GetSynchronizeFilename () const
{
  return m_SynchronizeFilename;
}

inline void ZDProcessDocumentOptions::SetSynchronizeFilename (CString value)
{
  m_SynchronizeFilename = value;
}

inline const BOOL ZDProcessDocumentOptions::GetSynchronizationHeader () const
{
  return m_SynchronizationHeader;
}

inline void ZDProcessDocumentOptions::SetSynchronizationHeader (BOOL value)
{
  m_SynchronizationHeader = value;
}

inline const ESynchronizationSeparatorType ZDProcessDocumentOptions::GetSynchronizationSeparator() const
{
  return m_SynchronizationSeparator;
}

inline void ZDProcessDocumentOptions::SetSynchronizationSeparator(ESynchronizationSeparatorType value)
{
  m_SynchronizationSeparator = value;
}

#endif
