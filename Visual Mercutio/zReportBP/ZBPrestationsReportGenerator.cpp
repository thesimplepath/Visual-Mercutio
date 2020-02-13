// **************************************************************************************************************
// *                                    Classe ZBPrestationsReportGenerator                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 8 mars 2006 - Ajout de la classe ZBPrestationsReportGenerator.                                *
// **************************************************************************************************************
// * Cette classe permet la génération d'un rapport de type Prestations dans un nouveau document.                *
// **************************************************************************************************************

// **************************************************************************************************************
// * INFO IMPORTANTE : Les ressources utilisées pour les textes, à l'exception des titres des rapports, sont    *
// * les mêmes que celles utilisées par les rapports Sesterce, Sesterce Unités et Sesterce Consolidé.            *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZBPrestationsReportGenerator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

const size_t _MaxDeliveryListSize = 20;

// ******************************************************************************************************
// *                              Fonctions utilisées par les classes internes                            *
// ******************************************************************************************************

// ***************************************** Classe _ZBProcessDatas *************************************

// Constructeur par défaut de la classe _ZBProcessDatas
_ZBProcessDatas::_ZBProcessDatas(CString                        ProcessName        /*= _T( "" )*/,
                                 PSS_AnnualNumberPropertiesBP    Workload        /*= 0*/,
                                 PSS_AnnualNumberPropertiesBP    Cost            /*= 0*/,
                                 PSS_AnnualNumberPropertiesBP    CostHMO            /*= 0*/,
                                 float                            Percentage        /*= 0.0f*/)
{
    m_ProcessName = ProcessName;
    m_Workload = Workload;
    m_Cost = Cost;
    m_CostHMO = CostHMO;
    m_ProprietaryPrestPercentage = Percentage;
}

// Destructeur de la classe _ZBProcessDatas
_ZBProcessDatas::~_ZBProcessDatas()
{
    m_ProcessName.Empty();
}

// Cette fonction permet de définir le nom du processus contenant la prestation.
void _ZBProcessDatas::SetName(CString Name)
{
    m_ProcessName = Name;
}

// Cette fonction permet d'obtenir le nom du processus contenant la prestation.
CString _ZBProcessDatas::GetName()
{
    return m_ProcessName;
}

// Cette fonction permet de définir la charge de travail prévisionnelle du processus contenant la prestation.
void _ZBProcessDatas::SetWorkload(PSS_AnnualNumberPropertiesBP Workload)
{
    m_Workload = Workload;
}

// Cette fonction permet d'obtenir la charge de travail prévisionnelle du processus contenant la prestation.
PSS_AnnualNumberPropertiesBP _ZBProcessDatas::GetWorkload()
{
    return m_Workload;
}

// Cette fonction permet de définir le coût prévisionnel du processus contenant la prestation.
void _ZBProcessDatas::SetCost(PSS_AnnualNumberPropertiesBP Cost)
{
    m_Cost = Cost;
}

// Cette fonction permet d'obtenir le coût prévisionnel du processus contenant la prestation.
PSS_AnnualNumberPropertiesBP _ZBProcessDatas::GetCost()
{
    return m_Cost;
}

// Cette fonction permet de définir le coût HMO du processus contenant la prestation.
void _ZBProcessDatas::SetCostHMO(PSS_AnnualNumberPropertiesBP CostHMO)
{
    m_CostHMO = CostHMO;
}

// Cette fonction permet d'obtenir le coût HMO du processus contenant la prestation.
PSS_AnnualNumberPropertiesBP _ZBProcessDatas::GetCostHMO()
{
    return m_CostHMO;
}

// Cette fonction permet de définir le pourcentage d'activité de la prestation dans le processus.
void _ZBProcessDatas::SetPercentage(double Percentage)
{
    m_ProprietaryPrestPercentage = Percentage;
}

// Cette fonction permet d'obtenir le pourcentage d'activité de la prestation dans le processus.
double _ZBProcessDatas::GetPercentage()
{
    return m_ProprietaryPrestPercentage;
}

// *************************************** Classe _ZBPrestationsDatas ***********************************

// Constructeur par défaut de la classe _ZBPrestationsDatas.
_ZBPrestationsDatas::_ZBPrestationsDatas(CString PrestationName /*= _T( "" )*/)
{
    m_PrestationName = PrestationName;
    m_Space = _T("");
    m_TotalWorkload = 0;
    m_TotalCost = 0;
    m_TotalCostHMO = 0;
}

// Destructeur de la classe _ZBPrestationsDatas.
_ZBPrestationsDatas::~_ZBPrestationsDatas()
{
    m_PrestationName.Empty();
    m_Space.Empty();

    POSITION Pos = m_ProcessList.GetHeadPosition();

    while (Pos != NULL)
    {
        _ZBProcessDatas* m_TmpData = dynamic_cast<_ZBProcessDatas*>(m_ProcessList.GetNext(Pos));

        if (m_TmpData != NULL)
        {
            delete m_TmpData;
            m_TmpData = NULL;
        }
    }

    m_ProcessList.RemoveAll();

    Pos = m_ChildPrestationsList.GetHeadPosition();

    while (Pos != NULL)
    {
        _ZBPrestationsDatas* m_TmpData = dynamic_cast<_ZBPrestationsDatas*>(m_ChildPrestationsList.GetNext(Pos));

        if (m_TmpData != NULL)
        {
            delete m_TmpData;
            m_TmpData = NULL;
        }
    }

    m_ChildPrestationsList.RemoveAll();
}

