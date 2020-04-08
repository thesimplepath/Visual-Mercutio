/****************************************************************************
 * ==> PSS_PublishModel ----------------------------------------------------*
 ****************************************************************************
 * Description : Publishes a model                                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PublishModel.h"

// std
#include <memory>

// processsoft
#include "zBaseLib\PSS_SystemOption.h"
#include "zBaseLib\PSS_Tokenizer.h"
#include "zProperty\PSS_PropertyAttributes.h"
#include "PSS_PublishModelWelcomeDialog.h"
#include "PSS_PublishModelSelDirDialog.h"
#include "PSS_PublishModelBannerDialog.h"
#include "PSS_PublishModelAttributesDialog.h"
#include "PSS_PublishModelOptionsDialog.h"

//---------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------
const CString g_PublishModelHTMLSectionName                  = _T("PublishModelToHTML");
const CString g_PublishModelHTMLAddressEntityName            = _T("PublishAddress");
const CString g_PublishModelHTMLLastLanguageEntityName       = _T("LastPublishLanguage");
const CString g_PublishModelHTMLPublishConceptor             = _T("PublishConceptor");
const CString g_PublishModelHTMLPublishConceptorDetails      = _T("PublishConceptorDetails");
const CString g_PublishModelHTMLPublishConceptorDeliverables = _T("PublishConceptorDeliverables");
const CString g_PublishModelHTMLPublishProcess               = _T("PublishProcess");
const CString g_PublishModelHTMLPublishRuleBook              = _T("PublishRuleBook");
const CString g_PublishModelHTMLVisualizeEntityName          = _T("Visualize");
const CString g_PublishModelHTMLLogoFileNameEntityName       = _T("LogoFilename");
const CString g_PublishModelHTMLLogoRefHTMLEntityName        = _T("LogoRef");
//---------------------------------------------------------------------------
// PSS_PublishModel
//---------------------------------------------------------------------------
PSS_PublishModel::PSS_PublishModel(PSS_PropertyAttributes*       pAttributes,
                                   PSS_Properties::IPropertySet* pSet,
                                   const CString&                iniFile) :
    m_pPropAttributes(pAttributes),
    m_pPropSet(pSet),
    m_Language(E_LN_Unknown),
    m_IniFile(iniFile),
    m_VisualizeResult(false),
    m_PublishConceptor(false),
    m_PublishConceptorDetails(false),
    m_PublishConceptorDeliverables(false),
    m_PublishProcess(false),
    m_PublishRuleBook(false)
{}
//---------------------------------------------------------------------------
PSS_PublishModel::PSS_PublishModel(const PSS_PublishModel& other)
{
    THROW("Calling PSS_PublishModel copy constructor is prohibited");
}
//---------------------------------------------------------------------------
const PSS_PublishModel& PSS_PublishModel::operator = (const PSS_PublishModel& other)
{
    THROW("Calling PSS_PublishModel copy operator is prohibited");
}
//---------------------------------------------------------------------------
PSS_PublishModel::~PSS_PublishModel()
{}
//---------------------------------------------------------------------------
BOOL PSS_PublishModel::SelectDir()
{
    PSS_PublishModelWelcomeDialog welcome;

    if (welcome.DoModal() == IDCANCEL)
        return FALSE;

    // load the last state
    LoadStateFromIniFile();

    // load attributes
    LoadAttributesFromIniFile();

    PSS_PublishModelSelDirDialog select(m_Directory, &m_ArrayOfAddress);

    if (select.DoModal() == IDCANCEL)
        return FALSE;

    // no directory selected
    if (select.GetDirectory().IsEmpty())
        return FALSE;

    m_Directory = select.GetDirectory();

    PSS_PublishModelBannerDialog banner(m_HyperLink, m_ImageFileName);

    if (banner.DoModal() == IDCANCEL)
        return FALSE;

    m_ImageFileName = banner.GetImageFileName();
    m_HyperLink = banner.GetHyperLink();

    CWaitCursor                      cursor;
    PSS_PublishModelAttributesDialog attributes(m_pPropAttributes, m_pPropSet);

    if (attributes.DoModal() == IDCANCEL)
        return FALSE;

    PSS_PublishModelOptionsDialog options(m_VisualizeResult,
                                          m_PublishConceptor,
                                          m_PublishConceptorDetails,
                                          m_PublishConceptorDeliverables,
                                          m_PublishProcess,
                                          m_PublishRuleBook,
                                          m_Language);

    if (options.DoModal() == IDCANCEL)
        return FALSE;

    m_VisualizeResult              = options.GetVisualize();
    m_PublishConceptor             = options.GetPublishConceptor();
    m_PublishConceptorDetails      = options.GetPublishConceptorDetails();
    m_PublishConceptorDeliverables = options.GetPublishConceptorDeliverables();
    m_PublishProcess               = options.GetPublishProcess();
    m_PublishRuleBook              = options.GetPublishRuleBook();
    m_Language                     = options.GetLanguage();

    // save the state
    SaveStateToIniFile();

    // also save attributes
    SaveAttributesToIniFile();

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PublishModel::AddAttribute(PSS_PropertyAttributes::IAttribute* pAttribute)
{
    if (!pAttribute)
        return;

    PSS_PropertyAttributes* pPropTemp = GetPropAttributes();
    ASSERT(pPropTemp);

    if (!FindAttribute(pAttribute->GetCategoryID(), pAttribute->GetItemID()))
        pPropTemp->GetAttributeSet().Add(pAttribute);
    else
        // otherwise delete the attribute
        delete pAttribute;
}
//---------------------------------------------------------------------------
PSS_PropertyAttributes::IAttribute* PSS_PublishModel::FindAttribute(int categoryID, int itemID)
{
    PSS_PropertyAttributes* pPropTemp = GetPropAttributes();
    ASSERT(pPropTemp);

    PSS_PropertyAttributes::IAttributeIterator it(&(pPropTemp->GetAttributeSet()));

    for (PSS_PropertyAttributes::IAttribute* pAtt = it.GetFirst(); pAtt; pAtt = it.GetNext())
        if (pAtt->GetCategoryID() == categoryID && pAtt->GetItemID() == itemID)
            return pAtt;

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_PublishModel::RemoveAllAttributes()
{
    PSS_PropertyAttributes* pPropTemp = GetPropAttributes();
    ASSERT(pPropTemp);

    PSS_PropertyAttributes::IAttributeIterator it(&(pPropTemp->GetAttributeSet()));

    for (PSS_PropertyAttributes::IAttribute* pAtt = it.GetFirst(); pAtt; pAtt = it.GetNext())
        delete pAtt;

    pPropTemp->GetAttributeSet().RemoveAll();
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::LoadStateFromIniFile()
{
    PSS_SystemOption systemOption(m_IniFile, g_PublishModelHTMLSectionName);

    // read the options
    m_PublishConceptor             =                        systemOption.ReadOption(g_PublishModelHTMLPublishConceptor,             true);
    m_PublishConceptorDetails      =                        systemOption.ReadOption(g_PublishModelHTMLPublishConceptorDetails,      true);
    m_PublishConceptorDeliverables =                        systemOption.ReadOption(g_PublishModelHTMLPublishConceptorDeliverables, true);
    m_PublishProcess               =                        systemOption.ReadOption(g_PublishModelHTMLPublishProcess,               true);
    m_PublishRuleBook              =                        systemOption.ReadOption(g_PublishModelHTMLPublishRuleBook,              true);
    m_VisualizeResult              =                        systemOption.ReadOption(g_PublishModelHTMLVisualizeEntityName,          true);
    m_Language                     = static_cast<ELanguage>(systemOption.ReadOption(g_PublishModelHTMLLastLanguageEntityName,       0));
    m_Directory                    =                        systemOption.ReadOption(g_PublishModelHTMLAddressEntityName,            _T(""));
    m_ImageFileName                =                        systemOption.ReadOption(g_PublishModelHTMLLogoFileNameEntityName,       _T(""));
    m_HyperLink                    =                        systemOption.ReadOption(g_PublishModelHTMLLogoRefHTMLEntityName,        _T(""));

    CString     keyName;
    CString     addr;
    std::size_t index = 0;

    // remove all elements
    m_ArrayOfAddress.RemoveAll();

    // set the maximum loop at thousand objects, which is big enough
    const std::size_t max = 1000;

    do
    {
        // format the key
        keyName.Format(_T("%s_%d"), (const char*)g_PublishModelHTMLAddressEntityName, index);
        addr = systemOption.ReadOption(keyName, _T(""));

        if (addr.IsEmpty())
            break;

        // add element to the table
        m_ArrayOfAddress.Add(addr);

        ++index;
    }
    while (index < max);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::SaveStateToIniFile()
{
    PSS_SystemOption systemOption(m_IniFile, g_PublishModelHTMLSectionName);

    // save the options
    systemOption.WriteOption(g_PublishModelHTMLPublishConceptor,             m_PublishConceptor);
    systemOption.WriteOption(g_PublishModelHTMLPublishConceptorDetails,      m_PublishConceptorDetails);
    systemOption.WriteOption(g_PublishModelHTMLPublishConceptorDeliverables, m_PublishConceptorDeliverables);
    systemOption.WriteOption(g_PublishModelHTMLPublishProcess,               m_PublishProcess);
    systemOption.WriteOption(g_PublishModelHTMLPublishRuleBook,              m_PublishRuleBook);
    systemOption.WriteOption(g_PublishModelHTMLVisualizeEntityName,          m_VisualizeResult);
    systemOption.WriteOption(g_PublishModelHTMLLastLanguageEntityName,       m_Language);
    systemOption.WriteOption(g_PublishModelHTMLAddressEntityName,            m_Directory);
    systemOption.WriteOption(g_PublishModelHTMLLogoFileNameEntityName,       m_ImageFileName);
    systemOption.WriteOption(g_PublishModelHTMLLogoRefHTMLEntityName,        m_HyperLink);

    CString keyName;

    // add the address to the array
    bool found = false;

    for (int i = 0; i < m_ArrayOfAddress.GetSize(); ++i)
        if (m_ArrayOfAddress.GetAt(i) == m_Directory)
            found = true;

    if (!found)
        m_ArrayOfAddress.Add(m_Directory);

    for (int i = 0; i < m_ArrayOfAddress.GetSize(); ++i)
    {
        // format the key
        keyName.Format(_T("%s_%d"), (const char*)g_PublishModelHTMLAddressEntityName, i);

        // write the string to the ini file
        systemOption.WriteOption(keyName, m_ArrayOfAddress.GetAt(i));
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::LoadAttributesFromIniFile()
{
    // delete all attributes
    RemoveAllAttributes();

    PSS_SystemOption systemOption(m_IniFile, _T("_PropertyDefaultAttributeSaveStateWeb"));

    CString     keyName;
    CString     line;
    std::size_t index = 0;

    // set the maximum loop at 1 million objects, which is big enough
    const std::size_t max = 100000;

    do
    {
        // Format the key
        keyName.Format(_T("%s%d"), _T("_PropertyDefaultAttributeSaveStateWeb"), index);
        line = systemOption.ReadOption(keyName, _T(""));

        if (line.IsEmpty())
            break;

        ++index;

        CString       str;
        PSS_Tokenizer token;

        // extract the category ID
        str = token.GetFirstToken(line);

        if (str.IsEmpty())
            continue;

        const int categoryID = std::atoi((const char*)str);

        // extract the item ID
        str = token.GetNextToken();

        if (str.IsEmpty())
            continue;

        const int itemID = std::atoi((const char*)str);

        // all objects have been extracted, create the object state
        std::unique_ptr<PSS_PropertyAttributes::IAttribute> pAtt(new PSS_PropertyAttributes::IAttribute(categoryID, itemID));

        // add it to the value array
        AddAttribute(pAtt.get());
        pAtt.release();
    }
    while (index < max);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::SaveAttributesToIniFile()
{
    PSS_SystemOption systemOption(m_IniFile, _T("_PropertyDefaultAttributeSaveStateWeb"));

    // need to delete all records before saving
    DeleteAttributesFromIniFile();

    std::size_t index = 0;
    CString     keyName;

    PSS_PropertyAttributes* pPropTemp = GetPropAttributes();
    ASSERT(pPropTemp);

    PSS_PropertyAttributes::IAttributeIterator it(&(pPropTemp->GetAttributeSet()));

    for (PSS_PropertyAttributes::IAttribute* pAtt = it.GetFirst(); pAtt; pAtt = it.GetNext(), ++index)
    {
        // format the key
        keyName.Format(_T("%s%d"), _T("_PropertyDefaultAttributeSaveStateWeb"), index);

        PSS_Tokenizer token;

        // build the string
        token.AddToken(pAtt->GetCategoryID());
        token.AddToken(pAtt->GetItemID());

        // write the string to the ini file
        systemOption.WriteOption(keyName, token.GetString());
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::DeleteAttributesFromIniFile()
{
    PSS_SystemOption systemOption(m_IniFile, _T("_PropertyDefaultAttributeSaveStateWeb"));

    CString     keyName;
    CString     line;
    std::size_t index = 0;

    // set the maximum loop at 1 million objects, which is big enough
    const std::size_t max = 1000000;

    do
    {
        // format the key
        keyName.Format(_T("%s%d"), _T("_PropertyDefaultAttributeSaveStateWeb"), index);
        line = systemOption.ReadOption(keyName, _T(""));

        if (line.IsEmpty())
            break;

        ++index;

        // easier to set the value to null than to delete the line
        systemOption.WriteOption(keyName, _T("0;0"));
    } while (index < max);

    return true;
}
//---------------------------------------------------------------------------
