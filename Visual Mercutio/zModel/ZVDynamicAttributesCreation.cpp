/****************************************************************************************************************
 *                                          Classe ZVDynamicAttributesCreation                                    *
 ****************************************************************************************************************
 * Cette classe, intégrant deux sous-classes (ZVDynamicAttributesCreationS1 et ZVDynamicAttributesCreationS2),    *
 * permet à l'utilisateur de créer un nouvel attribut dynamique, en suivant les instructions données par les    *
 * boîtes de dialogues contenues dans chacune des classes ZVDynamicAttributesCreationSx.                        *
 ****************************************************************************************************************/

#include "stdafx.h"
#include "ZVDynamicAttributesCreation.h"

#include "ZUDynamicAttributesManipulator.h"

#include "zModel\ProcGraphModelDoc.h"
#include "zProperty\ZBDynamicPropertiesManager.h"

#include "zBaseLib\PSS_Tokenizer.h"

#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// **************************************************************************************************************
// *                        Classe ZVDynamicAttributesCreation : Construction/Destruction                        *
// **************************************************************************************************************

// Constructeur par défaut de la classe ZVDynamicAttributesCreation.
ZVDynamicAttributesCreation::ZVDynamicAttributesCreation(PSS_ProcessGraphModelDoc* pModelDoc, bool SymbolSelected)
    : m_pModelDoc(pModelDoc),
    m_SymbolSelected(SymbolSelected)
{}

// Destructeur de la classe ZVDynamicAttributesCreation.
ZVDynamicAttributesCreation::~ZVDynamicAttributesCreation()
{}

// **************************************************************************************************************
// *                                Classe ZVDynamicAttributesCreation : Fonctions                                *
// **************************************************************************************************************

int    ZVDynamicAttributesCreation::DoModal()
{
    if (!m_pModelDoc)
        return IDCANCEL;

    ZVDynamicAttributesCreationS1 Cat(m_pModelDoc);

    if (Cat.DoModal() == IDCANCEL)
        return IDCANCEL;

    // Assigns values
    m_CategoryName = Cat.GetCategoryName();

    ZVDynamicAttributesCreationS2 Attr(m_pModelDoc, m_CategoryName, m_SymbolSelected);

    if (Attr.DoModal() == IDCANCEL)
        return IDCANCEL;

    // Assigns values
    m_AttributeName = Attr.GetAttributeName();
    m_AttributeDescription = Attr.GetAttributeDescription();
    m_PropertyType = Attr.GetPropertyType();
    m_Visibility = Attr.GetVisibility();

    return IDOK;
}

// **************************************************************************************************************
// *                               Classe ZVDynamicAttributesCreationS1 : Message map                            *
// **************************************************************************************************************

BEGIN_MESSAGE_MAP(ZVDynamicAttributesCreationS1, PSS_WizardDialog)
    //{{AFX_MSG_MAP(ZVDynamicAttributesCreationS1)
    ON_BN_CLICKED(IDNEXT, OnNext)
    ON_EN_CHANGE(IDC_CATEGORYNAME, OnChangeCategoryName)
    ON_LBN_SELCHANGE(IDC_CATEGORY_LIST, OnSelchangeCategoryList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// **************************************************************************************************************
// *                       Classe ZVDynamicAttributesCreationS1 : Construction/Destruction                        *
// **************************************************************************************************************

// Constructeur par défaut de la classe ZVDynamicAttributesCreationS1.
ZVDynamicAttributesCreationS1::ZVDynamicAttributesCreationS1(PSS_ProcessGraphModelDoc* pModelDoc, CWnd* pParent /*=NULL*/) :
    PSS_WizardDialog(ZVDynamicAttributesCreationS1::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_DYNATTRS1_ST_S,
                     IDS_WZ_DYNATTRS1_ST_T),
    m_pModelDoc(pModelDoc),
    m_InternalNameChange(false)
{
    //{{AFX_DATA_INIT(ZVDynamicAttributesCreationS1)
    m_CategoryName = _T("");
    //}}AFX_DATA_INIT
}

// **************************************************************************************************************
// *                               Classe ZVDynamicAttributesCreationS1 : Fonctions                                *
// **************************************************************************************************************

void ZVDynamicAttributesCreationS1::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVDynamicAttributesCreationS1)
    DDX_Control(pDX, IDC_CATEGORY_LIST, m_CategoryList);
    DDX_Text(pDX, IDC_CATEGORYNAME, m_CategoryName);
    //}}AFX_DATA_MAP
}

