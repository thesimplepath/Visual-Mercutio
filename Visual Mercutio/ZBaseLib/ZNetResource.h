/****************************************************************************
 * ==> PSS_NetResource -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a net resource                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_NetResourceH
#define PSS_NetResourceH

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
* Net resource
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_NetResource : public CObject
{
    DECLARE_DYNAMIC(PSS_NetResource)

    public:
        /**
        * Constructor
        *@param pNetResource - net resource
        *@param isDir - if true, the resource is a directory
        */
        PSS_NetResource(NETRESOURCE* pNetResource = NULL, bool isDir = false);

        /**
        * Constructor
        *@param netResource - net resource
        *@param isDir - if true, the resource is a directory
        */
        PSS_NetResource(const PSS_NetResource& netResource, bool isDir = false);

        virtual ~PSS_NetResource();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        const PSS_NetResource& operator = (const PSS_NetResource& other);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        const PSS_NetResource& operator = (const NETRESOURCE& other);

        /**
        * Initializes the net resource
        *@param pNetResource - net resource
        *@param isDir - if true, the resource is a directory
        */
        virtual void Initialize(NETRESOURCE& netResource, bool isDirectory = false);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_NetResource* Clone() const ;

        /**
        * Gets the native net resource object
        *@return the native net resource object
        */
        virtual NETRESOURCE* GetNetResourceObject();

        /**
        * Gets the scope
        *@return the scope
        */
        virtual inline DWORD GetScope() const;

        /**
        * Sets the scope
        *@param value - the scope
        */
        virtual inline void SetScope(DWORD value);

        /**
        * Gets the type
        *@return the type
        */
        virtual inline DWORD GetType() const;

        /**
        * Sets the type
        *@param value - the type
        */
        virtual inline void SetType(DWORD value);

        /**
        * Gets the display type
        *@return the display type
        */
        virtual inline DWORD GetDisplayType() const;

        /**
        * Sets the display type
        *@param value - the display type
        */
        virtual inline void SetDisplayType(DWORD value);

        /**
        * Gets the usage
        *@return the usage
        */
        virtual inline DWORD GetUsage() const;

        /**
        * Sets the usage
        *@param value - the usage
        */
        virtual inline void SetUsage(DWORD value);

        /**
        * Gets the local name
        *@return the local name
        */
        virtual inline CString GetLocalName() const;

        /**
        * Sets the local name
        *@param value - the local name
        */
        virtual inline void SetLocalName(const CString& value);

        /**
        * Gets the remote name
        *@return the remote name
        */
        virtual inline CString GetRemoteName() const;

        /**
        * Sets the remote name
        *@param value - the remote name
        */
        virtual inline void SetRemoteName(const CString& value);

        /**
        * Gets the comment
        *@return the comment
        */
        virtual inline CString GetComment() const;

        /**
        * Sets the comment
        *@param value - the comment
        */
        virtual inline void SetComment(const CString& value);

        /**
        * Gets the provider
        *@return the provider
        */
        virtual inline CString GetProvider() const;

        /**
        * Sets the provider
        *@param value - the provider
        */
        virtual inline void SetProvider(const CString& value);

        /**
        * Gets if the net resource is a directory
        *@return true if the net resource is a directory, otherwise false
        */
        virtual inline bool GetIsDirectory() const;

        /**
        * Sets if the net resource is a directory
        *@param value - if true, the net resource is a directory
        */
        virtual inline void SetIsDirectory(bool value);

    private:
        CString m_LocalName;
        CString m_RemoteName;
        CString m_Comment;
        CString m_Provider;
        DWORD   m_Scope;
        DWORD   m_Type;
        DWORD   m_DisplayType;
        DWORD   m_Usage;
        bool    m_IsDirectory;
};

//---------------------------------------------------------------------------
// PSS_NetResource
//---------------------------------------------------------------------------
DWORD PSS_NetResource::GetScope() const
{
    return m_Scope;
}
//---------------------------------------------------------------------------
void PSS_NetResource::SetScope(DWORD value)
{
    m_Scope = value;
}
//---------------------------------------------------------------------------
DWORD PSS_NetResource::GetType() const
{
    return m_Type;
}
//---------------------------------------------------------------------------
void PSS_NetResource::SetType(DWORD value)
{
    m_Type = value;
}
//---------------------------------------------------------------------------
DWORD PSS_NetResource::GetDisplayType() const
{
    return m_DisplayType;
}
//---------------------------------------------------------------------------
void PSS_NetResource::SetDisplayType(DWORD value)
{
    m_DisplayType = value;
}
//---------------------------------------------------------------------------
DWORD PSS_NetResource::GetUsage() const
{
    return m_Usage;
}
//---------------------------------------------------------------------------
void PSS_NetResource::SetUsage(DWORD value)
{
    m_Usage = value;
}
//---------------------------------------------------------------------------
CString PSS_NetResource::GetLocalName() const
{
    return m_LocalName;
}
//---------------------------------------------------------------------------
void PSS_NetResource::SetLocalName(const CString& value)
{
    m_LocalName = value;
}
//---------------------------------------------------------------------------
CString PSS_NetResource::GetRemoteName() const
{
    return m_RemoteName;
}
//---------------------------------------------------------------------------
void PSS_NetResource::SetRemoteName(const CString& value)
{
    m_RemoteName = value;
}
//---------------------------------------------------------------------------
CString PSS_NetResource::GetComment() const
{
    return m_Comment;
}
//---------------------------------------------------------------------------
void PSS_NetResource::SetComment(const CString& value)
{
    m_Comment = value;
}
//---------------------------------------------------------------------------
CString PSS_NetResource::GetProvider() const
{
    return m_Provider;
}
//---------------------------------------------------------------------------
void PSS_NetResource::SetProvider(const CString& value)
{
    m_Provider = value;
}
//---------------------------------------------------------------------------
bool PSS_NetResource::GetIsDirectory() const
{
    return m_IsDirectory;
}
//---------------------------------------------------------------------------
void PSS_NetResource::SetIsDirectory(bool value)
{
    m_IsDirectory = value;
}
//---------------------------------------------------------------------------

#endif
