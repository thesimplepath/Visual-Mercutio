// **************************************************************************************************************
// *                                      Classe ZVRiskProbabilityContainer                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 11 juillet 2007 - Ajout de la classe ZVRiskProbabilityContainer.                            *
// **************************************************************************************************************
// * Cette classe contient en mémoire les probabilités pour les risques, en synchronisation avec le fichier des    *
// * probabilités.                                                                                                *
// **************************************************************************************************************

#if !defined(AFX_ZVRISKPROBABILITYCONTAINER_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_)
#define AFX_ZVRISKPROBABILITYCONTAINER_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_

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

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZVRiskProbabilityContainer : public CObject
{
public:

    ZVRiskProbabilityContainer();
    ~ZVRiskProbabilityContainer();

public:

    BOOL LoadFile( CString fileName);

    CStringArray* GetElementsArray();

    CString GetElementAt( size_t Index ) const;
    CString GetFileName();

    void RemoveAllElements();

    // Obtient le nombre de propriétés contenues dans l'ensemble.
    size_t GetElementCount() const
    {
        return m_Set.GetSize();
    };

private:

    CString            m_FileName;
    CStringArray    m_Set;
};

#endif // !defined(AFX_ZVRISKPROBABILITYCONTAINER_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_)