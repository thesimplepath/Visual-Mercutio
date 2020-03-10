/****************************************************************************
 * ==> PSS_ExtAppPropertyMgr -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an external application properties manager        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ExtAppPropertyMgr.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zBaseLib\PSS_Tokenizer.h"
#include "zBaseLib\PSS_NetResourceWrapper.h"
#include "zBaseLib\PSS_TemplateFile.h"
#include "zBaseLib\PSS_File.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zWinUtil32\PSS_CommandLineDialog.h"
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_Symbol.h"
#include "PSS_SystemEntity.h"
#include "PSS_LogicalSystemEntity.h"
#include "PSS_LogicalPrestationsEntity.h"

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
static CMenu g_ExtAppsMenu;
//---------------------------------------------------------------------------
// PSS_ExtAppPropertyMgr
//---------------------------------------------------------------------------
PSS_ExtAppPropertyMgr::PSS_ExtAppPropertyMgr(CODSymbolComponent* pSymbol) :
    m_pSymbol(pSymbol)
{}
//---------------------------------------------------------------------------
PSS_ExtAppPropertyMgr::PSS_ExtAppPropertyMgr(const PSS_ExtAppPropertyMgr& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_ExtAppPropertyMgr::~PSS_ExtAppPropertyMgr()
{}
//---------------------------------------------------------------------------
PSS_ExtAppPropertyMgr& PSS_ExtAppPropertyMgr::operator = (const PSS_ExtAppPropertyMgr& other)
{
    m_ExternalApplications = other.m_ExternalApplications;
    return *this;
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::DoInsertExtApp(bool showDialog)
{
    // add a new external application
    const int index = AddNewExtApp();

    if (index < 0)
        return false;

    if (showDialog)
    {
        // show the dialog
        PSS_CommandLineDialog dlg(GetCommandTitle           (index),
                                  GetCommandLine            (index),
                                  GetCommandParameters      (index),
                                  GetCommandStartupDirectory(index),
                                  GetPriorityLevel          (index),
                                  GetWindowStartMode        (index));

        if (dlg.DoModal() == IDOK)
        {
            SetCommandTitle           (index, dlg.GetJobName());
            SetCommandLine            (index, dlg.GetCommandLine());
            SetCommandParameters      (index, dlg.GetParameters());
            SetCommandStartupDirectory(index, dlg.GetStartupDir());
            SetPriorityLevel          (index, dlg.GetPriority());
            SetWindowStartMode        (index, dlg.GetWindowMode());
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::AcceptDropItem(CObject* pObj, const CPoint& point)
{
    PSS_SystemEntity* pSystemEntity = dynamic_cast<PSS_SystemEntity*>(pObj);

    if (pSystemEntity)
        return true;

    PSS_NetResourceWrapper* pNetResources = dynamic_cast<PSS_NetResourceWrapper*>(pObj);

    // accept drop only if item is an executable file
    if (pNetResources && !pNetResources->GetFileName().IsEmpty() && pNetResources->IsFile())
    {
        PSS_File      file(pNetResources->GetFileName());
        const CString ext = file.GetFileExt().MakeLower();

        // check the file type
        return (ext == _T(".exe") || ext == _T(".com") || ext == _T(".bat"));
    }
 
    return false;
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::DropItem(CObject* pObj, const CPoint& point)
{
    PSS_SystemEntity* pSystemEntity = dynamic_cast<PSS_SystemEntity*>(pObj);

    if (pSystemEntity)
    {
        PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(m_pSymbol);

        // check if the system file belongs to the model
        if (pSymbol)
        {
            PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetRootModel());

            if (pModel && !pModel->MainUserGroupIsValid())
            {
                PSS_MsgBox mBox;
                mBox.Show(IDS_CANNOTDROP_SYSTEMDEFNOTINLINE, MB_OK);
                return false;
            }
        }

        int index = LocateFirstEmptyExtApp();

        // check if an empty application item is available, if yes, use it. Otherwise creates a new one
        if (index < 0)
        {
            index = AddNewExtApp();

            if (index < 0)
                return false;
        }

        SetCommandTitle           (index, pSystemEntity->GetEntityName());
        SetCommandLine            (index, pSystemEntity->GetEntityName());
        SetCommandParameters      (index, g_LogicalSystemKey + pSystemEntity->GetGUID());
        SetCommandStartupDirectory(index, _T(""));
        SetPriorityLevel          (index, THREAD_PRIORITY_NORMAL);
        SetWindowStartMode        (index, SW_SHOWNORMAL);

        return true;
    }

    PSS_NetResourceWrapper* pNetResources = dynamic_cast<PSS_NetResourceWrapper*>(pObj);

    // accept drop only if item is an executable file
    if (pNetResources && !pNetResources->GetFileName().IsEmpty() && pNetResources->IsFile())
    {
        const CString fileName = pNetResources->GetFileName();
        PSS_File      file(fileName);

        int index = LocateFirstEmptyExtApp();

        // check if an empty application item is available, if yes, use it. Otherwise creates a new one
        if (index < 0)
        {
            index = AddNewExtApp();

            if (index < 0)
                return false;
        }

        if (file.Exist())
            SetCommandTitle(index, file.GetDisplayName());
        else
            SetCommandTitle(index, fileName);

        SetCommandLine            (index, fileName);
        SetCommandParameters      (index, _T(""));
        SetCommandStartupDirectory(index, file.GetFilePath());
        SetPriorityLevel          (index, THREAD_PRIORITY_NORMAL);
        SetWindowStartMode        (index, SW_SHOWNORMAL);

        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::CreateSymbolProperties()
{
    // create the external files and apps initial properties
    m_ExternalApplications.CreateInitialProperties();
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::FillProperties(ZBPropertySet& propSet, bool numericValue, bool groupValue)
{
    // if the menu isn't loaded, load it
    if (!g_ExtAppsMenu.GetSafeHmenu())
        g_ExtAppsMenu.LoadMenu(IDR_EXTAPPS_MENU);

    CString propTitle;
    propTitle.LoadString(IDS_ZS_BP_PROP_EXTAPP_TITLE);

    CString propName;
    propName.LoadString(IDS_Z_COMMAND_TITLE_NAME);

    CString propDesc;
    propDesc.LoadString(IDS_Z_COMMAND_TITLE_DESC);

    PSS_Symbol*       pSymbol         = dynamic_cast<PSS_Symbol*>(m_pSymbol);
    const std::size_t count           = GetExtAppCount();
    bool              systemIsEnabled = true;

    // iterate through all external application properties
    for (std::size_t i = 0; i < count; ++i)
    {
        CString finalPropTitle;
        finalPropTitle.Format(_T("%s (%d)"), propTitle, i + 1);

        CString commandTitle;
        CString commandLine;

        // check if a logical system was defined
        if (pSymbol && GetCommandParameters(i).Left(g_LogicalSystemKey.GetLength()) == g_LogicalSystemKey)
        {
            PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetRootModel());

            if (pModel && !pModel->MainUserGroupIsValid())
                systemIsEnabled = false;

            bool error;

            commandTitle = pSymbol->RetrieveLogicalSystemName(GetCommandParameters(i).Right
                                                                      (GetCommandParameters(i).GetLength() -
                                                                       g_LogicalSystemKey.GetLength()),
                                                              error);

            commandLine = commandTitle;
        }
        else
        {
            commandTitle = GetCommandTitle(i);
            commandLine  = GetCommandLine(i);
        }

        std::unique_ptr<PSS_Property> pExtApp
                (new PSS_Property(finalPropTitle,
                                  groupValue ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                  propName,
                                  groupValue ? M_Command_Title_ID : (M_Command_Title_ID + (i * 40)),
                                  propDesc,
                                  commandTitle,
                                  PSS_Property::IE_T_EditMenu,
                                  systemIsEnabled,
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                  NULL,
                                  &g_ExtAppsMenu));

        propSet.Add(pExtApp.get());
        pExtApp.release();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::FillPropertiesMessenger(ZBPropertySet& propSet, bool numericValue, bool groupValue)
{
    // if the menu isn't loaded, load it
    if (!g_ExtAppsMenu.GetSafeHmenu())
        g_ExtAppsMenu.LoadMenu(IDR_EXTAPPS_MENU);

    CString propTitle;
    propTitle.LoadString(IDS_ZS_BP_PROP_EXTAPP_TITLE);

    CString propName;
    CString propDesc;

    PSS_Symbol*       pSymbol         = dynamic_cast<PSS_Symbol*>(m_pSymbol);
    bool              systemIsEnabled = true;
    const std::size_t count           = GetExtAppCount();

    // iterate through all external application properties
    for (std::size_t i = 0; i < count; ++i)
    {
        CString finalPropTitle;
        finalPropTitle.Format(_T("%s (%d)"), propTitle, i + 1);

        CString commandTitle;
        CString commandLine;

        // check if a logical system was defined
        if (pSymbol && GetCommandParameters(i).Left(g_LogicalSystemKey.GetLength()) == g_LogicalSystemKey)
        {
            PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetRootModel());

            if (pModel && !pModel->MainUserGroupIsValid())
                systemIsEnabled = false;

            bool error;

            commandTitle = pSymbol->RetrieveLogicalSystemName(GetCommandParameters(i).Right
                                                                      (GetCommandParameters(i).GetLength() -
                                                                       g_LogicalSystemKey.GetLength()),
                                                              error);

            commandLine = commandTitle;
        }
        else
        {
            commandTitle = GetCommandTitle(i);
            commandLine  = GetCommandLine(i);
        }

        std::unique_ptr<PSS_Property> pExtApp;

        propName.LoadString(IDS_Z_COMMAND_LINE_NAME);
        propDesc.LoadString(IDS_Z_COMMAND_LINE_DESC);

        pExtApp.reset(new PSS_Property(finalPropTitle,
                                       groupValue ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                       propName,
                                       groupValue ? M_Command_Line_ID : (M_Command_Line_ID + (i * 40)),
                                       propDesc,
                                       commandLine,
                                       PSS_Property::IE_T_EditExtended,
                                       systemIsEnabled));

        propSet.Add(pExtApp.get());
        pExtApp.release();

        propName.LoadString(IDS_Z_COMMAND_PARAM_NAME);
        propDesc.LoadString(IDS_Z_COMMAND_PARAM_DESC);

        pExtApp.reset(new PSS_Property(finalPropTitle,
                                       groupValue ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                       propName,
                                       groupValue ? M_Command_Param_ID : (M_Command_Param_ID + (i * 40)),
                                       propDesc,
                                       GetCommandParameters(i),
                                       PSS_Property::IE_T_EditExtended,
                                       systemIsEnabled));

        propSet.Add(pExtApp.get());
        pExtApp.release();

        propName.LoadString(IDS_Z_COMMAND_STARTUPDIR_NAME);
        propDesc.LoadString(IDS_Z_COMMAND_STARTUPDIR_DESC);

        pExtApp.reset(new PSS_Property(finalPropTitle,
                                       groupValue ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                       propName,
                                       groupValue ? M_Command_StartupDir_ID : (M_Command_StartupDir_ID + (i * 40)),
                                       propDesc,
                                       GetCommandStartupDirectory(i),
                                       PSS_Property::IE_T_EditDirectory,
                                       systemIsEnabled));

        propSet.Add(pExtApp.get());
        pExtApp.release();

        propName.LoadString(IDS_Z_PRIORITY_LEVEL_NAME);
        propDesc.LoadString(IDS_Z_PRIORITY_LEVEL_DESC);

        if (numericValue)
            pExtApp.reset(new PSS_Property(finalPropTitle,
                                           groupValue ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                           propName,
                                           groupValue ? M_Priority_Level_ID : (M_Priority_Level_ID + (i * 40)),
                                           propDesc,
                                           double(GetPriorityLevel(i)),
                                           PSS_Property::IE_T_EditNumber,
                                           systemIsEnabled));
        else
            pExtApp.reset(new PSS_Property(finalPropTitle,
                                           groupValue ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                           propName,
                                           groupValue ? M_Priority_Level_ID : (M_Priority_Level_ID + (i * 40)),
                                           propDesc,
                                           PSS_Global::GetJobPriorityString(GetPriorityLevel(i)),
                                           PSS_Property::IE_T_ComboStringReadOnly,
                                           systemIsEnabled,
                                           PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                           PSS_Global::GetArrayJobPriority()));

        propSet.Add(pExtApp.get());
        pExtApp.release();

        propName.LoadString(IDS_Z_WINDOW_STARTMODE_NAME);
        propDesc.LoadString(IDS_Z_WINDOW_STARTMODE_DESC);

        if (numericValue)
            pExtApp.reset(new PSS_Property(finalPropTitle,
                                           groupValue ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                           propName,
                                           groupValue ? M_Window_StartMode_ID : (M_Window_StartMode_ID + (i * 40)),
                                           propDesc,
                                           double(GetWindowStartMode(i)),
                                           PSS_Property::IE_T_EditNumber,
                                           systemIsEnabled));
        else
            pExtApp.reset(new PSS_Property(finalPropTitle,
                                           groupValue ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                           propName,
                                           groupValue ? M_Window_StartMode_ID : (M_Window_StartMode_ID + (i * 40)),
                                           propDesc,
                                           PSS_Global::GetWindowModeString(GetWindowStartMode(i)),
                                           PSS_Property::IE_T_ComboStringReadOnly,
                                           systemIsEnabled,
                                           PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                           PSS_Global::GetArrayWindowMode()));

        propSet.Add(pExtApp.get());
        pExtApp.release();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::SaveProperties(ZBPropertySet& propSet)
{
    ZBPropertyIterator it(&propSet);

    // iterate through the data list and fill the external files property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() >= ZS_BP_PROP_EXTAPP &&
            pProp->GetCategoryID() <= (ZS_BP_PROP_EXTAPP + int(GetExtAppCount())))
            SaveProperty(*pProp);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::FillProperty(PSS_Property& prop)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::SaveProperty(PSS_Property& prop)
{
    if (prop.GetCategoryID() >= ZS_BP_PROP_EXTAPP &&
        prop.GetCategoryID() <= (ZS_BP_PROP_EXTAPP + int(GetExtAppCount())))
    {
        const int i = prop.GetCategoryID() - ZS_BP_PROP_EXTAPP;

        switch (prop.GetItemID() - (i * 40))
        {
            case M_Command_Title_ID:      SetCommandTitle(i, prop.GetValueString());                               break;
            case M_Command_Line_ID:       SetCommandLine(i, prop.GetValueString());                                break;
            case M_Command_Param_ID:      SetCommandParameters(i, prop.GetValueString());                          break;
            case M_Command_StartupDir_ID: SetCommandStartupDirectory(i, prop.GetValueString());                    break;
            case M_Priority_Level_ID:     SetPriorityLevel(i, PSS_Global::GetJobPriority(prop.GetValueString()));  break;
            case M_Window_StartMode_ID:   SetWindowStartMode(i, PSS_Global::GetWindowMode(prop.GetValueString())); break;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::CheckPropertyValue(PSS_Property& prop, CString& value, ZBPropertySet& props)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::ProcessExtendedInput(PSS_Property&  prop,
                                                 CString&       value,
                                                 ZBPropertySet& props,
                                                 bool&          refresh)
{
    if (prop.GetCategoryID() >= ZS_BP_PROP_EXTAPP &&
        prop.GetCategoryID() <= (ZS_BP_PROP_EXTAPP + int(GetExtAppCount())))
    {
        const int index = prop.GetCategoryID() - ZS_BP_PROP_EXTAPP;

        // show the dialog
        PSS_CommandLineDialog dlg(GetCommandTitle           (index),
                                  GetCommandLine            (index),
                                  GetCommandParameters      (index),
                                  GetCommandStartupDirectory(index),
                                  GetPriorityLevel          (index),
                                  GetWindowStartMode        (index));

        if (dlg.DoModal() == IDOK)
        {
            value = dlg.GetJobName();
            SetCommandLine            (index, dlg.GetCommandLine());
            SetCommandParameters      (index, dlg.GetParameters());
            SetCommandStartupDirectory(index, dlg.GetStartupDir());
            SetPriorityLevel          (index, dlg.GetPriority());
            SetWindowStartMode        (index, dlg.GetWindowMode());

            refresh = true;
            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::ProcessMenuCommand(int            menuCmdID,
                                               PSS_Property&  prop,
                                               CString&       value,
                                               ZBPropertySet& props,
                                               bool&          refresh)
{
    if (prop.GetCategoryID() >= ZS_BP_PROP_EXTAPP &&
        prop.GetCategoryID() <= (ZS_BP_PROP_EXTAPP + int(GetExtAppCount())))
    {
        switch (menuCmdID)
        {
            case ID_ADD_NEWEXTAPP:     OnAddNewExtApp    (prop, value, props, refresh); break;
            case ID_DEL_CURRENTEXTAPP: OnDelCurrentExtApp(prop, value, props, refresh); break;
            default:                                                                    break;
        }

        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_ExtAppPropertyMgr::Serialize(CArchive& ar)
{
    // before storing elements, remove all the empty ones
    if (ar.IsStoring())
        RemoveAllEmptyExtApps();

    m_ExternalApplications.Serialize(ar);
}
//---------------------------------------------------------------------------
void PSS_ExtAppPropertyMgr::OnAddNewExtApp(PSS_Property& prop, CString& value, ZBPropertySet& props, bool& refresh)
{
    refresh = DoInsertExtApp(false);

    if (refresh)
        value = GetCommandTitle(GetExtAppCount() - 1);
}
//---------------------------------------------------------------------------
void PSS_ExtAppPropertyMgr::OnDelCurrentExtApp(PSS_Property& prop, CString& value, ZBPropertySet& props, bool& refresh)
{
    // delete the current selected external application
    const int index = prop.GetCategoryID() - ZS_BP_PROP_EXTAPP;

    if (DeleteExtApp(index))
        refresh = true;
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::OnPrePropertyChanged(const CString& newValue, PSS_Property& prop, ZBPropertySet& props)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::OnPostPropertyChanged(PSS_Property& prop, ZBPropertySet& props, bool& refresh)
{
    return false;
}
//---------------------------------------------------------------------------
