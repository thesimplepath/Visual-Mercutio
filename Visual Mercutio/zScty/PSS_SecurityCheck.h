/****************************************************************************
 * ==> PSS_SecurityCheck ---------------------------------------------------*
 ****************************************************************************
 * Description : Manages the security file for product key                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SecurityCheckH
#define PSS_SecurityCheckH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "security.h"

#ifdef _ZSCTYEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Manages the security file for product key
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZASecurityCheck : public ZASecurity
{
    public:
        ZASecurityCheck();

        ZASecurityCheck(const CString& fileName,
            int            daysMax,
            int            counterMax,
            int            counterMin,
            const CString& appRegistryKey = "",
            const CString& appPID         = "");

        ~ZASecurityCheck();

        //## Other Operations (specified)
        //## Operation: Check%812506911
        //    Check if the user can use the program or a
        //    functionnality.
        BOOL Check();

        //## Operation: FindOldVersion%812562131
        //    Find an old filename on the disks.
        const CString FindOldVersion(const CString&  sExeFilename);

        //## Operation: CreateSecurityFile%812564855
        BOOL CreateSecurityFile();

        //## Operation: Create%812682977
        BOOL Create(const CString&  sFilename, int iDaysMax, int iCounterMax, int iCounterMin,
            const CString ApplicationRegistryKey = "", const CString ApplicationPID = "");

        //## Operation: CheckRegistery%854929700
        BOOL CheckRegistery();

        //## Get and Set Operations for Has Relationships (generated)

        //## Documentation ZASecurityCheck::sFilenameToSearch.has
        const CString GetsFilenameToSearch() const;
        void SetsFilenameToSearch(const CString value);

        //## Documentation ZASecurityCheck::sFoundedFilename.has
        const CString GetsFoundedFilename() const;
        void SetsFoundedFilename(const CString value);

    private:
        //## Other Operations (specified)
        //## Operation: FindFile%812564853
        //    Find a specific file into a specific drive.
        //
        //    The return is the file otherwise an empty string.
        const CString&  FindFile(const CString&  sFilename, int iDrive);

        //## Operation: FindFileInCurrentDir%812564854
        BOOL FindFileInCurrentDir();

        // Data Members for Has Relationships

        //## Documentation ZASecurityCheck::iDaysMax.has
        //    The maximum days to reach.
        //## begin ZASecurityCheck::iDaysMax.has preserve=no  public: int {1 -> 1VO}
        int m_iDaysMax;
        //## end ZASecurityCheck::iDaysMax.has

        //## Documentation ZASecurityCheck::iCounterMax.has
        //    The maximum counter to reach.
        //## begin ZASecurityCheck::iCounterMax.has preserve=no  public: int {1 -> 1VO}
        int m_iCounterMax;
        //## end ZASecurityCheck::iCounterMax.has

        //## Documentation ZASecurityCheck::iCounterMin.has
        //    The minimum counter where the days can be checked.
        //## begin ZASecurityCheck::iCounterMin.has preserve=no  public: int {1 -> 1VO}
        int m_iCounterMin;
        //## end ZASecurityCheck::iCounterMin.has

        //## begin ZASecurityCheck::sFilenameToSearch.has preserve=no  public: CString {1 -> 1VO}
        CString m_sFilenameToSearch;
        //## end ZASecurityCheck::sFilenameToSearch.has

        //## begin ZASecurityCheck::sFoundedFilename.has preserve=no  public: CString {1 -> 1VO}
        CString m_sFoundedFilename;
        //## end ZASecurityCheck::sFoundedFilename.has

        // Additional Implementation Declarations
        //## begin ZASecurityCheck.implementation preserve=yes
        //## end ZASecurityCheck.implementation
};

// Class ZASecurityCheck 

//## Get and Set Operations for Has Relationships (inline)

inline const CString ZASecurityCheck::GetsFilenameToSearch() const
{
  //## begin ZASecurityCheck::GetsFilenameToSearch%.get preserve=no
  return m_sFilenameToSearch;
  //## end ZASecurityCheck::GetsFilenameToSearch%.get
}

inline void ZASecurityCheck::SetsFilenameToSearch(const CString value)
{
  //## begin ZASecurityCheck::SetsFilenameToSearch%.set preserve=no
  m_sFilenameToSearch = value;
  //## end ZASecurityCheck::SetsFilenameToSearch%.set
}

inline const CString ZASecurityCheck::GetsFoundedFilename() const
{
  //## begin ZASecurityCheck::GetsFoundedFilename%.get preserve=no
  return m_sFoundedFilename;
  //## end ZASecurityCheck::GetsFoundedFilename%.get
}

inline void ZASecurityCheck::SetsFoundedFilename(const CString value)
{
  //## begin ZASecurityCheck::SetsFoundedFilename%.set preserve=no
  m_sFoundedFilename = value;
  //## end ZASecurityCheck::SetsFoundedFilename%.set
}





#endif    // _SecuChk_h__


