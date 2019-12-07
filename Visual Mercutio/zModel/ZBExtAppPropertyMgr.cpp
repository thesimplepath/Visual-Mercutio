// ZBExtAppPropertyMgr.cpp: implementation of the ZBExtAppPropertyMgr class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBExtAppPropertyMgr.h"

#include "PSS_ProcessGraphModelMdl.h"
#include "ZBSymbol.h"

#include "zWinUtil32\PSS_CommandLineDialog.h"

#include "zBaseLib\PSS_Global.h"
#include "zBaseLib\PSS_Tokenizer.h"

#include "zBaseLib\PSS_NetResourceWrapper.h"
#include "zBaseLib\PSS_TemplateFile.h"
#include "zBaseLib\PSS_File.h"

#include "zBaseLib\PSS_MsgBox.h"

#include "ZBSystemEntity.h"
#include "ZBLogicalSystemEntity.h"

#include "ZBLogicalPrestationsEntity.h"

#include "zModelRes.h"
#include "PSS_ResIDs.h"
#include "zFormsRes\zFormsRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 13 octobre - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Static variables
static CMenu gExtAppsMenu;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBExtAppPropertyMgr::ZBExtAppPropertyMgr(CODSymbolComponent* pSymbol /*= NULL*/)
    : m_pSymbol(pSymbol)
{}

ZBExtAppPropertyMgr::~ZBExtAppPropertyMgr()
{}

ZBExtAppPropertyMgr::ZBExtAppPropertyMgr(const ZBExtAppPropertyMgr& src)
{
    *this = src;
}

ZBExtAppPropertyMgr& ZBExtAppPropertyMgr::operator=(const ZBExtAppPropertyMgr& src)
{
    m_ExternalApplications = src.m_ExternalApplications;
    return *this;
}

bool ZBExtAppPropertyMgr::CreateSymbolProperties()
{
    // Creates the initial properties for extfiles and extapps
    m_ExternalApplications.CreateInitialProperties();
    return true;
};