bool ZVDynamicAttributesCreationS1::CheckData()
{
    UpdateData(TRUE);

    if (m_CategoryName.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_PROPCATEGORYNAME_MISSING, MB_OK);
        return false;
    }

    for (int i = 0; i < m_StaticAttribArray.GetSize(); ++i)
    {
        if (m_StaticAttribArray.GetAt(i) == m_CategoryName)
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_PROPCATEGORYNAME_EXIST, MB_OK);
            return false;
        }
    }

    return true;
}

// **************************************************************************************************************
// *                           Classe ZVDynamicAttributesCreationS1 : message handlers                            *
// **************************************************************************************************************

BOOL ZVDynamicAttributesCreationS1::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    if (m_pModelDoc &&
        m_pModelDoc->GetModel() &&
        m_pModelDoc->GetDynamicPropertiesManager())
    {
        ZUDynamicAttributesManipulator::GetCategories(m_pModelDoc->GetModel(),
                                                      m_StaticAttribArray,
                                                      m_DynamicAttribArray);

        // Now, fill list box with dynamic categories
        for (int i = 0; i < m_DynamicAttribArray.GetSize(); ++i)
            m_CategoryList.AddString(m_DynamicAttribArray.GetAt(i));
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVDynamicAttributesCreationS1::OnOK()
{
    // Check information
    if (!CheckData())
        return;

    PSS_WizardDialog::OnOK();
}

void ZVDynamicAttributesCreationS1::OnNext()
{
    // Check information
    if (!CheckData())
        return;

    EndDialog(IDNEXT);
}

void ZVDynamicAttributesCreationS1::OnChangeCategoryName()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the ZIWizardDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    if (m_InternalNameChange)
        return;

    UpdateData(TRUE);
    m_CategoryList.SelectString(0, (const char*)m_CategoryName);
}

void ZVDynamicAttributesCreationS1::OnSelchangeCategoryList()
{
    int CurSel = m_CategoryList.GetCurSel();
    if (CurSel != LB_ERR)
    {
        m_InternalNameChange = true;

        m_CategoryList.GetText(CurSel, m_CategoryName);
        UpdateData(FALSE);

        m_InternalNameChange = false;
    }
}

// **************************************************************************************************************
// *                               Classe ZVDynamicAttributesCreationS2 : Message map                            *
// **************************************************************************************************************

BEGIN_MESSAGE_MAP(ZVDynamicAttributesCreationS2, PSS_WizardDialog)
    //{{AFX_MSG_MAP(ZVDynamicAttributesCreationS2)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// **************************************************************************************************************
// *                       Classe ZVDynamicAttributesCreationS2 : Construction/Destruction                        *
// **************************************************************************************************************

// Constructeur par défaut de la classe ZVDynamicAttributesCreationS2.
ZVDynamicAttributesCreationS2::ZVDynamicAttributesCreationS2(PSS_ProcessGraphModelDoc*    pModelDoc,
                                                             const CString                Category,
                                                             bool                        SymbolSelected,
                                                             CWnd*                        pParent /*=NULL*/) :
    PSS_WizardDialog(ZVDynamicAttributesCreationS2::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_DYNATTRS2_ST_S,
                     IDS_WZ_DYNATTRS2_ST_T),
    m_pModelDoc(pModelDoc),
    m_Category(Category),
    m_SymbolSelected(SymbolSelected)
{
    //{{AFX_DATA_INIT(ZVDynamicAttributesCreationS2)
    m_AttributeDescription = _T("");
    m_AttributeName = _T("");
    //}}AFX_DATA_INIT
}

