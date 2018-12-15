// ZBWorkspaceEntity.h: interface for the ZBWorkspaceEntity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBWORKSPACEENTITY_H__DBE9270D_4DE8_4EF3_91EA_E18EDEF6DE04__INCLUDED_)
#define AFX_ZBWORKSPACEENTITY_H__DBE9270D_4DE8_4EF3_91EA_E18EDEF6DE04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


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


class AFX_EXT_CLASS ZBWorkspaceEntity : public CObject  
{
    DECLARE_SERIAL(ZBWorkspaceEntity)
public:
    ZBWorkspaceEntity(const CString Name = "", ZBWorkspaceEntity* pParent = NULL);
    virtual ~ZBWorkspaceEntity();

    ZBWorkspaceEntity* GetParent()
    {
        return m_pParent;
    };
    virtual ZBWorkspaceEntity* GetRoot()
    {
        if (m_pParent)
            return m_pParent->GetRoot();
        return this;
    }
    virtual bool ContainEntity() const
    {
        return false;
    };
    virtual size_t GetEntityCount() const
    {
        return 0;
    };
    virtual ZBWorkspaceEntity* GetEntityAt( size_t Index )
    {
        return NULL;
    };

    virtual CString GetEntityName() const
    {
        return m_EntityName;
    };
    virtual void SetEntityName( const CString value )
    {
        m_EntityName = value;
    };
    virtual CString GetEntityDescription() const
    {
        return m_EntityName;
    };
    virtual void SetEntityDescription( const CString value )
    {
        m_EntityDescription = value;
    };

    virtual void ClearExtensionList()
    {
    };
    virtual void SetExtensionList( CStringArray& ExtensionArray )
    {
    };
    virtual void AddElementToExtensionList( CStringArray& ExtensionArray )
    {
    };
    virtual CStringArray* GetExtensionList()
    {
        return NULL;
    };
    virtual void SetExtensionList( const CString Extensions )
    {
    };
    virtual void GetExtensionList( CString& Extensions )
    {
    };
    virtual bool ContainThisExtension( const CString Extension )
    {
        return false;
    };

    virtual bool HasFilename() const
    {
        return false;
    };

    virtual CString GetFilename() const
    {
        return _T("");
    };
    virtual CString GetFileTitle() const
    {
        return _T("");
    };
    virtual CString GetFilePath() const
    {
        return _T("");
    };
    virtual CString GetFileExt() const
    {
        return _T("");
    };
    virtual void SetFilename( const CString value )
    {
    };
    virtual HICON GetFilenameIcon() const
    {
        return NULL;
    };

    virtual bool DisplayProperties()
    {
        return false;
    };

    void SetParent( ZBWorkspaceEntity* pParent )
    {
        m_pParent = pParent;
    };

    // Serialization mechanism
    virtual void Serialize(CArchive& ar);   // overridden for document i/o

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif


private:
    CString m_EntityName;
    CString m_EntityDescription;
    ZBWorkspaceEntity* m_pParent;


};

#endif // !defined(AFX_ZBWORKSPACEENTITY_H__DBE9270D_4DE8_4EF3_91EA_E18EDEF6DE04__INCLUDED_)