// Cette fonction permet de déterminer le nom de la prestation.
void _ZBPrestationsDatas::SetName(CString Name)
{
    m_PrestationName = Name;
}

// Cette fonction permet d'obtenir le nom de la prestation.
CString _ZBPrestationsDatas::GetName()
{
    return m_PrestationName;
}

// Cette fonction permet d'obtenir le total de la charge de travail prévisionnelle de la prestation.
PSS_AnnualNumberPropertiesBP _ZBPrestationsDatas::GetTotalWorkload()
{
    return m_TotalWorkload;
}

// Cette fonction permet d'obtenir le total du coût prévisionnel de la prestation.
PSS_AnnualNumberPropertiesBP _ZBPrestationsDatas::GetTotalCost()
{
    return m_TotalCost;
}

// Cette fonction permet d'obtenir le total du coût HMO de la prestation.
PSS_AnnualNumberPropertiesBP _ZBPrestationsDatas::GetTotalCostHMO()
{
    return m_TotalCostHMO;
}

// Cette fonction permet la génération de la hiérarchie des prestations. Les niveaux de l'arbre sont respectés.
void _ZBPrestationsDatas::GenerateHierarchy(PSS_LogicalPrestationsEntity* pPrestations, int Level /*= 0*/)
{
    if (pPrestations == NULL)
    {
        return;
    }

    m_Space = _T("");

    // Pour le respect de la hiérarchie. Plus le niveau est bas, plus le texte est décalé vers la droite.
    // Ainsi : Level1
    //           ¦-Level2
    //           |   '-Level3
    //           '-Level2
    //               '-Level3
    //                   '-Etc...
    for (int i = Level; i > 0; --i)
    {
        // Inscrit les espaces du niveau de hiérarchie dans l'objet courant.
        m_Space += _T("    ");
    }

    // Inscrit le nom de la prestation dans l'objet courant.
    m_PrestationName = pPrestations->GetEntityName();

    // Teste si la prestation contient des prestations enfants.
    if (pPrestations->ContainEntity())
    {
        int Count = pPrestations->GetEntityCount();

        for (int i = 0; i < Count; ++i)
        {
            PSS_PrestationsEntity* pEntity = pPrestations->GetEntityAt(i);

            if (!pEntity)
            {
                continue;
            }

            // Teste si l'objet enfant est bien un objet de type ZBLogicalPrestationsEntity.
            if (ISA(pEntity, PSS_LogicalPrestationsEntity))
            {
                // Crée un nouveau conteneur de données pour les prestations.
                _ZBPrestationsDatas* m_ChildPrestation = new _ZBPrestationsDatas();

                // Lance un appel récursif depuis le nouveau conteneur, pour descendre d'un niveau.
                m_ChildPrestation->GenerateHierarchy(dynamic_cast<PSS_LogicalPrestationsEntity*>(pEntity),
                                                     Level + 1);

                // Ajoute la prestation enfant dans la liste des enfants de l'objet courant.
                m_ChildPrestationsList.AddTail(m_ChildPrestation);
            }
        }
    }
}

