// **************************************************************************************************************
// *                                          Classe ZVRiskImpactContainer                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 11 juillet 2007 - Ajout de la classe ZVRiskImpactContainer.                                    *
// **************************************************************************************************************
// * Cette classe contient en mémoire les impacts pour les risques, en synchronisation avec le fichier des        *
// * impacts.                                                                                                    *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVRiskImpactContainer.h"

// processsoft
#include "zBaseLib\PSS_TextFile.h"

// Constructeur de la classe ZVRiskImpactContainer.
ZVRiskImpactContainer::ZVRiskImpactContainer()
{
}

// Destructeur de la classe ZVRiskImpactContainer.
ZVRiskImpactContainer::~ZVRiskImpactContainer()
{
    RemoveAllElements();
}

// Cette fonction permet d'ouvrir un fichier de données.
BOOL ZVRiskImpactContainer::LoadFile( CString fileName )
{
    if (fileName.IsEmpty() == true )
    {
        return FALSE;
    }

    m_FileName = fileName;

    PSS_TextFile p_File;

    if ( p_File.OpenRead( m_FileName ) == FALSE )
    {
        return FALSE;
    }

    BOOL    m_EndReached    = FALSE;
    CString    m_Text            = _T( "" );

    while( m_EndReached != TRUE )
    {
        p_File >> m_Text;

        if ( m_Text.IsEmpty() == false )
        {
            m_Set.Add( m_Text );
        }
        else
        {
            m_EndReached = TRUE;
        }
    }

    p_File.CloseFile();

    return TRUE;
}

// Obtient la liste des éléments.
CStringArray* ZVRiskImpactContainer::GetElementsArray()
{
    return &m_Set;
}

// Obtient l'élément à la position indiquée.
CString ZVRiskImpactContainer::GetElementAt( size_t Index ) const
{
    if ( Index < GetElementCount() )
    {
        return m_Set.GetAt( Index );
    }

    return _T( "" );
}

// Cette fonction retourne le nom du fchier en cours d'utilisation.
CString ZVRiskImpactContainer::GetFileName()
{
    return m_FileName;
}

// Cette fonction permet la suppression de tous les éléments dans la liste.
void ZVRiskImpactContainer::RemoveAllElements()
{
    m_Set.RemoveAll();
}
