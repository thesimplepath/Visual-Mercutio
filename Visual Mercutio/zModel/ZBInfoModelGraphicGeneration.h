// ZBInfoModelGraphicGeneration.h: interface for the ZBInfoModelGraphicGeneration class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBINFOMODELGRAPHICGENERATION_H__05209965_C481_4C8E_AA5F_E813CF9C313F__INCLUDED_)
#define AFX_ZBINFOMODELGRAPHICGENERATION_H__05209965_C481_4C8E_AA5F_E813CF9C313F__INCLUDED_

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

//////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZDProcessGraphModelMdl;
class ZDProcessGraphModelController;
class ZBServer;

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 2 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBInfoModelGraphicGeneration
{
public:

	ZBInfoModelGraphicGeneration( ZDProcessGraphModelMdl*			pModel					= NULL,
								  ZDProcessGraphModelController*	pCtlr					= NULL,
								  const CString						URLName					= _T( "" ),
								  bool								AbsolutePath			= true,
								  bool								IncludeConceptor		= true,
								  bool								IncludeProcessReport	= true,
								  bool								IncludeRuleBook			= true,
								  const								CString ImageFilename	= _T( "" ),
								  const								CString HyperLink		= _T( "" ),
								  CDC*								pDC						= NULL,
								  ZBServer*							pServer					= NULL);

	virtual ~ZBInfoModelGraphicGeneration();

	ZDProcessGraphModelMdl* GetpModel() const;
	void SetpModel( ZDProcessGraphModelMdl* value );
	
	ZDProcessGraphModelController* GetpCtlr() const;
	void SetpCtlr( ZDProcessGraphModelController* value );
	
	CString GetURLName() const;
	void SetURLName( CString value );

	bool GetAbsolutePath() const;
	void SetAbsolutePath( bool value );

	bool GetIncludeConceptor() const;
	void SetIncludeConceptor( bool value );

	// JMR-MODIF - Le 2 mars 2006 - Ajout des fonctions de gestion de la génération du rapport processus.
	bool GetIncludeProcessReport() const;
	void SetIncludeProcessReport( bool value );

	// JMR-MODIF - Le 16 janvier 2007 - Ajout des fonctions de gestion de la génération du livre des règles.
	bool GetIncludeRuleBook() const;
	void SetIncludeRuleBook( bool value );

	CString GetImageFilename() const;
	void SetImageFilename( CString value );

	CString GetHyperLink() const;
	void SetHyperLink( CString value );

	CDC* GetpDC() const;
	void SetpDC( CDC* value );

	ZBServer* GetpServer() const;
	void SetpServer( ZBServer* value );

private:

	bool							m_AbsolutePath;
	bool							m_IncludeConceptor;
	// JMR-MODIF - Le 2 mars 2006 - Ajout de la variable m_IncludeProcessReport.
	bool							m_IncludeProcessReport;
	// JMR-MODIF - Le 16 janvier 2007 - Ajout de la variable m_IncludeRuleBook.
	bool							m_IncludeRuleBook;

	CString							m_URLName;
	CString							m_ImageFilename;
	CString							m_HyperLink;

	CDC*							m_pDC;

	ZDProcessGraphModelMdl*			m_pModel;

	ZDProcessGraphModelController*	m_pCtlr;

	ZBServer*						m_pServer;
};

inline ZDProcessGraphModelMdl* ZBInfoModelGraphicGeneration::GetpModel() const
{
	return m_pModel;
}

inline void ZBInfoModelGraphicGeneration::SetpModel( ZDProcessGraphModelMdl* value )
{
	m_pModel = value;
}

inline ZDProcessGraphModelController* ZBInfoModelGraphicGeneration::GetpCtlr() const
{
	return m_pCtlr;
}

inline void ZBInfoModelGraphicGeneration::SetpCtlr( ZDProcessGraphModelController* value )
{
	m_pCtlr = value;
}

inline CString ZBInfoModelGraphicGeneration::GetURLName() const
{
	return m_URLName;
}

inline void ZBInfoModelGraphicGeneration::SetURLName( CString value )
{
	m_URLName = value;
}

inline bool ZBInfoModelGraphicGeneration::GetAbsolutePath() const
{
	return m_AbsolutePath;
}

inline void ZBInfoModelGraphicGeneration::SetAbsolutePath( bool value )
{
	m_AbsolutePath = value;
}

inline bool ZBInfoModelGraphicGeneration::GetIncludeConceptor() const
{
	return m_IncludeConceptor;
}

inline void ZBInfoModelGraphicGeneration::SetIncludeConceptor( bool value )
{
	m_IncludeConceptor = value;
}

// JMR-MODIF - Le 2 mars 2006 - Ajout de la fonction GetIncludeProcessReport.
inline bool ZBInfoModelGraphicGeneration::GetIncludeProcessReport() const
{
	return m_IncludeProcessReport;
}

// JMR-MODIF - Le 2 mars 2006 - Ajout de la fonction SetIncludeProcessReport.
inline void ZBInfoModelGraphicGeneration::SetIncludeProcessReport( bool value )
{
	m_IncludeProcessReport = value;
}

// JMR-MODIF - Le 16 janvier 2007 - Ajout de la fonction GetIncludeRuleBook.
inline bool ZBInfoModelGraphicGeneration::GetIncludeRuleBook() const
{
	return m_IncludeRuleBook;
}

// JMR-MODIF - Le 16 janvier 2007 - Ajout de la fonction SetIncludeRuleBook.
inline void ZBInfoModelGraphicGeneration::SetIncludeRuleBook( bool value )
{
	m_IncludeRuleBook = value;
}

inline CString ZBInfoModelGraphicGeneration::GetImageFilename() const
{
	return m_ImageFilename;
}

inline void ZBInfoModelGraphicGeneration::SetImageFilename( CString value )
{
	m_ImageFilename = value;
}

inline CString ZBInfoModelGraphicGeneration::GetHyperLink() const
{
	return m_HyperLink;
}

inline void ZBInfoModelGraphicGeneration::SetHyperLink( CString value )
{
	m_HyperLink = value;
}

inline CDC* ZBInfoModelGraphicGeneration::GetpDC() const
{
	return m_pDC;
}

inline void ZBInfoModelGraphicGeneration::SetpDC( CDC* value )
{
	m_pDC = value;
}

inline ZBServer* ZBInfoModelGraphicGeneration::GetpServer() const
{
	return m_pServer;
}

inline void ZBInfoModelGraphicGeneration::SetpServer( ZBServer* value )
{
	m_pServer = value;
}

#endif // !defined(AFX_ZBINFOMODELGRAPHICGENERATION_H__05209965_C481_4C8E_AA5F_E813CF9C313F__INCLUDED_)