/****************************************************************************
 * ==> PSS_TemplateDocument ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a template document which implements a collection *
 *               of templates entries                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TemplateDocumentH
#define PSS_TemplateDocumentH

// scope symbols in stingray foundation library
using namespace sfl;

/**
* Template map process callback
*/
typedef void (CALLBACK* ITfTemplateMapProc)(LPCSTR);

/**
* Template function accessor
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template <class T>
class PSS_TemplateFunctionAccessor
{
    public:
        typedef T ISourceClass;

        /**
        * Called when a file is open
        *@param pFileName - the file name to open
        */
        typedef CDocument* (T::*ITfOpenFile)(LPCSTR pFileName);

        /**
        * Called when a file is saved
        *@param pFileName - the file name to save
        */
        typedef void (T::*ITfSaveFile)(LPCSTR pFileName);

        PSS_TemplateFunctionAccessor() :
            m_fOpen(NULL),
            m_fSave(NULL)
        {}

        /**
        * Constructor
        *@param fOpen - open file function handler
        *@param fSave - save file function handler
        */
        PSS_TemplateFunctionAccessor(ITfOpenFile fOpen, ITfSaveFile fSave = NULL) :
            m_fOpen(fOpen),
            m_fSave(fSave)
        {}

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_TemplateFunctionAccessor(const PSS_TemplateFunctionAccessor& other)
        {
            m_fOpen = other.m_fOpen;
            m_fSave = other.m_fSave;
        }

        virtual ~PSS_TemplateFunctionAccessor()
        {}

        /**
        * Invokes the callback function to open a file
        *@param pSourceClass - the source class from which the callback should be invoked
        *@param pFileName - the file name to open
        *@return the opened document, NULL on error
        */
        virtual CDocument* OpenFile(const ISourceClass* pSourceClass, LPCSTR pFileName)
        {
            if (m_fOpen)
                return pSourceClass->*m_fOpen(pFileName);

            return NULL;
        }

        /**
        * Invokes the callback function to save a file
        *@param pSourceClass - the source class from which the callback should be invoked
        *@param pFileName - the file name to save
        *@return the opened document, NULL on error
        */
        virtual void SaveFile(ISourceClass* pSourceClass, LPCSTR pFileName)
        {
            if (m_pSave)
                pSourceClass->*m_fSave(pFileName);
        }

    protected:
        ITfOpenFile m_fOpen;
        ITfSaveFile m_fSave;
};

/**
* Template function accessor which does nothing
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_TemplateFunctionNoopAccessor
{
    public:
        typedef void ISourceClass;

        PSS_TemplateFunctionNoopAccessor()
        {}

        virtual ~PSS_TemplateFunctionNoopAccessor()
        {}

        /**
        * Invokes the callback function to open a file
        *@param pSourceClass - the source class from which the callback should be invoked
        *@param pFileName - the file name to open
        *@return the opened document, NULL on error
        *@note As implemented in this class, this function does nothing and always return NULL
        */
        virtual CDocument* OpenFile(const ISourceClass* pSourceClass, LPCSTR pFileName)
        {
            return NULL;
        }

        /**
        * Invokes the callback function to save a file
        *@param pSourceClass - the source class from which the callback should be invoked
        *@param pFileName - the file name to save
        *@note As implemented in this class, this function does nothing
        */
        virtual void SaveFile(ISourceClass* pSourceClass, LPCSTR pFileName)
        {}
};

