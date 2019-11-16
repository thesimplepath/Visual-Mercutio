// ZBExtFilePropertyMgr.cpp: implementation of the ZBExtFilePropertyMgr class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBExtFilePropertyMgr.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zBaseLib\PSS_Tokenizer.h"
#include "zBaseLib\PSS_NetResourceWrapper.h"
#include "zBaseLib\PSS_TemplateFile.h"
#include "zBaseLib\PSS_File.h"
#include "zWinUtil32\PSS_ReferenceFileDialog.h"
#include "ProcGraphModelMdl.h"

// resources
#include "zFormsRes\zFormsRes.h"
#include "zModelRes.h"
#include "PSS_ResIDs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 12 juin 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Static variables
static CMenu gExtFilesMenu;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBExtFilePropertyMgr::ZBExtFilePropertyMgr()
{}

ZBExtFilePropertyMgr::~ZBExtFilePropertyMgr()
{}

ZBExtFilePropertyMgr::ZBExtFilePropertyMgr(const ZBExtFilePropertyMgr& src)
{
    *this = src;
}

ZBExtFilePropertyMgr& ZBExtFilePropertyMgr::operator=(const ZBExtFilePropertyMgr& src)
{
    m_ExternalFiles = src.m_ExternalFiles;
    return *this;
}

bool ZBExtFilePropertyMgr::FillProperties(ZBPropertySet&    PropSet,
                                          bool                NumericValue    /*= false*/,
                                          bool                GroupValue        /*= false*/)
{
    // If the menu is not loaded, load it
    if (gExtFilesMenu.GetSafeHmenu() == NULL)
    {
        gExtFilesMenu.LoadMenu(IDR_EXTFILES_MENU);
    }

    // Run through all combination properties
    CString    FinalPropTitle;
    CString    PropTitle;
    CString    PropName;
    CString    PropDesc;
    size_t    Count = GetExtFileCount();

    PropTitle.LoadString(IDS_ZS_BP_PROP_EXTFILE_TITLE);

    for (size_t i = 0; i < Count; ++i)
    {
        FinalPropTitle.Format(_T("%s (%d)"), PropTitle, i + 1);

        PropName.LoadString(IDS_Z_FILE_TITLE_NAME);
        PropDesc.LoadString(IDS_Z_FILE_TITLE_DESC);

        // Propriété "Titre lien" du groupe "Lien externe"
        ZBProperty* pCombination = new ZBProperty(FinalPropTitle,
            (GroupValue == true) ? ZS_BP_PROP_EXTFILE : (ZS_BP_PROP_EXTFILE + i),
                                                  PropName,
                                                  (GroupValue == true) ? Z_FILE_TITLE : (Z_FILE_TITLE + (i * 40)),
                                                  PropDesc,
                                                  GetFileTitle(i),
                                                  ZBProperty::PT_EDIT_MENU,
                                                  true,
                                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                                  NULL,
                                                  &gExtFilesMenu);

        PropSet.Add(pCombination);

        PropName.LoadString(IDS_Z_FILE_NAME_NAME);
        PropDesc.LoadString(IDS_Z_FILE_NAME_DESC);

        // Propriété "Lien" du groupe "Lien externe"
        pCombination = new ZBProperty(FinalPropTitle,
            (GroupValue == true) ? ZS_BP_PROP_EXTFILE : (ZS_BP_PROP_EXTFILE + i),
                                      PropName,
                                      (GroupValue == true) ? Z_FILE_NAME : (Z_FILE_NAME + (i * 40)),
                                      PropDesc,
                                      GetFileName(i),
                                      ZBProperty::PT_EDIT_EXTENDED);

        PropSet.Add(pCombination);

        // RS-MODIF appears only if messenger activated (call to next function)
        /*
            PropName.LoadString( IDS_Z_INSERTION_TYPE_NAME );
            PropDesc.LoadString( IDS_Z_INSERTION_TYPE_DESC );

            if ( NumericValue )
            {
                pCombination = new ZBProperty( FinalPropTitle,
                                              ( GroupValue == true ) ? ZS_BP_PROP_EXTFILE : ( ZS_BP_PROP_EXTFILE + i ),
                                              PropName,
                                              ( GroupValue == true ) ? Z_INSERTION_TYPE : ( Z_INSERTION_TYPE + ( i * 40 ) ),
                                              PropDesc,
                                              (double)GetInsertionType( i ),
                                              ZBProperty::PT_EDIT_NUMBER );
            }
            else
            {
                pCombination = new ZBProperty( FinalPropTitle,
                                               ( GroupValue == true ) ? ZS_BP_PROP_EXTFILE : ( ZS_BP_PROP_EXTFILE + i ),
                                               PropName,
                                               ( GroupValue == true ) ? Z_INSERTION_TYPE : ( Z_INSERTION_TYPE + ( i * 40 ) ),
                                               PropDesc,
                                               ZAGlobal::GetInsertionTypeString( GetInsertionType( i ) ),
                                               ZBProperty::PT_COMBO_STRING_READONLY,
                                               true,
                                               ZBStringFormat( ZBStringFormat::General ),
                                               ZAGlobal::GetArrayInsertionType() );
            }

            PropSet.Add( pCombination );

            PropName.LoadString( IDS_Z_ACTIVATION_TYPE_NAME );
            PropDesc.LoadString( IDS_Z_ACTIVATION_TYPE_DESC );

            if ( NumericValue )
            {
                pCombination = new ZBProperty( FinalPropTitle,
                                               ( GroupValue == true ) ? ZS_BP_PROP_EXTFILE : ( ZS_BP_PROP_EXTFILE + i ),
                                               PropName,
                                               ( GroupValue == true ) ? Z_ACTIVATION_TYPE : ( Z_ACTIVATION_TYPE + ( i * 40 ) ),
                                               PropDesc,
                                               (double)GetActivationType( i ),
                                               ZBProperty::PT_EDIT_NUMBER );
            }
            else
            {
                pCombination = new ZBProperty( FinalPropTitle,
                                               ( GroupValue == true ) ? ZS_BP_PROP_EXTFILE : ( ZS_BP_PROP_EXTFILE + i ),
                                               PropName,
                                               ( GroupValue == true ) ? Z_ACTIVATION_TYPE : ( Z_ACTIVATION_TYPE + ( i * 40 ) ),
                                               PropDesc,
                                               ZAGlobal::GetActivationTypeString( GetActivationType( i ) ),
                                               ZBProperty::PT_COMBO_STRING_READONLY,
                                               true,
                                               ZBStringFormat( ZBStringFormat::General ),
                                               ZAGlobal::GetArrayActivationType() );
            }

            PropSet.Add( pCombination );
            */
    }

    return true;
}