bool ZBExtAppPropertyMgr::FillProperties(ZBPropertySet&    PropSet,
                                         bool                NumericValue    /*= false*/,
                                         bool                GroupValue        /*= false*/)
{
    // If the menu is not loaded, load it
    if (gExtAppsMenu.GetSafeHmenu() == NULL)
    {
        gExtAppsMenu.LoadMenu(IDR_EXTAPPS_MENU);
    }

    // Run through all external applications properties
    CString FinalPropTitle;
    CString PropTitle;
    CString PropName;
    CString PropDesc;

    size_t Count = GetExtAppCount();
    PropTitle.LoadString(IDS_ZS_BP_PROP_EXTAPP_TITLE);
    bool SystemIsEnabled = true;

    for (size_t i = 0; i < Count; ++i)
    {
        FinalPropTitle.Format(_T("%s (%d)"), PropTitle, i + 1);

        PropName.LoadString(IDS_Z_COMMAND_TITLE_NAME);
        PropDesc.LoadString(IDS_Z_COMMAND_TITLE_DESC);

        CString CommandTitle;
        CString CommandLine;

        // Check if we have a logical system defined
        if (m_pSymbol && ISA(m_pSymbol, ZBSymbol) &&
            GetCommandParameters(i).Left(gLogicalSystemKey.GetLength()) == gLogicalSystemKey)
        {
            // Check if system file is inline with the modèle
            if (m_pSymbol && ISA(m_pSymbol, ZBSymbol))
            {
                CODModel * pModel = dynamic_cast<ZBSymbol*>(m_pSymbol)->GetRootModel();

                if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
                    !dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->MainUserGroupIsValid())
                {
                    SystemIsEnabled = false;
                }
            }

            bool Error;

            CommandTitle =
                dynamic_cast<ZBSymbol*>(m_pSymbol)->RetrieveLogicalSystemName(GetCommandParameters(i).Right(GetCommandParameters(i).GetLength() - gLogicalSystemKey.GetLength()),
                                                                              Error);

            CommandLine = CommandTitle;
        }
        else
        {
            CommandTitle = GetCommandTitle(i);
            CommandLine = GetCommandLine(i);
        }

        ZBProperty* pExtApp;

        pExtApp = new ZBProperty(FinalPropTitle,
            (GroupValue == true) ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                 PropName,
                                 (GroupValue == true) ? Z_COMMAND_TITLE : (Z_COMMAND_TITLE + (i * 40)),
                                 PropDesc,
                                 CommandTitle,
                                 ZBProperty::PT_EDIT_MENU,
                                 SystemIsEnabled,
                                 PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                 NULL,
                                 &gExtAppsMenu);

        PropSet.Add(pExtApp);

        // RS-MODIF 20.12.04 only loaded if messenger enabled (see function below)
        /*

        PropName.LoadString( IDS_Z_COMMAND_LINE_NAME );
        PropDesc.LoadString( IDS_Z_COMMAND_LINE_DESC );

        pExtApp = new ZBProperty( FinalPropTitle,
                                  ( GroupValue == true ) ? ZS_BP_PROP_EXTAPP : ( ZS_BP_PROP_EXTAPP + i ),
                                  PropName,
                                  ( GroupValue == true ) ? Z_COMMAND_LINE : ( Z_COMMAND_LINE + ( i * 40 ) ),
                                  PropDesc,
                                  CommandLine,
                                  ZBProperty::PT_EDIT_EXTENDED,
                                  SystemIsEnabled );

        PropSet.Add( pExtApp );

        PropName.LoadString( IDS_Z_COMMAND_PARAM_NAME );
        PropDesc.LoadString( IDS_Z_COMMAND_PARAM_DESC );

        pExtApp = new ZBProperty( FinalPropTitle,
                                  ( GroupValue == true ) ? ZS_BP_PROP_EXTAPP : ( ZS_BP_PROP_EXTAPP + i ),
                                  PropName,
                                  ( GroupValue == true ) ? Z_COMMAND_PARAM : ( Z_COMMAND_PARAM + ( i * 40 ) ),
                                  PropDesc,
                                  GetCommandParameters( i ),
                                  ZBProperty::PT_EDIT_EXTENDED,
                                  SystemIsEnabled );

        PropSet.Add( pExtApp );

        // RS-MODIF 11.12.04 only loaded if messenger enabled (see function below)
        /*
        PropName.LoadString( IDS_Z_COMMAND_STARTUPDIR_NAME );
        PropDesc.LoadString( IDS_Z_COMMAND_STARTUPDIR_DESC );

        pExtApp = new ZBProperty( FinalPropTitle,
                                  ( GroupValue == true ) ? ZS_BP_PROP_EXTAPP : ( ZS_BP_PROP_EXTAPP + i ),
                                  PropName,
                                  ( GroupValue == true ) ? Z_COMMAND_STARTUPDIR : ( Z_COMMAND_STARTUPDIR + ( i * 40 ) ),
                                  PropDesc,
                                  GetCommandStartupDirectory( i ),
                                  ZBProperty::PT_EDIT_DIRECTORY,
                                  SystemIsEnabled );

        PropSet.Add( pExtApp );

        PropName.LoadString( IDS_Z_PRIORITY_LEVEL_NAME );
        PropDesc.LoadString( IDS_Z_PRIORITY_LEVEL_DESC );

        if (NumericValue)
        {
            pExtApp = new ZBProperty( FinalPropTitle,
                                      ( GroupValue == true ) ? ZS_BP_PROP_EXTAPP : ( ZS_BP_PROP_EXTAPP + i ),
                                      PropName,
                                      ( GroupValue == true ) ? Z_PRIORITY_LEVEL : ( Z_PRIORITY_LEVEL + ( i * 40 ) ),
                                      PropDesc,
                                      (double)GetPriorityLevel( i ),
                                      ZBProperty::PT_EDIT_NUMBER,
                                      SystemIsEnabled );
        }
        else
        {
            pExtApp = new ZBProperty( FinalPropTitle,
                                      ( GroupValue == true ) ? ZS_BP_PROP_EXTAPP : ( ZS_BP_PROP_EXTAPP + i ),
                                      PropName,
                                      ( GroupValue == true ) ? Z_PRIORITY_LEVEL : ( Z_PRIORITY_LEVEL + ( i * 40 ) ),
                                      PropDesc,
                                      ZAGlobal::GetJobPriorityString( GetPriorityLevel( i ) ),
                                      ZBProperty::PT_COMBO_STRING_READONLY,
                                      SystemIsEnabled,
                                      ZBStringFormat( ZBStringFormat::General ),
                                      ZAGlobal::GetArrayJobPriority() );
        }

        PropSet.Add( pExtApp );

        PropName.LoadString( IDS_Z_WINDOW_STARTMODE_NAME );
        PropDesc.LoadString( IDS_Z_WINDOW_STARTMODE_DESC );

        if ( NumericValue )
        {
            pExtApp = new ZBProperty( FinalPropTitle,
                                      ( GroupValue == true ) ? ZS_BP_PROP_EXTAPP : ( ZS_BP_PROP_EXTAPP + i ),
                                      PropName,
                                      ( GroupValue == true ) ? Z_WINDOW_STARTMODE : ( Z_WINDOW_STARTMODE + ( i * 40 ) ),
                                      PropDesc,
                                      (double)GetWindowStartMode( i ),
                                      ZBProperty::PT_EDIT_NUMBER,
                                      SystemIsEnabled );
        }
        else
        {
            pExtApp = new ZBProperty( FinalPropTitle,
                                      ( GroupValue == true ) ? ZS_BP_PROP_EXTAPP : ( ZS_BP_PROP_EXTAPP + i ),
                                      PropName,
                                      ( GroupValue == true ) ? Z_WINDOW_STARTMODE : ( Z_WINDOW_STARTMODE + ( i * 40 ) ),
                                      PropDesc,
                                      ZAGlobal::GetWindowModeString( GetWindowStartMode( i ) ),
                                      ZBProperty::PT_COMBO_STRING_READONLY,
                                      SystemIsEnabled,
                                      ZBStringFormat( ZBStringFormat::General ),
                                      ZAGlobal::GetArrayWindowMode() );

        PropSet.Add( pExtApp );
        */
    }

    return true;
}

