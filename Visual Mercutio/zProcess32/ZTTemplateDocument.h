/****************************************************************************
 * ==> PSS_TemplateDocument ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a template document                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TemplateDocumentH
#define PSS_TemplateDocumentH

// scope symbols in stingray foundation library
using namespace sfl;

typedef void (CALLBACK* TEMPLATEMAPPROC)(LPCSTR);

template <class T>
class _TemplateFunctionAccessor
{
    // Embedded types
public:

    typedef T _SourceClass;

    typedef CDocument* (T::*OPENFILE)(LPCSTR val);
    typedef void (T::*SAVEFILE)(LPCSTR val);

    // Constructors/destructor
public:

    _TemplateFunctionAccessor()
    {
        m_open = NULL;
        m_save = NULL;
    };

    _TemplateFunctionAccessor(const _TemplateFunctionAccessor& src)
    {
        m_open = src.m_open;
        m_save = src.m_save;
    };

    _TemplateFunctionAccessor(OPENFILE pOpen, SAVEFILE pSave = NULL)
    {
        m_open = pOpen;
        m_save = pSave;
    };

    // Operations
public:

    //@cmember,mfunc
    // Retrieve a property value.
    //@@rdesc void
    //@@parm Pointer to the object on which to invoke the get function on.
    //@@parm Output parameter to receive the property value.
    //@@comm
    // This function invokes the get function on the given source object
    // in order to retrieve the value.
    //@@end
    /* Retrieve a property value*/
    CDocument* OpenFile(const _SourceClass* pObj, LPCSTR val)
    {
        if (m_open != NULL)
        {
            return (pObj->*m_open)(val);
        }

        return NULL;
    };

    //@cmember,mfunc
    // Store a property value.
    //@@rdesc void
    //@@parm Pointer to the object on which to invoke the put function on.
    //@@parm Input value used to set the property value.
    //@@comm
    // This function invokes the put function on the given source object
    // in order to store the value.
    //@@end
    /* Store a property value*/
    void SaveFile(_SourceClass* pObj, LPCSTR val)
    {
        if (m_save != NULL)
        {
            (pObj->*m_save)(val);
        }
    };

    // Attributes
protected:

    //@cmember
    /* Pointer to the open function*/
    OPENFILE m_open;

    //@cmember
    /* Pointer to the save function*/
    SAVEFILE m_save;
};

/////////////////////////////////////////////////////////////////////////////
//@doc _TemplateFunctionNoopAccessor
//
//@class _TemplateFunctionNoopAccessor | This class implements a property accessor
// that does nothing. It is used as a parameter for the <c _TemplateMapCollection>

class _TemplateFunctionNoopAccessor
{
    // Embedded types
public:

    typedef void _SourceClass;

    //@cmember,mfunc
    // This function does nothing.
    //@@rdesc void
    //@@end
    /* This function does nothing*/
    CDocument* OpenFile(const _SourceClass* pObj, LPCSTR val)
    {
        return NULL;
    };

    //@cmember,mfunc
    // This function does nothing.
    //@@rdesc void
    //@@end
    /* This function does nothing*/
    void SaveFile(_SourceClass* pObj, LPCSTR val)
    {};
};

// The _TemplateMapCollection class implements a collection of templates entries
template <class _TemplateAccessor = _TemplateFunctionNoopAccessor>
class ZTTemplateDocument
{
public:

    typedef ZTTemplateDocument<_TemplateAccessor>    _ThisClass;
    typedef _TemplateAccessor                        _FileOpenWorkspaceAccessor;

    enum TemplateStringIndex
    {
        windowTitle,            // default window title
        docName,                // user visible name for default document
        fileNewName,            // user visible name for FileNew
        // for file based documents:
        filterName,                // user visible name for FileOpen
        filterExt,                // user visible extension for FileOpen
        // for file based documents with Shell open support:
        regFileTypeId,            // REGEDIT visible registered file type identifier
        regFileTypeName,        // Shell visible registered file type name
        TemplateMustBeRegisteredPosition,
        DefaultIconPosition,
    };

    class _TemplateMapCollection
    {
    public:

        // The _TemplateEntry class encapsulates a template resource ID and
        // accessors for openfile and savefile. Entries are stored in the map.
        class _TemplateEntry
        {
        public:

