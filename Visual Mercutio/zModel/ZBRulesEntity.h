// ******************************************************************************************************************
// *                                        Classe ZBRulesEntity                                                    *
// ******************************************************************************************************************
// * JMR-MODIF - Le 14 novembre 2006 - Ajout de la classe ZBRulesEntity.                                            *
// ******************************************************************************************************************
// * Cette classe représente une entité de type règle. Une entité peut être considérée comme un élément du document.*
// ******************************************************************************************************************

#if !defined(AFX_ZBRulesEntity_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_)
#define AFX_ZBRulesEntity_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZBRulesEntity : public CObject
{
    DECLARE_SERIAL( ZBRulesEntity )

public:

    ZBRulesEntity( const CString    Name        = _T( "" ),
                   const CString    Description    = _T( "" ),
                   ZBRulesEntity*    pParent        = NULL );

    ~ZBRulesEntity();

    ZBRulesEntity* GetParent()
    {
        return m_pParent;
    }

    virtual ZBRulesEntity* GetRoot()
    {
        if ( m_pParent )
        {
            return m_pParent->GetRoot();
        }

        return this;
    }

    virtual bool ContainEntity() const
    {
        return false;
    }

    virtual size_t GetEntityCount() const
    {
        return 0;
    }

    virtual ZBRulesEntity* GetEntityAt( size_t Index )
    {
        return NULL;
    }

    CString GetGUID() const
    {
        return m_GUID;
    }

    void SetGUID( CString value )
    {
        m_GUID = value;
    }

    virtual CString GetEntityName() const
    {
        return m_EntityName;
    }

    virtual void SetEntityName( const CString value )
    {
        m_EntityName = value;
    }

    virtual CString GetEntityDescription() const
    {
        return m_EntityDescription;
    }

    virtual void SetEntityDescription( const CString value )
    {
        m_EntityDescription = value;
    }

    virtual bool DisplayProperties()
    {
        return false;
    }

    void SetParent( ZBRulesEntity* pParent )
    {
        m_pParent = pParent;
    }

    // Serialization mechanism
    virtual void Serialize( CArchive& ar );    // overridden for document i/o

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

protected:

    void CreateGUID();

private:

    CString            m_GUID;
    CString            m_EntityName;
    CString            m_EntityDescription;
    ZBRulesEntity*    m_pParent;
};

#endif // !defined(AFX_ZBRulesEntity_H__2AC8D235_7673_47BE_86B3_CCD14A70DE78__INCLUDED_)