// **************************************************************************************************************
// *                               Classe ZVDynamicAttributesCreationS2 : Fonctions                                *
// **************************************************************************************************************

void ZVDynamicAttributesCreationS2::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVDynamicAttributesCreationS2)
    DDX_Control(pDX, IDC_ATTRIB_VISIBILITY, m_AttributeVisibility);
    DDX_Control(pDX, IDC_ATTRIB_TYPE, m_AttributeType);
    DDX_Text(pDX, IDC_ATTR_DESCRIPTION, m_AttributeDescription);
    DDX_Text(pDX, IDC_ATTRIB_NAME, m_AttributeName);
    //}}AFX_DATA_MAP
}

bool ZVDynamicAttributesCreationS2::CheckData()
{
    UpdateData(TRUE);

    if (m_AttributeName.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_PROPATTRIBNAME_MISSING, MB_OK);
        return false;
    }

    if (!m_pModelDoc || !m_pModelDoc->GetDynamicPropertiesManager())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_PROP_INITIALIZATIONPRB, MB_OK);
        return false;
    }

    if (m_pModelDoc->GetDynamicPropertiesManager()->PropertyItemExist(m_Category, m_AttributeName))
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_PROPATTRIBNAME_EXIST, MB_OK);
        return false;
    }

    m_Visibility = m_AttributeVisibility.GetCurSel();
    int DataType = m_AttributeType.GetCurSel();

    switch (DataType)
    {
        case 0:
        {
            m_PropertyType = ZBProperty::PT_EDIT_STRING;
            break;
        }

        case 1:
        {
            m_PropertyType = ZBProperty::PT_EDIT_MULTILINE;
            break;
        }

        case 2:
        {
            m_PropertyType = ZBProperty::PT_EDIT_NUMBER;
            break;
        }

        case 3:
        {
            m_PropertyType = ZBProperty::PT_EDIT_DATE;
            break;
        }

        case 4:
        {
            m_PropertyType = ZBProperty::PT_EDIT_TIME;
            break;
        }

        case 5:
        {
            m_PropertyType = ZBProperty::PT_EDIT_DURATION;
            break;
        }

        default:
            return false;
    }

    return true;
}
// **************************************************************************************************************
// *                           Classe ZVDynamicAttributesCreationS1 : message handlers                            *
// **************************************************************************************************************

BOOL ZVDynamicAttributesCreationS2::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    CString strValues;

    // Fill combo-boxes
    PSS_Tokenizer token;

    // Data type combo.
    strValues.LoadString(IDS_PROPTYPE_LIST);

    CString str = token.GetFirstToken(strValues);

    // Run through all tokens
    while (!str.IsEmpty())
    {
        m_AttributeType.AddString(str);

        // Get the next token
        str = token.GetNextToken();
    }

    // Selects the first item in the list
    m_AttributeType.SetCurSel(0);

    // Visibility combo.
    strValues.LoadString(IDS_PROPVISIBILITY_LIST);

    str = token.GetFirstToken(strValues);

    // Run through all tokens
    while (!str.IsEmpty())
    {
        m_AttributeVisibility.AddString(str);

        // Get the next token
        str = token.GetNextToken();
    }

    // Selects the first item in the list
    m_AttributeVisibility.SetCurSel(0);

    // If no symbol are selected
    if (!m_SymbolSelected)
    {
        m_AttributeVisibility.SetCurSel(2);
        m_AttributeVisibility.EnableWindow(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVDynamicAttributesCreationS2::OnOK()
{
    // Check information
    if (!CheckData())
        return;

    PSS_WizardDialog::OnOK();
}

void ZVDynamicAttributesCreationS2::OnNext()
{
    // Check information
    if (!CheckData())
        return;

    EndDialog(IDNEXT);
}
