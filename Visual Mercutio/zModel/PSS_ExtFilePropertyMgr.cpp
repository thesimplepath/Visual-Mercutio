/****************************************************************************
 * ==> PSS_ExtFilePropertyMgr ----------------------------------------------*
 ****************************************************************************
 * Description : Provides an external file properties manager               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ExtFilePropertyMgr.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zBaseLib\PSS_Tokenizer.h"
#include "zBaseLib\PSS_NetResourceWrapper.h"
#include "zBaseLib\PSS_TemplateFile.h"
#include "zBaseLib\PSS_File.h"
#include "zWinUtil32\PSS_ReferenceFileDialog.h"
#include "PSS_ProcessGraphModelMdl.h"

// resources
#include "zFormsRes\zFormsRes.h"
#include "zModelRes.h"
#include "PSS_ResIDs.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
static CMenu g_ExtFilesMenu;
//---------------------------------------------------------------------------
// PSS_ExtFilePropertyMgr
//---------------------------------------------------------------------------
PSS_ExtFilePropertyMgr::PSS_ExtFilePropertyMgr()
{}
//---------------------------------------------------------------------------
PSS_ExtFilePropertyMgr::PSS_ExtFilePropertyMgr(const PSS_ExtFilePropertyMgr& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_ExtFilePropertyMgr::~PSS_ExtFilePropertyMgr()
{}
//---------------------------------------------------------------------------
PSS_ExtFilePropertyMgr& PSS_ExtFilePropertyMgr::operator = (const PSS_ExtFilePropertyMgr& other)
{
    m_ExternalFiles = other.m_ExternalFiles;
    return *this;
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::DoInsertExtFile(bool showDialog)
{
    // add a new external file
    const int index = AddNewExtFile();

    if (index >= 0)
    {
        if (showDialog)
        {
            // show the dialog
            PSS_ReferenceFileDialog refFileDlg(GetFileName(index), GetInsertionType(index), GetActivationType(index));

            if (refFileDlg.DoModal() == IDOK)
            {
                PSS_File file(refFileDlg.GetReference());

                if (file.Exist())
                    SetFileTitle(index, file.GetDisplayName());
                else
                    SetFileTitle(index, refFileDlg.GetReference());

                SetFileName      (index, refFileDlg.GetReference());
                SetInsertionType (index, refFileDlg.GetInsertionType());
                SetActivationType(index, refFileDlg.GetActivationType());
            }
        }

        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::AcceptDropItem(CObject* pObj, const CPoint& point)
{
    PSS_TemplateFile* pTemplateFile = dynamic_cast<PSS_TemplateFile*>(pObj);

    // accept the external file if is a scriptor template
    if (pTemplateFile)
        return true;

    PSS_NetResourceWrapper* pNetResources = dynamic_cast<PSS_NetResourceWrapper*>(pObj);

    // only accept file and URL drop
    if (pNetResources && !pNetResources->GetFileName().IsEmpty() && pNetResources->IsFile())
    {
        PSS_File      file(pNetResources->GetFileName());
        const CString ext = file.GetFileExt().MakeLower();

        // check the file type, don't allow executable files
        return (ext != _T(".exe") && ext != _T(".com") && ext != _T(".bat"));
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::DropItem(CObject* pObj, const CPoint& pt)
{
    PSS_TemplateFile* pTemplateFile = dynamic_cast<PSS_TemplateFile*>(pObj);

    if (pTemplateFile)
    {
        int index = LocateFirstEmptyExtFile();

        // check if an empty file is available, if yes, use it. Otherwise creates a new one
        if (index < 0)
        {
            index = AddNewExtFile();

            if (index < 0)
                return false;
        }

        // file is a scriptor template, add it
        SetFileTitle     (index, pTemplateFile->GetTitle());
        SetFileName      (index, pTemplateFile->GetFileName());
        SetInsertionType (index, 0);
        SetActivationType(index, 0);

        return true;
    }

    PSS_NetResourceWrapper* pNetResources = dynamic_cast<PSS_NetResourceWrapper*>(pObj);

    if (pNetResources && !pNetResources->GetFileName().IsEmpty() && pNetResources->IsFile())
    {
        int index = LocateFirstEmptyExtFile();

        // check if an empty file item is available, if yes, use it. Otherwise creates a new one
        if (index < 0)
        {
            index = AddNewExtFile();

            if (index < 0)
                return false;
        }

        // normal file, add it
        PSS_File file(pNetResources->GetFileName());

        if (file.Exist())
            SetFileTitle(index, file.GetDisplayName());
        else
            SetFileTitle(index, pNetResources->GetFileName());

        SetFileName      (index, pNetResources->GetFileName());
        SetInsertionType (index, 0);
        SetActivationType(index, 0);

        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::CreateSymbolProperties()
{
    // create the external files initial properties
    m_ExternalFiles.CreateInitialProperties();
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::FillProperties(ZBPropertySet& propSet, bool numericValue, bool groupValue)
{
    // if the menu isn't loaded, load it
    if (!g_ExtFilesMenu.GetSafeHmenu())
        g_ExtFilesMenu.LoadMenu(IDR_EXTFILES_MENU);

    CString propTitle;
    propTitle.LoadString(IDS_ZS_BP_PROP_EXTFILE_TITLE);

    CString           propName;
    CString           propDesc;
    CString           finalPropTitle;
    const std::size_t count = GetExtFileCount();

    // iterate through all properties
    for (std::size_t i = 0; i < count; ++i)
    {
        finalPropTitle.Format(_T("%s (%d)"), propTitle, i + 1);

        std::unique_ptr<ZBProperty> pProp;

        propName.LoadString(IDS_Z_FILE_TITLE_NAME);
        propDesc.LoadString(IDS_Z_FILE_TITLE_DESC);

        // link title property in the external link group
        pProp.reset(new ZBProperty(finalPropTitle,
                                   groupValue ? ZS_BP_PROP_EXTFILE : (ZS_BP_PROP_EXTFILE + i),
                                   propName,
                                   groupValue ? M_File_Title_ID : (M_File_Title_ID + (i * 40)),
                                   propDesc,
                                   GetFileTitle(i),
                                   ZBProperty::PT_EDIT_MENU,
                                   true,
                                   PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                   NULL,
                                   &g_ExtFilesMenu));

        propSet.Add(pProp.get());
        pProp.release();

        propName.LoadString(IDS_Z_FILE_NAME_NAME);
        propDesc.LoadString(IDS_Z_FILE_NAME_DESC);

        // link property in the external link group
        pProp.reset(new ZBProperty(finalPropTitle,
                                   groupValue ? ZS_BP_PROP_EXTFILE : (ZS_BP_PROP_EXTFILE + i),
                                   propName,
                                   groupValue ? M_File_Name_ID : (M_File_Name_ID + (i * 40)),
                                   propDesc,
                                   GetFileName(i),
                                   ZBProperty::PT_EDIT_EXTENDED));

        propSet.Add(pProp.get());
        pProp.release();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::FillPropertiesMessenger(ZBPropertySet& propSet, bool numericValue, bool groupValue)
{
    // if the menu isn't loaded, load it
    if (!g_ExtFilesMenu.GetSafeHmenu())
        g_ExtFilesMenu.LoadMenu(IDR_EXTFILES_MENU);

    CString propTitle;
    propTitle.LoadString(IDS_ZS_BP_PROP_EXTFILE_TITLE);

    CString           propName;
    CString           propDesc;
    CString           finalPropTitle;
    const std::size_t count = GetExtFileCount();

    // iterate through properties
    for (std::size_t i = 0; i < count; ++i)
    {
        finalPropTitle.Format(_T("%s (%d)"), propTitle, i + 1);

        std::unique_ptr<ZBProperty> pProp;

        propName.LoadString(IDS_Z_INSERTION_TYPE_NAME);
        propDesc.LoadString(IDS_Z_INSERTION_TYPE_DESC);

        // insertion mode property from the external link group
        if (numericValue)
            pProp.reset(new ZBProperty(finalPropTitle,
                                       groupValue ? ZS_BP_PROP_EXTFILE : (ZS_BP_PROP_EXTFILE + i),
                                       propName,
                                       groupValue ? M_Insertion_Type_ID : (M_Insertion_Type_ID + (i * 40)),
                                       propDesc,
                                       double(GetInsertionType(i)),
                                       ZBProperty::PT_EDIT_NUMBER));
        else
            pProp.reset(new ZBProperty(finalPropTitle,
                                       groupValue ? ZS_BP_PROP_EXTFILE : (ZS_BP_PROP_EXTFILE + i),
                                       propName,
                                       groupValue ? M_Insertion_Type_ID : (M_Insertion_Type_ID + (i * 40)),
                                       propDesc,
                                       PSS_Global::GetInsertionTypeString(GetInsertionType(i)),
                                       ZBProperty::PT_COMBO_STRING_READONLY,
                                       true,
                                       PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                       PSS_Global::GetArrayInsertionType()));

        propSet.Add(pProp.get());
        pProp.release();

        propName.LoadString(IDS_Z_ACTIVATION_TYPE_NAME);
        propDesc.LoadString(IDS_Z_ACTIVATION_TYPE_DESC);

        // activation mode property from the external link group
        if (numericValue)
            pProp.reset(new ZBProperty(finalPropTitle,
                                       groupValue ? ZS_BP_PROP_EXTFILE : (ZS_BP_PROP_EXTFILE + i),
                                       propName,
                                       groupValue ? M_Activation_Type_ID : (M_Activation_Type_ID + (i * 40)),
                                       propDesc,
                                       double(GetActivationType(i)),
                                       ZBProperty::PT_EDIT_NUMBER));
        else
            pProp.reset(new ZBProperty(finalPropTitle,
                                       groupValue ? ZS_BP_PROP_EXTFILE : (ZS_BP_PROP_EXTFILE + i),
                                       propName,
                                       groupValue ? M_Activation_Type_ID : (M_Activation_Type_ID + (i * 40)),
                                       propDesc,
                                       PSS_Global::GetActivationTypeString(GetActivationType(i)),
                                       ZBProperty::PT_COMBO_STRING_READONLY,
                                       true,
                                       PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                       PSS_Global::GetArrayActivationType()));

        propSet.Add(pProp.get());
        pProp.release();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::SaveProperties(ZBPropertySet& propSet)
{
    ZBPropertyIterator it(&propSet);

    // iterate through the data list and fill the external files property set
    for (ZBProperty* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() >=  ZS_BP_PROP_EXTFILE &&
            pProp->GetCategoryID() <= (ZS_BP_PROP_EXTFILE + int(GetExtFileCount())))
            SaveProperty(*pProp);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::FillProperty(ZBProperty& prop)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::SaveProperty(ZBProperty& prop)
{
    if (prop.GetCategoryID() >=  ZS_BP_PROP_EXTFILE &&
        prop.GetCategoryID() <= (ZS_BP_PROP_EXTFILE + int(GetExtFileCount())))
    {
        const int i = prop.GetCategoryID() - ZS_BP_PROP_EXTFILE;

        switch (prop.GetItemID() - (i * 40))
        {
            case M_File_Title_ID:      SetFileTitle     (i, prop.GetValueString());                                break;
            case M_File_Name_ID:       SetFileName      (i, prop.GetValueString());                                break;
            case M_Insertion_Type_ID:  SetInsertionType (i, PSS_Global::GetInsertionType(prop.GetValueString()));  break;
            case M_Activation_Type_ID: SetActivationType(i, PSS_Global::GetActivationType(prop.GetValueString())); break;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::CheckPropertyValue(ZBProperty& prop, CString& value, ZBPropertySet& props)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::ProcessExtendedInput(ZBProperty&    prop,
                                                  CString&       value,
                                                  ZBPropertySet& props,
                                                  bool&          refresh)
{
    if (prop.GetCategoryID() >=  ZS_BP_PROP_EXTFILE &&
        prop.GetCategoryID() <= (ZS_BP_PROP_EXTFILE + int(GetExtFileCount())))
    {
        const int i = prop.GetCategoryID() - ZS_BP_PROP_EXTFILE;

        // show the dialog
        PSS_ReferenceFileDialog refFileDlg(GetFileName(i), GetInsertionType(i), GetActivationType(i));

        if (refFileDlg.DoModal() == IDOK)
        {
            value = refFileDlg.GetReference();
            PSS_File file(refFileDlg.GetReference());

            if (file.Exist())
                SetFileTitle(i, file.GetDisplayName());
            else
                SetFileTitle(i, refFileDlg.GetReference());

            SetFileName      (i, refFileDlg.GetReference());
            SetInsertionType (i, refFileDlg.GetInsertionType());
            SetActivationType(i, refFileDlg.GetActivationType());

            refresh = true;
            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::ProcessMenuCommand(int            menuCommand,
                                                ZBProperty&    prop,
                                                CString&       value,
                                                ZBPropertySet& props,
                                                bool&          refresh)
{
    if (prop.GetCategoryID() >=  ZS_BP_PROP_EXTFILE &&
        prop.GetCategoryID() <= (ZS_BP_PROP_EXTFILE + int(GetExtFileCount())))
    {
        switch (menuCommand)
        {
            case ID_ADD_NEWEXTFILE:     OnAddNewExtFile    (prop, value, props, refresh); break;
            case ID_DEL_CURRENTEXTFILE: OnDelCurrentExtFile(prop, value, props, refresh); break;
            default:                                                                      break;
        }

        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_ExtFilePropertyMgr::Serialize(CArchive& ar)
{
    // remove all empty elements before storing them
    if (ar.IsStoring())
        RemoveAllEmptyExtFiles();

    m_ExternalFiles.Serialize(ar);
}
//---------------------------------------------------------------------------
void PSS_ExtFilePropertyMgr::OnAddNewExtFile(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh)
{
    refresh = DoInsertExtFile(false);

    if (refresh)
        value = GetFileTitle(GetExtFileCount() - 1);
}
//---------------------------------------------------------------------------
void PSS_ExtFilePropertyMgr::OnDelCurrentExtFile(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh)
{
    // delete the current selected external file
    const int index = prop.GetCategoryID() - ZS_BP_PROP_EXTFILE;

    if (DeleteExtFile(index))
        refresh = true;
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::OnPrePropertyChanged(const CString& newValue, ZBProperty& prop, ZBPropertySet& props)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::OnPostPropertyChanged(ZBProperty& prop, ZBPropertySet& props, bool& refresh)
{
    return false;
}
//---------------------------------------------------------------------------
