// ZBSystemEntity.h: interface for the ZBSystemEntity class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSystemEntity_H__DBE9270D_4DE8_4EF3_91EA_E18EDEF6DE04__INCLUDED_)
#define AFX_ZBSystemEntity_H__DBE9270D_4DE8_4EF3_91EA_E18EDEF6DE04__INCLUDED_

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

// JMR-MODIF - Le 7 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commenatires)

class AFX_EXT_CLASS ZBSystemEntity : public CObject
{
	DECLARE_SERIAL( ZBSystemEntity )

public:

	ZBSystemEntity( const CString	Name		= _T( "" ),
				    const CString	Description	= _T( "" ),
				    ZBSystemEntity*	pParent		= NULL );

	virtual ~ZBSystemEntity();

	ZBSystemEntity* GetParent()
	{
		return m_pParent;
	}

	virtual ZBSystemEntity* GetRoot()
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

	virtual ZBSystemEntity* GetEntityAt( size_t Index )
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

	void SetParent( ZBSystemEntity* pParent )
	{
		m_pParent = pParent;
	}

	// Serialization mechanism
	virtual void Serialize( CArchive& ar );	// overridden for document i/o

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

protected:

	void CreateGUID();

private:

	CString			m_GUID;
	CString			m_EntityName;
	CString			m_EntityDescription;
	ZBSystemEntity*	m_pParent;
};

#endif // !defined(AFX_ZBSystemEntity_H__DBE9270D_4DE8_4EF3_91EA_E18EDEF6DE04__INCLUDED_)