// RS-MODIF 11.12.04 for segregation conceptor, this part only fills messenger properties
bool ZBExtAppPropertyMgr::FillPropertiesMessenger(ZBPropertySet&    PropSet,
                                                  bool                NumericValue    /*= false*/,
                                                  bool                GroupValue        /*= false*/)
{
    // If the menu is not loaded, load it
    if (gExtAppsMenu.GetSafeHmenu() == NULL)
    {
        gExtAppsMenu.LoadMenu(IDR_EXTAPPS_MENU);
    }

    // Run through all external applications properties
    CString FinalPropTitle;
    CString PropTitle;
    CString PropName;
    CString PropDesc;

    size_t Count = GetExtAppCount();
    PropTitle.LoadString(IDS_ZS_BP_PROP_EXTAPP_TITLE);
    bool SystemIsEnabled = true;

    for (size_t i = 0; i < Count; ++i)
    {
        FinalPropTitle.Format(_T("%s (%d)"), PropTitle, i + 1);

        PropName.LoadString(IDS_Z_COMMAND_TITLE_NAME);
        PropDesc.LoadString(IDS_Z_COMMAND_TITLE_DESC);

        CString CommandTitle;
        CString CommandLine;

        // Check if we have a logical system defined
        if (m_pSymbol && ISA(m_pSymbol, ZBSymbol) &&
            GetCommandParameters(i).Left(gLogicalSystemKey.GetLength()) == gLogicalSystemKey)
        {
            // Check if system file is inline with the modèle
            if (m_pSymbol && ISA(m_pSymbol, ZBSymbol))
            {
                CODModel * pModel = dynamic_cast<ZBSymbol*>(m_pSymbol)->GetRootModel();

                if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
                    !dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->MainUserGroupIsValid())
                {
                    SystemIsEnabled = false;
                }
            }

            bool Error;

            CommandTitle =
                dynamic_cast<ZBSymbol*>(m_pSymbol)->RetrieveLogicalSystemName(GetCommandParameters(i).Right(GetCommandParameters(i).GetLength() - gLogicalSystemKey.GetLength()),
                                                                              Error);

            CommandLine = CommandTitle;
        }
        else
        {
            CommandTitle = GetCommandTitle(i);
            CommandLine = GetCommandLine(i);
        }

        ZBProperty* pExtApp;

        PropName.LoadString(IDS_Z_COMMAND_LINE_NAME);
        PropDesc.LoadString(IDS_Z_COMMAND_LINE_DESC);

        pExtApp = new ZBProperty(FinalPropTitle,
            (GroupValue == true) ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                 PropName,
                                 (GroupValue == true) ? Z_COMMAND_LINE : (Z_COMMAND_LINE + (i * 40)),
                                 PropDesc,
                                 CommandLine,
                                 ZBProperty::PT_EDIT_EXTENDED,
                                 SystemIsEnabled);

        PropSet.Add(pExtApp);

        PropName.LoadString(IDS_Z_COMMAND_PARAM_NAME);
        PropDesc.LoadString(IDS_Z_COMMAND_PARAM_DESC);

        pExtApp = new ZBProperty(FinalPropTitle,
            (GroupValue == true) ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                 PropName,
                                 (GroupValue == true) ? Z_COMMAND_PARAM : (Z_COMMAND_PARAM + (i * 40)),
                                 PropDesc,
                                 GetCommandParameters(i),
                                 ZBProperty::PT_EDIT_EXTENDED,
                                 SystemIsEnabled);

        PropSet.Add(pExtApp);

        PropName.LoadString(IDS_Z_COMMAND_STARTUPDIR_NAME);
        PropDesc.LoadString(IDS_Z_COMMAND_STARTUPDIR_DESC);

        pExtApp = new ZBProperty(FinalPropTitle,
            (GroupValue == true) ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                 PropName,
                                 (GroupValue == true) ? Z_COMMAND_STARTUPDIR : (Z_COMMAND_STARTUPDIR + (i * 40)),
                                 PropDesc,
                                 GetCommandStartupDirectory(i),
                                 ZBProperty::PT_EDIT_DIRECTORY,
                                 SystemIsEnabled);

        PropSet.Add(pExtApp);

        PropName.LoadString(IDS_Z_PRIORITY_LEVEL_NAME);
        PropDesc.LoadString(IDS_Z_PRIORITY_LEVEL_DESC);

        if (NumericValue)
        {
            pExtApp = new ZBProperty(FinalPropTitle,
                (GroupValue == true) ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                     PropName,
                                     (GroupValue == true) ? Z_PRIORITY_LEVEL : (Z_PRIORITY_LEVEL + (i * 40)),
                                     PropDesc,
                                     (double)GetPriorityLevel(i),
                                     ZBProperty::PT_EDIT_NUMBER,
                                     SystemIsEnabled);
        }
        else
        {
            pExtApp = new ZBProperty(FinalPropTitle,
                (GroupValue == true) ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                     PropName,
                                     (GroupValue == true) ? Z_PRIORITY_LEVEL : (Z_PRIORITY_LEVEL + (i * 40)),
                                     PropDesc,
                                     PSS_Global::GetJobPriorityString(GetPriorityLevel(i)),
                                     ZBProperty::PT_COMBO_STRING_READONLY,
                                     SystemIsEnabled,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayJobPriority());
        }

        PropSet.Add(pExtApp);

        PropName.LoadString(IDS_Z_WINDOW_STARTMODE_NAME);
        PropDesc.LoadString(IDS_Z_WINDOW_STARTMODE_DESC);

        if (NumericValue)
        {
            pExtApp = new ZBProperty(FinalPropTitle,
                (GroupValue == true) ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                     PropName,
                                     (GroupValue == true) ? Z_WINDOW_STARTMODE : (Z_WINDOW_STARTMODE + (i * 40)),
                                     PropDesc,
                                     (double)GetWindowStartMode(i),
                                     ZBProperty::PT_EDIT_NUMBER,
                                     SystemIsEnabled);
        }
        else
        {
            pExtApp = new ZBProperty(FinalPropTitle,
                (GroupValue == true) ? ZS_BP_PROP_EXTAPP : (ZS_BP_PROP_EXTAPP + i),
                                     PropName,
                                     (GroupValue == true) ? Z_WINDOW_STARTMODE : (Z_WINDOW_STARTMODE + (i * 40)),
                                     PropDesc,
                                     PSS_Global::GetWindowModeString(GetWindowStartMode(i)),
                                     ZBProperty::PT_COMBO_STRING_READONLY,
                                     SystemIsEnabled,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayWindowMode());
        }

        PropSet.Add(pExtApp);
    }

    return true;
}