            UINT                m_nIDRes;
            CString                m_DefTemplate;
            CString                m_Extension;
            _TemplateAccessor*    m_pAccessor;

            _TemplateEntry(UINT            nIDRes,
                           const CString    DefTemplate)
                : m_nIDRes(nIDRes),
                m_DefTemplate(DefTemplate),
                m_pAccessor(NULL)
            {
                GetTemplateString(m_Extension, filterExt);
            };

            _TemplateEntry(UINT                        nIDRes,
                           const CString                DefTemplate,
                           const _TemplateAccessor&    accessor)
                : m_nIDRes(nIDRes),
                m_DefTemplate(DefTemplate)
            {
                GetTemplateString(m_Extension, filterExt);
                m_pAccessor = new _TemplateAccessor(accessor);
            };

            _TemplateEntry(const _TemplateEntry& src)
            {
                m_nIDRes = src.m_nIDRes;
                m_DefTemplate = src.m_DefTemplate;
                m_Extension = src.m_Extension;
                m_pAccessor = NULL;

                if (src.m_pAccessor != NULL)
                {
                    m_pAccessor = new _TemplateAccessor(*src.m_pAccessor);
                }
            };

            ~_TemplateEntry()
            {
                if (m_pAccessor)
                {
                    delete m_pAccessor;
                    m_pAccessor = NULL;
                }
            };

            _TemplateEntry& operator=(const _TemplateEntry& src)
            {
                m_nIDRes = src.m_nIDRes;
                m_DefTemplate = src.m_DefTemplate;
                m_Extension = src.m_Extension;

                if (m_pAccessor != NULL)
                {
                    delete m_pAccessor;
                    m_pAccessor = NULL;
                }

                if (src.m_pAccessor != NULL)
                {
                    m_pAccessor = new _TemplateAccessor(*src.m_pAccessor);
                }

                return *this;
            };

            bool GetTemplateString(CString& rString, int i) const
            {
                return (AfxExtractSubString(rString, m_DefTemplate, i)) ? true : false;
            }
        }; // End of class _TemplateEntry

    public:

        _TemplateMapCollection()
        {};

        ~_TemplateMapCollection()
        {
            DeleteAll();
        };

        ///////////////////////////////////////////////////////////////////////////
        // Collection definitions

        //@type _TemplateEntrySet | An array of _TemplateEntry pointers.
        //@iex typedef CCArray_T<_TemplateEntry*,_TemplateEntry*> _TemplateEntrySet;
        typedef CCArray_T<_TemplateEntry*, _TemplateEntry*> _TemplateEntrySet;

        //@type _TemplateEntryIterator | An iterator for _TemplateEntrySet collections.
        //@iex typedef Iterator_T<_TemplateEntry*> _TemplateEntryIterator;
        typedef Iterator_T<_TemplateEntry*> _TemplateEntryIterator;

        _TemplateEntrySet m_TemplateSet;

        bool AddEntry(UINT nIDRes)
        {
            if (nIDRes <= 0)
            {
                return false;
            }

            CString DefTemplate;
            DefTemplate.LoadString(nIDRes);

            _TemplateEntry* pEntry = new _TemplateEntry(nIDRes, DefTemplate);
            m_TemplateSet.Add(pEntry);

            return true;
        };

        bool AddEntry(UINT nIDRes, const _TemplateAccessor& accessor)
        {
            if (nIDRes <= 0)
            {
                return false;
            }

            CString DefTemplate;
            DefTemplate.LoadString(nIDRes);

            _TemplateEntry* pEntry = new _TemplateEntry(nIDRes, DefTemplate, accessor);
            m_TemplateSet.Add(pEntry);

            return true;
        };

        int GetNumEntries() const
        {
            return m_TemplateSet.GetSize();
        };

        _TemplateEntry* GetTemplateEntryByResource(UINT nIDRes) const
        {
            _TemplateEntryIterator i(&m_TemplateSet);

            for (_TemplateEntry* pEntry = i.GetFirst(); pEntry != NULL; pEntry = i.GetNext())
            {
                if (pEntry && pEntry->m_nIDRes == nIDRes)
                {
                    return pEntry;
                }
            }

            return NULL;
        };

