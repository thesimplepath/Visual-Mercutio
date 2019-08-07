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
    DECLARE_SERIAL(PSS_CommandLine)

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
        virtual void Initialize(const CString& commandLine,
                                const CString& startupDirectory = "",
                                const CString& arguments        = "",
                                DWORD          priority         = NORMAL_PRIORITY_CLASS);

        /**
        * Launches the command line
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Launch();

        /**
        * Serializes the class content
        *@param ar - archive in which the class content should be written
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Gets the launch command line process information
        *@return the launch command line process information
        */
        virtual inline ::PROCESS_INFORMATION* GetProcessInformation() const;

        /**
        * Gets the command line
        *@return the command line
        */
        virtual inline const CString GetCommandLine () const;

        /**
        * Sets the command line
        *@param value - the command line
        */
        virtual inline void SetCommandLine(const CString& value);

        /**
        * Gets the arguments
        *@return the arguments
        */
        virtual inline const CString GetArguments () const;

        /**
        * Sets the arguments
        *@param value - the arguments
        */
        virtual inline void SetArguments(const CString& value);

        /**
        * Gets the startup directory
        *@return the startup directory
        */
        virtual inline const CString GetStartupDirectory() const;

        /**
        * Sets the startup directory
        *@param value - the startup directory
        */
        virtual inline void SetStartupDirectory(const CString& value);

        /**
        * Gets the priority
        *@return the priority
        */
        virtual inline const DWORD GetPriority() const;

        /**
        * Sets the priority
        *@param value - the priority
        */
        virtual inline void SetPriority(DWORD value);

    private:
        ::PROCESS_INFORMATION* m_pProcessInfo;
        CString                m_CommandLine;
        CString                m_Arguments;
        CString                m_StartupDir;
        DWORD                  m_Priority;
        BOOL                   m_HasBeenLaunched;
};

//---------------------------------------------------------------------------
// PSS_CommandLine
//---------------------------------------------------------------------------
::PROCESS_INFORMATION* PSS_CommandLine::GetProcessInformation() const
{
    return m_pProcessInfo;
}
//---------------------------------------------------------------------------
const CString PSS_CommandLine::GetCommandLine() const
{
    return m_CommandLine;
}
//---------------------------------------------------------------------------
void PSS_CommandLine::SetCommandLine(const CString& value)
{
    m_CommandLine = value;
}
//---------------------------------------------------------------------------
const CString PSS_CommandLine::GetArguments() const
{
    return m_Arguments;
}
//---------------------------------------------------------------------------
void PSS_CommandLine::SetArguments(const CString& value)
{
    m_Arguments = value;
}
//---------------------------------------------------------------------------
const CString PSS_CommandLine::GetStartupDir() const
{
    return m_StartupDir;
}
//---------------------------------------------------------------------------
void PSS_CommandLine::SetStartupDir(const CString& value)
{
    m_StartupDir = value;
}
//---------------------------------------------------------------------------
const DWORD PSS_CommandLine::GetPriority() const
{
    return m_Priority;
}
//---------------------------------------------------------------------------
void PSS_CommandLine::SetPriority(DWORD value)
{
    m_Priority = value;
}
//---------------------------------------------------------------------------

#endif
