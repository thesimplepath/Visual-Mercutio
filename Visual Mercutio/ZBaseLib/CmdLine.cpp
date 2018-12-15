//## begin module%375181E901DC.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%375181E901DC.cm

//## begin module%375181E901DC.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%375181E901DC.cp

//## Module: CmdLine%375181E901DC; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\CmdLine.cpp

//## begin module%375181E901DC.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%375181E901DC.additionalIncludes

//## begin module%375181E901DC.includes preserve=yes
//## end module%375181E901DC.includes

// CmdLine
#include "CmdLine.h"
//## begin module%375181E901DC.declarations preserve=no
//## end module%375181E901DC.declarations

//## begin module%375181E901DC.additionalDeclarations preserve=yes

#include "ZUFileLauncher.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 21 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZUCommandLine, CObject, def_Version )
//## end module%375181E901DC.additionalDeclarations

// Class ZUCommandLine 

ZUCommandLine::ZUCommandLine( const ZUCommandLine &right )
    //## begin ZUCommandLine::ZUCommandLine%copy.hasinit preserve=no
    //## end ZUCommandLine::ZUCommandLine%copy.hasinit
    //## begin ZUCommandLine::ZUCommandLine%copy.initialization preserve=yes
    //## end ZUCommandLine::ZUCommandLine%copy.initialization
{
    //## begin ZUCommandLine::ZUCommandLine%copy.body preserve=yes
    *this = right;
    //## end ZUCommandLine::ZUCommandLine%copy.body
}

ZUCommandLine::ZUCommandLine ( const CString    CommandLine,
                               const CString    StartupDirectory,
                               const CString    Arguments,
                               DWORD            Priority)
    //## begin ZUCommandLine::ZUCommandLine%928085167.hasinit preserve=no
    //## end ZUCommandLine::ZUCommandLine%928085167.hasinit
    //## begin ZUCommandLine::ZUCommandLine%928085167.initialization preserve=yes
    : m_CommandLine            ( CommandLine ),
      m_StartupDirectory    ( StartupDirectory ),
      m_Arguments            ( Arguments ),
      m_Priority            ( Priority ),
      m_HasBeenLaunched        ( FALSE ),
      m_pProcessInformation    ( NULL )
      //## end ZUCommandLine::ZUCommandLine%928085167.initialization
{
    //## begin ZUCommandLine::ZUCommandLine%928085167.body preserve=yes
    //## end ZUCommandLine::ZUCommandLine%928085167.body
}

ZUCommandLine::~ZUCommandLine()
{
    //## begin ZUCommandLine::~ZUCommandLine%.body preserve=yes
    if ( m_pProcessInformation )
    {
        delete m_pProcessInformation;
        m_pProcessInformation = NULL;
    }
    //## end ZUCommandLine::~ZUCommandLine%.body
}

const ZUCommandLine & ZUCommandLine::operator=( const ZUCommandLine &right )
{
  //## begin ZUCommandLine::operator=%.body preserve=yes
    m_CommandLine        = right.m_CommandLine;
    m_StartupDirectory    = right.m_StartupDirectory;
    m_Arguments            = right.m_Arguments;
    m_Priority            = right.m_Priority;

    return *this;
  //## end ZUCommandLine::operator=%.body
}

//## Other Operations (implementation)
void ZUCommandLine::Initialize ( const CString    CommandLine,
                                 const CString    StartupDirectory,
                                 const CString    Arguments,
                                 DWORD            Priority )
{
    //## begin ZUCommandLine::Initialize%934529056.body preserve=yes
    m_CommandLine        = CommandLine;
    m_StartupDirectory    = StartupDirectory;
    m_Arguments            = Arguments;
    m_Priority            = Priority;
    //## end ZUCommandLine::Initialize%934529056.body
}

BOOL ZUCommandLine::Launch ()
{
    //## begin ZUCommandLine::Launch%928085168.body preserve=yes
    ZUFileLauncher    FileLauncher( m_CommandLine, FLMopen, m_Arguments, m_StartupDirectory );
    return FileLauncher.Launch();
    //## end ZUCommandLine::Launch%928085168.body
}

void ZUCommandLine::Serialize ( CArchive& ar )
{
    //## begin ZUCommandLine::Serialize%928085169.body preserve=yes
    if ( ar.IsStoring() )
    {
        // Write the elements
        ar << m_CommandLine;
        ar << m_StartupDirectory;
        ar << m_Arguments;
        ar << m_Priority;
    }
    else
    {
        ar >> m_CommandLine;
        ar >> m_StartupDirectory;
        ar >> m_Arguments;
        ar >> m_Priority;
    }
    //## end ZUCommandLine::Serialize%928085169.body
}

// Additional Declarations
//## begin ZUCommandLine%375171A7021D.declarations preserve=yes
//## end ZUCommandLine%375171A7021D.declarations

//## begin module%375181E901DC.epilog preserve=yes
//## end module%375181E901DC.epilog