bool ZBExtAppPropertyMgr::SaveProperties(ZBPropertySet& PropSet)
{
    // Now run through the list of data and fill the property set of external files
    ZBPropertyIterator i(&PropSet);
    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        if (pProp->GetCategoryID() >= ZS_BP_PROP_EXTAPP &&
            pProp->GetCategoryID() <= (ZS_BP_PROP_EXTAPP + (int)GetExtAppCount()))
        {
            SaveProperty(*pProp);
        }
    }

    return true;
}

bool ZBExtAppPropertyMgr::SaveProperty(ZBProperty& Property)
{
    if (Property.GetCategoryID() >= ZS_BP_PROP_EXTAPP &&
        Property.GetCategoryID() <= (ZS_BP_PROP_EXTAPP + (int)GetExtAppCount()))
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_EXTAPP;

        switch (Property.GetItemID() - (i * 40))
        {
            case Z_COMMAND_TITLE:
            {
                SetCommandTitle(i, Property.GetValueString());
                break;
            }

            case Z_COMMAND_LINE:
            {
                SetCommandLine(i, Property.GetValueString());
                break;
            }

            case Z_COMMAND_PARAM:
            {
                SetCommandParameters(i, Property.GetValueString());
                break;
            }

            case Z_COMMAND_STARTUPDIR:
            {
                SetCommandStartupDirectory(i, Property.GetValueString());
                break;
            }

            case Z_PRIORITY_LEVEL:
            {
                SetPriorityLevel(i, PSS_Global::GetJobPriority(Property.GetValueString()));
                break;
            }

            case Z_WINDOW_STARTMODE:
            {
                SetWindowStartMode(i, PSS_Global::GetWindowMode(Property.GetValueString()));
                break;
            }
        }
    }

    return true;
}