// Fonction d'inscription des données propres à chaque prestation dans le rapport.
void _ZBPrestationsDatas::DisplayDatas(ZBOStreamGrid    &ostream,
                                       CStringArray&    ProcessNameArray,
                                       CGXStyle        DisplayStyle,
                                       CGXStyle        AmountStyle,
                                       CGXStyle        NumericStyle,
                                       int                Index,
                                       bool            IncludeMonthDetails)
{
    int top = 0;
    int left = 0;

    // Obtient la position courante.
    ostream.GetCurSel(left, top);

    // Obtient le nombre de lignes du document.
    ROWCOL RowCount = ostream.GetGridCore()->GetRowCount();

    // Si pas assez, ajoute la quantité de lignes spécifiées.
    if ((top + 1) > (int)RowCount)
    {
        ostream.GetGridCore()->SetRowCount(RowCount + 1);
    }

    ostream << _T("\n");

    // Inscrit le nom de la prestation, avec son niveau hiérarchique.
    ostream << m_Space + m_PrestationName;
    ostream << DisplayStyle;

    // Distribue l'index courant du rapport.
    switch (Index)
    {
        // Page "Charge de travail"
        case 0:
        {
            // Colonne 1 - Document.
            ostream << _T("\t");
            ostream << m_TotalWorkload.GetNumberYear();
            ostream << DisplayStyle;
            ostream << NumericStyle;
            ostream << AmountStyle;

            // Inscription des détails du mois de la colonne 1.
            if (IncludeMonthDetails)
            {
                for (int i = 0; i < 12; ++i)
                {
                    ostream << _T("\t");
                    ostream << m_TotalWorkload.GetNumberAt(i);
                    ostream << DisplayStyle;
                    ostream << NumericStyle;
                    ostream << AmountStyle;
                }
            }

            // Colonne 2 à x - Détails par processus
            for (int i = 0; i < ProcessNameArray.GetSize(); ++i)
            {
                _ZBProcessDatas* m_CurData = NULL;

                POSITION Pos = m_ProcessList.GetHeadPosition();

                while (Pos != NULL)
                {
                    _ZBProcessDatas* m_TmpData = dynamic_cast<_ZBProcessDatas*>(m_ProcessList.GetNext(Pos));

                    if (m_TmpData != NULL)
                    {
                        if (m_TmpData->GetName() == ProcessNameArray.GetAt(i))
                        {
                            m_CurData = m_TmpData;
                        }
                    }
                }

                if (m_CurData != NULL && m_CurData->GetName() == ProcessNameArray.GetAt(i))
                {
                    ostream << _T("\t");
                    ostream << m_CurData->GetWorkload().GetNumberYear();
                    ostream << DisplayStyle;
                    ostream << NumericStyle;
                    ostream << AmountStyle;

                    // Inscription des détails du mois des colonnes 2 à x.
                    if (IncludeMonthDetails)
                    {
                        for (int i = 0; i < 12; ++i)
                        {
                            ostream << _T("\t");
                            ostream << m_CurData->GetWorkload().GetNumberAt(i);
                            ostream << DisplayStyle;
                            ostream << NumericStyle;
                            ostream << AmountStyle;
                        }
                    }
                }
                else
                {
                    ostream << _T("\t");
                    ostream << (double)0;
                    ostream << DisplayStyle;
                    ostream << NumericStyle;
                    ostream << AmountStyle;

                    if (IncludeMonthDetails)
                    {
                        for (int i = 0; i < 12; ++i)
                        {
                            ostream << _T("\t");
                            ostream << (double)0;
                            ostream << DisplayStyle;
                            ostream << NumericStyle;
                            ostream << AmountStyle;
                        }
                    }
                }
            }

            break;
        }

        // Page "Coûts"
        case 1:
        {
            // Colonne 1- Document.
            ostream << _T("\t");
            ostream << m_TotalCost.GetNumberYear();
            ostream << DisplayStyle;
            ostream << NumericStyle;
            ostream << AmountStyle;

            // Inscription des détails du mois de la colonne 1.
            if (IncludeMonthDetails)
            {
                for (int i = 0; i < 12; ++i)
                {
                    ostream << _T("\t");
                    ostream << m_TotalCost.GetNumberAt(i);
                    ostream << DisplayStyle;
                    ostream << NumericStyle;
                    ostream << AmountStyle;
                }
            }

            // Colonne 2 à x - Détails par processus
            for (int i = 0; i < ProcessNameArray.GetSize(); ++i)
            {
                _ZBProcessDatas* m_CurData = NULL;

                POSITION Pos = m_ProcessList.GetHeadPosition();

                while (Pos != NULL)
                {
                    _ZBProcessDatas* m_TmpData = dynamic_cast<_ZBProcessDatas*>(m_ProcessList.GetNext(Pos));

                    if (m_TmpData != NULL)
                    {
                        if (m_TmpData->GetName() == ProcessNameArray.GetAt(i))
                        {
                            m_CurData = m_TmpData;
                        }
                    }
                }

                if (m_CurData != NULL && m_CurData->GetName() == ProcessNameArray.GetAt(i))
                {
                    ostream << _T("\t");
                    ostream << m_CurData->GetCost().GetNumberYear();
                    ostream << DisplayStyle;
                    ostream << NumericStyle;
                    ostream << AmountStyle;

                    // Inscription des détails du mois des colonnes 2 à x.
                    if (IncludeMonthDetails)
                    {
                        for (int i = 0; i < 12; ++i)
                        {
                            ostream << _T("\t");
                            ostream << m_CurData->GetCost().GetNumberAt(i);
                            ostream << DisplayStyle;
                            ostream << NumericStyle;
                            ostream << AmountStyle;
                        }
                    }
                }
                else
                {
                    ostream << _T("\t");
                    ostream << (double)0;
                    ostream << DisplayStyle;
                    ostream << NumericStyle;
                    ostream << AmountStyle;

                    if (IncludeMonthDetails)
                    {
                        for (int i = 0; i < 12; ++i)
                        {
                            ostream << _T("\t");
                            ostream << (double)0;
                            ostream << DisplayStyle;
                            ostream << NumericStyle;
                            ostream << AmountStyle;
                        }
                    }
                }
            }

            break;
        }

        // Page "Coûts HMO"
        case 2:
        {
            // Colonne 1- Document.
            ostream << _T("\t");
            ostream << m_TotalCostHMO.GetNumberYear();
            ostream << DisplayStyle;
            ostream << NumericStyle;
            ostream << AmountStyle;

            // Inscription des détails du mois de la colonne 1.
            if (IncludeMonthDetails)
            {
                for (int i = 0; i < 12; ++i)
                {
                    ostream << _T("\t");
                    ostream << m_TotalCostHMO.GetNumberAt(i);
                    ostream << DisplayStyle;
                    ostream << NumericStyle;
                    ostream << AmountStyle;
                }
            }

            // Colonne 2 à x - Détails par processus
            for (int i = 0; i < ProcessNameArray.GetSize(); ++i)
            {
                _ZBProcessDatas* m_CurData = NULL;

                POSITION Pos = m_ProcessList.GetHeadPosition();

                while (Pos != NULL)
                {
                    _ZBProcessDatas* m_TmpData = dynamic_cast<_ZBProcessDatas*>(m_ProcessList.GetNext(Pos));

                    if (m_TmpData != NULL)
                    {
                        if (m_TmpData->GetName() == ProcessNameArray.GetAt(i))
                        {
                            m_CurData = m_TmpData;
                        }
                    }
                }

                if (m_CurData != NULL && m_CurData->GetName() == ProcessNameArray.GetAt(i))
                {
                    ostream << _T("\t");
                    ostream << m_CurData->GetCostHMO().GetNumberYear();
                    ostream << DisplayStyle;
                    ostream << NumericStyle;
                    ostream << AmountStyle;

                    // Inscription des détails du mois des colonnes 2 à x.
                    if (IncludeMonthDetails)
                    {
                        for (int i = 0; i < 12; ++i)
                        {
                            ostream << _T("\t");
                            ostream << m_CurData->GetCostHMO().GetNumberAt(i);
                            ostream << DisplayStyle;
                            ostream << NumericStyle;
                            ostream << AmountStyle;
                        }
                    }
                }
                else
                {
                    ostream << _T("\t");
                    ostream << (double)0;
                    ostream << DisplayStyle;
                    ostream << NumericStyle;
                    ostream << AmountStyle;

                    if (IncludeMonthDetails)
                    {
                        for (int i = 0; i < 12; ++i)
                        {
                            ostream << _T("\t");
                            ostream << (double)0;
                            ostream << DisplayStyle;
                            ostream << NumericStyle;
                            ostream << AmountStyle;
                        }
                    }
                }
            }

            break;
        }

        default:
        {
            break;
        }
    }

    // Récursion sur tous les objets enfants contenus dans la liste des enfants de l'objet courant.
    POSITION Pos = m_ChildPrestationsList.GetHeadPosition();

    while (Pos != NULL)
    {
        _ZBPrestationsDatas* m_TmpData = dynamic_cast<_ZBPrestationsDatas*>(m_ChildPrestationsList.GetNext(Pos));

        if (m_TmpData != NULL)
        {
            m_TmpData->DisplayDatas(ostream,
                                    ProcessNameArray,
                                    DisplayStyle,
                                    AmountStyle,
                                    NumericStyle,
                                    Index,
                                    IncludeMonthDetails);
        }
    }
}

