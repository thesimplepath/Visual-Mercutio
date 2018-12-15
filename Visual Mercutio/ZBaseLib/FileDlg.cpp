//## begin module%35D41FDA034A.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%35D41FDA034A.cm

//## begin module%35D41FDA034A.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%35D41FDA034A.cp

//## Module: FileDlg%35D41FDA034A; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\FileDlg.cpp

//## begin module%35D41FDA034A.additionalIncludes preserve=no
//## end module%35D41FDA034A.additionalIncludes

//## begin module%35D41FDA034A.includes preserve=yes
#include <StdAfx.h>
//## end module%35D41FDA034A.includes

// FileDlg
#include "FileDlg.h"

//## begin module%35D41FDA034A.declarations preserve=no
#include <AfxDlgs.h>
#include <Dlgs.h>
//## end module%35D41FDA034A.declarations

//## begin module%35D41FDA034A.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//## end module%35D41FDA034A.additionalDeclarations

// JMR-MODIF - Le 27 juin 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Class ZIFileDialog

BEGIN_MESSAGE_MAP( ZIFileDialog, CFileDialog )
    //{{AFX_MSG_MAP(ZIFileDialog)
    // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZIFileDialog::ZIFileDialog( const CString    Title,
                            const CString    Filter,
                            int                FilterCount,
                            const CString    InitialDir )
    //## begin ZIFileDialog::ZIFileDialog%903091426.hasinit preserve=no
    //## end ZIFileDialog::ZIFileDialog%903091426.hasinit
    //## begin ZIFileDialog::ZIFileDialog%903091426.initialization preserve=yes
    : CFileDialog    ( TRUE ),
      m_Title        ( Title ),
      m_Filter        ( Filter ),
      m_FilterCount    ( FilterCount ),
      m_InitialDir    ( InitialDir )
    //## end ZIFileDialog::ZIFileDialog%903091426.initialization
{
    //## begin ZIFileDialog::ZIFileDialog%903091426.body preserve=yes
    //## end ZIFileDialog::ZIFileDialog%903091426.body
}

ZIFileDialog::ZIFileDialog( UINT            nIDTitle,
                            const CString    Filter,
                            int                FilterCount,
                            const CString    InitialDir )
    //## begin ZIFileDialog::ZIFileDialog%918051898.hasinit preserve=no
    //## end ZIFileDialog::ZIFileDialog%918051898.hasinit
    //## begin ZIFileDialog::ZIFileDialog%918051898.initialization preserve=yes
    : CFileDialog    ( TRUE ),
      m_Filter        ( Filter ),
      m_FilterCount    ( FilterCount ),
      m_InitialDir    ( InitialDir )
    //## end ZIFileDialog::ZIFileDialog%918051898.initialization
{
    //## begin ZIFileDialog::ZIFileDialog%918051898.body preserve=yes
    if ( nIDTitle != 0 )
    {
        m_Title.LoadString( nIDTitle );
    }
    //## end ZIFileDialog::ZIFileDialog%918051898.body
}

ZIFileDialog::~ZIFileDialog()
{
    //## begin ZIFileDialog::~ZIFileDialog%.body preserve=yes
    //## end ZIFileDialog::~ZIFileDialog%.body
}

//## Other Operations (implementation)
int ZIFileDialog::DoModal()
{
    //## begin ZIFileDialog::DoModal%903091427.body preserve=yes
    m_ofn.nMaxCustFilter    += m_FilterCount;
    m_ofn.lpstrFilter         = m_Filter;
    m_ofn.hwndOwner             = AfxGetMainWnd()->GetSafeHwnd();
    m_ofn.lpstrTitle         = m_Title;
    m_ofn.lpstrFile             = m_Filename.GetBuffer( _MAX_PATH );

    // Set the initial directory
    m_ofn.lpstrInitialDir = m_InitialDir;

    BOOL bRet = CFileDialog::DoModal() == IDOK ? TRUE : FALSE;
    m_Filename.ReleaseBuffer();

    return bRet;
    //## end ZIFileDialog::DoModal%903091427.body
}

// Additional Declarations
//## begin ZIFileDialog%35D41E3D00F7.declarations preserve=yes
//## end ZIFileDialog%35D41E3D00F7.declarations

//## begin module%35D41FDA034A.epilog preserve=yes

#ifdef _WIN32
BOOL ZIFileDialog::OnFileNameOK()
{
    m_PathName = GetFolderPath();
    return CFileDialog::OnFileNameOK();
}
#endif

//## end module%35D41FDA034A.epilog

// Detached code regions:
// WARNING: this code will be lost if code is regenerated.

#if 0
//## begin ZIFileDialog::ZIFileDialog%918998214.initialization preserve=no
#ifdef _WIN32
    : CFileDialog( TRUE,
                   NULL,
                   NULL,
                   OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | ( ( DirectoryOnly==true ) ? ( OFN_EXPLORER | OFN_NOVALIDATE ) : 0 ) ),
#else
    : CFileDialog( TRUE,
                   NULL,
                   NULL,
                   OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ),
#endif
    m_DirectoryOnly    ( DirectoryOnly ),
    m_InitialDir    ( InitialDir )
//## end ZIFileDialog::ZIFileDialog%918998214.initialization

//## begin ZIFileDialog::ZIFileDialog%918998214.body preserve=no
    if ( nIDTitle != 0 )
    {
        m_Title.LoadString( nIDTitle );
    }
//## end ZIFileDialog::ZIFileDialog%918998214.body

//## begin ZIFileDialog::ZIFileDialog%918998215.initialization preserve=no
#ifdef _WIN32
    : CFileDialog( TRUE,
                   NULL,
                   NULL,
                   OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | ( ( DirectoryOnly == true ) ? ( OFN_EXPLORER | OFN_NOVALIDATE ) : 0 ) ),
#else
    : CFileDialog( TRUE,
                   NULL,
                   NULL,
                   OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ),
#endif

                   m_DirectoryOnly    ( DirectoryOnly ),
                   m_Title            ( Title ),
                   m_InitialDir        ( InitialDir )
//## end ZIFileDialog::ZIFileDialog%918998215.initialization

#endif