bool ZBExtAppPropertyMgr::ProcessExtendedInput(ZBProperty&    prop,
                                               CString&       value,
                                               ZBPropertySet& props,
                                               bool&          refresh)
{
    if (prop.GetCategoryID() >= ZS_BP_PROP_EXTAPP &&
        prop.GetCategoryID() <= (ZS_BP_PROP_EXTAPP + int(GetExtAppCount())))
    {
        const int index = prop.GetCategoryID() - ZS_BP_PROP_EXTAPP;

        // Call the dialog
        PSS_CommandLineDialog dlg(GetCommandTitle(index),
                                  GetCommandLine(index),
                                  GetCommandParameters(index),
                                  GetCommandStartupDirectory(index),
                                  GetPriorityLevel(index),
                                  GetWindowStartMode(index));

        if (dlg.DoModal() == IDOK)
        {
            value = dlg.GetJobName();
            SetCommandLine(index, dlg.GetCommandLine());
            SetCommandParameters(index, dlg.GetParameters());
            SetCommandStartupDirectory(index, dlg.GetStartupDir());
            SetPriorityLevel(index, dlg.GetPriority());
            SetWindowStartMode(index, dlg.GetWindowMode());

            refresh = true;
            return true;
        }
    }

    return false;
}

bool ZBExtAppPropertyMgr::ProcessMenuCommand(int                MenuCommand,
                                             ZBProperty&        Property,
                                             CString&            value,
                                             ZBPropertySet&    Properties,
                                             bool&                Refresh)
{
    if (Property.GetCategoryID() >= ZS_BP_PROP_EXTAPP &&
        Property.GetCategoryID() <= (ZS_BP_PROP_EXTAPP + (int)GetExtAppCount()))
    {
        switch (MenuCommand)
        {
            case ID_ADD_NEWEXTAPP:
            {
                OnAddNewExtApp(Property, value, Properties, Refresh);
                break;
            }

            case ID_DEL_CURRENTEXTAPP:
            {
                OnDelCurrentExtApp(Property, value, Properties, Refresh);
                break;
            }

            default:
            {
                break;
            }
        }

        return true;
    }

    return false;
}

bool ZBExtAppPropertyMgr::DoInsertExtApp(bool displayDialog)
{
    const int index = AddNewExtApp();

    // add a new external application
    if (index >= 0)
    {
        if (displayDialog)
        {
            // Call the dialog
            PSS_CommandLineDialog dlg(GetCommandTitle(index),
                                      GetCommandLine(index),
                                      GetCommandParameters(index),
                                      GetCommandStartupDirectory(index),
                                      GetPriorityLevel(index),
                                      GetWindowStartMode(index));

            if (dlg.DoModal() == IDOK)
            {
                SetCommandTitle(index, dlg.GetJobName());
                SetCommandLine(index, dlg.GetCommandLine());
                SetCommandParameters(index, dlg.GetParameters());
                SetCommandStartupDirectory(index, dlg.GetStartupDir());
                SetPriorityLevel(index, dlg.GetPriority());
                SetWindowStartMode(index, dlg.GetWindowMode());
            }
        }

        return true;
    }

    return false;
}

