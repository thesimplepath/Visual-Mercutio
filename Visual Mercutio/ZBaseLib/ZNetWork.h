//## begin module%366D71B0009D.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%366D71B0009D.cm

//## begin module%366D71B0009D.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%366D71B0009D.cp

//## Module: ZNetWork%366D71B0009D; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZNetWork.h

#ifndef ZNetWork_h
#define ZNetWork_h 1

//## begin module%366D71B0009D.additionalIncludes preserve=no
//## end module%366D71B0009D.additionalIncludes

//## begin module%366D71B0009D.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


const    int MAX_MNETS = 5;
#ifndef _WIN32
    #include "winnet.h"
#endif

#include "ZNetResourceManager.h"

//## end module%366D71B0009D.includes

//## begin module%366D71B0009D.declarations preserve=no
//## end module%366D71B0009D.declarations

//## begin module%366D71B0009D.additionalDeclarations preserve=yes
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
//## end module%366D71B0009D.additionalDeclarations


//## Class: ZUNetwork%366D71D50245
//    This class provides functionality for the network.
//## Category: ZBaseLib::Network classes%366D71CA007D
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZUNetwork 
{
  //## begin ZUNetwork%366D71D50245.initialDeclarations preserve=yes
  //## end ZUNetwork%366D71D50245.initialDeclarations

  public:
    //## Constructors (generated)
      ZUNetwork();

    //## Destructor (generated)
      ~ZUNetwork();


    //## Other Operations (specified)
      //## Operation: GetNetworkDrives%947664380
      //    Retreive mapped or unmapped network drive. All fixed and
      //    floppy drives are not included.
      bool GetNetworkDrives (CStringArray& DriveArray);

      //## Operation: Map%947664376
      //    Map a connection.
      //    If the local device is not specified, the function makes
      //    a connection to the network resource without redirecting
      //    a local device.
      bool Map (CString UNC, CString Local = "", bool CanSpecifyUsername = true);

      //## Operation: GetMap%947664377
      //    Get the UNC correspondance of a local map.
      CString GetMap (CString Local);

      //## Operation: RemoveConnection%947664378
      //    Remove an existing connection.
      //    The connection string specifies the name of either the
      //    redirected local device or the remote network resource
      //    to disconnect from. If this parameter specifies a
      //    redirected local resource, only the specified
      //    redirection is broken; otherwise, all connections to the
      //    remote network resource are broken.
      BOOL RemoveConnection (CString Connection);

      //## Operation: OpenConnection%945889219
      //    Open a network connection.
      bool OpenConnection (CString Path, HWND hwndOwner = NULL, bool Temporarily = true, bool Interactive = true);

      //## Operation: EnumConnections%947664379
      //    Enum existing connections.
      bool EnumConnections (ZNetResourceManager& ResourceManager);

      //## Operation: GetFreeConnections%947664375
      //    Retreive all free connections.
      bool GetFreeConnections (CStringArray& FreeConnectionArray);

      //## Operation: GetUNC%945619906
      CString GetUNC (const CString value);

      //## Operation: GetNetworkErrorNo%913142849
      //    returns the number of the network error.
      WORD GetNetworkErrorNo ();

      //## Operation: GetNetworkErrorMessage%913142850
      //    return the error message.
      CString GetNetworkErrorMessage ();

      //## Operation: GetUserName%913142851
      //    Get the connect user. If the username is empty, check
      //    the error message.
      CString GetUserName ();

    // Additional Public Declarations
      //## begin ZUNetwork%366D71D50245.public preserve=yes
      //## end ZUNetwork%366D71D50245.public

  protected:
    // Additional Protected Declarations
      //## begin ZUNetwork%366D71D50245.protected preserve=yes
      //## end ZUNetwork%366D71D50245.protected

  private:
    //## Constructors (generated)
      ZUNetwork(const ZUNetwork &right);

    //## Assignment Operation (generated)
      const ZUNetwork & operator=(const ZUNetwork &right);


    //## Other Operations (specified)
      //## Operation: MNetDetect%913142852
      //    This function determine whether the Windows for
      //    Workgroups Multinet driver is present.
      BOOL MNetDetect ();

      //## Operation: WFWDetect%913142853
      //    This function determine whether the Windows for
      //    Workgroups Multinet driver AND Windows for Workgroups
      //    networking  is present.
      BOOL WFWDetect ();

      //## Operation: GetWFWNetDriverHandle%913142854
      //    This function retrieve the hinstWFWDriver handle for
      //    MNet calls.
      HANDLE GetWFWNetDriverHandle ();

      //## Operation: GetLastTargetHandle%913142855
      //    This function call the MNetGetLastTarget.
      HANDLE GetLastTargetHandle ();

      //## Operation: SetNextTargetHandle%913142856
      //    This function call the MNetSetNextTarget.
      //    The return value  returned by the MNetSetNextTarget
      //    function.
      WORD SetNextTargetHandle (HANDLE hNetwork);

      //## Operation: NetworkEnumAll%913142857
      //    Enumerate any multinet networks and fill in the hinst
      //    MNet array.
      //    Returns TRUE if found some networks.
      //    FALSE if no networks.
      BOOL NetworkEnumAll ();

      //## Operation: EnumConnect%947664374
      //    Enum existing connections.
      bool EnumConnect (LPNETRESOURCE lpnr, ZNetResourceManager& ResourceManager);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: MNets%366D7A64020A
      //    our count of networks installed
      static const int GetMNets ();
      static void SetMNets (int value);

      //## Attribute: Primary%366D7A870015
      //    the primary network
      static const HANDLE GetPrimary ();
      static void SetPrimary (HANDLE value);

      //## Attribute: hInstNetDriver%366D7CF40249
      static const HANDLE GethInstNetDriver ();
      static void SethInstNetDriver (HANDLE value);

      //## Attribute: hInstWFWDriver%366D7D0C00DB
      static const HANDLE GethInstWFWDriver ();
      static void SethInstWFWDriver (HANDLE value);

    // Additional Private Declarations
      //## begin ZUNetwork%366D71D50245.private preserve=yes
      //## end ZUNetwork%366D71D50245.private

  private:  //## implementation
    // Data Members for Class Attributes

      //## begin ZUNetwork::MNets%366D7A64020A.attr preserve=no  private: static int {V} 0
      static int m_MNets;
      //## end ZUNetwork::MNets%366D7A64020A.attr

      //## begin ZUNetwork::Primary%366D7A870015.attr preserve=no  private: static HANDLE {V} 0
      static HANDLE m_Primary;
      //## end ZUNetwork::Primary%366D7A870015.attr

      //## begin ZUNetwork::hInstNetDriver%366D7CF40249.attr preserve=no  private: static HANDLE {V} 0
      static HANDLE m_hInstNetDriver;
      //## end ZUNetwork::hInstNetDriver%366D7CF40249.attr

      //## begin ZUNetwork::hInstWFWDriver%366D7D0C00DB.attr preserve=no  private: static HANDLE {V} 0
      static HANDLE m_hInstWFWDriver;
      //## end ZUNetwork::hInstWFWDriver%366D7D0C00DB.attr

    // Additional Implementation Declarations
      //## begin ZUNetwork%366D71D50245.implementation preserve=yes
        static HANDLE m_hInstMNet[MAX_MNETS];           
      //## end ZUNetwork%366D71D50245.implementation
};