        _TemplateEntry* GetTemplateEntryByExtension(const CString Ext) const
        {
            _TemplateEntryIterator i(&m_TemplateSet);

            for (_TemplateEntry* pEntry = i.GetFirst(); pEntry != NULL; pEntry = i.GetNext())
            {
                if (pEntry && pEntry->m_Extension == Ext)
                {
                    return pEntry;
                }
            }

            return NULL;
        };

        _TemplateEntry* GetTemplateEntryByFileName(const CString fileName) const
        {
            PSS_File file(fileName);
            return GetTemplateEntryByExtension(file.GetFileExt());
        };

        UINT GetTemplateIDByExtension(const CString Ext) const
        {
            _TemplateEntryIterator i(&m_TemplateSet);

            for (_TemplateEntry* pEntry = i.GetFirst(); pEntry != NULL; pEntry = i.GetNext())
            {
                if (pEntry && pEntry->m_Extension == Ext)
                {
                    return pEntry->m_nIDRes;
                }
            }

            return NULL;
        };

        UINT GetTemplateIDByFileName(const CString fileName) const
        {
            PSS_File file(fileName);
            return GetTemplateIDByExtension(file.GetFileExt());
        };

        _TemplateAccessor* GetAccessorByResource(UINT nIDRes) const
        {
            _TemplateEntry* pEntry = GetTemplateEntryByResource(nIDRes);
            return (pEntry) ? pEntry->m_pAccessor : NULL;
        };

        _TemplateAccessor* GetAccessorByExtension(const CString Ext) const
        {
            _TemplateEntry* pEntry = GetTemplateEntryByExtension(Ext);
            return (pEntry) ? pEntry->m_pAccessor : NULL;
        };

        _TemplateEntry* GetTemplateAt(const int nIdx) const
        {
            if (nIdx >= GetNumEntries())
            {
                return NULL;
            }

            return m_TemplateSet.GetAt(nIdx);
        };

        void DeleteAll()
        {
            _TemplateEntryIterator i(&m_TemplateSet);

            for (_TemplateEntry* pEntry = i.GetFirst(); pEntry != NULL; pEntry = i.GetNext())
            {
                if (pEntry)
                {
                    delete pEntry;
                }
            }

            m_TemplateSet.RemoveAll();
        };
    }; // End of class _TemplateMapCollection

    // Public function of class ZTemplateDocument
public:

    // JMR-MODIF - Le 30 mai 2005 - Ajout de typename pour conformité aux nouvelles normes ISO; voir doc VC.NET
    virtual typename ZTTemplateDocument<_TemplateAccessor>::_TemplateMapCollection& GetTemplateMapCollection() const
    {
        static ZTTemplateDocument<_TemplateAccessor>::_TemplateMapCollection templateMapCollection;
        return templateMapCollection;
    };

    bool RegisterTemplate(UINT nIDRes)
    {
        return GetTemplateMapCollection().AddEntry(nIDRes);
    };

    bool RegisterTemplate(UINT nIDRes, const _TemplateAccessor& accessor)
    {
        return GetTemplateMapCollection().AddEntry(nIDRes, accessor);
    };

    int GetTemplateNumEntries() const
    {
        return GetTemplateMapCollection().GetNumEntries();
    };

    typename _TemplateMapCollection::_TemplateEntry* GetTemplateAt(const int nIdx) const
    {
        return GetTemplateMapCollection().GetTemplateAt(nIdx);
    };

    typename _TemplateMapCollection::_TemplateEntry* GetTemplateByResource(UINT nIDRes) const
    {
        return GetTemplateMapCollection().GetTemplateEntryByResource(nIDRes);
    };

    typename _TemplateMapCollection::_TemplateEntry* GetTemplateEntryByExtension(const CString Ext) const
    {
        return GetTemplateMapCollection().GetTemplateEntryByExtension(Ext);
    };

    typename _TemplateMapCollection::_TemplateEntry* GetTemplateEntryByFileName(const CString fileName) const
    {
        return GetTemplateMapCollection().GetTemplateEntryByFileName(fileName);
    };

    UINT GetTemplateIDByExtension(const CString Ext) const
    {
        return GetTemplateMapCollection().GetTemplateIDByExtension(Ext);
    };

    UINT GetTemplateIDByFileName(const CString fileName) const
    {
        return GetTemplateMapCollection().GetTemplateIDByFileName(fileName);
    };
};

#endif