// Cette fonction permet d'obtenir la liste des processus contenant la prestation.
CObList* _ZBPrestationsDatas::GetProcessList()
{
    return &m_ProcessList;
}

// Fonction interne de calcul des totaux.
void _ZBPrestationsDatas::InternalUpdateTotals()
{
    // Ajoute la valeur courante de la prestation au total.
    POSITION Pos = m_ProcessList.GetHeadPosition();

    while (Pos != NULL)
    {
        _ZBProcessDatas* m_TmpData = dynamic_cast<_ZBProcessDatas*>(m_ProcessList.GetNext(Pos));

        if (m_TmpData != NULL)
        {
            m_TotalWorkload += m_TmpData->GetWorkload();
            m_TotalCost += m_TmpData->GetCost();
            m_TotalCostHMO += m_TmpData->GetCostHMO();
        }
    }

    // Mets à jour le niveau courant par processus, en ajoutant les valeurs des niveaux enfants.
    POSITION ChildPos = m_ChildPrestationsList.GetHeadPosition();

    while (ChildPos != NULL)
    {
        _ZBPrestationsDatas* m_TmpChild =
            dynamic_cast<_ZBPrestationsDatas*>(m_ChildPrestationsList.GetNext(ChildPos));

        if (m_TmpChild != NULL)
        {
            POSITION ChildList = m_TmpChild->GetProcessList()->GetHeadPosition();

            while (ChildList != NULL)
            {
                _ZBProcessDatas* m_TmpChildList =
                    dynamic_cast<_ZBProcessDatas*>(m_TmpChild->GetProcessList()->GetNext(ChildList));

                if (m_TmpChildList != NULL)
                {
                    BOOL        b_IsInCurList = FALSE;
                    POSITION    CurList = m_ProcessList.GetHeadPosition();

                    while (CurList != NULL)
                    {
                        _ZBProcessDatas* m_TmpCurList =
                            dynamic_cast<_ZBProcessDatas*>(m_ProcessList.GetNext(CurList));

                        if (m_TmpCurList != NULL)
                        {
                            if (m_TmpCurList->GetName() == m_TmpChildList->GetName())
                            {
                                m_TmpCurList->SetWorkload(m_TmpCurList->GetWorkload() + m_TmpChildList->GetWorkload());
                                m_TmpCurList->SetCost(m_TmpCurList->GetCost() + m_TmpChildList->GetCost());
                                m_TmpCurList->SetCostHMO(m_TmpCurList->GetCostHMO() + m_TmpChildList->GetCostHMO());
                                b_IsInCurList = TRUE;
                            }
                        }
                    }

                    // Crée une nouvelle donnée pour le total si la donnée recherchée n'existait pas dans la liste.
                    if (b_IsInCurList == FALSE)
                    {
                        _ZBProcessDatas* m_Data = new _ZBProcessDatas();

                        // Obtient les données standards depuis le processus.
                        m_Data->SetName(m_TmpChildList->GetName());
                        m_Data->SetWorkload(m_TmpChildList->GetWorkload());
                        m_Data->SetCost(m_TmpChildList->GetCost());
                        m_Data->SetCostHMO(m_TmpChildList->GetCostHMO());
                        m_Data->SetPercentage(m_TmpChildList->GetPercentage());

                        m_ProcessList.AddTail(m_Data);
                    }
                    else b_IsInCurList = FALSE;
                }
            }
        }
    }
}

