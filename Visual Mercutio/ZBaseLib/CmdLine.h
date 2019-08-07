/****************************************************************************
 * ==> PSS_CommandLine -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an encapsulated command line                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CommandLineH
#define PSS_CommandLineH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#include "Mfc.h"

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
* Encapsulated command line
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_CommandLine : public CObject
{
public:
    /**
    * Constructor
    *@param commandLine - command line to process
    *@param startupDir - startup directory
    *@param arguments - arguments
    *@param priority - priority
    */
    PSS_CommandLine(const CString& commandLine = "",
                    const CString& startupDir  = "",
                    const CString& arguments   = "",
                    DWORD          priority    = NORMAL_PRIORITY_CLASS);

    /**
    * Copy constructor
    *@param other - other object to copy from
    */
    PSS_CommandLine(const PSS_CommandLine& other);

    virtual ~PSS_CommandLine();

    /**
    * Copy operator
    *@param other - other object to copy from
    *@return copy of itself
    */
    const PSS_CommandLine& operator = (const PSS_CommandLine& other);

    /**
    * Initializes the command line
    *@param commandLine - command line to process
    *@param startupDir - startup directory
    *@param arguments - arguments
    *@param priority - priority
    */
    void Initialize(const CString& commandLine,
                    const CString& startupDirectory = "",
                    const CString& arguments        = "",
                    DWORD          priority         = NORMAL_PRIORITY_CLASS);

      /**
      * Launches the command line
      *@return TRUE on success, otherwise FALSE
      */
      BOOL Launch();

      /**
      * Serializes the class content
      *@param ar - archive in which the class content should be written
      */
      virtual void Serialize(CArchive& ar);

      /**
      * Get the launch command lineprocess information
      *@return the launch command lineprocess information
      */
      ::PROCESS_INFORMATION* GetProcessInformation() const;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: CommandLine%37517E030227
      //    The command line
      const CString GetCommandLine () const;
      void SetCommandLine (CString value);

      //## Attribute: Arguments%37B3DDD40324
      //    Contains the arguments.
      const CString GetArguments () const;
      void SetArguments (CString value);

      //## Attribute: StartupDirectory%37517E090117
      //    The startup directory.
      const CString GetStartupDirectory () const;
      void SetStartupDirectory (CString value);

      //## Attribute: Priority%3751A0BB0141
      const DWORD GetPriority () const;
      void SetPriority (DWORD value);

    // Additional Public Declarations
      //## begin ZUCommandLine%375171A7021D.public preserve=yes
      //## end ZUCommandLine%375171A7021D.public

  protected:
    // Additional Protected Declarations
      //## begin ZUCommandLine%375171A7021D.protected preserve=yes
    DECLARE_SERIAL(ZUCommandLine)
      //## end ZUCommandLine%375171A7021D.protected
  private:
    // Data Members for Class Attributes

      //## begin ZUCommandLine::CommandLine%37517E030227.attr preserve=no  public: CString {U} 
      CString m_CommandLine;
      //## end ZUCommandLine::CommandLine%37517E030227.attr

      //## begin ZUCommandLine::Arguments%37B3DDD40324.attr preserve=no  public: CString {U} 
      CString m_Arguments;
      //## end ZUCommandLine::Arguments%37B3DDD40324.attr

      //## begin ZUCommandLine::StartupDirectory%37517E090117.attr preserve=no  public: CString {U} 
      CString m_StartupDirectory;
      //## end ZUCommandLine::StartupDirectory%37517E090117.attr

      //## begin ZUCommandLine::Priority%3751A0BB0141.attr preserve=no  public: DWORD {U} 
      DWORD m_Priority;
      //## end ZUCommandLine::Priority%3751A0BB0141.attr

      //## Attribute: pProcessInformation%3751A151018D
      //    The process information used to receive information
      //    about the process newly created.
      //## begin ZUCommandLine::pProcessInformation%3751A151018D.attr preserve=no  public: PROCESS_INFORMATION* {U} 
      PROCESS_INFORMATION* m_pProcessInformation;
      //## end ZUCommandLine::pProcessInformation%3751A151018D.attr

      //## Attribute: HasBeenLaunched%3751A184001D
      //## begin ZUCommandLine::HasBeenLaunched%3751A184001D.attr preserve=no  public: BOOL {U} 
      BOOL m_HasBeenLaunched;
      //## end ZUCommandLine::HasBeenLaunched%3751A184001D.attr

    // Additional Private Declarations
      //## begin ZUCommandLine%375171A7021D.private preserve=yes
      //## end ZUCommandLine%375171A7021D.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZUCommandLine%375171A7021D.implementation preserve=yes
      //## end ZUCommandLine%375171A7021D.implementation

};

//## begin ZUCommandLine%375171A7021D.postscript preserve=yes
//## end ZUCommandLine%375171A7021D.postscript

// Class ZUCommandLine 


//## Other Operations (inline)
inline PROCESS_INFORMATION* ZUCommandLine::GetProcessInformation () const
{
  //## begin ZUCommandLine::GetProcessInformation%928085170.body preserve=yes
    return m_pProcessInformation;
  //## end ZUCommandLine::GetProcessInformation%928085170.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const CString ZUCommandLine::GetCommandLine () const
{
  //## begin ZUCommandLine::GetCommandLine%37517E030227.get preserve=no
  return m_CommandLine;
  //## end ZUCommandLine::GetCommandLine%37517E030227.get
}

inline void ZUCommandLine::SetCommandLine (CString value)
{
  //## begin ZUCommandLine::SetCommandLine%37517E030227.set preserve=no
  m_CommandLine = value;
  //## end ZUCommandLine::SetCommandLine%37517E030227.set
}

inline const CString ZUCommandLine::GetArguments () const
{
  //## begin ZUCommandLine::GetArguments%37B3DDD40324.get preserve=no
  return m_Arguments;
  //## end ZUCommandLine::GetArguments%37B3DDD40324.get
}

inline void ZUCommandLine::SetArguments (CString value)
{
  //## begin ZUCommandLine::SetArguments%37B3DDD40324.set preserve=no
  m_Arguments = value;
  //## end ZUCommandLine::SetArguments%37B3DDD40324.set
}

inline const CString ZUCommandLine::GetStartupDirectory () const
{
  //## begin ZUCommandLine::GetStartupDirectory%37517E090117.get preserve=no
  return m_StartupDirectory;
  //## end ZUCommandLine::GetStartupDirectory%37517E090117.get
}

inline void ZUCommandLine::SetStartupDirectory (CString value)
{
  //## begin ZUCommandLine::SetStartupDirectory%37517E090117.set preserve=no
  m_StartupDirectory = value;
  //## end ZUCommandLine::SetStartupDirectory%37517E090117.set
}

inline const DWORD ZUCommandLine::GetPriority () const
{
  //## begin ZUCommandLine::GetPriority%3751A0BB0141.get preserve=no
  return m_Priority;
  //## end ZUCommandLine::GetPriority%3751A0BB0141.get
}

inline void ZUCommandLine::SetPriority (DWORD value)
{
  //## begin ZUCommandLine::SetPriority%3751A0BB0141.set preserve=no
  m_Priority = value;
  //## end ZUCommandLine::SetPriority%3751A0BB0141.set
}

//## begin module%375181F103E6.epilog preserve=yes
//## end module%375181F103E6.epilog


#endif
