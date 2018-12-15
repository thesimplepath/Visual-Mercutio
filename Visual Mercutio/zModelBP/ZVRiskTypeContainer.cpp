// **************************************************************************************************************
// *                                            Classe ZVRiskTypeContainer                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 8 juillet 2007 - Ajout de la classe ZVRiskTypeContainer.                                    *
// **************************************************************************************************************
// * Cette classe contient en mémoire les types pour les risques, en synchronisation avec le fichier des types.    *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVRiskTypeContainer.h"

#include "zBaseLib\ZDTextFile.h"

// Constructeur de la classe ZVRiskTypeContainer.
ZVRiskTypeContainer::ZVRiskTypeContainer()
{
}

// Destructeur de la classe ZVRiskTypeContainer.
ZVRiskTypeContainer::~ZVRiskTypeContainer()
{
    RemoveAllElements();
}

// Cette fonction permet d'ouvrir un fichier de données.
BOOL ZVRiskTypeContainer::LoadFile( CString Filename )
{
    if ( Filename.IsEmpty() == true )
    {
        return FALSE;
    }

    m_Filename = Filename;

    ZDTextFile p_File;

    if ( p_File.OpenRead( m_Filename ) == FALSE )
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
CStringArray* ZVRiskTypeContainer::GetElementsArray()
{
    return &m_Set;
}

// Obtient l'élément à la position indiquée.
CString ZVRiskTypeContainer::GetElementAt( size_t Index ) const
{
    if ( Index < GetElementCount() )
    {
        return m_Set.GetAt( Index );
    }

    return _T( "" );
}

// Cette fonction retourne le nom du fchier en cours d'utilisation.
CString ZVRiskTypeContainer::GetFilename()
{
    return m_Filename;
}

// Cette fonction permet la suppression de tous les éléments dans la liste.
void ZVRiskTypeContainer::RemoveAllElements()
{
    m_Set.RemoveAll();
}
