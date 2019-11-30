// ZBExtAppPropertyMgr.h: interface for the ZBExtAppPropertyMgr class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBEXTAPPPROPERTYMGR_H__62413AB0_627B_42E2_8937_E3F47EFE93DB__INCLUDED_)
#define AFX_ZBEXTAPPPROPERTYMGR_H__62413AB0_627B_42E2_8937_E3F47EFE93DB__INCLUDED_

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

#include "ZBExtApps.h"
#include "ZBExtAppProp.h"
#include "zProperty\ZIProperties.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 13 octobre - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBExtAppPropertyMgr
{
public:

    ZBExtAppPropertyMgr(CODSymbolComponent* pSymbol = NULL);
    virtual ~ZBExtAppPropertyMgr();

    /* Copy constructor. */
    ZBExtAppPropertyMgr(const ZBExtAppPropertyMgr& src);

    /* Assignment operator. */
    ZBExtAppPropertyMgr& operator=(const ZBExtAppPropertyMgr& src);

    /////////////////////////////////////////////////////////////////////////////
    // External Applications methods

    // Returns the extern application object reference
    ZBExtApps& GetExtApps()
    {
        return m_ExternalApplications;
    }

    // Return the counter of ExtApps
    size_t GetExtAppCount() const
    {
        return m_ExternalApplications.GetExtAppCount();
    }

    // Add a new ExtApp, 
    // and return the index of the new added ExtApp
    // Return -1 if the function fails
    int AddNewExtApp()
    {
        return m_ExternalApplications.AddNewExtApp();
    }

    // Add a new ExtApp, 
    // and return the index of the new added ExtApp
    // Return -1 if the function fails
    int AddExtApp(ZBExtAppProperties* pProperty)
    {
        return m_ExternalApplications.AddExtApp(pProperty);
    }

    // Delete an ExtApp
    bool DeleteExtApp(size_t Index)
    {
        return m_ExternalApplications.DeleteExtApp(Index);
    }

    bool DeleteExtApp(const CString CommandTitle)
    {
        return m_ExternalApplications.DeleteExtApp(CommandTitle);
    }

    bool DeleteExtApp(ZBExtAppProperties* pProperty)
    {
        return m_ExternalApplications.DeleteExtApp(pProperty);
    }

    // Return true if the ExtApp already exists
    bool ExtAppExist(const CString CommandTitle) const
    {
        return m_ExternalApplications.ExtAppExist(CommandTitle);
    }

    // Retreive the right ExtApp properties base on the ExtApp file name
    ZBExtAppProperties* LocateExtApp(const CString CommandTitle) const
    {
        return m_ExternalApplications.LocateExtApp(CommandTitle);
    }

    ZBExtAppProperties* GetExtAppProperty(size_t Index) const
    {
        return m_ExternalApplications.GetProperty(Index);
    }

    // Returns the index of the first empty element if there is,
    // otherwise, return -1
    int LocateFirstEmptyExtApp() const
    {
        return m_ExternalApplications.LocateFirstEmptyExtApp();
    }

    // Remove only empty elements
    void RemoveAllEmptyExtApps()
    {
        m_ExternalApplications.RemoveAllEmptyExtApps();
    }

    // Remove all elements
    void RemoveAllExtApps()
    {
        m_ExternalApplications.RemoveAllExtApps();
    }

    /* Gets the file title at the specific Index. */
    CString GetCommandTitle(size_t Index) const
    {
        return m_ExternalApplications.GetCommandTitle(Index);
    }

    //@cmember
    /* Sets the file title at the specific Index. */
    void SetCommandTitle(size_t Index, CString Value)
    {
        m_ExternalApplications.SetCommandTitle(Index, Value);
    }

    //@cmember
    /* Gets the command line at the specific Index. */
    CString GetCommandLine(size_t Index) const
    {
        return m_ExternalApplications.GetCommandLine(Index);
    }

    //@cmember
    /* Sets the command line at the specific Index. */
    void SetCommandLine(size_t Index, CString Value)
    {
        m_ExternalApplications.SetCommandLine(Index, Value);
    }

    //@cmember
    /* Gets the command parameters at the specific Index. */
    CString GetCommandParameters(size_t Index) const
    {
        return m_ExternalApplications.GetCommandParameters(Index);
    }

    //@cmember
    /* Sets the command parameters at the specific Index. */
    void SetCommandParameters(size_t Index, CString Value)
    {
        m_ExternalApplications.SetCommandParameters(Index, Value);
    }

    //@cmember
    /* Gets the startup directory at the specific Index. */
    CString GetCommandStartupDirectory(size_t Index) const
    {
        return m_ExternalApplications.GetCommandStartupDirectory(Index);
    }

    //@cmember
    /* Sets the startup directory at the specific Index. */
    void SetCommandStartupDirectory(size_t Index, CString Value)
    {
        m_ExternalApplications.SetCommandStartupDirectory(Index, Value);
    }

    //@cmember
    /* Gets the insertion type at the specific Index. */
    int GetPriorityLevel(size_t Index) const
    {
        return m_ExternalApplications.GetPriorityLevel(Index);
    }

    //@cmember
    /* Sets the insertion type at the specific Index. */
    void SetPriorityLevel(size_t Index, const int value)
    {
        m_ExternalApplications.SetPriorityLevel(Index, value);
    }

    //@cmember
    /* Gets the activation type at the specific Index. */
    int GetWindowStartMode(size_t Index) const
    {
        return m_ExternalApplications.GetWindowStartMode(Index);
    }

    //@cmember
    /* Sets the activation type at the specific Index. */
    void SetWindowStartMode(size_t Index, const int value)
    {
        m_ExternalApplications.SetWindowStartMode(Index, value);
    }

    virtual void OnAddNewExtApp(ZBProperty& Property, CString& value, ZBPropertySet& Properties, bool& Refresh)
    {
        // Sets the refresh flag to true
        Refresh = DoInsertExtApp(false);

        if (Refresh)
        {
            value = GetCommandTitle(GetExtAppCount() - 1);
        }
    }

    virtual void OnDelCurrentExtApp(ZBProperty& Property, CString& value, ZBPropertySet& Properties, bool& Refresh)
    {
        // Delete the current selected external application
        int Index = Property.GetCategoryID() - ZS_BP_PROP_EXTAPP;

        if (DeleteExtApp(Index))
        {
            // Sets the refresh flag to true
            Refresh = true;
        }
    }

    // Do a standard ext app insertion.
    virtual bool DoInsertExtApp(bool DisplayDialog = true);

    // Drag and drop methods
    virtual bool AcceptDropItem(CObject* pObj, const CPoint& pt);
    virtual bool DropItem(CObject* pObj, const CPoint& pt);

    // Call when a new symbol is created
    virtual bool CreateSymbolProperties();

    // Call to retreive properties for the object
    virtual bool FillProperties(ZBPropertySet& PropSet, bool NumericValue = false, bool GroupValue = false);

    // RS-MODIF 11.12.04 fill properties function for messenger
    virtual bool FillPropertiesMessenger(ZBPropertySet& PropSet, bool NumericValue = false, bool GroupValue = false);

    // Call to save new changes to object's properties
    virtual bool SaveProperties(ZBPropertySet& PropSet);

    // Called to retreive a property for the object
    virtual bool FillProperty(ZBProperty& Property)
    {
        return true;
    }

    // Called to save a property for the object
    virtual bool SaveProperty(ZBProperty& Property);

    // Called to check the property value
    virtual bool CheckPropertyValue(ZBProperty& Property, CString& value, ZBPropertySet& Properties)
    {
        return true;
    }

    // Called to process the extended input for the property value
    virtual bool ProcessExtendedInput(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

    // Called to process the a menu command for the property value
    virtual bool ProcessMenuCommand(int            MenuCommand,
                                    ZBProperty&    Property,
                                    CString&        value,
                                    ZBPropertySet&    Properties,
                                    bool&            Refresh);

    // Called after the property changed
    virtual bool OnPostPropertyChanged(ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh)
    {
        // Nothing has changed
        return false;
    }

    // Called before the property changed
    virtual bool OnPrePropertyChanged(const CString& NewValue, ZBProperty& Property, ZBPropertySet& Properties)
    {
        // No error
        return true;
    }

    /* Serializes the external applications. */
    virtual void Serialize(CArchive& ar);

protected:

    ZBExtApps            m_ExternalApplications;
    CODSymbolComponent* m_pSymbol;
};

#endif // !defined(AFX_ZBEXTAPPPROPERTYMGR_H__62413AB0_627B_42E2_8937_E3F47EFE93DB__INCLUDED_)