// RS-MODIF 11.12.04 fill properties only for Messenger
bool ZBExtFilePropertyMgr::FillPropertiesMessenger(ZBPropertySet&    PropSet,
                                                   bool            NumericValue    /*= false*/,
                                                   bool            GroupValue        /*= false*/)
{
    // If the menu is not loaded, load it
    if (gExtFilesMenu.GetSafeHmenu() == NULL)
    {
        gExtFilesMenu.LoadMenu(IDR_EXTFILES_MENU);
    }

    // Run through all combination properties
    CString    FinalPropTitle;
    CString    PropTitle;
    CString    PropName;
    CString    PropDesc;
    size_t    Count = GetExtFileCount();

    PropTitle.LoadString(IDS_ZS_BP_PROP_EXTFILE_TITLE);

    for (size_t i = 0; i < Count; ++i)
    {
        FinalPropTitle.Format(_T("%s (%d)"), PropTitle, i + 1);

        ZBProperty* pCombination;

        PropName.LoadString(IDS_Z_INSERTION_TYPE_NAME);
        PropDesc.LoadString(IDS_Z_INSERTION_TYPE_DESC);

        // Propriété "Mode d'insertion" du groupe "Lien externe"
        if (NumericValue)
        {
            pCombination = new ZBProperty(FinalPropTitle,
                (GroupValue == true) ? ZS_BP_PROP_EXTFILE : (ZS_BP_PROP_EXTFILE + i),
                                          PropName,
                                          (GroupValue == true) ? Z_INSERTION_TYPE : (Z_INSERTION_TYPE + (i * 40)),
                                          PropDesc,
                                          (double)GetInsertionType(i),
                                          ZBProperty::PT_EDIT_NUMBER);
        }
        else
        {
            pCombination = new ZBProperty(FinalPropTitle,
                (GroupValue == true) ? ZS_BP_PROP_EXTFILE : (ZS_BP_PROP_EXTFILE + i),
                                          PropName,
                                          (GroupValue == true) ? Z_INSERTION_TYPE : (Z_INSERTION_TYPE + (i * 40)),
                                          PropDesc,
                                          PSS_Global::GetInsertionTypeString(GetInsertionType(i)),
                                          ZBProperty::PT_COMBO_STRING_READONLY,
                                          true,
                                          PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                          PSS_Global::GetArrayInsertionType());
        }

        PropSet.Add(pCombination);

        PropName.LoadString(IDS_Z_ACTIVATION_TYPE_NAME);
        PropDesc.LoadString(IDS_Z_ACTIVATION_TYPE_DESC);

        // Propriété "Mode d'activation" du groupe "Lien externe"
        if (NumericValue)
        {
            pCombination = new ZBProperty(FinalPropTitle,
                (GroupValue == true) ? ZS_BP_PROP_EXTFILE : (ZS_BP_PROP_EXTFILE + i),
                                          PropName,
                                          (GroupValue == true) ? Z_ACTIVATION_TYPE : (Z_ACTIVATION_TYPE + (i * 40)),
                                          PropDesc,
                                          (double)GetActivationType(i),
                                          ZBProperty::PT_EDIT_NUMBER);
        }
        else
        {
            pCombination = new ZBProperty(FinalPropTitle,
                (GroupValue == true) ? ZS_BP_PROP_EXTFILE : (ZS_BP_PROP_EXTFILE + i),
                                          PropName,
                                          (GroupValue == true) ? Z_ACTIVATION_TYPE : (Z_ACTIVATION_TYPE + (i * 40)),
                                          PropDesc,
                                          PSS_Global::GetActivationTypeString(GetActivationType(i)),
                                          ZBProperty::PT_COMBO_STRING_READONLY,
                                          true,
                                          PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                          PSS_Global::GetArrayActivationType());
        }

        PropSet.Add(pCombination);
    }

    return true;
}