// Drag and drop methods
bool ZBExtAppPropertyMgr::AcceptDropItem(CObject* pObj, const CPoint& pt)
{
    // Accept drop of file executable only
    if (pObj && (ISA(pObj, PSS_NetResourceWrapper) &&
                 !((PSS_NetResourceWrapper*)pObj)->GetFileName().IsEmpty() && ((PSS_NetResourceWrapper*)pObj)->IsFile()) ||
        ISA(pObj, ZBSystemEntity))        // If a system entity
    {
        // If it is a file, check what kind of file
        if (ISA(pObj, PSS_NetResourceWrapper))
        {
            PSS_File file(((PSS_NetResourceWrapper*)pObj)->GetFileName());

            if ((file.GetFileExt().CompareNoCase(_T(".exe")) == 0 ||
                 file.GetFileExt().CompareNoCase(_T(".com")) == 0 ||
                 file.GetFileExt().CompareNoCase(_T(".bat")) == 0))
            {
                return true;
            }
        }
        // If it is a system entity
        else if (ISA(pObj, ZBSystemEntity))
        {
            return true;
        }
    }

    return false;
}

bool ZBExtAppPropertyMgr::DropItem(CObject* pObj, const CPoint& pt)
{
    // Accept drop of file executable only
    if (pObj && (ISA(pObj, PSS_NetResourceWrapper) &&
                 !((PSS_NetResourceWrapper*)pObj)->GetFileName().IsEmpty() && ((PSS_NetResourceWrapper*)pObj)->IsFile()) ||
        ISA(pObj, ZBSystemEntity))        // If a system entity
    {
        // If it is a file, check what kind of file
        if (ISA(pObj, PSS_NetResourceWrapper))
        {
            PSS_File file(((PSS_NetResourceWrapper*)pObj)->GetFileName());

            // Add a new external application
            // First, check if there is an empty one.
            // If there is, use it
            int Idx = LocateFirstEmptyExtApp();

            if (Idx == -1)
            {
                Idx = AddNewExtApp();
            }

            if (Idx >= 0)
            {
                if (file.Exist())
                {
                    SetCommandTitle(Idx, file.GetDisplayName());
                }
                else
                {
                    SetCommandTitle(Idx, ((PSS_NetResourceWrapper*)pObj)->GetFileName());
                }

                SetCommandLine(Idx, ((PSS_NetResourceWrapper*)pObj)->GetFileName());
                SetCommandParameters(Idx, _T(""));
                SetCommandStartupDirectory(Idx, file.GetFilePath());
                SetPriorityLevel(Idx, THREAD_PRIORITY_NORMAL);
                SetWindowStartMode(Idx, SW_SHOWNORMAL);

                return true;
            }
        }
        // If it is a system entity
        else if (ISA(pObj, ZBSystemEntity))
        {
            // Check if system file is inline with the modèle
            if (m_pSymbol && ISA(m_pSymbol, ZBSymbol))
            {
                CODModel* pModel = dynamic_cast<ZBSymbol*>(m_pSymbol)->GetRootModel();

                if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
                    !dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->MainUserGroupIsValid())
                {
                    // Cannot delete all combinations
                    PSS_MsgBox mBox;
                    mBox.Show(IDS_CANNOTDROP_SYSTEMDEFNOTINLINE, MB_OK);
                    return false;
                }
            }

            // Add a new external application
            // First, check if there is an empty one.
            // If there is, use it
            int Idx = LocateFirstEmptyExtApp();

            if (Idx == -1)
            {
                Idx = AddNewExtApp();
            }

            if (Idx >= 0)
            {
                SetCommandTitle(Idx, dynamic_cast<ZBSystemEntity*>(pObj)->GetEntityName());
                SetCommandLine(Idx, dynamic_cast<ZBSystemEntity*>(pObj)->GetEntityName());

                // Put the guid in parameters
                SetCommandParameters(Idx, gLogicalSystemKey + dynamic_cast<ZBSystemEntity*>(pObj)->GetGUID());
                SetCommandStartupDirectory(Idx, _T(""));
                SetPriorityLevel(Idx, THREAD_PRIORITY_NORMAL);
                SetWindowStartMode(Idx, SW_SHOWNORMAL);

                return true;
            }
        }
    }

    return false;
}

void ZBExtAppPropertyMgr::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // Before storing elements, removes all empty elements
        RemoveAllEmptyExtApps();
    }

    m_ExternalApplications.Serialize(ar);
}