// Cette fonction effectue le calcul des totaux des charges et des coûts par niveau de hiérarchie.
void _ZBPrestationsDatas::UpdateTotals()
{
    m_TotalWorkload = 0;
    m_TotalCost = 0;

    // Additionne la valeur des totaux enfants au totaux du niveau courant.
    POSITION Pos = m_ChildPrestationsList.GetHeadPosition();

    while (Pos != NULL)
    {
        _ZBPrestationsDatas* m_TmpData = dynamic_cast<_ZBPrestationsDatas*>(m_ChildPrestationsList.GetNext(Pos));

        if (m_TmpData != NULL)
        {
            m_TmpData->UpdateTotals();

            m_TotalWorkload += m_TmpData->GetTotalWorkload();
            m_TotalCost += m_TmpData->GetTotalCost();
            m_TotalCostHMO += m_TmpData->GetTotalCostHMO();
        }
    }

    InternalUpdateTotals();
}

// Cette fonction effectue l'association des données entre les prestations et les processus qui les contiennent.
void _ZBPrestationsDatas::Associate(PSS_ProcessSymbolBP* Process)
{
    // Effectue la récursion pour chaque niveaux de prestations.
    POSITION Pos = m_ChildPrestationsList.GetHeadPosition();

    while (Pos != NULL)
    {
        _ZBPrestationsDatas* m_TmpData =
            dynamic_cast<_ZBPrestationsDatas*>(m_ChildPrestationsList.GetNext(Pos));

        if (m_TmpData != NULL)
        {
            m_TmpData->Associate(Process);
        }
    }

    // Obtient la liste des prestations contenues dans le processus à associer.
    PSS_Tokenizer m_PrestationsList = Process->GetPrestationsList();

    // Recherche si la prestation courante est contenue dans ce processus.
    for (size_t i = 0; i < m_PrestationsList.GetTokenCount(); i++)
    {
        CString m_PrestationInProcessName = _T("");
        m_PrestationsList.GetTokenAt(i, m_PrestationInProcessName);

        // Si la prestation courante est contenue dans le processus, associe les données nécessaires aux calculs.
        if (m_PrestationName == m_PrestationInProcessName)
        {
            _ZBProcessDatas* m_Data = new _ZBProcessDatas();

            ZBPropertySet PropSet;
            Process->FillProperties(PropSet);

            ZBPropertyIterator j(&PropSet);
            ZBProperty* pProp;

            BOOL IsGoodPrestationName = FALSE;

            // Obtient la valeur du pourcentage d'activité de la prestation dans le processus à associer.
            for (pProp = j.GetFirst(); pProp; pProp = j.GetNext())
            {
                // Recherche la prestation concernée.
                if (pProp->GetCategoryID() == ZS_BP_PROP_PRESTATIONS &&
                    pProp->GetItemID() == M_Prestation_Name)
                {
                    if (pProp->GetValueString() == m_PrestationName)
                    {
                        IsGoodPrestationName = TRUE;
                    }
                }

                // Obtient la valeur de pourcentage de la prestation.
                if (pProp->GetCategoryID() == ZS_BP_PROP_PRESTATIONS &&
                    pProp->GetItemID() == M_Prestation_Percentage &&
                    IsGoodPrestationName == TRUE)
                {
                    switch (pProp->GetPTValueType())
                    {
                        case ZBProperty::PT_DOUBLE:
                        {
                            m_Data->SetPercentage(pProp->GetValueDouble());
                            break;
                        }

                        case ZBProperty::PT_FLOAT:
                        {
                            m_Data->SetPercentage((double)pProp->GetValueFloat());
                            break;
                        }
                    }

                    IsGoodPrestationName = FALSE;
                }
            }

            // Obtient les données à associer. Les charges de travail et coûts sont multipliées par le taux
            // d'activité de la prestation dans le processus.
            m_Data->SetName(Process->GetSymbolName());
            m_Data->SetWorkload(Process->GetProcessWorkloadForecast() * m_Data->GetPercentage());
            m_Data->SetCost(Process->GetProcessCostForecast() * m_Data->GetPercentage());
            m_Data->SetCostHMO(Process->GetProcessCostHMO() * m_Data->GetPercentage());

            m_ProcessList.AddTail(m_Data);

            // Nettoie la mémoire utilisée pour la recherche.
            for (pProp = j.GetFirst(); pProp; pProp = j.GetNext())
            {
                if (pProp != NULL)
                {
                    delete pProp;
                }
            }
        }
    }
}

// ******************************************************************************************************
// *                                Classe ZBPrestationsReportGenerator                                    *
// ******************************************************************************************************