/**
* Template document, implements a collection of templates entries
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template <class TTemplateAccessor = PSS_TemplateFunctionNoopAccessor>
class PSS_TemplateDocument
{
    public:
        /**
        * Template string index
        */
        enum class IEStringIndex
        {
            IE_SI_WindowTitle,                      // default window title
            IE_SI_DocName,                          // user visible name for default document
            IE_SI_FileNewName,                      // user visible name for FileNew
            // for file based documents
            IE_SI_FilterName,                       // user visible name for FileOpen
            IE_SI_FilterExt,                        // user visible extension for FileOpen
            // for file based documents with Shell open support:
            IE_SI_RegFileTypeId,                    // REGEDIT visible registered file type identifier
            IE_SI_RegFileTypeName,                  // Shell visible registered file type name
            IE_SI_TemplateMustBeRegisteredPosition,
            IE_SI_DefaultIconPosition,
        };

        /**
        * Template map collection
        */
        class ITemplateMapCollection
        {
            public:
                /**
                * Template entry
                *@note This class encapsulates a template resource ID and accessors for open file and save file
                *      callbacks. Entries are stored in the map
                */
                class ITemplateEntry
                {
                    public:
                        TTemplateAccessor* m_pAccessor;
                        CString            m_DefTemplate;
                        CString            m_Extension;
                        UINT               m_ResID;

                        /**
                        * Constructor
                        *@resID - the resource identifier
                        *@param defTemplate - the default template
                        */
                        ITemplateEntry(UINT resID, const CString& defTemplate) :
                            m_pAccessor(NULL),
                            m_DefTemplate(defTemplate),
                            m_ResID(resID)
                        {
                            GetTemplateString(m_Extension, (int)IEStringIndex::IE_SI_FilterExt);
                        }

                        /**
                        * Constructor
                        *@resID - the resource identifier
                        *@param defTemplate - the default template
                        *@param accessor - the template accessor
                        */
                        ITemplateEntry(UINT                     resID,
                                       const CString&           defTemplate,
                                       const TTemplateAccessor& accessor) :
                            m_pAccessor(NULL),
                            m_DefTemplate(defTemplate),
                            m_ResID(resID)
                        {
                            GetTemplateString(m_Extension, (int)IEStringIndex::IE_SI_FilterExt);
                            m_pAccessor = new TTemplateAccessor(accessor);
                        }

                        /**
                        * Copy constructor
                        *@param other - other object to copy from
                        */
                        ITemplateEntry(const ITemplateEntry& other)
                        {
                            m_pAccessor   = NULL;
                            m_DefTemplate = other.m_DefTemplate;
                            m_Extension   = other.m_Extension;
                            m_ResID       = other.m_ResID;

                            if (other.m_pAccessor)
                                m_pAccessor = new ITemplateAccessor(*other.m_pAccessor);
                        }

                        virtual ~ITemplateEntry()
                        {
                            if (m_pAccessor)
                            {
                                delete m_pAccessor;
                                m_pAccessor = NULL;
                            }
                        }

                        /**
                        * Copy operator
                        *@param other - other object to copy from
                        *@return copy of itself
                        */
                        ITemplateEntry& operator = (const ITemplateEntry& other)
                        {
                            m_pAccessor   = NULL;
                            m_DefTemplate = other.m_DefTemplate;
                            m_Extension   = other.m_Extension;
                            m_nIDRes      = other.m_nIDRes;

                            if (m_pAccessor)
                            {
                                delete m_pAccessor;
                                m_pAccessor = NULL;
                            }

                            if (other.m_pAccessor)
                                m_pAccessor = new ITemplateAccessor(*src.m_pAccessor);

                            return *this;
                        }

                        /**
                        * Gets the template string
                        *@param[out] str - the string which will receive the result on function ends
                        *@param index - the zero-based index to extract from
                        *@return true on success, otherwise false
                        */
                        virtual bool GetTemplateString(CString& str, int index) const
                        {
                            return ::AfxExtractSubString(str, m_DefTemplate, index);
                        }
                };

                typedef CCArray_T <ITemplateEntry*, ITemplateEntry*> ITemplateEntrySet;
                typedef Iterator_T<ITemplateEntry*>                  ITemplateEntryIterator;

                ITemplateEntrySet m_TemplateSet;

                ITemplateMapCollection()
                {}

                virtual ~ITemplateMapCollection()
                {
                    // use the fully qualified name here to avoid to call a pure virtual function on destruction
                    ITemplateMapCollection::DeleteAll();
                }

                /**
                * Adds an entry
                *@param resID - the resource identifier
                *@return true on success, otherwise false
                */
                virtual bool AddEntry(UINT resID)
                {
                    if (resID <= 0)
                        return false;

                    CString defTemplate;
                    defTemplate.LoadString(resID);

                    std::unique_ptr<ITemplateEntry> pEntry(new ITemplateEntry(resID, defTemplate));
                    m_TemplateSet.Add(pEntry.get());
                    pEntry.release();

                    return true;
                }

                /**
                * Adds an entry
                *@param resID - the resource identifier
                *@param accessor - the template accessor to use
                *@return true on success, otherwise false
                */
                virtual bool AddEntry(UINT resID, const TTemplateAccessor& accessor)
                {
                    if (resID <= 0)
                        return false;

                    CString defTemplate;
                    defTemplate.LoadString(resID);

                    std::unique_ptr<ITemplateEntry> pEntry(new ITemplateEntry(resID, defTemplate, accessor));
                    m_TemplateSet.Add(pEntry.get());
                    pEntry.release();

                    return true;
                }

                /**
                * Gets the entry count
                *@return the entry count
                */
                virtual int GetCount() const
                {
                    return m_TemplateSet.GetSize();
                }

                /**
                * Gets a template entry by its resource
                *@param resID - the resource identifier to search
                *@return the template entry, NULL if not found or on error
                */
                virtual ITemplateEntry* GetTemplateEntryByResource(UINT resID) const
                {
                    ITemplateEntryIterator it(&m_TemplateSet);

                    for (ITemplateEntry* pEntry = it.GetFirst(); pEntry; pEntry = it.GetNext())
                        if (pEntry && pEntry->m_ResID == resID)
                            return pEntry;

                    return NULL;
                }

                /**
                * Gets a template entry by its extension
                *@param ext - the extension to search
                *@return the template entry, NULL if not found or on error
                */
                virtual ITemplateEntry* GetTemplateEntryByExtension(const CString& ext) const
                {
                    ITemplateEntryIterator it(&m_TemplateSet);

                    for (ITemplateEntry* pEntry = it.GetFirst(); pEntry; pEntry = it.GetNext())
                        if (pEntry && pEntry->m_Extension == ext)
                            return pEntry;

                    return NULL;
                }

                /**
                * Gets a template entry by its file name
                *@param fileName - the file name to search
                *@return the template entry, NULL if not found or on error
                */
                virtual ITemplateEntry* GetTemplateEntryByFileName(const CString& fileName) const
                {
                    PSS_File file(fileName);
                    return GetTemplateEntryByExtension(file.GetFileExt());
                }

                /**
                * Gets a template identifier by its extension
                *@param ext - the extension to search
                *@return the template identifier, 0 if not found or on error
                */
                virtual UINT GetTemplateIDByExtension(const CString& ext) const
                {
                    ITemplateEntryIterator it(&m_TemplateSet);

                    for (ITemplateEntry* pEntry = it.GetFirst(); pEntry; pEntry = it.GetNext())
                        if (pEntry && pEntry->m_Extension == ext)
                            return pEntry->m_ResID;

                    return 0;
                }

                /**
                * Gets a template identifier by its file name
                *@param fileName - the file name to search
                *@return the template identifier, 0 if not found or on error
                */
                virtual UINT GetTemplateIDByFileName(const CString fileName) const
                {
                    PSS_File file(fileName);
                    return GetTemplateIDByExtension(file.GetFileExt());
                }

                /**
                * Gets a template accessor by its resource identifier
                *@param resID - the resource identifier to search
                *@return the template accessor, NULL if not found or on error
                */
                virtual TTemplateAccessor* GetAccessorByResource(UINT resID) const
                {
                    ITemplateEntry* pEntry = GetTemplateEntryByResource(resID);
                    return (pEntry ? pEntry->m_pAccessor : NULL);
                }

                /**
                * Gets a template accessor by its extension
                *@param ext - the extension to search
                *@return the template accessor, NULL if not found or on error
                */
                virtual TTemplateAccessor* GetAccessorByExtension(const CString& ext) const
                {
                    ITemplateEntry* pEntry = GetTemplateEntryByExtension(ext);
                    return (pEntry ? pEntry->m_pAccessor : NULL);
                }

                /**
                * Gets a template at index
                *@param index - the index
                *@return the template, NULL if not found or on error
                */
                virtual ITemplateEntry* GetTemplateAt(const int index) const
                {
                    if (index >= GetCount())
                        return NULL;

                    return m_TemplateSet.GetAt(index);
                }

                /**
                * Deletes all the entries
                */
                virtual void DeleteAll()
                {
                    ITemplateEntryIterator it(&m_TemplateSet);

                    for (ITemplateEntry* pEntry = it.GetFirst(); pEntry; pEntry = it.GetNext())
                        if (pEntry)
                            delete pEntry;

                    m_TemplateSet.RemoveAll();
                }
        };

        typedef PSS_TemplateDocument<TTemplateAccessor> IThisClass;
        typedef TTemplateAccessor                       IFileOpenWorkspaceAccessor;

        PSS_TemplateDocument()
        {}

        virtual ~PSS_TemplateDocument()
        {}

        /**
        * Gets the template map collection
        *@return the template map collection
        */
        virtual typename PSS_TemplateDocument<TTemplateAccessor>::ITemplateMapCollection& GetTemplateMapCollection() const
        {
            static PSS_TemplateDocument<TTemplateAccessor>::ITemplateMapCollection templateMapCollection;
            return templateMapCollection;
        }

        /**
        * Registers a template
        *@param resID - the resource identifier
        */
        virtual bool RegisterTemplate(UINT resID)
        {
            return GetTemplateMapCollection().AddEntry(resID);
        }

        /**
        * Registers a template
        *@param resID - the resource identifier
        *@param accessor - the template accessor
        */
        virtual bool RegisterTemplate(UINT resID, const TTemplateAccessor& accessor)
        {
            return GetTemplateMapCollection().AddEntry(resID, accessor);
        }

        /**
        * Gets the template count
        *@return the template count
        */
        virtual int GetTemplateCount() const
        {
            return GetTemplateMapCollection().GetCount();
        }

        /**
        * Gets a template by its resource
        *@param resID - the resource identifier to search
        *@return the template, NULL if not found or on error
        */
        virtual typename ITemplateMapCollection::ITemplateEntry* GetTemplateByResource(UINT resID) const
        {
            return GetTemplateMapCollection().GetTemplateEntryByResource(resID);
        }

        /**
        * Gets a template by its extension
        *@param ext - the extension to search
        *@return the template, NULL if not found or on error
        */
        virtual typename ITemplateMapCollection::ITemplateEntry* GetTemplateEntryByExtension(const CString& ext) const
        {
            return GetTemplateMapCollection().GetTemplateEntryByExtension(ext);
        }

        /**
        * Gets a template by its file name
        *@param fileName - the file name to search
        *@return the template, NULL if not found or on error
        */
        virtual typename ITemplateMapCollection::ITemplateEntry* GetTemplateEntryByFileName(const CString& fileName) const
        {
            return GetTemplateMapCollection().GetTemplateEntryByFileName(fileName);
        }

        /**
        * Gets a template itentifier by its extension
        *@param ext - the extension to search
        *@return the template identifier, 0 if not found or on error
        */
        virtual UINT GetTemplateIDByExtension(const CString& ext) const
        {
            return GetTemplateMapCollection().GetTemplateIDByExtension(ext);
        }

        /**
        * Gets a template itentifier by its file name
        *@param fileName - the file name to search
        *@return the template identifier, 0 if not found or on error
        */
        virtual UINT GetTemplateIDByFileName(const CString fileName) const
        {
            return GetTemplateMapCollection().GetTemplateIDByFileName(fileName);
        }

        /**
        * Gets a template at index
        *@param index - the index
        *@return the template, NULL if not found or on error
        */
        virtual typename ITemplateMapCollection::ITemplateEntry* GetTemplateAt(const int index) const
        {
            return GetTemplateMapCollection().GetTemplateAt(index);
        }
};

#endif