bool ZBExtFilePropertyMgr::SaveProperties(ZBPropertySet& PropSet)
{
    // Now run through the list of data and fill the property set of external files
    ZBPropertyIterator i(&PropSet);
    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        if (pProp->GetCategoryID() >= ZS_BP_PROP_EXTFILE &&
            pProp->GetCategoryID() <= (ZS_BP_PROP_EXTFILE + (int)GetExtFileCount()))
        {
            SaveProperty(*pProp);
        }
    }

    return true;
}

bool ZBExtFilePropertyMgr::SaveProperty(ZBProperty& Property)
{
    if (Property.GetCategoryID() >= ZS_BP_PROP_EXTFILE &&
        Property.GetCategoryID() <= (ZS_BP_PROP_EXTFILE + (int)GetExtFileCount()))
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_EXTFILE;

        switch (Property.GetItemID() - (i * 40))
        {
            case Z_FILE_TITLE:
            {
                SetFileTitle(i, Property.GetValueString());
                break;
            }

            case Z_FILE_NAME:
            {
                SetFileName(i, Property.GetValueString());
                break;
            }

            case Z_INSERTION_TYPE:
            {
                SetInsertionType(i, PSS_Global::GetInsertionType(Property.GetValueString()));
                break;
            }

            case Z_ACTIVATION_TYPE:
            {
                SetActivationType(i, PSS_Global::GetActivationType(Property.GetValueString()));
                break;
            }
        }
    }

    return true;
}

bool ZBExtFilePropertyMgr::ProcessExtendedInput(ZBProperty&    Property,
                                                CString&        value,
                                                ZBPropertySet&    Properties,
                                                bool&            Refresh)
{
    if (Property.GetCategoryID() >= ZS_BP_PROP_EXTFILE &&
        Property.GetCategoryID() <= (ZS_BP_PROP_EXTFILE + (int)GetExtFileCount()))
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_EXTFILE;

        // Call the dialog
        PSS_ReferenceFileDialog refFileDlg(GetFileName(i),
                                           GetInsertionType(i),
                                           GetActivationType(i));

        if (refFileDlg.DoModal() == IDOK)
        {
            value = refFileDlg.GetReference();
            PSS_File file(refFileDlg.GetReference());

            if (file.Exist())
            {
                SetFileTitle(i, file.GetDisplayName());
            }
            else
            {
                SetFileTitle(i, refFileDlg.GetReference());
            }

            SetFileName(i, refFileDlg.GetReference());
            SetInsertionType(i, refFileDlg.GetInsertionType());
            SetActivationType(i, refFileDlg.GetActivationType());

            Refresh = true;
            return true;
        }
    }

    return false;
}