IMPLEMENT_SERIAL(ZBPrestationsReportGenerator, ZBModelBPReportGenerator, g_DefVersion)

// ******************************************************************************************************
// *                                   Construction et destruction                                        *
// ******************************************************************************************************

// Constructeur par défaut de la classe ZBPrestationsReportGenerator.
ZBPrestationsReportGenerator::ZBPrestationsReportGenerator(ZDGridDocument*                pDoc                /*= NULL*/,
                                                           PSS_ProcessGraphModelMdlBP*    pModel                /*= NULL*/,
                                                           PSS_ProcessGraphModelDoc*        pSourceDoc            /*= NULL*/,
                                                           bool                        IncludeMonthDetails    /*= true*/)
    : ZBModelBPReportGenerator(pDoc, pModel, pSourceDoc),
    m_IncludeMonthDetail(IncludeMonthDetails)
{
    // Initialise le stype pour les cellules d'en-tête.
    m_HeaderStyle.SetTextColor(defCOLOR_BLACK)                    // Couleur du texte
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))    // Police du texte
                 .SetSize(10)                                        // Taille du texte
                 .SetBold(FALSE))                                // Gras
        .SetInterior(defCOLOR_GREYPROCESS);                // Couleur de fond

// Initialise le style pour les cellules composant le corps des rapports.
    m_NormalStyle.SetTextColor(defCOLOR_BLACK)                    // Couleur du texte
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))    // Police du texte
                 .SetSize(10)                                        // Taille du texte
                 .SetBold(FALSE))                                // Gras
        .SetInterior(defCOLOR_WHITE);                    // Couleur de fond

    m_BlackBorderStyle.SetBorders(gxBorderAll, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_AmountFormatStyle.SetFormat(GX_FMT_COMMA).SetPlaces(0);
    m_NumericCellStyle.SetValueType(GX_VT_NUMERIC).SetPlaces(0);

    // Définit les tailles des cellules de l'ên-tête.
    m_HeaderPrestationsTitle.cx = 300;
    m_HeaderPrestationsTitle.cy = 40;
    m_HeaderStandardTitle.cx = 150;
    m_HeaderStandardTitle.cy = 0;
    m_HeadersDetailsTitle.cx = 80;
    m_HeadersDetailsTitle.cy = 0;

    // Crée et associe les données nécessaires au rapport.
    FillPrestationsDatas();
}

// Destructeur de la classe ZBPrestationsReportGenerator.
ZBPrestationsReportGenerator::~ZBPrestationsReportGenerator()
{
    RemoveObsoleteDatas();

    POSITION Pos = m_PrestationsArray.GetHeadPosition();

    while (Pos != NULL)
    {
        _ZBPrestationsDatas* m_TmpData = dynamic_cast<_ZBPrestationsDatas*>(m_PrestationsArray.GetNext(Pos));

        if (m_TmpData != NULL)
        {
            delete m_TmpData;
            m_TmpData = NULL;
        }
    }

    m_PrestationsArray.RemoveAll();
}

// ******************************************************************************************************
// *                       Fonctions privées de la classe ZBPrestationsReportGenerator                    *
// ******************************************************************************************************

// Cette fonction nettoie les ressources redondantes utilisées pour la génération de chaque rapport.
void ZBPrestationsReportGenerator::RemoveObsoleteDatas()
{
    m_ProcessNameArray.RemoveAll();
    m_TabNameArray.RemoveAll();
}

// Cette fonction crée et associe les données nécessaires au rapport.
void ZBPrestationsReportGenerator::FillPrestationsDatas()
{
    _ZBPrestationsDatas* m_PrestationData = new _ZBPrestationsDatas();

    m_PrestationData->GenerateHierarchy(m_pModel->GetMainLogicalPrestations(), 0);

    m_PrestationsArray.AddTail(m_PrestationData);

    Associate(m_pModel);
    UpdateTotals();
}

