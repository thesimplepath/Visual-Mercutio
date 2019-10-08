/****************************************************************************
 * ==> PSS_NetResourceWrapper ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a net resource wrapper                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_NetResourceWrapperH
#define PSS_NetResourceWrapperH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

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
* Net resource wrapper
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_NetResourceWrapper : public CObject
{
    DECLARE_DYNAMIC(PSS_NetResourceWrapper)

    public:
        /**
        * Constructor
        *@param fileName - file name
        *@param pNetResource - net resource
        *@param isDir - if true, the net resource is a directory
        */
        PSS_NetResourceWrapper(const CString& fileName, NETRESOURCE* pNetResource = NULL, bool isDir = false);

        virtual ~PSS_NetResourceWrapper();

        /**
        * Initializes the class
        *@param fileName - file name
        *@param pNetResource - net resource
        *@param isDir - if true, the net resource is a directory
        */
        virtual void Initialize(const CString& fileName, NETRESOURCE* pNetResource = NULL, bool isDir = false);

        /**
        * Gets the native net resource
        *@return the native net resource, NULL on error
        */
        virtual inline NETRESOURCE* GetNetResource();

        /**
        * Gets the file name
        *@return the file name
        */
        virtual inline CString GetFileName() const;

        /**
        * Gets if the net resource is a directory
        *@return true if the net resource is a directory, otherwise false
        */
        virtual inline bool IsDir() const;

        /**
        * Gets if the net resource is a file
        *@return true if the net resource is a file, otherwise false
        */
        virtual inline bool IsFile() const;

    private:
        NETRESOURCE* m_pNetResource;
        CString      m_FileName;
        bool         m_IsDir;
};

//---------------------------------------------------------------------------
// PSS_NetResourceWrapper
//---------------------------------------------------------------------------
NETRESOURCE* PSS_NetResourceWrapper::GetNetResource()
{
    return m_pNetResource;
}
//---------------------------------------------------------------------------
CString PSS_NetResourceWrapper::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
bool PSS_NetResourceWrapper::IsDir() const
{
    return m_IsDir;
}
//---------------------------------------------------------------------------
bool PSS_NetResourceWrapper::IsFile() const
{
    return !m_IsDir;
}
//---------------------------------------------------------------------------

#endif