bool ZBExtFilePropertyMgr::ProcessMenuCommand(int                MenuCommand,
                                              ZBProperty&        Property,
                                              CString&            value,
                                              ZBPropertySet&    Properties,
                                              bool&            Refresh)
{
    if (Property.GetCategoryID() >= ZS_BP_PROP_EXTFILE &&
        Property.GetCategoryID() <= (ZS_BP_PROP_EXTFILE + (int)GetExtFileCount()))
    {
        switch (MenuCommand)
        {
            case ID_ADD_NEWEXTFILE:
            {
                OnAddNewExtFile(Property, value, Properties, Refresh);
                break;
            }

            case ID_DEL_CURRENTEXTFILE:
            {
                OnDelCurrentExtFile(Property, value, Properties, Refresh);
                break;
            }

            default:
                break;
        }

        return true;
    }

    return false;
}

bool ZBExtFilePropertyMgr::DoInsertExtFile(bool DisplayDialog /*= true*/)
{
    int Idx = AddNewExtFile();

    // Add a new external file
    if (Idx >= 0)
    {
        if (DisplayDialog)
        {
            // call the dialog
            PSS_ReferenceFileDialog refFileDlg(GetFileName(Idx),
                                               GetInsertionType(Idx),
                                               GetActivationType(Idx));

            if (refFileDlg.DoModal() == IDOK)
            {
                PSS_File file(refFileDlg.GetReference());

                if (file.Exist())
                {
                    SetFileTitle(Idx, file.GetDisplayName());
                }
                else
                {
                    SetFileTitle(Idx, refFileDlg.GetReference());
                }

                SetFileName(Idx, refFileDlg.GetReference());
                SetInsertionType(Idx, refFileDlg.GetInsertionType());
                SetActivationType(Idx, refFileDlg.GetActivationType());
            }
        }

        return true;
    }

    return false;
}

// Drag and drop methods
bool ZBExtFilePropertyMgr::AcceptDropItem(CObject* pObj, CPoint pt)
{
    // Accept drop of file, scriptor template file and URL only
    if (pObj && ISA(pObj, PSS_TemplateFile) ||
        (ISA(pObj, PSS_NetResourceWrapper) && !((PSS_NetResourceWrapper*)pObj)->GetFileName().IsEmpty() &&
        ((PSS_NetResourceWrapper*)pObj)->IsFile()))
    {
        // If is a template, check if we accept external file
        if (ISA(pObj, PSS_TemplateFile))
        {
            return true;
        }

        // If it is a file, check what kind of file
        if (ISA(pObj, PSS_NetResourceWrapper))
        {
            // If an executable, not allowed
            PSS_File file(((PSS_NetResourceWrapper*)pObj)->GetFileName());

            if (file.GetFileExt().CompareNoCase(_T(".exe")) == 0 ||
                file.GetFileExt().CompareNoCase(_T(".com")) == 0 ||
                file.GetFileExt().CompareNoCase(_T(".bat")) == 0)
            {
                return false;
            }

            // Otherwise, ok
            return true;
        }
    }

    return false;
}

bool ZBExtFilePropertyMgr::DropItem(CObject* pObj, CPoint pt)
{
    if (pObj && ISA(pObj, PSS_TemplateFile) ||
        (ISA(pObj, PSS_NetResourceWrapper) && !((PSS_NetResourceWrapper*)pObj)->GetFileName().IsEmpty() &&
        ((PSS_NetResourceWrapper*)pObj)->IsFile()))
    {
        // Add a new external file
        // First, check if there is an empty one.
        // If there is, use it
        int Idx = LocateFirstEmptyExtFile();

        if (Idx == -1)
        {
            Idx = AddNewExtFile();
        }

        // If is a template, add it
        if (Idx >= 0 && ISA(pObj, PSS_TemplateFile))
        {
            SetFileTitle(Idx, ((PSS_TemplateFile*)pObj)->GetTitle());
            SetFileName(Idx, ((PSS_TemplateFile*)pObj)->GetFileName());
            SetInsertionType(Idx, 0);
            SetActivationType(Idx, 0);

            return true;
        }

        // If it is a file, add it
        if (Idx >= 0 && ISA(pObj, PSS_NetResourceWrapper))
        {
            PSS_File file(((PSS_NetResourceWrapper*)pObj)->GetFileName());

            if (file.Exist())
            {
                SetFileTitle(Idx, file.GetDisplayName());
            }
            else
            {
                SetFileTitle(Idx, ((PSS_NetResourceWrapper*)pObj)->GetFileName());
            }

            SetFileName(Idx, ((PSS_NetResourceWrapper*)pObj)->GetFileName());
            SetInsertionType(Idx, 0);
            SetActivationType(Idx, 0);

            return true;
        }
    }

    return false;
}

void ZBExtFilePropertyMgr::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // Before storing elements,
        // removes all empty elements
        RemoveAllEmptyExtFiles();
    }

    m_ExternalFiles.Serialize(ar);
}