// Fonction permettant d'associer les données des processus avec les prestations assignées à ceux-ci.
void ZBPrestationsReportGenerator::Associate(PSS_ProcessGraphModelMdlBP* m_RootModel)
{
    if (m_RootModel != NULL)
    {
        // Obtient l'ensemble des pages contenues dans le contrôleur de modèles.
        PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = m_RootModel->GetPageSet();

        if (pSet != NULL)
        {
            PSS_ProcessGraphModelMdl::IProcessGraphPageIterator i(pSet);

            // On passe en revue toutes les pages enfants contenues dans le contrôleur de modèles.
            for (PSS_ProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
            {
                // Obtient le contrôleur de modèle de la page courante.
                PSS_ProcessGraphModelMdlBP* m_CurModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

                if (m_CurModel != NULL)
                {
                    // Obtient l'ensemble des symboles contenus dans le contrôleur de modèles.
                    CODComponentSet* pCompSet = m_CurModel->GetComponents();

                    if (pCompSet != NULL)
                    {
                        // On passe en revue toutes les symboles contenus dans le contrôleur de modèles.
                        for (int j = 0; j < pCompSet->GetSize(); ++j)
                        {
                            CODComponent* pComponent = pCompSet->GetAt(j);

                            // Contrôle que le composant soit valide, et identifie s'il s'agit d'un processus.
                            if (pComponent && ISA(pComponent, PSS_ProcessSymbolBP))
                            {
                                // Convertit le symbole.
                                PSS_ProcessSymbolBP* m_Process = dynamic_cast<PSS_ProcessSymbolBP*>(pComponent);

                                // Obtient le contrôleur de modèle du processus.
                                PSS_ProcessGraphModelMdlBP* m_ChildModel =
                                    dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_Process->GetModel());

                                // Appel récursif à FillProcessAssociation, jusqu'à ce que tous les
                                // processus du modèle aient été visités.
                                Associate(m_ChildModel);

                                // Associe les valeurs du processus trouvé aux prestations racines.
                                POSITION Pos = m_PrestationsArray.GetHeadPosition();

                                while (Pos != NULL)
                                {
                                    _ZBPrestationsDatas* m_TmpData =
                                        dynamic_cast<_ZBPrestationsDatas*>(m_PrestationsArray.GetNext(Pos));

                                    if (m_TmpData != NULL)
                                    {
                                        m_TmpData->Associate(m_Process);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Cette fonction permet le calcul et la mise à jour des totaux des charges et coûts des processus.
void ZBPrestationsReportGenerator::UpdateTotals()
{
    POSITION Pos = m_PrestationsArray.GetHeadPosition();

    while (Pos != NULL)
    {
        _ZBPrestationsDatas* m_TmpData = dynamic_cast<_ZBPrestationsDatas*>(m_PrestationsArray.GetNext(Pos));

        if (m_TmpData != NULL)
        {
            m_TmpData->UpdateTotals();
        }
    }
}

// Contrôle et ajoute si nécessaire la quantité de colonnes souhaitées depuis la position courante dans le document.
CPoint ZBPrestationsReportGenerator::CheckColumn(ZBOStreamGrid &ostream, int Quantity)
{
    int top = 0;
    int left = 0;

    // Obtient la position courante.
    ostream.GetCurSel(left, top);

    // Obtient le nombre de colonnes du document.
    ROWCOL ColCount = ostream.GetGridCore()->GetColCount();

    // Si pas assez, ajoute la quantité de colonnes spécifiées.
    if ((left + Quantity) > (int)ColCount)
    {
        ostream.GetGridCore()->SetColCount(ColCount + Quantity);
    }

    return CPoint(top, left);
}

// Cette fonction permet la génération du rapport des prestations.
bool ZBPrestationsReportGenerator::FillGridPrestationsReport(CGXGridCore& GridCore, int Index)
{
    ZBOStreamGrid ostream(&GridCore);

    // Taille par défaut.
    GridCore.SetRowCount(60);        // 60 lignes
    GridCore.SetColCount(15);        // 15 colonnes

    // Obtient le pointeur sur l'objet vue de la grille.
    ZVGridView*    pView = NULL;
    CWnd*        pWnd = GridCore.GridWnd();

    if (pWnd && ISA(pWnd, ZVGridView))
    {
        pView = dynamic_cast<ZVGridView*>(pWnd);
    }

    // Publie les en-têtes du rapport.
    FillGridPrestationsHeaders(ostream, pView, Index);

    // Publie les données du rapport.
    POSITION Pos = m_PrestationsArray.GetHeadPosition();

    while (Pos != NULL)
    {
        _ZBPrestationsDatas* m_TmpData = dynamic_cast<_ZBPrestationsDatas*>(m_PrestationsArray.GetNext(Pos));

        if (m_TmpData != NULL)
        {
            m_TmpData->DisplayDatas(ostream,
                                    m_ProcessNameArray,
                                    m_NormalStyle,
                                    m_AmountFormatStyle,
                                    m_NumericCellStyle,
                                    Index,
                                    m_IncludeMonthDetail);
        }
    }

    return true;
}

// Cette fonction permet la génération des en-têtes pour le rapport des prestations.
void ZBPrestationsReportGenerator::FillGridPrestationsHeaders(ZBOStreamGrid &ostream, ZVGridView* pView, int Index)
{
    CString    s = _T("");
    int        Count = m_ProcessNameArray.GetSize() + 1;

    ostream << _T("\n\n");

    // Création des contrôles pour voir les détails de mensualités des processus.
    if (m_IncludeMonthDetail)
    {
        if (pView)
        {
            ostream << _T("\t");

            for (int i = 0; i < Count; ++i)
            {
                CPoint m_CurPos = CheckColumn(ostream, 20);

                CString Label;
                Label.LoadString(IDS_CHKBOX_LABEL);

                CString ToolTipText;
                ToolTipText.LoadString(IDS_CHKBOX_TTP);

                pView->InsertGroupCtrl(m_CurPos.x,                        // Colonnes
                                       m_CurPos.y,                        // Lignes
                                       (i + 1 < Count) ? 12 : 13,    // Nb. de cellules couvertes
                                       true,                            // Horizontal
                                       true,                            // Mode basculement
                                       Label,
                                       ToolTipText);

                // Déplace à droite vers le prochain contrôle.
                ostream.Right(13);
            }
        }
    }

    ostream << _T("\t");

    if (m_IncludeMonthDetail)
    {
        CheckColumn(ostream, (Count * 13));
    }
    else
    {
        CheckColumn(ostream, Count);
    }

    ostream << _T("\n");

    // Obtient le libellé du titre de la colonne des prestations.
    switch (Index)
    {
        case 0:
        {
            s.LoadString(IDS_WORKLOAD_PRESTATIONREPORT_LBLRPT2);
            break;
        }

        case 1:
        {
            s.LoadString(IDS_COSTUNIT_PRESTATIONREPORT_LBLRPT2);
            break;
        }

        case 2:
        {
            s.LoadString(IDS_COSTHMOUNIT_PRESTATIONREPORT_LBLRPT2);
            break;
        }
    }

    // Définit le format de la cellule du titre de la colonne des prestations.
    ostream << s;
    ostream << m_HeaderPrestationsTitle;
    ostream << m_HeaderStyle;
    ostream << _T("\t");

    // Inscrit le nom du modèle
    ostream << m_pModel->GetModelName();
    ostream << m_HeaderStandardTitle;
    ostream << m_HeaderStyle;

    // Définit le libellé pour chaque mois.
    if (m_IncludeMonthDetail)
    {
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT1);
        ostream << s;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT2);
        ostream << s;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT3);
        ostream << s;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT4);
        ostream << s;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT5);
        ostream << s;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT6);
        ostream << s;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT7);
        ostream << s;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT8);
        ostream << s;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT9);
        ostream << s;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT10);
        ostream << s;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT11);
        ostream << s;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT12);
        ostream << s;
        ostream << m_HeadersDetailsTitle;
        ostream << m_HeaderStyle;
        ostream << m_BlackBorderStyle;
    }

    // Inscrit l'en-tête pour chaque sous-processus.
    for (int i = 0; i < m_ProcessNameArray.GetSize(); ++i)
    {
        ostream << _T("\t");
        ostream << m_ProcessNameArray.GetAt(i);
        ostream << m_HeaderStandardTitle;
        ostream << m_HeaderStyle;

        // Définit le libellé pour chaque mois.
        if (m_IncludeMonthDetail)
        {
            ostream << _T("\t");

            // Then each month
            s.LoadString(IDS_MONTH_LBLRPT1);
            ostream << s;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT2);
            ostream << s;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT3);
            ostream << s;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT4);
            ostream << s;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT5);
            ostream << s;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT6);
            ostream << s;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT7);
            ostream << s;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT8);
            ostream << s;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT9);
            ostream << s;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT10);
            ostream << s;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT11);
            ostream << s;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT12);
            ostream << s;
            ostream << m_HeadersDetailsTitle;
            ostream << m_HeaderStyle;
            ostream << m_BlackBorderStyle;
        }
    }

    // Gèle les colonnes inamovibles.
    ZDGridDocument* pDoc = pView->GetDocument();

    if (pDoc)
    {
        pDoc->SetFrozenRow(4);
        pDoc->SetFrozenCol(1);

        pDoc->SetFrozenHeaderRow(4);
        pDoc->SetFrozenHeaderCol(1);

        pView->FreezeSplitter();
    }
}

