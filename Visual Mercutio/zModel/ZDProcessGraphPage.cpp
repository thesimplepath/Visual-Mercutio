// ZDProcessGraphPage.cpp: implementation of the ZDProcessGraphPage class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZDProcessGraphPage.h"

#include "ProcGraphModelMdl.h"

// JMR-MODIF - Le 14 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZDProcessGraphPage

IMPLEMENT_SERIAL( ZDProcessGraphPage, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZDProcessGraphPage::ZDProcessGraphPage( const CString			PageName	/*= ""*/,
										ZDProcessGraphModelMdl*	pModel		/*= NULL*/ )
	: m_PageName( PageName ),
	  m_pModel	( pModel )
{
}

ZDProcessGraphPage::~ZDProcessGraphPage()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZDProcessGraphPage diagnostics

#ifdef _DEBUG
void ZDProcessGraphPage::AssertValid() const
{
	CObject::AssertValid();
}

void ZDProcessGraphPage::Dump( CDumpContext& dc ) const
{
	CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// ZDProcessGraphPage serialization

void ZDProcessGraphPage::Serialize( CArchive& ar )
{
	CObject::Serialize( ar );

	if ( ar.IsStoring() )
	{
		m_ModelName.Empty();

		if ( m_pModel )
		{
			m_ModelName = m_pModel->GetAbsolutePath();
		}

		ar << m_PageName;
		ar << m_ModelName;
	}
	else
	{
		ar >> m_PageName;
		ar >> m_ModelName;
	}
}