//## begin ZUNetwork%366D71D50245.postscript preserve=yes
//## end ZUNetwork%366D71D50245.postscript

// Class ZUNetwork 


//## Other Operations (inline)
inline WORD ZUNetwork::GetNetworkErrorNo ()
{
  //## begin ZUNetwork::GetNetworkErrorNo%913142849.body preserve=yes
    INT         nError;
#ifndef _WIN32
    // Calling WNetGetError at this point I am assuming that
    // a network error has indeed occured.
    WNetGetError( &nError );
#else
    DWORD    Error;
    char    szErrorBuf[200];
    char    szNameBuf[200];
    WNetGetLastError( &Error, szErrorBuf, sizeof( szErrorBuf ),
                               szNameBuf, sizeof( szNameBuf ) );
    // Backward compatibility
    nError = Error;
#endif
    return nError;
  //## end ZUNetwork::GetNetworkErrorNo%913142849.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const int ZUNetwork::GetMNets ()
{
  //## begin ZUNetwork::GetMNets%366D7A64020A.get preserve=no
  return m_MNets;
  //## end ZUNetwork::GetMNets%366D7A64020A.get
}

inline void ZUNetwork::SetMNets (int value)
{
  //## begin ZUNetwork::SetMNets%366D7A64020A.set preserve=no
  m_MNets = value;
  //## end ZUNetwork::SetMNets%366D7A64020A.set
}

inline const HANDLE ZUNetwork::GetPrimary ()
{
  //## begin ZUNetwork::GetPrimary%366D7A870015.get preserve=no
  return m_Primary;
  //## end ZUNetwork::GetPrimary%366D7A870015.get
}

inline void ZUNetwork::SetPrimary (HANDLE value)
{
  //## begin ZUNetwork::SetPrimary%366D7A870015.set preserve=no
  m_Primary = value;
  //## end ZUNetwork::SetPrimary%366D7A870015.set
}

inline const HANDLE ZUNetwork::GethInstNetDriver ()
{
  //## begin ZUNetwork::GethInstNetDriver%366D7CF40249.get preserve=no
  return m_hInstNetDriver;
  //## end ZUNetwork::GethInstNetDriver%366D7CF40249.get
}

inline void ZUNetwork::SethInstNetDriver (HANDLE value)
{
  //## begin ZUNetwork::SethInstNetDriver%366D7CF40249.set preserve=no
  m_hInstNetDriver = value;
  //## end ZUNetwork::SethInstNetDriver%366D7CF40249.set
}

inline const HANDLE ZUNetwork::GethInstWFWDriver ()
{
  //## begin ZUNetwork::GethInstWFWDriver%366D7D0C00DB.get preserve=no
  return m_hInstWFWDriver;
  //## end ZUNetwork::GethInstWFWDriver%366D7D0C00DB.get
}

inline void ZUNetwork::SethInstWFWDriver (HANDLE value)
{
  //## begin ZUNetwork::SethInstWFWDriver%366D7D0C00DB.set preserve=no
  m_hInstWFWDriver = value;
  //## end ZUNetwork::SethInstWFWDriver%366D7D0C00DB.set
}

//## begin module%366D71B0009D.epilog preserve=yes
//## end module%366D71B0009D.epilog


#endif