// ******************************************************************************************************
// *                   Fonctions protégées de la classe ZBPrestationsReportGenerator                    *
// ******************************************************************************************************

// Cette fonction permet de remplir la liste des index pour la séléction des pages 
void ZBPrestationsReportGenerator::FillTabArray()
{
    // Ne rien faire si aucun document ou modèle est défini.
    if (!m_pDoc || !m_pModel)
    {
        return;
    }

    // D'abord, éliminer les éléments obsolètes.
    RemoveObsoleteDatas();

    // Obtient la liste des noms des processus.
    ZUExtractProcessName ExtractProcessName(m_pModel);
    ExtractProcessName.FillProcessNameArray(&m_ProcessNameArray);

    // Constuit la hiérarchie des formulaires.
    CString s = _T("");

    // Formulaire "Charge de travail"
    s.LoadString(IDS_WORKLOAD_TAB);
    m_TabNameArray.Add(s);

    // Formulaire "Coût"
    s.LoadString(IDS_COST_TAB);
    m_TabNameArray.Add(s);

    // Formulaire "Coût HMO"
    s.LoadString(IDS_COSTHMO_TAB);
    m_TabNameArray.Add(s);
}

// ******************************************************************************************************
// *                    Fonctions publiques de la classe ZBPrestationsReportGenerator                    *
// ******************************************************************************************************

// Cette fonction est la fonction d'entrée appelée par le générateur de documents ZDGridReportDocument.
bool ZBPrestationsReportGenerator::FillGrid(CGXGridCore& GridCore, size_t Index)
{
    return FillGridPrestationsReport(GridCore, Index);
}

// Fonction permettant de construire et de retourner le nom du modèle.
const CString ZBPrestationsReportGenerator::GetReportTitle() const
{
    CString s;

    if (m_pDoc)
    {
        s = m_pDoc->GetTitle();
    }

    CString ReportType;
    ReportType.LoadString(IDS_PRESTATIONS_RPT_T);

    s += _T(" [");
    s += ReportType;
    s += _T(" : ");

    if (m_pModel)
    {
        s += m_pModel->GetModelName();
    }
    else
    {
        s += _T("???");
    }

    s += _T(" ]");

    return s;
}
